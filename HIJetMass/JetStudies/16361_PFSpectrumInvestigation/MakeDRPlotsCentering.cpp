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
#include "Code/TauHelperFunctions3.h"
#include "Code/DrawRandom.h"

#define ID_One 0
#define ID_Other 1
#define ID_All 2

#define Sample_AA 0
#define Sample_PP 1
#define Sample_PPHIReco 2
#define Sample_MB 3

int main();
void AddPlot(PdfFileHelper &PdfFile, TTree *TAA, TTree *TPP, TTree *TP2, TTree *TMB, int IDType, double PTMin);
void FillPlot(TTree *Tree, int SampleType, int IDType, double PFPTMin, TH1D &HN, TH1D &HE);
double GetDR(double eta1, double phi1, double eta2, double phi2);

int main()
{
   SetThesisStyle();

   // TFile FAA("AA.root");
   // TFile FPP("PP.root");
   // TFile FP2("PP6Dijet220HIReco.root");
   // TFile FMB("MBCymbal.root");
   
   TFile FAA("AA8Dijet.root");
   TFile FPP("PP8Dijet.root");
   TFile FP2("PP6Dijet220HIReco.root");
   TFile FMB("MBHydjet.root");
   
   // TFile FAA("AAData.root");
   // TFile FPP("PPData.root");
   // TFile FP2("PP6Dijet220HIReco.root");
   // TFile FMB("AADataMB.root");

   TTree *TAA = (TTree *)FAA.Get("T");
   TTree *TPP = (TTree *)FPP.Get("T");
   TTree *TP2 = (TTree *)FP2.Get("T");
   TTree *TMB = (TTree *)FMB.Get("T");

   TMB->SetAlias("JetEta", "(rndm * 2 - 1)");
   TMB->SetAlias("JetPhi", "(rndm * 2 * 3.145926535)");
   TMB->SetAlias("JetPT", "(110+120)");

   /*
   TMB->SetAlias("DEta", "(JetEta-Eta)");
   TMB->SetAlias("DPhiX", "cos(JetPhi-Phi)");
   TMB->SetAlias("DPhiY", "sin(JetPhi-Phi)");
   TMB->SetAlias("DPhi", "(acos(DPhiX)*(1-2*(DPhiY<0)))");
   TMB->SetAlias("DR", "sqrt(DEta*DEta+DPhi*DPhi)");
   
   TMB->SetAlias("PFPT", "PT");
   TMB->SetAlias("PFID", "ID");
   */
   
   TMB->SetAlias("DEta", "(JetEta-PFEta)");
   TMB->SetAlias("DPhiX", "cos(JetPhi-PFPhi)");
   TMB->SetAlias("DPhiY", "sin(JetPhi-PFPhi)");
   TMB->SetAlias("DPhi", "(acos(DPhiX)*(1-2*(DPhiY<0)))");
   TMB->SetAlias("DR", "sqrt(DEta*DEta+DPhi*DPhi)");

   PdfFileHelper PdfFile("DRPlots.pdf");
   PdfFile.AddTextPage("PF Candidate DR Plots");

   AddPlot(PdfFile, TAA, TPP, TP2, TMB, ID_All, 0.0);
   // AddPlot(PdfFile, TAA, TPP, TP2, TMB, ID_All, 0.5);
   // AddPlot(PdfFile, TAA, TPP, TP2, TMB, ID_All, 1.5);
   // AddPlot(PdfFile, TAA, TPP, TP2, TMB, ID_All, 5.0);
   AddPlot(PdfFile, TAA, TPP, TP2, TMB, ID_One, 0.0);
   // AddPlot(PdfFile, TAA, TPP, TP2, TMB, ID_One, 1.5);
   // AddPlot(PdfFile, TAA, TPP, TP2, TMB, ID_One, 5.0);
   AddPlot(PdfFile, TAA, TPP, TP2, TMB, ID_Other, 0.0);
   // AddPlot(PdfFile, TAA, TPP, TP2, TMB, ID_Other, 1.5);
   // AddPlot(PdfFile, TAA, TPP, TP2, TMB, ID_Other, 5.0);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
   
   FAA.Close();
   FPP.Close();
   FP2.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TTree *TAA, TTree *TPP, TTree *TP2, TTree *TMB, int IDType, double PTMin)
{
   string JetSelection = "abs(JetEta) < 1.0 && JetPT > 150";
   string PFSelection;

   if(IDType == ID_All)
      PFSelection = Form("PFID > 0 && PFPT > %f", PTMin);
   if(IDType == ID_One)
      PFSelection = Form("PFID == 1 && PFPT > %f", PTMin);
   if(IDType == ID_Other)
      PFSelection = Form("PFID != 1 && PFPT > %f", PTMin);

   vector<string> Selections(10);
   Selections[0] = "Selection:";
   Selections[1] = "   Jet: " + JetSelection;
   Selections[2] = "   PF: " + PFSelection;
   PdfFile.AddTextPage(Selections);

   if(TPP == NULL || TAA == NULL || TP2 == NULL || TMB == NULL)
      return;

   // string CentralitySelection = "Centrality > 0.8";
   string CentralitySelection = "Centrality > 0.5 && Centrality < 0.8";

   TH1D HPP("HPP", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d N_{PF}}{d DR}", 40, 0.0, 0.5);
   TH1D HP2("HP2", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d N_{PF}}{d DR}", 40, 0.0, 0.5);
   TH1D HAA("HAA", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d N_{PF}}{d DR}", 40, 0.0, 0.5);
   TH1D HMB("HMB", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d N_{PF}}{d DR}", 40, 0.0, 0.5);
   
   TH1D HPPE("HPPE", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d #Sigma p_{T}}{d DR}", 40, 0.0, 0.5);
   TH1D HP2E("HP2E", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d #Sigma p_{T}}{d DR}", 40, 0.0, 0.5);
   TH1D HAAE("HAAE", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d #Sigma p_{T}}{d DR}", 40, 0.0, 0.5);
   TH1D HMBE("HMBE", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d #Sigma p_{T}}{d DR}", 40, 0.0, 0.5);
   
   TH1D HNAA("HNAA", "", 1000, -1000, 1000);
   TH1D HNMB("HNMB", "", 1000, -1000, 1000);

   HPP.Sumw2();
   HP2.Sumw2();
   HAA.Sumw2();
   HMB.Sumw2();
   
   TCanvas Canvas;

   FillPlot(TPP, Sample_PP,       IDType, PTMin, HPP, HPPE);
   FillPlot(TP2, Sample_PPHIReco, IDType, PTMin, HP2, HP2E);
   FillPlot(TAA, Sample_AA,       IDType, PTMin, HAA, HAAE);

   TMB->Draw("DR>>HMB",  ("       (" + JetSelection + " && " + PFSelection + " && " + CentralitySelection + ")").c_str(), "", 5000);
   TMB->Draw("DR>>HMBE", ("PFPT * (" + JetSelection + " && " + PFSelection + " && " + CentralitySelection + ")").c_str(), "", 5000);
   TMB->Draw("1>>HNMB",  ("       (" + JetSelection +                        " && " + CentralitySelection + ")").c_str(), "", 5000);

   double BinSize = (0.6 - 0.0) / 100;

   HPP.SetTitle("");
   HPP.SetStats(0);
   HPPE.SetTitle("");
   HPPE.SetStats(0);

   HAA.Scale(1 / BinSize);
   HPP.Scale(1 / BinSize);
   HP2.Scale(1 / BinSize);
   HMB.Scale(1.0 / HNMB.GetEntries() / BinSize);
   HAAE.Scale(1 / BinSize);
   HPPE.Scale(1 / BinSize);
   HP2E.Scale(1 / BinSize);
   HMBE.Scale(1.0 / HNMB.GetEntries() / BinSize);

   HMB.Scale(0.5);
   HMBE.Scale(0.5);

   HPP.SetMaximum(max(max(HPP.GetMaximum(), HMB.GetMaximum()), max(HAA.GetMaximum(), HP2.GetMaximum())) * 1.2);
   HPP.SetMinimum(0);
   HPPE.SetMaximum(max(max(HPPE.GetMaximum(), HMBE.GetMaximum()), max(HAAE.GetMaximum(), HP2E.GetMaximum())) * 1.2);
   HPPE.SetMinimum(0);
   
   HAA.SetLineColor(2);
   HPP.SetLineColor(4);
   HP2.SetLineColor(3);
   HMB.SetLineColor(6);
   HAAE.SetLineColor(2);
   HPPE.SetLineColor(4);
   HP2E.SetLineColor(3);
   HMBE.SetLineColor(6);
   
   HAA.SetMarkerColor(2);
   HPP.SetMarkerColor(4);
   HP2.SetMarkerColor(3);
   HMB.SetMarkerColor(6);
   HAAE.SetMarkerColor(2);
   HPPE.SetMarkerColor(4);
   HP2E.SetMarkerColor(3);
   HMBE.SetMarkerColor(6);
   
   HAA.SetMarkerStyle(20);
   HPP.SetMarkerStyle(20);
   HP2.SetMarkerStyle(20);
   HMB.SetMarkerStyle(20);
   HAAE.SetMarkerStyle(20);
   HPPE.SetMarkerStyle(20);
   HP2E.SetMarkerStyle(20);
   HMBE.SetMarkerStyle(20);

   TLegend Legend(0.45, 0.80, 0.75, 0.55);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HAA, "PbPb, 50-70%", "pl");
   Legend.AddEntry(&HPP, "PP", "pl");
   Legend.AddEntry(&HP2, "PP (HI Reco)", "pl");
   Legend.AddEntry(&HMB, "MB, 50-70%", "pl");

   HPP.Draw();
   HAA.Draw("same");
   HP2.Draw("same");
   HMB.Draw("same");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   HPPE.Draw();
   HAAE.Draw("same");
   HP2E.Draw("same");
   HMBE.Draw("same");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
   
   HPPE.SetMinimum(0.5);
   HPPE.SetMaximum(HPPE.GetMaximum() * 10);

   HPPE.Draw();
   HAAE.Draw("same");
   HP2E.Draw("same");
   HMBE.Draw("same");
   Legend.Draw();

   Canvas.SetLogy();

   PdfFile.AddCanvas(Canvas);

   HAAE.Divide(&HPPE);
   HP2E.Divide(&HPPE);
   HMBE.Divide(&HPPE);
   HPPE.Divide(&HPPE);

   HPPE.Draw("hist");
   HAAE.Draw("same");
   HP2E.Draw("same");
   HMBE.Draw("same");

   HPPE.SetMinimum(0);
   HPPE.SetMaximum(2);

   HPPE.GetYaxis()->SetTitle("Energy ratio over PP");

   Canvas.SetLogy(false);

   PdfFile.AddCanvas(Canvas);
}

void FillPlot(TTree *Tree, int SampleType, int IDType, double PFPTMin, TH1D &HN, TH1D &HE)
{
   if(Tree == NULL)
      return;

   double Centrality;
   double JetPT;
   double JetEta;
   double JetPhi;
   int PFCount;
   double PFPT[1000];
   double PFEta[1000];
   double PFPhi[1000];
   int PFID[1000];

   Tree->SetBranchAddress("Centrality", &Centrality);
   Tree->SetBranchAddress("JetPT", &JetPT);
   Tree->SetBranchAddress("JetEta", &JetEta);
   Tree->SetBranchAddress("JetPhi", &JetPhi);
   Tree->SetBranchAddress("PFCount", &PFCount);
   Tree->SetBranchAddress("PFPT", &PFPT);
   Tree->SetBranchAddress("PFEta", &PFEta);
   Tree->SetBranchAddress("PFPhi", &PFPhi);
   Tree->SetBranchAddress("PFID", &PFID);

   double JetCount = 0;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(SampleType == Sample_AA || SampleType == Sample_MB)
         if(Centrality < 0.5 || Centrality > 0.7)
            continue;

      if(SampleType == Sample_AA || SampleType == Sample_PP || SampleType == Sample_PPHIReco)
         if(JetEta < -1 || JetEta > 1 || JetPT < 150)
            continue;

      JetCount = JetCount + 1;

      double ReferenceEta = JetEta;
      double ReferencePhi = JetPhi;

      /*
      int BestID = 0;
      double BestPT = -1;
      for(int iPF = 0; iPF < PFCount; iPF++)
      {
         if(BestPT < 0 || BestPT < PFPT[iPF])
         {
            BestID = iPF;
            BestPT = PFPT[iPF];
         }
      }
      ReferenceEta = PFEta[BestID];
      ReferencePhi = PFPhi[BestID];
      */

      FourVector TotalP;
      for(int iPF = 0; iPF < PFCount; iPF++)
      {
         double DR = GetDR(JetEta, JetPhi, PFEta[iPF], PFPhi[iPF]);
         if(DR < 0.15)
         {
            FourVector P;
            P.SetPtEtaPhi(PFPT[iPF], PFEta[iPF], PFPhi[iPF]);
            TotalP = TotalP + P;
         }
      }
      ReferenceEta = TotalP.GetEta();
      ReferencePhi = TotalP.GetPhi();

      for(int iPF = 0; iPF < PFCount; iPF++)
      {
         if(IDType == ID_One && PFID[iPF] != 1)
            continue;
         if(IDType == ID_Other && PFID[iPF] == 1)
            continue;
         if(PFPT[iPF] < PFPTMin)
            continue;

         double DR = GetDR(ReferenceEta, ReferencePhi, PFEta[iPF], PFPhi[iPF]);

         HN.Fill(DR, 1);
         HE.Fill(DR, PFPT[iPF]);
      }
   }

   HN.Scale(1 / JetCount);
   HE.Scale(1 / JetCount);
}

double GetDR(double eta1, double phi1, double eta2, double phi2)
{
   double deta = eta1 - eta2;
   double dphix = cos(phi1 - phi2);
   double dphiy = sin(phi1 - phi2);
   double dphi = acos(dphix) * (1 - 2 * (dphiy < 0));

   return sqrt(deta * deta + dphi * dphi);
}



