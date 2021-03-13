#include <iostream>
#include <cmath>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "CommandLine.h"

#define MAX 10000

int main(int argc, char *argv[]);
double GetDR(double eta1, double phi1, double eta2, double phi2);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputOriginal = CL.Get("input");
   string InputMorphed = CL.Get("morphed");
   string Output = CL.Get("output");

   TFile FileOriginal(InputOriginal.c_str());
   TFile FileMorphed(InputMorphed.c_str());

   TTree *OTree = (TTree *)FileOriginal.Get("Tree");
   TTree *MTree = (TTree *)FileMorphed.Get("Tree");

   if(OTree == nullptr || MTree == nullptr)
      return -1;

   int ONJet;
   double OJetPT[MAX], ORawPT[MAX], OJetEta[MAX], OJetPhi[MAX];
   double OGenPT[MAX], OGenEta[MAX], OGenPhi[MAX], OGenDR[MAX];
   OTree->SetBranchAddress("NJet",   &ONJet);
   OTree->SetBranchAddress("JetPT",  &OJetPT);
   OTree->SetBranchAddress("RawPT",  &ORawPT);
   OTree->SetBranchAddress("JetEta", &OJetEta);
   OTree->SetBranchAddress("JetPhi", &OJetPhi);
   OTree->SetBranchAddress("GenPT",  &OGenPT);
   OTree->SetBranchAddress("GenEta", &OGenEta);
   OTree->SetBranchAddress("GenPhi", &OGenPhi);
   OTree->SetBranchAddress("GenDR",  &OGenDR);
   
   int MNJet;
   double MJetPT[MAX], MRawPT[MAX], MJetEta[MAX], MJetPhi[MAX];
   double MGenPT[MAX], MGenEta[MAX], MGenPhi[MAX], MGenDR[MAX];
   MTree->SetBranchAddress("NJet",   &MNJet);
   MTree->SetBranchAddress("JetPT",  &MJetPT);
   MTree->SetBranchAddress("RawPT",  &MRawPT);
   MTree->SetBranchAddress("JetEta", &MJetEta);
   MTree->SetBranchAddress("JetPhi", &MJetPhi);
   MTree->SetBranchAddress("GenPT",  &MGenPT);
   MTree->SetBranchAddress("GenEta", &MGenEta);
   MTree->SetBranchAddress("GenPhi", &MGenPhi);
   MTree->SetBranchAddress("GenDR",  &MGenDR);

   double OCentrality, MCentrality;
   OTree->SetBranchAddress("Centrality", &OCentrality);
   MTree->SetBranchAddress("Centrality", &MCentrality);

   int ONRho;
   double ORho[MAX];
   double OV2, OV3, OPhi2, OPhi3, OChi2, ONDoF, OChi2Probability;
   OTree->SetBranchAddress("NRho",            &ONRho);
   OTree->SetBranchAddress("Rho",             &ORho);
   OTree->SetBranchAddress("V2",              &OV2);
   OTree->SetBranchAddress("V3",              &OV3);
   OTree->SetBranchAddress("Phi2",            &OPhi2);
   OTree->SetBranchAddress("Phi3",            &OPhi3);
   OTree->SetBranchAddress("Chi2",            &OChi2);
   OTree->SetBranchAddress("NDoF",            &ONDoF);
   OTree->SetBranchAddress("Chi2Probability", &OChi2Probability);
   
   int MNRho;
   double MRho[MAX];
   double MV2, MV3, MPhi2, MPhi3, MChi2, MNDoF, MChi2Probability;
   MTree->SetBranchAddress("NRho",            &MNRho);
   MTree->SetBranchAddress("Rho",             &MRho);
   MTree->SetBranchAddress("V2",              &MV2);
   MTree->SetBranchAddress("V3",              &MV3);
   MTree->SetBranchAddress("Phi2",            &MPhi2);
   MTree->SetBranchAddress("Phi3",            &MPhi3);
   MTree->SetBranchAddress("Chi2",            &MChi2);
   MTree->SetBranchAddress("NDoF",            &MNDoF);
   MTree->SetBranchAddress("Chi2Probability", &MChi2Probability);

   TFile OutputFile(Output.c_str(), "RECREATE");

   TTree OutputTree("Tree", "Tree");

   OutputTree.Branch("OCentrality",      &OCentrality,      "OCentrality/D");
   OutputTree.Branch("MCentrality",      &MCentrality,      "MCentrality/D");
   OutputTree.Branch("ONRho",            &ONRho,            "ONRho/I");
   OutputTree.Branch("ORho",             &ORho,             "ORho[ONRho]/D");
   OutputTree.Branch("OV2",              &OV2,              "OV2/D");
   OutputTree.Branch("OV3",              &OV3,              "OV3/D");
   OutputTree.Branch("OPhi2",            &OPhi2,            "OPhi2/D");
   OutputTree.Branch("OPhi3",            &OPhi3,            "OPhi3/D");
   OutputTree.Branch("OChi2",            &OChi2,            "OChi2/D");
   OutputTree.Branch("ONDoF",            &ONDoF,            "ONDoF/D");
   OutputTree.Branch("OChi2Probability", &OChi2Probability, "OChi2Probability/D");
   OutputTree.Branch("MNRho",            &MNRho,            "MNRho/I");
   OutputTree.Branch("MRho",             &MRho,             "MRho[MNRho]/D");
   OutputTree.Branch("MV2",              &MV2,              "MV2/D");
   OutputTree.Branch("MV3",              &MV3,              "MV3/D");
   OutputTree.Branch("MPhi2",            &MPhi2,            "MPhi2/D");
   OutputTree.Branch("MPhi3",            &MPhi3,            "MPhi3/D");
   OutputTree.Branch("MChi2",            &MChi2,            "MChi2/D");
   OutputTree.Branch("MNDoF",            &MNDoF,            "MNDoF/D");
   OutputTree.Branch("MChi2Probability", &MChi2Probability, "MChi2Probability/D");

   double MorphedJetPT[MAX], MorphedRawPT[MAX], MorphedJetEta[MAX], MorphedJetPhi[MAX];
   double MorphedGenPT[MAX], MorphedGenEta[MAX], MorphedGenPhi[MAX], MorphedGenDR[MAX];
   double MorphedDR[MAX];
   OutputTree.Branch("NJet",    &ONJet,         "NJet/I");
   OutputTree.Branch("JetPT",   &OJetPT,        "JetPT[NJet]/D");
   OutputTree.Branch("RawPT",   &ORawPT,        "RawPT[NJet]/D");
   OutputTree.Branch("JetEta",  &OJetEta,       "JetEta[NJet]/D");
   OutputTree.Branch("JetPhi",  &OJetPhi,       "JetPhi[NJet]/D");
   OutputTree.Branch("GenPT",   &OGenPT,        "GenPT[NJet]/D");
   OutputTree.Branch("GenEta",  &OGenEta,       "GenEta[NJet]/D");
   OutputTree.Branch("GenPhi",  &OGenPhi,       "GenPhi[NJet]/D");
   OutputTree.Branch("GenDR",   &OGenDR,        "GenDR[NJet]/D");
   OutputTree.Branch("MJetPT",  &MorphedJetPT,  "MJetPT[NJet]/D");
   OutputTree.Branch("MRawPT",  &MorphedRawPT,  "MRawPT[NJet]/D");
   OutputTree.Branch("MJetEta", &MorphedJetEta, "MJetEta[NJet]/D");
   OutputTree.Branch("MJetPhi", &MorphedJetPhi, "MJetPhi[NJet]/D");
   OutputTree.Branch("MGenPT",  &MorphedGenPT,  "MGenPT[NJet]/D");
   OutputTree.Branch("MGenEta", &MorphedGenEta, "MGenEta[NJet]/D");
   OutputTree.Branch("MGenPhi", &MorphedGenPhi, "MGenPhi[NJet]/D");
   OutputTree.Branch("MGenDR",  &MorphedGenDR,  "MGenDR[NJet]/D");
   OutputTree.Branch("MDR",     &MorphedDR,     "MDR[NJet]/D");
   
   if(OTree->GetEntries() != MTree->GetEntries())
   {
      cerr << "The two trees have different number of entries!  Refuse to match..." << endl;
      OutputFile.Close();
      return 0;
   }

   int EntryCount = OTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      OTree->GetEntry(iE);
      MTree->GetEntry(iE);

      for(int iJ = 0; iJ < ONJet; iJ++)
      {
         int BestIndex = -1;
         double BestDR = -1;
         for(int i = 0; i < MNJet; i++)
         {
            double DR = GetDR(OJetEta[iJ], OJetPhi[iJ], MJetEta[i], MJetPhi[i]);
            if(BestDR < 0 || DR < BestDR)
            {
               BestIndex = i;
               BestDR = DR;
            }
         }

         if(BestIndex >= 0 && BestIndex < MNJet)
         {
            MorphedJetPT[iJ]  = MJetPT[BestIndex];
            MorphedRawPT[iJ]  = MRawPT[BestIndex];
            MorphedJetEta[iJ] = MJetEta[BestIndex];
            MorphedJetPhi[iJ] = MJetPhi[BestIndex];
            MorphedGenPT[iJ]  = MGenPT[BestIndex];
            MorphedGenEta[iJ] = MGenEta[BestIndex];
            MorphedGenPhi[iJ] = MGenPhi[BestIndex];
            MorphedGenDR[iJ]  = MGenDR[BestIndex];
            MorphedDR[iJ]     = BestDR;
         }
         else
         {
            MorphedJetPT[iJ] = -1;
            MorphedRawPT[iJ] = -1;
            MorphedJetEta[iJ] = -1;
            MorphedJetPhi[iJ] = -1;
            MorphedGenPT[iJ] = -1;
            MorphedGenEta[iJ] = -1;
            MorphedGenPhi[iJ] = -1;
            MorphedGenDR[iJ] = -1;
            MorphedDR[iJ] = -1;
         }
      }

      OutputTree.Fill();
   }

   OutputTree.Write();
   OutputFile.Close();

   FileMorphed.Close();
   FileOriginal.Close();

   return 0;
}

double GetDR(double eta1, double phi1, double eta2, double phi2)
{
   double deta = eta1 - eta2;
   double dphi = phi1 - phi2;
   if(dphi < -M_PI)
      dphi = dphi + 2 * M_PI;
   if(dphi > +M_PI)
      dphi = dphi - 2 * M_PI;

   return sqrt(deta * deta + dphi * dphi);
}



