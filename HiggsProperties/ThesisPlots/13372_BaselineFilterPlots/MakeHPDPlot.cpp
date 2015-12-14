#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

int main()
{
   TFile F1("SingleMu.root");
   TFile F2("MET.root");
   TFile F3("HcalHPDNoise.root");

   TTree *T1 = (TTree *)F1.Get("ExportTree/HcalNoiseTree");
   TTree *T2 = (TTree *)F2.Get("ExportTree/HcalNoiseTree");
   TTree *T3 = (TTree *)F3.Get("ExportTree/HcalNoiseTree");

   TH1D *H1 = new TH1D("H1", ";Number of hits;a.u.", 19, 0, 19);
   TH1D *H2 = new TH1D("H2", ";Number of hits;a.u.", 19, 0, 19);
   TH1D *H3 = new TH1D("H3", ";Number of hits;a.u.", 19, 0, 19);

   TH1D *H4 = new TH1D("H4", ";Number of ADC zeros;a.u.", 50, 0, 50);
   TH1D *H5 = new TH1D("H5", ";Number of ADC zeros;a.u.", 50, 0, 50);
   TH1D *H6 = new TH1D("H6", ";Number of ADC zeros;a.u.", 50, 0, 50);

   T1->Draw("HPDHits>>H1", "", "");
   T2->Draw("HPDHits>>H2", "", "");
   T3->Draw("HPDHits>>H3", "", "");

   T1->Draw("MaxZeros>>H4", "", "");
   T2->Draw("MaxZeros>>H5", "", "");
   T3->Draw("MaxZeros>>H6", "", "");

   H1->Scale(1 / H1->Integral());
   H2->Scale(1 / H2->Integral());
   H3->Scale(1 / H3->Integral());

   H4->Scale(1 / H4->Integral());
   H5->Scale(1 / H5->Integral());
   H6->Scale(1 / H6->Integral());

   H1->SetStats(0);
   H1->SetMinimum(2e-4);
   H1->SetMaximum(1);

   H4->SetStats(0);
   H4->SetMinimum(5e-5);
   H4->SetMaximum(1);

   H1->SetLineWidth(2);
   H1->SetLineColor(kBlack);
   H2->SetLineWidth(2);
   H2->SetLineColor(kRed);
   H3->SetLineWidth(2);
   H3->SetLineColor(kRed);

   H4->SetLineWidth(2);
   H4->SetLineColor(kBlack);
   H5->SetLineWidth(2);
   H5->SetLineColor(kRed);
   H6->SetLineWidth(2);
   H6->SetLineColor(kRed);

   TLegend Legend(0.5, 0.85, 0.85, 0.70);
   Legend.SetTextFont(42);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(H1, "SingleMu dataset", "l");
   Legend.AddEntry(H2, "MET dataset", "l");

   TCanvas C("C", "C", 1024, 1024);
   C.SetLogy();

   H1->Draw();
   H2->Draw("same");
   // H3->Draw("same");
   Legend.Draw();

   C.SaveAs("HcalNoise-2012BaselinePackage-R453.png");
   C.SaveAs("HcalNoise-2012BaselinePackage-R453.C");
   C.SaveAs("HcalNoise-2012BaselinePackage-R453.eps");
   C.SaveAs("HcalNoise-2012BaselinePackage-R453.pdf");

   H4->Draw();
   H5->Draw("same");
   // H6->Draw("same");
   Legend.Draw();

   C.SaveAs("HcalNoise-2012BaselinePackage-R454.png");
   C.SaveAs("HcalNoise-2012BaselinePackage-R454.C");
   C.SaveAs("HcalNoise-2012BaselinePackage-R454.eps");
   C.SaveAs("HcalNoise-2012BaselinePackage-R454.pdf");

   F3.Close();
   F2.Close();
   F1.Close();

   return 0;
}




