#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooProdPdf.h"
#include "RooArgList.h"
#include "RooDataSet.h"
using namespace RooFit;

void ReproduceProblem()
{
   RooRealVar A("A", "A", 0, 1000);
   RooRealVar B("B", "B", 0, 1000);
   RooFormulaVar AB("AB", "A+B", "A+B", RooArgList(A, B));

   RooRealVar AMean("AMean", "AMean", 20);
   RooRealVar BMean("BMean", "BMean", 20);
   RooRealVar ABMean("ABMean", "ABMean", 40);

   RooRealVar ASigma("ASigma", "ASigma", 20);
   RooRealVar BSigma("BSigma", "BSigma", 20);
   RooRealVar ABSigma("ABSigma", "ABSigma", 5);

   RooGaussian G1("G1", "G1", A, AMean, ASigma);
   RooGaussian G2("G2", "G2", B, BMean, BSigma);
   RooGaussian G3("G3", "G3", AB, ABMean, ABSigma);

   RooProdPdf Model("Model", "Model", RooArgList(G1, G2, G3));

   RooDataSet *ToyData = (RooDataSet *)Model.generate(RooArgSet(A, B), 1);
   double NLL = Model.createNLL(*ToyData)->getVal();
   cout << NLL << endl;
}



