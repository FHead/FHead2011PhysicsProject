#include <vector>
#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TFile.h"
#include "TLatex.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThumbStyle();
   vector<int> Colors = GetPrimaryColors();

   TFile File("Meow.root");

   TH1D *HBase = (TH1D *)File.Get("HD1OppositeBase");
   TH1D *HVariant = (TH1D *)File.Get("HD1OppositeVariant");

   HBase->SetMarkerColor(Colors[1]);
   HBase->SetMarkerSize(2.25);
   HBase->SetLineColor(Colors[1]);
   HBase->SetLineWidth(3);
   HVariant->SetMarkerColor(Colors[0]);
   HVariant->SetMarkerSize(2.0);
   HVariant->SetLineColor(Colors[0]);
   HVariant->SetLineWidth(3);

   HBase->Scale(0.001);
   HVariant->Scale(HBase->Integral() / HVariant->Integral());

   TCanvas Canvas;

   TH2D HWorld("HWorld",
      ";D^{0} Candidate Mass [GeV/c^{2}];Entries / (5 MeV/c^{2})",
      100, 1.75, 2.0, 100, 13.1, 18.9);
   HWorld.SetStats(0);

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
   Latex.DrawLatex(0.25, 0.25, "D^{0} p > 1 GeV/c");

   Canvas.SaveAs("DMass.pdf");
   Canvas.SaveAs("DMass.C");

   File.Close();

   return 0;
}




