#include <vector>
#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TFile.h"
#include "TLatex.h"

#include "SetStyle.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   SetThumbStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputBase    = CL.Get("Output");
   string BaseName      = CL.Get("Base");
   string VariantName   = CL.Get("Variant");
   string XTitle        = CL.Get("XTitle", "D^{0} Candidate Mass [GeV/c^{2}]");
   string YTitle        = CL.Get("YTitle", "Entries / (5 MeV/c^{2})");
   double XMin          = CL.GetDouble("XMin");
   double XMax          = CL.GetDouble("XMax");
   double YMin          = CL.GetDouble("YMin");
   double YMax          = CL.GetDouble("YMax");
   string ExtraInfo     = CL.Get("ExtraInfo", "");
   int Shift            = CL.GetInt("Shift", 0);

   TFile File(InputFileName.c_str());

   TH1D *HBase = (TH1D *)File.Get(BaseName.c_str());
   TH1D *HVariant = (TH1D *)File.Get(VariantName.c_str());

   HBase->SetMarkerColor(Colors[1]);
   HBase->SetMarkerSize(2.25);
   HBase->SetLineColor(Colors[1]);
   HBase->SetLineWidth(3);
   HVariant->SetMarkerColor(Colors[0]);
   HVariant->SetMarkerSize(2.0);
   HVariant->SetLineColor(Colors[0]);
   HVariant->SetLineWidth(3);

   for(int i = 0; i < Shift; i++)
      HBase->Scale(0.1);
   HVariant->Scale(HBase->Integral() / HVariant->Integral());

   TCanvas Canvas;

   TH2D HWorld("HWorld", "", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);
   HWorld.SetTitle("");
   HWorld.GetXaxis()->SetTitle(XTitle.c_str());
   HWorld.GetYaxis()->SetTitle(YTitle.c_str());

   HWorld.Draw("axis");
   HBase->Draw("same");
   HVariant->Draw("same");

   TLegend Legend(0.20, 0.85, 0.60, 0.70);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.05);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(HBase, "ALEPH e^{+}e^{-} archived data");
   Legend.AddEntry(HVariant, "Generative Networks");
   Legend.Draw();

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.05);
   Latex.SetTextAlign(12);
   Latex.SetNDC();
   Latex.DrawLatex(0.25, 0.25, ExtraInfo.c_str());
   if(Shift > 0)
      Latex.DrawLatex(0.12, 0.93, Form("x10^{%d}", Shift));

   Canvas.SaveAs(Form("%s.pdf", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.C", OutputBase.c_str()));

   File.Close();

   return 0;
}




