#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TGaxis.h"
#include "TPad.h"

#include "PlotHelper2.h"

int main()
{
   double Tries[] = {10, 20, 50, 200, 1000};
   double RMSs[] = {0.150928, 0.105914, 0.0663183, 0.0315127, 0.0129414};
   double Times[] = {3.3, 6.6, 15, 66, 310};
   
   TGraph GRMS(5, Tries, RMSs);
   GRMS.SetNameTitle("GRMS", "Precision as a function of number of tries");
   
   TGraph GTime(5, Tries, Times);
   GTime.SetNameTitle("GTime", "Time needed per job (min.)");
   
   TFile F("Plots.root", "recreate");

   PsFileHelper PsFile("TimeVsPrecision.ps");
   PsFile.AddTextPage("(Map-building) CPU time vs. bin-by-bin precision");

   vector<string> Explanations;
   Explanations.push_back("Generate 6D maps with dimension 20^{6}.");
   Explanations.push_back("The generation is splitted into 20 jobs, each running 20^{5} bins.");
   Explanations.push_back("While integrating the last angle (around Higgs) and also Higgs pt/eta,");
   Explanations.push_back("      we have the freedom to choose how many tries we want to integrate over.");
   Explanations.push_back("Since it's computationally intensive, we can not simple run thousands of tries,");
   Explanations.push_back("      and a comprimise between CPU time and precision is needed.");
   Explanations.push_back("Here I try to estimate precision by generating many maps and look at");
   Explanations.push_back("      bin-by-bin RMS.");
   Explanations.push_back("Quoted time is per job, ie., time to calculate 20^{5} bins");
   Explanations.push_back("");
   Explanations.push_back("Lepton efficiency is flat, |eta| < 2.4, PT > 10 for all of them.");
   Explanations.push_back("      In reality when we have the real lepton maps, it will take a bit longer");
   PsFile.AddTextPage(Explanations);

   TCanvas CRMS;
   GRMS.SetMarkerStyle(11);
   GRMS.Draw("ap");
   GRMS.GetXaxis()->SetTitle("Number of tries");
   GRMS.GetYaxis()->SetTitle("Absolute precision on efficiency on bins");
   PsFile.AddCanvas(CRMS);

   TCanvas CTime;
   GTime.Draw("apl");
   GTime.GetXaxis()->SetTitle("Number of tries");
   GTime.GetYaxis()->SetTitle("Time needed per job (min.)");
   PsFile.AddCanvas(CTime);

   TCanvas CSuperimpose;
   CSuperimpose.SetGridx(true);
   CSuperimpose.SetGridy(true);

   TH1F *Frame = CSuperimpose.DrawFrame(0, 0, 1050, 0.2);
   Frame->SetXTitle("Number of tries");
   Frame->SetYTitle("Absolute precision on efficiency (bin-by-bin)");
   
   GRMS.SetLineWidth(2);
   GRMS.Draw("pl");

   for(int i = 0; i < GTime.GetN(); i++)
   {
      double x, y;
      GTime.GetPoint(i, x, y);
      GTime.SetPoint(i, x, y / 350 * 0.2);
   }
   GTime.SetLineColor(kBlue);
   GTime.SetLineWidth(2);
   GTime.Draw("lp");

   TGaxis Axis(1050, 0, 1050, 0.2, 0, 350, 510, "+L");
   Axis.SetLineColor(kBlue);
   Axis.SetLabelColor(kBlue);
   Axis.SetTitle("Time needed per job (min.)");
   Axis.Draw();

   PsFile.AddCanvas(CSuperimpose);

   CSuperimpose.SaveAs("PrecisionVsTime.png");
   CSuperimpose.SaveAs("PrecisionVsTime.C");
   CSuperimpose.SaveAs("PrecisionVsTime.eps");
   CSuperimpose.SaveAs("PrecisionVsTime.pdf");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   CSuperimpose.Write();
   F.Close();

   return 0;
}





