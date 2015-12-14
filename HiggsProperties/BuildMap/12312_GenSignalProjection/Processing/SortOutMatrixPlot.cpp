#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

#include "Utilities.hcpp"

int main();
void DoOneHistogram(PsFileHelper &PsFile, vector<TFile *> &Files, string Name);

int main()
{
   SetStyle();
   gStyle->SetPaintTextFormat(".2e");

   vector<TFile *> Files;
   for(int i = 300; i <= 999; i++)
      Files.push_back(new TFile(Form("Matrix%d.root", i)));

   PsFileHelper PsFile("FinalMatrixPlots.ps");
   PsFile.AddTextPage("Final matrix plots");

   PsFile.AddTextPage(Form("Final matrix plots with %.1fM events", Files.size() * 0.2));

   PsFile.AddTextPage("Loose, 2e2mu");
   DoOneHistogram(PsFile, Files, "HMatrixLoose2e2mu");
   PsFile.AddTextPage("Absolute value, loose, 2e2mu");
   DoOneHistogram(PsFile, Files, "HAbsMatrixLoose2e2mu");
   PsFile.AddTextPage("Tight, 2e2mu");
   DoOneHistogram(PsFile, Files, "HMatrixTight2e2mu");
   PsFile.AddTextPage("Absolute value, tight, 2e2mu");
   DoOneHistogram(PsFile, Files, "HAbsMatrixTight2e2mu");
   PsFile.AddTextPage("Loose, 4e");
   DoOneHistogram(PsFile, Files, "HMatrixLoose4e");
   PsFile.AddTextPage("Absolute value, loose, 4e");
   DoOneHistogram(PsFile, Files, "HAbsMatrixLoose4e");
   PsFile.AddTextPage("Tight, 4e");
   DoOneHistogram(PsFile, Files, "HMatrixTight4e");
   PsFile.AddTextPage("Absolute value, tight, 4e");
   DoOneHistogram(PsFile, Files, "HAbsMatrixTight4e");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   for(int i = 0; i < (int)Files.size(); i++)
      if(Files[i] != NULL)
         delete Files[i];
}

void DoOneHistogram(PsFileHelper &PsFile, vector<TFile *> &Files, string Name)
{
   TH2D HN0("HN0", "", 14, 0, 14, 14, 0, 14);
   TH2D HN1("HN1", "", 14, 0, 14, 14, 0, 14);
   TH2D HN2("HN2", "", 14, 0, 14, 14, 0, 14);

   for(int i = 0; i < (int)Files.size(); i++)
   {
      if(Files[i] == NULL)
         continue;

      TH1D *H = (TH1D *)Files[i]->Get(Name.c_str());
      double EntryCount = ((TH1D *)Files[i]->Get("HEntryCount"))->GetBinContent(1);

      for(int iX = 1; iX <= 14; iX++)
      {
         for(int iY = 1; iY <= 14; iY++)
         {
            double V = H->GetBinContent(iX, iY) / EntryCount;

            HN0.Fill(iX - 1, iY - 1, 1);
            HN1.Fill(iX - 1, iY - 1, V);
            HN2.Fill(iX - 1, iY - 1, V * V);
         }
      }
   }

   TH2D HAverage("HAverage", "", 14, 0, 14, 14, 0, 14);
   TH2D HAverage2("HAverage2", "", 14, 0.025, 14.025, 14, 0.025, 14.025);
   TH2D HAverage3("HAverage3", "", 14, -0.025, 13.975, 14, 0.025, 14.025);
   TH2D HAverage4("HAverage4", "", 14, 0.025, 14.025, 14, -0.025, 13.975);
   TH2D HAverage5("HAverage5", "", 14, -0.025, 13.975, 14, -0.025, 13.975);
   TH2D HError("HError", "", 14, 0, 14, 14, 0, 14);

   HAverage.SetMarkerColor(kWhite);
   HAverage2.SetMarkerColor(kBlack);
   HAverage3.SetMarkerColor(kBlack);
   HAverage4.SetMarkerColor(kBlack);
   HAverage5.SetMarkerColor(kBlack);

   PrepareHistogram(HAverage);
   PrepareHistogram(HAverage2);
   PrepareHistogram(HAverage3);
   PrepareHistogram(HAverage4);
   PrepareHistogram(HAverage5);
   PrepareHistogram(HError);

   double Minimum = 0;

   for(int iX = 1; iX <= 14; iX++)
   {
      for(int iY = 1; iY <= 14; iY++)
      {
         double N0 = HN0.GetBinContent(iX, iY);
         double N1 = HN1.GetBinContent(iX, iY);
         double N2 = HN2.GetBinContent(iX, iY);

         // cout << iX << " " << iY << " " << N0 << " " << N1 << " " << N2 << " " << endl;

         HAverage.SetBinContent(iX, iY, N1 / N0);
         HAverage2.SetBinContent(iX, iY, N1 / N0);
         HAverage3.SetBinContent(iX, iY, N1 / N0);
         HAverage4.SetBinContent(iX, iY, N1 / N0);
         HAverage5.SetBinContent(iX, iY, N1 / N0);
         if(fabs(N1) > 1e-60)
            HError.SetBinContent(iX, iY, sqrt((N2 - N1 * N1 / N0) / (N0 - 1)) / sqrt(N0) / fabs(N1 / N0));

         if(fabs(N1 / N0) > 1e-40)
         {
            if(N1 / N0 < Minimum)
               Minimum = N1 / N0;
         }
      }
   }

   double ScaleFactor = 1 / HAverage.GetBinContent(1, 1) / 4;
   HAverage.Scale(ScaleFactor);
   HAverage2.Scale(ScaleFactor);
   HAverage3.Scale(ScaleFactor);
   HAverage4.Scale(ScaleFactor);
   HAverage5.Scale(ScaleFactor);

   HError.SetMaximum(1);
   HError.SetMinimum(0.01);

   PsFile.AddPlot(HAverage, "colz text15", false, false);
   PsFile.AddPlot(HAverage, "colz text15", false, true);

   TCanvas C;
   HAverage2.Draw("colz text15");
   HAverage3.Draw("text15 same");
   HAverage4.Draw("text15 same");
   HAverage5.Draw("text15 same");
   HAverage.Draw("text15 same");
   C.SetLogz();
   PsFile.AddCanvas(C);

   PsFile.AddPlot(HError, "colz text00", false, true);
}




