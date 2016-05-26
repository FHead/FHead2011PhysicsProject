#include <iostream>
using namespace std;

#include "DataHelper.h"

int main()
{
   double L = 2.8;

   DataHelper DHFile("Efficiencies.dh");

   // First Let's deal with SMVV: inputs
   double N_SMVV_2e2mu = 2.21;
   double N_SMVV_4e = 2.61;

   // These are assumptions!
   double K_SMVV_2e2mu = 1;
   double K_SMVV_4e = 1;

   // SMVV is simple enough
   // GenYield = sigma * epsilon_0
   double GenYield_SMVV_2e2mu = N_SMVV_2e2mu / L * K_SMVV_2e2mu
      / DHFile["SMVV_2e2mu"]["CutA"].GetDouble();
   double GenYield_SMVV_4e = N_SMVV_4e / L * K_SMVV_4e
      / DHFile["SMVV_4e"]["CutA"].GetDouble();

   // Now the H5 model
   // Ratio of cross section
   double R_H5 = 4.0 / 3.0;

   // This will come from MG once we have all samples
   double r0_H5_2e2mu = 0.6078867306 / 0.6022805781;
   double r0_H5_4e = 0.6050846042 / 0.6026416584;

   // All ingredients are there
   double GenYield_H5_2e2mu = GenYield_SMVV_2e2mu * R_H5 * r0_H5_2e2mu;
   double GenYield_H5_4e = GenYield_SMVV_4e * R_H5 * r0_H5_4e;

   // Moving on to backgrounds
   double N_uubar_2e2mu_plus_N_ddbar_2e2mu = 0.92;
   double N_uubar_4e_plus_N_ddbar_4e = 1.08;

   // These are assumptions again
   double K_uubar_2e2mu = 1;
   double K_uubar_4e = 1;
   double K_ddbar_2e2mu = 1;
   double K_ddbar_4e = 1;

   // Some ratios as input to the calculation - will come from MG
   double Epsilon0_uubar_2e2mu_over_Epsilon0_ddbar_2e2mu = 1;
   double Epsilon0_uubar_4e_over_Epsilon0_ddbar_4e = 1;

   // Cross section ratios
   double Sigma_uubar_over_Sigma_ddbar = 2;

   // Calculate the ratio of yields
   double N_uubar_2e2mu_over_N_ddbar_2e2mu
      = Sigma_uubar_over_Sigma_ddbar
         * Epsilon0_uubar_2e2mu_over_Epsilon0_ddbar_2e2mu
         * DHFile["uubar_2e2mu"]["CutA"].GetDouble()
         / DHFile["ddbar_2e2mu"]["CutA"].GetDouble()
         * K_ddbar_2e2mu / K_uubar_2e2mu;
   double N_uubar_4e_over_N_ddbar_4e
      = Sigma_uubar_over_Sigma_ddbar
         * Epsilon0_uubar_4e_over_Epsilon0_ddbar_4e
         * DHFile["uubar_4e"]["CutA"].GetDouble()
         / DHFile["ddbar_4e"]["CutA"].GetDouble()
         * K_ddbar_4e / K_uubar_4e;
   
   // Now get the individual N's
   double N_uubar_2e2mu = N_uubar_2e2mu_plus_N_ddbar_2e2mu
      * N_uubar_2e2mu_over_N_ddbar_2e2mu
      / (N_uubar_2e2mu_over_N_ddbar_2e2mu + 1);
   double N_ddbar_2e2mu = N_uubar_2e2mu_plus_N_ddbar_2e2mu
      / (N_uubar_2e2mu_over_N_ddbar_2e2mu + 1);
   double N_uubar_4e = N_uubar_4e_plus_N_ddbar_4e
      * N_uubar_4e_over_N_ddbar_4e
      / (N_uubar_4e_over_N_ddbar_4e + 1);
   double N_ddbar_4e = N_uubar_4e_plus_N_ddbar_4e
      / (N_uubar_4e_over_N_ddbar_4e + 1);

   // Finally the gen yields
   double GenYield_uubar_2e2mu = N_uubar_2e2mu / L * K_uubar_2e2mu
      / DHFile["uubar_2e2mu"]["CutA"].GetDouble();
   double GenYield_ddbar_2e2mu = N_ddbar_2e2mu / L * K_ddbar_2e2mu
      / DHFile["ddbar_2e2mu"]["CutA"].GetDouble();
   double GenYield_uubar_4e = N_uubar_4e / L * K_uubar_4e
      / DHFile["uubar_4e"]["CutA"].GetDouble();
   double GenYield_ddbar_4e = N_ddbar_4e / L * K_ddbar_4e
      / DHFile["ddbar_4e"]["CutA"].GetDouble();

   // Now that we're done, let's print the result to the screen
   // and maybe write them into a new DHFile
   cout << "SMVV: " << GenYield_SMVV_2e2mu << ", " << GenYield_SMVV_4e << endl;
   cout << "H5: " << GenYield_H5_2e2mu << ", " << GenYield_H5_4e << endl;
   cout << "uubar: " << GenYield_uubar_2e2mu << ", " << GenYield_uubar_4e << endl;
   cout << "ddbar: " << GenYield_ddbar_2e2mu << ", " << GenYield_ddbar_4e << endl;

   // Export to a DHFile for easy future exploitation!
   DataHelper DHFile2("Yields.dh");

   for(int i = 0; i < 13; i++)
   {
      string CutString = "CutA";
      CutString[3] = char('A' + i);

      DHFile2["uubar_2e2mu"][CutString] = GenYield_uubar_2e2mu
         * DHFile["uubar_2e2mu"][CutString].GetDouble();
      DHFile2["uubar_4e"][CutString] = GenYield_uubar_4e
         * DHFile["uubar_4e"][CutString].GetDouble();
      DHFile2["ddbar_2e2mu"][CutString] = GenYield_ddbar_2e2mu
         * DHFile["ddbar_2e2mu"][CutString].GetDouble();
      DHFile2["ddbar_4e"][CutString] = GenYield_ddbar_4e
         * DHFile["ddbar_4e"][CutString].GetDouble();
      DHFile2["SMVV_2e2mu"][CutString] = GenYield_SMVV_2e2mu
         * DHFile["SMVV_2e2mu"][CutString].GetDouble();
      DHFile2["SMVV_4e"][CutString] = GenYield_SMVV_4e
         * DHFile["SMVV_4e"][CutString].GetDouble();
      DHFile2["5plet_2e2mu"][CutString] = GenYield_H5_2e2mu
         * DHFile["5plet_2e2mu"][CutString].GetDouble();
      DHFile2["5plet_4e"][CutString] = GenYield_H5_4e
         * DHFile["5plet_4e"][CutString].GetDouble();
   }

   DHFile2.SaveToFile("Yields.dh");

   return 0;
}





