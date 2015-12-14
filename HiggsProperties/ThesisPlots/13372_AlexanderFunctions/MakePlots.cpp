#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "Shapes.h"

int main()
{
   double Min = 10;
   double Max = 1000;
   int Bin = 1000;

   double Bins[1001] = {0};
   for(int i = 0; i <= Bin; i++)
      Bins[i] = exp((log(Max) - log(Min)) / Bin * i + log(Min));

   TH1D H1A1("H1A1", ";Charge (fC);Ratio to trigger time sample", 1000, Bins);
   TH1D H2A1("H2A1", ";Charge (fC);Ratio to trigger time sample", 1000, Bins);
   TH1D H3A1("H3A1", ";Charge (fC);Ratio to trigger time sample", 1000, Bins);
   TH1D H4A1("H4A1", ";Charge (fC);Ratio to trigger time sample", 1000, Bins);
   TH1D H5A1("H5A1", ";Charge (fC);Ratio to trigger time sample", 1000, Bins);
   TH1D H6A1("H6A1", ";Charge (fC);Ratio to trigger time sample", 1000, Bins);
   TH1D H1A2("H1A2", ";Charge (fC);Ratio to trigger time sample", 1000, Bins);
   TH1D H2A2("H2A2", ";Charge (fC);Ratio to trigger time sample", 1000, Bins);
   TH1D H3A2("H3A2", ";Charge (fC);Ratio to trigger time sample", 1000, Bins);
   TH1D H4A2("H4A2", ";Charge (fC);Ratio to trigger time sample", 1000, Bins);
   TH1D H5A2("H5A2", ";Charge (fC);Ratio to trigger time sample", 1000, Bins);
   TH1D H6A2("H6A2", ";Charge (fC);Ratio to trigger time sample", 1000, Bins);

   for(int i = 1; i <= 1000; i++)
   {
      double Charge = H1A1.GetBinCenter(i);

      H1A1.SetBinContent(i, a1_HB(Charge) / Charge);
      H2A1.SetBinContent(i, a1_1720(Charge) / Charge);
      H3A1.SetBinContent(i, a1_2123(Charge) / Charge);
      H4A1.SetBinContent(i, a1_2425(Charge) / Charge);
      H5A1.SetBinContent(i, a1_2627(Charge) / Charge);
      H6A1.SetBinContent(i, a1_28(Charge) / Charge);
      H1A2.SetBinContent(i, a2_HB(Charge) / Charge);
      H2A2.SetBinContent(i, a2_1720(Charge) / Charge);
      H3A2.SetBinContent(i, a2_2123(Charge) / Charge);
      H4A2.SetBinContent(i, a2_2425(Charge) / Charge);
      H5A2.SetBinContent(i, a2_2627(Charge) / Charge);
      H6A2.SetBinContent(i, a2_28(Charge) / Charge);
   }

   H1A1.SetStats(0);
   H1A1.SetMaximum(1);
   H1A1.SetMinimum(0);
   H1A1.GetXaxis()->SetTitleOffset(1.1);
   H1A1.GetYaxis()->SetTitleOffset(1.2);
   H1A2.SetStats(0);
   H1A2.SetMaximum(1);
   H1A2.SetMinimum(0);
   H1A2.GetXaxis()->SetTitleOffset(1.1);
   H1A2.GetYaxis()->SetTitleOffset(1.2);

   H1A1.SetLineWidth(2);   H1A1.SetLineColor(kBlack);
   H2A1.SetLineWidth(2);   H2A1.SetLineColor(kBlue);
   H3A1.SetLineWidth(2);   H3A1.SetLineColor(kRed);
   H4A1.SetLineWidth(2);   H4A1.SetLineColor(kCyan - 3);
   H5A1.SetLineWidth(2);   H5A1.SetLineColor(kGreen - 3);
   H6A1.SetLineWidth(2);   H6A1.SetLineColor(kYellow - 3);
   H1A2.SetLineWidth(2);   H1A2.SetLineColor(kBlack);
   H2A2.SetLineWidth(2);   H2A2.SetLineColor(kBlue);
   H3A2.SetLineWidth(2);   H3A2.SetLineColor(kRed);
   H4A2.SetLineWidth(2);   H4A2.SetLineColor(kCyan - 3);
   H5A2.SetLineWidth(2);   H5A2.SetLineColor(kGreen - 3);
   H6A2.SetLineWidth(2);   H6A2.SetLineColor(kYellow - 3);

   TLegend Legend(0.5, 0.85, 0.8, 0.45);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&H1A1, "Barrel", "l");
   Legend.AddEntry(&H2A1, "Endcap (|i#eta| = 17-20)", "l");
   Legend.AddEntry(&H3A1, "Endcap (|i#eta| = 21-23)", "l");
   Legend.AddEntry(&H4A1, "Endcap (|i#eta| = 24-25)", "l");
   Legend.AddEntry(&H5A1, "Endcap (|i#eta| = 26-27)", "l");
   Legend.AddEntry(&H6A1, "Endcap (|i#eta| = 28-29)", "l");

   TCanvas C("C", "C", 1024, 1024);
   C.SetLogx();

   H1A1.Draw();
   H2A1.Draw("same");
   H3A1.Draw("same");
   H4A1.Draw("same");
   H5A1.Draw("same");
   H6A1.Draw("same");
   Legend.Draw();

   C.SaveAs("HcalNoise-25nsData-TimeSampleRatioFunctions1.png");
   C.SaveAs("HcalNoise-25nsData-TimeSampleRatioFunctions1.C");
   C.SaveAs("HcalNoise-25nsData-TimeSampleRatioFunctions1.eps");
   C.SaveAs("HcalNoise-25nsData-TimeSampleRatioFunctions1.pdf");

   H1A2.Draw();
   H2A2.Draw("same");
   H3A2.Draw("same");
   H4A2.Draw("same");
   H5A2.Draw("same");
   H6A2.Draw("same");
   Legend.Draw();

   C.SaveAs("HcalNoise-25nsData-TimeSampleRatioFunctions2.png");
   C.SaveAs("HcalNoise-25nsData-TimeSampleRatioFunctions2.C");
   C.SaveAs("HcalNoise-25nsData-TimeSampleRatioFunctions2.eps");
   C.SaveAs("HcalNoise-25nsData-TimeSampleRatioFunctions2.pdf");

   return 0;
}





