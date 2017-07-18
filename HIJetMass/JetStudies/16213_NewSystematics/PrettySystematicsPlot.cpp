#include <iostream>
#include <vector>
using namespace std;

#include "TH2D.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   string Suffix = "C0_P1";
   int SD = 7;

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " Suffix SD" << endl;
      return -1;
   }

   Suffix = argv[1];
   SD = atoi(argv[2]);

   SetThesisStyle();

   double Min = 0.0;
   double Max = 0.4;
   double Bin = 20;
   double SysBin = 160;

   int N = 12;
   vector<string> FileNames(N), Labels(N);
   
   FileNames[0]  = "OutputFile_Ghost_%d.root";      Labels[0]  = "Ghost Area";
   FileNames[1]  = "OutputFile_JER_%d.root";        Labels[1]  = "JER";
   FileNames[2]  = "OutputFile_JetEta_%d.root";     Labels[2]  = "JetEta";
   FileNames[3]  = "OutputFile_MB2_%d.root";        Labels[3]  = "Spectrum";
   FileNames[4]  = "OutputFile_PTScale_%d.root";    Labels[4]  = "PTScale";
   FileNames[5]  = "OutputFile_Rho_%d.root";        Labels[5]  = "Rho";
   FileNames[6]  = "OutputFile_NewSmear_%d.root";   Labels[6]  = "Smear";
   FileNames[7]  = "OutputFile_DR_%d.root";         Labels[7]  = "DR";
   FileNames[8]  = "OutputFile_Range_%d.root";      Labels[8]  = "Range";
   FileNames[9]  = "OutputFile_Trigger_%d.root";    Labels[9]  = "Trigger";
   FileNames[10] = "OutputFile_QuarkGluon_%d.root"; Labels[10] = "QuarkGluon";
   FileNames[11] = "OutputFile_MassScale_%d.root";  Labels[11] = "MassScale";
   
   vector<TGraph *> Graphs;

   for(int i = 0; i < N; i++)
   {
      TFile F(Form(FileNames[i].c_str(), SD));
      TGraphAsymmErrors *E = (TGraphAsymmErrors *)F.Get(Form("GRatio_%s", Suffix.c_str()));

      if(E == NULL)
      {
         Graphs.push_back(NULL);
         continue;
      }

      TGraph *G = new TGraph;

      for(int j = 0; j < SysBin; j++)
      {
         double BinCenter = (j + 0.5) / SysBin * (Max - Min) + Min;
         int S = (int)((BinCenter - Min) / (Max - Min) * SysBin);

         G->SetPoint(j, BinCenter, 100 * (exp(E->GetErrorYhigh(S)) - 1));
      }

      Graphs.push_back(G);

      F.Close();
   }

   TCanvas C;

   TH2D HWorld("HWorld", ";Mass/PT;%", 100, 0.00, 0.27, 100, 0, 100);
   HWorld.SetStats(0);

   HWorld.Draw();

   TLegend Legend(0.3, 0.85, 0.6, 0.35);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);

   int Colors[] = {kBlack, kRed, kGreen - 3, kYellow + 3, kMagenta, kCyan - 3,
      kBlue, kGray, kGreen, kYellow, kMagenta + 3, kGreen + 3};

   for(int i = 0; i < N; i++)
   {
      if(Graphs[i] == NULL)
         continue;

      Graphs[i]->SetLineColor(Colors[i]);
      Graphs[i]->SetMarkerColor(Colors[i]);
      Graphs[i]->Draw("pl");

      Legend.AddEntry(Graphs[i], Labels[i].c_str(), "pl");
   }
   
   Legend.Draw();

   // C.SaveAs(Form("Plots/SystematicsSummaryPlots_%s_%d.png", Suffix.c_str(), SD));
   // C.SaveAs(Form("Plots/SystematicsSummaryPlots_%s_%d.C",   Suffix.c_str(), SD));
   // C.SaveAs(Form("Plots/SystematicsSummaryPlots_%s_%d.eps", Suffix.c_str(), SD));
   C.SaveAs(Form("Plots/SystematicsSummaryPlots_%s_%d.pdf", Suffix.c_str(), SD));

   return 0;
}







