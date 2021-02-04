#include <iostream>
using namespace std;

#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"
#include "Math/ProbFuncMathCore.h"

#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"

#include "RhoCalculator.h"
#include "Messenger.h"

int main(int argc, char *argv[]);
vector<FourVector> ClusterGenJets(GenParticleTreeMessenger &MGen, double R, double MinPT);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   
   string InputFileName = CL.Get("input");
   double MinPT = CL.GetDouble("MinPT", 3);
   double R = CL.GetDouble("R", 0.40);
   double JetMinPT = CL.GetDouble("JetMinPT", 0);
   double CSR = CL.GetDouble("CSR", -1.0);
   double CSAlpha = CL.GetDouble("CSAlpha", 2.0);
   double MinProbability = CL.GetDouble("MinProbability", 0);
   double MaxProbability = CL.GetDouble("MaxProbability", 1);

   TFile File(InputFileName.c_str());

   HiEventTreeMessenger     MHiEvent(File);
   GenParticleTreeMessenger MGen(File);
   PFTreeMessenger          MPF(File);

   if(MHiEvent.Tree == nullptr)
      return -1;

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MHiEvent.GetEntry(iE);
      MGen.GetEntry(iE);
      MPF.GetEntry(iE);

      vector<FourVector> GenJets = ClusterGenJets(MGen, R, MinPT);

      cout << iE << " GenJet " << GenJets.size() << endl;
      for(int iJ = 0; iJ < GenJets.size(); iJ++)
         if(GenJets[iJ].GetPT() > 20)
            cout << " " << GenJets[iJ].GetPT() << " " << GenJets[iJ].GetEta() << " " << GenJets[iJ].GetPhi() << endl;
      cout << endl;

      vector<PseudoJet> FJPF;
      vector<FourVector> PF;
      vector<FourVector> PFID1;
      for(int iPF = 0; iPF < (int)MPF.ID->size(); iPF++)
      {
         FourVector P;
         P.SetPtEtaPhi((*MPF.PT)[iPF], (*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
         P[0] = (*MPF.E)[iPF];
         FJPF.emplace_back(P[1], P[2], P[3], P[0]);

         PF.emplace_back(P);
         if((*MPF.ID)[iPF] == 1)
            PFID1.emplace_back(P);
      }
      JetDefinition Definition(antikt_algorithm, R);
      GhostedAreaSpec GhostArea(6.5, 1, 0.005);
      AreaDefinition AreaDefinition(active_area_explicit_ghosts, GhostArea);
      ClusterSequenceArea Sequence(FJPF, Definition, AreaDefinition);
      vector<PseudoJet> TempJets = Sequence.inclusive_jets(JetMinPT);

      RhoCalculator CRho;
      RhoModulationCalculator CPhi;

      CRho.CalculateRho(PF);
      vector<double> PPhi = CPhi.DoRhoModulationFit(PFID1);

      vector<FourVector> Jets;

      for(int iJ = 0; iJ < TempJets.size(); iJ++)
      {
         vector<PseudoJet> Particle, Ghost;
         SelectorIsPureGhost().sift(TempJets[iJ].constituents(), Ghost, Particle);
         if(Particle.size() == 0)
            continue;

         double FitProbability = ROOT::Math::chisquared_cdf_c(PPhi[5], PPhi[6]);
         // cout << FitProbability << endl;
         
         for(PseudoJet &G : Ghost)
         {
            double Modulation = 1;
            if(FitProbability > MinProbability && FitProbability < MaxProbability)
               Modulation = CPhi.GetModulation(G.phi());

            double PT = CRho.GetRho(G.eta()) * G.area() * Modulation;
            G.reset_momentum_PtYPhiM(PT, G.rap(), G.phi(), 0);
         }

         contrib::ConstituentSubtractor Subtractor;
         Subtractor.set_distance_type(contrib::ConstituentSubtractor::deltaR);
         Subtractor.set_max_distance(CSR);
         Subtractor.set_alpha(CSAlpha);
         Subtractor.set_do_mass_subtraction(true);
         Subtractor.set_remove_all_zero_pt_particles(true);

         PseudoJet Subtracted = join(Subtractor.do_subtraction(Particle, Ghost));
         if(Subtracted.perp() > 0)
         {
            FourVector J;
            J.SetPtEtaPhiMass(Subtracted.perp(), Subtracted.eta(), Subtracted.phi(), Subtracted.m());
            Jets.emplace_back(J);
         }
      }

      cout << iE << " RecoJet " << Jets.size() << endl;
      for(int iJ = 0; iJ < (int)Jets.size(); iJ++)
         if(Jets[iJ].GetPT() > 40)
            cout << " " << Jets[iJ].GetPT() << " " << Jets[iJ].GetEta() << " " << Jets[iJ].GetPhi() << endl;
      cout << endl;
   }

   File.Close();

   return 0;
}

vector<FourVector> ClusterGenJets(GenParticleTreeMessenger &MGen, double R, double MinPT)
{
   vector<PseudoJet> GenParticles;
   int NGen = MGen.ID->size();
   for(int i = 0; i < NGen; i++)
   {
      // if((*MGen.ID)[i] == 12 || (*MGen.ID)[i] == -12)   continue;
      // if((*MGen.ID)[i] == 14 || (*MGen.ID)[i] == -14)   continue;
      // if((*MGen.ID)[i] == 16 || (*MGen.ID)[i] == -16)   continue;
      if((*MGen.DaughterCount)[i] > 0)                  continue;
      if((*MGen.SubEvent)[i] != 0)                      continue;

      FourVector P;
      P.SetPtEtaPhiMass((*MGen.PT)[i], (*MGen.Eta)[i], (*MGen.Phi)[i], 0);
      GenParticles.emplace_back(P[1], P[2], P[3], P[0]);
   }
   JetDefinition Definition(antikt_algorithm, R);
   ClusterSequence GenSequence(GenParticles, Definition);
   vector<PseudoJet> GenJets = sorted_by_pt(GenSequence.inclusive_jets(MinPT));

   vector<FourVector> Jets;
   for(int iJ = 0; iJ < GenJets.size(); iJ++)
   {
      FourVector P;
      P.SetPtEtaPhiMass(GenJets[iJ].perp(), GenJets[iJ].eta(), GenJets[iJ].phi(), GenJets[iJ].m());
      Jets.emplace_back(P);
   }

   return Jets;
}


