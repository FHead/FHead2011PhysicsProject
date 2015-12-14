#include <string>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TGraphErrors.h"

#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooRealVar.h"
#include "RooLorentzian.h"
#include "RooAddPdf.h"
#include "RooPolynomial.h"
#include "RooExponential.h"
#include "RooCruijff.h"
#include "RooPlot.h"
#include "RooExtendPdf.h"

#include "PlotHelper.h"

using namespace RooFit;

struct FitResult;
void FitZPeak(string RootFile = "Samples/DataAll.root");
FitResult FitZPeak(string RootFile, string TreeName, int JetCount, PsFileHelper &PsFile);

struct FitResult
{
   double Mass[2];
   double AlphaL[2];
   double AlphaR[2];
   double SigmaL[2];
   double SigmaR[2];
   double Yield[2];
};

void FitZPeak(string RootFile)
{
   PsFileHelper FitPlots("FitPlots.ps");
   FitPlots.AddTextPage("Fits!");

   FitResult Original[5];
   FitResult Iso[5];
   FitResult Hit[5];
   FitResult Chi2[5];

   for(int i = 0; i < 5; i++)
   {
      Original[i] = FitZPeak(RootFile, "EfficiencyTreeOriginal", i, FitPlots);
      Hit[i] = FitZPeak(RootFile, "EfficiencyTreeHit", i, FitPlots);
      Iso[i] = FitZPeak(RootFile, "EfficiencyTreeIso", i, FitPlots);
      Chi2[i] = FitZPeak(RootFile, "EfficiencyTreeChi2", i, FitPlots);
   }

   FitPlots.AddTimeStampPage();
   FitPlots.Close();

   for(int i = 0; i < 5; i++)
   {
      cout << "Jet count at least " << i << endl;

      cout << "Original: " << Original[i].Yield[0] << " +- " << Original[i].Yield[1] << endl;
      cout << "Don't requite isolation: " << Iso[i].Yield[0] << " +- " << Iso[i].Yield[1] << endl;
      cout << "Don't requite hits: " << Hit[i].Yield[0] << " +- " << Hit[i].Yield[1] << endl;
      cout << "Don't requite chi2: " << Chi2[i].Yield[0] << " +- " << Chi2[i].Yield[1] << endl;

      cout << "Isolation eff. = " << Original[i].Yield[0] / Iso[i].Yield[0] << endl;
      cout << "Hits eff. = " << Original[i].Yield[0] / Hit[i].Yield[0] << endl;
      cout << "Chi2 eff. = " << Original[i].Yield[0] / Chi2[i].Yield[0] << endl;
   }
}

FitResult FitZPeak(string RootFile, string TreeName, int JetCount, PsFileHelper &PsFile)
{
   RooRealVar ZMass("ZMass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NCaloJets("NCaloJet", "Count of jets", 0, 100000);
   RooArgSet TreeVarSet(ZMass, NCaloJets);

   TFile F(RootFile.c_str());
   TTree *ZTree = (TTree *)F.Get(TreeName.c_str());
   RooDataSet dataset("ZCandidates", "ZCandidates", ZTree, TreeVarSet);

   cout << "ZTree: " << ZTree << endl;

   TCut NumberOfJetCut = Form("NCaloJet >= %f", (double)JetCount - 0.0001);   // just to be safe
   RooDataSet *ReducedDataSet = (RooDataSet *)dataset.reduce(NumberOfJetCut);

   cout << "Number of entries = " << ReducedDataSet->sumEntries() << endl;

   RooRealVar PeakPosition("PeakPosition", "Z peak position", 91.01, 89, 93, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.445);
   RooRealVar AlphaL("AlphaL", "AlphaL", 0.517);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.14, 1, 3);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.10, 1, 3);
   RooCruijff MainZPeak("MainZPeak", "MainZPeak", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);
   RooRealVar Yield("Yield", "Yield", ReducedDataSet->sumEntries(), 0, 10000000);

   RooRealVar BackgroundExp("BackgroundExp", "Background exp", 0.000, -1.0, 0.0);
   RooExponential Background("Background", "Background shape", ZMass, BackgroundExp);
   RooRealVar BackgroundYield("BackgroundYield", "Background Yield", 1, 0, 1000000);

   RooAddPdf FinalFunction("FinalFunction", "Extended PDF", RooArgSet(MainZPeak, Background),
      RooArgSet(Yield, BackgroundYield));

   FinalFunction.fitTo(*ReducedDataSet);

   RooPlot *FinalResult = ZMass.frame(Bins(50), Name("MLL"), Title(TreeName.c_str()));

   ReducedDataSet->plotOn(FinalResult, MarkerSize(0.9));

   FinalFunction.paramOn(FinalResult, Format("NELU", AutoPrecision(2)), Layout(0.1, 0.4, 0.9));

   FinalFunction.plotOn(FinalResult, LineColor(kRed));
   FinalFunction.plotOn(FinalResult, LineColor(kRed), Components(Background));

   TCanvas Canvas("c1", "c1", 0, 0, 1024, 768);
   FinalResult->Draw();

   PsFile.AddCanvas(Canvas);

   FitResult Result;

   Result.Mass[0] = PeakPosition.getVal();
   Result.Mass[1] = PeakPosition.getError();
   Result.AlphaL[0] = AlphaL.getVal();
   Result.AlphaL[1] = AlphaL.getError();
   Result.AlphaR[0] = AlphaR.getVal();
   Result.AlphaR[1] = AlphaR.getError();
   Result.SigmaL[0] = SigmaL.getVal();
   Result.SigmaL[1] = SigmaL.getError();
   Result.SigmaR[0] = SigmaL.getVal();
   Result.SigmaR[1] = SigmaL.getError();
   Result.Yield[0] = Yield.getVal();
   Result.Yield[1] = Yield.getError();

   return Result;
}



