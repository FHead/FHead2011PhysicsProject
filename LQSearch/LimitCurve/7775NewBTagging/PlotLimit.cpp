#include <fstream>
#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TSpline.h"
#include "TF1.h"
#include "TFile.h"

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

   TFile F("Graphs.root", "RECREATE");

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

   TH1D HWorld("HWorld", ";M_{LQ} (GeV);Cross section (pb)", 10, 200, 525);
   HWorld.SetMaximum(50);
   HWorld.SetMinimum(0.005);
   HWorld.SetStats(0);
   HWorld.Draw();

   TGraph D0Exclusion;
   D0Exclusion.SetPoint(0, 247, 10000);
   D0Exclusion.SetPoint(1, 247, 0);
   D0Exclusion.SetLineWidth(9902);
   D0Exclusion.SetFillStyle(3005);
   D0Exclusion.SetLineColor(kBlack);
   D0Exclusion.Draw("l");

   /*
   TLatex ExclusionText;
   ExclusionText.SetTextFont(42);
   ExclusionText.SetTextSize(0.035);
   ExclusionText.DrawLatex(155, 0.065, "D#slash{0} Exclusion");
   // ExclusionText.DrawLatex(255, 0.065, "D#slash{0} Exclusion");
   */

   gStyle->SetHatchesLineWidth(3);
   ExpectedTwoSigma.SetFillColor(kCyan);
   ExpectedTwoSigma.SetLineColor(kBlue);
   ExpectedTwoSigma.SetMarkerStyle(1);
   ExpectedTwoSigma.SetFillStyle(3354);
   ExpectedTwoSigma.Draw("3");

   ExpectedOneSigma.SetFillColor(kCyan - 3);
   ExpectedOneSigma.SetLineColor(kBlue);
   ExpectedOneSigma.SetMarkerStyle(1);
   ExpectedOneSigma.Draw("3");

   Expected.SetLineColor(kBlue);
   Expected.SetMarkerStyle(1);
   Expected.Draw("l");

   TheoryBand.SetFillColor(kGreen - 3);
   TheoryBand.SetFillStyle(3001);
   TheoryBand.Draw("l3");

   gStyle->SetOptFit(0);
   TF1 SmoothLine("SmoothLine", "expo(0)+expo(2)+expo(4)");
   SmoothLine.SetParameter(0, 6.06623);
   SmoothLine.SetParameter(1, -0.0239341);
   SmoothLine.SetParameter(2, 0.0107564);
   SmoothLine.SetParameter(3, -0.00345357);
   SmoothLine.SetParameter(4, 31.4461);
   SmoothLine.SetParameter(5, -0.16413);
   SmoothLine.SetLineStyle(9);
   SmoothLine.SetLineColor(kBlack);
   SmoothLine.SetLineWidth(2);
   Observed.Fit(&SmoothLine, "", "", 195, 600);
   
   Observed.SetMarkerStyle(0);
   Observed.Draw("p");
   // SmoothLine.DrawCopy("same");

   TH1D HDummyObserved("HDummyObserved", "", 2, 0, 1);
   HDummyObserved.SetMarkerStyle(1);
   HDummyObserved.SetLineStyle(9);
   HDummyObserved.SetLineWidth(2);
   HDummyObserved.SetLineColor(kBlack);

   TLegend Legend(0.45, 0.85, 0.85, 0.55);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.AddEntry(&ExpectedOneSigma, "Expected 1 #sigma", "lf");
   Legend.AddEntry(&ExpectedTwoSigma, "Expected 2 #sigma", "lf");
   Legend.AddEntry(&HDummyObserved, "Observed limit", "pl");
   Legend.AddEntry(&TheoryBand, "Theory", "f");
   Legend.AddEntry(&D0Exclusion, "D0 exclusion (5 fb^{-1})", "f");
   Legend.Draw();

   AddCMSPreliminary(0.1, 0.92, 4700);

   C.SetLogy();
   C.SaveAs("LimitR05.png");
   C.SaveAs("LimitR05.C");
   C.SaveAs("LimitR05.eps");
   C.SaveAs("LimitR05.pdf");
   
   HWorld.SetMaximum(10);
   C.SetLogy(false);
   C.SaveAs("LinearLimitR05.png");
   C.SaveAs("LinearLimitR05.C");
   C.SaveAs("LinearLimitR05.eps");
   C.SaveAs("LinearLimitR05.pdf");

   Expected.Write();

   F.Close();

   return 0;
}



