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

struct FitResult;
int main(int argc, char *argv[]);
FitResult TwoDimensionalSimpleFit(PsFileHelper &PsFile, string FileName, double LQMass);

struct FitResult
{
   double B;
   double BError;
   double MROffset;
   double MROffsetError;
   double R2Offset;
   double R2OffsetError;
};

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

   // int Energies[] = {50, 80, 90, 120, 140, 172, 200, 250, 300, 400, 500, 750, 800};
   int Energies[] = {90, 120, 140, 172, 200, 250, 300, 400, 500, 750, 800};

   TGraphErrors GParameterB;
   TGraphErrors GParameterMROffset;
   TGraphErrors GParameterR2Offset;

   GParameterB.SetNameTitle("GParameterB", "Parameter B vs. LQ mass");
   GParameterMROffset.SetNameTitle("GParameterMROffset", "Parameter MROffset vs. LQ mass");
   GParameterR2Offset.SetNameTitle("GParameterR2Offset", "Parameter R2Offset vs. LQ mass");

   for(int i = 0; i < 11; i++)
   {
      stringstream energy;
      energy << Energies[i];

      PsFileHelper PsFile("LQ" + energy.str() + ".ps");
      FitResult result = TwoDimensionalSimpleFit(PsFile, "Samples/LQ" + energy.str() + ".root", Energies[i]);
      PsFile.AddTimeStampPage();
      PsFile.Close();

      GParameterB.SetPoint(i, Energies[i], result.B);
      GParameterB.SetPointError(i, 0, result.BError);
      GParameterMROffset.SetPoint(i, Energies[i], result.MROffset);
      GParameterMROffset.SetPointError(i, 0, result.MROffsetError);
      GParameterR2Offset.SetPoint(i, Energies[i], result.R2Offset);
      GParameterR2Offset.SetPointError(i, 0, result.R2OffsetError);
   }

   PsFileHelper PsFile("MRToy22_Summary.ps");
   PsFile.AddTextPage("Summary of fits from MRToy 22");

   PsFile.AddPlot(GParameterB, "ape");
   PsFile.AddPlot(GParameterMROffset, "ape");
   PsFile.AddPlot(GParameterR2Offset, "ape");

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

FitResult TwoDimensionalSimpleFit(PsFileHelper &PsFile, string FileName, double LQMass)
{
   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("OutputTree");
   if(Tree == NULL)
      return FitResult();
   
   double MRLowerBound = LQMass * 2;
   double MRUpperBound = LQMass * 3.5;
   double RLowerBound = 0.40;
   double RUpperBound = 0.70;

   RooRealVar MR("MR", "Chris' kinematic variable", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R("R", "Chris' another kinematic variable", RLowerBound, RUpperBound);
   RooRealVar BetaR("BetaR", "BetaR", -0.99, 0.99);
   RooArgSet TreeVarSet(MR, R, BetaR);
   // RooArgSet TreeVarSet(MR, R);

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet, "BetaR < 0.99 && BetaR > -0.99");
   // RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet);

   RooRealVar MROffset("MROffset", "offset in MR", LQMass - 300, -2500, MRLowerBound);
   RooRealVar R2Offset("R2Offset", "offset in R^2", -0.03, -1000, RLowerBound * RLowerBound);
   
   RooRealVar MROffset2("MROffset2", "offset2 in MR", -LQMass / 2, -2500, MRLowerBound);
   RooRealVar R2Offset2("R2Offset2", "offset2 in R^2", -0.15, -50, RLowerBound * RLowerBound);

   RooFormulaVar X("X", "MR - MROffset", "@0 - @1", RooArgList(MR, MROffset));
   RooFormulaVar Y("Y", "R^2 - R2Offset", "@0 * @0 - @1", RooArgList(R, R2Offset));
   RooRealVar B("B", "B", 0.04, 0.0, 100.0);
   RooFormulaVar XY("XY", "Variable in the function", "@0 * @1 * @2", RooArgList(X, Y, B));
   
   RooFormulaVar X2("X2", "MR - MROffset2", "@0 - @1", RooArgList(MR, MROffset2));
   RooFormulaVar Y2("Y2", "R^2 - R2Offset2", "@0 * @0 - @1", RooArgList(R, R2Offset2));
   RooRealVar B2("B2", "B2", 0.01, 0.0, 100.0);
   RooFormulaVar XY2("XY2", "Variable in the function", "@0 * @1 * @2", RooArgList(X2, Y2, B2));

   RooGenericPdf FinalModel("Model1", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY));
   RooGenericPdf Model2("Model2", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY2));

   RooRealVar Fraction("Fraction", "Fraction", 0.68, 0.50, 1.0);
   // RooAddPdf FinalModel("FinalModel", "Title", Model1, Model2, Fraction);

   RooFitResult *Result = (RooFitResult *)FinalModel.fitTo(Dataset, Save(true));
   R2Offset.setVal(R2Offset.getVal() + 0.05);
   B.setVal(B.getVal() * 1.1);
   MROffset.setVal(MROffset.getVal() + 25);
   Result = (RooFitResult *)FinalModel.fitTo(Dataset, Save(true));
   // Result = (RooFitResult *)FinalModel.fitTo(Dataset, Save(true));

   RooPlot* ParameterPlot = MR.frame(Bins(25), Name("FitParameters"), Title("Fit parameters!!!!"));
   FinalModel.paramOn(ParameterPlot, Format("NULE", AutoPrecision(3)), Layout(0.1, 0.5, 0.8));
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

   RooPlot ParameterBMROffsetPlot(B, MROffset,
      B.getVal() - B.getError() * 2, B.getVal() + B.getError() * 2,
      MROffset.getVal() - MROffset.getError() * 2, MROffset.getVal() + MROffset.getError() * 2);
   RooPlot ParameterBR2OffsetPlot(B, R2Offset,
      B.getVal() - B.getError() * 2, B.getVal() + B.getError() * 2,
      R2Offset.getVal() - R2Offset.getError() * 2, R2Offset.getVal() + R2Offset.getError() * 2);
   RooPlot ParameterMROffsetR2OffsetPlot(MROffset, R2Offset,
      MROffset.getVal() - MROffset.getError() * 2, MROffset.getVal() + MROffset.getError() * 2,
      R2Offset.getVal() - R2Offset.getError() * 2, R2Offset.getVal() + R2Offset.getError() * 2);

   Result->plotOn(&ParameterBMROffsetPlot, B, MROffset, "ME");
   Result->plotOn(&ParameterBR2OffsetPlot, B, R2Offset, "ME");
   Result->plotOn(&ParameterMROffsetR2OffsetPlot, MROffset, R2Offset, "ME");

   PsFile.AddPlot(ParameterBMROffsetPlot);
   PsFile.AddPlot(ParameterBR2OffsetPlot);
   PsFile.AddPlot(ParameterMROffsetR2OffsetPlot);

   R.setRange("R04", 0.4, RUpperBound);
   R.setRange("R05", 0.5, RUpperBound);
   R.setRange("R06", 0.6, RUpperBound);

   RooPlot *MRResultPlot_R04 = MR.frame(Bins(25), Name("MRResultPlot_R04"), Title("MR, R > 0.4 projection"));
   Dataset.plotOn(MRResultPlot_R04, MarkerSize(0.9), MarkerColor(1), CutRange("R04"));
   FinalModel.plotOn(MRResultPlot_R04, LineColor(kBlue), ProjectionRange("R04"));
   PsFile.AddPlot(MRResultPlot_R04, "", true);

   RooPlot *MRResultPlot_R05 = MR.frame(Bins(25), Name("MRResultPlot_R05"), Title("MR, R > 0.5 projection"));
   Dataset.plotOn(MRResultPlot_R05, MarkerSize(0.9), MarkerColor(1), CutRange("R05"));
   FinalModel.plotOn(MRResultPlot_R05, LineColor(kBlue), ProjectionRange("R05"));
   PsFile.AddPlot(MRResultPlot_R05, "", true);

   RooPlot *MRResultPlot_R06 = MR.frame(Bins(25), Name("MRResultPlot_R06"), Title("MR, R > 0.6 projection"));
   Dataset.plotOn(MRResultPlot_R06, MarkerSize(0.9), MarkerColor(1), CutRange("R06"));
   FinalModel.plotOn(MRResultPlot_R06, LineColor(kBlue), ProjectionRange("R06"));
   PsFile.AddPlot(MRResultPlot_R06, "", true);

   MR.setRange("MRRange1", LQMass * 2, MRUpperBound);
   MR.setRange("MRRange2", LQMass * 3, MRUpperBound);
   MR.setRange("MRRange3", LQMass * 4, MRUpperBound);

   RooPlot *RResultPlot_MRRange1 = R.frame(Bins(25), Name("RResultPlot_MRRange1"),
      Title(Form("R, MR > %f projection", LQMass * 2)));
   Dataset.plotOn(RResultPlot_MRRange1, MarkerSize(0.9), MarkerColor(1), CutRange("MRRange1"));
   FinalModel.plotOn(RResultPlot_MRRange1, LineColor(kBlue), ProjectionRange("MRRange1"));
   PsFile.AddPlot(RResultPlot_MRRange1, "", true);

   RooPlot *RResultPlot_MRRange2 = R.frame(Bins(25), Name("RResultPlot_MRRange2"),
      Title(Form("R, MR > %f projection", LQMass * 3)));
   Dataset.plotOn(RResultPlot_MRRange2, MarkerSize(0.9), MarkerColor(1), CutRange("MRRange2"));
   FinalModel.plotOn(RResultPlot_MRRange2, LineColor(kBlue), ProjectionRange("MRRange2"));
   PsFile.AddPlot(RResultPlot_MRRange2, "", true);

   RooPlot *RResultPlot_MRRange3 = R.frame(Bins(25), Name("RResultPlot_MRRange3"),
      Title(Form("R, MR > %f projection", LQMass * 4)));
   Dataset.plotOn(RResultPlot_MRRange3, MarkerSize(0.9), MarkerColor(1), CutRange("MRRange3"));
   FinalModel.plotOn(RResultPlot_MRRange3, LineColor(kBlue), ProjectionRange("MRRange3"));
   PsFile.AddPlot(RResultPlot_MRRange3, "", true);

   FitResult FinalResult;
   FinalResult.B = B.getVal();
   FinalResult.BError = B.getError();
   FinalResult.MROffset = MROffset.getVal();
   FinalResult.MROffsetError = MROffset.getError();
   FinalResult.R2Offset = R2Offset.getVal();
   FinalResult.R2OffsetError = R2Offset.getError();
   return FinalResult;
}


