#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile File("Histograms.root");

   TH1D *H1 = (TH1D *)File.Get("HZ2_A1VVEMP");
   TH1D *H2 = (TH1D *)File.Get("HZ2_A2VVEMP");
   TH1D *H3 = (TH1D *)File.Get("HZ2_A3VVEMP");

   H1->SetTitle("18.92 GeV (Toy from expression)");
   H1->GetXaxis()->SetTitle("M_{2}");
   H1->GetXaxis()->CenterTitle();

   H1->Rebin(20);
   H2->Rebin(20);
   H3->Rebin(20);

   H1->SetStats(0);

   H1->Scale(1 / H1->Integral());
   H2->Scale(1 / H2->Integral());
   H3->Scale(1 / H3->Integral());

   TCanvas C;

   H1->SetMarkerColor(kRed);
   H2->SetMarkerColor(kBlue);
   H3->SetMarkerColor(kGreen);
   
   H1->SetLineColor(kRed);
   H2->SetLineColor(kBlue);
   H3->SetLineColor(kGreen);

   H1->Draw();
   H2->Draw("same");
   H3->Draw("same");
   H1->Draw("same hist");
   H2->Draw("same hist");
   H3->Draw("same hist");

   TLegend Legend(0.2, 0.5, 0.5, 0.8);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(H1, "A1UU", "lp");
   Legend.AddEntry(H2, "A2UU", "lp");
   Legend.AddEntry(H3, "A3UU", "lp");
   Legend.Draw();

   C.SaveAs("M2.pdf");

   C.SetLogy();

   C.SaveAs("M2Log.pdf");
   
   File.Close();

   return 0;
}




