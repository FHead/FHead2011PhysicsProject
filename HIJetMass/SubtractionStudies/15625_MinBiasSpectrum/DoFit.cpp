#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooGenericPdf.h"
using namespace RooFit;

int main();

int main()
{
   TFile File("HydjetMBDragos_0.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   RooRealVar PT("PT", "PT", 0, 20);
   RooRealVar Eta("Eta", "Eta", -0.5, 0.5);
   RooRealVar Rho("Rho", "Rho", 0, 50);

   RooDataSet Data("Data", "Data", RooArgSet(PT, Eta, Rho), Import(*Tree));

   // turn-on part of the function: (tanh(a(x-b)) + 1) / 2
   RooRealVar A("A", "A", 0, 1000);
   RooRealVar B("B", "B", 0, 1);
   RooGenericPdf FTurnOn("FTurnOn", "FTurnOn", "(tanh(A*(PT-B) + 1) / 2", RooArgSet(PT, A, B));

   File.Close();

   return 0;
}




