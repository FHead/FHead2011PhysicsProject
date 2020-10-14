#include <algorithm>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/PseudoJet.hh"
#include "fastjet/JetDefinition.hh"
using namespace fastjet;

#include "Code/TauHelperFunctions3.h"
#include "CustomAssert.h"
#include "CommandLine.h"

#include "Messenger.h"

int main(int argc, char *argv[]);
vector<double> CalculateRho(PFTreeMessenger &MPF);
vector<double> CalculateRho(vector<FourVector> &PF);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");

   TFile InputFile(InputFileName.c_str());

   HiEventTreeMessenger MHiEvent(InputFile);
   PFTreeMessenger MPF(InputFile);

   Assert(MHiEvent.Tree != nullptr, "Error getting HiEvent tree");
   Assert(MPF.Tree != nullptr, "Error getting PF tree");

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MHiEvent.GetEntry(iE);
      MPF.GetEntry(iE);

      vector<double> Rho = CalculateRho(MPF);

      cout << "Event: " << iE << "/" << EntryCount << endl;
      for(int i = 0; i < (int)Rho.size(); i++)
         cout << " " << Rho[i];
      cout << endl;
   }

   InputFile.Close();

   return 0;
}

vector<double> CalculateRho(PFTreeMessenger &MPF)
{
   int N = MPF.ID->size();
   vector<FourVector> PF(N);

   for(int i = 0; i < N; i++)
   {
      PF[i].SetPtEtaPhi((*MPF.PT)[i], (*MPF.Eta)[i], (*MPF.Phi)[i]);
      PF[i][0] = (*MPF.E)[i];
   }

   return CalculateRho(PF);
}

vector<double> CalculateRho(vector<FourVector> &PF)
{
   // Basic settings come here
   vector<double> EtaRanges{-5.0, -4.0, -3.0, -2.5, -2.0, -0.8, 0.8, 2.0, 2.5, 3.0, 4.0, 5.0};
   double EtaMax1 = 2.0;
   double EtaMax2 = 3.0;
   double MaxNExclude1 = 2;
   double MaxNExclude2 = 1;
   double PTMin1 = 20;
   double PTMin2 = 20;
   double KTRadius = 0.4;
   double KTPadding = 0.2;
   double GhostArea = 0.005;
   double GhostEtaMax = 6.5;
   int AreaRepeats = 1;

   // First we cluster KT jets with R = 0.4
   vector<PseudoJet> PFParticles;
   for(int i = 0; i < (int)PF.size(); i++)
      PFParticles.push_back(PseudoJet(PF[i][1], PF[i][2], PF[i][3], PF[i][0]));
   JetDefinition Definition(kt_algorithm, KTRadius);
   AreaDefinition Area(active_area, GhostedAreaSpec(GhostEtaMax, AreaRepeats, GhostArea));
   ClusterSequenceArea PFSequence(PFParticles, Definition, Area);
   vector<PseudoJet> AllPFJets = sorted_by_pt(PFSequence.inclusive_jets());

   vector<FourVector> PFJets;
   for(int i = 0; i < (int)AllPFJets.size(); i++)
   {
      FourVector P(AllPFJets[i].e(), AllPFJets[i].px(), AllPFJets[i].py(), AllPFJets[i].pz());
      PFJets.push_back(P);
   }

   // Now let's do the jet excludes
   for(int i = 0; i < (int)AllPFJets.size(); i++)
   {
      PseudoJet &Jet = AllPFJets[i];

      if(fabs(Jet.eta()) < EtaMax1 && Jet.perp() > PTMin1 && MaxNExclude1 > 0)
      {
         MaxNExclude1 = MaxNExclude1 - 1;
         AllPFJets.erase(AllPFJets.begin() + i);
         i = i - 1;
         continue;
      }
      
      if(fabs(Jet.eta()) < EtaMax2 && fabs(Jet.eta()) > EtaMax1 && Jet.perp() > PTMin2 && MaxNExclude2 > 0)
      {
         MaxNExclude2 = MaxNExclude2 - 1;
         AllPFJets.erase(AllPFJets.begin() + i);
         i = i - 1;
         continue;
      }
   }

   // And we collect all rho and rhom values
   vector<double> ResultRho;
   
   for(int iEta = 0; iEta + 1 < (int)EtaRanges.size(); iEta++)
   {
      vector<double> Rhos;

      for(int iJ = 0; iJ < (int)AllPFJets.size(); iJ++)
      {
         PseudoJet &Jet = AllPFJets[iJ];

         if(Jet.eta() < EtaRanges[iEta] + KTPadding)
            continue;
         if(Jet.eta() > EtaRanges[iEta+1] - KTPadding)
            continue;

         double PT = Jet.perp();
         double Area = Jet.area();
         double Rho = PT / Area;

         Rhos.push_back(Rho);
      }

      sort(Rhos.begin(), Rhos.end());

      double MedianRho = 0;
      if(Rhos.size() == 0)
         MedianRho = -1;
      else if(Rhos.size() % 2 == 0)
         MedianRho = (Rhos[Rhos.size()/2-1] + Rhos[Rhos.size()/2]) / 2;
      else
         MedianRho = Rhos[Rhos.size()/2];

      ResultRho.push_back(MedianRho);
   }

   return ResultRho;
}



