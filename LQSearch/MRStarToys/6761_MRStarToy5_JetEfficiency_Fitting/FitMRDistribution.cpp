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
void TwoDimensionalSimpleFit(PsFileHelper &PsFile, string FileName, bool RequireTagging);

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

   PsFileHelper PsFile1("ImplicationsOnPTEfficiency_FlatOneJet.ps");
   PsFile1.AddTextPage("flat, one jet, before");
   TwoDimensionalSimpleFit(PsFile1, "FlatOneJet.root", false);
   PsFile1.AddTextPage("flat, one jet, after");
   TwoDimensionalSimpleFit(PsFile1, "FlatOneJet.root", true);
   PsFile1.AddTimeStampPage();
   PsFile1.Close();
   
   PsFileHelper PsFile2("ImplicationsOnPTEfficiency_FlatTwoJet.ps");
   PsFile2.AddTextPage("flat, two jet, before");
   TwoDimensionalSimpleFit(PsFile2, "FlatTwoJet.root", false);
   PsFile2.AddTextPage("flat, two jet, after");
   TwoDimensionalSimpleFit(PsFile2, "FlatTwoJet.root", true);
   PsFile2.AddTimeStampPage();
   PsFile2.Close();
   
   PsFileHelper PsFile3("ImplicationsOnPTEfficiency_TCHELOneJet.ps");
   PsFile3.AddTextPage("TCHEL, one jet, before");
   TwoDimensionalSimpleFit(PsFile3, "RoughlyTCHELOneJet.root", false);
   PsFile3.AddTextPage("TCHEL, one jet, after");
   TwoDimensionalSimpleFit(PsFile3, "RoughlyTCHELOneJet.root", true);
   PsFile3.AddTimeStampPage();
   PsFile3.Close();
   
   PsFileHelper PsFile4("ImplicationsOnPTEfficiency_TCHELTwoJet.ps");
   PsFile4.AddTextPage("TCHEL, two jet, before");
   TwoDimensionalSimpleFit(PsFile4, "RoughlyTCHELTwoJet.root", false);
   PsFile4.AddTextPage("TCHEL, two jet, after");
   TwoDimensionalSimpleFit(PsFile4, "RoughlyTCHELTwoJet.root", true);
   PsFile4.AddTimeStampPage();
   PsFile4.Close();
   
   PsFileHelper PsFile5("ImplicationsOnPTEfficiency_TCHELDropOneJet.ps");
   PsFile5.AddTextPage("TCHEL (drop), one jet, before");
   TwoDimensionalSimpleFit(PsFile5, "RoughlyTCHELOneJetModerateDrop.root", false);
   PsFile5.AddTextPage("TCHEL (drop), one jet, after");
   TwoDimensionalSimpleFit(PsFile5, "RoughlyTCHELOneJetModerateDrop.root", true);
   PsFile5.AddTimeStampPage();
   PsFile5.Close();
 
   PsFileHelper PsFile6("ImplicationsOnPTEfficiency_TCHELDropTwoJet.ps");
   PsFile6.AddTextPage("TCHEL (drop), two jet, before");
   TwoDimensionalSimpleFit(PsFile6, "RoughlyTCHELTwoJetModerateDrop.root", false);
   PsFile6.AddTextPage("TCHEL (drop), two jet, after");
   TwoDimensionalSimpleFit(PsFile6, "RoughlyTCHELTwoJetModerateDrop.root", true);
   PsFile6.AddTimeStampPage();
   PsFile6.Close();
   
   PsFileHelper PsFile7("ImplicationsOnPTEfficiency_BetterHighPTOneJet.ps");
   PsFile7.AddTextPage("Better high PT, one jet, before");
   TwoDimensionalSimpleFit(PsFile7, "BetterHighPTOneJet.root", false);
   PsFile7.AddTextPage("Better high PT, one jet, after");
   TwoDimensionalSimpleFit(PsFile7, "BetterHighPTOneJet.root", true);
   PsFile7.AddTimeStampPage();
   PsFile7.Close();
   
   PsFileHelper PsFile8("ImplicationsOnPTEfficiency_BetterHighPTTwoJet.ps");
   PsFile8.AddTextPage("Better high PT, two jet, before");
   TwoDimensionalSimpleFit(PsFile8, "BetterHighPTTwoJet.root", false);
   PsFile8.AddTextPage("Better high PT, two jet, after");
   TwoDimensionalSimpleFit(PsFile8, "BetterHighPTTwoJet.root", true);
   PsFile8.AddTimeStampPage();
   PsFile8.Close();
   
   PsFileHelper PsFile9("ImplicationsOnPTEfficiency_WorseHighPTOneJet.ps");
   PsFile9.AddTextPage("Worse high PT, one jet, before");
   TwoDimensionalSimpleFit(PsFile9, "WorseHighPTOneJet.root", false);
   PsFile9.AddTextPage("Worse high PT, one jet, after");
   TwoDimensionalSimpleFit(PsFile9, "WorseHighPTOneJet.root", true);
   PsFile9.AddTimeStampPage();
   PsFile9.Close();
   
   PsFileHelper PsFile10("ImplicationsOnPTEfficiency_WorseHighPTTwoJet.ps");
   PsFile10.AddTextPage("Worse high PT, two jet, before");
   TwoDimensionalSimpleFit(PsFile10, "WorseHighPTTwoJet.root", false);
   PsFile10.AddTextPage("Worse high PT, two jet, after");
   TwoDimensionalSimpleFit(PsFile10, "WorseHighPTTwoJet.root", true);
   PsFile10.AddTimeStampPage();
   PsFile10.Close();
   
   PsFileHelper PsFile11("ImplicationsOnPTEfficiency_NoHighPTOneJet.ps");
   PsFile11.AddTextPage("No high PT, one jet, before");
   TwoDimensionalSimpleFit(PsFile11, "NoHighPTOneJet.root", false);
   PsFile11.AddTextPage("No high PT, one jet, after");
   TwoDimensionalSimpleFit(PsFile11, "NoHighPTOneJet.root", true);
   PsFile11.AddTimeStampPage();
   PsFile11.Close();
   
   PsFileHelper PsFile12("ImplicationsOnPTEfficiency_NoHighPTTwoJet.ps");
   PsFile12.AddTextPage("No high PT, two jet, before");
   TwoDimensionalSimpleFit(PsFile12, "NoHighPTTwoJet.root", false);
   PsFile12.AddTextPage("No high PT, two jet, after");
   TwoDimensionalSimpleFit(PsFile12, "NoHighPTTwoJet.root", true);
   PsFile12.AddTimeStampPage();
   PsFile12.Close();
   
   PsFileHelper PsFile13("ImplicationsOnPTEfficiency_ExtremeDropOneJet.ps");
   PsFile13.AddTextPage("Extreme drop, one jet, before");
   TwoDimensionalSimpleFit(PsFile13, "ExtremeDropOneJet.root", false);
   PsFile13.AddTextPage("Extreme drop, one jet, after");
   TwoDimensionalSimpleFit(PsFile13, "ExtremeDropOneJet.root", true);
   PsFile13.AddTimeStampPage();
   PsFile13.Close();
   
   PsFileHelper PsFile14("ImplicationsOnPTEfficiency_ExtremeDropTwoJet.ps");
   PsFile14.AddTextPage("Extreme drop, two jet, before");
   TwoDimensionalSimpleFit(PsFile14, "ExtremeDropTwoJet.root", false);
   PsFile14.AddTextPage("Extreme drop, two jet, after");
   TwoDimensionalSimpleFit(PsFile14, "ExtremeDropTwoJet.root", true);
   PsFile14.AddTimeStampPage();
   PsFile14.Close();
}

void TwoDimensionalSimpleFit(PsFileHelper &PsFile, string FileName, bool RequireTagging)
{
   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("CleanedTree");
   if(Tree == NULL)
      return;
   
   double MRLowerBound = 500;
   double MRUpperBound = 1500;
   double RLowerBound = 0.50;
   double RUpperBound = 1;

   RooRealVar MR("MRStar", "Chris' kinematic variable", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R("RStar", "Chris' another kinematic variable", RLowerBound, RUpperBound);
   RooRealVar PassTagging("PassTagging", "Event pass b-tagging", -10, 10);
   RooArgSet TreeVarSet(MR, R, PassTagging);

   TString SelectionString;
   if(RequireTagging == true)
      SelectionString = "PassTagging > 0";
   else
      SelectionString = "";
   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet, SelectionString);

   RooRealVar MROffset("MROffset", "offset in MR", -100, -2000, 500);
   RooRealVar R2Offset("R2Offset", "offset in R^2", -0.5, -20, 0.0);

   RooFormulaVar X("X", "MR - MR0", "@0 - @1", RooArgList(MR, MROffset));
   RooFormulaVar Y("Y", "R^2 - R20", "@0 * @0 - @1", RooArgList(R, R2Offset));
   RooRealVar B("B", "B", 0.01, 0.0, 100.0);
   RooFormulaVar XY("XY", "Variable in the function", "@0 * @1 * @2", RooArgList(X, Y, B));

   RooGenericPdf FinalModel("Model", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY));

   RooFitResult *Result = (RooFitResult *)FinalModel.fitTo(Dataset, Save(true));

   RooPlot* ParameterPlot = MR.frame(Bins(50), Name("FitParameters"), Title("Fit parameters!!!!"));
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
}


