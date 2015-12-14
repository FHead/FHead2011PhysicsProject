#include "TFile.h"
#include "TTree.h"

#include "RooGaussian.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooPlot.h"
using namespace RooFit;

#include "PlotHelper.h"

void FitPeak()
{
   RooRealVar Mass("Mass", "Dimuon invariant mass", 1000, 2000, "GeV/c^2");
   RooArgSet TreeVarSet(Mass);

   TFile F("OppositeSign.root");
   TTree *Tree = (TTree *)F.Get("Dimuon");
   RooDataSet dataset("Dataset", "Dataset", Tree, TreeVarSet);

   RooRealVar GaussianMean("GaussianMean", "GaussianMean", 1600, 1000, 2000);
   RooRealVar GaussianSigma("GaussianSigma", "Sigma", 200, 0, 1000);
   RooGaussian MainPeak("MainPeak", "MainPeak", Mass, GaussianMean, GaussianSigma);
   RooRealVar SignalYield("SignalYield", "SignalYield", 0, 0, 10000000);

   RooRealVar BackgroundExp("BackgroundExp", "BackgroundExp", -0.4, -1.5, 0.0);
   RooExponential Background("Background", "Background", Mass, BackgroundExp);
   RooRealVar BackgroundYield("BackgroundYield", "Background Yield", 0, 0, 1000000);

   RooAddPdf FinalModel("FinalModel", "Final model",
      RooArgSet(MainPeak, Background), RooArgSet(SignalYield, BackgroundYield));

   RooFitResult *Result = FinalModel.fitTo(dataset, Save(true));

   PsFileHelper PsFile("FitResult.ps");
   PsFile.AddTextPage("Mysterious peak around 1650!");

   RooPlot *ParametersPlot = Mass.frame(Bins(50), Name("Parameters"), Title("Fit parameters"));
   FinalModel.paramOn(ParametersPlot, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.9, 0.9));
   PsFile.AddPlot(ParametersPlot, "", false);

   RooPlot *FitPlot = Mass.frame(Bins(25), Name("FitPlot"), Title("Fit result!"));
   dataset.plotOn(FitPlot);
   FinalModel.plotOn(FitPlot, LineColor(1));
   FinalModel.plotOn(FitPlot, LineColor(1), Components(Background));
   PsFile.AddPlot(FitPlot, "", false);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}



