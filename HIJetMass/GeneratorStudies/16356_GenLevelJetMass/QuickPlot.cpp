#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("Meow.pdf");
   PdfFile.AddTextPage("Meow");

   TFile F1("AA6DijetCymbalNoCut.root");
   TFile F2("PP6Dijet.root");

   TTree *T1 = (TTree *)F1.Get("GenJetTree");
   TTree *T2 = (TTree *)F2.Get("GenJetTree");

   PdfFile.AddPlot(T1, "PTHat", "MCWeight * (abs(JetEta) < 1.3 && Centrality > 0.8)", "", "AA;PTHat;", 100, 50, 600, true);
   PdfFile.AddPlot(T2, "PTHat", "MCWeight * (abs(JetEta) < 1.3)", "", "PP;PTHat;", 100, 50, 600, true);
   
   PdfFile.AddPlot(T1, "SubJetDR0", "MCWeight * (JetPT > 100 && abs(JetEta) < 1.3 && Centrality > 0.8)", "", "AA;DR (SD0);", 20, 0.0, 0.5, true);
   PdfFile.AddPlot(T2, "SubJetDR0", "MCWeight * (JetPT > 100 && abs(JetEta) < 1.3)", "", "PP;DR (SD0);", 20, 0.0, 0.5, true);
   
   PdfFile.AddPlot(T1, "SDMass0/JetPT", "MCWeight * (JetPT > 100 && abs(JetEta) < 1.3 && SubJetDR0 > 0.1 && Centrality > 0.8)", "", "AA;Mass/PT (SD0);", 20, 0.0, 0.3, true);
   PdfFile.AddPlot(T2, "SDMass0/JetPT", "MCWeight * (JetPT > 100 && abs(JetEta) < 1.3 && SubJetDR0 > 0.1)", "", "PP;Mass/PT (SD0);", 20, 0.0, 0.3, true);
   
   PdfFile.AddPlot(T1, "SDMass0/JetPT", "MCWeight * (JetPT > 100 && abs(JetEta) < 1.3 && SubJetDR0 > 0.1 && Centrality > 0.8)", "", "AA;Mass/PT (SD0);", 20, 0.0, 0.3, false);
   PdfFile.AddPlot(T2, "SDMass0/JetPT", "MCWeight * (JetPT > 100 && abs(JetEta) < 1.3 && SubJetDR0 > 0.1)", "", "PP;Mass/PT (SD0);", 20, 0.0, 0.3, false);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




