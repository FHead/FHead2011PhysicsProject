#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TChain.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"

int main();
double GetWeight(TH2D &HMap, double Y, double PT);

int main()
{
   SetStyle();

   PsFileHelper PsFile("ObtainPTWeight.ps");
   PsFile.AddTextPage("Obtain PT weight from gamma to Z");

   TFile FMap("Acceptance.root");

   TH2D *HPassedCount = (TH2D *)FMap.Get("HPassedCount");
   TH2D *HTotalCount = (TH2D *)FMap.Get("HTotalCount");
   HPassedCount->Rebin2D(5, 5);
   HTotalCount->Rebin2D(5, 5);
   HPassedCount->Divide(HTotalCount);

   HPassedCount->SetTitle("Passing percentage");
   HPassedCount->SetStats(0);
   PsFile.AddPlot(HPassedCount, "colz");

   TCanvas CPassedCount("CPassedCount", "", 1024, 1024);
   HPassedCount->Draw("colz");
   CPassedCount.SaveAs("PassingPercentage.png");
   CPassedCount.SaveAs("PassingPercentage.C");
   CPassedCount.SaveAs("PassingPercentage.eps");
   CPassedCount.SaveAs("PassingPercentage.pdf");

   TChain MuTree("MuTree", "Muon Tree");
   MuTree.AddFile("DataSamples/DoubleMu_All.root", TChain::kBigNumber, "ReducedTree");
   MuTree.AddFile("DataSamples/DoubleMu_Run2011B_All.root", TChain::kBigNumber, "ReducedTree");

   double MR, R, MRPhoton, RPhoton, MuonPT, MuonEta, MuonPhi, Muon2PT, Muon2Eta, Muon2Phi, PhotonPT, PhotonEta;
   MuTree.SetBranchAddress("MR", &MR);
   MuTree.SetBranchAddress("R", &R);
   MuTree.SetBranchAddress("MRPhoton", &MRPhoton);
   MuTree.SetBranchAddress("RPhoton", &RPhoton);
   MuTree.SetBranchAddress("MuonPT", &MuonPT);
   MuTree.SetBranchAddress("MuonEta", &MuonEta);
   MuTree.SetBranchAddress("MuonPhi", &MuonPhi);
   MuTree.SetBranchAddress("Muon2PT", &Muon2PT);
   MuTree.SetBranchAddress("Muon2Eta", &Muon2Eta);
   MuTree.SetBranchAddress("Muon2Phi", &Muon2Phi);
   MuTree.SetBranchAddress("PhotonPT", &PhotonPT);
   MuTree.SetBranchAddress("PhotonEta", &PhotonEta);

   TH1D HDiMuonPT("HDiMuonPT", "", 100, 0, 1000);

   int EntryCount = MuTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      MuTree.GetEntry(iEntry);

      if(fabs(MuonEta) > 2.4 || fabs(Muon2Eta) > 2.4)
         continue;
      if(MuonPT < 20 || Muon2PT < 20)
         continue;

      FourVector Muon1P, Muon2P;
      Muon1P.SetPtEtaPhi(MuonPT, MuonEta, MuonPhi);
      Muon2P.SetPtEtaPhi(Muon2PT, Muon2Eta, Muon2Phi);

      FourVector Dimuon = Muon1P + Muon2P;
   }

   FMap.Close();

   PsFile.Close();
}

double GetWeight(TH2D &HMap, double Y, double PT)
{
   Y = fabs(Y);
   if(Y > 1.5)
      return 0;

   int Bin = HMap.FindBin(Y, PT);

   double Efficiency = HMap.GetBinContent(Bin);
   if(Efficiency == 0)
      return 1;

   return 1 / HMap.GetBinContent(Bin);
}





