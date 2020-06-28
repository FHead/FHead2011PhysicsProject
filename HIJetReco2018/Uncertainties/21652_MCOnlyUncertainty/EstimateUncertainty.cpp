#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string AlgorithmName = CL.Get("Algorithm", "ak4pf");
   string OutputFileName = CL.Get("Output");
   string MonitorName = CL.Get("Plots", "plots.pdf");
   vector<double> PTBinning = CL.GetDoubleVector("PTBinning", vector<double>());
   double Scale = CL.GetDouble("Scale");
   double Constant = CL.GetDouble("Constant");
   double Constant2 = CL.GetDouble("Constant2", Constant);
   double Cutoff = CL.GetDouble("Cutoff");
   double Cutoff2 = CL.GetDouble("Cutoff2", 30);

   // Graph name = ak4pf/grMean_ak4pf_14 
   string GraphNameBase = AlgorithmName + "/" + "grMean_" + AlgorithmName + "_";

   // Ansatz 1/log(PT).  We do this for all eta bins separately

   TFile File(InputFileName.c_str());

   TGraphErrors *G = (TGraphErrors *)File.Get((GraphNameBase + "0").c_str());

   vector<double> X;
   for(int i = 0; i < G->GetN(); i++)
   {
      double x, y;
      G->GetPoint(i, x, y);
      X.push_back(x);
   }

   vector<double> BinEdges;
   BinEdges.push_back(-4.0);
   for(int i = 1; i < G->GetN(); i++)
      BinEdges.push_back((X[i-1] + X[i]) / 2);
   BinEdges.push_back(4.0);
   sort(BinEdges.begin(), BinEdges.end());

   vector<double> P0(X.size());
   vector<double> P1(X.size());
   vector<double> P2(X.size());

   for(int i = 0; i < (int)PTBinning.size() - 1; i++)
   {
      double PT = PTBinning[i+1];
      TGraphErrors *G = (TGraphErrors *)File.Get(Form("%s%d", GraphNameBase.c_str(), i));

      for(int j = 0; j < (int)G->GetN(); j++)
      {
         double x, y, ex, ey;
         G->GetPoint(j, x, y);
         ey = G->GetErrorY(j);

         if(y < 0.2 || y > 1.8)
            continue;
         if(ey > 0.1)
            continue;

         double yn;
         G->GetPoint(j + 1, x, yn);
         if(j < G->GetN() - 1 && yn < 0.1)
            continue;
         G->GetPoint(j - 1, x, yn);
         if(j > 0 && yn < 0.1)
            continue;

         double L = fabs(1 - y) * log(PT);
         if(L > P0[j])
            P0[j] = L;
         if(PT > Cutoff && L > P1[j])
            P1[j] = L;
         if(PT > Cutoff2 && L > P2[j])
            P2[j] = L;
      }
   }

   // Now we make some sanity check plots
   PdfFileHelper PdfFile(MonitorName);
   PdfFile.AddTextPage("MC Uncertainties");

   for(int i = 0; i < (int)PTBinning.size() - 1; i++)
   {
      double PT = PTBinning[i+1];
      TGraphErrors *G = (TGraphErrors *)File.Get(Form("%s%d", GraphNameBase.c_str(), i));

      TGraph G1a, G1b, G2a, G2b;
      for(int j = 0; j < (int)G->GetN(); j++)
      {
         double x, y;
         G->GetPoint(j, x, y);

         if(PT > Cutoff2)
         {
            G1a.SetPoint(j, x, 1 + P2[j] / log(PT) * Scale);
            G1b.SetPoint(j, x, 1 - P2[j] / log(PT) * Scale);
         }
         else if(PT > Cutoff)
         {
            G1a.SetPoint(j, x, 1 + P1[j] / log(PT) * Scale);
            G1b.SetPoint(j, x, 1 - P1[j] / log(PT) * Scale);
         }
         else
         {
            G1a.SetPoint(j, x, 1 + P0[j] / log(PT) * Scale);
            G1b.SetPoint(j, x, 1 - P0[j] / log(PT) * Scale);
         }
         if(x > -2.5 && x < 2.5)
         {
            G2a.SetPoint(j, x, 1 + Constant);
            G2b.SetPoint(j, x, 1 - Constant);
         }
         else
         {
            G2a.SetPoint(j, x, 1 + Constant2);
            G2b.SetPoint(j, x, 1 - Constant2);
         }
      }

      G1a.SetMarkerColor(kRed);
      G1b.SetMarkerColor(kRed);
      G2a.SetMarkerColor(kGreen);
      G2b.SetMarkerColor(kGreen);
      
      G1a.SetLineColor(kRed);
      G1b.SetLineColor(kRed);
      G2a.SetLineColor(kGreen);
      G2b.SetLineColor(kGreen);

      TCanvas Canvas;

      TH2D HWorld("HWorld", Form("PT %.0f - %.0f;eta;", PTBinning[i], PTBinning[i+1]),
         100, -4, 4, 100, 0.8, 1.2);
      HWorld.SetStats(0);
      HWorld.Draw();

      G->Draw("pl");
      G1a.Draw("pl");
      G1b.Draw("pl");
      G2a.Draw("pl");
      G2b.Draw("pl");

      PdfFile.AddCanvas(Canvas);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   ofstream out(OutputFileName);

   out << "{1 JetEta 1 JetPt \"\" Correction Uncertainty}" << endl;
   for(int i = 0; i < (int)X.size(); i++)
   {
      out << BinEdges[i] << " " << BinEdges[i+1];
      out << " " << PTBinning.size() * 3;
      for(int j = 0; j < (int)PTBinning.size(); j++)
      {
         double L = P0[i];
         if(PTBinning[j] > Cutoff)
            L = P1[i];
         if(PTBinning[j] > Cutoff2)
            L = P2[i];

         double U = L / log(PTBinning[j]) * Scale;
         if(X[i] < 2.5 && X[i] > -2.5)
            U = sqrt(U * U + Constant * Constant);
         else
            U = sqrt(U * U + Constant2 * Constant2);

         out << " " << PTBinning[j] << " " << U << " " << U;
      }
      out << endl;
   }

   out.close();

   File.Close();

   return 0;
}



