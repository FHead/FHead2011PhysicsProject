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
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"

int main(int argc, char *argv[]);
double DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double VisibleMass, const double InvisibleMass, const double BetaX);

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

   PsFileHelper PsFile("MRToy3_StaticGluon_CheckingXBoost.ps");
   PsFile.AddTextPage("Toys to understand MRStar better - part 3");

   vector<string> Explanations;
   Explanations.push_back("Setup: gluon with spatial momentum zero, decay into two heavy object");
   Explanations.push_back("of certain mass (300 GeV), each then further decays into two light objects");
   Explanations.push_back("one of them visible (4.2 GeV), one invisible (0 GeV)");
   Explanations.push_back("");
   Explanations.push_back("Assume perfect reconstruction of the visible final objects");
   Explanations.push_back("Check MRStar and RStar distribution changing x boost, GammaCM = 1.05");
   PsFile.AddTextPage(Explanations);

   DoToyAndAppendPlots(PsFile, 300, 630, 4.2, 0, 0);
   DoToyAndAppendPlots(PsFile, 300, 630, 4.2, 0, 0.1);
   DoToyAndAppendPlots(PsFile, 300, 630, 4.2, 0, 0.2);
   DoToyAndAppendPlots(PsFile, 300, 630, 4.2, 0, 0.5);
   DoToyAndAppendPlots(PsFile, 300, 630, 4.2, 0, 0.8);
   DoToyAndAppendPlots(PsFile, 300, 630, 4.2, 0, 0.9);
   DoToyAndAppendPlots(PsFile, 300, 630, 4.2, 0, 0.99);
   DoToyAndAppendPlots(PsFile, 300, 630, 4.2, 0, 0.999);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

double DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double VisibleMass, const double InvisibleMass, const double BetaX)
{
   TH1D HMRStar("HMRStar", Form("MRStar distribution, Mass %.2f, Energy %.2f, Visible %.2f, Invisible %.2f",
      HeavyMass, Energy, VisibleMass, InvisibleMass), 100, 0, HeavyMass * 2);
   TH1D HMRT("HMRT", Form("MRT distribution, Mass %.2f, Energy %.2f, Visible %.2f, Invisible %.2f",
      HeavyMass, Energy, VisibleMass, InvisibleMass), 100, 0, HeavyMass * 2);
   TH1D HRStar("HRStar", Form("RStar distribution, Mass %.2f, Energy %.2f, Visible %.2f, Invisible %.2f",
      HeavyMass, Energy, VisibleMass, InvisibleMass), 100, 0, 1.5);
   TH2D HMRStarVsRStar("HMRStarVsRStar", "MRStar vs RStar;MRStar;RStar", 100, 0, HeavyMass * 2, 100, 0, 1.5);
   TH1D HGammaRStar("HGammaRStar", "Gamma RStar", 100, 0, 10);
   TH1D HGammaRStarMRStar("HGammaRStarMRStar", "GammaStar * MRStar", 100, 0, HeavyMass * 2);
   TH2D HGammaRStarMRStarVsRStar("HGammaRStarMRStarVsRStar", "GammaStar * MRStar vs. RStar",
      100, 0, HeavyMass * 2, 100, 0, 1.5);
   TH2D HMRVsMRStar("HMRVsMRStar", "MR vs. MR star;MR;MRStar", 100, 0, HeavyMass * 2, 100, 0, HeavyMass * 2);
   TH2D HRVsRStar("HRVsRStar", "R vs. R star;R;RStar", 100, 0, 1.5, 100, 0, 1.5);

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
      double m12 = VisibleMass * VisibleMass;
      double m22 = InvisibleMass * InvisibleMass;
      double Momentum = sqrt(((M2 - m12 - m22) * (M2 - m12 - m22) - 4 * m12 * m22) / (4 * M2));

      // Inside CM of first heavy particle
      double Theta1 = DrawSine(0, PI);
      double Phi1 = DrawRandom(-PI, PI);
      FourVector VisibleChild1Heavy1CM(1, sin(Theta1) * cos(Phi1), sin(Theta1) * sin(Phi1), cos(Theta1));
      FourVector InvisibleChild1Heavy1CM(1, -sin(Theta1) * cos(Phi1), -sin(Theta1) * sin(Phi1), -cos(Theta1));
      
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
      FourVector VisibleChild2Heavy2CM(1, sin(Theta2) * cos(Phi2), sin(Theta2) * sin(Phi2), cos(Theta2));
      FourVector InvisibleChild2Heavy2CM(1, -sin(Theta2) * cos(Phi2), -sin(Theta2) * sin(Phi2), -cos(Theta2));
      
      for(int i = 1; i <= 3; i++)
      {
         VisibleChild2Heavy2CM[i] = VisibleChild2Heavy2CM[i] * Momentum;
         InvisibleChild2Heavy2CM[i] = InvisibleChild2Heavy2CM[i] * Momentum;
      }
      VisibleChild2Heavy2CM[0] = sqrt(VisibleMass * VisibleMass + Momentum * Momentum);
      InvisibleChild2Heavy2CM[0] = sqrt(InvisibleMass * InvisibleMass + Momentum * Momentum);

      // boost back to gluon frame
      FourVector VisibleChild1GluonCM = VisibleChild1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector InvisibleChild1GluonCM = InvisibleChild1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector VisibleChild2GluonCM = VisibleChild2Heavy2CM.Boost(HeavyParticle2Direction, Beta);
      FourVector InvisibleChild2GluonCM = InvisibleChild2Heavy2CM.Boost(HeavyParticle2Direction, Beta);

      // boost to lab frame
      FourVector XDirection(1, 1, 0, 0);   // vector in z direction
      FourVector VisibleChild1 = VisibleChild1GluonCM.Boost(XDirection, BetaX);
      FourVector InvisibleChild1 = InvisibleChild1GluonCM.Boost(XDirection, BetaX);
      FourVector VisibleChild2 = VisibleChild2GluonCM.Boost(XDirection, BetaX);
      FourVector InvisibleChild2 = InvisibleChild2GluonCM.Boost(XDirection, BetaX);

      FourVector InvisibleTotal = InvisibleChild1 + InvisibleChild2;

      double MRStar = GetMRStar(VisibleChild1, VisibleChild2);
      double MRT = GetMRT(VisibleChild1, VisibleChild2, InvisibleTotal);
      double RStar = GetRStar(VisibleChild1, VisibleChild2, InvisibleTotal);
      double GammaRStar = GetGammaRStar(VisibleChild1, VisibleChild2);
      double MR = GetMR(VisibleChild1, VisibleChild2);
      double R = GetR(VisibleChild1, VisibleChild2, InvisibleTotal);

      HMRStar.Fill(MRStar);
      HMRT.Fill(MRT);
      HRStar.Fill(RStar);
      HMRStarVsRStar.Fill(MRStar, RStar);
      HGammaRStar.Fill(GammaRStar);
      HGammaRStarMRStar.Fill(GammaRStar * MRStar);
      HGammaRStarMRStarVsRStar.Fill(GammaRStar * MRStar, RStar);
      HMRVsMRStar.Fill(MR, MRStar);
      HRVsRStar.Fill(R, RStar);
   }

   TCanvas canvas;

   canvas.Divide(3, 3);

   canvas.cd(1);
   HMRStar.Draw();
   canvas.cd(1)->SetLogy();

   canvas.cd(2);
   HMRT.Draw();
   canvas.cd(2)->SetLogy();
   
   canvas.cd(3);
   HRStar.Draw();
   canvas.cd(3)->SetLogy();
   
   canvas.cd(4);
   HMRStarVsRStar.Draw("colz");

   canvas.cd(5);
   HGammaRStar.Draw();
   canvas.cd(5)->SetLogy();
   
   canvas.cd(6);
   HGammaRStarMRStar.Draw();
   canvas.cd(6)->SetLogy();
   
   canvas.cd(7);
   HGammaRStarMRStarVsRStar.Draw("colz");

   canvas.cd(8);
   HMRVsMRStar.Draw("colz");

   canvas.cd(9);
   HRVsRStar.Draw("colz");

   PsFile.AddCanvas(canvas);

   return HMRStar.GetMean();
}





