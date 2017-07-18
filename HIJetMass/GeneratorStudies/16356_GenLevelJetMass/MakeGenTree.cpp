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

   if(IsData == true)
   {
      cerr << "I'd rather not run on data for this study." << endl;
      return -1;
   }

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

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("GenJetTree", "GenJetTree");

   double TreeCentrality, TreePTHat;
   OutputTree.Branch("Centrality", &TreeCentrality, "Centrality/D");
   OutputTree.Branch("PTHat", &TreePTHat, "PTHat/D");

   double TreeJetPT, TreeJetEta, TreeJetPhi, TreeJetEnergy;
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi/D");
   OutputTree.Branch("JetEnergy", &TreeJetEnergy, "JetEnergy/D");

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

   TH1D HN("HN", ";;", 1, 0, 1);

   int EntryCount = MHiEvent.Tree->GetEntries() * 0.10;
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

      TreeCentrality = GetCentrality(MHiEvent.hiBin);
      TreePTHat = MJet.PTHat;

      if(MJet.PTHat <= PTHatMin || MJet.PTHat > PTHatMax)
         continue;

      vector<PseudoJet> Particles;
      for(int iG = 0; iG < MGen.ID->size(); iG++)
      {
         int AbsID = (*MGen.ID)[iG];
         if(AbsID < 0)
            AbsID = -AbsID;

         if(AbsID == 12 || AbsID == 14 || AbsID == 16)   // neutrinos, skip
            continue;

         if((*MGen.DaughterCount)[iG] > 0)   // we want final state particles
            continue;

         double Mass = 0;
         if((*MGen.Charge)[iG] != 0)
            Mass = 0.13957018;   // Pion mass
      
         FourVector P;
         P.SetPtEtaPhiMass((*MGen.PT)[iG], (*MGen.Eta)[iG], (*MGen.Phi)[iG], Mass);
         Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets();

      for(int iJ = 0; iJ < Jets.size(); iJ++)
      {
         // Save some space!
         if(Jets[iJ].eta() < -1.5 || Jets[iJ].eta() > 1.5)
            continue;
         if(Jets[iJ].perp() < 50)
            continue;

         TreeJetPT = Jets[iJ].perp();
         TreeJetEta = Jets[iJ].eta();
         TreeJetPhi = Jets[iJ].phi();
         TreeJetEnergy = Jets[iJ].e();

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

         TreeDepth0 = NodeDistance(Groomed0, Nodes[0]);
         TreeDepth7 = NodeDistance(Groomed7, Nodes[0]);

         if(Groomed0->N > 1)
         {
            TreeSubJetDR0 = GetDR(Groomed0->Child1->P, Groomed0->Child2->P);
            TreeSDMass0 = Groomed0->P.GetMass();

            TreeSubJet1PT0  = Groomed0->Child1->P.GetPT();
            TreeSubJet1Eta0 = Groomed0->Child1->P.GetEta();
            TreeSubJet1Phi0 = Groomed0->Child1->P.GetPhi();
            TreeSubJet2PT0  = Groomed0->Child2->P.GetPT();
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











