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
#include "RooNumIntConfig.h"
#include "RooNumIntFactory.h"
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

   double MRLowerBound = 225;
   double MRUpperBound = 1500;
   double RLowerBound = 0.3;
   double RUpperBound = 1;

   TFile F("TTJets_TuneZ2_7TeV-madgraph-tauola_MR200.0_R0.2_Had.root");

   RooRealVar MR("MR", "Chris' kinematic variable", MRLowerBound, MRUpperBound, "GeV");
   RooRealVar Rsq("Rsq", "R*R", RLowerBound * RLowerBound, RUpperBound * RUpperBound);
   RooDataSet *Dataset = (RooDataSet *)F.Get("RMRTree");
   if(Dataset == NULL)
      return -1;

   MR.setRange("FitRange", MRLowerBound, MRUpperBound);
   Rsq.setRange("FitRange", RLowerBound * RLowerBound, RUpperBound * RUpperBound);

   // contants that are not used....
   RooRealVar SigmaX("SigmaX", "SigmaX", 0);
   RooRealVar SigmaY("SigmaY", "SigmaY", 0);
   RooRealVar XOFF("XOFF", "XOFF", 0);
   RooRealVar YOFF("YOFF", "YOFF", 0);

   // component 1
   srand(time(NULL));
   RooRealVar XHat1("XHat1", "XHat1", -47.87);
   RooRealVar YHat1("YHat1", "YHat1", -0.13946);
   RooRealVar B1("B1", "B1", 0.05786);
   RooRealVar X01("X01", "X01", 139, -100000, 1000000);
   RooRealVar Y01("Y01", "Y01", 0.112, -10000, 100000);
   RooRealVar C1("C1", "C1", 8, 0, 1000);
   RooRealVar S1("S1", "S1", 120, 0, 100000);
   RooDalglish Model1("Model1", "Model1", MR, Rsq, XHat1, YHat1, B1, X01, Y01, C1, S1, SigmaX, SigmaY, XOFF, YOFF);
   Model1.defaultIntegratorConfig()->setEpsAbs(1e-10);
   Model1.defaultIntegratorConfig()->setEpsRel(1e-10);

   // component 2
   RooRealVar XHat2("XHat2", "XHat2", -48.75);
   RooRealVar YHat2("YHat2", "YHat2", -0.21350);
   RooRealVar B2("B2", "B2", 0.022713);
   RooRealVar X02("X02", "X02", 139, -100000, 100000);
   RooRealVar Y02("Y02", "Y02", 0.112, -100000, 100000);
   RooRealVar C2("C2", "C2", 272, 0, 1000000);
   RooRealVar S2("S2", "S2", 2, 0, 100);
   RooDalglish Model2("Model2", "Model2", MR, Rsq, XHat2, YHat2, B2, X01, Y01, C2, S2, SigmaX, SigmaY, XOFF, YOFF);
   Model2.defaultIntegratorConfig()->setEpsAbs(1e-10);
   Model2.defaultIntegratorConfig()->setEpsRel(1e-10);

   RooRealVar Fraction("Fraction", "Fraction", 0.97, 0., 1);
   RooAddPdf Model("Model", "Final model!!!", Model1, Model2, Fraction);
   Model.defaultIntegratorConfig()->setEpsAbs(1e-10);
   Model.defaultIntegratorConfig()->setEpsRel(1e-10);

   Model.fitTo(*Dataset, Range("FitRange"));

   PsFileHelper PsFile("Result.ps");
   PsFile.AddTextPage("Fit results!!!!");

   TH2F *DataHistogram = MR.createHistogram("Data!", Rsq);
   Dataset->fillHistogram(DataHistogram, RooArgList(MR, Rsq));
   DataHistogram->Rebin2D(4, 4);
   DataHistogram->SetMinimum(0.3);
   PsFile.AddPlot(DataHistogram, "colz", false, true);

   TH2F *ModelHistogram = MR.createHistogram("Model!", Rsq);
   Model.fillHistogram(ModelHistogram, RooArgList(MR, Rsq),
      Dataset->reduce(Form("MR > %f && MR < %f && Rsq > %f && Rsq < %f", MRLowerBound, MRUpperBound,
      RLowerBound * RLowerBound, RUpperBound * RUpperBound))->sumEntries());
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

   RooPlot *ParameterPlot = MR.frame(Bins(50), Name("FitParameters"), Title("Fit parameters"));
   Model1.paramOn(ParameterPlot, Format("NELU", AutoPrecision(3)), Layout(0.1, 0.49, 0.9));
   Model2.paramOn(ParameterPlot, Format("NELU", AutoPrecision(3)), Layout(0.51, 0.9, 0.9));
   PsFile.AddPlot(ParameterPlot, "", false);

   Rsq.setRange("Rsq01", 0.1, 1.0);   MR.setRange("Rsq01", MRLowerBound, MRUpperBound);
   Rsq.setRange("Rsq02", 0.2, 1.0);   MR.setRange("Rsq02", MRLowerBound, MRUpperBound);
   Rsq.setRange("Rsq03", 0.3, 1.0);   MR.setRange("Rsq03", MRLowerBound, MRUpperBound);
   Rsq.setRange("Rsq04", 0.4, 1.0);   MR.setRange("Rsq04", MRLowerBound, MRUpperBound);
   Rsq.setRange("Rsq05", 0.5, 1.0);   MR.setRange("Rsq05", MRLowerBound, MRUpperBound);

   RooPlot *MRResultPlot_Rsq01 = MR.frame(Bins(25), Name("MRResultPlot_Rsq01"), Title("MR, R^2 > 0.1"));
   Dataset->reduce("Rsq > 0.1")->plotOn(MRResultPlot_Rsq01, MarkerSize(0.8), MarkerColor(1));
   Model.plotOn(MRResultPlot_Rsq01, LineColor(kBlue), ProjectionRange("Rsq01"), Normalization(1));
   PsFile.AddPlot(MRResultPlot_Rsq01, "", true);

   RooPlot *MRResultPlot_Rsq02 = MR.frame(Bins(25), Name("MRResultPlot_Rsq02"), Title("MR, R^2 > 0.2"));
   Dataset->reduce("Rsq > 0.2")->plotOn(MRResultPlot_Rsq02, MarkerSize(0.8), MarkerColor(1));
   Model.plotOn(MRResultPlot_Rsq02, LineColor(kBlue), ProjectionRange("Rsq02"), Normalization(1));
   PsFile.AddPlot(MRResultPlot_Rsq02, "", true);

   RooPlot *MRResultPlot_Rsq03 = MR.frame(Bins(25), Name("MRResultPlot_Rsq03"), Title("MR, R^2 > 0.3"));
   Model.plotOn(MRResultPlot_Rsq03, LineColor(kBlue), ProjectionRange("Rsq03"), Normalization(1));
   Dataset->reduce("Rsq > 0.3")->plotOn(MRResultPlot_Rsq03, MarkerSize(0.8), MarkerColor(1));
   PsFile.AddPlot(MRResultPlot_Rsq03, "", true);

   RooPlot *MRResultPlot_Rsq04 = MR.frame(Bins(25), Name("MRResultPlot_Rsq04"), Title("MR, R^2 > 0.4"));
   Model.plotOn(MRResultPlot_Rsq04, LineColor(kBlue), ProjectionRange("Rsq04"), Normalization(1));
   Dataset->reduce("Rsq > 0.4")->plotOn(MRResultPlot_Rsq04, MarkerSize(0.8), MarkerColor(1));
   PsFile.AddPlot(MRResultPlot_Rsq04, "", true);

   RooPlot *MRResultPlot_Rsq05 = MR.frame(Bins(25), Name("MRResultPlot_Rsq05"), Title("MR, R^2 > 0.5"));
   Model.plotOn(MRResultPlot_Rsq05, LineColor(kBlue), ProjectionRange("Rsq05"), Normalization(1));
   Dataset->reduce("Rsq > 0.5")->plotOn(MRResultPlot_Rsq05, MarkerSize(0.8), MarkerColor(1));
   PsFile.AddPlot(MRResultPlot_Rsq05, "", true);

   MR.setRange("MR250", 250, MRUpperBound);
   MR.setRange("MR300", 300, MRUpperBound);
   MR.setRange("MR350", 350, MRUpperBound);
   MR.setRange("MR400", 400, MRUpperBound);

   RooPlot *MRResultPlot_MR250 = Rsq.frame(Bins(25), Name("R2ResultPlot_MR250"), Title("R^2, MR > 250"));
   Model.plotOn(MRResultPlot_MR250, LineColor(kBlue), ProjectionRange("MR250"), Normalization(Dataset->sumEntries()));
   Dataset->reduce("MR > 250")->plotOn(MRResultPlot_MR250, MarkerSize(0.8), MarkerColor(1));
   PsFile.AddPlot(MRResultPlot_MR250, "", true);

   RooPlot *MRResultPlot_MR300 = Rsq.frame(Bins(25), Name("R2ResultPlot_MR300"), Title("R^2, MR > 300"));
   Model.plotOn(MRResultPlot_MR300, LineColor(kBlue), ProjectionRange("MR300"), Normalization(Dataset->sumEntries()));
   Dataset->reduce("MR > 300")->plotOn(MRResultPlot_MR300, MarkerSize(0.8), MarkerColor(1));
   PsFile.AddPlot(MRResultPlot_MR300, "", true);

   RooPlot *MRResultPlot_MR350 = Rsq.frame(Bins(25), Name("R2ResultPlot_MR350"), Title("R^2, MR > 350"));
   Model.plotOn(MRResultPlot_MR350, LineColor(kBlue), ProjectionRange("MR350"), Normalization(Dataset->sumEntries()));
   Dataset->reduce("MR > 350")->plotOn(MRResultPlot_MR350, MarkerSize(0.8), MarkerColor(1));
   PsFile.AddPlot(MRResultPlot_MR350, "", true);

   RooPlot *MRResultPlot_MR400 = Rsq.frame(Bins(25), Name("R2ResultPlot_MR400"), Title("R^2, MR > 400"));
   Model.plotOn(MRResultPlot_MR400, LineColor(kBlue), ProjectionRange("MR400"), Normalization(Dataset->sumEntries()));
   Dataset->reduce("MR > 400")->plotOn(MRResultPlot_MR400, MarkerSize(0.8), MarkerColor(1));
   PsFile.AddPlot(MRResultPlot_MR400, "", true);

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




