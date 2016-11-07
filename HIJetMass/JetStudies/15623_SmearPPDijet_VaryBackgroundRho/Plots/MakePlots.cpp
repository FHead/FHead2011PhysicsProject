#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main(int argc, char *argv[]);
void Export2DHistogram(TFile &File, string Name, string Base);

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " RootFile OutputBase" << endl;
      return -1;
   }

   string FileName = argv[1];
   string OutputBase = argv[2];

   SetThesisStyle();

   TFile File(FileName.c_str());

   Export2DHistogram(File, "HJetPTComparison",   OutputBase + "JetPTComparison");
   Export2DHistogram(File, "HSDMassComparison",  OutputBase + "SDMassComparison");
   Export2DHistogram(File, "HRecoDRComparison",  OutputBase + "RecoDRComparison");
   Export2DHistogram(File, "HSDMassJetPT",       OutputBase + "SDMassJetPT");
   Export2DHistogram(File, "HNewSDMassNewJetPT", OutputBase + "NewSDMassNewJetPT");

   TH1D *HSDMass = (TH1D *)File.Get("HSDMass");
   TH1D *HNewSDMass = (TH1D *)File.Get("HNewSDMass");
   TH1D *HNewSDMassGood = (TH1D *)File.Get("HNewSDMassGoodDR");
   TH1D *HNewSDMassBad = (TH1D *)File.Get("HNewSDMassBadDR");

   HSDMass->SetLineWidth(2);
   HNewSDMass->SetLineWidth(2);
   if(HNewSDMassGood != NULL)
      HNewSDMassGood->SetLineWidth(2);
   if(HNewSDMassBad != NULL)
      HNewSDMassBad->SetLineWidth(2);

   HSDMass->SetLineColor(kBlack);
   HNewSDMass->SetLineColor(kRed);
   if(HNewSDMassGood != NULL)
      HNewSDMassGood->SetLineColor(kGreen - 3);
   if(HNewSDMassBad != NULL)
      HNewSDMassBad->SetLineColor(kCyan + 3);

   HSDMass->SetStats(0);
   HNewSDMass->SetStats(0);

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

   Canvas.SaveAs(Form("%sSDMass.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%sSDMass.C"  , OutputBase.c_str()));
   Canvas.SaveAs(Form("%sSDMass.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%sSDMass.pdf", OutputBase.c_str()));

   if(HNewSDMassGood != NULL && HNewSDMassBad != NULL)
   {
      TLegend Legend2(0.3, 0.8, 0.6, 0.6);
      Legend2.SetBorderSize(0);
      Legend2.SetFillStyle(0);
      Legend2.SetTextFont(42);
      Legend2.SetTextSize(0.035);
      Legend2.AddEntry(HNewSDMass, "pp smeared", "l");
      Legend2.AddEntry(HNewSDMassGood, "pp smeared, DR (new) - DR (old) < 0.05", "l");
      Legend2.AddEntry(HNewSDMassBad, "pp smeared, DR (new) - DR (old) > 0.05", "l");

      HNewSDMass->Draw();
      HNewSDMassGood->Draw("same");
      HNewSDMassBad->Draw("same");

      Legend2.Draw();

      Canvas.SaveAs(Form("%sSDMassGoodBad.png", OutputBase.c_str()));
      Canvas.SaveAs(Form("%sSDMassGoodBad.C"  , OutputBase.c_str()));
      Canvas.SaveAs(Form("%sSDMassGoodBad.eps", OutputBase.c_str()));
      Canvas.SaveAs(Form("%sSDMassGoodBad.pdf", OutputBase.c_str()));
   }

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



