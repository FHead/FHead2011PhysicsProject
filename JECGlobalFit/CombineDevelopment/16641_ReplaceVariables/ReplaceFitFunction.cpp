#include <iostream>
using namespace std;

#include "TFile.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooWorkspace.h"
#include "RooFormulaVar.h"
using namespace RooFit;

int main()
{
   TFile InputFile("CombineWorkspace.root");

   int N = 8;
   int PTValue[] = {50, 75, 100, 120, 140, 160, 180, 200};

   RooWorkspace *W = (RooWorkspace *)InputFile.Get("W");
   
   RooRealVar P0("P0", "P0", 1.0, -20, 20);
   RooRealVar P1("P1", "P1", 0.0, -20, 20);
   RooRealVar P2("P2", "P2", 0.0, -20, 20);
   RooRealVar P3("P3", "P3", 0.0, -20, 20);
   RooRealVar R0("R0", "R0", 1.0, -20, 20);
   RooRealVar R1("R1", "R1", 0.0, -20, 20);
   RooRealVar R2("R2", "R2", 0.0, -20, 20);
   RooRealVar R3("R3", "R3", 0.0, -20, 20);

   /*
   W->import(P0);
   W->import(P1);
   W->import(P2);
   W->import(P3);
   W->import(R0);
   W->import(R1);
   W->import(R2);
   W->import(R3);
   */

   for(int i = 0; i < 8; i++)
   {
      int PT = PTValue[i];

      RooFormulaVar R(Form("MethodT_%d_0_RMean", PT), "R",
         Form("@0+@1*%d+@2*%d*%d+@3*%d*%d*%d", PT, PT, PT, PT, PT, PT), RooArgList(P0, P1, P2, P3));
      RooFormulaVar RR(Form("MethodT_%d_0_RSigma", PT), "R",
         Form("@0+@1*%d+@2*%d*%d+@3*%d*%d*%d", PT, PT, PT, PT, PT, PT), RooArgList(R0, R1, R2, R3));

      RooRealVar *MeanMC = (RooRealVar *)W->var(Form("MethodT_%d_0_MC_Mean", PT));
      RooRealVar *SigmaMC = (RooRealVar *)W->var(Form("MethodT_%d_0_MC_Sigma", PT));

      RooFormulaVar MeanData(Form("MethodT_%d_0_Data_MeanFit", PT), "data mean", "@0*@1", RooArgList(*MeanMC, R));
      RooFormulaVar SigmaData(Form("MethodT_%d_0_Data_SigmaFit", PT), "data Sigma", "@0*@1", RooArgList(*SigmaMC, RR));

      W->import(MeanData);
      W->import(SigmaData);
      W->factory(Form("EDIT::MethodT_%d_0_Data_ModelFit(MethodT_%d_0_Data_Model,MethodT_%d_0_Data_Mean=MethodT_%d_0_Data_MeanFit,MethodT_%d_0_Data_Sigma=MethodT_%d_0_Data_SigmaFit)", PT, PT, PT, PT, PT, PT));
   }

   W->writeToFile("ReplacedCombineWorkspace.root");

   InputFile.Close();

   return 0;
}
