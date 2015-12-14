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
   TFile FW("W.root");
   TFile FTTbar("TTbar.root");
   TFile FLM1("LM1.root");

   TH2D *HQCD = (TH2D *)FQCD.Get("HPFJetMRVsR2");
   TH2D *HW = (TH2D *)FW.Get("HPFJetMRVsR2");
   TH2D *HTTbar = (TH2D *)FTTbar.Get("HPFJetMRVsR2");
   TH2D *HLM1 = (TH2D *)FLM1.Get("HPFJetMRVsR2");

   cout << HQCD->GetEntries() << endl;

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

   HQCD->GetYaxis()->SetTitleOffset(1.1);
   HW->GetYaxis()->SetTitleOffset(1.1);
   HTTbar->GetYaxis()->SetTitleOffset(1.1);
   HLM1->GetYaxis()->SetTitleOffset(1.1);

   HQCD->GetZaxis()->SetTitleOffset(1.1);
   HW->GetZaxis()->SetTitleOffset(1.1);
   HTTbar->GetZaxis()->SetTitleOffset(1.1);
   HLM1->GetZaxis()->SetTitleOffset(1.1);

   HQCD->GetZaxis()->SetNoExponent(false);
   
   HQCD->GetXaxis()->SetNdivisions(505);
   HW->GetXaxis()->SetNdivisions(505);
   HTTbar->GetXaxis()->SetNdivisions(505);
   HLM1->GetXaxis()->SetNdivisions(505);

   TLatex l;
   l.SetTextAlign(12);
   l.SetTextSize(0.045);
   l.SetTextFont(132);
   l.SetNDC();

   double L = 1000;
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
   sprintf(s_latex," #splitline{CMS Simulation}{#sqrt{s}=7 TeV}");

   char *s_lumi = new char[100];
   if(iL_dec == 0)
      sprintf(s_lumi," #int L dt = %d %s", iL, unit);
   else
      sprintf(s_lumi," #int L dt = %d.%d %s", iL, iL_dec, unit);

   TCanvas C("C", "C", 0, 0, 1024, 1024);
   C.Divide(2, 2, 0.05, 0.05);
   C.cd(1);
   HQCD->Draw("colz");
   l.DrawLatex(0.57, 0.87, s_latex);
   l.DrawLatex(0.57, 0.74 ,s_lumi);
   l.DrawLatex(0.25, 0.85, "QCD");
   C.cd(2);
   HW->Draw("colz");
   l.DrawLatex(0.57, 0.87, s_latex);
   l.DrawLatex(0.57, 0.74 ,s_lumi);
   l.DrawLatex(0.25, 0.85, "W+Jets");
   C.cd(3);
   HTTbar->Draw("colz");
   l.DrawLatex(0.57, 0.87, s_latex);
   l.DrawLatex(0.57, 0.74 ,s_lumi);
   l.DrawLatex(0.25, 0.85, "t#bar{t}+Jets");
   C.cd(4);
   HLM1->Draw("colz");
   l.DrawLatex(0.57, 0.87, s_latex);
   l.DrawLatex(0.57, 0.74 ,s_lumi);
   l.DrawLatex(0.25, 0.85, "SUSY LM1");
   C.SaveAs("Figure1.png");
   C.SaveAs("Figure1.C");
   C.SaveAs("Figure1.eps");

   FLM1.Close();
   FTTbar.Close();
   FW.Close();
}
