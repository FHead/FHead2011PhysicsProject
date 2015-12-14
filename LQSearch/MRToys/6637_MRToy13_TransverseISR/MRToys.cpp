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

#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"

int main(int argc, char *argv[]);
void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double BottomMass, const double NuMass, const double ISRJetMomentum);

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

   PsFileHelper PsFile("MRToy13_TransverseISR.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 13");

   vector<string> Explanations;
   Explanations.push_back("Setup: gluon decay into two heavy object");
   Explanations.push_back("of certain mass, each then further decays into two lighter objects");
   Explanations.push_back("one is visible (mass 4.2), another one is invisible (mass 0)");
   Explanations.push_back("");
   Explanations.push_back("Add an ISR jet in transverse direction balancing the LQLQ system");
   Explanations.push_back("");
   Explanations.push_back("Assume perfect reconstruction of the visible final objects");
   Explanations.push_back("MR is reconstructed by hemispheres.  Gamma CM is always 1.00");
   Explanations.push_back("Check MR distribution changing the ISR jet size");
   PsFile.AddTextPage(Explanations);

   double HeavyMass = 300;
   double GammaCM = 1.00;
   double BottomMass = 4.2;
   double NuMass = 0;

   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 0);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 10);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 20);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 30);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 40);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 50);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 60);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 70);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 80);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 90);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 100);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 125);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 150);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 175);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 200);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 225);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 250);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 275);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 300);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 350);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 400);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 450);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 500);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 600);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 700);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 800);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 900);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 1000);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double BottomMass, const double NuMass, const double ISRJetMomentum)
{
   TH1D HMR("HMR", Form("MR distribution, HeavyMass %.2f, Energy %.2f, BottomMass %.2f, NuMass %.2f",
      HeavyMass, Energy, BottomMass, NuMass), 100, 0, HeavyMass * 4);
   TH1D HMRT("HMRT", Form("MRT distribution, ISR Jet Momentum %.2f", ISRJetMomentum), 100, 0, HeavyMass * 4);
   TH1D HR("HR", "R distribution", 100, 0, 1.5);
   TH2D HMRVsR("HMRVsR", "MR vs R;MR;R", 100, 0, HeavyMass * 4, 100, 0, 1.5);

   for(int iEntry = 0; iEntry < 100000; iEntry++)
   {
      // Decay angles of the two heavy guys
      double Theta = DrawSine(0, PI);
      double Phi = DrawRandom(-PI, PI);
      double Gamma = Energy / 2 / HeavyMass;
      double Beta = GammaToBeta(Gamma);

      FourVector HeavyParticle1Direction;   HeavyParticle1Direction.SetSizeThetaPhi(1, Theta, Phi);
      FourVector HeavyParticle2Direction;   HeavyParticle2Direction.SetSizeThetaPhi(1, PI - Theta, Phi + PI);

      // CM frame child momentum calculation
      double M2 = HeavyMass * HeavyMass;
      double m12 = BottomMass * BottomMass;
      double m22 = NuMass * NuMass;
      double Momentum = sqrt(((M2 - m12 - m22) * (M2 - m12 - m22) - 4 * m12 * m22) / (4 * M2));

      // Inside CM of first heavy particle
      double Theta1 = DrawSine(0, PI);
      double Phi1 = DrawRandom(-PI, PI);
      FourVector Bottom1Heavy1CM;   Bottom1Heavy1CM.SetSizeThetaPhiMass(Momentum, Theta1, Phi1, BottomMass);
      FourVector Nu1Heavy1CM;       Nu1Heavy1CM.SetSizeThetaPhiMass(Momentum, PI - Theta1, Phi1 + PI, NuMass);

      // In CM of second heavy particle
      double Theta2 = DrawSine(0, PI);
      double Phi2 = DrawRandom(-PI, PI);
      FourVector Bottom2Heavy2CM;   Bottom2Heavy2CM.SetSizeThetaPhiMass(Momentum, Theta2, Phi2, BottomMass);
      FourVector Nu2Heavy2CM;       Nu2Heavy2CM.SetSizeThetaPhiMass(Momentum, PI - Theta2, Phi2 + PI, NuMass);
      
      // boost to gluon frame
      FourVector Bottom1PGluonCM = Bottom1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector Nu1PGluonCM = Nu1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector Bottom2PGluonCM = Bottom2Heavy2CM.Boost(HeavyParticle2Direction, Beta);
      FourVector Nu2PGluonCM = Nu2Heavy2CM.Boost(HeavyParticle2Direction, Beta);

      // ISR jet
      double ISRTheta = PI / 2;
      double ISRPhi = DrawRandom(-PI, PI);
      FourVector ISRJet;           ISRJet.SetSizeThetaPhi(ISRJetMomentum, ISRTheta, ISRPhi);
      FourVector GluonDirection;   GluonDirection.SetSizeThetaPhi(ISRJetMomentum, PI - ISRTheta, ISRPhi + PI);

      // get gamma/beta of gluon
      double GluonP = ISRJet.GetP();   // event-wise momentum balance
      double GluonE = sqrt(Energy * Energy + GluonP * GluonP);   // lab frame gluon energy
      double GluonGamma = GluonE / Energy;   // boost needed
      double GluonBeta = GammaToBeta(GluonGamma);

      FourVector Bottom1P = Bottom1PGluonCM.Boost(GluonDirection, GluonBeta);
      FourVector Nu1P = Nu1PGluonCM.Boost(GluonDirection, GluonBeta);
      FourVector Bottom2P = Bottom2PGluonCM.Boost(GluonDirection, GluonBeta);
      FourVector Nu2P = Nu2PGluonCM.Boost(GluonDirection, GluonBeta);

      // calculate missing energy
      FourVector InvisibleTotal = Nu1P + Nu2P;
      
      // Find mega-jets
      vector<FourVector> Jets;
      Jets.push_back(Bottom1P);
      Jets.push_back(Bottom2P);
      Jets.push_back(ISRJet);

      vector<FourVector> Groups = SplitIntoGroups(Jets);

      double MR = GetMR(Groups[0], Groups[1]);
      double MRT = GetMRT(Groups[0], Groups[1], InvisibleTotal);
      double R = GetR(Groups[0], Groups[1], InvisibleTotal);

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




