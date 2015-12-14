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
#include "TF1.h"
#include "TStyle.h"

#include "SetStyle.h"

int main();
double InterpolateTheory(double Mass, vector<double> &TheoryMass, vector<double> &TheoryCrossSection);

int main()
{
   SetStyle();
   gStyle->SetOptFit(0);

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

   TGraph GCMS, GSmoothedCMS;
   GCMS.SetNameTitle("GCMS", "");
   GSmoothedCMS.SetNameTitle("GSmoothedCMS", "");

   int CMSCount = 0;
   ifstream CMSFile("ObservedLimits.txt");
   while(CMSFile)
   {
      double Mass = 0;
      double CrossSection = 0;

      CMSFile >> Mass >> CrossSection;

      if(Mass <= 0 || CrossSection <= 0)
         continue;
      if(Mass == 260)
         continue;

      double Theory = InterpolateTheory(Mass, TheoryMass, TheoryCrossSection);

      GCMS.SetPoint(CMSCount, Mass, sqrt(CrossSection / Theory));
      CMSCount = CMSCount + 1;
   }
   CMSFile.close();
   
   TGraphAsymmErrors GMC;
   GMC.SetNameTitle("GMC", "");
   
   TGraph GMCCenter, GMCUp, GMCDown, GSmoothedMCCenter;
   GMCCenter.SetNameTitle("GMCCenter", "");
   GMCUp.SetNameTitle("GMCUp", "");
   GMCDown.SetNameTitle("GMCDown", "");
   GSmoothedMCCenter.SetNameTitle("GSmoothedMCCenter", "");
   
   double tempy = 0;

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
      if(Mass == 260)
         continue;

      double Theory = InterpolateTheory(Mass, TheoryMass, TheoryCrossSection);

      GMC.SetPoint(MCCount, Mass, sqrt(CrossSection / Theory));
      GMC.SetPointError(MCCount, 0, 0,
         sqrt(CrossSection / Theory) - sqrt(CrossSectionDown / Theory),
         sqrt(CrossSectionUp / Theory) - sqrt(CrossSection / Theory));

      GMCCenter.SetPoint(MCCount, Mass, sqrt(CrossSection / Theory));
      GMCUp.SetPoint(MCCount, Mass, sqrt(CrossSectionUp / Theory));
      GMCDown.SetPoint(MCCount, Mass, sqrt(CrossSectionDown / Theory));

      MCCount = MCCount + 1;
   }
   MCFile.close();

   TGraphAsymmErrors GMCSmooth;
   GMCSmooth.SetNameTitle("GMSSmooth", "");

   /*
   TF1 MCFit("MCFit", "pol6", 200, 380);
   MCFit.SetParameter(0, 0.144597);
   MCFit.SetParameter(1, 0.0223388);
   MCFit.SetParameter(2, -0.000262471);
   MCFit.SetParameter(3, 1.35728e-6);
   MCFit.SetParameter(4, -3.47156e-9);
   MCFit.SetParameter(5, 4.38748e-12);
   MCFit.SetParameter(6, -2.14251e-15);
   MCFit.SetLineWidth(2);
   MCFit.SetLineColor(kRed);
   // GMCCenter.Fit(&MCFit, "", "", 200, 300);
   
   TF1 MCFitUp("MCFitUp", "pol6", 200, 380);
   MCFitUp.SetParameter(0, 1.2143);
   MCFitUp.SetParameter(1, 0.00314374);
   MCFitUp.SetParameter(2, -0.000103908);
   MCFitUp.SetParameter(3, 6.71235e-7);
   MCFitUp.SetParameter(4, -1.83473e-9);
   MCFitUp.SetParameter(5, 2.37352e-12);
   MCFitUp.SetParameter(6, -1.14061e-15);
   MCFitUp.SetLineWidth(2);
   MCFitUp.SetLineColor(kRed);
   // GMCUp.Fit(&MCFitUp, "", "", 200, 340);
   
   TF1 MCFitDown("MCFitDown", "expo+expo(2)", 200, 380);
   MCFitDown.SetParameter(0, -23.3964);
   MCFitDown.SetParameter(1, 0.0606313);
   MCFitDown.SetParameter(2, -1.03144);
   MCFitDown.SetParameter(3, 0.00228552);
   MCFitDown.SetLineWidth(2);
   MCFitDown.SetLineColor(kRed);
   // GMCDown.Fit(&MCFitDown);

   TF1 CMSFit("CMSFit", "expo+expo(2)+expo(4)", 200, 380);
   CMSFit.SetParameter(0, -19.4588);
   CMSFit.SetParameter(1, 0.0486725);
   CMSFit.SetParameter(2, -19.4589);
   CMSFit.SetParameter(3, 0.0486726);
   CMSFit.SetParameter(4, -0.925374);
   CMSFit.SetParameter(5, 0.00200222);
   CMSFit.SetLineWidth(2);
   CMSFit.SetLineColor(kRed);
   // GCMS.Fit(&CMSFit);

   for(int i = 0; i < 41; i++)
   {
      double Mass = 200 + i * 5;
      double OldCenter = 0;

      double NewCenter = MCFit.Eval(Mass);
      double NewUp = MCFitUp.Eval(Mass);
      double NewDown = MCFitDown.Eval(Mass);

      GMC.SetPoint(i, Mass, NewCenter);
      GMC.SetPointError(i, 0, 0, NewCenter - NewDown, NewUp - NewCenter);

      GSmoothedMCCenter.SetPoint(i, Mass, NewCenter);

      double CMSValue = CMSFit.Eval(Mass);

      GSmoothedCMS.SetPoint(i, Mass, CMSValue);
   }
   */

   TCanvas Canvas("Canvas", "", 1024, 1024);
   
   TH1D HWorld("HWorld", ";LQ Mass (GeV);Br(LQ #rightarrow b#nu_{#tau})", 10, 200, 450);
   HWorld.SetMinimum(0.30);
   HWorld.SetMaximum(1.00);
   HWorld.SetStats(0);
   HWorld.Draw();

   GMC.SetLineWidth(2);
   GMC.SetLineColor(kGreen - 6);
   GMC.SetFillColor(kGreen - 5);
   GMC.Draw("3");
   GMCCenter.SetLineWidth(2);
   GMCCenter.SetLineColor(kGreen - 6);
   GMCCenter.Draw("l");

   GD0.SetLineWidth(1);
   GD0.SetLineColor(kGray);
   GD0.SetFillColor(kGray);
   GD0.Draw("lf");
   
   GCMS.SetLineWidth(2);
   GCMS.SetLineColor(kBlack);
   GCMS.Draw("l");
   // GSmoothedCMS.SetLineWidth(2);
   // GSmoothedCMS.SetLineColor(kBlue);
   // GSmoothedCMS.Draw("l");
   
   // GSmoothedMCCenter.SetLineWidth(2);
   // GSmoothedMCCenter.SetLineColor(kGreen - 6);
   // GSmoothedMCCenter.SetFillColor(kGreen - 5);
   // GSmoothedMCCenter.Draw("l");

   TGraph HorizontalLine;
   HorizontalLine.SetPoint(0, 200, 1);
   HorizontalLine.SetPoint(1, 400, 1);
   HorizontalLine.Draw("l");

   TLegend legend(0.3, 0.15, 0.85, 0.35);
   // legend.SetFillStyle(0);
   // legend.SetBorderSize(0);
   legend.SetTextFont(42);
   legend.AddEntry(&GD0, "D0 exclusion (5.2 fb^{-1})", "f");
   legend.AddEntry(&GCMS, "CMS 95% CL Limit (observed, 4.7 fb^{-1})", "l");
   legend.AddEntry(&GMC, "CMS 95% CL Limit (expected, 4.7 fb^{-1})", "lf");
   legend.Draw();

   Canvas.SetGridx();
   Canvas.SetGridy();

   HWorld.Draw("axis same");

   /*
   MCFit.Draw("same");
   MCFitUp.Draw("same");
   MCFitDown.Draw("same");
   */
   
   AddCMSPreliminary(0.1, 0.92, 4700);

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


