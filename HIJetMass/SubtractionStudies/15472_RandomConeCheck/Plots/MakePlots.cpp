#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main(int argc, char *argv[]);
void NormalizeHistogram(TH1D *H);

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputBase" << endl;
      return -1;
   }

   SetThesisStyle();

   string InputFile = argv[1];
   string OutputBase = argv[2];

   TFile File(InputFile.c_str());

   TH2D *H = (TH2D *)File.Get("HSubtractedPTCentrality");
   H->SetTitle("");
   H->GetXaxis()->SetTitle("Centrality");
   H->GetYaxis()->SetTitle("PT-subtracted random cone");
   H->SetStats(0);

   TH1D *H1 = (TH1D *)H->ProjectionY("H1", 1, 10);
   TH1D *H2 = (TH1D *)H->ProjectionY("H2", 11, 30);
   TH1D *H3 = (TH1D *)H->ProjectionY("H3", 31, 50);
   TH1D *H4 = (TH1D *)H->ProjectionY("H4", 51, 80);
   TH1D *H5 = (TH1D *)H->ProjectionY("H5", 81, 100);

   NormalizeHistogram(H1);
   NormalizeHistogram(H2);
   NormalizeHistogram(H3);
   NormalizeHistogram(H4);
   NormalizeHistogram(H5);

   H1->SetLineColor(kBlack);
   H1->SetMarkerColor(kBlack);
   H1->SetMarkerStyle(8);
   H2->SetLineColor(kRed);
   H2->SetMarkerColor(kRed);
   H2->SetMarkerStyle(8);
   H3->SetLineColor(kBlue);
   H3->SetMarkerColor(kBlue);
   H3->SetMarkerStyle(8);
   H4->SetLineColor(kGreen - 3);
   H4->SetMarkerColor(kGreen - 3);
   H4->SetMarkerStyle(8);
   H5->SetLineColor(kCyan - 3);
   H5->SetMarkerColor(kCyan - 3);
   H5->SetMarkerStyle(8);

   TCanvas C;

   H->Draw("colz");

   C.SetLogz(true);
   
   C.SaveAs(Form("SubtractedPTCentrality_%s.png", OutputBase.c_str()));
   C.SaveAs(Form("SubtractedPTCentrality_%s.C", OutputBase.c_str()));
   C.SaveAs(Form("SubtractedPTCentrality_%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("SubtractedPTCentrality_%s.pdf", OutputBase.c_str()));

   TH2D HWorld("HWorld", ";PT-subtracted random cone;a.u.", 1000, -140, 100, 100, 2e-5, 2);
   HWorld.SetStats(0);

   HWorld.Draw();

   H1->Draw("same");
   H2->Draw("same");
   H3->Draw("same");
   H4->Draw("same");
   H5->Draw("same");

   TLegend Legend(0.14, 0.38, 0.3, 0.88);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetFillStyle(0);
   Legend.SetTextSize(0.025);
   Legend.AddEntry(H1, "0% - 10%", "l");
   Legend.AddEntry("", Form("(#mu = %.1f, RMS = %3.1f)", H1->GetMean(), H1->GetRMS()), "");
   Legend.AddEntry(H2, "10% - 30%", "l");
   Legend.AddEntry("", Form("(#mu = %.1f, RMS = %3.1f)", H2->GetMean(), H2->GetRMS()), "");
   Legend.AddEntry(H3, "30% - 50%", "l");
   Legend.AddEntry("", Form("(#mu = %.1f, RMS = %3.1f)", H3->GetMean(), H3->GetRMS()), "");
   Legend.AddEntry(H4, "50% - 80%", "l");
   Legend.AddEntry("", Form("(#mu = %.1f, RMS = %3.1f)", H4->GetMean(), H4->GetRMS()), "");
   Legend.AddEntry(H5, "80% - 100%", "l");
   Legend.AddEntry("", Form("(#mu = %.1f, RMS = %3.1f)", H5->GetMean(), H5->GetRMS()), "");
   Legend.Draw();

   C.SetLogy(true);
   
   C.SaveAs(Form("SubtractedPT_%s.png", OutputBase.c_str()));
   C.SaveAs(Form("SubtractedPT_%s.C", OutputBase.c_str()));
   C.SaveAs(Form("SubtractedPT_%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("SubtractedPT_%s.pdf", OutputBase.c_str()));

   File.Close();
}

void NormalizeHistogram(TH1D *H)
{
   if(H == NULL)
      return;

   int N = H->GetNbinsX();
   double Left = H->GetXaxis()->GetBinLowEdge(1);
   double Right = H->GetXaxis()->GetBinUpEdge(N);
   double BinSize = (Right - Left) / N;

   H->Scale(1 / H->Integral() / BinSize);
}




