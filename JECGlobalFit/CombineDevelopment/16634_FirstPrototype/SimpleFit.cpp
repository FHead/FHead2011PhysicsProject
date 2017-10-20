#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main()
{
   SetThesisStyle();

   int N = 8;
   int PT[] = {50, 75, 100, 120, 140, 160, 180, 200};

   TGraphErrors GData, GMC, GRatio;

   GData.SetTitle("Data");
   GMC.SetTitle("MC");

   TFile File("ToyInput.root");

   for(int i = 0; i < N; i++)
   {
      TH1D *H = (TH1D *)File.Get(Form("MethodT_%d_0_Data", PT[i]));
      TF1 Fit("Fit", "gaus");
      H->Fit(&Fit);
      GData.SetPoint(i, PT[i], Fit.GetParameter(1));
      GData.SetPointError(i, 0, Fit.GetParError(1));
   }
   for(int i = 0; i < N; i++)
   {
      TH1D *H = (TH1D *)File.Get(Form("MethodT_%d_0_MC", PT[i]));
      TF1 Fit("Fit", "gaus");
      H->Fit(&Fit);
      GMC.SetPoint(i, PT[i], Fit.GetParameter(1));
      GMC.SetPointError(i, 0, Fit.GetParError(1));
   }
   for(int i = 0; i < N; i++)
   {
      double x, y1, y2, ey1, ey2;
      GData.GetPoint(i, x, y1);
      GMC.GetPoint(i, x, y2);
      ey1 = GData.GetErrorY(i);
      ey2 = GMC.GetErrorY(i);

      double r = y1 / y2;
      double er = r * sqrt(ey1 * ey1 / y1 / y1 + ey2 * ey2 / y2 / y2);

      GRatio.SetPoint(i, x, r);
      GRatio.SetPointError(i, 0, er);
   }

   GRatio.Fit("pol2");

   File.Close();

   PdfFileHelper PdfFile("SimpleFit.pdf");
   PdfFile.AddTextPage("Test test test");

   PdfFile.AddPlot(GData, "ap");
   PdfFile.AddPlot(GMC, "ap");

   TF1 Fit("yay", "pol2", 40, 220);
   Fit.SetParameters(1.1262, -1.6117e-3, 2.5503e-6);
   Fit.SetLineColor(kBlue);

   TF1 Dummy("Dummy", "pol1", 40, 220);
   
   TCanvas C;

   GRatio.Draw("ap");
   Fit.Draw("same");

   GRatio.GetXaxis()->SetTitle("Jet P_{T}");
   GRatio.GetYaxis()->SetTitle("Data / MC");

   TLegend Legend(0.15, 0.15, 0.45, 0.45);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&GRatio, "Ratio", "pl");
   Legend.AddEntry(&Dummy, "Simple pol2", "l");
   Legend.AddEntry(&Fit, "From combine", "l");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}









