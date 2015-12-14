#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TLegend.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main();
map<double, double> ReadCrossSection(string FileName = "squark_crosssection.txt");
double CrossSection(const map<double, double> &ReferencePoints, double Mass);

int main()
{
   SetStyle();

   TH2D HExpected("HExpected",
      "Expected limit;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HObserved("HObserved",
      "Observed limit;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HExpectedPlus("HExpectedPlus",
      "Expected (+1) limit;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HExpectedPlus2("HExpectedPlus2",
      "Expected (+2) limit;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HExpectedMinus("HExpectedMinus",
      "Expected (-1) limit;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HExpectedMinus2("HExpectedMinus2",
      "Expected (-2) limit;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HCrossSection("HCrossSection",
      "CrossSection;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   HCrossSection.SetStats(0);
   
   TH2D HExpectedCopy("HExpectedCopy",
      "Expected limit - cross section;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HObservedCopy("HObservedCopy",
      "Observed limit - cross section;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HExpectedPlusCopy("HExpectedPlusCopy",
      "Expected (+1) limit - cross section;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HExpectedPlus2Copy("HExpectedPlus2Copy",
      "Expected (+2) limit - cross section;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HExpectedMinusCopy("HExpectedMinusCopy",
      "Expected (-1) limit - cross section;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HExpectedMinus2Copy("HExpectedMinus2Copy",
      "Expected (-2) limit - cross section;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);

   TH2D HWorld("HWorld", "Limit curves;Sbottom;Neutralino;#sigma (pb)", 50, 0, 600, 50, 0, 600);
   HWorld.SetStats(0);

   map<double, double> Sigma = ReadCrossSection("squark_crosssection.txt");

   TH1D HReferenceSigma("HReferenceSigma", "Reference cross section;Squark mass;Sigma", 1000, 0, 1000);
   for(int i = 1; i <= 1000; i++)
      HReferenceSigma.SetBinContent(i, CrossSection(Sigma, i));
   for(int i = 1; i <= 50; i++)
      for(int j = 1; j <= 50; j++)
         if(i >= j)
            HCrossSection.SetBinContent(i, j, CrossSection(Sigma, HCrossSection.GetXaxis()->GetBinCenter(i)));
   HCrossSection.SetMinimum(0.001);

   ifstream in("Result.txt");

   while(in)
   {
      double m0 = 0;
      double m12 = 0;
      double obs = 0;
      double exp = 0;
      double up = 0;
      double down = 0;
      double upup = 0;
      double downdown = 0;

      in >> m0 >> m12 >> obs >> exp >> up >> down >> upup >> downdown;

      if(m0 == 0)
         continue;

      HExpected.Fill(m0, m12, exp);
      HObserved.Fill(m0, m12, obs);
      HExpectedPlus.Fill(m0, m12, up);
      HExpectedPlus2.Fill(m0, m12, upup);
      HExpectedMinus.Fill(m0, m12, down);
      HExpectedMinus2.Fill(m0, m12, downdown);

      HExpectedCopy.Fill(m0, m12, exp - CrossSection(Sigma, m0));
      HObservedCopy.Fill(m0, m12, obs - CrossSection(Sigma, m0));
      HExpectedPlusCopy.Fill(m0, m12, up - CrossSection(Sigma, m0));
      HExpectedPlus2Copy.Fill(m0, m12, upup - CrossSection(Sigma, m0));
      HExpectedMinusCopy.Fill(m0, m12, down - CrossSection(Sigma, m0));
      HExpectedMinus2Copy.Fill(m0, m12, downdown - CrossSection(Sigma, m0));
   }

   in.close();

   HExpected.SetStats(0);
   HObserved.SetStats(0);
   HExpectedPlus.SetStats(0);
   HExpectedPlus2.SetStats(0);
   HExpectedMinus.SetStats(0);
   HExpectedMinus2.SetStats(0);
   HExpectedCopy.SetStats(0);
   HObservedCopy.SetStats(0);
   HExpectedPlusCopy.SetStats(0);
   HExpectedPlus2Copy.SetStats(0);
   HExpectedMinusCopy.SetStats(0);
   HExpectedMinus2Copy.SetStats(0);

   HExpected.GetZaxis()->SetTitleOffset(0.5);
   HObserved.GetZaxis()->SetTitleOffset(0.5);
   HExpectedPlus.GetZaxis()->SetTitleOffset(0.5);
   HExpectedPlus2.GetZaxis()->SetTitleOffset(0.5);
   HExpectedMinus.GetZaxis()->SetTitleOffset(0.5);
   HExpectedMinus2.GetZaxis()->SetTitleOffset(0.5);
   HExpectedCopy.GetZaxis()->SetTitleOffset(0.5);
   HObservedCopy.GetZaxis()->SetTitleOffset(0.5);
   HExpectedPlusCopy.GetZaxis()->SetTitleOffset(0.5);
   HExpectedPlus2Copy.GetZaxis()->SetTitleOffset(0.5);
   HExpectedMinusCopy.GetZaxis()->SetTitleOffset(0.5);
   HExpectedMinus2Copy.GetZaxis()->SetTitleOffset(0.5);

   PsFileHelper PsFile("Limits.ps");
   PsFile.AddTextPage("Limits!");

   vector<string> Explanation;
   Explanation.push_back("Preliminary limit plots for T2bb simplified model");
   Explanation.push_back("");
   Explanation.push_back("R^{2} > 0.25, M_{R} > 400 are used from LQ3 1.7/fb result");
   Explanation.push_back("Expected, +-1 sigma, +-2 sigma, and observed limits are plotted");
   Explanation.push_back("The color represent limit on cross section - everything above is excluded");
   Explanation.push_back("Each plot comes with both linear-color and log-color scale for convenience");
   Explanation.push_back("Signal efficiency uncertainty copied procedure from LQ analysis");
   Explanation.push_back("\"m_{sb}\" is the sbottom mass, \"m_{#chi}\" is the (first) neutralino mass");
   Explanation.push_back("");
   Explanation.push_back("CLs method used, with 1000 toys.  10000-toy version is crashing...");
   Explanation.push_back("It's with tag V01-00-19, as per email sent out by Gena Kukartsev on Jan. 22");
   Explanation.push_back("");
   PsFile.AddTextPage(Explanation);

   PsFile.AddPlot(HExpected, "colz", false, false);
   PsFile.AddPlot(HExpected, "colz", false, true);
   PsFile.AddPlot(HExpectedPlus, "colz", false, false);
   PsFile.AddPlot(HExpectedPlus, "colz", false, true);
   PsFile.AddPlot(HExpectedMinus, "colz", false, false);
   PsFile.AddPlot(HExpectedMinus, "colz", false, true);
   PsFile.AddPlot(HExpectedPlus2, "colz", false, false);
   PsFile.AddPlot(HExpectedPlus2, "colz", false, true);
   PsFile.AddPlot(HExpectedMinus2, "colz", false, false);
   PsFile.AddPlot(HExpectedMinus2, "colz", false, true);
   PsFile.AddPlot(HObserved, "colz", false, false);
   PsFile.AddPlot(HObserved, "colz", false, true);

   PsFile.AddTextPage("Now the limit interpretation part!");
   PsFile.AddPlot(HReferenceSigma, "", true);
   PsFile.AddPlot(HCrossSection, "colz", false, true);

   // PsFile.AddPlot(HExpectedCopy, "colz", false, false);
   
   TCanvas C("C", "C");

   HWorld.Draw();

   double Contours[1] = {0};
   
   HExpectedCopy.SetContour(1, Contours);
   HExpectedPlusCopy.SetContour(1, Contours);
   HExpectedMinusCopy.SetContour(1, Contours);
   HObservedCopy.SetContour(1, Contours);

   HExpectedCopy.Draw("cont3 same");
   HExpectedPlusCopy.Draw("cont3 same");
   HExpectedMinusCopy.Draw("cont3 same");
   HObservedCopy.Draw("cont3 same");

   HExpectedCopy.SetLineWidth(2);
   HExpectedPlusCopy.SetLineWidth(2);
   HExpectedMinusCopy.SetLineWidth(2);
   HObservedCopy.SetLineWidth(2);

   HExpectedCopy.SetLineColor(kBlue);
   HExpectedPlusCopy.SetLineColor(kBlue);
   HExpectedMinusCopy.SetLineColor(kBlue);
   HObservedCopy.SetLineColor(kGreen - 3);

   TGraph ForbiddenGraph;
   ForbiddenGraph.SetLineColor(kBlack);
   ForbiddenGraph.SetLineStyle(7);
   ForbiddenGraph.SetPoint(0, 0, 0);
   ForbiddenGraph.SetPoint(1, 1200, 1200);
   ForbiddenGraph.Draw("l");

   TLegend Legend(0.15, 0.55, 0.55, 0.85);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&HObservedCopy, "Observed Limit", "l");
   Legend.AddEntry(&HExpectedCopy, "Expected Limit", "l");
   Legend.AddEntry(&HExpectedPlusCopy, "Expected Limit (+1 #sigma)", "l");
   Legend.AddEntry(&HExpectedMinusCopy, "Expected Limit (-1 #sigma)", "l");
   Legend.Draw();

   TLatex ForbiddenText;
   ForbiddenText.SetTextAngle(33);
   ForbiddenText.SetTextSize(0.02);
   ForbiddenText.DrawLatex(100, 125, "Decay forbidden");

   PsFile.AddCanvas(C);

   PsFile.AddTimeStampPage();
   PsFile.Close();
   
   TCanvas C2("C2", "C2", 1024, 1024);
   HReferenceSigma.SetStats(0);
   HReferenceSigma.Draw();
   C2.SetLogy();
   C2.SaveAs("ReferenceSigma.png");
   C2.SaveAs("ReferenceSigma.C");
   C2.SaveAs("ReferenceSigma.eps");
   C2.SaveAs("ReferenceSigma.pdf");
   
   C2.SetLogy(false);
   HWorld.Draw();
   HExpectedCopy.Draw("cont3 same");
   HExpectedPlusCopy.Draw("cont3 same");
   HExpectedMinusCopy.Draw("cont3 same");
   HObservedCopy.Draw("cont3 same");
   ForbiddenGraph.Draw("l");
   ForbiddenText.SetTextAngle(45);
   ForbiddenText.SetTextSize(0.02);
   ForbiddenText.DrawLatex(100, 125, "Decay forbidden");
   Legend.Draw();
   C2.SaveAs("LimitCurves.png");
   C2.SaveAs("LimitCurves.C");
   C2.SaveAs("LimitCurves.eps");
   C2.SaveAs("LimitCurves.pdf");

   return 0;
}

map<double, double> ReadCrossSection(string FileName)
{
   map<double, double> result;

   ifstream in(FileName.c_str());

   while(in)
   {
      double temp1 = -1;
      double temp2 = -1;

      in >> temp1 >> temp2;

      if(temp1 < 0 || temp2 < 0)
         continue;

      result.insert(pair<double, double>(temp1, temp2));
   }

   in.close();

   return result;
}

double CrossSection(const map<double, double> &ReferencePoints, double Mass)
{
   if(ReferencePoints.size() == 0)   // What???
      return -1;

   if(Mass < ReferencePoints.begin()->first)
      return ReferencePoints.begin()->second / 5;

   double PreviousMass = ReferencePoints.begin()->first;
   double logPreviousSigma = ReferencePoints.begin()->second;
   double NextMass = 0;
   double logNextSigma = 0;

   for(map<double, double>::const_iterator iter = ReferencePoints.begin(); iter != ReferencePoints.end(); iter++)
   {
      if(Mass < iter->first)
      {
         NextMass = iter->first;
         logNextSigma = log(iter->second);
         break;
      }

      PreviousMass = iter->first;
      logPreviousSigma = log(iter->second);
   }

   if(NextMass > 0)
   {
      double logCrossSection = (NextMass - Mass) / (NextMass - PreviousMass) * (logPreviousSigma - logNextSigma) + logNextSigma;
      return exp(logCrossSection) / 5;
   }

   return 0;
}




