#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"

#include "Code/DrawRandom.h"

#define MAXBIN 1000

int main();
double KSDiscriminant(int BinCount, double Value1[], double Value2[]);
void Randomize(int BinCount, double Value[], double Error[], double Result[]);
void Transcribe(TGraphAsymmErrors *G, int BinCount, double Value[], double Error[]);

int main()
{
   int BinCount = 10;
   double Value1[MAXBIN] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   double Error1[MAXBIN] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
   double Value2[MAXBIN] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
   double Error2[MAXBIN] = {0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1};

   TFile File("Graphs_SD0_DataPicked.root");

   Transcribe((TGraphAsymmErrors *)File.Get("MassDataSys0_0_1"), BinCount, Value1, Error1);
   Transcribe((TGraphAsymmErrors *)File.Get("MassSmearSys0_0_1"), BinCount, Value2, Error2);

   File.Close();

   double Observed = KSDiscriminant(BinCount, Value1, Value2);

   int Tries = 1000000;
   for(int i = 0; i < Tries; i++)
   {
      double Temp1[MAXBIN], Temp2[MAXBIN];

      Randomize(BinCount, Value1, Error1, Temp1);
      Randomize(BinCount, Value1, Error2, Temp2);

      double Test1 = KSDiscriminant(BinCount, Temp1, Temp2);

      Randomize(BinCount, Value2, Error1, Temp1);
      Randomize(BinCount, Value2, Error2, Temp2);

      double Test2 = KSDiscriminant(BinCount, Temp1, Temp2);

      cout << "TEST " << Test1 << " " << Test2 << endl;
   }

   cout << "Observed " << Observed << endl;

   return 0;
}

double KSDiscriminant(int BinCount, double Value1[], double Value2[])
{
   double Total1 = 0, Total2 = 0;
   for(int i = 0; i < BinCount; i++)
   {
      Total1 = Total1 + Value1[i];
      Total2 = Total2 + Value2[i];
   }

   double Discriminant = 0;

   double Sum1 = 0, Sum2 = 0;
   for(int i = 0; i < BinCount; i++)
   {
      Sum1 = Sum1 + Value1[i];
      Sum2 = Sum2 + Value2[i];

      // KS
      double Y1 = Sum1 / Total1;
      double Y2 = Sum2 / Total2;
      
      // KS3
      // double Y1 = pow((Sum1 / Total1 - 0.5), 3);
      // double Y2 = pow((Sum2 / Total2 - 0.5), 3);

      Discriminant = max(Discriminant, fabs(Y1 - Y2));
   }

   return Discriminant;
}

void Randomize(int BinCount, double Value[], double Error[], double Result[])
{
   // for(int i = 0; i < BinCount; i++)
   //    Result[i] = max(double(0), DrawGaussian(Value[i], Error[i]));

   double CorrelatedNuisance = DrawGaussian(0, 1);

   for(int i = 0; i < BinCount; i++)
   {
      double EV = log(1 + Error[i] / Value[i]);
      double Factor = DrawGaussian(0, EV);

      // This is with half correlated
      Factor = DrawGaussian(0, EV) / sqrt(2) + CorrelatedNuisance * EV / sqrt(2);

      Result[i] = Value[i] * exp(Factor);
   }
}

void Transcribe(TGraphAsymmErrors *G, int BinCount, double Value[], double Error[])
{
   if(G == NULL)
   {
      cerr << "Graph not found!" << endl;
      return;
   }

   double x, y, ey;
   for(int i = 0; i < BinCount; i++)
   {
      G->GetPoint(i, x, y);
      ey = G->GetErrorYhigh(i);

      Value[i] = y;
      Error[i] = ey;
   }
}





