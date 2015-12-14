#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"

int main()
{
   TFile F("Matrices.root");

   TH1D *HZ = (TH1D *)F.Get("HMRStar_RStar020Cut_Znunu");
   TH1D *HW = (TH1D *)F.Get("HMRStar_RStar020Cut_W");

   HZ->SetStats(0);
   HW->SetStats(0);

   HZ->SetLineColor(kBlue);
   HW->SetLineColor(kRed);

   HZ->SetLineWidth(2);
   HW->SetLineWidth(2);

   HZ->SetTitle("Znunu vs. W shape in signal selection (no b-tag), R (new) > 0.2");

   TCanvas C("C", "C", 1024, 768);

   HZ->GetXaxis()->SetTitle("MR (new)");
   HZ->GetYaxis()->SetTitle("a.u.");

   HZ->Scale(1.0 / HZ->Integral(11, 999));
   HW->Scale(1.0 / HW->Integral(11, 999));

   HZ->Draw();
   HW->Draw("same");

   TLegend legend(0.5, 0.8, 0.8, 0.6);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.AddEntry(HZ, "Znunu", "l");
   legend.AddEntry(HW, "W", "l");
   legend.SetTextFont(42);
   legend.Draw();

   C.SetLogy();
   C.SaveAs("ZnunuWComparison.png");
   C.SaveAs("ZnunuWComparison.C");
   C.SaveAs("ZnunuWComparison.eps");
   C.SaveAs("ZnunuWComparison.pdf");

   F.Close();

   return 0;
}





