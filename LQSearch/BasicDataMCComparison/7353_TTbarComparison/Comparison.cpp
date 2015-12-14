#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraph.h"

#include "PlotHelper2.h"

int main()
{
   TFile F1("MuTTbar.root");
   TFile F2("ElectronTTbar.root");

   TTree *T1 = (TTree *)F1.Get("MRTree");
   TTree *T2 = (TTree *)F2.Get("MRTree");

   TH1D H1("H1", "R^{2}, MR > 400;R^{2}", 25, 0, 1);
   TH1D H2("H2", "R^{2}, MR > 400;R^{2}", 25, 0, 1);

   H1.Sumw2();
   H2.Sumw2();

   double MR = 0;
   double R = 0;
   double Factor = 0;
   T1->SetBranchAddress("MR", &MR);
   T1->SetBranchAddress("R", &R);
   T1->SetBranchAddress("Factor", &Factor);
   T2->SetBranchAddress("MR", &MR);
   T2->SetBranchAddress("R", &R);
   T2->SetBranchAddress("Factor", &Factor);

   int EntryCount = T1->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      T1->GetEntry(i);

      if(MR > 400)
         H1.Fill(R * R, Factor);
   }

   EntryCount = T2->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      T2->GetEntry(i);

      if(MR > 400)
         H2.Fill(R * R, Factor);
   }

   PsFileHelper PsFile("Yay.ps");
   PsFile.AddTextPage("Yay");

   PsFile.AddPlot(H1, "", true);
   PsFile.AddPlot(H2, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   TCanvas Canvas("Canvas", "Canvas", 1024, 1024 + 512);

   TPad C6_1("C6_1", "C6_1",0.009803922,0.33,0.9892157,0.9908759);
   C6_1.Draw();
   C6_1.cd();

   // H1.Scale(1.0 / H1.Integral());
   // H2.Scale(1.0 / H2.Integral());

   H1.SetLineColor(kBlue);
   H2.SetLineColor(kRed);

   H1.SetLineWidth(2);
   H2.SetLineWidth(2);

   H1.SetStats(0);
   H2.SetStats(0);

   H1.Draw();
   H2.Draw("same");

   C6_1.SetLogy();
   C6_1.Modified();
   Canvas.cd();
   TPad C6_2("C6_2", "C6_2",0.009803922,0.0091241,0.9892157,0.33);
   C6_2.Draw();
   C6_2.cd();

   TH1D *H3 = (TH1D *)H1.Clone("H3");
   H3->SetTitle("");
   H3->Divide(&H2);
   H3->SetMinimum(0);
   H3->SetMaximum(3);
   H3->Fit("pol1");
   H3->Draw();

   TGraph Line;
   Line.SetPoint(0, 0, 1);
   Line.SetPoint(1, 1, 1);
   Line.Draw("l");

   // C6_2.SetLogy();
   C6_2.Modified();

   Canvas.SetLogy();
   Canvas.SaveAs("TTbarComparison.png");
   Canvas.SaveAs("TTbarComparison.C");
   Canvas.SaveAs("TTbarComparison.eps");
   Canvas.SaveAs("TTbarComparison.pdf");
}




