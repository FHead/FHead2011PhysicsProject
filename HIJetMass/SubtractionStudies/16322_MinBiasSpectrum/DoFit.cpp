#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooGenericPdf.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooPlot.h"
using namespace RooFit;

#include "SetStyle.h"

int main();

int main()
{
   SetThesisStyle();

   TFile File("Result/HydjetMBDragos_0.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   RooRealVar PT("PT", "PT", 0, 20);
   RooRealVar Eta("Eta", "Eta", -1.3, 1.3);
   RooRealVar Rho("Rho", "Rho", 0, 400);

   RooDataSet Data("Data", "Data", Tree, RooArgSet(PT, Eta, Rho), "PT < 20 && Eta > -0.1 && Eta < 0.1 && Rho < 50");

   cout << "Dataset size = " << Data.sumEntries() << endl;

   // turn-on part of the function: (tanh(a(x-b)) + 1) / 2
   RooRealVar A("A", "A", 50, 0, 1000);
   RooRealVar B("B", "B", 0.3, 0, 1);
   RooGenericPdf FTurnOn("FTurnOn", "FTurnOn", "(tanh(A*(PT-B)) + 1 + 1e-10) / 2", RooArgSet(PT, A, B));

   RooRealVar K1("K1", "K1", -1.94, -100, -0.001);
   RooRealVar K2("K2", "K2", -3.62, -100, -0.001);
   RooRealVar Fraction("Fraction", "Fraction", 0, 1);
   RooExponential FExp1("FExp1", "FExp1", PT, K1);
   RooExponential FExp2("FExp2", "FExp2", PT, K2);
   RooAddPdf FDecay("FDecay", "FDecay", FExp1, FExp2, Fraction);

   RooProdPdf FModel("FModel", "FModel", FTurnOn, FDecay);

   FModel.fitTo(Data);

   RooPlot *Frame = PT.frame(Name("PTPlot"), Title("Fit result"), Bins(40));
   Data.plotOn(Frame);
   FModel.plotOn(Frame);

   FModel.paramOn(Frame, Layout(0.55));

   TCanvas Canvas;

   Frame->Draw();

   Canvas.SaveAs("FitResult.png");
   Canvas.SaveAs("FitResult.C");
   Canvas.SaveAs("FitResult.eps");
   Canvas.SaveAs("FitResult.pdf");

   File.Close();

   return 0;
}




