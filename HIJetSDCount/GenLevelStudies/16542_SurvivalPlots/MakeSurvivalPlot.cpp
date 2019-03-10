#include <cmath>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputTag" << endl;
      return -1;
   }

   SetThesisStyle();

   PdfFileHelper PdfFile(string("PrettyPlots_") + argv[2] + ".pdf");
   PdfFile.AddTextPage("CS Survival Studies");

   TFile File(argv[1]);

   TTree *Tree = (TTree *)File.Get("jetTree");

   PdfFile.AddPlot(Tree, "sigJetPt", "abs(sigJetEta) < 1.3", "",
      "|#eta^{pp jet}| < 1.3;p_{T}^{pp jet};", 100, 0, 200);
   
   PdfFile.AddPlot(Tree, "csRho", "", "",
      ";#rho;", 100, 0, 400);
   PdfFile.AddPlot2D(Tree, "csJetPhi:csJetEta", "csJetPt > 100", "colz",
      ";#eta^{jet};#phi^{jet}", 100, -2, 2, 100, 0, 2 * M_PI);
   PdfFile.AddPlot2D(Tree, "csJetEta:csJetPt", "", "colz",
      ";p_{T}^{jet};#eta^{jet}", 100, 0, 200, 100, -2, 2);
   PdfFile.AddPlot(Tree, "csJetPt", "abs(csJetEta) < 1.3", "",
      "|#eta^{jet}| < 1.3;p_{T}^{jet};", 100, 0, 200);
   
   PdfFile.AddPlot(Tree, "csJetSDPt/csJetPt", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, (0.1, 0.0);p_{T}^{SD jet} / p_{T}^{jet};", 100, 0.5, 1.001);
   PdfFile.AddPlot(Tree, "csJetSDPt/csJetPt", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, (0.1, 0.0);p_{T}^{SD jet} / p_{T}^{jet};", 100, 0.5, 1.001, true);
   PdfFile.AddPlot(Tree, "csJetSD2Pt/csJetPt", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, (0.5, 1.5);p_{T}^{SD jet} / p_{T}^{jet};", 100, 0.5, 1.001);
   PdfFile.AddPlot(Tree, "csJetSD2Pt/csJetPt", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, (0.5, 1.5);p_{T}^{SD jet} / p_{T}^{jet};", 100, 0.5, 1.001, true);
   
   PdfFile.AddPlot(Tree, "csJetSDdr12", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, (0.1, 0.0);#DeltaR_{12}^{SD jet};", 100, 0.0, 0.5);
   PdfFile.AddPlot(Tree, "csJetSDM/csJetPt", "abs(csJetEta) < 1.3 && csJetPt > 100 && csJetSDdr12 > 0.1", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, #DeltaR_{12}^{SD jet} > 0.1, (0.1, 0.0);M_{g}^{jet} / p_{T}^{jet};", 100, 0.0, 0.3);
   PdfFile.AddPlot(Tree, "csJetSD2dr12", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, (0.5, 1.5);#DeltaR_{12}^{SD jet};", 100, 0.0, 0.5);
   PdfFile.AddPlot(Tree, "csJetSD2M/csJetPt", "abs(csJetEta) < 1.3 && csJetPt > 100 && csJetSD2dr12 > 0.1", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, #DeltaR_{12}^{SD jet} > 0.1, (0.5, 1.5);M_{g}^{jet} / p_{T}^{jet};", 100, 0.0, 0.3);
   
   PdfFile.AddPlot(Tree, "csSurvivedJetPt/csJetPt", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3;p_{T}^{survived} / p_{T}^{jet};", 100, 0.0, 1.0);
   PdfFile.AddPlot(Tree, "csSurvivedJetPt/csJetPt", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3;p_{T}^{survived} / p_{T}^{jet};", 100, 0.0, 1.0, true);
   PdfFile.AddPlot2D(Tree, "csSurvivedJetPt/csJetPt:sigJetPt", "abs(csJetEta) < 1.3", "colz",
      "|#eta^{jet}| < 1.3;p_{T}^{gen jet};p_{T}^{survived} / p_{T}^{jet}", 50, 0.0, 300.0, 100, 0.0, 1.0, false, true);
   PdfFile.AddPlotProfile(Tree, "csSurvivedJetPt/csJetPt:sigJetPt", "abs(csJetEta) < 1.3", "prof",
      "|#eta^{jet}| < 1.3;p_{T}^{gen jet};<p_{T}^{survived} / p_{T}^{jet}>", 50, 0.0, 300.0);

   PdfFile.AddPlot(Tree, "csJetM/csJetPt", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3;M^{jet} / p_{T}^{jet};", 100, 0.0, 0.3);
   PdfFile.AddPlot(Tree, "csSurvivedJetM/csJetPt", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3;M^{survived} / p_{T}^{jet};", 100, 0.0, 0.3);
   PdfFile.AddPlot(Tree, "csSurvivedJetM/csJetM", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3;M^{survived} / M^{jet};", 100, 0.0, 1.0);
   PdfFile.AddPlot(Tree, "csSurvivedJetM/csJetSDM", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, (0.1, 0.0);M^{survived} / M_{g}^{jet};", 100, 0.0, 2.5);
   PdfFile.AddPlot(Tree, "csSurvivedJetM/csJetSDM", "abs(csJetEta) < 1.3 && csJetPt > 100 && csJetSDdr12 > 0.1", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, #DeltaR_{12}^{SD jet} > 0.1, (0.1, 0.0);M^{survived} / M_{g}^{jet};", 100, 0.0, 2.5);
   PdfFile.AddPlot(Tree, "csSurvivedJetM/csJetSD2M", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, (0.5, 1.5);M^{survived} / M_{g}^{jet};", 100, 0.0, 2.5);
   PdfFile.AddPlot(Tree, "csSurvivedJetM/csJetSD2M", "abs(csJetEta) < 1.3 && csJetPt > 100 && csJetSD2dr12 > 0.1", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, #DeltaR_{12}^{SD jet} > 0.1, (0.5, 1.5);M^{survived} / M_{g}^{jet};", 100, 0.0, 2.5);
   PdfFile.AddPlot2D(Tree, "csSurvivedJetM/csJetM:sigJetPt", "abs(csJetEta) < 1.3", "colz",
      "|#eta^{jet}| < 1.3;p_{T}^{gen jet};M^{survived} / M^{jet}", 50, 0.0, 300.0, 100, 0.0, 1.0, false, true);
   PdfFile.AddPlotProfile(Tree, "csSurvivedJetM/csJetM:sigJetPt", "abs(csJetEta) < 1.3", "prof",
      "|#eta^{jet}| < 1.3;p_{T}^{gen jet};<M^{survived} / M^{jet}>", 50, 0.0, 300.0);

   PdfFile.AddPlot2D(Tree, "csSurvivedJetPt/csJetPt:csSurvivedJetM/csJetM", "abs(csJetEta) < 1.3 && csJetPt > 100", "colz",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3;p_{T}^{survived} / p_{T}^{jet};M^{survived} / M^{jet};", 100, 0.0, 1.0, 100, 0.5, 1.0);
   
   PdfFile.AddPlot(Tree, "csSurvivedSDJetPt/csJetSDPt", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, (0.1, 0.0);p_{T}^{SD survived} / p_{T}^{SD jet};", 100, 0.0, 1.001);
   PdfFile.AddPlot(Tree, "csSurvivedSDJetPt/csJetSDPt", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, (0.1, 0.0);p_{T}^{SD survived} / p_{T}^{SD jet};", 100, 0.0, 1.001, true);
   PdfFile.AddPlot2D(Tree, "csSurvivedSDJetPt/csJetSDPt:sigJetPt", "abs(csJetEta) < 1.3", "colz",
      "|#eta^{jet}| < 1.3, (0.1, 0.0);p_{T}^{gen jet};p_{T}^{SD survived} / p_{T}^{SD jet}", 50, 0.0, 300.0, 100, 0.0, 1.0, false, true);
   PdfFile.AddPlotProfile(Tree, "csSurvivedSDJetPt/csJetSDPt:sigJetPt", "abs(csJetEta) < 1.3", "prof",
      "|#eta^{jet}| < 1.3, (0.1, 0.0);p_{T}^{gen jet};<p_{T}^{SD survived} / p_{T}^{SD jet}>", 50, 0.0, 300.0);
   
   PdfFile.AddPlot(Tree, "csSurvivedSDJetM/csJetSDM", "abs(csJetEta) < 1.3 && csJetPt > 100 && csJetSDdr12 > 0.1", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, #DeltaR_{12}^{SD jet} > 0.1, (0.1, 0.0);M^{SD survived} / M^{SD jet};", 100, 0.0, 1.001);
   PdfFile.AddPlot(Tree, "csSurvivedSDJetM/csJetSDM", "abs(csJetEta) < 1.3 && csJetPt > 100 && csJetSDdr12 > 0.1", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, #DeltaR_{12}^{SD jet} > 0.1, (0.1, 0.0);M^{SD survived} / M^{SD jet};", 100, 0.0, 1.001, true);
   PdfFile.AddPlot2D(Tree, "csSurvivedSDJetM/csJetSDM:sigJetPt", "abs(csJetEta) < 1.3", "colz",
      "|#eta^{jet}| < 1.3, (0.1, 0.0);p_{T}^{gen jet};M^{SD survived} / M^{SD jet}", 50, 0.0, 300.0, 100, 0.0, 1.0, false, true);
   PdfFile.AddPlotProfile(Tree, "csSurvivedSDJetM/csJetSDM:sigJetPt", "abs(csJetEta) < 1.3", "prof",
      "|#eta^{jet}| < 1.3, (0.1, 0.0);p_{T}^{gen jet};<M^{SD survived} / M^{SD jet}>", 50, 0.0, 300.0);
   
   PdfFile.AddPlot(Tree, "csSurvivedSD2JetPt/csJetSD2Pt", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, (0.5, 1.5);p_{T}^{SD survived} / p_{T}^{SD jet};", 100, 0.0, 1.001);
   PdfFile.AddPlot(Tree, "csSurvivedSD2JetPt/csJetSD2Pt", "abs(csJetEta) < 1.3 && csJetPt > 100", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, (0.5, 1.5);p_{T}^{SD survived} / p_{T}^{SD jet};", 100, 0.0, 1.001, true);
   PdfFile.AddPlot2D(Tree, "csSurvivedSD2JetPt/csJetSD2Pt:sigJetPt", "abs(csJetEta) < 1.3", "colz",
      "|#eta^{jet}| < 1.3, (0.5, 1.5);p_{T}^{gen jet};p_{T}^{SD survived} / p_{T}^{SD jet}", 50, 0.0, 300.0, 100, 0.0, 1.0, false, true);
   PdfFile.AddPlotProfile(Tree, "csSurvivedSD2JetPt/csJetSD2Pt:sigJetPt", "abs(csJetEta) < 1.3", "prof",
      "|#eta^{jet}| < 1.3, (0.5, 1.5);p_{T}^{gen jet};<p_{T}^{SD survived} / p_{T}^{SD jet}>", 50, 0.0, 300.0);
   
   PdfFile.AddPlot(Tree, "csSurvivedSD2JetM/csJetSD2M", "abs(csJetEta) < 1.3 && csJetPt > 100 && csJetSD2dr12 > 0.1", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, #DeltaR_{12}^{SD jet} > 0.1, (0.5, 1.5);M^{SD survived} / M^{SD jet};", 100, 0.0, 1.001);
   PdfFile.AddPlot(Tree, "csSurvivedSD2JetM/csJetSD2M", "abs(csJetEta) < 1.3 && csJetPt > 100 && csJetSD2dr12 > 0.1", "",
      "p_{T}^{jet} > 100, |#eta^{jet}| < 1.3, #DeltaR_{12}^{SD jet} > 0.1, (0.5, 1.5);M^{SD survived} / M^{SD jet};", 100, 0.0, 1.001, true);
   PdfFile.AddPlot2D(Tree, "csSurvivedSD2JetM/csJetSD2M:sigJetPt", "abs(csJetEta) < 1.3", "colz",
      "|#eta^{jet}| < 1.3, (0.5, 1.5);p_{T}^{gen jet};M^{SD survived} / M^{SD jet}", 50, 0.0, 300.0, 100, 0.0, 1.0, false, true);
   PdfFile.AddPlotProfile(Tree, "csSurvivedSD2JetM/csJetSD2M:sigJetPt", "abs(csJetEta) < 1.3", "prof",
      "|#eta^{jet}| < 1.3, (0.5, 1.5);p_{T}^{gen jet};<M^{SD survived} / M^{SD jet}>", 50, 0.0, 300.0);
   
   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}



