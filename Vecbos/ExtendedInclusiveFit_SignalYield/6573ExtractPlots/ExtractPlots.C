#include <iostream>
using namespace std;

#include "TFile.h"
#include "TObject.h"
#include "TList.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "RooCurve.h"
#include "RooHist.h"

void ExtractPlots();
void ExtractPlots(char *filename);

void ExtractPlots()
{
   ExtractPlots("FFF_3.root");
   ExtractPlots("FFF_4.root");
}

void ExtractPlots(char *filename)
{
   TFile F(filename, "update");

   TCanvas *TempCanvas = (TCanvas *)F.Get("TempCanvas");

   TList *List = (TList *)TempCanvas->GetListOfPrimitives();
   TIter next(List);

   int RooHistCount = 0;
   int TH1DCount = 0;
   int RooCurveCount = 0;

   TObject *Object = next();
   while(Object != NULL)
   {
      cout << Object->GetName() << " --- " << Object->IsA()->GetName() << endl;

      if(TString(Object->IsA()->GetName()) == "RooHist")
      {
         cout << "Cloning RooHist" << endl;
         RooHistCount = RooHistCount + 1;
         ((RooHist *)Object)->Clone(Form("RooHist%d", RooHistCount))->Write();
      }
      if(TString(Object->IsA()->GetName()) == "TH1D")
      {
         cout << "Cloning TH1D" << endl;
         TH1DCount = TH1DCount + 1;
         ((TH1D *)Object)->Clone(Form("Histogram%d", TH1DCount))->Write();
      }
      if(TString(Object->IsA()->GetName()) == "RooCurve")
      {
         cout << "Cloning RooCurve" << endl;
         RooCurveCount = RooCurveCount + 1;
         ((RooCurve *)Object)->Clone(Form("RooCurve%d", RooCurveCount))->Write();
      }

      Object = next();
   }

   F.Close();
}





