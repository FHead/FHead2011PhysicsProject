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
   double Sigma = 0.2;
   int N = 1000;

   TFile File("ToyInput.root", "RECREATE");

   for(int i = 0; i < 8; i++)
   {
      TH1D H(Form("MethodT_%.0f_0_Data", PT[i]), "Method T", 100, 0, 2);
      for(int j = 0; j < N; j++)
         H.Fill(DrawGaussian(Mean1[i], Sigma));
      H.Write();
   }
   
   for(int i = 0; i < 8; i++)
   {
      TH1D H(Form("MethodT_%.0f_0_MC", PT[i]), "Method T", 100, 0, 2);
      for(int j = 0; j < N; j++)
         H.Fill(DrawGaussian(Mean2[i], Sigma));
      H.Write();
   }

   File.Close();

   return 0;
}





