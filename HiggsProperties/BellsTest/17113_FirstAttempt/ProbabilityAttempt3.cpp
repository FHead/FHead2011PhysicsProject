#include <iostream>
#include <cmath>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "Code/DrawRandom.h"

int main(int argc, char *argv[]);
double GetRandomPhi();
double GetDPhi(double phi1, double phi2);
bool Decision(double Phi, double PhiReference);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   TH2D HAB("HAB", ";#phi_{A};#phi_{B}", 100, 0, 2 * M_PI, 100, 0, 2 * M_PI);

   for(int iA = 1; iA <= HAB.GetNbinsX(); iA++)
   {
      for(int iB = 1; iB <= HAB.GetNbinsY(); iB++)
      {
         double PhiA = HAB.GetXaxis()->GetBinCenter(iA);
         double PhiB = HAB.GetYaxis()->GetBinCenter(iB);

         double N = 10000;
         int Count = 0;

         for(int iT = 0; iT < N; iT++)
         {
            double Phi0 = DrawRandom(0, 2 * M_PI);
            double Phi = GetRandomPhi();

            double Phi1 = Phi0;
            double Phi2 = Phi0 + Phi;

            if(Decision(Phi1, PhiA) == Decision(Phi2, PhiB))
               Count = Count + 1;
         }

         HAB.SetBinContent(iA, iB, Count / N);
      }
   }

   HAB.SetStats(0);
   HAB.SetMinimum(0);
   HAB.SetMaximum(1);

   TCanvas C;
   HAB.Draw("colz");
   C.SaveAs("Probability.pdf");

   return 0;
}

double GetRandomPhi()
{
   bool Done = false;
   double Phi = DrawRandom(0, 2 * M_PI);

   while(Done == false)
   {
      if(DrawRandom(0, 2) < 1 + cos(Phi) * cos(Phi))
         Done = true;
      else
         Phi = DrawRandom(0, 2 * M_PI);
   }

   return Phi;
}

double GetDPhi(double phi1, double phi2)
{
   double dphi = phi1 - phi2;
   while(dphi > +M_PI)   dphi = dphi - 2 * M_PI;
   while(dphi < -M_PI)   dphi = dphi + 2 * M_PI;
   return dphi;
}

bool Decision(double Phi, double PhiReference)
{
   double DPhi = GetDPhi(Phi, PhiReference);
   if(DPhi > -M_PI / 2 && DPhi < M_PI / 2)
      return true;
   return false;
}




