#include <iostream>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"

#include "AngleConversion.h"

int main()
{
   SetThesisRegularStyle();

   EventParameters Event;
   Event.HMass = 125;
   Event.ZMass = 90;
   Event.Z2Mass = 23;
   Event.Phi0 = 0.1;
   Event.Theta0 = 0.2;
   Event.Phi = 0.3;
   Event.Theta1 = 0.4;
   Event.Theta2 = 0.5;
   Event.PhiOffset = 0.6;
   Event.PhiH = 0.7;
   Event.PTH = 0.8;
   Event.YH = 0.9;

   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   double M12_2 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass2();
   double M13_2 = (Leptons.Lepton11 + Leptons.Lepton21).GetMass2();
   double M14_2 = (Leptons.Lepton11 + Leptons.Lepton22).GetMass2();
   double M23_2 = (Leptons.Lepton12 + Leptons.Lepton21).GetMass2();
   double M24_2 = (Leptons.Lepton12 + Leptons.Lepton22).GetMass2();
   double M34_2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass2();

   TH2D HMPlus("HMPlus", ";m_{1} (GeV);m_{2} (GeV)", 100, 4, 100, 100, 4, 100);
   TH2D HMMinus("HMMinus", ";m_{1} (GeV);m_{2} (GeV)", 100, 4, 100, 100, 4, 100);

   HMPlus.SetStats(0);
   HMMinus.SetStats(0);

   HMPlus.GetXaxis()->SetNdivisions(505);
   HMPlus.GetYaxis()->SetNdivisions(505);
   HMPlus.GetZaxis()->SetNdivisions(505);
   HMMinus.GetXaxis()->SetNdivisions(505);
   HMMinus.GetYaxis()->SetNdivisions(505);
   HMMinus.GetZaxis()->SetNdivisions(505);

   cout << "Rm = " << (M13_2 + M14_2 + M23_2 + M24_2) / sqrt(M12_2 * M34_2) << endl;

   for(int i = 1; i <= 100; i++)
   {
      for(int j = 1; j <= 100; j++)
      {
         double m12 = HMPlus.GetXaxis()->GetBinCenter(i);
         double m34 = HMPlus.GetYaxis()->GetBinCenter(j);

         double MPlus = sqrt(m12 * m12 + m34 * m34 + m12 * m34 * (M13_2 + M14_2 + M23_2 + M24_2) / sqrt(M12_2 * M34_2));
         double MMinus = m12 - m34;

         HMPlus.SetBinContent(i, j, MPlus);
         HMMinus.SetBinContent(i, j, MMinus);
      }
   }

   TCanvas Canvas;

   HMPlus.Draw("colz");
   
   Canvas.SaveAs("MultiDimensionalDetails-Integration-MassScanDirectionPlus.png");
   Canvas.SaveAs("MultiDimensionalDetails-Integration-MassScanDirectionPlus.C");
   Canvas.SaveAs("MultiDimensionalDetails-Integration-MassScanDirectionPlus.eps");
   Canvas.SaveAs("MultiDimensionalDetails-Integration-MassScanDirectionPlus.pdf");

   HMMinus.Draw("colz");
   
   Canvas.SaveAs("MultiDimensionalDetails-Integration-MassScanDirectionMinus.png");
   Canvas.SaveAs("MultiDimensionalDetails-Integration-MassScanDirectionMinus.C");
   Canvas.SaveAs("MultiDimensionalDetails-Integration-MassScanDirectionMinus.eps");
   Canvas.SaveAs("MultiDimensionalDetails-Integration-MassScanDirectionMinus.pdf");

   return 0;
}





