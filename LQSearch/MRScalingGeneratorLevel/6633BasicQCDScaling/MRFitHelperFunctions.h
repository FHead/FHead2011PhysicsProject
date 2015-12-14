#ifndef MRFitHelperFunctions_H_6631_AJSICVNHAJLRSCGJLICRNHWGLJKRISWCGWCG
#define MRFitHelperFunctions_H_6631_AJSICVNHAJLRSCGJLICRNHWGLJKRISWCGWCG

#include <string>
#include <sstream>
using namespace std;

#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "RooAddPdf.h"
#include "RooAbsPdf.h"
#include "RooPlot.h"
#include "RooDataSet.h"
#include "RooExponential.h"
#include "RooTwoSideGaussianWithAnExponentialTail.h"
#include "RooTwoSideGaussianWithTwoExponentialTails.h"
using namespace RooFit;

#include "PlotHelper2.h"

#define MRFit_Strategy_Normal 100
#define MRFit_Strategy_IgnoreLeft 101
#define MRFit_Strategy_IgnoreGaussian 102

struct MRFitSingleFitResult;
MRFitSingleFitResult FitWithRCut(PsFileHelper *PsFile, string Filename, double RCut,
   string TreeName, string MRBranch, string RBranch,
   double MRLowerBound, double MRUpperBound,
   int Strategy = MRFit_Strategy_Normal, bool DoubleExponential = false,
   bool Optimize = true, int Category = 0);

struct MRFitSingleFitResult
{
   double X0;
   double SigmaL;
   double SigmaR;
   double S;
   double SError;
   double S2;
   double S2Error;
   double Fraction;
   double FractionError;
   bool DoubleExponential;
   int Strategy;
   int CovQual;
};

MRFitSingleFitResult FitWithRCut(PsFileHelper *PsFile, string Filename, double RCut,
   string TreeName, string MRBranch, string RBranch,
   double MRLowerBound, double MRUpperBound,
   int Strategy, bool DoubleExponential, bool Optimize, int Category)
{
   TFile F(Filename.c_str());
   TTree *Tree = (TTree *)F.Get(TreeName.c_str());
   if(Tree == NULL)
      return MRFitSingleFitResult();

   if(Strategy != MRFit_Strategy_Normal
      && Strategy != MRFit_Strategy_IgnoreLeft
      && Strategy != MRFit_Strategy_IgnoreGaussian)
      return MRFitSingleFitResult();
   
   RooRealVar MR(MRBranch.c_str(), "Chris' kinematic variable", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar R(RBranch.c_str(), "Chris' another kinematic variable", -200, 200);
   RooRealVar CategoryVariable("Category", "Boxes", -10000, 10000);
   RooArgSet TreeVarSet(MR, R, CategoryVariable);

   stringstream CutString;
   CutString << RBranch << " > " << RCut;
   if(Category != 0)
      CutString << " && Category < " << Category + 0.001 << " && Category > " << Category - 0.001;

   RooDataSet Dataset("Dataset", "MR Dataset", Tree, TreeVarSet, CutString.str().c_str());

   RooRealVar X0("X0", "gaussian mean", 200, 0, MRUpperBound, "GeV");
   RooRealVar SigmaL("SigmaL", "left-hand side gaussian width", 100, 0, 5000, "GeV");
   RooRealVar SigmaR("SigmaR", "right-hand side gaussian width", 100, 0, 5000, "GeV");
   RooRealVar S("S", "exponent of the tail", 0.12, 0, 1.5);
   RooFormulaVar NegativeS("NegativeS", "Negative S", "-S", RooArgList(S));
   RooRealVar S2("S2", "2nd exponent of the tail", 0.02, 0, 0.5);
   RooFormulaVar NegativeS2("NegativeS2", "Negative S2", "-S2", RooArgList(S2));
   RooRealVar Fraction("Fraction", "Second component fraction", 0.025, 0, 1000);
   RooAbsPdf *Model = NULL;
   RooAbsPdf *SubModel1 = NULL;
   RooAbsPdf *SubModel2 = NULL;
   if(Strategy == MRFit_Strategy_Normal && DoubleExponential == false)
      Model = new RooTwoSideGaussianWithAnExponentialTail("Model", "Model",
         MR, X0, SigmaL, SigmaR, S);
   else if(Strategy == MRFit_Strategy_IgnoreLeft && DoubleExponential == false)
      Model = new RooTwoSideGaussianWithAnExponentialTail("Model", "Model",
         MR, X0, SigmaR, SigmaR, S);
   else if(Strategy == MRFit_Strategy_IgnoreGaussian && DoubleExponential == false)
      Model = new RooExponential("Model", "Model", MR, NegativeS);
   else if(Strategy == MRFit_Strategy_Normal && DoubleExponential == true)
      Model = new RooTwoSideGaussianWithTwoExponentialTails("Model", "Model",
         MR, X0, SigmaL, SigmaR, S, S2, Fraction);
   else if(Strategy == MRFit_Strategy_IgnoreLeft && DoubleExponential == true)
      Model = new RooTwoSideGaussianWithTwoExponentialTails("Model", "Model",
         MR, X0, SigmaR, SigmaR, S, S2, Fraction);
   else if(Strategy == MRFit_Strategy_IgnoreGaussian && DoubleExponential == true)
   {
      SubModel1 = new RooExponential("SubModel1", "SubModel1", MR, NegativeS);
      SubModel2 = new RooExponential("SubModel2", "SubModel2", MR, NegativeS2);
      Model = new RooAddPdf("Model", "Model", *SubModel1, *SubModel2, Fraction);
   }

   if(Model == NULL)
   {
      cerr << "Something terribly wrong has happened.  "
         << "Model is NULL.  Please check what happened." << endl;
      return MRFitSingleFitResult();
   }

   RooFitResult *FitResult = Model->fitTo(Dataset, Save(true));

   if(PsFile != NULL)
   {
      stringstream Subtitle;
      Subtitle << "Fitting with R cut = " << RCut << ", ";

      if(Strategy == MRFit_Strategy_Normal)                Subtitle << "Normal";
      else if(Strategy == MRFit_Strategy_IgnoreLeft)       Subtitle << "Ignore left";
      else if(Strategy == MRFit_Strategy_IgnoreGaussian)   Subtitle << "Exponential";
      
      if(DoubleExponential == true)   Subtitle << " (DoubleExponential)";
      
      PsFile->AddTextPage(Subtitle.str());

      RooPlot *ParameterPlot = MR.frame(Bins(50), Name("FitParameters"),
         Title("Fit parameters"));
      Model->paramOn(ParameterPlot, Format("NELU", AutoPrecision(3)),
         Layout(0.1, 0.4, 0.9));
      PsFile->AddPlot(ParameterPlot, "", false);

      RooPlot *FinalResultPlot = MR.frame(Bins(50), Name("FitResults"),
         Title("MR"), AutoRange(Dataset));
      Dataset.plotOn(FinalResultPlot, MarkerSize(0.9));
      Model->plotOn(FinalResultPlot, LineColor(kBlue));
      PsFile->AddPlot(FinalResultPlot, "", true);
   }

   MRFitSingleFitResult result;

   if(Strategy == MRFit_Strategy_Normal)
   {
      double XC = S.getVal() * SigmaR.getVal() * SigmaR.getVal() + X0.getVal();
      if(DoubleExponential == true)
         XC = (S.getVal() + Fraction.getVal() * S2.getVal()) * SigmaR.getVal() * SigmaR.getVal() + X0.getVal();

      if(MRLowerBound + 0 < X0.getVal())
      {
         result.X0 = X0.getVal();
         result.SigmaL = SigmaL.getVal();
         result.SigmaR = SigmaR.getVal();
         result.S = S.getVal();
         result.SError = S.getError();
         result.Strategy = Strategy;

         if(DoubleExponential == true)
         {
            result.Fraction = Fraction.getVal();
            result.FractionError = Fraction.getError();
            result.S2 = S2.getVal();
            result.S2Error = S2.getError();
         }
         else
         {
            result.Fraction = -1000;
            result.FractionError = -1000;
            result.S2 = -1000;
            result.S2Error = -1000;
         }
      }

      if(MRLowerBound + 0 < XC && MRLowerBound + 0 >= X0.getVal() && Optimize == true)
         return FitWithRCut(PsFile, Filename, RCut, TreeName,
            MRBranch, RBranch, MRLowerBound, MRUpperBound,
            MRFit_Strategy_IgnoreLeft, DoubleExponential, true);
      if(MRLowerBound + 0 >= XC && Optimize == true)
         return FitWithRCut(PsFile, Filename, RCut, TreeName,
            MRBranch, RBranch, MRLowerBound, MRUpperBound,
            MRFit_Strategy_IgnoreGaussian, DoubleExponential, true);
   }

   if(Strategy == MRFit_Strategy_IgnoreLeft)
   {
      double XC = S.getVal() * SigmaR.getVal() * SigmaR.getVal() + X0.getVal();
      if(DoubleExponential == true)
         XC = (S.getVal() + Fraction.getVal() * S2.getVal()) * SigmaR.getVal() * SigmaR.getVal() + X0.getVal();

      if(MRLowerBound + 0 < XC)
      {
         result.X0 = X0.getVal();
         result.SigmaL = SigmaR.getVal();
         result.SigmaR = SigmaR.getVal();
         result.S = S.getVal();
         result.SError = S.getError();
         result.Strategy = Strategy;

         if(DoubleExponential == true)
         {
            result.Fraction = Fraction.getVal();
            result.FractionError = Fraction.getError();
            result.S2 = S2.getVal();
            result.S2Error = S2.getError();
         }
      }

      if(MRLowerBound + 0 >= XC && Optimize == true)
         return FitWithRCut(PsFile, Filename, RCut, TreeName,
            MRBranch, RBranch, MRLowerBound, MRUpperBound,
            MRFit_Strategy_IgnoreGaussian, DoubleExponential, true);
   }

   if(Strategy == MRFit_Strategy_IgnoreGaussian)
   {
      result.X0 = -1000;
      result.SigmaL = -1000;
      result.SigmaR = -1000;
      result.S = -NegativeS.getVal();
      result.SError = S.getError();
      result.Strategy = Strategy;

      if(DoubleExponential == true)
      {
         result.Fraction = 1 - Fraction.getVal();
         result.FractionError = 1 - Fraction.getError();
         result.S2 = -NegativeS2.getVal();
         result.S2Error = S2.getError();
      }
   }

   result.CovQual = FitResult->covQual();

   if(SubModel1 != NULL)
      delete SubModel1;
   if(SubModel2 != NULL)
      delete SubModel2;
   if(Model != NULL)
      delete Model;

   result.DoubleExponential = DoubleExponential;
   return result;
}

#endif

