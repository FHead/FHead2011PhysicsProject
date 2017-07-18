#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TEllipse.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"
#include "fastjet/contrib/SoftDrop.hh"
using namespace fastjet;

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions3.h"
#include "ProgressBar.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

#include "BasicUtilities.h"
#include "Messenger.h"
#include "SDJetHelper.h"
#include "CATree.h"
#include "DataHelper.h"

#define MAXSIZE 25000000

int main(int argc, char *argv[])
{
   SetThesisStyle();

   if(argc != 9 && argc != 10 && argc != 12)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag PTHatMin PTHatMax MinBiasForest GhostDistance Range ReuseRate Mod ModBase" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];
   double PTHatMin = atof(argv[4]);
   double PTHatMax = atof(argv[5]);

   string MBInput = argv[6];

   double GhostDistance = atof(argv[7]);
   double Range = atof(argv[8]);

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);
   bool IsPPHiReco = IsPPHiRecoFromTag(Tag);

   bool PassThroughMode = false;
   bool UseRhoM = false;   // switch to use rho_m or not

   if(IsData == true)
      cerr << "I'd be glad to run on data for this study" << endl;

   int ReuseRate = 1;
   if(argc >= 10)
      ReuseRate = atoi(argv[9]);

   int Mod = -1;   // -1 = don't use
   int ModBase = -1;
   if(argc >= 12)
   {
      Mod = atoi(argv[10]);
      ModBase = atoi(argv[11]);
   }

   TFile *InputFile = TFile::Open(Input.c_str());
   TFile *MBInputFile = TFile::Open(MBInput.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
   }
   if(IsPPHiReco == true)
   {
      JetTreeName = "akPu4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akPu4CaloJetAnalyzer/t";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);
   PFTreeMessenger MPF(InputFile, "pfcandAnalyzer/pfTree");
   SkimTreeMessenger MSkim(InputFile);
   TriggerTreeMessenger MHLT(InputFile);
   RhoTreeMessenger MRho(InputFile);

   HiEventTreeMessenger MMBHiEvent(MBInputFile);
   PFTreeMessenger MMBPF(MBInputFile, "pfcandAnalyzer/pfTree");
   SkimTreeMessenger MMBSkim(MBInputFile);
   TriggerTreeMessenger MMBHLT(MBInputFile);
   RhoTreeMessenger MMBRho(MBInputFile);

   if(MHiEvent.Tree == NULL)
      return -1;
   if(PassThroughMode == false && MMBHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TTree OutputTree("OutputTree", "OutputTree");

   bool PassFilter, PassHLT, PassMBHLT;
   OutputTree.Branch("PassFilter", &PassFilter, "PassFilter/O");
   OutputTree.Branch("PassHLT", &PassHLT, "PassHLT/O");
   OutputTree.Branch("PassMBHLT", &PassMBHLT, "PassMBHLT/O");

   double TreeJetPT, TreeJetEta, TreeJetPhi, TreeJetSDMass, TreeJetDR, TreeJetMass;
   double TreeJetShape1, TreeJetShape2, TreeJetShape3, TreeJetShape4, TreeJetShape5;
   double TreeNewJetPT, TreeNewJetEta, TreeNewJetPhi, TreeNewJetSDMass, TreeNewJetDR, TreeNewJetZG, TreeNewJetMass, TreeNewJetSDPT;
   double TreeFirstJetPT, TreeFirstJetEta, TreeFirstJetPhi, TreeFirstJetSDMass, TreeFirstJetDR, TreeFirstJetZG, TreeFirstJetMass, TreeFirstJetSDPT;
   double TreeBestJetPT, TreeBestJetEta, TreeBestJetPhi, TreeBestJetSDMass, TreeBestJetDR, TreeBestJetZG, TreeBestJetMass, TreeBestJetSDPT;
   double TreeNewJetSDMass2, TreeNewJetDR2, TreeNewJetZG2, TreeNewJetSDPT2;
   double TreeFirstJetSDMass2, TreeFirstJetDR2, TreeFirstJetZG2, TreeFirstJetSDPT2;
   double TreeBestJetSDMass2, TreeBestJetDR2, TreeBestJetZG2, TreeBestJetSDPT2;
   double TreeNewJetSDMass3, TreeNewJetDR3, TreeNewJetZG3, TreeNewJetSDPT3;
   double TreeFirstJetSDMass3, TreeFirstJetDR3, TreeFirstJetZG3, TreeFirstJetSDPT3;
   double TreeBestJetSDMass3, TreeBestJetDR3, TreeBestJetZG3, TreeBestJetSDPT3;
   double TreeBestJetShape1, TreeBestJetShape2, TreeBestJetShape3, TreeBestJetShape4, TreeBestJetShape5;
   double TreeBestJetSJ1E, TreeBestJetSJ1PT, TreeBestJetSJ1Eta, TreeBestJetSJ1Phi;
   double TreeBestJetSJ2E, TreeBestJetSJ2PT, TreeBestJetSJ2Eta, TreeBestJetSJ2Phi;
   double TreeBestJetSJ1E2, TreeBestJetSJ1PT2, TreeBestJetSJ1Eta2, TreeBestJetSJ1Phi2;
   double TreeBestJetSJ2E2, TreeBestJetSJ2PT2, TreeBestJetSJ2Eta2, TreeBestJetSJ2Phi2;
   double TreeTotalPT, TreeRho, TreeTotalPTInJet, TreeTotalStuffInJet;
   double TreePTHat, TreeCentrality;
   double TreePFPT[200], TreePFEta[200], TreePFPhi[200];
   OutputTree.Branch("JetPT",           &TreeJetPT,           "JetPT/D");
   OutputTree.Branch("JetEta",          &TreeJetEta,          "JetEta/D");
   OutputTree.Branch("JetPhi",          &TreeJetPhi,          "JetPhi/D");
   OutputTree.Branch("JetSDMass",       &TreeJetSDMass,       "JetSDMass/D");
   OutputTree.Branch("JetDR",           &TreeJetDR,           "JetDR/D");
   OutputTree.Branch("JetMass",         &TreeJetMass,         "JetMass/D");
   OutputTree.Branch("JetShape1",       &TreeJetShape1,       "JetShape1/D");
   OutputTree.Branch("JetShape2",       &TreeJetShape2,       "JetShape2/D");
   OutputTree.Branch("JetShape3",       &TreeJetShape3,       "JetShape3/D");
   OutputTree.Branch("JetShape4",       &TreeJetShape4,       "JetShape4/D");
   OutputTree.Branch("JetShape5",       &TreeJetShape5,       "JetShape5/D");
   OutputTree.Branch("NewJetPT",        &TreeNewJetPT,        "NewJetPT/D");
   OutputTree.Branch("NewJetEta",       &TreeNewJetEta,       "NewJetEta/D");
   OutputTree.Branch("NewJetPhi",       &TreeNewJetPhi,       "NewJetPhi/D");
   OutputTree.Branch("NewJetSDMass",    &TreeNewJetSDMass,    "NewJetSDMass/D");
   OutputTree.Branch("NewJetDR",        &TreeNewJetDR,        "NewJetDR/D");
   OutputTree.Branch("NewJetZG",        &TreeNewJetZG,        "NewJetZG/D");
   OutputTree.Branch("NewJetMass",      &TreeNewJetMass,      "NewJetMass/D");
   OutputTree.Branch("NewJetSDPT",      &TreeNewJetSDPT,      "NewJetSDPT/D");
   OutputTree.Branch("FirstJetPT",      &TreeFirstJetPT,      "FirstJetPT/D");
   OutputTree.Branch("FirstJetEta",     &TreeFirstJetEta,     "FirstJetEta/D");
   OutputTree.Branch("FirstJetPhi",     &TreeFirstJetPhi,     "FirstJetPhi/D");
   OutputTree.Branch("FirstJetSDMass",  &TreeFirstJetSDMass,  "FirstJetSDMass/D");
   OutputTree.Branch("FirstJetDR",      &TreeFirstJetDR,      "FirstJetDR/D");
   OutputTree.Branch("FirstJetZG",      &TreeFirstJetZG,      "FirstJetZG/D");
   OutputTree.Branch("FirstJetMass",    &TreeFirstJetMass,    "FirstJetMass/D");
   OutputTree.Branch("FirstJetSDPT",    &TreeFirstJetSDPT,    "FirstJetSDPT/D");
   OutputTree.Branch("BestJetPT",       &TreeBestJetPT,       "BestJetPT/D");
   OutputTree.Branch("BestJetEta",      &TreeBestJetEta,      "BestJetEta/D");
   OutputTree.Branch("BestJetPhi",      &TreeBestJetPhi,      "BestJetPhi/D");
   OutputTree.Branch("BestJetSDMass",   &TreeBestJetSDMass,   "BestJetSDMass/D");
   OutputTree.Branch("BestJetDR",       &TreeBestJetDR,       "BestJetDR/D");
   OutputTree.Branch("BestJetZG",       &TreeBestJetZG,       "BestJetZG/D");
   OutputTree.Branch("BestJetMass",     &TreeBestJetMass,     "BestJetMass/D");
   OutputTree.Branch("BestJetSDPT",     &TreeBestJetSDPT,     "BestJetSDPT/D");
   OutputTree.Branch("BestJetSJ1E",    &TreeBestJetSJ1E,    "BestJetSJ1E/D");
   OutputTree.Branch("BestJetSJ1PT",    &TreeBestJetSJ1PT,    "BestJetSJ1PT/D");
   OutputTree.Branch("BestJetSJ1Eta",   &TreeBestJetSJ1Eta,   "BestJetSJ1Eta/D");
   OutputTree.Branch("BestJetSJ1Phi",   &TreeBestJetSJ1Phi,   "BestJetSJ1Phi/D");
   OutputTree.Branch("BestJetSJ2E",    &TreeBestJetSJ2E,    "BestJetSJ2E/D");
   OutputTree.Branch("BestJetSJ2PT",    &TreeBestJetSJ2PT,    "BestJetSJ2PT/D");
   OutputTree.Branch("BestJetSJ2Eta",   &TreeBestJetSJ2Eta,   "BestJetSJ2Eta/D");
   OutputTree.Branch("BestJetSJ2Phi",   &TreeBestJetSJ2Phi,   "BestJetSJ2Phi/D");
   OutputTree.Branch("NewJetSDMass2",   &TreeNewJetSDMass2,   "NewJetSDMass2/D");
   OutputTree.Branch("NewJetDR2",       &TreeNewJetDR2,       "NewJetDR2/D");
   OutputTree.Branch("NewJetZG2",       &TreeNewJetZG2,       "NewJetZG2/D");
   OutputTree.Branch("NewJetSDPT2",     &TreeNewJetSDPT2,     "NewJetSDPT2/D");
   OutputTree.Branch("FirstJetSDMass2", &TreeFirstJetSDMass2, "FirstJetSDMass2/D");
   OutputTree.Branch("FirstJetDR2",     &TreeFirstJetDR2,     "FirstJetDR2/D");
   OutputTree.Branch("FirstJetZG2",     &TreeFirstJetZG2,     "FirstJetZG2/D");
   OutputTree.Branch("FirstJetSDPT2",   &TreeFirstJetSDPT2,   "FirstJetSDPT2/D");
   OutputTree.Branch("BestJetSDMass2",  &TreeBestJetSDMass2,  "BestJetSDMass2/D");
   OutputTree.Branch("BestJetDR2",      &TreeBestJetDR2,      "BestJetDR2/D");
   OutputTree.Branch("BestJetZG2",      &TreeBestJetZG2,      "BestJetZG2/D");
   OutputTree.Branch("BestJetSDPT2",    &TreeBestJetSDPT2,    "BestJetSDPT2/D");
   OutputTree.Branch("BestJetSJ1E2",   &TreeBestJetSJ1E2,   "BestJetSJ1E2/D");
   OutputTree.Branch("BestJetSJ1PT2",   &TreeBestJetSJ1PT2,   "BestJetSJ1PT2/D");
   OutputTree.Branch("BestJetSJ1Eta2",  &TreeBestJetSJ1Eta2,  "BestJetSJ1Eta2/D");
   OutputTree.Branch("BestJetSJ1Phi2",  &TreeBestJetSJ1Phi2,  "BestJetSJ1Phi2/D");
   OutputTree.Branch("BestJetSJ2E2",   &TreeBestJetSJ2E2,   "BestJetSJ2E2/D");
   OutputTree.Branch("BestJetSJ2PT2",   &TreeBestJetSJ2PT2,   "BestJetSJ2PT2/D");
   OutputTree.Branch("BestJetSJ2Eta2",  &TreeBestJetSJ2Eta2,  "BestJetSJ2Eta2/D");
   OutputTree.Branch("BestJetSJ2Phi2",  &TreeBestJetSJ2Phi2,  "BestJetSJ2Phi2/D");
   OutputTree.Branch("NewJetSDMass3",   &TreeNewJetSDMass3,   "NewJetSDMass3/D");
   OutputTree.Branch("NewJetDR3",       &TreeNewJetDR3,       "NewJetDR3/D");
   OutputTree.Branch("NewJetZG3",       &TreeNewJetZG3,       "NewJetZG3/D");
   OutputTree.Branch("NewJetSDPT3",     &TreeNewJetSDPT3,     "NewJetSDPT3/D");
   OutputTree.Branch("FirstJetSDMass3", &TreeFirstJetSDMass3, "FirstJetSDMass3/D");
   OutputTree.Branch("FirstJetDR3",     &TreeFirstJetDR3,     "FirstJetDR3/D");
   OutputTree.Branch("FirstJetZG3",     &TreeFirstJetZG3,     "FirstJetZG3/D");
   OutputTree.Branch("FirstJetSDPT3",   &TreeFirstJetSDPT3,   "FirstJetSDPT3/D");
   OutputTree.Branch("BestJetSDMass3",  &TreeBestJetSDMass3,  "BestJetSDMass3/D");
   OutputTree.Branch("BestJetDR3",      &TreeBestJetDR3,      "BestJetDR3/D");
   OutputTree.Branch("BestJetZG3",      &TreeBestJetZG3,      "BestJetZG3/D");
   OutputTree.Branch("BestJetSDPT3",    &TreeBestJetSDPT3,    "BestJetSDPT3/D");
   OutputTree.Branch("BestJetShape1",   &TreeBestJetShape1,   "BestJetShape1/D");
   OutputTree.Branch("BestJetShape2",   &TreeBestJetShape2,   "BestJetShape2/D");
   OutputTree.Branch("BestJetShape3",   &TreeBestJetShape3,   "BestJetShape3/D");
   OutputTree.Branch("BestJetShape4",   &TreeBestJetShape4,   "BestJetShape4/D");
   OutputTree.Branch("BestJetShape5",   &TreeBestJetShape5,   "BestJetShape5/D");
   OutputTree.Branch("TotalPT",         &TreeTotalPT,         "TotalPT/D");
   OutputTree.Branch("Rho",             &TreeRho,             "Rho/D");
   OutputTree.Branch("TotalPTInJet",    &TreeTotalPTInJet,    "TotalPTInJet/D");
   OutputTree.Branch("TotalStuffInJet", &TreeTotalStuffInJet, "TotalStuffInJet/D");
   OutputTree.Branch("PTHat",           &TreePTHat,           "PTHat/D");
   OutputTree.Branch("Centrality",      &TreeCentrality,      "Centrality/D");
   OutputTree.Branch("PFPT",            &TreePFPT,            "PFPT[200]/D");
   OutputTree.Branch("PFEta",           &TreePFEta,           "PFEta[200]/D");
   OutputTree.Branch("PFPhi",           &TreePFPhi,           "PFPhi[200]/D");

   TH1D HN("HN", "Raw event count", 1, 0, 1);
   TH1D HPTHatAll("HPTHatAll", "PTHat", 100, 0, 500);
   TH1D HPTHatSelected("HPTHatSelected", "PTHat", 100, 0, 500);

   TH1D HRho("HRho", "Rho distribution", 100, 0, 400);
   TH1D HPTAdded("HPTAdded", "PT of added particles", 100, 0, 20);

   TH2D HJetPTComparison("HJetPTComparison", ";Jet PT;New Jet PT", 100, 0, 400, 100, 0, 400);
   TH2D HSDMassComparison("HSDMassComparison", ";Jet SD Mass;New Jet SD Mass", 100, 0, 100, 100, 0, 100);
   TH2D HRecoDRComparison("HRecoDRComparison", ";Jet Reco DR;New Jet Reco DR", 100, 0, 0.4, 100, 0, 0.4);

   TH2D HSDMassJetPT("HSDMassJetPT", ";Jet PT;SD Mass", 100, 80, 500, 100, 0, 100);
   TH2D HNewSDMassNewJetPT("HNewSDMassNewJetPT", ";New Jet PT;New SD Mass", 100, 0, 600, 100, 0, 100);

   TH1D HSDMass("HSDMass", "SD Mass, DR > 0.1;SD Mass", 100, 0, 100);
   TH1D HNewSDMass("HNewSDMass", "New SD Mass, New DR > 0.1; New SD Mass", 100, 0, 100);

   int EntryCount = MHiEvent.Tree->GetEntries() * 1.00;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(1);

   PdfFileHelper PdfFile("SanityFiles.pdf");
   PdfFile.AddTextPage("Some plots for individual jets");
   int WriteJetCount = 0;

   int MBEntryCount = MMBHiEvent.Tree->GetEntries();

   for(int iEntry = 0, ReuseCount = 1; iEntry < EntryCount; ReuseCount++)
   {
      if(EntryCount <= 250 || iEntry % (EntryCount / 300) == 0)
      {
         Bar.Update(iEntry);
         Bar.Print();
      }

      if(ReuseRate <= 1 || ReuseCount % ReuseRate == 0)
         iEntry = iEntry + 1;
      if(Mod >= 0 && Mod < ModBase && iEntry % ModBase != Mod)
         continue;

      HN.Fill(0);

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);
      MPF.GetEntry(iEntry);
      MHLT.GetEntry(iEntry);
      MSkim.GetEntry(iEntry);

      if(PassThroughMode == false)
      {
         MMBHiEvent.GetEntry(iEntry % MBEntryCount);
         MMBPF.GetEntry(iEntry % MBEntryCount);
         MMBSkim.GetEntry(iEntry % MBEntryCount);
         MMBHLT.GetEntry(iEntry % MBEntryCount);
         MMBRho.GetEntry(iEntry % MBEntryCount);
      }
      else
         MRho.GetEntry(iEntry);

      PassFilter = true;
      PassHLT = true;
      PassMBHLT = true;
      if(IsData == true)
      {
         if(MSkim.PassBasicFilterLoose() == false)
            PassFilter = false;
         if(PassThroughMode == false && MMBSkim.PassBasicFilterLoose() == false)
            PassFilter = false;
         if(MHLT.CheckTrigger("HLT_AK4PFJet80_Eta5p1_v1") == false)
            PassHLT = false;
         if(PassThroughMode == false && MMBHLT.CheckTrigger("HLT_HIL1MinimumBiasHF1ANDPixel_SingleTrack_v1") == false)
            PassMBHLT = false;
      }

      SDJetHelper HSDJet(MSDJet);

      HPTHatAll.Fill(MSDJet.PTHat);
      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;
      TreePTHat = MSDJet.PTHat;

      HPTHatSelected.Fill(MSDJet.PTHat);

      // Step 0 - get inputs ready
      double Centrality, Rho, RhoM;
      if(PassThroughMode == false)
      {
         Centrality = GetCentrality(MMBHiEvent.hiBin);
         Rho = GetRho(MMBRho.EtaMax, MMBRho.Rho, 0, true);
         RhoM = GetRho(MMBRho.EtaMax, MMBRho.RhoM, 0, true);
      }
      else
      {
         Centrality = GetCentrality(MHiEvent.hiBin);
         Rho = GetRho(MRho.EtaMax, MRho.Rho, 0, true);
         RhoM = GetRho(MRho.EtaMax, MRho.RhoM, 0, true);
      }

      TreeRho = Rho;
      TreeCentrality = Centrality;

      // Step 1 - get all PF candidates within range
      vector<PseudoJet> Candidates;
      for(int i = 0; i < MPF.ID->size(); i++)
      {
         double Mass = 0;
         if(UseRhoM == true && (*MPF.ID)[i] == 1)
            Mass = 0.13957018;   // Pion :D

         FourVector P;
         P.SetPtEtaPhiMass((*MPF.PT)[i], (*MPF.Eta)[i], (*MPF.Phi)[i], Mass);

         Candidates.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }

      // Step 2 - sprinkle underlying event contribution from MB
      double TotalPTInJet = 0;
      if(PassThroughMode == false)
      {
         for(int i = 0; i < MMBPF.ID->size(); i++)
         {
            double Mass = 0;
            if(UseRhoM == true && (*MMBPF.ID)[i] == 1)
               Mass = 0.13957018;   // Pion :D

            FourVector P;
            P.SetPtEtaPhiMass((*MMBPF.PT)[i], (*MMBPF.Eta)[i], (*MMBPF.Phi)[i], Mass);

            Candidates.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
         }
      }

      // Step 3 - do pileup subtraction algorithm - via fastjet
      JetDefinition Definition(antikt_algorithm, 0.4);
      double GhostArea = GhostDistance * GhostDistance;
      AreaDefinition AreaDef(active_area_explicit_ghosts, GhostedAreaSpec(6.0, 1, GhostArea));
      ClusterSequenceArea Sequence(Candidates, Definition, AreaDef);
      vector<PseudoJet> JetsWithGhosts = Sequence.inclusive_jets();

      vector<PseudoJet> CSJets(JetsWithGhosts.size());
      for(int i = 0; i < (int)JetsWithGhosts.size(); i++)
      {
         if(UseRhoM == false)
            RhoM = 0;
         contrib::ConstituentSubtractor Subtractor(Rho, RhoM);
         Subtractor.set_alpha(1);  // optional
         // subtractor.set_max_deltaR(2);  // optional
         CSJets[i] = Subtractor(JetsWithGhosts[i]);
      }

      // Step 4 - Clustering and pick the jets
      vector<PseudoJet> CSCandidates;
      for(int i = 0; i < (int)CSJets.size(); i++)
      {
         vector<PseudoJet> Constituents = CSJets[i].constituents();
         CSCandidates.insert(CSCandidates.end(), Constituents.begin(), Constituents.end());
      }
      ClusterSequence NewSequence(CSCandidates, Definition);
      vector<PseudoJet> SDJets = NewSequence.inclusive_jets();

      if(SDJets.size() == 0)   // Huh?
         continue;

      for(int iJ = 0; iJ < (int)SDJets.size(); iJ++)
      {
         FourVector SDJetP;
         SDJetP[0] = SDJets[iJ].e();
         SDJetP[1] = SDJets[iJ].px();
         SDJetP[2] = SDJets[iJ].py();
         SDJetP[3] = SDJets[iJ].pz();

         if(SDJetP.GetAbsEta() > 1.5)
            continue;
         if(SDJetP.GetPT() < 80)
            continue;

         int CSIndex = -1;
         double CSDR2 = -1;
         for(int i = 0; i < MJet.JetCount; i++)
         {
            double DR2 = GetDR2(MJet.JetEta[i], MJet.JetPhi[i], SDJetP.GetEta(), SDJetP.GetPhi());
            if(CSDR2 < 0 || CSDR2 > DR2)
            {
               CSIndex = i;
               CSDR2 = DR2;
            }
         }

         FourVector JetP;
         JetP.SetPtEtaPhi(MJet.JetPT[CSIndex], MJet.JetEta[CSIndex], MJet.JetPhi[CSIndex]);

         TreeJetPT = MJet.JetPT[CSIndex];
         TreeJetEta = MJet.JetEta[CSIndex];
         TreeJetPhi = MJet.JetPhi[CSIndex];

         int SDIndex = -1;
         double SDDR2 = -1;
         for(int i = 0; i < MSDJet.JetCount; i++)
         {
            double DR2 = GetDR2(SDJetP.GetEta(), SDJetP.GetPhi(), MSDJet.JetEta[i], MSDJet.JetPhi[i]);
            if(SDDR2 < 0 || SDDR2 > DR2)
            {
               SDIndex = i;
               SDDR2 = DR2;
            }
         }

         TreeJetDR = HSDJet.RecoSubJetDR[SDIndex];
         TreeJetSDMass = MSDJet.JetM[SDIndex];

         int ClosestCSJet = 0;
         double ClosestCSDR2 = -1;
         for(int i = 0; i < (int)CSJets.size(); i++)
         {
            double DR2 = GetDR2(CSJets[i].eta(), CSJets[i].phi(), SDJetP.GetEta(), SDJetP.GetPhi());
            if(ClosestCSDR2 < 0 || ClosestCSDR2 > DR2)
            {
               ClosestCSJet = i;
               ClosestCSDR2 = DR2;
            }
         }

         int MaxCSJet = 0;
         for(int i = 0; i < (int)CSJets.size(); i++)
            if(CSJets[i].perp() > CSJets[MaxCSJet].perp())
               MaxCSJet = i;

         PseudoJet Jet = CSJets[ClosestCSJet];
         FourVector FirstJetP(Jet.e(), Jet.px(), Jet.py(), Jet.pz());
         FourVector BestJetP = SDJetP;

         vector<FourVector> GoodCandidatesBest, GoodCandidatesFirst;

         vector<PseudoJet> Constituents = CSJets[ClosestCSJet].constituents();
         for(int i = 0; i < (int)Constituents.size(); i++)
         {
            FourVector P;
            P[0] = Constituents[i].e();
            P[1] = Constituents[i].px();
            P[2] = Constituents[i].py();
            P[3] = Constituents[i].pz();
            // if(GetDR(P, FirstJetP) < 0.4)
               GoodCandidatesFirst.push_back(P);
         }
         Constituents = SDJets[iJ].constituents();
         for(int i = 0; i < 200; i++)
         {
            TreePFPT[i] = 0;
            TreePFEta[i] = 0;
            TreePFPhi[i] = 0;
         }
         for(int i = 0; i < (int)Constituents.size(); i++)
         {
            FourVector P;
            P[0] = Constituents[i].e();
            P[1] = Constituents[i].px();
            P[2] = Constituents[i].py();
            P[3] = Constituents[i].pz();
            // if(GetDR(P, BestJetP) < 0.4)
               GoodCandidatesBest.push_back(P);

            if(i < 200)
            {
               TreePFPT[i] = P.GetPT();
               TreePFEta[i] = P.GetEta();
               TreePFPhi[i] = P.GetPhi();
            }
            else
               cerr << "Constituent size = " << Constituents.size() << "! increase output size!" << endl;
         }

         std::vector<fastjet::PseudoJet> particles, ghosts;
         SelectorIsPureGhost().sift(Constituents, ghosts, particles);
         // if(TreeCentrality > 0.8)
         {
            cout << "Centrality = " << TreeCentrality << endl;
            cout << "Jet PT = " << SDJets[iJ].perp() << endl;
            cout << "Particle Size = " << particles.size() << endl;
            cout << "Ghost Size = " << ghosts.size() << endl;
            cout << endl;
         }

         if(GoodCandidatesBest.size() == 0 && GoodCandidatesFirst.size() == 0)
         {
            TreeFirstJetPT = -1;
            TreeBestJetPT = -1;
            OutputTree.Fill();
            continue;
         }

         // Step 5 - Run SD algorithm on the subtracted candidates
         vector<Node *> NodesFirst;
         for(int i = 0; i < (int)GoodCandidatesFirst.size(); i++)
            NodesFirst.push_back(new Node(GoodCandidatesFirst[i]));
         vector<Node *> NodesBest;
         for(int i = 0; i < (int)GoodCandidatesBest.size(); i++)
            NodesBest.push_back(new Node(GoodCandidatesBest[i]));

         BuildCATree(NodesFirst);
         BuildCATree(NodesBest);
         Node *GroomedFirst = FindSDNode(NodesFirst[0]);
         Node *GroomedBest = FindSDNode(NodesBest[0]);
         Node *GroomedFirst2 = FindSDNode(NodesFirst[0], 0.5, 1.5);
         Node *GroomedBest2 = FindSDNode(NodesBest[0], 0.5, 1.5);
         Node *GroomedFirst3 = FindSDNode(NodesFirst[0], 0.3, 1.5);
         Node *GroomedBest3 = FindSDNode(NodesBest[0], 0.3, 1.5);

         TreeBestJetPT = BestJetP.GetPT();
         TreeBestJetEta = BestJetP.GetEta();
         TreeBestJetPhi = BestJetP.GetPhi();
         TreeBestJetSDMass = GroomedBest->P.GetMass();
         TreeBestJetSDMass2 = GroomedBest2->P.GetMass();
         TreeBestJetSDMass3 = GroomedBest3->P.GetMass();
         TreeBestJetSDPT = GroomedBest->P.GetPT();
         TreeBestJetSDPT2 = GroomedBest2->P.GetPT();
         TreeBestJetSDPT3 = GroomedBest3->P.GetPT();
         if(GroomedBest->N > 1)
         {
            FourVector P1 = GroomedBest->Child1->P;
            FourVector P2 = GroomedBest->Child2->P;
            TreeBestJetDR = GetDR(P1, P2);
            TreeBestJetZG = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());

            TreeBestJetSJ1E = P1[0];
            TreeBestJetSJ1PT = P1.GetPT();
            TreeBestJetSJ1Eta = P1.GetEta();
            TreeBestJetSJ1Phi = P1.GetPhi();
            TreeBestJetSJ2E = P2[0];
            TreeBestJetSJ2PT = P2.GetPT();
            TreeBestJetSJ2Eta = P2.GetEta();
            TreeBestJetSJ2Phi = P2.GetPhi();
         }
         else
            TreeBestJetDR = -1, TreeBestJetZG = -1;
         if(GroomedBest2->N > 1)
         {
            FourVector P1 = GroomedBest2->Child1->P;
            FourVector P2 = GroomedBest2->Child2->P;
            TreeBestJetDR2 = GetDR(P1, P2);
            TreeBestJetZG2 = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());

            TreeBestJetSJ1E2 = P1[0];
            TreeBestJetSJ1PT2 = P1.GetPT();
            TreeBestJetSJ1Eta2 = P1.GetEta();
            TreeBestJetSJ1Phi2 = P1.GetPhi();
            TreeBestJetSJ2E2 = P2[0];
            TreeBestJetSJ2PT2 = P2.GetPT();
            TreeBestJetSJ2Eta2 = P2.GetEta();
            TreeBestJetSJ2Phi2 = P2.GetPhi();
         }
         else
            TreeBestJetDR2 = -1, TreeBestJetZG2 = -1;
         if(GroomedBest3->N > 1)
         {
            FourVector P1 = GroomedBest3->Child1->P;
            FourVector P2 = GroomedBest3->Child2->P;
            TreeBestJetDR3 = GetDR(P1, P2);
            TreeBestJetZG3 = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeBestJetDR3 = -1, TreeBestJetZG3 = -1;

         // cout << "Best " << BestJetP << endl;
         // cout << TreeBestJetDR << " " << TreeBestJetSDMass << endl;

         TreeFirstJetPT = FirstJetP.GetPT();
         TreeFirstJetEta = FirstJetP.GetEta();
         TreeFirstJetPhi = FirstJetP.GetPhi();
         TreeFirstJetSDMass = GroomedFirst->P.GetMass();
         TreeFirstJetSDMass2 = GroomedFirst2->P.GetMass();
         TreeFirstJetSDMass3 = GroomedFirst3->P.GetMass();
         TreeFirstJetSDPT = GroomedFirst->P.GetPT();
         TreeFirstJetSDPT2 = GroomedFirst2->P.GetPT();
         TreeFirstJetSDPT3 = GroomedFirst3->P.GetPT();
         if(GroomedFirst->N > 1)
         {
            FourVector P1 = GroomedFirst->Child1->P;
            FourVector P2 = GroomedFirst->Child2->P;
            TreeFirstJetDR = GetDR(P1, P2);
            TreeFirstJetZG = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeFirstJetDR = -1, TreeFirstJetZG = -1;
         if(GroomedFirst2->N > 1)
         {
            FourVector P1 = GroomedFirst2->Child1->P;
            FourVector P2 = GroomedFirst2->Child2->P;
            TreeFirstJetDR2 = GetDR(P1, P2);
            TreeFirstJetZG2 = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeFirstJetDR2 = -1, TreeFirstJetZG2 = -1;
         if(GroomedFirst3->N > 1)
         {
            FourVector P1 = GroomedFirst3->Child1->P;
            FourVector P2 = GroomedFirst3->Child2->P;
            TreeFirstJetDR3 = GetDR(P1, P2);
            TreeFirstJetZG3 = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeFirstJetDR3 = -1, TreeFirstJetZG3 = -1;

         // cout << TreeFirstJetDR << " " << TreeFirstJetSDMass << endl;

         bool WriteJet = false;
         // if(Centrality > 0.8 && SDJets[iJ].eta() < 1.3 && SDJets[iJ].eta() > -1.3 && SDJets[iJ].perp() > 140 && TreeBestJetDR > 0.35)
         //    WriteJet = true;
         if(WriteJet == true)
            WriteJetCount = WriteJetCount + 1;
         if(WriteJetCount >= 10)
         {
            iEntry = EntryCount;
            break;
         }

         if(WriteJet == true)
         {
            cout << "Starting to make plots for jet #" << WriteJetCount << endl;
            PdfFile.AddTextPage(Form("Centrality %.2f, Rho %.2f, RhoM %.2f", Centrality, Rho, RhoM));
            PdfFile.AddTextPage(Form("Jet (%.2f, %.2f, %.2f) [%d:%d]", SDJets[iJ].perp(), SDJets[iJ].eta(), SDJets[iJ].phi(), MHiEvent.Run, MHiEvent.Event));
            
            TH2D HPP("HPP", "PP Jet;eta;phi", 200, -3, 3, 200, 0, 2 * M_PI);
            HPP.SetStats(0);
            for(int i = 0; i < MPF.ID->size(); i++)
            {
               HPP.Fill((*MPF.Eta)[i], (*MPF.Phi)[i], (*MPF.PT)[i]);
               HPP.Fill((*MPF.Eta)[i], (*MPF.Phi)[i] + 2 * M_PI, (*MPF.PT)[i]);
            }
            PdfFile.AddPlot(HPP, "colz");
         
            for(int i = 0; i < MMBPF.ID->size(); i++)
            {
               HPP.Fill((*MMBPF.Eta)[i], (*MMBPF.Phi)[i], (*MMBPF.PT)[i]);
               HPP.Fill((*MMBPF.Eta)[i], (*MMBPF.Phi)[i] + 2 * M_PI, (*MMBPF.PT)[i]);
            }
            PdfFile.AddPlot(HPP, "colz");

            TH2D HCS("HCS", "CS;eta;phi", 200, -3, 3, 200, 0, 2 * M_PI);
            HCS.SetStats(0);
            for(int i = 0; i < (int)CSCandidates.size(); i++)
               HCS.Fill(CSCandidates[i].eta(), CSCandidates[i].phi(), CSCandidates[i].perp());
            PdfFile.AddPlot(HCS, "colz");

            TCanvas Canvas;
            HCS.Draw("colz");
            TEllipse Circle;
            Circle.SetFillStyle(0);
            for(int i = 0; i < (int)JetsWithGhosts.size(); i++)
               Circle.DrawEllipse(JetsWithGhosts[i].eta(), JetsWithGhosts[i].phi(), 0.4, 0.4, 0.0, 360, 0.0, "");
            Circle.SetLineStyle(kDashed);
            Circle.SetLineColor(kRed);
            for(int i = 0; i < (int)SDJets.size(); i++)
            {
               if(i == iJ)
                  Circle.SetLineColor(kGreen);
               else
                  Circle.SetLineColor(kRed);

               Circle.DrawEllipse(SDJets[i].eta(), SDJets[i].phi(), 0.4, 0.4, 0.0, 360, 0.0, "");
               if(i == iJ)
               {
                  Circle.DrawEllipse(SDJets[i].eta(), SDJets[i].phi() + 2 * M_PI, 0.4, 0.4, 0.0, 360, 0.0, "");
                  Circle.DrawEllipse(SDJets[i].eta(), SDJets[i].phi() - 2 * M_PI, 0.4, 0.4, 0.0, 360, 0.0, "");
               }
            }
            PdfFile.AddCanvas(Canvas);

            TH2D HCSJet("HCSJet", "Candidate in jet;eta;phi", 200, -3, 3, 200, 0, 2 * M_PI);
            HCSJet.SetStats(0);
            vector<PseudoJet> JetCandidates = SDJets[iJ].constituents();
            for(int i = 0; i < (int)JetCandidates.size(); i++)
               HCSJet.Fill(JetCandidates[i].eta(), JetCandidates[i].phi(), JetCandidates[i].perp());
            PdfFile.AddPlot(HCSJet, "colz");

            vector<string> Text(20);
            Text[0] = Form("Jet: (%.1f, %.2f, %.2f)", SDJetP.GetPT(), SDJetP.GetEta(), SDJetP.GetPhi());
            Text[1] = "";
            Text[2] = Form("BestJet: (%.1f, %.2f, %.2f)", BestJetP.GetPT(), BestJetP.GetEta(), BestJetP.GetPhi());
            Text[3] = Form("GroomedPT %.2f", GroomedBest->P.GetPT());
            Text[4] = Form("SDMass %.2f, SDMass/Jet %.2f", GroomedBest->P.GetMass(), GroomedBest->P.GetMass() / BestJetP.GetPT());
            Text[5] = Form("DR %.2f, ZG %.2f", TreeBestJetDR, TreeBestJetZG);
            Text[6] = "";
            Text[7] = Form("SubJet1 (%.1f, %.2f, %.2f)", GroomedBest->Child1->P.GetPT(), GroomedBest->Child1->P.GetEta(), GroomedBest->Child1->P.GetPhi());
            Text[8] = Form("SubJet2 (%.1f, %.2f, %.2f)", GroomedBest->Child2->P.GetPT(), GroomedBest->Child2->P.GetEta(), GroomedBest->Child2->P.GetPhi());

            PdfFile.AddTextPage(Text);
         }


         // Cleanup
         if(NodesFirst.size() > 0)
            delete NodesFirst[0];
         if(NodesBest.size() > 0)
            delete NodesBest[0];

         if(BestJetP.GetPT() > 80 && (TreeBestJetDR > 0.35 || TreeBestJetDR2 > 0.35))   // be careful not to blow up storage
            OutputTree.Fill();
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   OutputTree.Write();

   HN.Write();
   HPTHatAll.Write();
   HPTHatSelected.Write();

   HRho.Write();
   HPTAdded.Write();

   HJetPTComparison.Write();
   HSDMassComparison.Write();
   HRecoDRComparison.Write();

   HSDMassJetPT.Write();
   HNewSDMassNewJetPT.Write();

   HSDMass.Write();
   HNewSDMass.Write();

   OutputFile.Close();

   MBInputFile->Close();
   InputFile->Close();
}




