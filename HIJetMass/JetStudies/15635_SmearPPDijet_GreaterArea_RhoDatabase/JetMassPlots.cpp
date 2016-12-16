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
using namespace fastjet;

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"
#include "ProgressBar.h"

#include "BasicUtilities.h"
#include "Messenger.h"
#include "SDJetHelper.h"
#include "CATree.h"
#include "DataHelper.h"

int main(int argc, char *argv[]);
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

   DataHelper DHFile("SimpleFitParameters.dh");

   DataHelper RhoDHFile("RhoDatabase.dh");
   string RhoTag = "AA6Dijet";
   double CentralityMin = 0;
   double CentralityMax = 10;

   double CentralityA[100] = {0};
   double CentralityB[100] = {0};
   double CentralityC[100] = {0};
   double CentralityIntegral[100] = {0};
   double MaxCentralityIntegral = 0;
   for(int i = 0; i < 100; i++)
   {
      CentralityA[i] = RhoDHFile[RhoTag][Form("C%02d_A")].GetDouble();
      CentralityB[i] = RhoDHFile[RhoTag][Form("C%02d_B")].GetDouble();
      CentralityC[i] = RhoDHFile[RhoTag][Form("C%02d_C")].GetDouble();
      CentralityIntegral[i] = CentralityA[i] * CentralityC[i] * sqrt(2 * PI);
      if(CentralityIntegral[i] > MaxCentralityIntegral)
         MaxCentralityIntegral = CentralityIntegral[i];
   }

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);

   if(IsData == true)
   {
      cerr << "I'd rather not run on data for this study" << endl;
      return -1;
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
   GenParticleTreeMessenger MGen(InputFile);
   PFTreeMessenger MPF(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TTree OutputTree("OutputTree", "OutputTree");

   double TreeJetPT, TreeJetEta, TreeJetPhi, TreeJetSDMass, TreeJetDR, TreeJetMass;
   double TreeNewJetPT, TreeNewJetEta, TreeNewJetPhi, TreeNewJetSDMass, TreeNewJetDR, TreeNewJetMass;
   OutputTree.Branch("JetPT",        &TreeJetPT,        "JetPT/D");
   OutputTree.Branch("JetEta",       &TreeJetEta,       "JetEta/D");
   OutputTree.Branch("JetPhi",       &TreeJetPhi,       "JetPhi/D");
   OutputTree.Branch("JetSDMass",    &TreeJetSDMass,    "JetSDMass/D");
   OutputTree.Branch("JetDR",        &TreeJetDR,        "JetDR/D");
   OutputTree.Branch("JetMass",      &TreeJetMass,      "JetMass/D");
   OutputTree.Branch("NewJetPT",     &TreeNewJetPT,     "NewJetPT/D");
   OutputTree.Branch("NewJetEta",    &TreeNewJetEta,    "NewJetEta/D");
   OutputTree.Branch("NewJetPhi",    &TreeNewJetPhi,    "NewJetPhi/D");
   OutputTree.Branch("NewJetSDMass", &TreeNewJetSDMass, "NewJetSDMass/D");
   OutputTree.Branch("NewJetDR",     &TreeNewJetDR,     "NewJetDR/D");
   OutputTree.Branch("NewJetMass",   &TreeNewJetMass,   "NewJetMass/D");

   TH1D HN("HN", "Raw event count", 1, 0, 1);
   TH1D HPTHatAll("HPTHatAll", "PTHat", 100, 0, 500);
   TH1D HPTHatSelected("HPTHatSelected", "PTHat", 100, 0, 500);

   TH1D HRho("HRho", "Rho distribution", 100, 0, 400);

   TH2D HJetPTComparison("HJetPTComparison", ";Jet PT;New Jet PT", 100, 0, 400, 100, 0, 400);
   TH2D HSDMassComparison("HSDMassComparison", ";Jet SD Mass;New Jet SD Mass", 100, 0, 100, 100, 0, 100);
   TH2D HRecoDRComparison("HRecoDRComparison", ";Jet Reco DR;New Jet Reco DR", 100, 0, 0.4, 100, 0, 0.4);

   TH2D HSDMassJetPT("HSDMassJetPT", ";Jet PT;SD Mass", 100, 80, 500, 100, 0, 100);
   TH2D HNewSDMassNewJetPT("HNewSDMassNewJetPT", ";New Jet PT;New SD Mass", 100, 0, 600, 100, 0, 100);

   TH1D HSDMass("HSDMass", "SD Mass, DR > 0.1;SD Mass", 100, 0, 100);
   TH1D HNewSDMass("HNewSDMass", "New SD Mass, New DR > 0.1; New SD Mass", 100, 0, 100);

   int EntryCount = MHiEvent.Tree->GetEntries() * 0.10;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(1);
         
   pair<double, pair<int, int> > *Distances = new pair<double, pair<int, int> >[5000000];

   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if(EntryCount <= 250 || iEntry % (EntryCount / 300) == 0)
      {
         Bar.Update(iEntry);
         Bar.Print();
      }

      HN.Fill(0);

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);
      MGen.GetEntry(iEntry);
      MPF.GetEntry(iEntry);
      
      SDJetHelper HSDJet(MSDJet);

      HPTHatAll.Fill(MSDJet.PTHat);
      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;

      HPTHatSelected.Fill(MSDJet.PTHat);

      for(int iJ = 0; iJ < MSDJet.JetCount; iJ++)
      {
         if(MSDJet.JetEta[iJ] < -1.3 || MSDJet.JetEta[iJ] > 1.3)
            continue;

         FourVector JetP;
         JetP.SetPtEtaPhi(MSDJet.JetPT[iJ], MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ]);

         TreeJetPT = MSDJet.JetPT[iJ];
         TreeJetEta = MSDJet.JetEta[iJ];
         TreeJetPhi = MSDJet.JetPhi[iJ];
         TreeJetDR = HSDJet.RecoSubJetDR[iJ];
         TreeJetSDMass = MSDJet.JetM[iJ];
   
         // Step 0 - get inputs ready
         double Rho = 300;
         double Range = 0.8;

         int Centrality = 0;
         bool CentralityDone = false;
         while(CentralityDone == false)
         {
            Centrality = int(DrawRandom(0, 10));
            if(DrawRandom(0, 1) < CentralityIntegral[Centrality] / MaxCentralityIntegral)
               CentralityDone = true;
         }
         Rho = DrawGaussian(CentralityB[Centrality], CentralityC[Centrality]);

         HRho.Fill(Rho);

         // Step 1 - get all PF candidates within range
         vector<FourVector> Candidates;
         for(int i = 0; i < MPF.ID->size(); i++)
         {
            FourVector P;
            P.SetPtEtaPhi((*MPF.PT)[i], (*MPF.Eta)[i], (*MPF.Phi)[i]);
            if(GetDR(P, JetP) < 0.4)
               Candidates.push_back(P);
         }

         // Step 2 - sprinkle underlying event contribution
         double TotalPT = Rho * Range * Range * PI;
         while(TotalPT > 0)
         {
            double DEta = 0;
            double DPhi = 0;

            do
            {
               DEta = DrawRandom(-Range, Range);
               DPhi = DrawRandom(-Range, Range);
            } while(DEta * DEta + DPhi * DPhi > Range * Range);

            double PT = GetPT(MSDJet.JetEta[iJ] + DEta, Rho, DHFile);
            if(PT >= TotalPT)
               PT = TotalPT;
            TotalPT = TotalPT - PT;

            FourVector P;
            P.SetPtEtaPhi(PT, MSDJet.JetEta[iJ] + DEta, MSDJet.JetPhi[iJ] + DPhi);
            Candidates.push_back(P);
         }
         
         // Step 3 - do pileup subtraction algorithm
         vector<FourVector> Ghosts;
         double Delta = 0.04;
         for(double Eta = -Range; Eta <= Range; Eta = Eta + Delta)
         {
            for(double Phi = -Range; Phi <= Range; Phi = Phi + Delta)
            {
               if(Eta * Eta + Phi * Phi > Range * Range)
                  continue;
               FourVector P;
               P.SetPtEtaPhi(1, MSDJet.JetEta[iJ] + Eta, MSDJet.JetPhi[iJ] + Phi);
               Ghosts.push_back(P);
            }
         }
         double GhostPT = Rho * Range * Range * PI / Ghosts.size();
         for(int i = 0; i < (int)Ghosts.size(); i++)
            Ghosts[i].SetPtEtaPhi(GhostPT, Ghosts[i].GetEta(), Ghosts[i].GetPhi());

         vector<bool> CandidatesAlive(Candidates.size());
         vector<bool> GhostsAlive(Ghosts.size());

         for(int i = 0; i < (int)Candidates.size(); i++)
            CandidatesAlive[i] = true;
         for(int i = 0; i < (int)Ghosts.size(); i++)
            GhostsAlive[i] = true;
         
         vector<double> CandidatesPT(Candidates.size());
         vector<double> CandidatesEta(Candidates.size());
         vector<double> CandidatesPhi(Candidates.size());

         for(int i = 0; i < (int)Candidates.size(); i++)
         {
            CandidatesPT[i] = Candidates[i].GetPT();
            CandidatesEta[i] = Candidates[i].GetEta();
            CandidatesPhi[i] = Candidates[i].GetPhi();
         }

         vector<double> GhostsPT(Ghosts.size());
         vector<double> GhostsEta(Ghosts.size());
         vector<double> GhostsPhi(Ghosts.size());
         
         for(int i = 0; i < (int)Ghosts.size(); i++)
         {
            GhostsPT[i] = Ghosts[i].GetPT();
            GhostsEta[i] = Ghosts[i].GetEta();
            GhostsPhi[i] = Ghosts[i].GetPhi();
         }

         int IndexCount = 0;
         for(int i = 0; i < (int)Candidates.size(); i++)
         {
            for(int j = 0; j < (int)Ghosts.size(); j++)
            {
               double DR = GetDR2(CandidatesEta[i], CandidatesPhi[i], GhostsEta[j], GhostsPhi[j]);
               Distances[IndexCount] = pair<double, pair<int, int> >(DR, pair<int, int>(i, j));
               IndexCount = IndexCount + 1;
               if(IndexCount > 5000000)
                  cerr << "Oh no!" << endl;
            }
         }

         sort(Distances, Distances + IndexCount);

         for(int i = 0; i < IndexCount; i++)
         {
            if(CandidatesAlive[Distances[i].second.first] == false)
               continue;
            if(GhostsAlive[Distances[i].second.second] == false)
               continue;

            double CPT = CandidatesPT[Distances[i].second.first];
            double GPT = GhostsPT[Distances[i].second.second];

            if(CPT > GPT)
            {
               CandidatesPT[Distances[i].second.first] = CPT - GPT;
               GhostsAlive[Distances[i].second.second] = false;
            }
            else
            {
               CandidatesAlive[Distances[i].second.first] = false;
               GhostsPT[Distances[i].second.second] = GPT - CPT;
            }
         }

         vector<FourVector> GoodCandidates;
         for(int i = 0; i < (int)Candidates.size(); i++)
         {
            if(CandidatesAlive[i] == true)
            {
               Candidates[i].SetPtEtaPhi(CandidatesPT[i], CandidatesEta[i], CandidatesPhi[i]);
               GoodCandidates.push_back(Candidates[i]);
            }
         }

         if(GoodCandidates.size() == 0)
            continue;

         FourVector AllP;
         for(int i = 0; i < (int)GoodCandidates.size(); i++)
            AllP = AllP + GoodCandidates[i];

         // Step 4 - Clustering!
         vector<PseudoJet> Particles;
         for(int i = 0; i < (int)GoodCandidates.size(); i++)
         {
            FourVector &P = GoodCandidates[i];
            Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
         }
         JetDefinition Definition(antikt_algorithm, 0.4);
         ClusterSequence Sequence(Particles, Definition);
         vector<PseudoJet> Jets = Sequence.inclusive_jets();

         int LeadingIndex = 0;
         for(int i = 0; i < (int)Jets.size(); i++)
            if(Jets[i].perp() > Jets[LeadingIndex].perp())
               LeadingIndex = i;

         PseudoJet &Jet = Jets[LeadingIndex];
         FourVector NewJetP(Jet.e(), Jet.px(), Jet.py(), Jet.pz());
         for(int i = 0; i < (int)GoodCandidates.size(); i++)
         {
            if(GetDR(GoodCandidates[i], NewJetP) > 0.4)
            {
               GoodCandidates.erase(GoodCandidates.begin() + i);
               i = i - 1;
            }
         }

         HJetPTComparison.Fill(MSDJet.JetPT[iJ], NewJetP.GetPT());

         if(GoodCandidates.size() == 0)
            continue;

         // Step 5 - Run SD algorithm on the subtracted candidates
         vector<Node *> Nodes;
         for(int i = 0; i < (int)GoodCandidates.size(); i++)
            Nodes.push_back(new Node(GoodCandidates[i]));

         BuildCATree(Nodes);
         Node *Groomed = FindSDNode(Nodes[0]);

         if(Groomed->N > 1)
         {
            HSDMassComparison.Fill(MSDJet.JetM[iJ], Groomed->P.GetMass());
            HRecoDRComparison.Fill(HSDJet.RecoSubJetDR[iJ],
               GetDR(Groomed->Child1->P, Groomed->Child2->P));

            HSDMassJetPT.Fill(MSDJet.JetPT[iJ], MSDJet.JetM[iJ]);
            HNewSDMassNewJetPT.Fill(NewJetP.GetPT(), Groomed->P.GetMass());
         }
            
         if(HSDJet.RecoSubJetDR[iJ] > 0.1 && MSDJet.JetPT[iJ] > 120)
            HSDMass.Fill(MSDJet.JetM[iJ]);
         if(Groomed->N > 1 && GetDR(Groomed->Child1->P, Groomed->Child2->P) > 0.1
            && NewJetP.GetPT() > 120)
            HNewSDMass.Fill(Groomed->P.GetMass());

         TreeNewJetPT = NewJetP.GetPT();
         TreeNewJetEta = NewJetP.GetEta();
         TreeNewJetPhi = NewJetP.GetPhi();
         TreeNewJetSDMass = Groomed->P.GetMass();
         if(Groomed->N > 1)
            TreeNewJetDR = GetDR(Groomed->Child1->P, Groomed->Child2->P);
         else
            TreeNewJetDR = -1;
         
         // Cleanup
         if(Nodes.size() > 0)
            delete Nodes[0];

         OutputTree.Fill();
      }
   }

   delete[] Distances;

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();

   HN.Write();
   HPTHatAll.Write();
   HPTHatSelected.Write();

   HRho.Write();

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


