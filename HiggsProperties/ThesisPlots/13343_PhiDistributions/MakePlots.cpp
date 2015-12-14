#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "Code/TauHelperFunctions2.h"
#include "ProgressBar.h"
#include "SetStyle.h"

#include "AngleConversion.h"
#include "CalculateME.h"

int main()
{
   SetThesisRegularStyle();

   int Bin = 1000;

   TH1D HPhiA1ZZ_200("HPhiA1ZZ_200", "", Bin, 0, 2 * PI);
   TH1D HPhiA3ZZ_200("HPhiA3ZZ_200", "", Bin, 0, 2 * PI);
   TH1D HPhiA1ZZA3ZZ_200("HPhiA1ZZA3ZZ_200", "", Bin, 0, 2 * PI);
   TH1D HPhiA1ZZ_125("HPhiA1ZZ_125", "", Bin, 0, 2 * PI);
   TH1D HPhiA3ZZ_125("HPhiA3ZZ_125", "", Bin, 0, 2 * PI);
   TH1D HPhiA1ZZA3ZZ_125("HPhiA1ZZA3ZZ_125", "", Bin, 0, 2 * PI);

   GeneralScalarParameters PA1ZZ, PA3ZZ, PA1ZZA3ZZ;
   PA1ZZ.ahR = 1;
   PA3ZZ.aZdR = 1;
   PA1ZZA3ZZ.aZdR = 1;
   PA1ZZA3ZZ.ahR = 1;

   ProgressBar Bar(cout, Bin);
   Bar.SetStyle(5);
   
   for(int i = 1; i <= Bin; i++)
   {
      Bar.Update(i);
      Bar.Print();

      double phi = HPhiA1ZZ_200.GetBinCenter(i);

      double MMin = 4;
      double MMax = 120;
      int Grid = 100;

      EventParameters Event;
      
      for(int m1 = 0; m1 < Grid; m1++)
      {
         for(int m2 = 0; m2 < Grid; m2++)
         {
            double M1 = MMin + (MMax - MMin) / Grid * (m1 + 0.5);
            double M2 = MMin + (MMax - MMin) / Grid * (m2 + 0.5);
      
            Event.HMass = 200;
            Event.ZMass = M1;
            Event.Z2Mass = M2;
            Event.Phi0 = 1;
            Event.Theta0 = 1;
            Event.Phi = phi;
            Event.Theta1 = 1;
            Event.Theta2 = 1;
            Event.PhiH = 1;
            Event.PTH = 1;
            Event.YH = 1;
            Event.PhiOffset = 1;

            if(Event.ZMass + Event.Z2Mass < Event.HMass)
            {
               HPhiA1ZZ_200.Fill(phi, GetScalar2e2mu_CM_PhiM1M2_Projections(Event, PA1ZZ));
               HPhiA3ZZ_200.Fill(phi, GetScalar2e2mu_CM_PhiM1M2_Projections(Event, PA3ZZ));
               HPhiA1ZZA3ZZ_200.Fill(phi, GetScalar2e2mu_CM_PhiM1M2_Projections(Event, PA1ZZA3ZZ));
            }
            
            Event.HMass = 125;

            if(Event.ZMass + Event.Z2Mass < Event.HMass)
            {
               HPhiA1ZZ_125.Fill(phi, GetScalar2e2mu_CM_PhiM1M2_Projections(Event, PA1ZZ));
               HPhiA3ZZ_125.Fill(phi, GetScalar2e2mu_CM_PhiM1M2_Projections(Event, PA3ZZ));
               HPhiA1ZZA3ZZ_125.Fill(phi, GetScalar2e2mu_CM_PhiM1M2_Projections(Event, PA1ZZA3ZZ));
            }
         }
      }
   }

   Bar.Update(Bin);
   Bar.Print();
   Bar.PrintLine();

   double NA1ZZ_200 = HPhiA1ZZ_200.Integral();
   double NA3ZZ_200 = HPhiA3ZZ_200.Integral();
   double NA1ZZ_125 = HPhiA1ZZ_125.Integral();
   double NA3ZZ_125 = HPhiA3ZZ_125.Integral();

   HPhiA1ZZA3ZZ_200.Add(&HPhiA1ZZ_200, -1);
   HPhiA1ZZA3ZZ_200.Add(&HPhiA3ZZ_200, -1);
   HPhiA1ZZA3ZZ_125.Add(&HPhiA1ZZ_125, -1);
   HPhiA1ZZA3ZZ_125.Add(&HPhiA3ZZ_125, -1);

   HPhiA1ZZ_200.Scale(1 / NA1ZZ_200 * Bin / (2 * PI));
   HPhiA3ZZ_200.Scale(1 / NA3ZZ_200 * Bin / (2 * PI));
   HPhiA1ZZA3ZZ_200.Scale(1 / sqrt(NA1ZZ_200 * NA3ZZ_200) * Bin / (2 * PI));
   HPhiA1ZZ_125.Scale(1 / NA1ZZ_125 * Bin / (2 * PI));
   HPhiA3ZZ_125.Scale(1 / NA3ZZ_125 * Bin / (2 * PI));
   HPhiA1ZZA3ZZ_125.Scale(1 / sqrt(NA1ZZ_125 * NA3ZZ_125) * Bin / (2 * PI));

   HPhiA1ZZ_200.SetLineWidth(2);
   HPhiA3ZZ_200.SetLineWidth(2);
   HPhiA1ZZA3ZZ_200.SetLineWidth(2);
   HPhiA1ZZ_125.SetLineWidth(2);
   HPhiA3ZZ_125.SetLineWidth(2);
   HPhiA1ZZA3ZZ_125.SetLineWidth(2);

   HPhiA1ZZ_200.SetLineColor(kBlack);
   HPhiA3ZZ_200.SetLineColor(kBlue);
   HPhiA1ZZA3ZZ_200.SetLineColor(kRed);
   HPhiA1ZZ_125.SetLineColor(kBlack);
   HPhiA3ZZ_125.SetLineColor(kBlue);
   HPhiA1ZZA3ZZ_125.SetLineColor(kRed);

   TCanvas C;

   TH1D HWorld("HWorld", ";#phi;a.u.", Bin, 0, 2 * PI);
   HWorld.SetStats(0);
   HWorld.SetMaximum(0.4);
   HWorld.SetMinimum(-0.1);
   // HWorld.GetXaxis()->SetTitleOffset(1.1);
   // HWorld.GetYaxis()->SetTitleOffset(1.2);

   HWorld.Draw();
   HPhiA1ZZ_200.Draw("same");
   HPhiA3ZZ_200.Draw("same");
   HPhiA1ZZA3ZZ_200.Draw("same");

   double LegendX1 = ThesisNDCMappingRegularX(0.35);
   double LegendX2 = ThesisNDCMappingRegularX(0.83);
   double LegendY1 = ThesisNDCMappingRegularX(0.85);
   double LegendY2 = ThesisNDCMappingRegularX(0.58);

   TLegend Legend(LegendX1, LegendY1, LegendX2, LegendY2);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextSize(0.035 * 2 / 1.30);
   Legend.AddEntry(&HPhiA1ZZ_200, "A_{1}^{ZZ}", "l");
   Legend.AddEntry(&HPhiA3ZZ_200, "A_{3}^{ZZ}", "l");
   Legend.AddEntry(&HPhiA1ZZA3ZZ_200, "Interference", "l");
   Legend.Draw();

   C.SaveAs("HelicityAmplitudes-Amplitudes-PhiComparison.png");
   C.SaveAs("HelicityAmplitudes-Amplitudes-PhiComparison.C");
   C.SaveAs("HelicityAmplitudes-Amplitudes-PhiComparison.eps");
   C.SaveAs("HelicityAmplitudes-Amplitudes-PhiComparison.pdf");
   
   HWorld.Draw();
   HPhiA1ZZ_125.Draw("same");
   HPhiA3ZZ_125.Draw("same");
   HPhiA1ZZA3ZZ_125.Draw("same");
   Legend.Draw();

   C.SaveAs("CPViolation-SameVV-PhiDistribution.png");
   C.SaveAs("CPViolation-SameVV-PhiDistribution.C");
   C.SaveAs("CPViolation-SameVV-PhiDistribution.eps");
   C.SaveAs("CPViolation-SameVV-PhiDistribution.pdf");

   return 0;
}




