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
   Labels.push_back("Unweighted, Unfolding, Minus");
   Labels.push_back("Unweighted, Unfolding, Normal");
   Labels.push_back("Unweighted, Unfolding, Plus");
   Labels.push_back("Weighted, No unfolding, Minus");
   Labels.push_back("Weighted, No unfolding, Normal");
   Labels.push_back("Weighted, No unfolding, Plus");
   Labels.push_back("Weighted, Unfolding, Minus");
   Labels.push_back("Weighted, Unfolding, Normal");
   Labels.push_back("Weighted, Unfolding, Plus");

   TFile F1(("NoUnfold/Minus/ResultFileU_pf_" + Threshold + ".root").c_str());
   TFile F2(("NoUnfold/Normal/ResultFileU_pf_" + Threshold + ".root").c_str());
   TFile F3(("NoUnfold/Plus/ResultFileU_pf_" + Threshold + ".root").c_str());
   TFile F4(("Unfold/Minus/ResultFileU_pf_" + Threshold + ".root").c_str());
   TFile F5(("Unfold/Normal/ResultFileU_pf_" + Threshold + ".root").c_str());
   TFile F6(("Unfold/Plus/ResultFileU_pf_" + Threshold + ".root").c_str());
   TFile F7(("NoUnfold/Minus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F8(("NoUnfold/Normal/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F9(("NoUnfold/Plus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F10(("Unfold/Minus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F11(("Unfold/Normal/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F12(("Unfold/Plus/ResultFileW_pf_" + Threshold + ".root").c_str());

   Results.push_back((RooFitResult *)F1.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F2.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F3.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F4.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F5.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F6.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F7.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F8.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F9.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F10.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F11.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F12.Get("UnconstrainedFitResult"));

   cout << fixed << setprecision(0);

   cout << "\\begin{landscape}" << endl;
   cout << "\\begin{sidewaystable}" << endl;
   cout << "\\begin{tabular}{|c||c|c|c|c|c|}" << endl;
   cout << "\\hline" << endl;
   cout << "   & $\\ge 0$ & $\\ge 1$ & $\\ge 2$ & $\\ge 3$ & $\\ge 4$ \\\\\\hline\\hline" << endl;

   for(int i = 0; i < (int)Results.size(); i++)
   {
      cout << Labels[i];

      for(int j = 0; j < 5; j++)
      {
         double Value =
            ((RooRealVar *)(Results[i]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getVal();
         double Error =
            ((RooRealVar *)(Results[i]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getError();

         cout << " & $" << Value << " \\pm " << Error << "$ ";
      }

      if(i % 3 == 2)
         cout << " \\\\\\hline\\hline" << endl;
      else
         cout << " \\\\\\hline" << endl;
   }

   cout << "\\end{tabular}" << endl;
   cout << "\\caption{Unconstrained fit, threshold " << Threshold << " GeV, inclusive yields}" << endl;
   cout << "\\end{sidewaystable}" << endl;
   cout << "\\end{landscape}" << endl;

   cout << "\\clearpage" << endl;
   cout << endl;

   cout << "\\begin{landscape}" << endl;
   cout << "\\begin{sidewaystable}" << endl;
   cout << "\\begin{tabular}{|c||c|c|c|c|c|}" << endl;
   cout << "\\hline" << endl;
   cout << "   & $= 0$ & $= 1$ & $= 2$ & $= 3$ & $\\ge 4$ \\\\\\hline\\hline" << endl;

   for(int i = 0; i < (int)Results.size(); i++)
   {
      cout << Labels[i];

      for(int j = 0; j < 4; j++)
      {
         double Value1 =
            ((RooRealVar *)(Results[i]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getVal();
         double Error1 =
            ((RooRealVar *)(Results[i]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getError();
         double Value2 =
            ((RooRealVar *)(Results[i]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j + 1))))->getVal();
         double Error2 =
            ((RooRealVar *)(Results[i]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j + 1))))->getError();
         double Correlation =
            Results[i]->correlation(Form("SignalInclusiveYield%dJet", j), Form("SignalInclusiveYield%dJet", j + 1));

         double Value = Value1 - Value2;
         double Error = sqrt(Error1 * Error1 + Error2 * Error2 - 2 * Error1 * Error2 * Correlation);

         cout << " & $" << Value << " \\pm " << Error << "$ ";
      }
         
      double Value =
         ((RooRealVar *)(Results[i]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
      double Error =
         ((RooRealVar *)(Results[i]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getError();

      cout << " & $" << Value << " \\pm " << Error << "$ ";

      if(i % 3 == 2)
         cout << "\\\\\\hline\\hline" << endl;
      else
         cout << " \\\\\\hline" << endl;
   }

   cout << "\\end{tabular}" << endl;
   cout << "\\caption{Unconstrained fit, threshold " << Threshold << " GeV, exclusive yields}" << endl;
   cout << "\\end{sidewaystable}" << endl;
   cout << "\\end{landscape}" << endl;

   cout << "\\clearpage" << endl;
   cout << endl;


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
