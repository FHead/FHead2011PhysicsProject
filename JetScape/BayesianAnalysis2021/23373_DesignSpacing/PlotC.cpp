#include <vector>
#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
void SavePlot(TH1 &H, string Option = "");

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   PdfFileHelper PdfFile("ParametersC1C2C3.pdf");
   PdfFile.AddTextPage("C1 & C2");

   vector<double> LogTerms{5, 10, 15, 20, 25};
   double LogTerm0 = 4.605;

   for(double LogTerm : LogTerms)
   {
      TH2D H("H", Form("log term = %.2f;c_{1};c_{2}", LogTerm), 500, 0, 10, 500, 0, 10);
      H.SetStats(0);

      for(int iX = 1; iX <= H.GetNbinsX(); iX++)
      {
         for(int iY = 1; iY <= H.GetNbinsY(); iY++)
         {
            double X = H.GetXaxis()->GetBinCenter(iX);
            double Y = H.GetYaxis()->GetBinCenter(iY);

            H.SetBinContent(iX, iY, (1 + X * LogTerm0 + Y * LogTerm0 * LogTerm0) / (1 + X * LogTerm + Y * LogTerm * LogTerm));
         }
      }

      PdfFile.AddPlot(H, "colz");
      SavePlot(H, "colz");
      
      TH2D HLog("HLog", Form("log term = %.2f;ln(c_{1});ln(c_{2})", LogTerm), 500, -5, log(10), 500, -5, log(10));
      HLog.SetStats(0);

      for(int iX = 1; iX <= HLog.GetNbinsX(); iX++)
      {
         for(int iY = 1; iY <= HLog.GetNbinsY(); iY++)
         {
            double X = HLog.GetXaxis()->GetBinCenter(iX);
            double Y = HLog.GetYaxis()->GetBinCenter(iY);

            HLog.SetBinContent(iX, iY, (1 + exp(X) * LogTerm0 + exp(Y) * LogTerm0) / (1 + exp(X) * LogTerm + exp(Y) * LogTerm * LogTerm));
         }
      }

      PdfFile.AddPlot(HLog, "colz");
      SavePlot(HLog, "colz");
   }

   PdfFile.AddTextPage("C3");

   vector<double> XBs{0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
   double XB0 = 0.04;

   for(double XB : XBs)
   {
      TH1D H("H", Form("X_{B} = %.2f;c_{3}", XB), 1000, 0, 100);
      H.SetStats(0);

      for(int i = 1; i <= H.GetNbinsX(); i++)
      {
         double X = H.GetBinCenter(i);
         H.SetBinContent(i, ((exp(X * (1 - XB)) - 1) / (exp(X * (1 - XB0)) - 1)));
      }

      PdfFile.AddPlot(H);
      SavePlot(H);
      
      TH1D HLog("HLog", Form("X_{B} = %.2f;ln(c_{3})", XB), 1000, -5, log(100));
      HLog.SetStats(0);
      
      for(int i = 1; i <= HLog.GetNbinsX(); i++)
      {
         double X = HLog.GetBinCenter(i);
         HLog.SetBinContent(i, ((exp(exp(X) * (1 - XB)) - 1) / (exp(exp(X) * (1 - XB0)) - 1)));
      }

      PdfFile.AddPlot(HLog);
      SavePlot(HLog);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void SavePlot(TH1 &H, string Option)
{
   static int Index = 0;
   Index = Index + 1;

   TCanvas Canvas;

   H.Draw(Option.c_str());

   Canvas.SaveAs(Form("Plots/Parameters%d.png", Index));
}


