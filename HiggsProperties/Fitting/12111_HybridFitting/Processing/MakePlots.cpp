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

#include "PlotHelper2.h"
#include "Code/DrawRandom.h"

#define PI 3.14159265358979323846264338327950288479716939937510

struct FitResult;
int main();
vector<FitResult> ReadFile(string FileName);
void FillGraph(TGraph &Xi1, TGraph &Xi2, TGraph &Xi3, TGraph &Xi4,
   TGraph &A3sRAs, TGraph &A3sIAs, TGraph &A2sRAs, TGraph &A2sIAs,
   double x, double AsA, vector<FitResult> Result);
void OutputGraph(PsFileHelper &PsFile, TGraph &Xi1, TGraph &Xi2, TGraph &Xi3, TGraph &Xi4,
   int LineChoice, bool PIRange, string XAxis);

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
   vector<FitResult> B = ReadFile("OutputFile_B.root");

   vector<FitResult> Xi1N1 = ReadFile("OutputFile_Xi1N1.root");
   vector<FitResult> Xi1N2 = ReadFile("OutputFile_Xi1N2.root");
   vector<FitResult> Xi1N3 = ReadFile("OutputFile_Xi1N3.root");
   vector<FitResult> Xi1N4 = ReadFile("OutputFile_Xi1N4.root");
   vector<FitResult> Xi1P1 = ReadFile("OutputFile_Xi1P1.root");
   vector<FitResult> Xi1P2 = ReadFile("OutputFile_Xi1P2.root");
   vector<FitResult> Xi1P3 = ReadFile("OutputFile_Xi1P3.root");
   vector<FitResult> Xi1P4 = ReadFile("OutputFile_Xi1P4.root");
   vector<FitResult> Xi1P5 = ReadFile("OutputFile_Xi1P5.root");
   
   vector<FitResult> Xi2N1 = ReadFile("OutputFile_Xi2N1.root");
   vector<FitResult> Xi2N2 = ReadFile("OutputFile_Xi2N2.root");
   vector<FitResult> Xi2N3 = ReadFile("OutputFile_Xi2N3.root");
   vector<FitResult> Xi2N4 = ReadFile("OutputFile_Xi2N4.root");
   vector<FitResult> Xi2P1 = ReadFile("OutputFile_Xi2P1.root");
   vector<FitResult> Xi2P2 = ReadFile("OutputFile_Xi2P2.root");
   vector<FitResult> Xi2P3 = ReadFile("OutputFile_Xi2P3.root");
   vector<FitResult> Xi2P4 = ReadFile("OutputFile_Xi2P4.root");
   vector<FitResult> Xi2P5 = ReadFile("OutputFile_Xi2P5.root");

   vector<FitResult> Xi3N1 = ReadFile("OutputFile_Xi3N1.root");
   vector<FitResult> Xi3N2 = ReadFile("OutputFile_Xi3N2.root");
   vector<FitResult> Xi3N3 = ReadFile("OutputFile_Xi3N3.root");
   vector<FitResult> Xi3N4 = ReadFile("OutputFile_Xi3N4.root");
   vector<FitResult> Xi3P1 = ReadFile("OutputFile_Xi3P1.root");
   vector<FitResult> Xi3P2 = ReadFile("OutputFile_Xi3P2.root");
   vector<FitResult> Xi3P3 = ReadFile("OutputFile_Xi3P3.root");
   vector<FitResult> Xi3P4 = ReadFile("OutputFile_Xi3P4.root");
   vector<FitResult> Xi3P5 = ReadFile("OutputFile_Xi3P5.root");

   double Xi[9] = {-0.4 * PI, -0.3 * PI, -0.2 * PI, -0.1 * PI, 0.1 * PI, 0.2 * PI, 0.3 * PI, 0.4 * PI, 0.5 * PI};
   double A2sAs[9], A3sAs[9];
   for(int i = 0; i < 9; i++)
   {
      double A1, A2, A3;

      A1 = 1;
      A2 = 0;
      A3 = tan(Xi[i]) * 5 * A1;
      if(i == 9)
         A1 = 0, A3 = 1;

      A3sAs[i] = A3 / 5 / sqrt(A3 * A3 / 25 + A2 * A2 / 3.125 / 3.125 + A1 * A1);

      A1 = 1;
      A2 = tan(Xi[i]) * 3.125 * A1;
      A3 = 0;
      if(i == 9)
         A1 = 0, A2 = 1;

      A2sAs[i] = A2 / 3.125 / sqrt(A3 * A3 / 25 + A2 * A2 / 3.125 / 3.125 + A1 * A1);
   }

   TGraph GXi1ScanXi1, GXi1ScanXi2, GXi1ScanXi3, GXi1ScanXi4;
   GXi1ScanXi1.SetMarkerStyle(7);
   GXi1ScanXi2.SetMarkerStyle(7);
   GXi1ScanXi3.SetMarkerStyle(7);
   GXi1ScanXi4.SetMarkerStyle(7);
   
   TGraph GXi1ScanA3sRAs, GXi1ScanA3sIAs, GXi1ScanA2sRAs, GXi1ScanA2sIAs;
   GXi1ScanA3sRAs.SetMarkerStyle(7);
   GXi1ScanA3sIAs.SetMarkerStyle(7);
   GXi1ScanA2sRAs.SetMarkerStyle(7);
   GXi1ScanA2sIAs.SetMarkerStyle(7);
   
   TGraph GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4;
   GXi2ScanXi1.SetMarkerStyle(7);
   GXi2ScanXi2.SetMarkerStyle(7);
   GXi2ScanXi3.SetMarkerStyle(7);
   GXi2ScanXi4.SetMarkerStyle(7);

   TGraph GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs;
   GXi2ScanA3sRAs.SetMarkerStyle(7);
   GXi2ScanA3sIAs.SetMarkerStyle(7);
   GXi2ScanA2sRAs.SetMarkerStyle(7);
   GXi2ScanA2sIAs.SetMarkerStyle(7);

   TGraph GXi3ScanXi1, GXi3ScanXi2, GXi3ScanXi3, GXi3ScanXi4;
   GXi3ScanXi1.SetMarkerStyle(7);
   GXi3ScanXi2.SetMarkerStyle(7);
   GXi3ScanXi3.SetMarkerStyle(7);
   GXi3ScanXi4.SetMarkerStyle(7);

   TGraph GXi3ScanA3sRAs, GXi3ScanA3sIAs, GXi3ScanA2sRAs, GXi3ScanA2sIAs;
   GXi3ScanA3sRAs.SetMarkerStyle(7);
   GXi3ScanA3sIAs.SetMarkerStyle(7);
   GXi3ScanA2sRAs.SetMarkerStyle(7);
   GXi3ScanA2sIAs.SetMarkerStyle(7);

   FillGraph(GXi1ScanXi1, GXi1ScanXi2, GXi1ScanXi3, GXi1ScanXi4,
      GXi1ScanA3sRAs, GXi1ScanA3sIAs, GXi1ScanA2sRAs, GXi1ScanA2sIAs, 0, 0, B);
   FillGraph(GXi1ScanXi1, GXi1ScanXi2, GXi1ScanXi3, GXi1ScanXi4,
      GXi1ScanA3sRAs, GXi1ScanA3sIAs, GXi1ScanA2sRAs, GXi1ScanA2sIAs, Xi[0], A3sAs[0], Xi1N4);
   FillGraph(GXi1ScanXi1, GXi1ScanXi2, GXi1ScanXi3, GXi1ScanXi4,
      GXi1ScanA3sRAs, GXi1ScanA3sIAs, GXi1ScanA2sRAs, GXi1ScanA2sIAs, Xi[1], A3sAs[1], Xi1N3);
   FillGraph(GXi1ScanXi1, GXi1ScanXi2, GXi1ScanXi3, GXi1ScanXi4,
      GXi1ScanA3sRAs, GXi1ScanA3sIAs, GXi1ScanA2sRAs, GXi1ScanA2sIAs, Xi[2], A3sAs[2], Xi1N2);
   FillGraph(GXi1ScanXi1, GXi1ScanXi2, GXi1ScanXi3, GXi1ScanXi4,
      GXi1ScanA3sRAs, GXi1ScanA3sIAs, GXi1ScanA2sRAs, GXi1ScanA2sIAs, Xi[3], A3sAs[3], Xi1N1);
   FillGraph(GXi1ScanXi1, GXi1ScanXi2, GXi1ScanXi3, GXi1ScanXi4,
      GXi1ScanA3sRAs, GXi1ScanA3sIAs, GXi1ScanA2sRAs, GXi1ScanA2sIAs, Xi[4], A3sAs[4], Xi1P1);
   FillGraph(GXi1ScanXi1, GXi1ScanXi2, GXi1ScanXi3, GXi1ScanXi4,
      GXi1ScanA3sRAs, GXi1ScanA3sIAs, GXi1ScanA2sRAs, GXi1ScanA2sIAs, Xi[5], A3sAs[5], Xi1P2);
   FillGraph(GXi1ScanXi1, GXi1ScanXi2, GXi1ScanXi3, GXi1ScanXi4,
      GXi1ScanA3sRAs, GXi1ScanA3sIAs, GXi1ScanA2sRAs, GXi1ScanA2sIAs, Xi[6], A3sAs[6], Xi1P3);
   FillGraph(GXi1ScanXi1, GXi1ScanXi2, GXi1ScanXi3, GXi1ScanXi4,
      GXi1ScanA3sRAs, GXi1ScanA3sIAs, GXi1ScanA2sRAs, GXi1ScanA2sIAs, Xi[7], A3sAs[7], Xi1P4);
   FillGraph(GXi1ScanXi1, GXi1ScanXi2, GXi1ScanXi3, GXi1ScanXi4,
      GXi1ScanA3sRAs, GXi1ScanA3sIAs, GXi1ScanA2sRAs, GXi1ScanA2sIAs, Xi[8], A3sAs[8], Xi1P5);
   
   FillGraph(GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4,
      GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs, 0, 0, B);
   FillGraph(GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4,
      GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs, Xi[0], A3sAs[0], Xi2N4);
   FillGraph(GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4,
      GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs, Xi[1], A3sAs[1], Xi2N3);
   FillGraph(GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4,
      GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs, Xi[2], A3sAs[2], Xi2N2);
   // FillGraph(GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4,
   //    GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs, Xi[2]+0.05, A3sAs[2]+0.05, Xi2N2M);
   FillGraph(GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4,
      GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs, Xi[3], A3sAs[3], Xi2N1);
   FillGraph(GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4,
      GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs, Xi[4], A3sAs[4], Xi2P1);
   FillGraph(GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4,
      GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs, Xi[5], A3sAs[5], Xi2P2);
   FillGraph(GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4,
      GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs, Xi[6], A3sAs[6], Xi2P3);
   FillGraph(GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4,
      GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs, Xi[7], A3sAs[7], Xi2P4);
   FillGraph(GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4,
      GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs, Xi[8], A3sAs[8], Xi2P5);

   FillGraph(GXi3ScanXi1, GXi3ScanXi2, GXi3ScanXi3, GXi3ScanXi4,
      GXi3ScanA3sRAs, GXi3ScanA3sIAs, GXi3ScanA2sRAs, GXi3ScanA2sIAs, 0, 0, B);
   FillGraph(GXi3ScanXi1, GXi3ScanXi2, GXi3ScanXi3, GXi3ScanXi4,
      GXi3ScanA3sRAs, GXi3ScanA3sIAs, GXi3ScanA2sRAs, GXi3ScanA2sIAs, Xi[0], A2sAs[0], Xi3N4);
   FillGraph(GXi3ScanXi1, GXi3ScanXi2, GXi3ScanXi3, GXi3ScanXi4,
      GXi3ScanA3sRAs, GXi3ScanA3sIAs, GXi3ScanA2sRAs, GXi3ScanA2sIAs, Xi[1], A2sAs[1], Xi3N3);
   FillGraph(GXi3ScanXi1, GXi3ScanXi2, GXi3ScanXi3, GXi3ScanXi4,
      GXi3ScanA3sRAs, GXi3ScanA3sIAs, GXi3ScanA2sRAs, GXi3ScanA2sIAs, Xi[2], A2sAs[2], Xi3N2);
   FillGraph(GXi3ScanXi1, GXi3ScanXi2, GXi3ScanXi3, GXi3ScanXi4,
      GXi3ScanA3sRAs, GXi3ScanA3sIAs, GXi3ScanA2sRAs, GXi3ScanA2sIAs, Xi[3], A2sAs[3], Xi3N1);
   FillGraph(GXi3ScanXi1, GXi3ScanXi2, GXi3ScanXi3, GXi3ScanXi4,
      GXi3ScanA3sRAs, GXi3ScanA3sIAs, GXi3ScanA2sRAs, GXi3ScanA2sIAs, Xi[4], A2sAs[4], Xi3P1);
   FillGraph(GXi3ScanXi1, GXi3ScanXi2, GXi3ScanXi3, GXi3ScanXi4,
      GXi3ScanA3sRAs, GXi3ScanA3sIAs, GXi3ScanA2sRAs, GXi3ScanA2sIAs, Xi[5], A2sAs[5], Xi3P2);
   FillGraph(GXi3ScanXi1, GXi3ScanXi2, GXi3ScanXi3, GXi3ScanXi4,
      GXi3ScanA3sRAs, GXi3ScanA3sIAs, GXi3ScanA2sRAs, GXi3ScanA2sIAs, Xi[6], A2sAs[6], Xi3P3);
   FillGraph(GXi3ScanXi1, GXi3ScanXi2, GXi3ScanXi3, GXi3ScanXi4,
      GXi3ScanA3sRAs, GXi3ScanA3sIAs, GXi3ScanA2sRAs, GXi3ScanA2sIAs, Xi[7], A2sAs[7], Xi3P4);
   FillGraph(GXi3ScanXi1, GXi3ScanXi2, GXi3ScanXi3, GXi3ScanXi4,
      GXi3ScanA3sRAs, GXi3ScanA3sIAs, GXi3ScanA2sRAs, GXi3ScanA2sIAs, Xi[8], A2sAs[8], Xi3P5);

   PsFileHelper PsFile("AllResults.ps");

   PsFile.AddTextPage("SCAN REAL A3/A1 (Xi1)");
   OutputGraph(PsFile, GXi1ScanXi1, GXi1ScanXi2, GXi1ScanXi3, GXi1ScanXi4, 1, true, "Input Xi1");
   OutputGraph(PsFile, GXi1ScanA3sRAs, GXi1ScanA3sIAs, GXi1ScanA2sRAs, GXi1ScanA2sIAs, 1, false, "Input A3sRAs");
   
   PsFile.AddTextPage("SCAN IMAG A3/A1 (Xi2)");
   OutputGraph(PsFile, GXi2ScanXi1, GXi2ScanXi2, GXi2ScanXi3, GXi2ScanXi4, 2, true, "Input Xi2");
   OutputGraph(PsFile, GXi2ScanA3sRAs, GXi2ScanA3sIAs, GXi2ScanA2sRAs, GXi2ScanA2sIAs, 2, false, "Input A3sIAs");
   
   PsFile.AddTextPage("SCAN REAL A2/A1 (Xi3)");
   OutputGraph(PsFile, GXi3ScanXi1, GXi3ScanXi2, GXi3ScanXi3, GXi3ScanXi4, 3, true, "Input Xi3");
   OutputGraph(PsFile, GXi3ScanA3sRAs, GXi3ScanA3sIAs, GXi3ScanA2sRAs, GXi3ScanA2sIAs, 3, false, "Input A2sRAs");

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

      if(Messenger.Status >= 3)
         Results.push_back(Messenger);
   }

   File.Close();

   return Results;
}

void FillGraph(TGraph &Xi1, TGraph &Xi2, TGraph &Xi3, TGraph &Xi4,
   TGraph &A3sRAs, TGraph &A3sIAs, TGraph &A2sRAs, TGraph &A2sIAs,
   double x, double AsA, vector<FitResult> Result)
{
   for(int i = 0; i < (int)Result.size(); i++)
   {
      double FitXi1 = atan(Result[i].A3A1 * cos(Result[i].A3Phase) / 5);
      double FitXi2 = atan(Result[i].A3A1 * sin(Result[i].A3Phase) / 5);
      double FitXi3 = atan(Result[i].A2A1 * cos(Result[i].A2Phase) / 3.125);
      double FitXi4 = atan(Result[i].A2A1 * sin(Result[i].A2Phase) / 3.125);
      double FitAs =
         sqrt(Result[i].A3A1 * Result[i].A3A1 / 25 + Result[i].A2A1 * Result[i].A2A1 / 3.125 / 3.125 + 1);
      double FitA3sRAs = (Result[i].A3A1 * cos(Result[i].A3Phase) / 5 / FitAs);
      double FitA3sIAs = (Result[i].A3A1 * sin(Result[i].A3Phase) / 5 / FitAs);
      double FitA2sRAs = (Result[i].A2A1 * cos(Result[i].A2Phase) / 3.125 / FitAs);
      double FitA2sIAs = (Result[i].A2A1 * sin(Result[i].A2Phase) / 3.125 / FitAs);

      double Displacement = DrawRandom(-0.015, 0.015);

      Xi1.SetPoint(Xi1.GetN(), x + Displacement, FitXi1);
      Xi2.SetPoint(Xi2.GetN(), x + Displacement, FitXi2);
      Xi3.SetPoint(Xi3.GetN(), x + Displacement, FitXi3);
      Xi4.SetPoint(Xi4.GetN(), x + Displacement, FitXi4);
      A3sRAs.SetPoint(A3sRAs.GetN(), AsA + Displacement, FitA3sRAs);
      A3sIAs.SetPoint(A3sIAs.GetN(), AsA + Displacement, FitA3sIAs);
      A2sRAs.SetPoint(A2sRAs.GetN(), AsA + Displacement, FitA2sRAs);
      A2sIAs.SetPoint(A2sIAs.GetN(), AsA + Displacement, FitA2sIAs);
   }
}

void OutputGraph(PsFileHelper &PsFile, TGraph &Xi1, TGraph &Xi2, TGraph &Xi3, TGraph &Xi4,
   int LineChoice, bool PIRange, string XAxis)
{
   double Range = 1.65;
   if(PIRange == false)
      Range = 1.1;

   TH2D HWorld1("HWorld1", Form("Real A3;%s;Output", XAxis.c_str()), 100, -Range, Range, 100, -Range, Range);   HWorld1.SetStats(0);
   TH2D HWorld2("HWorld2", Form("Imag A3;%s;Output", XAxis.c_str()), 100, -Range, Range, 100, -Range, Range);   HWorld2.SetStats(0);
   TH2D HWorld3("HWorld3", Form("Real A2;%s;Output", XAxis.c_str()), 100, -Range, Range, 100, -Range, Range);   HWorld3.SetStats(0);
   TH2D HWorld4("HWorld4", Form("Imag A2;%s;Output", XAxis.c_str()), 100, -Range, Range, 100, -Range, Range);   HWorld4.SetStats(0);

   TGraph GLine;
   GLine.SetPoint(0, -100, -100);
   GLine.SetPoint(1, 100, 100);
   
   TGraph GFlat;
   GFlat.SetPoint(0, -100, 0);
   GFlat.SetPoint(1, 100, 0);

   TCanvas C;
   C.Divide(2, 2);

   C.cd(1);
   HWorld1.Draw();
   Xi1.Draw("p");
   if(LineChoice != 1)   GFlat.Draw("l");

   C.cd(2);
   HWorld2.Draw();
   Xi2.Draw("p");
   if(LineChoice != 2)   GFlat.Draw("l");

   C.cd(3);
   HWorld3.Draw();
   Xi3.Draw("p");
   if(LineChoice != 3)   GFlat.Draw("l");

   C.cd(4);
   HWorld4.Draw();
   Xi4.Draw("p");
   if(LineChoice != 4)   GFlat.Draw("l");

   C.cd(LineChoice);
   GLine.Draw("l");
   
   PsFile.AddCanvas(C);

   static int Counter = 0;
   Counter = Counter + 1;

   C.cd(0);
 
   HWorld1.Draw();
   Xi1.Draw("p");
   if(LineChoice != 1)   GFlat.Draw("l");
   else                  GLine.Draw("l");
   C.SaveAs(Form("Plot/Plot%d-1.png", Counter));
   C.SaveAs(Form("Plot/Plot%d-1.C", Counter));
   C.SaveAs(Form("Plot/Plot%d-1.eps", Counter));
   C.SaveAs(Form("Plot/Plot%d-1.pdf", Counter));
 
   HWorld2.Draw();
   Xi2.Draw("p");
   if(LineChoice != 2)   GFlat.Draw("l");
   else                  GLine.Draw("l");
   C.SaveAs(Form("Plot/Plot%d-2.png", Counter));
   C.SaveAs(Form("Plot/Plot%d-2.C", Counter));
   C.SaveAs(Form("Plot/Plot%d-2.eps", Counter));
   C.SaveAs(Form("Plot/Plot%d-2.pdf", Counter));
 
   HWorld3.Draw();
   Xi3.Draw("p");
   if(LineChoice != 3)   GFlat.Draw("l");
   else                  GLine.Draw("l");
   C.SaveAs(Form("Plot/Plot%d-3.png", Counter));
   C.SaveAs(Form("Plot/Plot%d-3.C", Counter));
   C.SaveAs(Form("Plot/Plot%d-3.eps", Counter));
   C.SaveAs(Form("Plot/Plot%d-3.pdf", Counter));
 
   HWorld4.Draw();
   Xi4.Draw("p");
   if(LineChoice != 4)   GFlat.Draw("l");
   else                  GLine.Draw("l");
   C.SaveAs(Form("Plot/Plot%d-4.png", Counter));
   C.SaveAs(Form("Plot/Plot%d-4.C", Counter));
   C.SaveAs(Form("Plot/Plot%d-4.eps", Counter));
   C.SaveAs(Form("Plot/Plot%d-4.pdf", Counter));
}





