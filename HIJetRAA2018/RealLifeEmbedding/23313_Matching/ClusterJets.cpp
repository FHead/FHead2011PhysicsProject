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
#include "ProgressBar.h"

#include "JetCorrector.h"
#include "JetProducer.h"
#include "RhoCalculator.h"
#include "Messenger.h"

#define MAX 10000

int main(int argc, char *argv[]);
vector<FourVector> ClusterGenJets(GenParticleTreeMessenger &MGen, double R, double MinPT, double MinParticlePT = 0);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   
   vector<string> InputFileName = CL.GetStringVector("input");
   string OutputFileName = CL.Get("output", "SubtractedJet.root");
   double Fraction       = CL.GetDouble("fraction", 1);
   
   // Jet parameters
   double R              = CL.GetDouble("R", 0.40);
   double JetMinPT       = CL.GetDouble("JetMinPT", 5);
   vector<string> JECs   = CL.GetStringVector("JEC", vector<string>({}));

   // GenJet parameters
   double GenMinPT       = CL.GetDouble("GenMinPT", 3);

   // Matching parameters
   double MatchDR        = CL.GetDouble("MatchDR", R * 0.5);
   
   // Subtraction parameters
   bool SkipSubtraction  = CL.GetBool("SkipSubtraction", false);
   double CSR            = CL.GetDouble("CSR", -1.0);
   double CSAlpha        = CL.GetDouble("CSAlpha", 2.0);
   double MinProbability = CL.GetDouble("MinProbability", 0.05);
   double MaxProbability = CL.GetDouble("MaxProbability", 0.95);
   
   // Rho parameters
   
   // RhoModulation parameters
   double RhoPhiMaxEta   = CL.GetDouble("RhoPhiMaxEta", 1.0);

   JetProducer Producer;
   Producer.SetJetR(R);
   Producer.SetMinJetPT(JetMinPT);
   Producer.SetCSR(CSR);
   Producer.SetCSAlpha(CSAlpha);
   Producer.SetMinProbability(MinProbability);
   Producer.SetMaxProbability(MaxProbability);
   Producer.SetMinPTDiff(0);
   Producer.SetPassThrough(SkipSubtraction);

   Producer.GetRhoCalculator().SetCMSPreset();
   Producer.GetRhoModulationCalculator().SetCMSPreset();
   Producer.GetRhoModulationCalculator().SetAbsEtaMax(RhoPhiMaxEta);

   JetCorrector JEC(JECs);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree Tree("Tree", "jet trees");

   double Centrality;
   Tree.Branch("Centrality", &Centrality, "Centrality/D");

   int NJet;
   double JetPT[MAX], RawPT[MAX], JetEta[MAX], JetPhi[MAX];
   double GenPT[MAX], GenEta[MAX], GenPhi[MAX], GenDR[MAX];
   Tree.Branch("NJet", &NJet, "NJet/I");
   Tree.Branch("JetPT", &JetPT, "JetPT[NJet]/D");
   Tree.Branch("RawPT", &RawPT, "RawPT[NJet]/D");
   Tree.Branch("JetEta", &JetEta, "JetEta[NJet]/D");
   Tree.Branch("JetPhi", &JetPhi, "JetPhi[NJet]/D");
   Tree.Branch("GenPT", &GenPT, "GenPT[NJet]/D");
   Tree.Branch("GenEta", &GenEta, "GenEta[NJet]/D");
   Tree.Branch("GenPhi", &GenPhi, "GenPhi[NJet]/D");
   Tree.Branch("GenDR", &GenDR, "GenDR[NJet]/D");
   
   int NRho;
   double Rho[MAX];
   double V2, V3, Phi2, Phi3, Chi2, NDoF, Chi2Probability;
   Tree.Branch("NRho", &NRho, "NRho/I");
   Tree.Branch("Rho", &Rho, "Rho[NRho]/D");
   Tree.Branch("V2", &V2, "V2/D");
   Tree.Branch("V3", &V3, "V3/D");
   Tree.Branch("Phi2", &Phi2, "Phi2/D");
   Tree.Branch("Phi3", &Phi3, "Phi3/D");
   Tree.Branch("Chi2", &Chi2, "Chi2/D");
   Tree.Branch("NDoF", &NDoF, "NDoF/D");
   Tree.Branch("Chi2Probability", &Chi2Probability, "Chi2Probability/D");

   for(string FileName : InputFileName)
   {
      cout << "Processing file " << FileName << endl;

      TFile File(FileName.c_str());

      HiEventTreeMessenger     MHiEvent(File);
      GenParticleTreeMessenger MGen(File);
      PFTreeMessenger          MPF(File);

      if(MHiEvent.Tree == nullptr)
         return -1;

      int EntryCount = MHiEvent.Tree->GetEntries() * Fraction;
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(6);
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         Bar.Print();

         MHiEvent.GetEntry(iE);
         MGen.GetEntry(iE);
         MPF.GetEntry(iE);

         Centrality = MHiEvent.hiBin * 0.005;
         
         for(int iJ = 0; iJ < MAX; iJ++)
         {
            JetPT[iJ] = 0;
            RawPT[iJ] = 0;
            JetEta[iJ] = 0;
            JetPhi[iJ] = 0;
            GenPT[iJ] = 0;
            GenEta[iJ] = 0;
            GenPhi[iJ] = 0;
            GenDR[iJ] = 0;
         }

         vector<FourVector> GenJets = ClusterGenJets(MGen, R, GenMinPT);

         vector<FourVector> PF;
         vector<FourVector> PFID1;
         for(int iPF = 0; iPF < (int)MPF.ID->size(); iPF++)
         {
            FourVector P;
            P.SetPtEtaPhi((*MPF.PT)[iPF], (*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
            P[0] = (*MPF.E)[iPF];

            PF.emplace_back(P);
            if((*MPF.ID)[iPF] == 1)
               PFID1.emplace_back(P);
         }

         vector<FourVector> Jets = Producer.ClusterJets(PF, PFID1);
         vector<FourVector> MatchedJets(Jets.size(), FourVector(-1, 0, 0, 0));

         vector<double> Rhos = Producer.GetRhoCalculator().GetRhoParameters();
         NRho = Rhos.size();
         for(int iR = 0; iR < NRho; iR++)
            Rho[iR] = Rhos[iR];

         vector<double> RhoFits = Producer.GetRhoModulationCalculator().GetParameters();
         V2   = RhoFits[1];
         Phi2 = RhoFits[2];
         V3   = RhoFits[3];
         Phi3 = RhoFits[4];
         Chi2 = RhoFits[5];
         NDoF = RhoFits[6];
         Chi2Probability = ROOT::Math::chisquared_cdf_c(RhoFits[5], RhoFits[6]);

         for(int iJ = 0; iJ < (int)Jets.size(); iJ++)
         {
            double BestGenDR = -1;
            int BestGenIndex = -1;

            for(int iG = 0; iG < (int)GenJets.size(); iG++)
            {
               double DR = GetDR(Jets[iJ], GenJets[iG]);
               if(BestGenDR < 0 || BestGenDR > DR)
               {
                  BestGenDR = DR;
                  BestGenIndex = iG;
               }
            }

            if(BestGenIndex < 0)
               continue;
            if(BestGenDR > MatchDR)
               continue;
            MatchedJets[iJ] = GenJets[BestGenIndex];
            GenDR[iJ] = BestGenDR;
         }

         NJet = 0;
         for(int iJ = 0; iJ < (int)Jets.size(); iJ++)
         {
            JEC.SetJetPT(Jets[iJ].GetPT());
            JEC.SetJetEta(Jets[iJ].GetEta());
            JEC.SetJetPhi(Jets[iJ].GetPhi());
            double CorrectedPT = JEC.GetCorrectedPT();

            if(CorrectedPT < JetMinPT)
               continue;

            JetPT[NJet]  = CorrectedPT;
            RawPT[NJet]  = Jets[iJ].GetPT();
            JetEta[NJet] = Jets[iJ].GetEta();
            JetPhi[NJet] = Jets[iJ].GetPhi();

            if(MatchedJets[iJ][0] > 0)
            {
               GenPT[NJet]  = MatchedJets[iJ].GetPT();
               GenEta[NJet] = MatchedJets[iJ].GetEta();
               GenPhi[NJet] = MatchedJets[iJ].GetPhi();
            }
            else
            {
               GenPT[NJet]  = -1;
               GenEta[NJet] = 0;
               GenPhi[NJet] = 0;
            }

            NJet++;
         }

         Tree.Fill();
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   OutputFile.cd();
   Tree.Write();
   OutputFile.Close();

   return 0;
}

vector<FourVector> ClusterGenJets(GenParticleTreeMessenger &MGen, double R, double MinPT, double MinParticlePT)
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

      if(P.GetPT() > MinParticlePT)
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


