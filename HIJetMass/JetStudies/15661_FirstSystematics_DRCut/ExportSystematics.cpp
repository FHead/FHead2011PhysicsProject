#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include "Code/DrawRandom.h"
#include "PlotHelper3.h"
#include "SetStyle.h"
#include "ProgressBar.h"
#include "TGraphAsymmErrors.h"

int main();
TGraphAsymmErrors GetEnvelope(TH2D &HRatio);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("Spectra.pdf");
   PdfFile.AddTextPage("DR cut systematics");

   TFile File("PP6Dijet.root");

   TTree *Tree = (TTree *)File.Get("OutputTree");

   Tree->SetAlias("Baseline", "(JetPT > 140)");

   TFile OutputFile("OutputFile.root", "recreate");

   TH1D HNominal_P0("HNominal_P0", ";mass/pt;a.u.", 160, 0, 0.4);
   TH1D HNominal_P1("HNominal_P1", ";mass/pt;a.u.", 160, 0, 0.4);
   TH1D HNominal_P2("HNominal_P2", ";mass/pt;a.u.", 160, 0, 0.4);
   TH1D HNominal_P3("HNominal_P3", ";mass/pt;a.u.", 160, 0, 0.4);
   TH1D HNominal_P4("HNominal_P4", ";mass/pt;a.u.", 160, 0, 0.4);
   TH1D HNominal_P5("HNominal_P5", ";mass/pt;a.u.", 160, 0, 0.4);

   Tree->Draw("NewJetSDMass2/NewJetPT>>HNominal_P0", Form("MCWeight * (JetPT > 120 && JetPT < 140 && NewJetDR2 > %f)", 0.100));
   Tree->Draw("NewJetSDMass2/NewJetPT>>HNominal_P1", Form("MCWeight * (JetPT > 140 && JetPT < 160 && NewJetDR2 > %f)", 0.100));
   Tree->Draw("NewJetSDMass2/NewJetPT>>HNominal_P2", Form("MCWeight * (JetPT > 160 && JetPT < 180 && NewJetDR2 > %f)", 0.100));
   Tree->Draw("NewJetSDMass2/NewJetPT>>HNominal_P3", Form("MCWeight * (JetPT > 180 && JetPT < 200 && NewJetDR2 > %f)", 0.100));
   Tree->Draw("NewJetSDMass2/NewJetPT>>HNominal_P4", Form("MCWeight * (JetPT > 200 && JetPT < 300 && NewJetDR2 > %f)", 0.100));
   Tree->Draw("NewJetSDMass2/NewJetPT>>HNominal_P5", Form("MCWeight * (JetPT > 300 && JetPT < 500 && NewJetDR2 > %f)", 0.100));

   HNominal_P0.Scale(1 / HNominal_P0.Integral());
   HNominal_P1.Scale(1 / HNominal_P1.Integral());
   HNominal_P2.Scale(1 / HNominal_P2.Integral());
   HNominal_P3.Scale(1 / HNominal_P3.Integral());
   HNominal_P4.Scale(1 / HNominal_P4.Integral());
   HNominal_P5.Scale(1 / HNominal_P5.Integral());

   TH2D HRatio_C0_P0("HRatio_C0_P0", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C0_P1("HRatio_C0_P1", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C0_P2("HRatio_C0_P2", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C0_P3("HRatio_C0_P3", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C0_P4("HRatio_C0_P4", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C0_P5("HRatio_C0_P5", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C1_P0("HRatio_C1_P0", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C1_P1("HRatio_C1_P1", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C1_P2("HRatio_C1_P2", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C1_P3("HRatio_C1_P3", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C1_P4("HRatio_C1_P4", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C1_P5("HRatio_C1_P5", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C2_P0("HRatio_C2_P0", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C2_P1("HRatio_C2_P1", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C2_P2("HRatio_C2_P2", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C2_P3("HRatio_C2_P3", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C2_P4("HRatio_C2_P4", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C2_P5("HRatio_C2_P5", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C3_P0("HRatio_C3_P0", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C3_P1("HRatio_C3_P1", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C3_P2("HRatio_C3_P2", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C3_P3("HRatio_C3_P3", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C3_P4("HRatio_C3_P4", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C3_P5("HRatio_C3_P5", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C4_P0("HRatio_C4_P0", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C4_P1("HRatio_C4_P1", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C4_P2("HRatio_C4_P2", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C4_P3("HRatio_C4_P3", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C4_P4("HRatio_C4_P4", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   TH2D HRatio_C4_P5("HRatio_C4_P5", ";mass/pt;log_{10}(a.u.)", 160, 0, 0.4, 1000, -2, 2);
   
   int EntryCount = 100;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(0);

   for(int iT = 0; iT < EntryCount; iT++)
   {
      Bar.Update(iT);
      Bar.Print();

      double DR = DrawGaussian(0.1, 0.01);

      TH1D HMass_P0("HMass_P0", ";mass/pt;a.u.", 160, 0, 0.4);
      TH1D HMass_P1("HMass_P1", ";mass/pt;a.u.", 160, 0, 0.4);
      TH1D HMass_P2("HMass_P2", ";mass/pt;a.u.", 160, 0, 0.4);
      TH1D HMass_P3("HMass_P3", ";mass/pt;a.u.", 160, 0, 0.4);
      TH1D HMass_P4("HMass_P4", ";mass/pt;a.u.", 160, 0, 0.4);
      TH1D HMass_P5("HMass_P5", ";mass/pt;a.u.", 160, 0, 0.4);

      Tree->Draw("NewJetSDMass2/NewJetPT>>HMass_P0",
         Form("MCWeight * (JetPT > 120 && JetPT < 140 && NewJetDR2 > %f)", DR));
      Tree->Draw("NewJetSDMass2/NewJetPT>>HMass_P1",
         Form("MCWeight * (JetPT > 140 && JetPT < 160 && NewJetDR2 > %f)", DR));
      Tree->Draw("NewJetSDMass2/NewJetPT>>HMass_P2",
         Form("MCWeight * (JetPT > 160 && JetPT < 180 && NewJetDR2 > %f)", DR));
      Tree->Draw("NewJetSDMass2/NewJetPT>>HMass_P3",
         Form("MCWeight * (JetPT > 180 && JetPT < 200 && NewJetDR2 > %f)", DR));
      Tree->Draw("NewJetSDMass2/NewJetPT>>HMass_P4",
         Form("MCWeight * (JetPT > 200 && JetPT < 300 && NewJetDR2 > %f)", DR));
      Tree->Draw("NewJetSDMass2/NewJetPT>>HMass_P5",
         Form("MCWeight * (JetPT > 300 && JetPT < 500 && NewJetDR2 > %f)", DR));

      HMass_P0.Scale(1 / HMass_P0.Integral());
      HMass_P1.Scale(1 / HMass_P1.Integral());
      HMass_P2.Scale(1 / HMass_P2.Integral());
      HMass_P3.Scale(1 / HMass_P3.Integral());
      HMass_P4.Scale(1 / HMass_P4.Integral());
      HMass_P5.Scale(1 / HMass_P5.Integral());

      for(int i = 1; i <= HMass_P0.GetNbinsX(); i++)
      {
         double x, y, NominalY;

         x = HMass_P0.GetBinCenter(i);
         
         y = HMass_P0.GetBinContent(i);
         NominalY = HNominal_P0.GetBinContent(i);
         HRatio_C0_P0.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C1_P0.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C2_P0.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C3_P0.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C4_P0.Fill(x, (log(y) - log(NominalY)) / log(10));
         
         y = HMass_P1.GetBinContent(i);
         NominalY = HNominal_P1.GetBinContent(i);
         HRatio_C0_P1.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C1_P1.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C2_P1.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C3_P1.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C4_P1.Fill(x, (log(y) - log(NominalY)) / log(10));
         
         y = HMass_P2.GetBinContent(i);
         NominalY = HNominal_P2.GetBinContent(i);
         HRatio_C0_P2.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C1_P2.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C2_P2.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C3_P2.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C4_P2.Fill(x, (log(y) - log(NominalY)) / log(10));
         
         y = HMass_P3.GetBinContent(i);
         NominalY = HNominal_P3.GetBinContent(i);
         HRatio_C0_P3.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C1_P3.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C2_P3.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C3_P3.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C4_P3.Fill(x, (log(y) - log(NominalY)) / log(10));
         
         y = HMass_P4.GetBinContent(i);
         NominalY = HNominal_P4.GetBinContent(i);
         HRatio_C0_P4.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C1_P4.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C2_P4.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C3_P4.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C4_P4.Fill(x, (log(y) - log(NominalY)) / log(10));
         
         y = HMass_P5.GetBinContent(i);
         NominalY = HNominal_P5.GetBinContent(i);
         HRatio_C0_P5.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C1_P5.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C2_P5.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C3_P5.Fill(x, (log(y) - log(NominalY)) / log(10));
         HRatio_C4_P5.Fill(x, (log(y) - log(NominalY)) / log(10));
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   PdfFile.AddPlot(HNominal_P0);
   PdfFile.AddPlot(HNominal_P1);
   PdfFile.AddPlot(HNominal_P2);
   PdfFile.AddPlot(HNominal_P3);
   PdfFile.AddPlot(HNominal_P4);
   PdfFile.AddPlot(HNominal_P5);

   PdfFile.AddPlot(HRatio_C0_P0, "colz", false, true);
   PdfFile.AddPlot(HRatio_C0_P1, "colz", false, true);
   PdfFile.AddPlot(HRatio_C0_P2, "colz", false, true);
   PdfFile.AddPlot(HRatio_C0_P3, "colz", false, true);
   PdfFile.AddPlot(HRatio_C0_P4, "colz", false, true);
   PdfFile.AddPlot(HRatio_C0_P5, "colz", false, true);

   HNominal_P0.Write();
   HNominal_P1.Write();
   HNominal_P2.Write();
   HNominal_P3.Write();
   HNominal_P4.Write();
   HNominal_P5.Write();

   HRatio_C0_P0.Write();
   HRatio_C0_P1.Write();
   HRatio_C0_P2.Write();
   HRatio_C0_P3.Write();
   HRatio_C0_P4.Write();
   HRatio_C0_P5.Write();
   HRatio_C1_P0.Write();
   HRatio_C1_P1.Write();
   HRatio_C1_P2.Write();
   HRatio_C1_P3.Write();
   HRatio_C1_P4.Write();
   HRatio_C1_P5.Write();
   HRatio_C2_P0.Write();
   HRatio_C2_P1.Write();
   HRatio_C2_P2.Write();
   HRatio_C2_P3.Write();
   HRatio_C2_P4.Write();
   HRatio_C2_P5.Write();
   HRatio_C3_P0.Write();
   HRatio_C3_P1.Write();
   HRatio_C3_P2.Write();
   HRatio_C3_P3.Write();
   HRatio_C3_P4.Write();
   HRatio_C3_P5.Write();
   HRatio_C4_P0.Write();
   HRatio_C4_P1.Write();
   HRatio_C4_P2.Write();
   HRatio_C4_P3.Write();
   HRatio_C4_P4.Write();
   HRatio_C4_P5.Write();

   TGraphAsymmErrors GRatio_C0_P0 = GetEnvelope(HRatio_C0_P0);
   TGraphAsymmErrors GRatio_C0_P1 = GetEnvelope(HRatio_C0_P1);
   TGraphAsymmErrors GRatio_C0_P2 = GetEnvelope(HRatio_C0_P2);
   TGraphAsymmErrors GRatio_C0_P3 = GetEnvelope(HRatio_C0_P3);
   TGraphAsymmErrors GRatio_C0_P4 = GetEnvelope(HRatio_C0_P4);
   TGraphAsymmErrors GRatio_C0_P5 = GetEnvelope(HRatio_C0_P5);
   TGraphAsymmErrors GRatio_C1_P0 = GetEnvelope(HRatio_C1_P0);
   TGraphAsymmErrors GRatio_C1_P1 = GetEnvelope(HRatio_C1_P1);
   TGraphAsymmErrors GRatio_C1_P2 = GetEnvelope(HRatio_C1_P2);
   TGraphAsymmErrors GRatio_C1_P3 = GetEnvelope(HRatio_C1_P3);
   TGraphAsymmErrors GRatio_C1_P4 = GetEnvelope(HRatio_C1_P4);
   TGraphAsymmErrors GRatio_C1_P5 = GetEnvelope(HRatio_C1_P5);
   TGraphAsymmErrors GRatio_C2_P0 = GetEnvelope(HRatio_C2_P0);
   TGraphAsymmErrors GRatio_C2_P1 = GetEnvelope(HRatio_C2_P1);
   TGraphAsymmErrors GRatio_C2_P2 = GetEnvelope(HRatio_C2_P2);
   TGraphAsymmErrors GRatio_C2_P3 = GetEnvelope(HRatio_C2_P3);
   TGraphAsymmErrors GRatio_C2_P4 = GetEnvelope(HRatio_C2_P4);
   TGraphAsymmErrors GRatio_C2_P5 = GetEnvelope(HRatio_C2_P5);
   TGraphAsymmErrors GRatio_C3_P0 = GetEnvelope(HRatio_C3_P0);
   TGraphAsymmErrors GRatio_C3_P1 = GetEnvelope(HRatio_C3_P1);
   TGraphAsymmErrors GRatio_C3_P2 = GetEnvelope(HRatio_C3_P2);
   TGraphAsymmErrors GRatio_C3_P3 = GetEnvelope(HRatio_C3_P3);
   TGraphAsymmErrors GRatio_C3_P4 = GetEnvelope(HRatio_C3_P4);
   TGraphAsymmErrors GRatio_C3_P5 = GetEnvelope(HRatio_C3_P5);
   TGraphAsymmErrors GRatio_C4_P0 = GetEnvelope(HRatio_C4_P0);
   TGraphAsymmErrors GRatio_C4_P1 = GetEnvelope(HRatio_C4_P1);
   TGraphAsymmErrors GRatio_C4_P2 = GetEnvelope(HRatio_C4_P2);
   TGraphAsymmErrors GRatio_C4_P3 = GetEnvelope(HRatio_C4_P3);
   TGraphAsymmErrors GRatio_C4_P4 = GetEnvelope(HRatio_C4_P4);
   TGraphAsymmErrors GRatio_C4_P5 = GetEnvelope(HRatio_C4_P5);

   GRatio_C0_P0.SetNameTitle("GRatio_C0_P0", "");
   GRatio_C0_P1.SetNameTitle("GRatio_C0_P1", "");
   GRatio_C0_P2.SetNameTitle("GRatio_C0_P2", "");
   GRatio_C0_P3.SetNameTitle("GRatio_C0_P3", "");
   GRatio_C0_P4.SetNameTitle("GRatio_C0_P4", "");
   GRatio_C0_P5.SetNameTitle("GRatio_C0_P5", "");
   GRatio_C1_P0.SetNameTitle("GRatio_C1_P0", "");
   GRatio_C1_P1.SetNameTitle("GRatio_C1_P1", "");
   GRatio_C1_P2.SetNameTitle("GRatio_C1_P2", "");
   GRatio_C1_P3.SetNameTitle("GRatio_C1_P3", "");
   GRatio_C1_P4.SetNameTitle("GRatio_C1_P4", "");
   GRatio_C1_P5.SetNameTitle("GRatio_C1_P5", "");
   GRatio_C2_P0.SetNameTitle("GRatio_C2_P0", "");
   GRatio_C2_P1.SetNameTitle("GRatio_C2_P1", "");
   GRatio_C2_P2.SetNameTitle("GRatio_C2_P2", "");
   GRatio_C2_P3.SetNameTitle("GRatio_C2_P3", "");
   GRatio_C2_P4.SetNameTitle("GRatio_C2_P4", "");
   GRatio_C2_P5.SetNameTitle("GRatio_C2_P5", "");
   GRatio_C3_P0.SetNameTitle("GRatio_C3_P0", "");
   GRatio_C3_P1.SetNameTitle("GRatio_C3_P1", "");
   GRatio_C3_P2.SetNameTitle("GRatio_C3_P2", "");
   GRatio_C3_P3.SetNameTitle("GRatio_C3_P3", "");
   GRatio_C3_P4.SetNameTitle("GRatio_C3_P4", "");
   GRatio_C3_P5.SetNameTitle("GRatio_C3_P5", "");
   GRatio_C4_P0.SetNameTitle("GRatio_C4_P0", "");
   GRatio_C4_P1.SetNameTitle("GRatio_C4_P1", "");
   GRatio_C4_P2.SetNameTitle("GRatio_C4_P2", "");
   GRatio_C4_P3.SetNameTitle("GRatio_C4_P3", "");
   GRatio_C4_P4.SetNameTitle("GRatio_C4_P4", "");
   GRatio_C4_P5.SetNameTitle("GRatio_C4_P5", "");
   
   GRatio_C0_P0.Write();
   GRatio_C0_P1.Write();
   GRatio_C0_P2.Write();
   GRatio_C0_P3.Write();
   GRatio_C0_P4.Write();
   GRatio_C0_P5.Write();
   GRatio_C1_P0.Write();
   GRatio_C1_P1.Write();
   GRatio_C1_P2.Write();
   GRatio_C1_P3.Write();
   GRatio_C1_P4.Write();
   GRatio_C1_P5.Write();
   GRatio_C2_P0.Write();
   GRatio_C2_P1.Write();
   GRatio_C2_P2.Write();
   GRatio_C2_P3.Write();
   GRatio_C2_P4.Write();
   GRatio_C2_P5.Write();
   GRatio_C3_P0.Write();
   GRatio_C3_P1.Write();
   GRatio_C3_P2.Write();
   GRatio_C3_P3.Write();
   GRatio_C3_P4.Write();
   GRatio_C3_P5.Write();
   GRatio_C4_P0.Write();
   GRatio_C4_P1.Write();
   GRatio_C4_P2.Write();
   GRatio_C4_P3.Write();
   GRatio_C4_P4.Write();
   GRatio_C4_P5.Write();

   PdfFile.AddPlot(GRatio_C0_P0);
   PdfFile.AddPlot(GRatio_C0_P1);
   PdfFile.AddPlot(GRatio_C0_P2);
   PdfFile.AddPlot(GRatio_C0_P3);
   PdfFile.AddPlot(GRatio_C0_P4);
   PdfFile.AddPlot(GRatio_C0_P5);

   OutputFile.Close();

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

TGraphAsymmErrors GetEnvelope(TH2D &HRatio)
{
   int Count = 0;
   double X[200] = {0};
   double RMS[200] = {0};

   for(int i = 1; i <= HRatio.GetNbinsX(); i++)
   {
      X[Count] = HRatio.GetXaxis()->GetBinCenter(i);
      RMS[Count] = HRatio.ProjectionY("HProjected", i, i)->GetRMS();
      Count = Count + 1;
   }

   for(int i = Count - 2; i >= 0; i--)
   {
      if(RMS[i] < RMS[i+1])
         RMS[i] = RMS[i+1];
   }
   
   for(int i = 1; i < Count; i++)
   {
      if(RMS[i] < 1e-5)
         RMS[i] = RMS[i-1];
   }

   TGraphAsymmErrors G;
   for(int i = 0; i < Count; i++)
   {
      G.SetPoint(i, X[i], 0);
      G.SetPointError(i, 0, 0, RMS[i], RMS[i]);
   }

   return G;
}



