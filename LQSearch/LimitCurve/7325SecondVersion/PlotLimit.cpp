#include <fstream>
#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TH1D.h"
#include "TLegend.h"

#include "SetStyle.h"

struct Limit
{
   double Mass;
   double Expected;
   double ExpectedUp;
   double ExpectedUpUp;
   double ExpectedDown;
   double ExpectedDownDown;
   double Observed;
   bool operator <(const Limit &other) const
   {
      if(Mass < other.Mass)
         return true;
      if(Mass > other.Mass)
         return false;

      if(Expected < other.Expected)
         return true;
      if(Expected > other.Expected)
         return false;

      return false;
   }
};

int main()
{
   SetStyle();

   TGraphAsymmErrors TheoryBand;
   TheoryBand.SetNameTitle("TheoryBand", "");

   int Count = 0;
   ifstream in("Theory.txt");
   while(in)
   {
      double Mass = -1;
      double CrossSection = -1;
      double CrossSectionError = -1;

      in >> Mass >> CrossSection >> CrossSectionError;
      if(Mass <= 0)
         continue;

      TheoryBand.SetPoint(Count, Mass, CrossSection);
      TheoryBand.SetPointError(Count, 0, 0, CrossSectionError, CrossSectionError);
      Count = Count + 1;
   }
   in.close();

   vector<Limit> Limits;
   ifstream in2("Limits.txt");
   while(in2)
   {
      Limit NewPoint;
      NewPoint.Mass = -1;

      in2 >> NewPoint.Mass >> NewPoint.Observed;
      in2 >> NewPoint.Expected >> NewPoint.ExpectedDown >> NewPoint.ExpectedUp;
      in2 >> NewPoint.ExpectedDownDown >> NewPoint.ExpectedUpUp;

      if(NewPoint.Mass < 0)
         continue;

      Limits.push_back(NewPoint);
   }
   in2.close();

   sort(Limits.begin(), Limits.end());

   TGraph Expected;
   Expected.SetNameTitle("Expected", "");

   TGraphAsymmErrors ExpectedOneSigma, ExpectedTwoSigma;
   ExpectedOneSigma.SetNameTitle("ExpectedOneSigma", "");
   ExpectedTwoSigma.SetNameTitle("ExpectedTwoSigma", "");

   TGraph Observed;
   Observed.SetNameTitle("Observed", "");

   Count = 0;
   for(int i = 0; i < (int)Limits.size(); i++)
   {
      if(i > 0 && Limits[i].Mass == Limits[i-1].Mass)
         continue;

      Expected.SetPoint(Count, Limits[i].Mass, Limits[i].Expected);

      ExpectedOneSigma.SetPoint(Count, Limits[i].Mass, Limits[i].Expected);
      ExpectedOneSigma.SetPointError(Count, 0, 0,
         Limits[i].Expected - Limits[i].ExpectedDown, Limits[i].ExpectedUp - Limits[i].Expected);
      ExpectedTwoSigma.SetPoint(Count, Limits[i].Mass, Limits[i].Expected);
      ExpectedTwoSigma.SetPointError(Count, 0, 0,
         Limits[i].Expected - Limits[i].ExpectedUpUp, Limits[i].ExpectedDownDown - Limits[i].Expected);

      Observed.SetPoint(Count, Limits[i].Mass, Limits[i].Observed);

      Count = Count + 1;
   }

   TCanvas C("C", "C", 1024, 1024);

   TH1D HWorld("HWorld", ";M_{LQ};Cross section (pb)", 10, 150, 525);
   HWorld.SetMaximum(50);
   HWorld.SetMinimum(0.05);
   HWorld.SetStats(0);
   HWorld.Draw();

   ExpectedTwoSigma.SetFillColor(kCyan);
   ExpectedTwoSigma.SetLineColor(kBlue);
   ExpectedTwoSigma.SetMarkerStyle(1);
   ExpectedTwoSigma.Draw("3");

   ExpectedOneSigma.SetFillColor(kCyan - 3);
   ExpectedOneSigma.SetLineColor(kBlue);
   ExpectedOneSigma.SetMarkerStyle(1);
   ExpectedOneSigma.Draw("3");

   Expected.SetLineColor(kBlue);
   Expected.SetMarkerStyle(1);
   Expected.Draw("l");

   TheoryBand.SetFillColor(kGreen - 3);
   TheoryBand.Draw("p3");

   Observed.SetMarkerStyle(8);
   Observed.Draw("p");

   TLegend Legend(0.45, 0.85, 0.85, 0.55);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.AddEntry(&ExpectedOneSigma, "Expected 1 #sigma", "lf");
   Legend.AddEntry(&ExpectedTwoSigma, "Expected 2 #sigma", "lf");
   Legend.AddEntry(&Observed, "Observed limit", "p");
   Legend.AddEntry(&TheoryBand, "Theory", "f");
   Legend.Draw();

   AddCMSPreliminary(0.1, 0.92, 1752);

   C.SetLogy();
   C.SaveAs("Limit.png");
   C.SaveAs("Limit.C");
   C.SaveAs("Limit.eps");
   C.SaveAs("Limit.pdf");

   return 0;
}
