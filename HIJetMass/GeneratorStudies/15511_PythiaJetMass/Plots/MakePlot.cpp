#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TCanvas.h"

int main();
void ExportHistogram1D(TFile &File, string HistogramName, string OutputName);
void ExportHistogram2D(TFile &File, string HistogramName, string OutputName);
void ExportHistogram2DWithProfile(TFile &File, string HistogramName, string ProfileName, string OutputName);

int main()
{
   TFile File("Output.root");

   ExportHistogram1D(File, "HJetPT", "JetPT");
   ExportHistogram1D(File, "HJetEta", "JetEta");
   ExportHistogram2DWithProfile(File, "HJetMassPT", "PJetMassPT", "JetMassPT");
   ExportHistogram2DWithProfile(File, "HJetGroomedMassPT", "PJetGroomedMassPT", "JetGroomedMassPT");

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

   C.SetGridx();
   C.SetGridy();

   C.SaveAs(Form("%s.png", OutputName.c_str()));
   C.SaveAs(Form("%s.C", OutputName.c_str()));
   C.SaveAs(Form("%s.eps", OutputName.c_str()));
   C.SaveAs(Form("%s.pdf", OutputName.c_str()));
}







