#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main();
void AddPlot(PdfFileHelper &PdfFile, TTree *TAA, TTree *TPP, TTree *TP2, TTree *TMB, string JetSelection, string PFSelection);

int main()
{
   SetThesisStyle();

   TFile FAA("AA.root");
   TFile FPP("PP.root");
   TFile FP2("PP6Dijet220HIReco.root");
   TFile FMB("MBCymbal.root");

   TTree *TAA = (TTree *)FAA.Get("T");
   TTree *TPP = (TTree *)FPP.Get("T");
   TTree *TP2 = (TTree *)FP2.Get("T");
   TTree *TMB = (TTree *)FMB.Get("Tree");

   TAA->SetAlias("DEta", "(JetEta-PFEta)");
   TAA->SetAlias("DPhiX", "cos(JetPhi-PFPhi)");
   TAA->SetAlias("DPhiY", "sin(JetPhi-PFPhi)");
   TAA->SetAlias("DPhi", "(acos(DPhiX)*(1-2*(DPhiY<0)))");
   TAA->SetAlias("DR", "sqrt(DEta*DEta+DPhi*DPhi)");

   TPP->SetAlias("DEta", "(JetEta-PFEta)");
   TPP->SetAlias("DPhiX", "cos(JetPhi-PFPhi)");
   TPP->SetAlias("DPhiY", "sin(JetPhi-PFPhi)");
   TPP->SetAlias("DPhi", "(acos(DPhiX)*(1-2*(DPhiY<0)))");
   TPP->SetAlias("DR", "sqrt(DEta*DEta+DPhi*DPhi)");

   TP2->SetAlias("DEta", "(JetEta-PFEta)");
   TP2->SetAlias("DPhiX", "cos(JetPhi-PFPhi)");
   TP2->SetAlias("DPhiY", "sin(JetPhi-PFPhi)");
   TP2->SetAlias("DPhi", "(acos(DPhiX)*(1-2*(DPhiY<0)))");
   TP2->SetAlias("DR", "sqrt(DEta*DEta+DPhi*DPhi)");

   TMB->SetAlias("JetEta", "(rndm * 2 - 1)");
   TMB->SetAlias("JetPhi", "(rndm * 2 * 3.145926535)");
   TMB->SetAlias("JetPT", "(10000+10000)");

   TMB->SetAlias("DEta", "(JetEta-Eta)");
   TMB->SetAlias("DPhiX", "cos(JetPhi-Phi)");
   TMB->SetAlias("DPhiY", "sin(JetPhi-Phi)");
   TMB->SetAlias("DPhi", "(acos(DPhiX)*(1-2*(DPhiY<0)))");
   TMB->SetAlias("DR", "sqrt(DEta*DEta+DPhi*DPhi)");
   
   TMB->SetAlias("PFPT", "PT");
   TMB->SetAlias("PFID", "ID");

   PdfFileHelper PdfFile("DRPlots.pdf");
   PdfFile.AddTextPage("PF Candidate DR Plots");

   AddPlot(PdfFile, TAA, TPP, TP2, TMB, "abs(JetEta) < 1.0 && JetPT > 250", "PFID > 0 && PFPT > 0.0");
   AddPlot(PdfFile, TAA, TPP, TP2, TMB, "abs(JetEta) < 1.0 && JetPT > 250", "PFID > 0 && PFPT > 0.5");
   AddPlot(PdfFile, TAA, TPP, TP2, TMB, "abs(JetEta) < 1.0 && JetPT > 250", "PFID > 0 && PFPT > 1.5");
   AddPlot(PdfFile, TAA, TPP, TP2, TMB, "abs(JetEta) < 1.0 && JetPT > 250", "PFID == 1 && PFPT > 0.0");
   AddPlot(PdfFile, TAA, TPP, TP2, TMB, "abs(JetEta) < 1.0 && JetPT > 250", "PFID == 1 && PFPT > 1.5");
   AddPlot(PdfFile, TAA, TPP, TP2, TMB, "abs(JetEta) < 1.0 && JetPT > 250", "PFID != 1 && PFPT > 0.0");
   AddPlot(PdfFile, TAA, TPP, TP2, TMB, "abs(JetEta) < 1.0 && JetPT > 250", "PFID != 1 && PFPT > 1.5");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
   
   FAA.Close();
   FPP.Close();
   FP2.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TTree *TAA, TTree *TPP, TTree *TP2, TTree *TMB, string JetSelection, string PFSelection)
{
   vector<string> Selections(10);
   Selections[0] = "Selection:";
   Selections[1] = "   Jet: " + JetSelection;
   Selections[2] = "   PF: " + PFSelection;
   PdfFile.AddTextPage(Selections);

   if(TPP == NULL || TAA == NULL || TP2 == NULL || TMB == NULL)
      return;

   TH1D HPP("HPP", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d N_{PF}}{d DR}", 60, 0.0, 0.6);
   TH1D HP2("HP2", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d N_{PF}}{d DR}", 60, 0.0, 0.6);
   TH1D HAA("HAA", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d N_{PF}}{d DR}", 60, 0.0, 0.6);
   TH1D HMB("HMB", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d N_{PF}}{d DR}", 60, 0.0, 0.6);
   
   TH1D HNMB("HNMB", "", 1000, -1000, 1000);

   HPP.Sumw2();
   HP2.Sumw2();
   HAA.Sumw2();
   HMB.Sumw2();
   
   TCanvas Canvas;

   cout << "1" << endl;
   TPP->Draw("DR>>HPP", (JetSelection + " && " + PFSelection).c_str(),                          "error");
   cout << "2" << endl;
   TAA->Draw("DR>>HAA", (JetSelection + " && " + PFSelection + " && Centrality > 0.8").c_str(), "error");
   cout << "3" << endl;
   TP2->Draw("DR>>HP2", (JetSelection + " && " + PFSelection).c_str(),                          "error");
   cout << "4" << endl;
   TMB->Draw("DR>>HMB", (JetSelection + " && " + PFSelection + " && Centrality > 0.8").c_str(), "error", 10000);
   TMB->Draw("1>>HNMB", (JetSelection +                        " && Centrality > 0.8").c_str(), "error", 10000);
   cout << "5" << endl;

   double BinSize = (0.6 - 0.0) / 100;

   HPP.SetTitle("");
   HPP.SetStats(0);

   HAA.Scale(1.0 / TAA->GetEntries((JetSelection + " && Centrality > 0.8").c_str()) / BinSize);
   HPP.Scale(1.0 / TPP->GetEntries((JetSelection                         ).c_str()) / BinSize);
   HP2.Scale(1.0 / TP2->GetEntries((JetSelection                         ).c_str()) / BinSize);
   HMB.Scale(1.0 / HNMB.GetEntries()                                                / BinSize);

   HPP.SetMinimum(0);
   HPP.SetMaximum(max(max(HPP.GetMaximum(), HMB.GetMaximum()), max(HAA.GetMaximum(), HP2.GetMaximum())) * 1.2);
   
   HAA.SetLineColor(2);
   HPP.SetLineColor(4);
   HP2.SetLineColor(3);
   HMB.SetLineColor(6);
   
   HAA.SetMarkerColor(2);
   HPP.SetMarkerColor(4);
   HP2.SetMarkerColor(3);
   HMB.SetMarkerColor(6);
   
   HAA.SetMarkerStyle(20);
   HPP.SetMarkerStyle(20);
   HP2.SetMarkerStyle(20);
   HMB.SetMarkerStyle(20);

   TLegend Legend(0.45, 0.80, 0.75, 0.55);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HAA, "Embedded, 80-100%", "pl");
   Legend.AddEntry(&HPP, "PP", "pl");
   Legend.AddEntry(&HP2, "PP (HI Reco)", "pl");
   Legend.AddEntry(&HMB, "MB, 80-100%", "pl");

   HPP.Draw();
   HAA.Draw("same");
   HP2.Draw("same");
   HMB.Draw("same");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
}





