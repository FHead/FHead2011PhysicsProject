#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main();
void MakePlot(PdfFileHelper &PdfFile, string Mass);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("M2DistributionsDifferentMass.pdf");
   PdfFile.AddTextPage("M2 for different masses");

   MakePlot(PdfFile, "18p4");
   MakePlot(PdfFile, "18p9");
   MakePlot(PdfFile, "18p92");
   MakePlot(PdfFile, "18p94");
   MakePlot(PdfFile, "19p3");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void MakePlot(PdfFileHelper &PdfFile, string Mass)
{
   TFile F1(("Phto2e2mu_A1UU_" + Mass + "GeV_NoPDF_ForEff_1.root").c_str());
   TFile F2(("Phto2e2mu_A2UU_" + Mass + "GeV_NoPDF_ForEff_1.root").c_str());
   TFile F3(("Phto2e2mu_A3UU_" + Mass + "GeV_NoPDF_ForEff_1.root").c_str());

   TTree *T1 = (TTree *)F1.Get("Tree");
   TTree *T2 = (TTree *)F2.Get("Tree");
   TTree *T3 = (TTree *)F3.Get("Tree");

   TH1D H1("H1", (Mass + " GeV;M_{2};#frac{1}{#sigma} #frac{d #sigma}{d M_{2}}").c_str(), 100, 0, 10);
   TH1D H2("H2", (Mass + " GeV;M_{2};#frac{1}{#sigma} #frac{d #sigma}{d M_{2}}").c_str(), 100, 0, 10);
   TH1D H3("H3", (Mass + " GeV;M_{2};#frac{1}{#sigma} #frac{d #sigma}{d M_{2}}").c_str(), 100, 0, 10);

   H2.SetStats(0);
   H2.GetXaxis()->CenterTitle();
   H2.GetYaxis()->CenterTitle();

   TCanvas C;

   T1->Draw("Z2Mass>>H1", "", "");
   T2->Draw("Z2Mass>>H2", "", "");
   T3->Draw("Z2Mass>>H3", "", "");

   H1.Scale(1 / H1.Integral() / (10 - 0) * 100);
   H2.Scale(1 / H2.Integral() / (10 - 0) * 100);
   H3.Scale(1 / H3.Integral() / (10 - 0) * 100);

   H2.Draw("hist");
   H1.Draw("hist same");
   H3.Draw("hist same");
   
   H1.Draw("same");
   H2.Draw("same");
   H3.Draw("same");

   H1.SetLineColor(kBlack);
   H2.SetLineColor(kGreen + 3);
   H3.SetLineColor(kRed);
   H1.SetMarkerColor(kBlack);
   H2.SetMarkerColor(kGreen + 3);
   H3.SetMarkerColor(kRed);
   H1.SetMarkerStyle(20);
   H2.SetMarkerStyle(20);
   H3.SetMarkerStyle(20);

   TLegend Legend(0.2, 0.65, 0.5, 0.85);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H1, "A1UU", "lp");
   Legend.AddEntry(&H2, "A2UU", "lp");
   Legend.AddEntry(&H3, "A3UU", "lp");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   C.SetLogy();

   PdfFile.AddCanvas(C);

   F3.Close();
   F2.Close();
   F1.Close();
}






