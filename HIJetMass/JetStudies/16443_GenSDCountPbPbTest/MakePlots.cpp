#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TTree.h"
#include "TFile.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " RootFile Tag" << endl;
      return -1;
   }

   PdfFileHelper PdfFile(string(argv[2]) + ".pdf");
   PdfFile.AddTextPage(argv[2]);

   TFile File(argv[1]);
   TTree *Tree = (TTree *)File.Get("T");

   PdfFile.AddTextPage("Basic CS plots");

   PdfFile.AddPlot2D(Tree, "Rho:Centrality", "", "colz",
      ";Centrality;Rho", 100, 0, 1, 100, 0, 500);
   PdfFile.AddPlot2D(Tree, "GenJetAllPT:GenJetPT", "", "colz",
      ";post-CS jet PT;pre-CS jet PT", 100, 0, 500, 100, 0, 500);
   PdfFile.AddPlot2D(Tree, "GenJetPT:PPJetPT", "PPJetPT > 10", "colz",
      ";pp jet PT;post-CS jet PT", 100, 0, 500, 100, 0, 500);
   PdfFile.AddPlot2D(Tree, "GenJetPT/PPJetPT:Centrality", "PPJetPT > 50", "colz",
      "Gen Jet PT > 50;Centrality;smeared PT / pp jet PT", 100, 0, 1, 100, 0.5, 1.5);
   PdfFile.AddPlotProfile(Tree, "GenJetPT/PPJetPT:Centrality", "PPJetPT > 50", "prof",
      "Gen Jet PT > 50;Centrality;smeared PT / pp jet PT", 100, 0, 1);
   PdfFile.AddPlotProfile(Tree, "GenJetPT/PPJetPT:Centrality", "PPJetPT > 120", "prof",
      "Gen Jet PT > 120;Centrality;smeared PT / pp jet PT", 100, 0, 1);

   PdfFile.AddTextPage("SD plots");

   PdfFile.AddPlot2D(Tree, "PPSDDR:Centrality", "PPSDDR > 0.0 && PPJetPT > 50", "colz",
      "PP Jet PT > 50;Centrality;DR (pp)", 100, 0, 1, 100, 0, 0.8);
   PdfFile.AddPlot2D(Tree, "GenSDDR:Centrality", "GenSDDR > 0.0 && GenJetPT > 50", "colz",
      "Smeared Jet PT > 50;Centrality;DR (smeared)", 100, 0, 1, 100, 0, 0.8);
   
   PdfFile.AddPlot2D(Tree, "GenSDDR:PPSDDR", "GenJetPT > 50 && PPJetPT > 50", "colz",
      "Smeared Jet PT > 50, pp Jet PT > 50;DR (pp);DR (smeared)", 100, 0, 0.8, 100, 0, 0.8);
   PdfFile.AddPlot2D(Tree, "GenSDDR:PPSDDR", "GenJetPT > 50 && PPJetPT > 50 && Centrality < 0.2", "colz",
      "Smeared Jet PT > 50, pp Jet PT > 50, 0-20%;DR (pp);DR (smeared)", 100, 0, 0.8, 100, 0, 0.8);
   PdfFile.AddPlot2D(Tree, "GenSDDR:PPSDDR", "GenJetPT > 50 && PPJetPT > 50 && Centrality > 0.5", "colz",
      "Smeared Jet PT > 50, pp Jet PT > 50, 50-100%;DR (pp);DR (smeared)", 100, 0, 0.8, 100, 0, 0.8);
   
   PdfFile.AddPlot2D(Tree, "PPSDMass/PPJetPT:Centrality", "PPSDDR > 0.0 && PPJetPT > 50", "colz",
      "PP Jet PT > 50;Centrality;Mass/PT (pp)", 100, 0, 1, 100, 0, 0.3);
   PdfFile.AddPlot2D(Tree, "GenSDMass/GenJetPT:Centrality", "GenSDDR > 0.0 && GenJetPT > 50", "colz",
      "Smeared Jet PT > 50;Centrality;Mass/PT (smeared)", 100, 0, 1, 100, 0, 0.3);
   
   PdfFile.AddPlot(Tree, "PPSDMass/PPJetPT", "PPSDDR > 0.1 && PPJetPT > 50 && Centrality < 0.1", "",
      "PP Jet PT > 50, DR > 0.1, 0-10%;Mass/PT (pp)", 100, 0, 0.3);
   PdfFile.AddPlot(Tree, "GenSDMass/GenJetPT", "GenSDDR > 0.1 && GenJetPT > 50 && Centrality < 0.1", "",
      "Smeared Jet PT > 50, DR > 0.1, 0-10%;Mass/PT (smear)", 100, 0, 0.3);
   
   PdfFile.AddPlot2D(Tree, "PPSDDR:Centrality", "PPSDDR > 0.0 && PPJetPT > 120", "colz",
      "PP Jet PT > 120;Centrality;DR (pp)", 100, 0, 1, 100, 0, 0.8);
   PdfFile.AddPlot2D(Tree, "GenSDDR:Centrality", "GenSDDR > 0.0 && GenJetPT > 120", "colz",
      "Smeared Jet PT > 120;Centrality;DR (smeared)", 100, 0, 1, 100, 0, 0.8);
   
   PdfFile.AddPlot2D(Tree, "GenSDDR:PPSDDR", "GenJetPT > 120 && PPJetPT > 120", "colz",
      "Smeared Jet PT > 120, pp Jet PT > 120;DR (pp);DR (smeared)", 100, 0, 0.8, 100, 0, 0.8);
   PdfFile.AddPlot2D(Tree, "GenSDDR:PPSDDR", "GenJetPT > 120 && PPJetPT > 120 && Centrality < 0.2", "colz",
      "Smeared Jet PT > 120, pp Jet PT > 120, 0-20%;DR (pp);DR (smeared)", 100, 0, 0.8, 100, 0, 0.8);
   PdfFile.AddPlot2D(Tree, "GenSDDR:PPSDDR", "GenJetPT > 120 && PPJetPT > 120 && Centrality > 0.5", "colz",
      "Smeared Jet PT > 120, pp Jet PT > 120, 120-100%;DR (pp);DR (smeared)", 100, 0, 0.8, 100, 0, 0.8);
   
   PdfFile.AddPlot2D(Tree, "PPSDMass/PPJetPT:Centrality", "PPSDDR > 0.0 && PPJetPT > 120", "colz",
      "PP Jet PT > 120;Centrality;Mass/PT (pp)", 100, 0, 1, 100, 0, 0.3);
   PdfFile.AddPlot2D(Tree, "GenSDMass/GenJetPT:Centrality", "GenSDDR > 0.0 && GenJetPT > 120", "colz",
      "Smeared Jet PT > 120;Centrality;Mass/PT (smeared)", 100, 0, 1, 100, 0, 0.3);
   
   PdfFile.AddPlot(Tree, "PPSDMass/PPJetPT", "PPSDDR > 0.1 && PPJetPT > 120 && Centrality < 0.1", "",
      "PP Jet PT > 120, DR > 0.1, 0-10%;Mass/PT (pp)", 100, 0, 0.3);
   PdfFile.AddPlot(Tree, "GenSDMass/GenJetPT", "GenSDDR > 0.1 && GenJetPT > 120 && Centrality < 0.1", "",
      "Smeared Jet PT > 120, DR > 0.1, 0-10%;Mass/PT (smear)", 100, 0, 0.3);

   PdfFile.AddTextPage("SD counting plots");
   
   PdfFile.AddPlot2D(Tree, "PPSDCount:Centrality", "PPSDDR > 0.0 && PPJetPT > 50", "colz",
      "PP Jet PT > 50;Centrality;n_{SD} (pp)", 100, 0, 1, 15, 0, 15);
   PdfFile.AddPlot2D(Tree, "GenSDCount:Centrality", "GenSDDR > 0.0 && GenJetPT > 50", "colz",
      "Smeared Jet PT > 50;Centrality;n_{SD} (smeared)", 100, 0, 1, 15, 0, 15);
   PdfFile.AddPlot2D(Tree, "GenSDCount:PPSDCount", "PPSDDR > 0.0 && PPJetPT > 50 && GenJetPT > 50 && GenSDDR > 0.0", "colz",
      "Both Jet PT > 50;n_{SD} (pp);n_{SD} (Smeared)", 15, 0, 15, 15, 0, 15);
   PdfFile.AddPlot2D(Tree, "GenSDCount:PPSDCount", "PPSDDR > 0.0 && PPJetPT > 50 && GenJetPT > 50 && GenSDDR > 0.0 && Centrality < 0.2", "colz",
      "Both Jet PT > 50, 0-20%;n_{SD} (pp);n_{SD} (Smeared)", 15, 0, 15, 15, 0, 15);
   PdfFile.AddPlot2D(Tree, "GenSDCount:PPSDCount", "PPSDDR > 0.0 && PPJetPT > 50 && GenJetPT > 50 && GenSDDR > 0.0 && Centrality > 0.5", "colz",
      "Both Jet PT > 50, 50-100%;n_{SD} (pp);n_{SD} (Smeared)", 15, 0, 15, 15, 0, 15);

   PdfFile.AddPlot2D(Tree, "PPSDCount:Centrality", "PPSDDR > 0.0 && PPJetPT > 120", "colz",
      "PP Jet PT > 120;Centrality;n_{SD} (pp)", 100, 0, 1, 15, 0, 15);
   PdfFile.AddPlot2D(Tree, "GenSDCount:Centrality", "GenSDDR > 0.0 && GenJetPT > 120", "colz",
      "Smeared Jet PT > 120;Centrality;n_{SD} (smeared)", 100, 0, 1, 15, 0, 15);
   PdfFile.AddPlot2D(Tree, "GenSDCount:PPSDCount", "PPSDDR > 0.0 && PPJetPT > 120 && GenJetPT > 120 && GenSDDR > 0.0", "colz",
      "Both Jet PT > 120;n_{SD} (pp);n_{SD} (Smeared)", 15, 0, 15, 15, 0, 15);
   PdfFile.AddPlot2D(Tree, "GenSDCount:PPSDCount", "PPSDDR > 0.0 && PPJetPT > 120 && GenJetPT > 120 && GenSDDR > 0.0 && Centrality < 0.2", "colz",
      "Both Jet PT > 120, 0-20%;n_{SD} (pp);n_{SD} (Smeared)", 15, 0, 15, 15, 0, 15);
   PdfFile.AddPlot2D(Tree, "GenSDCount:PPSDCount", "PPSDDR > 0.0 && PPJetPT > 120 && GenJetPT > 120 && GenSDDR > 0.0 && Centrality > 0.5", "colz",
      "Both Jet PT > 120, 50-100%;n_{SD} (pp);n_{SD} (Smeared)", 15, 0, 15, 15, 0, 15);

   PdfFile.AddTextPage("SD counting plots with nonzero kappa");
   
   PdfFile.AddPlot2D(Tree, "log(PPSDCKappa1)/log(10):Centrality", "PPSDDR > 0.0 && PPJetPT > 50 && PPSDCount > 0", "colz",
      "PP Jet PT > 50;Centrality;log_{10}(n^{(1.0)}_{SD}) (pp)", 100, 0, 1, 100, -2, 0.5);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa1)/log(10):Centrality", "GenSDDR > 0.0 && GenJetPT > 50 && GenSDCount > 0", "colz",
      "Smeared Jet PT > 50;Centrality;log_{10}(n^{(1.0)}_{SD}) (smeared)", 100, 0, 1, 100, -2, 0.5);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa1)/log(10):log(PPSDCKappa1)/log(10)", "PPSDDR > 0.0 && PPJetPT > 50 && GenJetPT > 50 && GenSDDR > 0.0 && PPSDCount > 0 && GenSDCount > 0", "colz",
      "Both Jet PT > 50;log_{10}(n^{(1.0)}_{SD}) (pp);log_{10}(n^{(1.0)}_{SD}) (Smeared)", 100, -2, 0.5, 100, -2, 0.5);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa1)/log(10):log(PPSDCKappa1)/log(10)", "PPSDDR > 0.0 && PPJetPT > 50 && GenJetPT > 50 && GenSDDR > 0.0 && Centrality < 0.2 && PPSDCount > 0 && GenSDCount > 0", "colz",
      "Both Jet PT > 50, 0-20%;log_{10}(n^{(1.0)}_{SD}) (pp);log_{10}(n^{(1.0)}_{SD}) (Smeared)", 100, -2, 0.5, 100, -2, 0.5);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa1)/log(10):log(PPSDCKappa1)/log(10)", "PPSDDR > 0.0 && PPJetPT > 50 && GenJetPT > 50 && GenSDDR > 0.0 && Centrality > 0.5 && PPSDCount > 0 && GenSDCount > 0", "colz",
      "Both Jet PT > 50, 50-100%;log_{10}(n^{(1.0)}_{SD}) (pp);log_{10}(n^{(1.0)}_{SD}) (Smeared)", 100, -2, 0.5, 100, -2, 0.5);

   PdfFile.AddPlot2D(Tree, "log(PPSDCKappa1)/log(10):Centrality", "PPSDDR > 0.0 && PPJetPT > 120 && PPSDCount > 0", "colz",
      "PP Jet PT > 120;Centrality;log_{10}(n^{(1.0)}_{SD}) (pp)", 100, 0, 1, 100, -2, 0.5);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa1)/log(10):Centrality", "GenSDDR > 0.0 && GenJetPT > 120 && GenSDCount > 0", "colz",
      "Smeared Jet PT > 120;Centrality;log_{10}(n^{(1.0)}_{SD}) (smeared)", 100, 0, 1, 100, -2, 0.5);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa1)/log(10):log(PPSDCKappa1)/log(10)", "PPSDDR > 0.0 && PPJetPT > 120 && GenJetPT > 120 && GenSDDR > 0.0 && PPSDCount > 0 && GenSDCount > 0", "colz",
      "Both Jet PT > 120;log_{10}(n^{(1.0)}_{SD}) (pp);log_{10}(n^{(1.0)}_{SD}) (Smeared)", 100, -2, 0.5, 100, -2, 0.5);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa1)/log(10):log(PPSDCKappa1)/log(10)", "PPSDDR > 0.0 && PPJetPT > 120 && GenJetPT > 120 && GenSDDR > 0.0 && Centrality < 0.2 && PPSDCount > 0 && GenSDCount > 0", "colz",
      "Both Jet PT > 120, 0-20%;log_{10}(n^{(1.0)}_{SD}) (pp);log_{10}(n^{(1.0)}_{SD}) (Smeared)", 100, -2, 0.5, 100, -2, 0.5);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa1)/log(10):log(PPSDCKappa1)/log(10)", "PPSDDR > 0.0 && PPJetPT > 120 && GenJetPT > 120 && GenSDDR > 0.0 && Centrality > 0.5 && PPSDCount > 0 && GenSDCount > 0", "colz",
      "Both Jet PT > 120, 50-100%;log_{10}(n^{(1.0)}_{SD}) (pp);log_{10}(n^{(1.0)}_{SD}) (Smeared)", 100, -2, 0.5, 100, -2, 0.5);
   
   PdfFile.AddPlot2D(Tree, "log(PPSDCKappa2)/log(10):Centrality", "PPSDDR > 0.0 && PPJetPT > 50 && PPSDCount > 0", "colz",
      "PP Jet PT > 50;Centrality;log_{10}(n^{(2.0)}_{SD}) (pp)", 100, 0, 1, 100, -2.5, 1.0);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa2)/log(10):Centrality", "GenSDDR > 0.0 && GenJetPT > 50 && GenSDCount > 0", "colz",
      "Smeared Jet PT > 50;Centrality;log_{10}(n^{(2.0)}_{SD}) (smeared)", 100, 0, 1, 100, -2.5, 1.0);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa2)/log(10):log(PPSDCKappa2)/log(10)", "PPSDDR > 0.0 && PPJetPT > 50 && GenJetPT > 50 && GenSDDR > 0.0 && PPSDCount > 0 && GenSDCount > 0", "colz",
      "Both Jet PT > 50;log_{10}(n^{(2.0)}_{SD}) (pp);log_{10}(n^{(2.0)}_{SD}) (Smeared)", 100, -2.5, 1.0, 100, -2.5, 1.0);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa2)/log(10):log(PPSDCKappa2)/log(10)", "PPSDDR > 0.0 && PPJetPT > 50 && GenJetPT > 50 && GenSDDR > 0.0 && Centrality < 0.2 && PPSDCount > 0 && GenSDCount > 0", "colz",
      "Both Jet PT > 50, 0-20%;log_{10}(n^{(2.0)}_{SD}) (pp);log_{10}(n^{(2.0)}_{SD}) (Smeared)", 100, -2.5, 1.0, 100, -2.5, 1.0);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa2)/log(10):log(PPSDCKappa2)/log(10)", "PPSDDR > 0.0 && PPJetPT > 50 && GenJetPT > 50 && GenSDDR > 0.0 && Centrality > 0.5 && PPSDCount > 0 && GenSDCount > 0", "colz",
      "Both Jet PT > 50, 50-100%;log_{10}(n^{(2.0)}_{SD}) (pp);log_{10}(n^{(2.0)}_{SD}) (Smeared)", 100, -2.5, 1.0, 100, -2.5, 1.0);
   
   PdfFile.AddPlot2D(Tree, "log(PPSDCKappa2)/log(10):Centrality", "PPSDDR > 0.0 && PPJetPT > 120 && PPSDCount > 0", "colz",
      "PP Jet PT > 120;Centrality;log_{10}(n^{(2.0)}_{SD}) (pp)", 100, 0, 1, 100, -2.5, 1.0);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa2)/log(10):Centrality", "GenSDDR > 0.0 && GenJetPT > 120 && GenSDCount > 0", "colz",
      "Smeared Jet PT > 120;Centrality;log_{10}(n^{(2.0)}_{SD}) (smeared)", 100, 0, 1, 100, -2.5, 1.0);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa2)/log(10):log(PPSDCKappa2)/log(10)", "PPSDDR > 0.0 && PPJetPT > 120 && GenJetPT > 120 && GenSDDR > 0.0 && PPSDCount > 0 && GenSDCount > 0", "colz",
      "Both Jet PT > 120;log_{10}(n^{(2.0)}_{SD}) (pp);log_{10}(n^{(2.0)}_{SD}) (Smeared)", 100, -2.5, 1.0, 100, -2.5, 1.0);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa2)/log(10):log(PPSDCKappa2)/log(10)", "PPSDDR > 0.0 && PPJetPT > 120 && GenJetPT > 120 && GenSDDR > 0.0 && Centrality < 0.2 && PPSDCount > 0 && GenSDCount > 0", "colz",
      "Both Jet PT > 120, 0-20%;log_{10}(n^{(2.0)}_{SD}) (pp);log_{10}(n^{(2.0)}_{SD}) (Smeared)", 100, -2.5, 1.0, 100, -2.5, 1.0);
   PdfFile.AddPlot2D(Tree, "log(GenSDCKappa2)/log(10):log(PPSDCKappa2)/log(10)", "PPSDDR > 0.0 && PPJetPT > 120 && GenJetPT > 120 && GenSDDR > 0.0 && Centrality > 0.5 && PPSDCount > 0 && GenSDCount > 0", "colz",
      "Both Jet PT > 120, 50-100%;log_{10}(n^{(2.0)}_{SD}) (pp);log_{10}(n^{(2.0)}_{SD}) (Smeared)", 100, -2.5, 1.0, 100, -2.5, 1.0);
   
   
   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}








