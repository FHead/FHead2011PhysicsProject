#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

#include "TFile.h"

#include "RooFitResult.h"
#include "RooRealVar.h"
using namespace RooFit;

void YieldTable()
{
   vector<string> Files;
   Files.push_back("Data/ResultFile_pf_15.root");
   Files.push_back("Data/ResultFileC_pf_15.root");
   Files.push_back("MC/ResultFile_pf_15.root");
   Files.push_back("MC/ResultFileC_pf_15.root");
   Files.push_back("Data/ResultFile_pf_30.root");
   Files.push_back("Data/ResultFileC_pf_30.root");
   Files.push_back("MC/ResultFile_pf_30.root");
   Files.push_back("MC/ResultFileC_pf_30.root");

   vector<string> Tags;
   Tags.push_back("Data, 15 GeV, normal");
   Tags.push_back("Data, 15 GeV, MT cut");
   Tags.push_back("MC, 15 GeV, normal");
   Tags.push_back("MC, 15 GeV, MT cut");
   Tags.push_back("Data, 30 GeV, normal");
   Tags.push_back("Data, 30 GeV, MT cut");
   Tags.push_back("MC, 30 GeV, normal");
   Tags.push_back("MC, 30 GeV, MT cut");

   TFile F1(Files[0].c_str());
   TFile F2(Files[1].c_str());
   TFile F3(Files[2].c_str());
   TFile F4(Files[3].c_str());
   TFile F5(Files[4].c_str());
   TFile F6(Files[5].c_str());
   TFile F7(Files[6].c_str());
   TFile F8(Files[7].c_str());

   vector<RooFitResult *> Results;
   Results.push_back((RooFitResult *)F1.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F2.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F3.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F4.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F5.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F6.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F7.Get("UnconstrainedFitResult"));
   Results.push_back((RooFitResult *)F8.Get("UnconstrainedFitResult"));

   cout << fixed << setprecision(0);

   cout << "\\begin{landscape}" << endl;
   cout << "\\begin{table}" << endl;
   cout << "\\begin{tabular}{|c||c|c|c|c|c|}" << endl;
   cout << "\\hline" << endl;
   cout << "   & $\\ge 0$ & $\\ge 1$ & $\\ge 2$ & $\\ge 3$ & $\\ge 4$ \\\\\\hline\\hline" << endl;

   for(int i = 0; i < (int)Files.size() && i < (int)Tags.size(); i++)
   {
      cout << fixed << setprecision(0);
      cout << Tags[i];

      for(int j = 0; j < 5; j++)
      {
         double Value =
            ((RooRealVar *)(Results[i]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getVal();
         double Error =
            ((RooRealVar *)(Results[i]->floatParsFinal().find(Form("SignalInclusiveYield%dJet", j))))->getError();

         cout << " & $" << Value << " \\pm " << Error << "$ ";
      }

      cout << "\\\\" << endl;

      if(i % 2 == 1)
      {
         cout << fixed << setprecision(3) << setfill('0');
         cout << "Central value";

         for(int j = 0; j < 5; j++)
         {
            TString Parameter = Form("SignalInclusiveYield%dJet", j);

            double Value1 = ((RooRealVar *)(Results[i-1]->floatParsFinal().find(Parameter)))->getVal();
            double Value2 = ((RooRealVar *)(Results[i]->floatParsFinal().find(Parameter)))->getVal();

            cout << " & $" << Value2 / Value1 << "$ ";
         }

         cout << "\\\\" << endl;
      }
   }

   cout << "\\hline" << endl;

   cout << "\\end{tabular}" << endl;
   cout << "\\caption{Unconstrained fit, inclusive yields}" << endl;
   cout << "\\end{table}" << endl;
   cout << "\\end{landscape}" << endl;
   cout << "\\clearpage" << endl;

   cout << "\\begin{landscape}" << endl;
   cout << "\\begin{table}" << endl;
   cout << "\\begin{tabular}{|c||c|c|c|c|c|}" << endl;
   cout << "\\hline" << endl;
   cout << "   & $= 0$ & $= 1$ & $= 2$ & $= 3$ & $\\ge 4$ \\\\\\hline\\hline" << endl;

   for(int i = 0; i < (int)Files.size() && i < (int)Tags.size(); i++)
   {
      cout << fixed << setprecision(0);
      cout << Tags[i];

      for(int j = 0; j < 5 - 1; j++)
      {
         TString Parameter1 = Form("SignalInclusiveYield%dJet", j);
         TString Parameter2 = Form("SignalInclusiveYield%dJet", j + 1);

         double Value1 = ((RooRealVar *)(Results[i]->floatParsFinal().find(Parameter1)))->getVal();
         double Error1 = ((RooRealVar *)(Results[i]->floatParsFinal().find(Parameter1)))->getError();
         double Value2 = ((RooRealVar *)(Results[i]->floatParsFinal().find(Parameter2)))->getVal();
         double Error2 = ((RooRealVar *)(Results[i]->floatParsFinal().find(Parameter2)))->getError();
         double Correlation = Results[i]->correlation(Parameter1, Parameter2);
         double Value = Value1 - Value2;
         double Error = sqrt(Error1 * Error1 + Error2 * Error2 - Error1 * Error2 * Correlation);

         cout << " & $" << Value << " \\pm " << Error << "$ ";
      }
            
      double LastValue = ((RooRealVar *)(Results[i]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
      double LastError = ((RooRealVar *)(Results[i]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getError();

      cout << " & $" << LastValue << " \\pm " << LastError << "$ \\\\" << endl;

      if(i % 2 == 1)
      {
         cout << fixed << setprecision(3) << setfill('0');
         cout << "Central value";

         for(int j = 0; j < 5 - 1; j++)
         {
            TString Parameter1 = Form("SignalInclusiveYield%dJet", j);
            TString Parameter2 = Form("SignalInclusiveYield%dJet", j + 1);

            double Value11 = ((RooRealVar *)(Results[i-1]->floatParsFinal().find(Parameter1)))->getVal();
            double Value21 = ((RooRealVar *)(Results[i]->floatParsFinal().find(Parameter1)))->getVal();
            double Value12 = ((RooRealVar *)(Results[i-1]->floatParsFinal().find(Parameter2)))->getVal();
            double Value22 = ((RooRealVar *)(Results[i]->floatParsFinal().find(Parameter2)))->getVal();

            cout << " & $" << (Value22 - Value21) / (Value12 - Value11) << "$ ";
         }

         double LastValue1 = ((RooRealVar *)(Results[i-1]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
         double LastValue2 = ((RooRealVar *)(Results[i]->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
         cout << " & $" << LastValue2 / LastValue1 << "$ ";

         cout << "\\\\" << endl;
      }
   }

   cout << "\\hline" << endl;

   cout << "\\end{tabular}" << endl;
   cout << "\\caption{Unconstrained fit, inclusive yields}" << endl;
   cout << "\\end{table}" << endl;
   cout << "\\end{landscape}" << endl;
   cout << "\\clearpage" << endl;

   F8.Close();
   F7.Close();
   F6.Close();
   F5.Close();
   F4.Close();
   F3.Close();
   F2.Close();
   F1.Close();
}



