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
void AddPlot(PdfFileHelper &PdfFile, TTree *TAA, TTree *TPP, TTree *TA2, int IDType, double PTMin);
void FillPlot(TTree *Tree, int SampleType, int IDType, double PFPTMin, TH1D &HN, TH1D &HE);
double GetDR(double eta1, double phi1, double eta2, double phi2);

int main()
{
   SetThesisStyle();

   TFile FAA("Samples/AA6Dijet220.root");
   TFile FA2("Samples/AA6Dijet220Cymbal.root");
   TFile FPP("Samples/PP6Dijet220.root");
   
   TTree *TAA = (TTree *)FAA.Get("T");
   TTree *TA2 = (TTree *)FA2.Get("T");
   TTree *TPP = (TTree *)FPP.Get("T");

   PdfFileHelper PdfFile("DRPlots.pdf");
   PdfFile.AddTextPage("PF Candidate DR Plots");

   AddPlot(PdfFile, TAA, TPP, TA2, ID_All, 0.0);
   AddPlot(PdfFile, TAA, TPP, TA2, ID_All, 0.5);
   AddPlot(PdfFile, TAA, TPP, TA2, ID_All, 1.5);
   AddPlot(PdfFile, TAA, TPP, TA2, ID_All, 5.0);
   AddPlot(PdfFile, TAA, TPP, TA2, ID_One, 0.0);
   AddPlot(PdfFile, TAA, TPP, TA2, ID_One, 1.5);
   AddPlot(PdfFile, TAA, TPP, TA2, ID_One, 5.0);
   AddPlot(PdfFile, TAA, TPP, TA2, ID_Other, 0.0);
   AddPlot(PdfFile, TAA, TPP, TA2, ID_Other, 1.5);
   AddPlot(PdfFile, TAA, TPP, TA2, ID_Other, 5.0);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
   
   FAA.Close();
   FPP.Close();
   FA2.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TTree *TAA, TTree *TPP, TTree *TA2, int IDType, double PTMin)
{
   string JetSelection = "Jet PT > 150 && Jet |Eta| < 1";
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

   if(TPP == NULL || TAA == NULL || TA2 == NULL)
      return;

   TH1D HPP("HPP", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d N_{PF}}{d DR}", 40, 0.0, 0.5);
   TH1D HA2("HA2", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d N_{PF}}{d DR}", 40, 0.0, 0.5);
   TH1D HAA("HAA", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d N_{PF}}{d DR}", 40, 0.0, 0.5);
   
   TH1D HPPE("HPPE", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d #Sigma p_{T}}{d DR}", 40, 0.0, 0.5);
   TH1D HA2E("HA2E", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d #Sigma p_{T}}{d DR}", 40, 0.0, 0.5);
   TH1D HAAE("HAAE", ";DR(PF Candidate, Jet);#frac{1}{N_{Jet}} #frac{d #Sigma p_{T}}{d DR}", 40, 0.0, 0.5);
   
   TH1D HNAA("HNAA", "", 1000, -1000, 1000);

   HPP.Sumw2();
   HA2.Sumw2();
   HAA.Sumw2();
   
   TCanvas Canvas;

   FillPlot(TPP, Sample_PP, IDType, PTMin, HPP, HPPE);
   FillPlot(TA2, Sample_AA, IDType, PTMin, HA2, HA2E);
   FillPlot(TAA, Sample_AA, IDType, PTMin, HAA, HAAE);

   double BinSize = (0.6 - 0.0) / 100;

   HPP.SetTitle("");
   HPP.SetStats(0);
   HPPE.SetTitle("");
   HPPE.SetStats(0);

   HAA.Scale(1 / BinSize);
   HPP.Scale(1 / BinSize);
   HA2.Scale(1 / BinSize);
   HAAE.Scale(1 / BinSize);
   HPPE.Scale(1 / BinSize);
   HA2E.Scale(1 / BinSize);

   HPP.SetMaximum(max(HPP.GetMaximum(), max(HAA.GetMaximum(), HA2.GetMaximum())) * 1.2);
   HPP.SetMinimum(0);
   HPPE.SetMaximum(max(HPPE.GetMaximum(), max(HAAE.GetMaximum(), HA2E.GetMaximum())) * 1.2);
   HPPE.SetMinimum(0);
   
   HAA.SetLineColor(2);
   HPP.SetLineColor(4);
   HA2.SetLineColor(3);
   HAAE.SetLineColor(2);
   HPPE.SetLineColor(4);
   HA2E.SetLineColor(3);
   
   HAA.SetMarkerColor(2);
   HPP.SetMarkerColor(4);
   HA2.SetMarkerColor(3);
   HAAE.SetMarkerColor(2);
   HPPE.SetMarkerColor(4);
   HA2E.SetMarkerColor(3);
   
   HAA.SetMarkerStyle(20);
   HPP.SetMarkerStyle(20);
   HA2.SetMarkerStyle(20);
   HAAE.SetMarkerStyle(20);
   HPPE.SetMarkerStyle(20);
   HA2E.SetMarkerStyle(20);

   TLegend Legend(0.45, 0.80, 0.75, 0.55);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HPP, "PP (pp reco)", "pl");
   Legend.AddEntry(&HAA, "PbPb (Drum)", "pl");
   Legend.AddEntry(&HA2, "PbPb (Cymbal)", "pl");
   Legend.AddEntry("", "", "");

   HPP.Draw();
   HAA.Draw("same");
   HA2.Draw("same");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   HPPE.Draw();
   HAAE.Draw("same");
   HA2E.Draw("same");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
   
   HPPE.SetMinimum(0.5);
   HPPE.SetMaximum(HPPE.GetMaximum() * 10);

   HPPE.Draw();
   HAAE.Draw("same");
   HA2E.Draw("same");
   Legend.Draw();

   Canvas.SetLogy();

   PdfFile.AddCanvas(Canvas);

   HAAE.Divide(&HPPE);
   HA2E.Divide(&HPPE);
   HPPE.Divide(&HPPE);

   HPPE.Draw("hist");
   HAAE.Draw("same");
   HA2E.Draw("same");

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
   double JetRawPT;
   double JetPT;
   double JetEta;
   double JetPhi;
   int PFCount;
   double PFPT[1000];
   double PFEta[1000];
   double PFPhi[1000];
   int PFID[1000];

   Tree->SetBranchAddress("Centrality", &Centrality);
   Tree->SetBranchAddress("JetPT", &JetRawPT);
   Tree->SetBranchAddress("JetCSPT", &JetPT);
   Tree->SetBranchAddress("JetCSEta", &JetEta);
   Tree->SetBranchAddress("JetCSPhi", &JetPhi);
   Tree->SetBranchAddress("PFCount", &PFCount);
   Tree->SetBranchAddress("PFPT", &PFPT);
   Tree->SetBranchAddress("PFEta", &PFEta);
   Tree->SetBranchAddress("PFPhi", &PFPhi);
   Tree->SetBranchAddress("PFID", &PFID);

   double JetCount = 0;

   int EntryCount = Tree->GetEntries() / 10;
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(SampleType == Sample_AA || SampleType == Sample_MB)
         if(Centrality < 0.5 || Centrality > 0.7)
            continue;
      // f(SampleType == Sample_AA || SampleType == Sample_MB)
      //   if(Centrality < 0.0 || Centrality > 0.1)
      //      continue;

      if(SampleType == Sample_AA || SampleType == Sample_PP || SampleType == Sample_PPHIReco)
         if(JetEta < -1 || JetEta > 1 || JetPT < 150)
            continue;

      if(JetPT / JetRawPT < 0.8)
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



