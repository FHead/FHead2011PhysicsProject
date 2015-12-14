#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TTree.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooKeysPdf.h"
#include "RooArgSet.h"
#include "RooPlot.h"

#include "PlotHelper2.h"
#include "Code/DrawRandom.h"

#define PI 3.14159265358979323846264338327950288479716939937510

struct FitResult;
int main();
vector<FitResult> ReadFile(string FileName);
void ProduceGraphs(PsFileHelper &PsFile, string FileNameBase);
pair<double, double> SigmaRange(double RMS, int N);

struct FitResult
{
   float A3A1, A3A1Error;
   float A3Phase, A3PhaseError;
   float A2A1, A2A1Error;
   float A2Phase, A2PhaseError;
   float Status;
};

int main()
{
   srand(time(NULL));

   PsFileHelper PsFile("AllResults.ps");
   PsFile.AddTextPage("Extrapolation to future");

   vector<string> Explanations(10);
   Explanations[0] = "Estimated width of various things as a function of dataset size.";
   Explanations[1] = "";
   Explanations[2] = "";
   Explanations[3] = "";
   PsFile.AddTextPage(Explanations);

   ProduceGraphs(PsFile, "OutputFile_B");
   // ProduceGraphs(PsFile, "OutputFile_Xi1N4");
   // ProduceGraphs(PsFile, "OutputFile_Xi1N3");
   // ProduceGraphs(PsFile, "OutputFile_Xi1N2");
   // ProduceGraphs(PsFile, "OutputFile_Xi1N1");
   // ProduceGraphs(PsFile, "OutputFile_Xi1P1");
   // ProduceGraphs(PsFile, "OutputFile_Xi1P2");
   // ProduceGraphs(PsFile, "OutputFile_Xi1P3");
   // ProduceGraphs(PsFile, "OutputFile_Xi1P4");
   // ProduceGraphs(PsFile, "OutputFile_Xi1P5");
   // ProduceGraphs(PsFile, "OutputFile_Xi2N4");
   // ProduceGraphs(PsFile, "OutputFile_Xi2N3");
   // ProduceGraphs(PsFile, "OutputFile_Xi2N2");
   // ProduceGraphs(PsFile, "OutputFile_Xi2N1");
   // ProduceGraphs(PsFile, "OutputFile_Xi2P1");
   // ProduceGraphs(PsFile, "OutputFile_Xi2P2");
   // ProduceGraphs(PsFile, "OutputFile_Xi2P3");
   // ProduceGraphs(PsFile, "OutputFile_Xi2P4");
   // ProduceGraphs(PsFile, "OutputFile_Xi2P5");
   // ProduceGraphs(PsFile, "OutputFile_Xi3N4");
   // ProduceGraphs(PsFile, "OutputFile_Xi3N3");
   // ProduceGraphs(PsFile, "OutputFile_Xi3N2");
   // ProduceGraphs(PsFile, "OutputFile_Xi3N1");
   // ProduceGraphs(PsFile, "OutputFile_Xi3P1");
   // ProduceGraphs(PsFile, "OutputFile_Xi3P2");
   // ProduceGraphs(PsFile, "OutputFile_Xi3P3");
   // ProduceGraphs(PsFile, "OutputFile_Xi3P4");
   // ProduceGraphs(PsFile, "OutputFile_Xi3P5");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

vector<FitResult> ReadFile(string FileName)
{
   vector<FitResult> Results;

   FitResult Messenger;

   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("ResultTree");

   Tree->SetBranchAddress("A3A1", &Messenger.A3A1);
   Tree->SetBranchAddress("A3A1Error", &Messenger.A3A1Error);
   Tree->SetBranchAddress("A3Phase", &Messenger.A3Phase);
   Tree->SetBranchAddress("A3PhaseError", &Messenger.A3PhaseError);
   Tree->SetBranchAddress("A2A1", &Messenger.A2A1);
   Tree->SetBranchAddress("A2A1Error", &Messenger.A2A1Error);
   Tree->SetBranchAddress("A2Phase", &Messenger.A2Phase);
   Tree->SetBranchAddress("A2PhaseError", &Messenger.A2PhaseError);
   Tree->SetBranchAddress("Status", &Messenger.Status);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree->GetEntry(iEntry);

      if(Messenger.A3A1 < 0)
      {
         Messenger.A3A1 = -Messenger.A3A1;
         Messenger.A3Phase = Messenger.A3Phase + PI;
      }
      if(Messenger.A2A1 < 0)
      {
         Messenger.A2A1 = -Messenger.A2A1;
         Messenger.A2Phase = Messenger.A2Phase + PI;
      }

      while(Messenger.A3Phase > PI)    Messenger.A3Phase = Messenger.A3Phase - 2 * PI;
      while(Messenger.A3Phase < -PI)   Messenger.A3Phase = Messenger.A3Phase + 2 * PI;
      while(Messenger.A2Phase > PI)    Messenger.A2Phase = Messenger.A2Phase - 2 * PI;
      while(Messenger.A2Phase < -PI)   Messenger.A2Phase = Messenger.A2Phase + 2 * PI;

      if(Messenger.Status > 2.5 && fabs(Messenger.A3A1) < 250 && fabs(Messenger.A2A1) < 250)
         Results.push_back(Messenger);
   }

   File.Close();

   return Results;
}

void ProduceGraphs(PsFileHelper &PsFile, string FileNameBase)
{
   int NumberOfPoints = 19;
   int CountsInt[] = {20, 30, 40, 50, 60, 70, 80, 90, 100, 150, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
   string CountsString[] = {"20", "30", "40", "50", "60", "70", "80", "90", "100", "150", "200", "300", "400",
      "500", "600", "700", "800", "900", "1000"};

   TGraphAsymmErrors GReA3A1, GImA3A1, GReA2A1, GImA2A1;

   double CommonMin = 99999;
   double CommonMax = -99999;

   for(int i = 0; i < NumberOfPoints; i++)
   {
      vector<FitResult> Results = ReadFile(FileNameBase + "_" + CountsString[i] + ".root");

      int N = Results.size();
      double Sum1ReA3A1 = 0, Sum2ReA3A1 = 0;
      double Sum1ImA3A1 = 0, Sum2ImA3A1 = 0;
      double Sum1ReA2A1 = 0, Sum2ReA2A1 = 0;
      double Sum1ImA2A1 = 0, Sum2ImA2A1 = 0;

      double ExtremeReA3A1 = 0;
      double ExtremeImA3A1 = 0;
      double ExtremeReA2A1 = 0;
      double ExtremeImA2A1 = 0;

      for(int j = 0; j < (int)Results.size(); j++)
      {
         double ReA3A1 = (Results[j].A3A1 * cos(Results[j].A3Phase) / 5);
         double ImA3A1 = (Results[j].A3A1 * sin(Results[j].A3Phase) / 5);
         double ReA2A1 = (Results[j].A2A1 * cos(Results[j].A2Phase) / 5);
         double ImA2A1 = (Results[j].A2A1 * sin(Results[j].A2Phase) / 5);

         Sum1ReA3A1 = Sum1ReA3A1 + ReA3A1;   Sum2ReA3A1 = Sum2ReA3A1 + ReA3A1 * ReA3A1;
         Sum1ImA3A1 = Sum1ImA3A1 + ImA3A1;   Sum2ImA3A1 = Sum2ImA3A1 + ImA3A1 * ImA3A1;
         Sum1ReA2A1 = Sum1ReA2A1 + ReA2A1;   Sum2ReA2A1 = Sum2ReA2A1 + ReA2A1 * ReA2A1;
         Sum1ImA2A1 = Sum1ImA2A1 + ImA2A1;   Sum2ImA2A1 = Sum2ImA2A1 + ImA2A1 * ImA2A1;

         if(fabs(ReA3A1) > fabs(ExtremeReA3A1))   ExtremeReA3A1 = ReA3A1;
         if(fabs(ImA3A1) > fabs(ExtremeImA3A1))   ExtremeImA3A1 = ImA3A1;
         if(fabs(ReA2A1) > fabs(ExtremeReA2A1))   ExtremeReA2A1 = ReA2A1;
         if(fabs(ImA2A1) > fabs(ExtremeImA2A1))   ExtremeImA2A1 = ImA2A1;
      }

      /*
      Sum1ReA3A1 = Sum1ReA3A1 - ExtremeReA3A1;
      Sum2ReA3A1 = Sum2ReA3A1 - ExtremeReA3A1 * ExtremeReA3A1;
      Sum1ImA3A1 = Sum1ImA3A1 - ExtremeImA3A1;
      Sum2ImA3A1 = Sum2ImA3A1 - ExtremeImA3A1 * ExtremeImA3A1;
      Sum1ReA2A1 = Sum1ReA2A1 - ExtremeReA2A1;
      Sum2ReA2A1 = Sum2ReA2A1 - ExtremeReA2A1 * ExtremeReA2A1;
      Sum1ImA2A1 = Sum1ImA2A1 - ExtremeImA2A1;
      Sum2ImA2A1 = Sum2ImA2A1 - ExtremeImA2A1 * ExtremeImA2A1;
      N = N - 1;
      */

      double RMSReA3A1 = sqrt((Sum2ReA3A1 - Sum1ReA3A1 * Sum1ReA3A1 / N) / (N - 1));
      double RMSImA3A1 = sqrt((Sum2ImA3A1 - Sum1ImA3A1 * Sum1ImA3A1 / N) / (N - 1));
      double RMSReA2A1 = sqrt((Sum2ReA2A1 - Sum1ReA2A1 * Sum1ReA2A1 / N) / (N - 1));
      double RMSImA2A1 = sqrt((Sum2ImA2A1 - Sum1ImA2A1 * Sum1ImA2A1 / N) / (N - 1));

      cout << RMSReA3A1 << " " << RMSImA3A1 << " " << RMSReA2A1 << " " << RMSImA2A1 << endl;

      pair<double, double> Range = SigmaRange(1, N);

      GReA3A1.SetPoint(i, CountsInt[i] * 1.2, (RMSReA3A1) * 5);
      GImA3A1.SetPoint(i, CountsInt[i] * 1.2, (RMSImA3A1) * 5);
      GReA2A1.SetPoint(i, CountsInt[i] * 1.2, (RMSReA2A1) * 5);
      GImA2A1.SetPoint(i, CountsInt[i] * 1.2, (RMSImA2A1) * 5);

      GReA3A1.SetPointError(i, 0, 0, (RMSReA3A1) * 5 - (RMSReA3A1 * Range.first) * 5, -(RMSReA3A1) * 5 + (RMSReA3A1 * Range.second) * 5);
      GImA3A1.SetPointError(i, 0, 0, (RMSImA3A1) * 5 - (RMSImA3A1 * Range.first) * 5, -(RMSImA3A1) * 5 + (RMSImA3A1 * Range.second) * 5);
      GReA2A1.SetPointError(i, 0, 0, (RMSReA2A1) * 5 - (RMSReA2A1 * Range.first) * 5, -(RMSReA2A1) * 5 + (RMSReA2A1 * Range.second) * 5);
      GImA2A1.SetPointError(i, 0, 0, (RMSImA2A1) * 5 - (RMSImA2A1 * Range.first) * 5, -(RMSImA2A1) * 5 + (RMSImA2A1 * Range.second) * 5);

      if(RMSReA3A1 < CommonMin)   CommonMin = RMSReA3A1;
      if(RMSImA3A1 < CommonMin)   CommonMin = RMSImA3A1;
      if(RMSReA2A1 < CommonMin)   CommonMin = RMSReA2A1;
      if(RMSImA2A1 < CommonMin)   CommonMin = RMSImA2A1;

      if(RMSReA3A1 > CommonMax)   CommonMax = RMSReA3A1;
      if(RMSImA3A1 > CommonMax)   CommonMax = RMSImA3A1;
      if(RMSReA2A1 > CommonMax)   CommonMax = RMSReA2A1;
      if(RMSImA2A1 > CommonMax)   CommonMax = RMSImA2A1;
   }

   GReA3A1.SetMarkerStyle(20);
   GImA3A1.SetMarkerStyle(20);
   GReA2A1.SetMarkerStyle(20);
   GImA2A1.SetMarkerStyle(20);   // use 20 for big dot
   GReA3A1.SetLineColor(kRed);
   GImA3A1.SetLineColor(kBlack);
   GReA2A1.SetLineColor(kGreen - 3);
   GImA2A1.SetLineColor(kYellow - 3);
   GReA3A1.SetMarkerColor(kRed);
   GImA3A1.SetMarkerColor(kBlack);
   GReA2A1.SetMarkerColor(kGreen - 3);
   GImA2A1.SetMarkerColor(kYellow - 3);

   PsFile.AddTextPage(FileNameBase);
   PsFile.AddPlot(GReA3A1, "ap", true, false, false, true);
   PsFile.AddPlot(GImA3A1, "ap", true, false, false, true);
   PsFile.AddPlot(GReA2A1, "ap", true, false, false, true);
   PsFile.AddPlot(GImA2A1, "ap", true, false, false, true);

   TCanvas C;
   C.SetLogx();
   C.SetLogy();

   GReA3A1.Draw("ap");
   GReA3A1.GetXaxis()->SetTitle("Dataset size");
   GReA3A1.GetYaxis()->SetTitle("Estimated spread for Re(A3/A1)");
   C.SaveAs("Plot/ReA3A1Spread.png");
   C.SaveAs("Plot/ReA3A1Spread.C");
   C.SaveAs("Plot/ReA3A1Spread.eps");
   C.SaveAs("Plot/ReA3A1Spread.pdf");
   PsFile.AddCanvas(C);

   GImA3A1.Draw("ap");
   GImA3A1.GetXaxis()->SetTitle("Dataset size");
   GImA3A1.GetYaxis()->SetTitle("Estimated spread for Im(A3/A1)");
   C.SaveAs("Plot/ImA3A1Spread.png");
   C.SaveAs("Plot/ImA3A1Spread.C");
   C.SaveAs("Plot/ImA3A1Spread.eps");
   C.SaveAs("Plot/ImA3A1Spread.pdf");
   PsFile.AddCanvas(C);

   GReA2A1.Draw("ap");
   GReA2A1.GetXaxis()->SetTitle("Dataset size");
   GReA2A1.GetYaxis()->SetTitle("Estimated spread for Re(A2/A1)");
   C.SaveAs("Plot/ReA2A1Spread.png");
   C.SaveAs("Plot/ReA2A1Spread.C");
   C.SaveAs("Plot/ReA2A1Spread.eps");
   C.SaveAs("Plot/ReA2A1Spread.pdf");
   PsFile.AddCanvas(C);

   GImA2A1.Draw("ap");
   GImA2A1.GetXaxis()->SetTitle("Dataset size");
   GImA2A1.GetYaxis()->SetTitle("Estimated spread for Im(A2/A1)");
   C.SaveAs("Plot/ImA2A1Spread.png");
   C.SaveAs("Plot/ImA2A1Spread.C");
   C.SaveAs("Plot/ImA2A1Spread.eps");
   C.SaveAs("Plot/ImA2A1Spread.pdf");
   PsFile.AddCanvas(C);

   TH1D HWorld("HWorld", ";Dataset size;Estimated spread", 100, 10, 2000);
   HWorld.SetStats(0);
   HWorld.SetMaximum((CommonMax) * 5 * 3);
   HWorld.SetMinimum((CommonMin) * 5 / 3);

   HWorld.Draw();
   GReA3A1.Draw("p");
   GImA3A1.Draw("p");
   GReA2A1.Draw("p");
   GImA2A1.Draw("p");

   TLegend Legend(0.15, 0.45, 0.35, 0.15);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&GReA3A1, "Re(A3/A1)", "lp");
   Legend.AddEntry(&GImA3A1, "Im(A3/A1)", "lp");
   Legend.AddEntry(&GReA2A1, "Re(A2/A1)", "lp");
   Legend.AddEntry(&GImA2A1, "Im(A2/A1)", "lp");
   Legend.Draw();

   C.SaveAs("AllSpread.png");
   C.SaveAs("AllSpread.C");
   C.SaveAs("AllSpread.eps");
   C.SaveAs("AllSpread.pdf");

   PsFile.AddCanvas(C);
}

pair<double, double> SigmaRange(double RMS, int N)
{
   pair<double, double> Result;

   vector<double> SigmaSamples;

   // First let's build the RMS PDF
   TNtuple Tree("RMSTree", "RMSTree", "RMSVariable");

   for(int iT = 0; iT < 10000; iT++)
   {
      double Sum0 = 0;
      double Sum1 = 0;
      double Sum2 = 0;

      for(int iS = 0; iS < N; iS++)
      {
         double Sample = DrawGaussian(0, 1);
         Sum0 = Sum0 + 1;
         Sum1 = Sum1 + Sample;
         Sum2 = Sum2 + Sample * Sample;
      }

      double SampleRMS = sqrt((Sum2 - Sum1 * Sum1 / Sum0) / (Sum0 - 1));

      Tree.Fill(SampleRMS);
   }

   RooRealVar RMSVariable("RMSVariable", "RMSVariable", 0, 100);
   RooDataSet RMSDataset("RMSDataset", "RMSDataset", &Tree, RooArgSet(RMSVariable));
   RooKeysPdf RMSPDF("RMSPDF", "RMSPDF", RMSVariable, RMSDataset);

   RooArgSet VariableSet(RMSVariable);

   RMSVariable = 1;
   double PMaxRMS = RMSPDF.getVal(&VariableSet) * 2;

   // Then let's have some fun with scanning through truth width
   while(SigmaSamples.size() < 100000)
   {
      double Sigma = DrawRandom(0, RMS * 10);

      RMSVariable = RMS / Sigma;
      double PRMS = RMSPDF.getVal(&VariableSet);

      if(PRMS / PMaxRMS > DrawRandom(0, 1))
         SigmaSamples.push_back(Sigma);
   }

   sort(SigmaSamples.begin(), SigmaSamples.end());

   Result.first = SigmaSamples[100000*0.1538];
   Result.second = SigmaSamples[100000*0.8462];

   cout << Result.first << " " << Result.second << endl;

   return Result;
}





