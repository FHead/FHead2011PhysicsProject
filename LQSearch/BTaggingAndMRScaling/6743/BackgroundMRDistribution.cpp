#include <string>
#include <vector>
#include <map>
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
#include "ChainAll.h"
#include "ReadNTPTree.h"

int main(int argc, char *argv[]);
void BackgroundMRDistribution(string InputFile, string OutputBase);
bool CheckLeptonicW(NTPTreeMessenger &M);

struct ExponentialFitResult
{
   double Exp;
   double ExpError;
};

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

   string InputFile = Tag + ".list";
   string OutputBase = Tag;

   BackgroundMRDistribution(InputFile, OutputBase);
}

void BackgroundMRDistribution(string InputList, string OutputBase)
{
   TChain *Tree = ChainAll(InputList, "ntp1");
   if(Tree == NULL)   // tree non-existent
      return;

   TFile OutputFile((OutputBase + "_MRTree.root").c_str(), "RECREATE");

   double TreeGroupPFMR;
   double TreeGroupPFR;
   double TreeJet1TCHE;
   double TreeJet2TCHE;
   double TreeJet1TCHP;
   double TreeJet2TCHP;
   double TreeJet1CSV;
   double TreeJet2CSV;
   double TreeJet1CSVM;
   double TreeJet2CSVM;

   TTree MRTree("MRTree", "MR Tree For Fitting Background Tails");
   MRTree.Branch("GroupPFMR", &TreeGroupPFMR, "GroupPFMR/D");
   MRTree.Branch("GroupPFR", &TreeGroupPFR, "GroupPFR/D");
   MRTree.Branch("Jet1TCHE", &TreeJet1TCHE, "Jet1TCHE/D");
   MRTree.Branch("Jet2TCHE", &TreeJet2TCHE, "Jet2TCHE/D");
   MRTree.Branch("Jet1TCHP", &TreeJet1TCHP, "Jet1TCHP/D");
   MRTree.Branch("Jet2TCHP", &TreeJet2TCHP, "Jet2TCHP/D");
   MRTree.Branch("Jet1CSV", &TreeJet1CSV, "Jet1CSV/D");
   MRTree.Branch("Jet2CSV", &TreeJet2CSV, "Jet2CSV/D");
   MRTree.Branch("Jet1CSVM", &TreeJet1CSVM, "Jet1CSVM/D");
   MRTree.Branch("Jet2CSVM", &TreeJet2CSVM, "Jet2CSVM/D");

   NTPTreeMessenger M;
   M.SetBranchAddress(Tree);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 50000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iEntry);

      bool ExistGoodElectron = false;
      bool ExistGoodMuon = false;
      bool ExistLeptonicW = false;

      if(ExistGoodElectron == true)
         continue;
      if(ExistGoodMuon == true)
         continue;
      if(ExistLeptonicW == true)
         continue;

      FourVector PFMETP(M.energyPFMet[0], M.pxPFMet[0], M.pyPFMet[1], M.pzPFMet[2]);

      if(M.nAK5PFJet >= 2)
      {
         vector<FourVector> PFJets;
         multimap<double, int, greater<double> > SortPFJets;
         for(int i = 0; i < 31 && i < M.nAK5PFJet; i++)
         {
            if(M.pxAK5PFJet[i] * M.pxAK5PFJet[i] + M.pyAK5PFJet[i] * M.pyAK5PFJet[i] < 30 * 30)
               continue;
            if(fabs(M.etaAK5PFJet[i]) > 2.4)
               continue;
            
            FourVector NewJet(M.energyAK5PFJet[i], M.pxAK5PFJet[i], M.pyAK5PFJet[i], M.pzAK5PFJet[i]);
            PFJets.push_back(NewJet);
            SortPFJets.insert(pair<double, int>(M.pxAK5PFJet[i] * M.pxAK5PFJet[i] + M.pyAK5PFJet[i] * M.pyAK5PFJet[i],
               i));
         }

         if(PFJets.size() >= 2)
         {
            multimap<double, int>::iterator iter = SortPFJets.begin();
            int Jet1Index = iter->second;
            iter++;
            int Jet2Index = iter->second;

            TreeJet1TCHE = M.trackCountingHighEffBJetTagsAK5PFJet[Jet1Index];
            TreeJet2TCHE = M.trackCountingHighEffBJetTagsAK5PFJet[Jet2Index];
            TreeJet1TCHP = M.trackCountingHighPurBJetTagsAK5PFJet[Jet1Index];
            TreeJet2TCHP = M.trackCountingHighPurBJetTagsAK5PFJet[Jet2Index];
            TreeJet1CSV = M.combinedSecondaryVertexBJetTagsAK5PFJet[Jet1Index];
            TreeJet2CSV = M.combinedSecondaryVertexBJetTagsAK5PFJet[Jet2Index];
            TreeJet1CSVM = M.combinedSecondaryVertexMVABJetTagsAK5PFJet[Jet1Index];
            TreeJet2CSVM = M.combinedSecondaryVertexMVABJetTagsAK5PFJet[Jet2Index];

            vector<FourVector> Groups = SplitIntoGroups(PFJets);

            double GroupPFMR = GetMR(Groups[0], Groups[1]);
            double GroupPFMRT = GetMRT(Groups[0], Groups[1], PFMETP);
            double GroupPFR = GetR(Groups[0], Groups[1], PFMETP);
         
            if(GroupPFMR == GroupPFMR && GroupPFR == GroupPFR)   // protection for nan
            {
               TreeGroupPFMR = GroupPFMR;
               TreeGroupPFR = GroupPFR;
               MRTree.Fill();
            }
         }
      }
   }

   MRTree.Write();
   OutputFile.Close();
}

bool CheckLeptonicW(NTPTreeMessenger &M)
{
   for(int i = 0; i < M.nMc && i < 1001; i++)
   {
      // we want lepton
      if(fabs(M.idMc[i]) < 11 && fabs(M.idMc[i]) > 18)   // allow 4-th generation....
         continue;

      // if mother of lepton is W, return true
      if(M.mothMc[i] < 0)   // orphan
         continue;
      if(M.mothMc[i] == 24 || M.mothMc[i] == -24)
         return true;
   }

   return false;
}




