#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TF1.h"
#include "TTree.h"

#include "PlotHelper2.h"
#include "Code/DrawRandom.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooGenericPdf.h"
using namespace RooFit;

int main()
{
   int N = 1000;
   int T = 1000;

   TFile File("FitResultTree.root", "RECREATE");

   TTree ResultTree("ResultTree", "Result tree");
   double R2YY, R3YY, R2YYError, R3YYError;
   double R2YN, R3YN, R2YNError, R3YNError;
   double R2NY, R3NY, R2NYError, R3NYError;
   ResultTree.Branch("R2YY", &R2YY, "R2YY/D");
   ResultTree.Branch("R3YY", &R3YY, "R3YY/D");
   ResultTree.Branch("R2YYError", &R2YYError, "R2YYError/D");
   ResultTree.Branch("R3YYError", &R3YYError, "R3YYError/D");
   ResultTree.Branch("R2YN", &R2YN, "R2YN/D");
   ResultTree.Branch("R3YN", &R3YN, "R3YN/D");
   ResultTree.Branch("R2YNError", &R2YNError, "R2YNError/D");
   ResultTree.Branch("R3YNError", &R3YNError, "R3YNError/D");
   ResultTree.Branch("R2NY", &R2NY, "R2NY/D");
   ResultTree.Branch("R3NY", &R3NY, "R3NY/D");
   ResultTree.Branch("R2NYError", &R2NYError, "R2NYError/D");
   ResultTree.Branch("R3NYError", &R3NYError, "R3NYError/D");

   PsFileHelper PsFile("Results.ps");

   for(int iT = 0; iT < T; iT++)
   {
      TTree Tree("Tree", "Tree");

      double Sample;
      Tree.Branch("X", &Sample, "X/D");

      TH1D HData("HData", "Data!", 100, 0, 2 * PI);

      for(int iN = 0; iN < N; iN++)
      {
         Sample = DrawRandom(0, 2 * PI);
         while(DrawRandom(0, 399) > 350 - 7 * cos(Sample) + 42 * cos(2 * Sample))
            Sample = DrawRandom(0, 2 * PI);
         Tree.Fill();

         HData.Fill(Sample);
      }

      PsFile.AddPlot(HData);

      string FunctionString = "";
      FunctionString = FunctionString + "1 * 1 * (350 - 7 * cos(X) + 42 * cos(2 * X))";
      FunctionString = FunctionString + "+ A2 * A2 * (32.4 - 0.6 * cos(X) + 7.3 * cos(2 * X))";
      FunctionString = FunctionString + "+ A3 * A3 * (13.3 - 3.1 * cos(2 * X))";
      FunctionString = FunctionString + "+ 1 * A2 * (-178 + 4 * cos(X) - 34 * cos(2 * X))";
      FunctionString = FunctionString + "+ 1 * A3 * (2.2 * sin(X) - 20 * sin(2 * X))";
      FunctionString = FunctionString + "+ A2 * A3 * (-0.3 * sin(X) + 9 * sin(2 * X))";

      RooRealVar X("X", "X", 0, 2 * PI);
      RooRealVar A2("A2", "A2", 0, -100, 100);
      RooRealVar A3("A3", "A3", 0, -100, 100);
      RooDataSet DataSet("DataSet", "DataSet", &Tree, X);
      RooGenericPdf Function("Function", "Function", FunctionString.c_str(), RooArgList(X, A2, A3));

      Function.fitTo(DataSet);

      R2YY = A2.getVal();
      R3YY = A3.getVal();
      R2YYError = A2.getError();
      R3YYError = A3.getError();

      A2.setVal(0);
      A3.setVal(0);
      A2.setConstant(true);
      A3.setConstant(false);

      Function.fitTo(DataSet);
      
      R2NY = A2.getVal();
      R3NY = A3.getVal();
      R2NYError = A2.getError();
      R3NYError = A3.getError();

      A2.setVal(0);
      A3.setVal(0);
      A2.setConstant(false);
      A3.setConstant(true);

      Function.fitTo(DataSet);
      
      R2YN = A2.getVal();
      R3YN = A3.getVal();
      R2YNError = A2.getError();
      R3YNError = A3.getError();

      ResultTree.Fill();
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   ResultTree.Write();
   File.Close();

   return 0;
}





