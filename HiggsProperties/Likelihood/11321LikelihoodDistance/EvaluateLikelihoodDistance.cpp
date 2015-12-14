//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
//---------------------------------------------------------------------------
#include "ProgressBar.h"
#include "DrawRandom2.h"
//---------------------------------------------------------------------------
int main();
bool MapCompatibilityCheck(string Map1Location, string Map2Location, bool CheckHiggsMass = false);
double CalculateIntegral(string FileName = "");
void DoToysAndEvaluateLikelihood(vector<string> Maps1, vector<string> Maps2,
   vector<double> Integral1, vector<double> Integral2, string ResultLocation, int ToyCount);
double CalculateMassIntegral(const vector<double> &HiggsMasses, const vector<double> &Values,
   const double Mean = 125, const double Gamma = 2);
double Interpolate(const vector<double> &HiggsMasses, const vector<double> &Values, const double Mass);
//---------------------------------------------------------------------------
int main()
{
   // Prepare input maps - hard-code for now - assume sorted as a function of 4l mass
   vector<string> ScalarMaps;
   // ScalarMaps.push_back("SignalMaps/All_Scalar_100.map7");
   // ScalarMaps.push_back("SignalMaps/All_Scalar_110.map7");
   ScalarMaps.push_back("SignalMaps/All_Scalar_120.map7");
   ScalarMaps.push_back("SignalMaps/All_Scalar_125.map7");
   ScalarMaps.push_back("SignalMaps/All_Scalar_130.map7");
   // ScalarMaps.push_back("SignalMaps/All_Scalar_140.map7");
   // ScalarMaps.push_back("SignalMaps/All_Scalar_160.map7");
   // ScalarMaps.push_back("SignalMaps/All_Scalar_200.map7");
   // ScalarMaps.push_back("SignalMaps/All_Scalar_300.map7");
   // ScalarMaps.push_back("SignalMaps/All_Scalar_400.map7");

   vector<string> PseudoscalarMaps;
   // PseudoscalarMaps.push_back("SignalMaps/All_PseudoScalar_100.map7");
   // PseudoscalarMaps.push_back("SignalMaps/All_PseudoScalar_110.map7");
   PseudoscalarMaps.push_back("SignalMaps/All_PseudoScalar_120.map7");
   PseudoscalarMaps.push_back("SignalMaps/All_PseudoScalar_125.map7");
   PseudoscalarMaps.push_back("SignalMaps/All_PseudoScalar_130.map7");
   // PseudoscalarMaps.push_back("SignalMaps/All_PseudoScalar_140.map7");
   // PseudoscalarMaps.push_back("SignalMaps/All_PseudoScalar_160.map7");
   // PseudoscalarMaps.push_back("SignalMaps/All_PseudoScalar_200.map7");
   // PseudoscalarMaps.push_back("SignalMaps/All_PseudoScalar_300.map7");
   // PseudoscalarMaps.push_back("SignalMaps/All_PseudoScalar_400.map7");

   // Check map compatibility
   if(ScalarMaps.size() != PseudoscalarMaps.size())
   {
      cerr << "Number of maps different between two sets!  Now exit..." << endl;
      return -1;
   }

   bool Compatible = true;
   for(int i = 1; i < (int)ScalarMaps.size() && Compatible == true; i++)
      if(MapCompatibilityCheck(ScalarMaps[0], ScalarMaps[i], false) == false)
         Compatible = false;
   for(int i = 1; i < (int)PseudoscalarMaps.size() && Compatible == true; i++)
      if(MapCompatibilityCheck(PseudoscalarMaps[0], PseudoscalarMaps[i], false) == false)
         Compatible = false;
   if(Compatible == false)
   {
      cerr << "Maps not self-consistent within set!  Now exit..." << endl;
      return -1;
   }

   for(int i = 0; i < (int)ScalarMaps.size() && Compatible == true; i++)
      if(MapCompatibilityCheck(ScalarMaps[i], PseudoscalarMaps[i], true) == false)
         Compatible = false;
   if(Compatible == false)
   {
      cerr << "Maps not consistent across sets!  Now exit..." << endl;
      return -1;
   }

   // For each map, calculate integral
   vector<double> ScalarIntegral, PseudoscalarIntegral;
   /*
   for(int i = 0; i < (int)ScalarMaps.size(); i++)
      ScalarIntegral.push_back(CalculateIntegral(ScalarMaps[i]));
   for(int i = 0; i < (int)PseudoscalarMaps.size(); i++)
      PseudoscalarIntegral.push_back(CalculateIntegral(PseudoscalarMaps[i]));
   */
   ScalarIntegral.push_back(8.34895e14);
   ScalarIntegral.push_back(2.01918e15);
   ScalarIntegral.push_back(4.50923e15);
   PseudoscalarIntegral.push_back(7.82794e12);
   PseudoscalarIntegral.push_back(2.01978e13);
   PseudoscalarIntegral.push_back(4.91246e13);
   
   for(int i = 0; i < (int)ScalarMaps.size(); i++)
   {
      if(ScalarIntegral[i] < 0)
      {
         cerr << "Integral error, exit" << endl;
         return -1;
      }
   }
   for(int i = 0; i < (int)PseudoscalarMaps.size(); i++)
   {
      if(PseudoscalarIntegral[i] < 0)
      {
         cerr << "Integral error, exit" << endl;
         return -1;
      }
   }

   // Output location - hardcoded for now
   string ScalarToyLocation = "SortedLL_Scalar.toyll";
   string PseudoscalarToyLocation = "SortedLL_Pseudoscalar.toyll";

   // Evaluate toys and write result
   DoToysAndEvaluateLikelihood(ScalarMaps, PseudoscalarMaps,
      ScalarIntegral, PseudoscalarIntegral, ScalarToyLocation, 1000000);
   DoToysAndEvaluateLikelihood(PseudoscalarMaps, ScalarMaps,
      PseudoscalarIntegral, ScalarIntegral, PseudoscalarToyLocation, 1000000);

   return 0;
}
//---------------------------------------------------------------------------
bool MapCompatibilityCheck(string Map1Location, string Map2Location, bool CheckHiggsMass)
{
   bool Compatible = true;

   ifstream in1(Map1Location.c_str());
   ifstream in2(Map2Location.c_str());

   for(int i = 0; i < 1 + 7 + 14; i++)
   {
      // 1 for the H masses
      // 7 for the bin count in each dimension
      // 14 for the ranges in each dimension, but the last 2 are masses

      double Temp1 = -999, Temp2 = -999;
      in1 >> Temp1;
      in2 >> Temp2;

      if(CheckHiggsMass == false && i == 0)   // don't check higgs mass
         continue;
      if(CheckHiggsMass == false && i >= 18)
         continue;

      if(Temp1 < -900 || Temp2 < -900)   // something's wrong
         Compatible = false;
      if(fabs(Temp1 - Temp2) > 1e-5)   // not the same number
         Compatible = false;
   }

   in2.close();
   in1.close();

   cout << "Checking map compatibility (header-only) between" << endl
      << "   \"" << Map1Location << "\" and \"" << Map2Location << "\"";
   if(Compatible == true)
      cout << "......good" << endl;
   else
      cout << "......not compatible" << endl;
   cout << endl;

   return Compatible;
}
//---------------------------------------------------------------------------
double CalculateIntegral(string FileName)
{
   // Sanity check
   if(FileName == "")
      return -1;

   // Placeholder for integral
   double Total = 0;

   // Prepare input and read dimensions
   ifstream in(FileName.c_str());

   double HMass = 0;
   in >> HMass;

   int NBinsPhi0 = -1, NBinsTheta0 = -1, NBinsPhi = -1, NBinsTheta1 = -1, NBinsTheta2 = -1;
   in >> NBinsPhi0 >> NBinsTheta0 >> NBinsPhi >> NBinsTheta1 >> NBinsTheta2;

   int NBinsMass1 = -1, NBinsMass2 = -1;
   in >> NBinsMass1 >> NBinsMass2;

   if(NBinsPhi0 <= 0 || NBinsTheta0 <= 0 || NBinsPhi <= 0 || NBinsTheta1 <= 0 || NBinsTheta2 <= 0
      || NBinsMass1 <= 0 || NBinsMass2 <= 0)
   {
      cerr << "Error!  Dimension of map non-positive in map " << FileName << "!" << endl;
      return -1;
   }

   // Progress bar for the impatient
   ProgressBar Bar(cout, NBinsPhi0 * NBinsTheta0);
   Bar.SetStyle(1);

   cout << "Start to calculate integral from file \"" << FileName << "\"" << endl;

   // Actual loops and calculate integral
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
                  for(int iMass1 = 0; iMass1 < NBinsMass1; iMass1++)
                  {
                     for(int iMass2 = 0; iMass2 < NBinsMass2; iMass2++)
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
   }

   Bar.PrintLine();
   cout << "Integral = " << Total << endl;
   cout << endl;

   in.close();

   return Total;
}
//---------------------------------------------------------------------------
void DoToysAndEvaluateLikelihood(vector<string> Maps1, vector<string> Maps2,
   vector<double> Integral1, vector<double> Integral2, string ResultLocation, int ToyCount)
{
   // Basic parameters
   double HMean = 125;
   double HGamma = 2;

   // Sanity check
   int MapCount = Maps1.size();
   if(MapCount != Maps2.size())
   {
      cerr << "Map size inconsistent.  This should not happen!" << endl;
      cerr << "   Now take the smaller of the two lists..." << endl;
      cerr << endl;

      MapCount = min(Maps1.size(), Maps2.size());
   }

   // Open map files
   vector<ifstream *> in1, in2;
   for(int i = 0; i < MapCount; i++)
   {
      in1.push_back(new ifstream(Maps1[i].c_str()));
      in2.push_back(new ifstream(Maps2[i].c_str()));
   }

   ofstream out(ResultLocation.c_str());

   // Prepare random number generator
   RandomBase Random;

   // Read map dimensions
   vector<double> HiggsMasses(MapCount);
   for(int i = 0; i < MapCount; i++)
   {
      *(in1[i]) >> HiggsMasses[i];
      *(in2[i]) >> HiggsMasses[i];
   }

   double MassMin = HiggsMasses[0];
   double MassMax = HiggsMasses[HiggsMasses.size()-1];

   int NBinsPhi0 = -1, NBinsTheta0 = -1, NBinsPhi = -1, NBinsTheta1 = -1, NBinsTheta2 = -1;
   int NBinsMass1 = -1, NBinsMass2 = -1;
   
   for(int i = 0; i < MapCount; i++)
   {
      *(in1[i]) >> NBinsPhi0 >> NBinsTheta0 >> NBinsPhi >> NBinsTheta1 >> NBinsTheta2;
      *(in1[i]) >> NBinsMass1 >> NBinsMass2;
      *(in2[i]) >> NBinsPhi0 >> NBinsTheta0 >> NBinsPhi >> NBinsTheta1 >> NBinsTheta2;
      *(in2[i]) >> NBinsMass1 >> NBinsMass2;
   }

   for(int i = 0; i < 14; i++)   // discard ranges of the dimensions
   {
      for(int j = 0; j < MapCount; j++)
      {
         double Temp = -1;
         *(in1)[j] >> Temp;
         *(in2)[j] >> Temp;
      }
   }

   // P(MH) normalization
   vector<double> Ones;
   for(int i = 0; i < MapCount; i++)
      Ones.push_back(1);
   double MHNormalization = CalculateMassIntegral(HiggsMasses, Ones, HMean, HGamma);

   // Now the real loop
   ProgressBar Bar(cout, NBinsPhi0 * NBinsTheta0 * NBinsPhi * NBinsTheta1 * NBinsTheta2 * NBinsMass1 * NBinsMass2);
   Bar.SetStyle(1);

   for(long long i = 0;
      i < NBinsPhi0 * NBinsTheta0 * NBinsPhi * NBinsTheta1 * NBinsTheta2 * NBinsMass1 * NBinsMass2; i++)
   {
      if(i % (NBinsPhi * NBinsTheta1 * NBinsTheta2 * NBinsMass1 * NBinsMass2) == 0)
      {
         Bar.Update(i);
         Bar.Print();
      }

      vector<double> Value1(MapCount);
      double MaxOfValue1 = 0;
      vector<double> Value2(MapCount);
      for(int j = 0; j < MapCount; j++)
      {
         *(in1[j]) >> Value1[j];
         *(in2[j]) >> Value2[j];

         Value1[j] = Value1[j] / Integral1[j];
         Value2[j] = Value2[j] / Integral2[j];

         if(MaxOfValue1 < Value1[j])
            MaxOfValue1 = Value1[j];
      }
      MaxOfValue1 = MaxOfValue1 / HGamma / HGamma;

      double TargetCount = CalculateMassIntegral(HiggsMasses, Value1, HMean, HGamma) / MHNormalization;
      TargetCount = TargetCount * ToyCount;

      int RealCount = Random.DrawPoissonInt(TargetCount);

      for(int j = 0; j < RealCount; j++)
      {
         double MassValue = 0;
         double PDFValue = 0;

         bool Accept = false;
         while(Accept == false)
         {
            MassValue = Random.DrawRandom(MassMin, MassMax);
            PDFValue = Interpolate(HiggsMasses, Value1, MassValue);
            PDFValue = PDFValue / ((MassValue - HMean) * (MassValue - HMean) + HGamma * HGamma);
            PDFValue = PDFValue / MHNormalization;

            double Check = Random.DrawRandom(0, MaxOfValue1);

            if(Check < PDFValue)
               Accept = true;
         }

         double OtherPDFValue = Interpolate(HiggsMasses, Value2, MassValue);
         OtherPDFValue = OtherPDFValue / ((MassValue - HMean) * (MassValue - HMean) + HGamma * HGamma);
         OtherPDFValue = OtherPDFValue / MHNormalization;

         // cout << PDFValue << " " << OtherPDFValue << endl;

         out << log(PDFValue) - log(OtherPDFValue) << endl;
      }
   }

   Bar.Update(NBinsPhi0 * NBinsTheta0 * NBinsPhi * NBinsTheta1 * NBinsTheta2 * NBinsMass1 * NBinsMass2);
   Bar.Print();
   Bar.PrintLine();

   cout << "Done!!" << endl;
   cout << endl;

   // Clean-up
   out.close();

   for(int i = 0; i < MapCount; i++)
   {
      if(in1[i] == NULL)
         continue;

      in1[i]->close();
      delete in1[i];
      in1[i] = NULL;
   }
   for(int i = 0; i < MapCount; i++)
   {
      if(in2[i] == NULL)
         continue;

      in2[i]->close();
      delete in2[i];
      in2[i] = NULL;
   }
}
//---------------------------------------------------------------------------
double CalculateMassIntegral(const vector<double> &HiggsMasses, const vector<double> &Values,
   const double Mean, const double Gamma)
{
   double Min = HiggsMasses[0];
   double Max = HiggsMasses[HiggsMasses.size()-1];
   int BinCount = 300;
   double BinSize = (Max - Min) / BinCount;

   double Total = 0;

   int Index = 0;
   for(int i = 0; i < BinCount; i++)
   {
      double Mass = (i + 0.5) * BinSize + Min;
      if(Mass < HiggsMasses[0])
         continue;
      if(Mass >= HiggsMasses[HiggsMasses.size()-1])
         break;

      while(Index < (int)HiggsMasses.size() - 1 && HiggsMasses[Index+1] < Mass)
         Index = Index + 1;

      double Value = Values[Index+1] * (Mass - HiggsMasses[Index])
         + Values[Index] * (HiggsMasses[Index+1] - Mass);
      Value = Value / (HiggsMasses[Index+1] - HiggsMasses[Index]);

      Value = Value / ((Mass - Mean) * (Mass - Mean) + Gamma * Gamma);

      Total = Total + Value * BinSize;
   }

   return Total;
}
//---------------------------------------------------------------------------
double Interpolate(const vector<double> &HiggsMasses, const vector<double> &Values, const double Mass)
{
   if(Mass < HiggsMasses[0])
      return 0;
   if(Mass >= HiggsMasses[HiggsMasses.size()-1])
      return 0;

   int Min = 0;
   int Max = (int)HiggsMasses.size() - 1;

   while(Max - Min > 1)
   {
      int Middle = (Min + Max) / 2;

      if(HiggsMasses[Middle] < Mass)
         Min = Middle;
      else
         Max = Middle;
   }

   double Result = Values[Min] * (HiggsMasses[Max] - Mass)
      + Values[Max] * (Mass - HiggsMasses[Min]);
   Result = Result / (HiggsMasses[Max] - HiggsMasses[Min]);

   return Result;
}
//---------------------------------------------------------------------------














