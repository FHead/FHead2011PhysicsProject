#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main();
void Export2DHistogram(TFile &File, string Name, string Base);

int main()
{
   SetThesisStyle();

   TFile File("ScaledResult/PP6Dijet.root");

   Export2DHistogram(File, "HJetPTComparison", "Plots/JetPTComparison");
   Export2DHistogram(File, "HSDMassComparison", "Plots/SDMassComparison");
   Export2DHistogram(File, "HRecoDRComparison", "Plots/RecoDRComparison");
   Export2DHistogram(File, "HSDMassJetPT", "Plots/SDMassJetPT");
   Export2DHistogram(File, "HNewSDMassNewJetPT", "Plots/NewSDMassNewJetPT");

   TH1D *HSDMass = (TH1D *)File.Get("HSDMass");
   TH1D *HNewSDMass = (TH1D *)File.Get("HNewSDMass");

   HSDMass->SetLineWidth(2);
   HNewSDMass->SetLineWidth(2);

   HSDMass->SetLineColor(kBlack);
   HNewSDMass->SetLineColor(kRed);

   HSDMass->SetStats(0);

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(HSDMass, "pp", "l");
   Legend.AddEntry(HNewSDMass, "pp smeared", "l");

   TCanvas Canvas;

   HSDMass->Draw();
   HNewSDMass->Draw("same");

   Legend.Draw();

   Canvas.SaveAs("Plots/SDMass.png");
   Canvas.SaveAs("Plots/SDMass.C");
   Canvas.SaveAs("Plots/SDMass.eps");
   Canvas.SaveAs("Plots/SDMass.pdf");

   return 0;
}

void Export2DHistogram(TFile &File, string Name, string Base)
{
   TH2D *H = (TH2D *)File.Get(Name.c_str());

   TCanvas C;

   H->SetStats(0);
   H->Draw("colz");

   C.SetLogz();

   C.SaveAs(Form("%s.png", Base.c_str()));
   C.SaveAs(Form("%s.C", Base.c_str()));
   C.SaveAs(Form("%s.eps", Base.c_str()));
   C.SaveAs(Form("%s.pdf", Base.c_str()));
}



