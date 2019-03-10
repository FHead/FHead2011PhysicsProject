#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"

#include "Code/DrawRandom.h"

int main()
{
   double PT[] = {50, 75, 100, 120, 140, 160, 180, 200};
   double Mean1[] = {1.1, 1.05, 1.00, 0.95, 0.90, 0.85, 0.80, 0.80};
   double Mean2[] = {1.05, 1.02, 1.00, 1.00, 0.95, 0.90, 0.85, 0.90};
   double Sigma1[] = {0.27, 0.26, 0.25, 0.24, 0.23, 0.22, 0.21, 0.20};
   double Sigma2[] = {0.25, 0.25, 0.23, 0.23, 0.20, 0.23, 0.19, 0.17};
   int N1[] = {1000, 700, 500, 400, 300, 200, 200, 200, 200, 200};
   int N2[] = {1000, 700, 500, 400, 300, 200, 200, 200, 200, 200};

   TFile File("ToyInput.root", "RECREATE");

   for(int i = 0; i < 8; i++)
   {
      TH1D H(Form("MethodT_%.0f_0_Data", PT[i]), "Method T", 100, 0, 2);
      for(int j = 0; j < N1[i]; j++)
         H.Fill(DrawGaussian(Mean1[i], Sigma1[i]));
      H.Write();
   }
   
   for(int i = 0; i < 8; i++)
   {
      TH1D H(Form("MethodT_%.0f_0_MC", PT[i]), "Method T", 100, 0, 2);
      for(int j = 0; j < N2[i]; j++)
         H.Fill(DrawGaussian(Mean2[i], Sigma2[i]));
      H.Write();
   }

   File.Close();

   return 0;
}





