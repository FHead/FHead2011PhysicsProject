#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TF1.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooCBShape.h"
#include "RooGenericPdf.h"
#include "RooDataHist.h"
#include "RooProdPdf.h"
#include "RooPlot.h"
using namespace RooFit;

#include "PlotHelper3.h"
#include "SetStyle.h"

int main()
{
   RooRealVar X("X", "X", 0.02, 0.4);
   RooRealVar Mean("Mean", "Mean", 0.025, 0.01, 0.4);
   RooRealVar Sigma("Sigma", "Sigma", 0.018, 0.01, 0.4);
   RooRealVar Alpha("Alpha", "Alpha", -1.2, -20, 0.0);
   RooRealVar N("N", "N", 1.2, 0, 20);

   RooCBShape FBase("FBase", "Crystal ball", X, Mean, Sigma, Alpha, N);

   RooRealVar CutoffA("CutoffA", "CutoffA", 30, 1, 100);
   RooRealVar CutoffB("CutoffB", "CutoffB", 0.23, 0.1, 0.4);
   RooGenericPdf FCutoff("FCutoff", "Cutoff", "0.5*(1-tanh(CutoffA*(X-CutoffB)))", RooArgList(X, CutoffA, CutoffB));

   RooProdPdf Model("Model", "Model", RooArgList(FBase, FCutoff));

   TFile File("PP6Dijet.root");

   TH1D H1("H1", "H1", 160, 0, 0.4);
   TH1D H2("H2", "H2", 160, 0, 0.4);

   TTree *T = (TTree *)File.Get("OutputTree");

   T->Draw("NewJetSDMass2/NewJetPT>>H1", "MCWeight * (JetPT > 120 && JetPT < 140 && NewJetSDMass2 > 0.01)", "hist");

   for(int i = 1; i <= 160; i++)
   {
      H2.SetBinContent(i, H1.GetBinContent(i));
      H2.SetBinError(i, 1);
   }

   RooDataHist Data("Data", "Data", RooArgList(X), &H1);

   FBase.fitTo(Data, SumW2Error(false), Range(0.02, 0.20));
   Mean.setConstant(true);
   Sigma.setConstant(true);
   Alpha.setConstant(true);
   N.setConstant(true);
   Model.fitTo(Data, SumW2Error(false));

   RooPlot *Frame = X.frame();
   Data.plotOn(Frame);
   Model.plotOn(Frame);

   PdfFileHelper PdfFile("CBFit.pdf");

   PdfFile.AddPlot(Frame);

   Frame->SetMinimum(1);
   PdfFile.AddPlot(Frame, "", true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();

   return 0;
}


