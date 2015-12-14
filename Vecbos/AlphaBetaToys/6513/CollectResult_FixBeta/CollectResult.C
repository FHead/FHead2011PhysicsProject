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

void CollectResult(string FixBetaFileName, string UnconstrainedFileName, string OutputFileName = "Result.root",
   int RunStart = 0, int RunEnd = 137);

void CollectResult(string FixBetaFileName, string UnconstrainedFileName, string OutputFileName,
   int RunStart, int RunEnd)
{
   // PsFileHelper PsFile("FourJetBin.ps");
   // PsFile.AddTextPage("Four jet bin?");

   TH1D FifthBinPrediction("FifthBinPrediction", "Prediction from constrained fit;Count", 100, 0, 50);
   TH1D FifthBinExtraction("FifthBinExtraction", "Extraction from unconstrained fit;Count", 100, 0, 50);
   TH1D Difference("Difference", "Prediction - Extraction;Difference", 100, -50, 50);
   TH1D DifferencePull("DifferencePull", "(Prediction - Extraction) / Error;Pull", 100, -4, 4);
   TH1D DifferencePull2("DifferencePull2", "(Prediction - Extraction) / PredictionError;Pull", 100, -4, 4);

   TFile *FFixBeta = new TFile(FixBetaFileName.c_str());
   TFile *FUnconstrained = new TFile(UnconstrainedFileName.c_str());

   int ToyCount = 0;

   for(int Run = RunStart; Run <= RunEnd; Run++)
   {
      RooFitResult *FixBetaResult = (RooFitResult *)FFixBeta->Get(Form("Result%d", Run));
      RooFitResult *UnconstrainedResult = (RooFitResult *)FUnconstrained->Get(Form("Result%d", Run));

      if(FixBetaResult == NULL || UnconstrainedResult == NULL)
         continue;
      if(FixBetaResult->covQual() != 3 || UnconstrainedResult->covQual() != 3)   // covariance matrix not OK
         continue;

      double Alpha = ((RooRealVar *)(FixBetaResult->floatParsFinal().find("Alpha")))->getVal();
      double AlphaError = ((RooRealVar *)(FixBetaResult->floatParsFinal().find("Alpha")))->getError();
      double InclusiveYield = ((RooRealVar *)(FixBetaResult->floatParsFinal().find("SignalInclusiveYield")))->getVal();
      double InclusiveError =
         ((RooRealVar *)(FixBetaResult->floatParsFinal().find("SignalInclusiveYield")))->getError();
      double Correlation = FixBetaResult->correlation("SignalInclusiveYield", "Alpha");
      // cout << "Correlation between alpha and yield = " << Correlation << endl;

      double Prediction = InclusiveYield / Alpha / Alpha / Alpha / Alpha;
      double Error2OnPrediction = (InclusiveError / Alpha / Alpha / Alpha / Alpha)
         * (InclusiveError / Alpha / Alpha / Alpha / Alpha)
         + (4 * AlphaError * InclusiveYield / Alpha / Alpha / Alpha / Alpha / Alpha)
         * (4 * AlphaError * InclusiveYield / Alpha / Alpha / Alpha / Alpha / Alpha);

      double ExtractedYield =
         ((RooRealVar *)(UnconstrainedResult->floatParsFinal().find("SignalInclusiveYield5Jet")))->getVal();
      double ExtractedError =
         ((RooRealVar *)(UnconstrainedResult->floatParsFinal().find("SignalInclusiveYield5Jet")))->getError();

      FifthBinPrediction.Fill(Prediction);
      FifthBinExtraction.Fill(ExtractedYield);
      Difference.Fill(Prediction - ExtractedYield);
      DifferencePull.Fill((Prediction - ExtractedYield) / sqrt(Error2OnPrediction + ExtractedError * ExtractedError));
      DifferencePull2.Fill((Prediction - ExtractedYield) / sqrt(Error2OnPrediction));

      ToyCount = ToyCount + 1;
   }

   cout << endl;
   cout << "Number of toys so far: " << ToyCount << endl;
   cout << endl;

   FUnconstrained->Close();
   delete FUnconstrained;

   FFixBeta->Close();
   delete FFixBeta;

   TFile F(OutputFileName.c_str(), "RECREATE");

   FifthBinPrediction.Clone("HFifthBinPrediction")->Write();
   FifthBinExtraction.Clone("HFifthBinExtraction")->Write();
   Difference.Clone("HDifference")->Write();
   DifferencePull.Clone("HDifferencePull")->Write();
   DifferencePull2.Clone("HDifferencePull2")->Write();

   F.Close();

   // PsFile.AddPlot(FifthBinPrediction);

   // PsFile.AddTimeStampPage();
   // PsFile.Close();
}

