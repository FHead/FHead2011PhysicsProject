#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "RooRealVar.h"
#include "RooExponential.h"
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooPlot.h"
using namespace RooFit;

#include "SetStyle.h"
#include "PlotHelper2.h"

#define R2CutSize 8

struct FitResults;
int main();
FitResults FitTree(PsFileHelper &PsFile, TTree *Tree, double MRMinumum, double ISRSize);

struct FitResults
{
   double Exp1Values[R2CutSize];
   double Exp1Errors[R2CutSize];
   double Exp2Values[R2CutSize];
   double Exp2Errors[R2CutSize];
};

int main()
{
   TFile F("output.root");

   PsFileHelper PsFile("FitTree.ps");

   FitResults ResultA = FitTree(PsFile, (TTree *)F.Get("Tree_A"), 400, 0);
   FitResults ResultB = FitTree(PsFile, (TTree *)F.Get("Tree_B"), 500, 30);
   FitResults ResultD = FitTree(PsFile, (TTree *)F.Get("Tree_D"), 600, 90);

   double R2Cuts[R2CutSize] = {0.15, 0.17, 0.19, 0.21, 0.23, 0.25, 0.27, 0.29};
   
   TGraphErrors GraphA1, GraphB1, GraphD1;
   TGraphErrors GraphA2, GraphB2, GraphD2;
   for(int i = 0; i < R2CutSize; i++)
   {
      GraphA1.SetPoint(i, R2Cuts[i], ResultA.Exp1Values[i]);
      GraphA1.SetPointError(i, 0, ResultA.Exp1Errors[i]);
      GraphB1.SetPoint(i, R2Cuts[i], ResultB.Exp1Values[i]);
      GraphB1.SetPointError(i, 0, ResultB.Exp1Errors[i]);
      GraphD1.SetPoint(i, R2Cuts[i], ResultD.Exp1Values[i]);
      GraphD1.SetPointError(i, 0, ResultD.Exp1Errors[i]);
      GraphA2.SetPoint(i, R2Cuts[i], ResultA.Exp2Values[i]);
      GraphA2.SetPointError(i, 0, ResultA.Exp2Errors[i]);
      GraphB2.SetPoint(i, R2Cuts[i], ResultB.Exp2Values[i]);
      GraphB2.SetPointError(i, 0, ResultB.Exp2Errors[i]);
      GraphD2.SetPoint(i, R2Cuts[i], ResultD.Exp2Values[i]);
      GraphD2.SetPointError(i, 0, ResultD.Exp2Errors[i]);
   }

   PsFile.AddTextPage("Summary graphs");

   TCanvas C;

   TH2D HWorld1("HWorld1", "Component slopes;R^{2} cut;Slope", 10, 0.135, 0.305, 10, -0.016, -0.006);
   HWorld1.SetStats(0);
   HWorld1.Draw();
   GraphA1.SetLineColor(kBlack);
   GraphA1.Draw("p");
   GraphB1.SetLineColor(kRed);
   GraphB1.Draw("p");
   GraphD1.SetLineColor(kBlue);
   GraphD1.Draw("p");
   PsFile.AddCanvas(C);
   
   TH2D HWorld2("HWorld2", "Second component slopes;R^{2} cut;Slope", 10, 0.135, 0.305, 10, -0.0065, -0.0035);
   HWorld2.SetStats(0);
   HWorld2.Draw();
   GraphA2.SetLineColor(kBlack);
   GraphA2.Draw("p");
   GraphB2.SetLineColor(kRed);
   GraphB2.Draw("p");
   GraphD2.SetLineColor(kBlue);
   GraphD2.Draw("p");
   PsFile.AddCanvas(C);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}

FitResults FitTree(PsFileHelper &PsFile, TTree *Tree, double MRMinimum, double ISRSize)
{
   PsFile.AddTextPage(Form("Starting to fit to tree with ISR size %f", ISRSize));

   double R2Cuts[R2CutSize] = {0.15, 0.17, 0.19, 0.21, 0.23, 0.25, 0.27, 0.29};

   FitResults Result;

   for(int i = 0; i < R2CutSize; i++)
   {
      PsFile.AddTextPage(Form("Fit tree with R2 cut %.3f", R2Cuts[i]));

      RooRealVar MR("MR", "MR", MRMinimum, 5000);
      RooRealVar R("R", "R", 0, 1);
      RooArgSet TreeVar(MR, R);

      RooDataSet DataSet("DataSet", "DataSet", Tree, TreeVar, Form("R*R > %f", R2Cuts[i]));

      RooRealVar Exp1("Exp1", "Exp1", -0.008, -10.0, 0.0);
      RooExponential Function1("Function1", "Function1", MR, Exp1);
      RooRealVar Exp2("Exp2", "Exp2", -0.005, -10.0, 0.0);
      RooExponential Function2("Function2", "Function2", MR, Exp2);
      RooRealVar Fraction("Fraction", "Fraction", 0.5, 0.0, 1.0);
      RooAddPdf Model("Model", "Model", Function1, Function2, Fraction);

      RooFitResult *FitResult = Model.fitTo(DataSet, Save(true));

      RooPlot *MRFrame = MR.frame(Range(MRMinimum, 3000));
      DataSet.plotOn(MRFrame);
      Model.plotOn(MRFrame);
      MRFrame->SetMinimum(0.5);
      PsFile.AddPlot(MRFrame, "", true);

      Result.Exp1Values[i] = Exp1.getVal();
      Result.Exp1Errors[i] = Exp1.getError();
      Result.Exp2Values[i] = Exp2.getVal();
      Result.Exp2Errors[i] = Exp2.getError();

      if(Result.Exp1Values[i] > Result.Exp2Values[i])
      {
         swap(Result.Exp1Values[i], Result.Exp2Values[i]);
         swap(Result.Exp1Errors[i], Result.Exp2Errors[i]);
      }
   }

   TGraphErrors Graph1, Graph2;
   for(int i = 0; i < R2CutSize; i++)
   {
      Graph1.SetPoint(i, R2Cuts[i], Result.Exp1Values[i]);
      Graph1.SetPointError(i, 0, Result.Exp1Errors[i]);
      Graph2.SetPoint(i, R2Cuts[i], Result.Exp2Values[i]);
      Graph2.SetPointError(i, 0, Result.Exp2Errors[i]);
   }

   PsFile.AddTextPage("Summary Graphs");

   PsFile.AddPlot(Graph1, "ap");
   PsFile.AddPlot(Graph2, "ap");

   return Result;
}




