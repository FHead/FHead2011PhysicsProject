#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "TFile.h"

#include "RooRealVar.h"
#include "RooFitResult.h"
using namespace RooFit;

void CollectResult();
void CollectResult(string Threshold);

void CollectResult()
{
   CollectResult("15");
   CollectResult("30");
}

void CollectResult(string Threshold)
{
   vector<string> Labels;
   vector<RooFitResult *> Results;

   Labels.push_back("Unweighted, Unfolding, Normal");
   Labels.push_back("Weighted, Unfolding, Normal");
   Labels.push_back("Weighted, Unfolding, Minus");
   Labels.push_back("Weighted, Unfolding, Plus");
   Labels.push_back("JEC Plus, Weighted, Unfolding");
   Labels.push_back("JEC Minus, Weighted, Unfolding");
   Labels.push_back("Weighted, Z2 Unfolding, Normal");
   Labels.push_back("Weighted, D6T Unfolding, Normal");
   Labels.push_back("Weighted, Pythia Unfolding, Normal");

   TFile F5(("NoJEC_Unfold_Unweighted/UnfoldedResultU_pf_" + Threshold + ".root").c_str());
   TFile F6(("NoJEC_Unfold_Weighted/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F7(("NoJEC_Unfold_WeightMinus/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F8(("NoJEC_Unfold_WeightPlus/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F9(("JECPlus_Unfold_Weighted/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F10(("JECMinus_Unfold_Weighted/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F11(("NoJEC_Z2Unfold_Weighted/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F12(("NoJEC_D6TUnfold_Weighted/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F13(("NoJEC_PythiaUnfold_Weighted/UnfoldedResultW_pf_" + Threshold + ".root").c_str());

   Results.push_back((RooFitResult *)F5.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F6.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F7.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F8.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F9.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F10.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F11.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F12.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F13.Get("ConstrainedResult"));

   cout << fixed << setprecision(3);

   cout << "\\begin{landscape}" << endl;
   cout << "\\begin{table}" << endl;
   cout << "\\centering" << endl;
   cout << "\\begin{tabular}{|c||c|c|}" << endl;
   cout << "\\hline" << endl;
   cout << "   & $\\alpha$ & $\\beta$ \\\\\\hline\\hline" << endl;

   for(int i = 0; i < (int)Results.size(); i++)
   {
      cout << Labels[i];

      double AlphaPrime = ((RooRealVar *)(Results[i]->floatParsFinal().find("AlphaPrime")))->getVal();
      double AlphaPrimeError = ((RooRealVar *)(Results[i]->floatParsFinal().find("AlphaPrime")))->getError();
      double BetaPrime = ((RooRealVar *)(Results[i]->floatParsFinal().find("BetaPrime")))->getVal();
      double BetaPrimeError = ((RooRealVar *)(Results[i]->floatParsFinal().find("BetaPrime")))->getError();
      double Correlation = Results[i]->correlation("AlphaPrime", "BetaPrime");

      double Alpha = AlphaPrime - BetaPrime;
      double Beta = BetaPrime;
      double AlphaError = sqrt(AlphaPrimeError * AlphaPrimeError + BetaPrimeError * BetaPrimeError
         - 2 * AlphaPrimeError * BetaPrimeError * Correlation);
      double BetaError = BetaPrimeError * BetaPrimeError;

      cout << " & $" << Alpha << " \\pm " << AlphaError << "$ ";
      cout << " & $" << Beta << " \\pm " << BetaError << "$ ";
      // cout << " & $" << Alpha << "$ ";
      // cout << " & $" << Beta << "$ ";

      cout << " \\\\\\hline" << endl;
   }

   cout << "\\end{tabular}" << endl;
   cout << "\\caption{Constrained fit, threshold " << Threshold << " GeV, alpha and beta}" << endl;
   cout << "\\end{table}" << endl;
   cout << "\\end{landscape}" << endl;

   cout << "\\clearpage" << endl;
   cout << endl;

   F13.Close();
   F12.Close();
   F11.Close();
   F10.Close();
   F9.Close();
   F8.Close();
   F7.Close();
   F6.Close();
   F5.Close();
}
