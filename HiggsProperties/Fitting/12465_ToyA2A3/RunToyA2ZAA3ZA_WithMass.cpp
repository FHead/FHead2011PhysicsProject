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
   int N = 25;
   int T = 2500;
   double Delta = 0.94;

   TFile File("FitResultTree.root", "RECREATE");

   TTree ResultTree("ResultTree", "Result tree");
   double R2YY, R3YY, R2YYError, R3YYError;
   double R2YN, R3YN, R2YNError, R3YNError;
   double R2NY, R3NY, R2NYError, R3NYError;
   double StatusYY, StatusYN, StatusNY;
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
   ResultTree.Branch("StatusYY", &StatusYY, "StatusYY/D");
   ResultTree.Branch("StatusYN", &StatusYN, "StatusYN/D");
   ResultTree.Branch("StatusNY", &StatusNY, "StatusNY/D");

   PsFileHelper PsFile("Results.ps");

   for(int iT = 0; iT < T; iT++)
   {
      TTree Tree("Tree", "Tree");

      double Sample, SampleM;
      Tree.Branch("X", &Sample, "X/D");
      Tree.Branch("M", &SampleM, "M/D");

      TH1D HData("HData", "Data!", 100, 0, 2 * PI);

      for(int iN = 0; iN < N; iN++)
      {
         Sample = DrawRandom(0, 2 * PI);
         while(DrawRandom(0, 399) > 350 - 7 * cos(Sample) + 42 * cos(2 * Sample))
            Sample = DrawRandom(0, 2 * PI);

         SampleM = DrawRandom(0, 1);
         while(DrawRandom(0, 1 + Delta) > (1 - Delta) + 2 * Delta * SampleM)
            SampleM = DrawRandom(0, 1);

         Tree.Fill();

         HData.Fill(Sample);
      }

      PsFile.AddPlot(HData);

      string FunctionString = "";
      FunctionString = FunctionString + "1 * 1 * (350 - 7 * cos(X) + 42 * cos(2 * X))"
         + " * " + Form("(1 - %f) + 2 * %f * M", Delta, Delta);
      FunctionString = FunctionString + "+ A2 * A2 * (356.8 - 1.4 * cos(X) + 9.8 * cos(2 * X)) * 100"
         + " * " + Form("(1 + %f) - 2 * %f * M", Delta, Delta);
      FunctionString = FunctionString + "+ A3 * A3 * (284.9 - 76.6 * cos(2 * X)) * 100"
         + " * " + Form("(1 + %f) - 2 * %f * M", Delta, Delta);
      FunctionString = FunctionString + "+ 1 * A2 * (300.5 - 821.4 * cos(X) + 52.6 * cos(2 * X))";
      FunctionString = FunctionString + "+ 1 * A3 * (-569 * sin(X) + 39.9 * sin(2 * X))";
      FunctionString = FunctionString + "+ A2 * A3 * (171.8 * sin(2 * X)) * 100";

      RooRealVar X("X", "X", 0, 2 * PI);
      RooRealVar M("M", "M", 0, 1);
      RooRealVar A2("A2", "A2", 0, -100, 100);
      RooRealVar A3("A3", "A3", 0, -100, 100);
      RooDataSet DataSet("DataSet", "DataSet", &Tree, RooArgSet(X, M));
      RooGenericPdf Function("Function", "Function", FunctionString.c_str(), RooArgList(X, M, A2, A3));

      RooFitResult *ResultYY = Function.fitTo(DataSet, Save(true));

      R2YY = A2.getVal();
      R3YY = A3.getVal();
      R2YYError = A2.getError();
      R3YYError = A3.getError();
      StatusYY = ResultYY->covQual();

      A2.setVal(0);
      A3.setVal(0);
      A2.setConstant(true);
      A3.setConstant(false);

      Function.fitTo(DataSet);
      RooFitResult *ResultNY = Function.fitTo(DataSet, Save(true));
      
      R2NY = A2.getVal();
      R3NY = A3.getVal();
      R2NYError = A2.getError();
      R3NYError = A3.getError();
      StatusNY = ResultNY->covQual();

      A2.setVal(0);
      A3.setVal(0);
      A2.setConstant(false);
      A3.setConstant(true);

      RooFitResult *ResultYN = Function.fitTo(DataSet, Save(true));
      
      R2YN = A2.getVal();
      R3YN = A3.getVal();
      R2YNError = A2.getError();
      R3YNError = A3.getError();
      StatusYN = ResultYN->covQual();

      ResultTree.Fill();

      delete ResultYY;
      delete ResultNY;
      delete ResultYN;
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   ResultTree.Write();
   File.Close();

   return 0;
}





