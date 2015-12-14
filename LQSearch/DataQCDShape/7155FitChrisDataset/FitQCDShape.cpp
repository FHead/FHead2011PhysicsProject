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

   TFile F("Jet_DiJetAve30.root");
   TTree *Tree = (TTree *)F.Get("EVENTS");
   if(Tree == NULL)
      return -1;

   const double MRLowerBound = 150;
   const double MRUpperBound = 300;
   const double RLowerBound = 0.1;
   const double RUpperBound = 0.5;
   const double R2LowerBound = RLowerBound * RLowerBound;
   const double R2UpperBound = RUpperBound * RUpperBound;

   RooRealVar MR("MR", "MR!!!!", MRLowerBound, MRUpperBound);
   RooRealVar RSQ("RSQ", "R*R!!!!", R2LowerBound, R2UpperBound);
   RooArgSet TreeVarSet(MR, RSQ);

   RooDataSet DataSet("DataSet", "MR/R DataSet", Tree, TreeVarSet);

   RooRealVar MROffset("MROffset", "offset in MR", -57.83, -200, MRLowerBound);
   RooRealVar R2Offset("R2Offset", "offset in R*R", -0.15738, -1, R2LowerBound);

   RooFormulaVar X("X", "MR - MR0", "@0 - @1", RooArgList(MR, MROffset));
   RooFormulaVar Y("Y", "R2 - R20", "@0 - @1", RooArgList(RSQ, R2Offset));
   RooRealVar B("B", "B", 0.1583, 0.0, 0.5);
   RooFormulaVar XY("XY", "Variable in the function", "@0 * @1 * @2", RooArgList(X, Y, B));

   RooGenericPdf FinalModel("Model", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY));

   RooFitResult *Result = (RooFitResult *)FinalModel.fitTo(DataSet, Save(true));

   PsFileHelper PsFile("QCDFitResult.ps");
   PsFile.AddTextPage("Fitting QCD shape in the low MR region");

   RooPlot *ParameterPlot = MR.frame(Bins(25), Name("ParameterPlot"), Title("Fit parameters"));
   FinalModel.paramOn(ParameterPlot, Format("NELU", AutoPrecision(3)), Layout(0.1, 0.9, 0.9));
   PsFile.AddPlot(ParameterPlot);

   TH2F *DataHistogram = MR.createHistogram("Data!", RSQ);
   DataSet.fillHistogram(DataHistogram, RooArgList(MR, RSQ));
   DataHistogram->Rebin2D(2, 2);
   PsFile.AddPlot(DataHistogram, "colz");
   
   TH2F *ModelHistogram = MR.createHistogram("Model!", RSQ);
   FinalModel.fillHistogram(ModelHistogram, RooArgList(MR, RSQ), DataSet.sumEntries());
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

   RSQ.setRange("RRange1", 0.25 * 0.25, R2UpperBound);
   RSQ.setRange("RRange2", 0.30 * 0.30, R2UpperBound);
   RSQ.setRange("RRange3", 0.35 * 0.35, R2UpperBound);
   RSQ.setRange("RRange4", 0.40 * 0.40, R2UpperBound);
   RSQ.setRange("RRange5", 0.45 * 0.45, R2UpperBound);
   
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
   DataSet.reduce("RSQ > 0.25 * 0.25")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(2));
   DataSet.reduce("RSQ > 0.3 * 0.3")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(3));
   DataSet.reduce("RSQ > 0.35 * 0.35")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(4));
   DataSet.reduce("RSQ > 0.4 * 0.4")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(5));
   DataSet.reduce("RSQ > 0.45 * 0.45")->plotOn(MRResultPlot, MarkerSize(1.1), MarkerColor(6));
   MRResultPlot->SetMinimum(0.3);
   PsFile.AddPlot(MRResultPlot, "", true);
   
   RooPlot *RResultPlot = RSQ.frame(Bins(25), Name("RResultPlot"), Title("R with different MR cuts"),
      Range(R2LowerBound, R2UpperBound));
   DataSet.plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(1));
   FinalModel.plotOn(RResultPlot, LineColor(1));
   FinalModel.plotOn(RResultPlot, LineColor(2), ProjectionRange("MRRange1"));
   FinalModel.plotOn(RResultPlot, LineColor(3), ProjectionRange("MRRange2"));
   FinalModel.plotOn(RResultPlot, LineColor(4), ProjectionRange("MRRange3"));
   FinalModel.plotOn(RResultPlot, LineColor(5), ProjectionRange("MRRange4"));
   DataSet.reduce("MR > 150")->plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(2));
   DataSet.reduce("MR > 180")->plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(3));
   DataSet.reduce("MR > 210")->plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(4));
   DataSet.reduce("MR > 240")->plotOn(RResultPlot, MarkerSize(1.1), MarkerColor(5));
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




