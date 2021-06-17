#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
using namespace fastjet;

#include "TFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions3.h"
#include "CommandLine.h"
#include "ProgressBar.h"

#include "ReadPU14Event.h"

#define MAX 10000

int main(int argc, char *argv[]);
void Preselection(PU14Event &E);

int main(int argc, char *argv[])
{
   ClusterSequence::set_fastjet_banner_stream(NULL);

   CommandLine CL(argc, argv);

   string InputFileNamePythia = CL.Get("InputPythia");
   string InputFileNameBackground = CL.Get("InputBackground");
   string OutputFileName = CL.Get("Output");
   int MaxEvent = CL.GetInt("MaxEvent");
   bool TagIsJet = CL.GetBool("TagIsJet", true);
   double Weight = CL.GetDouble("Weight", 1);

   PU14Reader InputPythia(InputFileNamePythia);
   PU14Reader InputBackground(InputFileNameBackground);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree OutputTree("Tree", "Tree");

   int TreeNJet;
   double TreeJetPT[MAX];
   double TreeJetEta[MAX];
   double TreeJetPhi[MAX];
   double TreeTagPT;
   double TreeTagEta;
   double TreeTagPhi;
   double TreeProbePT;
   double TreeProbeEta;
   double TreeProbePhi;
   double TreeSignalWTAPT;
   double TreeSignalWTAEta;
   double TreeSignalWTAPhi;
   double TreeAllWTAPT;
   double TreeAllWTAEta;
   double TreeAllWTAPhi;
   double TreeAllProbePT;
   double TreeAllProbeEta;
   double TreeAllProbePhi;
   double TreeWeight;

   OutputTree.Branch("NJet", &TreeNJet, "NJet/I");
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT[NJet]/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta[NJet]/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi[NJet]/D");
   OutputTree.Branch("TagPT", &TreeTagPT, "TagPT/D");
   OutputTree.Branch("TagEta", &TreeTagEta, "TagEta/D");
   OutputTree.Branch("TagPhi", &TreeTagPhi, "TagPhi/D");
   OutputTree.Branch("ProbePT", &TreeProbePT, "ProbePT/D");
   OutputTree.Branch("ProbeEta", &TreeProbeEta, "ProbeEta/D");
   OutputTree.Branch("ProbePhi", &TreeProbePhi, "ProbePhi/D");
   OutputTree.Branch("SignalWTAPT", &TreeSignalWTAPT, "SignalWTAPT/D");
   OutputTree.Branch("SignalWTAEta", &TreeSignalWTAEta, "SignalWTAEta/D");
   OutputTree.Branch("SignalWTAPhi", &TreeSignalWTAPhi, "SignalWTAPhi/D");
   OutputTree.Branch("AllWTAPT", &TreeAllWTAPT, "AllWTAPT/D");
   OutputTree.Branch("AllWTAEta", &TreeAllWTAEta, "AllWTAEta/D");
   OutputTree.Branch("AllWTAPhi", &TreeAllWTAPhi, "AllWTAPhi/D");
   OutputTree.Branch("AllProbePT", &TreeAllProbePT, "AllProbePT/D");
   OutputTree.Branch("AllProbeEta", &TreeAllProbeEta, "AllProbeEta/D");
   OutputTree.Branch("AllProbePhi", &TreeAllProbePhi, "AllProbePhi/D");
   OutputTree.Branch("Weight", &TreeWeight, "Weight/D");

   int iE = 0;
   ProgressBar Bar(cout, 100000);
   Bar.SetStyle(7);

   while(InputPythia.ReadNextEvent() == true && InputBackground.ReadNextEvent() == true)
   {
      Bar.Update(iE);
      Bar.Print();

      iE = iE + 1;
      if(iE > MaxEvent)
         break;

      PU14Event PythiaEvent = InputPythia.GetEvent();
      PU14Event BackgroundEvent = InputBackground.GetEvent();

      TreeWeight = Weight;

      Preselection(PythiaEvent);
      Preselection(BackgroundEvent);

      int NS = PythiaEvent.P.size();
      int NB = BackgroundEvent.P.size();
      
      // Regular clustering without the WTA scheme
      vector<PseudoJet> Particles;
      for(int i = 0; i < NS; i++)
      {
         FourVector &P = PythiaEvent.P[i];
         Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> FastJets = Sequence.inclusive_jets();

      vector<FourVector> Jets;
      for(auto J : FastJets)
         Jets.push_back(FourVector(J.e(), J.px(), J.py(), J.pz()));

      // Find leading jet or photon
      FourVector Tag(-1, 0, 0, 0);
      if(TagIsJet == true)
      {
         for(auto J : Jets)
            if(J.GetPT() > Tag.GetPT())
               Tag = J;
      }
      else   // tag is leading photon
      {
         for(int i = 0; i < NS; i++)
            if(PythiaEvent.ID[i] == 22 && PythiaEvent.P[i].GetPT() > Tag.GetPT())
               Tag = PythiaEvent.P[i];
      }

      // Find leading jet on the other side
      FourVector Probe(-1, 0, 0, 0);
      for(auto J : Jets)
      {
         if(fabs(GetDPhi(J, Tag)) < M_PI / 2)
            continue;
         if(J.GetPT() > Probe.GetPT())
            Probe = J;
      }

      // Cluster hemisphere with WTA scheme
      vector<PseudoJet> ParticlesSignalHemisphere;
      vector<PseudoJet> ParticlesAllHemisphere;
      for(int i = 0; i < NS; i++)
      {
         double DPhi = GetDPhi(PythiaEvent.P[i], Tag);
         if(fabs(DPhi) < M_PI / 2)   // same side as the leading jet
            continue;

         FourVector &P = PythiaEvent.P[i];
         ParticlesSignalHemisphere.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
         ParticlesAllHemisphere.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      for(int i = 0; i < NB; i++)
      {
         double DPhi = GetDPhi(BackgroundEvent.P[i], Tag);
         if(fabs(DPhi) < M_PI / 2)   // same side as the leading jet
            continue;

         FourVector &P = BackgroundEvent.P[i];
         ParticlesAllHemisphere.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      
      JetDefinition WTADefinition(antikt_algorithm, 10.0, WTA_pt_scheme);
      ClusterSequence SequenceSignal(ParticlesSignalHemisphere, WTADefinition);
      vector<PseudoJet> SignalOneJet = SequenceSignal.exclusive_jets(1);
      ClusterSequence SequenceAll(ParticlesAllHemisphere, WTADefinition);
      vector<PseudoJet> AllOneJet = SequenceAll.exclusive_jets(1);
      ClusterSequence SequenceAllRegular(ParticlesAllHemisphere, Definition);
      vector<PseudoJet> AllFastJets = SequenceAllRegular.inclusive_jets();

      FourVector SignalWTA(SignalOneJet[0].e(), SignalOneJet[0].px(), SignalOneJet[0].py(), SignalOneJet[0].pz());
      FourVector AllWTA(AllOneJet[0].e(), AllOneJet[0].px(), AllOneJet[0].py(), AllOneJet[0].pz());

      vector<FourVector> AllJets;
      for(auto J : AllFastJets)
         AllJets.push_back(FourVector(J.e(), J.px(), J.py(), J.pz()));

      FourVector AllProbe(-1, 0, 0, 0);
      for(auto J : AllJets)
         if(J.GetPT() > AllProbe.GetPT())
            AllProbe = J;

      // Fill output tree
      TreeNJet = Jets.size();
      for(int i = 0; i < TreeNJet; i++)
      {
         TreeJetPT[i] = Jets[i].GetPT();
         TreeJetEta[i] = Jets[i].GetEta();
         TreeJetPhi[i] = Jets[i].GetPhi();
      }
      TreeTagPT = Tag.GetPT();
      TreeTagEta = Tag.GetEta();
      TreeTagPhi = Tag.GetPhi();
      TreeProbePT = Probe.GetPT();
      TreeProbeEta = Probe.GetEta();
      TreeProbePhi = Probe.GetPhi();
      TreeSignalWTAPT = SignalWTA.GetPT();
      TreeSignalWTAEta = SignalWTA.GetEta();
      TreeSignalWTAPhi = SignalWTA.GetPhi();
      TreeAllWTAPT = AllWTA.GetPT();
      TreeAllWTAEta = AllWTA.GetEta();
      TreeAllWTAPhi = AllWTA.GetPhi();
      TreeAllProbePT = AllProbe.GetPT();
      TreeAllProbeEta = AllProbe.GetEta();
      TreeAllProbePhi = AllProbe.GetPhi();

      OutputTree.Fill();
   }

   Bar.PrintLine();

   OutputTree.Write();
   OutputFile.Close();

   return 0;
}

void Preselection(PU14Event &E)
{
   int N = E.P.size();
   for(int i = 0; i < N; i++)
   {
      bool Remove = false;

      if(E.ID[i] == 12 || E.ID[i] == -12)   Remove = true;
      if(E.ID[i] == 14 || E.ID[i] == -14)   Remove = true;
      if(E.ID[i] == 16 || E.ID[i] == -16)   Remove = true;
      if(E.P[i].GetAbsEta() > 5)            Remove = true;

      if(Remove == true)
      {
         E.P.erase(E.P.begin() + i);
         E.ID.erase(E.ID.begin() + i);
         E.Type.erase(E.Type.begin() + i);
         i = i - 1;
         N = N - 1;
      }
   }
}



