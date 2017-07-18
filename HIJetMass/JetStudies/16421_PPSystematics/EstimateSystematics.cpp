#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TF1.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"

#include "SetStyle.h"
#include "Code/DrawRandom.h"
#include "PlotHelper3.h"
#include "ProgressBar.h"

#include "ReadTree.h"
#include "JetEnergyScale.h"

#define BIN 20
#define SYSBIN 160
#define WEIGHTBIN 400
#define WEIGHTMIN -15
#define WEIGHTMAX 25

#define TypeQuarkGluon 0
#define TypeJES 1
#define TypeJER 2
#define TypeDR 3
#define TypeJetEta 4

#define TypeLinear 0
#define TypeQuadratic 1
#define TypeExponential 2

struct Box;
int main(int argc, char *argv[]);
vector<pair<double, double>> QuadraticError(PdfFileHelper &PdfFile,
   vector<double> HN, vector<double> HM, vector<double> HN2, vector<double> HM2, int FunctionType);
double GetBinCenter(int B);
double GetSysBinCenter(int B);
int FindBin(double X);
void TranscribeQuadratic(vector<pair<double, double>> V, TGraphAsymmErrors *G);
void AddPlot(PdfFileHelper &PdfFile, vector<double> N, vector<double> M, vector<double> N2, vector<double> M2, TGraphAsymmErrors *G);
bool InBox(StraightTreeMessenger &M, Box &B);
bool DRCut(StraightTreeMessenger &M, double Cut = 0.10);

struct Box
{
   double PTMin;
   double PTMax;
   double CentralityMin;
   double CentralityMax;
   Box(double ptmin, double ptmax, double centralitymin, double centralitymax)
      : PTMin(ptmin), PTMax(ptmax), CentralityMin(centralitymin), CentralityMax(centralitymax)
   {
   }
};

int main(int argc, char *argv[])
{
   if(argc != 7)
   {
      cerr << "Usage: " << argv[0] << " BaseFile ModifiedFile SD Type Tag FunctionType" << endl;
      return -1;
   }

   char *BaseFile = argv[1];
   char *ModifiedFile = argv[2];
   int SD = ((argv[3][0] == '0') ? 0 : 7);
   string StringType = argv[4];
   string Tag = argv[5];
   string StringFunctionType = argv[6];

   int Type = TypeQuarkGluon;
   if(StringType == "QuarkGluon")
      Type = TypeQuarkGluon;
   if(StringType == "DR")
      Type = TypeDR;
   if(StringType == "JES")
      Type = TypeJES;
   if(StringType == "JER")
      Type = TypeJER;
   if(StringType == "JetEta")
      Type = TypeJetEta;

   int FunctionType = TypeQuadratic;
   if(StringFunctionType == "Quadratic")
      FunctionType = TypeQuadratic;
   if(StringFunctionType == "Linear")
      FunctionType = TypeLinear;
   if(StringFunctionType == "Exponential")
      FunctionType = TypeExponential;

   Tag = Form("%s_%d", Tag.c_str(), SD);

   SetThesisStyle();

   PdfFileHelper PdfFile(string("Systematics_") + Tag + ".pdf");
   PdfFile.AddTextPage("Systematics");

   TFile F1(BaseFile);
   TFile F2(ModifiedFile);

   StraightTreeMessenger M1(F1, "T", true, SD, -1);
   StraightTreeMessenger M2(F2, "T", true, SD, -1);

   TFile OutputFile((string("OutputFile_") + Tag + ".root").c_str(), "RECREATE");

   vector<Box> Cuts;
   vector<string> Labels;

   double PTEdge[] = {120, 140, 160, 180, 200, 300, 500};
   for(int i = 0; i < 6; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         Cuts.push_back(Box(PTEdge[i], PTEdge[i+1], 0.0, 1.0));
         Labels.push_back(Form("GRatio_C%d_P%d", j, i));
      }
   }

   vector<vector<double>> HN(Cuts.size(), vector<double>(BIN));
   vector<vector<double>> HM(Cuts.size(), vector<double>(BIN));
   vector<vector<double>> HN2(Cuts.size(), vector<double>(BIN));
   vector<vector<double>> HM2(Cuts.size(), vector<double>(BIN));
   vector<vector<double>> HNW(Cuts.size(), vector<double>(WEIGHTBIN));
   vector<vector<double>> HMW(Cuts.size(), vector<double>(WEIGHTBIN));
   vector<double> HNInt(Cuts.size());
   vector<double> HMInt(Cuts.size());

   double M1DRCut = 0.1;
   double M2DRCut = 0.1;

   if(Type == TypeDR)
   {
      M1DRCut = 0.095;
      M2DRCut = 0.105;
   }

   //////////////////////////////////////////
   // First Step: get JES from source tree //
   //////////////////////////////////////////
   
   int EntryCount;
   
   EntryCount = M1.Tree->GetEntries();
   ProgressBar Bar1(cout, EntryCount);
   Bar1.SetStyle(-1);

   JetEnergyScale JES;

   Bar1.Update(0);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar1.Update(iE);
      Bar1.PrintWithMod(300);

      M1.GetEntry(iE);

      if(M1.PassSelection() == false)       continue;

      JES.Fill(M1.JetPT, M1.RawJetPT, M1.JetEta, M1.MCWeight);
   }
   Bar1.Update(EntryCount);
   Bar1.Print();
   Bar1.PrintLine();

   JES.DoFit();

   M1.SetJES(&JES);
   M2.SetJES(&JES);

   //////////////////////////////////////////////////
   // Second step: start filling histograms for M1 //
   //////////////////////////////////////////////////

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar1.Update(iE);
      Bar1.PrintWithMod(300);

      M1.GetEntry(iE);

      if(M1.PassSelection() == false)
         continue;
      if(Type == TypeJetEta && abs(M1.MatchJetEta) >= 0.5)
         continue;
      if(Type == TypeQuarkGluon && abs(M1.Flavor) >= 5)
         continue;

      int iWB = (log(M1.MCWeight) - WEIGHTMIN) / (WEIGHTMAX - WEIGHTMIN) * WEIGHTBIN;
      if(iWB < 0)            iWB = 0;
      if(iWB >= WEIGHTBIN)   iWB = WEIGHTBIN;

      int iB = FindBin(M1.SDMassRatio);

      for(int iC = 0; iC < (int)Cuts.size(); iC++)
      {
         if(InBox(M1, Cuts[iC]) == false)
            continue;

         if(DRCut(M1, M1DRCut) == true)
         {
            HNW[iC][iWB] = HNW[iC][iWB] + 1;
            HNInt[iC] = HNInt[iC] + M1.MCWeight;
            HN[iC][iB] = HN[iC][iB] + M1.MCWeight;
            HN2[iC][iB] = HN2[iC][iB] + M1.MCWeight * M1.MCWeight;
         }
      }
   }
   Bar1.Update(EntryCount);
   Bar1.Print();
   Bar1.PrintLine();

   /////////////////////////////////////////////////
   // Third step: start filling histograms for M2 //
   /////////////////////////////////////////////////
   
   EntryCount = M2.Tree->GetEntries();
   ProgressBar Bar2(cout, EntryCount);
   Bar2.SetStyle(-1);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar2.Update(iE);
      Bar2.PrintWithMod(300);

      M2.GetEntry(iE);
      
      if(Type == TypeJER)
         M2.CorrectedJetPT = M2.CorrectedJetPT * DrawGaussian(1.0, 0.05);
      if(Type == TypeJES)
         M2.CorrectedJetPT = M2.CorrectedJetPT * 1.02;

      if(M2.PassSelection() == false)
         continue;
      if(Type == TypeJetEta && abs(M2.MatchJetEta) < 0.5)
         continue;
      if(Type == TypeQuarkGluon && M2.Flavor != 21)
         continue;

      int iWB = (log(M2.MCWeight) - WEIGHTMIN) / (WEIGHTMAX - WEIGHTMIN) * WEIGHTBIN;
      if(iWB < 0)            iWB = 0;
      if(iWB >= WEIGHTBIN)   iWB = WEIGHTBIN;
      
      int iB = FindBin(M2.SDMassRatio);

      for(int iC = 0; iC < (int)Cuts.size(); iC++)
      {
         if(InBox(M2, Cuts[iC]) == false)
            continue;

         if(DRCut(M2, M2DRCut) == true)
         {
            HMW[iC][iWB] = HMW[iC][iWB] + 1;
            HMInt[iC] = HMInt[iC] + M2.MCWeight;
            HM[iC][iB] = HM[iC][iB] + M2.MCWeight;
            HM2[iC][iB] = HM2[iC][iB] + M2.MCWeight * M2.MCWeight;
         }
      }
   }
   Bar2.Update(EntryCount);
   Bar2.Print();
   Bar2.PrintLine();

   for(int iC = 0; iC < (int)Cuts.size(); iC++)
   {
      for(int iB = 0; iB < BIN; iB++)
         HN[iC][iB] = HN[iC][iB] / HNInt[iC];
      for(int iB = 0; iB < BIN; iB++)
         HN2[iC][iB] = HN2[iC][iB] / HNInt[iC] / HNInt[iC];
      for(int iB = 0; iB < BIN; iB++)
         HM[iC][iB] = HM[iC][iB] / HMInt[iC];
      for(int iB = 0; iB < BIN; iB++)
         HM2[iC][iB] = HM2[iC][iB] / HMInt[iC] / HNInt[iC];
   }

   vector<TGraphAsymmErrors *> GRatio(Cuts.size());
   for(int iC = 0; iC < (int)Cuts.size(); iC++)
   {
      GRatio[iC] = new TGraphAsymmErrors;
      GRatio[iC]->SetNameTitle(Labels[iC].c_str(),
         Form("PT %.0f-%.0f, Centrality %.2f-%.2f",
            Cuts[iC].PTMin, Cuts[iC].PTMax,
            Cuts[iC].CentralityMin, Cuts[iC].CentralityMax));
   }

   vector<vector<pair<double, double>>> Error(Cuts.size());
   for(int iC = 0; iC < (int)Cuts.size(); iC++)
   {
      PdfFile.AddTextPage(Labels[iC]);
      
      Error[iC] = QuadraticError(PdfFile, HN[iC], HM[iC], HN2[iC], HM2[iC], FunctionType);

      TranscribeQuadratic(Error[iC], GRatio[iC]);

      AddPlot(PdfFile, HN[iC], HM[iC], HN2[iC], HM2[iC], GRatio[iC]);

      TH1D HistNW("HistNW", "Nominal weight distribution;log(W);Count", WEIGHTBIN, WEIGHTMIN, WEIGHTMAX);
      HistNW.SetStats(0);
      for(int i = 1; i <= WEIGHTBIN; i++)
         HistNW.SetBinContent(i, HNW[iC][i-1]);
      PdfFile.AddPlot(HistNW, "", true);

      TH1D HistMW("HistMW", "Nominal weight distribution;log(W);Count", WEIGHTBIN, WEIGHTMIN, WEIGHTMAX);
      HistMW.SetStats(0);
      for(int i = 1; i <= WEIGHTBIN; i++)
         HistMW.SetBinContent(i, HMW[iC][i-1]);
      PdfFile.AddPlot(HistMW, "", true);
   }

   for(int iC = 0; iC < (int)Cuts.size(); iC++)
      GRatio[iC]->Write();

   OutputFile.Close();

   F2.Close();
   F1.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double GetBinCenter(int B)
{
   return 0.0 + (0.4 - 0.0) / BIN * (B + 0.5);
}

double GetSysBinCenter(int B)
{
   return 0.0 + (0.4 - 0.0) / SYSBIN * (B + 0.5);
}

int FindBin(double X)
{
   return (int)((X - 0.0) / (0.4 - 0.0) * BIN);
}

void TranscribeQuadratic(vector<pair<double, double>> V, TGraphAsymmErrors *G)
{
   if(G == NULL)
      return;

   for(int i = 0; i < SYSBIN; i++)
   {
      double X = GetSysBinCenter(i);
      int Bin = i;

      double Mean = (V[Bin].first + V[Bin].second) / 2;

      G->SetPoint(i, X, Mean);
      G->SetPointError(i, 0, 0, (Mean - V[Bin].first) * 0.5, (V[Bin].second - Mean) * 0.5);
   }
}

vector<pair<double, double>> QuadraticError(PdfFileHelper &PdfFile,
   vector<double> HN, vector<double> HM, vector<double> HN2, vector<double> HM2, int FunctionType)
{
   vector<double> D, DE;
   for(int i = 0; i < (int)HN.size(); i++)
   {
      // Ratio
      if(HN[i] > 0 && HM[i] > 0)
         D.push_back(log(HN[i]) - log(HM[i]));
      else
         D.push_back(0);
      
      if(HN[i] > 0 && HM[i] > 0)
         DE.push_back(sqrt(HN2[i] / HN[i] / HN[i] + HM2[i] / HM[i] / HM[i]));
      else
         DE.push_back(20);

      // Linear
      // D.push_back(N[i] - M[i]);
      // DE.push_back(sqrt(N2[i] + M2[i]));
   }

   for(int i = 0; i < (int)HN.size(); i++)
   {
      if(fabs(D[i]) > log(3))
      {
         D[i] = 0;
         DE[i] = 20;
      }
   }

   TH1D H("H", "", BIN, 0.0, 0.4);
   H.SetStats(0);

   for(int i = 0; i < (int)HN.size(); i++)
   {
      H.SetBinContent(i + 1, D[i]);
      H.SetBinError(i + 1, DE[i]);
   }

   PdfFile.AddPlot(H);

   string FunctionString = "pol2";
   if(FunctionType == TypeLinear)
      FunctionString = "pol1";
   if(FunctionType == TypeQuadratic)
      FunctionString = "pol2";
   if(FunctionType == TypeExponential)
      FunctionString = "[0]+[1]*exp(-[2]*x)";

   int ParameterCount = 3;
   if(FunctionType == TypeLinear)        ParameterCount = 2;
   if(FunctionType == TypeQuadratic)     ParameterCount = 3;
   if(FunctionType == TypeExponential)   ParameterCount = 3;

   TF1 Function("Function", FunctionString.c_str(), 0.0, 0.4);

   if(FunctionType == TypeExponential)
   {
      Function.SetParameter(0, H.GetBinContent(H.FindBin(0.20)));
      Function.SetParameter(1, 10);
      Function.SetParameter(2, 80);
   }

   TFitResultPtr FitResult = H.Fit(&Function, "S");
   TMatrixDSym Matrix = FitResult->GetCovarianceMatrix();

   H.GetFunction("Function")->SetBit(TF1::kNotDraw);

   // cout << "Covariance matrix: " << endl;
   // for(int i = 0; i < 3; i++)
   // {
   //    for(int j = 0; j < 3; j++)
   //       cout << Matrix[i][j] << " ";
   //    cout << endl;
   // }
   // cout << endl;

   double L[3][3] = {{0}};   // Cholesky decomposition:  find L such that L x L^T = M, where L is lower triangle

   if(ParameterCount >= 1)
      L[0][0] = sqrt(Matrix[0][0]);
   if(ParameterCount >= 2)
   {
      L[1][0] = Matrix[1][0] / L[0][0];
      L[1][1] = sqrt(Matrix[1][1] - L[1][0] * L[1][0]);
   }
   if(ParameterCount >= 3)
   {
      L[2][0] = Matrix[2][0] / L[0][0];
      L[2][1] = (Matrix[2][1] - L[2][0] * L[1][0]) / L[1][1];
      L[2][2] = sqrt(Matrix[2][2] - L[2][0] * L[2][0] - L[2][1] * L[2][1]);
   }

   // double LLT[3][3] = {{0}};   // Sanity check

   // for(int i = 0; i < 3; i++)
   //    for(int j = 0; j < 3; j++)
   //       LLT[i][j] = L[i][0] * L[j][0] + L[i][1] * L[j][1] + L[i][2] * L[j][2];
   
   // cout << "L: " << endl;
   // for(int i = 0; i < 3; i++)
   // {
   //    for(int j = 0; j < 3; j++)
   //       cout << L[i][j] << " ";
   //    cout << endl;
   // }
   // cout << endl;

   // cout << "L x LT: " << endl;
   // for(int i = 0; i < 3; i++)
   // {
   //    for(int j = 0; j < 3; j++)
   //       cout << LLT[i][j] << " ";
   //    cout << endl;
   // }
   // cout << endl;

   double Mean[3] = {0};
   if(ParameterCount >= 1)   Mean[0] = Function.GetParameter(0);
   if(ParameterCount >= 2)   Mean[1] = Function.GetParameter(1);
   if(ParameterCount >= 3)   Mean[2] = Function.GetParameter(2);

   vector<vector<double>> BinResults(160);
   TH2D HSpread("HSpread", ";Mass / PT;log(Ratio)", SYSBIN, 0.0, 0.4, 500, -1, 1);
   HSpread.SetStats(0);

   int Trials = 10000;
   for(int i = 0; i < Trials; i++)
   {
      double X[3] = {DrawGaussian(0, 1), DrawGaussian(0, 1), DrawGaussian(0, 1)};

      if(ParameterCount == 1)   X[2] = 0, X[1] = 0;
      if(ParameterCount == 2)   X[2] = 0;

      double Y[3] = {0};

      Y[0] = L[0][0] * X[0] + L[0][1] * X[1] + L[0][2] * X[2] + Mean[0];
      Y[1] = L[1][0] * X[0] + L[1][1] * X[1] + L[1][2] * X[2] + Mean[1];
      Y[2] = L[2][0] * X[0] + L[2][1] * X[1] + L[2][2] * X[2] + Mean[2];

      for(int iS = 0; iS < SYSBIN; iS++)
      {
         double x = GetSysBinCenter(iS);

         double v;
         if(FunctionType == TypeQuadratic)
            v = Y[0] + Y[1] * x + Y[2] * x * x;
         if(FunctionType == TypeLinear)
            v = Y[0] + Y[1] * x;
         if(FunctionType == TypeExponential)
            v = Y[0] + Y[1] * exp(-Y[2] * x);

         BinResults[iS].push_back(fabs(v));

         HSpread.Fill(x, v);
      }
   }

   TCanvas C;

   HSpread.Draw("colz");
   H.Draw("same");

   PdfFile.AddCanvas(C);

   vector<pair<double, double>> Result(160);

   for(int iS = 0; iS < SYSBIN; iS++)
   {
      sort(BinResults[iS].begin(), BinResults[iS].end());

      double P = 0.68;
      int Size = BinResults[iS].size();

      // int Min = (0.5 - P / 2) * Size;
      // int Max = (0.5 + P / 2) * Size;

      // Result[iS] = pair<double, double>(BinResults[iS][Min], BinResults[iS][Max]);

      int Location = Size * P;
      Result[iS] = pair<double, double>(-BinResults[iS][Location], BinResults[iS][Location]);
   }

   return Result;
}

void AddPlot(PdfFileHelper &PdfFile, vector<double> N, vector<double> M, vector<double> N2, vector<double> M2, TGraphAsymmErrors *G)
{
   TH1D HN("HN", "", BIN, 0.0, 0.4);
   TH1D HM("HM", "", BIN, 0.0, 0.4);
   TH1D HD("HD", "", BIN, 0.0, 0.4);

   for(int i = 0; i < BIN && i < (int)N.size() && i < (int)M.size(); i++)
   {
      HN.SetBinContent(i + 1, N[i]);
      HM.SetBinContent(i + 1, M[i]);
      HN.SetBinError(i + 1, sqrt(N2[i]));
      HM.SetBinError(i + 1, sqrt(M2[i]));
      if(N[i] > 0 && M[i] > 0)
      {
         HD.SetBinContent(i + 1, log(N[i]) - log(M[i]));
         HD.SetBinError(i + 1, sqrt(N2[i] / N[i] / N[i] + M2[i] / M[i] / M[i]));
      }
   }

   HN.SetStats(0);

   HN.SetLineColor(kBlue);
   HM.SetLineColor(kRed);
   HN.SetMarkerColor(kBlue);
   HM.SetMarkerColor(kRed);

   G->SetMarkerStyle(0);

   TCanvas C;

   HN.Draw("hist error");
   HM.Draw("hist error same");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetFillStyle(0);
   Legend.SetTextSize(0.035);
   Legend.SetTextFont(42);
   Legend.AddEntry(&HN, "Original", "l");
   Legend.AddEntry(&HM, "Modified", "l");
   Legend.Draw();

   PdfFile.AddCanvas(C);

   TGraph GLine;
   GLine.SetPoint(0, 0, 0);
   GLine.SetPoint(1, 10000, 0);

   HD.SetStats(0);
   HD.Draw();
   GLine.Draw("l");

   PdfFile.AddCanvas(C);

   TH2D HWorld("HWorld", ";SD Mass / Jet PT;log(Ratio)", 100, 0, 0.4, 100, -0.5, 0.5);
   HWorld.SetStats(0);

   HWorld.Draw();
   G->Draw("");
   HD.Draw("same");

   PdfFile.AddCanvas(C);
}

bool InBox(StraightTreeMessenger &M, Box &B)
{
   if(M.CorrectedJetPT > B.PTMin && M.CorrectedJetPT <= B.PTMax
      && M.Centrality > B.CentralityMin && M.Centrality <= B.CentralityMax)
      return true;
   return false;
}

bool DRCut(StraightTreeMessenger &M, double Cut)
{
   if(M.SDRecoDR <= Cut)
      return false;
   return true;
}



