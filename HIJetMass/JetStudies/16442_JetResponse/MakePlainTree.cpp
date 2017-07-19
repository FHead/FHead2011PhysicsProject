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

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   string PFTreeName = "pfcandAnalyzer/pfTree";

   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
      PFTreeName = "pfcandAnalyzer/pfTree";
   }

   if(IsPPHiReco == true)
   {
      JetTreeName = "akPu4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akPu4CaloJetAnalyzer/t";
      PFTreeName = "pfcandAnalyzer/pfTree";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);
   PFTreeMessenger MPF(InputFile, PFTreeName);
   RhoTreeMessenger MRho(InputFile);
   TriggerTreeMessenger MHLT(InputFile);
   SkimTreeMessenger MSkim(InputFile);
   GenParticleTreeMessenger MGen(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

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
   double TreeCentrality, TreePTHat, TreeRho;
   OutputTree.Branch("Centrality", &TreeCentrality, "Centrality/D");
   OutputTree.Branch("PTHat", &TreePTHat, "PTHat/D");
   OutputTree.Branch("Rho", &TreeRho, "Rho/D");

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

   // Matched jet quantities
   double MatchJetRawPT, MatchJetEta, MatchJetPhi, MatchJetBestDR;
   OutputTree.Branch("MatchJetRawPT", &MatchJetRawPT, "MatchJetRawPT/D");
   OutputTree.Branch("MatchJetEta", &MatchJetEta, "MatchJetEta/D");
   OutputTree.Branch("MatchJetPhi", &MatchJetPhi, "MatchJetPhi/D");
   OutputTree.Branch("MatchJetBestDR", &MatchJetBestDR, "MatchJetBestDR/D");

   double CSJetRawPT, CSJetPT, CSJetEta, CSJetPhi, CSJetBestDR;
   OutputTree.Branch("CSJetRawPT", &CSJetRawPT, "CSJetRawPT/D");
   OutputTree.Branch("CSJetPT", &CSJetPT, "CSJetPT/D");
   OutputTree.Branch("CSJetEta", &CSJetEta, "CSJetEta/D");
   OutputTree.Branch("CSJetPhi", &CSJetPhi, "CSJetPhi/D");
   OutputTree.Branch("CSJetBestDR", &CSJetBestDR, "CSJetBestDR/D");

   double CSJetRefPT, CSJetRefEta, CSJetRefPhi;
   OutputTree.Branch("CSJetRefPT", &CSJetRefPT, "CSJetRefPT/D");
   OutputTree.Branch("CSJetRefEta", &CSJetRefEta, "CSJetRefEta/D");
   OutputTree.Branch("CSJetRefPhi", &CSJetRefPhi, "CSJetRefPhi/D");

   int Flavor, FlavorB;
   OutputTree.Branch("Flavor", &Flavor, "Flavor/I");
   OutputTree.Branch("FlavorB", &FlavorB, "FlavorB/I");

   // SD quantities
   int SD0Depth, SD7Depth;
   double SD0DR, SD7DR;
   double SD0Mass, SD7Mass;
   double SD0SubJet1E, SD0SubJet1PT, SD0SubJet1Eta, SD0SubJet1Phi;
   double SD0SubJet2E, SD0SubJet2PT, SD0SubJet2Eta, SD0SubJet2Phi;
   double SD7SubJet1E, SD7SubJet1PT, SD7SubJet1Eta, SD7SubJet1Phi;
   double SD7SubJet2E, SD7SubJet2PT, SD7SubJet2Eta, SD7SubJet2Phi;
   OutputTree.Branch("SD0Depth", &SD0Depth, "SD0Depth/I");
   OutputTree.Branch("SD7Depth", &SD7Depth, "SD7Depth/I");
   OutputTree.Branch("SD0DR", &SD0DR, "SD0DR/D");
   OutputTree.Branch("SD7DR", &SD7DR, "SD7DR/D");
   OutputTree.Branch("SD0Mass", &SD0Mass, "SD0Mass/D");
   OutputTree.Branch("SD7Mass", &SD7Mass, "SD7Mass/D");
   OutputTree.Branch("SD0SubJet1E", &SD0SubJet1E, "SD0SubJet1E/D");
   OutputTree.Branch("SD0SubJet1PT", &SD0SubJet1PT, "SD0SubJet1PT/D");
   OutputTree.Branch("SD0SubJet1Eta", &SD0SubJet1Eta, "SD0SubJet1Eta/D");
   OutputTree.Branch("SD0SubJet1Phi", &SD0SubJet1Phi, "SD0SubJet1Phi/D");
   OutputTree.Branch("SD0SubJet2E", &SD0SubJet2E, "SD0SubJet2E/D");
   OutputTree.Branch("SD0SubJet2PT", &SD0SubJet2PT, "SD0SubJet2PT/D");
   OutputTree.Branch("SD0SubJet2Eta", &SD0SubJet2Eta, "SD0SubJet2Eta/D");
   OutputTree.Branch("SD0SubJet2Phi", &SD0SubJet2Phi, "SD0SubJet2Phi/D");
   OutputTree.Branch("SD7SubJet1E", &SD7SubJet1E, "SD7SubJet1E/D");
   OutputTree.Branch("SD7SubJet1PT", &SD7SubJet1PT, "SD7SubJet1PT/D");
   OutputTree.Branch("SD7SubJet1Eta", &SD7SubJet1Eta, "SD7SubJet1Eta/D");
   OutputTree.Branch("SD7SubJet1Phi", &SD7SubJet1Phi, "SD7SubJet1Phi/D");
   OutputTree.Branch("SD7SubJet2E", &SD7SubJet2E, "SD7SubJet2E/D");
   OutputTree.Branch("SD7SubJet2PT", &SD7SubJet2PT, "SD7SubJet2PT/D");
   OutputTree.Branch("SD7SubJet2Eta", &SD7SubJet2Eta, "SD7SubJet2Eta/D");
   OutputTree.Branch("SD7SubJet2Phi", &SD7SubJet2Phi, "SD7SubJet2Phi/D");

   ///////////////////
   // Start looping //
   ///////////////////

   int EntryCount = MHiEvent.Tree->GetEntries() * 0.1;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      Bar.PrintWithMod(200);

      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MSDJet.GetEntry(iE);
      MPF.GetEntry(iE);
      MRho.GetEntry(iE);
      MHLT.GetEntry(iE);
      MSkim.GetEntry(iE);
      MGen.GetEntry(iE);
         
      HN.Fill(0);

      ///////////////////////
      // Event coordinates //
      ///////////////////////

      TreeRun = MHiEvent.Run;
      TreeEvent = MHiEvent.Event;
      TreeLumi = MHiEvent.Lumi;

      /////////////////////////////////
      // Basic event-wide quantities //
      /////////////////////////////////

      TreeCentrality = GetCentrality(MHiEvent.hiBin);
      TreePTHat = MSDJet.PTHat;
      TreeRho = GetRho(MRho.EtaMax, MRho.Rho, 0, true);

      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;
      
      ///////////////////
      // Event cleanup //
      ///////////////////

      TreePassPbPb40 = MHLT.CheckTrigger("HLT_HIPuAK4CaloJet40_Eta5p1_v1");
      TreePassPbPb60 = MHLT.CheckTrigger("HLT_HIPuAK4CaloJet60_Eta5p1_v1");
      TreePassPbPb80 = MHLT.CheckTrigger("HLT_HIPuAK4CaloJet80_Eta5p1_v1");
      TreePassPbPb100 = MHLT.CheckTrigger("HLT_HIPuAK4CaloJet100_Eta5p1_v1");

      if(IsData == true && IsPP == true && MHLT.CheckTrigger("HLT_AK4PFJet80_Eta5p1_v1") == false)
         continue;
      if(IsData == true && IsPP == false)
      {
         if(MHLT.CheckTrigger("HLT_HIPuAK4CaloJet40_Eta5p1_v1") == false
            && MHLT.CheckTrigger("HLT_HIPuAK4CaloJet60_Eta5p1_v1") == false
            && MHLT.CheckTrigger("HLT_HIPuAK4CaloJet80_Eta5p1_v1") == false
            && MHLT.CheckTrigger("HLT_HIPuAK4CaloJet100_Eta5p1_v1") == false)
         continue;
      }
      if(IsData == true && MSkim.PassBasicFilterLoose() == false)
         continue;

      //////////////////////
      // Cluster gen-jets //
      //////////////////////

      vector<PseudoJet> GenParticles;
      for(int iG = 0; iG < MGen.ID->size(); iG++)
      {
         if(MGen.SubEvent->size() < iG)
            continue;
         if((*MGen.SubEvent)[iG] != 0)
            continue;
         FourVector P;
         P.SetPtEtaPhi((*MGen.PT)[iG], (*MGen.Eta)[iG], (*MGen.Phi)[iG]);
         GenParticles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition GenDefinition(antikt_algorithm, 0.4);
      ClusterSequence GenSequence(GenParticles, GenDefinition);
      vector<PseudoJet> GenJets = GenSequence.inclusive_jets();

      ///////////////////////
      // Cluster reco jets //
      ///////////////////////

      vector<PseudoJet> Particles;
      for(int iPF = 0; iPF < MPF.ID->size(); iPF++)
      {
         double Mass = 0;
         if((*MPF.ID)[iPF] == 1)
            Mass = 0.13957018;   // Pion...
         if(UseRhoM == false)
            Mass = 0;
         FourVector P;
         P.SetPtEtaPhiMass((*MPF.PT)[iPF], (*MPF.Eta)[iPF], (*MPF.Phi)[iPF], Mass);
         Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      double GhostArea = 0.07 * 0.07;
      AreaDefinition AreaDef(active_area_explicit_ghosts, GhostedAreaSpec(6.0, 1, GhostArea));
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequenceArea Sequence(Particles, Definition, AreaDef);
      vector<PseudoJet> RawJets = Sequence.inclusive_jets();

      vector<PseudoJet> CSJets(RawJets.size());
      for(int i = 0; i < (int)RawJets.size(); i++)
      {
         double Rho = GetRho(MRho.EtaMax, MRho.Rho, RawJets[i].eta(), true);
         double RhoM = GetRho(MRho.EtaMax, MRho.RhoM, RawJets[i].eta(), true);
         if(UseRhoM == false)
            RhoM = 0;
         contrib::ConstituentSubtractor Subtractor(Rho, RhoM, 0, -1);
         Subtractor.set_alpha(1);
         CSJets[i] = Subtractor(RawJets[i]);
      }

      vector<PseudoJet> AllCandidates;
      for(int i = 0; i < (int)CSJets.size(); i++)
      {
         vector<PseudoJet> Constituents = CSJets[i].constituents();
         AllCandidates.insert(AllCandidates.end(), Constituents.begin(), Constituents.end());
      }
      ClusterSequence NewSequence(AllCandidates, Definition);
      vector<PseudoJet> Jets = NewSequence.inclusive_jets();

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

         ///////////////////
         // Match to jets //
         ///////////////////

         int iJ = -1;
         double BestDR = -1;
         for(int i = 0; i < (int)Jets.size(); i++)
         {
            double DR = GetDR(GenJets[iG].eta(), GenJets[iG].phi(), Jets[i].eta(), Jets[i].phi());
            if(BestDR < 0 || BestDR > DR)
               iJ = i, BestDR = DR;
         }

         MatchJetRawPT = Jets[iJ].perp();
         MatchJetEta = Jets[iJ].eta();
         MatchJetPhi = Jets[iJ].phi();

         MatchJetBestDR = BestDR;
 
         //////////////////////
         // Match to CS jets //
         //////////////////////

         int iCS = -1;
         double BestCSDR = -1;
         for(int i = 0; i < MJet.JetCount; i++)
         {
            double DR = GetDR(GenJets[iG].eta(), GenJets[iG].phi(), MJet.JetEta[i], MJet.JetPhi[i]);
            if(BestCSDR < 0 || BestCSDR > DR)
               iCS = i, BestCSDR = DR;
         }

         CSJetRawPT = MJet.JetRawPT[iCS];
         CSJetPT = MJet.JetPT[iCS];
         CSJetEta = MJet.JetEta[iCS];
         CSJetPhi = MJet.JetPhi[iCS];
         
         CSJetRefPT = MJet.RefPT[iCS];
         CSJetRefEta = MJet.RefEta[iCS];
         CSJetRefPhi = MJet.RefPhi[iCS];

         CSJetBestDR = BestCSDR;

         Flavor = MJet.RefPartonFlavor[iCS];
         FlavorB = MJet.RefPartonFlavorForB[iCS];

         ///////////////////////////////////////
         // Run soft drop on the matched jets //
         ///////////////////////////////////////

         vector<PseudoJet> Constituents = Jets[iJ].constituents();
         vector<Node *> Nodes;
         for(int i = 0; i < (int)Constituents.size(); i++)
         {
            FourVector P;
            P[0] = Constituents[i].e();
            P[1] = Constituents[i].px();
            P[2] = Constituents[i].py();
            P[3] = Constituents[i].pz();
            Nodes.push_back(new Node(P));
         }

         BuildCATree(Nodes);

         Node *Groomed0 = FindSDNode(Nodes[0], 0.1, 0.0, 0.4);
         Node *Groomed7 = FindSDNode(Nodes[0], 0.5, 1.5, 0.4);

         SD0Depth = NodeDistance(Groomed0, Nodes[0]);
         SD7Depth = NodeDistance(Groomed7, Nodes[0]);

         if(Groomed0->N > 1)
         {
            SD0DR         = GetDR(Groomed0->Child1->P, Groomed0->Child2->P);
            SD0Mass       = Groomed0->P.GetMass();

            SD0SubJet1E   = Groomed0->Child1->P[0];
            SD0SubJet1PT  = Groomed0->Child1->P.GetPT();
            SD0SubJet1Eta = Groomed0->Child1->P.GetEta();
            SD0SubJet1Phi = Groomed0->Child1->P.GetPhi();
            SD0SubJet2E   = Groomed0->Child2->P[0];
            SD0SubJet2PT  = Groomed0->Child2->P.GetPT();
            SD0SubJet2Eta = Groomed0->Child2->P.GetEta();
            SD0SubJet2Phi = Groomed0->Child2->P.GetPhi();
         }
         else
            SD0DR = -1;

         if(Groomed7->N > 1)
         {
            SD7DR         = GetDR(Groomed7->Child1->P, Groomed7->Child2->P);
            SD7Mass       = Groomed7->P.GetMass();

            SD7SubJet1E   = Groomed7->Child1->P[0];
            SD7SubJet1PT  = Groomed7->Child1->P.GetPT();
            SD7SubJet1Eta = Groomed7->Child1->P.GetEta();
            SD7SubJet1Phi = Groomed7->Child1->P.GetPhi();
            SD7SubJet2E   = Groomed7->Child1->P[0];
            SD7SubJet2PT  = Groomed7->Child2->P.GetPT();
            SD7SubJet2Eta = Groomed7->Child2->P.GetEta();
            SD7SubJet2Phi = Groomed7->Child2->P.GetPhi();
         }
         else
            SD7DR = -1;

         if(Nodes.size() > 0 && Nodes[0] != NULL)
            delete Nodes[0];

         OutputTree.Fill();
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











