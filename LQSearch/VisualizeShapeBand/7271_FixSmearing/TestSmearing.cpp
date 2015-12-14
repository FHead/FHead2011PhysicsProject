#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TTree.h"

#include "RooGaussian.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
using namespace RooFit;

#include "PlotHelper2.h"
#include "DrawRandom.h"

int main()
{
   RooRealVar InputMean("InputMean", "InputMean", 0);
   RooRealVar InputError("InputError", "InputError", 1);
   RooRealVar X("X", "X", -20, 20);
   RooGaussian Input("Input", "Input", X, InputMean, InputError);

   RooDataSet *dataset = (RooDataSet *)Input.generate(RooArgSet(X), 100);

   dataset->Print();
   
   RooRealVar Mean("Mean", "InputMean", 0, -10, 10);
   RooRealVar Error("Error", "InputError", 1, 0, 100);
   RooGaussian Result("Result", "Result", X, Mean, Error);
   RooFitResult *FitResult = (RooFitResult *)Result.fitTo(*dataset, Save(true));

   TH1D HMean("HMean", "Mean of the generated Gaussian", 100, -1, 1);

   for(int i = 0; i < 1000; i++)
   {
      RooDataSet *newdataset = (RooDataSet *)Result.generate(RooArgSet(X), 100);

      TTree *Tree = (TTree *)newdataset->tree();

      double x = 0;
      Tree->SetBranchAddress("X", &x);

      double sum = 0;
      double EntryCount = Tree->GetEntries();
      for(int j = 0; j < Tree->GetEntries(); j++)
      {
         Tree->GetEntry(j);
         sum = sum + x;
      }

      HMean.Fill(sum / EntryCount);
   }

   TH1D HMeanRandomized("HMeanRandomized", "Mean of the generated Gaussian (randomized)", 100, -1, 1);

   for(int i = 0; i < 1000; i++)
   {
      FitResult->randomizePars();

      RooDataSet *newdataset = (RooDataSet *)Result.generate(RooArgSet(X), 100);

      TTree *Tree = (TTree *)newdataset->tree();

      double x = 0;
      Tree->SetBranchAddress("X", &x);

      double sum = 0;
      double EntryCount = Tree->GetEntries();
      for(int j = 0; j < Tree->GetEntries(); j++)
      {
         Tree->GetEntry(j);
         sum = sum + x;
      }

      HMeanRandomized.Fill(sum / EntryCount);
   }

   TH1D HMeanRandomizedAndSet("HMeanRandomizedAndSet",
      "Mean of the generated Gaussian (randomized and set)", 100, -1, 1);

   for(int i = 0; i < 1000; i++)
   {
      const RooArgList Parameters = FitResult->randomizePars();
      Mean.setVal(((RooAbsReal *)Parameters.find("Mean"))->getVal());
      Error.setVal(((RooAbsReal *)Parameters.find("Error"))->getVal());

      RooDataSet *newdataset = (RooDataSet *)Result.generate(RooArgSet(X), 100);

      TTree *Tree = (TTree *)newdataset->tree();

      double x = 0;
      Tree->SetBranchAddress("X", &x);

      double sum = 0;
      double EntryCount = Tree->GetEntries();
      for(int j = 0; j < Tree->GetEntries(); j++)
      {
         Tree->GetEntry(j);
         sum = sum + x;
      }

      HMeanRandomizedAndSet.Fill(sum / EntryCount);
   }
   
   TH1D HMeanRandomizedAndSmear("HMeanRandomizedAndSmear",
      "Mean of the generated Gaussian (randomized and smeared)", 100, -1, 1);

   for(int i = 0; i < 1000; i++)
   {
      const RooArgList Parameters = FitResult->randomizePars();
      Mean.setVal(((RooAbsReal *)Parameters.find("Mean"))->getVal() + DrawGaussian(0.5));
      Error.setVal(((RooAbsReal *)Parameters.find("Error"))->getVal() + DrawGaussian(0.1));

      RooDataSet *newdataset = (RooDataSet *)Result.generate(RooArgSet(X), 100);

      TTree *Tree = (TTree *)newdataset->tree();

      double x = 0;
      Tree->SetBranchAddress("X", &x);

      double sum = 0;
      double EntryCount = Tree->GetEntries();
      for(int j = 0; j < Tree->GetEntries(); j++)
      {
         Tree->GetEntry(j);
         sum = sum + x;
      }

      HMeanRandomizedAndSmear.Fill(sum / EntryCount);
   }

   PsFileHelper PsFile("TestSmearing.ps");

   PsFile.AddPlot(HMean, "", false);
   PsFile.AddPlot(HMeanRandomized, "", false);
   PsFile.AddPlot(HMeanRandomizedAndSet, "", false);
   PsFile.AddPlot(HMeanRandomizedAndSmear, "", false);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}






