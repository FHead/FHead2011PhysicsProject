#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"

#include "SetStyle.h"
#include "PlotHelper3.h"
#include "Code/TauHelperFunctions3.h"

int main(int argc, char *argv[]);
void MakePlot(PdfFileHelper &PdfFile, bool IsPP, bool Is0, string DataFileName, string MCFileName);
void FillHistogram(TH1D &H, string FileName, char SD, bool IsMC, bool IsPP);

int main(int argc, char *argv[])
{
   SetThesisSmallStyle();

   // Aux. file
   PdfFileHelper PdfFile("QualityControl.pdf");
   PdfFile.AddTextPage("Quality control");

   // Input values
   string PPDataFileName = "PPData.root";
   string PPMCFileName = "PPMC.root";
   string AADataFileName = "AAData.root";
   string AAMCFileName = "AAMC.root";

   // Run everything
   MakePlot(PdfFile, true, true, PPDataFileName, PPMCFileName);
   MakePlot(PdfFile, true, false, PPDataFileName, PPMCFileName);
   MakePlot(PdfFile, false, true, AADataFileName, AAMCFileName);
   MakePlot(PdfFile, false, false, AADataFileName, AAMCFileName);

   // Clean up
   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void MakePlot(PdfFileHelper &PdfFile, bool IsPP, bool Is0, string DataFileName, string MCFileName)
{
   // Title page
   string TitlePage = "";
   TitlePage = TitlePage + "IsPP = " + (IsPP ? "Yes" : "No");
   TitlePage = TitlePage + ", SD = " + (Is0 ? "0" : "7");
   PdfFile.AddTextPage(TitlePage);

   // Derived settings
   char SD = (Is0 ? '0' : '7');
   double Min = (Is0 ? 0.5 : 0.3);
   double Max = 1.0;
   int Bin = 50;
   double YMin = 0.02;
   double YMax = (Is0 ? 100 : 2000);

   // Get histograms
   TH1D HData("HData", ";;", Bin, Min, Max);
   TH1D HMC("HMC", ";;", Bin, Min, Max);

   HData.Sumw2();
   // HMC.Sumw2();

   FillHistogram(HData, DataFileName, SD, false, IsPP);
   FillHistogram(HMC, MCFileName, SD, true, IsPP);

   PdfFile.AddPlot(HData);
   PdfFile.AddPlot(HMC);

   // Styling of the histograms
   HData.SetStats(0);
   HMC.SetStats(0);

   HData.SetMarkerColor(kRed + 1);
   HData.SetLineColor(kRed + 1);

   HMC.SetFillColor(kAzure + 8);
   HMC.SetLineColor(kWhite);

   // Legends
   TLegend Legend(0.475, 0.675, 0.8, 0.8);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&HData, "data", "p");
   if(IsPP == true)
      Legend.AddEntry(&HMC, "PYTHIA", "f");
   else
      Legend.AddEntry(&HMC, "PYTHIA+HYDJET", "f");

   // Profit!
   TH2D HWorld("HWorld", ";p_{T,g}/p_{T,jet};#frac{1}{N_{jet}}#frac{dN}{d(p_{T,g}/p_{T,jet})}",
      Bin, Min, Max, Bin, YMin, YMax);
   HWorld.SetStats(0);

   HWorld.GetXaxis()->CenterTitle();
   HWorld.GetYaxis()->CenterTitle();

   TCanvas C;
   C.SetLogy();

   HWorld.Draw();
   HMC.Draw("hist bar same");
   HData.Draw("same");
   HWorld.Draw("axis same");

   Legend.Draw();

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(12);
   Latex.SetNDC();
   double YTop = 0.825;
   double YSpacing = 0.065;

   if(IsPP == false)
   {
      Latex.DrawLatex(0.15, YTop - 0 * YSpacing, "PbPb #sqrt{s_{NN}} = 5.02 TeV 404 #mub^{-1}");
      Latex.DrawLatex(0.15, YTop - 1 * YSpacing, "Centrality: 0-10\%");
      Latex.DrawLatex(0.15, YTop - 2 * YSpacing, "140 < p_{T,jet} < 160 GeV");
      Latex.DrawLatex(0.15, YTop - 3 * YSpacing, "anti-k_{T} R=0.4 |#eta_{jet}|<1.3");
      if(Is0 == true)
         Latex.DrawLatex(0.15, YTop - 4 * YSpacing, "SoftDrop #beta=0 z_{cut}=0.1");
      else
         Latex.DrawLatex(0.15, YTop - 4 * YSpacing, "SoftDrop #beta=1.5 z_{cut}=0.5");
      Latex.DrawLatex(0.15, YTop - 5 * YSpacing, "#DeltaR_{12} > 0.1");
      Latex.DrawLatex(0.15, YTop - 6 * YSpacing, "#font[62]{CMS Preliminary}");
   }
   else
   {
      Latex.DrawLatex(0.15, YTop - 0 * YSpacing, "pp #sqrt{s_{NN}} = 5.02 TeV 25.8 pb^{-1}");
      Latex.DrawLatex(0.15, YTop - 1 * YSpacing, "140 < p_{T,jet} < 160 GeV");
      Latex.DrawLatex(0.15, YTop - 2 * YSpacing, "anti-k_{T} R=0.4 |#eta_{jet}|<1.3");
      if(Is0 == true)
         Latex.DrawLatex(0.15, YTop - 3 * YSpacing, "SoftDrop #beta=0 z_{cut}=0.1");
      else
         Latex.DrawLatex(0.15, YTop - 3 * YSpacing, "SoftDrop #beta=1.5 z_{cut}=0.5");
      Latex.DrawLatex(0.15, YTop - 4 * YSpacing, "#DeltaR_{12} > 0.1");
      Latex.DrawLatex(0.15, YTop - 5 * YSpacing, "#font[62]{CMS Preliminary}");
   }

   string Tag = "Comparison";
   Tag = Tag + "_" + (IsPP ? "PP" : "AA");
   Tag = Tag + "_SD" + (Is0 ? "0" : "7");
   
   C.SaveAs(Form("%s.png", Tag.c_str()));
   C.SaveAs(Form("%s.C",   Tag.c_str()));
   C.SaveAs(Form("%s.eps", Tag.c_str()));
   C.SaveAs(Form("%s.pdf", Tag.c_str()));

   PdfFile.AddCanvas(C);
}
   
void FillHistogram(TH1D &H, string FileName, char SD, bool IsMC, bool IsPP)
{
   TFile F(FileName.c_str());

   TTree *T = (TTree *)F.Get("T");

   double PT1, Eta1, Phi1, PT2, Eta2, Phi2, PT, W = 1.00, Eta, Match, C = 0.00, DR;
   T->SetBranchAddress(Form("SubJet1PT%c", SD), &PT1);
   T->SetBranchAddress(Form("SubJet1Eta%c", SD), &Eta1);
   T->SetBranchAddress(Form("SubJet1Phi%c", SD), &Phi1);
   T->SetBranchAddress(Form("SubJet2PT%c", SD), &PT2);
   T->SetBranchAddress(Form("SubJet2Eta%c", SD), &Eta2);
   T->SetBranchAddress(Form("SubJet2Phi%c", SD), &Phi2);
   T->SetBranchAddress("MatchPT", &PT);
   T->SetBranchAddress("JetEta", &Eta);
   T->SetBranchAddress("MatchDR", &Match);
   if(IsMC == true)
      T->SetBranchAddress("MCWeight", &W);
   if(IsPP == false)
      T->SetBranchAddress("Centrality", &C);
   T->SetBranchAddress(Form("SubJetDR%c", SD), &DR);

   int EntryCount = T->GetEntries() * 0.1;
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);

      if(Match > 0.1)
         continue;
      if(PT < 140 || PT > 160)
         continue;
      if(abs(Eta) > 1.3)
         continue;

      if(IsPP == false && C > 0.1)
         continue;

      if(DR < 0.1)
         continue;

      FourVector P1, P2;
      P1.SetPtEtaPhi(PT1, Eta1, Phi1);
      P2.SetPtEtaPhi(PT2, Eta2, Phi2);

      double F = (P1 + P2).GetPT() / PT;

      H.Fill(F, W);
   }

   int Bin = H.GetNbinsX();
   double Min = H.GetXaxis()->GetBinLowEdge(1);
   double Max = H.GetXaxis()->GetBinUpEdge(Bin);
   double BinSize = (Max - Min) / Bin;

   H.Scale(1 / H.Integral() / BinSize);

   F.Close();
}




