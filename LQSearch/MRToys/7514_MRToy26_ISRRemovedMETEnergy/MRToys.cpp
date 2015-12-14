#include <string>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TTree.h"

#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double VisibleMass, const double InvisibleMass, double BoostBeta);

int main(int argc, char *argv[])
{
   PsFileHelper PsFile("MRToy26_ISRRemovedMETEnergy.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 26");

   vector<string> Explanations;
   Explanations.push_back("");
   PsFile.AddTextPage(Explanations);

   double HeavyMass = 300;
   double GammaCM = 1.01;

   DoToyAndAppendPlots(PsFile, HeavyMass, 2 * GammaCM * HeavyMass, 4.2, 0, -1);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double VisibleMass, const double InvisibleMass, double BoostBeta)
{
   bool RandomBeta = false;
   if(BoostBeta < 0)
      RandomBeta = true;

   TH1D HMETEnergy("HMETEnergy", "MET Energy", 100, 0, 600);

   TFile F("Output.root", "recreate");

   double TreeMETEnergy;
   double TreeMETx;
   double TreeMETy;
   double TreeJet1x;
   double TreeJet1y;
   double TreeJet2x;
   double TreeJet2y;
   double TreeBoostBeta;

   TTree Tree("Tree", "Tree");
   Tree.Branch("METEnergy", &TreeMETEnergy, "METEnergy/D");
   Tree.Branch("METx", &TreeMETx, "METx/D");
   Tree.Branch("METy", &TreeMETy, "METy/D");
   Tree.Branch("Jet1x", &TreeJet1x, "Jet1x/D");
   Tree.Branch("Jet1y", &TreeJet1y, "Jet1y/D");
   Tree.Branch("Jet2x", &TreeJet2x, "Jet2x/D");
   Tree.Branch("Jet2y", &TreeJet2y, "Jet2y/D");
   Tree.Branch("Beta", &TreeBoostBeta, "Beta/D");

   for(int iEntry = 0; iEntry < 100000; iEntry++)
   {
      if(RandomBeta == true)
         BoostBeta = DrawRandom(0, 0.9999);

      // Decay angles of the two heavy guys
      double Theta = DrawSine(0, PI);
      double Phi = DrawRandom(-PI, PI);
      double Gamma = Energy / 2 / HeavyMass;
      double Beta = GammaToBeta(Gamma);

      FourVector HeavyParticle1Direction, HeavyParticle2Direction;
      HeavyParticle1Direction.SetSizeThetaPhi(1, Theta, Phi);
      HeavyParticle2Direction.SetSizeThetaPhi(1, PI - Theta, Phi + PI);

      // CM frame child momentum calculation
      double M2 = HeavyMass * HeavyMass;
      double m12 = VisibleMass * VisibleMass;
      double m22 = InvisibleMass * InvisibleMass;
      double Momentum = sqrt(((M2 - m12 - m22) * (M2 - m12 - m22) - 4 * m12 * m22) / (4 * M2));

      // Inside CM of first heavy particle
      double Theta1 = DrawSine(0, PI);
      double Phi1 = DrawRandom(-PI, PI);

      FourVector VisibleChild1Heavy1CM, InvisibleChild1Heavy1CM;
      VisibleChild1Heavy1CM.SetSizeThetaPhi(Momentum, Theta1, Phi1);
      InvisibleChild1Heavy1CM.SetSizeThetaPhi(Momentum, PI - Theta1, Phi1 + PI);
      
      // In CM of second heavy particle
      double Theta2 = DrawSine(0, PI);
      double Phi2 = DrawRandom(-PI, PI);
      
      FourVector VisibleChild2Heavy2CM, InvisibleChild2Heavy2CM;
      VisibleChild2Heavy2CM.SetSizeThetaPhi(Momentum, Theta2, Phi2);
      InvisibleChild2Heavy2CM.SetSizeThetaPhi(Momentum, PI - Theta2, Phi2 + PI);
      
      // boost back to gluon frame
      FourVector VisibleChild1 = VisibleChild1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector InvisibleChild1 = InvisibleChild1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector VisibleChild2 = VisibleChild2Heavy2CM.Boost(HeavyParticle2Direction, Beta);
      FourVector InvisibleChild2 = InvisibleChild2Heavy2CM.Boost(HeavyParticle2Direction, Beta);

      // do a final ISR boost
      double InitialDirectionPhi = DrawRandom(-PI, PI);
      double InitialDirectionTheta = DrawSine(0, PI);
      FourVector InitialDirection;
      InitialDirection.SetSizeThetaPhi(1, InitialDirectionTheta, InitialDirectionPhi);

      FourVector VisibleChild1Final = VisibleChild1.Boost(InitialDirection, BoostBeta);
      FourVector InvisibleChild1Final = InvisibleChild1.Boost(InitialDirection, BoostBeta);
      FourVector VisibleChild2Final = VisibleChild2.Boost(InitialDirection, BoostBeta);
      FourVector InvisibleChild2Final = InvisibleChild2.Boost(InitialDirection, BoostBeta);

      // collect result
      FourVector InvisibleTotal = InvisibleChild1Final + InvisibleChild2Final;

      HMETEnergy.Fill(InvisibleTotal[0]);

      TreeMETEnergy = InvisibleTotal[0];
      TreeMETx = InvisibleTotal[1];
      TreeMETy = InvisibleTotal[2];
      TreeJet1x = VisibleChild1[1];
      TreeJet1y = VisibleChild1[2];
      TreeJet2x = VisibleChild2[1];
      TreeJet2y = VisibleChild2[2];
      TreeBoostBeta = BoostBeta;

      Tree.Fill();
   }

   Tree.Write();
   F.Close();

   PsFile.AddPlot(HMETEnergy, "", true);
}





