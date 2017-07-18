#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/contrib/ConstituentSubtractor.hh"
#include "fastjet/contrib/SoftDrop.hh"
using namespace fastjet;

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions3.h"
#include "ProgressBar.h"

#include "BasicUtilities.h"
#include "Messenger.h"
#include "SDJetHelper.h"
#include "CATree.h"
#include "DataHelper.h"

#define MAXSIZE 25000000

#define PTType_MB 0
#define PTType_Hard 1
#define PTType_Soft 2
#define PTType_Data 3
#define PTType_Half 4
#define PTType_DataData 5
#define PTType_MC 6

int main(int argc, char *argv[]);
double GetPFPT(double Eta, double Rho, DataHelper &DHFile, int PTType);
double GetModifiedPT(double Eta, double Rho, DataHelper &DHFile);
double GetModifiedPT2(double Eta, double Rho, DataHelper &DHFile);
double GetModifiedPTData(double Eta, double Rho, DataHelper &DHFile);
double GetModifiedPTDataData(double Eta, double Rho, DataHelper &DHFile);
double GetModifiedPTData2(double Eta, double Rho, DataHelper &DHFile);
double GetPT(double Eta, double Rho, DataHelper &DHFile);
double PresampleFactor(double PT);
double Evaluate(double Eta, double Rho, double PT, DataHelper &DHFile);
double Evaluate(double PT, DataHelper &DHFile, string State);
double EvaluateWithCache(int EtaBin, int RhoBin, double PT, DataHelper &DHFile);
double GetEtaMin(double Eta);
double GetEtaMax(double Eta);
int GetEtaBin(double Eta);
double GetRhoMin(double Rho);
double GetRhoMax(double Rho);
int GetRhoBin(double Rho);
string FindState(double Eta, double Rho);
double GetPresample();

int main(int argc, char *argv[])
{
   if(argc != 12 && argc != 13 && argc != 15)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag PTHatMin PTHatMax RhoMultiplier GhostDistance Smear MBMultiplier PTType Range ReuseRate Mod ModBase" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];
   double PTHatMin = atof(argv[4]);
   double PTHatMax = atof(argv[5]);

   double RhoMultiplier = atof(argv[6]);
   double GhostDistance = atof(argv[7]);
   double Smear = atof(argv[8]);
   double MBMultiplier = atof(argv[9]);
   double Range = atof(argv[10]);

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);

   int PTType = atoi(argv[11]);

   if(IsData == true)
      cerr << "I'd be glad to run on data for this study" << endl;

   int ReuseRate = 1;
   if(argc >= 13)
      ReuseRate = atoi(argv[12]);

   int Mod = -1;   // -1 = don't use
   int ModBase = -1;
   if(argc >= 15)
   {
      Mod = atoi(argv[13]);
      ModBase = atoi(argv[14]);
   }

   string DHFileName = "SimpleFitParametersAADataMBDragos.dh";
   if(IsData == false)
      DHFileName = "SimpleFitParametersMBCymbal.dh";
   if(IsData == false)
      DHFileName = "SimpleFitParameters.dh";
   DataHelper DHFile(DHFileName);

   DataHelper RhoDHFile("RhoDatabase.dh");
   string RhoTag = "AA6DijetCymbal";
   if(IsData == true)
      RhoTag = "AAData";

   double CentralityA[100] = {0};
   double CentralityB[100] = {0};
   double CentralityC[100] = {0};
   double CentralityIntegral[100] = {0};
   double MaxCentralityIntegral = 0;
   for(int i = 0; i < 99; i++)
   {
      CentralityA[i] = RhoDHFile[RhoTag][Form("C%02d_A", i)].GetDouble();
      CentralityB[i] = RhoDHFile[RhoTag][Form("C%02d_B", i)].GetDouble();
      CentralityC[i] = RhoDHFile[RhoTag][Form("C%02d_C", i)].GetDouble();
      CentralityIntegral[i] = CentralityA[i] * CentralityC[i] * sqrt(2 * PI);
      if(CentralityIntegral[i] > MaxCentralityIntegral)
         MaxCentralityIntegral = CentralityIntegral[i];
   }

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
   PFTreeMessenger MPF(InputFile);
   SkimTreeMessenger MSkim(InputFile);
   TriggerTreeMessenger MHLT(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TTree OutputTree("OutputTree", "OutputTree");

   bool PassFilter, PassHLT;
   OutputTree.Branch("PassFilter", &PassFilter, "PassFilter/O");
   OutputTree.Branch("PassHLT", &PassHLT, "PassHLT/O");

   double TreeJetPT, TreeJetEta, TreeJetPhi, TreeJetSDMass, TreeJetDR, TreeJetMass;
   double TreeNewJetPT, TreeNewJetEta, TreeNewJetPhi, TreeNewJetSDMass, TreeNewJetDR, TreeNewJetZG, TreeNewJetMass, TreeNewJetSDPT;
   double TreeFirstJetPT, TreeFirstJetEta, TreeFirstJetPhi, TreeFirstJetSDMass, TreeFirstJetDR, TreeFirstJetZG, TreeFirstJetMass, TreeFirstJetSDPT;
   double TreeBestJetPT, TreeBestJetEta, TreeBestJetPhi, TreeBestJetSDMass, TreeBestJetDR, TreeBestJetZG, TreeBestJetMass, TreeBestJetSDPT;
   double TreeNewJetSDMass2, TreeNewJetDR2, TreeNewJetZG2, TreeNewJetSDPT2;
   double TreeFirstJetSDMass2, TreeFirstJetDR2, TreeFirstJetZG2, TreeFirstJetSDPT2;
   double TreeBestJetSDMass2, TreeBestJetDR2, TreeBestJetZG2, TreeBestJetSDPT2;
   double TreeNewJetSDMass3, TreeNewJetDR3, TreeNewJetZG3, TreeNewJetSDPT3;
   double TreeFirstJetSDMass3, TreeFirstJetDR3, TreeFirstJetZG3, TreeFirstJetSDPT3;
   double TreeBestJetSDMass3, TreeBestJetDR3, TreeBestJetZG3, TreeBestJetSDPT3;
   double TreeTotalPT, TreeRho, TreeTotalPTInJet, TreeTotalStuffInJet;
   double TreePTHat, TreeCentrality;
   OutputTree.Branch("JetPT",          &TreeJetPT,          "JetPT/D");
   OutputTree.Branch("JetEta",         &TreeJetEta,         "JetEta/D");
   OutputTree.Branch("JetPhi",         &TreeJetPhi,         "JetPhi/D");
   OutputTree.Branch("JetSDMass",      &TreeJetSDMass,      "JetSDMass/D");
   OutputTree.Branch("JetDR",          &TreeJetDR,          "JetDR/D");
   OutputTree.Branch("JetMass",        &TreeJetMass,        "JetMass/D");
   OutputTree.Branch("NewJetPT",       &TreeNewJetPT,       "NewJetPT/D");
   OutputTree.Branch("NewJetEta",      &TreeNewJetEta,      "NewJetEta/D");
   OutputTree.Branch("NewJetPhi",      &TreeNewJetPhi,      "NewJetPhi/D");
   OutputTree.Branch("NewJetSDMass",   &TreeNewJetSDMass,   "NewJetSDMass/D");
   OutputTree.Branch("NewJetDR",       &TreeNewJetDR,       "NewJetDR/D");
   OutputTree.Branch("NewJetZG",       &TreeNewJetZG,       "NewJetZG/D");
   OutputTree.Branch("NewJetMass",     &TreeNewJetMass,     "NewJetMass/D");
   OutputTree.Branch("NewJetSDPT",     &TreeNewJetSDPT,     "NewJetSDPT/D");
   OutputTree.Branch("FirstJetPT",      &TreeFirstJetPT,      "FirstJetPT/D");
   OutputTree.Branch("FirstJetEta",     &TreeFirstJetEta,     "FirstJetEta/D");
   OutputTree.Branch("FirstJetPhi",     &TreeFirstJetPhi,     "FirstJetPhi/D");
   OutputTree.Branch("FirstJetSDMass",  &TreeFirstJetSDMass,  "FirstJetSDMass/D");
   OutputTree.Branch("FirstJetDR",      &TreeFirstJetDR,      "FirstJetDR/D");
   OutputTree.Branch("FirstJetZG",      &TreeFirstJetZG,      "FirstJetZG/D");
   OutputTree.Branch("FirstJetMass",    &TreeFirstJetMass,    "FirstJetMass/D");
   OutputTree.Branch("FirstJetSDPT",    &TreeFirstJetSDPT,    "FirstJetSDPT/D");
   OutputTree.Branch("BestJetPT",      &TreeBestJetPT,      "BestJetPT/D");
   OutputTree.Branch("BestJetEta",     &TreeBestJetEta,     "BestJetEta/D");
   OutputTree.Branch("BestJetPhi",     &TreeBestJetPhi,     "BestJetPhi/D");
   OutputTree.Branch("BestJetSDMass",  &TreeBestJetSDMass,  "BestJetSDMass/D");
   OutputTree.Branch("BestJetDR",      &TreeBestJetDR,      "BestJetDR/D");
   OutputTree.Branch("BestJetZG",      &TreeBestJetZG,      "BestJetZG/D");
   OutputTree.Branch("BestJetMass",    &TreeBestJetMass,    "BestJetMass/D");
   OutputTree.Branch("BestJetSDPT",    &TreeBestJetSDPT,    "BestJetSDPT/D");
   OutputTree.Branch("NewJetSDMass2",  &TreeNewJetSDMass2,  "NewJetSDMass2/D");
   OutputTree.Branch("NewJetDR2",      &TreeNewJetDR2,      "NewJetDR2/D");
   OutputTree.Branch("NewJetZG2",      &TreeNewJetZG2,      "NewJetZG2/D");
   OutputTree.Branch("NewJetSDPT2",    &TreeNewJetSDPT2,    "NewJetSDPT2/D");
   OutputTree.Branch("FirstJetSDMass2", &TreeFirstJetSDMass2, "FirstJetSDMass2/D");
   OutputTree.Branch("FirstJetDR2",     &TreeFirstJetDR2,     "FirstJetDR2/D");
   OutputTree.Branch("FirstJetZG2",     &TreeFirstJetZG2,     "FirstJetZG2/D");
   OutputTree.Branch("FirstJetSDPT2",   &TreeFirstJetSDPT2,   "FirstJetSDPT2/D");
   OutputTree.Branch("BestJetSDMass2", &TreeBestJetSDMass2, "BestJetSDMass2/D");
   OutputTree.Branch("BestJetDR2",     &TreeBestJetDR2,     "BestJetDR2/D");
   OutputTree.Branch("BestJetZG2",     &TreeBestJetZG2,     "BestJetZG2/D");
   OutputTree.Branch("BestJetSDPT2",   &TreeBestJetSDPT2,   "BestJetSDPT2/D");
   OutputTree.Branch("NewJetSDMass3",  &TreeNewJetSDMass3,  "NewJetSDMass3/D");
   OutputTree.Branch("NewJetDR3",      &TreeNewJetDR3,      "NewJetDR3/D");
   OutputTree.Branch("NewJetZG3",      &TreeNewJetZG3,      "NewJetZG3/D");
   OutputTree.Branch("NewJetSDPT3",    &TreeNewJetSDPT3,    "NewJetSDPT3/D");
   OutputTree.Branch("FirstJetSDMass3", &TreeFirstJetSDMass3, "FirstJetSDMass3/D");
   OutputTree.Branch("FirstJetDR3",     &TreeFirstJetDR3,     "FirstJetDR3/D");
   OutputTree.Branch("FirstJetZG3",     &TreeFirstJetZG3,     "FirstJetZG3/D");
   OutputTree.Branch("FirstJetSDPT3",   &TreeFirstJetSDPT3,   "FirstJetSDPT3/D");
   OutputTree.Branch("BestJetSDMass3", &TreeBestJetSDMass3, "BestJetSDMass3/D");
   OutputTree.Branch("BestJetDR3",     &TreeBestJetDR3,     "BestJetDR3/D");
   OutputTree.Branch("BestJetZG3",     &TreeBestJetZG3,     "BestJetZG3/D");
   OutputTree.Branch("BestJetSDPT3",   &TreeBestJetSDPT3,   "BestJetSDPT3/D");
   OutputTree.Branch("TotalPT",        &TreeTotalPT,        "TotalPT/D");
   OutputTree.Branch("Rho",            &TreeRho,            "Rho/D");
   OutputTree.Branch("TotalPTInJet",   &TreeTotalPTInJet,   "TotalPTInJet/D");
   OutputTree.Branch("TotalStuffInJet",&TreeTotalStuffInJet,"TotalStuffInJet/D");
   OutputTree.Branch("PTHat",          &TreePTHat,          "PTHat/D");
   OutputTree.Branch("Centrality",     &TreeCentrality,     "Centrality/D");

   TH1D HN("HN", "Raw event count", 1, 0, 1);
   TH1D HPTHatAll("HPTHatAll", "PTHat", 100, 0, 500);
   TH1D HPTHatSelected("HPTHatSelected", "PTHat", 100, 0, 500);

   TH1D HRho("HRho", "Rho distribution", 100, 0, 400);
   TH1D HPTAdded("HPTAdded", "PT of added particles", 100, 0, 20);

   TH2D HJetPTComparison("HJetPTComparison", ";Jet PT;New Jet PT", 100, 0, 400, 100, 0, 400);
   TH2D HSDMassComparison("HSDMassComparison", ";Jet SD Mass;New Jet SD Mass", 100, 0, 100, 100, 0, 100);
   TH2D HRecoDRComparison("HRecoDRComparison", ";Jet Reco DR;New Jet Reco DR", 100, 0, 0.4, 100, 0, 0.4);

   TH2D HSDMassJetPT("HSDMassJetPT", ";Jet PT;SD Mass", 100, 80, 500, 100, 0, 100);
   TH2D HNewSDMassNewJetPT("HNewSDMassNewJetPT", ";New Jet PT;New SD Mass", 100, 0, 600, 100, 0, 100);

   TH1D HSDMass("HSDMass", "SD Mass, DR > 0.1;SD Mass", 100, 0, 100);
   TH1D HNewSDMass("HNewSDMass", "New SD Mass, New DR > 0.1; New SD Mass", 100, 0, 100);

   int EntryCount = MHiEvent.Tree->GetEntries() * 0.2;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(1);

   // pair<double, pair<int, int>> *Distances = new pair<double, pair<int, int>>[MAXSIZE];

   for(int iEntry = 0, ReuseCount = 1; iEntry < EntryCount; ReuseCount++)
   {
      if(EntryCount <= 250 || iEntry % (EntryCount / 300) == 0)
      {
         Bar.Update(iEntry);
         Bar.Print();
      }

      if(ReuseRate <= 1 || ReuseCount % ReuseRate == 0)
         iEntry = iEntry + 1;
      if(Mod >= 0 && Mod < ModBase && iEntry % ModBase != Mod)
         continue;

      HN.Fill(0);

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);
      MPF.GetEntry(iEntry);
      MHLT.GetEntry(iEntry);
      MSkim.GetEntry(iEntry);

      PassFilter = true;
      PassHLT = true;
      if(IsData == true)
      {
         if(MSkim.PassBasicFilter() == false)
            PassFilter = false;
         if(MHLT.CheckTrigger("HLT_AK4PFJet80_Eta5p1_v1") == false)
            PassHLT = false;
      }

      SDJetHelper HSDJet(MSDJet);

      HPTHatAll.Fill(MSDJet.PTHat);
      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;
      TreePTHat = MSDJet.PTHat;

      HPTHatSelected.Fill(MSDJet.PTHat);

      for(int iJ = 0; iJ < MJet.JetCount; iJ++)
      {
         if(MJet.JetEta[iJ] < -1.5 || MJet.JetEta[iJ] > 1.5)
            continue;
         if(MJet.JetPT[iJ] < 10)
            continue;

         FourVector JetP;
         JetP.SetPtEtaPhi(MJet.JetPT[iJ], MJet.JetEta[iJ], MJet.JetPhi[iJ]);

         TreeJetPT = MJet.JetPT[iJ];
         TreeJetEta = MJet.JetEta[iJ];
         TreeJetPhi = MJet.JetPhi[iJ];

         int SDIndex = -1;
         double SDDR2 = -1;
         for(int i = 0; i < MSDJet.JetCount; i++)
         {
            double DR2 = GetDR2(MJet.JetEta[iJ], MJet.JetPhi[iJ], MSDJet.JetEta[i], MSDJet.JetPhi[i]);
            if(SDDR2 < 0 || SDDR2 > DR2)
            {
               SDIndex = i;
               SDDR2 = DR2;
            }
         }

         TreeJetDR = HSDJet.RecoSubJetDR[SDIndex];
         TreeJetSDMass = MSDJet.JetM[SDIndex];

         // Step 0 - get inputs ready
         double Rho = 300;

         int Centrality = 0;
         bool CentralityDone = false;
         while(CentralityDone == false)
         {
            Centrality = int(DrawRandom(0, 80));
            if(DrawRandom(0, 1) < CentralityIntegral[Centrality] / MaxCentralityIntegral)
               CentralityDone = true;
         }

         do
         {
            Rho = DrawGaussian(CentralityB[Centrality], CentralityC[Centrality]) * RhoMultiplier;
         } while(Rho < 0);

         TreeRho = Rho;
         TreeCentrality = Centrality;

         HRho.Fill(Rho);

         // Step 1 - get all PF candidates within range
         vector<PseudoJet> Candidates;
         FourVector TotalStuffInJet;
         for(int i = 0; i < MPF.ID->size(); i++)
         {
            FourVector P;
            P.SetPtEtaPhi((*MPF.PT)[i], (*MPF.Eta)[i], (*MPF.Phi)[i]);
            if(GetDR(P, JetP) < Range)
               Candidates.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
            if(GetDR(P, JetP) < 0.4)
               TotalStuffInJet = TotalStuffInJet + P;
         }
         TreeTotalStuffInJet = TotalStuffInJet.GetPT();

         // Step 2 - sprinkle underlying event contribution
         double TotalPT = Rho * Range * Range * PI * DrawGaussian(1, Smear);
         TreeTotalPT = TotalPT;
         double TotalPTInJet = 0;
         while(TotalPT > 0)
         {
            double DEta = 0;
            double DPhi = 0;

            do
            {
               DEta = DrawRandom(-Range, Range);
               DPhi = DrawRandom(-Range, Range);
            } while(DEta * DEta + DPhi * DPhi > Range * Range);

            double PT = GetPFPT(MJet.JetEta[iJ] + DEta, Rho, DHFile, PTType) * MBMultiplier;
            if(PT >= TotalPT)
               PT = TotalPT;
            TotalPT = TotalPT - PT;
            HPTAdded.Fill(PT);

            FourVector P;
            P.SetPtEtaPhi(PT, MJet.JetEta[iJ] + DEta, MJet.JetPhi[iJ] + DPhi);
            Candidates.push_back(PseudoJet(P[1], P[2], P[3], P[0]));

            if(GetDR(P.GetEta(), P.GetPhi(), MJet.JetEta[iJ], MJet.JetPhi[iJ]) < 0.4)
               TotalPTInJet = TotalPTInJet + P.GetPT();
         }
         TreeTotalPTInJet = TotalPTInJet;

         // Step 3 - do pileup subtraction algorithm - via fastjet
         JetDefinition Definition(antikt_algorithm, 0.4);
         double GhostArea = GhostDistance * GhostDistance;
         AreaDefinition AreaDef(active_area_explicit_ghosts, GhostedAreaSpec(6.0, 1, GhostArea));
         ClusterSequenceArea Sequence(Candidates, Definition, AreaDef);
         vector<PseudoJet> JetsWithGhosts = Sequence.inclusive_jets();

         vector<PseudoJet> CSJets(JetsWithGhosts.size());
         for(int i = 0; i < (int)JetsWithGhosts.size(); i++)
         {
            contrib::ConstituentSubtractor Subtractor(Rho);
            Subtractor.set_alpha(1);  // optional
            // subtractor.set_max_deltaR(2);  // optional
            CSJets[i] = Subtractor(JetsWithGhosts[i]);
         }

         int ClosestCSJet = 0;
         double ClosestCSDR2 = -1;
         for(int i = 0; i < (int)CSJets.size(); i++)
         {
            double DR2 = GetDR2(CSJets[i].eta(), CSJets[i].phi(), MJet.JetEta[iJ], MJet.JetPhi[iJ]);
            if(ClosestCSDR2 < 0 || ClosestCSDR2 > DR2)
            {
               ClosestCSJet = i;
               ClosestCSDR2 = DR2;
            }
         }

         int MaxCSJet = 0;
         for(int i = 0; i < (int)CSJets.size(); i++)
         {
            // cout << "CS Jet " << CSJets[i].perp() << " " << CSJets[i].eta() << " " << CSJets[i].phi() << endl;
            if(CSJets[i].perp() > CSJets[MaxCSJet].perp())
               MaxCSJet = i;
         }

         // Step 4 - Clustering and pick the jets
         vector<PseudoJet> CSCandidates;
         for(int i = 0; i < (int)CSJets.size(); i++)
         {
            vector<PseudoJet> Constituents = CSJets[i].constituents();
            CSCandidates.insert(CSCandidates.end(), Constituents.begin(), Constituents.end());
         }
         ClusterSequence NewSequence(CSCandidates, Definition);
         vector<PseudoJet> SDJets = NewSequence.inclusive_jets();

         if(SDJets.size() == 0)   // Huh?
            continue;

         int LeadingIndex = 0;
         for(int i = 0; i < (int)SDJets.size(); i++)
            if(SDJets[i].perp() > SDJets[LeadingIndex].perp())
               LeadingIndex = i;

         int ClosestIndex = 0;
         double ClosestDR2 = -1;
         for(int i = 0; i < (int)SDJets.size(); i++)
         {
            double DR2 = GetDR2(SDJets[i].eta(), SDJets[i].phi(), MJet.JetEta[iJ], MJet.JetPhi[iJ]);
            if(ClosestDR2 < 0 || ClosestDR2 > DR2)
            {
               ClosestIndex = i;
               ClosestDR2 = DR2;
            }
         }

         PseudoJet &Jet = SDJets[LeadingIndex];
         FourVector NewJetP(Jet.e(), Jet.px(), Jet.py(), Jet.pz());
         Jet = CSJets[ClosestCSJet];
         FourVector FirstJetP(Jet.e(), Jet.px(), Jet.py(), Jet.pz());
         Jet = SDJets[ClosestIndex];
         FourVector BestJetP(Jet.e(), Jet.px(), Jet.py(), Jet.pz());

         vector<FourVector> GoodCandidates, GoodCandidatesBest, GoodCandidatesFirst;

         vector<PseudoJet> Constituents = SDJets[LeadingIndex].constituents();
         for(int i = 0; i < (int)Constituents.size(); i++)
         {
            FourVector P;
            P[0] = Constituents[i].e();
            P[1] = Constituents[i].px();
            P[2] = Constituents[i].py();
            P[3] = Constituents[i].pz();
            GoodCandidates.push_back(P);
         }
         Constituents = CSJets[ClosestCSJet].constituents();
         for(int i = 0; i < (int)Constituents.size(); i++)
         {
            FourVector P;
            P[0] = Constituents[i].e();
            P[1] = Constituents[i].px();
            P[2] = Constituents[i].py();
            P[3] = Constituents[i].pz();
            GoodCandidatesFirst.push_back(P);
         }
         Constituents = SDJets[ClosestIndex].constituents();
         for(int i = 0; i < (int)Constituents.size(); i++)
         {
            FourVector P;
            P[0] = Constituents[i].e();
            P[1] = Constituents[i].px();
            P[2] = Constituents[i].py();
            P[3] = Constituents[i].pz();
            GoodCandidatesBest.push_back(P);
         }

         // cout << GoodCandidates.size() << " " << GoodCandidatesBest.size() << endl;

         HJetPTComparison.Fill(MJet.JetPT[iJ], NewJetP.GetPT());

         if(GoodCandidates.size() == 0 && GoodCandidatesBest.size() == 0 && GoodCandidatesFirst.size() == 0)
         {
            TreeNewJetPT = -1;
            TreeFirstJetPT = -1;
            TreeBestJetPT = -1;
            OutputTree.Fill();
            continue;
         }

         // Step 5 - Run SD algorithm on the subtracted candidates
         vector<Node *> Nodes;
         for(int i = 0; i < (int)GoodCandidates.size(); i++)
            Nodes.push_back(new Node(GoodCandidates[i]));
         vector<Node *> NodesFirst;
         for(int i = 0; i < (int)GoodCandidatesFirst.size(); i++)
            NodesFirst.push_back(new Node(GoodCandidatesFirst[i]));
         vector<Node *> NodesBest;
         for(int i = 0; i < (int)GoodCandidatesBest.size(); i++)
            NodesBest.push_back(new Node(GoodCandidatesBest[i]));

         BuildCATree(Nodes);
         BuildCATree(NodesFirst);
         BuildCATree(NodesBest);
         Node *Groomed = FindSDNode(Nodes[0]);
         Node *GroomedFirst = FindSDNode(NodesFirst[0]);
         Node *GroomedBest = FindSDNode(NodesBest[0]);
         Node *Groomed2 = FindSDNode(Nodes[0], 0.5, 1.5);
         Node *GroomedFirst2 = FindSDNode(NodesFirst[0], 0.5, 1.5);
         Node *GroomedBest2 = FindSDNode(NodesBest[0], 0.5, 1.5);
         Node *Groomed3 = FindSDNode(Nodes[0], 0.3, 1.5);
         Node *GroomedFirst3 = FindSDNode(NodesFirst[0], 0.3, 1.5);
         Node *GroomedBest3 = FindSDNode(NodesBest[0], 0.3, 1.5);

         if(Groomed->N > 1)
         {
            HSDMassComparison.Fill(MSDJet.JetM[SDIndex], Groomed->P.GetMass());
            HRecoDRComparison.Fill(HSDJet.RecoSubJetDR[SDIndex],
               GetDR(Groomed->Child1->P, Groomed->Child2->P));

            HSDMassJetPT.Fill(MSDJet.JetPT[SDIndex], MSDJet.JetM[SDIndex]);
            HNewSDMassNewJetPT.Fill(NewJetP.GetPT(), Groomed->P.GetMass());
         }

         if(HSDJet.RecoSubJetDR[SDIndex] > 0.1 && MSDJet.JetPT[SDIndex] > 120)
            HSDMass.Fill(MSDJet.JetM[SDIndex]);
         if(Groomed->N > 1 && GetDR(Groomed->Child1->P, Groomed->Child2->P) > 0.1
            && NewJetP.GetPT() > 120)
            HNewSDMass.Fill(Groomed->P.GetMass());

         TreeNewJetPT = NewJetP.GetPT();
         TreeNewJetEta = NewJetP.GetEta();
         TreeNewJetPhi = NewJetP.GetPhi();
         TreeNewJetSDMass = Groomed->P.GetMass();
         TreeNewJetSDMass2 = Groomed2->P.GetMass();
         TreeNewJetSDMass3 = Groomed3->P.GetMass();
         TreeNewJetSDPT = Groomed->P.GetPT();
         TreeNewJetSDPT2 = Groomed2->P.GetPT();
         TreeNewJetSDPT3 = Groomed3->P.GetPT();
         if(Groomed->N > 1)
         {
            FourVector P1 = Groomed->Child1->P;
            FourVector P2 = Groomed->Child2->P;
            TreeNewJetDR = GetDR(P1, P2);
            TreeNewJetZG = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeNewJetDR = -1, TreeNewJetZG = 1;
         if(Groomed2->N > 1)
         {
            FourVector P1 = Groomed2->Child1->P;
            FourVector P2 = Groomed2->Child2->P;
            TreeNewJetDR2 = GetDR(P1, P2);
            TreeNewJetZG2 = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeNewJetDR2 = -1, TreeNewJetZG2 = -1;
         if(Groomed3->N > 1)
         {
            FourVector P1 = Groomed3->Child1->P;
            FourVector P2 = Groomed3->Child2->P;
            TreeNewJetDR3 = GetDR(P1, P2);
            TreeNewJetZG3 = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeNewJetDR3 = -1, TreeNewJetZG3 = -1;

         TreeBestJetPT = BestJetP.GetPT();
         TreeBestJetEta = BestJetP.GetEta();
         TreeBestJetPhi = BestJetP.GetPhi();
         TreeBestJetSDMass = GroomedBest->P.GetMass();
         TreeBestJetSDMass2 = GroomedBest2->P.GetMass();
         TreeBestJetSDMass3 = GroomedBest3->P.GetMass();
         TreeBestJetSDPT = GroomedBest->P.GetPT();
         TreeBestJetSDPT2 = GroomedBest2->P.GetPT();
         TreeBestJetSDPT3 = GroomedBest3->P.GetPT();
         if(GroomedBest->N > 1)
         {
            FourVector P1 = GroomedBest->Child1->P;
            FourVector P2 = GroomedBest->Child2->P;
            TreeBestJetDR = GetDR(P1, P2);
            TreeBestJetZG = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeBestJetDR = -1, TreeBestJetZG = -1;
         if(GroomedBest2->N > 1)
         {
            FourVector P1 = GroomedBest2->Child1->P;
            FourVector P2 = GroomedBest2->Child2->P;
            TreeBestJetDR2 = GetDR(P1, P2);
            TreeBestJetZG2 = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeBestJetDR2 = -1, TreeBestJetZG2 = -1;
         if(GroomedBest3->N > 1)
         {
            FourVector P1 = GroomedBest3->Child1->P;
            FourVector P2 = GroomedBest3->Child2->P;
            TreeBestJetDR3 = GetDR(P1, P2);
            TreeBestJetZG3 = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeBestJetDR3 = -1, TreeBestJetZG3 = -1;

         // cout << "Best " << BestJetP << endl;
         // cout << TreeBestJetDR << " " << TreeBestJetSDMass << endl;

         TreeFirstJetPT = FirstJetP.GetPT();
         TreeFirstJetEta = FirstJetP.GetEta();
         TreeFirstJetPhi = FirstJetP.GetPhi();
         TreeFirstJetSDMass = GroomedFirst->P.GetMass();
         TreeFirstJetSDMass2 = GroomedFirst2->P.GetMass();
         TreeFirstJetSDMass3 = GroomedFirst3->P.GetMass();
         TreeFirstJetSDPT = GroomedFirst->P.GetPT();
         TreeFirstJetSDPT2 = GroomedFirst2->P.GetPT();
         TreeFirstJetSDPT3 = GroomedFirst3->P.GetPT();
         if(GroomedFirst->N > 1)
         {
            FourVector P1 = GroomedFirst->Child1->P;
            FourVector P2 = GroomedFirst->Child2->P;
            TreeFirstJetDR = GetDR(P1, P2);
            TreeFirstJetZG = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeFirstJetDR = -1, TreeFirstJetZG = -1;
         if(GroomedFirst2->N > 1)
         {
            FourVector P1 = GroomedFirst2->Child1->P;
            FourVector P2 = GroomedFirst2->Child2->P;
            TreeFirstJetDR2 = GetDR(P1, P2);
            TreeFirstJetZG2 = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeFirstJetDR2 = -1, TreeFirstJetZG2 = -1;
         if(GroomedFirst3->N > 1)
         {
            FourVector P1 = GroomedFirst3->Child1->P;
            FourVector P2 = GroomedFirst3->Child2->P;
            TreeFirstJetDR3 = GetDR(P1, P2);
            TreeFirstJetZG3 = min(P1.GetPT(), P2.GetPT()) / (P1.GetPT() + P2.GetPT());
         }
         else
            TreeFirstJetDR3 = -1, TreeFirstJetZG3 = -1;
         
         // cout << TreeFirstJetDR << " " << TreeFirstJetSDMass << endl;

         // Cleanup
         if(Nodes.size() > 0)
            delete Nodes[0];
         if(NodesFirst.size() > 0)
            delete NodesFirst[0];
         if(NodesBest.size() > 0)
            delete NodesBest[0];

         OutputTree.Fill();
      }
   }

   // delete[] Distances;

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();

   HN.Write();
   HPTHatAll.Write();
   HPTHatSelected.Write();

   HRho.Write();
   HPTAdded.Write();

   HJetPTComparison.Write();
   HSDMassComparison.Write();
   HRecoDRComparison.Write();

   HSDMassJetPT.Write();
   HNewSDMassNewJetPT.Write();

   HSDMass.Write();
   HNewSDMass.Write();

   OutputFile.Close();

   InputFile.Close();
}

double GetPFPT(double Eta, double Rho, DataHelper &DHFile, int PTType)
{
   if(PTType == PTType_MB)
      return GetPT(Eta, Rho, DHFile);
   if(PTType == PTType_Hard)
      return GetPT(Eta, Rho, DHFile) * 1.2;
   if(PTType == PTType_Soft)
      return GetPT(Eta, Rho, DHFile) * 0.8;
   if(PTType == PTType_Data)
      return GetModifiedPTData(Eta, Rho, DHFile);
   if(PTType == PTType_Half)
   {
      if(DrawRandom(0, 1) < 0.5)
         return GetModifiedPTData(Eta, Rho, DHFile);
      else
         return GetPT(Eta, Rho, DHFile);
   }
   if(PTType == PTType_DataData)
      return GetModifiedPTDataData(Eta, Rho, DHFile);
   if(PTType == PTType_MC)
      return GetModifiedPT2(Eta, Rho, DHFile);

   return 10000;
}

double GetModifiedPT(double Eta, double Rho, DataHelper &DHFile, int PTType)
{
   double P[7] = {0};

   P[0] = 0.9749;
   P[1] = 0.7382;
   P[2] = -0.8869;
   P[3] = 0.3503;
   P[4] = -0.05973;
   P[5] = 0.004686;
   P[6] = -0.0001403;

   bool Good = false;

   double PT = 0;

   do
   {
      PT = GetPT(Eta, Rho, DHFile);

      double Factor = PT;
      if(PT < 1)
         Factor = PT;
      else if(PT < 10)
         Factor = P[0] + P[1] * PT + P[2] * PT * PT + P[3] * PT * PT * PT + P[4] * PT * PT * PT * PT + P[5] * PT * PT * PT * PT * PT + P[6] * PT * PT * PT * PT * PT * PT;
      else
         Factor = 1;
      Factor = Factor / 2;

      if(DrawRandom(0, 1) < Factor)
         Good = true;
   } while(Good == false);

   return PT;
}

double GetPT(double Eta, double Rho, DataHelper &DHFile)
{
   int EtaBin = GetEtaBin(Eta);
   int RhoBin = GetRhoBin(Rho);

   double M1 = EvaluateWithCache(EtaBin, RhoBin, 2, DHFile) / PresampleFactor(2);
   double M2 = EvaluateWithCache(EtaBin, RhoBin, 3, DHFile) / PresampleFactor(3);
   double M3 = EvaluateWithCache(EtaBin, RhoBin, 4, DHFile) / PresampleFactor(4);

   double Max = M1;
   if(Max < M2)
      Max = M2;
   if(Max < M3)
      Max = M3;

   Max = Max * 1.2;

   bool Accepted = false;
   double PT = 0;

   while(Accepted == false)
   {
      PT = GetPresample();

      double Height = EvaluateWithCache(EtaBin, RhoBin, PT, DHFile) / PresampleFactor(PT);

      if(DrawRandom(0, 1) < Height / Max)
         Accepted = true;
   }

   return PT;
}

double GetModifiedPT2(double Eta, double Rho, DataHelper &DHFile)
{
   double P[9] = {0};

   P[0] = 1.572;
   P[1] = 0.7239;
   P[2] = 2.475;
   P[3] = 1.541;
   P[4] = -0.3508;
   P[5] = 8.22;
   P[6] = -25.75;
   P[7] = 33.55;
   P[8] = -14.63;

   bool Good = false;

   double PT = 0;

   do
   {
      PT = GetPT(Eta, Rho, DHFile);

      double Factor = 1;

      if(PT < 1)
         Factor = P[4] + P[5] * PT + P[6] * PT * PT + P[7] * PT * PT * PT + P[8] * PT * PT * PT * PT;
      else
         Factor = P[0] - P[1] * exp(-(PT - P[2]) * (PT - P[2]) / (2 * P[3] * P[3]));

      Factor = Factor / P[0];

      if(DrawRandom(0, 1) < Factor)
         Good = true;
   } while(Good == false);

   return PT;
}

double GetModifiedPTData(double Eta, double Rho, DataHelper &DHFile)
{
   double P[4] = {0};

   P[0] = 0.9442;
   P[1] = 0.7242;
   P[2] = 1.85;
   P[3] = 0.9561;

   bool Good = false;

   double PT = 0;

   do
   {
      PT = GetPT(Eta, Rho, DHFile);

      double Factor = 1;

      if(PT < 1)
         Factor = PT * P[0];
      else
         Factor = 1.57 - P[1] * exp(-(PT - P[2]) * (PT - P[2]) / (2 * P[3] * P[3]));

      Factor = Factor / 1.57;

      if(DrawRandom(0, 1) < Factor)
         Good = true;
   } while(Good == false);

   return PT;
}

double GetModifiedPTDataData(double Eta, double Rho, DataHelper &DHFile)
{
   double P[4] = {0};

   P[0] = 0.9442;
   P[1] = 0.7242;
   P[2] = 1.85;
   P[3] = 0.9561;

   bool Good = false;

   double PT = 0;

   do
   {
      PT = GetPT(Eta, Rho, DHFile);

      double Factor = 1;

      if(PT < 1)
         Factor = PT * P[0];
      else
         Factor = 1.57 - P[1] * exp(-(PT - P[2]) * (PT - P[2]) / (2 * P[3] * P[3]));

      Factor = Factor / 1.57;

      if(DrawRandom(0, 1) < Factor * Factor)
         Good = true;
   } while(Good == false);

   return PT;
}

double GetModifiedPTData2(double Eta, double Rho, DataHelper &DHFile)
{
   double P[6] = {0};

   P[0] = 0.3202;
   P[1] = 0.9087;
   P[2] = 1.342;
   P[3] = 0.3497;
   P[4] = 1.916;
   P[5] = 0.8441;

   bool Good = false;

   double PT = 0;

   do
   {
      PT = GetPT(Eta, Rho, DHFile);

      double Factor = 1;

      if(PT < 1)
         Factor = P[0] + P[1] * PT;
      else
         Factor = P[2] - P[3] * exp(-(PT - P[4]) * (PT - P[4]) / (2 * P[5] * P[5]));

      Factor = Factor / P[2];

      if(DrawRandom(0, 1) < Factor)
         Good = true;
   } while(Good == false);

   return PT;
}

double GetPresample()
{
   double C1 = 0.5208333;   // Integral of first exp
   double C2 = 2.272385;    // Integral of second exp
   double Fraction = 0.005;

   if(DrawRandom(0, 1) < C1 / (C1 + Fraction * C2))
      return DrawExponential(-1.92, 0, 20);
   return DrawExponential(-0.44, 0, 20);
}

double PresampleFactor(double PT)
{
   return exp(-1.92 * PT) + 0.005 * exp(-0.44 * PT);
}

double Evaluate(double Eta, double Rho, double PT, DataHelper &DHFile)
{
   return Evaluate(PT, DHFile, FindState(Eta, Rho));
}

double Evaluate(double PT, DataHelper &DHFile, string State)
{
   double P1 = DHFile[State]["P1"].GetDouble();
   double P2 = DHFile[State]["P2"].GetDouble();
   double P3 = DHFile[State]["P3"].GetDouble();
   double P4 = DHFile[State]["P4"].GetDouble();
   double P5 = DHFile[State]["P5"].GetDouble();
   double P6 = DHFile[State]["P6"].GetDouble();
   double P7 = DHFile[State]["P7"].GetDouble();
   double P8 = DHFile[State]["P8"].GetDouble();
   double P9 = DHFile[State]["P9"].GetDouble();

   return max(tanh(P1 * (PT - P2)), 0.0)
      * (exp(-P3 * PT) + P4 * exp(-P5 * PT) + P6 * exp(-P7 * PT) + P8 * exp(-P9 * PT));
}

double EvaluateWithCache(int EtaBin, int RhoBin, double PT, DataHelper &DHFile)
{
   static bool First = true;
   static double P1[3][6];
   static double P2[3][6];
   static double P3[3][6];
   static double P4[3][6];
   static double P5[3][6];
   static double P6[3][6];
   static double P7[3][6];
   static double P8[3][6];
   static double P9[3][6];

   if(First == true)
   {
      First = false;

      double Etas[4] = {0.0, 0.5, 0.9, 1.3};
      double Rhos[7] = {0, 50, 100, 150, 200, 250, 350};

      for(int i = 0; i < 3; i++)
      {
         for(int j = 0; j < 6; j++)
         {
            double EtaMin = Etas[i];
            double EtaMax = Etas[i+1];
            double RhoMin = Rhos[j];
            double RhoMax = Rhos[j+1];
            string State = Form("SimpleFit_%.2f_%.2f_%.0f_%.0f", EtaMin, EtaMax, RhoMin, RhoMax);

            P1[i][j] = DHFile[State]["P1"].GetDouble();
            P2[i][j] = DHFile[State]["P2"].GetDouble();
            P3[i][j] = DHFile[State]["P3"].GetDouble();
            P4[i][j] = DHFile[State]["P4"].GetDouble();
            P5[i][j] = DHFile[State]["P5"].GetDouble();
            P6[i][j] = DHFile[State]["P6"].GetDouble();
            P7[i][j] = DHFile[State]["P7"].GetDouble();
            P8[i][j] = DHFile[State]["P8"].GetDouble();
            P9[i][j] = DHFile[State]["P9"].GetDouble();
         }
      }
   }

   return max(tanh(P1[EtaBin][RhoBin] * (PT - P2[EtaBin][RhoBin])), 0.0)
      * (exp(-P3[EtaBin][RhoBin] * PT) + P4[EtaBin][RhoBin] * exp(-P5[EtaBin][RhoBin] * PT) + P6[EtaBin][RhoBin] * exp(-P7[EtaBin][RhoBin] * PT) + P8[EtaBin][RhoBin] * exp(-P9[EtaBin][RhoBin] * PT));
}

double GetEtaMin(double Eta)
{
   if(Eta < 0)
      Eta = -Eta;

   if(Eta < 0.5)
      return 0.0;
   if(Eta < 0.9)
      return 0.5;
   return 0.9;
}

double GetEtaMax(double Eta)
{
   if(Eta < 0)
      Eta = -Eta;

   if(Eta < 0.5)
      return 0.5;
   if(Eta < 0.9)
      return 0.9;
   return 1.3;
}

int GetEtaBin(double Eta)
{
   if(Eta < 0)
      Eta = -Eta;

   if(Eta < 0.5)
      return 0;
   if(Eta < 0.9)
      return 1;
   return 2;
}

double GetRhoMin(double Rho)
{
   if(Rho < 50)
      return 0;
   if(Rho < 100)
      return 50;
   if(Rho < 150)
      return 100;
   if(Rho < 200)
      return 150;
   if(Rho < 250)
      return 200;
   return 250;
}

double GetRhoMax(double Rho)
{
   if(Rho < 50)
      return 50;
   if(Rho < 100)
      return 100;
   if(Rho < 150)
      return 150;
   if(Rho < 200)
      return 200;
   if(Rho < 250)
      return 250;
   return 350;
}

int GetRhoBin(double Rho)
{
   if(Rho < 50)
      return 0;
   if(Rho < 100)
      return 1;
   if(Rho < 150)
      return 2;
   if(Rho < 200)
      return 3;
   if(Rho < 250)
      return 4;
   return 5;
}

string FindState(double Eta, double Rho)
{
   double EtaMin = GetEtaMin(Eta);
   double EtaMax = GetEtaMax(Eta);
   double RhoMin = GetRhoMin(Rho);
   double RhoMax = GetRhoMax(Rho);
   string State = Form("SimpleFit_%.2f_%.2f_%.0f_%.0f", EtaMin, EtaMax, RhoMin, RhoMax);

   return State;
}


