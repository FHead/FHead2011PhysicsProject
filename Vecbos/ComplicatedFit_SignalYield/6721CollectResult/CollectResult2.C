#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "TFile.h"

#include "RooRealVar.h"
#include "RooFitResult.h"
using namespace RooFit;

void CollectResult2();
void CollectResult2(string Threshold);

void CollectResult2()
{
   // CollectResult2("15");
   CollectResult2("30");
}

void CollectResult2(string Threshold)
{
   vector<string> Labels;
   vector<RooFitResult *> Results;

   Labels.push_back("constrained");
   Labels.push_back("constr. unsmeared");
   Labels.push_back("constr. weighted");
   Labels.push_back("constr. weighted, unsmeared");

   TFile F2(("NoJEC_NoUnfold_Unweighted/UnfoldedResultU_pf_" + Threshold + ".root").c_str());
   TFile F8(("NoJEC_Unfold_Unweighted/UnfoldedResultU_pf_" + Threshold + ".root").c_str());
   TFile F11(("NoJEC_NoUnfold_Weighted/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F17(("NoJEC_Unfold_Weighted/UnfoldedResultW_pf_" + Threshold + ".root").c_str());

   Results.push_back((RooFitResult *)F2.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F8.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F11.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F17.Get("ConstrainedResult"));

   cout << fixed << setprecision(1);

   cout << "\\begin{landscape}" << endl;
   cout << "\\begin{table}" << endl;
   cout << "\\centering" << endl;
   cout << "\\begin{tabular}{|c||c|c|}" << endl;
   cout << "\\hline" << endl;
   cout << "   & $\\alpha$ & $\\beta$ \\\\\\hline\\hline" << endl;

   for(int i = 0; i < (int)Results.size(); i++)
   {
      cout << Labels[i];

      double Alpha = ((RooRealVar *)(Results[i]->floatParsFinal().find("Alpha")))->getVal();
      double AlphaError = ((RooRealVar *)(Results[i]->floatParsFinal().find("Alpha")))->getError();
      double Beta = ((RooRealVar *)(Results[i]->floatParsFinal().find("Beta")))->getVal();
      double BetaError = ((RooRealVar *)(Results[i]->floatParsFinal().find("Beta")))->getError();

      cout << " & $" << Alpha << " \\pm " << AlphaError << "$ ";
      cout << " & $" << Beta << " \\pm " << BetaError << "$ ";

      cout << " \\\\\\hline" << endl;
   }

   cout << "\\end{tabular}" << endl;
   cout << "\\caption{Constrained fit, threshold " << Threshold << " GeV, alpha and beta}" << endl;
   cout << "\\end{table}" << endl;
   cout << "\\end{landscape}" << endl;

   cout << "\\clearpage" << endl;
   cout << endl;

   F17.Close();
   F11.Close();
   F8.Close();
   F2.Close();
}
