#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

#include "TFile.h"

#include "RooRealVar.h"
#include "RooFitResult.h"
using namespace RooFit;

void CollectResult4();
void CollectResult4(string Threshold, vector<int> JESMC, vector<int> PileUp);

void CollectResult4()
{
   vector<int> JESMC;
   JESMC.push_back(3);
   JESMC.push_back(4);
   JESMC.push_back(9);
   JESMC.push_back(15);
   JESMC.push_back(20);

   vector<int> PileUp;
   PileUp.push_back(-5);
   PileUp.push_back(5);
   PileUp.push_back(10);
   PileUp.push_back(20);
   PileUp.push_back(20);

   // CollectResult4("15", JESMC, PileUp);

   JESMC.clear();
   JESMC.push_back(1);
   JESMC.push_back(4);
   JESMC.push_back(6);
   JESMC.push_back(8);
   JESMC.push_back(14);

   PileUp.clear();
   
   CollectResult4("30", JESMC, PileUp);
}

void CollectResult4(string Threshold, vector<int> JESMC, vector<int> PileUp)
{
   TFile FCentral(("NoJEC_Unfold_Weighted/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile FWP(("NoJEC_Unfold_WeightPlus/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile FWM(("NoJEC_Unfold_WeightMinus/ResultFileW_pf_" + Threshold + ".root").c_str());

   TFile FJESCentral(("NoJEC_Unfold_Weighted/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile FJESP(("JECPlus_Unfold_Weighted/ResultFileW_pf_" + Threshold + ".root").c_str());
   TFile FJESM(("JECMinus_Unfold_Weighted/ResultFileW_pf_" + Threshold + ".root").c_str());

   cout << fixed << setprecision(0);

   RooFitResult *CentralResult = (RooFitResult *)FCentral.Get("UnconstrainedFitResult");
   RooFitResult *WPResult = (RooFitResult *)FWP.Get("UnconstrainedFitResult");
   RooFitResult *WMResult = (RooFitResult *)FWM.Get("UnconstrainedFitResult");
   RooFitResult *JESCentralResult = (RooFitResult *)FJESCentral.Get("UnconstrainedFitResult");
   RooFitResult *JESPResult = (RooFitResult *)FJESP.Get("UnconstrainedFitResult");
   RooFitResult *JESMResult = (RooFitResult *)FJESM.Get("UnconstrainedFitResult");

   for(int j = 0; j < 4; j++)
   {
      TString Jet1 = Form("SignalInclusiveYield%dJet", j);
      TString Jet2 = Form("SignalInclusiveYield%dJet", j + 1);

      double Value1 = ((RooRealVar *)(CentralResult->floatParsFinal().find(Jet1)))->getVal();
      double Error1 = ((RooRealVar *)(CentralResult->floatParsFinal().find(Jet1)))->getError();
      double Value2 = ((RooRealVar *)(CentralResult->floatParsFinal().find(Jet2)))->getVal();
      double Error2 = ((RooRealVar *)(CentralResult->floatParsFinal().find(Jet2)))->getError();
      double Correlation = CentralResult->correlation(Jet1, Jet2);
      double Value = Value1 - Value2;
      double Error = sqrt(Error1 * Error1 + Error2 * Error2 - 2 * Error1 * Error2 * Correlation);
      
      double JESValue1 = ((RooRealVar *)(JESCentralResult->floatParsFinal().find(Jet1)))->getVal();
      double JESValue2 = ((RooRealVar *)(JESCentralResult->floatParsFinal().find(Jet2)))->getVal();
      double JESValue = JESValue1 - JESValue2;

      double WMValue1 = ((RooRealVar *)(WMResult->floatParsFinal().find(Jet1)))->getVal();
      double WMValue2 = ((RooRealVar *)(WMResult->floatParsFinal().find(Jet2)))->getVal();
      double WMValue = WMValue1 - WMValue2;
      double WPValue1 = ((RooRealVar *)(WPResult->floatParsFinal().find(Jet1)))->getVal();
      double WPValue2 = ((RooRealVar *)(WPResult->floatParsFinal().find(Jet2)))->getVal();
      double WPValue = WPValue1 - WPValue2;
      double WeightPercentage = (fabs(WPValue - WMValue)) / Value * 100;

      double JESMValue1 = ((RooRealVar *)(JESMResult->floatParsFinal().find(Jet1)))->getVal();
      double JESMValue2 = ((RooRealVar *)(JESMResult->floatParsFinal().find(Jet2)))->getVal();
      double JESMValue = JESMValue1 - JESMValue2;
      double JESPValue1 = ((RooRealVar *)(JESPResult->floatParsFinal().find(Jet1)))->getVal();
      double JESPValue2 = ((RooRealVar *)(JESPResult->floatParsFinal().find(Jet2)))->getVal();
      double JESPValue = JESPValue1 - JESPValue2;
      double JESPercentage = (fabs(JESPValue - JESValue) + fabs(JESValue - JESMValue)) / 2 / JESValue * 100;

      cout << j << " & " << Value << " & " << Error;
      cout << " & $\\pm$" << JESMC[j] << "\\%";
      cout << " & $\\pm$" << JESPercentage << "\\%";
      if((int)PileUp.size() > j)
      {
         cout << " & ";
         if(PileUp[j] > 0)
            cout << "+";
         cout << PileUp[j] << "\\%";
      }
      cout << " & $\\pm$" << WeightPercentage << "\\%";
      cout << " \\\\" << endl;
   }
         
   double Value = ((RooRealVar *)(CentralResult->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
   double Error = ((RooRealVar *)(CentralResult->floatParsFinal().find("SignalInclusiveYield4Jet")))->getError();

   double WMValue = ((RooRealVar *)(WMResult->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
   double WPValue = ((RooRealVar *)(WPResult->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
   double WeightPercentage = (fabs(WPValue - WMValue)) / Value * 100;

   double JESMValue = ((RooRealVar *)(JESMResult->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
   double JESPValue = ((RooRealVar *)(JESPResult->floatParsFinal().find("SignalInclusiveYield4Jet")))->getVal();
   double JESPercentage = (fabs(JESPValue - Value) - fabs(Value - JESMValue)) / 2 / Value * 100;

   cout << " $\\geq$ 4 & " << Value << " & " << Error;
   cout << " & $\\pm$" << JESMC[4] << "\\%";
   cout << " & $\\pm$" << JESPercentage << "\\%";
   if(PileUp.size() > 4)
   {
      cout << " & ";
      if(PileUp[4] > 0)
         cout << "+";
      cout << PileUp[4] << "\\%";
   }
   cout << " & $\\pm$" << WeightPercentage << "\\%";
   cout << " \\\\" << endl;

   cout << "\\end{tabular}" << endl;
   cout << "\\caption{Unconstrained fit, threshold " << Threshold << " GeV, exclusive yields}" << endl;
   cout << "\\end{table}" << endl;
   cout << "\\end{landscape}" << endl;

   cout << "\\clearpage" << endl;
   cout << endl;

   FCentral.Close();
}
