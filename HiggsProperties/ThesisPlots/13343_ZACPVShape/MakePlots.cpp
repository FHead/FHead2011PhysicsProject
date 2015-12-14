#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main();
double CPVDensity(double CosThetaLL, double MH, double MLL);

int main()
{
   SetThesisRegularStyle();

   int Bin = 500;

   TH1D HCosTheta("HCosTheta", ";cos#theta_{l#bar{l}};a.u.", Bin, -1, 1);
   TH2D HCosThetaMLL("HCosThetaMLL", ";cos#theta_{l#bar{l}};m_{l#bar{l}}", Bin, -1, 1, Bin, 4, 120);
   TH1D HMLL("HMLL", ";m_{l#bar{l}};a.u.", Bin, 4, 120);

   for(int x = 1; x <= Bin; x++)
   {
      for(int y = 1; y <= Bin; y++)
      {
         double CosTheta = HCosThetaMLL.GetXaxis()->GetBinCenter(x);
         double MLL = HCosThetaMLL.GetYaxis()->GetBinCenter(y);

         double Density = CPVDensity(CosTheta, 125, MLL) * MLL;
         if(Density != Density)
            continue;

         HCosTheta.Fill(CosTheta, Density);
         HCosThetaMLL.Fill(CosTheta, MLL, Density);
         if(CosTheta > 0)
            HMLL.Fill(MLL, Density);
      }
   }

   HCosTheta.SetStats(0);
   HCosThetaMLL.SetStats(0);
   HMLL.SetStats(0);

   HCosTheta.Scale(double(Bin) / 2 / HCosTheta.Integral(Bin / 2 + 1, Bin));
   HCosThetaMLL.Scale(double(Bin * Bin) / 2 / (120 - 4) / HCosThetaMLL.Integral(Bin / 2 + 1, Bin, 1, Bin));
   HMLL.Scale(double(Bin) / (120 - 4) / HMLL.Integral());
   
   HCosThetaMLL.Rebin2D(5, 5);

   HCosThetaMLL.GetXaxis()->SetNdivisions(508);

   TCanvas C;

   HCosTheta.Draw();

   C.SaveAs("CPViolation-DifferentVV-InterferenceShape1D.png");
   C.SaveAs("CPViolation-DifferentVV-InterferenceShape1D.C");
   C.SaveAs("CPViolation-DifferentVV-InterferenceShape1D.eps");
   C.SaveAs("CPViolation-DifferentVV-InterferenceShape1D.pdf");

   HCosThetaMLL.Draw("col");

   C.SaveAs("CPViolation-DifferentVV-InterferenceShape2D.png");
   C.SaveAs("CPViolation-DifferentVV-InterferenceShape2D.C");
   C.SaveAs("CPViolation-DifferentVV-InterferenceShape2D.eps");
   C.SaveAs("CPViolation-DifferentVV-InterferenceShape2D.pdf");

   HMLL.Draw("");
   HMLL.SetMinimum(5e-4);
   C.SetLogy();

   C.SaveAs("CPViolation-DifferentVV-InterferenceShape1D2.png");
   C.SaveAs("CPViolation-DifferentVV-InterferenceShape1D2.C");
   C.SaveAs("CPViolation-DifferentVV-InterferenceShape1D2.eps");
   C.SaveAs("CPViolation-DifferentVV-InterferenceShape1D2.pdf");

   return 0;
}

double CPVDensity(double CosThetaLL, double MH, double MLL)
{
   double MZ = 91.1876;
   double GZ = 2.4;

   return CosThetaLL * (MH * MH - MLL * MLL) * (MH * MH - MLL * MLL) * (MH * MH - MLL * MLL)
      / (MZ * MZ * GZ * GZ + (MLL * MLL - MZ * MZ) * (MLL * MLL - MZ * MZ));
}








