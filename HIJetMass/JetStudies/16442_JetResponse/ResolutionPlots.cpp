#include <iostream>
#include <vector>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"

#include "Code/TauHelperFunctions3.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

#include "BasicUtilities.h"

class Messenger;
class Histograms;
int main();

class Messenger
{
public:
   TFile *File;
   TTree *Tree;
   int Run, Event, Lumi;
   double Centrality, PTHat, Rho;
   bool Pass40, Pass60, Pass80, Pass100;
   int GenJetIndex;
   double GenJetPT, GenJetEta, GenJetPhi;
   double MatchJetRawPT, MatchJetEta, MatchJetPhi, MatchJetBestDR;
   double CSJetRawPT, CSJetPT, CSJetEta, CSJetPhi, CSJetBestDR;
   double CSJetRefPT, CSJetRefEta, CSJetRefPhi;
   int Flavor, FlavorB;
   int SD0Depth, SD7Depth;
   double SD0DR, SD7DR;
   double SD0Mass, SD7Mass;
   double SD0SubJet1E, SD0SubJet1PT, SD0SubJet1Eta, SD0SubJet1Phi;
   double SD0SubJet2E, SD0SubJet2PT, SD0SubJet2Eta, SD0SubJet2Phi;
   double SD7SubJet1E, SD7SubJet1PT, SD7SubJet1Eta, SD7SubJet1Phi;
   double SD7SubJet2E, SD7SubJet2PT, SD7SubJet2Eta, SD7SubJet2Phi;
   double MCWeight;
public:
   Messenger(string FileName)
   {
      File = TFile::Open(FileName.c_str());
      if(File == NULL)
         return;

      Tree = (TTree *)File->Get("T");
      if(Tree == NULL)
         return;

      Tree->SetBranchAddress("Run",            &Run);
      Tree->SetBranchAddress("Event",          &Event);
      Tree->SetBranchAddress("Lumi",           &Lumi);
      Tree->SetBranchAddress("Centrality",     &Centrality);
      Tree->SetBranchAddress("PTHat",          &PTHat);
      Tree->SetBranchAddress("Rho",            &Rho);
      Tree->SetBranchAddress("PassPbPb40",     &Pass40);
      Tree->SetBranchAddress("PassPbPb60",     &Pass60);
      Tree->SetBranchAddress("PassPbPb80",     &Pass80);
      Tree->SetBranchAddress("PassPbPb100",    &Pass100);
      Tree->SetBranchAddress("GenJetIndex",    &GenJetIndex);
      Tree->SetBranchAddress("GenJetPT",       &GenJetPT);
      Tree->SetBranchAddress("GenJetEta",      &GenJetEta);
      Tree->SetBranchAddress("GenJetPhi",      &GenJetPhi);
      Tree->SetBranchAddress("MatchJetRawPT",  &MatchJetRawPT);
      Tree->SetBranchAddress("MatchJetEta",    &MatchJetEta);
      Tree->SetBranchAddress("MatchJetPhi",    &MatchJetPhi);
      Tree->SetBranchAddress("MatchJetBestDR", &MatchJetBestDR);
      Tree->SetBranchAddress("CSJetRawPT",     &CSJetRawPT);
      Tree->SetBranchAddress("CSJetPT",        &CSJetPT);
      Tree->SetBranchAddress("CSJetEta",       &CSJetEta);
      Tree->SetBranchAddress("CSJetPhi",       &CSJetPhi);
      Tree->SetBranchAddress("CSJetBestDR",    &CSJetBestDR);
      Tree->SetBranchAddress("CSJetRefPT",     &CSJetRefPT);
      Tree->SetBranchAddress("CSJetRefEta",    &CSJetRefEta);
      Tree->SetBranchAddress("CSJetRefPhi",    &CSJetRefPhi);
      Tree->SetBranchAddress("Flavor",         &Flavor);
      Tree->SetBranchAddress("FlavorB",        &FlavorB);
      Tree->SetBranchAddress("SD0Depth",       &SD0Depth);
      Tree->SetBranchAddress("SD7Depth",       &SD7Depth);
      Tree->SetBranchAddress("SD0DR",          &SD0DR);
      Tree->SetBranchAddress("SD7DR",          &SD7DR);
      Tree->SetBranchAddress("SD0Mass",        &SD0Mass);
      Tree->SetBranchAddress("SD7Mass",        &SD7Mass);
      Tree->SetBranchAddress("SD0SubJet1E",    &SD0SubJet1E);
      Tree->SetBranchAddress("SD0SubJet1PT",   &SD0SubJet1PT);
      Tree->SetBranchAddress("SD0SubJet1Eta",  &SD0SubJet1Eta);
      Tree->SetBranchAddress("SD0SubJet1Phi",  &SD0SubJet1Phi);
      Tree->SetBranchAddress("SD0SubJet2E",    &SD0SubJet2E);
      Tree->SetBranchAddress("SD0SubJet2PT",   &SD0SubJet2PT);
      Tree->SetBranchAddress("SD0SubJet2Eta",  &SD0SubJet2Eta);
      Tree->SetBranchAddress("SD0SubJet2Phi",  &SD0SubJet2Phi);
      Tree->SetBranchAddress("SD7SubJet1E",    &SD7SubJet1E);
      Tree->SetBranchAddress("SD7SubJet1PT",   &SD7SubJet1PT);
      Tree->SetBranchAddress("SD7SubJet1Eta",  &SD7SubJet1Eta);
      Tree->SetBranchAddress("SD7SubJet1Phi",  &SD7SubJet1Phi);
      Tree->SetBranchAddress("SD7SubJet2E",    &SD7SubJet2E);
      Tree->SetBranchAddress("SD7SubJet2PT",   &SD7SubJet2PT);
      Tree->SetBranchAddress("SD7SubJet2Eta",  &SD7SubJet2Eta);
      Tree->SetBranchAddress("SD7SubJet2Phi",  &SD7SubJet2Phi);
      Tree->SetBranchAddress("MCWeight",       &MCWeight);

      if(Tree->GetBranch("MCWeight") == NULL)
         MCWeight = 1;
   }
   ~Messenger()
   {
      if(File != NULL)
      {
         File->Close();
         delete File;
      }
   }
   void GetEntry(int iE)
   {
      if(Tree == NULL)
         return;

      Tree->GetEntry(iE);
   }
   int EntryCount()
   {
      if(Tree == NULL)
         return 0;
      return Tree->GetEntries();
   }
   int FindCBin(int N, double Edge[])
   {
      return FindBin(Centrality, N, Edge);
   }
   int FindPTBin(int N, double Edge[])
   {
      return FindBin(GenJetPT, N, Edge);
      // return FindBin(CSJetRefPT, N, Edge);
   }
   int FindBin(double x, int N, double Edge[])
   {
      if(N == 0)
         return -1;
      if(x <= Edge[0])
         return -1;
      if(x > Edge[N-1])
         return N;

      for(int i = 0; i < N; i++)
         if(x <= Edge[i+1] && x > Edge[i])
            return i;

      return -1;
   }
};

class Histograms
{
public:
   string Tag;
   TH1D *HGenPT;
   TH1D *HCentrality;
   TH1D *HMatchDR;
   TH1D *HCSDR;
   TH1D *HResponse;
   TH1D *HResponseGoodMatch;
   TH1D *HRefResponse;
   TH1D *HRefResponseGoodMatch;
   TH1D *HResponseM0;
   TH1D *HResponseM1;
   TH1D *HResponseM2;
   TH1D *HResponseM3;
public:
   Histograms(string tag)
      : Tag(tag)
   {
      HGenPT = new TH1D(Form("HGenPT_%s", Tag.c_str()), ";Gen PT;", 100, 0, 500);
      HCentrality = new TH1D(Form("HCentrality_%s", Tag.c_str()), ";Centrality;", 100, 0, 1);
      HMatchDR = new TH1D(Form("HMatchDR_%s", Tag.c_str()), ";DR;", 100, 0, 0.4);
      HCSDR = new TH1D(Form("HCSDR_%s", Tag.c_str()), ";DR;", 100, 0, 0.4);
      HResponse = new TH1D(Form("HResponse_%s", Tag.c_str()), ";Reco/Gen - 1;", 100, -1, 1);
      HResponseGoodMatch = new TH1D(Form("HResponseGoodMatch_%s", Tag.c_str()), ";Reco/Gen - 1;", 100, -1, 1);
      HRefResponse = new TH1D(Form("HRefResponse_%s", Tag.c_str()), ";Reco/Gen - 1;", 100, -1, 1);
      HRefResponseGoodMatch = new TH1D(Form("HRefResponseGoodMatch_%s", Tag.c_str()), ";Reco/Gen - 1;", 100, -1, 1);
      HResponseM0 = new TH1D(Form("HResponseM0_%s", Tag.c_str()), ";Reco/Gen - 1;", 100, -1, 1);
      HResponseM1 = new TH1D(Form("HResponseM1_%s", Tag.c_str()), ";Reco/Gen - 1;", 100, -1, 1);
      HResponseM2 = new TH1D(Form("HResponseM2_%s", Tag.c_str()), ";Reco/Gen - 1;", 100, -1, 1);
      HResponseM3 = new TH1D(Form("HResponseM3_%s", Tag.c_str()), ";Reco/Gen - 1;", 100, -1, 1);

      BasicStyling(HGenPT);
      BasicStyling(HCentrality);
      BasicStyling(HMatchDR);
      BasicStyling(HCSDR);
      BasicStyling(HResponse);
      BasicStyling(HResponseGoodMatch);
      BasicStyling(HRefResponse);
      BasicStyling(HRefResponseGoodMatch);
      BasicStyling(HResponseM0);
      BasicStyling(HResponseM1);
      BasicStyling(HResponseM2);
      BasicStyling(HResponseM3);
   }
   ~Histograms() {}
   void Fill(Messenger &M)
   {
      double MatchDR = GetDR(M.MatchJetEta, M.MatchJetPhi, M.GenJetEta, M.GenJetPhi);
      double CSDR = GetDR(M.CSJetEta, M.CSJetPhi, M.GenJetEta, M.GenJetPhi);

      HGenPT->Fill(M.GenJetPT, M.MCWeight);
      HCentrality->Fill(M.Centrality, M.MCWeight);
      HMatchDR->Fill(MatchDR, M.MCWeight);
      HCSDR->Fill(CSDR, M.MCWeight);
      
      HResponse->Fill(M.CSJetPT / M.GenJetPT - 1, M.MCWeight);
      if(CSDR < 0.15)
         HResponseGoodMatch->Fill(M.CSJetPT / M.GenJetPT - 1, M.MCWeight);
      
      HRefResponse->Fill(M.CSJetPT / M.CSJetRefPT - 1, M.MCWeight);
      if(CSDR < 0.15)
         HRefResponseGoodMatch->Fill(M.CSJetPT / M.CSJetRefPT - 1, M.MCWeight);

      if(M.SD0DR > 0)
      {
         if(M.SD0Mass / M.MatchJetRawPT >= 0.00 && M.SD0Mass / M.MatchJetRawPT < 0.05)
            HResponseM0->Fill(M.CSJetPT / M.GenJetPT - 1, M.MCWeight);
         if(M.SD0Mass / M.MatchJetRawPT >= 0.05 && M.SD0Mass / M.MatchJetRawPT < 0.10)
            HResponseM1->Fill(M.CSJetPT / M.GenJetPT - 1, M.MCWeight);
         if(M.SD0Mass / M.MatchJetRawPT >= 0.10 && M.SD0Mass / M.MatchJetRawPT < 0.15)
            HResponseM2->Fill(M.CSJetPT / M.GenJetPT - 1, M.MCWeight);
         if(M.SD0Mass / M.MatchJetRawPT >= 0.15 && M.SD0Mass / M.MatchJetRawPT < 0.25)
            HResponseM3->Fill(M.CSJetPT / M.GenJetPT - 1, M.MCWeight);
      }
   }
   void Write()
   {
      HGenPT->Write();
      HCentrality->Write();
      HMatchDR->Write();
      HCSDR->Write();
      HResponse->Write();
      HResponseGoodMatch->Write();
      HRefResponse->Write();
      HRefResponseGoodMatch->Write();
      HResponseM0->Write();
      HResponseM1->Write();
      HResponseM2->Write();
      HResponseM3->Write();
   }
   void SanityCheck(PdfFileHelper &PdfFile)
   {
      PdfFile.AddTextPage("Start plots with tag \"" + Tag + "\"");

      PdfFile.AddPlot(HGenPT);
      PdfFile.AddPlot(HCentrality);
      PdfFile.AddPlot(HMatchDR);
      PdfFile.AddPlot(HCSDR);
      
      HResponse->Fit("gaus", "", "", -0.25, 0.25);
      PdfFile.AddPlot(HResponse);
      PdfFile.AddPlot(HResponse, "", true);
      PdfFile.AddPlot(HResponseGoodMatch);
      PdfFile.AddPlot(HResponseGoodMatch, "", true);
      
      PdfFile.AddPlot(HRefResponse);
      PdfFile.AddPlot(HRefResponse, "", true);
      PdfFile.AddPlot(HRefResponseGoodMatch);
      PdfFile.AddPlot(HRefResponseGoodMatch, "", true);
      
      PdfFile.AddPlot(HResponseM0);
      PdfFile.AddPlot(HResponseM1);
      PdfFile.AddPlot(HResponseM2);
      PdfFile.AddPlot(HResponseM3);
   }
   void BasicStyling(TH1D *H)
   {
      if(H == NULL)
         return;

      H->Sumw2();
      H->SetLineWidth(2);
      H->SetMarkerStyle(20);
   }
};

int main()
{
   SetThesisStyle();

   Messenger M("AA6DijetCymbal.root");
   // Messenger M("Meow.root");

   int CBin = 5;
   int PTBin = 14;
   double CBins[] = {0.0, 0.1, 0.3, 0.5, 0.8, 1.0};
   double PTBins[] = {50, 60, 70, 80, 100, 120, 140, 160, 180, 200, 220, 240, 270, 300, 500};

   PdfFileHelper PdfFile("ResolutionPlotSanityCheck.pdf");
   PdfFile.AddTextPage("Sanity check for resolution plots");

   TFile OutputFile("Histograms.root", "RECREATE");

   Histograms *H[CBin][PTBin];
   for(int i = 0; i < CBin; i++)
      for(int j = 0; j < PTBin; j++)
         H[i][j] = new Histograms(Form("All_C%dPT%d", i, j));
   Histograms *HQ[CBin][PTBin];
   for(int i = 0; i < CBin; i++)
      for(int j = 0; j < PTBin; j++)
         HQ[i][j] = new Histograms(Form("Q_C%dPT%d", i, j));
   Histograms *HG[CBin][PTBin];
   for(int i = 0; i < CBin; i++)
      for(int j = 0; j < PTBin; j++)
         HG[i][j] = new Histograms(Form("G_C%dPT%d", i, j));

   int EntryCount = M.EntryCount();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      M.GetEntry(iE);

      if(abs(M.GenJetEta) > 1.3)
         continue;

      int iC = M.FindCBin(CBin, CBins);
      int iPT = M.FindPTBin(PTBin, PTBins);

      if(iC < 0 || iPT < 0 || iC >= CBin || iPT >= PTBin)
         continue;

      H[iC][iPT]->Fill(M);

      if(M.Flavor == 21)
         HG[iC][iPT]->Fill(M);
      if(M.Flavor >= -3 && M.Flavor <= 3)
         HQ[iC][iPT]->Fill(M);
   }

   for(int i = 0; i < CBin; i++)
   {
      for(int j = 0; j < PTBin; j++)
      {
         H[i][j]->Write();
         HQ[i][j]->Write();
         HG[i][j]->Write();
      }
   }

   for(int i = 0; i < CBin; i++)
   {
      for(int j = 0; j < PTBin; j++)
      {
         H[i][j]->SanityCheck(PdfFile);
         HQ[i][j]->SanityCheck(PdfFile);
         HG[i][j]->SanityCheck(PdfFile);
      }
   }

   for(int i = 0; i < CBin; i++)
   {
      for(int j = 0; j < PTBin; j++)
      {
         delete H[i][j];
         delete HQ[i][j];
         delete HG[i][j];
      }
   }

   OutputFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}






