#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TChain.h"
#include "TH1D.h"

#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: exe in out" << endl;
      return -1;
   }

   string InputFileName = argv[1];
   string OutputFileName = argv[2];

   TChain InputTree("DelphesPlainTree", "DelphesPlainTree");
   InputTree.AddFile(InputFileName.c_str());

   TH1D HParticleCount("HParticleCount", "Number of particles in event", 1000, 0, 1000);

   int ParticleCount = 0;
   InputTree.SetBranchAddress("ParticleCount", &ParticleCount);

   double ParticleE[1000] = {0};
   double ParticleX[1000] = {0};
   double ParticleY[1000] = {0};
   double ParticleZ[1000] = {0};
   int ParticleStatus[1000] = {0};
   int ParticlePDGID[1000] = {0};

   InputTree.SetBranchAddress("E", ParticleE);
   InputTree.SetBranchAddress("Px", ParticleX);
   InputTree.SetBranchAddress("Py", ParticleY);
   InputTree.SetBranchAddress("Pz", ParticleZ);
   InputTree.SetBranchAddress("Status", ParticleStatus);
   InputTree.SetBranchAddress("PDGID", ParticlePDGID);

   TFile OutputFile(OutputFileName.c_str(), "recreate");

   TTree OutputTree("ReducedTree", "ReducedTree 7621");

   double MR, R, MR11, R11;
   OutputTree.Branch("MR", &MR, "MR/D");
   OutputTree.Branch("R", &R, "R/D");
   OutputTree.Branch("MR11", &MR11, "MR11/D");
   OutputTree.Branch("R11", &R11, "R11/D");

   int LooseBTagCount, MediumBTagCount, TightBTagCount;
   OutputTree.Branch("LooseBTagCount", &LooseBTagCount, "LooseBTagCount/I");
   OutputTree.Branch("MediumBTagCount", &MediumBTagCount, "MediumBTagCount/I");
   OutputTree.Branch("TightBTagCount", &TightBTagCount, "TightBTagCount/I");

   int PileupCount;
   OutputTree.Branch("PileupCount", &PileupCount, "PileupCount/I");

   int LeptonCount;
   OutputTree.Branch("GoodMuonCountLoose", &LeptonCount, "GoodMuonCountLoose/I");
   OutputTree.Branch("GoodMuonCountTight", &LeptonCount, "GoodMuonCountTight/I");
   OutputTree.Branch("GoodElectronCountLoose", &LeptonCount, "GoodElectronCountLoose/I");
   OutputTree.Branch("GoodElectronCountTight", &LeptonCount, "GoodElectronCountTight/I");

   int EntryCount = InputTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      InputTree.GetEntry(iEntry);

      HParticleCount.Fill(ParticleCount);
      if(ParticleCount == 0)   // rejected event
         continue;

      FourVector ME(0, 0, 0, 0);

      vector<PseudoJet> Particles;
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

      vector<FourVector> Jets;
      for(int i = 0; i < (int)PseudoJets.size(); i++)
      {
         if(PseudoJets[i].perp() < 40)
            continue;

         Jets.push_back(FourVector(PseudoJets[i].e(), PseudoJets[i].px(), PseudoJets[i].py(), PseudoJets[i].pz()));
      }

      // cout << Particles.size() << endl;

      if(Jets.size() < 2)
         continue;

      // cout << Jets.size() << endl;

      vector<FourVector> Group = SplitIntoGroups(Jets, true);

      MR = Get2011MR(Group[0], Group[1]);
      R = Get2011R(Group[0], Group[1], ME);

      OutputTree.Fill();
   }

   OutputTree.Write();

   OutputFile.Close();

   PsFileHelper PsFile("DQM.ps");
   PsFile.AddTextPage("Data quality monitoring plots");

   PsFile.AddPlot(HParticleCount, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

