#include <algorithm>
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
#include "RooPlot.h"

#include "PlotHelper2.h"
#include "Code/DrawRandom.h"

int main();
double GetEffectiveSigma(double Sigma1, double Sigma2, double Coefficient);

int main()
{
   TFile File("ReducedTree.root");
   TTree *Tree = (TTree *)File.Get("Tree");

   PsFileHelper PsFile("SigmaResult.ps");
   PsFile.AddTextPage("Sigmas");

   double EffectiveSigma[20][7] = {0};
   int EventCount[20] = {30, 40, 50, 70, 85,
      100, 150, 200, 250, 300,
      400, 500, 600, 700, 850,
      1000, 1500, 2000, 2500, 3000};
   string Components[7] = {"A1ZZ", "A2ZZ", "A3ZZ", "A2ZA", "A3ZA", "A2AA", "A3AA"};

   for(int j = 6; j < 7; j++)
   {
      PsFile.AddTextPage(("Plots for " + Components[j]).c_str());
      for(int i = 0; i < 20; i++)
      {
         RooRealVar Status("Status", "Status", 0, 3);
         RooRealVar Sem("Sem", "Sem", 0, 100000);
         RooRealVar See("See", "See", 0, 100000);

         RooRealVar AX(Components[j].c_str(), "", -1, 1);

         double Mean1Min = 0, Mean1Max = 1, Mean1Initial = 0.014;
         double Mean2Min = -1, Mean2Max = 0, Mean2Initial = -0.014;
         // if(Components[j] == "A3ZZ")
         // {
         //    Mean1Min = 0, Mean1Max = 1, Mean1Initial = 0.95;
         //    Mean2Min = 1, Mean2Max = 2, Mean2Initial = 1.05;
         // }

         RooRealVar Mean1("Mean1", "Mean1", Mean1Initial, Mean1Min, Mean1Max);
         RooRealVar Mean2("Mean2", "Mean2", Mean2Initial, Mean2Min, Mean2Max);
         RooRealVar SigmaA("SigmaA", "SigmaA", 0.002 / pow(EventCount[i] / 1000.0, 0.5), 0.0001, 10);
         RooRealVar SigmaB("SigmaB", "SigmaB", 0.005 / pow(EventCount[i] / 1000.0, 0.5), 0.0001, 10);
         RooFormulaVar ReflectedMean1("ReflectedMean1", "-Mean1", RooArgSet(Mean1));

         RooRealVar ConstAB("ConstAB", "ConstAB", 0.25, 0, 1);
         RooRealVar Const1("Const1", "Const1", 0.5);

         RooGaussian Gauss1A("Gauss1A", "Gauss1A", AX, Mean1, SigmaA);
         RooGaussian Gauss1B("Gauss1B", "Gauss1B", AX, Mean1, SigmaB);
         RooGaussian Gauss2A("Gauss2A", "Gauss2A", AX, ReflectedMean1, SigmaA);
         RooGaussian Gauss2B("Gauss2B", "Gauss2B", AX, ReflectedMean1, SigmaB);

         RooAddPdf Gauss1("Gauss1", "Gauss1", Gauss1A, Gauss1B, ConstAB);
         RooAddPdf Gauss2("Gauss2", "Gauss2", Gauss2A, Gauss2B, ConstAB);
         RooAddPdf Model("Model", "Model", Gauss1, Gauss2, Const1);

         RooDataSet Dataset("Dataset", "Dataset", Tree,
            RooArgSet(AX, Status, Sem, See),
            Form("Sem + See == %d && Status == 3", EventCount[i]));

         Model.fitTo(Dataset);

         RooPlot *Plot = AX.frame(RooFit::Range(-0.05, 0.05));
         Dataset.plotOn(Plot);
         Model.plotOn(Plot);
         PsFile.AddPlot(Plot);

         EffectiveSigma[i][j] = GetEffectiveSigma(SigmaA.getVal(), SigmaB.getVal(), ConstAB.getVal());
         cout << "SigmaA = " << SigmaA.getVal() << endl;
         cout << "SigmaB = " << SigmaB.getVal() << endl;
         cout << "ConstAB = " << ConstAB.getVal() << endl;
      }
   }

   for(int j = 0; j < 7; j++)
   {
      cout << Components[j] << endl;
      for(int i = 0; i < 20; i++)
         cout << EventCount[i] << " " << EffectiveSigma[i][j] << endl;
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   File.Close();

   return 0;
}

double GetEffectiveSigma(double Sigma1, double Sigma2, double Coefficient)
{
   vector<double> Samples(100000);

   for(int i = 0; i < 100000; i++)
   {
      double Value;
      if(DrawRandom(0, 1) < Coefficient)
         Value = fabs(DrawGaussian(0, Sigma1));
      else
         Value = fabs(DrawGaussian(0, Sigma2));

      Samples[i] = Value;
   }

   sort(Samples.begin(), Samples.end());

   return Samples[100000*0.68];
}



