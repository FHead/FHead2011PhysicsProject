#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraphErrors.h"

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

int main();
void FitTree(PsFileHelper &PsFile, TTree *Tree, double DecayConstant);

int main()
{
   TFile F("output.root");

   PsFileHelper PsFile("FitTree.ps");

   // FitTree(PsFile, (TTree *)F.Get("Tree_A"), 0.1);
   // FitTree(PsFile, (TTree *)F.Get("Tree_B"), 0.25);
   FitTree(PsFile, (TTree *)F.Get("Tree_C"), 0.5);
   // FitTree(PsFile, (TTree *)F.Get("Tree_D"), 1);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}

void FitTree(PsFileHelper &PsFile, TTree *Tree, double DecayConstant)
{
   PsFile.AddTextPage(Form("Starting to fit to tree with decay constant %.3f", DecayConstant));

   double R2Cuts[9] = {0.25, 0.275, 0.3, 0.325, 0.35, 0.375, 0.4, 0.425, 0.45};

   double Exp1Values[9] = {0};
   double Exp1Errors[9] = {0};
   double Exp2Values[9] = {0};
   double Exp2Errors[9] = {0};

   for(int i = 0; i < 9; i++)
   {
      PsFile.AddTextPage(Form("Fit tree with R2 cut %.2f", R2Cuts[i]));

      RooRealVar MR("MR", "MR", 400, 5000);
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

      RooPlot *MRFrame = MR.frame(Range(400, 3000));
      DataSet.plotOn(MRFrame);
      Model.plotOn(MRFrame);
      MRFrame->SetMinimum(0.5);
      PsFile.AddPlot(MRFrame, "", true);

      Exp1Values[i] = Exp1.getVal();
      Exp1Errors[i] = Exp1.getError();
      Exp2Values[i] = Exp2.getVal();
      Exp2Errors[i] = Exp2.getError();

      if(Exp1Values[i] > Exp2Values[i])
      {
         swap(Exp1Values[i], Exp2Values[i]);
         swap(Exp1Errors[i], Exp2Errors[i]);
      }
   }

   TGraphErrors Graph1, Graph2;
   for(int i = 0; i < 9; i++)
   {
      Graph1.SetPoint(i, R2Cuts[i], Exp1Values[i]);
      Graph1.SetPointError(i, 0, Exp1Errors[i]);
      Graph2.SetPoint(i, R2Cuts[i], Exp2Values[i]);
      Graph2.SetPointError(i, 0, Exp2Errors[i]);
   }

   PsFile.AddTextPage("Summary Graphs");

   PsFile.AddPlot(Graph1, "ap");
   PsFile.AddPlot(Graph2, "ap");
}




