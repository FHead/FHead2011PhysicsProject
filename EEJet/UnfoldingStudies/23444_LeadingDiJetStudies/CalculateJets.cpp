#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions3.h"
#include "CommandLine.h"

#include "JetCorrector.h"
#include "CATree.h"

#define MAX 1000

int main(int argc, char *argv[]);
int FindBin(int N, double Bins[], double X);
bool DecreasingEnergy(pair<FourVector, PseudoJet> &V1, pair<FourVector, PseudoJet> &V2);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileName  = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   bool IsMC                     = CL.GetBool("MC", false);
   bool BaselineCut              = CL.GetBool("BaselineCut", false);
   bool UseStored                = CL.GetBool("UseStored", false);
   double ThetaMin               = CL.GetDouble("ThetaMin", 0.2 * M_PI);
   double ThetaMax               = CL.GetDouble("ThetaMax", 0.8 * M_PI);
   double GenSumECut             = CL.GetDouble("GenSumECut", -99999);
   double RecoSumECut            = CL.GetDouble("RecoSumECut", -99999);
   double HybridJetMin           = CL.GetDouble("HybridJetMin", 5);
   bool DoSumESmear              = CL.GetBool("DoSumESmear", false);
   double SumESmear              = CL.GetDouble("SumESmear", 0.02);
   vector<string> JECFiles       = CL.GetStringVector("JEC", vector<string>{});
   double Fraction               = CL.GetDouble("Fraction", 1.00);
   double JetR                   = CL.GetDouble("JetR", 0.4);
   string RecoTreeName           = CL.Get("RecoTreeName", "t");
   string GenTreeName            = CL.Get("GenTreeName", "tgenBefore");
   bool CheckLeadingGenDiJet     = CL.GetBool("CheckLeadingGenDiJet", false);

   JetCorrector JEC(JECFiles);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("UnfoldingTree", "Trees for unfolding studies");

   int NSD = 2;
   vector<float> SDZCut{0.1, 0.5};
   vector<float> SDBeta{0.0, 1.5};
   int NSumE = 5;
   vector<float> SumECut{0.08 * M_PI, 0.10 * M_PI, 0.12 * M_PI, 0.15 * M_PI, 0.20 * M_PI};
   vector<float> RecoSumE;
   vector<float> RecoHybridE;
   int NRecoJets;
   vector<float> RecoJetPX;
   vector<float> RecoJetPY;
   vector<float> RecoJetPZ;
   vector<float> RecoJetP;
   vector<float> RecoJetTheta;
   vector<float> RecoJetPhi;
   vector<float> RecoJetM;
   vector<float> RecoJetE;
   vector<float> RecoJetJEC;
   vector<float> RecoJetJEU;
   vector<vector<float>> RecoJetZG;   // first index is SD index, second index is jet
   vector<vector<float>> RecoJetRG;
   vector<vector<float>> RecoJetPG;
   vector<vector<float>> RecoJetMG;
   vector<vector<float>> RecoJetNG;
   float RecoThrust;
   vector<float> GenSumE;
   vector<float> GenHybridE;
   int NGenJets;
   vector<float> GenJetPX;
   vector<float> GenJetPY;
   vector<float> GenJetPZ;
   vector<float> GenJetP;
   vector<float> GenJetTheta;
   vector<float> GenJetPhi;
   vector<float> GenJetM;
   vector<float> GenJetE;
   vector<vector<float>> GenJetZG;
   vector<vector<float>> GenJetRG;
   vector<vector<float>> GenJetPG;
   vector<vector<float>> GenJetMG;
   vector<vector<float>> GenJetNG;
   float GenThrust;
   vector<float> MatchedJetPX;
   vector<float> MatchedJetPY;
   vector<float> MatchedJetPZ;
   vector<float> MatchedJetP;
   vector<float> MatchedJetTheta;
   vector<float> MatchedJetPhi;
   vector<float> MatchedJetM;
   vector<float> MatchedJetE;
   vector<vector<float>> MatchedJetZG;
   vector<vector<float>> MatchedJetRG;
   vector<vector<float>> MatchedJetPG;
   vector<vector<float>> MatchedJetMG;
   vector<vector<float>> MatchedJetNG;
   vector<float> MatchedJetJEC;
   vector<float> MatchedJetJEU;
   vector<float> MatchedJetAngle;

   OutputTree.Branch("NSD",             &NSD, "NSD/I");
   OutputTree.Branch("SDZCut",          &SDZCut);
   OutputTree.Branch("SDBeta",          &SDBeta);
   OutputTree.Branch("NSumE",           &NSumE, "NSumE/I");
   OutputTree.Branch("SumECut",         &SumECut);
   OutputTree.Branch("HybridJetMin",    &HybridJetMin, "HybridJetMin/D");
   OutputTree.Branch("RecoSumE",        &RecoSumE);
   OutputTree.Branch("RecoHybridE",     &RecoHybridE);
   OutputTree.Branch("NRecoJets",       &NRecoJets, "NRecoJets/I");
   OutputTree.Branch("RecoJetPX",       &RecoJetPX);
   OutputTree.Branch("RecoJetPY",       &RecoJetPY);
   OutputTree.Branch("RecoJetPZ",       &RecoJetPZ);
   OutputTree.Branch("RecoJetP",        &RecoJetP);
   OutputTree.Branch("RecoJetTheta",    &RecoJetTheta);
   OutputTree.Branch("RecoJetPhi",      &RecoJetPhi);
   OutputTree.Branch("RecoJetM",        &RecoJetM);
   OutputTree.Branch("RecoJetE",        &RecoJetE);
   OutputTree.Branch("RecoJetJEC",      &RecoJetJEC);
   OutputTree.Branch("RecoJetJEU",      &RecoJetJEU);
   OutputTree.Branch("RecoJetZG",       &RecoJetZG);
   OutputTree.Branch("RecoJetRG",       &RecoJetRG);
   OutputTree.Branch("RecoJetPG",       &RecoJetPG);
   OutputTree.Branch("RecoJetMG",       &RecoJetMG);
   OutputTree.Branch("RecoJetNG",       &RecoJetNG);
   OutputTree.Branch("RecoThrust",      &RecoThrust);
   OutputTree.Branch("GenSumE",         &GenSumE);
   OutputTree.Branch("GenHybridE",      &GenHybridE);
   OutputTree.Branch("NGenJets",        &NGenJets, "NGenJets/I");
   OutputTree.Branch("GenJetPX",        &GenJetPX);
   OutputTree.Branch("GenJetPY",        &GenJetPY);
   OutputTree.Branch("GenJetPZ",        &GenJetPZ);
   OutputTree.Branch("GenJetP",         &GenJetP);
   OutputTree.Branch("GenJetTheta",     &GenJetTheta);
   OutputTree.Branch("GenJetPhi",       &GenJetPhi);
   OutputTree.Branch("GenJetM",         &GenJetM);
   OutputTree.Branch("GenJetE",         &GenJetE);
   OutputTree.Branch("GenJetZG",        &GenJetZG);
   OutputTree.Branch("GenJetRG",        &GenJetRG);
   OutputTree.Branch("GenJetPG",        &GenJetPG);
   OutputTree.Branch("GenJetMG",        &GenJetMG);
   OutputTree.Branch("GenJetNG",        &GenJetNG);
   OutputTree.Branch("GenThrust",       &GenThrust);
   OutputTree.Branch("MatchedJetPX",    &MatchedJetPX);
   OutputTree.Branch("MatchedJetPY",    &MatchedJetPY);
   OutputTree.Branch("MatchedJetPZ",    &MatchedJetPZ);
   OutputTree.Branch("MatchedJetP",     &MatchedJetP);
   OutputTree.Branch("MatchedJetTheta", &MatchedJetTheta);
   OutputTree.Branch("MatchedJetPhi",   &MatchedJetPhi);
   OutputTree.Branch("MatchedJetM",     &MatchedJetM);
   OutputTree.Branch("MatchedJetE",     &MatchedJetE);
   OutputTree.Branch("MatchedJetZG",    &MatchedJetZG);
   OutputTree.Branch("MatchedJetRG",    &MatchedJetRG);
   OutputTree.Branch("MatchedJetPG",    &MatchedJetPG);
   OutputTree.Branch("MatchedJetMG",    &MatchedJetMG);
   OutputTree.Branch("MatchedJetNG",    &MatchedJetNG);
   OutputTree.Branch("MatchedJetAngle", &MatchedJetAngle);
   OutputTree.Branch("MatchedJetJEC",   &MatchedJetJEC);
   OutputTree.Branch("MatchedJetJEU",   &MatchedJetJEU);
   OutputTree.Branch("MatchedThrust",   &RecoThrust);

   int RecoEventNumber;
   int NReco;
   float RecoPX[MAX];
   float RecoPY[MAX];
   float RecoPZ[MAX];
   float RecoP[MAX];
   float RecoE[MAX];
   float RecoTheta[MAX];
   float RecoMass[MAX];
   bool RecoHighPurity[MAX];
   bool RecoPassSTheta = true;
   bool RecoPassAll = true;
   int GenEventNumber;
   int NGen;
   float GenPX[MAX];
   float GenPY[MAX];
   float GenPZ[MAX];
   float GenP[MAX];
   float GenE[MAX];
   float GenTheta[MAX];
   float GenMass[MAX];
   int GenStatus[MAX];
   bool GenPassSTheta = true;

   OutputTree.Branch("RecoEventNumber", &RecoEventNumber, "RecoEventNumber/I");
   OutputTree.Branch("NReco",           &NReco,           "NReco/I");
   OutputTree.Branch("RecoPX",          &RecoPX,          "RecoPX[NReco]/F");
   OutputTree.Branch("RecoPY",          &RecoPY,          "RecoPY[NReco]/F");
   OutputTree.Branch("RecoPZ",          &RecoPZ,          "RecoPZ[NReco]/F");
   OutputTree.Branch("RecoP",           &RecoP,           "RecoP[NReco]/F");
   OutputTree.Branch("RecoE",           &RecoE,           "RecoE[NReco]/F");
   OutputTree.Branch("RecoTheta",       &RecoTheta,       "RecoTheta[NReco]/F");
   OutputTree.Branch("RecoMass",        &RecoMass,        "RecoMass[NReco]/F");
   OutputTree.Branch("RecoHighPurity",  &RecoHighPurity,  "RecoHighPurity[NReco]/O");
   OutputTree.Branch("RecoPassSTheta",  &RecoPassSTheta,  "RecoPassSTheta/O");
   OutputTree.Branch("RecoPassAll",     &RecoPassAll,     "RecoPassAll/O");
   OutputTree.Branch("GenEventNumber",  &GenEventNumber,  "GenEventNumber/I");
   OutputTree.Branch("NGen",            &NGen,            "NGen/I");
   OutputTree.Branch("GenPX",           &GenPX,           "GenPX[NGen]/F");
   OutputTree.Branch("GenPY",           &GenPY,           "GenPY[NGen]/F");
   OutputTree.Branch("GenPZ",           &GenPZ,           "GenPZ[NGen]/F");
   OutputTree.Branch("GenP",            &GenP,            "GenP[NGen]/F");
   OutputTree.Branch("GenE",            &GenE,            "GenE[NGen]/F");
   OutputTree.Branch("GenTheta",        &GenTheta,        "GenTheta[NGen]/F");
   OutputTree.Branch("GenMass",         &GenMass,         "GenMass[NGen]/F");
   OutputTree.Branch("GenStatus",       &GenStatus,       "GenStatus[NGen]/I");
   OutputTree.Branch("GenPassSTheta",   &GenPassSTheta,   "GenPassSTheta/O");

   int PassedEventCount = 0;

   for(string FileName : InputFileName)
   {
      TFile InputFile(FileName.c_str());

      TTree *RecoTree    = (TTree *)InputFile.Get(RecoTreeName.c_str());
      TTree *GenTree     = (TTree *)InputFile.Get(GenTreeName.c_str());
      TTree *RecoJetTree = (TTree *)InputFile.Get("akR4ESchemeJetTree");
      TTree *GenJetTree  = (TTree *)InputFile.Get("akR4ESchemeGenJetTree");

      if(RecoTree == nullptr && GenTree == nullptr)
         continue;
      if(IsMC == true && GenTree == nullptr)
         continue;

      for(int i = 0; i < MAX; i++)
         GenStatus[i] = 1;
      
      if(GenTree != nullptr)
      {
         GenTree->SetBranchAddress("EventNo",      &GenEventNumber);
         GenTree->SetBranchAddress("nParticle",    &NGen);
         GenTree->SetBranchAddress("px",           &GenPX);
         GenTree->SetBranchAddress("py",           &GenPY);
         GenTree->SetBranchAddress("pz",           &GenPZ);
         GenTree->SetBranchAddress("mass",         &GenMass);
         if(GenTree->GetBranch("status") != nullptr)
            GenTree->SetBranchAddress("status",       &GenStatus);
         GenTree->SetBranchAddress("Thrust",       &GenThrust);
         GenTree->SetBranchAddress("passesSTheta", &GenPassSTheta);
      }
      if(RecoTree != nullptr)
      {
         RecoTree->SetBranchAddress("EventNo",      &RecoEventNumber);
         RecoTree->SetBranchAddress("nParticle",    &NReco);
         RecoTree->SetBranchAddress("px",           &RecoPX);
         RecoTree->SetBranchAddress("py",           &RecoPY);
         RecoTree->SetBranchAddress("pz",           &RecoPZ);
         RecoTree->SetBranchAddress("pmag",         &RecoP);
         RecoTree->SetBranchAddress("mass",         &RecoMass);
         RecoTree->SetBranchAddress("highPurity",   &RecoHighPurity);
         RecoTree->SetBranchAddress("Thrust",       &RecoThrust);
         RecoTree->SetBranchAddress("passesAll",    &RecoPassAll);
         RecoTree->SetBranchAddress("passesSTheta", &RecoPassSTheta);
      }
      
      int NStoredRecoJet;
      float StoredRecoJetPT[MAX];
      float StoredRecoJetEta[MAX];
      float StoredRecoJetPhi[MAX];
      float StoredRecoJetM[MAX];
      if(RecoJetTree != nullptr)
      {
         RecoJetTree->SetBranchAddress("nref",  &NStoredRecoJet);
         RecoJetTree->SetBranchAddress("jtpt",  &StoredRecoJetPT);
         RecoJetTree->SetBranchAddress("jteta", &StoredRecoJetEta);
         RecoJetTree->SetBranchAddress("jtphi", &StoredRecoJetPhi);
         RecoJetTree->SetBranchAddress("jtm",   &StoredRecoJetM);
      }

      int NStoredGenJet;
      float StoredGenJetPT[MAX];
      float StoredGenJetEta[MAX];
      float StoredGenJetPhi[MAX];
      float StoredGenJetM[MAX];
      if(GenJetTree != nullptr)
      {
         GenJetTree->SetBranchAddress("nref",  &NStoredGenJet);
         GenJetTree->SetBranchAddress("jtpt",  &StoredGenJetPT);
         GenJetTree->SetBranchAddress("jteta", &StoredGenJetEta);
         GenJetTree->SetBranchAddress("jtphi", &StoredGenJetPhi);
         GenJetTree->SetBranchAddress("jtm",   &StoredGenJetM);
      }

      int GenEntryShift = 0;

      int EntryCount = 0;
      if(RecoTree != nullptr)
         EntryCount = RecoTree->GetEntries() * Fraction;
      else if(GenTree != nullptr)
         EntryCount = GenTree->GetEntries() * Fraction;
      for(int iE = 0; iE < EntryCount; iE++)
      {
         NGen = 0;
         NReco = 0;
         NStoredGenJet = 0;
         NStoredRecoJet = 0;

         if(GenTree != nullptr)       GenTree->GetEntry(iE + GenEntryShift);
         if(RecoTree != nullptr)      RecoTree->GetEntry(iE);

         if(GenTree != nullptr && RecoTree != nullptr)
         {
            while(GenEventNumber != RecoEventNumber)
            {
               GenEntryShift = GenEntryShift + 1;
               GenTree->GetEntry(iE + GenEntryShift);
            }
         }

         if(RecoJetTree != nullptr)   RecoJetTree->GetEntry(iE);
         if(GenJetTree != nullptr)    GenJetTree->GetEntry(iE);

         if(BaselineCut == true)
         {
            if(RecoPassAll == false)
               continue;
            // if(IsMC == true && GenPassSTheta == false)
            //    continue;
         }

         // if(fabs(cos(RecoSTheta)) > 0.8)
         //    continue;
         // if(IsMC == true && fabs(cos(GenSTheta)) > 0.8)
         //    continue;

         double PSum = 0;
         for(int i = 0; i < NReco; i++)
            PSum = PSum + RecoP[i];
         if(PSum > 200)   // Mercedes Benz rejection
            continue;

         GenSumE.resize(NSumE);
         for(float &N : GenSumE)
            N = 0;

         for(int i = 0; i < NGen; i++)
         {
            FourVector P(0, GenPX[i], GenPY[i], GenPZ[i]);
            P[0] = sqrt(P.GetP() * P.GetP() + GenMass[i] * GenMass[i]);
            
            GenP[i] = P.GetP();
            GenE[i] = P[0];
            GenTheta[i] = P.GetTheta();
            
            if(GenStatus[i] != 1)   // we want only final state particles
               continue;
            
            for(int j = 0; j < NSumE; j++)
               if(P.GetTheta() > SumECut[j] && P.GetTheta() < M_PI - SumECut[j])
                  GenSumE[j] = GenSumE[j] + P[0];
         }
         if(GenSumE[0] < GenSumECut)
            continue;

         RecoSumE.resize(NSumE);
         for(float &N : RecoSumE)
            N = 0;
         
         for(int i = 0; i < NReco; i++)
         {
            FourVector P(0, RecoPX[i], RecoPY[i], RecoPZ[i]);
            P[0] = sqrt(P.GetP() * P.GetP() + RecoMass[i] * RecoMass[i]);
            
            RecoE[i] = P[0];
            RecoTheta[i] = P.GetTheta();
   
            for(int j = 0; j < NSumE; j++)
               if(P.GetTheta() > SumECut[j] && P.GetTheta() < M_PI - SumECut[j])
                  RecoSumE[j] = RecoSumE[j] + P[0];
         }

         if(DoSumESmear == false)
         {
            if(RecoSumE[0] < RecoSumECut)
               continue;
         }
         else
         {
            if(RecoSumE[0] * DrawGaussian(1, SumESmear) < RecoSumECut)
               continue;
         }

         PassedEventCount = PassedEventCount + 1;

         vector<FourVector> GenParticles;
         vector<PseudoJet> GenFJParticles;
         for(int i = 0; i < NGen; i++)
         {
            if(GenStatus[i] != 1)
               continue;
            FourVector P(0, GenPX[i], GenPY[i], GenPZ[i]);
            P[0] = sqrt(P.GetP() * P.GetP() + GenMass[i] * GenMass[i]);
            GenParticles.emplace_back(P);
            GenFJParticles.emplace_back(P[1], P[2], P[3], P[0]);
         }

         vector<FourVector> RecoParticles;
         vector<PseudoJet> RecoFJParticles;
         for(int i = 0; i < NReco; i++)
         {
            FourVector P(0, RecoPX[i], RecoPY[i], RecoPZ[i]);
            P[0] = sqrt(P.GetP() * P.GetP() + RecoMass[i] * RecoMass[i]);
            RecoParticles.emplace_back(P);
            RecoFJParticles.emplace_back(P[1], P[2], P[3], P[0]);
         }

         vector<pair<FourVector, PseudoJet>> GenJets;
         vector<pair<FourVector, PseudoJet>> RecoJets;

         JetDefinition Definition(ee_genkt_algorithm, JetR, -1);
         ClusterSequence GenSequence(GenFJParticles, Definition);
         vector<PseudoJet> GenFastJets = GenSequence.inclusive_jets(0.5);
         ClusterSequence RecoSequence(RecoFJParticles, Definition);
         vector<PseudoJet> RecoFastJets = RecoSequence.inclusive_jets(0.5);

         if(UseStored == true)
         {
            GenJets.resize(NStoredGenJet);
            for(int i = 0; i < NStoredGenJet; i++)
            {
               GenJets[i].first.SetPtEtaPhiMass(StoredGenJetPT[i], StoredGenJetEta[i], StoredGenJetPhi[i], StoredGenJetM[i]);
               GenJets[i].second.reset_momentum(GenJets[i].first[1], GenJets[i].first[2], GenJets[i].first[3], GenJets[i].first[0]);
            }

            RecoJets.resize(NStoredRecoJet);
            for(int i = 0; i < NStoredRecoJet; i++)
            {
               RecoJets[i].first.SetPtEtaPhiMass(StoredRecoJetPT[i], StoredRecoJetEta[i], StoredRecoJetPhi[i], StoredRecoJetM[i]);
               RecoJets[i].second.reset_momentum(RecoJets[i].first[1], RecoJets[i].first[2], RecoJets[i].first[3], RecoJets[i].first[0]);
            }
         }
         else
         {
            for(int i = 0 ; i < (int)GenFastJets.size(); i++)
            {
               FourVector P(GenFastJets[i].e(), GenFastJets[i].px(), GenFastJets[i].py(), GenFastJets[i].pz());
               GenJets.emplace_back(pair<FourVector, PseudoJet>(P, GenFastJets[i]));
            }

            for(int i = 0 ; i < (int)RecoFastJets.size(); i++)
            {
               FourVector P(RecoFastJets[i].e(), RecoFastJets[i].px(), RecoFastJets[i].py(), RecoFastJets[i].pz());
               RecoJets.emplace_back(pair<FourVector, PseudoJet>(P, RecoFastJets[i]));
            }
         }
            
         // Apply JEC to reco jets
         for(int iR = 0; iR < (int)RecoJets.size(); iR++)
         {
            JEC.SetJetP(RecoJets[iR].first.GetP());
            JEC.SetJetTheta(RecoJets[iR].first.GetTheta());
            JEC.SetJetPhi(RecoJets[iR].first.GetPhi());
            double Correction = JEC.GetCorrection();
            if(Correction < 0)
               Correction = 1;
            RecoJets[iR].first = RecoJets[iR].first * Correction;
         }

         // Sort jets according to energy
         sort(GenJets.begin(), GenJets.end(), DecreasingEnergy);
         sort(RecoJets.begin(), RecoJets.end(), DecreasingEnergy);

         if(GenJets.size() > 0 && GenJets[0].first[0] < 10)
         {
            for(int iJ = 0; iJ < GenJets.size(); iJ++)
               cout << iJ << " " << GenJets[iJ].first[0] << " " << GenJets[iJ].first.GetTheta() << endl;
         }

         // Check leading jet if applicable
         if(CheckLeadingGenDiJet == true)
         {
            if(GenJets.size() >= 1 && GenJets[0].first.GetTheta() < ThetaMin)
               continue;
            if(GenJets.size() >= 1 && GenJets[0].first.GetTheta() > ThetaMax)
               continue;
            if(GenJets.size() >= 2 && GenJets[1].first.GetTheta() < ThetaMin)
               continue;
            if(GenJets.size() >= 2 && GenJets[1].first.GetTheta() > ThetaMax)
               continue;
         }

         // Remove jets out of the acceptance
         for(int i = 0; i < (int)GenJets.size(); i++)
         {
            if(GenJets[i].first.GetTheta() < ThetaMin || GenJets[i].first.GetTheta() > ThetaMax)
            {
               GenJets.erase(GenJets.begin() + i);
               i = i - 1;
            }
         }
         for(int i = 0; i < (int)RecoJets.size(); i++)
         {
            if(RecoJets[i].first.GetTheta() < ThetaMin || RecoJets[i].first.GetTheta() > ThetaMax)
            {
               RecoJets.erase(RecoJets.begin() + i);
               i = i - 1;
            }
         }

         // Now calculate the hybrid sums
         GenHybridE.resize(NSumE);
         for(int i = 0; i < NSumE; i++)
            GenHybridE[i] = 0;
         for(FourVector &P : GenParticles)
         {
            for(int i = 0; i < NSumE; i++)
            {
               bool Include = false;
               
               if(P.GetTheta() > SumECut[i] && P.GetTheta() < M_PI - SumECut[i])
                  Include = true;
               else
               {
                  for(pair<FourVector, PseudoJet> &Pair : GenJets)
                  {
                     FourVector &J = Pair.first;
                     if(J[0] < HybridJetMin)
                        continue;

                     if(J.GetTheta() > SumECut[i] && J.GetTheta() < M_PI - SumECut[i] && GetAngle(P, J) < JetR)
                        Include = true;
                     if(Include == true)
                        break;
                  }
               }

               if(Include == true)
                  GenHybridE[i] = GenHybridE[i] + P[0];
            }
         }

         RecoHybridE.resize(NSumE);
         for(int i = 0; i < NSumE; i++)
            RecoHybridE[i] = 0;
         for(FourVector &P : RecoParticles)
         {
            for(int i = 0; i < NSumE; i++)
            {
               bool Include = false;
               
               if(P.GetTheta() > SumECut[i] && P.GetTheta() < M_PI - SumECut[i])
                  Include = true;
               else
               {
                  for(pair<FourVector, PseudoJet> &Pair : RecoJets)
                  {
                     FourVector &J = Pair.first;
                     if(J[0] < HybridJetMin)
                        continue;

                     if(J.GetTheta() > SumECut[i] && J.GetTheta() < M_PI - SumECut[i] && GetAngle(P, J) < JetR)
                        Include = true;
                     if(Include == true)
                        break;
                  }
               }

               if(Include == true)
                  RecoHybridE[i] = RecoHybridE[i] + P[0];
            }
         }


         // Calculate groomed quantities for gen jets
         GenJetZG.resize(GenJets.size());
         GenJetRG.resize(GenJets.size());
         GenJetPG.resize(GenJets.size());
         GenJetMG.resize(GenJets.size());
         GenJetNG.resize(GenJets.size());
         for(int i = 0; i < (int)GenJets.size(); i++)
         {
            vector<Node *> Nodes;
            if(UseStored == true || GenJets[i].second.has_constituents() == false)
            {
               for(FourVector V : GenParticles)
                  if(GetAngle(GenJets[i].first, V) < JetR)
                     Nodes.push_back(new Node(V));
            }
            else   // we cluster jets ourselves.  We get the constituents!
            {
               vector<PseudoJet> Constituents = GenJets[i].second.constituents();
               for(PseudoJet &P : Constituents)
               {
                  FourVector V(P.e(), P.px(), P.py(), P.pz());
                  Nodes.push_back(new Node(V));
               }
            }
            BuildCATree(Nodes);
         
            GenJetZG[i].resize(NSD);
            GenJetRG[i].resize(NSD);
            GenJetPG[i].resize(NSD);
            GenJetMG[i].resize(NSD);
            GenJetNG[i].resize(NSD);

            if(Nodes.size() > 0)
            {
               for(int iSD = 0; iSD < NSD; iSD++)
               {
                  Node *SDNode = FindSDNodeE(Nodes[0], SDZCut[iSD], SDBeta[iSD]);
                  if(SDNode != nullptr && SDNode->Child1 != nullptr && SDNode->Child2 != nullptr)
                  {
                     FourVector &P1 = SDNode->Child1->P;
                     FourVector &P2 = SDNode->Child2->P;
                     GenJetZG[i][iSD] = P2.GetP() / (P1.GetP() + P2.GetP());
                     GenJetRG[i][iSD] = GetAngle(P1, P2);
                     GenJetPG[i][iSD] = SDNode->P.GetP();
                     GenJetMG[i][iSD] = SDNode->P.GetMass();
                     GenJetNG[i][iSD] = CountFinalNode(SDNode);
                  }
                  else
                  {
                     GenJetZG[i][iSD] = -1;
                     GenJetRG[i][iSD] = -1;
                     GenJetPG[i][iSD] = -1;
                     GenJetMG[i][iSD] = -1;
                     GenJetNG[i][iSD] = -1;
                  }
               }
            }
         }

         RecoJetZG.resize(RecoJets.size());
         RecoJetRG.resize(RecoJets.size());
         RecoJetPG.resize(RecoJets.size());
         RecoJetMG.resize(RecoJets.size());
         RecoJetNG.resize(RecoJets.size());
         for(int i = 0; i < (int)RecoJets.size(); i++)
         {
            vector<Node *> Nodes;
            if(UseStored == true || RecoJets[i].second.has_constituents() == false)
            {
               for(FourVector V : RecoParticles)
                  if(GetAngle(RecoJets[i].first, V) < JetR)
                     Nodes.push_back(new Node(V));
            }
            else   // we cluster jets ourselves.  We get the constituents!
            {
               vector<PseudoJet> Constituents = RecoJets[i].second.constituents();
               for(PseudoJet &P : Constituents)
               {
                  FourVector V(P.e(), P.px(), P.py(), P.pz());
                  Nodes.push_back(new Node(V));
               }
            }
            BuildCATree(Nodes);
            
            RecoJetZG[i].resize(NSD);
            RecoJetRG[i].resize(NSD);
            RecoJetPG[i].resize(NSD);
            RecoJetMG[i].resize(NSD);
            RecoJetNG[i].resize(NSD);

            if(Nodes.size() > 0)
            {
               for(int iSD = 0; iSD < NSD; iSD++)
               {
                  Node *SDNode = FindSDNodeE(Nodes[0], SDZCut[iSD], SDBeta[iSD]);
                  if(SDNode != nullptr && SDNode->Child1 != nullptr && SDNode->Child2 != nullptr)
                  {
                     FourVector &P1 = SDNode->Child1->P;
                     FourVector &P2 = SDNode->Child2->P;
                     RecoJetZG[i][iSD] = P2.GetP() / (P1.GetP() + P2.GetP());
                     RecoJetRG[i][iSD] = GetAngle(P1, P2);
                     RecoJetPG[i][iSD] = SDNode->P.GetP();
                     RecoJetMG[i][iSD] = SDNode->P.GetMass();
                     RecoJetNG[i][iSD] = CountFinalNode(SDNode);
                  }
                  else
                  {
                     RecoJetZG[i][iSD] = -1;
                     RecoJetRG[i][iSD] = -1;
                     RecoJetPG[i][iSD] = -1;
                     RecoJetMG[i][iSD] = -1;
                     RecoJetNG[i][iSD] = -1;
                  }
               }
            }
         }

         // Gen & reco jets
         NRecoJets = RecoJets.size();
         RecoJetPX.resize(NRecoJets);
         RecoJetPY.resize(NRecoJets);
         RecoJetPZ.resize(NRecoJets);
         RecoJetM.resize(NRecoJets);
         RecoJetE.resize(NRecoJets);
         RecoJetP.resize(NRecoJets);
         RecoJetTheta.resize(NRecoJets);
         RecoJetPhi.resize(NRecoJets);
         RecoJetJEC.resize(NRecoJets);
         RecoJetJEU.resize(NRecoJets);
         for(int iR = 0; iR < NRecoJets; iR++)
         {
            // double Correction = RecoJets[iR].first[0] / RecoJets[iR].second.e();
            double Correction = 1;
            double Uncertainty = 0.005;
            
            RecoJetPX[iR]    = RecoJets[iR].first[1];
            RecoJetPY[iR]    = RecoJets[iR].first[2];
            RecoJetPZ[iR]    = RecoJets[iR].first[3];
            RecoJetM[iR]     = RecoJets[iR].first.GetMass();
            RecoJetE[iR]     = RecoJets[iR].first[0];
            RecoJetP[iR]     = RecoJets[iR].first.GetP();
            RecoJetTheta[iR] = RecoJets[iR].first.GetTheta();
            RecoJetPhi[iR]   = RecoJets[iR].first.GetPhi();
            RecoJetJEC[iR]   = Correction;
            RecoJetJEU[iR]   = Uncertainty;
            
            for(int iSD = 0; iSD < NSD; iSD++)
            {
               RecoJetPG[iR][iSD] = RecoJetPG[iR][iSD] * Correction;
               RecoJetMG[iR][iSD] = RecoJetMG[iR][iSD] * Correction;
            }
         }
         
         NGenJets = GenJets.size();
         GenJetPX.resize(NGenJets);
         GenJetPY.resize(NGenJets);
         GenJetPZ.resize(NGenJets);
         GenJetM.resize(NGenJets);
         GenJetE.resize(NGenJets);
         GenJetP.resize(NGenJets);
         GenJetTheta.resize(NGenJets);
         GenJetPhi.resize(NGenJets);
         for(int iR = 0; iR < NGenJets; iR++)
         {
            GenJetPX[iR]    = GenJets[iR].first[1];
            GenJetPY[iR]    = GenJets[iR].first[2];
            GenJetPZ[iR]    = GenJets[iR].first[3];
            GenJetM[iR]     = GenJets[iR].first.GetMass();
            GenJetE[iR]     = GenJets[iR].first[0];
            GenJetP[iR]     = GenJets[iR].first.GetP();
            GenJetTheta[iR] = GenJets[iR].first.GetTheta();
            GenJetPhi[iR]   = GenJets[iR].first.GetPhi();
         }

         // Match reco to gen jets
         MatchedJetPX.resize(NGenJets);
         MatchedJetPY.resize(NGenJets);
         MatchedJetPZ.resize(NGenJets);
         MatchedJetM.resize(NGenJets);
         MatchedJetE.resize(NGenJets);
         MatchedJetP.resize(NGenJets);
         MatchedJetTheta.resize(NGenJets);
         MatchedJetPhi.resize(NGenJets);
         MatchedJetAngle.resize(NGenJets);
         MatchedJetJEC.resize(NGenJets);
         MatchedJetJEU.resize(NGenJets);
         MatchedJetZG.resize(NGenJets);
         MatchedJetRG.resize(NGenJets);
         MatchedJetPG.resize(NGenJets);
         MatchedJetMG.resize(NGenJets);
         MatchedJetNG.resize(NGenJets);
         for(int iG = 0; iG < NGenJets; iG++)
         {
            MatchedJetAngle[iG] = -1;

            int BestIndex = -1;
            double BestAngle = -1;
            for(int iR = 0; iR < NRecoJets; iR++)
            {
               double Angle = GetAngle(GenJets[iG].first, RecoJets[iR].first);
               if(BestAngle < 0 || Angle < BestAngle)
               {
                  BestIndex = iR;
                  BestAngle = Angle;
               }
            }

            MatchedJetZG[iG].resize(NSD, -1);
            MatchedJetRG[iG].resize(NSD, -1);
            MatchedJetPG[iG].resize(NSD, -1);
            MatchedJetMG[iG].resize(NSD, -1);
            MatchedJetNG[iG].resize(NSD, -1);

            if(BestIndex < 0)   // WTF
               continue;

            // Fill output tree with matched jets
            MatchedJetPX[iG]    = RecoJets[BestIndex].first[1];
            MatchedJetPY[iG]    = RecoJets[BestIndex].first[2];
            MatchedJetPZ[iG]    = RecoJets[BestIndex].first[3];
            MatchedJetM[iG]     = RecoJets[BestIndex].first.GetMass();
            MatchedJetE[iG]     = RecoJets[BestIndex].first[0];
            MatchedJetP[iG]     = RecoJets[BestIndex].first.GetP();
            MatchedJetTheta[iG] = RecoJets[BestIndex].first.GetTheta();
            MatchedJetPhi[iG]   = RecoJets[BestIndex].first.GetPhi();
            MatchedJetAngle[iG] = BestAngle;
            MatchedJetJEC[iG]   = RecoJetJEC[BestIndex];
            MatchedJetJEU[iG]   = RecoJetJEU[BestIndex];
            for(int iSD = 0; iSD < NSD; iSD++)
            {
               MatchedJetZG[iG][iSD] = RecoJetZG[BestIndex][iSD];
               MatchedJetRG[iG][iSD] = RecoJetRG[BestIndex][iSD];
               MatchedJetPG[iG][iSD] = RecoJetPG[BestIndex][iSD];
               MatchedJetMG[iG][iSD] = RecoJetMG[BestIndex][iSD];
               MatchedJetNG[iG][iSD] = RecoJetNG[BestIndex][iSD];
            }
         }

         OutputTree.Fill();
      }

      InputFile.Close();
   }

   OutputFile.cd();
   OutputTree.Write();

   TNamed Count;
   Count.SetNameTitle("EventCount", Form("%d", PassedEventCount));
   Count.Write();

   OutputFile.Close();

   return 0;
}

int FindBin(int N, double Bins[], double X)
{
   if(X < Bins[0])
      return -1;
   for(int i = 1; i <= N; i++)
      if(X < Bins[i])
         return i - 1;
   return N - 1;
}

bool DecreasingEnergy(pair<FourVector, PseudoJet> &V1, pair<FourVector, PseudoJet> &V2)
{
   return V1.first[0] > V2.first[0];
}










