#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"

#include "PlotHelper2.h"

int main()
{
   TFile File("AllResults.root");

   TGraphErrors Graph2, Graph5, Graph10, Graph20, Graph25;

   for(int iS = 1; iS <= 100; iS++)
   {
      TH1D *H = (TH1D *)File.Get(Form("HBestFitPosition_%d_2", iS));

      double Mean = H->GetMean() * (iS + 2);
      double Error = H->GetRMS() * (iS + 2);

      Graph2.SetPoint(iS, iS, Mean);
      Graph2.SetPointError(iS, 0, Error);

      H = (TH1D *)File.Get(Form("HBestFitPosition_%d_5", iS));

      Mean = H->GetMean() * (iS + 5);
      Error = H->GetRMS() * (iS + 5);

      Graph5.SetPoint(iS, iS, Mean);
      Graph5.SetPointError(iS, 0, Error);
      
      H = (TH1D *)File.Get(Form("HBestFitPosition_%d_10", iS));

      Mean = H->GetMean() * (iS + 10);
      Error = H->GetRMS() * (iS + 10);

      Graph10.SetPoint(iS, iS, Mean);
      Graph10.SetPointError(iS, 0, Error);
      
      H = (TH1D *)File.Get(Form("HBestFitPosition_%d_20", iS));

      Mean = H->GetMean() * (iS + 20);
      Error = H->GetRMS() * (iS + 20);

      Graph20.SetPoint(iS, iS, Mean);
      Graph20.SetPointError(iS, 0, Error);

      H = (TH1D *)File.Get(Form("HBestFitPosition_%d_25", iS));

      Mean = H->GetMean() * (iS + 25);
      Error = H->GetRMS() * (iS + 25);

      Graph25.SetPoint(iS, iS, Mean);
      Graph25.SetPointError(iS, 0, Error);
   }

   Graph2.SetMarkerStyle(11);
   Graph5.SetMarkerStyle(11);
   Graph10.SetMarkerStyle(11);
   Graph20.SetMarkerStyle(11);
   Graph25.SetMarkerStyle(11);

   PsFileHelper PsFile("SummaryPlot.ps");
   PsFile.AddTextPage("Summary plot!");

   vector<string> Explanations(12);
   Explanations[0] = "Group signal MC into groups of X events, and background MC into groups of 5 events.";
   Explanations[1] = "For each pair of groups, try to fit for the best background fraction.";
   Explanations[2] = "Collect all fractions, and translate it into background event count.";
   Explanations[3] = "Repeat exercise with different X and see if we can get out the correct number.";
   Explanations[4] = "";
   Explanations[5] = "Then repeat the whole thing with 10 background events, and then 20, 25, 2";
   Explanations[6] = "";
   Explanations[7] = "As you can see we have overall bias.  The extracted result is stable however.";
   Explanations[8] = "This could be due to the fact that I'm only using M=125 map to calculate";
   Explanations[9] = "likelihood, and the 120 < M4l < 130 cut makes things sub-optimal.";
   Explanations[10] = "In the blue shaded region, background likelihood is increased by 5% artificially";
   Explanations[11] = "to see the effect of wrong integral.";
   PsFile.AddTextPage(Explanations);

   TCanvas Canvas;

   Graph5.Draw("ap");
   Graph5.GetXaxis()->SetTitle("Number of signal events");
   Graph5.GetYaxis()->SetTitle("Mean of extracted background events");

   TGraph Line;
   Line.SetPoint(0, -1000, 5);
   Line.SetPoint(1, 1000, 5);
   Line.Draw("l");

   PsFile.AddCanvas(Canvas);

   Graph10.Draw("ap");
   Graph10.GetXaxis()->SetTitle("Number of signal events");
   Graph10.GetYaxis()->SetTitle("Mean of extracted background events");
   
   Line.SetPoint(0, -1000, 10);
   Line.SetPoint(1, 1000, 10);
   Line.Draw("l");

   PsFile.AddCanvas(Canvas);

   Graph20.Draw("ap");

   TGraph Coloring;
   Coloring.SetPoint(0, 70, -1000);
   Coloring.SetPoint(1, 80, -1000);
   Coloring.SetPoint(2, 80, 1000);
   Coloring.SetPoint(3, 5, 1000);
   Coloring.SetPoint(4, 5, -1000);
   Coloring.SetPoint(5, 10, -1000);
   Coloring.SetPoint(6, 10, 1000);
   Coloring.SetPoint(7, 70, 1000);
   Coloring.SetPoint(8, 70, -1000);
   Coloring.SetFillColor(kCyan);
   Coloring.Draw("f");

   Graph20.Draw("p");
   Graph20.GetXaxis()->SetTitle("Number of signal events");
   Graph20.GetYaxis()->SetTitle("Mean of extracted background events");
   
   Line.SetPoint(0, -1000, 20);
   Line.SetPoint(1, 1000, 20);
   Line.Draw("l");

   PsFile.AddCanvas(Canvas);

   Graph25.Draw("ap");
   Graph25.GetXaxis()->SetTitle("Number of signal events");
   Graph25.GetYaxis()->SetTitle("Mean of extracted background events");
   
   Line.SetPoint(0, -1000, 25);
   Line.SetPoint(1, 1000, 25);
   Line.Draw("l");

   PsFile.AddCanvas(Canvas);

   Graph2.Draw("ap");
   Graph2.GetXaxis()->SetTitle("Number of signal events");
   Graph2.GetYaxis()->SetTitle("Mean of extracted background events");
   
   Line.SetPoint(0, -1000, 2);
   Line.SetPoint(1, 1000, 2);
   Line.Draw("l");

   PsFile.AddCanvas(Canvas);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   File.Close();

   return 0;
}







