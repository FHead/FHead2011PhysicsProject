#include <map>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraph.h"
#include "TLatex.h"

int main()
{
   TFile FE("A3Expected.root");
   TFile FO("MeowFA3.root");

   TTree *TE = (TTree *)FE.Get("ResultTree");
   TTree *TO = (TTree *)FO.Get("ResultTree");

   float NLL, A3ZZ;
   TE->SetBranchAddress("BestNLLNoPenalty", &NLL);
   TE->SetBranchAddress("A3ZZA1ZZ", &A3ZZ);
   TO->SetBranchAddress("BestNLLNoPenalty", &NLL);
   TO->SetBranchAddress("A3ZZA1ZZ", &A3ZZ);

   TGraph GE;
   TGraph GO;

   int EntryCount;
   vector<pair<double, double> > Sorter;

   EntryCount = TE->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      TE->GetEntry(i);
      Sorter.push_back(pair<double, double>(A3ZZ, NLL / 1000 + 408.0725));
   }
   sort(Sorter.begin(), Sorter.end());
   for(int i = 0; i < (int)Sorter.size(); i++)
      GE.SetPoint(i, Sorter[i].first, Sorter[i].second);
   Sorter.clear();

   EntryCount = TO->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      TO->GetEntry(i);
      Sorter.push_back(pair<double, double>(A3ZZ, NLL - 24.4));
   }
   sort(Sorter.begin(), Sorter.end());
   for(int i = 0; i < (int)Sorter.size(); i++)
      GO.SetPoint(i, Sorter[i].first, Sorter[i].second);
   Sorter.clear();

   GE.SetLineWidth(3);
   GE.SetLineStyle(kDashed);
   GE.SetLineColor(kBlack);

   GO.SetLineWidth(3);
   GO.SetLineStyle(kSolid);
   GO.SetLineColor(kBlack);

   TCanvas C("C", "C", 1024, 1024);

   TH1D HWorld("HWorld", ";A_{3}^{ZZ} / A_{1}^{ZZ};-2 #Delta ln(L)", 100, -20, 20);
   HWorld.SetMinimum(0);
   HWorld.SetMaximum(20);
   HWorld.SetStats(0);
   HWorld.Draw();
   HWorld.GetYaxis()->SetTitleOffset(1.25);

   GO.Draw("l");
   GE.Draw("c");

   TLatex Latex;
   Latex.SetNDC(true);
   Latex.SetTextFont(42);

   Latex.SetTextAlign(11);
   Latex.SetTextSize(0.04);
   Latex.DrawLatex(0.1, 0.91, "CMS");
   
   Latex.SetTextAlign(11);
   Latex.SetTextSize(0.03);
   Latex.DrawLatex(0.19, 0.91, "(preliminary)");
   
   Latex.SetTextAlign(31);
   Latex.SetTextSize(0.03);
   Latex.DrawLatex(0.9, 0.91, "19.7 fb^{-1} (8 TeV) + 5.1 fb^{-1} (7 TeV)");

   TGraph G1;
   G1.SetPoint(0, -1000, 1);
   G1.SetPoint(1, +1000, 1);
   G1.SetLineWidth(2);
   G1.SetLineStyle(9);
   G1.Draw("l");

   Latex.SetNDC(false);
   Latex.SetTextAlign(11);
   Latex.SetTextSize(0.02);
   Latex.DrawLatex(-19.5, 1.10, "68% CL");

   TGraph G2;
   G2.SetPoint(0, -1000, 3.74);
   G2.SetPoint(1, +1000, 3.74);
   G2.SetLineWidth(3);
   G2.SetLineStyle(9);
   G2.Draw("l");
   
   Latex.SetNDC(false);
   Latex.SetTextAlign(11);
   Latex.SetTextSize(0.02);
   Latex.DrawLatex(-19.5, 3.84, "95% CL");

   TLegend Legend(0.15, 0.85, 0.45, 0.65);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&GE, "Expected", "l");
   Legend.AddEntry(&GO, "Observed", "l");
   Legend.Draw();

   C.SaveAs("ScanA3.png");
   C.SaveAs("ScanA3.C");
   C.SaveAs("ScanA3.eps");
   C.SaveAs("ScanA3.pdf");

   return 0;
}


