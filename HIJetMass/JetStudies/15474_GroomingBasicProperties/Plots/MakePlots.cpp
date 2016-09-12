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

   ExportHistogram2DWithProfile(File, "HPTGroomedRatio", "PPTGroomedRatio",
      string(OutputBase) + "_GroomedRatioPT");
   ExportHistogram2DWithProfile(File, "HEtaGroomedRatio", "PEtaGroomedRatio",
      string(OutputBase) + "_GroomedRatioEta");
   ExportHistogram2DWithProfileFit(File, "HPTDepth", "PPTDepth",
      string(OutputBase) + "_DepthPT");
   ExportHistogram2DWithProfile(File, "HEtaDepth", "PEtaDepth",
      string(OutputBase) + "_DepthEta");
   
   ExportHistogram2D(File, "PGroomedRatio", string(OutputBase) + "_GroomedRatio");
   ExportHistogram2D(File, "PDepth", string(OutputBase) + "_Depth");

   TH1D *HGroomedRatio_PT100 = (TH1D *)File.Get("HGroomedRatio_PT100");
   TH1D *HGroomedRatio_PT120 = (TH1D *)File.Get("HGroomedRatio_PT120");
   TH1D *HGroomedRatio_PT140 = (TH1D *)File.Get("HGroomedRatio_PT140");
   TH1D *HGroomedRatio_PT160 = (TH1D *)File.Get("HGroomedRatio_PT160");
   TH1D *HGroomedRatio_PT200 = (TH1D *)File.Get("HGroomedRatio_PT200");
   TH1D *HDepth_PT100 = (TH1D *)File.Get("HDepth_PT100");
   TH1D *HDepth_PT120 = (TH1D *)File.Get("HDepth_PT120");
   TH1D *HDepth_PT140 = (TH1D *)File.Get("HDepth_PT140");
   TH1D *HDepth_PT160 = (TH1D *)File.Get("HDepth_PT160");
   TH1D *HDepth_PT200 = (TH1D *)File.Get("HDepth_PT200");

   HGroomedRatio_PT100->Rebin(5);
   HGroomedRatio_PT120->Rebin(5);
   HGroomedRatio_PT140->Rebin(5);
   HGroomedRatio_PT160->Rebin(5);
   HGroomedRatio_PT200->Rebin(5);

   NormalizeHistogram(*HGroomedRatio_PT100);
   NormalizeHistogram(*HGroomedRatio_PT120);
   NormalizeHistogram(*HGroomedRatio_PT140);
   NormalizeHistogram(*HGroomedRatio_PT160);
   NormalizeHistogram(*HGroomedRatio_PT200);
   NormalizeHistogram(*HDepth_PT100);
   NormalizeHistogram(*HDepth_PT120);
   NormalizeHistogram(*HDepth_PT140);
   NormalizeHistogram(*HDepth_PT160);
   NormalizeHistogram(*HDepth_PT200);

   HGroomedRatio_PT100->SetLineColor(kBlack);
   HGroomedRatio_PT120->SetLineColor(kGreen - 3);
   HGroomedRatio_PT140->SetLineColor(kBlue);
   HGroomedRatio_PT160->SetLineColor(kRed);
   HGroomedRatio_PT200->SetLineColor(kCyan - 3);
   HDepth_PT100->SetLineColor(kBlack);
   HDepth_PT120->SetLineColor(kGreen - 3);
   HDepth_PT140->SetLineColor(kBlue);
   HDepth_PT160->SetLineColor(kRed);
   HDepth_PT200->SetLineColor(kCyan - 3);
   
   HGroomedRatio_PT100->SetMarkerColor(kBlack);
   HGroomedRatio_PT120->SetMarkerColor(kGreen - 3);
   HGroomedRatio_PT140->SetMarkerColor(kBlue);
   HGroomedRatio_PT160->SetMarkerColor(kRed);
   HGroomedRatio_PT200->SetMarkerColor(kCyan - 3);
   HDepth_PT100->SetMarkerColor(kBlack);
   HDepth_PT120->SetMarkerColor(kGreen - 3);
   HDepth_PT140->SetMarkerColor(kBlue);
   HDepth_PT160->SetMarkerColor(kRed);
   HDepth_PT200->SetMarkerColor(kCyan - 3);
   
   HGroomedRatio_PT100->SetMarkerStyle(11);
   HGroomedRatio_PT120->SetMarkerStyle(11);
   HGroomedRatio_PT140->SetMarkerStyle(11);
   HGroomedRatio_PT160->SetMarkerStyle(11);
   HGroomedRatio_PT200->SetMarkerStyle(11);
   HDepth_PT100->SetMarkerStyle(11);
   HDepth_PT120->SetMarkerStyle(11);
   HDepth_PT140->SetMarkerStyle(11);
   HDepth_PT160->SetMarkerStyle(11);
   HDepth_PT200->SetMarkerStyle(11);

   TCanvas C;

   TH2D HWorld("HWorld", "Groomed jet PT ratio;PT Groomed / PT Jet; a.u.", 100, 0.4, 1.0, 100, 1e-3, 100);
   HWorld.SetStats(0);

   HWorld.Draw();
   HGroomedRatio_PT100->Draw("same point c");
   HGroomedRatio_PT120->Draw("same point c");
   HGroomedRatio_PT140->Draw("same point c");
   HGroomedRatio_PT160->Draw("same point c");
   HGroomedRatio_PT200->Draw("same point c");

   TLegend Legend(0.14, 0.45, 0.44, 0.85);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(HGroomedRatio_PT100, "PT = 100-120", "pl");
   Legend.AddEntry(HGroomedRatio_PT120, "PT = 100-120", "pl");
   Legend.AddEntry(HGroomedRatio_PT140, "PT = 100-120", "pl");
   Legend.AddEntry(HGroomedRatio_PT160, "PT = 100-200", "pl");
   Legend.AddEntry(HGroomedRatio_PT200, "PT = 200-300", "pl");
   Legend.Draw();

   C.SetLogy();

   C.SaveAs(Form("%s_GroomedRatioPerPT.png", OutputBase));
   C.SaveAs(Form("%s_GroomedRatioPerPT.C", OutputBase));
   C.SaveAs(Form("%s_GroomedRatioPerPT.eps", OutputBase));
   C.SaveAs(Form("%s_GroomedRatioPerPT.pdf", OutputBase));
   
   TH2D HWorld2("HWorld2", ";Depth; a.u.", 12, 0, 12, 100, 1e-4, 1000);
   HWorld2.SetStats(0);

   HWorld2.Draw();
   HDepth_PT100->Draw("same point");
   HDepth_PT120->Draw("same point");
   HDepth_PT140->Draw("same point");
   HDepth_PT160->Draw("same point");
   HDepth_PT200->Draw("same point");
   HDepth_PT100->Draw("same hist");
   HDepth_PT120->Draw("same hist");
   HDepth_PT140->Draw("same hist");
   HDepth_PT160->Draw("same hist");
   HDepth_PT200->Draw("same hist");

   TLegend Legend2(0.55, 0.55, 0.85, 0.85);
   Legend2.SetBorderSize(0);
   Legend2.SetFillStyle(0);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.AddEntry(HDepth_PT100, "PT = 100-120", "pl");
   Legend2.AddEntry(HDepth_PT120, "PT = 100-120", "pl");
   Legend2.AddEntry(HDepth_PT140, "PT = 100-120", "pl");
   Legend2.AddEntry(HDepth_PT160, "PT = 100-200", "pl");
   Legend2.AddEntry(HDepth_PT200, "PT = 200-300", "pl");
   Legend2.Draw();

   C.SaveAs(Form("%s_DepthPerPT.png", OutputBase));
   C.SaveAs(Form("%s_DepthPerPT.C", OutputBase));
   C.SaveAs(Form("%s_DepthPerPT.eps", OutputBase));
   C.SaveAs(Form("%s_DepthPerPT.pdf", OutputBase));

   TH2D HWorld3("HWorld3", ";Depth; a.u.", 12, 0, 12, 100, 0, 0.25);
   HWorld3.SetStats(0);

   HWorld3.Draw();
   HDepth_PT100->Draw("same point");
   HDepth_PT120->Draw("same point");
   HDepth_PT140->Draw("same point");
   HDepth_PT160->Draw("same point");
   HDepth_PT200->Draw("same point");
   HDepth_PT100->Draw("same hist");
   HDepth_PT120->Draw("same hist");
   HDepth_PT140->Draw("same hist");
   HDepth_PT160->Draw("same hist");
   HDepth_PT200->Draw("same hist");

   Legend2.Draw();

   C.SetLogy(false);

   C.SaveAs(Form("%s_DepthPerPTLinear.png", OutputBase));
   C.SaveAs(Form("%s_DepthPerPTLinear.C", OutputBase));
   C.SaveAs(Form("%s_DepthPerPTLinear.eps", OutputBase));
   C.SaveAs(Form("%s_DepthPerPTLinear.pdf", OutputBase));

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






