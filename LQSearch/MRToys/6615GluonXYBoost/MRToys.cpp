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

#include "DrawRandom.h"
#include "TauHelperFunctions.h"
#include "PlotHelper2.h"

struct ToyResult;
int main(int argc, char *argv[]);
ToyResult DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double VisibleMass, const double InvisibleMass, const double XYBoostBeta);

struct ToyResult
{
   double MRMean;
   double MRRMS;
};

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

   PsFileHelper PsFile("MRToy5_XYBoost.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 5");

   vector<string> Explanations;
   Explanations.push_back("Setup: gluon with spatial momentum in xy direction, decay into two heavy object");
   Explanations.push_back("of certain mass, each then further decays into two light objects");
   Explanations.push_back("one of them visible, one invisible.  Gamma CM here is always 1.01");
   Explanations.push_back("Visible mass: 4.2, Invisible mass: 0, Heavy mass: 300");
   Explanations.push_back("");
   Explanations.push_back("Assume non-perfect reconstruction of the visible final objects");
   Explanations.push_back("Check MR distribution changing xy boost");
   PsFile.AddTextPage(Explanations);

   TGraphErrors MRSummaryGraph;
   MRSummaryGraph.SetNameTitle("MRSummaryGraph", "Summary of MR changing transverse boost");

   double ValuesToTry[30] = {0, 0.001, 0.002, 0.003, 0.004, 0.005, 0.01, 0.02, 0.03, 0.04, 0.05,
      0.075, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99};
   for(int i = 0; i < 30; i++)
   {
      ToyResult Result = DoToyAndAppendPlots(PsFile, 300, 606, 4.2, 0, ValuesToTry[i]);
      MRSummaryGraph.SetPoint(i, BetaToGamma(ValuesToTry[i]), Result.MRMean / 300);
      MRSummaryGraph.SetPointError(i, 0, Result.MRRMS / 300);
   }

   PsFile.AddPlot(MRSummaryGraph, "ap", false, false, false, true);
   PsFile.AddPlot(MRSummaryGraph, "ap", false, false, false, false);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

ToyResult DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double VisibleMass, const double InvisibleMass, const double XYBoostBeta)
{
   TH1D HMR("HMR", Form("MR distribution, Mass %.2f, Energy %.2f, Visible %.2f, Invisible %.2f, Beta %.3f",
      HeavyMass, Energy, VisibleMass, InvisibleMass, XYBoostBeta), 200, 0, HeavyMass * 5);
   TH1D HMRT("HMRT", Form("MRT distribution, Mass %.2f, Energy %.2f, Visible %.2f, Invisible %.2f",
      HeavyMass, Energy, VisibleMass, InvisibleMass), 200, 0, HeavyMass * 5);
   TH1D HR("HR", Form("R distribution, Mass %.2f, Energy %.2f, Visible %.2f, Invisible %.2f",
      HeavyMass, Energy, VisibleMass, InvisibleMass), 200, 0, 1.5);
   TH2D HMRVsR("HMRVsR", "MR vs R^{2};MR;R^{2}", 200, 0, HeavyMass * 5, 200, 0, 1.5);

   double TotalMR = 0;
   double TotalMR2 = 0;
   double EntryCount = 0;

   for(int iEntry = 0; iEntry < 5000000; iEntry++)
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

      // do a final xy direction boost;
      double InitialDirectionPhi = DrawRandom(-PI, PI);
      double InitialDirection[4] = {1, cos(InitialDirectionPhi), sin(InitialDirectionPhi), 0};

      double VisibleChild1Final[4], InvisibleChild1Final[4];
      double VisibleChild2Final[4], InvisibleChild2Final[4];

      Boost(VisibleChild1, VisibleChild1Final, InitialDirection, XYBoostBeta);
      Boost(VisibleChild2, VisibleChild2Final, InitialDirection, XYBoostBeta);
      Boost(InvisibleChild1, InvisibleChild1Final, InitialDirection, XYBoostBeta);
      Boost(InvisibleChild2, InvisibleChild2Final, InitialDirection, XYBoostBeta);

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
      HMRVsR.Fill(MR, R * R);

      if(MR > 0 && MR < 1e8)
      {
         TotalMR = TotalMR + MR;
         TotalMR2 = TotalMR2 + MR * MR;
         EntryCount = EntryCount + 1;
      }
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

   ToyResult Result;
   Result.MRMean = TotalMR / EntryCount;
   Result.MRRMS = sqrt((TotalMR2 - TotalMR * TotalMR / EntryCount) / EntryCount);

   return Result;
}





