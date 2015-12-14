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
void TwoDimensionalSimpleFit(PsFileHelper &PsFile, string FileName, double Jet1TCHELimit, double Jet2TCHELimit,
   DataHelper &DHFile, string State);

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

   DataHelper DHFile("CollectResult.dh");
   DataHelper DHFile2("CollectResult2.dh");

   PsFileHelper PsFile("StudyOfBTagging.ps");

   PsFile.AddTextPage("Fit to whole MC sample!");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", -1000, -1000, DHFile, "All");
   
   PsFile.AddTextPage("BTagging, leading jet, TCHE > 0");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 0, -1000, DHFile, "Jet1 0.0");
   
   PsFile.AddTextPage("BTagging, leading jet, TCHE > 1");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 1, -1000, DHFile, "Jet1 1.0");
   
   PsFile.AddTextPage("BTagging, leading jet, TCHE > 1.5");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 1.5, -1000, DHFile, "Jet1 1.5");
   
   PsFile.AddTextPage("BTagging, leading jet, TCHE > 2");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 2, -1000, DHFile, "Jet1 2.0");
   
   PsFile.AddTextPage("BTagging, leading jet, TCHE > 2.5");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 2.5, -1000, DHFile, "Jet1 2.5");
   
   PsFile.AddTextPage("BTagging, leading jet, TCHE > 3.3");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 3.3, -1000, DHFile, "Jet1 3.3");
   
   PsFile.AddTextPage("BTagging, leading jet, TCHE > 4");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 4, -1000, DHFile, "Jet1 4");
   
   PsFile.AddTextPage("BTagging, leading jet, TCHE > 4.5");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 4.5, -1000, DHFile, "Jet1 4.5");
   
   PsFile.AddTextPage("BTagging, leading jet, TCHE > 5");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 5, -1000, DHFile, "Jet1 5.0");
  
   PsFile.AddTextPage("BTagging, both jet, TCHE > 0");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 0, 0, DHFile2, "Jet1 0.0, Jet2 0.0");
   
   PsFile.AddTextPage("BTagging, both jet, TCHE > 1");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 1, 1, DHFile2, "Jet1 1.0, Jet2 1.0");
   
   PsFile.AddTextPage("BTagging, both jet, TCHE > 2");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 2, 2, DHFile2, "Jet1 2.0, Jet2 2.0");
   
   PsFile.AddTextPage("BTagging, both jet, TCHE > 3.3");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 3.3, 3.3, DHFile2, "Jet1 3.3, Jet2 3.3");
   
   PsFile.AddTextPage("BTagging, both jet, TCHE > 5");
   TwoDimensionalSimpleFit(PsFile, "TTJets_TuneD6T_MRTree.root", 5, 5, DHFile2, "Jet1 5.0, Jet2 5.0");
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   DHFile.SaveToFile("CollectResult.dh");
   DHFile2.SaveToFile("CollectResult2.dh");
}

void TwoDimensionalSimpleFit(PsFileHelper &PsFile, string FileName, double Jet1TCHELimit, double Jet2TCHELimit,
   DataHelper &DHFile, string State)
{
   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("MRTree");
   if(Tree == NULL)
      return;
   
   double MRLowerBound = 400;
   double MRUpperBound = 1500;
   double RLowerBound = 0.30;
   double RUpperBound = 1;

   RooRealVar MR("GroupPFMR", "Chris' kinematic variable", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R("GroupPFR", "Chris' another kinematic variable", RLowerBound, RUpperBound);
   RooRealVar Jet1TCHE("Jet1TCHE", "TCHE tag", -100000, 100000);
   RooRealVar Jet2TCHE("Jet2TCHE", "TCHE tag", -100000, 100000);
   RooArgSet TreeVarSet(MR, R, Jet1TCHE, Jet2TCHE);

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet,
      Form("Jet1TCHE > %f && Jet2TCHE > %f", Jet1TCHELimit, Jet2TCHELimit));

   RooRealVar MROffset("MROffset", "offset in MR", -450, -1000, MRLowerBound);
   RooRealVar R2Offset("R2Offset", "offset in R^2", -0.2, -10, RLowerBound * RLowerBound);

   RooFormulaVar X("X", "MR - MR0", "@0 - @1", RooArgList(MR, MROffset));
   RooFormulaVar Y("Y", "R^2 - R20", "@0 * @0 - @1", RooArgList(R, R2Offset));
   RooRealVar B("B", "B", 0.06, 0.0, 100.0);
   RooFormulaVar XY("XY", "Variable in the function", "@0 * @1 * @2", RooArgList(X, Y, B));

   RooGenericPdf FinalModel("Model", "Title", "(@0 - 1) * exp(-@0)", RooArgList(XY));

   RooFitResult *Result = (RooFitResult *)FinalModel.fitTo(Dataset, Save(true));

   TH2F DataHistogram("DataHistogram", "Data!;MR;R", 25, 350, 1500, 25, 0.3, 1);
   Dataset.fillHistogram(&DataHistogram, RooArgList(MR, R));
   TCanvas DataCanvas;
   DataHistogram.SetMinimum(0.5);
   DataHistogram.Draw("lego");
   DataCanvas.SetLogz();
   DataCanvas.SetTheta(35);
   DataCanvas.SetPhi(145);
   PsFile.AddCanvas(DataCanvas);
   
   TH2F ModelHistogram("ModelHistogram", "Model!;MR;R", 25, 400, 1500, 25, 0.3, 1);
   FinalModel.fillHistogram(&ModelHistogram, RooArgList(MR, R), Dataset.sumEntries());
   TCanvas ModelCanvas;
   ModelHistogram.SetMinimum(0.5);
   ModelHistogram.Draw("surf");
   ModelCanvas.SetLogz();
   ModelCanvas.SetTheta(35);
   ModelCanvas.SetPhi(145);
   PsFile.AddCanvas(ModelCanvas);

   TH2F ResidualHistogram("ResidualHistogram", "Residual!;MR;R", 25, 400, 1500, 25, 0.3, 1);
   Dataset.fillHistogram(&ResidualHistogram, RooArgList(MR, R));
   ResidualHistogram.Add(&ModelHistogram, -1);
   PsFile.AddPlot(ResidualHistogram, "colz", false, false);
   
   TCanvas ResidualCanvas;
   ResidualHistogram.Draw("lego");
   ResidualCanvas.SetTheta(35);
   ResidualCanvas.SetPhi(145);
   PsFile.AddCanvas(ResidualCanvas);

   RooPlot *ParameterPlot = MR.frame(Bins(50), Name("FitParameters"), Title("Fit parameters"));
   FinalModel.paramOn(ParameterPlot, Format("NELU", AutoPrecision(3)), Layout(0.1, 0.4, 0.9));
   PsFile.AddPlot(ParameterPlot);

   DHFile[State]["B"] = B.getVal();
   DHFile[State]["BError"] = B.getError();
   DHFile[State]["MROffset"] = MROffset.getVal();
   DHFile[State]["MROffsetError"] = MROffset.getError();
   DHFile[State]["R2Offset"] = R2Offset.getVal();
   DHFile[State]["R2OffsetError"] = R2Offset.getError();

   DHFile[State]["Jet1TCHELimit"] = Jet1TCHELimit;
   DHFile[State]["Jet2TCHELimit"] = Jet2TCHELimit;
}


