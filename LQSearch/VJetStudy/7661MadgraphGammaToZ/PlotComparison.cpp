#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper2.h"

int main();
double GetCorrectionFactor(double PT);

int main()
{
   double R2Cuts[] = {0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4};

   TFile F1("PhotonAll.root");
   TFile F2("ZAll.root");

   TTree *Tree1 = (TTree *)F1.Get("Tree");
   TTree *Tree2 = (TTree *)F2.Get("Tree");

   double PT, Y, MR, R;
   Tree1->SetBranchAddress("TreePT", &PT);
   Tree1->SetBranchAddress("TreeY", &Y);
   Tree1->SetBranchAddress("TreeMR", &MR);
   Tree1->SetBranchAddress("TreeR", &R);
   Tree2->SetBranchAddress("TreePT", &PT);
   Tree2->SetBranchAddress("TreeY", &Y);
   Tree2->SetBranchAddress("TreeMR", &MR);
   Tree2->SetBranchAddress("TreeR", &R);

   PsFileHelper PsFile("ReweightingComparison.ps");
   PsFile.AddTextPage("See if reweighting works");

   vector<string> Explanation;
   Explanation.push_back("We see that PT spectra of gamma jet and Z jet are different");
   Explanation.push_back("Therefore MR distributions are different");
   Explanation.push_back("");
   Explanation.push_back("Try to obtain event weight as a function of PT");
   Explanation.push_back("and see if gamma jet reproduced Z jet");
   PsFile.AddTextPage(Explanation);

   TH1D HWeight("HWeight", "Event weight", 100, 0, 200);
   for(int i = 1; i <= HWeight.GetNbinsX(); i++)
      HWeight.SetBinContent(i, GetCorrectionFactor(HWeight.GetBinCenter(i)));
   HWeight.SetStats(0);
   PsFile.AddPlot(HWeight, "", false);

   for(int iCut = 0; iCut < 7; iCut++)
   {
      TH1D HMRZ(Form("MRZ%d", iCut), "MR from Z", 50, 0, 1000);
      TH1D HMRA(Form("MRA%d", iCut), "MR from A", 50, 0, 1000);
      TH1D HMRAWeighted(Form("MRAWeighted%d", iCut), "MR from A (weighted)", 50, 0, 1000);

      HMRZ.SetLineWidth(2);
      HMRA.SetLineWidth(2);
      HMRAWeighted.SetLineWidth(2);

      HMRZ.SetLineColor(kBlue);
      HMRA.SetLineColor(kRed);
      HMRAWeighted.SetLineColor(kGreen);

      HMRZ.SetStats(0);
      HMRA.SetStats(0);
      HMRAWeighted.SetStats(0);

      HMRAWeighted.Sumw2();

      int EntryCount = Tree1->GetEntries();
      for(int iEntry = 0; iEntry < EntryCount; iEntry++)
      {
         Tree1->GetEntry(iEntry);

         if(Y < -2 || Y > 2)        continue;
         if(PT < 30 || PT > 150)    continue;
         if(R * R < R2Cuts[iCut])   continue;

         HMRA.Fill(MR);
         HMRAWeighted.Fill(MR, GetCorrectionFactor(PT));
      }

      EntryCount = Tree2->GetEntries();
      for(int iEntry = 0; iEntry < EntryCount; iEntry++)
      {
         Tree2->GetEntry(iEntry);

         if(Y < -2 || Y > 2)        continue;
         if(PT < 30 || PT > 150)    continue;
         if(R * R < R2Cuts[iCut])   continue;

         HMRZ.Fill(MR);
      }

      TCanvas C;
      HMRZ.SetTitle(Form("M_{R}, R^{2} > %.2f, PT_{V} = 30-150, |y_{V}| < 2", R2Cuts[iCut]));
      HMRZ.GetXaxis()->SetTitle("M_{R}");
      HMRZ.Draw();
      HMRA.Draw("same");
      HMRAWeighted.Draw("same");

      TLegend Legend(0.46, 0.57, 0.87, 0.85);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.SetTextFont(42);
      Legend.AddEntry(&HMRZ, "Z(#nu#nu) + jet", "l");
      Legend.AddEntry(&HMRA, "Photon + jet", "l");
      Legend.AddEntry(&HMRAWeighted, "Photon + jet, reweighted", "l");
      Legend.Draw();

      C.SetLogy();
      PsFile.AddCanvas(C);
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F2.Close();
   F1.Close();
}

double GetCorrectionFactor(double PT)
{
   if(PT < 30)
      return 0;

   // return (exp(3.63896 - 0.0681001 * PT) + exp(1.71994 - 0.0291704 * PT)) / (exp(4.62515 - 0.0840729 * PT) + exp(0.76950 - 0.0348133 * PT)) * 0.4;
   return (exp(8.86102 - 0.0623860 * PT) + exp(6.60672 - 0.0262230 * PT)) / (exp(9.93207 - 0.0846930 * PT) + exp(6.05542 - 0.0337726 * PT)) * 0.4;
}



