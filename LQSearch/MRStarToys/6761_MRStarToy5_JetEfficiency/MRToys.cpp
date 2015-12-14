#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TTree.h"

#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "GenparticleTree.h"

int main(int argc, char *argv[]);
void DoToyAndAppendPlots(PsFileHelper &PsFile, const vector<double> &JetPT,
   const vector<double> &JetEfficiency, const double &LQMass, bool ApplyOnTwoJets, const string OutputFileName);
int FindChildIndex(GenParticleTree &Tree, int ChildPDGID, int ParentPDGID);
int TraceBHadron(GenParticleTree &Tree, int StartIndex);
bool HasB(int PDGID);
int FindClosestJet(vector<PseudoJet> &Jets, double Eta, double Phi);
double GetEfficiency(double PT, const vector<double> &JetPT, const vector<double> &JetEfficiency);

int main(int argc, char *argv[])
{
   gROOT->SetStyle("Plain");

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   PsFileHelper PsFile("MRStarToy5_ImplicationsOfBTaggingEfficiency.ps");
   PsFile.AddTextPage("Toys to understand MRStar better - part 5");

   vector<string> Explanations;
   Explanations.push_back("");
   PsFile.AddTextPage(Explanations);

   vector<double> FlatPT;
   vector<double> FlatEfficiency;

   FlatPT.push_back(30);
   FlatPT.push_back(1000);
   FlatEfficiency.push_back(1);
   FlatEfficiency.push_back(1);

   // PsFile.AddTextPage("100% Efficient");
   // DoToyAndAppendPlots(PsFile, FlatPT, FlatEfficiency, 400, false);

   FlatEfficiency[0] = 0.8;
   FlatEfficiency[1] = 0.8;

   PsFile.AddTextPage("Flat efficiency curve, but non-perfect.  One jet.");
   DoToyAndAppendPlots(PsFile, FlatPT, FlatEfficiency, 400, false, "FlatOneJet.root");

   PsFile.AddTextPage("Flat efficiency curve, but non-perfect.  Two jets");
   DoToyAndAppendPlots(PsFile, FlatPT, FlatEfficiency, 400, true, "FlatTwoJet.root");

   double TCHELPTTemp[] = {40, 60, 80, 100, 200, 300, 500, 1000};
   double TCHELEfficiencyTemp[] = {0.75, 0.825, 0.85, 0.87, 0.87, 0.82, 0.7, 0.4};
   double TCHELEfficiencyTempModerateDrop[] = {0.75, 0.825, 0.85, 0.87, 0.82, 0.77, 0.65, 0.3};
   double TCHELEfficiencyTempUp[] = {0.75, 0.825, 0.85, 0.87, 0.87, 0.87, 0.87, 0.87};
   double TCHELEfficiencyTempDown[] = {0.75, 0.825, 0.85, 0.87, 0.87, 0.72, 0.35, 0.0};
   double TCHELEfficiencyTempNoHighPT[] = {0.75, 0.825, 0.85, 0.87, 0.87, 0.82, 0.0, 0.0};
   double TCHELEfficiencyTempExtremeDrop[] = {0.75, 0.825, 0.85, 0.87, 0.60, 0.20, 0.0, 0.0};

   vector<double> TCHELPT(TCHELPTTemp, TCHELPTTemp + 8);
   vector<double> TCHELEfficiency(TCHELEfficiencyTemp, TCHELEfficiencyTemp + 8);
   vector<double> TCHELEfficiencyModerateDrop(TCHELEfficiencyTempModerateDrop, TCHELEfficiencyTempModerateDrop + 8);
   vector<double> TCHELEfficiencyUp(TCHELEfficiencyTempUp, TCHELEfficiencyTempUp + 8);
   vector<double> TCHELEfficiencyDown(TCHELEfficiencyTempDown, TCHELEfficiencyTempDown + 8);
   vector<double> TCHELEfficiencyNoHighPT(TCHELEfficiencyTempNoHighPT, TCHELEfficiencyTempNoHighPT + 8);
   vector<double> TCHELEfficiencyExtremeDrop(TCHELEfficiencyTempExtremeDrop, TCHELEfficiencyTempExtremeDrop + 8);

   PsFile.AddTextPage("Roughly TCHEL efficiency, one jet");
   DoToyAndAppendPlots(PsFile, TCHELPT, TCHELEfficiency, 400, false, "RoughlyTCHELOneJet.root");
   PsFile.AddTextPage("Roughly TCHEL efficiency, two jets");
   DoToyAndAppendPlots(PsFile, TCHELPT, TCHELEfficiency, 400, true, "RoughlyTCHELTwoJet.root");
   
   PsFile.AddTextPage("Roughly TCHEL efficiency (moderate drop at high PT), one jet");
   DoToyAndAppendPlots(PsFile, TCHELPT, TCHELEfficiencyModerateDrop, 400, false, "RoughlyTCHELOneJetModerateDrop.root");
   PsFile.AddTextPage("Roughly TCHEL efficiency (moderate drop at high PT), two jets");
   DoToyAndAppendPlots(PsFile, TCHELPT, TCHELEfficiencyModerateDrop, 400, true, "RoughlyTCHELTwoJetModerateDrop.root");
   
   PsFile.AddTextPage("Roughly TCHEL efficiency (high PT up), one jet");
   DoToyAndAppendPlots(PsFile, TCHELPT, TCHELEfficiencyUp, 400, false, "BetterHighPTOneJet.root");
   PsFile.AddTextPage("Roughly TCHEL efficiency (high PT up), two jets");
   DoToyAndAppendPlots(PsFile, TCHELPT, TCHELEfficiencyUp, 400, true, "BetterHighPTTwoJet.root");
   
   PsFile.AddTextPage("Roughly TCHEL efficiency (high PT down), one jet");
   DoToyAndAppendPlots(PsFile, TCHELPT, TCHELEfficiencyDown, 400, false, "WorseHighPTOneJet.root");
   PsFile.AddTextPage("Roughly TCHEL efficiency (high PT down), two jets");
   DoToyAndAppendPlots(PsFile, TCHELPT, TCHELEfficiencyDown, 400, true, "WorseHighPTTwoJet.root");

   PsFile.AddTextPage("Roughly TCHEL efficiency (no high PT), one jet");
   DoToyAndAppendPlots(PsFile, TCHELPT, TCHELEfficiencyNoHighPT, 400, false, "NoHighPTOneJet.root");
   PsFile.AddTextPage("Roughly TCHEL efficiency (no high PT), two jets");
   DoToyAndAppendPlots(PsFile, TCHELPT, TCHELEfficiencyNoHighPT, 400, true, "NoHighPTTwoJet.root");

   PsFile.AddTextPage("Roughly TCHEL efficiency (extreme drop), one jet");
   DoToyAndAppendPlots(PsFile, TCHELPT, TCHELEfficiencyExtremeDrop, 400, false, "ExtremeDropOneJet.root");
   PsFile.AddTextPage("Roughly TCHEL efficiency (extreme drop), two jets");
   DoToyAndAppendPlots(PsFile, TCHELPT, TCHELEfficiencyExtremeDrop, 400, true, "ExtremeDropTwoJet.root");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void DoToyAndAppendPlots(PsFileHelper &PsFile, const vector<double> &JetPT,
   const vector<double> &JetEfficiency, const double &LQMass, const bool ApplyOnTwoJets, const string OutputFileName)
{
   cout << "Starting Job And Write To File " << OutputFileName << endl;

   double TreeMRStar = 0;
   double TreeRStar = 0;
   double TreeGammaRStar = 0;
   bool TreePassTagging = false;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree OutputTree("OutputTree", "Tree! ®");
   OutputTree.Branch("MRStar", &TreeMRStar, "MRStar/D");
   OutputTree.Branch("RStar", &TreeRStar, "RStar/D");
   OutputTree.Branch("GammaRStar", &TreeGammaRStar, "RStar/D");
   OutputTree.Branch("PassTagging", &TreePassTagging, "PassTagging/O");

   stringstream LQMassStream;
   LQMassStream << "42: m0 = " << LQMass;

   Pythia pythia;

   pythia.readString("ParticleDecays:limitTau0 = on");     // Particle lifetime cutoff
   pythia.readString("ParticleDecays:tauMax = 10");

   pythia.readString("42:0:products = 5 16");              // Force decay to b nu_tau
   pythia.readString(LQMassStream.str().c_str());          // LQ mass set to input value
   pythia.readString("LeptoQuark:gg2LQLQbar = on");        // production mechanism: gg
   pythia.readString("LeptoQuark:qqbar2LQLQbar = on");     // production mechanism: qqbar

   pythia.readString("Tune:pp 2");                         // Tune?  What??
   pythia.readString("Tune:ee 3");                         // I see this in CMS production settings.....

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.init(2212, 2212, 7000);                          // Proton-proton collision at 7 TeV

   TGraph EfficiencyInput;
   for(int i = 0; i < (int)JetPT.size(); i++)
      EfficiencyInput.SetPoint(i, JetPT[i], JetEfficiency[i]);
   EfficiencyInput.SetTitle("Input efficiency curve");
   PsFile.AddPlot(EfficiencyInput, "apl");

   TH2D HMRStarVsRStarAll("HMRStarVsRStarAll", "MRStar vs. RStar, all", 100, 0, 1500, 100, 0, 1.5);
   TH2D HMRStarVsRStarPass("HMRStarVsRStarPass", "MRStar vs. RStar, pass", 100, 0, 1500, 100, 0, 1.5);
   TH2D HMRStarVsRStarFail("HMRStarVsRStarFail", "MRStar vs. RStar, fail", 100, 0, 1500, 100, 0, 1.5);
   TH1D HMRStarAll("HMRStarAll", "MRStar, all", 100, 0, 1500);
   TH1D HMRStarPass("HMRStarPass", "MRStar, pass", 100, 0, 1500);
   TH1D HMRStarFail("HMRStarFail", "MRStar, fail", 100, 0, 1500);
   TH1D HRStarAll("HRStarAll", "RStar, all", 100, 0, 1.500);
   TH1D HRStarPass("HRStarPass", "RStar, pass", 100, 0, 1.500);
   TH1D HRStarFail("HRStarFail", "RStar, fail", 100, 0, 1.500);
   TH1D HGammaRStarAll("HGammaRStarAll", "GammaRStar, all", 100, 0, 15);
   TH1D HGammaRStarPass("HGammaRStarPass", "GammaRStar, pass", 100, 0, 15);
   TH1D HGammaRStarFail("HGammaRStarFail", "GammaRStar, fail", 100, 0, 15);

   for(int iEntry = 0; iEntry < 100000; iEntry++)
   {
      // Generate event
      pythia.next();

      // Particles
      vector<GenParticle> Particles(pythia.event.size());

      // Loop over particles
      for(int j = 0; j < pythia.event.size(); j++)
      {
         Particles[j].P[0] = pythia.event[j].e();
         Particles[j].P[1] = pythia.event[j].px();
         Particles[j].P[2] = pythia.event[j].py();
         Particles[j].P[3] = pythia.event[j].pz();
         
         Particles[j].V[0] = pythia.event[j].tProd();
         Particles[j].V[1] = pythia.event[j].xProd();
         Particles[j].V[2] = pythia.event[j].yProd();
         Particles[j].V[3] = pythia.event[j].zProd();

         Particles[j].PDGID = pythia.event[j].id();
         Particles[j].StatusCode = pythia.event.statusHepMC(j);

         Particles[j].Mothers = pythia.event.motherList(j);
         Particles[j].Daughters = pythia.event.daughterList(j);
      }
      GenParticleTree Tree(Particles, 1, iEntry + 1);

      // Group into jets - also calculate MET along the way
      FourVector MissingEnergy;
      vector<PseudoJet> VisibleParticles;
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].StatusCode != 1)   // final particles only
            continue;
         if(Tree[i].PDGID == 16 || Tree[i].PDGID == -16 || Tree[i].PDGID == 14 || Tree[i].PDGID == -14
            || Tree[i].PDGID == 12 || Tree[i].PDGID == -12)   // neutrinos - invisible
            continue;
         if(fabs(FourVector(Tree[i].P).GetEta()) > 3)   // calorimeter range
            continue;
         if(FourVector(Tree[i].P).GetPT() < 1)   // mini particles - forget it
            continue;

         VisibleParticles.push_back(PseudoJet(Tree[i].P[1], Tree[i].P[2], Tree[i].P[3], Tree[i].P[0]));
         MissingEnergy = MissingEnergy - FourVector(Tree[i].P);
      }
      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.5);   // anti-kt, R = 0.5

      // Trace b quarks from lepto-quarks
      int BFromLQIndex = max(FindChildIndex(Tree, 5, 42), FindChildIndex(Tree, -5, 42));
      int BFromLQBarIndex = max(FindChildIndex(Tree, 5, -42), FindChildIndex(Tree, -5, -42));

      if(BFromLQIndex < 0 || BFromLQBarIndex < 0)   // something's wrong
         continue;

      int JetFromLQ = FindClosestJet(Jets, FourVector(Tree[BFromLQIndex].P).GetEta(),
         FourVector(Tree[BFromLQIndex].P).GetPhi());
      int JetFromLQBar = FindClosestJet(Jets, FourVector(Tree[BFromLQIndex].P).GetEta(),
         FourVector(Tree[BFromLQIndex].P).GetPhi());

      if(Jets[JetFromLQ].eta() > 2.4 || Jets[JetFromLQ].eta() < -2.4)   // acceptance
         continue;
      if(Jets[JetFromLQBar].eta() > 2.4 || Jets[JetFromLQBar].eta() < -2.4)   // acceptance
         continue;

      if(Jets[JetFromLQ].perp() < 40 || Jets[JetFromLQBar].perp() < 40)   // PT too small. not interesting.
         continue;

      double EfficiencyJet1 = GetEfficiency(Jets[JetFromLQ].perp(), JetPT, JetEfficiency);
      double EfficiencyJet2 = GetEfficiency(Jets[JetFromLQBar].perp(), JetPT, JetEfficiency);

      double TotalEfficiency = 0;
      if(ApplyOnTwoJets == true)
         TotalEfficiency = EfficiencyJet1 * EfficiencyJet2;
      else
         TotalEfficiency = 1 - (1 - EfficiencyJet1) * (1 - EfficiencyJet2);

      bool FailBTagging = false;

      double TestNumber = DrawRandom(0, 1);
      if(TestNumber > TotalEfficiency)
         FailBTagging = true;
      else
         FailBTagging = false;

      vector<FourVector> GoodJets;
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         if(Jets[i].perp() < 30)
            continue;
         GoodJets.push_back(FourVector(Jets[i].e(), Jets[i].px(), Jets[i].py(), Jets[i].pz()));
      }
      vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);

      double MRStar = GetMRStar(Groups[0], Groups[1]);
      double RStar = GetRStar(Groups[0], Groups[1], MissingEnergy);
      double GammaRStar = GetGammaRStar(Groups[0], Groups[1]);

      HMRStarVsRStarAll.Fill(MRStar, RStar);
      HMRStarAll.Fill(MRStar);
      HRStarAll.Fill(RStar);
      HGammaRStarAll.Fill(GammaRStar);
      if(FailBTagging == false)
      {
         HMRStarVsRStarPass.Fill(MRStar, RStar);
         HMRStarPass.Fill(MRStar);
         HRStarPass.Fill(RStar);
         HGammaRStarPass.Fill(GammaRStar);
      }
      else
      {
         HMRStarVsRStarFail.Fill(MRStar, RStar);
         HMRStarFail.Fill(MRStar);
         HRStarFail.Fill(RStar);
         HGammaRStarFail.Fill(GammaRStar);
      }

      TreeMRStar = MRStar;
      TreeRStar = RStar;
      TreeGammaRStar = GammaRStar;
      TreePassTagging = !FailBTagging;

      OutputTree.Fill();
   }

   PsFile.AddPlot(HMRStarVsRStarAll, "colz");
   PsFile.AddPlot(HMRStarVsRStarPass, "colz");
   PsFile.AddPlot(HMRStarVsRStarFail, "colz");
   PsFile.AddPlot(HMRStarAll, "", false);
   PsFile.AddPlot(HMRStarPass, "", false);
   PsFile.AddPlot(HMRStarFail, "", false);
   PsFile.AddPlot(HRStarAll, "", false);
   PsFile.AddPlot(HRStarPass, "", false);
   PsFile.AddPlot(HRStarFail, "", false);
   PsFile.AddPlot(HGammaRStarAll, "", true);
   PsFile.AddPlot(HGammaRStarPass, "", true);
   PsFile.AddPlot(HGammaRStarFail, "", true);

   HMRStarVsRStarAll.Write();
   HMRStarVsRStarPass.Write();
   HMRStarVsRStarFail.Write();
   HMRStarAll.Write();
   HMRStarPass.Write();
   HMRStarFail.Write();
   HRStarAll.Write();
   HRStarPass.Write();
   HRStarFail.Write();
   HGammaRStarAll.Write();
   HGammaRStarPass.Write();
   HGammaRStarFail.Write();

   OutputTree.Write();
   OutputFile.Close();
}

int FindChildIndex(GenParticleTree &Tree, int ChildPDGID, int ParentPDGID)
{
   int MotherIndex = -1;

   for(int i = 0; i < Tree.ParticleCount(); i++)
   {
      if(Tree[i].PDGID == ChildPDGID)
      {
         for(int j = 0; j < (int)Tree[i].Mothers.size(); j++)
         {
            if(Tree[Tree[i].Mothers[j]].PDGID == ParentPDGID)
               return i;
         }
      }
   }

   return -1;
}

int TraceBHadron(GenParticleTree &Tree, int StartIndex)
{
   if(StartIndex < 0 || StartIndex >= Tree.ParticleCount())
      return -1;
   if(HasB(Tree[StartIndex].PDGID) == false && Tree[StartIndex].PDGID != 92)
      return -1;

   int CurrentIndex = StartIndex;

   bool OK = false;
   while(OK == false)
   {
      // step 1: collect list of children that contain b (or is a string)
      vector<int> ChildrenIndex;;
      for(int i = 0; i < (int)Tree[CurrentIndex].Daughters.size(); i++)
      {
         if(Tree[Tree[CurrentIndex].Daughters[i]].PDGID != 92
            && HasB(Tree[Tree[CurrentIndex].Daughters[i]].PDGID) == false)
            continue;
         ChildrenIndex.push_back(Tree[CurrentIndex].Daughters[i]);
      }

      // step 2: if there is more than one candidate, choose the one with highest pt
      if(ChildrenIndex.size() == 0)
         return CurrentIndex;
      else if(ChildrenIndex.size() == 1)
         CurrentIndex = ChildrenIndex[0];
      else
      {
         double BestCandidatePT = FourVector(Tree[ChildrenIndex[0]].P).GetPT();
         int BestCandidate = 0;
         for(int i = 1; i < (int)ChildrenIndex.size(); i++)
         {
            double PT = FourVector(Tree[ChildrenIndex[i]].P).GetPT();
            if(PT > BestCandidatePT)
            {
               BestCandidate = i;
               BestCandidatePT = PT;
            }
         }

         CurrentIndex = ChildrenIndex[BestCandidate];
      }
   }

   return -1;

}

bool HasB(int PDGID)
{
   // note:
   //    b quark: +-5
   //    meson code = 100i + 10j + 2s + 1, quark(i), anti-quark(-j)
   //    baryon code = 1000i + 100j + 10k + 2s + 1, quarks(ijk)
   //    s is spin, let's happily ignore

   if(PDGID < 0)
      PDGID = -PDGID;

   if(PDGID == 5)
      return true;
   if((PDGID % 100) / 10 == 5)
      return true;
   if((PDGID % 1000) / 100 == 5)
      return true;
   if((PDGID % 10000) / 1000 == 5)
      return true;

   return false;
}

int FindClosestJet(vector<PseudoJet> &Jets, double Eta, double Phi)
{
   double ClosestJetDR = 999999;
   int ClosestJetIndex = 0;
   for(int i = 0; i < (int)Jets.size(); i++)
   {
      double EtaJet = Jets[i].eta();
      double PhiJet = Jets[i].phi();

      double DEta = Eta - EtaJet;
      double DPhi = Phi - PhiJet;
      if(DPhi > PI)   DPhi = DPhi - 2 * PI;
      if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
      double DR = sqrt(DPhi * DPhi + DEta * DEta);

      if(ClosestJetDR > DR)
      {
         ClosestJetDR = DR;
         ClosestJetIndex = i;
      }
   }

   return ClosestJetIndex;
}

double GetEfficiency(double PT, const vector<double> &JetPT, const vector<double> &JetEfficiency)
{
   if(JetPT.size() == 0)
      return 0;
   if(PT < JetPT[0])
      return 0;
   if(PT > JetPT[JetPT.size()-1])
      return JetEfficiency[JetPT.size()-1];

   for(int i = 0; i < JetPT.size() - 1; i++)
   {
      if(JetPT[i] < PT && JetPT[i+1] >= PT)
         return JetEfficiency[i] +
            (PT - JetPT[i]) / (JetPT[i+1] - JetPT[i]) * (JetEfficiency[i+1] - JetEfficiency[i]);
   }

   return 0;
}





