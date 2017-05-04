#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"
#include "fastjet/contrib/SoftDrop.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"

// #include "ProgressBar.h"

#include "Messenger.h"

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " Input Output" << endl;
      return -1;
   }

   // Input TFile
   TFile File(argv[1]);

   // Messengers to get content of the trees
   HiEventTreeMessenger MHiEvent(File);
   PFTreeMessenger MPF(File, "pfcandAnalyzer/pfTree");
   PFTreeMessenger MPFCS(File, "pfcandAnalyzerCS/pfTree");

   // File error!
   if(MHiEvent.Tree == NULL)
      return -1;

   // Output Files and trees
   TFile OutputFile(argv[2], "RECREATE");

   TTree OutputTree("T", "T");

   double Centrality;
   OutputTree.Branch("Centrality", &Centrality, "Centrality/D");

   double JetPT, JetEta, JetPhi;
   double SDPT, SDEta, SDPhi, SDMass;
   double SDDR, SDZ, SDMu;
   OutputTree.Branch("JetPT", &JetPT, "&JetPT/D");
   OutputTree.Branch("JetEta", &JetEta, "&JetEta/D");
   OutputTree.Branch("JetPhi", &JetPhi, "&JetPhi/D");
   OutputTree.Branch("SDPT", &SDPT, "SDPT/D");
   OutputTree.Branch("SDEta", &SDEta, "SDEta/D");
   OutputTree.Branch("SDPhi", &SDPhi, "SDPhi/D");
   OutputTree.Branch("SDMass", &SDMass, "SDMass/D");
   OutputTree.Branch("SDDR", &SDDR, "SDDR/D");
   OutputTree.Branch("SDZ", &SDZ, "SDZ/D");
   OutputTree.Branch("SDMu", &SDMu, "SDMu/D");
   
   // Looping over tree and setup progress bar
   int EntryCount = MHiEvent.Tree->GetEntries();
   // ProgressBar Bar(cout, EntryCount);
   // Bar.SetStyle(2);

   for(int iE = 0; iE < EntryCount; iE = iE + 1)
   {
      // Bar.Update(iE);
      // if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0)
      //    Bar.Print();

      // Get entries from forest
      MHiEvent.GetEntry(iE);
      MPF.GetEntry(iE);
      MPFCS.GetEntry(iE);

      // Centrality
      Centrality = MHiEvent.hiBin;

      // Prepare fastjet clustering
      vector<PseudoJet> Particles;
      for(int i = 0; i < (int)MPFCS.ID->size(); i++)
      {
         PseudoJet P;
         P.reset_PtYPhiM((*MPFCS.PT)[i], (*MPFCS.Eta)[i], (*MPFCS.Phi)[i], 0);
         Particles.push_back(P);
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      // double GhostArea = 0.005;
      // AreaDefinition AreaDef(active_area_explicit_ghosts, GhostedAreaSpec(6.0, 1, GhostArea));
      // ClusterSequenceArea Sequence(Particles, Definition, AreaDef);
      ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets();

      // Loop over jets
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         // Basic cuts
         if(Jets[i].perp() < 50)
            continue;
         if(Jets[i].eta() < -2 || Jets[i].eta() > 2)
            continue;

         JetPT = Jets[i].perp();
         JetEta = Jets[i].eta();
         JetPhi = Jets[i].phi();

         // Soft drop!
         contrib::SoftDrop SD(0.0, 0.1);   // zcut & beta
         PseudoJet SDJet = SD(Jets[i]);

         SDPT = SDJet.perp();
         SDEta = SDJet.eta();
         SDPhi = SDJet.phi();
         SDMass = SDJet.m();

         SDDR = SDJet.structure_of<contrib::SoftDrop>().delta_R();
         SDZ = SDJet.structure_of<contrib::SoftDrop>().symmetry();
         SDMu = SDJet.structure_of<contrib::SoftDrop>().mu();

         cout << SDJet.constituents().size() << endl;

         OutputTree.Fill();
      }
   }

   // Bar.Update(EntryCount);
   // Bar.Print();
   // Bar.PrintLine();

   OutputTree.Write();

   OutputFile.Close();

   File.Close();

   return 0;
}

