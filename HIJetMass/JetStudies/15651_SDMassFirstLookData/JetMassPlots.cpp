#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"
#include "ProgressBar.h"

#include "BasicUtilities.h"
#include "Messenger.h"
#include "CATree.h"

int main(int argc, char *argv[]);
double CalculateDR(double eta1, double phi1, double eta2, double phi2);

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);
   bool IsPA = IsPAFromTag(Tag);

   TFile InputFile(Input.c_str());

   string JetTreeName = "ak4PFJetAnalyzer/t";

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, "ak4PFJetAnalyzer/t");
   SkimTreeMessenger MSkim(InputFile);
   TriggerTreeMessenger MTrigger(InputFile);
   PFTreeMessenger MPF(InputFile, "pfcandAnalyzer/pfTree");
   RhoTreeMessenger MRho(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TTree OutputTree("Tree", "Tree");

   double TreeRun, TreeLumi, TreeEvent, TreeRho, TreeHFPlus, TreeHFMinus;
   OutputTree.Branch("Run", &TreeRun, "Run/D");
   OutputTree.Branch("Lumi", &TreeLumi, "Lumi/D");
   OutputTree.Branch("Event", &TreeEvent, "Event/D");
   OutputTree.Branch("Rho", &TreeRho, "Rho/D");
   OutputTree.Branch("HFPlus", &TreeHFPlus, "HFPlus/D");
   OutputTree.Branch("HFMinus", &TreeHFMinus, "HFMinus/D");

   double TreeJetPT, TreeJetConePT, TreeJetEta, TreeJetPhi, TreeJetMass;
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT/D");
   OutputTree.Branch("JetConePT", &TreeJetConePT, "JetConePT/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi/D");
   OutputTree.Branch("JetMass", &TreeJetMass, "JetMass/D");

   double TreeJetRecoDR, TreeJetSDMass, TreeJetZG, TreeJetSDPT;
   OutputTree.Branch("JetRecoDR", &TreeJetRecoDR, "JetRecoDR/D");
   OutputTree.Branch("JetSDMass", &TreeJetSDMass, "JetSDMass/D");
   OutputTree.Branch("JetSDPT", &TreeJetSDPT, "JetSDPT/D");
   OutputTree.Branch("JetZG", &TreeJetZG, "JetZG/D");
   
   double TreeJetRecoDR2, TreeJetSDMass2, TreeJetZG2, TreeJetSDPT2;
   OutputTree.Branch("JetRecoDR2", &TreeJetRecoDR2, "JetRecoDR2/D");
   OutputTree.Branch("JetSDMass2", &TreeJetSDMass2, "JetSDMass2/D");
   OutputTree.Branch("JetSDPT2", &TreeJetSDPT2, "JetSDPT2/D");
   OutputTree.Branch("JetZG2", &TreeJetZG2, "JetZG2/D");
   
   double TreeJetSubJet1, TreeSubJet2PT;

   string PTBin[9] = {"PTBinA", "PTBinB", "PTBin0", "PTBin1", "PTBin2", "PTBin3", "PTBin4", "PTBin5", "PTBin6"};
   double PTBinMin[9+1] = {40, 60, 80, 100, 120, 140, 160, 200, 300, 500};

   TH1D HN("HN", "Raw event count", 1, 0, 1);

   TH1D HRecoJetPT("HRecoJetPT", ";Jet PT", 100, 0, 500);
   TH1D *HSDMass[9] = {NULL};

   for(int j = 0; j < 9; j++)
   {
      HSDMass[j] = new TH1D(Form("HSDMass_%s", PTBin[j].c_str()),
         Form("Jet PT %.0f-%.0f;SD Mass", PTBinMin[j], PTBinMin[j+1]),
            200, 0, 100);

      HSDMass[j]->Sumw2();
   }

   int EntryCount = MHiEvent.Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(0);
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if(EntryCount < 500 || (iEntry % (EntryCount / 300)) == 0)
      {
         Bar.Update(iEntry);
         Bar.Print();
      }

      HN.Fill(0);

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSkim.GetEntry(iEntry);
      MTrigger.GetEntry(iEntry);
      MPF.GetEntry(iEntry);
      MRho.GetEntry(iEntry);

      TreeRun = MHiEvent.Run;
      TreeLumi = MHiEvent.Lumi;
      TreeEvent = MHiEvent.Event;
      TreeRho = GetRho(MRho.EtaMax, MRho.Rho, 0);
      TreeHFPlus = MHiEvent.hiHFplusEta4;
      TreeHFMinus = MHiEvent.hiHFminusEta4;

      if(IsData == true && MSkim.PassBasicFilter() == false)
         continue;
      if(IsData == true && IsPP == false && IsPA == false && MTrigger.CheckTrigger("HLT_HIPuAK4CaloJet80_Eta5p1_v1") != 1)
         continue;
      if(IsData == true && IsPA == true)
      {
         if(MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta5p1_v2") != 1
            && MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta5p1_v3") != 1
            && MTrigger.CheckTrigger("HLT_PAAK4PFJet80_Eta5p1_v4") != 1)
         continue;
      }
      if(IsData == true && IsPP == true && MTrigger.CheckTrigger("HLT_AK4PFJet80_Eta5p1_v1") != 1)
         continue;

      double Centrality = GetCentrality(MHiEvent.hiBin);

      for(int iJ = 0; iJ < MJet.JetCount; iJ++)
      {
         TreeJetPT = MJet.JetPT[iJ];
         TreeJetEta = MJet.JetEta[iJ];
         TreeJetPhi = MJet.JetPhi[iJ];
         TreeJetMass = MJet.JetM[iJ];

         if(MJet.JetPT[iJ] < 40)
            continue;
         if(MJet.JetEta[iJ] < -1.3 || MJet.JetEta[iJ] > 1.3)
            continue;

         vector<FourVector> Candidates;
         FourVector TotalP;
         for(int j = 0; j < MPF.ID->size(); j++)
         {
            if(GetDR2(MJet.JetEta[iJ], MJet.JetPhi[iJ], (*MPF.Eta)[j], (*MPF.Phi)[j]) > 0.4 * 0.4)
               continue;

            FourVector P;
            P.SetPtEtaPhi((*MPF.PT)[j], (*MPF.Eta)[j], (*MPF.Phi)[j]);
            Candidates.push_back(P);

            TotalP = TotalP + P;
         }

         TreeJetConePT = TotalP.GetPT();

         vector<Node *> Nodes;
         for(int j = 0; j < (int)Candidates.size(); j++)
            Nodes.push_back(new Node(Candidates[j]));

         BuildCATree(Nodes);
         Node *Groomed = FindSDNode(Nodes[0]);
         Node *Groomed2 = FindSDNode(Nodes[0], 0.5, 1.5);

         if(Groomed->N > 1)
         {
            FourVector P1 = Groomed->Child1->P;
            FourVector P2 = Groomed->Child2->P;

            double RecoSubJetDR = GetDR(P1, P2);

            double SubJetPT1 = P1.GetPT();
            double SubJetPT2 = P2.GetPT();

            double ZG = min(SubJetPT1, SubJetPT2) / (SubJetPT1 + SubJetPT2);
            double SDMass = Groomed->P.GetMass();

            double RecoJetPT = MJet.JetPT[iJ];

            int PIndex = 0;
            for(int i = 0; i < 9; i++)
               if(RecoJetPT >= PTBinMin[i] && RecoJetPT < PTBinMin[i+1])
                  PIndex = i;

            TreeJetRecoDR = RecoSubJetDR;
            TreeJetZG = ZG;
            TreeJetSDMass = SDMass;
            TreeJetSDPT = Groomed->P.GetPT();
         
            if(RecoSubJetDR < 0.1)
               continue;

            HRecoJetPT.Fill(RecoJetPT);

            HSDMass[PIndex]->Fill(SDMass);
         }
         else
         {
            TreeJetRecoDR = -1;
            TreeJetZG = -1;
            TreeJetSDMass = -1;
            TreeJetSDPT = -1;
         }

         if(Groomed2->N > 1)
         {
            FourVector P1 = Groomed2->Child1->P;
            FourVector P2 = Groomed2->Child2->P;

            double RecoSubJetDR = GetDR(P1, P2);

            double SubJetPT1 = P1.GetPT();
            double SubJetPT2 = P2.GetPT();

            double ZG = min(SubJetPT1, SubJetPT2) / (SubJetPT1 + SubJetPT2);
            double SDMass = Groomed2->P.GetMass();

            TreeJetRecoDR2 = RecoSubJetDR;
            TreeJetZG2 = ZG;
            TreeJetSDMass2 = SDMass;
            TreeJetSDPT2 = Groomed2->P.GetPT();
         }
         else
         {
            TreeJetRecoDR2 = -1;
            TreeJetZG2 = -1;
            TreeJetSDMass2 = -1;
            TreeJetSDPT2 = -1;
         }

         OutputTree.Fill();
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   HN.Write();

   HRecoJetPT.Write();

   for(int j = 0; j < 9; j++)
   {
      if(HSDMass[j] != NULL)             HSDMass[j]->Write();
      if(HSDMass[j] != NULL)             delete HSDMass[j];
   }

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





