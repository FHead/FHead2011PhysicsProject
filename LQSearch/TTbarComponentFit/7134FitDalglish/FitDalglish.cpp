#include <string>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"

#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooFormulaVar.h"
#include "RooDataSet.h"
#include "RooGenericPdf.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
using namespace RooFit;

#include "PlotHelper2.h"
#include "DrawRandom.h"
#include "SetStyle.h"

#include "RooDalglish.h"

int main();
double GetPercentage(double Base, double Test);

int main()
{
   SetStyle();

   TFile F("TTbarReducedTree.root");
   TTree *Tree = (TTree *)F.Get("OutputTree");
   if(Tree == NULL)
      return -1;

   double MRLowerBound = 300;
   double RLowerBound = 0.3;

   RooRealVar MR("GammaMRStar", "Chris' kinematic variable", MRLowerBound, 1500, "GeV");
   RooRealVar R("RStar", "Chris' another kinematic variable", RLowerBound, 1.0);
   RooRealVar MCCategory("MCCategory", "MCCategory", -1000, 1000);
   RooFormulaVar RSquared("RSquared", "@0 * @0", RooArgList(R));
   RooArgSet TreeVarSet(MR, R, MCCategory);
   RooDataSet Dataset("Dataset", "Dataset!!!!!!", Tree, TreeVarSet);

   // contants that are not used....
   RooRealVar SigmaX("SigmaX", "SigmaX", 0);
   RooRealVar SigmaY("SigmaY", "SigmaY", 0);
   RooRealVar XOFF("XOFF", "XOFF", 0);
   RooRealVar YOFF("YOFF", "YOFF", 0);

   // component 1
   RooRealVar XHat1("XHat1", "XHat1", 121.471, -1000, 300);
   RooRealVar YHat1("YHat1", "YHat1", -0.172715, -100, 100);
   RooRealVar B1("B1", "B1", 0.050749, 0, 100);
   RooRealVar X01("X01", "X01", 139);
   RooRealVar Y01("Y01", "Y01", 0.107);
   RooRealVar C1("C1", "C1", 6);
   RooRealVar S1("S1", "S1", 0.00157);
   RooDalglish Model1("Model1", "Model1", MR, RSquared, XHat1, YHat1, B1, X01, Y01, C1, S1, SigmaX, SigmaY, XOFF, YOFF);

   // component 2
   RooRealVar XHat2("XHat2", "XHat2", -57.5526, -1000, 300);
   RooRealVar YHat2("YHat2", "YHat2", -0.327986, -100, 100);
   RooRealVar B2("B2", "B2", 0.159852, 0, 100);
   RooRealVar X02("X02", "X02", 139);
   RooRealVar Y02("Y02", "Y02", 0.112);
   RooRealVar C2("C2", "C2", 200);
   RooRealVar S2("S2", "S2", 0.01);
   RooDalglish Model2("Model2", "Model2", MR, RSquared, XHat2, YHat2, B2, X02, Y02, C2, S2, SigmaX, SigmaY, XOFF, YOFF);

   RooRealVar Fraction("Fraction", "Fraction", 0.751328, 0, 1);
   RooAddPdf Model("Model", "Final model!!!", Model1, Model2, Fraction);

   Model.fitTo(Dataset);

   PsFileHelper PsFile("Result.ps");
   PsFile.AddTextPage("Fit results!!!!");

   TH2F *DataHistogram = MR.createHistogram("Data!", R);
   Dataset.fillHistogram(DataHistogram, RooArgList(MR, R));
   DataHistogram->Rebin2D(4, 4);
   DataHistogram->SetMinimum(0.3);
   PsFile.AddPlot(DataHistogram, "colz", false, true);

   TH2F *ModelHistogram = MR.createHistogram("Model!", R);
   Model.fillHistogram(ModelHistogram, RooArgList(MR, R), Dataset.sumEntries());
   ModelHistogram->Rebin2D(4, 4);
   ModelHistogram->SetMinimum(0.3);
   PsFile.AddPlot(ModelHistogram, "colz", false, true);

   const Int_t NRGBs = 6;
   const Int_t NCont = 255;
   Double_t stops[NRGBs] = {0.00, 0.32, 0.4999, 0.50, 0.68, 1.00};
   Double_t red[NRGBs]   = {1.00, 0.50, 0.00, 0.00, 0.00, 0.00};
   Double_t green[NRGBs] = {0.00, 0.00, 1.00, 1.00, 0.00, 0.00};
   Double_t blue[NRGBs]  = {0.00, 0.00, 0.00, 0.00, 0.50, 1.00};
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   TH2F *PercentageHistogram = (TH2F *)DataHistogram->Clone("PercentageHistogram");
   PercentageHistogram->SetTitle("Percentage!!!");
   for(int i = 1; i <= PercentageHistogram->GetNbinsX(); i++)
   {
      for(int j = 1; j <= PercentageHistogram->GetNbinsY(); j++)
      {
         double DataPoint = DataHistogram->GetBinContent(i, j);
         double ModelPoint = ModelHistogram->GetBinContent(i, j);
         if(DataPoint > 0)
            PercentageHistogram->SetBinContent(i, j, GetPercentage(ModelPoint, DataPoint));
      }
   }
   PercentageHistogram->SetMinimum(0);
   PercentageHistogram->SetMaximum(1);
   PercentageHistogram->SetStats(0);
   PsFile.AddPlot(PercentageHistogram, "colz");

   RooPlot *ParameterPlot1 = MR.frame(Bins(50), Name("FitParameters1"), Title("Fit parameters"));
   Model1.paramOn(ParameterPlot1, Format("NELU", AutoPrecision(3)), Layout(0.1, 0.9, 0.9));
   PsFile.AddPlot(ParameterPlot1, "", false);

   RooPlot *ParameterPlot2 = MR.frame(Bins(50), Name("FitParameters2"), Title("Fit parameters"));
   Model2.paramOn(ParameterPlot2, Format("NELU", AutoPrecision(3)), Layout(0.1, 0.9, 0.9));
   PsFile.AddPlot(ParameterPlot2, "", false);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

double GetPercentage(double Base, double Test)
{
   const double NumberOfTries = 10000;
   double SuccessfulTries = 0;

   for(int i = 0; i < NumberOfTries; i++)
   {
      double value = 0;

      if(Base < 20)
      {
         bool OK = false;
         while(OK == false)
         {
            value = (int)DrawRandom(Base * 1.5 + 10);
            double check = DrawRandom();
            if(check < TMath::Poisson(value, Base))
               OK = true;
         }
      }
      else
         value = DrawGaussian(Base, sqrt(Base));

      if(value < Test)
         SuccessfulTries = SuccessfulTries + 1;
   }

   if(SuccessfulTries < 1e-3)
      SuccessfulTries = 1e-3;

   return SuccessfulTries / NumberOfTries;
}




