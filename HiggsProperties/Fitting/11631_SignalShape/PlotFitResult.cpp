#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TF1.h"
#include "TGraphErrors.h"

#include "PlotHelper2.h"

struct Result;
int main();

struct Result
{
   double Mass;
   double M0, M0Error;
   double Sigma, SigmaError;
   double AlphaL, AlphaLError;
   double AlphaR, AlphaRError;
   double NL, NLError;
   double NR, NRError;
};

int main()
{
   vector<Result> Results;

   ifstream in("ProcessedFitResult.txt");

   while(in)
   {
      Result NewResult;

      in >> NewResult.Mass;
      in >> NewResult.M0 >> NewResult.M0Error;
      in >> NewResult.Sigma >> NewResult.SigmaError;
      in >> NewResult.AlphaL >> NewResult.AlphaLError;
      in >> NewResult.AlphaR >> NewResult.AlphaRError;
      in >> NewResult.NL >> NewResult.NLError;
      in >> NewResult.NR >> NewResult.NRError;

      if(NewResult.Mass > 0 && NewResult.NR > 0)
         Results.push_back(NewResult);
   }

   in.close();

   TFile File("FitResultFile.root", "RECREATE");

   TGraphErrors M0, Sigma, AlphaL, AlphaR, NL, NR;
   M0.SetNameTitle("M0", "M0");
   Sigma.SetNameTitle("Sigma", "Sigma");
   AlphaL.SetNameTitle("AlphaL", "AlphaL");
   AlphaR.SetNameTitle("AlphaR", "AlphaR");
   NL.SetNameTitle("NL", "NL");
   NR.SetNameTitle("NR", "NR");

   M0.SetMarkerStyle(20);
   Sigma.SetMarkerStyle(20);
   AlphaL.SetMarkerStyle(20);
   AlphaR.SetMarkerStyle(20);
   NL.SetMarkerStyle(20);
   NR.SetMarkerStyle(20);

   for(int i = 0; i < (int)Results.size(); i++)
   {
      if(Results[i].Mass > 190)
         continue;

      M0.SetPoint(i, Results[i].Mass, Results[i].M0);
      M0.SetPointError(i, 0, Results[i].M0Error);
      Sigma.SetPoint(i, Results[i].Mass, Results[i].Sigma);
      Sigma.SetPointError(i, 0, Results[i].SigmaError);
      AlphaL.SetPoint(i, Results[i].Mass, Results[i].AlphaL);
      AlphaL.SetPointError(i, 0, Results[i].AlphaLError);
      AlphaR.SetPoint(i, Results[i].Mass, Results[i].AlphaR);
      AlphaR.SetPointError(i, 0, Results[i].AlphaRError);
      NL.SetPoint(i, Results[i].Mass, Results[i].NL);
      NL.SetPointError(i, 0, Results[i].NLError);
      NR.SetPoint(i, Results[i].Mass, Results[i].NR);
      NR.SetPointError(i, 0, Results[i].NRError);
   }

   TF1 FM0("M0", "pol4", 100, 190);
   M0.Fit(&FM0, "R");
   TF1 FSigma("Sigma", "pol4", 100, 190);
   Sigma.Fit(&FSigma, "R");
   TF1 FAlphaL("AlphaL", "pol4", 100, 190);
   AlphaL.Fit(&FAlphaL, "R");
   TF1 FAlphaR("AlphaR", "pol4", 100, 190);
   AlphaR.Fit(&FAlphaR, "R");
   TF1 FNL("NL", "pol4", 100, 190);
   NL.Fit(&FNL, "R");
   TF1 FNR("NR", "pol4", 100, 190);
   NR.Fit(&FNR, "R");

   PsFileHelper PsFile("SummaryOfResult.ps");
   PsFile.AddTextPage("Summary of fit results");
   
   PsFile.AddPlot(M0, "ap");
   PsFile.AddPlot(Sigma, "ap");
   PsFile.AddPlot(AlphaL, "ap");
   PsFile.AddPlot(AlphaR, "ap");
   PsFile.AddPlot(NL, "ap");
   PsFile.AddPlot(NR, "ap");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   M0.Write();
   Sigma.Write();
   AlphaL.Write();
   AlphaR.Write();
   NL.Write();
   NR.Write();

   File.Close();

   return 0;
}







