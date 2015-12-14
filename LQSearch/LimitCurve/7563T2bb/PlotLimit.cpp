#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

#include "TFile.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main()
{
   SetStyle();

   TFile F("Histograms.root", "RECREATE");

   TH2D HExpected("HExpected", "Expected limit;sbottom;neutralino;#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HObserved("HObserved", "Observed limit;sbottom;neutralino;#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HExpectedPlus("HExpectedPlus", "Expected (+1) limit;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HExpectedPlus2("HExpectedPlus2", "Expected (+2) limit;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HExpectedMinus("HExpectedMinus", "Expected (-1) limit;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);
   TH2D HExpectedMinus2("HExpectedMinus2", "Expected (-2) limit;m_{sb};m_{#chi};#sigma (pb)", 50, -12.5, 1237.5, 50, -12.5, 1237.5);

   TH1D HExpectedNeutralino50("HExpectedNeutralino50",
      "Expected limit, neutralino mass = 50 GeV;Sbottom mass;#sigma (pb)", 50, -12.5, 1237.5);
   TH1D HExpectedNeutralino75("HExpectedNeutralino75",
      "Expected limit, neutralino mass = 75 GeV;Sbottom mass;#sigma (pb)", 50, -12.5, 1237.5);
   TH1D HExpectedNeutralino100("HExpectedNeutralino100",
      "Expected limit, neutralino mass = 100 GeV;Sbottom mass;#sigma (pb)", 50, -12.5, 1237.5);

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

      if(m12 == 50)   // bad practice
         HExpectedNeutralino50.Fill(m0, exp);
      if(m12 == 75)
         HExpectedNeutralino75.Fill(m0, exp);
      if(m12 == 100)
         HExpectedNeutralino100.Fill(m0, exp);
   }

   in.close();

   HExpected.SetStats(0);
   HObserved.SetStats(0);
   HExpectedPlus.SetStats(0);
   HExpectedPlus2.SetStats(0);
   HExpectedMinus.SetStats(0);
   HExpectedMinus2.SetStats(0);

   HExpected.GetZaxis()->SetTitleOffset(0.5);
   HObserved.GetZaxis()->SetTitleOffset(0.5);
   HExpectedPlus.GetZaxis()->SetTitleOffset(0.5);
   HExpectedPlus2.GetZaxis()->SetTitleOffset(0.5);
   HExpectedMinus.GetZaxis()->SetTitleOffset(0.5);
   HExpectedMinus2.GetZaxis()->SetTitleOffset(0.5);

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
   Explanation.push_back("CLs method used, with 1000 toys.  10000-toy version is running on batch now,");
   Explanation.push_back("      and I expect it to finish in O(2 days).");
   Explanation.push_back("It's with tag V01-00-19, as per email sent out by Gena Kukartsev on Jan. 22");
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

   TCanvas C("C", "C", 1024, 1024);

   HExpected.Draw("colz");

   C.SetLogz();
   C.SaveAs("ExpectedCrossSection.png");
   C.SaveAs("ExpectedCrossSection.C");
   C.SaveAs("ExpectedCrossSection.eps");
   C.SaveAs("ExpectedCrossSection.pdf");

   HObserved.Draw("colz");

   C.SaveAs("ObservedCrossSection.png");
   C.SaveAs("ObservedCrossSection.C");
   C.SaveAs("ObservedCrossSection.eps");
   C.SaveAs("ObservedCrossSection.pdf");

   PsFile.AddPlot(HExpectedNeutralino50, "", true);
   PsFile.AddPlot(HExpectedNeutralino75, "", true);
   PsFile.AddPlot(HExpectedNeutralino100, "", true);

   HExpectedNeutralino50.Write();
   HExpectedNeutralino75.Write();
   HExpectedNeutralino100.Write();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();

   return 0;
}





