#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "SetStyle.h"

#include "AngleConversion.h"

int main()
{
   SetThesisRegularStyle();

   TFile F1("gg.root");
   TFile F2("qq.root");

   TTree *T1 = (TTree *)F1.Get("Tree");
   TTree *T2 = (TTree *)F2.Get("Tree");

   TH1D HGG("HGG", ";m_{4l};a.u.", 30, 100, 500);
   TH1D HQQ("HQQ", ";m_{4l};a.u.", 30, 100, 500);

   HGG.Sumw2();
   HQQ.Sumw2();

   EventParameters Event;

   T1->SetBranchAddress("B1", &Event.HMass);
   T1->SetBranchAddress("B2", &Event.ZMass);
   T1->SetBranchAddress("B3", &Event.Z2Mass);
   T1->SetBranchAddress("B4", &Event.Phi0);
   T1->SetBranchAddress("B5", &Event.Theta0);
   T1->SetBranchAddress("B6", &Event.Phi);
   T1->SetBranchAddress("B7", &Event.Theta1);
   T1->SetBranchAddress("B8", &Event.Theta2);
   T1->SetBranchAddress("B9", &Event.YH);
   T1->SetBranchAddress("B10", &Event.PTH);
   T1->SetBranchAddress("B11", &Event.PhiH);
   T1->SetBranchAddress("B12", &Event.PhiOffset);

   T2->SetBranchAddress("B1", &Event.HMass);
   T2->SetBranchAddress("B2", &Event.ZMass);
   T2->SetBranchAddress("B3", &Event.Z2Mass);
   T2->SetBranchAddress("B4", &Event.Phi0);
   T2->SetBranchAddress("B5", &Event.Theta0);
   T2->SetBranchAddress("B6", &Event.Phi);
   T2->SetBranchAddress("B7", &Event.Theta1);
   T2->SetBranchAddress("B8", &Event.Theta2);
   T2->SetBranchAddress("B9", &Event.YH);
   T2->SetBranchAddress("B10", &Event.PTH);
   T2->SetBranchAddress("B11", &Event.PhiH);
   T2->SetBranchAddress("B12", &Event.PhiOffset);

   int EntryCount = T1->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T1->GetEntry(iE);

      if(Event.HMass < 100 || Event.HMass > 500)
         continue;
      if(Event.ZMass < 40 || Event.Z2Mass < 12)
         continue;

      LeptonVectors Lepton = ConvertAnglesToVectorsRoberto(Event);
      if(Lepton.Lepton11.GetPT() < 5)   continue;
      if(Lepton.Lepton12.GetPT() < 5)   continue;
      if(Lepton.Lepton21.GetPT() < 5)   continue;
      if(Lepton.Lepton22.GetPT() < 5)   continue;

      HGG.Fill(Event.HMass);
   }
   
   EntryCount = T2->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T2->GetEntry(iE);

      if(Event.HMass < 100 || Event.HMass > 500)
         continue;
      if(Event.ZMass < 40 || Event.Z2Mass < 12)
         continue;

      LeptonVectors Lepton = ConvertAnglesToVectorsRoberto(Event);
      if(Lepton.Lepton11.GetPT() < 5)   continue;
      if(Lepton.Lepton12.GetPT() < 5)   continue;
      if(Lepton.Lepton21.GetPT() < 5)   continue;
      if(Lepton.Lepton22.GetPT() < 5)   continue;

      HQQ.Fill(Event.HMass);
   }

   // TCanvas C("C", "C", 1024, 1024);
   TCanvas C;

   HGG.Divide(&HQQ);

   HGG.GetXaxis()->SetNdivisions(505);
   HGG.GetYaxis()->SetNdivisions(505);
   
   double r200 = HGG.GetBinContent(HGG.FindBin(200));
   HGG.Scale(1 / r200 * 0.3);
   
   HGG.SetStats(0);
   // HGG.GetXaxis()->SetTitleOffset(1.1);
   HGG.GetYaxis()->SetTitleOffset(1.4);
   // HGG.GetYaxis()->SetTitle("r(m_{4l}) / r(m_{4l} = 200)");
   HGG.GetYaxis()->SetTitle("#sigma(gg#rightarrowZZ)/#sigma(q#bar{q}#rightarrowZZ)");
   HGG.SetLineWidth(2);
   HGG.SetMinimum(0.00);
   // HGG.SetMaximum(1.18);
   HGG.SetMaximum(0.48);
   HGG.SetMarkerStyle(20);
   HGG.SetMarkerSize(1.8);
   HGG.Draw("P");

   C.SaveAs("CurrentHiggsProperty-Width-BackgroundComposition.png");
   C.SaveAs("CurrentHiggsProperty-Width-BackgroundComposition.C");
   C.SaveAs("CurrentHiggsProperty-Width-BackgroundComposition.eps");
   C.SaveAs("CurrentHiggsProperty-Width-BackgroundComposition.pdf");

   return 0;
}





