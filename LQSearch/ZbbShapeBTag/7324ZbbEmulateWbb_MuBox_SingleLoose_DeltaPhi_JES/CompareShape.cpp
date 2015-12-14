#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TLegend.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main()
{
   SetStyle();

   TFile F("ZbbPlots.root");

   TTree *TreeUp = (TTree *)F.Get("MRTreeUp");
   TTree *TreeDown = (TTree *)F.Get("MRTreeDown");

   TH1D HistUp("HistUp", ";MR (GeV)", 25, 400, 2000);
   TH1D HistDown("HistDown", ";MR (GeV)", 25, 400, 2000);

   double MR = 0;
   double R = 0;
   TreeUp->SetBranchAddress("MR", &MR);
   TreeUp->SetBranchAddress("R", &R);
   TreeDown->SetBranchAddress("MR", &MR);
   TreeDown->SetBranchAddress("R", &R);

   int EntryCount = TreeUp->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      TreeUp->GetEntry(i);

      if(R * R > 0.25)
         HistUp.Fill(MR);
   }
   
   EntryCount = TreeDown->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      TreeDown->GetEntry(i);

      if(R * R > 0.25)
         HistDown.Fill(MR);
   }

   HistUp.SetStats(0);
   HistDown.SetStats(0);

   HistUp.SetLineWidth(2);
   HistDown.SetLineWidth(2);

   HistUp.SetLineColor(kRed);
   HistDown.SetLineColor(kBlue);

   TLegend legend(0.5, 0.8, 0.8, 0.6);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
   legend.AddEntry(&HistUp, "JES Up", "l");
   legend.AddEntry(&HistDown, "JES Down", "l");

   TCanvas C("C", "", 1024, 1024);
   HistUp.Draw();
   HistDown.Draw("same");
   legend.Draw();
   C.SetLogy();
   AddCMSSimulation(0.1, 0.92);
   C.SaveAs("JESComparison.png");
   C.SaveAs("JESComparison.C");
   C.SaveAs("JESComparison.eps");
   C.SaveAs("JESComparison.pdf");

   F.Close();

   return 0;
}





