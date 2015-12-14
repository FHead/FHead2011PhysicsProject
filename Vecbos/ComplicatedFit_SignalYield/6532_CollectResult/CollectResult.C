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
   vector<string> Labels;
   vector<RooFitResult *> Results;

   Labels.push_back("Unweighted, No unfolding, Minus");
   Labels.push_back("Unweighted, No unfolding, Normal");
   Labels.push_back("Unweighted, No unfolding, Plus");
   Labels.push_back("Unweighted, D6T Unfolding, Minus");
   Labels.push_back("Unweighted, D6T Unfolding, Normal");
   Labels.push_back("Unweighted, D6T Unfolding, Plus");
   Labels.push_back("Unweighted, Z2 Unfolding, Minus");
   Labels.push_back("Unweighted, Z2 Unfolding, Normal");
   Labels.push_back("Unweighted, Z2 Unfolding, Plus");
   Labels.push_back("Weighted, No unfolding, Minus");
   Labels.push_back("Weighted, No unfolding, Normal");
   Labels.push_back("Weighted, No unfolding, Plus");
   Labels.push_back("Weighted, D6T Unfolding, Minus");
   Labels.push_back("Weighted, D6T Unfolding, Normal");
   Labels.push_back("Weighted, D6T Unfolding, Plus");
   Labels.push_back("Weighted, Z2 Unfolding, Minus");
   Labels.push_back("Weighted, Z2 Unfolding, Normal");
   Labels.push_back("Weighted, Z2 Unfolding, Plus");

   TFile F1(("NoUnfold/Minus/ResultPlotsU_pf_" + Threshold + ".root").c_str());
   TFile F2(("NoUnfold/Normal/ResultPlotsU_pf_" + Threshold + ".root").c_str());
   TFile F3(("NoUnfold/Plus/ResultPlotsU_pf_" + Threshold + ".root").c_str());
   TFile F4(("D6TUnfold/Minus/UnfoldedResultU_pf_" + Threshold + ".root").c_str());
   TFile F5(("D6TUnfold/Normal/UnfoldedResultU_pf_" + Threshold + ".root").c_str());
   TFile F6(("D6TUnfold/Plus/UnfoldedResultU_pf_" + Threshold + ".root").c_str());
   TFile F7(("Z2Unfold/Minus/UnfoldedResultU_pf_" + Threshold + ".root").c_str());
   TFile F8(("Z2Unfold/Normal/UnfoldedResultU_pf_" + Threshold + ".root").c_str());
   TFile F9(("Z2Unfold/Plus/UnfoldedResultU_pf_" + Threshold + ".root").c_str());
   TFile F10(("NoUnfold/Minus/ResultPlotsW_pf_" + Threshold + ".root").c_str());
   TFile F11(("NoUnfold/Normal/ResultPlotsW_pf_" + Threshold + ".root").c_str());
   TFile F12(("NoUnfold/Plus/ResultPlotsW_pf_" + Threshold + ".root").c_str());
   TFile F13(("D6TUnfold/Minus/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F14(("D6TUnfold/Normal/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F15(("D6TUnfold/Plus/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F16(("Z2Unfold/Minus/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F17(("Z2Unfold/Normal/UnfoldedResultW_pf_" + Threshold + ".root").c_str());
   TFile F18(("Z2Unfold/Plus/UnfoldedResultW_pf_" + Threshold + ".root").c_str());

   Results.push_back((RooFitResult *)F1.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F2.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F3.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F4.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F5.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F6.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F7.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F8.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F9.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F10.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F11.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F12.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F13.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F14.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F15.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F16.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F17.Get("ConstrainedResult"));
   Results.push_back((RooFitResult *)F18.Get("ConstrainedResult"));

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

      double Alpha = ((RooRealVar *)(Results[i]->floatParsFinal().find("Alpha")))->getVal();
      double AlphaError = ((RooRealVar *)(Results[i]->floatParsFinal().find("Alpha")))->getError();
      double Beta = ((RooRealVar *)(Results[i]->floatParsFinal().find("Beta")))->getVal();
      double BetaError = ((RooRealVar *)(Results[i]->floatParsFinal().find("Beta")))->getError();

      cout << " & $" << Alpha << " \\pm " << AlphaError << "$ ";
      cout << " & $" << Beta << " \\pm " << BetaError << "$ ";

      if(i % 3 == 2)
         cout << " \\\\\\hline\\hline" << endl;
      else
         cout << " \\\\\\hline" << endl;
   }

   cout << "\\end{tabular}" << endl;
   cout << "\\caption{Constrained fit, threshold " << Threshold << " GeV, alpha and beta}" << endl;
   cout << "\\end{table}" << endl;
   cout << "\\end{landscape}" << endl;

   cout << "\\clearpage" << endl;
   cout << endl;

   F18.Close();
   F17.Close();
   F16.Close();
   F15.Close();
   F14.Close();
   F13.Close();
   F12.Close();
   F11.Close();
   F10.Close();
   F9.Close();
   F8.Close();
   F7.Close();
   F6.Close();
   F5.Close();
   F4.Close();
   F3.Close();
   F2.Close();
   F1.Close();
}
