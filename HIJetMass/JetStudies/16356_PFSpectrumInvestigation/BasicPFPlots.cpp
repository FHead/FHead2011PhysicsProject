#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraph.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

using namespace std;

class Histogram;
class Histograms;
int main();
double GetDR(double Eta1, double Phi1, double Eta2, double Phi2);
void AddComparisonPlot(PdfFileHelper &PdfFile, TH1D *HPPOriginal, TH1D *HPPHIRecoOriginal, TH1D *HAAOriginal,
   string Title, bool LogY);

class Histogram
{
public:
   TH1D *HN;
   TH1D *HPT;
public:
   Histogram(string Tag)
      : HN(NULL), HPT(NULL)
   {
      HN = new TH1D(Form("HN_%s", Tag.c_str()), "Multiplicity", 30, 0, 30);
      HPT = new TH1D(Form("HPT_%s", Tag.c_str()), "PT Distribution", 50, 0, 100);

      HN->Sumw2();
      HPT->Sumw2();
   }
   ~Histogram()
   {
      if(HN != NULL)    delete HN;
      if(HPT != NULL)   delete HPT;
   }
};

class Histograms
{
public:
   vector<double> Radii;
   vector<Histogram *> IDAll;
   vector<Histogram *> ID1;
   double JetCount;
public:
   Histograms(string Tag)
   {
      Radii.push_back(0.10);
      Radii.push_back(0.20);
      Radii.push_back(0.30);
      Radii.push_back(0.40);
      Radii.push_back(0.50);
      Radii.push_back(0.60);

      for(int i = 0; i < (int)Radii.size(); i++)
      {
         IDAll.push_back(new Histogram(Tag + Form("_%03d", int(Radii[i] * 100))));
         ID1.push_back(new Histogram(Tag + Form("_%03dID1", int(Radii[i] * 100))));
      }
      
      JetCount = 0;
   }
   ~Histograms()
   {
      for(int i = 0; i < (int)IDAll.size(); i++)
         if(IDAll[i] != NULL)
            delete IDAll[i];
      
      for(int i = 0; i < (int)ID1.size(); i++)
         if(ID1[i] != NULL)
            delete ID1[i];
   }
   void Fill(double CEta, double CPhi, int N, double PT[], double Eta[], double Phi[], int ID[])
   {
      for(int iR = 0; iR < (int)Radii.size(); iR++)
      {
         int Count = 0;
         int CountID1 = 0;

         for(int i = 0; i < N; i++)
         {
            double DR = GetDR(CEta, CPhi, Eta[i], Phi[i]);

            if(DR > Radii[iR])
               continue;
            if(iR > 0 && DR <= Radii[iR-1])
               continue;

            Count = Count + 1;
            if(ID[i] == 1)
               CountID1 = Count + 1;

            IDAll[iR]->HPT->Fill(PT[i]);
            if(ID[i] == 1)
               ID1[iR]->HPT->Fill(PT[i]);
         }

         IDAll[iR]->HN->Fill(Count);
         ID1[iR]->HN->Fill(CountID1);
      }

      JetCount = JetCount + 1;
   }
   void Normalize()
   {
      for(int iR = 0; iR < (int)Radii.size(); iR++)
      {
         IDAll[iR]->HN->Scale(1 / JetCount);
         IDAll[iR]->HPT->Scale(1 / JetCount);
         
         ID1[iR]->HN->Scale(1 / JetCount);
         ID1[iR]->HPT->Scale(1 / JetCount);
      }
   }
};

int main()
{
   SetThesisStyle();

   Histograms HPP("PP");
   Histograms HPPHIReco("PPHIReco");
   Histograms HAA("AA");

   TFile FPP("PP.root");
   TFile FPPHIReco("PP6Dijet220HIReco.root");
   TFile FAA("AA.root");

   TTree *TPP = (TTree *)FPP.Get("T");
   TTree *TPPHIReco = (TTree *)FPPHIReco.Get("T");
   TTree *TAA = (TTree *)FAA.Get("T");

   double JetEta, JetPhi, JetPT;
   int PFCount;
   double PFPT[1000];
   double PFEta[1000];
   double PFPhi[1000];
   int PFID[1000];
   double Centrality;

   TPP->SetBranchAddress("JetEta", &JetEta);
   TPP->SetBranchAddress("JetPhi", &JetPhi);
   TPP->SetBranchAddress("MatchPT", &JetPT);
   TPP->SetBranchAddress("PFCount", &PFCount);
   TPP->SetBranchAddress("PFPT", &PFPT);
   TPP->SetBranchAddress("PFEta", &PFEta);
   TPP->SetBranchAddress("PFPhi", &PFPhi);
   TPP->SetBranchAddress("PFID", &PFID);
   
   TPPHIReco->SetBranchAddress("JetEta", &JetEta);
   TPPHIReco->SetBranchAddress("JetPhi", &JetPhi);
   TPPHIReco->SetBranchAddress("MatchPT", &JetPT);
   TPPHIReco->SetBranchAddress("PFCount", &PFCount);
   TPPHIReco->SetBranchAddress("PFPT", &PFPT);
   TPPHIReco->SetBranchAddress("PFEta", &PFEta);
   TPPHIReco->SetBranchAddress("PFPhi", &PFPhi);
   TPPHIReco->SetBranchAddress("PFID", &PFID);
   
   TAA->SetBranchAddress("JetEta", &JetEta);
   TAA->SetBranchAddress("JetPhi", &JetPhi);
   TAA->SetBranchAddress("MatchPT", &JetPT);
   TAA->SetBranchAddress("PFCount", &PFCount);
   TAA->SetBranchAddress("PFPT", &PFPT);
   TAA->SetBranchAddress("PFEta", &PFEta);
   TAA->SetBranchAddress("PFPhi", &PFPhi);
   TAA->SetBranchAddress("PFID", &PFID);
   TAA->SetBranchAddress("Centrality", &Centrality);

   int EntryCount;

   EntryCount = TPP->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      TPP->GetEntry(iE);
      if(JetPT > 200)
         HPP.Fill(JetEta, JetPhi, PFCount, PFPT, PFEta, PFPhi, PFID);
   }
   
   EntryCount = TPPHIReco->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      TPPHIReco->GetEntry(iE);
      if(JetPT > 200)
         HPPHIReco.Fill(JetEta, JetPhi, PFCount, PFPT, PFEta, PFPhi, PFID);
   }
   
   EntryCount = TAA->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      TAA->GetEntry(iE);
      if(JetPT > 200 && Centrality > 0.85)
         HAA.Fill(JetEta, JetPhi, PFCount, PFPT, PFEta, PFPhi, PFID);
   }

   HPP.Normalize();
   HPPHIReco.Normalize();
   HAA.Normalize();

   PdfFileHelper PdfFile("PFCandidatePlots.pdf");
   PdfFile.AddTextPage("PF Candidates");
   
   PdfFileHelper PdfFilePP("PFCandidatePlotsPP.pdf");
   PdfFileHelper PdfFilePPHIReco("PFCandidatePlotsPPHIReco.pdf");
   PdfFileHelper PdfFileAA("PFCandidatePlotsAA.pdf");
   PdfFilePP.AddTextPage("PF Candidates (PP)");
   PdfFilePPHIReco.AddTextPage("PF Candidates (PPHIReco)");
   PdfFileAA.AddTextPage("PF Candidates (AA)");

   for(int i = 0; i < (int)HPP.Radii.size(); i++)
   {
      double OuterRadius = HPP.Radii[i];
      double InnerRadius = ((i == 0) ? 0 : HPP.Radii[i-1]);

      PdfFilePP.AddTextPage(Form("Radius = %.2f-%.2f", InnerRadius, OuterRadius));

      PdfFilePP.AddPlot(HPP.IDAll[i]->HN);
      PdfFilePP.AddPlot(HPP.IDAll[i]->HPT);
      PdfFilePP.AddPlot(HPP.ID1[i]->HN);
      PdfFilePP.AddPlot(HPP.ID1[i]->HPT);
      
      PdfFilePPHIReco.AddTextPage(Form("Radius = %.2f-%.2f", InnerRadius, OuterRadius));

      PdfFilePPHIReco.AddPlot(HPPHIReco.IDAll[i]->HN);
      PdfFilePPHIReco.AddPlot(HPPHIReco.IDAll[i]->HPT);
      PdfFilePPHIReco.AddPlot(HPPHIReco.ID1[i]->HN);
      PdfFilePPHIReco.AddPlot(HPPHIReco.ID1[i]->HPT);
      
      PdfFileAA.AddTextPage(Form("Radius = %.2f-%.2f", InnerRadius, OuterRadius));
      
      PdfFileAA.AddPlot(HAA.IDAll[i]->HN);
      PdfFileAA.AddPlot(HAA.IDAll[i]->HPT);
      PdfFileAA.AddPlot(HAA.ID1[i]->HN);
      PdfFileAA.AddPlot(HAA.ID1[i]->HPT);

      PdfFile.AddTextPage(Form("Radius = %.2f-%.2f", InnerRadius, OuterRadius));

      AddComparisonPlot(PdfFile, HPP.IDAll[i]->HN,  HPPHIReco.IDAll[i]->HN,  HAA.IDAll[i]->HN,  "Multiplicity", false);
      AddComparisonPlot(PdfFile, HPP.ID1[i]->HN,    HPPHIReco.ID1[i]->HN,    HAA.ID1[i]->HN,    "Multiplicity, ID = 1", false);
      AddComparisonPlot(PdfFile, HPP.IDAll[i]->HPT, HPPHIReco.IDAll[i]->HPT, HAA.IDAll[i]->HPT, "PT Distribution", false);
      AddComparisonPlot(PdfFile, HPP.ID1[i]->HPT,   HPPHIReco.ID1[i]->HPT,   HAA.ID1[i]->HPT,   "PT Distribution, ID = 1", false);
      AddComparisonPlot(PdfFile, HPP.IDAll[i]->HPT, HPPHIReco.IDAll[i]->HPT, HAA.IDAll[i]->HPT, "PT Distribution", true);
      AddComparisonPlot(PdfFile, HPP.ID1[i]->HPT,   HPPHIReco.ID1[i]->HPT,   HAA.ID1[i]->HPT,   "PT Distribution, ID = 1", true);
   }

   PdfFileAA.AddTimeStampPage();
   PdfFilePPHIReco.AddTimeStampPage();
   PdfFilePP.AddTimeStampPage();
   PdfFileAA.Close();
   PdfFilePPHIReco.Close();
   PdfFilePP.Close();
   
   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   FAA.Close();
   FPPHIReco.Close();
   FPP.Close();

   return 0;
}

double GetDR(double Eta1, double Phi1, double Eta2, double Phi2)
{
   double DEta = Eta1 - Eta2;
   double DPhiX = cos(Phi1 - Phi2);
   double DPhiY = sin(Phi1 - Phi2);
   double DPhi = acos(DPhiX);
   if(DPhiY < 0)
      DPhi = -DPhi;

   return sqrt(DEta * DEta + DPhi * DPhi);
}

void AddComparisonPlot(PdfFileHelper &PdfFile, TH1D *HPPOriginal, TH1D *HPPHIRecoOriginal, TH1D *HAAOriginal,
   string Title, bool LogY)
{
   TH1D *HPP       = (TH1D *)HPPOriginal->Clone("HPP");
   TH1D *HPPHIReco = (TH1D *)HPPHIRecoOriginal->Clone("HPPHIReco");
   TH1D *HAA       = (TH1D *)HAAOriginal->Clone("HAA");

   if(LogY == false)
   {
      HPP->SetMaximum(max(max(HPP->GetMaximum(), HAA->GetMaximum()), HPPHIReco->GetMaximum()) * 1.2);
      HPP->SetMinimum(0);
   }
   else
   {
      HPP->SetMaximum(max(max(HPP->GetMaximum(), HAA->GetMaximum()), HPPHIReco->GetMaximum()) * 3);
      HPP->SetMinimum(HPP->GetMaximum() * 1e-4);
   }

   HPP->SetLineColor(kBlue);
   HPPHIReco->SetLineColor(kGreen);
   HAA->SetLineColor(kRed);

   HPP->SetMarkerColor(kBlue);
   HPPHIReco->SetMarkerColor(kGreen);
   HAA->SetMarkerColor(kRed);

   HPP->SetStats(0);
   HPPHIReco->SetStats(0);
   HAA->SetStats(0);

   HPP->SetTitle(Title.c_str());
   HPPHIReco->SetTitle(Title.c_str());
   HAA->SetTitle(Title.c_str());

   TCanvas C;

   HPP->Draw();
   HPPHIReco->Draw("same");
   HAA->Draw("same");

   TLegend Legend(0.65, 0.80, 0.85, 0.60);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(HPP, "PP" ,"lp");
   Legend.AddEntry(HPPHIReco, "PP (HI)" ,"lp");
   Legend.AddEntry(HAA, "AA" ,"lp");
   Legend.Draw();

   if(LogY == true)
      C.SetLogy();

   PdfFile.AddCanvas(C);

   C.SetLogy(false);

   HAA->Divide(HPPHIReco);

   HAA->GetYaxis()->SetTitle("AA / PP (HI)");

   HAA->Draw();
   HAA->SetMinimum(0);
   HAA->SetMaximum(2);

   TGraph G;
   G.SetPoint(0, 0, 1);
   G.SetPoint(1, 10000, 1);
   G.Draw("l");

   PdfFile.AddCanvas(C);

   delete HPP;
   delete HAA;
}



