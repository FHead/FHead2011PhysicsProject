#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "TFile.h"

#include "RooRealVar.h"
#include "RooFitResult.h"
using namespace RooFit;

void CollectResult2(string Threshold = "30")
{
   // for the unconstrained yield tables

   vector<string> Labels;
   vector<RooFitResult *> Results;

   Labels.push_back("unconstrained");
   Labels.push_back("unconstr. unsmeared");
   Labels.push_back("unconstr. weighted");
   Labels.push_back("unconstr. weighted, unsmeared");

   TFile F2(("NoUnfold/Normal/ResultFileU_pf_" + Threshold + ".root").c_str());
   TFile F8(("Z2Unfold/Normal/ResultFileU_pf_" + Threshold + ".root").c_str());
   TFile F11(("NoUnfold/Normal/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F17(("Z2Unfold/Normal/ResultFileW_pf_" + Threshold + ".root").c_str());

   Results.push_back((RooFitResult *)F2.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F8.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F11.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F17.Get("UnconstrainedFitResult"));

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

   F17.Close();
   F11.Close();
   F8.Close();
   F2.Close();
}
