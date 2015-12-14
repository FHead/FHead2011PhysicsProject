#include <iostream>
#include <fstream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "PlotHelper2.h"

int main(int argc, char *argv[])
{
   string Tag = "20";
   if(argc >= 2)
      Tag = argv[1];

   TH1D HMean(Form("HMean_%s", Tag.c_str()), "Mean value (pass percentage) of the bins", 100, -0.1, 1.1);
   TH1D HRMS(Form("HRMS_%s", Tag.c_str()), "RMS  on the pass percentage of the bins", 100, 0, 0.3);
   TH2D HMeanVsRMS(Form("HMeanVsRMS_%s", Tag.c_str()), "Mean vs. RMS;Mean;RMS", 100, -0.1, 1.1, 100, 0, 0.3);
   TProfile PMeanVsRMS(Form("PMeanVsRMS_%s", Tag.c_str()), "Mean vs. RMS;Mean;RMS", 100, -0.1, 1.1);

   ifstream RMSFile(("RMS_" + Tag).c_str());
   ifstream MeanFile(("Mean_" + Tag).c_str());

   while(RMSFile)
   {
      double RMS = -100, Mean = -100;

      MeanFile >> Mean;
      RMSFile >> RMS;

      if(RMS < 0 || Mean < -50)
         continue;
      if(RMS < 0.0001)
         continue;

      HMean.Fill(Mean);
      HRMS.Fill(RMS);
      HMeanVsRMS.Fill(Mean, RMS);
      PMeanVsRMS.Fill(Mean, RMS);
   }

   MeanFile.close();
   RMSFile.close();

   PsFileHelper PsFile("ResultMeanRMS_" + Tag + ".ps");
   PsFile.AddTextPage("Mean vs. RMS for each bin - " + Tag + " tries");

   PsFile.AddPlot(HMean, "", true, false, true);
   PsFile.AddPlot(HRMS, "", true, false, true);
   PsFile.AddPlot(HMeanVsRMS, "colz", false, false, true);

   TCanvas C;
   C.SetTheta(55.74153);
   C.SetPhi(143.7931);
   C.SetLogz();
   HMeanVsRMS.Draw("surf2z");
   PsFile.AddCanvas(C);
   
   PsFile.AddPlot(PMeanVsRMS, "", false, false, true);
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   int Bin = PMeanVsRMS.GetMaximumBin();
   cout << "Maximum RMS bin = " << Bin << endl;
   cout << "   with bin center " << PMeanVsRMS.GetBinCenter(Bin)
      << " and value " << PMeanVsRMS.GetBinContent(Bin) << endl;

   return 0;
}







