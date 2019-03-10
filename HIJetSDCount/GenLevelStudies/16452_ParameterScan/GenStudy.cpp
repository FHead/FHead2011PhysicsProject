#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"
using namespace fastjet;

#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TEllipse.h"
#include "TGraph.h"

#include "ProgressBar.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

#include "Messenger.h"
#include "SDJetHelper.h"
#include "BasicUtilities.h"
#include "CATree.h"

#include "JewelMessenger.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   /////////////////
   // Basic Stuff //
   /////////////////

   bool UseRhoM = false;

   SetThesisStyle();

   ClusterSequence::set_fastjet_banner_stream(NULL);

   ////////////
   // Inputs //
   ////////////

   string InputFileName = "HiForestAOD_999.root";
   string OutputFileName = "Output_HiForestAOD_999.root";
   string Tag = "AA6Dijet100";
   double PTHatMin = -1000000;
   double PTHatMax = 1000000;

   if(argc < 6)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag PTHatMin PTHatMax" << endl;
      return -1;
   }

   InputFileName = argv[1];
   OutputFileName = argv[2];
   Tag = argv[3];
   PTHatMin = atof(argv[4]);
   PTHatMax = atof(argv[5]);

   ////////////////////////
   // Prepare messengers //
   ////////////////////////

   bool IsPP = IsPPFromTag(Tag);
   bool IsData = IsDataFromTag(Tag);
   bool IsPPHiReco = IsPPHiRecoFromTag(Tag);

   TFile *InputFile = TFile::Open(InputFileName.c_str());

   JewelMessenger MJewel(InputFile);

   /////////////////////////
   // Prepare output file //
   /////////////////////////

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TH1D HN("HN", ";;", 1, 0, 1);

   TTree OutputTree("T", "T");

   // Event coordinates
   int TreeRun, TreeEvent, TreeLumi;
   OutputTree.Branch("Run", &TreeRun, "Run/I");
   OutputTree.Branch("Event", &TreeEvent, "Event/I");
   OutputTree.Branch("Lumi", &TreeLumi, "Lumi/I");

   // Event-wide quantities
   double TreeCentrality, TreePTHat, TreeRho, TreeWeight;
   OutputTree.Branch("Centrality", &TreeCentrality, "Centrality/D");
   OutputTree.Branch("PTHat", &TreePTHat, "PTHat/D");
   OutputTree.Branch("Rho", &TreeRho, "Rho/D");
   OutputTree.Branch("Weight", &TreeWeight, "Weight/D");

   // Trigger information
   bool TreePassPbPb40, TreePassPbPb60, TreePassPbPb80, TreePassPbPb100;
   OutputTree.Branch("PassPbPb40", &TreePassPbPb40, "PassPbPb40/O");
   OutputTree.Branch("PassPbPb60", &TreePassPbPb60, "PassPbPb60/O");
   OutputTree.Branch("PassPbPb80", &TreePassPbPb80, "PassPbPb80/O");
   OutputTree.Branch("PassPbPb100", &TreePassPbPb100, "PassPbPb100/O");

   // Gen-jet quantities
   int GenJetIndex;
   double GenJetPT, GenJetEta, GenJetPhi;
   OutputTree.Branch("GenJetIndex", &GenJetIndex, "GenJetIndex/I");
   OutputTree.Branch("GenJetPT", &GenJetPT, "GenJetPT/D");
   OutputTree.Branch("GenJetEta", &GenJetEta, "GenJetEta/D");
   OutputTree.Branch("GenJetPhi", &GenJetPhi, "GenJetPhi/D");

   double GenSDMass[9], GenSDDR[9], GenSDCount[9];
   OutputTree.Branch("GenSDMass", &GenSDMass, "GenSDMass[9]/D");
   OutputTree.Branch("GenSDDR", &GenSDDR, "GenSDDR[9]/D");
   OutputTree.Branch("GenSDCount", &GenSDCount, "GenSDCount[9]/D");

   double GenSDCKappa1[9], GenSDCKappa2[9], GenSDCKappa3[9];
   OutputTree.Branch("GenSDCKappa1", &GenSDCKappa1, "GenSDCKappa1[9]/D");
   OutputTree.Branch("GenSDCKappa2", &GenSDCKappa2, "GenSDCKappa2[9]/D");
   OutputTree.Branch("GenSDCKappa3", &GenSDCKappa3, "GenSDCKappa3[9]/D");

   int Flavor, FlavorB;
   OutputTree.Branch("Flavor", &Flavor, "Flavor/I");
   OutputTree.Branch("FlavorB", &FlavorB, "FlavorB/I");

   ///////////////////
   // Start looping //
   ///////////////////

   int EntryCount = MJewel.Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      Bar.Print();

      MJewel.GetEntry(iE);
         
      HN.Fill(0.0, MJewel.Weight);

      ///////////////////////
      // Event coordinates //
      ///////////////////////

      TreeRun = 314;
      TreeEvent = MJewel.E[0];
      TreeLumi = 26;

      /////////////////////////////////
      // Basic event-wide quantities //
      /////////////////////////////////

      TreeCentrality = 0.99;
      TreeWeight = MJewel.Weight;

      //////////////////////
      // Cluster gen-jets //
      //////////////////////

      vector<PseudoJet> GenParticles;
      for(int iG = 0; iG < MJewel.ParticleCount; iG++)
      {
         if(MJewel.Status[iG] != 1)
            continue;
         FourVector P(MJewel.E[iG], MJewel.PX[iG], MJewel.PY[iG], MJewel.PZ[iG]);
         GenParticles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition GenDefinition(antikt_algorithm, 0.4);
      ClusterSequence GenSequence(GenParticles, GenDefinition);
      vector<PseudoJet> GenJets = GenSequence.inclusive_jets();
     
      //////////////////////////
      // Loop over (gen) jets //
      //////////////////////////
      
      GenJetIndex = -1;
      for(int iG = 0; iG < GenJets.size(); iG++)
      {
         if(GenJets[iG].perp() < 10)   // mini jets!
            continue;
         if(fabs(GenJets[iG].eta()) > 3)   // forward jets!
            continue;

         GenJetIndex = GenJetIndex + 1;
         GenJetPT = GenJets[iG].perp();
         GenJetEta = GenJets[iG].eta();
         GenJetPhi = GenJets[iG].phi();

         vector<Node *> GenNodes;
         vector<PseudoJet> GenConstituent = GenJets[iG].constituents();
         for(int i = 0; i < (int)GenConstituent.size(); i++)
         {
            FourVector P;
            P.SetPtEtaPhi(GenConstituent[i].perp(), GenConstituent[i].eta(), GenConstituent[i].phi());
            GenNodes.push_back(new Node(P));
         }

         BuildCATree(GenNodes);

         double ZCut[9] = {0.1, 0.05, 0.5, 0.2, 0.007, 0.05, 0.025, 0.05, 0.1};
         double Beta[9] = {0.0, 0.0, 1.5, 1.5, -1, -0.845, -2, -0.544, 0.5};
         double R0 = 0.4;
         double RCut = 0.0;

         for(int i = 0; i < 9; i++)
         {
            Node *Groomed = FindSDNode(GenNodes[0], ZCut[i], Beta[i], R0);
            vector<pair<double, double>> SDC = CountSD(GenNodes[0], ZCut[i], Beta[i], R0, RCut);

            GenSDDR[i] = -1;
            if(Groomed->N > 1)
            {
               GenSDDR[i] = GetDR(Groomed->Child1->P, Groomed->Child2->P);
               GenSDMass[i] = Groomed->P.GetMass();
            }

            GenSDCount[i] = SDC.size();

            GenSDCKappa1[i] = SDCSum(SDC, 1.0);
            GenSDCKappa2[i] = SDCSum(SDC, 2.0);
            GenSDCKappa3[i] = SDCSum(SDC, 3.0);
         }

         OutputTree.Fill();

         if(GenNodes[0] != NULL)
            delete GenNodes[0];
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();
   HN.Write();

   OutputFile.Close();

   InputFile->Close();

   return 0;
}











