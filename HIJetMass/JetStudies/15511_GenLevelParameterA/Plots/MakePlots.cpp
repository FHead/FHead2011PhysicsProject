#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TF1.h"

#include "SetStyle.h"

int main(int argc, char *argv[]);
void ExportHistogram1D(TFile &File, string HistogramName, string OutputName);
void ExportHistogram2D(TFile &File, string HistogramName, string OutputName);
void ExportHistogram2DWithProfile(TFile &File, string HistogramName, string ProfileName, string OutputName);
void ExportHistogram2DWithProfileFit(TFile &File, string HistogramName, string ProfileName, string OutputName);
void NormalizeHistogram(TH1D &H);

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputBase" << endl;
      return -1;
   }

   SetThesisStyle();

   char *InputFile = argv[1];
   char *OutputBase = argv[2];

   TFile File(InputFile);

   ExportHistogram2DWithProfileFit(File, "HPTDepth", "PPTDepth",
      string(OutputBase) + "_DepthPT");
   
   File.Close();

   return 0;
}

void ExportHistogram1D(TFile &File, string HistogramName, string OutputName)
{
   TH1D *H = (TH1D *)File.Get(HistogramName.c_str());

   if(H == NULL)
      return;

   TCanvas C;

   H->SetStats(0);
   H->Draw();

   C.SaveAs(Form("%s.png", OutputName.c_str()));
   C.SaveAs(Form("%s.C", OutputName.c_str()));
   C.SaveAs(Form("%s.eps", OutputName.c_str()));
   C.SaveAs(Form("%s.pdf", OutputName.c_str()));
}

void ExportHistogram2D(TFile &File, string HistogramName, string OutputName)
{
   TH2D *H = (TH2D *)File.Get(HistogramName.c_str());

   if(H == NULL)
      return;

   TCanvas C;

   H->SetStats(0);
   H->Draw("colz");

   C.SaveAs(Form("%s.png", OutputName.c_str()));
   C.SaveAs(Form("%s.C", OutputName.c_str()));
   C.SaveAs(Form("%s.eps", OutputName.c_str()));
   C.SaveAs(Form("%s.pdf", OutputName.c_str()));
}

void ExportHistogram2DWithProfile(TFile &File, string HistogramName, string ProfileName, string OutputName)
{
   TH2D *H = (TH2D *)File.Get(HistogramName.c_str());
   TProfile *P = (TProfile *)File.Get(ProfileName.c_str());

   if(H == NULL || P == NULL)
      return;

   TCanvas C;

   P->Rebin(2);
   P->SetMarkerStyle(8);
   P->SetMarkerColor(kRed);
   P->SetLineWidth(2);
   P->SetLineColor(kRed);

   H->SetStats(0);
   H->Draw("colz");
   P->Draw("same");

   C.SaveAs(Form("%s.png", OutputName.c_str()));
   C.SaveAs(Form("%s.C", OutputName.c_str()));
   C.SaveAs(Form("%s.eps", OutputName.c_str()));
   C.SaveAs(Form("%s.pdf", OutputName.c_str()));
}

void ExportHistogram2DWithProfileFit(TFile &File, string HistogramName, string ProfileName, string OutputName)
{
   TH2D *H = (TH2D *)File.Get(HistogramName.c_str());
   TProfile *P = (TProfile *)File.Get(ProfileName.c_str());

   if(H == NULL || P == NULL)
      return;

   TCanvas C;

   P->Rebin(2);
   P->SetMarkerStyle(8);
   P->SetMarkerColor(kRed);
   P->SetLineWidth(2);
   P->SetLineColor(kRed);

   TF1 F("F", "[0]*log(x)+[1]");
   P->Fit(&F);

   H->SetStats(0);
   H->Draw("colz");
   P->Draw("same");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(P, "Fit: a ln(p_{T}^{jet}) + b", "l");
   Legend.AddEntry("", Form("a = %4.2f #pm %4.2f", F.GetParameter(0), F.GetParError(0)), "");
   Legend.AddEntry("", Form("b = %4.2f #pm %4.2f", F.GetParameter(1), F.GetParError(1)), "");
   Legend.Draw();

   C.SaveAs(Form("%s.png", OutputName.c_str()));
   C.SaveAs(Form("%s.C", OutputName.c_str()));
   C.SaveAs(Form("%s.eps", OutputName.c_str()));
   C.SaveAs(Form("%s.pdf", OutputName.c_str()));
}

void NormalizeHistogram(TH1D &H)
{
   int N = H.GetNbinsX();
   double L = H.GetXaxis()->GetBinLowEdge(1);
   double R = H.GetXaxis()->GetBinUpEdge(N);
   double BinSize = (R - L) / N;

   H.Scale(1 / H.Integral() / BinSize);
}






