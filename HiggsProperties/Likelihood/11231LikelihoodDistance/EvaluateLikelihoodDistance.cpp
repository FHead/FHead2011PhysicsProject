//----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//----------------------------------------------------------------------------
#include "DrawRandom2.h"
#include "ProgressBar.h"
//----------------------------------------------------------------------------
int main();
bool MapCompatibilityCheck(string Map1Location, string Map2Location);
double CalculateIntegral(string MapLocation);
void DoToysAndEvaluateLikelihood(string Map1Location, string Map2Location, string OutputFileName,
   double Map1Integral, double Map2Integral, int TotalCount);
//----------------------------------------------------------------------------
int main()
{
   // Map locations
   string Map1Location = "All_Scalar.map";
   string Map2Location = "All_PseudoScalar.map";
   
   // Sanity check from the file header
   if(MapCompatibilityCheck(Map1Location, Map2Location) == false)
   {
      cerr << "Maps not compatible with each other.  Exiting..." << endl;
      return -1;
   }

   // First calculate the integral of the maps for normalization purposes
   // In principle this can be done along the way, but let's keep it simple
   // Timewise speaking this adds about 2 minutes to the total run time, which is fine (for now)
   double Integral1 = CalculateIntegral(Map1Location);
   double Integral2 = CalculateIntegral(Map2Location);

   // LL locations (output)
   string Result1Location = "SortedLL_Scalar.toyll";
   string Result2Location = "SortedLL_PseudoScalar.toyll";

   // Now evaluate the toys and write out result
   DoToysAndEvaluateLikelihood(Map1Location, Map2Location, Result1Location, Integral1, Integral2, 10000000);
   DoToysAndEvaluateLikelihood(Map2Location, Map1Location, Result2Location, Integral2, Integral1, 10000000);

   return 0;
}
//----------------------------------------------------------------------------
bool MapCompatibilityCheck(string Map1Location, string Map2Location)
{
   bool Compatible = true;

   ifstream in1(Map1Location.c_str());
   ifstream in2(Map2Location.c_str());

   for(int i = 0; i < 2 + 6 + 12; i++)
   {
      // 2 for the Z and H masses
      // 6 for the bin count in each dimension
      // 12 for the ranges in each dimension

      double Temp1 = -999, Temp2 = -999;
      in1 >> Temp1;
      in2 >> Temp2;

      if(Temp1 < -900 || Temp2 < -900)   // something's wrong
         Compatible = false;
      if(fabs(Temp1 - Temp2) > 1e-5)   // not the same number
         Compatible = false;
   }

   in2.close();
   in1.close();

   cout << "Checking map compatibility (header-only)";
   if(Compatible == true)
      cout << "......good" << endl;
   else
      cout << "......not compatible" << endl;
   cout << endl;

   return Compatible;
}
//----------------------------------------------------------------------------
double CalculateIntegral(string MapLocation)
{
   double Total = 0;

   ifstream in(MapLocation.c_str());

   double ZMass = -1, HMass = -1;
   in >> HMass >> ZMass;

   int NBinsMass = -1, NBinsPhi0 = -1, NBinsTheta0 = -1, NBinsPhi = -1, NBinsTheta1 = -1, NBinsTheta2 = -1;
   in >> NBinsPhi0 >> NBinsTheta0 >> NBinsPhi >> NBinsTheta1 >> NBinsTheta2 >> NBinsMass;

   double Phi0Min = 0, Phi0Max = 0;
   double Theta0Min = 0, Theta0Max = 0;
   double PhiMin = 0, PhiMax = 0;
   double Theta1Min = 0, Theta1Max = 0;
   double Theta2Min = 0, Theta2Max = 0;
   double MassMin = 0, MassMax = 0;
   in >> Phi0Min >> Phi0Max;
   in >> Theta0Min >> Theta0Max;
   in >> PhiMin >> PhiMax;
   in >> Theta1Min >> Theta1Max;
   in >> Theta2Min >> Theta2Max;
   in >> MassMin >> MassMax;

   if(ZMass < 0 || HMass < 0 || NBinsMass < 0 || NBinsPhi0 < 0 || NBinsTheta1 < 0 || NBinsTheta2 < 0)
   {
      cerr << "INPUTFILE ERROR!  REQUIRED PARAMETERS ARE NEGATIVE!!" << endl;
      return -1;
   }

   ProgressBar Bar(cout, NBinsPhi0 * NBinsTheta0);
   Bar.SetStyle(1);

   cout << "Start to calculate integral of map from file \"" << MapLocation << "\"" << endl;

   for(int iPhi0 = 0; iPhi0 < NBinsPhi0; iPhi0++)
   {
      for(int iTheta0 = 0; iTheta0 < NBinsTheta0; iTheta0++)
      {
         Bar.Update(iPhi0 * NBinsTheta0 + iTheta0 + 1);
         Bar.Print();

         for(int iPhi = 0; iPhi < NBinsPhi; iPhi++)
         {
            for(int iTheta1 = 0; iTheta1 < NBinsTheta1; iTheta1++)
            {
               for(int iTheta2 = 0; iTheta2 < NBinsTheta2; iTheta2++)
               {
                  for(int iMass = 0; iMass < NBinsMass; iMass++)
                  {
                     double Value = -1;
                     in >> Value;

                     Total = Total + Value;
                  }
               }
            }
         }
      }
   }

   Bar.PrintLine();
   cout << "Final Integral = " << Total << endl;
   cout << endl;

   in.close();

   return Total;
}
//----------------------------------------------------------------------------
void DoToysAndEvaluateLikelihood(string Map1Location, string Map2Location, string OutputFileName,
   double Map1Integral, double Map2Integral, int TotalCount)
{
   cout << "Start generating toys from map \"" << Map1Location << "\" and ";
   cout << "evaluate likelihood difference on both maps" << endl;
   cout << "   and write to file \"" << OutputFileName << "\"" << endl;

   // Inputs
   ifstream in1(Map1Location.c_str());
   ifstream in2(Map2Location.c_str());
   ofstream out(OutputFileName.c_str());

   double LogIntegral1 = log(Map1Integral);
   double LogIntegral2 = log(Map2Integral);

   // Prepare random number generator
   RandomBase Random;

   // Read dimensions (and discard other parts of header)
   double ZMass = -1, HMass = -1;
   in1 >> HMass >> ZMass;
   in2 >> HMass >> ZMass;

   long long NBinsMass = -1, NBinsPhi0 = -1, NBinsTheta0 = -1, NBinsPhi = -1, NBinsTheta1 = -1, NBinsTheta2 = -1;
   in1 >> NBinsPhi0 >> NBinsTheta0 >> NBinsPhi >> NBinsTheta1 >> NBinsTheta2 >> NBinsMass;
   in2 >> NBinsPhi0 >> NBinsTheta0 >> NBinsPhi >> NBinsTheta1 >> NBinsTheta2 >> NBinsMass;

   for(int i = 0; i < 12; i++)   // ranges of the dimensions - discard here
   {
      double Temp = -1;
      in1 >> Temp;
      in2 >> Temp;
   }

   // Now loop over all bins and generate toys & evaluate likelihoods
   ProgressBar Bar(cout, NBinsMass * NBinsPhi0 * NBinsTheta0 * NBinsPhi * NBinsTheta1 * NBinsTheta2);
   Bar.SetStyle(1);
   for(long long i = 0; i < NBinsMass * NBinsPhi0 * NBinsTheta0 * NBinsPhi * NBinsTheta1 * NBinsTheta2; i++)
   {
      if(i % (NBinsTheta0 * NBinsPhi * NBinsTheta1 * NBinsTheta2) == 0)
      {
         Bar.Update(i);
         Bar.Print();
      }

      double Value1 = -1;
      in1 >> Value1;
      
      double Value2 = -1;
      in2 >> Value2;

      double TargetCount = Value1 / Map1Integral * TotalCount;
      int RealCount = Random.DrawPoissonInt(TargetCount);

      double LLDistance = (log(Value1) - LogIntegral1) - (log(Value2) - LogIntegral2);

      for(int j = 0; j < RealCount; j++)
         out << LLDistance << endl;
   }

   Bar.Update(NBinsMass * NBinsPhi0 * NBinsTheta0 * NBinsPhi * NBinsTheta1 * NBinsTheta2);
   Bar.Print();
   Bar.PrintLine();

   cout << "Done!" << endl;
   cout << endl;

   // Clean up
   out.close();
   in2.close();
   in1.close();
}
//----------------------------------------------------------------------------







