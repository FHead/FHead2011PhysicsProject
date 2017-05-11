#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"

#include "ProgressBar.h"

#include "Messenger.h"
#include "SDJetHelper.h"
#include "BasicUtilities.h"
#include "CATree.h"

int main(int argc, char *argv[])
{
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

   if(IsPP == true)
   {
      cerr << "Error the code is not equipped to run on pp yet!" << endl;
      return -1;
   }

   TFile InputFile(InputFileName.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string PUJetTreeName = "akPu4PFJetAnalyzer/t";
   string CaloPUJetTreeName = "akPu4CaloJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   string PFTreeName = "pfcandAnalyzerCS/pfTree";
   string J60ObjectTreeName = "hltobject/HLT_HIPuAK4CaloJet60_Eta5p1_v";
   string J80ObjectTreeName = "hltobject/HLT_HIPuAK4CaloJet80_Eta5p1_v";
   string J100ObjectTreeName = "hltobject/HLT_HIPuAK4CaloJet100_Eta5p1_v";

   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      PUJetTreeName = "ak4PFJetAnalyzer/t";
      CaloPUJetTreeName = "4CaloJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
      PFTreeName = "pfcandAnalyzer/pfTree";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);
   JetTreeMessenger MPUJet(InputFile, PUJetTreeName);
   JetTreeMessenger MCaloPUJet(InputFile, CaloPUJetTreeName);
   PFTreeMessenger MPF(InputFile, PFTreeName);
   RhoTreeMessenger MRho(InputFile);
   TriggerTreeMessenger MHLT(InputFile);
   SkimTreeMessenger MSkim(InputFile);
   TriggerObjectTreeMessenger MJ60(InputFile, J60ObjectTreeName);
   TriggerObjectTreeMessenger MJ80(InputFile, J80ObjectTreeName);
   TriggerObjectTreeMessenger MJ100(InputFile, J100ObjectTreeName);

   if(MHiEvent.Tree == NULL)
      return -1;

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

   double TreeJetPUMatchDR, TreeJetPUPT, TreeJetPURawPT, TreeJetPUEta, TreeJetPUPhi;
   OutputTree.Branch("JetPUMatchDR", &TreeJetPUMatchDR, "JetPUMatchDR/D");
   OutputTree.Branch("JetPURawPT", &TreeJetPURawPT, "JetPURawPT/D");
   OutputTree.Branch("JetPUPT", &TreeJetPUPT, "JetPUPT/D");
   OutputTree.Branch("JetPUEta", &TreeJetPUEta, "JetPUEta/D");
   OutputTree.Branch("JetPUPhi", &TreeJetPUPhi, "JetPUPhi/D");

   double TreeJetCaloPUMatchDR, TreeJetCaloPUPT, TreeJetCaloPURawPT, TreeJetCaloPUEta, TreeJetCaloPUPhi;
   OutputTree.Branch("JetCaloPUMatchDR", &TreeJetCaloPUMatchDR, "JetCaloPUMatchDR/D");
   OutputTree.Branch("JetCaloPURawPT", &TreeJetCaloPURawPT, "JetCaloPURawPT/D");
   OutputTree.Branch("JetCaloPUPT", &TreeJetCaloPUPT, "JetCaloPUPT/D");
   OutputTree.Branch("JetCaloPUEta", &TreeJetCaloPUEta, "JetCaloPUEta/D");
   OutputTree.Branch("JetCaloPUPhi", &TreeJetCaloPUPhi, "JetCaloPUPhi/D");

   double TreeJetPT, TreeJetRawPT, TreeJetEta, TreeJetPhi;
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT/D");
   OutputTree.Branch("JetRawPT", &TreeJetRawPT, "JetRawPT/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi/D");

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

   int TreeDepth0, TreeDepth7;
   OutputTree.Branch("Depth0", &TreeDepth0, "Depth0/I");
   OutputTree.Branch("Depth7", &TreeDepth7, "Depth7/I");

   double TreeSubJetDR0, TreeSDMass0;
   double TreeSubJetDR7, TreeSDMass7;
   OutputTree.Branch("SubJetDR0", &TreeSubJetDR0, "SubJetDR0/D");
   OutputTree.Branch("SDMass0", &TreeSDMass0, "SDMass0/D");
   OutputTree.Branch("SubJetDR7", &TreeSubJetDR7, "SubJetDR7/D");
   OutputTree.Branch("SDMass7", &TreeSDMass7, "SDMass7/D");

   double TreeSubJet1PT0, TreeSubJet1Eta0, TreeSubJet1Phi0;
   double TreeSubJet2PT0, TreeSubJet2Eta0, TreeSubJet2Phi0;
   OutputTree.Branch("SubJet1PT0", &TreeSubJet1PT0, "SubJet1PT0/D");
   OutputTree.Branch("SubJet1Eta0", &TreeSubJet1Eta0, "SubJet1Eta0/D");
   OutputTree.Branch("SubJet1Phi0", &TreeSubJet1Phi0, "SubJet1Phi0/D");
   OutputTree.Branch("SubJet2PT0", &TreeSubJet2PT0, "SubJet2PT0/D");
   OutputTree.Branch("SubJet2Eta0", &TreeSubJet2Eta0, "SubJet2Eta0/D");
   OutputTree.Branch("SubJet2Phi0", &TreeSubJet2Phi0, "SubJet2Phi0/D");

   double TreeSubJet1PT7, TreeSubJet1Eta7, TreeSubJet1Phi7;
   double TreeSubJet2PT7, TreeSubJet2Eta7, TreeSubJet2Phi7;
   OutputTree.Branch("SubJet1PT7", &TreeSubJet1PT7, "SubJet1PT7/D");
   OutputTree.Branch("SubJet1Eta7", &TreeSubJet1Eta7, "SubJet1Eta7/D");
   OutputTree.Branch("SubJet1Phi7", &TreeSubJet1Phi7, "SubJet1Phi7/D");
   OutputTree.Branch("SubJet2PT7", &TreeSubJet2PT7, "SubJet2PT7/D");
   OutputTree.Branch("SubJet2Eta7", &TreeSubJet2Eta7, "SubJet2Eta7/D");
   OutputTree.Branch("SubJet2Phi7", &TreeSubJet2Phi7, "SubJet2Phi7/D");

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

   int TreeJetIndex;
   OutputTree.Branch("JetIndex", &TreeJetIndex, "TreeJetIndex/I");

   // Trigger objects
   double TreeJ60PT, TreeJ60Eta, TreeJ60Phi;
   double TreeJ80PT, TreeJ80Eta, TreeJ80Phi;
   double TreeJ100PT, TreeJ100Eta, TreeJ100Phi;
   OutputTree.Branch("J60PT", &TreeJ60PT, "J60PT/D");
   OutputTree.Branch("J60Eta", &TreeJ60Eta, "J60Eta/D");
   OutputTree.Branch("J60Phi", &TreeJ60Phi, "J60Phi/D");
   OutputTree.Branch("J80PT", &TreeJ80PT, "J80PT/D");
   OutputTree.Branch("J80Eta", &TreeJ80Eta, "J80Eta/D");
   OutputTree.Branch("J80Phi", &TreeJ80Phi, "J80Phi/D");
   OutputTree.Branch("J100PT", &TreeJ100PT, "J100PT/D");
   OutputTree.Branch("J100Eta", &TreeJ100Eta, "J100Eta/D");
   OutputTree.Branch("J100Phi", &TreeJ100Phi, "J100Phi/D");

   double TreeJ60CaloPUPT, TreeJ60CaloPUEta, TreeJ60CaloPUPhi;
   double TreeJ80CaloPUPT, TreeJ80CaloPUEta, TreeJ80CaloPUPhi;
   double TreeJ100CaloPUPT, TreeJ100CaloPUEta, TreeJ100CaloPUPhi;
   OutputTree.Branch("J60CaloPUPT", &TreeJ60CaloPUPT, "J60CaloPUPT/D");
   OutputTree.Branch("J60CaloPUEta", &TreeJ60CaloPUEta, "J60CaloPUEta/D");
   OutputTree.Branch("J60CaloPUPhi", &TreeJ60CaloPUPhi, "J60CaloPUPhi/D");
   OutputTree.Branch("J80CaloPUPT", &TreeJ80CaloPUPT, "J80CaloPUPT/D");
   OutputTree.Branch("J80CaloPUEta", &TreeJ80CaloPUEta, "J80CaloPUEta/D");
   OutputTree.Branch("J80CaloPUPhi", &TreeJ80CaloPUPhi, "J80CaloPUPhi/D");
   OutputTree.Branch("J100CaloPUPT", &TreeJ100CaloPUPT, "J100CaloPUPT/D");
   OutputTree.Branch("J100CaloPUEta", &TreeJ100CaloPUEta, "J100CaloPUEta/D");
   OutputTree.Branch("J100CaloPUPhi", &TreeJ100CaloPUPhi, "J100CaloPUPhi/D");

   double TreeJ60PFPUPT, TreeJ60PFPUEta, TreeJ60PFPUPhi;
   double TreeJ80PFPUPT, TreeJ80PFPUEta, TreeJ80PFPUPhi;
   double TreeJ100PFPUPT, TreeJ100PFPUEta, TreeJ100PFPUPhi;
   OutputTree.Branch("J60PFPUPT", &TreeJ60PFPUPT, "J60PFPUPT/D");
   OutputTree.Branch("J60PFPUEta", &TreeJ60PFPUEta, "J60PFPUEta/D");
   OutputTree.Branch("J60PFPUPhi", &TreeJ60PFPUPhi, "J60PFPUPhi/D");
   OutputTree.Branch("J80PFPUPT", &TreeJ80PFPUPT, "J80PFPUPT/D");
   OutputTree.Branch("J80PFPUEta", &TreeJ80PFPUEta, "J80PFPUEta/D");
   OutputTree.Branch("J80PFPUPhi", &TreeJ80PFPUPhi, "J80PFPUPhi/D");
   OutputTree.Branch("J100PFPUPT", &TreeJ100PFPUPT, "J100PFPUPT/D");
   OutputTree.Branch("J100PFPUEta", &TreeJ100PFPUEta, "J100PFPUEta/D");
   OutputTree.Branch("J100PFPUPhi", &TreeJ100PFPUPhi, "J100PFPUPhi/D");

   int EntryCount = MHiEvent.Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(iE < 200 || (iE % (EntryCount / 300)) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      // Messengers
      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MSDJet.GetEntry(iE);
      MPUJet.GetEntry(iE);
      MPF.GetEntry(iE);
      MRho.GetEntry(iE);
      MHLT.GetEntry(iE);
      MSkim.GetEntry(iE);
      MJ60.GetEntry(iE);
      MJ80.GetEntry(iE);
      MJ100.GetEntry(iE);

      // For normalization purposes
      HN.Fill(0);

      // HF Stuff
      TreeHF = MHiEvent.hiHF;
      TreeHFPlus = MHiEvent.hiHFplus;
      TreeHFMinus = MHiEvent.hiHFminus;
      TreeHFPlusEta4 = MHiEvent.hiHFplusEta4;
      TreeHFMinusEta4 = MHiEvent.hiHFminusEta4;

      // Basic selection
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

      SDJetHelper HSDJet(MSDJet);

      // Centrality and stuff
      TreeCentrality = GetCentrality(MHiEvent.hiBin);
      TreePTHat = MSDJet.PTHat;
      TreeRho = GetRho(MRho.EtaMax, MRho.Rho, 0);

      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;

      // Trigger objects and matchings
      TreeJ60PT = -1, TreeJ60Eta = -1, TreeJ60Phi = -1;
      TreeJ60CaloPUPT = -1, TreeJ60Eta = -1, TreeJ60Phi = -1;
      TreeJ60PFPUPT = -1, TreeJ60PFPUEta = -1, TreeJ60PFPUPhi = -1;
      if(MJ60.ID != NULL && MJ60.ID->size() > 0)
      {
         TreeJ60PT = (*MJ60.PT)[0];   // I think the first one is always the largest PT - need to double check
         TreeJ60Eta = (*MJ60.Eta)[0];
         TreeJ60Phi = (*MJ60.Phi)[0];

         int BestIndex = -1;
         double BestDR2 = -1;
         for(int i = 0; i < MPUJet.JetCount; i++)
         {
            double DR2 = GetDR2(TreeJ60Eta, TreeJ60Phi, MPUJet.JetEta[i], MPUJet.JetPhi[i]);
            if(BestDR2 < 0 || BestDR2 > DR2)
            {
               BestIndex = i;
               BestDR2 = DR2;
            }
         }

         if(BestIndex >= 0)
         {
            TreeJ60PFPUPT = MPUJet.JetPT[BestIndex];
            TreeJ60PFPUEta = MPUJet.JetEta[BestIndex];
            TreeJ60PFPUPhi = MPUJet.JetPhi[BestIndex];
         }

         BestIndex = -1;
         BestDR2 = -1;
         for(int i = 0; i < MCaloPUJet.JetCount; i++)
         {
            double DR2 = GetDR2(TreeJ60Eta, TreeJ60Phi, MCaloPUJet.JetEta[i], MCaloPUJet.JetPhi[i]);
            if(BestDR2 < 0 || BestDR2 > DR2)
            {
               BestIndex = i;
               BestDR2 = DR2;
            }
         }

         cout << "Number of calo PU jet = " << MCaloPUJet.JetCount << endl;
         cout << BestIndex << endl;

         if(BestIndex >= 0)
         {
            TreeJ60CaloPUPT = MCaloPUJet.JetPT[BestIndex];
            TreeJ60CaloPUEta = MCaloPUJet.JetEta[BestIndex];
            TreeJ60CaloPUPhi = MCaloPUJet.JetPhi[BestIndex];
         }

         cout << TreeJ60CaloPUPT << " " << TreeJ60CaloPUEta << " " << TreeJ60CaloPUPhi << endl;
      }

      TreeJ80PT = -1, TreeJ80Eta = -1, TreeJ80Phi = -1;
      TreeJ80CaloPUPT = -1, TreeJ80Eta = -1, TreeJ80Phi = -1;
      TreeJ80PFPUPT = -1, TreeJ80PFPUEta = -1, TreeJ80PFPUPhi = -1;
      if(MJ80.ID != NULL && MJ80.ID->size() > 0)
      {
         TreeJ80PT = (*MJ80.PT)[0];   // I think the first one is always the largest PT - need to double check
         TreeJ80Eta = (*MJ80.Eta)[0];
         TreeJ80Phi = (*MJ80.Phi)[0];

         int BestIndex = -1;
         double BestDR2 = -1;
         for(int i = 0; i < MPUJet.JetCount; i++)
         {
            double DR2 = GetDR2(TreeJ80Eta, TreeJ80Phi, MPUJet.JetEta[i], MPUJet.JetPhi[i]);
            if(BestDR2 < 0 || BestDR2 > DR2)
            {
               BestIndex = i;
               BestDR2 = DR2;
            }
         }

         if(BestIndex >= 0)
         {
            TreeJ80PFPUPT = MPUJet.JetPT[BestIndex];
            TreeJ80PFPUEta = MPUJet.JetEta[BestIndex];
            TreeJ80PFPUPhi = MPUJet.JetPhi[BestIndex];
         }

         BestIndex = -1;
         BestDR2 = -1;
         for(int i = 0; i < MCaloPUJet.JetCount; i++)
         {
            double DR2 = GetDR2(TreeJ80Eta, TreeJ80Phi, MCaloPUJet.JetEta[i], MCaloPUJet.JetPhi[i]);
            if(BestDR2 < 0 || BestDR2 > DR2)
            {
               BestIndex = i;
               BestDR2 = DR2;
            }
         }

         if(BestIndex >= 0)
         {
            TreeJ80CaloPUPT = MCaloPUJet.JetPT[BestIndex];
            TreeJ80CaloPUEta = MCaloPUJet.JetEta[BestIndex];
            TreeJ80CaloPUPhi = MCaloPUJet.JetPhi[BestIndex];
         }
      }

      TreeJ100PT = -1, TreeJ100Eta = -1, TreeJ100Phi = -1;
      TreeJ100CaloPUPT = -1, TreeJ100Eta = -1, TreeJ100Phi = -1;
      TreeJ100PFPUPT = -1, TreeJ100PFPUEta = -1, TreeJ100PFPUPhi = -1;
      if(MJ100.ID != NULL && MJ100.ID->size() > 0)
      {
         TreeJ100PT = (*MJ100.PT)[0];   // I think the first one is always the largest PT - need to double check
         TreeJ100Eta = (*MJ100.Eta)[0];
         TreeJ100Phi = (*MJ100.Phi)[0];

         int BestIndex = -1;
         double BestDR2 = -1;
         for(int i = 0; i < MPUJet.JetCount; i++)
         {
            double DR2 = GetDR2(TreeJ100Eta, TreeJ100Phi, MPUJet.JetEta[i], MPUJet.JetPhi[i]);
            if(BestDR2 < 0 || BestDR2 > DR2)
            {
               BestIndex = i;
               BestDR2 = DR2;
            }
         }

         if(BestIndex >= 0)
         {
            TreeJ100PFPUPT = MPUJet.JetPT[BestIndex];
            TreeJ100PFPUEta = MPUJet.JetEta[BestIndex];
            TreeJ100PFPUPhi = MPUJet.JetPhi[BestIndex];
         }

         BestIndex = -1;
         BestDR2 = -1;
         for(int i = 0; i < MCaloPUJet.JetCount; i++)
         {
            double DR2 = GetDR2(TreeJ100Eta, TreeJ100Phi, MCaloPUJet.JetEta[i], MCaloPUJet.JetPhi[i]);
            if(BestDR2 < 0 || BestDR2 > DR2)
            {
               BestIndex = i;
               BestDR2 = DR2;
            }
         }

         if(BestIndex >= 0)
         {
            TreeJ100CaloPUPT = MCaloPUJet.JetPT[BestIndex];
            TreeJ100CaloPUEta = MCaloPUJet.JetEta[BestIndex];
            TreeJ100CaloPUPhi = MCaloPUJet.JetPhi[BestIndex];
         }
      }

      // Cluster all the PF candidates
      vector<PseudoJet> Particles;
      for(int iPF = 0; iPF < MPF.ID->size(); iPF++)
      {
         FourVector P;
         P.SetPtEtaPhi((*MPF.PT)[iPF], (*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
         Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets();

      // Loop over all SD jets
      TreeJetIndex = 0;
      for(int iJ = 0; iJ < MSDJet.JetCount; iJ++)
      {
         // Basic jet quantities
         TreeJetPT = MSDJet.JetPT[iJ];
         TreeJetRawPT = MSDJet.JetRawPT[iJ];
         TreeJetEta = MSDJet.JetEta[iJ];
         TreeJetPhi = MSDJet.JetPhi[iJ];

         TreeSubJet1PT = HSDJet.RecoSubJet1[iJ].GetPT();
         TreeSubJet1Eta = HSDJet.RecoSubJet1[iJ].GetEta();
         TreeSubJet1Phi = HSDJet.RecoSubJet1[iJ].GetPhi();
         TreeSubJet2PT = HSDJet.RecoSubJet2[iJ].GetPT();
         TreeSubJet2Eta = HSDJet.RecoSubJet2[iJ].GetEta();
         TreeSubJet2Phi = HSDJet.RecoSubJet2[iJ].GetPhi();

         TreeSubJetDR = HSDJet.RecoSubJetDR[iJ];
         TreeSDMass = MSDJet.JetM[iJ];

         TreePartonFlavor = MSDJet.RefPartonFlavor[iJ];
         TreePartonFlavorForB = MSDJet.RefPartonFlavorForB[iJ];

         // Match to CS jets to get PF jet ID
         int BestCSJet = 0;
         double BestCSDR = -1;
         for(int i = 0; i < MJet.JetCount; i++)
         {
            double DR = GetDR(MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ], MJet.JetEta[i], MJet.JetPhi[i]);
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

         // Match to PF PU jet
         int BestPUJet = 0;
         double BestPUDR = -1;
         for(int i = 0; i < MPUJet.JetCount; i++)
         {
            double DR = GetDR(MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ], MPUJet.JetEta[i], MPUJet.JetPhi[i]);
            if(BestPUDR < 0 || DR < BestPUDR)
            {
               BestPUJet = i;
               BestPUDR = DR;
            }
         }

         if(BestPUDR >= 0)
         {
            TreeJetPUMatchDR = BestPUDR;
            TreeJetPUPT = MPUJet.JetPT[BestPUJet];
            TreeJetPURawPT = MPUJet.JetRawPT[BestPUJet];
            TreeJetPUEta = MPUJet.JetEta[BestPUJet];
            TreeJetPUPhi = MPUJet.JetPhi[BestPUJet];
         }

         // Match to Calo PU Jet
         int BestCaloPUJet = 0;
         double BestCaloPUDR = -1;
         for(int i = 0; i < MCaloPUJet.JetCount; i++)
         {
            double DR = GetDR(MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ], MCaloPUJet.JetEta[i], MCaloPUJet.JetPhi[i]);
            if(BestCaloPUDR < 0 || DR < BestCaloPUDR)
            {
               BestCaloPUJet = i;
               BestCaloPUDR = DR;
            }
         }

         if(BestCaloPUDR >= 0)
         {
            TreeJetCaloPUMatchDR = BestCaloPUDR;
            TreeJetCaloPUPT = MCaloPUJet.JetPT[BestCaloPUJet];
            TreeJetCaloPURawPT = MCaloPUJet.JetRawPT[BestCaloPUJet];
            TreeJetCaloPUEta = MCaloPUJet.JetEta[BestCaloPUJet];
            TreeJetCaloPUPhi = MCaloPUJet.JetPhi[BestCaloPUJet];
         }

         // What is the closest reclustered jets - for additional SD settings
         int BestJet = 0;
         double BestDR = -1;
         for(int i = 0; i < (int)Jets.size(); i++)
         {
            double DR = GetDR(MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ], Jets[i].eta(), Jets[i].phi());
            if(BestDR < 0 || DR < BestDR)
            {
               BestJet = i;
               BestDR = DR;
            }
         }

         if(BestDR >= 0)
         {
            TreeMatchDR = BestDR;
            TreeMatchPT = Jets[BestJet].perp();

            if(TreeJetPT < 40 && TreeMatchPT < 40)   // no need to store them!
               continue;
            if(abs(TreeJetEta) > 1.5)
               continue;

            vector<PseudoJet> Constituents = Jets[BestJet].constituents();
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

            TreeDepth0 = NodeDistance(Groomed0, Nodes[0]);
            TreeDepth7 = NodeDistance(Groomed7, Nodes[0]);

            if(Groomed0->N > 1)
            {
               TreeSubJetDR0 = GetDR(Groomed0->Child1->P, Groomed0->Child2->P);
               TreeSDMass0 = Groomed0->P.GetMass();

               TreeSubJet1PT0 = Groomed0->Child1->P.GetPT();
               TreeSubJet1Eta0 = Groomed0->Child1->P.GetEta();
               TreeSubJet1Phi0 = Groomed0->Child1->P.GetPhi();
               TreeSubJet2PT0 = Groomed0->Child2->P.GetPT();
               TreeSubJet2Eta0 = Groomed0->Child2->P.GetEta();
               TreeSubJet2Phi0 = Groomed0->Child2->P.GetPhi();
            }
            else
               TreeSubJetDR0 = -1;

            if(Groomed7->N > 1)
            {
               TreeSubJetDR7 = GetDR(Groomed7->Child1->P, Groomed7->Child2->P);
               TreeSDMass7 = Groomed7->P.GetMass();

               TreeSubJet1PT7 = Groomed7->Child1->P.GetPT();
               TreeSubJet1Eta7 = Groomed7->Child1->P.GetEta();
               TreeSubJet1Phi7 = Groomed7->Child1->P.GetPhi();
               TreeSubJet2PT7 = Groomed7->Child2->P.GetPT();
               TreeSubJet2Eta7 = Groomed7->Child2->P.GetEta();
               TreeSubJet2Phi7 = Groomed7->Child2->P.GetPhi();
            }
            else
               TreeSubJetDR7 = -1;

            delete Nodes[0];
         }
         else
            TreeMatchDR = -1;

         OutputTree.Fill();
         TreeJetIndex = TreeJetIndex + 1;
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();
   HN.Write();

   OutputFile.Close();

   InputFile.Close();

   return 0;
}










