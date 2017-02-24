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
#include "SDJetHelper.h"

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
   GenParticleTreeMessenger MGen(InputFile);

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
   
   double TreeJetGenPT, TreeJetGenEta, TreeJetGenPhi;
   OutputTree.Branch("JetGenPT", &TreeJetGenPT, "JetGenPT/D");
   OutputTree.Branch("JetGenEta", &TreeJetGenEta, "JetGenEta/D");
   OutputTree.Branch("JetGenPhi", &TreeJetGenPhi, "JetGenPhi/D");

   double TreeJetSubJetX1, TreeJetSubJetX2, TreeJetSubJetY1, TreeJetSubJetY2, TreeJetSubJetPT1, TreeJetSubJetPT2;
   OutputTree.Branch("JetSubJetX1", &TreeJetSubJetX1, "JetSubJetX1/D");
   OutputTree.Branch("JetSubJetY1", &TreeJetSubJetY1, "JetSubJetY1/D");
   OutputTree.Branch("JetSubJetX2", &TreeJetSubJetX2, "JetSubJetX2/D");
   OutputTree.Branch("JetSubJetY2", &TreeJetSubJetY2, "JetSubJetY2/D");
   OutputTree.Branch("JetSubJetPT1", &TreeJetSubJetPT1, "JetSubJetPT1/D");
   OutputTree.Branch("JetSubJetPT2", &TreeJetSubJetPT2, "JetSubJetPT2/D");

   double TreeJetSDMass, TreeJetSDZG, TreeJetSDRecoDR, TreeJetMaxDR;
   OutputTree.Branch("JetSDMass", &TreeJetSDMass, "JetSDMass/D");
   OutputTree.Branch("JetSDZG", &TreeJetSDZG, "JetSDZG/D");
   OutputTree.Branch("JetSDRecoDR", &TreeJetSDRecoDR, "JetSDRecoDR/D");
   OutputTree.Branch("JetMaxDR", &TreeJetMaxDR, "JetMaxDR/D");
   
   double TreeNewJetPT, TreeNewJetEta, TreeNewJetPhi;
   OutputTree.Branch("NewJetPT", &TreeNewJetPT, "NewJetPT/D");
   OutputTree.Branch("NewJetEta", &TreeNewJetEta, "NewJetEta/D");
   OutputTree.Branch("NewJetPhi", &TreeNewJetPhi, "NewJetPhi/D");

   double TreeSDPT[MAX], TreeSDMass[MAX], TreeSDZG[MAX], TreeSDRecoDR[MAX], TreeSDMaxDR[MAX];
   double TreeGenSDPT[MAX], TreeGenSDMass[MAX], TreeGenSDZG[MAX], TreeGenSDRecoDR[MAX];
   double TreeSDX1[MAX], TreeSDX2[MAX], TreeSDY1[MAX], TreeSDY2[MAX], TreeSDPT1[MAX], TreeSDPT2[MAX];
   double TreeGenSDPT1[MAX], TreeGenSDPT2[MAX];
   OutputTree.Branch("SDPT", &TreeSDPT, Form("SDPT[%d]/D", MAX));
   OutputTree.Branch("SDMass", &TreeSDMass, Form("SDMass[%d]/D", MAX));
   OutputTree.Branch("SDZG", &TreeSDZG, Form("SDZG[%d]/D", MAX));
   OutputTree.Branch("SDRecoDR", &TreeSDRecoDR, Form("SDRecoDR[%d]/D", MAX));
   OutputTree.Branch("SDMaxDR", &TreeSDMaxDR, Form("SDMaxDR[%d]/D", MAX));
   OutputTree.Branch("GenSDPT", &TreeGenSDPT, Form("GenSDPT[%d]/D", MAX));
   OutputTree.Branch("GenSDMass", &TreeGenSDMass, Form("GenSDMass[%d]/D", MAX));
   OutputTree.Branch("GenSDZG", &TreeGenSDZG, Form("GenSDZG[%d]/D", MAX));
   OutputTree.Branch("GenSDRecoDR", &TreeGenSDRecoDR, Form("GenSDRecoDR[%d]/D", MAX));
   OutputTree.Branch("SDX1", &TreeSDX1, Form("SDX1[%d]/D", MAX));
   OutputTree.Branch("SDY1", &TreeSDY1, Form("SDY1[%d]/D", MAX));
   OutputTree.Branch("SDPT1", &TreeSDPT1, Form("SDPT1[%d]/D", MAX));
   OutputTree.Branch("SDX2", &TreeSDX2, Form("SDX2[%d]/D", MAX));
   OutputTree.Branch("SDY2", &TreeSDY2, Form("SDY2[%d]/D", MAX));
   OutputTree.Branch("SDPT2", &TreeSDPT2, Form("SDPT2[%d]/D", MAX));
   OutputTree.Branch("GenSDPT1", &TreeGenSDPT1, Form("GenSDPT1[%d]/D", MAX));
   OutputTree.Branch("GenSDPT2", &TreeGenSDPT2, Form("GenSDPT2[%d]/D", MAX));

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
      MGen.GetEntry(iEntry);

      HPTHatAll.Fill(MJet.PTHat);
      if(MJet.PTHat <= PTHatMin || MJet.PTHat > PTHatMax)
         continue;
      
      SDJetHelper HSDJet(MSDJet);

      if(IsData == true && MSkim.PassBasicFilter() == false)
         continue;
      if(IsData == true && IsPP == false && MTrigger.CheckTrigger("HLT_HIPuAK4CaloJet80_Eta5p1_v1") != 1)
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
      
      vector<PseudoJet> GenParticles;
      for(int i = 0; i < (int)MGen.ID->size(); i++)
      {
         if(abs((*MGen.ID)[i]) == 12)
            continue;
         if(abs((*MGen.ID)[i]) == 14)
            continue;
         if(abs((*MGen.ID)[i]) == 16)
            continue;

         FourVector P;
         P.SetPtEtaPhi((*MGen.PT)[i], (*MGen.Eta)[i], (*MGen.Phi)[i]);
         GenParticles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition GenDefinition(antikt_algorithm, 0.4);
      ClusterSequence GenSequence(GenParticles, GenDefinition);
      vector<PseudoJet> GenJets = GenSequence.inclusive_jets();

      if(GenJets.size() == 0)   // WTF
         continue;

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

         int BestGenIndex = -1;
         BestDR2 = -1;
         for(int i = 0; i < (int)GenJets.size(); i++)
         {
            double DR2 = GetDR2(GenJets[i].eta(), GenJets[i].phi(), Jets[iJ].eta(), Jets[iJ].phi());
            if(BestDR2 < 0 || BestDR2 > DR2)
            {
               BestGenIndex = i;
               BestDR2 = DR2;
            }
         }

         if(BestIndex < 0)   // something is wrong
            continue;
         if(BestGenIndex < 0)   // something is wrong!
            continue;

         if(MJet.JetPT[BestIndex] < 50)   // too low - let's not consider them
            continue;
         if(MJet.JetEta[BestIndex] < -2 || MJet.JetEta[BestIndex] > 2)   // too forward!
            continue;

         TreeRho = GetRho(MRho.EtaMax, MRho.Rho, MJet.JetEta[BestIndex]);

         TreeJetPT = MJet.JetPT[BestIndex];
         TreeJetEta = MJet.JetEta[BestIndex];
         TreeJetPhi = MJet.JetPhi[BestIndex];
         TreeJetSDPT = MSDJet.JetPT[BestSDIndex];
         TreeJetSDEta = MSDJet.JetEta[BestSDIndex];
         TreeJetSDPhi = MSDJet.JetPhi[BestSDIndex];
         TreeJetGenPT = GenJets[BestGenIndex].perp();
         TreeJetGenEta = GenJets[BestGenIndex].eta();
         TreeJetGenPhi = GenJets[BestGenIndex].phi();
         TreeJetSubJetX1 = HSDJet.SubJetX1[BestSDIndex];
         TreeJetSubJetY1 = HSDJet.SubJetY1[BestSDIndex];
         TreeJetSubJetX2 = HSDJet.SubJetX2[BestSDIndex];
         TreeJetSubJetY2 = HSDJet.SubJetY2[BestSDIndex];
         TreeJetSubJetPT1 = HSDJet.RecoSubJet1[BestSDIndex].GetPT();
         TreeJetSubJetPT2 = HSDJet.RecoSubJet2[BestSDIndex].GetPT();
         TreeNewJetPT = Jets[iJ].perp();
         TreeNewJetEta = Jets[iJ].eta();
         TreeNewJetPhi = Jets[iJ].phi();

         TreeJetSDMass = MSDJet.JetM[BestSDIndex];
         TreeJetSDZG = -1;
         TreeJetSDRecoDR = -1;
         TreeJetMaxDR = HSDJet.SubJetMaxDR[BestSDIndex];

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
         
         PSCandidates = GenJets[BestGenIndex].constituents();
         vector<Node *> GenNodes;
         for(int i = 0; i < (int)PSCandidates.size(); i++)
         {
            FourVector P(PSCandidates[i].e(), PSCandidates[i].px(), PSCandidates[i].py(), PSCandidates[i].pz());
            GenNodes.push_back(new Node(P));
         }

         BuildCATree(Nodes);
         BuildCATree(GenNodes);

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

         Node *GenSD[MAX] = {NULL};
         GenSD[0] = FindSDNode(GenNodes[0], 0.1, 0.0);
         GenSD[1] = FindSDNode(GenNodes[0], 0.2, 0.0);
         GenSD[2] = FindSDNode(GenNodes[0], 0.3, 0.0);
         GenSD[3] = FindSDNode(GenNodes[0], 0.05, 0.0);
         GenSD[4] = FindSDNode(GenNodes[0], 0.1, 0.5);
         GenSD[5] = FindSDNode(GenNodes[0], 0.1, 1.0);
         GenSD[6] = FindSDNode(GenNodes[0], 0.1, 2.0);
         GenSD[7] = FindSDNode(GenNodes[0], 0.5, 1.5);
         GenSD[8] = FindSDNode(GenNodes[0], 0.3, 1.5);
         GenSD[9] = FindSDNode(GenNodes[0], 0.2, 1.5);

         for(int i = 0; i < MAX; i++)
         {
            if(SD[i] == NULL || GenSD[i] == NULL)
               continue;

            TreeSDPT[i] = SD[i]->P.GetPT();
            TreeSDMass[i] = SD[i]->P.GetMass();
            TreeSDZG[i] = -1;
            TreeSDRecoDR[i] = -1;
            TreeGenSDPT[i] = GenSD[i]->P.GetPT();
            TreeGenSDMass[i] = GenSD[i]->P.GetMass();
            TreeGenSDZG[i] = -1;
            TreeGenSDRecoDR[i] = -1;

            if(SD[i]->N > 1)
            {
               FourVector P1 = SD[i]->Child1->P;
               FourVector P2 = SD[i]->Child2->P;
        
               if(GenSD[i]->N > 1)
               {
                  double DR11 = GetDR(GenSD[i]->Child1->P, P1);
                  double DR12 = GetDR(GenSD[i]->Child1->P, P2);
                  double DR21 = GetDR(GenSD[i]->Child2->P, P1);
                  double DR22 = GetDR(GenSD[i]->Child2->P, P2);

                  if(DR11 + DR22 < DR12 + DR21)
                     TreeSDMaxDR[i] = std::max(DR11, DR22);
                  else
                     TreeSDMaxDR[i] = std::max(DR12, DR21);

                  double DeltaEta = GenSD[i]->Child1->P.GetEta() - GenSD[i]->Child2->P.GetEta();
                  double MeanEta = (GenSD[i]->Child1->P.GetEta() + GenSD[i]->Child2->P.GetEta()) / 2;
                  double DeltaPhi = (GenSD[i]->Child1->P.GetPhi() - GenSD[i]->Child2->P.GetPhi());
                  if(DeltaPhi < -PI)   DeltaPhi = DeltaPhi + 2 * PI;
                  if(DeltaPhi > +PI)   DeltaPhi = DeltaPhi - 2 * PI;
                  double MeanPhi = GenSD[i]->Child2->P.GetPhi() + DeltaPhi / 2;
                  if(MeanPhi < -PI)   MeanPhi = MeanPhi + 2 * PI;
                  if(MeanPhi > +PI)   MeanPhi = MeanPhi - 2 * PI;

                  double M11 = DeltaEta / 2;
                  double M12 = DeltaPhi / 2;
                  double M21 = -DeltaPhi / 2;
                  double M22 = DeltaEta / 2;

                  double DetM = M11 * M22 - M12 * M21;

                  double IM11 = M22 / DetM;
                  double IM12 = -M21 / DetM;
                  double IM21 = -M12 / DetM;
                  double IM22 = M11 / DetM;
                  
                  double SubJetEta1 = SD[i]->Child1->P.GetEta() - MeanEta;
                  double SubJetPhi1 = SD[i]->Child1->P.GetPhi() - MeanPhi;
                  double SubJetEta2 = SD[i]->Child2->P.GetEta() - MeanEta;
                  double SubJetPhi2 = SD[i]->Child2->P.GetPhi() - MeanPhi;
                  if(SubJetPhi1 > +PI)   SubJetPhi1 = SubJetPhi1 - 2 * PI;
                  if(SubJetPhi1 < -PI)   SubJetPhi1 = SubJetPhi1 + 2 * PI;
                  if(SubJetPhi2 > +PI)   SubJetPhi2 = SubJetPhi2 - 2 * PI;
                  if(SubJetPhi2 < -PI)   SubJetPhi2 = SubJetPhi2 + 2 * PI;

                  TreeSDX1[i] = IM11 * SubJetEta1 + IM12 * SubJetPhi1;
                  TreeSDY1[i] = IM21 * SubJetEta1 + IM22 * SubJetPhi1;
                  TreeSDX2[i] = IM11 * SubJetEta2 + IM12 * SubJetPhi2;
                  TreeSDY2[i] = IM21 * SubJetEta2 + IM22 * SubJetPhi2;
               }

               TreeSDPT1[i] = SD[i]->Child1->P.GetPT();
               TreeSDPT2[i] = SD[i]->Child2->P.GetPT();

               TreeSDZG[i] = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
               TreeSDRecoDR[i] = GetDR(P1, P2);
            }
        
            if(GenSD[i]->N > 1)
            {
               FourVector P1 = GenSD[i]->Child1->P;
               FourVector P2 = GenSD[i]->Child2->P;
        
               TreeGenSDPT1[i] = P1.GetPT();
               TreeGenSDPT2[i] = P2.GetPT();

               TreeGenSDZG[i] = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
               TreeGenSDRecoDR[i] = GetDR(P1, P2);
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





