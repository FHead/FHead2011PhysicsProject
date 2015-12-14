#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile File("AllGraphs.root");

   TGraph *GA_YT = (TGraph *)File.Get("YT_BothS_A_Lumi_FloatSingle");
   TGraph *GJ_YT = (TGraph *)File.Get("YT_BothS_J_Lumi_FloatSingle");
   TGraph *GA_YTA = (TGraph *)File.Get("YTA_BothS_A_Lumi_FloatSingle");
   TGraph *GJ_YTA = (TGraph *)File.Get("YTA_BothS_J_Lumi_FloatSingle");

   GA_YT->SetLineWidth(2);
   GJ_YT->SetLineWidth(2);
   GA_YTA->SetLineWidth(2);
   GJ_YTA->SetLineWidth(2);
   
   GA_YT->SetLineColor(kBlack);
   GJ_YT->SetLineColor(kRed);
   GA_YTA->SetLineColor(kBlack);
   GJ_YTA->SetLineColor(kRed);

   TH2D HYT("HYT", "(Float only one);N_{S} / #epsilon;#sigma(yt)", 100, 200, 20000, 100, 0.5, 100);
   TH2D HYTA("HYTA", "(Float only one);N_{S} / #epsilon;#sigma(yta)", 100, 200, 20000, 100, 0.25, 100);

   HYT.SetStats(0);
   HYTA.SetStats(0);

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextSize(0.035);
   Legend.SetTextFont(42);
   Legend.AddEntry(GA_YT, "CMS - tight", "lp");
   Legend.AddEntry(GJ_YT, "Relaxed - #Upsilon", "lp");

   TCanvas C;
   C.SetLogx();
   C.SetLogy();

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.02);
   Latex.SetNDC();

   HYT.Draw();
   GA_YT->Draw("pl");
   GJ_YT->Draw("pl");
   Legend.Draw();
   Latex.DrawLatex(0.1, 0.91, "Very preliminary (Jan 18, 2015)");

   C.SaveAs("YTSigma.png");
   C.SaveAs("YTSigma.C");
   C.SaveAs("YTSigma.eps");
   C.SaveAs("YTSigma.pdf");

   HYTA.Draw();
   GA_YTA->Draw("pl");
   GJ_YTA->Draw("pl");
   Legend.Draw();
   Latex.DrawLatex(0.1, 0.91, "Very preliminary (Jan 18, 2015)");

   C.SaveAs("YTASigma.png");
   C.SaveAs("YTASigma.C");
   C.SaveAs("YTASigma.eps");
   C.SaveAs("YTASigma.pdf");

   File.Close();

   return 0;
}
