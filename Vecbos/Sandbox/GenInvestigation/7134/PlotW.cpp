#include <cmath>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TChain.h"

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "ChainAll.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main()
{
   TChain *Tree = ChainAll("W.list", "ntp1");

   TFile F("W.root", "recreate");

   TH1D HLeadingJetPT("HLeadingJetPT", "Leading jet PT", 100, 0, 100);
   TH1D HJetCount1("HJetCount1", "Jet count (mu)", 10, 0, 10);
   TH1D HJetCount2("HJetCount2", "Jet count (e)", 10, 0, 10);
   TH1D HEventCount("HEventCount", "Event count", 1, 0, 1);

   int nMc;
   int idMc[2000];
   int statusMc[2000];
   int mothMc[2000];
   float etaMc[2000];
   float phiMc[2000];
   float energyMc[2000];

   int nAK5GenJet;
   float pxAK5GenJet[100];
   float pyAK5GenJet[100];
   float etaAK5GenJet[100];
   float phiAK5GenJet[100];

   Tree->SetBranchStatus("*", false);
   Tree->SetBranchStatus("nMc", true);
   Tree->SetBranchStatus("idMc", true);
   Tree->SetBranchStatus("mothMc", true);
   Tree->SetBranchStatus("statusMc", true);
   Tree->SetBranchStatus("etaMc", true);
   Tree->SetBranchStatus("phiMc", true);
   Tree->SetBranchStatus("energyMc", true);
   
   Tree->SetBranchStatus("nAK5GenJet", true);
   Tree->SetBranchStatus("pxAK5GenJet", true);
   Tree->SetBranchStatus("pyAK5GenJet", true);
   Tree->SetBranchStatus("etaAK5GenJet", true);
   Tree->SetBranchStatus("phiAK5GenJet", true);

   Tree->SetBranchAddress("nMc", &nMc);
   Tree->SetBranchAddress("idMc", idMc);
   Tree->SetBranchAddress("mothMc", mothMc);
   Tree->SetBranchAddress("statusMc", statusMc);
   Tree->SetBranchAddress("etaMc", etaMc);
   Tree->SetBranchAddress("phiMc", phiMc);
   Tree->SetBranchAddress("energyMc", energyMc);

   Tree->SetBranchAddress("nAK5GenJet", &nAK5GenJet);
   Tree->SetBranchAddress("pxAK5GenJet", pxAK5GenJet);
   Tree->SetBranchAddress("pyAK5GenJet", pyAK5GenJet);
   Tree->SetBranchAddress("etaAK5GenJet", etaAK5GenJet);
   Tree->SetBranchAddress("phiAK5GenJet", phiAK5GenJet);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 50000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iEntry);

      // reject non-W-munu events
      bool HasWMuNu = false;
      int MuIndex = -1;
      int MuBarIndex = -1;
      for(int i = 0; i < nMc; i++)
      {
         if(idMc[i] == 13)
         {
            if(mothMc[i] != -1 && fabs(idMc[mothMc[i]]) == 24)
            {
               HasWMuNu = true;
               MuIndex = i;
            }
         }
         if(idMc[i] == -13)
         {
            if(mothMc[i] != -1 && fabs(idMc[mothMc[i]]) == 24)
            {
               HasWMuNu = true;
               MuBarIndex = i;
            }
         }
      }
      if(HasWMuNu == false)
         continue;
      HEventCount.Fill(0);

      int FirstLegMuonCount = 0;
      int SecondLegMuonCount = 0;

      int FirstLegElectronCount = 0;
      int SecondLegElectronCount = 0;

      for(int i = 0; i < nMc; i++)
      {
         if(idMc[i] != 13 && idMc[i] != -13)
            continue;
         if(statusMc[i] != 1)
            continue;

         double PT = energyMc[i] / cosh(etaMc[i]);

         if(fabs(etaMc[i]) < 2.1 && PT > 20)
            FirstLegMuonCount = FirstLegMuonCount + 1;
         if(fabs(etaMc[i]) < 2.5 && PT > 10)
            SecondLegMuonCount = SecondLegMuonCount + 1;
         
         if(fabs(etaMc[i]) < 2.5 && PT > 20 && (fabs(etaMc[i]) < 1.4442 || fabs(etaMc[i] > 1.566)))
            FirstLegElectronCount = FirstLegElectronCount + 1;
         if(fabs(etaMc[i]) < 2.5 && PT > 10 && (fabs(etaMc[i]) < 1.4442 || fabs(etaMc[i] > 1.566)))
            SecondLegElectronCount = SecondLegElectronCount + 1;
      }

      vector<PseudoJet> Particles;
      for(int i = 0; i < nMc; i++)
      {
         if(statusMc[i] != 1)
            continue;
         if(etaMc[i] < -3 || etaMc[i] > 3)
            continue;
         if(MuIndex >= 0 && idMc[i] == 13)
         {
            double DEta = etaMc[i] - etaMc[MuIndex];
            double DPhi = min((double)fabs(phiMc[i] - phiMc[MuIndex]), 2 * PI - fabs(phiMc[i] - phiMc[MuIndex]));
            if(DEta * DEta + DPhi * DPhi < 0.1 * 0.1)
               continue;
         }
         if(MuBarIndex >= 0 && idMc[i] == -13)
         {
            double DEta = etaMc[i] - etaMc[MuBarIndex];
            double DPhi = min((double)fabs(phiMc[i] - phiMc[MuBarIndex]), 2 * PI - fabs(phiMc[i] - phiMc[MuBarIndex]));
            if(DEta * DEta + DPhi * DPhi < 0.1 * 0.1)
               continue;
         }
         if(idMc[i] == 12 || idMc[i] == -12
            || idMc[i] == 14 || idMc[i] == -14
            || idMc[i] == 16 || idMc[i] == -16)
            continue;

         double px = energyMc[i] / cosh(etaMc[i]) * cos(phiMc[i]);
         double py = energyMc[i] / cosh(etaMc[i]) * sin(phiMc[i]);
         double pz = energyMc[i] * tanh(etaMc[i]);
         
         Particles.push_back(PseudoJet(px, py, pz, energyMc[i]));
      }
      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.5);

      int JetCount = 0;
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         if(Jets[i].eta() < -2.4 || Jets[i].eta() > 2.4)
            continue;
         if(Jets[i].perp() < 30)
            continue;

         JetCount = JetCount + 1;
      }

      if(FirstLegMuonCount == 1 && SecondLegMuonCount == 1)
         HJetCount1.Fill(JetCount);
      if(FirstLegElectronCount == 1 && SecondLegElectronCount == 1)
         HJetCount2.Fill(JetCount);
   }

   HLeadingJetPT.Write();
   
   HJetCount1.Write();
   HJetCount2.Write();
   HEventCount.Write();

   F.Close();

   return 0;
}



