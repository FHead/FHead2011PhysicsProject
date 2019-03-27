#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
using namespace fastjet;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "TF1.h"
#include "TLatex.h"

#include "Code/TauHelperFunctions3.h"
#include "ProgressBar.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "CommandLine.h"

#include "Messenger.h"

#define MAXJET 500
#define MAXD0 10

int main(int argc, char *argv[])
{
   SetThesisStyle();

   ClusterSequence::set_fastjet_banner_stream(NULL);

   CommandLine CL(argc, argv);

   vector<string> InputFileName  = CL.GetStringVector("Input", "");
   string OutputFileName         = CL.Get("Output", "Result.root");
   double JetPTMin               = CL.GetDouble("JetPTMin", 40);
   double JetEtaMin              = CL.GetDouble("JetEtaMin", -4.0);
   double JetEtaMax              = CL.GetDouble("JetEtaMax", 4.0);
   double D0PTMin                = CL.GetDouble("D0PTMin", 1);
   double D0EtaMin               = CL.GetDouble("D0EtaMin", -3.0);
   double D0EtaMax               = CL.GetDouble("D0EtaMax", 3.0);
   bool KeepEventsWithNoD        = CL.GetBool("KeepEventsWithNoD", false);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TH1D HN("HN", "", 2, 0, 2);

   TTree OutputTree("Tree", "Tree");

   double TreeWeight, TreePTHat;
   int TreeJetCount;
   double TreeJetPT[MAXJET], TreeJetEta[MAXJET], TreeJetPhi[MAXJET];
   int TreeD0Count;
   double TreeD0PT[MAXD0], TreeD0Eta[MAXD0], TreeD0Phi[MAXD0];
   double TreeKPT[MAXD0], TreeKEta[MAXD0], TreeKPhi[MAXD0];
   double TreePiPT[MAXD0], TreePiEta[MAXD0], TreePiPhi[MAXD0];

   OutputTree.Branch("Weight", &TreeWeight, "Weight/D");
   OutputTree.Branch("PTHat", &TreePTHat, "PTHat/D");
   OutputTree.Branch("JetCount", &TreeJetCount, "JetCount/I");
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT[JetCount]/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta[JetCount]/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi[JetCount]/D");
   OutputTree.Branch("D0Count", &TreeD0Count, "D0Count/I");
   OutputTree.Branch("D0PT", &TreeD0PT, "D0PT[D0Count]/D");
   OutputTree.Branch("D0Eta", &TreeD0Eta, "D0Eta[D0Count]/D");
   OutputTree.Branch("D0Phi", &TreeD0Phi, "D0Phi[D0Count]/D");
   OutputTree.Branch("KPT", &TreeKPT, "KPT[D0Count]/D");
   OutputTree.Branch("KEta", &TreeKEta, "KEta[D0Count]/D");
   OutputTree.Branch("KPhi", &TreeKPhi, "KPhi[D0Count]/D");
   OutputTree.Branch("PiPT", &TreePiPT, "PiPT[D0Count]/D");
   OutputTree.Branch("PiEta", &TreePiEta, "PiEta[D0Count]/D");
   OutputTree.Branch("PiPhi", &TreePiPhi, "PiPhi[D0Count]/D");

   for(string FileName : InputFileName)
   {
      cout << "Processing file " << FileName << endl;

      TFile InputFile(FileName.c_str());

      HiEventTreeMessenger MHiEvent(InputFile);
      GenParticleTreeMessenger MGen(InputFile);

      if(MHiEvent.Tree == nullptr)
      {
         cout << "Tree not found" << endl;
         InputFile.Close();
         continue;
      }

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
         MGen.GetEntry(iE);

         TreeWeight = MHiEvent.Weight;
         TreePTHat = MHiEvent.PTHat;

         HN.Fill(0);
         HN.Fill(1, MHiEvent.Weight);
         
         vector<PseudoJet> Particles;
         vector<FourVector> D0a;
         vector<FourVector> D0b;   // with two daughters and they are pi and K
         vector<FourVector> PiFromD0b;   // 211 = pi+
         vector<FourVector> KFromD0b;   // 321 = K+
         vector<FourVector> D0c;   // with two daughters and they are pi and K, with track cuts

         int ParticleCount = MGen.PT->size();
         for(int iP = 0; iP < ParticleCount; iP++)
         {
            if((*MGen.Eta)[iP] < -4 || (*MGen.Eta)[iP] > 4)
               continue;
            if((*MGen.DaughterCount)[iP] > 0)
               continue;
            if((*MGen.ID)[iP] == 12 || (*MGen.ID)[iP] == -12)
               continue;
            if((*MGen.ID)[iP] == 14 || (*MGen.ID)[iP] == -16)
               continue;
            if((*MGen.ID)[iP] == 14 || (*MGen.ID)[iP] == -16)
               continue;

            FourVector P;
            P.SetPtEtaPhi((*MGen.PT)[iP], (*MGen.Eta)[iP], (*MGen.Phi)[iP]);
            Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
         }
         JetDefinition Definition(antikt_algorithm, 0.3);
         ClusterSequence Sequence(Particles, Definition);
         vector<PseudoJet> FastJets = Sequence.inclusive_jets();

         vector<FourVector> Jets;
         for(PseudoJet J : FastJets)
         {
            if(J.eta() < -3 && J.eta() > 3)
               continue;
            if(J.perp() > MHiEvent.PTHat * 1.5)
               continue;

            Jets.push_back(FourVector(J.e(), J.px(), J.py(), J.pz()));
         }

         for(int iP = 0; iP < ParticleCount; iP++)
         {
            if((*MGen.Eta)[iP] < -4 || (*MGen.Eta)[iP] > 4)
               continue;

            FourVector P;
            P.SetPtEtaPhi((*MGen.PT)[iP], (*MGen.Eta)[iP], (*MGen.Phi)[iP]);
         
            if((*MGen.ID)[iP] != 421 && (*MGen.ID)[iP] != -421)
               continue;

            D0a.push_back(P);

            if((*MGen.DaughterCount)[iP] != 2)
               continue;
            if((*MGen.DaughterIndex)[iP].size() != 2)
               continue;

            int ID1 = (*MGen.DaughterIndex)[iP][0];
            int ID2 = (*MGen.DaughterIndex)[iP][1];

            FourVector P1, P2;
            P1.SetPtEtaPhi((*MGen.PT)[ID1], (*MGen.Eta)[ID1], (*MGen.Phi)[ID1]);
            P2.SetPtEtaPhi((*MGen.PT)[ID2], (*MGen.Eta)[ID2], (*MGen.Phi)[ID2]);

            if((*MGen.ID)[ID1] == 211 && (*MGen.ID)[ID2] == -321)
            {
               PiFromD0b.push_back(P1);
               KFromD0b.push_back(P2);
               D0b.push_back(P);
            }
            else if((*MGen.ID)[ID1] == -211 && (*MGen.ID)[ID2] == 321)
            {
               PiFromD0b.push_back(P1);
               KFromD0b.push_back(P2);
               D0b.push_back(P);
            }
            else if((*MGen.ID)[ID1] == 321 && (*MGen.ID)[ID2] == -211)
            {
               PiFromD0b.push_back(P2);
               KFromD0b.push_back(P1);
               D0b.push_back(P);
            }
            else if((*MGen.ID)[ID1] == -321 && (*MGen.ID)[ID2] == 211)
            {
               PiFromD0b.push_back(P2);
               KFromD0b.push_back(P1);
               D0b.push_back(P);
            }
            else
               continue;

            if(P1.GetAbsEta() > 2)
               continue;
            if(P2.GetAbsEta() > 2)
               continue;
            if(P1.GetPT() < 2)
               continue;
            if(P2.GetPT() < 2)
               continue;

            D0c.push_back(P);
         }

         // Fill jets into the tree
         TreeJetCount = 0;
         for(int iJ = 0; iJ < (int)Jets.size(); iJ++)
         {
            if(Jets[iJ].GetPT() > JetPTMin && Jets[iJ].GetEta() > JetEtaMin && Jets[iJ].GetEta() < JetEtaMax)
            {
               TreeJetPT[TreeJetCount] = Jets[iJ].GetPT();
               TreeJetEta[TreeJetCount] = Jets[iJ].GetEta();
               TreeJetPhi[TreeJetCount] = Jets[iJ].GetPhi();
               TreeJetCount = TreeJetCount + 1;
            }
         }
         if(TreeJetCount == 0)
            continue;

         // Fill D0s into the tree.  We store only ones with the right decay
         TreeD0Count = 0;
         for(int iD = 0; iD < (int)D0b.size(); iD++)
         {
            if(D0b[iD].GetPT() > D0PTMin && D0b[iD].GetEta() > D0EtaMin && D0b[iD].GetEta() < D0EtaMax)
            {
               TreeD0PT[TreeD0Count] = D0b[iD].GetPT();
               TreeD0Eta[TreeD0Count] = D0b[iD].GetEta();
               TreeD0Phi[TreeD0Count] = D0b[iD].GetPhi();
               TreeKPT[TreeD0Count] = KFromD0b[iD].GetPT();
               TreeKEta[TreeD0Count] = KFromD0b[iD].GetEta();
               TreeKPhi[TreeD0Count] = KFromD0b[iD].GetPhi();
               TreePiPT[TreeD0Count] = PiFromD0b[iD].GetPT();
               TreePiEta[TreeD0Count] = PiFromD0b[iD].GetEta();
               TreePiPhi[TreeD0Count] = PiFromD0b[iD].GetPhi();
               TreeD0Count = TreeD0Count + 1;
            }
         }
         if(KeepEventsWithNoD == false && TreeD0Count == 0)
            continue;

         OutputTree.Fill();
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   OutputFile.cd();

   HN.Write();
   OutputTree.Write();

   OutputFile.Close();

   return 0;
}



