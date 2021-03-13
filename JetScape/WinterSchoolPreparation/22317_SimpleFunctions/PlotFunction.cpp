#include <iostream>
using namespace std;

#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   double XMin = CL.GetDouble("XMin", 0);
   double XMax = CL.GetDouble("XMax", 12);
   double YMin = CL.GetDouble("YMin", 0);
   double YMax = CL.GetDouble("YMax", 0.25);
   string Function = CL.Get("Function", "(x^3*exp(-x))/6");
   string Output = CL.Get("Output", "Poisson3.pdf");
   string Title = CL.Get("Title", ";#theta;L(#theta|x=3)");

   TH2D HWorld("HWorld", Title.c_str(), 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   TF1 F("F", Function.c_str(), XMin, XMax);

   TH1D H("H", "", 1000, XMin, XMax);
   for(int i = 1; i <= H.GetNbinsX(); i++)
   {
      double X = H.GetBinCenter(i);
      double Y = F.Eval(X);
      H.SetBinContent(i, Y);
   }

   TCanvas Canvas;
   HWorld.Draw("axis");
   H.Draw("same");
   Canvas.SaveAs(Output.c_str());

   cout << "Mean = " << H.GetMean() << endl;
   cout << "RMS = " << H.GetRMS() << endl;
   cout << "Skewness = " << H.GetSkewness() << endl;

   return 0;
}




