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
   bool UseRhoM = false;

   SetThesisStyle();

   ClusterSequence::set_fastjet_banner_stream(NULL);

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

   bool Valid = true;
   int TreeSize = MHiEvent.Tree->GetEntries();
   if(MJet.Tree != NULL && MJet.Tree->GetEntries() > 0 && TreeSize != MJet.Tree->GetEntries())   Valid = false;
   if(MSDJet.Tree != NULL && MSDJet.Tree->GetEntries() > 0 && TreeSize != MSDJet.Tree->GetEntries())   Valid = false;
   if(MPF.Tree != NULL && MPF.Tree->GetEntries() > 0 && TreeSize != MPF.Tree->GetEntries())   Valid = false;
   if(MRho.Tree != NULL && MRho.Tree->GetEntries() > 0 && TreeSize != MRho.Tree->GetEntries())   Valid = false;

   if(Valid == false)
   {
      cerr << "Oh no!  This tree \"" << InputFileName << "\" is not properly merged!" << endl;
      return -1;
   }

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TH1D HN("HN", ";;", 1, 0, 1);

   TTree OutputTree("T", "T");

   double TreeHF, TreeHFPlus, TreeHFMinus, TreeHFPlusEta4, TreeHFMinusEta4;
   OutputTree.Branch("HF", &TreeHF, "HF/D");
   OutputTree.Branch("HFPlus", &TreeHFPlus, "HFPlus/D");
   OutputTree.Branch("HFMinus", &TreeHFMinus, "HFMinus/D");
   OutputTree.Branch("HFPlusEta4", &TreeHFPlusEta4, "HFPlusEta4/D");
   OutputTree.Branch("HFMinusEta4", &TreeHFMinusEta4, "HFMinusEta4/D");

   int TreePartonFlavor, TreePartonFlavorForB;
   OutputTree.Branch("Flavor", &TreePartonFlavor, "Flavor/I");
   OutputTree.Branch("FlavorB", &TreePartonFlavorForB, "FlavorB/I");

   double TreeJetCSPT, TreeJetCSRawPT, TreeJetCSEta, TreeJetCSPhi;
   OutputTree.Branch("JetCSPT", &TreeJetCSPT, "JetCSPT/D");
   OutputTree.Branch("JetCSRawPT", &TreeJetCSRawPT, "JetCSRawPT/D");
   OutputTree.Branch("JetCSEta", &TreeJetCSEta, "JetCSEta/D");
   OutputTree.Branch("JetCSPhi", &TreeJetCSPhi, "JetCSPhi/D");
   
   double TreeJetPT, TreeJetRawPT, TreeJetEta, TreeJetPhi;
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT/D");
   OutputTree.Branch("JetRawPT", &TreeJetRawPT, "JetRawPT/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi/D");

   double TreeGenPT, TreeGenEta, TreeGenPhi, TreeGenDR;
   OutputTree.Branch("GenPT", &TreeGenPT, "GenPT/D");
   OutputTree.Branch("GenEta", &TreeGenEta, "GenEta/D");
   OutputTree.Branch("GenPhi", &TreeGenPhi, "GenPhi/D");
   OutputTree.Branch("GenDR", &TreeGenDR, "GenDR/D");

   double TreeGenSubJetDR, TreeGenSDMass;
   double TreeGenSubJet1PT, TreeGenSubJet1Eta, TreeGenSubJet1Phi;
   double TreeGenSubJet2PT, TreeGenSubJet2Eta, TreeGenSubJet2Phi;
   OutputTree.Branch("GenSubJetDR", &TreeGenSubJetDR, "GenSubJetDR/D");
   OutputTree.Branch("GenSDMass", &TreeGenSDMass, "GenSDMass/D");
   OutputTree.Branch("GenSubJet1PT", &TreeGenSubJet1PT, "GenSubJet1PT/D");
   OutputTree.Branch("GenSubJet1Eta", &TreeGenSubJet1Eta, "GenSubJet1Eta/D");
   OutputTree.Branch("GenSubJet1Phi", &TreeGenSubJet1Phi, "GenSubJet1Phi/D");
   OutputTree.Branch("GenSubJet2PT", &TreeGenSubJet2PT, "GenSubJet2PT/D");
   OutputTree.Branch("GenSubJet2Eta", &TreeGenSubJet2Eta, "GenSubJet2Eta/D");
   OutputTree.Branch("GenSubJet2Phi", &TreeGenSubJet2Phi, "GenSubJet2Phi/D");
   
   double TreeMatchEta, TreeMatchPhi;
   OutputTree.Branch("MatchEta", &TreeMatchEta, "MatchEta/D");
   OutputTree.Branch("MatchPhi", &TreeMatchPhi, "MatchPhi/D");
   
   double TreeSubJet1PT, TreeSubJet1Eta, TreeSubJet1Phi;
   double TreeSubJet2PT, TreeSubJet2Eta, TreeSubJet2Phi;
   OutputTree.Branch("SubJet1PT", &TreeSubJet1PT, "SubJet1PT/D");
   OutputTree.Branch("SubJet1Eta", &TreeSubJet1Eta, "SubJet1Eta/D");
   OutputTree.Branch("SubJet1Phi", &TreeSubJet1Phi, "SubJet1Phi/D");
   OutputTree.Branch("SubJet2PT", &TreeSubJet2PT, "SubJet2PT/D");
   OutputTree.Branch("SubJet2Eta", &TreeSubJet2Eta, "SubJet2Eta/D");
   OutputTree.Branch("SubJet2Phi", &TreeSubJet2Phi, "SubJet2Phi/D");

   double TreeSubJetDR, TreeSDMass;
   OutputTree.Branch("SubJetDR", &TreeSubJetDR, "SubJetDR/D");
   OutputTree.Branch("SDMass", &TreeSDMass, "SDMass/D");

   double TreeCentrality, TreePTHat, TreeRho;
   OutputTree.Branch("Centrality", &TreeCentrality, "Centrality/D");
   OutputTree.Branch("PTHat", &TreePTHat, "PTHat/D");
   OutputTree.Branch("Rho", &TreeRho, "Rho/D");

   double TreeMatchDR, TreeMatchPT;
   OutputTree.Branch("MatchDR", &TreeMatchDR, "MatchDR/D");
   OutputTree.Branch("MatchPT", &TreeMatchPT, "MatchPT/D");

   int TreeDepth0, TreeDepth7, TreeDepths[10];
   OutputTree.Branch("Depth0", &TreeDepth0, "Depth0/I");
   OutputTree.Branch("Depth7", &TreeDepth7, "Depth7/I");
   OutputTree.Branch("Depths", &TreeDepths, "Depths[10]/I");

   double TreeSubJetDR0, TreeSDMass0, TreeSubJetWTADR0, TreeSDPT0;
   double TreeSubJetDR7, TreeSDMass7, TreeSubJetWTADR7, TreeSDPT7;
   double TreeSubJetDRs[10], TreeSDMasses[10], TreeSubJetWTADRs[10];
   OutputTree.Branch("SubJetDR0", &TreeSubJetDR0, "SubJetDR0/D");
   OutputTree.Branch("SDMass0", &TreeSDMass0, "SDMass0/D");
   OutputTree.Branch("SubJetWTADR0", &TreeSubJetWTADR0, "SubJetWTADR0/D");
   OutputTree.Branch("SDPT0", &TreeSDPT0, "SDPT0/D");
   OutputTree.Branch("SubJetDR7", &TreeSubJetDR7, "SubJetDR7/D");
   OutputTree.Branch("SDMass7", &TreeSDMass7, "SDMass7/D");
   OutputTree.Branch("SDPT7", &TreeSDPT7, "SDPT7/D");
   OutputTree.Branch("SubJetDRs", &TreeSubJetDRs, "SubJetDRs[10]/D");
   OutputTree.Branch("SDMasses", &TreeSDMasses, "SDMasses[10]/D");
   OutputTree.Branch("SubJetWTADRs", &TreeSubJetWTADRs, "SubJetWTADRs[10]/D");
   
   double TreeSubJet1E0, TreeSubJet1PT0, TreeSubJet1Eta0, TreeSubJet1Phi0, TreeSubJet1WTAEta0, TreeSubJet1WTAPhi0;
   double TreeSubJet2E0, TreeSubJet2PT0, TreeSubJet2Eta0, TreeSubJet2Phi0, TreeSubJet2WTAEta0, TreeSubJet2WTAPhi0;
   OutputTree.Branch("SubJet1E0", &TreeSubJet1E0, "SubJet1E0/D");
   OutputTree.Branch("SubJet1PT0", &TreeSubJet1PT0, "SubJet1PT0/D");
   OutputTree.Branch("SubJet1Eta0", &TreeSubJet1Eta0, "SubJet1Eta0/D");
   OutputTree.Branch("SubJet1Phi0", &TreeSubJet1Phi0, "SubJet1Phi0/D");
   OutputTree.Branch("SubJet1WTAEta0", &TreeSubJet1WTAEta0, "SubJet1WTAEta0/D");
   OutputTree.Branch("SubJet1WTAPhi0", &TreeSubJet1WTAPhi0, "SubJet1WTAPhi0/D");
   OutputTree.Branch("SubJet2E0", &TreeSubJet2E0, "SubJet2E0/D");
   OutputTree.Branch("SubJet2PT0", &TreeSubJet2PT0, "SubJet2PT0/D");
   OutputTree.Branch("SubJet2Eta0", &TreeSubJet2Eta0, "SubJet2Eta0/D");
   OutputTree.Branch("SubJet2Phi0", &TreeSubJet2Phi0, "SubJet2Phi0/D");
   OutputTree.Branch("SubJet2WTAEta0", &TreeSubJet2WTAEta0, "SubJet2WTAEta0/D");
   OutputTree.Branch("SubJet2WTAPhi0", &TreeSubJet2WTAPhi0, "SubJet2WTAPhi0/D");
   
   double TreeSubJet1E7, TreeSubJet1PT7, TreeSubJet1Eta7, TreeSubJet1Phi7;
   double TreeSubJet2E7, TreeSubJet2PT7, TreeSubJet2Eta7, TreeSubJet2Phi7;
   OutputTree.Branch("SubJet1E7", &TreeSubJet1E7, "SubJet1E7/D");
   OutputTree.Branch("SubJet1PT7", &TreeSubJet1PT7, "SubJet1PT7/D");
   OutputTree.Branch("SubJet1Eta7", &TreeSubJet1Eta7, "SubJet1Eta7/D");
   OutputTree.Branch("SubJet1Phi7", &TreeSubJet1Phi7, "SubJet1Phi7/D");
   OutputTree.Branch("SubJet2E7", &TreeSubJet2E7, "SubJet2E7/D");
   OutputTree.Branch("SubJet2PT7", &TreeSubJet2PT7, "SubJet2PT7/D");
   OutputTree.Branch("SubJet2Eta7", &TreeSubJet2Eta7, "SubJet2Eta7/D");
   OutputTree.Branch("SubJet2Phi7", &TreeSubJet2Phi7, "SubJet2Phi7/D");
   
   double TreeSubJet1Es[10], TreeSubJet1PTs[10], TreeSubJet1Etas[10], TreeSubJet1Phis[10], TreeSubJet1WTAEtas[10], TreeSubJet1WTAPhis[10];
   double TreeSubJet2Es[10], TreeSubJet2PTs[10], TreeSubJet2Etas[10], TreeSubJet2Phis[10], TreeSubJet2WTAEtas[10], TreeSubJet2WTAPhis[10];
   OutputTree.Branch("SubJet1Es",  &TreeSubJet1Es,  "SubJet1Es[10]/D");
   OutputTree.Branch("SubJet1PTs",  &TreeSubJet1PTs,  "SubJet1PTs[10]/D");
   OutputTree.Branch("SubJet1Etas", &TreeSubJet1Etas, "SubJet1Etas[10]/D");
   OutputTree.Branch("SubJet1Phis", &TreeSubJet1Phis, "SubJet1Phis[10]/D");
   OutputTree.Branch("SubJet1WTAEtas", &TreeSubJet1WTAEtas, "SubJet1WTAEtas[10]/D");
   OutputTree.Branch("SubJet1WTAPhis", &TreeSubJet1WTAPhis, "SubJet1WTAPhis[10]/D");
   OutputTree.Branch("SubJet2Es",  &TreeSubJet2Es,  "SubJet2Es[10]/D");
   OutputTree.Branch("SubJet2PTs",  &TreeSubJet2PTs,  "SubJet2PTs[10]/D");
   OutputTree.Branch("SubJet2Etas", &TreeSubJet2Etas, "SubJet2Etas[10]/D");
   OutputTree.Branch("SubJet2Phis", &TreeSubJet2Phis, "SubJet2Phis[10]/D");
   OutputTree.Branch("SubJet2WTAEtas", &TreeSubJet2WTAEtas, "SubJet2WTAEtas[10]/D");
   OutputTree.Branch("SubJet2WTAPhis", &TreeSubJet2WTAPhis, "SubJet2WTAPhis[10]/D");

   bool TreePassPbPb40, TreePassPbPb60, TreePassPbPb80, TreePassPbPb100;
   OutputTree.Branch("PassPbPb40", &TreePassPbPb40, "PassPbPb40/O");
   OutputTree.Branch("PassPbPb60", &TreePassPbPb60, "PassPbPb60/O");
   OutputTree.Branch("PassPbPb80", &TreePassPbPb80, "PassPbPb80/O");
   OutputTree.Branch("PassPbPb100", &TreePassPbPb100, "PassPbPb100/O");

   double TreeCHF, TreeNHF, TreeCEF, TreeNEF, TreeMUF;
   OutputTree.Branch("CHF", &TreeCHF, "CHF/D");
   OutputTree.Branch("NHF", &TreeNHF, "NHF/D");
   OutputTree.Branch("CEF", &TreeCEF, "CEF/D");
   OutputTree.Branch("NEF", &TreeNEF, "NEF/D");
   OutputTree.Branch("MUF", &TreeMUF, "MUF/D");
   
   double TreeCHM, TreeNHM, TreeCEM, TreeNEM, TreeMUM;
   OutputTree.Branch("CHM", &TreeCHM, "CHM/D");
   OutputTree.Branch("NHM", &TreeNHM, "NHM/D");
   OutputTree.Branch("CEM", &TreeCEM, "CEM/D");
   OutputTree.Branch("NEM", &TreeNEM, "NEM/D");
   OutputTree.Branch("MUM", &TreeMUM, "MUM/D");

   int EntryCount = MHiEvent.Tree->GetEntries() * 1.00;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   PdfFileHelper PdfFile("SanityCheck.pdf");
   PdfFile.AddTextPage("Some visualizations :D");

   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(iE < 200 || (iE % (EntryCount / 300)) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MSDJet.GetEntry(iE);
      MPF.GetEntry(iE);
      MRho.GetEntry(iE);
      MHLT.GetEntry(iE);
      MSkim.GetEntry(iE);
      MGen.GetEntry(iE);
         
      HN.Fill(0);

      TreeHF = MHiEvent.hiHF;
      TreeHFPlus = MHiEvent.hiHFplus;
      TreeHFMinus = MHiEvent.hiHFminus;
      TreeHFPlusEta4 = MHiEvent.hiHFplusEta4;
      TreeHFMinusEta4 = MHiEvent.hiHFminusEta4;
         
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

      TreeCentrality = GetCentrality(MHiEvent.hiBin);
      TreePTHat = MSDJet.PTHat;
      TreeRho = GetRho(MRho.EtaMax, MRho.Rho, 0, true);

      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;

      vector<PseudoJet> GenJets;
      vector<PseudoJet> GenParticles;
      if(MGen.Tree != NULL)   // gen particle tree exists!
      {
         for(int iGen = 0; iGen < MGen.ID->size(); iGen++)
         {
            if((*MGen.SubEvent)[iGen] != 0)
               continue;
            if((*MGen.ID)[iGen] == 12 || (*MGen.ID)[iGen] == -12)
               continue;
            if((*MGen.ID)[iGen] == 14 || (*MGen.ID)[iGen] == -14)
               continue;
            if((*MGen.ID)[iGen] == 16 || (*MGen.ID)[iGen] == -16)
               continue;
            if((*MGen.DaughterCount)[iGen] != 0)
               continue;
            if((*MGen.PT)[iGen] < 5)   // hack!  to match the pp sample
               continue;

            FourVector P;
            P.SetPtEtaPhi((*MGen.PT)[iGen], (*MGen.Eta)[iGen], (*MGen.Phi)[iGen]);
            GenParticles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
         }
      }
      JetDefinition GenDefinition(antikt_algorithm, 0.4);
      ClusterSequence GenSequence(GenParticles, GenDefinition);
      GenJets = GenSequence.inclusive_jets(30);

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

      for(int iJ = 0; iJ < Jets.size(); iJ++)
      {
         int BestSDJet = 0;
         double BestSDDR = -1;
         for(int i = 0; i < (int)Jets.size(); i++)
         {
            double DR = GetDR(MSDJet.JetEta[i], MSDJet.JetPhi[i], Jets[iJ].eta(), Jets[iJ].phi());
            if(BestSDDR < 0 || DR < BestSDDR)
            {
               BestSDJet = i;
               BestSDDR = DR;
            }
         }

         if(BestSDDR >= 0)
         {
            TreeJetPT = MSDJet.JetPT[BestSDJet];
            TreeJetRawPT = MSDJet.JetRawPT[BestSDJet];
            TreeJetEta = MSDJet.JetEta[BestSDJet];
            TreeJetPhi = MSDJet.JetPhi[BestSDJet];

            TreeSDMass = MSDJet.JetM[BestSDJet];

            TreePartonFlavor = MSDJet.RefPartonFlavor[BestSDJet];
            TreePartonFlavorForB = MSDJet.RefPartonFlavorForB[BestSDJet];
         }

         if(GenJets.size() > 0)
         {
            int BestGenJet = 0;
            double BestGenDR = -1;
            for(int i = 0; i < (int)GenJets.size(); i++)
            {
               double DR = GetDR(Jets[iJ].eta(), Jets[iJ].phi(), GenJets[i].eta(), GenJets[i].phi());
               if(BestGenDR < 0 || DR < BestGenDR)
               {
                  BestGenJet = i;
                  BestGenDR = DR;
               }
            }

            TreeGenPT = GenJets[BestGenJet].perp();
            TreeGenEta = GenJets[BestGenJet].eta();
            TreeGenPhi = GenJets[BestGenJet].phi();
            TreeGenDR = BestGenDR;

            vector<Node *> GenNodes;
            vector<PseudoJet> GenConstituents = GenJets[BestGenJet].constituents();
            for(int i = 0; i < (int)GenConstituents.size(); i++)
            {
               FourVector P;
               P[0] = GenConstituents[i].e();
               P[1] = GenConstituents[i].px();
               P[2] = GenConstituents[i].py();
               P[3] = GenConstituents[i].pz();
               GenNodes.push_back(new Node(P));
            }

            BuildCATree(GenNodes);
         
            Node *GroomedGen = FindSDNode(GenNodes[0], 0.1, 0.0, 0.4);

            if(GroomedGen->N <= 1)
               TreeGenSubJetDR = -1;
            else
            {
               FourVector P1 = GroomedGen->Child1->P;
               FourVector P2 = GroomedGen->Child2->P;

               TreeGenSubJet1PT = P1.GetPT();
               TreeGenSubJet1Eta = P1.GetEta();
               TreeGenSubJet1Phi = P1.GetPhi();
               TreeGenSubJet2PT = P2.GetPT();
               TreeGenSubJet2Eta = P2.GetEta();
               TreeGenSubJet2Phi = P2.GetPhi();

               TreeGenSubJetDR = GetDR(P1, P2);
               TreeGenSDMass = GroomedGen->P.GetMass();
            }

            delete GenNodes[0];
         }
         else
         {
            TreeGenPT = -1;
            TreeGenEta = 0;
            TreeGenPhi = 0;
            TreeGenDR = -1;
         }

         int BestCSJet = 0;
         double BestCSDR = -1;
         for(int i = 0; i < MJet.JetCount; i++)
         {
            double DR = GetDR(Jets[iJ].eta(), Jets[iJ].phi(), MJet.JetEta[i], MJet.JetPhi[i]);
            if(BestCSDR < 0 || DR < BestCSDR)
            {
               BestCSJet = i;
               BestCSDR = DR;
            }
         }

         if(BestCSDR >= 0)
         {
            TreeCHF = MJet.JetPFCHF[BestCSJet];
            TreeNHF = MJet.JetPFNHF[BestCSJet];
            TreeCEF = MJet.JetPFCEF[BestCSJet];
            TreeNEF = MJet.JetPFNEF[BestCSJet];
            TreeMUF = MJet.JetPFMUF[BestCSJet];
            TreeCHM = MJet.JetPFCHM[BestCSJet];
            TreeNHM = MJet.JetPFNHM[BestCSJet];
            TreeCEM = MJet.JetPFCEM[BestCSJet];
            TreeNEM = MJet.JetPFNEM[BestCSJet];
            TreeMUM = MJet.JetPFMUM[BestCSJet];

            TreeJetCSPT = MJet.JetPT[BestCSJet];
            TreeJetCSRawPT = MJet.JetRawPT[BestCSJet];
            TreeJetCSEta = MJet.JetEta[BestCSJet];
            TreeJetCSPhi = MJet.JetPhi[BestCSJet];
         }

         TreeMatchDR = BestCSDR;
         TreeMatchPT = Jets[iJ].perp();
         TreeMatchEta = Jets[iJ].eta();
         TreeMatchPhi = Jets[iJ].phi();

         if(TreeMatchPT < 80)   // no need to store them!
            continue;
         if(abs(TreeMatchEta) > 1.5)
            continue;

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
         Node *Groomed[10];
         Groomed[0] = FindSDNode(Nodes[0], 0.20, 0.0, 0.4);
         Groomed[1] = FindSDNode(Nodes[0], 0.25, 0.0, 0.4);
         Groomed[2] = FindSDNode(Nodes[0], 0.30, 0.0, 0.4);
         Groomed[3] = FindSDNode(Nodes[0], 0.35, 0.0, 0.4);
         Groomed[4] = FindSDNode(Nodes[0], 0.40, 0.0, 0.4);
         Groomed[5] = FindSDNode(Nodes[0], 0.45, 0.0, 0.4);
         Groomed[6] = FindSDNode(Nodes[0], 0.20, -1.0, 0.4);
         Groomed[7] = FindSDNode(Nodes[0], 0.30, -1.0, 0.4);
         Groomed[8] = FindSDNode(Nodes[0], 0.40, -1.0, 0.4);
         Groomed[9] = FindSDNode(Nodes[0], 0.20, -2.0, 0.4);

         TreeDepth0 = NodeDistance(Groomed0, Nodes[0]);
         TreeDepth7 = NodeDistance(Groomed7, Nodes[0]);

         if(Groomed0->N > 1)
         {
            TreeSubJetDR0 = GetDR(Groomed0->Child1->P, Groomed0->Child2->P);
            TreeSDMass0 = Groomed0->P.GetMass();
            TreeSDPT0 = Groomed0->P.GetPT();

            TreeSubJet1E0   = Groomed0->Child1->P[0];
            TreeSubJet1PT0  = Groomed0->Child1->P.GetPT();
            TreeSubJet1Eta0 = Groomed0->Child1->P.GetEta();
            TreeSubJet1Phi0 = Groomed0->Child1->P.GetPhi();
            TreeSubJet2E0   = Groomed0->Child2->P[0];
            TreeSubJet2PT0  = Groomed0->Child2->P.GetPT();
            TreeSubJet2Eta0 = Groomed0->Child2->P.GetEta();
            TreeSubJet2Phi0 = Groomed0->Child2->P.GetPhi();

            std::pair<double, double> P1WTA = WinnerTakesAllAxis(Groomed0->Child1);
            std::pair<double, double> P2WTA = WinnerTakesAllAxis(Groomed0->Child2);
            
            TreeSubJet1WTAEta0 = P1WTA.first;
            TreeSubJet1WTAPhi0 = P1WTA.second;
            TreeSubJet2WTAEta0 = P2WTA.first;
            TreeSubJet2WTAPhi0 = P2WTA.second;
            TreeSubJetWTADR0 = GetDR(P1WTA.first, P1WTA.second, P2WTA.first, P2WTA.second);
         }
         else
            TreeSubJetDR0 = -1, TreeSubJetWTADR0 = -1;

         if(Groomed7->N > 1)
         {
            TreeSubJetDR7 = GetDR(Groomed7->Child1->P, Groomed7->Child2->P);
            TreeSDMass7 = Groomed7->P.GetMass();
            TreeSDPT7 = Groomed7->P.GetPT();

            TreeSubJet1E7   = Groomed7->Child1->P[0];
            TreeSubJet1PT7  = Groomed7->Child1->P.GetPT();
            TreeSubJet1Eta7 = Groomed7->Child1->P.GetEta();
            TreeSubJet1Phi7 = Groomed7->Child1->P.GetPhi();
            TreeSubJet2E7   = Groomed7->Child1->P[0];
            TreeSubJet2PT7  = Groomed7->Child2->P.GetPT();
            TreeSubJet2Eta7 = Groomed7->Child2->P.GetEta();
            TreeSubJet2Phi7 = Groomed7->Child2->P.GetPhi();
         }
         else
            TreeSubJetDR7 = -1;
            
         for(int i = 0; i < 10; i++)
         {
            if(Groomed[i]->N > 1)
            {
               TreeSubJetDRs[i] = GetDR(Groomed[i]->Child1->P, Groomed[i]->Child2->P);
               TreeSDMasses[i] = Groomed[i]->P.GetMass();

               TreeSubJet1Es[i] = Groomed[i]->Child1->P[0];
               TreeSubJet1PTs[i] = Groomed[i]->Child1->P.GetPT();
               TreeSubJet1Etas[i] = Groomed[i]->Child1->P.GetEta();
               TreeSubJet1Phis[i] = Groomed[i]->Child1->P.GetPhi();
               TreeSubJet2Es[i] = Groomed[i]->Child2->P[0];
               TreeSubJet2PTs[i] = Groomed[i]->Child2->P.GetPT();
               TreeSubJet2Etas[i] = Groomed[i]->Child2->P.GetEta();
               TreeSubJet2Phis[i] = Groomed[i]->Child2->P.GetPhi();

               std::pair<double, double> P1WTA = WinnerTakesAllAxis(Groomed[i]->Child1);
               std::pair<double, double> P2WTA = WinnerTakesAllAxis(Groomed[i]->Child2);

               TreeSubJet1WTAEtas[i] = P1WTA.first;
               TreeSubJet1WTAPhis[i] = P1WTA.second;
               TreeSubJet2WTAEtas[i] = P2WTA.first;
               TreeSubJet2WTAPhis[i] = P2WTA.second;
               TreeSubJetWTADRs[i] = GetDR(P1WTA.first, P1WTA.second, P2WTA.first, P2WTA.second);
            }
            else
               TreeSubJetDRs[i] = -1, TreeSubJetWTADRs[i] = -1;
         }

         if(Nodes.size() > 0 && Nodes[0] != NULL)
            delete Nodes[0];

         OutputTree.Fill();
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();
   HN.Write();

   OutputFile.Close();

   InputFile->Close();

   return 0;
}











