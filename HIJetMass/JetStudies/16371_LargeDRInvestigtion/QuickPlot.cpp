#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main();

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFilePP("PFPlotsPP.pdf");
   PdfFileHelper PdfFileAA("PFPlotsAA.pdf");
   
   PdfFilePP.AddTextPage("CS PF Plots (PP)");
   PdfFileAA.AddTextPage("CS PF Plots (AA)");

   TFile PPFile("PP6Dijet.root");
   TFile AAFile("AA6DijetCymbal.root");

   TTree *TPP = (TTree *)PPFile.Get("OutputTree");
   TTree *TAA = (TTree *)AAFile.Get("T");

   TPP->SetAlias("DEta", "(PFEta-BestJetEta)");
   TPP->SetAlias("DPhiX", "cos(PFPhi-BestJetPhi)");
   TPP->SetAlias("DPhiY", "sin(PFPhi-BestJetPhi)");
   TPP->SetAlias("DPhi", "(acos(DPhiX)*(1-2*(DPhiY<0)))");
   TPP->SetAlias("DR", "sqrt(DEta*DEta+DPhi*DPhi)");
   TPP->SetAlias("Baseline", "(BestJetPT > 140 && abs(BestJetEta) < 1.3 && PTHat > 100 && BestJetDR > 0.35)");
   
   TAA->SetAlias("DEta", "(PFEta-MatchEta)");
   TAA->SetAlias("DPhiX", "cos(PFPhi-MatchPhi)");
   TAA->SetAlias("DPhiY", "sin(PFPhi-MatchPhi)");
   TAA->SetAlias("DPhi", "(acos(DPhiX)*(1-2*(DPhiY<0)))");
   TAA->SetAlias("DR", "sqrt(DEta*DEta+DPhi*DPhi)");
   TAA->SetAlias("Baseline", "(MatchPT > 140 && abs(MatchEta) < 1.3 && PTHat > 100 && SubJetDR0 > 0.35)");

   // 2D DEta-DPhi plots
   PdfFilePP.AddPlot2D(TPP, "DEta:DPhi", "Baseline * MCWeight * (PFPT > 0)", "colz",
      "PP, PT > 0;#Delta#phi (jet - CS);#Delta#eta (jet - CS)", 200, -0.6, 0.6, 200, -0.6, 0.6);
   PdfFilePP.AddPlot2D(TPP, "DEta:DPhi", "Baseline * MCWeight * (PFPT > 0.5)", "colz",
      "PP, PT > 0.5;#Delta#phi (jet - CS);#Delta#eta (jet - CS)", 200, -0.6, 0.6, 200, -0.6, 0.6);
   PdfFilePP.AddPlot2D(TPP, "DEta:DPhi", "Baseline * MCWeight * (PFPT > 1.5)", "colz",
      "PP, PT > 1.5;#Delta#phi (jet - CS);#Delta#eta (jet - CS)", 200, -0.6, 0.6, 200, -0.6, 0.6);
   PdfFilePP.AddPlot2D(TPP, "DEta:DPhi", "Baseline * MCWeight * (PFPT > 10)", "colz",
      "PP, PT > 10;#Delta#phi (jet - CS);#Delta#eta (jet - CS)", 200, -0.6, 0.6, 200, -0.6, 0.6);
   
   PdfFileAA.AddPlot2D(TAA, "DEta:DPhi", "Baseline * MCWeight * (PFPT > 0)", "colz",
      "AA, PT > 0;#Delta#phi (jet - CS);#Delta#eta (jet - CS)", 200, -0.6, 0.6, 200, -0.6, 0.6);
   PdfFileAA.AddPlot2D(TAA, "DEta:DPhi", "Baseline * MCWeight * (PFPT > 0.5)", "colz",
      "AA, PT > 0.5;#Delta#phi (jet - CS);#Delta#eta (jet - CS)", 200, -0.6, 0.6, 200, -0.6, 0.6);
   PdfFileAA.AddPlot2D(TAA, "DEta:DPhi", "Baseline * MCWeight * (PFPT > 1.5)", "colz",
      "AA, PT > 1.5;#Delta#phi (jet - CS);#Delta#eta (jet - CS)", 200, -0.6, 0.6, 200, -0.6, 0.6);
   PdfFileAA.AddPlot2D(TAA, "DEta:DPhi", "Baseline * MCWeight * (PFPT > 10)", "colz",
      "AA, PT > 10;#Delta#phi (jet - CS);#Delta#eta (jet - CS)", 200, -0.6, 0.6, 200, -0.6, 0.6);
   
   // DR plots
   PdfFilePP.AddPlot(TPP, "DR", "Baseline * MCWeight * (PFPT > 0)", "",
      "PP, PT > 0;#DeltaR (jet - CS);", 200, 0, 0.6);
   PdfFilePP.AddPlot(TPP, "DR", "Baseline * MCWeight * (PFPT > 0.5)", "",
      "PP, PT > 0.5;#DeltaR (jet - CS);", 200, 0, 0.6);
   PdfFilePP.AddPlot(TPP, "DR", "Baseline * MCWeight * (PFPT > 1.5)", "",
      "PP, PT > 1.5;#DeltaR (jet - CS);", 200, 0, 0.6);
   PdfFilePP.AddPlot(TPP, "DR", "Baseline * MCWeight * (PFPT > 10)", "",
      "PP, PT > 10;#DeltaR (jet - CS);", 200, 0, 0.6);
   
   PdfFileAA.AddPlot(TAA, "DR", "Baseline * MCWeight * (PFPT > 0)", "",
      "AA, PT > 0;#DeltaR (jet - CS);", 200, 0, 0.6);
   PdfFileAA.AddPlot(TAA, "DR", "Baseline * MCWeight * (PFPT > 0.5)", "",
      "AA, PT > 0.5;#DeltaR (jet - CS);", 200, 0, 0.6);
   PdfFileAA.AddPlot(TAA, "DR", "Baseline * MCWeight * (PFPT > 1.5)", "",
      "AA, PT > 1.5;#DeltaR (jet - CS);", 200, 0, 0.6);
   PdfFileAA.AddPlot(TAA, "DR", "Baseline * MCWeight * (PFPT > 10)", "",
      "AA, PT > 10;#DeltaR (jet - CS);", 200, 0, 0.6);

   // DR plots - energy
   PdfFilePP.AddPlot(TPP, "DR", "Baseline * MCWeight * (PFPT > 0) * PFPT", "",
      "PP, PT > 0;#DeltaR (jet - CS);PT", 200, 0, 0.6);
   PdfFilePP.AddPlot(TPP, "DR", "Baseline * MCWeight * (PFPT > 0.5) * PFPT", "",
      "PP, PT > 0.5;#DeltaR (jet - CS);PT", 200, 0, 0.6);
   PdfFilePP.AddPlot(TPP, "DR", "Baseline * MCWeight * (PFPT > 1.5) * PFPT", "",
      "PP, PT > 1.5;#DeltaR (jet - CS);PT", 200, 0, 0.6);
   PdfFilePP.AddPlot(TPP, "DR", "Baseline * MCWeight * (PFPT > 10) * PFPT", "",
      "PP, PT > 10;#DeltaR (jet - CS);PT", 200, 0, 0.6);
   
   PdfFileAA.AddPlot(TAA, "DR", "Baseline * MCWeight * (PFPT > 0) * PFPT", "",
      "AA, PT > 0;#DeltaR (jet - CS);PT", 200, 0, 0.6);
   PdfFileAA.AddPlot(TAA, "DR", "Baseline * MCWeight * (PFPT > 0.5) * PFPT", "",
      "AA, PT > 0.5;#DeltaR (jet - CS);PT", 200, 0, 0.6);
   PdfFileAA.AddPlot(TAA, "DR", "Baseline * MCWeight * (PFPT > 1.5) * PFPT", "",
      "AA, PT > 1.5;#DeltaR (jet - CS);PT", 200, 0, 0.6);
   PdfFileAA.AddPlot(TAA, "DR", "Baseline * MCWeight * (PFPT > 10) * PFPT", "",
      "AA, PT > 10;#DeltaR (jet - CS);PT", 200, 0, 0.6);

   // DR plots breaking down into smaller jet PT and centrality and SubJetDR bins
   PdfFilePP.AddPlot(TPP, "DR", "Baseline * MCWeight * (PFPT > 0 && BestJetDR > 0.40 && Centrality > 0.8)", "",
      "PP, PT > 0, SD DR > 0.40;#DeltaR (jet - CS);", 50, 0, 0.6);
   PdfFilePP.AddPlot(TPP, "DR", "Baseline * MCWeight * (PFPT > 10 && BestJetDR > 0.40 && Centrality > 0.8)", "",
      "PP, PT > 10, SD DR > 0.40;#DeltaR (jet - CS);", 50, 0, 0.6);
   
   PdfFileAA.AddPlot(TAA, "DR", "Baseline * MCWeight * (PFPT > 0 && SubJetDR0 > 0.40 && Centrality > 0.8)", "",
      "AA, PT > 0, SD DR > 0.40;#DeltaR (jet - CS);", 50, 0, 0.6);
   PdfFileAA.AddPlot(TAA, "DR", "Baseline * MCWeight * (PFPT > 10 && SubJetDR0 > 0.40 && Centrality > 0.8)", "",
      "AA, PT > 10, SD DR > 0.40;#DeltaR (jet - CS);", 50, 0, 0.6);


   AAFile.Close();
   PPFile.Close();

   PdfFileAA.AddTimeStampPage();
   PdfFileAA.Close();
   
   PdfFilePP.AddTimeStampPage();
   PdfFilePP.Close();

   return 0;
}





