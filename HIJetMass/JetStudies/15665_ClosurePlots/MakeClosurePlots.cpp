#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TTree.h"
#include "TGraph.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

#include "BasicUtilities.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main();
void AddPlots(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, TH1D &H3, bool LogY);

int main()
{
   SetThesisStyle();

   TFile F1("Straight/AA6Dijet.root");
   TFile F2("ScaledResult17/PP6Dijet.root");
   TFile F3("Straight/PP6Dijet.root");

   TTree *T1 = (TTree *)F1.Get("Tree");
   TTree *T2 = (TTree *)F2.Get("OutputTree");
   TTree *T3 = (TTree *)F3.Get("Tree");

   double SDMass, SDDR, JetEta, JetPT, JetPhi, NewJetPT, NewJetEta, NewJetPhi, MCWeight, Rho, Centrality, TotalPT;
   double SDMasses[10], SDDRs[10];

   T1->SetBranchAddress("SDMass", &SDMasses);
   T1->SetBranchAddress("SDRecoDR", &SDDRs);
   T1->SetBranchAddress("JetEta", &JetEta);
   T1->SetBranchAddress("JetPT", &JetPT);
   T1->SetBranchAddress("JetPhi", &JetPhi);
   T1->SetBranchAddress("NewJetPT", &NewJetPT);
   T1->SetBranchAddress("MCWeight", &MCWeight);
   T1->SetBranchAddress("Rho", &Rho);
   T1->SetBranchAddress("Centrality", &Centrality);

   T2->SetBranchAddress("NewJetSDMass2", &SDMass);
   T2->SetBranchAddress("NewJetDR2", &SDDR);
   T2->SetBranchAddress("JetEta", &JetEta);
   T2->SetBranchAddress("JetPT", &JetPT);
   T2->SetBranchAddress("JetPhi", &JetPhi);
   T2->SetBranchAddress("NewJetPT", &NewJetPT);
   T2->SetBranchAddress("NewJetEta", &NewJetEta);
   T2->SetBranchAddress("NewJetPhi", &NewJetPhi);
   T2->SetBranchAddress("MCWeight", &MCWeight);
   T2->SetBranchAddress("Rho", &Rho);
   T2->SetBranchAddress("TotalPT", &TotalPT);

   T3->SetBranchAddress("SDMass", &SDMasses);
   T3->SetBranchAddress("SDRecoDR", &SDDRs);
   T3->SetBranchAddress("JetEta", &JetEta);
   T3->SetBranchAddress("JetPT", &JetPT);
   T3->SetBranchAddress("JetPhi", &JetPhi);
   T3->SetBranchAddress("NewJetPT", &NewJetPT);
   T3->SetBranchAddress("MCWeight", &MCWeight);
   
   TFile OutputFile("OutputFile.root", "RECREATE");

   TH1D HJetPT1("HJetPT1", ";PT;", 40, 120, 500);
   TH1D HJetPT2("HJetPT2", ";PT;", 40, 120, 500);
   TH1D HJetPT3("HJetPT3", ";PT;", 40, 120, 500);
   TH1D HWeightedJetPT1("HWeightedJetPT1", ";PT;", 40, 120, 500);
   TH1D HWeightedJetPT2("HWeightedJetPT2", ";PT;", 40, 120, 500);
   TH1D HWeightedJetPT3("HWeightedJetPT3", ";PT;", 40, 120, 500);
   TH1D HSDDR1("HSDDR1", ";Reco Jet DR;", 80, 0, 0.4);
   TH1D HSDDR2("HSDDR2", ";Reco Jet DR;", 80, 0, 0.4);
   TH1D HSDDR3("HSDDR3", ";Reco Jet DR;", 80, 0, 0.4);
   TH1D HMassPT1("HMassPT1", ";Mass/PT;", 60, 0, 0.4);
   TH1D HMassPT2("HMassPT2", ";Mass/PT;", 60, 0, 0.4);
   TH1D HMassPT2Fudged("HMassPT2Fudged", ";Mass/PT;", 60, 0, 0.4);
   TH1D HMassPT3("HMassPT3", ";Mass/PT;", 60, 0, 0.4);

   int EntryCount;

   EntryCount = T1->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T1->GetEntry(iE);

      if(Centrality > 0.1 || Centrality < 0.0)
         continue;
      if(JetEta < -1.3 || JetEta > 1.3)
         continue;
      if(JetPT < 200 || JetPT > 500)
         continue;

      HSDDR1.Fill(SDDRs[7], MCWeight);
      HJetPT1.Fill(JetPT, MCWeight);
      HWeightedJetPT1.Fill(JetPT, MCWeight);

      if(SDDRs[7] > 0.1)
      {
         HMassPT1.Fill(SDMasses[7] / NewJetPT, MCWeight);
      }
   }

   EntryCount = T2->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T2->GetEntry(iE);

      if(NewJetPT < 200 || NewJetPT > 500)
         continue;
      if(abs(NewJetEta) > 1.3)
         continue;

      double JetShift = GetDR(JetEta, JetPhi, NewJetEta, NewJetPhi);
      if(JetShift > 0.2)   // these are background jets!
         continue;
      
      // double ExcessPT = (TotalPT - 2.0 * 2.0 * PI * Rho) / 25;
      double ExcessPT = (TotalPT - 1.6 * 1.6 * PI * Rho) / 16;
      // double ExcessPT = (TotalPT - 1.2 * 1.2 * PI * Rho) / 9;
      // double ExcessPT = (TotalPT - 0.8 * 0.8 * PI * Rho) / 4;

      double SmearWeightV3 = exp(-0.5 * pow(ExcessPT / 17.2, 2)) / exp(-0.5 * pow(ExcessPT / 27.4, 2));

      HJetPT2.Fill(NewJetPT, MCWeight * SmearWeightV3);

      double PTWeight = 0.929846 + exp(9.16730 - 0.0754417 * NewJetPT);

      HWeightedJetPT2.Fill(NewJetPT, MCWeight * PTWeight * SmearWeightV3);
      HSDDR2.Fill(SDDR, MCWeight * PTWeight * SmearWeightV3);

      double DRFudge = 1.16137 - exp(-0.00205447 - 23.2991 * SDDR);
      
      if(SDDR > 0.1)
      {
         HMassPT2.Fill(SDMass / NewJetPT, MCWeight * PTWeight * SmearWeightV3);
         HMassPT2Fudged.Fill(SDMass / NewJetPT, MCWeight * PTWeight * SmearWeightV3 * DRFudge);
      }
   }

   EntryCount = T3->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T3->GetEntry(iE);

      if(JetEta < -1.3 || JetEta > 1.3)
         continue;
      if(JetPT < 200 || JetPT > 500)
         continue;
      
      HJetPT3.Fill(JetPT, MCWeight);
      
      double PTWeight = 0.729964 + exp(0.749469 - 0.0122101 * JetPT);

      HWeightedJetPT3.Fill(JetPT, MCWeight * PTWeight);
      HSDDR3.Fill(SDDRs[7], MCWeight * PTWeight);

      if(SDDRs[7] > 0.1)
      {
         HMassPT3.Fill(SDMasses[7] / NewJetPT, MCWeight * PTWeight);
      }
   }

   PdfFileHelper PdfFile("ClosurePlots.pdf");
   PdfFile.AddTextPage("Closure plots");

   vector<string> Explanation(10);
   Explanation[1] = "Black = embedded pythia";
   Explanation[2] = "Red = smeared pythia";
   Explanation[3] = "Green = original pythia";
   Explanation[4] = "Ratio = embedded / smeared pythia";
   Explanation[5] = "        and original / smeared pythia";
   PdfFile.AddTextPage(Explanation);

   AddPlots(PdfFile, HJetPT1, HJetPT2, HJetPT3, true);
   AddPlots(PdfFile, HWeightedJetPT1, HWeightedJetPT2, HWeightedJetPT3,  true);
   AddPlots(PdfFile, HSDDR1, HSDDR2, HSDDR3, false);
   AddPlots(PdfFile, HMassPT1, HMassPT2, HMassPT3, false);
   AddPlots(PdfFile, HMassPT1, HMassPT2Fudged, HMassPT3, false);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   HJetPT1.Write();            HJetPT2.Write();           HJetPT3.Write();
   HWeightedJetPT1.Write();    HWeightedJetPT2.Write();   HWeightedJetPT3.Write();
   HSDDR1.Write();             HSDDR2.Write();            HSDDR3.Write();
   HMassPT1.Write();           HMassPT2.Write();          HMassPT3.Write();
                               HMassPT2Fudged.Write();

   OutputFile.Close();

   F3.Close();
   F2.Close();
   F1.Close();

   return 0;
}

void AddPlots(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, TH1D &H3, bool LogY)
{
   H1.SetStats(0);
   H2.SetStats(0);
   H3.SetStats(0);

   H1.Scale(1 / H1.Integral());
   H2.Scale(1 / H2.Integral());
   H3.Scale(1 / H3.Integral());

   H1.SetLineColor(kBlack);
   H2.SetLineColor(kRed);
   H3.SetLineColor(kGreen);
   H1.SetMarkerColor(kBlack);
   H2.SetMarkerColor(kRed);
   H3.SetMarkerColor(kGreen);

   TCanvas C;

   H3.Draw();
   H1.Draw("same");
   H2.Draw("same");

   if(LogY == true)
      C.SetLogy();

   PdfFile.AddCanvas(C);

   TCanvas C2;

   TH1D *H1Clone = (TH1D *)H1.Clone("H1Clone");
   TH1D *H3Clone = (TH1D *)H3.Clone("H3Clone");

   H1Clone->Divide(&H2);
   H3Clone->Divide(&H2);

   H1Clone->SetMaximum(10);
   H1Clone->SetMinimum(0.1);

   H1Clone->Draw();
   H3Clone->Draw("same");

   TGraph G;
   G.SetPoint(0, 0, 1);
   G.SetPoint(1, 1, 1);
   G.Draw("l");

   C2.SetLogy();

   PdfFile.AddCanvas(C2);

   delete H1Clone;
   delete H3Clone;
}









