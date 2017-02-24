#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"
#include "ProgressBar.h"

#include "BasicUtilities.h"
#include "Messenger.h"
#include "CATree.h"

#define MAX 10

int main(int argc, char *argv[]);
double CalculateDR(double eta1, double phi1, double eta2, double phi2);

int main(int argc, char *argv[])
{
   if(argc < 6)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag PTHatMin PTHatMax" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];
   double PTHatMin = atof(argv[4]);
   double PTHatMax = atof(argv[5]);

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);

   TFile InputFile(Input.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   string PFTreeName = "pfcandAnalyzerCS/pfTree";
   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
      PFTreeName = "pfcandAnalyzer/pfTree";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);
   SkimTreeMessenger MSkim(InputFile);
   TriggerTreeMessenger MTrigger(InputFile);
   PFTreeMessenger MPF(InputFile, PFTreeName);
   RhoTreeMessenger MRho(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TH1D HN("HN", "Raw event count", 1, 0, 1);
   TH1D HPTHatAll("HPTHatAll", "PTHat", 100, 0, 500);
   TH1D HPTHatSelected("HPTHatSelected", "PTHat", 100, 0, 500);

   TTree OutputTree("Tree", "Tree");

   double TreeJetPT, TreeJetEta, TreeJetPhi;
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi/D");
   
   double TreeJetSDPT, TreeJetSDEta, TreeJetSDPhi;
   OutputTree.Branch("JetSDPT", &TreeJetSDPT, "JetSDPT/D");
   OutputTree.Branch("JetSDEta", &TreeJetSDEta, "JetSDEta/D");
   OutputTree.Branch("JetSDPhi", &TreeJetSDPhi, "JetSDPhi/D");

   int TreeRefPartonFlavor, TreeRefPartonFlavorForB;
   OutputTree.Branch("RefPartonFlavor", &TreeRefPartonFlavor, "RefPartonFlavor/I");
   OutputTree.Branch("RefPartonFlavorForB", &TreeRefPartonFlavorForB, "RefPartonFlavorForB/I");

   double TreeJetTau1, TreeJetTau2, TreeJetTau3;
   OutputTree.Branch("JetTau1", &TreeJetTau1, "JetTau1/D");
   OutputTree.Branch("JetTau2", &TreeJetTau2, "JetTau2/D");
   OutputTree.Branch("JetTau3", &TreeJetTau3, "JetTau3/D");

   double TreeJetCHF, TreeJetNHF, TreeJetCEF, TreeJetNEF, TreeJetMUF;
   OutputTree.Branch("JetCHF", &TreeJetCHF, "JetCHF/D");
   OutputTree.Branch("JetNHF", &TreeJetNHF, "JetNHF/D");
   OutputTree.Branch("JetCEF", &TreeJetCEF, "JetCEF/D");
   OutputTree.Branch("JetNEF", &TreeJetNEF, "JetNEF/D");
   OutputTree.Branch("JetMUF", &TreeJetMUF, "JetMUF/D");
   
   int TreeJetCHM, TreeJetNHM, TreeJetCEM, TreeJetNEM, TreeJetMUM;
   OutputTree.Branch("JetCHM", &TreeJetCHM, "JetCHM/I");
   OutputTree.Branch("JetNHM", &TreeJetNHM, "JetNHM/I");
   OutputTree.Branch("JetCEM", &TreeJetCEM, "JetCEM/I");
   OutputTree.Branch("JetNEM", &TreeJetNEM, "JetNEM/I");
   OutputTree.Branch("JetMUM", &TreeJetMUM, "JetMUM/I");

   double TreeJetSDMass, TreeJetSDZG, TreeJetSDRecoDR;
   OutputTree.Branch("JetSDMass", &TreeJetSDMass, "JetSDMass/D");
   OutputTree.Branch("JetSDZG", &TreeJetSDZG, "JetSDZG/D");
   OutputTree.Branch("JetSDRecoDR", &TreeJetSDRecoDR, "JetSDRecoDR/D");
   
   double TreeNewJetPT, TreeNewJetEta, TreeNewJetPhi;
   OutputTree.Branch("NewJetPT", &TreeNewJetPT, "NewJetPT/D");
   OutputTree.Branch("NewJetEta", &TreeNewJetEta, "NewJetEta/D");
   OutputTree.Branch("NewJetPhi", &TreeNewJetPhi, "NewJetPhi/D");

   double TreeSDPT[MAX], TreeSDMass[MAX], TreeSDZG[MAX], TreeSDRecoDR[MAX];
   OutputTree.Branch("SDPT", &TreeSDPT, Form("SDPT[%d]/D", MAX));
   OutputTree.Branch("SDMass", &TreeSDMass, Form("SDMass[%d]/D", MAX));
   OutputTree.Branch("SDZG", &TreeSDZG, Form("SDZG[%d]/D", MAX));
   OutputTree.Branch("SDRecoDR", &TreeSDRecoDR, Form("SDRecoDR[%d]/D", MAX));

   double TreeRho, TreeCentrality;
   OutputTree.Branch("Rho", &TreeRho, "Rho/D");
   OutputTree.Branch("Centrality", &TreeCentrality, "Centrality/D");

   int EntryCount = MHiEvent.Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(0);
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if(EntryCount < 300 || iEntry % (EntryCount / 300) == 0)
      {
         Bar.Update(iEntry);
         Bar.Print();
      }

      HN.Fill(0);

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);
      MSkim.GetEntry(iEntry);
      MTrigger.GetEntry(iEntry);
      MPF.GetEntry(iEntry);
      MRho.GetEntry(iEntry);

      HPTHatAll.Fill(MJet.PTHat);
      if(MJet.PTHat <= PTHatMin || MJet.PTHat > PTHatMax)
         continue;

      if(IsData == true && MSkim.PassBasicFilter() == false)
         continue;
      if(IsData == true && IsPP == false && MTrigger.CheckTrigger("HLT_HIPuAK4CaloJet100_Eta5p1_v1") != 1)
         continue;
      if(IsData == true && IsPP == true && MTrigger.CheckTrigger("HLT_AK4PFJet80_Eta5p1_v1") != 1)
         continue;

      HPTHatSelected.Fill(MJet.PTHat);
      
      TreeCentrality = GetCentrality(MHiEvent.hiBin);

      vector<PseudoJet> Particles;
      for(int i = 0; i < (int)MPF.ID->size(); i++)
      {
         FourVector P;
         P.SetPtEtaPhi((*MPF.PT)[i], (*MPF.Eta)[i], (*MPF.Phi)[i]);
         Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets();

      for(int iJ = 0; iJ < (int)Jets.size(); iJ++)
      {
         if(Jets[iJ].perp() < 10)
            continue;

         int BestIndex = -1;
         double BestDR2 = -1;
         for(int i = 0; i < MJet.JetCount; i++)
         {
            double DR2 = GetDR2(MJet.JetEta[i], MJet.JetPhi[i], Jets[iJ].eta(), Jets[iJ].phi());
            if(BestDR2 < 0 || BestDR2 > DR2)
            {
               BestIndex = i;
               BestDR2 = DR2;
            }
         }

         int BestSDIndex = -1;
         BestDR2 = -1;
         for(int i = 0; i < MSDJet.JetCount; i++)
         {
            double DR2 = GetDR2(MSDJet.JetEta[i], MSDJet.JetPhi[i], Jets[iJ].eta(), Jets[iJ].phi());
            if(BestDR2 < 0 || BestDR2 > DR2)
            {
               BestSDIndex = i;
               BestDR2 = DR2;
            }
         }

         if(BestIndex < 0)   // something is wrong
            continue;

         if(MJet.JetPT[BestIndex] < 50)   // too low - let's not consider them
            continue;

         TreeRho = GetRho(MRho.EtaMax, MRho.Rho, MJet.JetEta[BestIndex]);

         TreeJetPT = MJet.JetPT[BestIndex];
         TreeJetEta = MJet.JetEta[BestIndex];
         TreeJetPhi = MJet.JetPhi[BestIndex];
         TreeJetSDPT = MSDJet.JetPT[BestSDIndex];
         TreeJetSDEta = MSDJet.JetEta[BestSDIndex];
         TreeJetSDPhi = MSDJet.JetPhi[BestSDIndex];
         TreeNewJetPT = Jets[iJ].perp();
         TreeNewJetEta = Jets[iJ].eta();
         TreeNewJetPhi = Jets[iJ].phi();

         TreeRefPartonFlavor = MJet.RefPartonFlavor[BestIndex];
         TreeRefPartonFlavorForB = MJet.RefPartonFlavorForB[BestIndex];
         TreeJetTau1 = MJet.JetTau1[BestIndex];
         TreeJetTau2 = MJet.JetTau2[BestIndex];
         TreeJetTau3 = MJet.JetTau3[BestIndex];

         TreeJetCHF = MJet.JetPFCHF[BestIndex];
         TreeJetNHF = MJet.JetPFNHF[BestIndex];
         TreeJetCEF = MJet.JetPFCEF[BestIndex];
         TreeJetNEF = MJet.JetPFNEF[BestIndex];
         TreeJetMUF = MJet.JetPFMUF[BestIndex];
         TreeJetCHM = MJet.JetPFCHM[BestIndex];
         TreeJetNHM = MJet.JetPFNHM[BestIndex];
         TreeJetCEM = MJet.JetPFCEM[BestIndex];
         TreeJetNEM = MJet.JetPFNEM[BestIndex];
         TreeJetMUM = MJet.JetPFMUM[BestIndex];

         TreeJetSDMass = MSDJet.JetM[BestSDIndex];
         TreeJetSDZG = -1;
         TreeJetSDRecoDR = -1;

         if((*MSDJet.JetSubJetPT)[BestSDIndex].size() >= 2)
         {
            FourVector P1, P2;
            P1.SetPtEtaPhi((*MSDJet.JetSubJetPT)[BestSDIndex][0], (*MSDJet.JetSubJetEta)[BestSDIndex][0], (*MSDJet.JetSubJetPhi)[BestSDIndex][0]);
            P2.SetPtEtaPhi((*MSDJet.JetSubJetPT)[BestSDIndex][1], (*MSDJet.JetSubJetEta)[BestSDIndex][1], (*MSDJet.JetSubJetPhi)[BestSDIndex][1]);

            TreeJetSDZG = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
            TreeJetSDRecoDR = GetDR(P1, P2);
         }

         vector<PseudoJet> PSCandidates = Jets[iJ].constituents();
         vector<Node *> Nodes;
         for(int i = 0; i < (int)PSCandidates.size(); i++)
         {
            FourVector P(PSCandidates[i].e(), PSCandidates[i].px(), PSCandidates[i].py(), PSCandidates[i].pz());
            Nodes.push_back(new Node(P));
         }

         BuildCATree(Nodes);

         Node *SD[MAX] = {NULL};
         SD[0] = FindSDNode(Nodes[0], 0.1, 0.0);
         SD[1] = FindSDNode(Nodes[0], 0.2, 0.0);
         SD[2] = FindSDNode(Nodes[0], 0.3, 0.0);
         SD[3] = FindSDNode(Nodes[0], 0.05, 0.0);
         SD[4] = FindSDNode(Nodes[0], 0.1, 0.5);
         SD[5] = FindSDNode(Nodes[0], 0.1, 1.0);
         SD[6] = FindSDNode(Nodes[0], 0.1, 2.0);
         SD[7] = FindSDNode(Nodes[0], 0.5, 1.5);
         SD[8] = FindSDNode(Nodes[0], 0.3, 1.5);
         SD[9] = FindSDNode(Nodes[0], 0.2, 1.5);

         for(int i = 0; i < MAX; i++)
         {
            if(SD[i] == NULL)
               continue;

            TreeSDPT[i] = SD[i]->P.GetPT();
            TreeSDMass[i] = SD[i]->P.GetMass();
            TreeSDZG[i] = -1;
            TreeSDRecoDR[i] = -1;

            if(SD[i]->N > 1)
            {
               FourVector P1 = SD[i]->Child1->P;
               FourVector P2 = SD[i]->Child2->P;

               TreeSDZG[i] = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
               TreeSDRecoDR[i] = GetDR(P1, P2);
            }
         }

         OutputTree.Fill();

         if(Nodes[0] != NULL)
            delete Nodes[0];
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

   InputFile.Close();
}

double CalculateDR(double eta1, double phi1, double eta2, double phi2)
{
   double DEta = eta1 - eta2;
   double DPhi = phi1 - phi2;
   if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
   if(DPhi > +PI)   DPhi = DPhi - 2 * PI;
   return sqrt(DEta * DEta + DPhi * DPhi);
}





