#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TCanvas.h"

#include "RooDataSet.h"
#include "RooFitResult.h"
#include "RooArgSet.h"
#include "RooRealVar.h"
#include "RooLorentzian.h"
#include "RooVoigtian.h"
#include "RooAddPdf.h"
#include "RooPolynomial.h"
#include "RooExponential.h"
#include "RooPlot.h"
#include "RooBifurGauss.h"
#include "RooCruijff.h"
#include "RooCBShape.h"
#include "RooReverseLandau.h"

using namespace RooFit;

struct FitResult;
void FitZPeak(string OutputFileName = "30pb.root", string lumi = "30");
vector<string> ReadFileNames(string FileList);
FitResult FitZPeak_Cruijff(string Rootfile, string BackgroundRootFile);

struct FitResult
{
   double SignalInput;
   double SignalYieldValue;
   double SignalYieldError;

   double AlphaLValue;
   double AlphaLError;
   double SigmaLValue;
   double SigmaLError;
   double AlphaRValue;
   double AlphaRError;
   double SigmaRValue;
   double SigmaRError;

   double PeakWidthValue;
   double PeakWidthError;
   double PeakSigmaValue;
   double PeakSigmaError;
   double PeakAlphaValue;
   double PeakAlphaError;
   double NValue;
   double NError;

   double ExponentialValue;
   double ExponentialError;

   int FitStatus;
};

void FitZPeak(string OutputFileName, string lumi)
{
   vector<string> SignalFileNames[4];
   SignalFileNames[0] = ReadFileNames("Signal_" + lumi + "_1.txt");
   SignalFileNames[1] = ReadFileNames("Signal_" + lumi + "_2.txt");
   SignalFileNames[2] = ReadFileNames("Signal_" + lumi + "_3.txt");
   SignalFileNames[3] = ReadFileNames("Signal_" + lumi + "_4.txt");

   vector<string> BackgroundFileNames[4];
   BackgroundFileNames[0] = ReadFileNames("Background_" + lumi + "_1.txt");
   BackgroundFileNames[1] = ReadFileNames("Background_" + lumi + "_2.txt");
   BackgroundFileNames[2] = ReadFileNames("Background_" + lumi + "_3.txt");
   BackgroundFileNames[3] = ReadFileNames("Background_" + lumi + "_4.txt");

   for(int i = 0; i < 4; i++)
      while(BackgroundFileNames[i].size() < SignalFileNames[i].size())
         BackgroundFileNames[i].insert(BackgroundFileNames[i].end(),
            BackgroundFileNames[i].begin(), BackgroundFileNames[i].end());

   vector<FitResult> results[4];

   for(int i = 0; i < 4; i++)
   {
      for(unsigned int j = 0; j < 10; j++)
      {
         FitResult result = FitZPeak_Cruijff(SignalFileNames[i][j], BackgroundFileNames[i][j]);

         results[i].push_back(result);
      }
   }

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree *Tree = new TTree("FitResult", "FitResult");

   double SignalYieldValue[4], SignalYieldError[4];
   Tree->Branch("SignalYieldValue", &SignalYieldValue, "SignalYieldValue[4]/D");
   Tree->Branch("SignalYieldError", &SignalYieldError, "SignalYieldError[4]/D");

   int SignalInput[4];
   Tree->Branch("SignalInput", &SignalInput, "SignalInput[4]/I");

   int FitStatus[4];
   Tree->Branch("FitStatus", &FitStatus, "FitStatus[4]/I");

   unsigned int size = results[0].size();
   for(unsigned int i = 1; i < 4; i++)
      if(size < results[i].size())
         size = results[i].size();

   for(unsigned int i = 0; i < size; i++)
   {
      // clear variables
      for(int j = 0; j < 4; j++)
      {
         SignalYieldValue[j] = -1;
         SignalYieldError[j] = -1;
         SignalInput[j] = -1;
         FitStatus[j] = -1;
      }

      // fill variables
      for(int j = 0; j < 4; j++)
      {
         SignalYieldValue[j] = results[j][i].SignalYieldValue;
         SignalYieldError[j] = results[j][i].SignalYieldError;
         SignalInput[j] = results[j][i].SignalInput;
         FitStatus[j] = results[j][i].FitStatus;
      }

      Tree->Fill();
   }

   OutputFile.Write();
   OutputFile.Close();
}

vector<string> ReadFileNames(string FileList)
{
   vector<string> FileNames;

   ifstream in(FileList.c_str());

   while(in)
   {
      char ch[10000] = "";
      in.getline(ch, 9999, '\n');

      if(string(ch) != "")
         FileNames.push_back(ch);
   }

   in.close();

   return FileNames;
}

FitResult FitZPeak_Cruijff(string RootFile, string BackgroundRootFile)
{
   RooRealVar mll("mll", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooArgSet TreeVarSet(mll);

   TChain ZTree("MllTree", "MllTree");
   ZTree.AddFile(RootFile.c_str());
   RooDataSet dataset("ZCandidates", "ZCandidates", &ZTree, TreeVarSet);

   TChain BackgroundTree("MllTree", "MllTree");
   BackgroundTree.AddFile(BackgroundRootFile.c_str());
   RooDataSet BackgroundDataset("BackgroundCandidates", "BackgroundCandidates", &BackgroundTree, TreeVarSet);

   dataset.append(BackgroundDataset);

   RooRealVar PeakPosition("PeakPosition", "Z peak position", 90, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.45);
   RooRealVar AlphaL("AlphaL", "AlphaL", 0.56);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.27);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.30);
   RooCruijff MainZPeak("MainZPeak", "MainZPeak", mll, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);
   RooRealVar PeakYield("PeakYield", "Peak Yield", 1000, 0, 1000000);

   RooRealVar BackgroundExp("BackgroundExp", "Background exp", -0.009, -10.0, 0.0);
   RooExponential Background("Background", "Background", mll, BackgroundExp);
   RooRealVar BackgroundYield("BackgroundYield", "Background Yield", 100, 0, 1000000);

   RooArgList Distributions(MainZPeak, Background);
   RooArgList Yields(PeakYield, BackgroundYield);
   RooAddPdf TotalPDF("TotalPDF", "Fit function!", Distributions, Yields);

   RooFitResult *fitresult = TotalPDF.fitTo(dataset, Save());

   FitResult result;

   result.SignalInput = ZTree.GetEntries();
   result.SignalYieldValue = PeakYield.getVal();
   result.SignalYieldError = PeakYield.getError();

   result.AlphaLValue = AlphaL.getVal();
   result.AlphaLError = AlphaL.getError();
   result.SigmaLValue = SigmaL.getVal();
   result.SigmaLError = SigmaL.getError();
   result.AlphaRValue = AlphaR.getVal();
   result.AlphaRError = AlphaR.getError();
   result.SigmaRValue = SigmaR.getVal();
   result.SigmaRError = SigmaR.getError();

   result.ExponentialValue = BackgroundExp.getVal();
   result.ExponentialError = BackgroundExp.getError();

   result.FitStatus = fitresult->covQual();

   return result;
}

