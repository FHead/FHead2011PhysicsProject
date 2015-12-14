#include <string>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "Pythia.h"
using namespace Pythia8;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"

#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "GenparticleTree.h"
#include "PlotHelper2.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void PlotShapeVariation(PsFileHelper &PsFile, TH1D *H, vector<double> Percentages);

int main(int argc, char *argv[])
{
   SetStyle();

   PsFileHelper PsFile("MRToy25_TTbarShapeSystematics.ps");
   PsFile.AddTextPage("Toys to understand things better - part 25");

   vector<string> Explanations;
   Explanations.push_back("Setup: pythia 8, generating ttbar");
   Explanations.push_back("Require one W decay to mu/e nu, and another one hadronically");
   Explanations.push_back("Plot M^{R} with respect to different R^{*} cut");
   Explanations.push_back("Vary shape (a,b) by different amount, visualize effect");
   PsFile.AddTextPage(Explanations);
   PsFile.InsertNamedDestination("Explanations");

   Pythia pythia;

   pythia.readString("ParticleDecays:limitTau0 = on");     // Particle lifetime cutoff
   pythia.readString("ParticleDecays:tauMax = 10");

   pythia.readString("Top:gg2ttbar = on");                 // gg -> ttbar
   pythia.readString("Top:qqbar2ttbar(s:gmZ) = on");       // qqbar -> g -> ttbar
   pythia.readString("Top:ffbar2ttbar(s:gmZ) = on");       // ffbar -> gamma*/Z0 -> ttbar
   pythia.readString("Top:gmgm2ttbar = on");               // gamma gamma -> ttbar

   pythia.readString("Tune:pp 2");                         // Tune?  What??
   pythia.readString("Tune:ee 3");                         // I see this in CMS production settings.....

   pythia.readString("Random:setSeed = on");               // Random seed on
   pythia.readString("Random:seed = 0");                   // Set random seed based on time

   pythia.init(2212, 2212, 7000);                          // Proton-proton collision at 7 TeV

   TH2D HMRVsR("HMRVsR", "M^{R} vs. R^{*};M^{R};R^{*}", 40, 0, 1000, 40, 0, 1.5);
   TH1D HMR_R00("HMR_R00", "M^{R}, R^{*} > 0.0;M^{R}", 40, 0, 1000);
   TH1D HMR_R01("HMR_R01", "M^{R}, R^{*} > 0.1;M^{R}", 40, 0, 1000);
   TH1D HMR_R02("HMR_R02", "M^{R}, R^{*} > 0.2;M^{R}", 40, 0, 1000);
   TH1D HMR_R03("HMR_R03", "M^{R}, R^{*} > 0.3;M^{R}", 40, 0, 1000);
   TH1D HMR_R04("HMR_R04", "M^{R}, R^{*} > 0.4;M^{R}", 40, 0, 1000);
   TH1D HMR_R05("HMR_R05", "M^{R}, R^{*} > 0.5;M^{R}", 40, 0, 1000);

   int NumberOfEntries = 200000;

   for(int i = 0; i < NumberOfEntries; i++)
   {
      pythia.next();

      vector<GenParticle> Particles(pythia.event.size());
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

      GenParticleTree Tree(Particles, 1, i + 1);

      int WMuNuCount = 0;
      int WENuCount = 0;
      int WTauNuCount = 0;
      for(int j = 0; j < Tree.ParticleCount(); j++)
      {
         if(Tree[j].PDGID != 24 && Tree[j].PDGID != -24)   // we want to check W
            continue;

         for(int k = 0; k < (int)Tree[j].Daughters.size(); k++)   // count electron or muon daughters
         {
            if(Tree[Tree[j].Daughters[k]].PDGID == 11 || Tree[Tree[j].Daughters[k]].PDGID == -11)
               WENuCount = WENuCount + 1;
            if(Tree[Tree[j].Daughters[k]].PDGID == 13 || Tree[Tree[j].Daughters[k]].PDGID == -13)
               WMuNuCount = WMuNuCount + 1;
            if(Tree[Tree[j].Daughters[k]].PDGID == 15 || Tree[Tree[j].Daughters[k]].PDGID == -15)
               WTauNuCount = WTauNuCount + 1;
         }
      }
      if(WMuNuCount + WENuCount != 1 || WTauNuCount != 0)   // one WMuNu or one WENu, not both
      {
         i = i - 1;
         continue;
      }

      FourVector MissingEnergy;
      vector<PseudoJet> VisibleParticles;
      for(int j = 0; j < Tree.ParticleCount(); j++)
      {
         if(Tree[j].StatusCode != 1)
            continue;

         if(Tree[j].PDGID == 16 || Tree[j].PDGID == -16
            || Tree[j].PDGID == 14 || Tree[j].PDGID == -14
            || Tree[j].PDGID == 12 || Tree[j].PDGID == -12)
         {
            MissingEnergy = MissingEnergy + FourVector(Tree[j].P);
            continue;
         }

         if(fabs(FourVector(Tree[j].P).GetEta()) > 3)
         {
            MissingEnergy = MissingEnergy + FourVector(Tree[j].P);
            continue;
         }

         if(FourVector(Tree[j].P).GetPT() < 1)
         {
            MissingEnergy = MissingEnergy + FourVector(Tree[j].P);
            continue;
         }

         VisibleParticles.push_back(PseudoJet(Tree[j].P[1], Tree[j].P[2], Tree[j].P[3], Tree[j].P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.5);

      vector<FourVector> InputJets;
      for(int j = 0; j < (int)Jets.size(); j++)
      {
         if(Jets[j].perp() < 40)
            continue;
         if(Jets[j].eta() < -3 || Jets[j].eta() > 3)
            continue;

         InputJets.push_back(FourVector(Jets[j].e(), Jets[j].px(), Jets[j].py(), Jets[j].pz()));
      }
      
      if(InputJets.size() < 2)   // oops
      {
         i = i - 1;
         continue;
      }

      vector<FourVector> Hemispheres = SplitIntoGroups(InputJets, true);

      FourVector Jet1P = Hemispheres[0];
      FourVector Jet2P = Hemispheres[1];

      double GammaMRStar = GetMRStar(Jet1P, Jet2P) * GetGammaRStar(Jet1P, Jet2P);
      double RStar = GetRStar(Jet1P, Jet2P, MissingEnergy);

      HMRVsR.Fill(GammaMRStar, RStar);

      if(RStar > 0.0)   HMR_R00.Fill(GammaMRStar);
      if(RStar > 0.1)   HMR_R01.Fill(GammaMRStar);
      if(RStar > 0.2)   HMR_R02.Fill(GammaMRStar);
      if(RStar > 0.3)   HMR_R03.Fill(GammaMRStar);
      if(RStar > 0.4)   HMR_R04.Fill(GammaMRStar);
      if(RStar > 0.5)   HMR_R05.Fill(GammaMRStar);
   }

   PsFile.AddTextPage("Basic distributions");
   PsFile.AddPlot(HMRVsR, "colz");
   PsFile.AddPlot(HMR_R00, "", true);
   PsFile.AddPlot(HMR_R01, "", true);
   PsFile.AddPlot(HMR_R02, "", true);
   PsFile.AddPlot(HMR_R03, "", true);
   PsFile.AddPlot(HMR_R04, "", true);
   PsFile.AddPlot(HMR_R05, "", true);

   vector<double> Percentages;
   Percentages.push_back(-0.4);
   Percentages.push_back(-0.2);
   Percentages.push_back(0.2);
   Percentages.push_back(0.4);

   PsFile.AddTextPage("Shape variations");
   PlotShapeVariation(PsFile, &HMR_R00, Percentages);
   PlotShapeVariation(PsFile, &HMR_R01, Percentages);
   PlotShapeVariation(PsFile, &HMR_R02, Percentages);
   PlotShapeVariation(PsFile, &HMR_R03, Percentages);
   PlotShapeVariation(PsFile, &HMR_R04, Percentages);
   PlotShapeVariation(PsFile, &HMR_R05, Percentages);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void PlotShapeVariation(PsFileHelper &PsFile, TH1D *H, vector<double> Percentages)
{
   if(H == NULL)
      return;

   TCanvas C;

   H->SetStats(0);
   H->Draw();

   int MaxBin = 1;
   for(int i = 1; i <= H->GetNbinsX(); i++)
      if(H->GetBinContent(i) > H->GetBinContent(MaxBin))
         MaxBin = i;
   double MaxBinContent = H->GetBinContent(MaxBin);

   vector<TH1D *> Clones;
   for(int i = 0; i < (int)Percentages.size(); i++)
   {
      Clones.push_back((TH1D *)H->Clone(Form("Clone_%d", i)));

      double Factor = 1 - Percentages[i];

      for(int j = MaxBin + 1; j <= H->GetNbinsX(); j++)
      {
         double Value = H->GetBinContent(j);
         if(Value == 0)
            continue;

         double LogTarget = log(MaxBinContent) - (log(MaxBinContent) - log(Value)) * Factor;
         Clones[i]->SetBinContent(j, exp(LogTarget));
      }

      Clones[i]->SetLineColor(i + 2);
      Clones[i]->Draw("same");
   }

   TLegend legend(0.7, 0.85, 0.9, 0.65);
   legend.AddEntry(H, "Original", "l");
   for(int i = 0; i < (int)Percentages.size(); i++)
      if(Clones[i] != NULL)
         legend.AddEntry(Clones[i], Form("%+.2f", Percentages[i]), "l");
   legend.SetFillColor(0);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.Draw();

   C.SetLogy();
   PsFile.AddCanvas(C);

   for(int i = 0; i < (int)Percentages.size(); i++)
   {
      if(Clones[i] != NULL)
         delete Clones[i];
      Clones[i] = NULL;
   }
}





