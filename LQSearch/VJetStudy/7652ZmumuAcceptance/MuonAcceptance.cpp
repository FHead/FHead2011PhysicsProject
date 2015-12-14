//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
#include "fastjet/ClusterSequence.hh"
using namespace fastjet;
//---------------------------------------------------------------------------
#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"
//---------------------------------------------------------------------------
#include "TauHelperFunctions2.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage " << argv[0] << " input output" << endl;
      return -1;
   }

   TChain Tree("DelphesPlainTree", "DelphesPlainTree");
   Tree.AddFile(argv[1]);

   int ParticleCount = 0;
   double ParticleE[1000] = {0};
   double ParticleX[1000] = {0};
   double ParticleY[1000] = {0};
   double ParticleZ[1000] = {0};
   int ParticleStatus[1000] = {0};
   int ParticlePDGID[1000] = {0};
   int ParticleM1[1000] = {0};
   int ParticleM2[1000] = {0};

   Tree.SetBranchAddress("ParticleCount", &ParticleCount);
   Tree.SetBranchAddress("E", ParticleE);
   Tree.SetBranchAddress("Px", ParticleX);
   Tree.SetBranchAddress("Py", ParticleY);
   Tree.SetBranchAddress("Pz", ParticleZ);
   Tree.SetBranchAddress("Status", ParticleStatus);
   Tree.SetBranchAddress("PDGID", ParticlePDGID);
   Tree.SetBranchAddress("M1", ParticleM1);
   Tree.SetBranchAddress("M2", ParticleM2);

   TFile OutputFile(argv[2], "recreate");

   TH2D HMRRCount("HMRRMap", "MR vs. R map;MR;R*R", 50, 0, 1500, 50, 0, 1.0);
   TH2D HMRRCountGoodMuon("HMRRMapGoodMuon",
      "MR vs. R map (muons in acceptance);MR;R*R", 50, 0, 1500, 50, 0, 1.0);
   TH1D HNuNuMass("HNuNuMass", "nunu mass;Mass [GeV]", 100, 0, 150);
   TH1D HNuNuAngle("HNuNuAngle", "nunu angle;Angle", 100, 0, 3.2);
   TH1D HNuP("HNuP", "nu momentum;P [GeV]", 100, 0, 150);
   TH1D HNuPT("HNuPT", "nu transverse momentum;P [GeV]", 100, 0, 150);
   TH1D HNuEta("HNuEta", "nu eta;eta", 100, -5, 5);
   TH1D HNuNuPT("HNuNuPT", "nunu transverse momentum;P [GeV]", 100, 0, 150);
   TH2D HNuPTPT("HNuPTPT", "PT1 vs. PT2", 100, 0, 150, 100, 0, 150);

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree.GetEntry(iEntry);

      FourVector ME(0, 0, 0, 0);

      vector<PseudoJet> Particles;
      FourVector Nu1P, Nu2P;
      for(int i = 0; i < ParticleCount; i++)
      {
         if(ParticleStatus[i] != 1)
            continue;

         FourVector ParticleP(ParticleE[i], ParticleX[i], ParticleY[i], ParticleZ[i]);

         if(ParticlePDGID[i] == 12 || ParticlePDGID[i] == -12
               || ParticlePDGID[i] == 14 || ParticlePDGID[i] == -14
               || ParticlePDGID[i] == 16 || ParticlePDGID[i] == -16)
         {
            ME = ME + ParticleP;
            if(ParticlePDGID[i] > 0)
               Nu1P = ParticleP;
            else
               Nu2P = ParticleP;
            continue;
         }

         if(ParticleP.GetAbsEta() > 3)
         {
            ME = ME + ParticleP;
            continue;
         }

         Particles.push_back(PseudoJet(ParticleX[i], ParticleY[i], ParticleZ[i], ParticleE[i]));
      }
      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> PseudoJets = Sequence.inclusive_jets(0.5);

      // some mc plots
      HNuNuMass.Fill((Nu1P + Nu2P).GetMass());
      HNuNuAngle.Fill(GetAngle(Nu1P, Nu2P));
      HNuP.Fill(Nu1P.GetP());       HNuP.Fill(Nu2P.GetP());
      HNuPT.Fill(Nu1P.GetPT());     HNuPT.Fill(Nu2P.GetPT());
      HNuEta.Fill(Nu1P.GetEta());   HNuEta.Fill(Nu2P.GetEta());
      HNuNuPT.Fill((Nu1P + Nu2P).GetPT());
      HNuPTPT.Fill(Nu1P.GetPT(), Nu2P.GetPT());

      vector<FourVector> Jets;
      for(int i = 0; i < (int)PseudoJets.size(); i++)
      {
         if(PseudoJets[i].perp() < 40)
            continue;

         Jets.push_back(FourVector(PseudoJets[i].e(), PseudoJets[i].px(), PseudoJets[i].py(), PseudoJets[i].pz()));
      }

      if(Jets.size() < 2)
         continue;

      vector<FourVector> Group = SplitIntoGroups(Jets, true);

      double MR = Get2011MR(Group[0], Group[1]);
      double R = Get2011R(Group[0], Group[1], ME);

      int LeptonInAcceptance = 0;   // 20 GeV and eta cut
      for(int i = 0; i < ParticleCount; i++)
      {
         if(ParticlePDGID[i] != 12 && ParticlePDGID[i] != -12 && ParticlePDGID[i] != 14
            && ParticlePDGID[i] != -14 && ParticlePDGID[i] != 16 && ParticlePDGID[i] != -16)
            continue;

         // cout << ParticlePDGID[i] << " " << ParticleM1[i] << " " << ParticleM2[i] << endl;

         if(ParticleM1[i] <= 0 && ParticleM2[i] <= 0)
            continue;

         bool ZMother = false;
         if(ParticleM1[i] > 0 && ParticlePDGID[ParticleM1[i]] == 23)
            ZMother = true;
         if(ParticleM2[i] > 0 && ParticlePDGID[ParticleM2[i]] == 23)
            ZMother = true;
         if(ZMother == false)
            continue;

         FourVector ParticleP(ParticleE[i], ParticleX[i], ParticleY[i], ParticleZ[i]);
         if(ParticleP.GetAbsEta() > 3 || ParticleP.GetPT() < 20)
            continue;

         LeptonInAcceptance = LeptonInAcceptance + 1;
      }

      // cout << LeptonInAcceptance << endl;

      HMRRCount.Fill(MR, R * R);
      if(LeptonInAcceptance == 2)
         HMRRCountGoodMuon.Fill(MR, R * R);
   }

   HMRRCount.Write();
   HMRRCountGoodMuon.Write();
   HNuNuMass.Write();
   HNuNuAngle.Write();
   HNuP.Write();
   HNuPT.Write();
   HNuEta.Write();
   HNuNuPT.Write();
   HNuPTPT.Write();

   OutputFile.Close();

   return 0;
}
//---------------------------------------------------------------------------




