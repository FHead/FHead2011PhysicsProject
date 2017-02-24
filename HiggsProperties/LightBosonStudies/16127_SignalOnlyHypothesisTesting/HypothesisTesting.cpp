#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "PlotHelper3.h"
#include "ProgressBar.h"
#include "SetStyle.h"

#include "AngleConversion.h"
#include "Cuts.h"

class Likelihood;
int main();
vector<Likelihood> SelectEvents(string FileName, int Cut);
void ThreePlots(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, TH1D &H3);

class Likelihood
{
public:
   double L1;
   double L2;
   double L3;
};

int main()
{
   int Cut = 5;   // 5 = cut F = lepton loose && base, 7 = cut H = lepton tight && base

   srand(time(NULL));

   SetThesisStyle();

   vector<Likelihood> L1 = SelectEvents("Phto2e2mu_A1UU_18p4GeV_noPDF_ForEff_1.root", Cut);
   vector<Likelihood> L2 = SelectEvents("Phto2e2mu_A2UU_18p4GeV_noPDF_ForEff_1.root", Cut);
   vector<Likelihood> L3 = SelectEvents("Phto2e2mu_A3UU_18p4GeV_noPDF_ForEff_1.root", Cut);

   PdfFileHelper PdfFile(Form("HypothesisTestingResult_%c.pdf", char('A' + Cut)));
   PdfFile.AddTextPage(Form("Signal only with cut %c", char('A' + Cut)));

   int EventSize[11] = {2, 5, 10, 20, 40, 80, 160, 320, 640, 1280, 2560};
   for(int iS = 0; iS < 11; iS++)
   {
      random_shuffle(L1.begin(), L1.end());
      random_shuffle(L2.begin(), L2.end());
      random_shuffle(L3.begin(), L3.end());

      vector<double> S1_L12, S1_L23, S1_L13;
      vector<double> S2_L12, S2_L23, S2_L13;
      vector<double> S3_L12, S3_L23, S3_L13;

      for(int i = 0; i + (EventSize[iS] - 1) < (int)L1.size(); i = i + EventSize[iS])
      {
         double Total12 = 0, Total23 = 0, Total13 = 0;
         for(int j = 0; j < EventSize[iS]; j++)
         {
            Total12 = Total12 + log(L1[i+j].L1) - log(L1[i+j].L2) - 9.5;
            Total23 = Total23 + log(L1[i+j].L2) - log(L1[i+j].L3) - 1.5;
            Total13 = Total13 + log(L1[i+j].L1) - log(L1[i+j].L3) - 11;
         }
         S1_L12.push_back(Total12);
         S1_L23.push_back(Total23);
         S1_L13.push_back(Total13);
      }
      for(int i = 0; i + (EventSize[iS] - 1) < (int)L2.size(); i = i + EventSize[iS])
      {
         double Total12 = 0, Total23 = 0, Total13 = 0;
         for(int j = 0; j < EventSize[iS]; j++)
         {
            Total12 = Total12 + log(L2[i+j].L1) - log(L2[i+j].L2) - 9.5;
            Total23 = Total23 + log(L2[i+j].L2) - log(L2[i+j].L3) - 1.5;
            Total13 = Total13 + log(L2[i+j].L1) - log(L2[i+j].L3) - 11;
         }
         S2_L12.push_back(Total12);
         S2_L23.push_back(Total23);
         S2_L13.push_back(Total13);
      }
      for(int i = 0; i + (EventSize[iS] - 1) < (int)L3.size(); i = i + EventSize[iS])
      {
         double Total12 = 0, Total23 = 0, Total13 = 0;
         for(int j = 0; j < EventSize[iS]; j++)
         {
            Total12 = Total12 + log(L3[i+j].L1) - log(L3[i+j].L2) - 9.5;
            Total23 = Total23 + log(L3[i+j].L2) - log(L3[i+j].L3) - 1.5;
            Total13 = Total13 + log(L3[i+j].L1) - log(L3[i+j].L3) - 11;
         }
         S3_L12.push_back(Total12);
         S3_L23.push_back(Total23);
         S3_L13.push_back(Total13);
      }
      
      TH1D H1_L12("H1_L12", ";(log(L1) - log(L2)) / N;a.u.", 500, -5, 5);
      TH1D H1_L23("H1_L23", ";(log(L2) - log(L3)) / N;a.u.", 500, -5, 5);
      TH1D H1_L13("H1_L13", ";(log(L1) - log(L3)) / N;a.u.", 500, -5, 5);
      TH1D H2_L12("H2_L12", ";(log(L1) - log(L2)) / N;a.u.", 500, -5, 5);
      TH1D H2_L23("H2_L23", ";(log(L2) - log(L3)) / N;a.u.", 500, -5, 5);
      TH1D H2_L13("H2_L13", ";(log(L1) - log(L3)) / N;a.u.", 500, -5, 5);
      TH1D H3_L12("H3_L12", ";(log(L1) - log(L2)) / N;a.u.", 500, -5, 5);
      TH1D H3_L23("H3_L23", ";(log(L2) - log(L3)) / N;a.u.", 500, -5, 5);
      TH1D H3_L13("H3_L13", ";(log(L1) - log(L3)) / N;a.u.", 500, -5, 5);

      for(int i = 0; i < (int)S1_L12.size(); i++)
         H1_L12.Fill(S1_L12[i] / EventSize[iS]);
      for(int i = 0; i < (int)S1_L23.size(); i++)
         H1_L23.Fill(S1_L23[i] / EventSize[iS]);
      for(int i = 0; i < (int)S1_L13.size(); i++)
         H1_L13.Fill(S1_L13[i] / EventSize[iS]);
      for(int i = 0; i < (int)S2_L12.size(); i++)
         H2_L12.Fill(S2_L12[i] / EventSize[iS]);
      for(int i = 0; i < (int)S2_L23.size(); i++)
         H2_L23.Fill(S2_L23[i] / EventSize[iS]);
      for(int i = 0; i < (int)S2_L13.size(); i++)
         H2_L13.Fill(S2_L13[i] / EventSize[iS]);
      for(int i = 0; i < (int)S3_L12.size(); i++)
         H3_L12.Fill(S3_L12[i] / EventSize[iS]);
      for(int i = 0; i < (int)S3_L23.size(); i++)
         H3_L23.Fill(S3_L23[i] / EventSize[iS]);
      for(int i = 0; i < (int)S3_L13.size(); i++)
         H3_L13.Fill(S3_L13[i] / EventSize[iS]);

      PdfFile.AddTextPage(Form("Dataset Size %d", EventSize[iS]));

      ThreePlots(PdfFile, H1_L12, H2_L12, H3_L12);
      ThreePlots(PdfFile, H1_L23, H2_L23, H3_L23);
      ThreePlots(PdfFile, H1_L13, H2_L13, H3_L13);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

vector<Likelihood> SelectEvents(string FileName, int Cut)
{
   vector<Likelihood> Result;

   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("Tree");

   if(Tree == NULL)
      return Result;

   double L1PT, L1Eta, L1Phi;
   double L2PT, L2Eta, L2Phi;
   double L3PT, L3Eta, L3Phi;
   double L4PT, L4Eta, L4Phi;

   Tree->SetBranchAddress("L1PT", &L1PT);
   Tree->SetBranchAddress("L1Eta", &L1Eta);
   Tree->SetBranchAddress("L1Phi", &L1Phi);
   Tree->SetBranchAddress("L2PT", &L2PT);
   Tree->SetBranchAddress("L2Eta", &L2Eta);
   Tree->SetBranchAddress("L2Phi", &L2Phi);
   Tree->SetBranchAddress("L3PT", &L3PT);
   Tree->SetBranchAddress("L3Eta", &L3Eta);
   Tree->SetBranchAddress("L3Phi", &L3Phi);
   Tree->SetBranchAddress("L4PT", &L4PT);
   Tree->SetBranchAddress("L4Eta", &L4Eta);
   Tree->SetBranchAddress("L4Phi", &L4Phi);

   Likelihood L;

   Tree->SetBranchAddress("B1_A1VVR_A1VVR", &L.L1);
   Tree->SetBranchAddress("B1_A2VVR_A2VVR", &L.L2);
   Tree->SetBranchAddress("B1_A3VVR_A3VVR", &L.L3);

   int EntryCount = Tree->GetEntries();

   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 200 || (iE % (EntryCount / 300) == 0))
      {
         Bar.Update(iE);
         Bar.Print();
      }

      Tree->GetEntry(iE);

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      vector<bool> Pass = PassPairingCuts(Leptons);

      if(Pass[Cut] == false)   // 5 = cut F = lepton loose && base, 7 = cut H = lepton tight && base
         continue;

      if(L.L1 > 0.999)
         continue;
      if(L.L2 > 0.999)
         continue;
      if(L.L3 > 0.999)
         continue;

      Result.push_back(L);
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   cout << "Events selected: " << Result.size() << "/" << EntryCount << endl;

   File.Close();

   return Result;
}

void ThreePlots(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2, TH1D &H3)
{
   TCanvas Canvas;

   TH2D HWorld("HWorld", ";;", 100, -5, 5, 100, 0.0001, 1);
   HWorld.GetXaxis()->SetTitle(H1.GetXaxis()->GetTitle());
   HWorld.SetStats(0);
   TH2D HWorld2("HWorld2", ";;", 100, -2, 2, 100, 0.0001, 1);
   HWorld2.GetXaxis()->SetTitle(H1.GetXaxis()->GetTitle());
   HWorld2.SetStats(0);

   H1.Scale(1 / H1.Integral());
   H2.Scale(1 / H2.Integral());
   H3.Scale(1 / H3.Integral());

   H1.SetLineColor(kBlack);
   H2.SetLineColor(kRed);
   H3.SetLineColor(kBlue);

   TLegend Legend(0.2, 0.8, 0.5, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H1, "A1UU", "l");
   Legend.AddEntry(&H2, "A2UU", "l");
   Legend.AddEntry(&H3, "A3UU", "l");

   HWorld.Draw();
   H1.Draw("same");
   H2.Draw("same");
   H3.Draw("same");
   Legend.Draw();

   Canvas.SetLogy();

   PdfFile.AddCanvas(Canvas);
   
   HWorld2.Draw();
   H1.Draw("same");
   H2.Draw("same");
   H3.Draw("same");
   Legend.Draw();
   
   PdfFile.AddCanvas(Canvas);
}




