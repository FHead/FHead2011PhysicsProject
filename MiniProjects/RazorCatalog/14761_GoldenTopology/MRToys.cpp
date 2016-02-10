#include <string>
#include <vector>
#include <map>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TF1.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double BottomMass, const double NuMass, const double ISRJetMomentum,
   const double JetK, double JetP, bool BBNuNuCase = false);

int main(int argc, char *argv[])
{
   SetStyle();

   PsFileHelper PsFile("RazorCatalog001_GoldenTopologyToy.ps");
   PsFile.AddTextPage("Razor catalog: golden topology (toy)");

   vector<string> Explanations(11);
   Explanations[0] = "";
   PsFile.AddTextPage(Explanations);

   double HeavyMass = 750;
   double GammaCM = 1.500;
   double BottomMass = 4.2;
   double NuMass = 0;
   double JetK = 0.03;
   double JetP = 0.10;
   double JetThreshold = 30;

   PsFile.AddTextPage("Nominal case");
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.000, BottomMass, NuMass, JetThreshold, JetK, JetP, false);
   
   PsFile.AddTextPage("bbnunu case - gammaCM goes from 1 to 2 in steps of 0.1");
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.000, BottomMass, NuMass, JetThreshold, JetK, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, JetK, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.200, BottomMass, NuMass, JetThreshold, JetK, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.300, BottomMass, NuMass, JetThreshold, JetK, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.400, BottomMass, NuMass, JetThreshold, JetK, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.500, BottomMass, NuMass, JetThreshold, JetK, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.600, BottomMass, NuMass, JetThreshold, JetK, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.700, BottomMass, NuMass, JetThreshold, JetK, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.800, BottomMass, NuMass, JetThreshold, JetK, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.900, BottomMass, NuMass, JetThreshold, JetK, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 2.000, BottomMass, NuMass, JetThreshold, JetK, JetP, true);
   
   PsFile.AddTextPage("bbnunu case - gammaCM set at 1.1, changing jet spectrum");
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, 0.01, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, 0.02, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, 0.03, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, 0.04, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, 0.05, JetP, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, 0.10, JetP, true);
   
   PsFile.AddTextPage("bbnunu case - gammaCM set at 1.1, changing jet count");
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, JetK, 0.30, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, JetK, 0.20, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, JetK, 0.10, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, JetK, 0.05, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, JetK, 0.02, true);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * 1.100, BottomMass, NuMass, JetThreshold, JetK, 0.01, true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double BottomMass, const double NuMass, const double ISRJetMomentumThreshold,
   const double JetK, double JetP, bool BBNuNuCase)
{
   TH1D HMR("HMR", ";MR;", 1000, 0, 2500);
   TH1D HR2("HR2", ";R^{2};", 1000, 0, 1.2);
   TH1D HNJet("HNJet", ";Jet Count;", 10, 0, 10);
   TH1D HJetMomentum("HJetMomentum", ";Jet Momentum", 100, 0, 200);

   HMR.SetStats(0);
   HR2.SetStats(0);
   HNJet.SetStats(0);
   HJetMomentum.SetStats(0);

   if(JetP < 0)
      JetP = exp(-JetK * ISRJetMomentumThreshold);

   for(int iEntry = 0; iEntry < 1000000; iEntry++)
   {
      // Decay angles of the two heavy guys
      double Theta = DrawSine(0, PI);
      double Phi = DrawRandom(-PI, PI);
      double Gamma = Energy / 2 / HeavyMass;
      double Beta = GammaToBeta(Gamma);

      FourVector HeavyParticle1Direction(1, sin(Theta) * cos(Phi), sin(Theta) * sin(Phi), cos(Theta));
      FourVector HeavyParticle2Direction(1, -sin(Theta) * cos(Phi), -sin(Theta) * sin(Phi), -cos(Theta));

      // CM frame child momentum calculation
      double M2 = HeavyMass * HeavyMass;
      double m12 = BottomMass * BottomMass;
      double m22 = NuMass * NuMass;
      double Momentum = sqrt(((M2 - m12 - m22) * (M2 - m12 - m22) - 4 * m12 * m22) / (4 * M2));

      // Inside CM of first heavy particle
      double Theta1 = DrawSine(0, PI);
      double Phi1 = DrawRandom(-PI, PI);
      FourVector Bottom1Heavy1CM;
      Bottom1Heavy1CM.SetSizeThetaPhiMass(Momentum, Theta1, Phi1, BottomMass);
      FourVector Nu1Heavy1CM;
      Nu1Heavy1CM.SetSizeThetaPhiMass(Momentum, PI - Theta1, Phi1 + PI, NuMass);

      // In CM of second heavy particle
      double Theta2 = DrawSine(0, PI);
      double Phi2 = DrawRandom(-PI, PI);
      FourVector Bottom2Heavy2CM;
      Bottom2Heavy2CM.SetSizeThetaPhiMass(Momentum, Theta2, Phi2, BottomMass);
      FourVector Nu2Heavy2CM;
      Nu2Heavy2CM.SetSizeThetaPhiMass(Momentum, PI - Theta2, Phi2 + PI, NuMass);

      // boost to gluon frame
      FourVector Nu1PGluonCM = Nu1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector Bottom1PGluonCM = Bottom1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector Nu2PGluonCM = Nu2Heavy2CM.Boost(HeavyParticle2Direction, Beta);
      FourVector Bottom2PGluonCM = Bottom2Heavy2CM.Boost(HeavyParticle2Direction, Beta);

      // ISR jet(s)
      FourVector ISRTotal;
      vector<FourVector> ISRJets;
      while(DrawRandom(0, 1) < JetP)   // One more jet!
      {
         double ISRTheta = DrawSine(0, PI);
         double ISRPhi = DrawRandom(-PI, PI);
         FourVector ISRJet(1, sin(ISRTheta) * cos(ISRPhi), sin(ISRTheta) * sin(ISRPhi), cos(ISRTheta));
         double ISRJetMomentum = DrawExponential(-JetK, ISRJetMomentumThreshold);
         ISRJet = ISRJet * ISRJetMomentum;

         ISRTotal = ISRTotal + ISRJet;

         ISRJets.push_back(ISRJet);
         HJetMomentum.Fill(ISRJetMomentum);
      }
      HNJet.Fill(ISRJets.size());

      FourVector GluonDirection = -ISRTotal.SpatialNormalize();
      GluonDirection[0] = 1;

      // get gamma/beta of gluon
      double GluonP = ISRTotal.GetP();   // event-wise momentum balance
      double GluonE = sqrt(Energy * Energy + GluonP * GluonP);   // lab frame gluon energy
      double GluonGamma = GluonE / Energy;   // boost needed
      double GluonBeta = GammaToBeta(GluonGamma);

      FourVector Nu1P = Nu1PGluonCM.Boost(GluonDirection, GluonBeta);
      FourVector Bottom1P = Bottom1PGluonCM.Boost(GluonDirection, GluonBeta);
      FourVector Nu2P = Nu2PGluonCM.Boost(GluonDirection, GluonBeta);
      FourVector Bottom2P = Bottom2PGluonCM.Boost(GluonDirection, GluonBeta);

      // calculate missing energy
      FourVector InvisibleTotal = Nu1P + Nu2P;
      if(BBNuNuCase == true)
         InvisibleTotal = Nu2P + Bottom2P;

      // Group into hemispheres
      vector<FourVector> Jets = ISRJets;
      if(BBNuNuCase == true)
      {
         Jets.push_back(Bottom1P);
         Jets.push_back(Nu1P);
      }
      else
      {
         Jets.push_back(Bottom1P);
         Jets.push_back(Bottom2P);
      }

      vector<FourVector> Hemispheres = SplitIntoGroups(Jets, true);

      double MR = GetMR(Hemispheres[0], Hemispheres[1]);
      double MRT = GetMRT(Hemispheres[0], Hemispheres[1], InvisibleTotal);
      double R = GetR(Hemispheres[0], Hemispheres[1], InvisibleTotal);

      HMR.Fill(MR);
      HR2.Fill(R * R);
   }

   TCanvas canvas;

   canvas.Divide(2, 2);

   canvas.cd(1);
   HMR.Draw();
   canvas.cd(1)->SetLogy();

   canvas.cd(2);
   HR2.Draw();
   canvas.cd(2)->SetLogy();

   canvas.cd(3);
   HNJet.Draw();
   canvas.cd(3)->SetLogy();

   canvas.cd(4);
   HJetMomentum.Draw();
   canvas.cd(4)->SetLogy();

   PsFile.AddCanvas(canvas);
}




