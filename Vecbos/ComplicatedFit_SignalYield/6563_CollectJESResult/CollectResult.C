#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "TFile.h"

#include "RooRealVar.h"
#include "RooFitResult.h"
using namespace RooFit;

void CollectResult(string Threshold = "30")
{
   vector<RooFitResult *> Results;

   TFile F1(("Normal/ResultPlotsW_pf_" + Threshold + ".root").c_str());
   TFile F2(("Minus/ResultPlotsW_pf_" + Threshold + ".root").c_str());
   TFile F3(("Plus/ResultPlotsW_pf_" + Threshold + ".root").c_str());

   Results.push_back((RooFitResult *)F1.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F2.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F3.Get("ConstrainedResult"));

   cout << fixed << setprecision(1);

   cout << "Z, " << Threshold << " GeV ";

   double NormalAlpha = ((RooRealVar *)(Results[0]->floatParsFinal().find("Alpha")))->getVal();
   double MinusAlpha = ((RooRealVar *)(Results[1]->floatParsFinal().find("Alpha")))->getVal();
   double PlusAlpha = ((RooRealVar *)(Results[2]->floatParsFinal().find("Alpha")))->getVal();
      
   cout << " & $" << NormalAlpha << "^{~";
   if(MinusAlpha - NormalAlpha > 0)
      cout << "+";
   cout << MinusAlpha - NormalAlpha << "}" << "_{~";
   if(PlusAlpha - NormalAlpha > 0)
      cout << "+";
   cout << PlusAlpha - NormalAlpha << "}$";
   
   double NormalBeta = ((RooRealVar *)(Results[0]->floatParsFinal().find("Beta")))->getVal();
   double MinusBeta = ((RooRealVar *)(Results[1]->floatParsFinal().find("Beta")))->getVal();
   double PlusBeta = ((RooRealVar *)(Results[2]->floatParsFinal().find("Beta")))->getVal();
      
   cout << " & $" << NormalBeta << "^{~";
   if(MinusBeta - NormalBeta > 0)
      cout << "+";
   cout << MinusBeta - NormalBeta << "}" << "_{~";
   if(PlusBeta - NormalBeta > 0)
      cout << "+";
   cout << PlusBeta - NormalBeta << "}$ \\\\" << endl;
   
   F3.Close();
   F2.Close();
   F1.Close();
}



