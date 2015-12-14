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
   const double VisibleMass, const double InvisibleMass);

int main(int argc, char *argv[])
{
   // gROOT->SetStyle("Plain");

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   PsFileHelper PsFile("MRToy2_StaticGluon_ChangeFinalObjectMass.ps");
   PsFile.AddTextPage("Toys to understand MR better - part 2");

   vector<string> Explanations;
   Explanations.push_back("Setup: gluon with spatial momentum zero, decay into two heavy object");
   Explanations.push_back("of certain mass, each then further decays into two light objects");
   Explanations.push_back("one of them visible, one invisible");
   Explanations.push_back("");
   Explanations.push_back("Assume perfect reconstruction of the visible final objects");
   Explanations.push_back("Check MR distribution changing the mass of two light objects");
   PsFile.AddTextPage(Explanations);

   TH1D HMasslessInvisibleMRMean("HMasslessInvisibleMRMean", "MR mean varying visible mass (invisible = 0);Mass",
      150, 0, 150);
   TH1D HInvisible25MRMean("HInvisible25MRMean", "MR mean varying visible mass (invisible = 25);Mass",
      150, 0, 150);
   TH1D HInvisible50MRMean("HInvisible50MRMean", "MR mean varying visible mass (invisible = 50);Mass",
      150, 0, 150);
   TH1D HInvisible75MRMean("HInvisible75MRMean", "MR mean varying visible mass (invisible = 75);Mass",
      150, 0, 150);
   TH1D HInvisible100MRMean("HInvisible100MRMean", "MR mean varying visible mass (invisible = 100);Mass",
      150, 0, 150);

   for(int i = 0; i < 150; i++)
   {
      double MRMean = DoToyAndAppendPlots(PsFile, 300, 600, i, 0);
      HMasslessInvisibleMRMean.Fill(i, MRMean);
      MRMean = DoToyAndAppendPlots(PsFile, 300, 600, i, 25);
      HInvisible25MRMean.Fill(i, MRMean);
      MRMean = DoToyAndAppendPlots(PsFile, 300, 600, i, 50);
      HInvisible50MRMean.Fill(i, MRMean);
      MRMean = DoToyAndAppendPlots(PsFile, 300, 600, i, 75);
      HInvisible75MRMean.Fill(i, MRMean);
      MRMean = DoToyAndAppendPlots(PsFile, 300, 600, i, 100);
      HInvisible100MRMean.Fill(i, MRMean);
   }

   TF1 TheoryLine("TheoryLine", "2 * sqrt(x*x + (([0]-x*x-[1])*([0]-x*x-[1]) - 4*x*x*[1]) / (4*[0]))", 0, 150);
   TheoryLine.SetParameter(0, 300 * 300);
   TheoryLine.SetLineWidth(1);

   HMasslessInvisibleMRMean.SetStats(0);
   HInvisible25MRMean.SetStats(0);
   HInvisible50MRMean.SetStats(0);
   HInvisible75MRMean.SetStats(0);
   HInvisible100MRMean.SetStats(0);

   TCanvas Invisible0MRMeanCanvas;
   HMasslessInvisibleMRMean.Draw();
   TheoryLine.SetParameter(1, 0 * 0);
   TheoryLine.Draw("same");
   PsFile.AddCanvas(Invisible0MRMeanCanvas);

   TCanvas Invisible25MRMeanCanvas;
   HInvisible25MRMean.Draw();
   TheoryLine.SetParameter(1, 25 * 25);
   TheoryLine.Draw("same");
   PsFile.AddCanvas(Invisible25MRMeanCanvas);
   
   TCanvas Invisible50MRMeanCanvas;
   HInvisible50MRMean.Draw();
   TheoryLine.SetParameter(1, 50 * 50);
   TheoryLine.Draw("same");
   PsFile.AddCanvas(Invisible50MRMeanCanvas);
   
   TCanvas Invisible75MRMeanCanvas;
   HInvisible75MRMean.Draw();
   TheoryLine.SetParameter(1, 75 * 75);
   TheoryLine.Draw("same");
   PsFile.AddCanvas(Invisible75MRMeanCanvas);
   
   TCanvas Invisible100MRMeanCanvas;
   HInvisible100MRMean.Draw();
   TheoryLine.SetParameter(1, 100 * 100);
   TheoryLine.Draw("same");
   PsFile.AddCanvas(Invisible100MRMeanCanvas);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

double DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double VisibleMass, const double InvisibleMass)
{
   TH1D HMR("HMR", Form("MR distribution, Mass %.2f, Energy %.2f, Visible %.2f, Invisible %.2f",
      HeavyMass, Energy, VisibleMass, InvisibleMass), 100, 0, HeavyMass * 2);
   TH1D HMRT("HMRT", Form("MRT distribution, Mass %.2f, Energy %.2f, Visible %.2f, Invisible %.2f",
      HeavyMass, Energy, VisibleMass, InvisibleMass), 100, 0, HeavyMass * 2);
   TH1D HR("HR", Form("R distribution, Mass %.2f, Energy %.2f, Visible %.2f, Invisible %.2f",
      HeavyMass, Energy, VisibleMass, InvisibleMass), 100, 0, 1.5);
   TH2D HMRVsR("HMRVsR", "MR vs R;MR;R", 100, 0, HeavyMass * 2, 100, 0, 1.5);

   for(int iEntry = 0; iEntry < 100000; iEntry++)
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

      // boost back to lab frame
      double VisibleChild1[4], InvisibleChild1[4];
      double VisibleChild2[4], InvisibleChild2[4];

      Boost(VisibleChild1Heavy1CM, VisibleChild1, HeavyParticle1Direction, Beta);
      Boost(InvisibleChild1Heavy1CM, InvisibleChild1, HeavyParticle1Direction, Beta);
      Boost(VisibleChild2Heavy2CM, VisibleChild2, HeavyParticle2Direction, Beta);
      Boost(InvisibleChild2Heavy2CM, InvisibleChild2, HeavyParticle2Direction, Beta);

      double InvisibleTotal[4];
      InvisibleTotal[0] = InvisibleChild1[0] + InvisibleChild2[0];
      InvisibleTotal[1] = InvisibleChild1[1] + InvisibleChild2[1];
      InvisibleTotal[2] = InvisibleChild1[2] + InvisibleChild2[2];
      InvisibleTotal[3] = InvisibleChild1[3] + InvisibleChild2[3];

      double MR = GetMR(VisibleChild1, VisibleChild2);
      double MRT = GetMRT(VisibleChild1, VisibleChild2, InvisibleTotal);
      double R = GetR(VisibleChild1, VisibleChild2, InvisibleTotal);

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





