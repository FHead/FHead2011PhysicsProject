#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooMeow.hh"
using namespace RooFit;

#define PI 3.1415926535897932384626433832795028847971693993751058209749445923078164

int main()
{
   TFile File("FitTree.root");
   TTree *Tree = (TTree *)File.Get("OutputTree");

   RooRealVar V11a("V11a", "V11a", 0.0, 100.0);      RooRealVar V11b("V11b", "V11b", 0.0, 100.0);
   RooRealVar V33a("V33a", "V33a", 0.0, 100.0);      RooRealVar V33b("V33b", "V33b", 0.0, 100.0);
   RooRealVar V44a("V44a", "V44a", 0.0, 100.0);      RooRealVar V44b("V44b", "V44b", 0.0, 100.0);
   RooRealVar V13a("V13a", "V13a", -100.0, 100.0);   RooRealVar V13b("V13b", "V13b", -100.0, 100.0);
   RooRealVar V14a("V14a", "V14a", -100.0, 100.0);   RooRealVar V14b("V14b", "V14b", -100.0, 100.0);
   // RooRealVar V34a("V34a", "V34a", -100.0, 100.0);   RooRealVar V34b("V34b", "V34b", -100.0, 100.0);
   
   RooRealVar I11a("I11a", "I11a", 0.0, 100.0);      RooRealVar I11b("I11b", "I11b", 0.0, 100.0);
   RooRealVar I33a("I33a", "I33a", 0.0, 100.0);      RooRealVar I33b("I33b", "I33b", 0.0, 100.0);
   RooRealVar I44a("I44a", "I44a", 0.0, 100.0);      RooRealVar I44b("I44b", "I44b", 0.0, 100.0);
   RooRealVar I13a("I13a", "I13a", -100.0, 100.0);   RooRealVar I13b("I13b", "I13b", -100.0, 100.0);
   RooRealVar I14a("I14a", "I14a", -100.0, 100.0);   RooRealVar I14b("I14b", "I14b", -100.0, 100.0);
   // RooRealVar I34a("I34a", "I34a", -100.0, 100.0);   RooRealVar I34b("I34b", "I34b", -100.0, 100.0);

   RooArgSet Variables;
   Variables.add(V11a);   Variables.add(V11b);   Variables.add(I11a);   Variables.add(I11b);
   Variables.add(V33a);   Variables.add(V33b);   Variables.add(I33a);   Variables.add(I33b);
   Variables.add(V44a);   Variables.add(V44b);   Variables.add(I44a);   Variables.add(I44b);
   Variables.add(V13a);   Variables.add(V13b);   Variables.add(I13a);   Variables.add(I13b);
   Variables.add(V14a);   Variables.add(V14b);   Variables.add(I14a);   Variables.add(I14b);
   // Variables.add(V34a);   Variables.add(V34b);   Variables.add(I34a);   Variables.add(I34b);

   RooDataSet Dataset("Data", "Data", Tree, Variables);

   RooRealVar A1("A1", "A1", 1.0);
   RooRealVar A3("A3", "A3", 0.0, 100.0);
   RooRealVar A3Phase("A3Phase", "A3Phase", -PI, PI);

   RooRealVar N1("N1", "N1", 0.0);

   RooFormulaVar V11("V11", "V11", "V11a + V11b * N1", RooArgList(V11a, V11b, N1));
   RooFormulaVar V33("V33", "V33", "V33a + V33b * N1", RooArgList(V33a, V33b, N1));
   RooFormulaVar V44("V44", "V44", "V44a + V44b * N1", RooArgList(V44a, V44b, N1));
   RooFormulaVar V13("V13", "V13", "V13a + V13b * N1", RooArgList(V13a, V13b, N1));
   RooFormulaVar V14("V14", "V14", "V14a + V14b * N1", RooArgList(V14a, V14b, N1));
   // RooFormulaVar V34("V34", "V34", "V34a + V34b * N1", RooArgList(V34a, V34b, N1));

   RooFormulaVar I11("I11", "I11", "I11a + I11b * N1", RooArgList(I11a, I11b, N1));
   RooFormulaVar I33("I33", "I33", "I33a + I33b * N1", RooArgList(I33a, I33b, N1));
   RooFormulaVar I44("I44", "I44", "I44a + I44b * N1", RooArgList(I44a, I44b, N1));
   RooFormulaVar I13("I13", "I13", "I13a + I13b * N1", RooArgList(I13a, I13b, N1));
   RooFormulaVar I14("I14", "I14", "I14a + I14b * N1", RooArgList(I14a, I14b, N1));
   // RooFormulaVar I34("I34", "I34", "I34a + I34b * N1", RooArgList(I34a, I34b, N1));

   RooMeow Meow("Meow", "Meow", A1, A3, A3Phase, V11, V33, V44, V13, V14/*, V34*/, I11, I33, I44, I13, I14/*, I34*/);

   Meow.fitTo(Dataset);

   File.Close();

   return 0;
}





