#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
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
   string InputFileName = "HiForestAOD_999.root";
   string OutputFileName = "Output_HiForestAOD_999.root";

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " Input Output" << endl;
      return -1;
   }

   InputFileName = argv[1];
   OutputFileName = argv[2];

   TFile InputFile(InputFileName.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   string PFTreeName = "pfcandAnalyzerCS/pfTree";

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);
   PFTreeMessenger MPF(InputFile, PFTreeName);
   RhoTreeMessenger MRho(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("T", "T");

   double TreeJetPT, TreeJetEta, TreeJetPhi, TreeJetSDPT;
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi/D");
   OutputTree.Branch("JetSDPT", &TreeJetSDPT, "JetSDPT/D");
   
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

   double TreeMatchDR, TreeMatchPT, TreeMatchArea;
   OutputTree.Branch("MatchDR", &TreeMatchDR, "MatchDR/D");
   OutputTree.Branch("MatchPT", &TreeMatchPT, "MatchPT/D");
   OutputTree.Branch("MatchArea", &TreeMatchArea, "MatchArea/D");

   double TreeSubJetDR0, TreeSDMass0, TreeSDPT0;
   double TreeSubJetDR7, TreeSDMass7, TreeSDPT7;
   OutputTree.Branch("SubJetDR0", &TreeSubJetDR0, "SubJetDR0/D");
   OutputTree.Branch("SDMass0", &TreeSDMass0, "SDMass0/D");
   OutputTree.Branch("SDPT0", &TreeSDPT0, "SDPT0/D");
   OutputTree.Branch("SubJetDR7", &TreeSubJetDR7, "SubJetDR7/D");
   OutputTree.Branch("SDMass7", &TreeSDMass7, "SDMass7/D");
   OutputTree.Branch("SDPT7", &TreeSDPT7, "SDPT7/D");
   
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

   int EntryCount = MHiEvent.Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      Bar.Print();

      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MSDJet.GetEntry(iE);
      MPF.GetEntry(iE);
      MRho.GetEntry(iE);

      SDJetHelper HSDJet(MSDJet);

      TreeCentrality = GetCentrality(MHiEvent.hiBin);
      TreePTHat = MSDJet.PTHat;
      TreeRho = GetRho(MRho.EtaMax, MRho.Rho, 0);

      vector<PseudoJet> Particles;
      for(int iPF = 0; iPF < MPF.ID->size(); iPF++)
      {
         FourVector P;
         P.SetPtEtaPhi((*MPF.PT)[iPF], (*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
         // P[0] = (*MPF.E)[iPF];
         Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets();

      ClusterSequenceArea SequenceArea(Particles, Definition, GhostedAreaSpec(6.0, 1, 0.001));
      vector<PseudoJet> JetsWithGhost = SequenceArea.inclusive_jets();

      for(int iJ = 0; iJ < MSDJet.JetCount; iJ++)
      {
         TreeJetPT = MSDJet.JetPT[iJ];
         TreeJetEta = MSDJet.JetEta[iJ];
         TreeJetPhi = MSDJet.JetPhi[iJ];

         TreeSubJet1PT = HSDJet.RecoSubJet1[iJ].GetPT();
         TreeSubJet1Eta = HSDJet.RecoSubJet1[iJ].GetEta();
         TreeSubJet1Phi = HSDJet.RecoSubJet1[iJ].GetPhi();
         TreeSubJet2PT = HSDJet.RecoSubJet2[iJ].GetPT();
         TreeSubJet2Eta = HSDJet.RecoSubJet2[iJ].GetEta();
         TreeSubJet2Phi = HSDJet.RecoSubJet2[iJ].GetPhi();

         FourVector P1, P2;
         P1.SetPtEtaPhi(TreeSubJet1PT, TreeSubJet1Eta, TreeSubJet1Phi);
         P2.SetPtEtaPhi(TreeSubJet2PT, TreeSubJet2Eta, TreeSubJet2Phi);

         TreeJetSDPT = (P1 + P2).GetPT();

         TreeSubJetDR = HSDJet.RecoSubJetDR[iJ];
         TreeSDMass = MSDJet.JetM[iJ];

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

         int BestJetWithGhost = 0;
         double BestDRWithGhost = -1;
         for(int i = 0; i < (int)JetsWithGhost.size(); i++)
         {
            double DR = GetDR(MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ], JetsWithGhost[i].eta(), JetsWithGhost[i].phi());
            if(BestDRWithGhost < 0 || DR < BestDRWithGhost)
            {
               BestJetWithGhost = i;
               BestDRWithGhost = DR;
            }
         }

         if(BestDR >= 0)
         {
            TreeMatchDR = BestDR;
            TreeMatchPT = Jets[BestJet].perp();
            if(JetsWithGhost[BestJetWithGhost].has_area())
               TreeMatchArea = JetsWithGhost[BestJetWithGhost].area();
            else
               TreeMatchArea = -1;

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

            if(Groomed0->N > 1)
            {
               TreeSubJetDR0 = GetDR(Groomed0->Child1->P, Groomed0->Child2->P);
               TreeSDMass0 = Groomed0->P.GetMass();
               TreeSDPT0 = Groomed0->P.GetPT();
         
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
               TreeSDPT7 = Groomed7->P.GetPT();
               
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

   OutputFile.Close();

   InputFile.Close();

   return 0;
}










