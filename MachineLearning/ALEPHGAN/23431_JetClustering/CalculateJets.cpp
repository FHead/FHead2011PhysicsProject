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
bool DecreasingEnergy(FourVector &V1, FourVector &V2);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileName  = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   bool IsMC                     = CL.GetBool("MC", true);
   bool BaselineCut              = CL.GetBool("BaselineCut", false);
   bool UseStored                = CL.GetBool("UseStored", false);
   double ThetaMin               = CL.GetDouble("ThetaMin", 0);
   double ThetaMax               = CL.GetDouble("ThetaMax", M_PI);
   double GanSumECut             = CL.GetDouble("GanSumECut", -99999);
   vector<string> JECFiles       = CL.GetStringVector("JEC", vector<string>{});
   double Fraction               = CL.GetDouble("Fraction", 1.00);
   double JetR                   = CL.GetDouble("JetR", 0.4);
   string GanTreeName            = CL.Get("GanTreeName", "tgan");

   JetCorrector JEC(JECFiles);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("UnfoldingTree", "Trees for unfolding studies");

   int NSD = 2;
   vector<float> SDZCut{0.1, 0.5};
   vector<float> SDBeta{0.0, 1.5};
   float GanSumE;
   int NGanJets;
   vector<float> GanJetPX;
   vector<float> GanJetPY;
   vector<float> GanJetPZ;
   vector<float> GanJetP;
   vector<float> GanJetTheta;
   vector<float> GanJetPhi;
   vector<float> GanJetE;
   vector<vector<float>> GanJetZG;
   vector<vector<float>> GanJetRG;
   vector<vector<float>> GanJetPG;
   vector<vector<float>> GanJetMG;
   vector<vector<float>> GanJetNG;
   float GanThrust = -1;

   OutputTree.Branch("NSD",             &NSD, "NSD/I");
   OutputTree.Branch("SDZCut",          &SDZCut);
   OutputTree.Branch("SDBeta",          &SDBeta);
   OutputTree.Branch("GanSumE",         &GanSumE, "GanSumE/F");
   OutputTree.Branch("NGanJets",        &NGanJets, "NGanJets/I");
   OutputTree.Branch("GanJetPX",        &GanJetPX);
   OutputTree.Branch("GanJetPY",        &GanJetPY);
   OutputTree.Branch("GanJetPZ",        &GanJetPZ);
   OutputTree.Branch("GanJetP",         &GanJetP);
   OutputTree.Branch("GanJetTheta",     &GanJetTheta);
   OutputTree.Branch("GanJetPhi",       &GanJetPhi);
   OutputTree.Branch("GanJetE",         &GanJetE);
   OutputTree.Branch("GanJetZG",        &GanJetZG);
   OutputTree.Branch("GanJetRG",        &GanJetRG);
   OutputTree.Branch("GanJetPG",        &GanJetPG);
   OutputTree.Branch("GanJetMG",        &GanJetMG);
   OutputTree.Branch("GanJetNG",        &GanJetNG);
   OutputTree.Branch("GanThrust",       &GanThrust);

   int PassedEventCount = 0;

   for(string FileName : InputFileName)
   {
      TFile InputFile(FileName.c_str());

      TTree *GanTree     = (TTree *)InputFile.Get(GanTreeName.c_str());

      if(GanTree == nullptr)
         continue;
      if(IsMC == true && GanTree == nullptr)
         continue;

      int NGan;
      float GanPX[MAX];
      float GanPY[MAX];
      float GanPZ[MAX];
      float GanMass[MAX];
      int GanStatus[MAX];
      bool GanPassSTheta = true;

      for(int i = 0; i < MAX; i++)
         GanStatus[i] = 1;
      
      if(GanTree != nullptr)
      {
         GanTree->SetBranchAddress("nParticle",    &NGan);
         GanTree->SetBranchAddress("px",           &GanPX);
         GanTree->SetBranchAddress("py",           &GanPY);
         GanTree->SetBranchAddress("pz",           &GanPZ);
         GanTree->SetBranchAddress("mass",         &GanMass);
         if(GanTree->GetBranch("status") != nullptr)
            GanTree->SetBranchAddress("status",       &GanStatus);
      }
      
      int EntryCount = 0;
      if(GanTree != nullptr)
         EntryCount = GanTree->GetEntries() * Fraction;
      for(int iE = 0; iE < EntryCount; iE++)
      {
         NGan = 0;

         if(GanTree != nullptr)       GanTree->GetEntry(iE);

         GanSumE = 0;
         for(int i = 0; i < NGan; i++)
         {
            if(GanStatus[i] != 1)   // we want only final state particles
               continue;
            FourVector P(0, GanPX[i], GanPY[i], GanPZ[i]);
            P[0] = sqrt(P.GetP() * P.GetP() + GanMass[i] * GanMass[i]);
            if(P.GetTheta() < ThetaMin || P.GetTheta() > ThetaMax)
               continue;
            GanSumE = GanSumE + P[0];
         }
         if(GanSumE < GanSumECut)
            continue;

         PassedEventCount = PassedEventCount + 1;

         vector<FourVector> GanParticles;
         vector<PseudoJet> GanFJParticles;
         for(int i = 0; i < NGan; i++)
         {
            if(GanStatus[i] != 1)
               continue;
            FourVector P(0, GanPX[i], GanPY[i], GanPZ[i]);
            P[0] = sqrt(P.GetP() * P.GetP() + GanMass[i] * GanMass[i]);
            GanParticles.emplace_back(P);
            GanFJParticles.emplace_back(P[1], P[2], P[3], P[0]);
         }

         vector<FourVector> GanJets;

         JetDefinition Definition(ee_genkt_algorithm, JetR, -1);
         ClusterSequence GanSequence(GanFJParticles, Definition);
         vector<PseudoJet> GanFastJets = GanSequence.inclusive_jets(0.5);

         for(int i = 0 ; i < (int)GanFastJets.size(); i++)
         {
            FourVector P(GanFastJets[i].e(), GanFastJets[i].px(), GanFastJets[i].py(), GanFastJets[i].pz());
            if(P.GetTheta() < ThetaMin || P.GetTheta() > ThetaMax)
               continue;
            GanJets.emplace_back(P);
         }
            
         sort(GanJets.begin(), GanJets.end(), DecreasingEnergy);

         GanJetZG.resize(GanJets.size());
         GanJetRG.resize(GanJets.size());
         GanJetPG.resize(GanJets.size());
         GanJetMG.resize(GanJets.size());
         GanJetNG.resize(GanJets.size());
         for(int i = 0; i < (int)GanJets.size(); i++)
         {
            vector<Node *> Nodes;
            for(FourVector V : GanParticles)
               if(GetAngle(GanJets[i], V) < JetR)
                  Nodes.push_back(new Node(V));
            BuildCATree(Nodes);
         
            GanJetZG[i].resize(NSD);
            GanJetRG[i].resize(NSD);
            GanJetPG[i].resize(NSD);
            GanJetMG[i].resize(NSD);
            GanJetNG[i].resize(NSD);

            if(Nodes.size() > 0)
            {
               for(int iSD = 0; iSD < NSD; iSD++)
               {
                  Node *SDNode = FindSDNodeE(Nodes[0], SDZCut[iSD], SDBeta[iSD]);
                  if(SDNode != nullptr && SDNode->Child1 != nullptr && SDNode->Child2 != nullptr)
                  {
                     FourVector &P1 = SDNode->Child1->P;
                     FourVector &P2 = SDNode->Child2->P;
                     GanJetZG[i][iSD] = P2.GetP() / (P1.GetP() + P2.GetP());
                     GanJetRG[i][iSD] = GetAngle(P1, P2);
                     GanJetPG[i][iSD] = SDNode->P.GetP();
                     GanJetMG[i][iSD] = SDNode->P.GetMass();
                     GanJetNG[i][iSD] = CountFinalNode(SDNode);
                  }
                  else
                  {
                     GanJetZG[i][iSD] = -1;
                     GanJetRG[i][iSD] = -1;
                     GanJetPG[i][iSD] = -1;
                     GanJetMG[i][iSD] = -1;
                     GanJetNG[i][iSD] = -1;
                  }
               }
            }
         }

         NGanJets = GanJets.size();
         GanJetPX.resize(NGanJets);
         GanJetPY.resize(NGanJets);
         GanJetPZ.resize(NGanJets);
         GanJetE.resize(NGanJets);
         GanJetP.resize(NGanJets);
         GanJetTheta.resize(NGanJets);
         GanJetPhi.resize(NGanJets);
         for(int iR = 0; iR < NGanJets; iR++)
         {
            GanJetPX[iR]    = GanJets[iR][1];
            GanJetPY[iR]    = GanJets[iR][2];
            GanJetPZ[iR]    = GanJets[iR][3];
            GanJetE[iR]     = GanJets[iR][0];
            GanJetP[iR]     = GanJets[iR].GetP();
            GanJetTheta[iR] = GanJets[iR].GetTheta();
            GanJetPhi[iR]   = GanJets[iR].GetPhi();
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

bool DecreasingEnergy(FourVector &V1, FourVector &V2)
{
   return V1[0] > V2[0];
}










