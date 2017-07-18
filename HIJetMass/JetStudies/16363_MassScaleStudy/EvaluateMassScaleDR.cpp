#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TProfile.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TF1.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main();
double ExtractScale(PdfFileHelper &PdfFile, string CutPlain, string CutSmear, string Description = "", bool DRCorrection = false, bool SD0 = true);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("ScalePlots.pdf");
   PdfFile.AddTextPage("Attempt to understang scale vs. DR");

   PdfFile.AddTextPage("Some random plots");
   ExtractScale(PdfFile,
      "(PTHat > 170 && PTHat < 180 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(PTHat > 170 && PTHat < 180 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 170-180, Centrality = 0-100%, JetPT = 140-300");
   ExtractScale(PdfFile,
      "(PTHat > 100 && PTHat < 200 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(PTHat > 100 && PTHat < 200 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 100-200, Centrality = 0-100%, JetPT = 140-300");
   ExtractScale(PdfFile,
      "(PTHat > 200 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(PTHat > 200 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 0-100%, JetPT = 140-300");
   ExtractScale(PdfFile,
      "(PTHat > 100 && PTHat < 200 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(PTHat > 100 && PTHat < 200 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 100-200, Centrality = 0-100%, JetPT = 240-300");
   ExtractScale(PdfFile,
      "(PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 0-100%, JetPT = 240-300");
   
   PdfFile.AddTextPage("Centrality depedence, PTHat 200-300");
   ExtractScale(PdfFile,
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 0-20%, JetPT = 200-300");
   ExtractScale(PdfFile,
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 20-40%, JetPT = 200-300");
   ExtractScale(PdfFile,
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 40-60%, JetPT = 200-300");
   ExtractScale(PdfFile,
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 60-80%, JetPT = 200-300");
   ExtractScale(PdfFile,
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 80-100%, JetPT = 200-300");
   
   PdfFile.AddTextPage("Centrality depedence, PTHat 100-300");
   ExtractScale(PdfFile,
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 0-20%, JetPT = 140-300");
   ExtractScale(PdfFile,
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 20-40%, JetPT = 140-300");
   ExtractScale(PdfFile,
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 40-60%, JetPT = 140-300");
   ExtractScale(PdfFile,
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 60-80%, JetPT = 140-300");
   ExtractScale(PdfFile,
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 80-100%, JetPT = 140-300");

   PdfFile.AddTextPage("Centrality depedence, PTHat 200-300, DR");
   ExtractScale(PdfFile,
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 0-20%, JetPT = 200-300, DR", true);
   ExtractScale(PdfFile,
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 20-40%, JetPT = 200-300, DR", true);
   ExtractScale(PdfFile,
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 40-60%, JetPT = 200-300, DR", true);
   ExtractScale(PdfFile,
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 60-80%, JetPT = 200-300, DR", true);
   ExtractScale(PdfFile,
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 80-100%, JetPT = 200-300, DR", true);
   
   PdfFile.AddTextPage("Centrality depedence, PTHat 100-200, DR");
   ExtractScale(PdfFile,
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 100 && PTHat < 200 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 100 && PTHat < 200 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 100-200, Centrality = 0-20%, JetPT = 140-300, DR", true);
   ExtractScale(PdfFile,
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 100 && PTHat < 200 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 100 && PTHat < 200 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 100-200, Centrality = 20-40%, JetPT = 140-300, DR", true);
   ExtractScale(PdfFile,
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 100 && PTHat < 200 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 100 && PTHat < 200 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 100-200, Centrality = 40-60%, JetPT = 140-300, DR", true);
   ExtractScale(PdfFile,
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 100 && PTHat < 200 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 100 && PTHat < 200 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 100-200, Centrality = 60-80%, JetPT = 140-300, DR", true);
   ExtractScale(PdfFile,
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 100 && PTHat < 200 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR0 > 0.1) * MCWeight",
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 100 && PTHat < 200 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR > 0.1) * MCWeight",
      "PTHat = 100-200, Centrality = 80-100%, JetPT = 140-300, DR", true);

   PdfFile.AddTextPage("SD7 Centrality depedence, PTHat 200-300");
   ExtractScale(PdfFile,
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 0-20%, JetPT = 200-300", false, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 20-40%, JetPT = 200-300", false, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 40-60%, JetPT = 200-300", false, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 60-80%, JetPT = 200-300", false, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 80-100%, JetPT = 200-300", false, true);
   
   PdfFile.AddTextPage("SD7 Centrality depedence, PTHat 100-300");
   ExtractScale(PdfFile,
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 0-20%, JetPT = 140-300", false, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 20-40%, JetPT = 140-300", false, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 40-60%, JetPT = 140-300", false, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 60-80%, JetPT = 140-300", false, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 80-100%, JetPT = 140-300", false, true);

   PdfFile.AddTextPage("SD7 Centrality depedence, PTHat 200-300, DR");
   ExtractScale(PdfFile,
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 0-20%, JetPT = 200-300, DR", true, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 20-40%, JetPT = 200-300, DR", true, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 40-60%, JetPT = 200-300 DR", true, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 60-80%, JetPT = 200-300 DR", true, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 200 && PTHat < 300 && JetCSRawPT > 200 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 200 && PTHat < 300 && BestJetPT > 200 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 200-300, Centrality = 80-100%, JetPT = 200-300 DR", true, true);
   
   PdfFile.AddTextPage("SD7 Centrality depedence, PTHat 100-300, DR");
   ExtractScale(PdfFile,
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.0 && Centrality < 0.2 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 0-20%, JetPT = 140-300 DR", true, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.2 && Centrality < 0.4 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 20-40%, JetPT = 140-300 DR", true, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.4 && Centrality < 0.6 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 40-60%, JetPT = 140-300 DR", true, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.6 && Centrality < 0.8 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 60-80%, JetPT = 140-300 DR", true, true);
   ExtractScale(PdfFile,
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 100 && PTHat < 300 && JetCSRawPT > 140 && JetCSRawPT < 300 && abs(JetCSEta) < 1.3 && SubJetDR7 > 0.1) * MCWeight",
      "(Centrality > 0.8 && Centrality < 1.0 && PTHat > 100 && PTHat < 300 && BestJetPT > 140 && BestJetPT < 300 && abs(BestJetEta) < 1.3 && BestJetDR2 > 0.1) * MCWeight",
      "PTHat = 100-300, Centrality = 80-100%, JetPT = 140-300 DR", true, true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double ExtractScale(PdfFileHelper &PdfFile, string CutPlain, string CutSmear, string Description, bool DRCorrection, bool SD0)
{
   if(Description != "")
      PdfFile.AddTextPage(Description, 0.035);
   else
   {
      vector<string> Condition(10);
      Condition[0] = "Cut on embedded sample:";
      Condition[1] = CutPlain;
      Condition[2] = "";
      Condition[3] = "";
      Condition[4] = "Cut on smeared sample:";
      Condition[5] = CutSmear;
      PdfFile.AddTextPage(Condition);
   }

   TCanvas Canvas;

   CutPlain = "(" + CutPlain + ")";
   CutSmear = "(" + CutSmear + ")";

   TFile FPlain("AA6DijetCymbal.root");
   TFile FSmear("PP6Dijet.root");

   TTree *TPlain = (TTree *)FPlain.Get("T");
   TTree *TSmear = (TTree *)FSmear.Get("OutputTree");

   TH1D HCentralityPlain("HCentralityPlain", "Embedded;Centrality;", 50, 0.0, 1.0);
   TH1D HCentralitySmear("HCentralitySmear", "Smeared pp;Centrality;", 50, 0.0, 1.0);

   TPlain->Draw("Centrality>>HCentralityPlain", CutPlain.c_str());
   TSmear->Draw("Centrality>>HCentralitySmear", CutSmear.c_str());

   HCentralityPlain.SetMinimum(0);
   HCentralitySmear.SetMinimum(0);

   PdfFile.AddPlot(HCentralityPlain);
   PdfFile.AddPlot(HCentralitySmear);

   string CString = "(0";
   for(int i = 1; i <= HCentralityPlain.GetNbinsX(); i++)
   {
      if(HCentralitySmear.GetBinContent(i) == 0)
         continue;
      CString = CString + Form("+(Centrality>%.2f&&Centrality<=%.2f)*%.2f", HCentralityPlain.GetXaxis()->GetBinLowEdge(i), HCentralityPlain.GetXaxis()->GetBinUpEdge(i), HCentralityPlain.GetBinContent(i) / HCentralitySmear.GetBinContent(i));
   }
   CString = CString + ")";

   TSmear->SetAlias("CWeight", CString.c_str());

   TProfile PPlain("PPlain", ";DR;<M_{g}/p_{T}>", 20, 0.1, 0.4);
   TProfile PSmear("PSmear", ";DR;<M_{g}/p_{T}>", 20, 0.1, 0.4);

   if(SD0 == true)
   {
      TPlain->Draw("SDMass0/MatchPT:SubJetDR0>>PPlain", CutPlain.c_str(), "prof");
      if(DRCorrection == false)
         TSmear->Draw("BestJetSDMass/BestJetPT:BestJetDR>>PSmear", (CutSmear + " * CWeight").c_str(), "prof");
      else
         TSmear->Draw("BestJetSDMass/BestJetPT*(1.01-0.075*BestJetDR):BestJetDR>>PSmear", (CutSmear + " * CWeight").c_str(), "prof");
   }
   else
   {
      TPlain->Draw("SDMass7/MatchPT:SubJetDR7>>PPlain", CutPlain.c_str(), "prof");
      if(DRCorrection == false)
         TSmear->Draw("BestJetSDMass2/BestJetPT:BestJetDR2>>PSmear", (CutSmear + " * CWeight").c_str(), "prof");
      else
         TSmear->Draw("BestJetSDMass2/BestJetPT*(1.01-0.075*BestJetDR2):BestJetDR2>>PSmear", (CutSmear + " * CWeight").c_str(), "prof");
   }

   PPlain.SetStats(0);
   PPlain.SetMaximum(0.25);
   PPlain.SetMinimum(0.00);
   PPlain.SetLineColor(kMagenta);
   PPlain.SetMarkerColor(kMagenta);
   PSmear.SetLineColor(kBlue);
   PSmear.SetMarkerColor(kBlue);

   TLegend Legend(0.5, 0.4, 0.8, 0.2);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&PPlain, "Embedded", "pl");
   Legend.AddEntry(&PSmear, "Smeared", "pl");

   PPlain.Draw();
   PSmear.Draw("same");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   PPlain.Divide(&PSmear);
   PPlain.Draw("hist p");
   PPlain.SetMinimum(0.85);
   PPlain.SetMaximum(1.05);
   PPlain.GetYaxis()->SetTitle("Ratio Embedded/Smeared");
   
   TF1 Fit("fit", "pol2");
   PPlain.Fit(&Fit, "", "", 0.10, 0.39);
   Fit.Draw("same");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetNDC();
   Latex.DrawLatex(0.20, 0.28, Form("p0 = %.2f #pm %.2f", Fit.GetParameter(0), Fit.GetParError(0)));
   Latex.DrawLatex(0.20, 0.23, Form("p1 = %.2f #pm %.2f", Fit.GetParameter(1), Fit.GetParError(1)));
   Latex.DrawLatex(0.20, 0.18, Form("p2 = %.2f #pm %.2f", Fit.GetParameter(2), Fit.GetParError(2)));

   TGraph GReference;
   GReference.SetPoint(0, 0.0, 1.01 - 0.0 * 0.075);
   GReference.SetPoint(1, 0.4, 1.01 - 0.4 * 0.075);
   GReference.SetLineWidth(2);
   GReference.SetLineColor(kGreen);
   if(DRCorrection == false)
      GReference.Draw("l");

   PdfFile.AddCanvas(Canvas);

   FSmear.Close();
   FPlain.Close();

   return 1;
}









