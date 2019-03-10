#include <iostream>
using namespace std;

#include "TFile.h"
#include "TF2.h"

#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooGenericPdf.h"
#include "RooArgSet.h"

#include "CustomAssert.h"
#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string InputTreeName = CL.Get("tree", "FitData");

   TFile File(InputFileName.c_str());
   TTree *Tree = (TTree *)File.Get(InputTreeName.c_str());

   Assert(Tree != NULL, "Problem getting tree");

   RooRealVar PT("PT", "P_{T}^{PU} (GeV)", 0, 10000);
   RooRealVar OOA("OOA", "Offset/Area (GeV)", -100, 100);
   RooRealVar OOAPT("OOAPT", "Offset/Area/P_{T}^{PU}", -10, 10);
   RooRealVar Rho("Rho", "Rho (GeV)", 0, 100);

   RooDataSet Data("Data", "Data", Tree, RooArgSet(PT, Rho, OOA));

   RooRealVar A("A", "A", 1, 0, 100);
   RooRealVar B("B", "B", 0, -10, 10);
   RooRealVar C("C", "C", 0, -10, 10);
   RooRealVar D("D", "D", 0, -10, 10);
   RooRealVar E("E", "E", 0, -10, 10);
   RooRealVar RhoUE0("RhoUE0", "RhoUE0", 2);
   RooRealVar RhoUE1("RhoUE1", "RhoUE1", 0);
   RooRealVar AverageRho("AverageRho", "AverageRho", 0);
   RooRealVar PTNorm("PTNorm", "PTNorm", 30);

   RooArgSet Set(PT, Rho, OOA);
   Set.add(RooArgSet(A, B, C, D, E));
   Set.add(RooArgSet(RhoUE0, RhoUE1, AverageRho, PTNorm));
   RooGenericPdf Function("Function", "Function",
      "pow(A*(Rho-(RhoUE0+RhoUE1*Rho))*(1+B*(Rho-AverageRho))*(1+C*log(PT/PTNorm))+(D+E*log(PT))-OOA,2)", Set);

   Function.fitTo(Data);

   File.Close();

   return 0;
}
