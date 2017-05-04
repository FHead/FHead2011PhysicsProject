#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraph.h"

#include "DataHelper.h"
#include "PlotHelper3.h"

int main(int argc, char *argv[]);
double PresampleFactor(double PT);

int main(int argc, char *argv[])
{
   string Tag = "";

   if(argc > 2)
   {
      cerr << "Usage: " << argv[0] << " Tag" << endl;
      return -1;
   }

   if(argc == 2)
      Tag = argv[1];
   else
      Tag = "";

   string FileName = "SimpleFitParameters" + Tag + ".dh";
   DataHelper DHFile(FileName);

   PdfFileHelper PdfFile("ResultSamplingCheck" + Tag + ".pdf");
   PdfFile.AddTextPage(Tag);

   double EtaMin[] = {0.0, 0.5, 0.9};
   double EtaMax[] = {0.5, 0.9, 1.3};
   double RhoMin[] = {0, 50, 100, 150, 200, 250};
   double RhoMax[] = {50, 100, 150, 200, 250, 350};

   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 6; j++)
      {
         string State = Form("SimpleFit_%.2f_%.2f_%.0f_%.0f", EtaMin[i], EtaMax[i], RhoMin[j], RhoMax[j]);

         PdfFile.AddTextPage(State);

         double P1 = DHFile[State]["P1"].GetDouble();
         double P2 = DHFile[State]["P2"].GetDouble();
         double P3 = DHFile[State]["P3"].GetDouble();
         double P4 = DHFile[State]["P4"].GetDouble();
         double P5 = DHFile[State]["P5"].GetDouble();
         double P6 = DHFile[State]["P6"].GetDouble();
         double P7 = DHFile[State]["P7"].GetDouble();
         double P8 = DHFile[State]["P8"].GetDouble();
         double P9 = DHFile[State]["P9"].GetDouble();

         TH1D HSpectrum("HSpectrum", ";PT;Spectrum", 1000, 0, 20);
         TH1D HSpectrumPresample("HSpectrumPresample", ";PT;Spectrum with presample", 1000, 0, 20);

         HSpectrum.SetStats(0);
         HSpectrumPresample.SetStats(0);

         for(int k = 1; k <= 1000; k++)
         {
            double PT = HSpectrum.GetBinCenter(k);
         
            double Value = max(tanh(P1 * (PT - P2)), 0.0)
               * (exp(-P3 * PT) + P4 * exp(-P5 * PT) + P6 * exp(-P7 * PT) + P8 * exp(-P9 * PT));

            HSpectrum.SetBinContent(k, Value);
            HSpectrumPresample.SetBinContent(k, Value / PresampleFactor(PT));
         }

         PdfFile.AddPlot(HSpectrum);
         // PdfFile.AddPlot(HSpectrumPresample);

         double M1 = HSpectrum.GetBinContent(HSpectrum.FindBin(2)) / PresampleFactor(2);
         double M2 = HSpectrum.GetBinContent(HSpectrum.FindBin(3)) / PresampleFactor(3);
         double M3 = HSpectrum.GetBinContent(HSpectrum.FindBin(4)) / PresampleFactor(4);
         double Max = max(M1, max(M2, M3)) * 1.2;

         HSpectrumPresample.SetMaximum(max(Max, HSpectrumPresample.GetMaximum()) * 1.1);

         TGraph Graph;
         Graph.SetPoint(0, 0, Max);
         Graph.SetPoint(1, 20, Max);

         TCanvas C;

         HSpectrumPresample.Draw();
         Graph.Draw("l");

         PdfFile.AddCanvas(C);
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double PresampleFactor(double PT)
{
   return exp(-1.92 * PT) + 0.005 * exp(-0.44 * PT);
}




