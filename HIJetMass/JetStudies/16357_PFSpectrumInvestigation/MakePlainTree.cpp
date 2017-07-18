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
      JetTreeName = "akPu4CaloJetAnalyzer/t";
      SoftDropJetTreeName = "akPu4PFJetAnalyzer/t";
      PFTreeName = "pfcandAnalyzer/pfTree";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);
   PFTreeMessenger MPF(InputFile, PFTreeName);
   RhoTreeMessenger MRho(InputFile);
   TriggerTreeMessenger MHLT(InputFile);
   SkimTreeMessenger MSkim(InputFile);

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

   double TreeJetSDPT, TreeJetSDRawPT, TreeJetSDEta, TreeJetSDPhi;
   OutputTree.Branch("JetSDPT", &TreeJetSDPT, "JetSDPT/D");
   OutputTree.Branch("JetSDRawPT", &TreeJetSDRawPT, "JetSDRawPT/D");
   OutputTree.Branch("JetSDEta", &TreeJetSDEta, "JetSDEta/D");
   OutputTree.Branch("JetSDPhi", &TreeJetSDPhi, "JetSDPhi/D");
   
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

   int TreePFCount;
   double TreePFPT[1000] = {0}, TreePFEta[1000] = {0}, TreePFPhi[1000] = {0};
   int TreePFID[1000] = {0};
   OutputTree.Branch("PFCount", &TreePFCount, "PFCount/I");
   OutputTree.Branch("PFPT", &TreePFPT, "PFPT[1000]/D");
   OutputTree.Branch("PFEta", &TreePFEta, "PFEta[1000]/D");
   OutputTree.Branch("PFPhi", &TreePFPhi, "PFPhi[1000]/D");
   OutputTree.Branch("PFID", &TreePFID, "PFID[1000]/I");

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

      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MSDJet.GetEntry(iE);
      MPF.GetEntry(iE);
      MRho.GetEntry(iE);
      MHLT.GetEntry(iE);
      MSkim.GetEntry(iE);
         
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
      // if(IsData == true && IsPP == false)
      // {
      //    if(MHLT.CheckTrigger("HLT_HIPuAK4CaloJet40_Eta5p1_v1") == false
      //       && MHLT.CheckTrigger("HLT_HIPuAK4CaloJet60_Eta5p1_v1") == false
      //       && MHLT.CheckTrigger("HLT_HIPuAK4CaloJet80_Eta5p1_v1") == false
      //       && MHLT.CheckTrigger("HLT_HIPuAK4CaloJet100_Eta5p1_v1") == false)
      //    continue;
      // }
      if(IsData == true && MSkim.PassBasicFilterLoose() == false)
         continue;

      SDJetHelper HSDJet(MSDJet);

      TreeCentrality = GetCentrality(MHiEvent.hiBin);
      TreePTHat = MSDJet.PTHat;
      if(IsPP == false)
         TreeRho = GetRho(MRho.EtaMax, MRho.Rho, 0);
      else
         TreeRho = -1;

      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;

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

      for(int iJ = 0; iJ < MJet.JetCount; iJ++)
      {
         if(MJet.JetEta[iJ] > 2 || MJet.JetEta[iJ] < -2)
            continue;

         TreePFCount = 0;
         for(int i = 0; i < 1000; i++)
         {
            TreePFPT[i] = 0;
            TreePFEta[i] = 0;
            TreePFPhi[i] = 0;
            TreePFID[i] = 0;
         }
         for(int iPF = 0; iPF < MPF.ID->size(); iPF++)
         {
            if((*MPF.Eta)[iPF] < -2 || (*MPF.Eta)[iPF] > 2)
               continue;

            if(GetDR2(MJet.JetEta[iJ], MJet.JetPhi[iJ], (*MPF.Eta)[iPF], (*MPF.Phi)[iPF]) < 0.6 * 0.6)
            {
               TreePFPT[TreePFCount] = (*MPF.PT)[iPF];
               TreePFEta[TreePFCount] = (*MPF.Eta)[iPF];
               TreePFPhi[TreePFCount] = (*MPF.Phi)[iPF];
               TreePFID[TreePFCount] = (*MPF.ID)[iPF];
               TreePFCount = TreePFCount + 1;

               if(TreePFCount >= 1000)
                  break;
            }
         }

         TreeJetPT = MJet.JetPT[iJ];
         TreeJetRawPT = MJet.JetRawPT[iJ];
         TreeJetEta = MJet.JetEta[iJ];
         TreeJetPhi = MJet.JetPhi[iJ];

         TreeCHF = MJet.JetPFCHF[iJ];
         TreeNHF = MJet.JetPFNHF[iJ];
         TreeCEF = MJet.JetPFCEF[iJ];
         TreeNEF = MJet.JetPFNEF[iJ];
         TreeMUF = MJet.JetPFMUF[iJ];
         TreeCHM = MJet.JetPFCHM[iJ];
         TreeNHM = MJet.JetPFNHM[iJ];
         TreeCEM = MJet.JetPFCEM[iJ];
         TreeNEM = MJet.JetPFNEM[iJ];
         TreeMUM = MJet.JetPFMUM[iJ];

         int BestSDJet = 0;
         double BestSDDR = -1;
         for(int i = 0; i < MSDJet.JetCount; i++)
         {
            double DR = GetDR(MJet.JetEta[iJ], MJet.JetPhi[iJ], MSDJet.JetEta[i], MSDJet.JetPhi[i]);
            if(BestSDDR < 0 || DR < BestSDDR)
            {
               BestSDJet = i;
               BestSDDR = DR;
            }
         }

         if(BestSDDR >= 0)
         {
            TreeSubJet1PT = HSDJet.RecoSubJet1[BestSDJet].GetPT();
            TreeSubJet1Eta = HSDJet.RecoSubJet1[BestSDJet].GetEta();
            TreeSubJet1Phi = HSDJet.RecoSubJet1[BestSDJet].GetPhi();
            TreeSubJet2PT = HSDJet.RecoSubJet2[BestSDJet].GetPT();
            TreeSubJet2Eta = HSDJet.RecoSubJet2[BestSDJet].GetEta();
            TreeSubJet2Phi = HSDJet.RecoSubJet2[BestSDJet].GetPhi();

            TreeSubJetDR = HSDJet.RecoSubJetDR[BestSDJet];
            TreeSDMass = MJet.JetM[BestSDJet];

            TreePartonFlavor = MJet.RefPartonFlavor[BestSDJet];
            TreePartonFlavorForB = MJet.RefPartonFlavorForB[BestSDJet];

            TreeJetSDPT = MSDJet.JetPT[BestSDJet];
            TreeJetSDRawPT = MSDJet.JetRawPT[BestSDJet];
            TreeJetSDEta = MSDJet.JetEta[BestSDJet];
            TreeJetSDPhi = MSDJet.JetPhi[BestSDJet];
         }

         int BestJet = 0;
         double BestDR = -1;
         for(int i = 0; i < (int)Jets.size(); i++)
         {
            double DR = GetDR(MJet.JetEta[iJ], MJet.JetPhi[iJ], Jets[i].eta(), Jets[i].phi());
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

            if(TreeJetPT < 80 && TreeMatchPT < 80)   // no need to store them!
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










