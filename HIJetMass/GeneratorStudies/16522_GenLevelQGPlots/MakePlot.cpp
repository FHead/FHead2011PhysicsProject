#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main()
{
   SetThesisStyle();

   TFile File("PP6Dijet.root");

   TTree *Tree = (TTree *)File.Get("GenJetTree");

   double BinSize = (0.25 - 0.00) / 50;
   TH1D HG0("HG0", ";M_{g} / p_{T}^{jet};#frac{1}{N} #frac{d N}{d M_{g} / p_{T}^{jet}}", 50, 0.00, 0.25);
   TH1D HG7("HG7", ";M_{g} / p_{T}^{jet};#frac{1}{N} #frac{d N}{d M_{g} / p_{T}^{jet}}", 50, 0.00, 0.25);
   TH1D HQ0("HQ0", ";M_{g} / p_{T}^{jet};#frac{1}{N} #frac{d N}{d M_{g} / p_{T}^{jet}}", 50, 0.00, 0.25);
   TH1D HQ7("HQ7", ";M_{g} / p_{T}^{jet};#frac{1}{N} #frac{d N}{d M_{g} / p_{T}^{jet}}", 50, 0.00, 0.25);
   TH1D HG0DR("HG0DR", ";M_{g} / p_{T}^{jet};#frac{1}{N} #frac{d N}{d M_{g} / p_{T}^{jet}}", 50, 0.00, 0.25);
   TH1D HG7DR("HG7DR", ";M_{g} / p_{T}^{jet};#frac{1}{N} #frac{d N}{d M_{g} / p_{T}^{jet}}", 50, 0.00, 0.25);
   TH1D HQ0DR("HQ0DR", ";M_{g} / p_{T}^{jet};#frac{1}{N} #frac{d N}{d M_{g} / p_{T}^{jet}}", 50, 0.00, 0.25);
   TH1D HQ7DR("HQ7DR", ";M_{g} / p_{T}^{jet};#frac{1}{N} #frac{d N}{d M_{g} / p_{T}^{jet}}", 50, 0.00, 0.25);

   HG0.SetStats(0);
   HG7.SetStats(0);
   HQ0.SetStats(0);
   HQ7.SetStats(0);
   HG0DR.SetStats(0);
   HG7DR.SetStats(0);
   HQ0DR.SetStats(0);
   HQ7DR.SetStats(0);

   int Type;
   double Mass0, DR0;
   double Mass7, DR7;
   double PT, Eta;
   double W;

   Tree->SetBranchAddress("MatchType", &Type);
   Tree->SetBranchAddress("SDMass0", &Mass0);
   Tree->SetBranchAddress("SDMass7", &Mass7);
   Tree->SetBranchAddress("SubJetDR0", &DR0);
   Tree->SetBranchAddress("SubJetDR7", &DR7);
   Tree->SetBranchAddress("JetPT", &PT);
   Tree->SetBranchAddress("JetEta", &Eta);
   Tree->SetBranchAddress("MCWeight", &W);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(abs(Eta) > 1.3)
         continue;
      if(PT < 100)
         continue;

      if(Type > -6 && Type < 6)
      {
         if(DR0 > 0.0)   HQ0.Fill(Mass0 / PT, W);
         if(DR7 > 0.0)   HQ7.Fill(Mass7 / PT, W);
         if(DR0 > 0.1)   HQ0DR.Fill(Mass0 / PT, W);
         if(DR7 > 0.1)   HQ7DR.Fill(Mass7 / PT, W);
      }
      if(Type == 21)
      {
         if(DR0 > 0.0)   HG0.Fill(Mass0 / PT, W);
         if(DR7 > 0.0)   HG7.Fill(Mass7 / PT, W);
         if(DR0 > 0.1)   HG0DR.Fill(Mass0 / PT, W);
         if(DR7 > 0.1)   HG7DR.Fill(Mass7 / PT, W);
      }
   }

   HG0.Scale(1 / HG0.Integral() / BinSize);
   HG7.Scale(1 / HG7.Integral() / BinSize);
   HQ0.Scale(1 / HQ0.Integral() / BinSize);
   HQ7.Scale(1 / HQ7.Integral() / BinSize);
   HG0DR.Scale(1 / HG0DR.Integral() / BinSize);
   HG7DR.Scale(1 / HG7DR.Integral() / BinSize);
   HQ0DR.Scale(1 / HQ0DR.Integral() / BinSize);
   HQ7DR.Scale(1 / HQ7DR.Integral() / BinSize);

   PdfFileHelper PdfFile("QGPlots.pdf");
   PdfFile.AddTextPage("Q-G plots in pythia6 dijet");

   PdfFile.AddPlot(HG0);
   PdfFile.AddPlot(HG7);
   PdfFile.AddPlot(HQ0);
   PdfFile.AddPlot(HQ7);
   PdfFile.AddPlot(HG0DR);
   PdfFile.AddPlot(HG7DR);
   PdfFile.AddPlot(HQ0DR);
   PdfFile.AddPlot(HQ7DR);

   HG0.SetLineColor(kRed);
   HG0.SetMarkerColor(kRed);
   HG7.SetLineColor(kRed);
   HG7.SetMarkerColor(kRed);
   HQ0.SetLineColor(kBlue);
   HQ0.SetMarkerColor(kBlue);
   HQ7.SetLineColor(kBlue);
   HQ7.SetMarkerColor(kBlue);
   HG0DR.SetLineColor(kRed);
   HG0DR.SetMarkerColor(kRed);
   HG7DR.SetLineColor(kRed);
   HG7DR.SetMarkerColor(kRed);
   HQ0DR.SetLineColor(kBlue);
   HQ0DR.SetMarkerColor(kBlue);
   HQ7DR.SetLineColor(kBlue);
   HQ7DR.SetMarkerColor(kBlue);

   TH2D HWorld("HWorld", ";M_{g} / p_{T}^{jet};#frac{1}{N} #frac{d N}{d M_{g} / p_{T}^{jet}}   ", 100, 0.00, 0.25, 100, 1e-2, 100);
   HWorld.SetStats(0);
   HWorld.GetYaxis()->SetTitleOffset(1.00);
   HWorld.GetXaxis()->CenterTitle();
   HWorld.GetYaxis()->CenterTitle();

   TLegend Legend(0.5, 0.8, 0.8, 0.65);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&HG0, "Gluon", "pl");
   Legend.AddEntry(&HQ0, "Quark", "pl");

   TLegend Legend2(0.5, 0.55, 0.8, 0.4);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.AddEntry(&HG0, "Gluon", "pl");
   Legend2.AddEntry(&HQ0, "Quark", "pl");

   TLatex Text;
   Text.SetTextFont(42);
   Text.SetTextSize(0.035);
   Text.SetTextAlign(11);
   Text.SetNDC();

   TCanvas C;
   C.SetLogy();

   HWorld.Draw("axis");
   HG0.Draw("same");
   HQ0.Draw("same");
   Legend.Draw();

   Text.DrawLatex(0.15, 0.27, "PYTHIA 6, #hat{p}_{T} > 100");
   Text.DrawLatex(0.15, 0.21, "p_{T}^{jet} > 100 GeV, |#eta_{jet}| < 1.3");
   Text.DrawLatex(0.15, 0.15, "Soft Drop z_{cut} = 0.1, #beta = 0.0, #DeltaR_{12} > 0.0");

   C.SaveAs("SD0.png");
   C.SaveAs("SD0.C");
   C.SaveAs("SD0.eps");
   C.SaveAs("SD0.pdf");

   PdfFile.AddCanvas(C);

   HWorld.Draw("axis");
   HG7.Draw("same");
   HQ7.Draw("same");
   Legend.Draw();

   Text.DrawLatex(0.15, 0.27, "PYTHIA 6, #hat{p}_{T} > 100");
   Text.DrawLatex(0.15, 0.21, "p_{T}^{jet} > 100 GeV, |#eta_{jet}| < 1.3");
   Text.DrawLatex(0.15, 0.15, "Soft Drop z_{cut} = 0.5, #beta = 1.5, #DeltaR_{12} > 0.0");

   C.SaveAs("SD7.png");
   C.SaveAs("SD7.C");
   C.SaveAs("SD7.eps");
   C.SaveAs("SD7.pdf");

   PdfFile.AddCanvas(C);

   HWorld.Draw("axis");
   HG0DR.Draw("same");
   HQ0DR.Draw("same");
   Legend.Draw();

   Text.DrawLatex(0.15, 0.27, "PYTHIA 6, #hat{p}_{T} > 100");
   Text.DrawLatex(0.15, 0.21, "p_{T}^{jet} > 100 GeV, |#eta_{jet}| < 1.3");
   Text.DrawLatex(0.15, 0.15, "Soft Drop z_{cut} = 0.1, #beta = 0.0, #DeltaR_{12} > 0.1");

   C.SaveAs("SD0DR.png");
   C.SaveAs("SD0DR.C");
   C.SaveAs("SD0DR.eps");
   C.SaveAs("SD0DR.pdf");

   PdfFile.AddCanvas(C);

   HWorld.Draw("axis");
   HG7DR.Draw("same");
   HQ7DR.Draw("same");
   Legend.Draw();

   Text.DrawLatex(0.15, 0.27, "PYTHIA 6, #hat{p}_{T} > 100");
   Text.DrawLatex(0.15, 0.21, "p_{T}^{jet} > 100 GeV, |#eta_{jet}| < 1.3");
   Text.DrawLatex(0.15, 0.15, "Soft Drop z_{cut} = 0.5, #beta = 1.5, #DeltaR_{12} > 0.1");

   C.SaveAs("SD7DR.png");
   C.SaveAs("SD7DR.C");
   C.SaveAs("SD7DR.eps");
   C.SaveAs("SD7DR.pdf");

   PdfFile.AddCanvas(C);

   TH2D HWorld2("HWorld2", ";M_{g} / p_{T}^{jet};#frac{1}{N} #frac{d N}{d M_{g} / p_{T}^{jet}}   ", 100, 0.00, 0.25, 100, 0, 40);
   HWorld2.SetStats(0);
   HWorld2.GetYaxis()->SetTitleOffset(1.00);
   HWorld2.GetXaxis()->CenterTitle();
   HWorld2.GetYaxis()->CenterTitle();

   C.SetLogy(false);

   HWorld2.Draw("axis");
   HG0.Draw("same");
   HQ0.Draw("same");
   HG0.Draw("same hist");
   HQ0.Draw("same hist");
   Legend2.Draw();
   
   Text.SetTextAlign(31);
   Text.DrawLatex(0.80, 0.83, "PYTHIA 6, #hat{p}_{T} > 100");
   Text.DrawLatex(0.80, 0.77, "p_{T}^{jet} > 100 GeV, |#eta_{jet}| < 1.3");
   Text.DrawLatex(0.80, 0.71, "Soft Drop z_{cut} = 0.1, #beta = 0.0, #DeltaR_{12} > 0.0");

   C.SaveAs("SD0Linear.png");
   C.SaveAs("SD0Linear.C");
   C.SaveAs("SD0Linear.eps");
   C.SaveAs("SD0Linear.pdf");

   PdfFile.AddCanvas(C);
 
   HWorld2.Draw("axis");
   HG7.Draw("same");
   HQ7.Draw("same");
   HG7.Draw("same hist");
   HQ7.Draw("same hist");
   Legend2.Draw();
   
   Text.DrawLatex(0.80, 0.83, "PYTHIA 6, #hat{p}_{T} > 100");
   Text.DrawLatex(0.80, 0.77, "p_{T}^{jet} > 100 GeV, |#eta_{jet}| < 1.3");
   Text.DrawLatex(0.80, 0.71, "Soft Drop z_{cut} = 0.5, #beta = 1.5, #DeltaR_{12} > 0.0");

   C.SaveAs("SD7Linear.png");
   C.SaveAs("SD7Linear.C");
   C.SaveAs("SD7Linear.eps");
   C.SaveAs("SD7Linear.pdf");

   PdfFile.AddCanvas(C);
   
   TH2D HWorld3("HWorld3", ";M_{g} / p_{T}^{jet};#frac{1}{N} #frac{d N}{d M_{g} / p_{T}^{jet}}   ", 100, 0.00, 0.25, 100, 0, 25);
   HWorld3.SetStats(0);
   HWorld3.GetYaxis()->SetTitleOffset(1.00);
   HWorld3.GetXaxis()->CenterTitle();
   HWorld3.GetYaxis()->CenterTitle();

   HWorld3.Draw("axis");
   HG0DR.Draw("same");
   HQ0DR.Draw("same");
   HG0DR.Draw("same hist");
   HQ0DR.Draw("same hist");
   Legend2.Draw();
   
   Text.DrawLatex(0.80, 0.83, "PYTHIA 6, #hat{p}_{T} > 100");
   Text.DrawLatex(0.80, 0.77, "p_{T}^{jet} > 100 GeV, |#eta_{jet}| < 1.3");
   Text.DrawLatex(0.80, 0.71, "Soft Drop z_{cut} = 0.1, #beta = 0.0, #DeltaR_{12} > 0.1");

   C.SaveAs("SD0DRLinear.png");
   C.SaveAs("SD0DRLinear.C");
   C.SaveAs("SD0DRLinear.eps");
   C.SaveAs("SD0DRLinear.pdf");

   PdfFile.AddCanvas(C);

   HWorld3.Draw("axis");
   HG7DR.Draw("same");
   HQ7DR.Draw("same");
   HG7DR.Draw("same hist");
   HQ7DR.Draw("same hist");
   Legend2.Draw();

   Text.DrawLatex(0.80, 0.83, "PYTHIA 6, #hat{p}_{T} > 100");
   Text.DrawLatex(0.80, 0.77, "p_{T}^{jet} > 100 GeV, |#eta_{jet}| < 1.3");
   Text.DrawLatex(0.80, 0.71, "Soft Drop z_{cut} = 0.5, #beta = 1.5, #DeltaR_{12} > 0.1");

   C.SaveAs("SD7DRLinear.png");
   C.SaveAs("SD7DRLinear.C");
   C.SaveAs("SD7DRLinear.eps");
   C.SaveAs("SD7DRLinear.pdf");

   PdfFile.AddCanvas(C);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();

   return 0;
}




