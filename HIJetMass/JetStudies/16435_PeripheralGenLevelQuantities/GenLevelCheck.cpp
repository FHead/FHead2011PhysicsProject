#include <iostream>
#include <vector>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"
using namespace fastjet;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"

#include "ProgressBar.h"
#include "Code/TauHelperFunctions3.h"

#include "Messenger.h"
#include "BasicUtilities.h"

#define MAX 2000

int main(int argc, char *argv[])
{
   if(argc != 6)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag PTHatMin PTHatMax" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];
   double PTHatMin = atof(argv[4]);
   double PTHatMax = atof(argv[5]);

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);
   bool IsPPHIReco = IsPPHiRecoFromTag(Tag);

   string TreeName = "akCs4PFJetAnalyzer/t";
   if(IsPP == true)
      TreeName = "ak4PFJetAnalyzer/t";
   if(IsPPHIReco == true)
      TreeName = "akPu4PFJetAnalyzer/t";

   TFile *InputFile = TFile::Open(Input.c_str());

   HiEventTreeMessenger MHiEvent(InputFile);
   GenParticleTreeMessenger MGen(InputFile);
   JetTreeMessenger MJet(InputFile, TreeName);
   PFTreeMessenger MPF(InputFile, "pfcandanalyzer/pfTree");

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TH1D HN("HN", "N;;", 1, 0, 1);

   TTree OutputTree("Tree", "Tree");

   double PTHat, Centrality;
   OutputTree.Branch("PTHat", &PTHat, "PTHat/D");
   OutputTree.Branch("Centrality", &Centrality, "Centrality/D");

   int GenCount;
   double GenPT[MAX], GenEta[MAX], GenPhi[MAX];
   int GenID[MAX], GenDaughterCount[MAX];
   
   OutputTree.Branch("GenCount", &GenCount, "GenCount/I");
   OutputTree.Branch("GenPT", &GenPT, "GenPT[GenCount]/D");
   OutputTree.Branch("GenEta", &GenEta, "GenEta[GenCount]/D");
   OutputTree.Branch("GenPhi", &GenPhi, "GenPhi[GenCount]/D");
   OutputTree.Branch("GenID", &GenID, "GenID[GenCount]/I");
   OutputTree.Branch("GenDaughterCount", &GenDaughterCount, "GenDaughterCount[GenCount]/I");

   int JetCount;
   double JetPT[MAX], JetEta[MAX], JetPhi[MAX];
   OutputTree.Branch("JetCount", &JetCount, "JetCount/I");
   OutputTree.Branch("JetPT", &JetPT, "JetPT[JetCount]/D");
   OutputTree.Branch("JetEta", &JetEta, "JetEta[JetCount]/D");
   OutputTree.Branch("JetPhi", &JetPhi, "JetPhi[JetCount]/D");

   int EntryCount = MHiEvent.Tree->GetEntries() * 0.05;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      HN.Fill(0);

      Bar.Update(iE);
      Bar.PrintWithMod(200);

      MHiEvent.GetEntry(iE);
      MGen.GetEntry(iE);
      MJet.GetEntry(iE);
      MPF.GetEntry(iE);

      if(MJet.PTHat <= PTHatMin || MJet.PTHat > PTHatMax)
         continue;

      PTHat = MJet.PTHat;
      Centrality = GetCentrality(MHiEvent.hiBin);

      GenCount = 0;
      for(int i = 0; i < MAX; i++)
      {
         GenPT[i] = 0;
         GenEta[i] = 0;
         GenPhi[i] = 0;
         GenID[i] = 0;
         GenDaughterCount[i] = 0;
      }

      for(int i = 0; i < MGen.PT->size(); i++)
      {
         if((*MGen.SubEvent)[i] == 0)
         {
            if(GenCount < MAX)
            {
               GenPT[GenCount] = (*MGen.PT)[i];
               GenEta[GenCount] = (*MGen.Eta)[i];
               GenPhi[GenCount] = (*MGen.Phi)[i];
               GenID[GenCount] = (*MGen.ID)[i];
               GenDaughterCount[GenCount] = (*MGen.DaughterCount)[i];
            }

            GenCount = GenCount + 1;
         }
      }
      if(GenCount >= MAX)
      {
         cerr << "[WARNING] Number of gen particle larger than array size!  skipping event..." << endl;
         cerr << "[WARNING] Count = " << GenCount << endl;
         continue;
      }

      vector<PseudoJet> Candidates;
      for(int i = 0; i < GenCount; i++)
      {
         FourVector P;
         P.SetPtEtaPhi(GenPT[i], GenEta[i], GenPhi[i]);
         if(GenDaughterCount[i] == 0)
            Candidates.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence Sequence(Candidates, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets();

      JetCount = 0;
      for(int i = 0; i < MAX; i++)
      {
         JetPT[i] = 0;
         JetEta[i] = 0;
         JetPhi[i] = 0;
      }

      for(int i = 0; i < Jets.size(); i++)
      {
         if(Jets[i].perp() < 10)
            continue;

         if(JetCount < MAX)
         {
            JetPT[JetCount] = Jets[i].perp();
            JetEta[JetCount] = Jets[i].eta();
            JetPhi[JetCount] = Jets[i].phi();
         }
         JetCount = JetCount + 1;
      }
      if(JetCount >= MAX)
      {
         cerr << "[WARNING] Number of jets larger than array size!  skipping event..." << endl;
         cerr << "[WARNING] Count = " << JetCount << endl;
         continue;
      }

      OutputTree.Fill();
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   HN.Write();
   OutputTree.Write();

   OutputFile.Close();

   InputFile->Close();
   delete InputFile;

   return 0;
}



