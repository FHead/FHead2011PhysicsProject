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

#include "DrawRandom.h"
#include "TauHelperFunctions.h"
#include "PlotHelper2.h"

int main(int argc, char *argv[]);
double DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double VisibleMass, const double InvisibleMass, const double ZBoostBeta);

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

   PsFileHelper PsFile("MRToy4_ZBoostBeta.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 4");

   vector<string> Explanations;
   Explanations.push_back("Setup: gluon with spatial momentum in z direction, decay into two heavy object");
   Explanations.push_back("of certain mass, each then further decays into two light objects");
   Explanations.push_back("one of them visible, one invisible.  Gamma CM here is always 1.01");
   Explanations.push_back("Visible mass: 4.2, Invisible mass: 0, Heavy mass: 300");
   Explanations.push_back("");
   Explanations.push_back("Assume non-perfect reconstruction of the visible final objects");
   Explanations.push_back("Check MR distribution changing z boost");
   PsFile.AddTextPage(Explanations);

   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.0);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.1);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.2);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.3);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.4);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.5);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.6);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.7);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.8);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.9);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.99);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.999);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.9999);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, 0.99999);
   DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, -0.9);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

double DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double VisibleMass, const double InvisibleMass, const double ZBoostBeta)
{
   TH1D HMR("HMR", Form("MR distribution, Mass %.2f, Energy %.2f, Visible %.2f, Invisible %.2f, Beta %.4f",
      HeavyMass, Energy, VisibleMass, InvisibleMass, ZBoostBeta), 200, 0, HeavyMass * 4);
   TH1D HMRT("HMRT", Form("MRT distribution, Mass %.2f, Energy %.2f, Visible %.2f, Invisible %.2f",
      HeavyMass, Energy, VisibleMass, InvisibleMass), 200, 0, HeavyMass * 4);
   TH1D HR("HR", Form("R distribution, Mass %.2f, Energy %.2f, Visible %.2f, Invisible %.2f",
      HeavyMass, Energy, VisibleMass, InvisibleMass), 100, 0, 1.5);
   TH2D HMRVsR("HMRVsR", "MR vs R;MR;R", 100, 0, HeavyMass * 2, 100, 0, 1.5);

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
      double m12 = VisibleMass * VisibleMass;
      double m22 = InvisibleMass * InvisibleMass;
      double Momentum = sqrt(((M2 - m12 - m22) * (M2 - m12 - m22) - 4 * m12 * m22) / (4 * M2));

      // Inside CM of first heavy particle
      double Theta1 = DrawSine(0, PI);
      double Phi1 = DrawRandom(-PI, PI);
      double VisibleChild1Heavy1CM[4] = {1, sin(Theta1) * cos(Phi1), sin(Theta1) * sin(Phi1), cos(Theta1)};
      double InvisibleChild1Heavy1CM[4] = {1, -sin(Theta1) * cos(Phi1), -sin(Theta1) * sin(Phi1), -cos(Theta1)};

      for(int i = 1; i <= 3; i++)
      {
         VisibleChild1Heavy1CM[i] = VisibleChild1Heavy1CM[i] * Momentum;
         InvisibleChild1Heavy1CM[i] = InvisibleChild1Heavy1CM[i] * Momentum;
      }
      VisibleChild1Heavy1CM[0] = sqrt(VisibleMass * VisibleMass + Momentum * Momentum);
      InvisibleChild1Heavy1CM[0] = sqrt(InvisibleMass * InvisibleMass + Momentum * Momentum);
      
      // In CM of second heavy particle
      double Theta2 = DrawSine(0, PI);
      double Phi2 = DrawRandom(-PI, PI);
      double VisibleChild2Heavy2CM[4] = {1, sin(Theta2) * cos(Phi2), sin(Theta2) * sin(Phi2), cos(Theta2)};
      double InvisibleChild2Heavy2CM[4] = {1, -sin(Theta2) * cos(Phi2), -sin(Theta2) * sin(Phi2), -cos(Theta2)};
      
      for(int i = 1; i <= 3; i++)
      {
         VisibleChild2Heavy2CM[i] = VisibleChild2Heavy2CM[i] * Momentum;
         InvisibleChild2Heavy2CM[i] = InvisibleChild2Heavy2CM[i] * Momentum;
      }
      VisibleChild2Heavy2CM[0] = sqrt(VisibleMass * VisibleMass + Momentum * Momentum);
      InvisibleChild2Heavy2CM[0] = sqrt(InvisibleMass * InvisibleMass + Momentum * Momentum);

      // boost back to gluon frame
      double VisibleChild1[4], InvisibleChild1[4];
      double VisibleChild2[4], InvisibleChild2[4];

      Boost(VisibleChild1Heavy1CM, VisibleChild1, HeavyParticle1Direction, Beta);
      Boost(InvisibleChild1Heavy1CM, InvisibleChild1, HeavyParticle1Direction, Beta);
      Boost(VisibleChild2Heavy2CM, VisibleChild2, HeavyParticle2Direction, Beta);
      Boost(InvisibleChild2Heavy2CM, InvisibleChild2, HeavyParticle2Direction, Beta);

      // do a final z direction boost;
      double VisibleChild1Final[4], InvisibleChild1Final[4];
      double VisibleChild2Final[4], InvisibleChild2Final[4];

      BoostZ(VisibleChild1, VisibleChild1Final, ZBoostBeta);
      BoostZ(VisibleChild2, VisibleChild2Final, ZBoostBeta);
      BoostZ(InvisibleChild1, InvisibleChild1Final, ZBoostBeta);
      BoostZ(InvisibleChild2, InvisibleChild2Final, ZBoostBeta);

      // collect result
      double InvisibleTotal[4];
      InvisibleTotal[0] = InvisibleChild1Final[0] + InvisibleChild2Final[0];
      InvisibleTotal[1] = InvisibleChild1Final[1] + InvisibleChild2Final[1];
      InvisibleTotal[2] = InvisibleChild1Final[2] + InvisibleChild2Final[2];
      InvisibleTotal[3] = InvisibleChild1Final[3] + InvisibleChild2Final[3];

      double MR = GetMR(VisibleChild1Final, VisibleChild2Final);
      double MRT = GetMRT(VisibleChild1Final, VisibleChild2Final, InvisibleTotal);
      double R = GetR(VisibleChild1Final, VisibleChild2Final, InvisibleTotal);

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

   return HMR.GetMean();
}





