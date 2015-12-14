#include <string>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TF1.h"

#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "GenparticleTree.h"
#include "PlotHelper2.h"

int main(int argc, char *argv[]);
void DoToyAndAppendPlots(PsFileHelper &PsFile, string InputFile, string Tag, int MRMode);

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

   PsFileHelper PsFile("MRToy11_Pythia8HardProcessOnly.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 11");

   vector<string> TOCItems;
   TOCItems.push_back("Explanations");
   TOCItems.push_back("LQ Mass = 300 GeV, MR/R from final b and nu");
   TOCItems.push_back("LQ Mass = 300 GeV, MR/R from highest particles and nu");
   TOCItems.push_back("LQ Mass = 300 GeV, MR/R from highest jets and nu");
   TOCItems.push_back("LQ Mass = 300 GeV, MR/R from hemispheres and nu");
   TOCItems.push_back("LQ Mass = 400 GeV, MR/R from final b and nu");
   TOCItems.push_back("LQ Mass = 400 GeV, MR/R from highest particles and nu");
   TOCItems.push_back("LQ Mass = 400 GeV, MR/R from highest jets and nu");
   TOCItems.push_back("LQ Mass = 400 GeV, MR/R from hemispheres and nu");

   vector<string> Destinations;
   Destinations.push_back("Explanations");
   Destinations.push_back("LQ300Mode1");
   Destinations.push_back("LQ300Mode2");
   Destinations.push_back("LQ300Mode3");
   Destinations.push_back("LQ300Mode4");
   Destinations.push_back("LQ400Mode1");
   Destinations.push_back("LQ400Mode2");
   Destinations.push_back("LQ400Mode3");
   Destinations.push_back("LQ400Mode4");

   PsFile.AddTableOfContentPage(TOCItems, Destinations);
   PsFile.InsertNamedDestination("TableOfContentPage");
   PsFile.SetAutomaticHomeButton(true, "TableOfContentPage");

   vector<string> Explanations;
   Explanations.push_back("Setup: pythia 8, turning on LQ");
   Explanations.push_back("LQ force decay to b nu, LQ mass 300 and 400");
   Explanations.push_back("1. No ISR, No FSR, No MI, No Hadron Step");
   Explanations.push_back("2. No ISR, No FSR, No Hadron Step");
   Explanations.push_back("3. No FSR, No MI, No Hadron Step");
   Explanations.push_back("4. No ISR, No MI, No Hadron Step");
   PsFile.AddTextPage(Explanations);
   PsFile.InsertNamedDestination("Explanations");

   PsFile.AddTextPage("LQ Mass = 300 GeV, MR from b b nu nu");
   PsFile.InsertNamedDestination("LQ300Mode1");
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSRMI_NoHadronization_LQ300",
      "Hard process only, LQ 300 GeV", 1);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSR_NoHadronization_LQ300",
      "With MI, LQ 300 GeV", 1);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoFSRMI_NoHadronization_LQ300",
      "With ISR, LQ 300 GeV", 1);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRMI_NoHadronization_LQ300",
      "With FSR (erroneous), LQ 300 GeV", 1);
   
   PsFile.AddTextPage("LQ Mass = 300 GeV, MR from leading particles and nu nu");
   PsFile.InsertNamedDestination("LQ300Mode2");
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSRMI_NoHadronization_LQ300",
      "Hard process only, LQ 300 GeV", 2);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSR_NoHadronization_LQ300",
      "With MI, LQ 300 GeV", 2);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoFSRMI_NoHadronization_LQ300",
      "With ISR, LQ 300 GeV", 2);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRMI_NoHadronization_LQ300",
      "With FSR (erroneous), LQ 300 GeV", 2);
   
   PsFile.AddTextPage("LQ Mass = 300 GeV, MR from leading jets and nu nu");
   PsFile.InsertNamedDestination("LQ300Mode3");
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSRMI_NoHadronization_LQ300",
      "Hard process only, LQ 300 GeV", 3);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSR_NoHadronization_LQ300",
      "With MI, LQ 300 GeV", 3);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoFSRMI_NoHadronization_LQ300",
      "With ISR, LQ 300 GeV", 3);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRMI_NoHadronization_LQ300",
      "With FSR (erroneous), LQ 300 GeV", 3);
   
   PsFile.AddTextPage("LQ Mass = 300 GeV, MR from hemispheres and nu nu");
   PsFile.InsertNamedDestination("LQ300Mode4");
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSRMI_NoHadronization_LQ300",
      "Hard process only, LQ 300 GeV", 4);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSR_NoHadronization_LQ300",
      "With MI, LQ 300 GeV", 4);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoFSRMI_NoHadronization_LQ300",
      "With ISR, LQ 300 GeV", 4);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRMI_NoHadronization_LQ300",
      "With FSR (erroneous), LQ 300 GeV", 4);
   
   PsFile.AddTextPage("LQ Mass = 400 GeV, MR from b b nu nu");
   PsFile.InsertNamedDestination("LQ400Mode1");
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSRMI_NoHadronization_LQ400",
      "Hard process only, LQ 400 GeV", 1);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSR_NoHadronization_LQ400",
      "With MI, LQ 400 GeV", 1);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoFSRMI_NoHadronization_LQ400",
      "With ISR, LQ 400 GeV", 1);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRMI_NoHadronization_LQ400",
      "With FSR (erroneous), LQ 400 GeV", 1);
   
   PsFile.AddTextPage("LQ Mass = 400 GeV, MR from leading particles and nu nu");
   PsFile.InsertNamedDestination("LQ400Mode2");
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSRMI_NoHadronization_LQ400",
      "Hard process only, LQ 400 GeV", 2);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSR_NoHadronization_LQ400",
      "With MI, LQ 400 GeV", 2);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoFSRMI_NoHadronization_LQ400",
      "With ISR, LQ 400 GeV", 2);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRMI_NoHadronization_LQ400",
      "With FSR (erroneous), LQ 400 GeV", 2);

   PsFile.AddTextPage("LQ Mass = 400 GeV, MR from leading jets and nu nu");
   PsFile.InsertNamedDestination("LQ400Mode3");
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSRMI_NoHadronization_LQ400",
      "Hard process only, LQ 400 GeV", 3);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSR_NoHadronization_LQ400",
      "With MI, LQ 400 GeV", 3);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoFSRMI_NoHadronization_LQ400",
      "With ISR, LQ 400 GeV", 3);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRMI_NoHadronization_LQ400",
      "With FSR (erroneous), LQ 400 GeV", 3);

   PsFile.AddTextPage("LQ Mass = 400 GeV, MR from hemispheres and nu nu");
   PsFile.InsertNamedDestination("LQ400Mode4");
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSRMI_NoHadronization_LQ400",
      "Hard process only, LQ 400 GeV", 4);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRFSR_NoHadronization_LQ400",
      "With MI, LQ 400 GeV", 4);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoFSRMI_NoHadronization_LQ400",
      "With ISR, LQ 400 GeV", 4);
   DoToyAndAppendPlots(PsFile, "Samples/Pythia8_NoISRMI_NoHadronization_LQ400",
      "With FSR (erroneous), LQ 400 GeV", 4);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void DoToyAndAppendPlots(PsFileHelper &PsFile, string InputFile, string Tag, int MRMode)
{
   // MRMode: determines what we should use to calculate MR/R/etc.
   //    1 - MR from the two final b quarks, MET from the two final neutrinos
   //    2 - MR from two highest final particles (in PT), MET from final neutrinos
   //    3 - MR from two highest final gen-jets (in PT), MET from final neutrinos

   TH1D HMR("HMR", Form("MR distribution (Tag %s)", Tag.c_str()), 100, 0, 1000);
   TH1D HMRT("HMRT", "MRT distribution", 100, 0, 1000);
   TH1D HR("HR", "R distribution", 100, 0, 1.5);
   TH2D HMRVsR("HMRVsR", "MR vs R;MR;R", 100, 0, 1000, 100, 0, 1.5);

   ifstream in(InputFile.c_str());

   SaveHelper Helper;
   in.read(Helper.CharValue, 16);

   for(int iEntry = 0; iEntry < Helper.IntValue; iEntry++)
   {
      GenParticleTree Tree;
      Tree.LoadFromStream(in);

      double MR = 0;
      double MRT = 0;
      double R = 0;

      if(MRMode == 1)
      {
         int BIndex = -1;
         int BbarIndex = -1;
         int NuIndex = -1;
         int NubarIndex = -1;

         for(int i = 0; i < Tree.ParticleCount(); i++)
         {
            if(Tree[i].StatusCode != 1)   // we want "final" particles
               continue;

            if(Tree[i].PDGID == 5)
               BIndex = i;
            if(Tree[i].PDGID == -5)
               BbarIndex = i;
            if(Tree[i].PDGID == 16)
               NuIndex = i;
            if(Tree[i].PDGID == -16)
               NubarIndex = i;
         }

         if(BIndex >= 0 && BbarIndex >= 0 && NuIndex >= 0 && NubarIndex >= 0)
         {
            FourVector InvisibleTotal = FourVector(Tree[NuIndex].P) + FourVector(Tree[NubarIndex].P);
            MR = GetMR(FourVector(Tree[BIndex].P), FourVector(Tree[BbarIndex].P));
            MRT = GetMRT(FourVector(Tree[BIndex].P), FourVector(Tree[BbarIndex].P), InvisibleTotal);
            R = GetR(FourVector(Tree[BIndex].P), FourVector(Tree[BbarIndex].P), InvisibleTotal);
         }
      }
      else if(MRMode == 2)
      {
         multimap<double, int, greater<double> > SortParticles;
         int NuIndex = -1;
         int NubarIndex = -1;

         for(int i = 0; i < Tree.ParticleCount(); i++)
         {
            if(Tree[i].StatusCode != 1)   // we want "final" particles
               continue;

            if(Tree[i].PDGID == 16)
               NuIndex = i;
            else if(Tree[i].PDGID == -16)
               NubarIndex = i;
            else
               SortParticles.insert(pair<double, int>(FourVector(Tree[i].P).GetPT(), i));
         }

         if(SortParticles.size() >= 2 && NuIndex >= 0 && NubarIndex >= 0)
         {
            FourVector InvisibleTotal = FourVector(Tree[NuIndex].P) + FourVector(Tree[NubarIndex].P);
            
            multimap<double, int, greater<double> >::iterator iter = SortParticles.begin();
            int Particle1Index = iter->second;
            iter++;
            int Particle2Index = iter->second;

            MR = GetMR(FourVector(Tree[Particle1Index].P), FourVector(Tree[Particle2Index].P));
            MRT = GetMRT(FourVector(Tree[Particle1Index].P), FourVector(Tree[Particle2Index].P), InvisibleTotal);
            R = GetR(FourVector(Tree[Particle1Index].P), FourVector(Tree[Particle2Index].P), InvisibleTotal);
         }
      }
      else if(MRMode == 3)
      {
         int NuIndex = -1;
         int NubarIndex = -1;

         vector<PseudoJet> VisibleParticles;
         for(int i = 0; i < Tree.ParticleCount(); i++)
         {
            if(Tree[i].StatusCode != 1)   // we want "final" particles
               continue;

            if(Tree[i].PDGID == 16)
               NuIndex = i;
            else if(Tree[i].PDGID == -16)
               NubarIndex = i;
            else
               VisibleParticles.push_back(PseudoJet(Tree[i].P[1], Tree[i].P[2], Tree[i].P[3], Tree[i].P[0]));
         }
         JetDefinition Definition(antikt_algorithm, 0.5);
         ClusterSequence Sequence(VisibleParticles, Definition);
         vector<PseudoJet> Jets = Sequence.inclusive_jets(0.5);

         if(Jets.size() >= 2 && NuIndex >= 0 && NubarIndex >= 0)
         {
            FourVector InvisibleTotal = FourVector(Tree[NuIndex].P) + FourVector(Tree[NubarIndex].P);

            multimap<double, int, greater<double> > SortJets;
            for(int i = 0; i < (int)Jets.size(); i++)
               SortJets.insert(pair<double, int>(Jets[i].perp(), i));

            multimap<double, int, greater<double> >::iterator iter = SortJets.begin();
            int Jet1Index = iter->second;
            iter++;
            int Jet2Index = iter->second;

            FourVector Jet1P(Jets[Jet1Index].e(), Jets[Jet1Index].px(), Jets[Jet1Index].py(), Jets[Jet1Index].pz());
            FourVector Jet2P(Jets[Jet2Index].e(), Jets[Jet2Index].px(), Jets[Jet2Index].py(), Jets[Jet2Index].pz());

            MR = GetMR(Jet1P, Jet2P);
            MRT = GetMRT(Jet1P, Jet2P, InvisibleTotal);
            R = GetR(Jet1P, Jet2P, InvisibleTotal);
         }
      }
      else if(MRMode == 4)
      {
         int NuIndex = -1;
         int NubarIndex = -1;

         vector<PseudoJet> VisibleParticles;
         for(int i = 0; i < Tree.ParticleCount(); i++)
         {
            if(Tree[i].StatusCode != 1)   // we want "final" particles
               continue;

            if(Tree[i].PDGID == 16)
               NuIndex = i;
            else if(Tree[i].PDGID == -16)
               NubarIndex = i;
            else
               VisibleParticles.push_back(PseudoJet(Tree[i].P[1], Tree[i].P[2], Tree[i].P[3], Tree[i].P[0]));
         }
         JetDefinition Definition(antikt_algorithm, 0.5);
         ClusterSequence Sequence(VisibleParticles, Definition);
         vector<PseudoJet> Jets = Sequence.inclusive_jets(0.5);

         if(Jets.size() >= 2 && NuIndex >= 0 && NubarIndex >= 0)
         {
            FourVector InvisibleTotal = FourVector(Tree[NuIndex].P) + FourVector(Tree[NubarIndex].P);

            vector<FourVector> InputJets;
            for(int i = 0; i < (int)Jets.size(); i++)
               if(Jets[i].perp() > 30)
                  InputJets.push_back(FourVector(Jets[i].e(), Jets[i].px(), Jets[i].py(), Jets[i].pz()));

            vector<FourVector> Hemispheres = SplitIntoGroups(InputJets);

            FourVector &Jet1P = Hemispheres[0];
            FourVector &Jet2P = Hemispheres[1];

            MR = GetMR(Jet1P, Jet2P);
            MRT = GetMRT(Jet1P, Jet2P, InvisibleTotal);
            R = GetR(Jet1P, Jet2P, InvisibleTotal);
         }
      }

      HMR.Fill(MR);
      HMRT.Fill(MRT);
      HR.Fill(R);
      HMRVsR.Fill(MR, R);
   }

   TCanvas canvas;

   canvas.Divide(2, 2);

   canvas.cd(1);
   HMR.Draw();
   canvas.cd(1)->SetLogy();

   canvas.cd(2);
   HMRT.Draw();
   canvas.cd(2)->SetLogy();
   
   canvas.cd(3);
   HR.Draw();
   canvas.cd(3)->SetLogy();
   
   canvas.cd(4);
   HMRVsR.Draw("colz");

   PsFile.AddCanvas(canvas);
}





