#include <fstream>
#include <vector>
#include <string>
using namespace std;

#include "TF1.h"
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TGraphErrors.h"

struct ExponentResult;
void SummarizeScan(string ScanList, string OutputRootFile = "Output.root");
ExponentResult FitSingleExperiment(double SignalYieldValue[4], double SignalYieldError[4], int FitResult[4]);

struct ExponentResult
{
   double ExpValue;
   double ExpError;
   double Chisquare;
};

void SummarizeScan(string ScanList, string OutputRootFile)
{
   vector<double> Values;
   vector<string> Files;

   ifstream in(ScanList.c_str());

   while(in)
   {
      double value = -1000;
      string file = "";

      in >> value >> file;

      if(value < -500 || file == "")
         continue;

      Values.push_back(value);
      Files.push_back("IndividualParameters/" + file);
   }

   in.close();

   double MeanSignalYield[] = {6600 * 0.3, 1308 * 0.3, 256.8 * 0.3, 54.96 * 0.3};

   TFile F(("SummaryTree/" + OutputRootFile).c_str(), "RECREATE");

   TTree Tree("Tree", "Tree");

   double ParameterValue = 0;
   double MeanRelativeSignalYield[4] = {0};
   double SigmaRelativeSignalYield[4] = {0};
   double MeanRelativeSignalYieldGood[4] = {0};
   double SigmaRelativeSignalYieldGood[4] = {0};
   double FitSuccessRate[4] = {0};
   double ExponentMean = 0;
   double ExponentSigma = 0;

   Tree.Branch("ParameterValue", &ParameterValue, "ParameterValue/D");
   Tree.Branch("MeanRelativeSignalYield", &MeanRelativeSignalYield, "MeanRelativeSignalYield[4]/D");
   Tree.Branch("SigmaRelativeSignalYield", &SigmaRelativeSignalYield, "SigmaRelativeSignalYield[4]/D");
   Tree.Branch("MeanRelativeSignalYieldGood", &MeanRelativeSignalYieldGood, "MeanRelativeSignalYieldGood[4]/D");
   Tree.Branch("SigmaRelativeSignalYieldGood", &SigmaRelativeSignalYieldGood, "SigmaRelativeSignalYieldGood[4]/D");
   Tree.Branch("FitSuccessRate", &FitSuccessRate, "FitSuccessRate[4]/D");
   Tree.Branch("ExponentMean", &ExponentMean, "ExponentMean/D");
   Tree.Branch("ExponentSigma", &ExponentSigma, "ExponentSigma/D");

   for(unsigned int i = 0; i < Values.size(); i++)
   {
      ParameterValue = Values[i];

      TChain Chain("FitResult", "FitResult");
      Chain.AddFile(Files[i].c_str());

      TH1D RelativeSignalYieldHistogram("RelativeSignalYieldHistogram", "Meow!", 200, -2, 2);

      for(int j = 0; j < 4; j++)
      {
         Chain.Draw(Form("(SignalYieldValue[%d]-%f)/%f>>RelativeSignalYieldHistogram",
                  j, MeanSignalYield[j], MeanSignalYield[j]),
               "", "");

         TF1 F1(Form("F%d%d1", i, j), "gaus");

         RelativeSignalYieldHistogram.Fit(&F1);

         MeanRelativeSignalYield[j] = F1.GetParameter(1);
         SigmaRelativeSignalYield[j] = F1.GetParameter(2);

         Chain.Draw(Form("(SignalYieldValue[%d]-%f)/%f>>RelativeSignalYieldHistogram",
                  j, MeanSignalYield[j], MeanSignalYield[j]),
               Form("FitStatus[%d] == 3", j), "");

         TF1 F2(Form("F%d%d2", i, j), "gaus");

         RelativeSignalYieldHistogram.Fit(&F2);

         MeanRelativeSignalYieldGood[j] = F2.GetParameter(1);
         SigmaRelativeSignalYieldGood[j] = F2.GetParameter(2);

         FitSuccessRate[j] = Chain.Draw(Form("FitStatus[%d]", j), Form("FitStatus[%d] == 3", j)) / 1000.0;
      }

      TH1D ExponentHistogram("ExponentHistogram", "ExponentHistogram", 100, -2.5, -0.5);

      double SignalYieldValue[4];
      double SignalYieldError[4];
      int FitStatus[4];

      Chain.SetBranchAddress("SignalYieldValue", SignalYieldValue);
      Chain.SetBranchAddress("SignalYieldError", SignalYieldError);
      Chain.SetBranchAddress("FitStatus", FitStatus);

      int numberofentries = Chain.GetEntries();
      for(int j = 0; j < numberofentries; j++)
      {
         Chain.GetEntry(j);

         ExponentResult exponent = FitSingleExperiment(SignalYieldValue, SignalYieldError, FitStatus);

         if(exponent.Chisquare > 50)
            continue;

         ExponentHistogram.Fill(exponent.ExpValue);
      }

      TF1 ExponentGaussFit("ExponentGaussFit", "gaus");

      ExponentHistogram.Fit(&ExponentGaussFit);

      ExponentMean = ExponentGaussFit.GetParameter(1);
      ExponentSigma = ExponentGaussFit.GetParameter(2);

      Tree.Fill();
   }

   Tree.SetMarkerStyle(20);

   F.Write();

   F.Close();
}

ExponentResult FitSingleExperiment(double SignalYieldValue[4], double SignalYieldError[4], int FitResult[4])
{
   ExponentResult result;

   TGraphErrors graph;
   for(int i = 0; i < 4; i++)
   {
      graph.SetPoint(i, i + 1, SignalYieldValue[i]);
      graph.SetPointError(i, 0, SignalYieldError[i]);
   }

   TF1 expo("exponentfit", "expo");

   graph.Fit(&expo);

   result.ExpValue = expo.GetParameter(1);
   result.ExpError = expo.GetParError(1);
   result.Chisquare = expo.GetChisquare();

   return result;
}

