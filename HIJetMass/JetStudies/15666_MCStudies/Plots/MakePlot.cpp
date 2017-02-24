#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TTree.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main();
void SetAlias(TTree *Tree);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("AllPlots.pdf", "");

   PdfFile.AddTextPage("Different SD parameters");

   TFile F1("ScaledResult/PP8Dijet.root");
   TFile F2("ScaledResult/AA8Dijet.root");
   TFile F3("ScaledResult/PPDataHighPTJet_NoCrossSection.root");
   TFile F4("ScaledResult/AAData_NoCrossSection.root");

   TTree *T1 = (TTree *)F1.Get("Tree");
   TTree *T2 = (TTree *)F2.Get("Tree");
   TTree *T3 = (TTree *)F3.Get("Tree");
   TTree *T4 = (TTree *)F4.Get("Tree");

   SetAlias(T1);
   SetAlias(T2);
   SetAlias(T3);
   SetAlias(T4);

   TH1D HA1("HA1", "SDMass PPDijet", 100, 0, 60);
   TH1D HB1("HB1", "SDMass AADijet", 100, 0, 60);
   TH1D HC1("HC1", "SDMass PPData", 100, 0, 60);
   TH1D HD1("HD1", "SDMass AAData", 100, 0, 60);
   TH1D HA2("HA2", "ZG PPDijet", 100, 0, 0.5);
   TH1D HB2("HB2", "ZG AADijet", 100, 0, 0.5);
   TH1D HC2("HC2", "ZG PPData", 100, 0, 0.5);
   TH1D HD2("HD2", "ZG AAData", 100, 0, 0.5);

   TCanvas C, C4;
   C4.Divide(2, 2);
   
   PdfFile.AddTextPage("Matching between reclustered jet and original jet");
   
   C4.cd(1);
   T1->Draw("log(JetShift)/log(10)", "(NewJetPT/JetPT > 0.8 && JetPT > 120) * MCWeight");
   C4.cd(2);
   T2->Draw("log(JetShift)/log(10)", "(NewJetPT/JetPT > 0.8 && JetPT > 120) * MCWeight");
   C4.cd(3);
   T3->Draw("log(JetShift)/log(10)", "(NewJetPT/JetPT > 0.8 && JetPT > 120)");
   C4.cd(4);
   T4->Draw("log(JetShift)/log(10)", "(NewJetPT/JetPT > 0.8 && JetPT > 120)");

   PdfFile.AddCanvas(C4);
   
   PdfFile.AddTextPage("Stored SD mass with no matching cut");
   
   C4.cd(1);
   T1->Draw("JetSDMass>>HA1", "(JetSDRecoDR > 0.1 && JetPT > 120 && JetSDMass < 60) * MCWeight");
   C4.cd(2);
   T2->Draw("JetSDMass>>HB1", "(JetSDRecoDR > 0.1 && JetPT > 120 && JetSDMass < 60) * MCWeight");
   C4.cd(3);
   T3->Draw("JetSDMass>>HC1", "(JetSDRecoDR > 0.1 && JetPT > 120 && JetSDMass < 60)");
   C4.cd(4);
   T4->Draw("JetSDMass>>HD1", "(JetSDRecoDR > 0.1 && JetPT > 120 && JetSDMass < 60)");

   PdfFile.AddCanvas(C4);
   
   PdfFile.AddTextPage("Stored SD mass with some matching cut");
   
   C4.cd(1);
   T1->Draw("JetSDMass>>HA1", "(JetSDRecoDR > 0.1 && JetShift < 0.05 && NewJetPT/JetPT > 0.8 && JetPT > 120) * MCWeight");
   C4.cd(2);
   T2->Draw("JetSDMass>>HB1", "(JetSDRecoDR > 0.1 && JetShift < 0.05 && NewJetPT/JetPT > 0.8 && JetPT > 120) * MCWeight");
   C4.cd(3);
   T3->Draw("JetSDMass>>HC1", "(JetSDRecoDR > 0.1 && JetShift < 0.05 && NewJetPT/JetPT > 0.8 && JetPT > 120)");
   C4.cd(4);
   T4->Draw("JetSDMass>>HD1", "(JetSDRecoDR > 0.1 && JetShift < 0.05 && NewJetPT/JetPT > 0.8 && JetPT > 120)");

   PdfFile.AddCanvas(C4);
   
   PdfFile.AddTextPage("Stored SD mass with very tight matching cut");
   
   C4.cd(1);
   T1->Draw("JetSDMass>>HA1", "(JetSDRecoDR > 0.1 && log(JetShift) / log(10) < -3.0 && NewJetPT/JetPT > 0.8 && JetPT > 120) * MCWeight");
   C4.cd(2);
   T2->Draw("JetSDMass>>HB1", "(JetSDRecoDR > 0.1 && log(JetShift) / log(10) < -3.0 && NewJetPT/JetPT > 0.8 && JetPT > 120) * MCWeight");
   C4.cd(3);
   T3->Draw("JetSDMass>>HC1", "(JetSDRecoDR > 0.1 && log(JetShift) / log(10) < -3.0 && NewJetPT/JetPT > 0.8 && JetPT > 120)");
   C4.cd(4);
   T4->Draw("JetSDMass>>HD1", "(JetSDRecoDR > 0.1 && log(JetShift) / log(10) < -3.0 && NewJetPT/JetPT > 0.8 && JetPT > 120)");

   PdfFile.AddCanvas(C4);

   PdfFile.AddTextPage("Stored SD mass with baseline cut (DR 0.05, PT ratio 0.8)");
   
   C4.cd(1);
   T1->Draw("JetSDMass>>HA1", "Baseline * (JetSDRecoDR > 0.1 && NewJetPT/JetPT > 0.8 && JetPT > 120 && JetSDMass < 60) * MCWeight");
   C4.cd(2);
   T2->Draw("JetSDMass>>HB1", "Baseline * (JetSDRecoDR > 0.1 && NewJetPT/JetPT > 0.8 && JetPT > 120 && JetSDMass < 60) * MCWeight");
   C4.cd(3);
   T3->Draw("JetSDMass>>HC1", "Baseline * (JetSDRecoDR > 0.1 && NewJetPT/JetPT > 0.8 && JetPT > 120 && JetSDMass < 60)");
   C4.cd(4);
   T4->Draw("JetSDMass>>HD1", "Baseline * (JetSDRecoDR > 0.1 && NewJetPT/JetPT > 0.8 && JetPT > 120 && JetSDMass < 60)");

   PdfFile.AddCanvas(C4);
   
   double Z[10] = {0.1, 0.2, 0.3, 0.05, 0.1, 0.1, 0.1, 0.5, 0.3, 0.2};
   double Beta[10] = {0.0, 0.0, 0.0, 0.0, 0.5, 1.0, 2.0, 1.5, 1.5, 1.5};

   for(int i = 0; i < 10; i++)
   {
      PdfFile.AddTextPage(Form("Scenario %d", i));

      TH1D HZ("HZ", "SD Condition;Sub-jet DR;SD Threshold", 1000, 0, 0.4);
      HZ.SetStats(0);
      for(int j = 1; j <= 1000; j++)
      {
         double DR = HZ.GetXaxis()->GetBinCenter(j);
         double SDThreshold = Z[i] * pow(DR / 0.4, Beta[i]);
         HZ.SetBinContent(j, SDThreshold);
      }
      PdfFile.AddPlot(HZ);
   
      HA1.SetLineColor(kBlack);
      HB1.SetLineColor(kBlack);
      HC1.SetLineColor(kBlack);
      HD1.SetLineColor(kBlack);
      HA1.SetMarkerColor(kBlack);
      HB1.SetMarkerColor(kBlack);
      HC1.SetMarkerColor(kBlack);
      HD1.SetMarkerColor(kBlack);

      TCanvas Canvas;
      TCanvas Canvas2;

      Canvas.Divide(2, 2);

      Canvas.cd(1);
      T1->Draw(Form("SDMass[%d] * JEC>>HA1", i), Form("Baseline * (SDRecoDR[%d] > 0.1 && NewJetPT/JetPT > 0.8 && JetPT > 120 && SDMass[%d] * JEC < 60) * MCWeight", i, i));
      Canvas.cd(2);
      T2->Draw(Form("SDMass[%d] * JEC>>HB1", i), Form("Baseline * (SDRecoDR[%d] > 0.1 && NewJetPT/JetPT > 0.8 && JetPT > 120 && SDMass[%d] * JEC < 60) * MCWeight", i, i));
      Canvas.cd(3);
      T3->Draw(Form("SDMass[%d] * JEC>>HC1", i), Form("Baseline * (SDRecoDR[%d] > 0.1 && NewJetPT/JetPT > 0.8 && JetPT > 120 && SDMass[%d] * JEC < 60)", i, i));
      Canvas.cd(4);
      T4->Draw(Form("SDMass[%d] * JEC>>HD1", i), Form("Baseline * (SDRecoDR[%d] > 0.1 && NewJetPT/JetPT > 0.8 && JetPT > 120 && SDMass[%d] * JEC < 60)", i, i));

      PdfFile.AddCanvas(Canvas);
      
      Canvas2.cd();

      HA1.SetLineColor(kBlack);
      HB1.SetLineColor(kRed);
      HC1.SetLineColor(kGreen + 3);
      HD1.SetLineColor(kYellow + 3);
      HA1.SetMarkerColor(kBlack);
      HB1.SetMarkerColor(kRed);
      HC1.SetMarkerColor(kGreen + 3);
      HD1.SetMarkerColor(kYellow + 3);

      HA1.Scale(1 / HA1.Integral());
      HB1.Scale(1 / HB1.Integral());
      HC1.Scale(1 / HC1.Integral());
      HD1.Scale(1 / HD1.Integral());

      HA1.Draw();
      HB1.Draw("same");
      HC1.Draw("same");
      HD1.Draw("same");

      PdfFile.AddCanvas(Canvas2);
      
      Canvas.cd();

      Canvas.cd(1);
      T1->Draw(Form("SDZG[%d]>>HA2", i), Form("Baseline * (SDRecoDR[%d] > 0.1 && NewJetPT/JetPT > 0.8 && JetPT > 120) * MCWeight", i, i));
      Canvas.cd(2);
      T2->Draw(Form("SDZG[%d]>>HB2", i), Form("Baseline * (SDRecoDR[%d] > 0.1 && NewJetPT/JetPT > 0.8 && JetPT > 120) * MCWeight", i, i));
      Canvas.cd(3);
      T3->Draw(Form("SDZG[%d]>>HC2", i), Form("Baseline * (SDRecoDR[%d] > 0.1 && NewJetPT/JetPT > 0.8 && JetPT > 120)", i, i));
      Canvas.cd(4);
      T4->Draw(Form("SDZG[%d]>>HD2", i), Form("Baseline * (SDRecoDR[%d] > 0.1 && NewJetPT/JetPT > 0.8 && JetPT > 120)", i, i));
      
      PdfFile.AddCanvas(Canvas);
      
      Canvas2.cd();
      
      HA2.SetLineColor(kBlack);
      HB2.SetLineColor(kRed);
      HC2.SetLineColor(kGreen + 3);
      HD2.SetLineColor(kYellow + 3);
      HA2.SetMarkerColor(kBlack);
      HB2.SetMarkerColor(kRed);
      HC2.SetMarkerColor(kGreen + 3);
      HD2.SetMarkerColor(kYellow + 3);
      
      HA2.Scale(1 / HA2.Integral());
      HB2.Scale(1 / HB2.Integral());
      HC2.Scale(1 / HC2.Integral());
      HD2.Scale(1 / HD2.Integral());

      HA2.Draw();
      HB2.Draw("same");
      HC2.Draw("same");
      HD2.Draw("same");
      
      PdfFile.AddCanvas(Canvas2);
   }

   F4.Close();
   F3.Close();
   F2.Close();
   F1.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void SetAlias(TTree *Tree)
{
   if(Tree == NULL)
      return;
   Tree->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   Tree->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   Tree->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   Tree->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   Tree->SetAlias("Baseline", "(JetShift < 0.05 && NewJetPT/JetPT > 0.8 && JetSDZG > 0)");
   Tree->SetAlias("JEC", "(JetPT/NewJetPT)");
}



