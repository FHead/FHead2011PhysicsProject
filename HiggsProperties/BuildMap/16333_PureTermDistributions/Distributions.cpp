#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TLegend.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

#include "AngleConversion.h"

class Histograms;
int main();
void OverlayPlots(PdfFileHelper &PdfFile, TH1D *H1, TH1D *H2, TH1D *H3, TH1D *H4, TH1D *H5, TH1D *H6, double Max);
void NormalizeHistogram(TH1D *H);

class Histograms
{
public:
   TH1D *HM1;
   TH1D *HM2;
   TH1D *HCosTheta0;
   TH1D *HPhi0;
   TH1D *HCosTheta1;
   TH1D *HCosTheta2;
   TH1D *HPhi;
public:
   Histograms(string Tag)
      : HM1(NULL), HM2(NULL), HCosTheta0(NULL), HPhi0(NULL), HCosTheta1(NULL), HCosTheta2(NULL), HPhi(NULL)
   {
      HM1 = new TH1D(Form("HM1%s", Tag.c_str()), ";M_{1};", 100, 0, 20);
      HM2 = new TH1D(Form("HM2%s", Tag.c_str()), ";M_{ll};", 25, 0, 10);
      HCosTheta0 = new TH1D(Form("HCosTheta0%s", Tag.c_str()), ";cos#Theta;", 50, 0, 1);
      HPhi0 = new TH1D(Form("HPhi0%s", Tag.c_str()), ";#Phi_{0};", 50, -M_PI, M_PI);
      HCosTheta1 = new TH1D(Form("HCosTheta1%s", Tag.c_str()), ";cos#theta_{1};", 20, -1, 1);
      HCosTheta2 = new TH1D(Form("HCosTheta2%s", Tag.c_str()), ";cos#theta_{ll};", 20, -1, 1);
      HPhi = new TH1D(Form("HPhi%s", Tag.c_str()), ";#Phi;", 24, -M_PI, M_PI);

      BasicStyling(HM1);
      BasicStyling(HM2);
      BasicStyling(HCosTheta0);
      BasicStyling(HPhi0);
      BasicStyling(HCosTheta1);
      BasicStyling(HCosTheta2);
      BasicStyling(HPhi);
   }
   ~Histograms()
   {
      if(HM1 != NULL)          delete HM1;
      if(HM2 != NULL)          delete HM2;
      if(HCosTheta0 != NULL)   delete HCosTheta0;
      if(HPhi0 != NULL)        delete HPhi0;
      if(HCosTheta1 != NULL)   delete HCosTheta1;
      if(HCosTheta2 != NULL)   delete HCosTheta2;
      if(HPhi != NULL)         delete HPhi;
   }
   void FillLepton(TTree *Tree)
   {
      if(Tree == NULL)
         return;

      double L1ID, L1PT, L1Eta, L1Phi;
      double L2ID, L2PT, L2Eta, L2Phi;
      double L3ID, L3PT, L3Eta, L3Phi;
      double L4ID, L4PT, L4Eta, L4Phi;
      Tree->SetBranchAddress("L1ID", &L1ID);
      Tree->SetBranchAddress("L1PT", &L1PT);
      Tree->SetBranchAddress("L1Eta", &L1Eta);
      Tree->SetBranchAddress("L1Phi", &L1Phi);
      Tree->SetBranchAddress("L2ID", &L2ID);
      Tree->SetBranchAddress("L2PT", &L2PT);
      Tree->SetBranchAddress("L2Eta", &L2Eta);
      Tree->SetBranchAddress("L2Phi", &L2Phi);
      Tree->SetBranchAddress("L3ID", &L3ID);
      Tree->SetBranchAddress("L3PT", &L3PT);
      Tree->SetBranchAddress("L3Eta", &L3Eta);
      Tree->SetBranchAddress("L3Phi", &L3Phi);
      Tree->SetBranchAddress("L4ID", &L4ID);
      Tree->SetBranchAddress("L4PT", &L4PT);
      Tree->SetBranchAddress("L4Eta", &L4Eta);
      Tree->SetBranchAddress("L4Phi", &L4Phi);

      int EntryCount = Tree->GetEntries();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         LeptonVectors Leptons;
         Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
         Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
         Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
         Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

         if(abs(L1ID) == abs(L3ID))
            Leptons = Leptons.ReorderLeptons4e();
         else
            Leptons = Leptons.ReorderLeptons2e2mu();

         EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

         if(Event.Phi0 > M_PI)
            Event.Phi0 = Event.Phi0 - 2 * M_PI;
         if(Event.Phi > M_PI)
            Event.Phi = Event.Phi - 2 * M_PI;

         HM1->Fill(Event.ZMass);
         HM2->Fill(Event.Z2Mass);
         HCosTheta0->Fill(cos(Event.Theta0));
         HPhi0->Fill(Event.Phi0);
         HCosTheta1->Fill(cos(Event.Theta1));
         HCosTheta1->Fill(-cos(Event.Theta1));
         HCosTheta2->Fill(cos(Event.Theta2));
         HCosTheta2->Fill(-cos(Event.Theta2));
         HPhi->Fill(Event.Phi);
         HPhi->Fill(-Event.Phi);
         HPhi->Fill(Event.Phi + (Event.Phi < 0) * M_PI - (Event.Phi > 0) * M_PI);
         HPhi->Fill(-Event.Phi + (-Event.Phi < 0) * M_PI - (-Event.Phi > 0) * M_PI);
      }
   }
   void Fill(TTree *Tree)
   {
      if(Tree == NULL)
         return;

      double ZMass, Z2Mass, Theta0, Phi0, Theta1, Theta2, Phi;
      Tree->SetBranchAddress("ZMass", &ZMass);
      Tree->SetBranchAddress("Z2Mass", &Z2Mass);
      Tree->SetBranchAddress("Theta0", &Theta0);
      Tree->SetBranchAddress("Phi0", &Phi0);
      Tree->SetBranchAddress("Theta1", &Theta1);
      Tree->SetBranchAddress("Theta2", &Theta2);
      Tree->SetBranchAddress("Phi", &Phi);

      int EntryCount = Tree->GetEntries();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         HM1->Fill(ZMass);
         HM2->Fill(Z2Mass);
         HCosTheta0->Fill(cos(Theta0));
         HPhi0->Fill(Phi0);
         HCosTheta1->Fill(cos(Theta1));
         HCosTheta2->Fill(cos(Theta2));
         HPhi->Fill(Phi);
      }
   }
   void BasicStyling(TH1D *H)
   {
      H->SetStats(0);
      // H->Sumw2();

      H->SetLineWidth(3);
   }
};

int main()
{
   SetThesisStyle();

   Histograms A1UU2e2mu("A1UU2e2mu");
   Histograms A1UZ2e2mu("A1UZ2e2mu");
   Histograms A2UA2e2mu("A2UA2e2mu");
   Histograms A2UU2e2mu("A2UU2e2mu");
   Histograms A2UZ2e2mu("A2UZ2e2mu");
   Histograms A3UU2e2mu("A3UU2e2mu");
   Histograms A1UU4e("A1UU4e");
   Histograms A1UZ4e("A1UZ4e");
   Histograms A2UA4e("A2UA4e");
   Histograms A2UU4e("A2UU4e");
   Histograms A2UZ4e("A2UZ4e");
   Histograms A3UU4e("A3UU4e");

   TFile FA1UU2e2mu("16246/Phto2e2mu_A1UU_18p4GeV_NoPDF_ForEff.root");
   TFile FA1UZ2e2mu("16246/Phto2e2mu_A1UZ_18p4GeV_NoPDF_ForEff.root");
   TFile FA2UA2e2mu("16246/Phto2e2mu_A2UA_18p4GeV_NoPDF_ForEff.root");
   TFile FA2UU2e2mu("16246/Phto2e2mu_A2UU_18p4GeV_NoPDF_ForEff.root");
   TFile FA2UZ2e2mu("16246/Phto2e2mu_A2UZ_18p4GeV_NoPDF_ForEff.root");
   TFile FA3UU2e2mu("16246/Phto2e2mu_A3UU_18p4GeV_NoPDF_ForEff.root");
   TFile FA1UU4e("16246/Phto4e_A1UU_18p4GeV_NoPDF_ForEff.root");
   TFile FA1UZ4e("16246/Phto4e_A1UZ_18p4GeV_NoPDF_ForEff.root");
   TFile FA2UA4e("16246/Phto4e_A2UA_18p4GeV_NoPDF_ForEff.root");
   TFile FA2UU4e("16246/Phto4e_A2UU_18p4GeV_NoPDF_ForEff.root");
   TFile FA2UZ4e("16246/Phto4e_A2UZ_18p4GeV_NoPDF_ForEff.root");
   TFile FA3UU4e("16246/Phto4e_A3UU_18p4GeV_NoPDF_ForEff.root");

   A1UU2e2mu.FillLepton((TTree *)FA1UU2e2mu.Get("Tree"));
   A1UZ2e2mu.FillLepton((TTree *)FA1UZ2e2mu.Get("Tree"));
   A2UA2e2mu.FillLepton((TTree *)FA2UA2e2mu.Get("Tree"));
   A2UU2e2mu.FillLepton((TTree *)FA2UU2e2mu.Get("Tree"));
   A2UZ2e2mu.FillLepton((TTree *)FA2UZ2e2mu.Get("Tree"));
   A3UU2e2mu.FillLepton((TTree *)FA3UU2e2mu.Get("Tree"));
   A1UU4e.FillLepton((TTree *)FA1UU4e.Get("Tree"));
   A1UZ4e.FillLepton((TTree *)FA1UZ4e.Get("Tree"));
   A2UA4e.FillLepton((TTree *)FA2UA4e.Get("Tree"));
   A2UU4e.FillLepton((TTree *)FA2UU4e.Get("Tree"));
   A2UZ4e.FillLepton((TTree *)FA2UZ4e.Get("Tree"));
   A3UU4e.FillLepton((TTree *)FA3UU4e.Get("Tree"));

   PdfFileHelper PdfFile("BasicDistributions.pdf");
   PdfFile.AddTextPage("Distributions from MG");

   PdfFile.AddTextPage("2e2#mu plots");
   OverlayPlots(PdfFile, A1UU2e2mu.HM1, A1UZ2e2mu.HM1, A2UA2e2mu.HM1, A2UU2e2mu.HM1, A2UZ2e2mu.HM1, A3UU2e2mu.HM1, -1);
   OverlayPlots(PdfFile, A1UU2e2mu.HM2, A1UZ2e2mu.HM2, A2UA2e2mu.HM2, A2UU2e2mu.HM2, A2UZ2e2mu.HM2, A3UU2e2mu.HM2, 1);
   OverlayPlots(PdfFile, A1UU2e2mu.HCosTheta0, A1UZ2e2mu.HCosTheta0, A2UA2e2mu.HCosTheta0, A2UU2e2mu.HCosTheta0, A2UZ2e2mu.HCosTheta0, A3UU2e2mu.HCosTheta0, 1.35 / 2);
   OverlayPlots(PdfFile, A1UU2e2mu.HPhi0, A1UZ2e2mu.HPhi0, A2UA2e2mu.HPhi0, A2UU2e2mu.HPhi0, A2UZ2e2mu.HPhi0, A3UU2e2mu.HPhi0, 0.22);
   OverlayPlots(PdfFile, A1UU2e2mu.HCosTheta1, A1UZ2e2mu.HCosTheta1, A2UA2e2mu.HCosTheta1, A2UU2e2mu.HCosTheta1, A2UZ2e2mu.HCosTheta1, A3UU2e2mu.HCosTheta1, 1.7 / 2);
   OverlayPlots(PdfFile, A1UU2e2mu.HCosTheta2, A1UZ2e2mu.HCosTheta2, A2UA2e2mu.HCosTheta2, A2UU2e2mu.HCosTheta2, A2UZ2e2mu.HCosTheta2, A3UU2e2mu.HCosTheta2, 1.7 / 2);
   OverlayPlots(PdfFile, A1UU2e2mu.HPhi, A1UZ2e2mu.HPhi, A2UA2e2mu.HPhi, A2UU2e2mu.HPhi, A2UZ2e2mu.HPhi, A3UU2e2mu.HPhi, 0.27);

   PdfFile.AddTextPage("4e/4#mu plots");
   OverlayPlots(PdfFile, A1UU4e.HM1, A1UZ4e.HM1, A2UA4e.HM1, A2UU4e.HM1, A2UZ4e.HM1, A3UU4e.HM1, -1);
   OverlayPlots(PdfFile, A1UU4e.HM2, A1UZ4e.HM2, A2UA4e.HM2, A2UU4e.HM2, A2UZ4e.HM2, A3UU4e.HM2, 0.85);
   OverlayPlots(PdfFile, A1UU4e.HCosTheta0, A1UZ4e.HCosTheta0, A2UA4e.HCosTheta0, A2UU4e.HCosTheta0, A2UZ4e.HCosTheta0, A3UU4e.HCosTheta0, 1.35 / 2);
   OverlayPlots(PdfFile, A1UU4e.HPhi0, A1UZ4e.HPhi0, A2UA4e.HPhi0, A2UU4e.HPhi0, A2UZ4e.HPhi0, A3UU4e.HPhi0, 0.22);
   OverlayPlots(PdfFile, A1UU4e.HCosTheta1, A1UZ4e.HCosTheta1, A2UA4e.HCosTheta1, A2UU4e.HCosTheta1, A2UZ4e.HCosTheta1, A3UU4e.HCosTheta1, 2.2 / 2);
   OverlayPlots(PdfFile, A1UU4e.HCosTheta2, A1UZ4e.HCosTheta2, A2UA4e.HCosTheta2, A2UU4e.HCosTheta2, A2UZ4e.HCosTheta2, A3UU4e.HCosTheta2, 2.1 / 2);
   OverlayPlots(PdfFile, A1UU4e.HPhi, A1UZ4e.HPhi, A2UA4e.HPhi, A2UU4e.HPhi, A2UZ4e.HPhi, A3UU4e.HPhi, 0.7);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   FA3UU2e2mu.Close();
   FA2UZ2e2mu.Close();
   FA2UU2e2mu.Close();
   FA2UA2e2mu.Close();
   FA1UZ2e2mu.Close();
   FA1UU2e2mu.Close();
   FA3UU4e.Close();
   FA2UZ4e.Close();
   FA2UU4e.Close();
   FA2UA4e.Close();
   FA1UZ4e.Close();
   FA1UU4e.Close();

   return 0;
}

void OverlayPlots(PdfFileHelper &PdfFile, TH1D *H1, TH1D *H2, TH1D *H3, TH1D *H4, TH1D *H5, TH1D *H6, double Max)
{
   if(H1 == NULL || H2 == NULL || H3 == NULL || H4 == NULL || H5 == NULL || H6 == NULL)
      return;

   TH1D *HT1 = (TH1D *)H1->Clone("TempH1");
   TH1D *HT2 = (TH1D *)H2->Clone("TempH2");
   TH1D *HT3 = (TH1D *)H3->Clone("TempH3");
   TH1D *HT4 = (TH1D *)H4->Clone("TempH4");
   TH1D *HT5 = (TH1D *)H5->Clone("TempH5");
   TH1D *HT6 = (TH1D *)H6->Clone("TempH6");

   NormalizeHistogram(HT1);
   NormalizeHistogram(HT2);
   NormalizeHistogram(HT3);
   NormalizeHistogram(HT4);
   NormalizeHistogram(HT5);
   NormalizeHistogram(HT6);

   HT1->SetLineColor(kBlack);
   HT2->SetLineColor(kRed);
   HT3->SetLineColor(kGreen);
   HT4->SetLineColor(kBlue);
   HT5->SetLineColor(kYellow - 3);
   HT6->SetLineColor(kCyan - 3);

   HT1->SetMarkerColor(kBlack);
   HT2->SetMarkerColor(kRed);
   HT3->SetMarkerColor(kGreen);
   HT4->SetMarkerColor(kBlue);
   HT5->SetMarkerColor(kYellow - 3);
   HT6->SetMarkerColor(kCyan - 3);

   int N = H1->GetNbinsX();
   double L = H1->GetXaxis()->GetBinLowEdge(1);
   double R = H1->GetXaxis()->GetBinUpEdge(N);
   if(Max < 0)
      Max = max(max(max(HT1->GetMaximum(), HT2->GetMaximum()), max(HT3->GetMaximum(), HT4->GetMaximum())), max(HT5->GetMaximum(), HT6->GetMaximum())) * 1.2;

   TH2D HWorld("HWorld", ";;", 100, L, R, 100, 0, Max);
   HWorld.SetStats(0);

   string XTitle = H1->GetXaxis()->GetTitle();

   HWorld.GetXaxis()->SetTitle(XTitle.c_str());
   HWorld.GetYaxis()->SetTitle(Form("#Gamma^{-1} d#Gamma_{#varphi#rightarrow4l} / d %s", XTitle.c_str()));

   if(XTitle == "M_{ll}")
      HWorld.GetXaxis()->SetTitle((XTitle + " [GeV]").c_str());

   HWorld.GetYaxis()->SetTitleOffset(1.4);

   HWorld.GetXaxis()->CenterTitle(true);
   HWorld.GetYaxis()->CenterTitle(true);

   TH2D HWorldLog("HWorldLog", ";;", 100, L, R, 100, Max * 0.0001, Max * 100);
   HWorldLog.SetStats(0);

   HWorldLog.GetXaxis()->SetTitle(XTitle.c_str());
   HWorldLog.GetYaxis()->SetTitle(Form("#Gamma^{-1} d#Gamma_{#varphi#rightarrow4l} / d %s", XTitle.c_str()));

   TLegend Legend1(0.2, 0.75, 0.5, 0.85);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.035);
   Legend1.SetFillStyle(0);
   TLegend Legend2(0.4, 0.75, 0.7, 0.85);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetFillStyle(0);
   TLegend Legend3(0.6, 0.75, 0.9, 0.85);
   Legend3.SetTextFont(42);
   Legend3.SetTextSize(0.035);
   Legend3.SetFillStyle(0);
   Legend1.AddEntry(HT1, "|A_{1}^{#Upsilon#Upsilon}|^{2}", "l");
   Legend1.AddEntry(HT2, "|A_{1}^{#UpsilonZ}|^{2}", "l");
   Legend2.AddEntry(HT3, "|A_{2}^{#Upsilon#gamma}|^{2}", "l");
   Legend2.AddEntry(HT4, "|A_{2}^{#Upsilon#Upsilon}|^{2}", "l");
   Legend3.AddEntry(HT5, "|A_{2}^{#UpsilonZ}|^{2}", "l");
   Legend3.AddEntry(HT6, "|A_{3}^{#Upsilon#Upsilon}|^{2}", "l");

   TCanvas C;

   HWorld.Draw("axis");
   HT1->Draw("same p");
   HT2->Draw("same p");
   HT3->Draw("same p");
   HT4->Draw("same p");
   HT5->Draw("same p");
   HT6->Draw("same p");

   TH1D *HT1C = (TH1D *)HT1->Clone();
   TH1D *HT2C = (TH1D *)HT2->Clone();
   TH1D *HT3C = (TH1D *)HT3->Clone();
   TH1D *HT4C = (TH1D *)HT4->Clone();
   TH1D *HT5C = (TH1D *)HT5->Clone();
   TH1D *HT6C = (TH1D *)HT6->Clone();

   if(XTitle == "cos#theta_{ll}" || XTitle == "cos#theta_{1}")
   {
      HT1C->Smooth();
      HT2C->Smooth();
      HT3C->Smooth();
      HT4C->Smooth();
      HT5C->Smooth();
      HT6C->Smooth();
   }

   HT1C->Draw("same c");
   HT2C->Draw("same c");
   HT3C->Draw("same c");
   HT4C->Draw("same c");
   HT5C->Draw("same c");
   HT6C->Draw("same c");

   Legend1.Draw();
   Legend2.Draw();
   Legend3.Draw();

   PdfFile.AddCanvas(C);

   HWorldLog.Draw("axis");
   HT1->Draw("same c");
   HT2->Draw("same c");
   HT3->Draw("same c");
   HT4->Draw("same c");
   HT5->Draw("same c");
   HT6->Draw("same c");
   Legend1.Draw();
   Legend2.Draw();
   Legend3.Draw();

   C.SetLogy();

   PdfFile.AddCanvas(C);

   delete HT1C;

   delete HT1;
   delete HT2;
   delete HT3;
   delete HT4;
   delete HT5;
   delete HT6;
}

void NormalizeHistogram(TH1D *H)
{
   int N = H->GetNbinsX();
   double Min = H->GetXaxis()->GetBinLowEdge(1);
   double Max = H->GetXaxis()->GetBinUpEdge(N);

   double BinSize = (Max - Min) / N;

   H->Scale(1 / H->Integral() / BinSize);
}



