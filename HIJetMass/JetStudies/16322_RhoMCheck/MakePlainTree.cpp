#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"
#include "fastjet/contrib/SoftDrop.hh"
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

   TFile InputFile(InputFileName.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   string PFTreeName = "pfcandAnalyzer/pfTree";
   string CSPFTreeName = "pfcandAnalyzerCS/pfTree";

   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
      PFTreeName = "pfcandAnalyzer/pfTree";
      CSPFTreeName = "pfcandAnalyzer/pfTree";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);
   PFTreeMessenger MPF(InputFile, PFTreeName);
   PFTreeMessenger MCSPF(InputFile, CSPFTreeName);
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

   double TreeCentrality, TreePTHat, TreeRho, TreeRhoM;
   OutputTree.Branch("Centrality", &TreeCentrality, "Centrality/D");
   OutputTree.Branch("PTHat", &TreePTHat, "PTHat/D");
   OutputTree.Branch("Rho", &TreeRho, "Rho/D");
   OutputTree.Branch("RhoM", &TreeRhoM, "RhoM/D");

   bool TreePassPbPb40, TreePassPbPb60, TreePassPbPb80, TreePassPbPb100;
   OutputTree.Branch("PassPbPb40", &TreePassPbPb40, "PassPbPb40/O");
   OutputTree.Branch("PassPbPb60", &TreePassPbPb60, "PassPbPb60/O");
   OutputTree.Branch("PassPbPb80", &TreePassPbPb80, "PassPbPb80/O");
   OutputTree.Branch("PassPbPb100", &TreePassPbPb100, "PassPbPb100/O");

   int TreeJetIndex;
   OutputTree.Branch("JetIndex", &TreeJetIndex, "JetIndex/I");

   double TreeJetPT, TreeJetEta, TreeJetPhi, TreeJetMPT, TreeJetMEta, TreeJetMPhi;
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi/D");
   OutputTree.Branch("JetMPT", &TreeJetMPT, "JetMPT/D");
   OutputTree.Branch("JetMEta", &TreeJetMEta, "JetMEta/D");
   OutputTree.Branch("JetMPhi", &TreeJetMPhi, "JetMPhi/D");

   int TreeDepth0, TreeDepth7, TreeDepth0M, TreeDepth7M;
   OutputTree.Branch("Depth0", &TreeDepth0, "Depth0/I");
   OutputTree.Branch("Depth7", &TreeDepth7, "Depth7/I");
   OutputTree.Branch("Depth0M", &TreeDepth0M, "Depth0M/I");
   OutputTree.Branch("Depth7M", &TreeDepth7M, "Depth7M/I");

   double TreeSubJetDR0, TreeSDMass0;
   double TreeSubJetDR7, TreeSDMass7;
   double TreeSubJetDR0M, TreeSDMass0M;
   double TreeSubJetDR7M, TreeSDMass7M;
   OutputTree.Branch("SubJetDR0", &TreeSubJetDR0, "SubJetDR0/D");
   OutputTree.Branch("SDMass0", &TreeSDMass0, "SDMass0/D");
   OutputTree.Branch("SubJetDR7", &TreeSubJetDR7, "SubJetDR7/D");
   OutputTree.Branch("SDMass7", &TreeSDMass7, "SDMass7/D");
   OutputTree.Branch("SubJetDR0M", &TreeSubJetDR0M, "SubJetDR0M/D");
   OutputTree.Branch("SDMass0M", &TreeSDMass0M, "SDMass0M/D");
   OutputTree.Branch("SubJetDR7M", &TreeSubJetDR7M, "SubJetDR7M/D");
   OutputTree.Branch("SDMass7M", &TreeSDMass7M, "SDMass7M/D");
   
   double TreeSubJet1PT0, TreeSubJet1Eta0, TreeSubJet1Phi0;
   double TreeSubJet2PT0, TreeSubJet2Eta0, TreeSubJet2Phi0;
   double TreeSubJet1PT0M, TreeSubJet1Eta0M, TreeSubJet1Phi0M;
   double TreeSubJet2PT0M, TreeSubJet2Eta0M, TreeSubJet2Phi0M;
   OutputTree.Branch("SubJet1PT0", &TreeSubJet1PT0, "SubJet1PT0/D");
   OutputTree.Branch("SubJet1Eta0", &TreeSubJet1Eta0, "SubJet1Eta0/D");
   OutputTree.Branch("SubJet1Phi0", &TreeSubJet1Phi0, "SubJet1Phi0/D");
   OutputTree.Branch("SubJet2PT0", &TreeSubJet2PT0, "SubJet2PT0/D");
   OutputTree.Branch("SubJet2Eta0", &TreeSubJet2Eta0, "SubJet2Eta0/D");
   OutputTree.Branch("SubJet2Phi0", &TreeSubJet2Phi0, "SubJet2Phi0/D");
   OutputTree.Branch("SubJet1PT0M", &TreeSubJet1PT0M, "SubJet1PT0M/D");
   OutputTree.Branch("SubJet1Eta0M", &TreeSubJet1Eta0M, "SubJet1Eta0M/D");
   OutputTree.Branch("SubJet1Phi0M", &TreeSubJet1Phi0M, "SubJet1Phi0M/D");
   OutputTree.Branch("SubJet2PT0M", &TreeSubJet2PT0M, "SubJet2PT0M/D");
   OutputTree.Branch("SubJet2Eta0M", &TreeSubJet2Eta0M, "SubJet2Eta0M/D");
   OutputTree.Branch("SubJet2Phi0M", &TreeSubJet2Phi0M, "SubJet2Phi0M/D");
   
   double TreeSubJet1PT7, TreeSubJet1Eta7, TreeSubJet1Phi7;
   double TreeSubJet2PT7, TreeSubJet2Eta7, TreeSubJet2Phi7;
   double TreeSubJet1PT7M, TreeSubJet1Eta7M, TreeSubJet1Phi7M;
   double TreeSubJet2PT7M, TreeSubJet2Eta7M, TreeSubJet2Phi7M;
   OutputTree.Branch("SubJet1PT7", &TreeSubJet1PT7, "SubJet1PT7/D");
   OutputTree.Branch("SubJet1Eta7", &TreeSubJet1Eta7, "SubJet1Eta7/D");
   OutputTree.Branch("SubJet1Phi7", &TreeSubJet1Phi7, "SubJet1Phi7/D");
   OutputTree.Branch("SubJet2PT7", &TreeSubJet2PT7, "SubJet2PT7/D");
   OutputTree.Branch("SubJet2Eta7", &TreeSubJet2Eta7, "SubJet2Eta7/D");
   OutputTree.Branch("SubJet2Phi7", &TreeSubJet2Phi7, "SubJet2Phi7/D");
   OutputTree.Branch("SubJet1PT7M", &TreeSubJet1PT7M, "SubJet1PT7M/D");
   OutputTree.Branch("SubJet1Eta7M", &TreeSubJet1Eta7M, "SubJet1Eta7M/D");
   OutputTree.Branch("SubJet1Phi7M", &TreeSubJet1Phi7M, "SubJet1Phi7M/D");
   OutputTree.Branch("SubJet2PT7M", &TreeSubJet2PT7M, "SubJet2PT7M/D");
   OutputTree.Branch("SubJet2Eta7M", &TreeSubJet2Eta7M, "SubJet2Eta7M/D");
   OutputTree.Branch("SubJet2Phi7M", &TreeSubJet2Phi7M, "SubJet2Phi7M/D");

   int EntryCount = MHiEvent.Tree->GetEntries() * 0.2;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 200 || (iE % (EntryCount / 300)) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MSDJet.GetEntry(iE);
      MPF.GetEntry(iE);
      MCSPF.GetEntry(iE);
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

      TreeCentrality = GetCentrality(MHiEvent.hiBin);
      TreePTHat = MSDJet.PTHat;
      TreeRho = GetRho(MRho.EtaMax, MRho.Rho, 0);
      TreeRhoM = GetRho(MRho.EtaMax, MRho.RhoM, 0);

      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;

      vector<PseudoJet> Particles, ParticlesM;
      for(int iPF = 0; iPF < MPF.ID->size(); iPF++)
      {
         FourVector P;
         P.SetPtEtaPhi((*MPF.PT)[iPF], (*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
         Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
         P[0] = (*MPF.E)[iPF];
         ParticlesM.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      JetDefinition DefinitionM(antikt_algorithm, 0.4);
      AreaDefinition AreaDef(active_area_explicit_ghosts, GhostedAreaSpec(6.0, 1, 0.005));
      AreaDefinition AreaDefM(active_area_explicit_ghosts, GhostedAreaSpec(6.0, 1, 0.005));
      ClusterSequenceArea Sequence(Particles, Definition, AreaDef);
      ClusterSequenceArea SequenceM(ParticlesM, DefinitionM, AreaDefM);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(30);
      vector<PseudoJet> JetsM = SequenceM.inclusive_jets(30);

      vector<PseudoJet> CSJets(Jets.size()), CSJetsM(JetsM.size());
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         contrib::ConstituentSubtractor Subtractor(TreeRho, 0, 0, -1);
         Subtractor.set_alpha(1);
         CSJets[i] = Subtractor(Jets[i]);
      }
      for(int i = 0; i < (int)JetsM.size(); i++)
      {
         contrib::ConstituentSubtractor Subtractor(TreeRho, TreeRhoM, 0, -1);
         Subtractor.set_alpha(1);
         CSJetsM[i] = Subtractor(JetsM[i]);
      }

      TreeJetIndex = 0;

      vector<double> CSEta(CSJets.size());
      vector<double> CSPhi(CSJets.size());
      vector<double> CSMEta(CSJetsM.size());
      vector<double> CSMPhi(CSJetsM.size());
      for(int i = 0; i < (int)CSJets.size(); i++)
      {
         CSEta[i] = CSJets[i].eta();
         CSPhi[i] = CSJets[i].phi();
      }
      for(int i = 0; i < (int)CSJetsM.size(); i++)
      {
         CSMEta[i] = CSJetsM[i].eta();
         CSMPhi[i] = CSJetsM[i].phi();
      }

      for(int iJ = 0; iJ < (int)CSJets.size(); iJ++)
      {
         if(fabs(CSJets[iJ].eta()) > 1.5)
            continue;
         if(CSJets[iJ].perp() < 80)
            continue;

         int BestIndex = 0;
         double BestDR2 = -1;
         for(int iJM = 0; iJM < (int)CSJetsM.size(); iJM++)
         {
            double DR2 = GetDR2(CSEta[iJ], CSPhi[iJ], CSMEta[iJM], CSMPhi[iJM]);
            if(BestDR2 < 0 || DR2 < BestDR2)
            {
               BestIndex = iJM;
               BestDR2 = DR2;
            }
         }

         if(fabs(CSJetsM[BestIndex].eta()) > 1.5)
            continue;
         if(CSJetsM[BestIndex].perp() < 80)
            continue;

         TreeJetPT   = CSJets[iJ].perp();
         TreeJetEta  = CSJets[iJ].eta();
         TreeJetPhi  = CSJets[iJ].phi();
         TreeJetMPT  = CSJetsM[BestIndex].perp();
         TreeJetMEta = CSJetsM[BestIndex].eta();
         TreeJetMPhi = CSJetsM[BestIndex].phi();
            
         vector<PseudoJet> Constituents;
         vector<Node *> Nodes, NodesM;

         Constituents = CSJets[iJ].constituents();
         for(int i = 0; i < (int)Constituents.size(); i++)
         {
            FourVector P;
            P[0] = Constituents[i].e();
            P[1] = Constituents[i].px();
            P[2] = Constituents[i].py();
            P[3] = Constituents[i].pz();
            Nodes.push_back(new Node(P));
         }
         Constituents = CSJetsM[BestIndex].constituents();
         for(int i = 0; i < (int)Constituents.size(); i++)
         {
            FourVector P;
            P[0] = Constituents[i].e();
            P[1] = Constituents[i].px();
            P[2] = Constituents[i].py();
            P[3] = Constituents[i].pz();

            P[0] = P.GetP();

            NodesM.push_back(new Node(P));
         }

         BuildCATree(Nodes);
         BuildCATree(NodesM);
            
         Node *Groomed0 = FindSDNode(Nodes[0], 0.1, 0.0, 0.4);
         Node *Groomed7 = FindSDNode(Nodes[0], 0.5, 1.5, 0.4);
         Node *Groomed0M = FindSDNode(NodesM[0], 0.1, 0.0, 0.4);
         Node *Groomed7M = FindSDNode(NodesM[0], 0.5, 1.5, 0.4);

         TreeDepth0 = NodeDistance(Groomed0, Nodes[0]);
         TreeDepth7 = NodeDistance(Groomed7, Nodes[0]);
         TreeDepth0M = NodeDistance(Groomed0M, NodesM[0]);
         TreeDepth7M = NodeDistance(Groomed7M, NodesM[0]);
         
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
         {
            TreeSubJetDR0 = -1;
            TreeSDMass0 = -1;
         }

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
         {
            TreeSubJetDR7 = -1;
            TreeSDMass7 = -1;
         }

         if(Groomed0M->N > 1)
         {
            TreeSubJetDR0M = GetDR(Groomed0M->Child1->P, Groomed0M->Child2->P);
            TreeSDMass0M = Groomed0M->P.GetMass();
               
            TreeSubJet1PT0M = Groomed0M->Child1->P.GetPT();
            TreeSubJet1Eta0M = Groomed0M->Child1->P.GetEta();
            TreeSubJet1Phi0M = Groomed0M->Child1->P.GetPhi();
            TreeSubJet2PT0M = Groomed0M->Child2->P.GetPT();
            TreeSubJet2Eta0M = Groomed0M->Child2->P.GetEta();
            TreeSubJet2Phi0M = Groomed0M->Child2->P.GetPhi();
         }
         else
         {
            TreeSubJetDR0M = -1;
            TreeSDMass0M = -1;
         }

         if(Groomed7M->N > 1)
         {
            TreeSubJetDR7M = GetDR(Groomed7M->Child1->P, Groomed7M->Child2->P);
            TreeSDMass7M = Groomed7M->P.GetMass();
               
            TreeSubJet1PT7M = Groomed7M->Child1->P.GetPT();
            TreeSubJet1Eta7M = Groomed7M->Child1->P.GetEta();
            TreeSubJet1Phi7M = Groomed7M->Child1->P.GetPhi();
            TreeSubJet2PT7M = Groomed7M->Child2->P.GetPT();
            TreeSubJet2Eta7M = Groomed7M->Child2->P.GetEta();
            TreeSubJet2Phi7M = Groomed7M->Child2->P.GetPhi();
         }
         else
         {
            TreeSubJetDR7M = -1;
            TreeSDMass7M = -1;
         }

         TreeJetIndex = TreeJetIndex + 1;
         OutputTree.Fill();

         delete Nodes[0];
         delete NodesM[0];
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










