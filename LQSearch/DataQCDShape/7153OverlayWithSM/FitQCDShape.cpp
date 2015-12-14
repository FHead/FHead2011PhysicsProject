#include <iostream>
#include <string>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TMath.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooFormulaVar.h"
#include "RooFitResult.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooGenericPdf.h"
using namespace RooFit;

#include "SetStyle.h"
#include "PlotHelper2.h"
#include "DrawRandom.h"

int main();
double GetPercentage(double Base, double Test);

int main()
{
   SetStyle();

   TFile F("JetReducedTree.root");
   TTree *Tree = (TTree *)F.Get("MRTree");
   if(Tree == NULL)
      return -1;

   double MRLowerBound = 120;
   double MRUpperBound = 400;
   double RLowerBound = 0.2;
   double RUpperBound = 1.0;
   double R2LowerBound = RLowerBound * RLowerBound;
   double R2UpperBound = RUpperBound * RUpperBound;

   RooRealVar MR("GammaMRStar", "MR!!!!", MRLowerBound, MRUpperBound);
   RooRealVar R("RStar", "R!!!!", RLowerBound, RUpperBound);
   RooRealVar PassDiJetAve30Int("PassDiJetAve30Int", "Trigger requirement", -100, 100);
   RooRealVar LeadingJetDeltaPhi("LeadingJetDeltaPhi", "Delta phi requirement", -100, 100);
   RooArgSet TreeVarSet(MR, R, PassDiJetAve30Int, LeadingJetDeltaPhi);

   RooDataSet DataSet("DataSet", "MR/R DataSet", Tree, TreeVarSet,
      "PassDiJetAve30Int > 0 && (LeadingJetDeltaPhi > 0.2 || LeadingJetDeltaPhi < -0.2)");

   RooRealVar MROffset("MROffset", "offset in MR", -450, -1000, MRLowerBound);
   RooRealVar R2Offset("R2Offset", "offset in R*R", -0.2, -10, R2LowerBound);

   RooFormulaVar X("X", "MR - MR0", "@0 - @1", RooArgList(MR, MROffset));
   RooFormulaVar Y("Y", "R^2 - R20", "@0 * @0 - @1", RooArgList(R, R2Offset));
   RooRealVar B("B", "B", 0.03, 0.0, 100.0);
   RooFormulaVar XY("XY", "Variable in the function", "@0 * @1 * @2", RooArgList(X, Y, B));

   RooGenericPdf FinalModel("Model", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY));

   RooFitResult *Result = (RooFitResult *)FinalModel.fitTo(DataSet, Save(true));

   PsFileHelper PsFile("QCDFitResult.ps");
   PsFile.AddTextPage("Fitting QCD shape in the low MR region");

   RooPlot *ParameterPlot = MR.frame(Bins(25), Name("ParameterPlot"), Title("Fit parameters"));
   FinalModel.paramOn(ParameterPlot, Format("NELU", AutoPrecision(3)), Layout(0.1, 0.9, 0.9));
   PsFile.AddPlot(ParameterPlot);

   TH2F *DataHistogram = MR.createHistogram("Data!", R);
   DataSet.fillHistogram(DataHistogram, RooArgList(MR, R));
   DataHistogram->Rebin2D(2, 2);
   PsFile.AddPlot(DataHistogram, "colz");
   
   TH2F *ModelHistogram = MR.createHistogram("Model!", R);
   FinalModel.fillHistogram(ModelHistogram, RooArgList(MR, R), DataSet.sumEntries());
   ModelHistogram->Rebin2D(2, 2);
   PsFile.AddPlot(ModelHistogram, "colz");

   const Int_t NRGBs = 6;
   const Int_t NCont = 255;
   Double_t stops[NRGBs] = {0.00, 0.32, 0.4999, 0.50, 0.68, 1.00};
   Double_t red[NRGBs]   = {1.00, 0.50, 0.00, 0.00, 0.00, 0.00};
   Double_t green[NRGBs] = {0.00, 0.00, 1.00, 1.00, 0.00, 0.00};
   Double_t blue[NRGBs]  = {0.00, 0.00, 0.00, 0.00, 0.50, 1.00};
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   TH2F *PercentageHistogram = (TH2F *)DataHistogram->Clone("PercentageHistogram");
   PercentageHistogram->SetTitle("Percentage!!!");
   for(int i = 1; i <= PercentageHistogram->GetNbinsX(); i++)
   {
      for(int j = 1; j <= PercentageHistogram->GetNbinsY(); j++)
      {
         double DataPoint = DataHistogram->GetBinContent(i, j);
         double ModelPoint = ModelHistogram->GetBinContent(i, j);
         if(DataPoint > 0)
            PercentageHistogram->SetBinContent(i, j, GetPercentage(ModelPoint, DataPoint));
      }
   }
   PercentageHistogram->SetMinimum(0);
   PercentageHistogram->SetMaximum(1);
   PercentageHistogram->SetStats(0);
   PsFile.AddPlot(PercentageHistogram, "colz");

   R.setRange("RRange1", 0.25, RUpperBound);
   R.setRange("RRange2", 0.30, RUpperBound);
   R.setRange("RRange3", 0.35, RUpperBound);
   R.setRange("RRange4", 0.40, RUpperBound);
   R.setRange("RRange5", 0.45, RUpperBound);
   
   MR.setRange("MRRange1", 150, MRUpperBound);
   MR.setRange("MRRange2", 180, MRUpperBound);
   MR.setRange("MRRange3", 210, MRUpperBound);
   MR.setRange("MRRange4", 240, MRUpperBound);

   // projections...
   RooPlot *MRResultPlot = MR.frame(Bins(25), Name("MRResultPlot"), Title("MR with different R cuts"));
   DataSet.plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(1));
   FinalModel.plotOn(MRResultPlot, LineColor(1));
   FinalModel.plotOn(MRResultPlot, LineColor(2), ProjectionRange("RRange1"));
   FinalModel.plotOn(MRResultPlot, LineColor(3), ProjectionRange("RRange2"));
   FinalModel.plotOn(MRResultPlot, LineColor(4), ProjectionRange("RRange3"));
   FinalModel.plotOn(MRResultPlot, LineColor(5), ProjectionRange("RRange4"));
   FinalModel.plotOn(MRResultPlot, LineColor(6), ProjectionRange("RRange5"));
   DataSet.reduce("RStar > 0.25")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(2));
   DataSet.reduce("RStar > 0.3")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(3));
   DataSet.reduce("RStar > 0.35")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(4));
   DataSet.reduce("RStar > 0.4")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(5));
   DataSet.reduce("RStar > 0.45")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(6));
   MRResultPlot->SetMinimum(0.3);
   PsFile.AddPlot(MRResultPlot, "", true);
   
   RooPlot *RResultPlot = R.frame(Bins(25), Name("RResultPlot"), Title("R with different MR cuts"),
      Range(RLowerBound, 0.6));
   DataSet.plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(1));
   FinalModel.plotOn(RResultPlot, LineColor(1));
   FinalModel.plotOn(RResultPlot, LineColor(2), ProjectionRange("MRRange1"));
   FinalModel.plotOn(RResultPlot, LineColor(3), ProjectionRange("MRRange2"));
   FinalModel.plotOn(RResultPlot, LineColor(4), ProjectionRange("MRRange3"));
   FinalModel.plotOn(RResultPlot, LineColor(5), ProjectionRange("MRRange4"));
   DataSet.reduce("GammaMRStar > 150")->plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(2));
   DataSet.reduce("GammaMRStar > 180")->plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(3));
   DataSet.reduce("GammaMRStar > 210")->plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(4));
   DataSet.reduce("GammaMRStar > 240")->plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(5));
   RResultPlot->SetMinimum(0.3);
   PsFile.AddPlot(RResultPlot, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

double GetPercentage(double Base, double Test)
{
   const double NumberOfTries = 10000;
   double SuccessfulTries = 0;

   for(int i = 0; i < NumberOfTries; i++)
   {
      double value = 0;

      if(Base < 20)
      {
         bool OK = false;
         while(OK == false)
         {
            value = (int)DrawRandom(Base * 1.5 + 10);
            double check = DrawRandom();
            if(check < TMath::Poisson(value, Base))
               OK = true;
         }
      }
      else
         value = DrawGaussian(Base, sqrt(Base));

      if(value < Test)
         SuccessfulTries = SuccessfulTries + 1;
   }

   if(SuccessfulTries < 1e-3)
      SuccessfulTries = 1e-3;

   return SuccessfulTries / NumberOfTries;
}




