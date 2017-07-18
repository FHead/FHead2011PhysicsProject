#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main()
{
   SetThesisStyle();

   double CentralityMin = 0, CentralityMax = 0.1;
   double EtaMin = 0.0, EtaMax = 0.5;
   double PTMin = 200;

   TFile FPP("PP.root");
   TFile FAA("AA.root");
   TFile FMB("MBCymbal.root");

   TTree *TPP = (TTree *)FPP.Get("T");
   TTree *TAA = (TTree *)FAA.Get("T");
   TTree *TMB = (TTree *)FMB.Get("Tree");

   int PPEntryCount = TPP->GetEntries();
   int AAEntryCount = TAA->GetEntries();
   int MBEntryCount = TMB->GetEntries();

   int PFCount;
   double PFPT[1000], PFEta[1000], PFPhi[1000];
   double JetPT, JetEta, JetPhi;
   double Centrality;

   double Rho, Eta, PT;

   TPP->SetBranchAddress("PFCount", &PFCount);
   TPP->SetBranchAddress("PFPT", &PFPT);
   TPP->SetBranchAddress("PFEta", &PFEta);
   TPP->SetBranchAddress("PFPhi", &PFPhi);
   TPP->SetBranchAddress("JetPT", &JetPT);
   TPP->SetBranchAddress("JetEta", &JetEta);
   TPP->SetBranchAddress("JetPhi", &JetPhi);
   
   TAA->SetBranchAddress("PFCount", &PFCount);
   TAA->SetBranchAddress("PFPT", &PFPT);
   TAA->SetBranchAddress("PFEta", &PFEta);
   TAA->SetBranchAddress("PFPhi", &PFPhi);
   TAA->SetBranchAddress("JetPT", &JetPT);
   TAA->SetBranchAddress("JetEta", &JetEta);
   TAA->SetBranchAddress("JetPhi", &JetPhi);
   TAA->SetBranchAddress("Centrality", &Centrality);

   TMB->SetBranchAddress("Rho", &Rho);
   TMB->SetBranchAddress("Eta", &Eta);
   TMB->SetBranchAddress("PT", &PT);

   double NPP = 0, NAA = 0, NMB = 0;
   TH1D HPP("HPP", "PP;PT", 100, 0, 20);   HPP.SetStats(0);
   TH1D HAA("HAA", "AA;PT", 100, 0, 20);   HAA.SetStats(0);
   TH1D HMB("HMB", "MB;PT", 100, 0, 20);   HMB.SetStats(0);

   for(int iE = 0; iE < PPEntryCount; iE++)
   {
      TPP->GetEntry(iE);

      if(JetPT < PTMin)
         continue;
      if(fabs(JetEta) > EtaMax || fabs(JetEta) < EtaMin)
         continue;

      NPP = NPP + 1;
      for(int i = 0; i < PFCount; i++)
         HPP.Fill(PFPT[i]);
   }

   for(int iE = 0; iE < AAEntryCount; iE++)
   {
      TAA->GetEntry(iE);

      if(Centrality < CentralityMin || Centrality > CentralityMax)
         continue;
      if(JetPT < PTMin)
         continue;
      if(fabs(JetEta) > EtaMax || fabs(JetEta) < EtaMin)
         continue;

      NAA = NAA + 1;
      for(int i = 0; i < PFCount; i++)
         HAA.Fill(PFPT[i]);
   }

   NMB = ((TH1D *)FMB.Get("HN"))->GetEntries() * 0.01;
   for(int iE = 0; iE < MBEntryCount; iE++)
   {
      TMB->GetEntry(iE);

      if(Rho < 150)
         continue;

      HMB.Fill(PT);
   }

   HPP.Scale(1 / NPP / 0.2);
   HAA.Scale(1 / NAA / 0.2);
   HMB.Scale((HAA.Integral(6, 100) - HPP.Integral(6, 100)) / HMB.Integral(6, 100));

   PdfFileHelper PdfFile("Result.pdf");
   PdfFile.AddTextPage("PF Spectra");

   PdfFile.AddPlot(HPP, "", true);
   PdfFile.AddPlot(HAA, "", true);
   PdfFile.AddPlot(HMB, "", true);

   TCanvas C;

   HAA.SetTitle("");
   HAA.GetYaxis()->SetTitle("per-jet distribution");
   HPP.SetLineColor(kGreen);
   HMB.SetLineColor(kRed);

   HAA.Draw();
   HPP.Draw("same");
   HMB.Draw("same");

   C.SetLogy();

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&HPP, "PP", "l");
   Legend.AddEntry(&HAA, "AA", "l");
   Legend.AddEntry(&HMB, "MB", "l");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   FMB.Close();
   FAA.Close();
   FPP.Close();

   return 0;
}




