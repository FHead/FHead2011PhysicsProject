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
void DoToyAndAppendPlots(PsFileHelper &PsFile, const double LQMass, const string OutputFileName);
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

   PsFileHelper PsFile("MRToy22_Meow.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 22");

   vector<string> Explanations;
   Explanations.push_back("");
   PsFile.AddTextPage(Explanations);

   /*
   DoToyAndAppendPlots(PsFile, 50, "LQ50.root");
   DoToyAndAppendPlots(PsFile, 80, "LQ80.root");
   DoToyAndAppendPlots(PsFile, 90, "LQ90.root");
   DoToyAndAppendPlots(PsFile, 140, "LQ140.root");
   DoToyAndAppendPlots(PsFile, 172, "LQ172.root");
   DoToyAndAppendPlots(PsFile, 200, "LQ200.root");
   DoToyAndAppendPlots(PsFile, 300, "LQ300.root");
   DoToyAndAppendPlots(PsFile, 500, "LQ500.root");
   DoToyAndAppendPlots(PsFile, 800, "LQ800.root");
   */
   
   // DoToyAndAppendPlots(PsFile, 120, "LQ120.root");
   // DoToyAndAppendPlots(PsFile, 250, "LQ250.root");
   // DoToyAndAppendPlots(PsFile, 400, "LQ400.root");
   // DoToyAndAppendPlots(PsFile, 750, "LQ750.root");
   DoToyAndAppendPlots(PsFile, 251, "LQ251.root");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void DoToyAndAppendPlots(PsFileHelper &PsFile, const double LQMass, const string OutputFileName)
{
   cout << "Starting Job And Write To File " << OutputFileName << endl;

   double TreeMRStar = 0;
   double TreeRStar = 0;
   double TreeGammaRStar = 0;
   double TreeMR = 0;
   double TreeR = 0;
   double TreeBetaR = 0;
   double TreeDeltaPhi = 0;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree OutputTree("OutputTree", "Tree! ®");
   OutputTree.Branch("MRStar", &TreeMRStar, "MRStar/D");
   OutputTree.Branch("RStar", &TreeRStar, "RStar/D");
   OutputTree.Branch("GammaRStar", &TreeGammaRStar, "RStar/D");
   OutputTree.Branch("MR", &TreeMR, "MR/D");
   OutputTree.Branch("R", &TreeR, "R/D");
   OutputTree.Branch("BetaR", &TreeBetaR, "BetaR/D");
   OutputTree.Branch("DeltaPhi", &TreeDeltaPhi, "DeltaPhi/D");

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

   TH2D HGammaMRStarVsRStar("HGammaMRStarVsRStar", "GammaMRStar vs. RStar", 100, 0, 1500, 100, 0, 1.5);
   TH1D HMRStar("HMRStar", "MRStar", 100, 0, 1500);
   TH1D HRStar("HRStar", "RStar", 100, 0, 1.500);
   TH1D HGammaRStar("HGammaRStar", "GammaRStar", 100, 0, 15);
   TH2D HMRVsR("HMRVsR", "MR vs. R", 100, 0, 1500, 100, 0, 1.5);
   TH1D HMR("HMR", "MR", 100, 0, 1500);
   TH1D HR("HR", "R", 100, 0, 1.500);

   for(int iEntry = 0; iEntry < 100000; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Generating and processing entry" << iEntry + 1 << "/" << 100000 << endl;

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

      vector<FourVector> GoodJets;
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         if(Jets[i].perp() < 40)
            continue;
         GoodJets.push_back(FourVector(Jets[i].e(), Jets[i].px(), Jets[i].py(), Jets[i].pz()));
      }
      vector<FourVector> Groups = SplitIntoGroups(GoodJets, true);

      double MRStar = GetMRStar(Groups[0], Groups[1]);
      double RStar = GetRStar(Groups[0], Groups[1], MissingEnergy);
      double GammaRStar = GetGammaRStar(Groups[0], Groups[1]);
      double MR = GetMR(Groups[0], Groups[1]);
      double R = GetR(Groups[0], Groups[1], MissingEnergy);
      double BetaR = (Groups[0][0] - Groups[1][0]) / (Groups[0][3] - Groups[1][3]);
      double MRT = GetMRT(Groups[0], Groups[1], MissingEnergy);
      double DeltaPhi = GetDPhi(Groups[0], Groups[1]);
      // cout << MRT << endl;

      HGammaMRStarVsRStar.Fill(MRStar * GammaRStar, RStar);
      HMRStar.Fill(MRStar);
      HRStar.Fill(RStar);
      HGammaRStar.Fill(GammaRStar);
      HMRVsR.Fill(MR, R);
      HMR.Fill(MR);
      HR.Fill(R);

      TreeMRStar = MRStar;
      TreeRStar = RStar;
      TreeGammaRStar = GammaRStar;
      TreeMR = MR;
      TreeR = R;
      TreeBetaR = BetaR;
      TreeDeltaPhi = DeltaPhi;

      OutputTree.Fill();
   }

   PsFile.AddPlot(HGammaMRStarVsRStar, "colz");
   PsFile.AddPlot(HMRStar, "", false);
   PsFile.AddPlot(HRStar, "", false);
   PsFile.AddPlot(HGammaRStar, "", true);
   PsFile.AddPlot(HMRVsR, "colz");
   PsFile.AddPlot(HMR, "", false);
   PsFile.AddPlot(HR, "", false);

   HGammaMRStarVsRStar.Write();
   HMRStar.Write();
   HRStar.Write();
   HGammaRStar.Write();
   HMRVsR.Write();
   HMR.Write();
   HR.Write();

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





