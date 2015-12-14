#include <iostream>
using namespace std;

#include "TFile.h"
#include "TChain.h"
#include "TTree.h"

#include "ReadLQ3Tree.h"
#include "TauHelperFunctions2.h"

int main()
{
   TChain InputTree("LQ3Tree");
   InputTree.AddFile("Samples/JetMay10ReRecov1_All.root");

   TreeRecord M;
   M.SetBranchAddress(&InputTree);

   TFile OutputFile("JetReducedTree.root", "RECREATE");
   TTree OutputTree("MRTree", "MRTree");

   long long RunNumber;
   long long EventNumber;
   long long LumiSection;
   double MR;
   double R;
   double MRStar;
   double RStar;
   double GammaMRStar;
   double BetaR;
   bool PassDiJetAve30;
   bool PassDiJetAve60;
   bool PassDiJetAve80;
   bool PassDiJetAve110;
   bool PassDiJetAve150;
   bool PassDiJetAve190;
   bool PassDiJetAve240;
   bool PassDiJetAve300;
   bool PassDiJetAve370;
   bool PassDiJetAve15U;
   bool PassDiJetAve30U;
   bool PassDiJetAve50U;
   bool PassDiJetAve70U;
   bool PassDiJetAve100U;
   bool PassDiJetAve140U;
   bool PassDiJetAve180U;
   bool PassDiJetAve300U;
   double DeltaPhi;
   double LeadingJetDeltaPhi;

   OutputTree.Branch("RunNumber", &RunNumber, "RunNumber/LL");
   OutputTree.Branch("EventNumber", &EventNumber, "EventNumber/LL");
   OutputTree.Branch("LumiSection", &LumiSection, "LumiSection/LL");
   OutputTree.Branch("MR", &MR, "MR/D");
   OutputTree.Branch("R", &R, "R/D");
   OutputTree.Branch("MRStar", &MRStar, "MRStar/D");
   OutputTree.Branch("RStar", &RStar, "RStar/D");
   OutputTree.Branch("GammaMRStar", &GammaMRStar, "GammaMRStar/D");
   OutputTree.Branch("BetaR", &BetaR, "BetaR/D");
   OutputTree.Branch("PassDiJetAve30", &PassDiJetAve30, "PassDiJetAve30/O");
   OutputTree.Branch("PassDiJetAve60", &PassDiJetAve60, "PassDiJetAve60/O");
   OutputTree.Branch("PassDiJetAve80", &PassDiJetAve80, "PassDiJetAve80/O");
   OutputTree.Branch("PassDiJetAve110", &PassDiJetAve110, "PassDiJetAve110/O");
   OutputTree.Branch("PassDiJetAve150", &PassDiJetAve150, "PassDiJetAve150/O");
   OutputTree.Branch("PassDiJetAve190", &PassDiJetAve190, "PassDiJetAve190/O");
   OutputTree.Branch("PassDiJetAve240", &PassDiJetAve240, "PassDiJetAve240/O");
   OutputTree.Branch("PassDiJetAve300", &PassDiJetAve300, "PassDiJetAve300/O");
   OutputTree.Branch("PassDiJetAve370", &PassDiJetAve370, "PassDiJetAve370/O");
   OutputTree.Branch("PassDiJetAve15U", &PassDiJetAve15U, "PassDiJetAve15U/O");
   OutputTree.Branch("PassDiJetAve30U", &PassDiJetAve30U, "PassDiJetAve30U/O");
   OutputTree.Branch("PassDiJetAve50U", &PassDiJetAve50U, "PassDiJetAve50U/O");
   OutputTree.Branch("PassDiJetAve70U", &PassDiJetAve70U, "PassDiJetAve70U/O");
   OutputTree.Branch("PassDiJetAve100U", &PassDiJetAve100U, "PassDiJetAve100U/O");
   OutputTree.Branch("PassDiJetAve140U", &PassDiJetAve140U, "PassDiJetAve140U/O");
   OutputTree.Branch("PassDiJetAve180U", &PassDiJetAve180U, "PassDiJetAve180U/O");
   OutputTree.Branch("PassDiJetAve300U", &PassDiJetAve300U, "PassDiJetAve300U/O");
   OutputTree.Branch("DeltaPhi", &DeltaPhi, "DeltaPhi/D");
   OutputTree.Branch("LeadingJetDeltaPhi", &LeadingJetDeltaPhi, "LeadingJetDeltaPhi/D");

   int EntryCount = InputTree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 250000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      InputTree.GetEntry(iEntry);

      if(M.PassNoiseFilter == false)
         continue;
      if(M.PrimaryVertexCount == 0)
         continue;
      if(M.PassPFJetID == false)
         continue;

      vector<FourVector> InputJets;
      for(int i = 0; i < M.PFJetCount; i++)
      {
         if(M.PFJetEta[i] < -2.4 || M.PFJetEta[i] > 2.4)
            continue;
         if(M.PFJetPT[i] < 30)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.PFJetPT[i], M.PFJetEta[i], M.PFJetPhi[i]);
         NewJet[0] = M.PFJetE[i];
         InputJets.push_back(NewJet);
      }
      if(InputJets.size() < 2)   // we need two jets
         continue;
      if(InputJets.size() > 20)   // woah....
      {
         cout << "More than 20 jets detected!!!" << endl;
         continue;
      }

      int TCHETCount = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetPT[i] < 30)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;
         if(M.CaloJetTCHETag[i] > 10.2)
            TCHETCount = TCHETCount + 1;
      }
      if(TCHETCount == 0)   // we want a b tagged jet
         continue;

      vector<FourVector> Groups = SplitIntoGroups(InputJets, true);
      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);

      MR = GetMR(Groups[0], Groups[1]);
      R = GetR(Groups[0], Groups[1], PFMET);
      MRStar = GetMRStar(Groups[0], Groups[1]);
      RStar = GetRStar(Groups[0], Groups[1], PFMET);
      GammaMRStar = GetGammaRStar(Groups[0], Groups[1]) * MRStar;
      BetaR = (Groups[0][0] - Groups[1][0]) / (Groups[0][3] - Groups[1][3]);
      DeltaPhi = GetDPhi(Groups[0], Groups[1]);
      LeadingJetDeltaPhi = GetDPhi(InputJets[0], InputJets[1]);
      
      PassDiJetAve30 = M.PassDiJetAve30;
      PassDiJetAve60 = M.PassDiJetAve60;
      PassDiJetAve80 = M.PassDiJetAve80;
      PassDiJetAve110 = M.PassDiJetAve110;
      PassDiJetAve150 = M.PassDiJetAve150;
      PassDiJetAve190 = M.PassDiJetAve190;
      PassDiJetAve240 = M.PassDiJetAve240;
      PassDiJetAve300 = M.PassDiJetAve300;
      PassDiJetAve370 = M.PassDiJetAve370;
      PassDiJetAve15U = M.PassDiJetAve15U;
      PassDiJetAve30U = M.PassDiJetAve30U;
      PassDiJetAve50U = M.PassDiJetAve50U;
      PassDiJetAve70U = M.PassDiJetAve70U;
      PassDiJetAve100U = M.PassDiJetAve100U;
      PassDiJetAve140U = M.PassDiJetAve140U;
      PassDiJetAve180U = M.PassDiJetAve180U;
      PassDiJetAve300U = M.PassDiJetAve300U;

      RunNumber = M.RunNumber;
      EventNumber = M.EventNumber;
      LumiSection = M.LumiSection;

      OutputTree.Fill();
   }

   OutputTree.Write();
   OutputFile.Close();

   return 0;
}
