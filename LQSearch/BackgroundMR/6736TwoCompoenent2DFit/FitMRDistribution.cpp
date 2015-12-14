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

int main(int argc, char *argv[]);
void TwoDimensionalSimpleFit(PsFileHelper &PsFile, DataHelper &DHFile, string State, string FileName);

int main(int argc, char *argv[])
{
   gROOT->SetStyle("Plain");

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   DataHelper DHFile("ToyResults.dh");

   for(int i = 101; i <= 1000; i++)
   {
      stringstream NumberToString;
      NumberToString << i;
      PsFileHelper PsFile("OutputFiles/TwoDimensionalToy_" + NumberToString.str() + ".ps");

      stringstream State;
      State << "TwoDimensionalToy_" << i;
      
      TwoDimensionalSimpleFit(PsFile, DHFile, State.str(), "Samples/ToyOn2DFit_" + NumberToString.str() + ".root");

      PsFile.AddTimeStampPage();
      PsFile.Close();

      DHFile.SaveToFile("ToyResults.dh");
   }

   DHFile.SaveToFile("ToyResults.dh");
}

void TwoDimensionalSimpleFit(PsFileHelper &PsFile, DataHelper &DHFile, string State, string FileName)
{
   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("MRTree");
   if(Tree == NULL)
      return;
   
   double MRLowerBound = 300;
   double MRUpperBound = 1500;
   double RLowerBound = 0.30;
   double RUpperBound = 1;

   RooRealVar MR("GroupPFMR", "Chris' kinematic variable", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R("GroupPFR", "Chris' another kinematic variable", RLowerBound, RUpperBound);
   RooArgSet TreeVarSet(MR, R);

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet, "");

   RooRealVar MR1Offset("MR1Offset", "offset in MR (1)", -450, -1000, MRLowerBound);
   RooRealVar R21Offset("R21Offset", "offset in R^2 (1)", -0.2, -10, RLowerBound * RLowerBound);
   RooRealVar MR2Offset("MR2Offset", "offset in MR (2)", -450, -1000, MRLowerBound);
   RooRealVar R22Offset("R22Offset", "offset in R^2 (2)", -0.2, -10, RLowerBound * RLowerBound);

   RooFormulaVar X1("X1", "MR - MR01", "@0 - @1", RooArgList(MR, MR1Offset));
   RooFormulaVar X2("X2", "MR - MR02", "@0 - @1", RooArgList(MR, MR2Offset));
   RooFormulaVar Y1("Y1", "R^2 - R201", "@0 * @0 - @1", RooArgList(R, R21Offset));
   RooFormulaVar Y2("Y2", "R^2 - R202", "@0 * @0 - @1", RooArgList(R, R22Offset));
   RooRealVar B1("B1", "B1", 0.03, 0.0, 100.0);
   RooRealVar B2("B2", "B2", 0.03, 0.0, 100.0);
   RooFormulaVar XY1("XY1", "Variable in the function", "@0 * @1 * @2", RooArgList(X1, Y1, B1));
   RooFormulaVar XY2("XY2", "Variable in the function", "@0 * @1 * @2", RooArgList(X2, Y2, B2));

   RooGenericPdf Component1("Model1", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY1));
   RooGenericPdf Component2("Model2", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY2));
   RooRealVar Fraction("Fraction", "Fraction", 0, 1);
   RooAddPdf FinalModel("Model", "Final model!", Component1, Component2, Fraction);

   RooFitResult *Result = (RooFitResult *)FinalModel.fitTo(Dataset, Save(true));

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

   RooPlot ParameterB1MR1OffsetPlot(B1, MR1Offset,
      B1.getVal() - B1.getError() * 2, B1.getVal() + B1.getError() * 2,
      MR1Offset.getVal() - MR1Offset.getError() * 2, MR1Offset.getVal() + MR1Offset.getError() * 2);
   RooPlot ParameterB1R21OffsetPlot(B1, R21Offset,
      B1.getVal() - B1.getError() * 2, B1.getVal() + B1.getError() * 2,
      R21Offset.getVal() - R21Offset.getError() * 2, R21Offset.getVal() + R21Offset.getError() * 2);
   RooPlot ParameterMR1OffsetR21OffsetPlot(MR1Offset, R21Offset,
      MR1Offset.getVal() - MR1Offset.getError() * 2, MR1Offset.getVal() + MR1Offset.getError() * 2,
      R21Offset.getVal() - R21Offset.getError() * 2, R21Offset.getVal() + R21Offset.getError() * 2);
   RooPlot ParameterB2MR2OffsetPlot(B2, MR2Offset,
      B2.getVal() - B2.getError() * 2, B2.getVal() + B2.getError() * 2,
      MR2Offset.getVal() - MR2Offset.getError() * 2, MR2Offset.getVal() + MR2Offset.getError() * 2);
   RooPlot ParameterB2R22OffsetPlot(B2, R22Offset,
      B2.getVal() - B2.getError() * 2, B2.getVal() + B2.getError() * 2,
      R22Offset.getVal() - R22Offset.getError() * 2, R22Offset.getVal() + R22Offset.getError() * 2);
   RooPlot ParameterMR2OffsetR22OffsetPlot(MR2Offset, R22Offset,
      MR2Offset.getVal() - MR2Offset.getError() * 2, MR2Offset.getVal() + MR2Offset.getError() * 2,
      R22Offset.getVal() - R22Offset.getError() * 2, R22Offset.getVal() + R22Offset.getError() * 2);
   RooPlot ParameterB1B2Plot(B1, B2,
      B1.getVal() - B1.getError() * 2, B1.getVal() + B1.getError() * 2,
      B2.getVal() - B2.getError() * 2, B2.getVal() + B2.getError() * 2);

   Result->plotOn(&ParameterB1MR1OffsetPlot, B1, MR1Offset, "ME");
   Result->plotOn(&ParameterB1R21OffsetPlot, B1, R21Offset, "ME");
   Result->plotOn(&ParameterMR1OffsetR21OffsetPlot, MR1Offset, R21Offset, "ME");
   Result->plotOn(&ParameterB2MR2OffsetPlot, B2, MR2Offset, "ME");
   Result->plotOn(&ParameterB2R22OffsetPlot, B2, R22Offset, "ME");
   Result->plotOn(&ParameterMR2OffsetR22OffsetPlot, MR2Offset, R22Offset, "ME");
   Result->plotOn(&ParameterB1B2Plot, B1, B2, "ME");

   PsFile.AddPlot(ParameterB1MR1OffsetPlot);
   PsFile.AddPlot(ParameterB1R21OffsetPlot);
   PsFile.AddPlot(ParameterMR1OffsetR21OffsetPlot);
   PsFile.AddPlot(ParameterB2MR2OffsetPlot);
   PsFile.AddPlot(ParameterB2R22OffsetPlot);
   PsFile.AddPlot(ParameterMR2OffsetR22OffsetPlot);
   PsFile.AddPlot(ParameterB1B2Plot);

   DHFile[State]["B1"] = B1.getVal();
   DHFile[State]["B1Error"] = B1.getError();
   DHFile[State]["MR1Offset"] = MR1Offset.getVal();
   DHFile[State]["MR1OffsetError"] = MR1Offset.getError();
   DHFile[State]["R21Offset"] = R21Offset.getVal();
   DHFile[State]["R21OffsetError"] = R21Offset.getError();
   DHFile[State]["B2"] = B2.getVal();
   DHFile[State]["B2Error"] = B2.getError();
   DHFile[State]["MR2Offset"] = MR2Offset.getVal();
   DHFile[State]["MR2OffsetError"] = MR2Offset.getError();
   DHFile[State]["R22Offset"] = R22Offset.getVal();
   DHFile[State]["R22OffsetError"] = R22Offset.getError();
   DHFile[State]["Fraction"] = Fraction.getVal();
   DHFile[State]["FractionError"] = Fraction.getError();
   DHFile[State]["CovarianceQuality"] = Result->covQual();
}


