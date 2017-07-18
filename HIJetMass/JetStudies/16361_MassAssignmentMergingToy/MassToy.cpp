#include <iostream>
#include <vector>
using namespace std;

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions3.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   double R[] = {0.05, 0.07, 0.10, 0.15};
   int N[] = {5, 7, 10, 14, 20, 25, 30, 50};

   double TotalPT = 100;

   PdfFileHelper PdfFile("ToyResult.pdf");
   PdfFile.AddTextPage("Toys");

   for(int iR = 0; iR < 4; iR++)
   {
      for(int iN = 0; iN < 8; iN++)
      {
         double Max = 0;
         if(iR == 0)   Max = 5;
         if(iR == 1)   Max = 7;
         if(iR == 2)   Max = 10;
         if(iR == 3)   Max = 16;

         TH1D H("H", Form("R = %.2f, N = %d;Mass;#", R[iR], N[iN]), 1000, 0, Max);
         TH1D H2("H2", Form("R = %.2f, N = %d;Mass^{2};#", R[iR], N[iN]), 1000, 0, 400);

         for(int iT = 0; iT < 100000; iT++)
         {
            vector<double> Weight(N[iN]);
            for(int i = 0; i < N[iN]; i++)
               Weight[i] = DrawRandom(0, 1);

            double TotalWeight = 0;
            for(int i = 0; i < N[iN]; i++)
               TotalWeight = TotalWeight + Weight[i];
            for(int i = 0; i < N[iN]; i++)
               Weight[i] = Weight[i] / TotalWeight;

            vector<FourVector> P(N[iN]);
            for(int i = 0; i < N[iN]; i++)
            {
               double PT = TotalPT * Weight[i];
               double Eta = 0;
               double Phi = 0;
               do
               {
                  Eta = DrawRandom(-R[iR], R[iR]);
                  Phi = DrawRandom(-R[iR], R[iR]);
               } while(Eta * Eta + Phi * Phi > R[iR] * R[iR]);

               P[i].SetPtEtaPhiMass(PT, Eta, Phi, 0);
            }

            FourVector TotalP;
            for(int i = 0; i < N[iN]; i++)
               TotalP = TotalP + P[i];

            double Mass = TotalP.GetMass();

            H.Fill(Mass);
            H2.Fill(Mass * Mass);
         }

         PdfFile.AddPlot(H);
         PdfFile.AddPlot(H2);
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}






