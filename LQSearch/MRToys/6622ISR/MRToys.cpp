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
#include "TauHelperFunctions.h"
#include "PlotHelper2.h"

int main(int argc, char *argv[]);
void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double BottomMass, const double NuMass, const double ISRJetMomentum);
void SplitIntoHalf(double V1[4], double V2[4], double V3[4], double V4[4], double Out1[4], double Out2[4]);

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

   PsFileHelper PsFile("MRToy10_ISR.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 10");

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
   Explanations.push_back("MR is reconstructed by the leading two jets.  Gamma CM is always 1.1");
   Explanations.push_back("Check MR distribution changing the ISR jet size");
   PsFile.AddTextPage(Explanations);
   // PsFile.InsertNamedDestination("Explanations");

   double HeavyMass = 300;
   double GammaCM = 1.1;
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

   for(int iEntry = 0; iEntry < 1000000; iEntry++)
   {
      // Decay angles of the two heavy guys
      double Theta = DrawSine(0, PI);
      double Phi = DrawRandom(-PI, PI);
      double Gamma = Energy / 2 / HeavyMass;
      double Beta = GammaToBeta(Gamma);

      double HeavyParticle1Direction[4] = {1, sin(Theta) * cos(Phi), sin(Theta) * sin(Phi), cos(Theta)};
      double HeavyParticle2Direction[4] = {1, -sin(Theta) * cos(Phi), -sin(Theta) * sin(Phi), -cos(Theta)};

      // CM frame child momentum calculation
      double M2 = HeavyMass * HeavyMass;
      double m12 = BottomMass * BottomMass;
      double m22 = NuMass * NuMass;
      double Momentum = sqrt(((M2 - m12 - m22) * (M2 - m12 - m22) - 4 * m12 * m22) / (4 * M2));

      // Inside CM of first heavy particle
      double Theta1 = DrawSine(0, PI);
      double Phi1 = DrawRandom(-PI, PI);
      double Bottom1Heavy1CM[4] = {1, sin(Theta1) * cos(Phi1), sin(Theta1) * sin(Phi1), cos(Theta1)};
      double Nu1Heavy1CM[4] = {1, -sin(Theta1) * cos(Phi1), -sin(Theta1) * sin(Phi1), -cos(Theta1)};

      for(int i = 1; i <= 3; i++)
      {
         Bottom1Heavy1CM[i] = Bottom1Heavy1CM[i] * Momentum;
         Nu1Heavy1CM[i] = Nu1Heavy1CM[i] * Momentum;
      }
      Bottom1Heavy1CM[0] = sqrt(BottomMass * BottomMass + Momentum * Momentum);
      Nu1Heavy1CM[0] = sqrt(NuMass * NuMass + Momentum * Momentum);
      
      // In CM of second heavy particle
      double Theta2 = DrawSine(0, PI);
      double Phi2 = DrawRandom(-PI, PI);
      double Bottom2Heavy2CM[4] = {1, sin(Theta2) * cos(Phi2), sin(Theta2) * sin(Phi2), cos(Theta2)};
      double Nu2Heavy2CM[4] = {1, -sin(Theta2) * cos(Phi2), -sin(Theta2) * sin(Phi2), -cos(Theta2)};

      for(int i = 1; i <= 3; i++)
      {
         Bottom2Heavy2CM[i] = Bottom2Heavy2CM[i] * Momentum;
         Nu2Heavy2CM[i] = Nu2Heavy2CM[i] * Momentum;
      }
      Bottom2Heavy2CM[0] = sqrt(BottomMass * BottomMass + Momentum * Momentum);
      Nu2Heavy2CM[0] = sqrt(NuMass * NuMass + Momentum * Momentum);

      // boost to gluon frame
      double Nu1PGluonCM[4], Bottom1PGluonCM[4];
      double Nu2PGluonCM[4], Bottom2PGluonCM[4];

      Boost(Nu1Heavy1CM, Nu1PGluonCM, HeavyParticle1Direction, Beta);
      Boost(Bottom1Heavy1CM, Bottom1PGluonCM, HeavyParticle1Direction, Beta);
      Boost(Nu2Heavy2CM, Nu2PGluonCM, HeavyParticle2Direction, Beta);
      Boost(Bottom2Heavy2CM, Bottom2PGluonCM, HeavyParticle2Direction, Beta);

      // ISR jet
      double ISRTheta = DrawSine(0, PI);
      double ISRPhi = DrawRandom(-PI, PI);
      double ISRJet[4] = {1, sin(ISRTheta) * cos(ISRPhi), sin(ISRTheta) * sin(ISRPhi), cos(ISRTheta)};
      for(int i = 0; i < 4; i++)
         ISRJet[i] = ISRJet[i] * ISRJetMomentum;
      double GluonDirection[4] = {1, -sin(ISRTheta) * cos(ISRPhi), -sin(ISRTheta) * sin(ISRPhi), -cos(ISRTheta)};

      // get gamma/beta of gluon
      double GluonP = GetP(ISRJet);   // event-wise momentum balance
      double GluonE = sqrt(Energy * Energy + GluonP * GluonP);   // lab frame gluon energy
      double GluonGamma = GluonE / Energy;   // boost needed
      double GluonBeta = GammaToBeta(GluonGamma);

      double Nu1P[4], Bottom1P[4];
      double Nu2P[4], Bottom2P[4];
      Boost(Nu1PGluonCM, Nu1P, GluonDirection, GluonBeta);
      Boost(Bottom1PGluonCM, Bottom1P, GluonDirection, GluonBeta);
      Boost(Nu2PGluonCM, Nu2P, GluonDirection, GluonBeta);
      Boost(Bottom2PGluonCM, Bottom2P, GluonDirection, GluonBeta);

      // calculate missing energy
      double InvisibleTotal[4];
      InvisibleTotal[0] = Nu1P[0] + Nu2P[0];
      InvisibleTotal[1] = Nu1P[1] + Nu2P[1];
      InvisibleTotal[2] = Nu1P[2] + Nu2P[2];
      InvisibleTotal[3] = Nu1P[3] + Nu2P[3];

      // Find leading jets
      multimap<double, double *, greater<double> > SortJets;
      SortJets.insert(pair<double, double *>(GetPT(Bottom1P), Bottom1P));
      SortJets.insert(pair<double, double *>(GetPT(Bottom2P), Bottom2P));
      SortJets.insert(pair<double, double *>(GetPT(ISRJet), ISRJet));

      multimap<double, double *, greater<double> >::iterator iter = SortJets.begin();
      double *LeadingJetP = iter->second;
      iter++;
      double *SubLeadingJetP = iter->second;

      double MR = GetMR(LeadingJetP, SubLeadingJetP);
      double MRT = GetMRT(LeadingJetP, SubLeadingJetP, InvisibleTotal);
      double R = GetR(LeadingJetP, SubLeadingJetP, InvisibleTotal);

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

void SplitIntoHalf(double V1[4], double V2[4], double V3[4], double V4[4], double Out1[4], double Out2[4])
{
   double BestSumM2 = -1;
   Out1[0] = 0;   Out2[0] = 0;
   Out1[1] = 0;   Out2[1] = 0;
   Out1[2] = 0;   Out2[2] = 0;
   Out1[3] = 0;   Out2[3] = 0;

   for(int i = 0; i < 8; i++)
   {
      double TempOut1[4] = {V1[0], V1[1], V1[2], V1[3]};
      double TempOut2[4] = {0, 0, 0, 0};

      if(i % 2 == 0)
      {
         TempOut1[0] = TempOut1[0] + V2[0];
         TempOut1[1] = TempOut1[1] + V2[1];
         TempOut1[2] = TempOut1[2] + V2[2];
         TempOut1[3] = TempOut1[3] + V2[3];
      }
      else
      {
         TempOut2[0] = TempOut2[0] + V2[0];
         TempOut2[1] = TempOut2[1] + V2[1];
         TempOut2[2] = TempOut2[2] + V2[2];
         TempOut2[3] = TempOut2[3] + V2[3];
      }

      if((i / 2) % 2 == 0)
      {
         TempOut1[0] = TempOut1[0] + V3[0];
         TempOut1[1] = TempOut1[1] + V3[1];
         TempOut1[2] = TempOut1[2] + V3[2];
         TempOut1[3] = TempOut1[3] + V3[3];
      }
      else
      {
         TempOut2[0] = TempOut2[0] + V3[0];
         TempOut2[1] = TempOut2[1] + V3[1];
         TempOut2[2] = TempOut2[2] + V3[2];
         TempOut2[3] = TempOut2[3] + V3[3];
      }

      if((i / 4) % 2 == 0)
      {
         TempOut1[0] = TempOut1[0] + V4[0];
         TempOut1[1] = TempOut1[1] + V4[1];
         TempOut1[2] = TempOut1[2] + V4[2];
         TempOut1[3] = TempOut1[3] + V4[3];
      }
      else
      {
         TempOut2[0] = TempOut2[0] + V4[0];
         TempOut2[1] = TempOut2[1] + V4[1];
         TempOut2[2] = TempOut2[2] + V4[2];
         TempOut2[3] = TempOut2[3] + V4[3];
      }

      double SumM2 = GetMass2(TempOut1) + GetMass2(TempOut2);

      if(BestSumM2 < 0 || SumM2 < BestSumM2)
      {
         Out1[0] = TempOut1[0];
         Out1[1] = TempOut1[1];
         Out1[2] = TempOut1[2];
         Out1[3] = TempOut1[3];
         
         Out2[0] = TempOut2[0];
         Out2[1] = TempOut2[1];
         Out2[2] = TempOut2[2];
         Out2[3] = TempOut2[3];

         BestSumM2 = SumM2;
      }
   }
}




