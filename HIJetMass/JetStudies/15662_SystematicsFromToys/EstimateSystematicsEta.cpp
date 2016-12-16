#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "Code/DrawRandom.h"
#include "PlotHelper3.h"

#define BIN 40

int main(int argc, char *argv[]);
double GetFlatRMS(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2);
void SetAlias(TTree *Tree);
void AddPlots(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2);

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " BaseFile ModifiedFile Tag" << endl;
      return -1;
   }

   char *BaseFile = argv[1];
   char *ModifiedFile = argv[2];
   char *Tag = argv[3];

   PdfFileHelper PdfFile(string("Systematics_") + Tag + ".pdf");
   PdfFile.AddTextPage("Systematics");

   TFile F1(BaseFile);
   TFile F2(ModifiedFile);

   TTree *T1 = (TTree *)F1.Get("OutputTree");
   TTree *T2 = (TTree *)F2.Get("OutputTree");

   SetAlias(T1);
   SetAlias(T2);
   
   TFile OutputFile((string("OutputFile_") + Tag + ".root").c_str(), "RECREATE");

   TH1D HNominal_P0("HNominal_P0", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HNominal_P1("HNominal_P1", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HNominal_P2("HNominal_P2", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HNominal_P3("HNominal_P3", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HNominal_P4("HNominal_P4", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HNominal_P5("HNominal_P5", ";mass/pt;a.u.", BIN, 0, 0.4);
   
   TH1D HModified_P0("HModified_P0", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HModified_P1("HModified_P1", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HModified_P2("HModified_P2", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HModified_P3("HModified_P3", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HModified_P4("HModified_P4", ";mass/pt;a.u.", BIN, 0, 0.4);
   TH1D HModified_P5("HModified_P5", ";mass/pt;a.u.", BIN, 0, 0.4);

   T1->SetAlias("Fudge", "((MCWeight < 500) * (1 + 122.874 * exp(-0.5 * ((JetPT-45.0945) / 43.8684)**2)))");
   T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P0", "MCWeight * (JetShift < 0.2 && JetPT > 120 && JetPT < 140 && NewJetDR2 > 0.1 && abs(JetEta) > 0.5)");
   T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P1", "MCWeight * (JetShift < 0.2 && JetPT > 140 && JetPT < 160 && NewJetDR2 > 0.1 && abs(JetEta) > 0.5)");
   T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P2", "MCWeight * (JetShift < 0.2 && JetPT > 160 && JetPT < 180 && NewJetDR2 > 0.1 && abs(JetEta) > 0.5)");
   T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P3", "MCWeight * (JetShift < 0.2 && JetPT > 180 && JetPT < 200 && NewJetDR2 > 0.1 && abs(JetEta) > 0.5)");
   T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P4", "MCWeight * (JetShift < 0.2 && JetPT > 200 && JetPT < 300 && NewJetDR2 > 0.1 && abs(JetEta) > 0.5)");
   T1->Draw("NewJetSDMass2/NewJetPT>>HNominal_P5", "MCWeight * (JetShift < 0.2 && JetPT > 300 && JetPT < 500 && NewJetDR2 > 0.1 && abs(JetEta) > 0.5)");
   
   T2->SetAlias("Fudge", "((MCWeight < 500) * (1 + 122.874 * exp(-0.5 * ((JetPT-45.0945) / 43.8684)**2)))");
   T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P0", "MCWeight * (JetShift < 0.2 && JetPT > 120 && JetPT < 140 && NewJetDR2 > 0.1 && abs(JetEta) < 0.5)");
   T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P1", "MCWeight * (JetShift < 0.2 && JetPT > 140 && JetPT < 160 && NewJetDR2 > 0.1 && abs(JetEta) < 0.5)");
   T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P2", "MCWeight * (JetShift < 0.2 && JetPT > 160 && JetPT < 180 && NewJetDR2 > 0.1 && abs(JetEta) < 0.5)");
   T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P3", "MCWeight * (JetShift < 0.2 && JetPT > 180 && JetPT < 200 && NewJetDR2 > 0.1 && abs(JetEta) < 0.5)");
   T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P4", "MCWeight * (JetShift < 0.2 && JetPT > 200 && JetPT < 300 && NewJetDR2 > 0.1 && abs(JetEta) < 0.5)");
   T2->Draw("NewJetSDMass2/NewJetPT>>HModified_P5", "MCWeight * (JetShift < 0.2 && JetPT > 300 && JetPT < 500 && NewJetDR2 > 0.1 && abs(JetEta) < 0.5)");

   HNominal_P0.Scale(1 / HNominal_P0.Integral());
   HNominal_P1.Scale(1 / HNominal_P1.Integral());
   HNominal_P2.Scale(1 / HNominal_P2.Integral());
   HNominal_P3.Scale(1 / HNominal_P3.Integral());
   HNominal_P4.Scale(1 / HNominal_P4.Integral());
   HNominal_P5.Scale(1 / HNominal_P5.Integral());

   PdfFile.AddPlot(HNominal_P0);
   PdfFile.AddPlot(HNominal_P1);
   PdfFile.AddPlot(HNominal_P2);
   PdfFile.AddPlot(HNominal_P3);
   PdfFile.AddPlot(HNominal_P4);
   PdfFile.AddPlot(HNominal_P5);
   
   HModified_P0.Scale(1 / HModified_P0.Integral());
   HModified_P1.Scale(1 / HModified_P1.Integral());
   HModified_P2.Scale(1 / HModified_P2.Integral());
   HModified_P3.Scale(1 / HModified_P3.Integral());
   HModified_P4.Scale(1 / HModified_P4.Integral());
   HModified_P5.Scale(1 / HModified_P5.Integral());

   PdfFile.AddPlot(HModified_P0);
   PdfFile.AddPlot(HModified_P1);
   PdfFile.AddPlot(HModified_P2);
   PdfFile.AddPlot(HModified_P3);
   PdfFile.AddPlot(HModified_P4);
   PdfFile.AddPlot(HModified_P5);

   AddPlots(PdfFile, HNominal_P0, HModified_P0);
   AddPlots(PdfFile, HNominal_P1, HModified_P1);
   AddPlots(PdfFile, HNominal_P2, HModified_P2);
   AddPlots(PdfFile, HNominal_P3, HModified_P3);
   AddPlots(PdfFile, HNominal_P4, HModified_P4);
   AddPlots(PdfFile, HNominal_P5, HModified_P5);

   double RMS_P0 = GetFlatRMS(PdfFile, HNominal_P0, HModified_P0);
   double RMS_P1 = GetFlatRMS(PdfFile, HNominal_P1, HModified_P1);
   double RMS_P2 = GetFlatRMS(PdfFile, HNominal_P2, HModified_P2);
   double RMS_P3 = GetFlatRMS(PdfFile, HNominal_P3, HModified_P3);
   double RMS_P4 = GetFlatRMS(PdfFile, HNominal_P4, HModified_P4);
   double RMS_P5 = GetFlatRMS(PdfFile, HNominal_P5, HModified_P5);

   TGraphAsymmErrors GRatio_C0_P0;   GRatio_C0_P0.SetNameTitle("GRatio_C0_P0", "");
   TGraphAsymmErrors GRatio_C0_P1;   GRatio_C0_P1.SetNameTitle("GRatio_C0_P1", "");
   TGraphAsymmErrors GRatio_C0_P2;   GRatio_C0_P2.SetNameTitle("GRatio_C0_P2", "");
   TGraphAsymmErrors GRatio_C0_P3;   GRatio_C0_P3.SetNameTitle("GRatio_C0_P3", "");
   TGraphAsymmErrors GRatio_C0_P4;   GRatio_C0_P4.SetNameTitle("GRatio_C0_P4", "");
   TGraphAsymmErrors GRatio_C0_P5;   GRatio_C0_P5.SetNameTitle("GRatio_C0_P5", "");
   TGraphAsymmErrors GRatio_C1_P0;   GRatio_C1_P0.SetNameTitle("GRatio_C1_P0", "");
   TGraphAsymmErrors GRatio_C1_P1;   GRatio_C1_P1.SetNameTitle("GRatio_C1_P1", "");
   TGraphAsymmErrors GRatio_C1_P2;   GRatio_C1_P2.SetNameTitle("GRatio_C1_P2", "");
   TGraphAsymmErrors GRatio_C1_P3;   GRatio_C1_P3.SetNameTitle("GRatio_C1_P3", "");
   TGraphAsymmErrors GRatio_C1_P4;   GRatio_C1_P4.SetNameTitle("GRatio_C1_P4", "");
   TGraphAsymmErrors GRatio_C1_P5;   GRatio_C1_P5.SetNameTitle("GRatio_C1_P5", "");
   TGraphAsymmErrors GRatio_C2_P0;   GRatio_C2_P0.SetNameTitle("GRatio_C2_P0", "");
   TGraphAsymmErrors GRatio_C2_P1;   GRatio_C2_P1.SetNameTitle("GRatio_C2_P1", "");
   TGraphAsymmErrors GRatio_C2_P2;   GRatio_C2_P2.SetNameTitle("GRatio_C2_P2", "");
   TGraphAsymmErrors GRatio_C2_P3;   GRatio_C2_P3.SetNameTitle("GRatio_C2_P3", "");
   TGraphAsymmErrors GRatio_C2_P4;   GRatio_C2_P4.SetNameTitle("GRatio_C2_P4", "");
   TGraphAsymmErrors GRatio_C2_P5;   GRatio_C2_P5.SetNameTitle("GRatio_C2_P5", "");
   TGraphAsymmErrors GRatio_C3_P0;   GRatio_C3_P0.SetNameTitle("GRatio_C3_P0", "");
   TGraphAsymmErrors GRatio_C3_P1;   GRatio_C3_P1.SetNameTitle("GRatio_C3_P1", "");
   TGraphAsymmErrors GRatio_C3_P2;   GRatio_C3_P2.SetNameTitle("GRatio_C3_P2", "");
   TGraphAsymmErrors GRatio_C3_P3;   GRatio_C3_P3.SetNameTitle("GRatio_C3_P3", "");
   TGraphAsymmErrors GRatio_C3_P4;   GRatio_C3_P4.SetNameTitle("GRatio_C3_P4", "");
   TGraphAsymmErrors GRatio_C3_P5;   GRatio_C3_P5.SetNameTitle("GRatio_C3_P5", "");
   TGraphAsymmErrors GRatio_C4_P0;   GRatio_C4_P0.SetNameTitle("GRatio_C4_P0", "");
   TGraphAsymmErrors GRatio_C4_P1;   GRatio_C4_P1.SetNameTitle("GRatio_C4_P1", "");
   TGraphAsymmErrors GRatio_C4_P2;   GRatio_C4_P2.SetNameTitle("GRatio_C4_P2", "");
   TGraphAsymmErrors GRatio_C4_P3;   GRatio_C4_P3.SetNameTitle("GRatio_C4_P3", "");
   TGraphAsymmErrors GRatio_C4_P4;   GRatio_C4_P4.SetNameTitle("GRatio_C4_P4", "");
   TGraphAsymmErrors GRatio_C4_P5;   GRatio_C4_P5.SetNameTitle("GRatio_C4_P5", "");
   
   for(int i = 0; i < 160; i++)
   {
      double X = 0.4 / 160 * (i + 0.5);

      GRatio_C0_P0.SetPoint(i, X, 0);
      GRatio_C0_P1.SetPoint(i, X, 0);
      GRatio_C0_P2.SetPoint(i, X, 0);
      GRatio_C0_P3.SetPoint(i, X, 0);
      GRatio_C0_P4.SetPoint(i, X, 0);
      GRatio_C0_P5.SetPoint(i, X, 0);
      GRatio_C1_P0.SetPoint(i, X, 0);
      GRatio_C1_P1.SetPoint(i, X, 0);
      GRatio_C1_P2.SetPoint(i, X, 0);
      GRatio_C1_P3.SetPoint(i, X, 0);
      GRatio_C1_P4.SetPoint(i, X, 0);
      GRatio_C1_P5.SetPoint(i, X, 0);
      GRatio_C2_P0.SetPoint(i, X, 0);
      GRatio_C2_P1.SetPoint(i, X, 0);
      GRatio_C2_P2.SetPoint(i, X, 0);
      GRatio_C2_P3.SetPoint(i, X, 0);
      GRatio_C2_P4.SetPoint(i, X, 0);
      GRatio_C2_P5.SetPoint(i, X, 0);
      GRatio_C3_P0.SetPoint(i, X, 0);
      GRatio_C3_P1.SetPoint(i, X, 0);
      GRatio_C3_P2.SetPoint(i, X, 0);
      GRatio_C3_P3.SetPoint(i, X, 0);
      GRatio_C3_P4.SetPoint(i, X, 0);
      GRatio_C3_P5.SetPoint(i, X, 0);
      GRatio_C4_P0.SetPoint(i, X, 0);
      GRatio_C4_P1.SetPoint(i, X, 0);
      GRatio_C4_P2.SetPoint(i, X, 0);
      GRatio_C4_P3.SetPoint(i, X, 0);
      GRatio_C4_P4.SetPoint(i, X, 0);
      GRatio_C4_P5.SetPoint(i, X, 0);

      GRatio_C0_P0.SetPointError(i, 0, 0, RMS_P0, RMS_P0);
      GRatio_C0_P1.SetPointError(i, 0, 0, RMS_P1, RMS_P1);
      GRatio_C0_P2.SetPointError(i, 0, 0, RMS_P2, RMS_P2);
      GRatio_C0_P3.SetPointError(i, 0, 0, RMS_P3, RMS_P3);
      GRatio_C0_P4.SetPointError(i, 0, 0, RMS_P4, RMS_P4);
      GRatio_C0_P5.SetPointError(i, 0, 0, RMS_P5, RMS_P5);
      GRatio_C1_P0.SetPointError(i, 0, 0, RMS_P0, RMS_P0);
      GRatio_C1_P1.SetPointError(i, 0, 0, RMS_P1, RMS_P1);
      GRatio_C1_P2.SetPointError(i, 0, 0, RMS_P2, RMS_P2);
      GRatio_C1_P3.SetPointError(i, 0, 0, RMS_P3, RMS_P3);
      GRatio_C1_P4.SetPointError(i, 0, 0, RMS_P4, RMS_P4);
      GRatio_C1_P5.SetPointError(i, 0, 0, RMS_P5, RMS_P5);
      GRatio_C2_P0.SetPointError(i, 0, 0, RMS_P0, RMS_P0);
      GRatio_C2_P1.SetPointError(i, 0, 0, RMS_P1, RMS_P1);
      GRatio_C2_P2.SetPointError(i, 0, 0, RMS_P2, RMS_P2);
      GRatio_C2_P3.SetPointError(i, 0, 0, RMS_P3, RMS_P3);
      GRatio_C2_P4.SetPointError(i, 0, 0, RMS_P4, RMS_P4);
      GRatio_C2_P5.SetPointError(i, 0, 0, RMS_P5, RMS_P5);
      GRatio_C3_P0.SetPointError(i, 0, 0, RMS_P0, RMS_P0);
      GRatio_C3_P1.SetPointError(i, 0, 0, RMS_P1, RMS_P1);
      GRatio_C3_P2.SetPointError(i, 0, 0, RMS_P2, RMS_P2);
      GRatio_C3_P3.SetPointError(i, 0, 0, RMS_P3, RMS_P3);
      GRatio_C3_P4.SetPointError(i, 0, 0, RMS_P4, RMS_P4);
      GRatio_C3_P5.SetPointError(i, 0, 0, RMS_P5, RMS_P5);
      GRatio_C4_P0.SetPointError(i, 0, 0, RMS_P0, RMS_P0);
      GRatio_C4_P1.SetPointError(i, 0, 0, RMS_P1, RMS_P1);
      GRatio_C4_P2.SetPointError(i, 0, 0, RMS_P2, RMS_P2);
      GRatio_C4_P3.SetPointError(i, 0, 0, RMS_P3, RMS_P3);
      GRatio_C4_P4.SetPointError(i, 0, 0, RMS_P4, RMS_P4);
      GRatio_C4_P5.SetPointError(i, 0, 0, RMS_P5, RMS_P5);
   }

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

   F2.Close();
   F1.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double GetFlatRMS(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2)
{
   TH1D HLogRatio("HLogRatio", "log(Ratio)", BIN, 0, 0.4);

   TH1D H("H", "H", 10000, -5, 5);

   for(int i = 1; i <= H1.GetNbinsX(); i++)
   {
      double V1 = H1.GetBinContent(i);
      double E1 = H1.GetBinError(i);
      double V2 = H2.GetBinContent(i);
      double E2 = H2.GetBinError(i);

      double LV = (log(V1) - log(V2)) / log(10);
      double LE = sqrt((E1 / V1) * (E1 / V1) + (E2 / V2) * (E2 / V2)) / log(10);
      
      cout << i << " " << V1 << " " << V2 << " " << LV << " " << LE << endl;

      if(V1 == 0 || V2 == 0)
         continue;

      HLogRatio.SetBinContent(i, LV);
      HLogRatio.SetBinError(i, LE);

      for(int j = 0; j < 10000; j++)
         H.Fill(DrawGaussian(LV, LE), 1 / LE / LE);
   }

   TF1 F("F", "gaus");
   H.Fit(&F);
   
   TGraph G1, G2;
   G1.SetPoint(0, 0,  F.GetParameter(2) * 1.50);
   G1.SetPoint(1, 1,  F.GetParameter(2) * 1.50);
   G2.SetPoint(0, 0, -F.GetParameter(2) * 1.50);
   G2.SetPoint(1, 1, -F.GetParameter(2) * 1.50);

   TCanvas C;

   HLogRatio.Draw();
   G1.Draw("same");
   G2.Draw("same");

   PdfFile.AddCanvas(C);
   
   PdfFile.AddPlot(H);

   return F.GetParameter(2) * 1.50;
}

void SetAlias(TTree *Tree)
{
   if(Tree == NULL)
      return;
   Tree->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   Tree->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   Tree->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   Tree->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
}

void AddPlots(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2)
{
   H1.SetLineColor(kBlack);
   H2.SetLineColor(kRed);

   TCanvas C;

   H1.Draw();
   H2.Draw("same");

   PdfFile.AddCanvas(C);
}





