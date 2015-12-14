#include <string>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"

#include "RooFitResult.h"
#include "RooRealVar.h"
using namespace RooFit;

#include "PlotHelper.h"

void CollectResult(string FileName, double AlphaCentralValue, double BetaCentralValue,
   int RunStart = 0, int RunEnd = 137);

void CollectResult(string FileName, double AlphaCentralValue, double BetaCentralValue, int RunStart, int RunEnd)
{
   TH1D AlphaPull("AlphaPull", "Alpha parameter pull distribution;Pull", 25, -5, 5);
   TH1D BetaPull("BetaPull", "Beta parameter pull distribution;Pull", 25, -5, 5);
   TH1D Alpha("Alpha", "Alpha parameter distribution;Alpha", 25, 2, 8);
   TH1D Beta("Beta", "Beta parameter distribution;Beta", 25, -3, 3);
   TH1D AlphaError("AlphaError", "Alpha parameter error distribution;Alpha error", 25, 0, 2);
   TH1D BetaError("BetaError", "Beta parameter error distribution;Beta error", 25, 0, 2);

   PsFileHelper PsFile("PullDistribution.ps");
   PsFile.AddTextPage("Pull distributions of alpha and beta");

   TFile F(FileName.c_str());

   int ToyCount = 0;

   for(int Run = RunStart; Run <= RunEnd; Run++)
   {
      RooFitResult *Result = (RooFitResult *)F.Get(Form("FitResult%d", Run));

      if(Result == NULL)
         continue;
      if(Result->covQual() != 3)   // covariance matrix not OK
         continue;

      double alpha = ((RooRealVar *)(Result->floatParsFinal().find("Alpha")))->getVal();
      double alphaerror = ((RooRealVar *)(Result->floatParsFinal().find("Alpha")))->getError();
      double beta = ((RooRealVar *)(Result->floatParsFinal().find("Beta")))->getVal();
      double betaerror = ((RooRealVar *)(Result->floatParsFinal().find("Beta")))->getError();

      AlphaPull.Fill((alpha - AlphaCentralValue) / alphaerror);
      BetaPull.Fill((beta - BetaCentralValue) / betaerror);
      Alpha.Fill(alpha);
      AlphaError.Fill(alphaerror);
      Beta.Fill(beta);
      BetaError.Fill(betaerror);

      ToyCount = ToyCount + 1;
   }

   cout << endl;
   cout << "Number of toys so far: " << ToyCount << endl;
   cout << endl;

   Alpha.Fit("gaus");
   Beta.Fit("gaus");

   PsFile.AddPlot(Alpha);
   PsFile.AddPlot(AlphaError);
   PsFile.AddPlot(Beta);
   PsFile.AddPlot(BetaError);

   PsFileHelper PsFile2("Errors.ps");
   PsFile2.AddTextPage("Distribution of errors on alpha and beta");
   PsFile2.AddPlot(AlphaError);
   PsFile2.AddPlot(BetaError);
   PsFile2.AddTimeStampPage();
   PsFile2.Close();

   TF1 AlphaGaus("AlphaGaus", "gaus");
   TF1 BetaGaus("BetaGaus", "gaus");

   AlphaPull.Fit(&AlphaGaus);
   BetaPull.Fit(&BetaGaus);

   PsFile.AddPlot(AlphaPull, "");
   PsFile.AddPlot(BetaPull, "");

   TCanvas C("C", "C", 0, 0, 1024, 768);
   AlphaPull.Draw();
   C.SaveAs("AlphaPull.C");
   C.SaveAs("AlphaPull.eps");
   C.SaveAs("AlphaPull.png");
   
   BetaPull.Draw();
   C.SaveAs("BetaPull.C");
   C.SaveAs("BetaPull.eps");
   C.SaveAs("BetaPull.png");

   TCanvas C2("C2", "C2", 0, 0, 1024, 512);
   C2.Divide(2, 1);

   C2.cd(1);
   AlphaPull.Draw();
   
   C2.cd(2);
   BetaPull.Draw();

   C2.SaveAs("Pulls.C");
   C2.SaveAs("Pulls.eps");
   C2.SaveAs("Pulls.png");

   F.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

