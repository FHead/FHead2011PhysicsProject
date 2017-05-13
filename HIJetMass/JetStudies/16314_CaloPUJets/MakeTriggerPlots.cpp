#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("TriggerPlots.pdf");
   PdfFile.AddTextPage("Trigger plots");

   TFile File("AADataPrescale0127.root");

   TTree *Tree = (TTree *)File.Get("T");

   Tree->SetAlias("J60PFPUDEta", "(J60Eta-J60PFPUEta)");
   Tree->SetAlias("J80PFPUDEta", "(J80Eta-J80PFPUEta)");
   Tree->SetAlias("J100PFPUDEta", "(J100Eta-J100PFPUEta)");
   Tree->SetAlias("J60CaloPUDEta", "(J60Eta-J60CaloPUEta)");
   Tree->SetAlias("J80CaloPUDEta", "(J80Eta-J80CaloPUEta)");
   Tree->SetAlias("J100CaloPUDEta", "(J100Eta-J100CaloPUEta)");

   Tree->SetAlias("J60PFPUDPhi", "((J60Phi-J60PFPUPhi)+2*3.1415926535*(J60Phi-J60PFPUPhi<-3.1415926535)-2*3.1415926535*(J60Phi-J60PFPUPhi>3.1415926535))");
   Tree->SetAlias("J80PFPUDPhi", "((J80Phi-J80PFPUPhi)+2*3.1415926535*(J80Phi-J80PFPUPhi<-3.1415926535)-2*3.1415926535*(J80Phi-J80PFPUPhi>3.1415926535))");
   Tree->SetAlias("J100PFPUDPhi", "((J100Phi-J100PFPUPhi)+2*3.1415926535*(J100Phi-J100PFPUPhi<-3.1415926535)-2*3.1415926535*(J100Phi-J100PFPUPhi>3.1415926535))");
   Tree->SetAlias("J60CaloPUDPhi", "((J60Phi-J60CaloPUPhi)+2*3.1415926535*(J60Phi-J60CaloPUPhi<-3.1415926535)-2*3.1415926535*(J60Phi-J60CaloPUPhi>3.1415926535))");
   Tree->SetAlias("J80CaloPUDPhi", "((J80Phi-J80CaloPUPhi)+2*3.1415926535*(J80Phi-J80CaloPUPhi<-3.1415926535)-2*3.1415926535*(J80Phi-J80CaloPUPhi>3.1415926535))");
   Tree->SetAlias("J100CaloPUDPhi", "((J100Phi-J100CaloPUPhi)+2*3.1415926535*(J100Phi-J100CaloPUPhi<-3.1415926535)-2*3.1415926535*(J100Phi-J100CaloPUPhi>3.1415926535))");

   Tree->SetAlias("J60PFPUDR", "sqrt(J60PFPUDEta*J60PFPUDEta+J60PFPUDPhi*J60PFPUDPhi)");
   Tree->SetAlias("J80PFPUDR", "sqrt(J80PFPUDEta*J80PFPUDEta+J80PFPUDPhi*J80PFPUDPhi)");
   Tree->SetAlias("J100PFPUDR", "sqrt(J100PFPUDEta*J100PFPUDEta+J100PFPUDPhi*J100PFPUDPhi)");
   Tree->SetAlias("J60CaloPUDR", "sqrt(J60CaloPUDEta*J60CaloPUDEta+J60CaloPUDPhi*J60CaloPUDPhi)");
   Tree->SetAlias("J80CaloPUDR", "sqrt(J80CaloPUDEta*J80CaloPUDEta+J80CaloPUDPhi*J80CaloPUDPhi)");
   Tree->SetAlias("J100CaloPUDR", "sqrt(J100CaloPUDEta*J100CaloPUDEta+J100CaloPUDPhi*J100CaloPUDPhi)");

   PdfFile.AddTextPage("Trigger object distributions");

   PdfFile.AddPlot(Tree, "J60Phi", "JetIndex == 0 && PassPbPb60", "error",
      "J60 (60);phi;", 100, -3.2, 3.2);
   PdfFile.AddPlot2D(Tree, "J60PT:J60Eta", "JetIndex == 0 && PassPbPb60", "colz",
      "J60 (60);eta;PT", 100, -5, 5, 100, 0, 250);
   PdfFile.AddPlot2D(Tree, "J60Eta:J60Phi", "JetIndex == 0 && PassPbPb60", "colz",
      "J60 (60);phi;eta", 100, -3.2, 3.2, 100, -5, 5);

   PdfFile.AddPlot(Tree, "J80Phi", "JetIndex == 0 && PassPbPb80",
      "error", "J80 (80);phi;", 100, -3.2, 3.2);
   PdfFile.AddPlot2D(Tree, "J80PT:J80Eta", "JetIndex == 0 && PassPbPb80", "colz",
      "J80 (80);eta;PT", 100, -5, 5, 100, 0, 250);
   PdfFile.AddPlot2D(Tree, "J80Eta:J80Phi", "JetIndex == 0 && PassPbPb80", "colz",
      "J80 (80);phi;eta", 100, -3.2, 3.2, 100, -5, 5);

   PdfFile.AddPlot(Tree, "J100Phi", "JetIndex == 0 && PassPbPb100", "error",
      "J100 (100);phi;", 100, -3.2, 3.2);
   PdfFile.AddPlot2D(Tree, "J100PT:J100Eta", "JetIndex == 0 && PassPbPb100", "colz",
      "J100 (100);eta;PT", 100, -5, 5, 100, 0, 250);
   PdfFile.AddPlot2D(Tree, "J100Eta:J100Phi", "JetIndex == 0 && PassPbPb100", "colz",
      "J100 (100);phi;eta", 100, -3.2, 3.2, 100, -5, 5);
   
   PdfFile.AddPlot(Tree, "J60Phi", "JetIndex == 0 && PassPbPb60 && !PassPbPb100", "error",
      "J60 (60 & !100);phi;", 100, -3.2, 3.2);
   PdfFile.AddPlot2D(Tree, "J60PT:J60Eta", "JetIndex == 0 && PassPbPb60 && !PassPbPb100", "colz",
      "J60 (60 & !100);eta;PT", 100, -5, 5, 100, 0, 250);
   PdfFile.AddPlot2D(Tree, "J60Eta:J60Phi", "JetIndex == 0 && PassPbPb60 && !PassPbPb100", "colz",
      "J60 (60 & !100);phi;eta", 100, -3.2, 3.2, 100, -5, 5);
   PdfFile.AddPlot2D(Tree, "J60Eta:J60Phi", "JetIndex == 0 && PassPbPb60 && !PassPbPb100 && J60PT > 100", "colz",
      "J60 (60 & !100 & PT > 100);phi;eta", 100, -3.2, 3.2, 100, -5, 5);
   
   PdfFile.AddPlotProfile(Tree, "PassPbPb100:J60PT", "JetIndex == 0 && PassPbPb60", "prof",
      "PbPb100 turn on relative to PbPb60;PT;", 100, 0, 250);
   PdfFile.AddPlotProfile(Tree, "PassPbPb100:J60PT", "JetIndex == 0 && PassPbPb60 && abs(J60Eta) < 1.5", "prof",
      "PbPb100 turn on relative to PbPb60 (eta < 1.5);PT;", 100, 0, 250);
   PdfFile.AddPlotProfile2D(Tree, "PassPbPb100:J60PT:J60Eta",
      "JetIndex == 0 && PassPbPb60", "prof2d colz",
      "PbPb100 turn on relative to PbPb60;eta;PT", 50, -3.2, 3.2, 50, 0, 300);

   PdfFile.AddTextPage("Matched calo PU distributions");
   
   PdfFile.AddPlot(Tree, "J60CaloPUPhi", "JetIndex == 0 && PassPbPb60", "error",
      "J60 (60);phi;", 100, -3.2, 3.2);
   PdfFile.AddPlot(Tree, "J60CaloPUEta", "JetIndex == 0 && PassPbPb60", "error",
      "J60 (60);Eta;", 100, -5, 5);
   PdfFile.AddPlot2D(Tree, "J60CaloPUPT:J60CaloPUEta", "JetIndex == 0 && PassPbPb60", "colz",
      "J60 (60);eta;PT", 100, -5, 5, 100, 0, 250);
   PdfFile.AddPlot2D(Tree, "J60CaloPUEta:J60CaloPUPhi", "JetIndex == 0 && PassPbPb60", "colz",
      "J60 (60);phi;eta", 100, -3.2, 3.2, 100, -5, 5);

   PdfFile.AddPlot2D(Tree, "J60CaloPUDEta:J60CaloPUDPhi", "JetIndex == 0 && PassPbPb60", "colz",
      "J60 matching (60);dphi;deta", 100, -2, 2, 100, -2, 2);
   PdfFile.AddPlot2D(Tree, "J60CaloPUDEta:J60CaloPUDPhi", "JetIndex == 0 && PassPbPb60 && abs(J60Eta) < 2", "colz",
      "J60 matching (60), trigger object |eta| < 2;dphi;deta", 100, -2, 2, 100, -2, 2);
   PdfFile.AddPlot2D(Tree, "J60CaloPUDEta:J60CaloPUDPhi", "JetIndex == 0 && PassPbPb60 && abs(J60Eta) < 2", "colz",
      "J60 matching (60), trigger object |eta| < 2;dphi;deta", 100, -2, 2, 100, -2, 2, false, true);
   PdfFile.AddPlot2D(Tree, "J60CaloPUDR:J60Eta", "JetIndex == 0 && PassPbPb60", "colz",
      "J60 matching (60);trigger object eta;DR", 100, -5, 5, 100, 0, 2, false, true);

   PdfFile.AddPlot(Tree, "J80CaloPUPhi", "JetIndex == 0 && PassPbPb80",
      "error", "J80 (80);phi;", 100, -3.2, 3.2);
   PdfFile.AddPlot(Tree, "J80CaloPUEta", "JetIndex == 0 && PassPbPb80", "error",
      "J80 (80);Eta;", 100, -5, 5);
   PdfFile.AddPlot2D(Tree, "J80CaloPUPT:J80CaloPUEta", "JetIndex == 0 && PassPbPb80", "colz",
      "J80 (80);eta;PT", 100, -5, 5, 100, 0, 250);
   PdfFile.AddPlot2D(Tree, "J80CaloPUEta:J80CaloPUPhi", "JetIndex == 0 && PassPbPb80", "colz",
      "J80 (80);phi;eta", 100, -3.2, 3.2, 100, -5, 5);

   PdfFile.AddPlot2D(Tree, "J80CaloPUDEta:J80CaloPUDPhi", "JetIndex == 0 && PassPbPb80", "colz",
      "J80 matching (80);dphi;deta", 100, -2, 2, 100, -2, 2);
   PdfFile.AddPlot2D(Tree, "J80CaloPUDEta:J80CaloPUDPhi", "JetIndex == 0 && PassPbPb80 && abs(J80Eta) < 2", "colz",
      "J80 matching (80), trigger object |eta| < 2;dphi;deta", 100, -2, 2, 100, -2, 2);
   PdfFile.AddPlot2D(Tree, "J80CaloPUDEta:J80CaloPUDPhi", "JetIndex == 0 && PassPbPb80 && abs(J80Eta) < 2", "colz",
      "J80 matching (80), trigger object |eta| < 2;dphi;deta", 100, -2, 2, 100, -2, 2, false, true);
   PdfFile.AddPlot2D(Tree, "J80CaloPUDR:J80Eta", "JetIndex == 0 && PassPbPb80", "colz",
      "J80 matching (80);trigger object eta;DR", 100, -5, 5, 100, 0, 2, false, true);

   PdfFile.AddPlot(Tree, "J100CaloPUPhi", "JetIndex == 0 && PassPbPb100", "error",
      "J100 (100);phi;", 100, -3.2, 3.2);
   PdfFile.AddPlot(Tree, "J100CaloPUEta", "JetIndex == 0 && PassPbPb100", "error",
      "J100 (100);Eta;", 100, -5, 5);
   PdfFile.AddPlot2D(Tree, "J100CaloPUPT:J100CaloPUEta", "JetIndex == 0 && PassPbPb100", "colz",
      "J100 (100);eta;PT", 100, -5, 5, 100, 0, 250);
   PdfFile.AddPlot2D(Tree, "J100CaloPUEta:J100CaloPUPhi", "JetIndex == 0 && PassPbPb100", "colz",
      "J100 (100);phi;eta", 100, -3.2, 3.2, 100, -5, 5);
   
   PdfFile.AddPlot2D(Tree, "J100CaloPUDEta:J100CaloPUDPhi", "JetIndex == 0 && PassPbPb100", "colz",
      "J100 matching (100);dphi;deta", 100, -2, 2, 100, -2, 2);
   PdfFile.AddPlot2D(Tree, "J100CaloPUDEta:J100CaloPUDPhi", "JetIndex == 0 && PassPbPb100 && abs(J100Eta) < 2", "colz",
      "J100 matching (100), trigger object |eta| < 2;dphi;deta", 100, -2, 2, 100, -2, 2);
   PdfFile.AddPlot2D(Tree, "J100CaloPUDEta:J100CaloPUDPhi", "JetIndex == 0 && PassPbPb100 && abs(J100Eta) < 2", "colz",
      "J100 matching (100), trigger object |eta| < 2;dphi;deta", 100, -2, 2, 100, -2, 2, false, true);
   PdfFile.AddPlot2D(Tree, "J100CaloPUDR:J100Eta", "JetIndex == 0 && PassPbPb100", "colz",
      "J100 matching (100);trigger object eta;DR", 100, -5, 5, 100, 0, 2, false, true);

   PdfFile.AddPlot(Tree, "J60CaloPUPhi", "JetIndex == 0 && PassPbPb60 && !PassPbPb100", "error",
      "J60 (60 & !100);phi;", 100, -3.2, 3.2);
   PdfFile.AddPlot2D(Tree, "J60CaloPUPT:J60CaloPUEta", "JetIndex == 0 && PassPbPb60 && !PassPbPb100", "colz",
      "J60 (60 & !100);eta;PT", 100, -5, 5, 100, 0, 250);
   PdfFile.AddPlot2D(Tree, "J60CaloPUEta:J60CaloPUPhi", "JetIndex == 0 && PassPbPb60 && !PassPbPb100", "colz",
      "J60 (60 & !100);phi;eta", 100, -3.2, 3.2, 100, -5, 5);
   PdfFile.AddPlot2D(Tree, "J60CaloPUEta:J60CaloPUPhi", "JetIndex == 0 && PassPbPb60 && !PassPbPb100 && J60PT > 100", "colz",
      "J60 (60 & !100 & PT > 100);phi;eta", 100, -3.2, 3.2, 100, -5, 5);
   
   PdfFile.AddPlotProfile(Tree, "PassPbPb100:J60CaloPUPT", "JetIndex == 0 && PassPbPb60", "prof",
      "PbPb100 turn on relative to PbPb60;PT;", 100, 0, 250);
   PdfFile.AddPlotProfile(Tree, "PassPbPb100:J60CaloPUPT", "JetIndex == 0 && PassPbPb60 && abs(J60Eta) < 1.5", "prof",
      "PbPb100 turn on relative to PbPb60 (eta < 1.5);PT;", 100, 0, 250);
   PdfFile.AddPlotProfile2D(Tree, "PassPbPb100:J60CaloPUPT:J60CaloPUEta",
      "JetIndex == 0 && PassPbPb60", "prof2d colz",
      "PbPb100 turn on relative to PbPb60;eta;PT", 50, -3.2, 3.2, 50, 0, 300);
   
   PdfFile.AddTextPage("Matched PF PU distributions");
   
   PdfFile.AddPlot(Tree, "J60PFPUPhi", "JetIndex == 0 && PassPbPb60", "error",
      "J60 (60);phi;", 100, -3.2, 3.2);
   PdfFile.AddPlot(Tree, "J60PFPUEta", "JetIndex == 0 && PassPbPb60", "error",
      "J60 (60);Eta;", 100, -5, 5);
   PdfFile.AddPlot2D(Tree, "J60PFPUPT:J60PFPUEta", "JetIndex == 0 && PassPbPb60", "colz",
      "J60 (60);eta;PT", 100, -5, 5, 100, 0, 250);
   PdfFile.AddPlot2D(Tree, "J60PFPUEta:J60PFPUPhi", "JetIndex == 0 && PassPbPb60", "colz",
      "J60 (60);phi;eta", 100, -3.2, 3.2, 100, -5, 5);

   PdfFile.AddPlot2D(Tree, "J60PFPUDEta:J60PFPUDPhi", "JetIndex == 0 && PassPbPb60", "colz",
      "J60 matching (60);dphi;deta", 100, -2, 2, 100, -2, 2);
   PdfFile.AddPlot2D(Tree, "J60PFPUDEta:J60PFPUDPhi", "JetIndex == 0 && PassPbPb60 && abs(J60Eta) < 2", "colz",
      "J60 matching (60), trigger object |eta| < 2;dphi;deta", 100, -2, 2, 100, -2, 2);
   PdfFile.AddPlot2D(Tree, "J60PFPUDEta:J60PFPUDPhi", "JetIndex == 0 && PassPbPb60 && abs(J60Eta) < 2", "colz",
      "J60 matching (60), trigger object |eta| < 2;dphi;deta", 100, -2, 2, 100, -2, 2, false, true);
   PdfFile.AddPlot2D(Tree, "J60PFPUDR:J60Eta", "JetIndex == 0 && PassPbPb60", "colz",
      "J60 matching (60);trigger object eta;DR", 100, -5, 5, 100, 0, 2, false, true);

   PdfFile.AddPlot(Tree, "J80PFPUPhi", "JetIndex == 0 && PassPbPb80",
      "error", "J80 (80);phi;", 100, -3.2, 3.2);
   PdfFile.AddPlot(Tree, "J80PFPUEta", "JetIndex == 0 && PassPbPb80", "error",
      "J80 (80);Eta;", 100, -5, 5);
   PdfFile.AddPlot2D(Tree, "J80PFPUPT:J80PFPUEta", "JetIndex == 0 && PassPbPb80", "colz",
      "J80 (80);eta;PT", 100, -5, 5, 100, 0, 250);
   PdfFile.AddPlot2D(Tree, "J80PFPUEta:J80PFPUPhi", "JetIndex == 0 && PassPbPb80", "colz",
      "J80 (80);phi;eta", 100, -3.2, 3.2, 100, -5, 5);

   PdfFile.AddPlot2D(Tree, "J80PFPUDEta:J80PFPUDPhi", "JetIndex == 0 && PassPbPb80", "colz",
      "J80 matching (80);dphi;deta", 100, -2, 2, 100, -2, 2);
   PdfFile.AddPlot2D(Tree, "J80PFPUDEta:J80PFPUDPhi", "JetIndex == 0 && PassPbPb80 && abs(J80Eta) < 2", "colz",
      "J80 matching (80), trigger object |eta| < 2;dphi;deta", 100, -2, 2, 100, -2, 2);
   PdfFile.AddPlot2D(Tree, "J80PFPUDEta:J80PFPUDPhi", "JetIndex == 0 && PassPbPb80 && abs(J80Eta) < 2", "colz",
      "J80 matching (80), trigger object |eta| < 2;dphi;deta", 100, -2, 2, 100, -2, 2, false, true);
   PdfFile.AddPlot2D(Tree, "J80PFPUDR:J80Eta", "JetIndex == 0 && PassPbPb80", "colz",
      "J80 matching (80);trigger object eta;DR", 100, -5, 5, 100, 0, 2, false, true);

   PdfFile.AddPlot(Tree, "J100PFPUPhi", "JetIndex == 0 && PassPbPb100", "error",
      "J100 (100);phi;", 100, -3.2, 3.2);
   PdfFile.AddPlot(Tree, "J100PFPUEta", "JetIndex == 0 && PassPbPb100", "error",
      "J100 (100);Eta;", 100, -5, 5);
   PdfFile.AddPlot2D(Tree, "J100PFPUPT:J100PFPUEta", "JetIndex == 0 && PassPbPb100", "colz",
      "J100 (100);eta;PT", 100, -5, 5, 100, 0, 250);
   PdfFile.AddPlot2D(Tree, "J100PFPUEta:J100PFPUPhi", "JetIndex == 0 && PassPbPb100", "colz",
      "J100 (100);phi;eta", 100, -3.2, 3.2, 100, -5, 5);
   
   PdfFile.AddPlot2D(Tree, "J100PFPUDEta:J100PFPUDPhi", "JetIndex == 0 && PassPbPb100", "colz",
      "J100 matching (100);dphi;deta", 100, -2, 2, 100, -2, 2);
   PdfFile.AddPlot2D(Tree, "J100PFPUDEta:J100PFPUDPhi", "JetIndex == 0 && PassPbPb100 && abs(J100Eta) < 2", "colz",
      "J100 matching (100), trigger object |eta| < 2;dphi;deta", 100, -2, 2, 100, -2, 2);
   PdfFile.AddPlot2D(Tree, "J100PFPUDEta:J100PFPUDPhi", "JetIndex == 0 && PassPbPb100 && abs(J100Eta) < 2", "colz",
      "J100 matching (100), trigger object |eta| < 2;dphi;deta", 100, -2, 2, 100, -2, 2, false, true);
   PdfFile.AddPlot2D(Tree, "J100PFPUDR:J100Eta", "JetIndex == 0 && PassPbPb100", "colz",
      "J100 matching (100);trigger object eta;DR", 100, -5, 5, 100, 0, 2, false, true);

   PdfFile.AddPlot(Tree, "J60PFPUPhi", "JetIndex == 0 && PassPbPb60 && !PassPbPb100", "error",
      "J60 (60 & !100);phi;", 100, -3.2, 3.2);
   PdfFile.AddPlot2D(Tree, "J60PFPUPT:J60PFPUEta", "JetIndex == 0 && PassPbPb60 && !PassPbPb100", "colz",
      "J60 (60 & !100);eta;PT", 100, -5, 5, 100, 0, 250);
   PdfFile.AddPlot2D(Tree, "J60PFPUEta:J60PFPUPhi", "JetIndex == 0 && PassPbPb60 && !PassPbPb100", "colz",
      "J60 (60 & !100);phi;eta", 100, -3.2, 3.2, 100, -5, 5);
   PdfFile.AddPlot2D(Tree, "J60PFPUEta:J60PFPUPhi", "JetIndex == 0 && PassPbPb60 && !PassPbPb100 && J60PT > 100", "colz",
      "J60 (60 & !100 & PT > 100);phi;eta", 100, -3.2, 3.2, 100, -5, 5);
   
   PdfFile.AddPlotProfile(Tree, "PassPbPb100:J60PFPUPT", "JetIndex == 0 && PassPbPb60", "prof",
      "PbPb100 turn on relative to PbPb60;PT;", 100, 0, 250);
   PdfFile.AddPlotProfile(Tree, "PassPbPb100:J60PFPUPT", "JetIndex == 0 && PassPbPb60 && abs(J60Eta) < 1.5", "prof",
      "PbPb100 turn on relative to PbPb60 (eta < 1.5);PT;", 100, 0, 250);
   PdfFile.AddPlotProfile2D(Tree, "PassPbPb100:J60PFPUPT:J60PFPUEta",
      "JetIndex == 0 && PassPbPb60", "prof2d colz",
      "PbPb100 turn on relative to PbPb60;eta;PT", 50, -3.2, 3.2, 50, 0, 300);


   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}








