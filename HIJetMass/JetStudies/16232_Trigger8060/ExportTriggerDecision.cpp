#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

#include "Messenger.h"
#include "BasicUtilities.h"

int main(int argc, char *argv[]);

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

   if(IsData == false)
   {
      cerr << "Right now let's run on data." << endl;
      return -1;
   }

   TFile File(Input.c_str());

   HiEventTreeMessenger MHiEvent(File);
   JetTreeMessenger MJet(File, "akCs4PFJetAnalyzer/t");
   TriggerTreeMessenger MTrigger(File);

   if(MHiEvent.Tree == NULL)
   {
      cerr << "Tree not found.  Exiting" << endl;
      return -1;
   }

   TFile OutputFile(Output.c_str(), "RECREATE");

   TH1D HN("HN", "", 1, 0, 1);

   TTree Tree("Tree", "Tree");
   
   double TreeCentrality;
   Tree.Branch("Centrality", &TreeCentrality, "Centrality/D");

   double TreeJetPT;
   Tree.Branch("JetPT", &TreeJetPT, "JetPT/D");

   bool TreePassL144, TreePassL152;
   Tree.Branch("PassL144", &TreePassL144, "PassL144/O");
   Tree.Branch("PassL152", &TreePassL152, "PassL152/O");
   
   bool TreePass60, TreePass80, TreePass100;
   Tree.Branch("Pass60", &TreePass60, "Pass60/O");
   Tree.Branch("Pass80", &TreePass80, "Pass80/O");
   Tree.Branch("Pass100", &TreePass100, "Pass100/O");

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      HN.Fill(0);

      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MTrigger.GetEntry(iE);

      TreeCentrality = GetCentrality(MHiEvent.hiBin);

      if(MJet.PTHat < PTHatMin || MJet.PTHat > PTHatMax)
         continue;

      TreeJetPT = -1;
      for(int iJ = 0; iJ < MJet.JetCount; iJ++)
      {
         if(MJet.JetEta[iJ] < -5.1 || MJet.JetEta[iJ] > 5.1)
            continue;

         if(MJet.JetPT[iJ] > TreeJetPT)
            TreeJetPT = MJet.JetPT[iJ];
      }

      TreePassL144 = MTrigger.CheckTrigger("L1_SingleJet44_BptxAND");
      TreePassL152 = MTrigger.CheckTrigger("L1_SingleJet52_BptxAND");
      
      TreePass60 = MTrigger.CheckTrigger("HLT_HIPuAK4CaloJet60_Eta5p1_v1");
      TreePass80 = MTrigger.CheckTrigger("HLT_HIPuAK4CaloJet80_Eta5p1_v1");
      TreePass100 = MTrigger.CheckTrigger("HLT_HIPuAK4CaloJet100_Eta5p1_v1");

      Tree.Fill();
   }

   HN.Write();
   Tree.Write();

   OutputFile.Close();

   File.Close();

   return 0;
}






