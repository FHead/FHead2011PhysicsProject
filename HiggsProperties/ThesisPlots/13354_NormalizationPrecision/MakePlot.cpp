#include <map>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

#include "TCanvas.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TF1.h"

#include "SetStyle.h"

int main();
double Average(vector<double> &Values);
pair<double, double> GetRMS(vector<double> &Values, int N);

int main()
{
   SetThesisRegularStyle();

   ifstream in("V1A1ZZ");

   vector<double> Values;

   while(in)
   {
      double Temp = -99999;
      in >> Temp;
      if(Temp > -99998.9)
         Values.push_back(Temp);
   }

   TGraph G;
   G.SetMarkerStyle(7);

   double Mean = Average(Values);
   for(int N = 1; N < (int)Values.size() / 10; N++)
   {
      pair<double, double> RMS = GetRMS(Values, N);

      G.SetPoint(N - 1, N * 1000, RMS.first / Mean);
   }

   TCanvas C;
   C.SetLogy();
   C.SetLogx();

   TH1D HWorld("HWorld", ";Sample Size;RMS/Mean", 100, 300, 2000000);
   HWorld.SetStats(0);
   HWorld.SetMaximum(0.30);
   HWorld.SetMinimum(5e-4);
   // HWorld.GetXaxis()->SetTitleOffset(1.2);
   // HWorld.GetYaxis()->SetTitleOffset(1.4);

   TF1 F("F", "1.90505/sqrt(x)", 500, 1e7);
   F.SetLineWidth(1);
   F.SetLineColor(kBlue);

   HWorld.Draw();
   G.Draw("p");
   F.Draw("same");

   C.SaveAs("MultiDimensionalOverview-Normalization-Precision.png");
   C.SaveAs("MultiDimensionalOverview-Normalization-Precision.C");
   C.SaveAs("MultiDimensionalOverview-Normalization-Precision.eps");
   C.SaveAs("MultiDimensionalOverview-Normalization-Precision.pdf");

   return 0;
}

double Average(vector<double> &Values)
{
   double Sum = 0;
   for(int i = 0; i < (int)Values.size(); i++)
      Sum = Sum + Values[i];
   return Sum / Values.size();
}

pair<double, double> GetRMS(vector<double> &Values, int N)
{
   random_shuffle(Values.begin(), Values.end());

   vector<double> Means(Values.size() / N);

   for(int i = 0; i < Values.size() / N; i++)
   {
      double Sum = 0;
      for(int j = 0; j < N; j++)
         Sum = Sum + Values[i*N+j];
      Means[i] = Sum / N;
   }

   double Sum0 = 0, Sum1 = 0, Sum2 = 0;
   for(int i = 0; i < (int)Means.size(); i++)
   {
      Sum0 = Sum0 + 1;
      Sum1 = Sum1 + Means[i];
      Sum2 = Sum2 + Means[i] * Means[i];
   }

   double RMS = sqrt((Sum2 - Sum1 * Sum1 / Sum0) / (Sum0 - 1));

   pair<double, double> Result;
   Result.first = RMS;
   Result.second = 0;

   return Result;
}




