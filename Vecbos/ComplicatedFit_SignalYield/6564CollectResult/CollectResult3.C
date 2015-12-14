#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "TFile.h"

#include "RooRealVar.h"
#include "RooFitResult.h"
using namespace RooFit;

void CollectResult3(string Threshold = "30")
{
   vector<string> Labels;
   vector<RooFitResult *> Results;

   Labels.push_back("constrained");
   Labels.push_back("");
   Labels.push_back("");
   Labels.push_back("constr. unsmeared");
   Labels.push_back("");
   Labels.push_back("");

   TFile F10(("NoJEC_NoUnfold_WeightMinus/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F11(("NoJEC_NoUnfold_Weighted/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F12(("NoJEC_NoUnfold_WeightPlus/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F16(("NoJEC_Unfold_WeightMinus/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F17(("NoJEC_Unfold_Weighted/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F18(("NoJEC_Unfold_WeightPlus/UnfoldedResultW_pf_" + Threshold + ".root").c_str());

   Results.push_back((RooFitResult *)F10.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F11.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F12.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F16.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F17.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F18.Get("ConstrainedResult"));

   cout << fixed << setprecision(1);

   cout << "\\begin{table}[h!]" << endl;
   cout << "\\center" << endl;
   cout << "\\begin{tabular}{  |c | c |c |}" << endl;
   cout << "\\hline" << endl;
   cout << "   & $\\alpha$ & $\\beta$ \\\\\\hline" << endl;

   for(int i = 0; i < (int)Results.size(); i = i + 3)
   {
      cout << Labels[i];

      double NormalAlpha = ((RooRealVar *)(Results[i+1]->floatParsFinal().find("Alpha")))->getVal();
      double PlusAlpha = ((RooRealVar *)(Results[i+2]->floatParsFinal().find("Alpha")))->getVal();
      double MinusAlpha = ((RooRealVar *)(Results[i]->floatParsFinal().find("Alpha")))->getVal();
      double NormalAlphaError = ((RooRealVar *)(Results[i+1]->floatParsFinal().find("Alpha")))->getError();
      
      double NormalBeta = ((RooRealVar *)(Results[i+1]->floatParsFinal().find("Beta")))->getVal();
      double PlusBeta = ((RooRealVar *)(Results[i+2]->floatParsFinal().find("Beta")))->getVal();
      double MinusBeta = ((RooRealVar *)(Results[i]->floatParsFinal().find("Beta")))->getVal();
      double NormalBetaError = ((RooRealVar *)(Results[i+1]->floatParsFinal().find("Beta")))->getError();

      cout << " & $" << NormalAlpha << "^{~";
      if(MinusAlpha - NormalAlpha > 0)
         cout << "+";
      cout << MinusAlpha - NormalAlpha << "}_{~";
      if(PlusAlpha - NormalAlpha > 0)
         cout << "+";
      cout << PlusAlpha - NormalAlpha << "}$";
      
      cout << " & $" << NormalBeta << "^{~";
      if(MinusBeta - NormalBeta > 0)
         cout << "+";
      cout << MinusBeta - NormalBeta << "}_{~";
      if(PlusBeta - NormalBeta > 0)
         cout << "+";
      cout << PlusBeta - NormalBeta << "}$ \\\\" << endl;

      cout << " & ($\\pm$ " << NormalAlphaError << ")";
      cout << " & ($\\pm$ " << NormalBetaError << ")";
      cout << "\\\\\\hline" << endl;
   }

   cout << "\\end{tabular}" << endl;
   cout << "\\caption{Constrained fit, threshold " << Threshold << " GeV, alpha and beta}" << endl;
   cout << "\\end{table}" << endl;

   cout << "\\clearpage" << endl;
   cout << endl;

   F18.Close();
   F17.Close();
   F16.Close();
   F12.Close();
   F11.Close();
   F10.Close();
}
