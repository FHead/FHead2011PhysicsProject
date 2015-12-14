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
#include "SetStyle.h"

int main(int argc, char *argv[]);
void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double BottomMass, const double NuMass, const double ISRJetMomentum);

int main(int argc, char *argv[])
{
   SetStyle();

   PsFileHelper PsFile("MRToy21_ISRGrouping.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 21");

   // vector<string> TOCItems;
   // TOCItems.push_back("Explanations");

   // vector<string> Destinations;
   // Destinations.push_back("Explanations");

   // PsFile.AddTableOfContentPage(TOCItems, Destinations);
   // PsFile.InsertNamedDestination("TableOfContentPage");
   // PsFile.SetAutomaticHomeButton(true, "TableOfContentPage");

   vector<string> Explanations;
   Explanations.push_back("Setup: gluon decay into two heavy object");
   Explanations.push_back("of certain mass, each then further decays into two lighter objects");
   Explanations.push_back("one is visible (mass 4.2), another one is invisible (mass 0)");
   Explanations.push_back("");
   Explanations.push_back("Add an ISR jet in random direction balancing the LQLQ system");
   Explanations.push_back("");
   Explanations.push_back("Assume perfect reconstruction of the visible final objects");
   Explanations.push_back("MR is reconstructed by hemispheres.  Gamma CM is always ???");
   Explanations.push_back("Check MR distribution changing the ISR jet size");
   PsFile.AddTextPage(Explanations);
   // PsFile.InsertNamedDestination("Explanations");

   double HeavyMass = 300;
   double GammaCM = 1.000;
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
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 150);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 200);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 300);
   DoToyAndAppendPlots(PsFile, HeavyMass, HeavyMass * 2 * GammaCM, BottomMass, NuMass, 500);

   PsFile.AddTextPage("Part 2!  Change heavy mass, leave ISR size alone");
   DoToyAndAppendPlots(PsFile, 300, 300 * 2 * GammaCM, BottomMass, NuMass, 10);
   DoToyAndAppendPlots(PsFile, 350, 350 * 2 * GammaCM, BottomMass, NuMass, 10);
   DoToyAndAppendPlots(PsFile, 400, 400 * 2 * GammaCM, BottomMass, NuMass, 10);
   DoToyAndAppendPlots(PsFile, 500, 500 * 2 * GammaCM, BottomMass, NuMass, 10);
   DoToyAndAppendPlots(PsFile, 600, 600 * 2 * GammaCM, BottomMass, NuMass, 10);
   DoToyAndAppendPlots(PsFile, 800, 800 * 2 * GammaCM, BottomMass, NuMass, 10);
   DoToyAndAppendPlots(PsFile, 1000, 1000 * 2 * GammaCM, BottomMass, NuMass, 10);
   DoToyAndAppendPlots(PsFile, 2000, 2000 * 2 * GammaCM, BottomMass, NuMass, 10);
   DoToyAndAppendPlots(PsFile, 5000, 5000 * 2 * GammaCM, BottomMass, NuMass, 10);

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

   TH1D HMR_R04("HMR_R04", "MR, R > 0.4", 100, 0, HeavyMass * 4);
   TH1D HMR_R05("HMR_R05", "MR, R > 0.5", 100, 0, HeavyMass * 4);
   TH1D HMR_R06("HMR_R06", "MR, R > 0.6", 100, 0, HeavyMass * 4);
   TH1D HMR_R07("HMR_R07", "MR, R > 0.7", 100, 0, HeavyMass * 4);
   TH1D HMR_R08("HMR_R08", "MR, R > 0.8", 100, 0, HeavyMass * 4);

   TH1D HR2_MR400("HR2_MR400", "R^2 distribution, MR > 400;R * R", 100, 0, 1.5);
   TH1D HR2_MR500("HR2_MR500", "R^2 distribution, MR > 500;R * R", 100, 0, 1.5);
   TH1D HR2_MR600("HR2_MR600", "R^2 distribution, MR > 600;R * R", 100, 0, 1.5);
   TH1D HR2_MR700("HR2_MR700", "R^2 distribution, MR > 700;R * R", 100, 0, 1.5);
   TH1D HR2_MR800("HR2_MR800", "R^2 distribution, MR > 800;R * R", 100, 0, 1.5);
   
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

      // ISR jet
      double ISRTheta = DrawSine(0, PI);
      double ISRPhi = DrawRandom(-PI, PI);
      FourVector ISRJet(1, sin(ISRTheta) * cos(ISRPhi), sin(ISRTheta) * sin(ISRPhi), cos(ISRTheta));
      ISRJet = ISRJet * ISRJetMomentum;
      FourVector GluonDirection(1, -sin(ISRTheta) * cos(ISRPhi), -sin(ISRTheta) * sin(ISRPhi), -cos(ISRTheta));

      // get gamma/beta of gluon
      double GluonP = ISRJet.GetP();   // event-wise momentum balance
      double GluonE = sqrt(Energy * Energy + GluonP * GluonP);   // lab frame gluon energy
      double GluonGamma = GluonE / Energy;   // boost needed
      double GluonBeta = GammaToBeta(GluonGamma);

      FourVector Nu1P = Nu1PGluonCM.Boost(GluonDirection, GluonBeta);
      FourVector Bottom1P = Bottom1PGluonCM.Boost(GluonDirection, GluonBeta);
      FourVector Nu2P = Nu2PGluonCM.Boost(GluonDirection, GluonBeta);
      FourVector Bottom2P = Bottom2PGluonCM.Boost(GluonDirection, GluonBeta);

      // calculate missing energy
      FourVector InvisibleTotal = Nu1P + Nu2P;

      // Group into hemispheres
      vector<FourVector> Jets;
      Jets.push_back(Bottom1P);
      Jets.push_back(Bottom2P);
      Jets.push_back(ISRJet);

      vector<FourVector> Hemispheres = SplitIntoGroups(Jets, true);

      double MR = GetMR(Hemispheres[0], Hemispheres[1]);
      double MRT = GetMRT(Hemispheres[0], Hemispheres[1], InvisibleTotal);
      double R = GetR(Hemispheres[0], Hemispheres[1], InvisibleTotal);

      HMR.Fill(MR);
      HMRT.Fill(MRT);
      HR.Fill(R);
      HMRVsR.Fill(MR, R);

      if(R > 0.4)
         HMR_R04.Fill(MR);
      if(R > 0.5)
         HMR_R05.Fill(MR);
      if(R > 0.6)
         HMR_R06.Fill(MR);
      if(R > 0.7)
         HMR_R07.Fill(MR);
      if(R > 0.8)
         HMR_R08.Fill(MR);

      if(MR > 400)
         HR2_MR400.Fill(R * R);
      if(MR > 500)
         HR2_MR500.Fill(R * R);
      if(MR > 600)
         HR2_MR600.Fill(R * R);
      if(MR > 700)
         HR2_MR700.Fill(R * R);
      if(MR > 800)
         HR2_MR800.Fill(R * R);
   }

   TCanvas canvas;

   canvas.Divide(2, 2);

   canvas.cd(1);
   HMR.Draw();
   HMRT.Draw("same");
   canvas.cd(1)->SetLogy();

   canvas.cd(2);
   // HMRT.Draw();
   HMR_R04.Draw();
   HMR_R05.Draw("same");
   HMR_R06.Draw("same");
   HMR_R07.Draw("same");
   HMR_R08.Draw("same");
   canvas.cd(2)->SetLogy();
   
   canvas.cd(3);
   HR2_MR400.Draw();
   HR2_MR500.Draw("same");
   HR2_MR600.Draw("same");
   HR2_MR700.Draw("same");
   HR2_MR800.Draw("same");
   canvas.cd(3)->SetLogy();
   
   canvas.cd(4);
   HMRVsR.Draw("colz");

   PsFile.AddCanvas(canvas);
}




