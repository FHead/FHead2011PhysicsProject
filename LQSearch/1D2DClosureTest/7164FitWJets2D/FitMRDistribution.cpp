#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

#include "TH2F.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TMath.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooArgSet.h"
#include "RooFormulaVar.h"
#include "RooFitResult.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooSameAs.h"
#include "RooAtLeast.h"
#include "RooAbsPdf.h"
#include "RooExponential.h"
#include "RooGenericPdf.h"
using namespace RooFit;

#include "PlotHelper2.h"
#include "DataHelper.h"
#include "SetStyle.h"
#include "DrawRandom.h"

int main(int argc, char *argv[]);
void TwoDimensionalSimpleFit(PsFileHelper &PsFile, string FileName);
double GetPercentage(double Base, double Test);

int main(int argc, char *argv[])
{
   SetStyle();

   PsFileHelper PsFile("DevelopTwoDimensionalFit.ps");
   PsFile.AddTextPage("2D Fit to WJets in the electron box");

   TwoDimensionalSimpleFit(PsFile, "Samples/Wjets.root");

   PsFile.AddTimeStampPage();   
   PsFile.Close();
}

void TwoDimensionalSimpleFit(PsFileHelper &PsFile, string FileName)
{
   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("EVENTS");
   if(Tree == NULL)
      return;
   
   double MRLowerBound = 300;
   double MRUpperBound = 1500;
   double RLowerBound = 0.30;
   double RUpperBound = 1;

   RooRealVar MR("MR", "M_{R}", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R("RSQ", "R^{2}", RLowerBound * RLowerBound, RUpperBound * RUpperBound);
   RooRealVar BoxNumber("BOX_NUM", "Box number", -10, 10);
   RooArgSet TreeVarSet(MR, R, BoxNumber);

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet, "BOX_NUM == 4");

   RooRealVar MROffset1("MROffset1", "offset 1 in MR", -450, -10000000, MRLowerBound);
   RooRealVar R2Offset1("R2Offset1", "offset 1 in R^2", -0.4779, -10000, 0.09);
   RooRealVar MROffset2("MROffset2", "offset 2 in MR", -450, -10000000, MRLowerBound);
   RooRealVar R2Offset2("R2Offset2", "offset 2 in R^2", -0.3589, -10000, 0.09);

   RooFormulaVar X1("X1", "MR - MR0", "@0 - @1", RooArgList(MR, MROffset1));
   RooFormulaVar Y1("Y1", "R^2 - R20", "@0 - @1", RooArgList(R, R2Offset1));
   RooRealVar B1("B1", "B1", 0.00480202, 0, 10000);
   RooFormulaVar XY1("XY1", "Variable in the function", "@0 * @1 * @2", RooArgList(X1, Y1, B1));
   RooGenericPdf Model1("Model1", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY1));

   RooFormulaVar X2("X2", "MR - MR0", "@0 - @1", RooArgList(MR, MROffset2));
   RooFormulaVar Y2("Y2", "R^2 - R20", "@0 - @1", RooArgList(R, R2Offset2));
   RooRealVar B2("B2", "B2", 0.00861269, 0, 10000);
   RooFormulaVar XY2("XY2", "Variable in the function", "@0 * @1 * @2", RooArgList(X2, Y2, B2));
   RooGenericPdf Model2("Model2", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY2));

   RooRealVar Fraction("Fraction", "Fraction", 0.3, 0, 1);
   RooAddPdf FinalModel("FinalModel", "Final model....", Model1, Model2, Fraction);

   RooFitResult *Result = (RooFitResult *)FinalModel.fitTo(Dataset, Save(true));

   RooPlot *ParameterPlot = MR.frame(Bins(25), Name("ParameterPlot"), Title("Fit parameters"));
   FinalModel.paramOn(ParameterPlot, Format("NELU", AutoPrecision(3)), Layout(0.1, 0.9, 0.9));
   PsFile.AddPlot(ParameterPlot);

   TH2F *DataHistogram = MR.createHistogram("Data!", R);
   Dataset.fillHistogram(DataHistogram, RooArgList(MR, R));
   PsFile.AddPlot(DataHistogram, "lego");
   
   TH2F *ModelHistogram = MR.createHistogram("Model!", R);
   FinalModel.fillHistogram(ModelHistogram, RooArgList(MR, R), Dataset.sumEntries());
   PsFile.AddPlot(ModelHistogram, "surf");

   TH2F *ResidualHistogram = MR.createHistogram("Residual!", R);
   Dataset.fillHistogram(ResidualHistogram, RooArgList(MR, R));
   ResidualHistogram->Add(ModelHistogram, -1);
   PsFile.AddPlot(ResidualHistogram, "lego", false, false);
   
   DataHistogram->Rebin2D(3, 4);
   ModelHistogram->Rebin2D(3, 4);

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



