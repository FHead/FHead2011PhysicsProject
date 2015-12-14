#include <string>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TGraph.h"

#include "DrawRandom.h"
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy);

int main(int argc, char *argv[])
{
   SetStyle();

   PsFileHelper PsFile("MRToy29_ProbeMinimalScale.ps");
   PsFile.AddTextPage("Probe scale with ISR");

   vector<string> Explanations;
   Explanations.push_back("");
   PsFile.AddTextPage(Explanations);

   // DoToyAndAppendPlots(PsFile, 300, 600);
   DoToyAndAppendPlots(PsFile, 300, 660);
   // DoToyAndAppendPlots(PsFile, 300, 900);
   // DoToyAndAppendPlots(PsFile, 300, 1200);
   // DoToyAndAppendPlots(PsFile, 300, 2400);
   // DoToyAndAppendPlots(PsFile, 300, 4800);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy)
{
   TH1D HEqualMassMinMass("HEqualMassMinMass", "Min. Mass under equal-mass assumption", 100, 0, HeavyMass * 2);

   for(int iEntry = 0; iEntry < 10000; iEntry++)
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

      // boost back to hard process frame
      FourVector VisibleChild1 = VisibleChild1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector InvisibleChild1 = InvisibleChild1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      FourVector VisibleChild2 = VisibleChild2Heavy2CM.Boost(HeavyParticle2Direction, Beta);
      FourVector InvisibleChild2 = InvisibleChild2Heavy2CM.Boost(HeavyParticle2Direction, Beta);

      // ISR direction and size
      double ISRTheta = DrawSine(0, PI);
      double ISRPhi = DrawRandom(-PI, PI);
      double ISRBeta = DrawRandom(0, 0.5);
      double ISRMass = DrawRandom(0, 50);

      FourVector ISRDirection;
      ISRDirection.SetSizeThetaPhi(1, ISRTheta, ISRPhi);

      FourVector FinalJ1 = VisibleChild1.Boost(ISRDirection, ISRBeta);
      FourVector FinalNu1 = InvisibleChild1.Boost(ISRDirection, ISRBeta);
      FourVector FinalJ2 = VisibleChild2.Boost(ISRDirection, ISRBeta);
      FourVector FinalNu2 = InvisibleChild2.Boost(ISRDirection, ISRBeta);

      FourVector FinalTotal = FinalJ1 + FinalNu1 + FinalJ2 + FinalNu2;
      FourVector ISRVector = -FinalTotal;
      ISRVector[0] = sqrt(ISRVector.GetP2() + ISRMass * ISRMass);

      FourVector InvisibleTotal = FinalNu1 + FinalNu2;

      TH2D HMassEstimator("HMassEstimator", "Mass estimator as a function of E^{MET} and P_{z}^{MET} percentage",
         100, 0, HeavyMass * 2, 100, -1, 1);
      TH1D HMassEstimatorEqualMass("HMassEstimatorEqualMass",
         "Estimated Mass, assumption mass(j1 j2) = mass(nu1 nu2)", 1000, -HeavyMass * 5, HeavyMass * 5);

      TGraph RealPosition;
      RealPosition.SetMarkerStyle(11);
      RealPosition.SetPoint(0, InvisibleTotal[0], InvisibleTotal[3] / sqrt(InvisibleTotal[0] * InvisibleTotal[0] - InvisibleTotal.GetPT() * InvisibleTotal.GetPT()));

      for(int i = 1; i <= 100; i++)
      {
         InvisibleTotal[0] = HMassEstimator.GetXaxis()->GetBinCenter(i);
         InvisibleTotal[3] = 0;

         if(InvisibleTotal.GetMass2() <= 0)
            continue;
         double PartialMass = InvisibleTotal.GetMass();

         for(int j = 1; j <= 100; j++)
         {
            InvisibleTotal[3] = HMassEstimator.GetYaxis()->GetBinCenter(j) * PartialMass;

            FourVector TempTotal = InvisibleTotal + FinalJ1 + FinalJ2 + ISRVector;
            double TempBetaZ = TempTotal[3] / TempTotal[0];

            FourVector TempJ1 = FinalJ1.Boost(FourVector(1, 0, 0, 1), TempBetaZ);
            FourVector TempJ2 = FinalJ2.Boost(FourVector(1, 0, 0, 1), TempBetaZ);
            FourVector TempME = InvisibleTotal.Boost(FourVector(1, 0, 0, 1), TempBetaZ);
            FourVector TempISR = ISRVector.Boost(FourVector(1, 0, 0, 1), TempBetaZ);

            TempTotal = TempJ1 + TempJ2 + TempME;
            double TempBeta = TempTotal.GetP() / TempTotal[0];

            TempJ1 = TempJ1.Boost(TempTotal, TempBeta);
            TempJ2 = TempJ2.Boost(TempTotal, TempBeta);
            TempME = TempME.Boost(TempTotal, TempBeta);

            double EMET = TempME[0];
            double SumE = TempJ1[0] + TempJ2[0];
            double DeltaE = TempJ1[0] - TempJ2[0];
            double ES = (TempJ1 + TempJ2).GetP();
            double ED = (TempJ1 - TempJ2).GetP();
            double A = SumE * DeltaE / ES;
            double B = sqrt(ED * ED - A * A);

            double m0 = (SumE - EMET) / (2 * DeltaE) - SumE * DeltaE / ES / ES;
            double m1 = DeltaE * (SumE + EMET) / 2;

            double EQA = m0 * m0 + B * B / ES / ES;
            double EQB = 2 * m0 * m1 - B * B;
            double EQC = m1 * m1;

            double X2Max = (-EQB + sqrt(EQB * EQB - 4 * EQA * EQC)) / (2 * EQA);
            double X2Min = (-EQB - sqrt(EQB * EQB - 4 * EQA * EQC)) / (2 * EQA);

            if(X2Min > ES * ES)
               continue;
            if(X2Max < 0)
               continue;

            if(X2Max > ES * ES)
               X2Max = ES * ES;

            double X = sqrt(X2Max);
            double Y = ((X * X + DeltaE * DeltaE) * SumE - (X * X - DeltaE * DeltaE) * EMET) / (2 * X * DeltaE);

            double M2 = (SumE * X - DeltaE * Y) * (SumE * X - DeltaE * Y) / (X * X - DeltaE * DeltaE) / 4;

            if(M2 > 0)
               HMassEstimator.SetBinContent(i, j, sqrt(M2) * 2);
         }
      }

      {
         double MinMass = HeavyMass * 1000;

         if(InvisibleTotal.GetMass2() <= 0)
            continue;
         double JJMass = (FinalJ1 + FinalJ2).GetMass();

         for(int j = 1; j <= 1000; j++)
         {
            InvisibleTotal[3] = HMassEstimatorEqualMass.GetXaxis()->GetBinCenter(j);
            InvisibleTotal[0] = sqrt(JJMass * JJMass + InvisibleTotal.GetP2());

            FourVector TempTotal = InvisibleTotal + FinalJ1 + FinalJ2 + ISRVector;
            double TempBetaZ = TempTotal[3] / TempTotal[0];

            FourVector TempJ1 = FinalJ1.Boost(FourVector(1, 0, 0, 1), TempBetaZ);
            FourVector TempJ2 = FinalJ2.Boost(FourVector(1, 0, 0, 1), TempBetaZ);
            FourVector TempME = InvisibleTotal.Boost(FourVector(1, 0, 0, 1), TempBetaZ);
            FourVector TempISR = ISRVector.Boost(FourVector(1, 0, 0, 1), TempBetaZ);

            TempTotal = TempJ1 + TempJ2 + TempME;
            double TempBeta = TempTotal.GetP() / TempTotal[0];

            TempJ1 = TempJ1.Boost(TempTotal, TempBeta);
            TempJ2 = TempJ2.Boost(TempTotal, TempBeta);
            TempME = TempME.Boost(TempTotal, TempBeta);

            double EMET = TempME[0];
            double SumE = TempJ1[0] + TempJ2[0];
            double DeltaE = TempJ1[0] - TempJ2[0];
            double ES = (TempJ1 + TempJ2).GetP();
            double ED = (TempJ1 - TempJ2).GetP();
            double A = SumE * DeltaE / ES;
            double B = sqrt(ED * ED - A * A);

            double m0 = (SumE - EMET) / (2 * DeltaE) - SumE * DeltaE / ES / ES;
            double m1 = DeltaE * (SumE + EMET) / 2;

            double EQA = m0 * m0 + B * B / ES / ES;
            double EQB = 2 * m0 * m1 - B * B;
            double EQC = m1 * m1;

            double X2Max = (-EQB + sqrt(EQB * EQB - 4 * EQA * EQC)) / (2 * EQA);
            double X2Min = (-EQB - sqrt(EQB * EQB - 4 * EQA * EQC)) / (2 * EQA);

            if(X2Min > ES * ES)
               continue;
            if(X2Max < 0)
               continue;

            if(X2Max > ES * ES)
               X2Max = ES * ES;

            double X = sqrt(X2Max);
            double Y = ((X * X + DeltaE * DeltaE) * SumE - (X * X - DeltaE * DeltaE) * EMET) / (2 * X * DeltaE);

            double M2 = (SumE * X - DeltaE * Y) * (SumE * X - DeltaE * Y) / (X * X - DeltaE * DeltaE) / 4;

            if(M2 > 0)
            {
               HMassEstimatorEqualMass.SetBinContent(j, sqrt(M2) * 2);

               if(M2 < MinMass * MinMass)
                  MinMass = sqrt(M2);
            }
         }

         HEqualMassMinMass.Fill(MinMass * 2);
      }

      HMassEstimator.SetStats(0);

      if(iEntry < 100)
      {
         TCanvas C("C", "C", 1024, 1024);

         HMassEstimator.GetXaxis()->SetTitle("E^{MET}");
         HMassEstimator.GetYaxis()->SetTitle("P_{z}^{MET} / sqrt(E^{2}-p_{x}^{2}-p_{y}^{2})");

         HMassEstimator.Draw("colz");
         RealPosition.Draw("p");

         C.SaveAs(Form("MassScan_%d.png", iEntry));
         C.SaveAs(Form("MassScan_%d.C", iEntry));
         C.SaveAs(Form("MassScan_%d.eps", iEntry));
         C.SaveAs(Form("MassScan_%d.pdf", iEntry));

         // PsFile.AddCanvas(C);

         HMassEstimatorEqualMass.GetYaxis()->SetTitle("Mass estimator (GeV)");
         HMassEstimatorEqualMass.GetXaxis()->SetTitle("P_{z}^{MET} (GeV)");

         HMassEstimatorEqualMass.SetStats(0);
         HMassEstimatorEqualMass.Draw();

         C.SaveAs(Form("PzScan_%d.png", iEntry));
         C.SaveAs(Form("PzScan_%d.C", iEntry));
         C.SaveAs(Form("PzScan_%d.eps", iEntry));
         C.SaveAs(Form("PzScan_%d.pdf", iEntry));

         PsFile.AddPlot(HMassEstimatorEqualMass, "");
      }
   }

   PsFile.AddPlot(HEqualMassMinMass, "", false);
   PsFile.AddPlot(HEqualMassMinMass, "", true);

   TCanvas C("C", "C", 1024, 1024);

   HEqualMassMinMass.SetStats(0);
   HEqualMassMinMass.GetXaxis()->SetTitle("Mass estimator (GeV)");
   HEqualMassMinMass.Draw();

   C.SaveAs("HEqualMassMinMass.png");
   C.SaveAs("HEqualMassMinMass.C");
   C.SaveAs("HEqualMassMinMass.eps");
   C.SaveAs("HEqualMassMinMass.pdf");
}




