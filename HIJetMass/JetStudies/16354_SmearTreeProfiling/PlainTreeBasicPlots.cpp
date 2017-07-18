#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("PlainPlots.pdf");
   PdfFile.AddTextPage("Basic Plots");

   TFile File("../../Samples/PlainTree/16353/AA6DijetCymbal.root");

   TTree *Tree = (TTree *)File.Get("T");

   PdfFile.AddPlot(Tree, "Centrality", "MCWeight", "", ";Centrality;", 100, 0.0, 1.0);
   PdfFile.AddPlot(Tree, "PTHat", "MCWeight", "", ";PTHat;", 750, 0, 750, true);

   PdfFile.AddPlot(Tree, "MatchPT", "MCWeight * (abs(JetCSEta) < 1.3)", "", ";Raw PT;", 250, 0, 1000, true);
   PdfFile.AddPlot(Tree, "JetCSEta", "MCWeight * (abs(JetCSEta) < 1.3 && MatchPT > 100)", "", "Raw PT > 100;Eta;", 50, -1.3, 1.3);
   PdfFile.AddPlot(Tree, "MatchDR", "MCWeight * (abs(JetCSEta) < 1.3 && MatchPT > 100)", "", "Raw PT > 100;Match DR;", 100, 0, 1, true);

   PdfFile.AddPlot(Tree, "MatchDR", "MCWeight * (abs(JetCSEta) < 1.3 && MatchPT > 100 && Centrality > 0.0 && Centrality < 0.2)", "", "Raw PT > 100, Centrality = 0-20%;Match DR;", 100, 0, 1, true);
   PdfFile.AddPlot(Tree, "MatchDR", "MCWeight * (abs(JetCSEta) < 1.3 && MatchPT > 100 && Centrality > 0.2 && Centrality < 0.4)", "", "Raw PT > 100, Centrality = 20-40%;Match DR;", 100, 0, 1, true);
   PdfFile.AddPlot(Tree, "MatchDR", "MCWeight * (abs(JetCSEta) < 1.3 && MatchPT > 100 && Centrality > 0.4 && Centrality < 0.6)", "", "Raw PT > 100, Centrality = 40-60%;Match DR;", 100, 0, 1, true);
   PdfFile.AddPlot(Tree, "MatchDR", "MCWeight * (abs(JetCSEta) < 1.3 && MatchPT > 100 && Centrality > 0.6 && Centrality < 0.8)", "", "Raw PT > 100, Centrality = 60-80%;Match DR;", 100, 0, 1, true);
   PdfFile.AddPlot(Tree, "MatchDR", "MCWeight * (abs(JetCSEta) < 1.3 && MatchPT > 100 && Centrality > 0.8 && Centrality < 1.0)", "", "Raw PT > 100, Centrality = 80-100%;Match DR;", 100, 0, 1, true);

   PdfFile.AddPlot(Tree, "SubJetDR0", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.0 && Centrality < 0.2 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 0-20%;DR (SD0);", 100, 0.0, 4.0, true);
   PdfFile.AddPlot(Tree, "SubJetDR0", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.0 && Centrality < 0.2 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 0-20%;DR (SD0);", 100, 0.0, 0.5, false);
   PdfFile.AddPlot(Tree, "SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.0 && Centrality < 0.2 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 0-20%;Mass/PT;", 100, 0.0, 200.0, true);
   PdfFile.AddPlot(Tree, "SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.0 && Centrality < 0.2 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 0-20%;Mass/PT;", 100, 0.0, 0.3);
   PdfFile.AddPlot2D(Tree, "SubJetDR0:SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.0 && Centrality < 0.2 && abs(JetCSEta) < 1.3)", "colz", "Raw PT > 100, Centrality = 0-20%;Mass/PT;DR", 100, 0.0, 200.0, 100, 0.0, 4.0, false, true);
   PdfFile.AddPlot2D(Tree, "SubJetDR0:SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.0 && Centrality < 0.2 && abs(JetCSEta) < 1.3)", "colz", "Raw PT > 100, Centrality = 0-20%;Mass/PT;DR", 100, 0.0, 0.5, 100, 0.0, 0.7, false, true);

   PdfFile.AddPlot(Tree, "SubJetDR0", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.2 && Centrality < 0.4 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 20-40%;DR (SD0);", 100, 0.0, 4.0, true);
   PdfFile.AddPlot(Tree, "SubJetDR0", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.2 && Centrality < 0.4 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 20-40%;DR (SD0);", 100, 0.0, 0.5, false);
   PdfFile.AddPlot(Tree, "SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.2 && Centrality < 0.4 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 20-40%;Mass/PT;", 100, 0.0, 200.0, true);
   PdfFile.AddPlot(Tree, "SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.2 && Centrality < 0.4 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 20-40%;Mass/PT;", 100, 0.0, 0.3);
   PdfFile.AddPlot2D(Tree, "SubJetDR0:SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.2 && Centrality < 0.4 && abs(JetCSEta) < 1.3)", "colz", "Raw PT > 100, Centrality = 20-40%;Mass/PT;DR", 100, 0.0, 200.0, 100, 0.0, 4.0, false, true);
   PdfFile.AddPlot2D(Tree, "SubJetDR0:SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.2 && Centrality < 0.4 && abs(JetCSEta) < 1.3)", "colz", "Raw PT > 100, Centrality = 20-40%;Mass/PT;DR", 100, 0.0, 0.5, 100, 0.0, 0.7, false, true);

   PdfFile.AddPlot(Tree, "SubJetDR0", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.4 && Centrality < 0.6 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 40-60%;DR (SD0);", 100, 0.0, 4.0, true);
   PdfFile.AddPlot(Tree, "SubJetDR0", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.4 && Centrality < 0.6 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 40-60%;DR (SD0);", 100, 0.0, 0.5, false);
   PdfFile.AddPlot(Tree, "SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.4 && Centrality < 0.6 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 40-60%;Mass/PT;", 100, 0.0, 200.0, true);
   PdfFile.AddPlot(Tree, "SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.4 && Centrality < 0.6 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 40-60%;Mass/PT;", 100, 0.0, 0.3);
   PdfFile.AddPlot2D(Tree, "SubJetDR0:SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.4 && Centrality < 0.6 && abs(JetCSEta) < 1.3)", "colz", "Raw PT > 100, Centrality = 40-60%;Mass/PT;DR", 100, 0.0, 200.0, 100, 0.0, 4.0, false, true);
   PdfFile.AddPlot2D(Tree, "SubJetDR0:SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.4 && Centrality < 0.6 && abs(JetCSEta) < 1.3)", "colz", "Raw PT > 100, Centrality = 40-60%;Mass/PT;DR", 100, 0.0, 0.5, 100, 0.0, 0.7, false, true);

   PdfFile.AddPlot(Tree, "SubJetDR0", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.6 && Centrality < 0.8 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 60-80%;DR (SD0);", 100, 0.0, 4.0, true);
   PdfFile.AddPlot(Tree, "SubJetDR0", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.6 && Centrality < 0.8 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 60-80%;DR (SD0);", 100, 0.0, 0.5, false);
   PdfFile.AddPlot(Tree, "SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.6 && Centrality < 0.8 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 60-80%;Mass/PT;", 100, 0.0, 200.0, true);
   PdfFile.AddPlot(Tree, "SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.6 && Centrality < 0.8 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 60-80%;Mass/PT;", 100, 0.0, 0.3);
   PdfFile.AddPlot2D(Tree, "SubJetDR0:SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.6 && Centrality < 0.8 && abs(JetCSEta) < 1.3)", "colz", "Raw PT > 100, Centrality = 60-80%;Mass/PT;DR", 100, 0.0, 200.0, 100, 0.0, 4.0, false, true);
   PdfFile.AddPlot2D(Tree, "SubJetDR0:SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.6 && Centrality < 0.8 && abs(JetCSEta) < 1.3)", "colz", "Raw PT > 100, Centrality = 60-80%;Mass/PT;DR", 100, 0.0, 0.5, 100, 0.0, 0.7, false, true);

   PdfFile.AddPlot(Tree, "SubJetDR0", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.8 && Centrality < 1.0 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 80-100%;DR (SD0);", 100, 0.0, 4.0, true);
   PdfFile.AddPlot(Tree, "SubJetDR0", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.8 && Centrality < 1.0 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 80-100%;DR (SD0);", 100, 0.0, 0.5, false);
   PdfFile.AddPlot(Tree, "SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.8 && Centrality < 1.0 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 80-100%;Mass/PT;", 100, 0.0, 200.0, true);
   PdfFile.AddPlot(Tree, "SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.8 && Centrality < 1.0 && abs(JetCSEta) < 1.3)", "", "Raw PT > 100, Centrality = 80-100%;Mass/PT;", 100, 0.0, 0.3);
   PdfFile.AddPlot2D(Tree, "SubJetDR0:SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.8 && Centrality < 1.0 && abs(JetCSEta) < 1.3)", "colz", "Raw PT > 100, Centrality = 80-100%;Mass/PT;DR", 100, 0.0, 200.0, 100, 0.0, 4.0, false, true);
   PdfFile.AddPlot2D(Tree, "SubJetDR0:SDMass0/MatchPT", "MCWeight * (MatchDR < 0.08 && MatchPT > 100 && Centrality > 0.8 && Centrality < 1.0 && abs(JetCSEta) < 1.3)", "colz", "Raw PT > 100, Centrality = 80-100%;Mass/PT;DR", 100, 0.0, 0.5, 100, 0.0, 0.7, false, true);
   

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}





