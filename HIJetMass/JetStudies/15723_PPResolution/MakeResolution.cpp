#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"

#include "ProgressBar.h"

#include "Messenger.h"
#include "BasicUtilities.h"

int main(int argc, char *argv[])
{
   string FileName = "PPExample.root";
   string OutputFileName = "Output.root";
   string JetTreeName = "ak4PFJetAnalyzer/t";
   string Tag = "PPDijet";
   double PTHatMin = 0;
   double PTHatMax = 100000;

   if(argc != 7 && argc != 6)
   {
      cerr << "Usage: " << argv[0] << " FileName OutputFileName Tag PTHatMin PTHatMax [JetTreeName]" << endl;
      return -1;
   }

   FileName = argv[1];
   OutputFileName = argv[2];
   Tag = argv[3];
   PTHatMin = atof(argv[4]);
   PTHatMax = atof(argv[5]);
   if(argc == 7)
      JetTreeName = argv[6];

   bool IsData = IsDataFromTag(Tag);
   if(IsData == true)
   {
      cerr << "Oh no!  We don't have gen PT in data!" << endl;
      return -1;
   }

   bool IsPP = IsPPFromTag(Tag);

   TFile File(FileName.c_str());

   HiEventTreeMessenger MHiEvent(File);
   JetTreeMessenger MJet(File, JetTreeName);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("Tree", "Tree");

   double TreeJetPT, TreeJetEta, TreeJetPhi;
   double TreeRefPT, TreeRefEta, TreeRefPhi;
   double TreeRun, TreeLumi, TreeEvent;
   double TreePTHat;
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi/D");
   OutputTree.Branch("RefPT", &TreeRefPT, "RefPT/D");
   OutputTree.Branch("RefEta", &TreeRefEta, "RefEta/D");
   OutputTree.Branch("RefPhi", &TreeRefPhi, "RefPhi/D");
   OutputTree.Branch("Run", &TreeRun, "Run/D");
   OutputTree.Branch("Lumi", &TreeLumi, "Lumi/D");
   OutputTree.Branch("Event", &TreeEvent, "Event/D");
   OutputTree.Branch("PTHat", &TreePTHat, "PTHat/D");
   
   TH1D HN("HN", "Raw event count", 1, 0, 1);
   TH1D HPTHatAll("HPTHatAll", "PTHat", 100, 0, 500);
   TH1D HPTHatSelected("HPTHatSelected", "PTHat", 100, 0, 500);

   int EntryCount = MHiEvent.Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(3);

   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Bar.Update(iEntry);
      if(EntryCount < 250 || (iEntry % (EntryCount / 300)) == 0)
         Bar.Print();

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);

      HN.Fill(0);

      HPTHatAll.Fill(MJet.PTHat);
      if(MJet.PTHat <= PTHatMin || MJet.PTHat > PTHatMax)
         continue;
      TreePTHat = MJet.PTHat;

      HPTHatSelected.Fill(MJet.PTHat);

      TreeRun = MHiEvent.Run;
      TreeLumi = MHiEvent.Lumi;
      TreeEvent = MHiEvent.Event;

      for(int iJ = 0; iJ < MJet.JetCount; iJ++)
      {
         TreeJetPT = MJet.JetPT[iJ];
         TreeJetEta = MJet.JetEta[iJ];
         TreeJetPhi = MJet.JetPhi[iJ];
         TreeRefPT = MJet.RefPT[iJ];
         TreeRefEta = MJet.RefEta[iJ];
         TreeRefPhi = MJet.RefPhi[iJ];

         OutputTree.Fill();
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   HN.Write();
   HPTHatAll.Write();
   HPTHatSelected.Write();

   OutputTree.Write();

   OutputFile.Close();

   File.Close();

   return 0;
}





