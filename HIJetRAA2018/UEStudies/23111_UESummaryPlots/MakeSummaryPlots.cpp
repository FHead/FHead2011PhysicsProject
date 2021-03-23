#include <iostream>
#include <vector>
using namespace std;

#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "DataHelper.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
TGraphAsymmErrors TranscribeEtaScan(DataHelper &DHFile, string Prefix,
   int RBin, int CBin);
double FindMax(TGraphAsymmErrors &G);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);
   string DHFileNameMC      = CL.Get("MC");
   string DHFileNameMCEta   = CL.Get("MCEta");
   string DHFileNameData    = CL.Get("Data");
   string DHFileNameDataEta = CL.Get("DataEta");
   string Output            = CL.Get("Output");

   DataHelper DHFileMC(DHFileNameMC);
   DataHelper DHFileMCEta(DHFileNameMCEta);
   // DataHelper DHFileData(DHFileNameData);
   // DataHelper DHFileDataEta(DHFileNameDataEta);

   PdfFileHelper PdfFile(Output);
   PdfFile.AddTextPage("Random cone plots");

   vector<double> Radius{0.15, 0.20, 0.30, 0.40, 0.50, 0.60, 0.80, 1.00, 1.20};
   
   // Do eta scan plots
   {
      vector<double> Centrality{0.0, 0.1, 0.3, 0.5, 0.8};

      for(int iR = 0; iR < (int)Radius.size(); iR++)
      {
         for(int iC = 0; iC < 4; iC++)
         {
            TGraphAsymmErrors GMC       = TranscribeEtaScan(DHFileMC, "RhoEta", iR, iC);
            TGraphAsymmErrors GMCPhi    = TranscribeEtaScan(DHFileMC, "RhoPhiEta", iR, iC);
            TGraphAsymmErrors GMCEta    = TranscribeEtaScan(DHFileMCEta, "RhoEta", iR, iC);
            TGraphAsymmErrors GMCEtaPhi = TranscribeEtaScan(DHFileMCEta, "RhoPhiEta", iR, iC);

            GMCPhi.SetMarkerColor(kBlue);
            GMCPhi.SetLineColor(kBlue);
            GMCEta.SetMarkerColor(kGreen + 3);
            GMCEta.SetLineColor(kGreen + 3);
            GMCEtaPhi.SetMarkerColor(kRed);
            GMCEtaPhi.SetLineColor(kRed);

            double Max = FindMax(GMC);
            Max = max(Max, FindMax(GMCPhi));
            Max = max(Max, FindMax(GMCEta));
            Max = max(Max, FindMax(GMCEtaPhi));

            TCanvas Canvas;

            TH2D HWorld("HWorld", "", 100, 0, 3, 100, 0, Max * 1.2);
            HWorld.SetTitle(Form("Centrality: [%d%, %d%], R = %.02f",
               int(Centrality[iC] * 100), int(Centrality[iC+1] * 100), Radius[iR]));
            HWorld.GetXaxis()->SetTitle("|#eta|");
            HWorld.GetYaxis()->SetTitle("#sigma");
            HWorld.SetStats(0);

            TLegend Legend(0.15, 0.15, 0.45, 0.35);
            Legend.SetTextFont(42);
            Legend.SetTextSize(0.035);
            Legend.SetFillStyle(0);
            Legend.SetBorderSize(0);
            Legend.AddEntry(&GMC, "MC (no phi)", "lp");
            Legend.AddEntry(&GMCPhi, "MC (phi-modulated)", "lp");
            Legend.AddEntry(&GMCEta, "MC (reduced eta bins, no phi)", "lp");
            Legend.AddEntry(&GMCEtaPhi, "MC (reduced eta bins, phi-modulated)", "lp");

            HWorld.Draw("axis");
            GMC.Draw("p");
            GMCPhi.Draw("p");
            GMCEta.Draw("p");
            GMCEtaPhi.Draw("p");
            Legend.Draw();

            PdfFile.AddCanvas(Canvas);
         }
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

TGraphAsymmErrors TranscribeEtaScan(DataHelper &DHFile, string Prefix,
   int RBin, int CBin)
{
   vector<string> States = DHFile.GetListOfKeys();

   TGraphAsymmErrors G;

   for(string State : States)
   {
      if(State.find(Prefix + "_") != 0)   // we want the right prefix
         continue;
      if(State.find(Form("C%d", CBin)) == string::npos)   // wrong centrality bin
         continue;
      if(State.find(Form("R%d", RBin)) == string::npos)   // wrong radius bin
         continue;

      // we found a valid state!

      int N = G.GetN();
      double EtaMin     = DHFile[State]["EtaMin"].GetDouble();
      double EtaMax     = DHFile[State]["EtaMax"].GetDouble();
      double Sigma      = DHFile[State]["P2"].GetDouble();
      double SigmaError = DHFile[State]["P2Error"].GetDouble();

      G.SetPoint(N, (EtaMin + EtaMax) / 2, Sigma);
      G.SetPointError(N, (EtaMax - EtaMin) / 2, (EtaMax - EtaMin) / 2, SigmaError, SigmaError);
   }

   return G;
}

double FindMax(TGraphAsymmErrors &G)
{
   double Max = 0;
   for(int i = 0; i < G.GetN(); i++)
   {
      double x, y;
      G.GetPoint(i, x, y);
      if(y > Max)
         Max = y;
   }
   return Max;
}


