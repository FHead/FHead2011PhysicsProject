#include <string>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TLegend.h"
#include "TFitResult.h"
#include "TGraphErrors.h"

#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "ReadLQ3Tree.h"

int main(int argc, char *argv[]);
void BackgroundMRDistribution(string InputFile, string OutputBase);

int main(int argc, char *argv[])
{
   gROOT->SetStyle("Plain");

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   string Tag = "TTJets_TuneD6T";
   if(argc > 1)
      Tag = argv[1];

   string InputFile = "Samples/" + Tag + ".root";
   string OutputBase = "Samples/" + Tag;

   BackgroundMRDistribution(InputFile, OutputBase);
}

void BackgroundMRDistribution(string InputFile, string OutputBase)
{
   TFile F(InputFile.c_str());
   TTree *Tree = (TTree *)F.Get("LQ3Tree");

   if(Tree == NULL)   // tree non-existent
      return;

   TFile OutputFile((OutputBase + "_MRTree.root").c_str(), "RECREATE");

   double TreeGroupPFMR;
   double TreeGroupPFR;
   int Category;

   TTree MRTree("MRTree", "MR Tree For Fitting Background Tails");
   MRTree.Branch("MR", &TreeGroupPFMR, "MR/D");
   MRTree.Branch("R", &TreeGroupPFR, "R/D");
   MRTree.Branch("Category", &Category, "Category/I");

   TreeRecord M;
   M.SetBranchAddress(Tree);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 100000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iEntry);

      Category = 0;
      if(M.GoodMuonCount >= 1)
         Category = 1;
      else if(M.GoodElectronCount >= 1)
         Category = 2;
      else
         Category = 3;

      FourVector PFMETP(0, M.PFMET[0], M.PFMET[1], 0);
      PFMETP[0] = PFMETP.GetP();

      if(M.PFJetCount >= 2)
      {
         vector<FourVector> PFJets;
         for(int i = 0; i < 50 && i < M.PFJetCount; i++)
         {
            if(M.PFJetPT[i] > 30 && fabs(M.PFJetEta[i]) < 2.4)
            {
               FourVector NewJet;
               NewJet.SetPtEtaPhi(M.PFJetPT[i], M.PFJetEta[i], M.PFJetPhi[i]);
               PFJets.push_back(NewJet);
            }
         }

         vector<FourVector> Groups = SplitIntoGroups(PFJets);

         double BetaR = (Groups[0][0] - Groups[1][0]) / (Groups[0][3] - Groups[1][3]);
         // double DeltaRho = GetAngle(Groups[0], Groups[1]);
         double GroupPFMR = GetMR(Groups[0], Groups[1]);
         double GroupPFMRT = GetMRT(Groups[0], Groups[1], PFMETP);
         double GroupPFR = GetR(Groups[0], Groups[1], PFMETP);
         
         if(GroupPFMR == GroupPFMR && GroupPFR == GroupPFR && fabs(BetaR) < 0.99)   // first two: protection for nan
         {
            TreeGroupPFMR = GroupPFMR;
            TreeGroupPFR = GroupPFR;
            MRTree.Fill();
         }
      }
   }

   MRTree.Write();
   OutputFile.Close();

   F.Close();
}






