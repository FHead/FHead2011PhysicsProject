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

   Labels.push_back("Unweighted, No unfolding, Normal");
   Labels.push_back("Weighted, No unfolding, Normal");
   Labels.push_back("Weighted, No unfolding, Minus");
   Labels.push_back("Weighted, No unfolding, Plus");
   Labels.push_back("Unweighted, Unfolding, Normal");
   Labels.push_back("Weighted, Unfolding, Normal");
   Labels.push_back("Weighted, Unfolding, Minus");
   Labels.push_back("Weighted, Unfolding, Plus");
   Labels.push_back("Weighted, Unfolding, JES Minus");
   Labels.push_back("Weighted, Unfolding, JES Plus");

   TFile F1(("NoJEC_NoUnfold_Unweighted/ResultFileU_pf_" + Threshold + ".root").c_str());
   TFile F2(("NoJEC_NoUnfold_Weighted/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F3(("NoJEC_NoUnfold_WeightMinus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F4(("NoJEC_NoUnfold_WeightPlus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F5(("NoJEC_Unfold_Unweighted/ResultFileU_pf_" + Threshold + ".root").c_str());
   TFile F6(("NoJEC_Unfold_Weighted/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F7(("NoJEC_Unfold_WeightMinus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F8(("NoJEC_Unfold_WeightPlus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F9(("JECMinus_Unfold_Weighted/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F10(("JECPlus_Unfold_Weighted/ResultFileW_pf_" + Threshold + ".root").c_str());

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

   cout << fixed << setprecision(0);

   cout << "\\begin{landscape}" << endl;
   cout << "\\begin{table}" << endl;
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

      cout << " \\\\\\hline" << endl;
   }

   cout << "\\end{tabular}" << endl;
   cout << "\\caption{Unconstrained fit, threshold " << Threshold << " GeV, inclusive yields}" << endl;
   cout << "\\end{table}" << endl;
   cout << "\\end{landscape}" << endl;

   cout << "\\clearpage" << endl;
   cout << endl;

   cout << "\\begin{landscape}" << endl;
   cout << "\\begin{table}" << endl;
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

      cout << " \\\\\\hline" << endl;
   }

   cout << "\\end{tabular}" << endl;
   cout << "\\caption{Unconstrained fit, threshold " << Threshold << " GeV, exclusive yields}" << endl;
   cout << "\\end{table}" << endl;
   cout << "\\end{landscape}" << endl;

   cout << "\\clearpage" << endl;
   cout << endl;

   F8.Close();
   F7.Close();
   F6.Close();
   F5.Close();
   F4.Close();
   F3.Close();
   F2.Close();
   F1.Close();
}
