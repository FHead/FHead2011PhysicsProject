#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main();
void ExportHistogram2D(TFile &File, string Name, string Base);

int main()
{
   string Base = "Plots/";

   SetThesisStyle();

   TFile File("Output.root");

   ExportHistogram2D(File, "HGenMatchingQuality1",            Base + "GenMatchingQuality1");
   ExportHistogram2D(File, "HGenMatchingQuality2",            Base + "GenMatchingQuality2");
   ExportHistogram2D(File, "HRecoMatchingQuality1",           Base + "RecoMatchingQuality1");
   ExportHistogram2D(File, "HRecoMatchingQuality2",           Base + "RecoMatchingQuality2");
   ExportHistogram2D(File, "HGenMatchingDistance",            Base + "GenMatchingDistance");
   ExportHistogram2D(File, "HRecoMatchingDistance",           Base + "RecoMatchingDistance");
   ExportHistogram2D(File, "HGenMatchedPT",                   Base + "GenMatchedPT");
   ExportHistogram2D(File, "HRecoMatchedPT",                  Base + "RecoMatchedPT");
   ExportHistogram2D(File, "HSubJet1PTRatioVsSubJet2PTRatio", Base + "SubJet1PTRatioVsSubJet2PTRatio");
   ExportHistogram2D(File, "HRecoSubJet1PTVsTotalGenPT",      Base + "RecoSubJet1PTVsTotalGenPT");
   ExportHistogram2D(File, "HTotalRecoPTVsTotalGenPT",        Base + "TotalRecoPTVsTotalGenPT");
   ExportHistogram2D(File, "HRecoSubJet1XVsGenAverageX",      Base + "RecoSubJet1XVsGenAverageX");
   ExportHistogram2D(File, "HReco1OneUpXY",                   Base + "Reco1OneUpXY");
   ExportHistogram2D(File, "HReco2OneUpXY",                   Base + "Reco2OneUpXY");
   ExportHistogram2D(File, "HReco2OneUpDistanceVsCentrality", Base + "Reco2OneUpDistanceVsCentrality");
   ExportHistogram2D(File, "HReco2OneUpDistanceVsJetPT",      Base + "Reco2OneUpDistanceVsJetPT");
   ExportHistogram2D(File, "HReco2OneUpDistanceVsJetEta",     Base + "Reco2OneUpDistanceVsJetEta");
   ExportHistogram2D(File, "PGoodReco2OneUpVsCentrality",     Base + "GoodReco2OneUpVsCentrality");
   ExportHistogram2D(File, "PGoodReco2OneUpVsJetPT",          Base + "GoodReco2OneUpVsJetPT");
   ExportHistogram2D(File, "PGoodReco2OneUpVsJetEta",         Base + "GoodReco2OneUpVsJetEta");

   File.Close();

   return 0;
}

void ExportHistogram2D(TFile &File, string Name, string Base)
{
   TH2D *H = (TH2D *)File.Get(Name.c_str());

   H->SetStats(0);

   TCanvas C;

   H->Draw("colz");

   C.SaveAs((Base + ".png").c_str());
   C.SaveAs((Base + ".C").c_str());
   C.SaveAs((Base + ".eps").c_str());
   C.SaveAs((Base + ".pdf").c_str());
}



