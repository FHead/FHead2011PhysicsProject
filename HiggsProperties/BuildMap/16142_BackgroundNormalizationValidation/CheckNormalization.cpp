#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "DataHelper.h"
#include "ProgressBar.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

#include "AngleConversion.h"
#include "Cuts.h"

int main();
vector<pair<double, double>> ReadTree(string FileName);

int main()
{
   SetThesisStyle();

   vector<pair<double, double>> S = ReadTree("Phto2e2mu_A1UU_18p4GeV_noPDF_ForEff_1.root");
   vector<pair<double, double>> B = ReadTree("ddbar_PDF_to_2e2mu_LO_ForEff_13TeV_10to25GeV_1.root");

   PdfFileHelper PdfFile("BackgroundScan.pdf");
   PdfFile.AddTextPage("Check background nomralization");

   vector<string> Explanation(10);
   Explanation[0] = "Take 100 background events and different number";
   Explanation[1] = "of signal events";
   Explanation[2] = "";
   Explanation[3] = "Scan through different background fraction and plot";
   Explanation[4] = "-log(likelihood)";
   Explanation[5] = "";
   Explanation[6] = "Red vertical line = position of the minimum";
   Explanation[7] = "Black vertical line = input fraction";
   Explanation[8] = "";
   Explanation[9] = "Summary of input vs. output in the end";
   PdfFile.AddTextPage(Explanation);

   TGraph GInputOutput;

   double Fraction[] = {0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75, 0.80, 0.85, 0.90, 0.95};
   for(int iF = 0; iF < 19; iF++)
   {
      int NB = 100;
      int NS = NB / Fraction[iF] - NB;

      double TrueFraction = (double)NB / (NS + NB);

      TGraph Scan;
      Scan.SetNameTitle("Scan", Form("True fraction = %.3f", TrueFraction));

      double MinF = -1;
      double MinLL = 0;

      for(double F = 0.000; F <= 1.000; F = F + 0.001)
      {
         double LL = 0;
         for(int i = 0; i < NS; i++)
            LL = LL + log(S[i].first * (1 - F) + S[i].second * F);
         for(int i = 0; i < NB; i++)
            LL = LL + log(B[i].first * (1 - F) + B[i].second * F);

         Scan.SetPoint(Scan.GetN(), F, -LL);

         if(MinF < 0 || MinLL < LL)
         {
            MinF = F;
            MinLL = LL;
         }
      }

      TGraph GTrue, GBest;
      GTrue.SetPoint(0, TrueFraction, -100000);
      GTrue.SetPoint(1, TrueFraction, +100000);
      GBest.SetPoint(0, MinF, -100000);
      GBest.SetPoint(1, MinF, +100000);

      GBest.SetLineColor(kRed);

      TCanvas C;

      Scan.Draw("al");
      GBest.Draw("l");
      GTrue.Draw("l");

      Scan.GetXaxis()->SetTitle("Background Fraction");

      PdfFile.AddCanvas(C);

      GInputOutput.SetPoint(GInputOutput.GetN(), TrueFraction, MinF);
   }

   PdfFile.AddTextPage("Summary Plot");

   TCanvas C;

   GInputOutput.SetMarkerStyle(11);
   GInputOutput.Draw("ap");

   TGraph GDiagonal;
   GDiagonal.SetPoint(0, 0, 0);
   GDiagonal.SetPoint(1, 1, 1);
   GDiagonal.Draw("l");

   GInputOutput.GetXaxis()->SetTitle("Input fraction");
   GInputOutput.GetYaxis()->SetTitle("Output fraction");

   C.SetGridx();
   C.SetGridy();

   PdfFile.AddCanvas(C);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

vector<pair<double, double>> ReadTree(string FileName)
{
   vector<pair<double, double>> Result;

   TFile F(FileName.c_str());

   TTree *T = (TTree *)F.Get("Tree");

   double LS, LB;
   double L1PT, L1Eta, L1Phi;
   double L2PT, L2Eta, L2Phi;
   double L3PT, L3Eta, L3Phi;
   double L4PT, L4Eta, L4Phi;

   T->SetBranchAddress("B1_A1VVR_A1VVR", &LS);
   T->SetBranchAddress("B2_DDbar", &LB);
   T->SetBranchAddress("L1PT", &L1PT);
   T->SetBranchAddress("L1Eta", &L1Eta);
   T->SetBranchAddress("L1Phi", &L1Phi);
   T->SetBranchAddress("L2PT", &L2PT);
   T->SetBranchAddress("L2Eta", &L2Eta);
   T->SetBranchAddress("L2Phi", &L2Phi);
   T->SetBranchAddress("L3PT", &L3PT);
   T->SetBranchAddress("L3Eta", &L3Eta);
   T->SetBranchAddress("L3Phi", &L3Phi);
   T->SetBranchAddress("L4PT", &L4PT);
   T->SetBranchAddress("L4Eta", &L4Eta);
   T->SetBranchAddress("L4Phi", &L4Phi);

   DataHelper DHFile("Normalization.dh");
   double IS = DHFile["0TeV"]["TF1_A1VVR_A1VVR"].GetDouble();
   double IB = DHFile["0TeV"]["TF2_DDbar"].GetDouble();

   int EntryCount = T->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(iE % 500 == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      T->GetEntry(iE);

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      Leptons = Leptons.GoToRest();

      if(PassPairingCuts(Leptons)[5] == false)   // F cut
         continue;

      Result.push_back(pair<double, double>(LS / IS, LB / IB));
   }
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   F.Close();

   cout << "File " << FileName << ": " << Result.size() << "/" << EntryCount << " selected" << endl;

   return Result;
}





