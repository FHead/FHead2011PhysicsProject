#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#include "TLegend.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TH1D.h"

#include "SetStyle.h"

int main();
double InterpolateTheory(double Mass, vector<double> &TheoryMass, vector<double> &TheoryCrossSection);

int main()
{
   SetStyle();

   TGraph GD0;
   GD0.SetNameTitle("D0Curve", ";LQ Mass (GeV/c^{2});Br(LQ #rightarrow b #nu_{#tau})");

   int D0Count = 0;
   ifstream D0File("D0.txt");
   while(D0File)
   {
      double Mass = 0;
      double TheoryToObservedRatio = 0;

      D0File >> Mass >> TheoryToObservedRatio;

      if(Mass <= 0 || TheoryToObservedRatio <= 0)
         continue;

      GD0.SetPoint(D0Count, Mass, sqrt(1 / TheoryToObservedRatio));
      D0Count = D0Count + 1;
   }
   D0File.close();

   GD0.SetPoint(D0Count, 400, 99999);
   GD0.SetPoint(D0Count + 1, 100, 99999);
   GD0.SetPoint(D0Count + 2, 100, 0);

   vector<double> TheoryMass;
   vector<double> TheoryCrossSection;

   ifstream TheoryFile("Theory.txt");
   while(TheoryFile)
   {
      double Mass = 0;
      double CrossSection = 0;

      TheoryFile >> Mass >> CrossSection;

      if(Mass <= 0 || CrossSection <= 0)
         continue;

      TheoryMass.push_back(Mass);
      TheoryCrossSection.push_back(CrossSection);
   }
   TheoryFile.close();

   TGraph GCMS;
   GCMS.SetNameTitle("GCMS", "");

   int CMSCount = 0;
   ifstream CMSFile("ObservedLimits.txt");
   while(CMSFile)
   {
      double Mass = 0;
      double CrossSection = 0;

      CMSFile >> Mass >> CrossSection;

      if(Mass <= 0 || CrossSection <= 0)
         continue;

      double Theory = InterpolateTheory(Mass, TheoryMass, TheoryCrossSection);

      GCMS.SetPoint(CMSCount, Mass, sqrt(CrossSection / Theory));
      CMSCount = CMSCount + 1;
   }
   CMSFile.close();
   
   TGraphAsymmErrors GMC;
   GMC.SetNameTitle("GMC", "");
   TGraph GMCCenter;
   GMCCenter.SetNameTitle("GMCCenter", "");
   
   int MCCount = 0;
   ifstream MCFile("ExpectedLimits.txt");
   while(MCFile)
   {
      double Mass = 0;
      double CrossSection = 0;
      double CrossSectionDown = 0;
      double CrossSectionUp = 0;

      MCFile >> Mass >> CrossSection >> CrossSectionDown >> CrossSectionUp;

      if(Mass <= 0 || CrossSection <= 0 || CrossSectionDown <= 0 || CrossSectionUp <= 0)
         continue;

      double Theory = InterpolateTheory(Mass, TheoryMass, TheoryCrossSection);

      GMC.SetPoint(MCCount, Mass, sqrt(CrossSection / Theory));
      GMC.SetPointError(MCCount, 0, 0,
         sqrt(CrossSection / Theory) - sqrt(CrossSectionDown / Theory),
         sqrt(CrossSectionUp / Theory) - sqrt(CrossSection / Theory));
      GMCCenter.SetPoint(MCCount, Mass, sqrt(CrossSection / Theory));

      MCCount = MCCount + 1;
   }
   MCFile.close();

   TCanvas Canvas("Canvas", "", 1024, 1024);
   
   TH1D HWorld("HWorld", ";LQ Mass (GeV);Br(LQ #rightarrow b#nu_{#tau})", 10, 200, 400);
   HWorld.SetMinimum(0.00);
   HWorld.SetMaximum(1.00);
   HWorld.SetStats(0);
   HWorld.Draw();

   GMC.SetLineWidth(2);
   GMC.SetLineColor(kGreen - 6);
   GMC.SetFillColor(kGreen - 5);
   GMC.Draw("3");

   GD0.SetLineWidth(2);
   GD0.SetFillColor(kGray);
   GD0.Draw("lf");
   
   GCMS.SetLineWidth(2);
   GCMS.SetLineColor(kBlue);
   GCMS.Draw("l");
   
   GMCCenter.SetLineWidth(2);
   GMCCenter.SetLineColor(kGreen - 6);
   GMCCenter.SetFillColor(kGreen - 5);
   GMCCenter.Draw("l");

   TGraph HorizontalLine;
   HorizontalLine.SetPoint(0, 200, 1);
   HorizontalLine.SetPoint(1, 400, 1);
   HorizontalLine.Draw("l");

   TLegend legend(0.3, 0.15, 0.85, 0.35);
   // legend.SetFillStyle(0);
   // legend.SetBorderSize(0);
   legend.SetTextFont(42);
   legend.AddEntry(&GD0, "D0 exclusion (5.2 fb^{-1})", "f");
   legend.AddEntry(&GCMS, "CMS 95% CL Limit (observed, 1.75 fb^{-1})", "l");
   legend.AddEntry(&GMC, "CMS 95% CL Limit (expected, 1.75 fb^{-1})", "lf");
   legend.Draw();

   Canvas.SetGridx();
   Canvas.SetGridy();

   HWorld.Draw("axis same");

   AddCMSPreliminary(0.1, 0.92, 1752);

   Canvas.SaveAs("Limit2D.png");
   Canvas.SaveAs("Limit2D.C");
   Canvas.SaveAs("Limit2D.eps");
   Canvas.SaveAs("Limit2D.pdf");
}

double InterpolateTheory(double Mass, vector<double> &TheoryMass, vector<double> &TheoryCrossSection)
{
   // no extrapolation
   if(Mass < TheoryMass[0])
      return -1;
   if(Mass > TheoryMass[TheoryMass.size()-1])
      return -1;

   double SigmaL = 0;
   double SigmaR = 0;
   double MassL = 0;
   double MassR = 0;

   for(int i = 0; i + 1 < (int)TheoryMass.size(); i++)
   {
      if(Mass > TheoryMass[i+1])
         continue;
      if(Mass == TheoryMass[i+1])
         return TheoryCrossSection[i+1];
      
      SigmaL = log(TheoryCrossSection[i]);
      SigmaR = log(TheoryCrossSection[i+1]);
      MassL = TheoryMass[i];
      MassR = TheoryMass[i+1];
      break;
   }

   double LogSigma = SigmaL - (Mass - MassL) / (MassR - MassL) * (SigmaL - SigmaR);

   return exp(LogSigma);
}


