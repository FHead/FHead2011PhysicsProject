#include <iostream>
using namespace std;

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooWorkspace.h"
#include "RooFormulaVar.h"
#include "RooPolynomial.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH1.h"
using namespace RooFit;

int main()
{
   TFile InputFile("ToyInput.root");

   int N = 8;
   int PTValue[] = {50, 75, 100, 120, 140, 160, 180, 200};

   RooWorkspace W("W", "Workspace");

   // Variables to use
   RooRealVar x("x", "x", 0.0, 2.0);
   RooRealVar PT("PT", "PT", 0, 500);

   // Function to model the ratio
   RooRealVar P0Temp("P0Temp", "P0Temp", 1.0, -20, 20);
   RooRealVar P1Temp("P1Temp", "P1Temp", 0.0, -20, 20);
   RooRealVar P2Temp("P2Temp", "P2Temp", 0.0, -20, 20);
   RooRealVar R0Temp("R0Temp", "R0Temp", 1.0, -20, 20);
   RooRealVar R1Temp("R1Temp", "R1Temp", 0.0, -20, 20);
   RooRealVar R2Temp("R2Temp", "R2Temp", 0.0, -20, 20);

   // Create necessary RooHist's
   for(int i = 0; i < 8; i++)
   {
      TH1D *H = (TH1D *)InputFile.Get(Form("MethodT_%d_0_Data", PTValue[i]));
      RooDataHist D(H->GetName(), H->GetTitle(), RooArgSet(x), Import(*H, kFALSE));
      W.import(D);
   }
   for(int i = 0; i < 8; i++)
   {
      TH1D *H = (TH1D *)InputFile.Get(Form("MethodT_%d_0_MC", PTValue[i]));
      RooDataHist D(H->GetName(), H->GetTitle(), RooArgSet(x), Import(*H, kFALSE));
      W.import(D);
   }

   // Create necessary RooGaussian's
   for(int i = 0; i < 8; i++)
   {
      RooFormulaVar R(Form("MethodT_%d_0_TempRMean", PTValue[i]), "R",
         Form("@0+@1*%d+@2*%d*%d", PTValue[i], PTValue[i], PTValue[i]), RooArgList(P0Temp, P1Temp, P2Temp));
      RooFormulaVar RR(Form("MethodT_%d_0_TempRSigma", PTValue[i]), "R",
         Form("@0+@1*%d+@2*%d*%d", PTValue[i], PTValue[i], PTValue[i]), RooArgList(R0Temp, R1Temp, R2Temp));

      RooRealVar MeanMC(Form("MethodT_%d_0_MC_Mean", PTValue[i]), "MC mean", 1.0, 0.0, 2.0);
      RooFormulaVar MeanData(Form("MethodT_%d_0_Data_Mean", PTValue[i]), "data mean", "@0*@1", RooArgList(MeanMC, R));
      RooRealVar SigmaMC(Form("MethodT_%d_0_MC_Sigma", PTValue[i]), "MC sigma", 1.0, 0.0, 2.0);
      RooFormulaVar SigmaData(Form("MethodT_%d_0_Data_Sigma", PTValue[i]), "data mean", "@0*@1", RooArgList(SigmaMC, RR));
      RooGaussian ModelMC(Form("MethodT_%d_0_MC_Model", PTValue[i]), "MC model", x, MeanMC, SigmaMC);
      RooGaussian ModelData(Form("MethodT_%d_0_Data_Model", PTValue[i]), "data model", x, MeanData, SigmaData);

      W.import(ModelMC);
      W.import(ModelData);
   }

   // Create background shapes
   for(int i = 0; i < 8; i++)
   {
      RooRealVar BackgroundMC(Form("MethodT_%d_0_MC_Background", PTValue[i]), "Background level", 1);
      RooRealVar BackgroundData(Form("MethodT_%d_0_Data_Background", PTValue[i]), "Background level", 1);

      RooPolynomial ModelMC(Form("MethodT_%d_0_MC_BackgroundModel", PTValue[i]), "", x, RooArgList(BackgroundMC));
      RooPolynomial ModelData(Form("MethodT_%d_0_Data_BackgroundModel", PTValue[i]), "", x, RooArgList(BackgroundData));

      W.import(ModelMC);
      W.import(ModelData);
   }

   W.writeToFile("CombineWorkspace.root");

   InputFile.Close();

   return 0;
}







