#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"
#include "TGraph.h"

#include "SetStyle.h"

// #define WITH_GAUSSIAN

int main();
double Evaluate(double x);
double EstimateIntegral(double a, double b, double fa, double fc, double fb, double tolerance, vector<double> &checked);

int main()
{
   SetThesisRegularStyle();

   double min = -10;
   double max = +10;
   int N = 10;
   double tolerance = 1e-5;

   vector<double> checked;

   for(int i = 0; i < N; i++)
   {
      double a = (max - min) / N * i + min;
      double b = (max - min) / N * (i + 1) + min;
      double c = (a + b) / 2;

      checked.push_back(a);
      checked.push_back(b);
      checked.push_back(c);

      double fa = Evaluate(a);
      double fb = Evaluate(b);
      double fc = Evaluate(c);

      EstimateIntegral(a, b, fa, fc, fb, tolerance / N, checked);
   }

   TH1D HFunction("HFunction", ";x;f(x)", 1000, min, max);
   for(int i = 1; i <= HFunction.GetNbinsX(); i++)
      HFunction.SetBinContent(i, Evaluate(HFunction.GetBinCenter(i)));

   HFunction.SetStats(0);
   HFunction.SetMinimum(0);

   TGraph HPoint;
   for(int i = 0; i < (int)checked.size(); i++)
      HPoint.SetPoint(i, checked[i], Evaluate(checked[i]));

   HPoint.SetMarkerStyle(20);
   HPoint.SetMarkerSize(1.5);

   TCanvas C;

   HFunction.Draw();
   HPoint.Draw("p");

#ifdef WITH_GAUSSIAN
   C.SaveAs("MultiDimensionalDetails-Recursive-ActionB.png");
   C.SaveAs("MultiDimensionalDetails-Recursive-ActionB.C");
   C.SaveAs("MultiDimensionalDetails-Recursive-ActionB.eps");
   C.SaveAs("MultiDimensionalDetails-Recursive-ActionB.pdf");
#else
   C.SaveAs("MultiDimensionalDetails-Recursive-ActionA.png");
   C.SaveAs("MultiDimensionalDetails-Recursive-ActionA.C");
   C.SaveAs("MultiDimensionalDetails-Recursive-ActionA.eps");
   C.SaveAs("MultiDimensionalDetails-Recursive-ActionA.pdf");
#endif

   return 0;
}

double Evaluate(double x)
{
#ifdef WITH_GAUSSIAN
   return exp(-x * x / 2) + x * x / 75;
#else
   return x * x / 75;
#endif
}

double EstimateIntegral(double a, double b, double fa, double fc, double fb, double tolerance, vector<double> &checked)
{
   double c = (a + b) / 2;
   double d = (a + c) / 2;
   double e = (c + b) / 2;

   checked.push_back(d);
   checked.push_back(e);

   double fd = Evaluate(d);
   double fe = Evaluate(e);

   double sab = (fa + 4 * fc + fb) * (b - a) / 6;
   double sac = (fa + 4 * fd + fc) * (c - a) / 6;
   double scb = (fc + 4 * fe + fb) * (b - c) / 6;

   if(fabs(sab - sac - scb) < 10 * tolerance)
      return sac + scb;

   double left = EstimateIntegral(a, c, fa, fd, fc, tolerance / 2, checked);
   double right = EstimateIntegral(c, b, fc, fe, fb, tolerance / 2, checked);

   return left + right;
}






