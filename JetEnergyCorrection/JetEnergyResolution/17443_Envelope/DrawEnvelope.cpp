#include <iostream>
#include <string>
using namespace std;

#include "TH1F.h"
#include "TFile.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TMatrixDSym.h"
#include "TGraphErrors.h"

#include "CommandLine.h"
#include "PlotHelper3.h"
#include "SetStyle.h"
#include "Code/DrawRandom.h"

int main(int argc, char *argv[]);
void ProcessRatio(PdfFileHelper &PdfFile, TH1F *HData, TH1F *HMC);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);
   string InputFileName = CL.Get("input", "JERs.root");
   string OutputFileName = CL.Get("output", "Envelope.pdf");

   TFile File(InputFileName.c_str());

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("JER Envelopes");

   ProcessRatio(PdfFile, (TH1F *)File.Get("data_cor_JER_classtc0"), (TH1F *)File.Get("MC_cor_JER_classic0"));
   ProcessRatio(PdfFile, (TH1F *)File.Get("data_cor_JER_classtc1"), (TH1F *)File.Get("MC_cor_JER_classic1"));
   ProcessRatio(PdfFile, (TH1F *)File.Get("data_cor_JER_classtc2"), (TH1F *)File.Get("MC_cor_JER_classic2"));
   ProcessRatio(PdfFile, (TH1F *)File.Get("data_cor_JER_classtc3"), (TH1F *)File.Get("MC_cor_JER_classic3"));
   ProcessRatio(PdfFile, (TH1F *)File.Get("data_cor_JER_classtc4"), (TH1F *)File.Get("MC_cor_JER_classic4"));
   ProcessRatio(PdfFile, (TH1F *)File.Get("data_cor_JER_classtc5"), (TH1F *)File.Get("MC_cor_JER_classic5"));
   ProcessRatio(PdfFile, (TH1F *)File.Get("data_cor_JER_classtc6"), (TH1F *)File.Get("MC_cor_JER_classic6"));
   ProcessRatio(PdfFile, (TH1F *)File.Get("data_cor_JER_classtc7"), (TH1F *)File.Get("MC_cor_JER_classic7"));
   ProcessRatio(PdfFile, (TH1F *)File.Get("data_cor_JER_classtc8"), (TH1F *)File.Get("MC_cor_JER_classic8"));
   ProcessRatio(PdfFile, (TH1F *)File.Get("data_cor_JER_classtc9"), (TH1F *)File.Get("MC_cor_JER_classic9"));

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();

   return 0;
}

void ProcessRatio(PdfFileHelper &PdfFile, TH1F *HData, TH1F *HMC)
{
   if(HData == NULL || HMC == NULL)
      return;

   vector<string> Titles;
   Titles.push_back("Ratio plots for");
   Titles.push_back(string("   Data = ") + HData->GetName());
   Titles.push_back(string("   MC = ") + HMC->GetName());
   PdfFile.AddTextPage(Titles);

   TF1 FData("FData", "sqrt([0]*[0]/x/x+[1]*[1]/x+[2]*[2])", 0, 5000);
   TF1 FMC("FMC", "sqrt([0]*[0]/x/x+[1]*[1]/x+[2]*[2])", 0, 5000);
   TF1 FRatio("FRatio", "sqrt([0]*[0]/x/x+[1]*[1]/x+[2]*[2])/sqrt([3]*[3]/x/x+[4]*[4]/x+[5]*[5])", 0, 5000);
   
   FData.SetLineWidth(1);
   FMC.SetLineWidth(1);
   FRatio.SetLineWidth(1);
   FData.SetLineStyle(kDashed);
   FMC.SetLineStyle(kDashed);
   FRatio.SetLineStyle(kDashed);

   FData.SetParameters(0.01, 0.01, 0.01);
   FMC.SetParameters(0.01, 0.01, 0.01);

   TFitResultPtr FitResultData = HData->Fit(&FData, "S");
   TFitResultPtr FitResultMC = HMC->Fit(&FMC, "S");

   HData->SetMarkerStyle(20);
   HMC->SetMarkerStyle(20);
   HData->SetMarkerColor(kMagenta);
   HMC->SetMarkerColor(kMagenta);
   
   HData->SetLineWidth(2);
   HMC->SetLineWidth(2);

   FRatio.SetParameter(0, FData.GetParameter(0));
   FRatio.SetParameter(1, FData.GetParameter(1));
   FRatio.SetParameter(2, FData.GetParameter(2));
   FRatio.SetParameter(3, FMC.GetParameter(0));
   FRatio.SetParameter(4, FMC.GetParameter(1));
   FRatio.SetParameter(5, FMC.GetParameter(2));

   int BinCount = 500;
   double Logs[10000] = {0};
   for(int i = 0; i <= BinCount; i++)
      Logs[i] = 50 * pow(2000 / 50, double(i) / BinCount);
   TH2D HDataSamples("HDataSamples", "Data JER;p_{T};#sigma_{JER} / <p_{T}>", BinCount, Logs, BinCount, 0, 0.2);
   TH2D HMCSamples("HMCSamples", "MC JER;p_{T};#sigma_{JER} / <p_{T}>", BinCount, Logs, BinCount, 0, 0.2);
   TH2D HRatioSamples("HRatioSamples", "Ratio JER;p_{T};JER SF", BinCount, Logs, BinCount, 0.5, 1.5);
   HDataSamples.SetStats(0);
   HMCSamples.SetStats(0);
   HRatioSamples.SetStats(0);

   TMatrixDSym MatrixData = FitResultData->GetCovarianceMatrix();
   TMatrixDSym MatrixMC = FitResultMC->GetCovarianceMatrix();

   double LData[3][3] = {{0}};   // Cholesky decomposition:  find L such that L x L^T = M, where L is lower triangle
   double LMC[3][3] = {{0}};

   LData[0][0] = sqrt(MatrixData[0][0]);
   LData[1][0] = MatrixData[1][0] / LData[0][0];
   LData[1][1] = sqrt(MatrixData[1][1] - LData[1][0] * LData[1][0]);
   LData[2][0] = MatrixData[2][0] / LData[0][0];
   LData[2][1] = (MatrixData[2][1] - LData[2][0] * LData[1][0]) / LData[1][1];
   LData[2][2] = sqrt(MatrixData[2][2] - LData[2][0] * LData[2][0] - LData[2][1] * LData[2][1]);
   LMC[0][0] = sqrt(MatrixMC[0][0]);
   LMC[1][0] = MatrixMC[1][0] / LMC[0][0];
   LMC[1][1] = sqrt(MatrixMC[1][1] - LMC[1][0] * LMC[1][0]);
   LMC[2][0] = MatrixMC[2][0] / LMC[0][0];
   LMC[2][1] = (MatrixMC[2][1] - LMC[2][0] * LMC[1][0]) / LMC[1][1];
   LMC[2][2] = sqrt(MatrixMC[2][2] - LMC[2][0] * LMC[2][0] - LMC[2][1] * LMC[2][1]);

   double MeanData[3] = {0}, MeanMC[3] = {0};
   MeanData[0] = FData.GetParameter(0);
   MeanData[1] = FData.GetParameter(1);
   MeanData[2] = FData.GetParameter(2);
   MeanMC[0] = FMC.GetParameter(0);
   MeanMC[1] = FMC.GetParameter(1);
   MeanMC[2] = FMC.GetParameter(2);

   int Tries = 100000;
   for(int iT = 0; iT < Tries; iT++)
   {
      double XData[3] = {DrawGaussian(0, 1), DrawGaussian(0, 1), DrawGaussian(0, 1)};
      double XMC[3] = {DrawGaussian(0, 1), DrawGaussian(0, 1), DrawGaussian(0, 1)};

      double YData[3] = {0}, YMC[3] = {0};

      YData[0] = LData[0][0] * XData[0] + LData[0][1] * XData[1] + LData[0][2] * XData[2] + MeanData[0];
      YData[1] = LData[1][0] * XData[0] + LData[1][1] * XData[1] + LData[1][2] * XData[2] + MeanData[1];
      YData[2] = LData[2][0] * XData[0] + LData[2][1] * XData[1] + LData[2][2] * XData[2] + MeanData[2];
      YMC[0] = LMC[0][0] * XMC[0] + LMC[0][1] * XMC[1] + LMC[0][2] * XMC[2] + MeanMC[0];
      YMC[1] = LMC[1][0] * XMC[0] + LMC[1][1] * XMC[1] + LMC[1][2] * XMC[2] + MeanMC[1];
      YMC[2] = LMC[2][0] * XMC[0] + LMC[2][1] * XMC[1] + LMC[2][2] * XMC[2] + MeanMC[2];

      for(int iB = 1; iB <= BinCount; iB++)
      {
         double PT = HDataSamples.GetXaxis()->GetBinCenter(iB);

         double VData = sqrt(YData[0] * YData[0] / PT / PT + YData[1] * YData[1] / PT + YData[2] * YData[2]);
         double VMC = sqrt(YMC[0] * YMC[0] / PT / PT + YMC[1] * YMC[1] / PT + YMC[2] * YMC[2]);
         double VRatio = VData / VMC;

         HDataSamples.Fill(PT, VData);
         HMCSamples.Fill(PT, VMC);
         HRatioSamples.Fill(PT, VRatio);
      }
   }

   TGraph GLow, GHigh;
   double ThresholdLow = 0.1575, ThresholdHigh = 0.8425;
   for(int iB = 1; iB <= BinCount; iB++)
   {
      double Total = 0;
      for(int iY = 0; iY <= BinCount + 1; iY++)
         Total = Total + HRatioSamples.GetBinContent(iB, iY);

      double RunningTotal = 0;
      for(int iY = 0; iY <= BinCount + 1; iY++)
      {
         if(RunningTotal < Total * ThresholdLow && RunningTotal + HRatioSamples.GetBinContent(iB, iY) >= Total * ThresholdLow)
            GLow.SetPoint(GLow.GetN(), HRatioSamples.GetXaxis()->GetBinCenter(iB), HRatioSamples.GetYaxis()->GetBinCenter(iY));
         if(RunningTotal < Total * ThresholdHigh && RunningTotal + HRatioSamples.GetBinContent(iB, iY) >= Total * ThresholdHigh)
            GHigh.SetPoint(GHigh.GetN(), HRatioSamples.GetXaxis()->GetBinCenter(iB), HRatioSamples.GetYaxis()->GetBinCenter(iY));
         RunningTotal = RunningTotal + HRatioSamples.GetBinContent(iB, iY);
      }
   }

   TGraphErrors GRatio;
   GRatio.SetMarkerStyle(20);
   GRatio.SetLineColor(kMagenta);
   GRatio.SetMarkerColor(kMagenta);
   GRatio.SetLineWidth(2);

   for(int iB = 1; iB <= HData->GetNbinsX(); iB++)
   {
      int iMC = -1;

      if(HData->GetBinContent(iB) < 1e-5)
         continue;
      for(int i = iB - 5; i <= iB + 5; i++)
      {
         if(i <= 0 || i > HData->GetNbinsX())
            continue;
         if(HMC->GetBinContent(i) < 1e-5)
            continue;
         iMC = i;
      }
      if(iMC < 0)
         continue;

      double VData = HData->GetBinContent(iB);
      double EData = HData->GetBinError(iB);
      double VMC = HMC->GetBinContent(iMC);
      double EMC = HMC->GetBinError(iMC);

      double VRatio = VData / VMC;
      double ERatio = VRatio * sqrt(EData * EData / VData / VData + EMC * EMC / VMC / VMC);

      int N = GRatio.GetN();
      GRatio.SetPoint(N, HData->GetBinCenter(iB), VRatio);
      GRatio.SetPointError(N, 0, ERatio);

      cout << N << " " << HData->GetBinCenter(iB) << " " << VRatio << " " << ERatio << endl;
   }

   TCanvas Canvas;
   Canvas.SetLogx();

   HDataSamples.Draw("colz");
   HData->Draw("same");
   PdfFile.AddCanvas(Canvas);
   
   HMCSamples.Draw("colz");
   HMC->Draw("same");
   PdfFile.AddCanvas(Canvas);

   HRatioSamples.Draw("colz");
   FRatio.Draw("same");
   GRatio.Draw("p");
   GLow.Draw("l");
   GHigh.Draw("l");
   PdfFile.AddCanvas(Canvas);

   TCanvas C;
}








