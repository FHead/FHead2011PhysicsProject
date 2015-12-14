#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "TFile.h"

#include "RooRealVar.h"
#include "RooFitResult.h"
using namespace RooFit;

void CollectResult(string Threshold = "15")
{
   vector<RooFitResult *> Results;

   TFile F1(("Normal/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F2(("Minus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F3(("Plus/ResultFileW_pf_" + Threshold + ".root").c_str());

   Results.push_back((RooFitResult *)F1.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F2.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F3.Get("UnconstrainedFitResult"));

   cout << fixed << setprecision(0);

   cout << "Z, " << Threshold << " GeV ";

   for(int j = 0; j < 4; j++)
   {
      double NormalValue1 =
         ((RooRealVar *)(Results[0]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getVal();
      double NormalValue2 =
         ((RooRealVar *)(Results[0]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j + 1))))->getVal();
      double MinusValue1 =
         ((RooRealVar *)(Results[1]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getVal();
      double MinusValue2 =
         ((RooRealVar *)(Results[1]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j + 1))))->getVal();
      double PlusValue1 =
         ((RooRealVar *)(Results[2]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getVal();
      double PlusValue2 =
         ((RooRealVar *)(Results[2]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j + 1))))->getVal();

      double NormalValue = NormalValue1 - NormalValue2;
      double MinusValue = MinusValue1 - MinusValue2;
      double PlusValue = PlusValue1 - PlusValue2;

      cout << " & $" << NormalValue << "^{~";
      if(MinusValue - NormalValue > 0)
         cout << "+";
      cout << MinusValue - NormalValue << "}" << "_{~";
      if(NormalValue - PlusValue < 0)
         cout << "+";
      cout << PlusValue - NormalValue << "}$";
   }
         
   double NormalValue =
      ((RooRealVar *)(Results[0]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
   double MinusValue =
      ((RooRealVar *)(Results[1]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
   double PlusValue =
      ((RooRealVar *)(Results[2]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
      
   cout << " & $" << NormalValue << "^{~";
   if(MinusValue - NormalValue > 0)
      cout << "+";
   cout << MinusValue - NormalValue << "}" << "_{~";
   if(PlusValue - NormalValue > 0)
      cout << "+";
   cout << PlusValue - NormalValue << "}$";
   
   F3.Close();
   F2.Close();
   F1.Close();
}



