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
   // double ZCut = 0.007;
   // double Beta = -1;
   // double R0 = 0.6;
   // double ThetaCut = 0;
   
   double ZCut = 0.1;
   double Beta = 0.0;
   double R0 = 0.4;
   double ThetaCut = 0.1;

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
   double GenJetAllPT, GenJetAllEta, GenJetAllPhi;
   double GenJetPT, GenJetEta, GenJetPhi;
   OutputTree.Branch("GenJetIndex", &GenJetIndex, "GenJetIndex/I");
   OutputTree.Branch("GenJetAllPT", &GenJetAllPT, "GenJetAllPT/D");
   OutputTree.Branch("GenJetAllEta", &GenJetAllEta, "GenJetAllEta/D");
   OutputTree.Branch("GenJetAllPhi", &GenJetAllPhi, "GenJetAllPhi/D");
   OutputTree.Branch("GenJetPT", &GenJetPT, "GenJetPT/D");
   OutputTree.Branch("GenJetEta", &GenJetEta, "GenJetEta/D");
   OutputTree.Branch("GenJetPhi", &GenJetPhi, "GenJetPhi/D");

   double GenSDMass, GenSDDR, GenSDCount;
   OutputTree.Branch("GenSDMass", &GenSDMass, "GenSDMass/D");
   OutputTree.Branch("GenSDDR", &GenSDDR, "GenSDDR/D");
   OutputTree.Branch("GenSDCount", &GenSDCount, "GenSDCount/D");

   double GenSDCKappa0, GenSDCKappa1, GenSDCKappa2;
   OutputTree.Branch("GenSDCKappa0", &GenSDCKappa0, "GenSDCKappa0/D");
   OutputTree.Branch("GenSDCKappa1", &GenSDCKappa1, "GenSDCKappa1/D");
   OutputTree.Branch("GenSDCKappa2", &GenSDCKappa2, "GenSDCKappa2/D");

   int Flavor, FlavorB;
   OutputTree.Branch("Flavor", &Flavor, "Flavor/I");
   OutputTree.Branch("FlavorB", &FlavorB, "FlavorB/I");

   // pp quantities
   double PPJetPT, PPJetEta, PPJetPhi;
   OutputTree.Branch("PPJetPT", &PPJetPT, "PPJetPT/D");
   OutputTree.Branch("PPJetEta", &PPJetEta, "PPJetEta/D");
   OutputTree.Branch("PPJetPhi", &PPJetPhi, "PPJetPhi/D");

   double PPSDMass, PPSDDR, PPSDCount;
   OutputTree.Branch("PPSDMass", &PPSDMass, "PPSDMass/D");
   OutputTree.Branch("PPSDDR", &PPSDDR, "PPSDDR/D");
   OutputTree.Branch("PPSDCount", &PPSDCount, "PPSDCount/D");

   double PPSDCKappa0, PPSDCKappa1, PPSDCKappa2;
   OutputTree.Branch("PPSDCKappa0", &PPSDCKappa0, "PPSDCKappa0/D");
   OutputTree.Branch("PPSDCKappa1", &PPSDCKappa1, "PPSDCKappa1/D");
   OutputTree.Branch("PPSDCKappa2", &PPSDCKappa2, "PPSDCKappa2/D");

   ///////////////////
   // Start looping //
   ///////////////////

   int EntryCount = MHiEvent.Tree->GetEntries() * 0.02;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      Bar.Print();
      // Bar.PrintWithMod(200);

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
      
      //////////////////////
      // Cluster gen-jets //
      //////////////////////

      double TotalPT = 0;

      vector<PseudoJet> PPGenParticles;
      vector<PseudoJet> GenParticles;
      for(int iG = 0; iG < MGen.ID->size(); iG++)
      {
         if(MGen.SubEvent->size() < iG)
            continue;
         if((*MGen.SubEvent)[iG] != 0)
            if(fabs((*MGen.Eta)[iG]) < 2.5)
               TotalPT = TotalPT + (*MGen.PT)[iG];
         FourVector P;
         P.SetPtEtaPhi((*MGen.PT)[iG], (*MGen.Eta)[iG], (*MGen.Phi)[iG]);
         GenParticles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
         if((*MGen.SubEvent)[iG] == 0)
            PPGenParticles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition GenDefinition(antikt_algorithm, R0);
      AreaDefinition AreaDef(active_area_explicit_ghosts, GhostedAreaSpec(6.0, 1, 0.005));
      ClusterSequenceArea GenSequence(GenParticles, GenDefinition, AreaDef);
      vector<PseudoJet> GenJetsWithGhosts = GenSequence.inclusive_jets();

      double Rho = TotalPT / (2.5 * 2) / (M_PI * 2);   // flat!
      TreeRho = Rho;

      ///////////
      // Do CS //
      ///////////

      vector<PseudoJet> GenJets(GenJetsWithGhosts.size());
      for(int i = 0; i < (int)GenJets.size(); i++)
      {
         contrib::ConstituentSubtractor Subtractor(Rho);
         Subtractor.set_alpha(1);
         GenJets[i] = Subtractor(GenJetsWithGhosts[i]);
      }

      /////////////////////
      // Cluster pp jets //
      /////////////////////

      JetDefinition PPGenDefinition(antikt_algorithm, R0);
      ClusterSequence PPGenSequence(PPGenParticles, PPGenDefinition);
      vector<PseudoJet> PPGenJets = PPGenSequence.inclusive_jets();

      //////////////////////////
      // Loop over (gen) jets //
      //////////////////////////
      
      GenJetIndex = -1;
      for(int iG = 0; iG < GenJets.size(); iG++)
      {
         if(GenJets[iG].perp() < 10)   // mini jets!
            continue;
         if(fabs(GenJets[iG].eta()) > 1.5)   // forward jets!
            continue;

         GenJetIndex = GenJetIndex + 1;
         GenJetPT = GenJets[iG].perp();
         GenJetEta = GenJets[iG].eta();
         GenJetPhi = GenJets[iG].phi();

         GenJetAllPT = GenJetsWithGhosts[iG].perp();
         GenJetAllEta = GenJetsWithGhosts[iG].eta();
         GenJetAllPhi = GenJetsWithGhosts[iG].phi();

         vector<Node *> GenNodes;
         vector<PseudoJet> GenConstituent = GenJets[iG].constituents();
         for(int i = 0; i < (int)GenConstituent.size(); i++)
         {
            FourVector P;
            P.SetPtEtaPhi(GenConstituent[i].perp(), GenConstituent[i].eta(), GenConstituent[i].phi());
            GenNodes.push_back(new Node(P));
         }

         BuildCATree(GenNodes);

         Node *Groomed = FindSDNode(GenNodes[0], ZCut, Beta, R0);
         vector<pair<double, double>> SDC = CountSD(GenNodes[0], ZCut, Beta, R0, ThetaCut);

         GenSDDR = -1;
         if(Groomed->N > 1)
         {
            GenSDDR = GetDR(Groomed->Child1->P, Groomed->Child2->P);
            GenSDMass = Groomed->P.GetMass();
         }

         GenSDCount = SDC.size();
         GenSDCKappa0 = SDCSum(SDC, 0.0);
         GenSDCKappa1 = SDCSum(SDC, 1.0);
         GenSDCKappa2 = SDCSum(SDC, 2.0);

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

         if(iCS >= 0)
         {
         Flavor = MJet.RefPartonFlavor[iCS];
         FlavorB = MJet.RefPartonFlavorForB[iCS];
         }
         else
         {
            Flavor = -999;
            FlavorB = -999;
         }

         //////////////////////////
         // Match to pp gen jets //
         //////////////////////////

         int iPP = -1;
         double BestPPDR = -1;
         for(int i = 0; i < (int)PPGenJets.size(); i++)
         {
            double DR = GetDR(GenJets[iG].eta(), GenJets[iG].phi(), PPGenJets[i].eta(), PPGenJets[i].phi());
            if(BestPPDR < 0 || BestPPDR > DR)
               iPP = i, BestPPDR = DR;
         }

         PPJetPT = -1;
         PPJetEta = -1;
         PPJetPhi = -1;

         vector<Node *> PPNodes;
         if(iPP >= 0)
         {
            PPJetPT = PPGenJets[iPP].perp();
            PPJetEta = PPGenJets[iPP].eta();
            PPJetPhi = PPGenJets[iPP].phi();

            vector<PseudoJet> PPConstituent = PPGenJets[iPP].constituents();
            for(int i = 0; i < (int)PPConstituent.size(); i++)
            {
               FourVector P;
               P.SetPtEtaPhi(PPConstituent[i].perp(), PPConstituent[i].eta(), PPConstituent[i].phi());
               PPNodes.push_back(new Node(P));
            }

            BuildCATree(PPNodes);

            Node *PPGroomed = FindSDNode(PPNodes[0], ZCut, Beta, R0);
            vector<pair<double, double>> PPSDC = CountSD(PPNodes[0], ZCut, Beta, R0, ThetaCut);

            PPSDDR = -1;
            if(PPGroomed->N > 1)
            {
               PPSDDR = GetDR(PPGroomed->Child1->P, PPGroomed->Child2->P);
               PPSDMass = PPGroomed->P.GetMass();
            }

            PPSDCount = PPSDC.size();
            PPSDCKappa0 = SDCSum(PPSDC, 0.0);
            PPSDCKappa1 = SDCSum(PPSDC, 1.0);
            PPSDCKappa2 = SDCSum(PPSDC, 2.0);
         }

         OutputTree.Fill();

         if(GenNodes.size() > 0 && GenNodes[0] != NULL)
            delete GenNodes[0];
         if(PPNodes.size() > 0 && PPNodes[0] != NULL)
            delete PPNodes[0];
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











