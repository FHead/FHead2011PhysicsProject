#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "TFile.h"

#include "RooRealVar.h"
#include "RooFitResult.h"
using namespace RooFit;

void CollectResult3();
void CollectResult3(string Threshold);

void CollectResult3()
{
   CollectResult3("15");
   CollectResult3("30");
}

void CollectResult3(string Threshold)
{
   vector<string> Labels;
   vector<RooFitResult *> Results;

   Labels.push_back("unconstrained");
   Labels.push_back("");
   Labels.push_back("");
   Labels.push_back("unconstr. unsmeared");
   Labels.push_back("");
   Labels.push_back("");

   TFile F10(("NoJEC_NoUnfold_WeightMinus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F11(("NoJEC_NoUnfold_Weighted/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F12(("NoJEC_NoUnfold_WeightPlus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F16(("NoJEC_Unfold_WeightMinus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F17(("NoJEC_Unfold_Weighted/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile F18(("NoJEC_Unfold_WeightPlus/ResultFileW_pf_" + Threshold + ".root").c_str());

   Results.push_back((RooFitResult *)F10.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F11.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F12.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F16.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F17.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F18.Get("UnconstrainedFitResult"));

   cout << fixed << setprecision(0);

   cout << "\\begin{table}[h!]" << endl;
   cout << "\\center" << endl;
   cout << "\\begin{tabular}{|c|c|c|c|c|c|}" << endl;
   cout << "\\hline" << endl;
   cout << "Njets   & $\\ge 0$ & $\\ge 1$ & $\\ge 2$ & $\\ge 3$ & $\\ge 4$ \\\\\\hline" << endl;

   for(int i = 0; i < (int)Results.size(); i = i + 3)
   {
      cout << Labels[i];

      for(int j = 0; j < 5; j++)
      {
         double MinusValue =
            ((RooRealVar *)(Results[i]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getVal();
         double NormalValue =
            ((RooRealVar *)(Results[i+1]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getVal();
         double PlusValue =
            ((RooRealVar *)(Results[i+2]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getVal();

         cout << " & $" << NormalValue << "^{~";
         if(MinusValue - NormalValue > 0)
            cout << "+";
         cout << MinusValue - NormalValue << "}_{~";
         if(PlusValue - NormalValue > 0)
            cout << "+";
         cout << PlusValue - NormalValue << "}$";
      }

      cout << "\\\\" << endl;

      for(int j = 0; j < 5; j++)
      {
         double Error =
            ((RooRealVar *)(Results[i+1]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getError();

         cout << " & ($\\pm$ " << Error << ")";
      }

      cout << " \\\\\\hline" << endl;
   }

   cout << "\\end{tabular}" << endl;
   cout << "\\end{table}" << endl;

   cout << "\\clearpage" << endl;
   cout << endl;

   cout << "\\begin{landscape}" << endl;
   cout << "\\begin{table}" << endl;
   cout << "\\begin{tabular}{|c||c|c|c|c|c|}" << endl;
   cout << "\\hline" << endl;
   cout << "   & $= 0$ & $= 1$ & $= 2$ & $= 3$ & $\\ge 4$ \\\\\\hline\\hline" << endl;

   for(int i = 0; i < (int)Results.size(); i = i + 3)
   {
      cout << Labels[i];

      for(int j = 0; j < 4; j++)
      {
         TString String1 = Form("SignalInclusiveYield%dJet", j);
         TString String2 = Form("SignalInclusiveYield%dJet", j + 1);

         double NormalValue1 = ((RooRealVar *)(Results[i+1]->floatParsFinal().find(String1)))->getVal();
         double NormalValue2 = ((RooRealVar *)(Results[i+1]->floatParsFinal().find(String2)))->getVal();
         double PlusValue1 = ((RooRealVar *)(Results[i+2]->floatParsFinal().find(String1)))->getVal();
         double PlusValue2 = ((RooRealVar *)(Results[i+2]->floatParsFinal().find(String2)))->getVal();
         double MinusValue1 = ((RooRealVar *)(Results[i]->floatParsFinal().find(String1)))->getVal();
         double MinusValue2 = ((RooRealVar *)(Results[i]->floatParsFinal().find(String2)))->getVal();

         double NormalValue = NormalValue1 - NormalValue2;
         double PlusValue = PlusValue1 - PlusValue2;
         double MinusValue = MinusValue1 - MinusValue2;
         
         cout << " & $" << NormalValue << "^{~";
         if(MinusValue - NormalValue > 0)
            cout << "+";
         cout << MinusValue - NormalValue << "}_{~";
         if(PlusValue - NormalValue > 0)
            cout << "+";
         cout << PlusValue - NormalValue << "}$";
      }
         
      double NormalValue =
         ((RooRealVar *)(Results[i+1]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
      double PlusValue =
         ((RooRealVar *)(Results[i+2]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
      double MinusValue =
         ((RooRealVar *)(Results[i]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
         
      cout << " & $" << NormalValue << "^{~";
      if(MinusValue - NormalValue > 0)
         cout << "+";
      cout << MinusValue - NormalValue << "}_{~";
      if(PlusValue - NormalValue > 0)
         cout << "+";
      cout << PlusValue - NormalValue << "}$";
      cout << "\\\\" << endl;

      for(int j = 0; j < 4; j++)
      {
         TString String1 = Form("SignalInclusiveYield%dJet", j);
         TString String2 = Form("SignalInclusiveYield%dJet", j + 1);

         double Error1 = ((RooRealVar *)(Results[i+1]->floatParsFinal().find(String1)))->getError();
         double Error2 = ((RooRealVar *)(Results[i+1]->floatParsFinal().find(String2)))->getError();
         double Correlation = Results[i+1]->correlation(String1, String2);

         double Error = sqrt(Error1 * Error1 + Error2 * Error2 - 2 * Error1 * Error2 * Correlation);

         cout << " & ($\\pm$ " << Error << ")";
      }

      double Error =
         ((RooRealVar *)(Results[i+1]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getError();
      cout << " & ($\\pm$ " << Error << ")";

      cout << " \\\\\\hline" << endl;
   }

   cout << "\\end{tabular}" << endl;
   cout << "\\caption{Unconstrained fit, threshold " << Threshold << " GeV, exclusive yields}" << endl;
   cout << "\\end{table}" << endl;
   cout << "\\end{landscape}" << endl;

   cout << "\\clearpage" << endl;
   cout << endl;


   F18.Close();
   F17.Close();
   F16.Close();
   F12.Close();
   F11.Close();
   F10.Close();
}
