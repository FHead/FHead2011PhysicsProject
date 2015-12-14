#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

int main()
{
   string Histogram = "HMET";
   // string Histogram = "HR";
   // string Histogram = "HMR";

   TFile F("Output.root");
   TFile F2("LQToBNutau_600.root");

   TH1D H("H", "", 10, 0, 1500);   // For MET
   // TH1D H("H", "", 22, 0, 1.5);   // For R^{2}
   // TH1D H("H", "", 22, 180, 1500);   // For MR
   TH1D *H1 = (TH1D *)F.Get(Form("%s_0600_0150", Histogram.c_str()));
   TH1D *H2 = (TH1D *)F.Get(Form("%s_0600_0250", Histogram.c_str()));
   TH1D *H3 = (TH1D *)F.Get(Form("%s_0600_0350", Histogram.c_str()));
   TH1D *H4 = (TH1D *)F.Get(Form("%s_0800_0450", Histogram.c_str()));
   // TH1D *H5 = (TH1D *)F2.Get("HMET_MR400R2014_Had_All");
   // TH1D *H5 = (TH1D *)F2.Get("HR2_MR000_Had_All");
   // TH1D *H5 = (TH1D *)F2.Get("HMR_R2000_Had_All");

   TCanvas C("C", "", 1024, 1024);

   H.GetXaxis()->SetTitle("PF MET (GeV)");
   // H.GetXaxis()->SetTitle("R^{2}");
   // H.GetXaxis()->SetTitle("M_{R} (GeV)");

   H.SetMaximum(0.5);
   H.SetMinimum(0.001);

   H.SetStats(0);
   H1->SetStats(0);
   H2->SetStats(0);
   H3->SetStats(0);
   H4->SetStats(0);
   // H5->SetStats(0);

   H1->SetLineColor(kBlack);
   H2->SetLineColor(kRed);
   H3->SetLineColor(kBlue);
   H4->SetLineColor(kGreen - 3);
   // H5->SetLineColor(kYellow - 3);

   H1->SetLineWidth(2);
   H2->SetLineWidth(2);
   H3->SetLineWidth(2);
   H4->SetLineWidth(2);
   // H5->SetLineWidth(2);

   H.Draw();
   H1->DrawNormalized("same");
   H2->DrawNormalized("same");
   H3->DrawNormalized("same");
   H4->DrawNormalized("same");
   // H5->DrawNormalized("same");

   TLegend Legend(0.55, 0.85, 0.85, 0.65);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(H1, "M_{#tilde{b}} = 600, M_{#tilde{#chi}^{0}_{1}} = 150", "l");
   Legend.AddEntry(H2, "M_{#tilde{b}} = 600, M_{#tilde{#chi}^{0}_{1}} = 250", "l");
   Legend.AddEntry(H3, "M_{#tilde{b}} = 600, M_{#tilde{#chi}^{0}_{1}} = 350", "l");
   Legend.AddEntry(H4, "M_{#tilde{b}} = 800, M_{#tilde{#chi}^{0}_{1}} = 450", "l");
   // Legend.AddEntry(H5, "M_{LQ} = 600, M_{#nu} = 0", "l");
   Legend.Draw();

   C.SetLogy();

   C.SaveAs(Form("%s_Comparison.png", Histogram.c_str()));
   C.SaveAs(Form("%s_Comparison.C", Histogram.c_str()));
   C.SaveAs(Form("%s_Comparison.eps", Histogram.c_str()));
   C.SaveAs(Form("%s_Comparison.pdf", Histogram.c_str()));

   F2.Close();
   F.Close();
}




