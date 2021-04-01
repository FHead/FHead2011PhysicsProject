#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TDirectory.h"

#include "Code/TauHelperFunctions3.h"
#include "SetStyle.h"
#include "CommandLine.h"
#include "ProgressBar.h"
#include "CustomAssert.h"

#include "Messenger.h"

struct GenParticle;
int main(int argc, char *argv[]);
bool SortByPT(const GenParticle &V1, const GenParticle &V2);
FourVector GetVisTauAdhoc(L1GenMessenger &MGen, int Index);
pair<int, int> FindBestTwo(vector<GenericObject> &V, FourVector P1, FourVector P2, double DR, bool CheckFlag = false);
double CalculateGenIsolation(FourVector &P, vector<FourVector> &Particles, double DR);

struct GenParticle
{
   FourVector P;
   int Parent;
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   // Some root styling
   SetThesisStyle();

   // Get arguments
   vector<string> InputFileNames = CL.GetStringVector("input", ',');
   string OutputFileName         = CL.Get("output");

   // Output File
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   // Output tree
   int GenTauCount;
   double GenTau1PT, GenTau1Eta, GenTau1Phi;   int GenTau1Parent;
   double GenTau2PT, GenTau2Eta, GenTau2Phi;   int GenTau2Parent;
   double CaloTau1PT, CaloTau1Eta, CaloTau1Phi, CaloTau1VZ;
   double CaloTau2PT, CaloTau2Eta, CaloTau2Phi, CaloTau2VZ;
   double TkEGTau1PT, TkEGTau1Eta, TkEGTau1Phi, TkEGTau1VZ;
   double TkEGTau2PT, TkEGTau2Eta, TkEGTau2Phi, TkEGTau2VZ;
   double NNPFTau1PT, NNPFTau1Eta, NNPFTau1Phi, NNPFTau1VZ;
   double NNPFTau2PT, NNPFTau2Eta, NNPFTau2Phi, NNPFTau2VZ;
   double GenTauDR, CaloTauDR, TkEGTauDR, NNPFTauDR;
   TTree OutputTree("Tree", "Tree");
   OutputTree.Branch("GenTauCount",   &GenTauCount,   "GenTauCount/I");
   OutputTree.Branch("GenTau1PT",     &GenTau1PT,     "GenTau1PT/D");
   OutputTree.Branch("GenTau1Eta",    &GenTau1Eta,    "GenTau1Eta/D");
   OutputTree.Branch("GenTau1Phi",    &GenTau1Phi,    "GenTau1Phi/D");
   OutputTree.Branch("GenTau1Parent", &GenTau1Parent, "GenTau1Parent/I");
   OutputTree.Branch("GenTau2PT",     &GenTau2PT,     "GenTau2PT/D");
   OutputTree.Branch("GenTau2Eta",    &GenTau2Eta,    "GenTau2Eta/D");
   OutputTree.Branch("GenTau2Phi",    &GenTau2Phi,    "GenTau2Phi/D");
   OutputTree.Branch("GenTau2Parent", &GenTau2Parent, "GenTau2Parent/I");
   OutputTree.Branch("CaloTau1PT",    &CaloTau1PT,    "CaloTau1PT/D");
   OutputTree.Branch("CaloTau1Eta",   &CaloTau1Eta,   "CaloTau1Eta/D");
   OutputTree.Branch("CaloTau1Phi",   &CaloTau1Phi,   "CaloTau1Phi/D");
   OutputTree.Branch("CaloTau1VZ",    &CaloTau1VZ,    "CaloTau1VZ/D");
   OutputTree.Branch("CaloTau2PT",    &CaloTau2PT,    "CaloTau2PT/D");
   OutputTree.Branch("CaloTau2Eta",   &CaloTau2Eta,   "CaloTau2Eta/D");
   OutputTree.Branch("CaloTau2Phi",   &CaloTau2Phi,   "CaloTau2Phi/D");
   OutputTree.Branch("CaloTau2VZ",    &CaloTau2VZ,    "CaloTau2VZ/D");
   OutputTree.Branch("TkEGTau1PT",    &TkEGTau1PT,    "TkEGTau1PT/D");
   OutputTree.Branch("TkEGTau1Eta",   &TkEGTau1Eta,   "TkEGTau1Eta/D");
   OutputTree.Branch("TkEGTau1Phi",   &TkEGTau1Phi,   "TkEGTau1Phi/D");
   OutputTree.Branch("TkEGTau1VZ",    &TkEGTau1VZ,    "TkEGTau1VZ/D");
   OutputTree.Branch("TkEGTau2PT",    &TkEGTau2PT,    "TkEGTau2PT/D");
   OutputTree.Branch("TkEGTau2Eta",   &TkEGTau2Eta,   "TkEGTau2Eta/D");
   OutputTree.Branch("TkEGTau2Phi",   &TkEGTau2Phi,   "TkEGTau2Phi/D");
   OutputTree.Branch("TkEGTau2VZ",    &TkEGTau2VZ,    "TkEGTau2VZ/D");
   OutputTree.Branch("NNPFTau1PT",    &NNPFTau1PT,    "NNPFTau1PT/D");
   OutputTree.Branch("NNPFTau1Eta",   &NNPFTau1Eta,   "NNPFTau1Eta/D");
   OutputTree.Branch("NNPFTau1Phi",   &NNPFTau1Phi,   "NNPFTau1Phi/D");
   OutputTree.Branch("NNPFTau1VZ",    &NNPFTau1VZ,    "NNPFTau1VZ/D");
   OutputTree.Branch("NNPFTau2PT",    &NNPFTau2PT,    "NNPFTau2PT/D");
   OutputTree.Branch("NNPFTau2Eta",   &NNPFTau2Eta,   "NNPFTau2Eta/D");
   OutputTree.Branch("NNPFTau2Phi",   &NNPFTau2Phi,   "NNPFTau2Phi/D");
   OutputTree.Branch("NNPFTau2VZ",    &NNPFTau2VZ,    "NNPFTau2VZ/D");
   OutputTree.Branch("GenTauDR",      &GenTauDR,      "GenTauDR/D");
   OutputTree.Branch("CaloTauDR",     &CaloTauDR,     "CaloTauDR/D");
   OutputTree.Branch("TkEGTauDR",     &TkEGTauDR,     "TkEGTauDR/D");
   OutputTree.Branch("NNPFTauDR",     &NNPFTauDR,     "NNPFTauDR/D");

   for(string InputFileName : InputFileNames)
   {
      cout << "Processing file " << InputFileName << endl;

      // Input File
      TFile File(InputFileName.c_str());

      // Messengers
      L1GenMessenger MGen(File, "genTree/L1GenTree");
      L1PhaseIITreeV10p4Messenger MPhaseII(File, "l1PhaseIITree/L1PhaseIITree");

      if(MGen.Tree == nullptr || MPhaseII.Tree == nullptr)
         continue;

      // Loop over events
      int EntryCount = MGen.Tree->GetEntries();
      ProgressBar Bar(cout, EntryCount);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         Bar.Print();

         MGen.GetEntry(iE);
         MPhaseII.GetEntry(iE);

         vector<GenParticle> Taus, VisTaus;
         vector<FourVector> Particles;
         
         // Collect gen-particles
         for(int i = 0; i < (int)MGen.GenP.size(); i++)
         {
            int AbsID = MGen.GenID[i];
            if(AbsID < 0)
               AbsID = -AbsID;

            if(AbsID == 12 || AbsID == 14 || AbsID == 16)
               continue;

            if(AbsID == 15)
            {
               FourVector P = GetVisTauAdhoc(MGen, i);
               if(P.GetAbsEta() < 2.1)
               {
                  GenParticle G;
                  G.Parent = MGen.GenParent[i];

                  if(P[0] > 0)
                  {
                     G.P = P;
                     VisTaus.push_back(G);
                  }

                  G.P = MGen.GenP[i];
                  Taus.push_back(G);
               }
            }

            if(MGen.GenStatus[i] == 1)   // we only want final state particles here
               Particles.push_back(MGen.GenP[i]);
         }

         for(int i = 0; i < (int)Taus.size(); i++)
         {
            double Isolation = CalculateGenIsolation(Taus[i].P, Particles, 0.3);
            if(Isolation > 0.15)
            {
               Taus.erase(Taus.begin() + i);
               i = i - 1;
            }
         }
         for(int i = 0; i < (int)VisTaus.size(); i++)
         {
            double Isolation = CalculateGenIsolation(VisTaus[i].P, Particles, 0.3);
            if(Isolation > 0.15)
            {
               VisTaus.erase(VisTaus.begin() + i);
               i = i - 1;
            }
         }

         sort(Taus.begin(), Taus.end(), SortByPT);
         sort(VisTaus.begin(), VisTaus.end(), SortByPT);

         FourVector Tau1(-1, 0, 0, 0), Tau2(-1, 0, 0, 0);
         if(VisTaus.size() > 0)   Tau1 = VisTaus[0].P;
         if(VisTaus.size() > 1)   Tau2 = VisTaus[1].P;

         // Find the best L1 object
         pair<int, int> CaloTauIndex = FindBestTwo(MPhaseII.CaloTau, Tau1, Tau2, 0.30);
         pair<int, int> TkEGTauIndex = FindBestTwo(MPhaseII.TkEGTau, Tau1, Tau2, 0.15);
         pair<int, int> NNPFTauIndex = FindBestTwo(MPhaseII.NNTauLoose, Tau1, Tau2, 0.20, true);
      
         // Write outputs
         GenTauCount = 0;
         GenTau1PT = -1, GenTau1Eta = 0, GenTau1Phi = 0;   GenTau1Parent = 0;
         GenTau2PT = -1, GenTau2Eta = 0, GenTau2Phi = 0;   GenTau2Parent = 0;
         CaloTau1PT = -1, CaloTau1Eta = 0, CaloTau1Phi = 0, CaloTau1VZ = 0;
         CaloTau2PT = -1, CaloTau2Eta = 0, CaloTau2Phi = 0, CaloTau2VZ = 0;
         TkEGTau1PT = -1, TkEGTau1Eta = 0, TkEGTau1Phi = 0, TkEGTau1VZ = 0;
         TkEGTau2PT = -1, TkEGTau2Eta = 0, TkEGTau2Phi = 0, TkEGTau2VZ = 0;
         NNPFTau1PT = -1, NNPFTau1Eta = 0, NNPFTau1Phi = 0, NNPFTau1VZ = 0;
         NNPFTau2PT = -1, NNPFTau2Eta = 0, NNPFTau2Phi = 0, NNPFTau2VZ = 0;
         GenTauDR = 0, CaloTauDR = 0, TkEGTauDR = 0, NNPFTauDR = 0;

         GenTauCount = VisTaus.size();
         if(VisTaus.size() > 0)
         {
            GenTau1PT  = VisTaus[0].P.GetPT();
            GenTau1Eta = VisTaus[0].P.GetEta();
            GenTau1Phi = VisTaus[0].P.GetPhi();
            GenTau1Parent = VisTaus[0].Parent;
         }
         if(VisTaus.size() > 1)
         {
            GenTau2PT  = VisTaus[1].P.GetPT();
            GenTau2Eta = VisTaus[1].P.GetEta();
            GenTau2Phi = VisTaus[1].P.GetPhi();
            GenTau2Parent = VisTaus[1].Parent;
            GenTauDR = GetDR(VisTaus[0].P, VisTaus[1].P);
         }

         if(CaloTauIndex.first >= 0)
         {
            CaloTau1PT  = MPhaseII.CaloTau[CaloTauIndex.first].P.GetPT();
            CaloTau1Eta = MPhaseII.CaloTau[CaloTauIndex.first].P.GetEta();
            CaloTau1Phi = MPhaseII.CaloTau[CaloTauIndex.first].P.GetPhi();
            CaloTau1VZ  = MPhaseII.CaloTau[CaloTauIndex.first].VZ;
         }
         if(CaloTauIndex.second >= 0)
         {
            CaloTau2PT  = MPhaseII.CaloTau[CaloTauIndex.second].P.GetPT();
            CaloTau2Eta = MPhaseII.CaloTau[CaloTauIndex.second].P.GetEta();
            CaloTau2Phi = MPhaseII.CaloTau[CaloTauIndex.second].P.GetPhi();
            CaloTau2VZ  = MPhaseII.CaloTau[CaloTauIndex.second].VZ;
         }
         if(CaloTauIndex.first >= 0 && CaloTauIndex.second >= 0)
            CaloTauDR = GetDR(MPhaseII.CaloTau[CaloTauIndex.first].P, MPhaseII.CaloTau[CaloTauIndex.second].P);

         if(TkEGTauIndex.first >= 0)
         {
            TkEGTau1PT  = MPhaseII.TkEGTau[TkEGTauIndex.first].P.GetPT();
            TkEGTau1Eta = MPhaseII.TkEGTau[TkEGTauIndex.first].P.GetEta();
            TkEGTau1Phi = MPhaseII.TkEGTau[TkEGTauIndex.first].P.GetPhi();
            TkEGTau1VZ  = MPhaseII.TkEGTau[TkEGTauIndex.first].VZ;
         }
         if(TkEGTauIndex.second >= 0)
         {
            TkEGTau2PT  = MPhaseII.TkEGTau[TkEGTauIndex.second].P.GetPT();
            TkEGTau2Eta = MPhaseII.TkEGTau[TkEGTauIndex.second].P.GetEta();
            TkEGTau2Phi = MPhaseII.TkEGTau[TkEGTauIndex.second].P.GetPhi();
            TkEGTau2VZ  = MPhaseII.TkEGTau[TkEGTauIndex.second].VZ;
         }
         if(TkEGTauIndex.first >= 0 && TkEGTauIndex.second >= 0)
            TkEGTauDR = GetDR(MPhaseII.TkEGTau[TkEGTauIndex.first].P, MPhaseII.TkEGTau[TkEGTauIndex.second].P);

         if(NNPFTauIndex.first >= 0)
         {
            NNPFTau1PT  = MPhaseII.NNTauLoose[NNPFTauIndex.first].P.GetPT();
            NNPFTau1Eta = MPhaseII.NNTauLoose[NNPFTauIndex.first].P.GetEta();
            NNPFTau1Phi = MPhaseII.NNTauLoose[NNPFTauIndex.first].P.GetPhi();
            NNPFTau1VZ  = MPhaseII.NNTauLoose[NNPFTauIndex.first].VZ;
         }
         if(NNPFTauIndex.second >= 0)
         {
            NNPFTau2PT  = MPhaseII.NNTauLoose[NNPFTauIndex.second].P.GetPT();
            NNPFTau2Eta = MPhaseII.NNTauLoose[NNPFTauIndex.second].P.GetEta();
            NNPFTau2Phi = MPhaseII.NNTauLoose[NNPFTauIndex.second].P.GetPhi();
            NNPFTau2VZ  = MPhaseII.NNTauLoose[NNPFTauIndex.second].VZ;
         }
         if(NNPFTauIndex.first >= 0 && NNPFTauIndex.second >= 0)
            NNPFTauDR = GetDR(MPhaseII.NNTauLoose[NNPFTauIndex.first].P, MPhaseII.NNTauLoose[NNPFTauIndex.second].P);

         OutputTree.Fill();
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   // Write result to file
   OutputFile.cd();
   OutputTree.Write();

   // Clean up
   OutputFile.Close();

   // Yay
   return 0;
}

bool SortByPT(const GenParticle &V1, const GenParticle &V2)
{
   if(V1.P.InnerGetPT()  > V2.P.InnerGetPT())    return true;
   if(V1.P.InnerGetPT()  < V2.P.InnerGetPT())    return false;
   if(V1.P.InnerGetEta() > V2.P.InnerGetEta())   return true;
   if(V1.P.InnerGetEta() < V2.P.InnerGetEta())   return false;
   if(V1.P.InnerGetPhi() > V2.P.InnerGetPhi())   return true;
   if(V1.P.InnerGetPhi() < V2.P.InnerGetPhi())   return false;
   if(V1.P[0] > V2.P[0])                         return true;
   if(V1.P[0] < V2.P[0])                         return false;
   if(V1.Parent < V2.Parent)                     return true;
   if(V1.Parent > V2.Parent)                     return false;
   return false;
}

FourVector GetVisTauAdhoc(L1GenMessenger &MGen, int Index)
{
   int ID = MGen.GenID[Index];

   FourVector P;
   bool LeptonicDecay = false;

   for(int i = 0; i < (int)MGen.GenID.size(); i++)
   {
      if(MGen.GenParent[i] != ID)
         continue;

      if(MGen.GenID[i] == 11 || MGen.GenID[i] == -11)
         LeptonicDecay = true;
      if(MGen.GenID[i] == 13 || MGen.GenID[i] == -13)
         LeptonicDecay = true;

      if(MGen.GenID[i] == 12 || MGen.GenID[i] == -12)
         continue;
      if(MGen.GenID[i] == 14 || MGen.GenID[i] == -14)
         continue;
      if(MGen.GenID[i] == 16 || MGen.GenID[i] == -16)
         continue;

      P = P + MGen.GenP[i];
   }

   if(LeptonicDecay == true)
      return FourVector(-1, 0, 0, 0);
   return P;
}

pair<int, int> FindBestTwo(vector<GenericObject> &V, FourVector P1, FourVector P2, double DR, bool CheckFlag)
{
   // First we find ones close to either of them, or both
   vector<pair<double, int>> NearP1;
   vector<pair<double, int>> NearP2;

   for(int i = 0; i < (int)V.size(); i++)
   {
      if(CheckFlag == true && V[i].Flag == false)
         continue;

      double DR1 = GetDR(V[i].P, P1);
      double DR2 = GetDR(V[i].P, P2);

      if(DR1 < DR)   NearP1.push_back(pair<double, int>(-V[i].P.GetPT(), i));
      if(DR2 < DR)   NearP2.push_back(pair<double, int>(-V[i].P.GetPT(), i));
   }

   sort(NearP1.begin(), NearP1.end());
   sort(NearP2.begin(), NearP2.end());

   int Index1 = -1, Index2 = -1;

   if(NearP1.size() == 0 || NearP2.size() == 0)
   {
      // No overlap: things are easy
      if(NearP1.size() > 0)   Index1 = NearP1[0].second;
      if(NearP2.size() > 0)   Index2 = NearP2[0].second;
   }
   else
   {
      // Both have matches
      Index1 = NearP1[0].second;
      Index2 = NearP2[0].second;

      if(Index1 == Index2)
      {
         // oh we picked the same ones for both!
         if(NearP1.size() == 1 && NearP2.size() == 1)
         {
            // Not much we can do, we only have one L1 tau
            Index2 = -1;
         }
         else if(NearP1.size() > 1 && NearP2.size() == 1)
         {
            // P2 only matches one, P1 has more
            Index1 = NearP1[1].second;
         }
         else if(NearP1.size() == 1 && NearP1.size() == 1)
         {
            // P1 only matches one, P2 has more
            Index2 = NearP2[1].second;
         }
         else
         {
            // Both have more than one matches.  We compare the second ranks
            if(fabs(NearP1[1].first) > fabs(NearP2[1].first))
               Index1 = NearP1[1].second;
            else
               Index2 = NearP2[1].second;
         }
      }
   }

   return pair<int, int>(Index1, Index2);
}

double CalculateGenIsolation(FourVector &P, vector<FourVector> &Particles, double DR)
{
   double Isolation = 0;

   for(auto G : Particles)
   {
      if(GetDR(G, P) < DR)
         Isolation = Isolation + G.GetPT();
   }

   return Isolation / P.GetPT() - 1;
}
