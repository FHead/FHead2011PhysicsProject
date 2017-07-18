#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"

#include "Code/DrawRandom.h"

#include "BasicUtilities.h"

int main(int argc, char *argv[]);
double GetDPhi(double phi1, double phi2);

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag" << endl;
      return -1;
   }

   cout << "Running with input file " << argv[1] << endl;

   string TriggerString = "HLT_HIPuAK4CaloJet100_Eta5p1_v1";

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];

   bool IsData = IsDataFromTag(Tag);

   TFile InputFile(Input.c_str());

   TTree *Tree = (TTree *)InputFile.Get("hiEvtAnalyzer/HiTree");
   TTree *RhoTree = (TTree *)InputFile.Get("hiFJRhoAnalyzer/t");
   TTree *HLTTree = (TTree *)InputFile.Get("hltanalysis/HltTree");
   TTree *SkimTree = (TTree *)InputFile.Get("skimanalysis/HltTree");
   TTree *PFTree = (TTree *)InputFile.Get("pfcandAnalyzer/pfTree");

   if(Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");
  
   TH2D HSubtractedPTCentrality("HSubtractedPTCentrality", ";Centrality;Subtracted Random Cone PT",
      100, -0.0001, 0.9999, 1000, -100, 100);
   TH2D HSubtractedPTRatioCentrality("HSubtractedPTRatioCentrality", ";Centrality;Subtracted Random Cone PT / PT",
      100, 0, 1, 1000, -2, 2);

   TTree OutputTree("T", "Yay random cone studies!");

   double TreeEta;
   double TreePhi;
   double TreeCentrality;
   double TreeRho;
   double TreeTotalPT;
   OutputTree.Branch("Eta", &TreeEta, "Eta/D");
   OutputTree.Branch("Phi", &TreePhi, "Phi/D");
   OutputTree.Branch("Centrality", &TreeCentrality, "Centrality/D");
   OutputTree.Branch("Rho", &TreeRho, "Rho/D");
   OutputTree.Branch("TotalPT", &TreeTotalPT, "TotalPT/D");

   float hiHF;
   int hiBin;
   unsigned int run;
   Tree->SetBranchAddress("hiHF", &hiHF);
   Tree->SetBranchAddress("hiBin", &hiBin);
   Tree->SetBranchAddress("run", &run);
   
   int HBHENoise;
   int HBHENoiseRun2Loose;
   int PVFilter;
   int ClusterCompatibilityFilter;
   int HFCoincidenceFilter;
   int CollisionEventSelection;
   SkimTree->SetBranchAddress("HBHENoiseFilterResult", &HBHENoise);
   SkimTree->SetBranchAddress("HBHENoiseFilterResultRun2Loose", &HBHENoiseRun2Loose);
   SkimTree->SetBranchAddress("pprimaryVertexFilter", &PVFilter);
   SkimTree->SetBranchAddress("pclusterCompatibilityFilter", &ClusterCompatibilityFilter);
   SkimTree->SetBranchAddress("phfCoincFilter3", &HFCoincidenceFilter);
   SkimTree->SetBranchAddress("pcollisionEventSelection", &CollisionEventSelection);

   vector<double> *EtaMax = NULL;
   vector<double> *Rho = NULL;
   vector<double> *RhoM = NULL;
   
   RhoTree->SetBranchAddress("etaMax", &EtaMax);
   RhoTree->SetBranchAddress("rho", &Rho);
   RhoTree->SetBranchAddress("rhom", &RhoM);

   int Decision = 1;
   if(IsData == true)
      HLTTree->SetBranchAddress(TriggerString.c_str(), &Decision);

   vector<int> *PFID = NULL;
   vector<float> *PFPT = NULL;
   vector<float> *PFEnergy = NULL;
   vector<float> *PFEta = NULL;
   vector<float> *PFPhi = NULL;
   PFTree->SetBranchAddress("pfId", &PFID);
   PFTree->SetBranchAddress("pfPt", &PFPT);
   PFTree->SetBranchAddress("pfEnergy", &PFEnergy);
   PFTree->SetBranchAddress("pfEta", &PFEta);
   PFTree->SetBranchAddress("pfPhi", &PFPhi);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree->GetEntry(iEntry);
      RhoTree->GetEntry(iEntry);
      SkimTree->GetEntry(iEntry);
      PFTree->GetEntry(iEntry);

      if(IsData == true)
      {
         HLTTree->GetEntry(iEntry);
         // if(Decision == false)
         //    continue;
         
         // if(HBHENoise == 0)
         //    continue;
         if(HBHENoiseRun2Loose == 0)
            continue;
         if(PVFilter == 0)
            continue;
         if(ClusterCompatibilityFilter == 0)
            continue;
         if(HFCoincidenceFilter == 0)
            continue;
         if(CollisionEventSelection == 0)
            continue;
      }

      double EventRho = GetRho(EtaMax, Rho, 0);

      int Tries = 10;
      for(int iT = 0; iT < Tries; iT++)
      {
         double Eta = DrawRandom(-1.3, 1.3);
         double Phi = DrawRandom(0, 2 * PI);

         double TotalPT = 0;
         for(int iC = 0; iC < (int)PFPT->size(); iC++)
         {
            if(Eta - (*PFEta)[iC] > 0.4 || Eta - (*PFEta)[iC] < -0.4)
               continue;

            double DPhi = GetDPhi(Phi, (*PFPhi)[iC]);
            double DEta = Eta - (*PFEta)[iC];
            if(DPhi * DPhi + DEta * DEta < 0.4 * 0.4)
               TotalPT = TotalPT + (*PFPT)[iC];
         }

         double SubtractedPT = TotalPT - 0.4 * 0.4 * PI * EventRho;

         HSubtractedPTCentrality.Fill(GetCentrality(hiBin), SubtractedPT);
         HSubtractedPTRatioCentrality.Fill(GetCentrality(hiBin), SubtractedPT / TotalPT);

         TreeEta = Eta;
         TreePhi = Phi;
         TreeRho = EventRho;
         TreeCentrality = GetCentrality(hiBin);
         TreeTotalPT = TotalPT;

         OutputTree.Fill();
      }
   }

   HSubtractedPTCentrality.Write();
   HSubtractedPTRatioCentrality.Write();

   OutputTree.Write();

   OutputFile.Close();

   InputFile.Close();
}

double GetDPhi(double phi1, double phi2)
{
   double dphi = phi1 - phi2;

   if(dphi < -PI)   dphi = dphi + 2 * PI;
   if(dphi > +PI)   dphi = dphi - 2 * PI;

   return dphi;
}






