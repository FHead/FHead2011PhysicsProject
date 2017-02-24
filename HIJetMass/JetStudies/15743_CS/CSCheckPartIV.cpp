#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"
#include "fastjet/contrib/SoftDrop.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"

#include "Code/TauHelperFunctions2.h"
#include "ProgressBar.h"

#include "Messenger.h"
#include "BasicUtilities.h"
#include "CATree.h"

int main(int argc, char *argv[]);
double GetDPhi(double Phi1, double Phi2);

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " Input Output" << endl;
      return -1;
   }

   TFile File(argv[1]);

   HiEventTreeMessenger MHiEvent(File);
   JetTreeMessenger MJet(File);
   PFTreeMessenger MPF(File, "pfcandAnalyzer/pfTree");
   PFTreeMessenger MPFCS(File, "pfcandAnalyzerCS/pfTree");
   RhoTreeMessenger MRho(File);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(argv[2], "RECREATE");

   TTree OutputTree("T", "T");

   double Centrality;
   OutputTree.Branch("Centrality", &Centrality, "Centrality/D");

   double JetPT, PT, Eta, Phi, Mass, GroomedPT, Mass7, GroomedPT7;
   double SDPT, SDEta, SDPhi, SDMass;
   OutputTree.Branch("JetPT", &JetPT, "JetPT/D");
   OutputTree.Branch("PT", &PT, "PT/D");
   OutputTree.Branch("Eta", &Eta, "Eta/D");
   OutputTree.Branch("Phi", &Phi, "Phi/D");
   OutputTree.Branch("Mass", &Mass, "Mass/D");
   OutputTree.Branch("Mass7", &Mass7, "Mass7/D");
   OutputTree.Branch("GroomedPT", &GroomedPT, "GroomedPT/D");
   OutputTree.Branch("GroomedPT7", &GroomedPT7, "GroomedPT7/D");
   OutputTree.Branch("SDPT", &SDPT, "SDPT/D");
   OutputTree.Branch("SDEta", &SDEta, "SDEta/D");
   OutputTree.Branch("SDPhi", &SDPhi, "SDPhi/D");
   OutputTree.Branch("SDMass", &SDMass, "SDMass/D");
   
   double SubJet1PT, SubJet2PT, SubJetDR;
   OutputTree.Branch("SubJet1PT", &SubJet1PT, "SubJet1PT/D");
   OutputTree.Branch("SubJet2PT", &SubJet2PT, "SubJet2PT/D");
   OutputTree.Branch("SubJetDR", &SubJetDR, "SubJetDR/D");
   
   double SubJet1PT7, SubJet2PT7, SubJetDR7;
   OutputTree.Branch("SubJet1PT7", &SubJet1PT7, "SubJet1PT7/D");
   OutputTree.Branch("SubJet2PT7", &SubJet2PT7, "SubJet2PT7/D");
   OutputTree.Branch("SubJetDR7", &SubJetDR7, "SubJetDR7/D");

   int Count = 0;

   int EntryCount = MHiEvent.Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(2);

   for(int iE = 0; iE < EntryCount; iE = iE + 1)
   {
      Bar.Update(iE);
      if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0)
         Bar.Print();

      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MPF.GetEntry(iE);
      MRho.GetEntry(iE);

      Centrality = GetCentrality(MHiEvent.hiBin);

      vector<PseudoJet> Particles;
      for(int i = 0; i < (int)MPF.ID->size(); i++)
      {
         FourVector P;
         P.SetPtEtaPhi((*MPF.PT)[i], (*MPF.Eta)[i], (*MPF.Phi)[i]);
         P[0] = (*MPF.E)[i];
         Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      double GhostArea = 0.005;
      AreaDefinition AreaDef(active_area_explicit_ghosts, GhostedAreaSpec(6.0, 1, GhostArea));
      ClusterSequenceArea Sequence(Particles, Definition, AreaDef);
      // ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets();

      vector<PseudoJet> NewJets(Jets.size());
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         double rho = GetRho(MRho.EtaMax, MRho.Rho, Jets[i].eta());
         double rhom = GetRho(MRho.EtaMax, MRho.RhoM, Jets[i].eta());
         contrib::ConstituentSubtractor Subtractor(rho);
         Subtractor.set_alpha(1);  // optional
         // subtractor.set_max_deltaR(2);  // optional
         NewJets[i] = Subtractor(Jets[i]);
      }

      vector<PseudoJet> CSCandidates;
      for(int i = 0; i < (int)NewJets.size(); i++)
      {
         vector<PseudoJet> Candidates = NewJets[i].constituents();
         for(int j = 0; j < (int)Candidates.size(); j++)
            if(Candidates[j].has_area() == false || Candidates[j].is_pure_ghost() == false)   // remove ghosts
               CSCandidates.push_back(Candidates[j]);
      }
      ClusterSequence NewSequence(CSCandidates, Definition);
      vector<PseudoJet> SDJets = NewSequence.inclusive_jets();

      for(int i = 0; i < (int)SDJets.size(); i++)
      {
         if(SDJets[i].perp() < 50)
            continue;
         if(SDJets[i].eta() < -2 || SDJets[i].eta() > 2)
            continue;

         vector<Node *> Nodes;

         vector<PseudoJet> Candidates = SDJets[i].constituents();
         if(Candidates.size() < 1)
            continue;

         for(int j = 0; j < (int)Candidates.size(); j++)
         {
            FourVector P;
            P[0] = Candidates[j].e();
            P[1] = Candidates[j].px();
            P[2] = Candidates[j].py();
            P[3] = Candidates[j].pz();
            Nodes.push_back(new Node(P));
         }
         
         BuildCATree(Nodes);

         Node *Groomed = FindSDNode(Nodes[0]);
         Node *Groomed7 = FindSDNode(Nodes[0], 0.5, 1.5);

         JetPT = SDJets[i].perp();
         PT = Groomed->P.GetPT();
         Eta = Groomed->P.GetEta();
         Phi = Groomed->P.GetPhi();
         Mass = Groomed->P.GetMass();
         GroomedPT = Groomed->P.GetPT();

         Mass7 = Groomed7->P.GetMass();
         GroomedPT7 = Groomed7->P.GetPT();

         if(Groomed->N > 1)
         {
            SubJet1PT = Groomed->Child1->P.GetPT();
            SubJet2PT = Groomed->Child2->P.GetPT();
            SubJetDR = GetDR(Groomed->Child1->P, Groomed->Child2->P);
         }
         else
         {
            SubJet1PT = 0;
            SubJet2PT = 0;
            SubJetDR = -1;
         }
         
         if(Groomed7->N > 1)
         {
            SubJet1PT7 = Groomed7->Child1->P.GetPT();
            SubJet2PT7 = Groomed7->Child2->P.GetPT();
            SubJetDR7 = GetDR(Groomed7->Child1->P, Groomed7->Child2->P);
         }
         else
         {
            SubJet1PT7 = 0;
            SubJet2PT7 = 0;
            SubJetDR7 = -1;
         }

         // contrib::SoftDrop SD(0.0, 0.1);
         // PseudoJet SDJet = SD(NewJets[i]);

         // SDPT = SDJet.perp();
         // SDEta = SDJet.eta();
         // SDPhi = SDJet.phi();
         // SDMass = SDJet.m();
         // sd_jet.structure_of<contrib::SoftDrop>().mu();

         OutputTree.Fill();

         if(JetPT > 80 && PT / JetPT > 0.99 && abs(Eta) < 2 && Count < 10)
         {
            Count = Count + 1;

            TH2D H1(Form("H1_%d", Count), "", 100, -0.5, 0.5, 100, -0.5, 0.5);
            TH2D H2(Form("H2_%d", Count), "", 100, -0.5, 0.5, 100, -0.5, 0.5);

            vector<PseudoJet> Constituents = Jets[i].constituents();
            for(int j = 0; j < (int)Constituents.size(); j++)
               H1.Fill(Constituents[j].eta() - Jets[i].eta(), GetDPhi(Constituents[j].phi(), Jets[i].phi()), Constituents[j].perp());
            for(int j = 0; j < (int)Candidates.size(); j++)
               H2.Fill(Candidates[j].eta() - NewJets[i].eta(), GetDPhi(Candidates[j].phi(), NewJets[i].phi()), Candidates[j].perp());

            H1.Write();
            H2.Write();
         }

         delete Nodes[0];
      }

      // if(Count >= 20)
      //    break;
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();

   OutputFile.Close();

   File.Close();

   return 0;
}

double GetDPhi(double Phi1, double Phi2)
{
   double DPhi = Phi1 - Phi2;
   while(DPhi < -PI)
      DPhi = DPhi + 2 * PI;
   while(DPhi >= +PI)
      DPhi = DPhi - 2 * PI;
   return DPhi;
}




