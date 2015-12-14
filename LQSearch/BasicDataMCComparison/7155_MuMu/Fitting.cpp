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
void PerformFit(string InputFile, string OutputBase);

int main()
{
   SetStyle();
   
   PerformFit("DataPlots.root", "FitData");
   PerformFit("TTbar.root", "FitTTbar");

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

void PerformFit(string InputFile, string OutputBase)
{
   TFile F(InputFile.c_str());
   TTree *Tree = (TTree *)F.Get("MRTree");
   if(Tree == NULL)
      return;

   double MRLowerBound = 300;
   double MRUpperBound = 1000;
   double RLowerBound = 0.3;
   double RUpperBound = 1.0;
   double R2LowerBound = RLowerBound * RLowerBound;
   double R2UpperBound = RUpperBound * RUpperBound;

   RooRealVar MR("MR", "MR!!!!", MRLowerBound, MRUpperBound);
   RooRealVar R("R", "R!!!!", RLowerBound, RUpperBound);
   RooArgSet TreeVarSet(MR, R);

   RooDataSet DataSet("DataSet", "MR/R DataSet", Tree, TreeVarSet, Form("MR > %f && R > %f", MRLowerBound, RLowerBound));

   RooRealVar MROffset1("MROffset", "offset in MR", -450, -1000, MRLowerBound);
   RooRealVar R2Offset1("R2Offset", "offset in R*R", -0.2, -10, R2LowerBound);
   RooFormulaVar X1("X1", "MR - MR0", "@0 - @1", RooArgList(MR, MROffset1));
   RooFormulaVar Y1("Y1", "R^2 - R20", "@0 * @0 - @1", RooArgList(R, R2Offset1));
   RooRealVar B1("B1", "B1", 0.03, 0.0, 100.0);
   RooFormulaVar XY1("XY1", "Variable in the function", "@0 * @1 * @2", RooArgList(X1, Y1, B1));
   RooGenericPdf Model1("Model1", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY1));
   
   RooRealVar MROffset2("MROffset2", "offset in MR", -450, -1000, MRLowerBound);
   RooRealVar R2Offset2("R2Offset2", "offset in R*R", -0.2, -10, R2LowerBound);
   RooFormulaVar X2("X2", "MR - MR0", "@0 - @1", RooArgList(MR, MROffset2));
   RooFormulaVar Y2("Y2", "R^2 - R20", "@0 * @0 - @1", RooArgList(R, R2Offset2));
   RooRealVar B2("B2", "B2", 0.03, 0.0, 100.0);
   RooFormulaVar XY2("XY2", "Variable in the function", "@0 * @1 * @2", RooArgList(X2, Y2, B2));
   RooGenericPdf Model2("Model2", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY2));

   RooRealVar Fraction("Fraction", "Fraction", 0.2, 0, 1);
   RooAddPdf FinalModel("FinalModel", "Model!", Model1, Model2, Fraction);

   RooFitResult *Result = (RooFitResult *)FinalModel.fitTo(DataSet, Save(true));

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage("Fitting");

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

   R.setRange("RRange1", 0.30, RUpperBound);
   R.setRange("RRange2", 0.35, RUpperBound);
   R.setRange("RRange3", 0.40, RUpperBound);
   R.setRange("RRange4", 0.45, RUpperBound);
   
   MR.setRange("MRRange1", 300, MRUpperBound);
   MR.setRange("MRRange2", 350, MRUpperBound);
   MR.setRange("MRRange3", 400, MRUpperBound);
   MR.setRange("MRRange4", 450, MRUpperBound);

   // projections...
   RooPlot *MRResultPlot = MR.frame(Bins(25), Name("MRResultPlot"), Title("MR with different R cuts"));
   DataSet.plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(1));
   FinalModel.plotOn(MRResultPlot, LineColor(1));
   FinalModel.plotOn(MRResultPlot, LineColor(2), ProjectionRange("RRange1"));
   FinalModel.plotOn(MRResultPlot, LineColor(3), ProjectionRange("RRange2"));
   FinalModel.plotOn(MRResultPlot, LineColor(4), ProjectionRange("RRange3"));
   FinalModel.plotOn(MRResultPlot, LineColor(5), ProjectionRange("RRange4"));
   DataSet.reduce("R > 0.3")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(2));
   DataSet.reduce("R > 0.35")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(3));
   DataSet.reduce("R > 0.4")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(4));
   DataSet.reduce("R > 0.45")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(5));
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
   DataSet.reduce("MR > 300")->plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(2));
   DataSet.reduce("MR > 350")->plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(3));
   DataSet.reduce("MR > 400")->plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(4));
   DataSet.reduce("MR > 450")->plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(5));
   RResultPlot->SetMinimum(0.3);
   PsFile.AddPlot(RResultPlot, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

}



