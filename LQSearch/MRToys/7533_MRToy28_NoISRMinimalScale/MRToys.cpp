#include <string>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"

#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy);

int main(int argc, char *argv[])
{
   SetStyle();

   PsFileHelper PsFile("MRToy28_ProbeMinimalScale.ps");

   vector<string> Explanations;
   Explanations.push_back("");
   PsFile.AddTextPage(Explanations);

   DoToyAndAppendPlots(PsFile, 300, 700);
   // DoToyAndAppendPlots(PsFile, 300, 900);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy)
{
   TH1D HMinMass("HMinMass", "Minimum mass scanning through boost directions", 100, 0, HeavyMass * 2);
   TH1D HMaxMass("HMaxMass", "Maximum mass scanning through X", 100, 0, HeavyMass * 2);

   TH1D HX2Min("HX2Min", "X2Min/Es^2", 100, -1, 2);
   TH1D HX2Max("HX2Max", "X2Max/Es^2", 100, -1, 2);
   TH1D HMassEstimator("HMassEstimator", "Estimated Mass", 100, 0, HeavyMass * 2);

   for(int iEntry = 0; iEntry < 100000; iEntry++)
   {
      // Decay angles of the two heavy guys
      double Theta = DrawSine(0, PI);
      double Phi = DrawRandom(-PI, PI);
      double Gamma = Energy / 2 / HeavyMass;
      double Beta = GammaToBeta(Gamma);

      FourVector HeavyParticle1Direction, HeavyParticle2Direction;
      HeavyParticle1Direction.SetSizeThetaPhi(1, Theta, Phi);
      HeavyParticle2Direction.SetSizeThetaPhi(1, PI - Theta, Phi + PI);

      // Inside CM of first heavy particle
      double Theta1 = DrawSine(0, PI);
      double Phi1 = DrawRandom(-PI, PI);

      FourVector VisibleChild1Heavy1CM, InvisibleChild1Heavy1CM;
      VisibleChild1Heavy1CM.SetSizeThetaPhi(HeavyMass / 2, Theta1, Phi1);
      InvisibleChild1Heavy1CM.SetSizeThetaPhi(HeavyMass / 2, PI - Theta1, Phi1 + PI);
      
      // In CM of second heavy particle
      double Theta2 = DrawSine(0, PI);
      double Phi2 = DrawRandom(-PI, PI);

      FourVector VisibleChild2Heavy2CM, InvisibleChild2Heavy2CM;
      VisibleChild2Heavy2CM.SetSizeThetaPhi(HeavyMass / 2, Theta2, Phi2);
      InvisibleChild2Heavy2CM.SetSizeThetaPhi(HeavyMass / 2, PI - Theta2, Phi2 + PI);

      // boost back to lab frame
      FourVector VisibleChild1 = VisibleChild1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector InvisibleChild1 = InvisibleChild1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector VisibleChild2 = VisibleChild2Heavy2CM.Boost(HeavyParticle2Direction, Beta);
      FourVector InvisibleChild2 = InvisibleChild2Heavy2CM.Boost(HeavyParticle2Direction, Beta);

      FourVector InvisibleTotal = InvisibleChild1 + InvisibleChild2;

      double EMET = InvisibleTotal[0];
      double E1 = VisibleChild1[0];
      double E2 = VisibleChild2[0];
      double PSum = (VisibleChild1 + VisibleChild2).GetP();
      double PDiff = (VisibleChild1 - VisibleChild2).GetP();
      double DeltaE = E1 - E2;
      double SumE = E1 + E2;

      double A = (VisibleChild1.GetP2() - VisibleChild2.GetP2()) / PSum;
      double B = (VisibleChild1 - VisibleChild2 - (VisibleChild1 + VisibleChild2) / PSum * A).GetP();

      /*
      double X = DeltaE;
      double Y = X * SumE / DeltaE;

      double M2 = (SumE * X - DeltaE * Y) * (SumE * X - DeltaE * Y) / (X * X - DeltaE * DeltaE) / 4;

      cout << (X + Y) / E1 << " " << (X - Y) / E2 << " " << M2 << endl;
      */

      // Scan of theta and phi
      TH2D HBeta("HBeta", "Beta;Theta;Phi", 100, 0, PI, 100, -PI, PI);
      TH2D HMass2("HMass2", "Mass2;Theta;Phi", 100, 0, PI, 100, -PI, PI);
      TH2D HMass("HMass", "Mass;Theta;Phi", 100, 0, PI, 100, -PI, PI);
      TH2D HA1("HA1", "A1;Theta;Phi", 100, 0, PI, 100, -PI, PI);
      TH2D HA2("HA2", "A2;Theta;Phi", 100, 0, PI, 100, -PI, PI);
      TH2D HMETDistance("HMETDistance", "Distance to EMET;Theta;Phi", 100, 0, PI, 100, -PI, PI);
      TH2D HInvMETDistance("HInvMETDistance", "Inv. Distance to EMET;Theta;Phi", 100, 0, PI, 100, -PI, PI);

      double MinMass = 999999;

      for(int i = 1; i <= 100; i++)
      {
         for(int j = 1; j <= 100; j++)
         {
            double ProbeTheta = HBeta.GetXaxis()->GetBinCenter(i);
            double ProbePhi = HBeta.GetYaxis()->GetBinCenter(j);

            FourVector Direction;
            Direction.SetSizeThetaPhi(1, ProbeTheta, ProbePhi);

            double A1 = Direction.SpatialDot(VisibleChild1);
            double A2 = Direction.SpatialDot(VisibleChild2);

            double X = A1 + A2;
            double Y = A1 - A2;

            double Beta = DeltaE / X;

            double Mass2 = (SumE * X - DeltaE * Y) * (SumE * X - DeltaE * Y) / (X * X - DeltaE * DeltaE) / 4;

            double EMETFromXY = ((X * X + DeltaE * DeltaE) * SumE - 2 * X * Y * DeltaE) / (X * X - DeltaE * DeltaE);

            if(Beta >= 1 || Beta <= -1)
               continue;

            HBeta.SetBinContent(i, j, Beta);
            HMass2.SetBinContent(i, j, Mass2);
            HMass.SetBinContent(i, j, sqrt(Mass2));
            HA1.SetBinContent(i, j, A1);
            HA2.SetBinContent(i, j, A2);
            HMETDistance.SetBinContent(i, j, fabs(EMETFromXY - EMET));
            HInvMETDistance.SetBinContent(i, j, 1 / fabs(EMETFromXY - EMET));

            if(sqrt(Mass2) < MinMass)
               MinMass = sqrt(Mass2);
         }
      }

      if(iEntry < 10)
      {
         PsFile.AddPlot(HA1, "colz");
         PsFile.AddPlot(HA2, "colz");
         PsFile.AddPlot(HBeta, "colz");
         PsFile.AddPlot(HMass2, "colz");
         PsFile.AddPlot(HMass, "colz", false, true);
         PsFile.AddPlot(HMETDistance, "colz");

         HMETDistance.SetMaximum(5);
         PsFile.AddPlot(HMETDistance, "colz");

         PsFile.AddPlot(HInvMETDistance, "colz", false, true);
      }

      HMinMass.Fill(MinMass * 2);

      TH1D HMass2X("HMass2X", "Mass^{2} as a function of X/E", 10000, -1, 1);
      TH1D HMassX("HMassX", "Mass as a function of X/E", 10000, -1, 1);

      double MaxSeenMass = 0;

      for(int i = 1; i <= 10000; i++)
      {
         double X = PSum * HMass2X.GetXaxis()->GetBinCenter(i);
         double Y = (-EMET * (X * X - DeltaE * DeltaE) + (X * X + DeltaE * DeltaE) * SumE)
            / (2 * X * DeltaE);

         double A0 = X / PSum;

         if(fabs(Y - A0 * A) > fabs(sqrt(1 - A0 * A0) * B))
            continue;

         double Mass2 = (SumE * X - DeltaE * Y) * (SumE * X - DeltaE * Y) / (X * X - DeltaE * DeltaE) / 4; 
         if(Mass2 < 0)
            continue;

         HMass2X.SetBinContent(i, Mass2 * 4);
         HMassX.SetBinContent(i, sqrt(Mass2) * 2);

         if(sqrt(Mass2) > MaxSeenMass)
            MaxSeenMass = sqrt(Mass2);
      }

      if(iEntry < 10)
      {
         PsFile.AddPlot(HMass2X, "");
         PsFile.AddPlot(HMassX, "");

         TCanvas MassCanvas("C", "C", 1024, 1024);

         HMassX.SetStats(0);
         HMassX.GetXaxis()->SetTitle("#frac{X}{|p1+p2|}");
         HMassX.GetYaxis()->SetTitle("Mass of heavy particle which satisfies the two equations");
         HMassX.Draw();

         MassCanvas.SaveAs(Form("MassAsAFunctionOfXE_%d.png", iEntry));
         MassCanvas.SaveAs(Form("MassAsAFunctionOfXE_%d.C", iEntry));
         MassCanvas.SaveAs(Form("MassAsAFunctionOfXE_%d.eps", iEntry));
         MassCanvas.SaveAs(Form("MassAsAFunctionOfXE_%d.pdf", iEntry));
      }

      HMaxMass.Fill(MaxSeenMass * 2);

      // calculate allowed range of X!

      double m0 = (SumE - EMET) / (2 * DeltaE) - SumE * DeltaE / PSum / PSum;
      double m1 = DeltaE * (SumE + EMET) / 2;

      double EQA = m0 * m0 + B * B / PSum / PSum;
      double EQB = 2 * m0 * m1 - B * B;
      double EQC = m1 * m1;

      double X2Min = (-EQB - sqrt(EQB * EQB - 4 * EQA * EQC)) / (2 * EQA);
      double X2Max = (-EQB + sqrt(EQB * EQB - 4 * EQA * EQC)) / (2 * EQA);

      // cout << X2Min / PSum / PSum << " " << X2Max / PSum / PSum << endl;
      HX2Min.Fill(X2Min / PSum / PSum);
      HX2Max.Fill(X2Max / PSum / PSum);

      if(X2Min > PSum * PSum || X2Max < 0)
         cout << "Unphysical X2 range!!!" << endl;

      double X2Estimator = X2Max;
      if(X2Estimator > PSum * PSum)
         X2Estimator = PSum * PSum;

      double XEstimator = sqrt(X2Estimator);
      double YEstimator = (-EMET * (X2Estimator - DeltaE * DeltaE) + (X2Estimator + DeltaE * DeltaE) * SumE)
         / (2 * XEstimator * DeltaE);
      double Mass2Estimator = (SumE * XEstimator - DeltaE * YEstimator)
         * (SumE * XEstimator - DeltaE * YEstimator) / (X2Estimator - DeltaE * DeltaE) / 4;

      HMassEstimator.Fill(sqrt(Mass2Estimator) * 2);
   }

   PsFile.AddPlot(HMinMass, "", true);
   PsFile.AddPlot(HMaxMass, "", false);
   PsFile.AddPlot(HMaxMass, "", true);
   PsFile.AddPlot(HX2Min, "", true);
   PsFile.AddPlot(HX2Max, "", true);
   PsFile.AddPlot(HMassEstimator, "", true);

   TCanvas FinalCanvas("C", "C", 1024, 1024);

   HMassEstimator.SetStats(0);
   HMassEstimator.GetXaxis()->SetTitle("Mass estimator (GeV)");
   HMassEstimator.Draw();

   FinalCanvas.SaveAs("ToyMassEstimator.png");
   FinalCanvas.SaveAs("ToyMassEstimator.C");
   FinalCanvas.SaveAs("ToyMassEstimator.eps");
   FinalCanvas.SaveAs("ToyMassEstimator.pdf");
}




