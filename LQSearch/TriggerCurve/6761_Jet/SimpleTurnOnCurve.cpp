#include <string>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TROOT.h"
#include "TStyle.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main()
{
   SetStyle();

   TFile InputFile("ReducedTree.root");
   TTree *Tree = (TTree *)InputFile.Get("OutputTree");

   double MR;
   double R;
   bool PassDiJetAve150;
   bool PassR020MR500;
   
   Tree->SetBranchAddress("MR", &MR);
   Tree->SetBranchAddress("R", &R);
   Tree->SetBranchAddress("PassDiJetAve150", &PassDiJetAve150);
   Tree->SetBranchAddress("PassR020MR500", &PassR020MR500);

   TH1D HMRPassDiJetAve150("HMRPassDiJetAve150", "MR, passing dijet ave. 150 trigger, R > 0.25;MR", 20, 0, 1500);
   TH1D HMRPassDiJetAve150AndR020MR500("HMRPassDiJetAve150AndR020MR500",
      "MR, passing dijet ave. 150 trigger AND R0.2/MR500 trigger, R > 0.25;MR", 20, 0, 1500);
   TH1D HRPassDiJetAve150("HRPassDiJetAve150", "R, passing dijet ave. 150 trigger, MR > 550;R", 20, 0, 0.4);
   TH1D HRPassDiJetAve150AndR020MR500("HRPassDiJetAve150AndR020MR500",
      "R, passing dijet ave. 150 trigger AND R0.2/MR500 trigger, MR > 550;R", 20, 0, 0.4);

   PsFileHelper PsFile("SimpleTurnOnCurve.ps");
   PsFile.AddTextPage("Simple turn-on curve from jet dataset");

   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      if(PassDiJetAve150 == true && R > 0.25)
         HMRPassDiJetAve150.Fill(MR);
      if(PassDiJetAve150 == true && PassR020MR500 == true && R > 0.25)
         HMRPassDiJetAve150AndR020MR500.Fill(MR);
      if(PassDiJetAve150 == true && MR > 550)
         HRPassDiJetAve150.Fill(R);
      if(PassDiJetAve150 == true && PassR020MR500 == true && MR > 550)
         HRPassDiJetAve150AndR020MR500.Fill(R);
   }

   PsFile.AddPlot(HMRPassDiJetAve150);
   PsFile.AddPlot(HMRPassDiJetAve150AndR020MR500);

   TGraphAsymmErrors HMRTurnOnR020MR500;
   HMRTurnOnR020MR500.BayesDivide(&HMRPassDiJetAve150AndR020MR500, &HMRPassDiJetAve150);
   HMRTurnOnR020MR500.SetTitle("Turn-on of R0.2/MR500 with respect to dijet average 150; MR (R > 0.25)");
   PsFile.AddPlot(HMRTurnOnR020MR500, "ape");

   TCanvas C1;
   HMRTurnOnR020MR500.Draw("ape");
   C1.SaveAs("MRTurnOn.png");
   
   PsFile.AddPlot(HRPassDiJetAve150);
   PsFile.AddPlot(HRPassDiJetAve150AndR020MR500);

   TGraphAsymmErrors HRTurnOnR020MR500;
   HRTurnOnR020MR500.BayesDivide(&HRPassDiJetAve150AndR020MR500, &HRPassDiJetAve150);
   HRTurnOnR020MR500.SetTitle("Turn-on of R0.2/MR500 with respect to dijet average 150; R (MR > 550)");
   PsFile.AddPlot(HRTurnOnR020MR500, "ape");

   TCanvas C2;
   HRTurnOnR020MR500.Draw("ape");
   C2.SaveAs("RTurnOn.png");

   TCanvas C3("C3", "C3", 1024, 512);
   C3.Divide(2);
   C3.cd(1);
   HMRTurnOnR020MR500.Draw("ape");
   C3.cd(2);
   HRTurnOnR020MR500.Draw("ape");
   C3.SaveAs("MRAndRTurnOnForR020MR500.png");
   C3.SaveAs("MRAndRTurnOnForR020MR500.C");
   C3.SaveAs("MRAndRTurnOnForR020MR500.eps");

   InputFile.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}






