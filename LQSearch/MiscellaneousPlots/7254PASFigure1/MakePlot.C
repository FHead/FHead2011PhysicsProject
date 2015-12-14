#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLatex.h"

#include "SetStyle.h"

void MakePlot()
{
   // gROOT->SetStyle("Plain");
   SetTDRStyle();

   TFile FQCD("QCD_All.root");
   TFile FW("VB.root");
   TFile FTTbar("TTbar.root");
   TFile FLM1("LM6.root");

   TH2D *HQCD = (TH2D *)FQCD.Get("HPFJetMRVsR2");
   TH2D *HW = (TH2D *)FW.Get("HPFJetMRVsR2");
   TH2D *HTTbar = (TH2D *)FTTbar.Get("HPFJetMRVsR2");
   TH2D *HLM1 = (TH2D *)FLM1.Get("HPFJetMRVsR2");

   // cout << HQCD->GetEntries() << endl;

   HQCD->SetStats(0);
   HW->SetStats(0);
   HTTbar->SetStats(0);
   HLM1->SetStats(0);

   HQCD->SetTitle("");
   HW->SetTitle("");
   HTTbar->SetTitle("");
   HLM1->SetTitle("");

   HQCD->GetXaxis()->SetTitle("M_{R} [GeV]");
   HW->GetXaxis()->SetTitle("M_{R} [GeV]");
   HTTbar->GetXaxis()->SetTitle("M_{R} [GeV]");
   HLM1->GetXaxis()->SetTitle("M_{R} [GeV]");
   
   HQCD->GetYaxis()->SetTitle("R^{2}");
   HW->GetYaxis()->SetTitle("R^{2}");
   HTTbar->GetYaxis()->SetTitle("R^{2}");
   HLM1->GetYaxis()->SetTitle("R^{2}");

   HQCD->GetZaxis()->SetTitle("Events / bin");
   HW->GetZaxis()->SetTitle("Events / bin");
   HTTbar->GetZaxis()->SetTitle("Events / bin");
   HLM1->GetZaxis()->SetTitle("Events / bin");

   HQCD->GetXaxis()->CenterTitle();
   HW->GetXaxis()->CenterTitle();
   HTTbar->GetXaxis()->CenterTitle();
   HLM1->GetXaxis()->CenterTitle();

   HQCD->GetYaxis()->CenterTitle();
   HW->GetYaxis()->CenterTitle();
   HTTbar->GetYaxis()->CenterTitle();
   HLM1->GetYaxis()->CenterTitle();

   HQCD->GetZaxis()->CenterTitle();
   HW->GetZaxis()->CenterTitle();
   HTTbar->GetZaxis()->CenterTitle();
   HLM1->GetZaxis()->CenterTitle();

   HQCD->GetXaxis()->SetTitleFont(132);
   HW->GetXaxis()->SetTitleFont(132);
   HTTbar->GetXaxis()->SetTitleFont(132);
   HLM1->GetXaxis()->SetTitleFont(132);
   
   HQCD->GetYaxis()->SetTitleFont(132);
   HW->GetYaxis()->SetTitleFont(132);
   HTTbar->GetYaxis()->SetTitleFont(132);
   HLM1->GetYaxis()->SetTitleFont(132);
   
   HQCD->GetZaxis()->SetTitleFont(132);
   HW->GetZaxis()->SetTitleFont(132);
   HTTbar->GetZaxis()->SetTitleFont(132);
   HLM1->GetZaxis()->SetTitleFont(132);
   
   HQCD->GetXaxis()->SetLabelFont(132);
   HW->GetXaxis()->SetLabelFont(132);
   HTTbar->GetXaxis()->SetLabelFont(132);
   HLM1->GetXaxis()->SetLabelFont(132);
   
   HQCD->GetYaxis()->SetLabelFont(132);
   HW->GetYaxis()->SetLabelFont(132);
   HTTbar->GetYaxis()->SetLabelFont(132);
   HLM1->GetYaxis()->SetLabelFont(132);
   
   HQCD->GetZaxis()->SetLabelFont(132);
   HW->GetZaxis()->SetLabelFont(132);
   HTTbar->GetZaxis()->SetLabelFont(132);
   HLM1->GetZaxis()->SetLabelFont(132);
   
   HQCD->GetXaxis()->SetTitleSize(0.06);
   HW->GetXaxis()->SetTitleSize(0.06);
   HTTbar->GetXaxis()->SetTitleSize(0.06);
   HLM1->GetXaxis()->SetTitleSize(0.06);
   
   HQCD->GetYaxis()->SetTitleSize(0.06);
   HW->GetYaxis()->SetTitleSize(0.06);
   HTTbar->GetYaxis()->SetTitleSize(0.06);
   HLM1->GetYaxis()->SetTitleSize(0.06);
   
   HQCD->GetZaxis()->SetTitleSize(0.06);
   HW->GetZaxis()->SetTitleSize(0.06);
   HTTbar->GetZaxis()->SetTitleSize(0.06);
   HLM1->GetZaxis()->SetTitleSize(0.06);
   
   HQCD->GetXaxis()->SetLabelSize(0.05);
   HW->GetXaxis()->SetLabelSize(0.05);
   HTTbar->GetXaxis()->SetLabelSize(0.05);
   HLM1->GetXaxis()->SetLabelSize(0.05);
   
   HQCD->GetYaxis()->SetLabelSize(0.05);
   HW->GetYaxis()->SetLabelSize(0.05);
   HTTbar->GetYaxis()->SetLabelSize(0.05);
   HLM1->GetYaxis()->SetLabelSize(0.05);
   
   HQCD->GetZaxis()->SetLabelSize(0.05);
   HW->GetZaxis()->SetLabelSize(0.05);
   HTTbar->GetZaxis()->SetLabelSize(0.05);
   HLM1->GetZaxis()->SetLabelSize(0.05);
   
   HQCD->GetXaxis()->SetTitleOffset(1.05);
   HW->GetXaxis()->SetTitleOffset(1.05);
   HTTbar->GetXaxis()->SetTitleOffset(1.05);
   HLM1->GetXaxis()->SetTitleOffset(1.05);

   HQCD->GetYaxis()->SetTitleOffset(1.18);
   HW->GetYaxis()->SetTitleOffset(1.18);
   HTTbar->GetYaxis()->SetTitleOffset(1.18);
   HLM1->GetYaxis()->SetTitleOffset(1.18);

   HQCD->GetZaxis()->SetTitleOffset(0.9);
   HW->GetZaxis()->SetTitleOffset(0.9);
   HTTbar->GetZaxis()->SetTitleOffset(0.9);
   HLM1->GetZaxis()->SetTitleOffset(0.9);

   HQCD->GetZaxis()->SetNoExponent(false);
   HW->GetZaxis()->SetNoExponent(false);
   HTTbar->GetZaxis()->SetNoExponent(false);
   HLM1->GetZaxis()->SetNoExponent(false);
   
   HQCD->GetXaxis()->SetNdivisions(505);
   HW->GetXaxis()->SetNdivisions(505);
   HTTbar->GetXaxis()->SetNdivisions(505);
   HLM1->GetXaxis()->SetNdivisions(505);

   TLatex l;
   l.SetTextAlign(12);
   l.SetTextSize(0.03);
   l.SetTextFont(132);
   l.SetNDC();

   double L = 750;
   int iL;
   int iL_dec;

   char *unit;

   if(L < 1.)
   {
      iL = int(1000. * L);
      iL_dec = 0;
      unit = "nb^{-1}";

   }
   else if(L > 1000.)
   {
      iL = int(L/1000.);
      iL_dec = int(L) % 1000;
      unit = "fb^{-1}";
   }
   else
   {
      iL = int(L);
      iL_dec = int(L * 10) % 10;
      unit = "pb^{-1}";
   }

   char *s_latex = new char[100];
   // sprintf(s_latex," #splitline{CMS Simulation}{#sqrt{s}=7 TeV}");
   sprintf(s_latex, "CMS Simulation #sqrt{s}=7 TeV");

   char *s_lumi = new char[100];
   if(iL_dec == 0)
      sprintf(s_lumi," #int L dt = %d %s", iL, unit);
   else
      sprintf(s_lumi," #int L dt = %d.%d %s", iL, iL_dec, unit);

   TCanvas C1("C1", "C1", 0, 0, 1024, 1024);
   C1.SetTopMargin(0.15);
   C1.SetBottomMargin(0.15);
   C1.SetLeftMargin(0.15);
   C1.SetRightMargin(0.18);
   HQCD->Draw("colz");
   l.SetTextAlign(12);
   l.DrawLatex(0.15, 0.875, s_latex);
   l.SetTextAlign(12);
   l.DrawLatex(0.50, 0.87, "#int L dt = 7.29 nb^{-1}");
   l.SetTextAlign(32);
   l.DrawLatex(0.87, 0.875, "QCD");
   C1.SaveAs("Figure1_QCD.png");
   C1.SaveAs("Figure1_QCD.C");
   C1.SaveAs("Figure1_QCD.eps");
   C1.SaveAs("Figure1_QCD.pdf");

   TCanvas C2("C2", "C2", 0, 0, 1024, 1024);
   C2.SetTopMargin(0.15);
   C2.SetBottomMargin(0.15);
   C2.SetLeftMargin(0.15);
   C2.SetRightMargin(0.18);
   HW->Draw("colz");
   l.SetTextAlign(12);
   l.DrawLatex(0.15, 0.875, s_latex);
   l.SetTextAlign(12);
   l.DrawLatex(0.50, 0.87, s_lumi);
   l.SetTextAlign(32);
   l.DrawLatex(0.87, 0.875, "W, Z");
   C2.SaveAs("Figure1_VB.png");
   C2.SaveAs("Figure1_VB.C");
   C2.SaveAs("Figure1_VB.eps");
   C2.SaveAs("Figure1_VB.pdf");

   TCanvas C3("C3", "C3", 0, 0, 1024, 1024);
   C3.SetTopMargin(0.15);
   C3.SetBottomMargin(0.15);
   C3.SetLeftMargin(0.15);
   C3.SetRightMargin(0.18);
   HLM1->Draw("colz");
   l.SetTextAlign(12);
   l.DrawLatex(0.15, 0.875, s_latex);
   l.SetTextAlign(12);
   l.DrawLatex(0.50, 0.87, s_lumi);
   l.SetTextAlign(32);
   l.DrawLatex(0.87, 0.875, "SUSY LM6");
   C3.SaveAs("Figure1_LM6.png");
   C3.SaveAs("Figure1_LM6.C");
   C3.SaveAs("Figure1_LM6.eps");
   C3.SaveAs("Figure1_LM6.pdf");

   TCanvas C4("C4", "C4", 0, 0, 1024, 1024);
   C4.SetTopMargin(0.15);
   C4.SetBottomMargin(0.15);
   C4.SetLeftMargin(0.15);
   C4.SetRightMargin(0.18);
   HTTbar->Draw("colz");
   l.SetTextAlign(12);
   l.DrawLatex(0.15, 0.875, s_latex);
   l.SetTextAlign(12);
   l.DrawLatex(0.50, 0.87, s_lumi);
   l.SetTextAlign(32);
   l.DrawLatex(0.87, 0.875, "TTbar");
   C4.SaveAs("Figure1_TTbar.png");
   C4.SaveAs("Figure1_TTbar.C");
   C4.SaveAs("Figure1_TTbar.eps");
   C4.SaveAs("Figure1_TTbar.pdf");

   FLM1.Close();
   FTTbar.Close();
   FW.Close();
}

