#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooFormulaVar.h"
#include "RooArgSet.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"

int main()
{
   RooRealVar Status("Status", "Status", 0, 3);
   RooRealVar Sem("Sem", "Sem", 0, 100000);

   RooRealVar ThetaZX("ThetaZX", "ThetaZX", -1000, 1000);
   RooRealVar PhiZX("PhiZX", "PhiZX", -1000, 1000);
   RooRealVar ThetaZZ("ThetaZZ", "ThetaZZ", -1000, 1000);
   RooRealVar PhiZZ("PhiZZ", "PhiZZ", -1000, 1000);
   RooRealVar ThetaZA("ThetaZA", "ThetaZA", -1000, 1000);
   RooRealVar ThetaAA("ThetaAA", "ThetaAA", -1000, 1000);

   RooFormulaVar AZZ("AZZ", "cos(ThetaZX)*cos(PhiZX)", RooArgSet(ThetaZX, PhiZX));
   RooFormulaVar AZA("AZA", "cos(ThetaZX)*sin(PhiZX)", RooArgSet(ThetaZX, PhiZX));
   RooFormulaVar AAA("AAA", "sin(ThetaZX)", RooArgSet(ThetaZX));

   RooFormulaVar A1ZZ("A1ZZ", "AZZ*cos(ThetaZZ)*cos(PhiZZ)", RooArgSet(AZZ, ThetaZZ, PhiZZ));
   RooFormulaVar A2ZZ("A2ZZ", "AZZ*cos(ThetaZZ)*sin(PhiZZ)", RooArgSet(AZZ, ThetaZZ, PhiZZ));
   RooFormulaVar A3ZZ("A3ZZ", "AZZ*sin(ThetaZZ)", RooArgSet(AZZ, ThetaZZ));
   RooFormulaVar A2ZA("A2ZA", "AZA*cos(ThetaZA)", RooArgSet(AZA, ThetaZA));
   RooFormulaVar A3ZA("A3ZA", "AZA*sin(ThetaZA)", RooArgSet(AZA, ThetaZA));
   RooFormulaVar A2AA("A2AA", "AAA*cos(ThetaAA)", RooArgSet(AAA, ThetaAA));
   RooFormulaVar A3AA("A3AA", "AAA*sin(ThetaAA)", RooArgSet(AAA, ThetaAA));

   RooRealVar Mean("Mean", "Mean", 0.2, 0, 1);
   RooRealVar Sigma("Sigma", "Sigma", 0.2, 0, 10000);
   RooFormulaVar ReflectedMean1("ReflectedMean1", "-Mean", RooArgSet(Mean));
   RooFormulaVar ReflectedMean2("ReflectedMean2", "2 - Mean", RooArgSet(Mean));

   RooRealVar Const1("Const1", "Const1", 1);
   RooRealVar Const2("Const2", "Const2", 1);
   RooRealVar Const3("Const3", "Const3", 1);

   RooGaussian Gauss1("Gauss1", "Gauss1", A3AA, Mean, Sigma);
   RooGaussian Gauss2("Gauss2", "Gauss2", A3AA, ReflectedMean1, Sigma);
   RooGaussian Gauss3("Gauss3", "Gauss3", A3AA, ReflectedMean2, Sigma);
   RooAddPdf Model("Model", "Model", RooArgList(Gauss1, Gauss2, Gauss3), RooArgList(Const1, Const2, Const3));

   TFile File("OutputFile_8.root");
   TTree *Tree = (TTree *)File.Get("ResultTree");

   RooDataSet Dataset("Dataset", "Dataset", Tree,
      RooArgSet(ThetaZX, PhiZX, ThetaZZ, PhiZZ, ThetaZA, ThetaAA, Status, Sem),
      "Sem == 1000 && Status == 3");

   Model.fitTo(Dataset);

   File.Close();

   return 0;
}




