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

   RooRealVar MROffset("MROffset", "offset in MR", -450, -1000, MRLowerBound);
   RooRealVar R2Offset("R2Offset", "offset in R^2", -0.2, -10, RLowerBound * RLowerBound);

   RooFormulaVar X("X", "MR - MR0", "@0 - @1", RooArgList(MR, MROffset));
   RooFormulaVar Y("Y", "R^2 - R20", "@0 * @0 - @1", RooArgList(R, R2Offset));
   RooRealVar B("B", "B", 0.03, 0.0, 100.0);
   RooFormulaVar XY("XY", "Variable in the function", "@0 * @1 * @2", RooArgList(X, Y, B));

   RooGenericPdf FinalModel("Model", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY));

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

   DHFile[State]["B"] = B.getVal();
   DHFile[State]["BError"] = B.getError();
   DHFile[State]["MROffset"] = MROffset.getVal();
   DHFile[State]["MROffsetError"] = MROffset.getError();
   DHFile[State]["R2Offset"] = R2Offset.getVal();
   DHFile[State]["R2OffsetError"] = R2Offset.getError();
}


