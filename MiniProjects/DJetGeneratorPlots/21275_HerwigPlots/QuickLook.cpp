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

int main(int argc, char *argv[])
{
   SetThesisStyle();

   ClusterSequence::set_fastjet_banner_stream(NULL);

   CommandLine CL(argc, argv);

   vector<string> InputFileName  = CL.GetStringVector("Input", "");
   string OutputFileName         = CL.Get("Output", "Result.root");

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TH1D HN("HN", "", 2, 0, 2);
   
   TH1D HPTHat("HPTHat", ";#hat{p}_{T};", 100, 0, 1200);
   TH1D HJetCount("HJetCount", ";Jet count;", 100, 0, 100);
   TH1D HJetCountPT30("HJetCountPT30", ";Jet count;", 100, 0, 100);
   TH1D HJetCountPT50("HJetCountPT50", ";Jet count;", 100, 0, 100);
   TH1D HJetCountPT75("HJetCountPT75", ";Jet count;", 100, 0, 100);
   TH1D HJetCountPT100("HJetCountPT100", ";Jet count;", 100, 0, 100);
   TH1D HJetCountPT125("HJetCountPT125", ";Jet count;", 100, 0, 100);
   TH1D HJetPT("HJetPT", ";Jet p_{T};", 100, 0, 1200);
   TH1D HLeadingJetPT("HLeadingJetPT", ";Leading jet p_{T};", 100, 0, 1200);

   TH1D HD0aCount("HD0aCount", ";D^{0}(a) count;", 10, 0, 10);
   TH1D HD0aPT("HD0aPT", ";D^{0}(a) p_{T};", 100, 0, 100);
   TH1D HD0aEta("HD0aEta", ";D^{0}(a) #eta;", 100, -4, 4);
   TH1D HD0bCount("HD0bCount", ";D^{0}(b) count;", 10, 0, 10);
   TH1D HD0bPT("HD0bPT", ";D^{0}(b) p_{T};", 100, 0, 100);
   TH1D HD0bEta("HD0bEta", ";D^{0}(b) #eta;", 100, -4, 4);
   TH1D HD0cCount("HD0cCount", ";D^{0}(c) count;", 10, 0, 10);
   TH1D HD0cPT("HD0cPT", ";D^{0}(c) p_{T};", 100, 0, 100);
   TH1D HD0cEta("HD0cEta", ";D^{0}(c) #eta;", 100, -4, 4);

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

         double W = MHiEvent.Weight;
         W = 1;

         HN.Fill(0);
         HN.Fill(1, W);
         
         HPTHat.Fill(MHiEvent.PTHat, W);

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
         JetDefinition Definition(antikt_algorithm, 0.4);
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

         int JetCount = 0;
         int JetCountPT30 = 0;
         int JetCountPT50 = 0;
         int JetCountPT75 = 0;
         int JetCountPT100 = 0;
         int JetCountPT125 = 0;

         if(Jets.size() > 0)
            HLeadingJetPT.Fill(Jets[0].GetPT(), W);
         for(FourVector J : Jets)
         {
            JetCount = JetCount + 1;
            if(J.GetPT() > 30)    JetCountPT30 = JetCountPT30 + 1;
            if(J.GetPT() > 50)    JetCountPT50 = JetCountPT50 + 1;
            if(J.GetPT() > 75)    JetCountPT75 = JetCountPT75 + 1;
            if(J.GetPT() > 100)   JetCountPT100 = JetCountPT100 + 1;
            if(J.GetPT() > 125)   JetCountPT125 = JetCountPT125 + 1;

            HJetPT.Fill(J.GetPT(), W);
         }

         HJetCount.Fill(JetCount, W);
         HJetCountPT30.Fill(JetCountPT30, W);
         HJetCountPT50.Fill(JetCountPT50, W);
         HJetCountPT75.Fill(JetCountPT75, W);
         HJetCountPT100.Fill(JetCountPT100, W);
         HJetCountPT125.Fill(JetCountPT125, W);

         HD0aCount.Fill(D0a.size(), W);
         for(auto P : D0a)
         {
            HD0aPT.Fill(P.GetPT(), W);
            HD0aEta.Fill(P.GetEta(), W);
         }
         HD0bCount.Fill(D0b.size(), W);
         for(auto P : D0b)
         {
            HD0bPT.Fill(P.GetPT(), W);
            HD0bEta.Fill(P.GetEta(), W);
         }
         HD0cCount.Fill(D0c.size(), W);
         for(auto P : D0c)
         {
            HD0cPT.Fill(P.GetPT(), W);
            HD0cEta.Fill(P.GetEta(), W);
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   OutputFile.cd();

   HN.Write();
   
   HPTHat.Write();
   HJetCount.Write();
   HJetCountPT30.Write();
   HJetCountPT50.Write();
   HJetCountPT75.Write();
   HJetCountPT100.Write();
   HJetCountPT125.Write();
   HJetPT.Write();
   HLeadingJetPT.Write();

   HD0aCount.Write();
   HD0aPT.Write();
   HD0aEta.Write();
   HD0bCount.Write();
   HD0bPT.Write();
   HD0bEta.Write();
   HD0cCount.Write();
   HD0cPT.Write();
   HD0cEta.Write();
   
   OutputFile.Close();

   return 0;
}



