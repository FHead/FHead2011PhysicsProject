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
void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double VisibleMass, const double InvisibleMass, const double RStart, const double REnd);

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

   PsFileHelper PsFile("MRToy12_RPhaseSpace.ps");
   PsFile.AddTextPage("Toys to understand MR/R better - part 12");

   vector<string> Explanations;
   Explanations.push_back("Setup: gluon with spatial momentum zero, decay into two heavy object");
   Explanations.push_back("of certain mass, each then further decays into two light objects");
   Explanations.push_back("one of them visible, one invisible");
   Explanations.push_back("Mass setting: 300 GeV decay into 4.2 GeV and 0 GeV, GammaCM 1.000");
   Explanations.push_back("");
   Explanations.push_back("Assume perfect reconstruction of the visible final objects");
   PsFile.AddTextPage(Explanations);

   for(double x = 0; x < 1; x = x + 0.025)
      DoToyAndAppendPlots(PsFile, 300, 600, 4.2, 0, x, x + 0.025);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void DoToyAndAppendPlots(PsFileHelper &PsFile, const double HeavyMass, const double Energy,
   const double VisibleMass, const double InvisibleMass, const double RStart, const double REnd)
{
   TH2D HTheta1VsTheta2("HTheta1VsTheta2",
      Form("Theta of the two visible particles, R = %.3f-%.3f;Theta1;Theta2", RStart, REnd),
      100, 0, 3.2, 100, 0, 3.2);
   TH2D HAngleVsDeltaTheta("HAngleVsDeltaTheta",
      Form("Angle of the two visible particles vs. delta theta, R = %.3f-%.3f;Angle;DeltaTheta", RStart, REnd),
      100, 0, 3.2, 100, 0, 3.2);

   TH2D HTheta2VsDeltaPhi_Theta1Bin1("HTheta2VsDeltaPhi_Theta1Bin1", "Theta1 = 0-pi/8;Theta2;DeltaPhi",
      100, 0, 3.2, 100, 0, 3.2);
   TH2D HTheta2VsDeltaPhi_Theta1Bin2("HTheta2VsDeltaPhi_Theta1Bin2", "Theta1 = pi/8-pi/4;Theta2;DeltaPhi",
      100, 0, 3.2, 100, 0, 3.2);
   TH2D HTheta2VsDeltaPhi_Theta1Bin3("HTheta2VsDeltaPhi_Theta1Bin3", "Theta1 = pi/4-5pi/16;Theta2;DeltaPhi",
      100, 0, 3.2, 100, 0, 3.2);
   TH2D HTheta2VsDeltaPhi_Theta1Bin4("HTheta2VsDeltaPhi_Theta1Bin4", "Theta1 = 5pi/16-3pi/8;Theta2;DeltaPhi",
      100, 0, 3.2, 100, 0, 3.2);
   TH2D HTheta2VsDeltaPhi_Theta1Bin5("HTheta2VsDeltaPhi_Theta1Bin5", "Theta1 = 3pi/8-7pi/16;Theta2;DeltaPhi",
      100, 0, 3.2, 100, 0, 3.2);
   TH2D HTheta2VsDeltaPhi_Theta1Bin6("HTheta2VsDeltaPhi_Theta1Bin6", "Theta1 = 7pi/16-pi/2;Theta2;DeltaPhi",
      100, 0, 3.2, 100, 0, 3.2);

   HTheta1VsTheta2.SetStats(0);
   HAngleVsDeltaTheta.SetStats(0);
   HTheta2VsDeltaPhi_Theta1Bin1.SetStats(0);
   HTheta2VsDeltaPhi_Theta1Bin2.SetStats(0);
   HTheta2VsDeltaPhi_Theta1Bin3.SetStats(0);
   HTheta2VsDeltaPhi_Theta1Bin4.SetStats(0);
   HTheta2VsDeltaPhi_Theta1Bin5.SetStats(0);
   HTheta2VsDeltaPhi_Theta1Bin6.SetStats(0);

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

      VisibleChild1Heavy1CM = VisibleChild1Heavy1CM * Momentum;
      InvisibleChild1Heavy1CM = InvisibleChild1Heavy1CM * Momentum;
      VisibleChild1Heavy1CM[0] = sqrt(VisibleMass * VisibleMass + Momentum * Momentum);
      InvisibleChild1Heavy1CM[0] = sqrt(InvisibleMass * InvisibleMass + Momentum * Momentum);
      
      // In CM of second heavy particle
      double Theta2 = DrawSine(0, PI);
      double Phi2 = DrawRandom(-PI, PI);
      FourVector VisibleChild2Heavy2CM(1, sin(Theta2) * cos(Phi2), sin(Theta2) * sin(Phi2), cos(Theta2));
      FourVector InvisibleChild2Heavy2CM(1, -sin(Theta2) * cos(Phi2), -sin(Theta2) * sin(Phi2), -cos(Theta2));
      
      VisibleChild2Heavy2CM = VisibleChild2Heavy2CM * Momentum;
      InvisibleChild2Heavy2CM = InvisibleChild2Heavy2CM * Momentum;
      VisibleChild2Heavy2CM[0] = sqrt(VisibleMass * VisibleMass + Momentum * Momentum);
      InvisibleChild2Heavy2CM[0] = sqrt(InvisibleMass * InvisibleMass + Momentum * Momentum);

      // boost back to lab frame
      FourVector VisibleChild1, InvisibleChild1;
      FourVector VisibleChild2, InvisibleChild2;

      VisibleChild1 = VisibleChild1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      InvisibleChild1 = InvisibleChild1Heavy1CM.Boost(HeavyParticle1Direction, Beta);
      VisibleChild2 = VisibleChild2Heavy2CM.Boost(HeavyParticle2Direction, Beta);
      InvisibleChild2 = InvisibleChild2Heavy2CM.Boost(HeavyParticle2Direction, Beta);

      FourVector InvisibleTotal = InvisibleChild1 + InvisibleChild2;

      double MR = GetMR(VisibleChild1, VisibleChild2);
      double MRT = GetMRT(VisibleChild1, VisibleChild2, InvisibleTotal);
      double R = GetR(VisibleChild1, VisibleChild2, InvisibleTotal);

      if(R >= RStart && R < REnd)
      {
         double FinalTheta1 = VisibleChild1.GetTheta();
         double FinalTheta2 = VisibleChild2.GetTheta();
         double Angle = GetAngle(VisibleChild1, VisibleChild2);
         double AbsDeltaPhi = fabs(GetDPhi(VisibleChild1, VisibleChild2));

         HTheta1VsTheta2.Fill(FinalTheta1, FinalTheta2);
         HAngleVsDeltaTheta.Fill(Angle, fabs(FinalTheta1 - FinalTheta2));

         if(FinalTheta1 >= 0 && FinalTheta1 < PI / 8)
            HTheta2VsDeltaPhi_Theta1Bin1.Fill(FinalTheta2, AbsDeltaPhi);
         if(FinalTheta1 >= PI / 8 && FinalTheta1 < PI / 4)
            HTheta2VsDeltaPhi_Theta1Bin2.Fill(FinalTheta2, AbsDeltaPhi);
         if(FinalTheta1 >= PI / 4 && FinalTheta1 < 5 * PI / 16)
            HTheta2VsDeltaPhi_Theta1Bin3.Fill(FinalTheta2, AbsDeltaPhi);
         if(FinalTheta1 >= 5 * PI / 16 && FinalTheta1 < 3 * PI / 8)
            HTheta2VsDeltaPhi_Theta1Bin4.Fill(FinalTheta2, AbsDeltaPhi);
         if(FinalTheta1 >= 3 * PI / 8 && FinalTheta1 < 7 * PI / 16)
            HTheta2VsDeltaPhi_Theta1Bin5.Fill(FinalTheta2, AbsDeltaPhi);
         if(FinalTheta1 >= 7 * PI / 16 && FinalTheta1 < PI / 2)
            HTheta2VsDeltaPhi_Theta1Bin6.Fill(FinalTheta2, AbsDeltaPhi);
         if(FinalTheta1 >= PI / 2 && FinalTheta1 < 9 * PI / 16)
            HTheta2VsDeltaPhi_Theta1Bin6.Fill(PI - FinalTheta2, AbsDeltaPhi);
         if(FinalTheta1 >= 9 * PI / 16 && FinalTheta1 < 5 * PI / 8)
            HTheta2VsDeltaPhi_Theta1Bin5.Fill(PI - FinalTheta2, AbsDeltaPhi);
         if(FinalTheta1 >= 5 * PI / 8 && FinalTheta1 < 11 * PI / 16)
            HTheta2VsDeltaPhi_Theta1Bin4.Fill(PI - FinalTheta2, AbsDeltaPhi);
         if(FinalTheta1 >= 11 * PI / 16 && FinalTheta1 < 3 * PI / 4)
            HTheta2VsDeltaPhi_Theta1Bin3.Fill(PI - FinalTheta2, AbsDeltaPhi);
         if(FinalTheta1 >= 3 * PI / 4 && FinalTheta1 < 7 * PI / 8)
            HTheta2VsDeltaPhi_Theta1Bin2.Fill(PI - FinalTheta2, AbsDeltaPhi);
         if(FinalTheta1 >= 7 * PI / 8 && FinalTheta1 < PI)
            HTheta2VsDeltaPhi_Theta1Bin1.Fill(PI - FinalTheta2, AbsDeltaPhi);
      }
   }

   TCanvas canvas;

   canvas.Divide(3, 3);

   canvas.cd(1);
   HTheta1VsTheta2.Draw("colz");

   canvas.cd(2);
   HAngleVsDeltaTheta.Draw("colz");

   canvas.cd(4);
   HTheta2VsDeltaPhi_Theta1Bin1.Draw("colz");
   canvas.cd(5);
   HTheta2VsDeltaPhi_Theta1Bin2.Draw("colz");
   canvas.cd(6);
   HTheta2VsDeltaPhi_Theta1Bin3.Draw("colz");
   canvas.cd(7);
   HTheta2VsDeltaPhi_Theta1Bin4.Draw("colz");
   canvas.cd(8);
   HTheta2VsDeltaPhi_Theta1Bin5.Draw("colz");
   canvas.cd(9);
   HTheta2VsDeltaPhi_Theta1Bin6.Draw("colz");

   PsFile.AddCanvas(canvas);
}





