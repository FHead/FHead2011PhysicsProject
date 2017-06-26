#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " PU" << endl;
      return -1;
   }

   SetThesisStyle();
   
   string PU = argv[1];

   PdfFileHelper PdfFile("QuickViewGen_PU" + PU + ".pdf");
   PdfFile.AddTextPage("PU " + PU + " jet supplementary plots");

   vector<string> Texts(20);
   Texts[0] = "Goal: understanding the efficiency weirdness";
   Texts[1] = "";
   Texts[2] = "In TTbar sample find leading gen jet  with |eta| < 3";
   Texts[3] = "Find closest jet in #DeltaR without PT requirements";
   Texts[4] = "Focus on high PT gen jets with PT > 150, |#eta| < 1.5,";
   Texts[5] = "   and #DeltaR > 0.5";
   Texts[6] = "";
   Texts[7] = "";
   Texts[8] = "";
   Texts[9] = "";
   Texts[10] = "";
   Texts[11] = "";
   PdfFile.AddTextPage(Texts);

   TFile File(("GenResult/Combined/TTBar" + PU + "PU.root").c_str());

   TTree *T = (TTree *)File.Get("T");
   T->SetAlias("DEta", "(GenJetEta-JetEta)");
   T->SetAlias("DPhiRaw", "(GenJetPhi-JetPhi)");
   T->SetAlias("DPhi", "(DPhiRaw+2*TMath::Pi()*(DPhiRaw<-TMath::Pi())-2*TMath::Pi()*(DPhiRaw>TMath::Pi()))");

   PdfFile.AddTextPage("Some reference plots without selection");
   PdfFile.AddPlot(T, "BestDR", "BestDR > 0", "",
      "#DeltaR for all events;Closest Jet DR;", 100, 0, 5, true);
   PdfFile.AddPlotProfile(T, "BestDR:GenJetPT", "BestDR > 0", "prof",
      "Average #DeltaR;GenJet PT;<Closest Jet #DeltaR>", 50, 0, 500);
   PdfFile.AddPlotProfile(T, "BestDR > 0.5:GenJetPT", "BestDR > 0", "prof",
      "Percentage with #DeltaR above 0.5;GenJet PT;p(#DeltaR > 0.5)", 50, 0, 500);
   PdfFile.AddPlot2D(T, "JetPT/GenJetPT:GenJetPT", "BestDR > 0", "colz",
      "Resolution;GenJet PT;Jet PT / GenJet PT", 100, 0, 400, 100, 0, 3);
   
   PdfFile.AddTextPage("High PT central GenJet events");
   PdfFile.AddPlot(T, "BestDR", "GenJetPT > 150 && abs(GenJetEta) < 1.5", "",
      "GenJet PT > 150, |#eta| < 1.5;Closest Jet #DeltaR;", 100, 0, 1.5);
   PdfFile.AddPlot2D(T, "JetPT/GenJetPT:BestDR", "GenJetPT > 150 && abs(GenJetEta) < 1.5", "",
      "GenJet PT > 150, |#eta| < 1.5;Closest Jet #DeltaR;Jet PT / GenJet PT", 100, 0, 1.5, 100, 0, 2);
   PdfFile.AddPlot2D(T, "JetPT/GenJetPT:BestDR", "GenJetPT > 150 && abs(GenJetEta) < 1.5", "colz",
      "GenJet PT > 150, |#eta| < 1.5;Closest Jet #DeltaR;Jet PT / GenJet PT", 100, 0, 1.5, 100, 0, 2);
   PdfFile.AddPlot2D(T, "JetPT:GenJetPT", "GenJetPT > 150 && abs(GenJetEta) < 1.5 && BestDR > 0.5", "",
      "GenJet PT > 150, |#eta| < 1.5, #DeltaR > 0.5;GenJet PT;Closest Jet PT", 100, 100, 500, 100, 0, 500);
   PdfFile.AddPlot2D(T, "JetPT:GenJetPT", "GenJetPT > 150 && abs(GenJetEta) < 1.5 && BestDR < 0.3", "",
      "GenJet PT > 150, |#eta| < 1.5, #DeltaR < 0.3;GenJet PT;Closest Jet PT", 100, 100, 500, 100, 0, 500);
   PdfFile.AddPlot2D(T, "GenJetPhi:GenJetEta", "GenJetPT > 150 && abs(GenJetEta) < 1.5 && BestDR > 0.5", "",
      "GenJet PT > 150, |#eta| < 1.5, #DeltaR > 0.5;GenJet #eta;GenJet #phi", 100, -5, 5, 100, -M_PI, M_PI);
   PdfFile.AddPlot2D(T, "JetPhi:JetEta", "GenJetPT > 150 && abs(GenJetEta) < 1.5 && BestDR > 0.5", "",
      "GenJet PT > 150, |#eta| < 1.5, #DeltaR > 0.5;Closest jet #eta;Closest jet #phi", 100, -5, 5, 100, -M_PI, M_PI);
   PdfFile.AddPlot2D(T, "DPhi:DEta", "GenJetPT > 150 && abs(GenJetEta) < 1.5 && BestDR > 0.5", "",
      "GenJet PT > 150, |#eta| < 1.5, #DeltaR > 0.5;#Delta#eta (GenJet - Jet);#Delta#phi (GenJet - Jet)", 100, -2, 2, 100, -2, 2);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}









