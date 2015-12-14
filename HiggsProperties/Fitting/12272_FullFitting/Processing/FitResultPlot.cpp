#include <iostream>
#include <string>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TVirtualPad.h"

#include "PlotHelper2.h"

int main(int argc, char *argv[]);
void SingleDistributionPlot(TVirtualPad *Target, TH1D &H, TGraph &Line, double Real);
void Add2DPlot(PsFileHelper &PsFile, TH2D &H, double RealX, double RealY);

int main(int argc, char *argv[])
{
   double R2ZZReal = 0, R3ZZReal = 0;
   double R2ZAReal = 0, R3ZAReal = 0;
   double R2AAReal = 0, R3AAReal = 0;
   double FemReal = 0.20;

   string InputFileName = "OutputFile.root";

   TH1D HR2ZZ("HR2ZZ", "R_{2}^{ZZ};R_{2}^{ZZ}", 100, -5, 5);
   TH1D HR3ZZ("HR3ZZ", "R_{3}^{ZZ};R_{3}^{ZZ}", 100, -10, 10);
   TH1D HR2ZA("HR2ZA", "R_{2}^{ZA};R_{2}^{ZA}", 100, -0.2, 0.2);
   TH1D HR3ZA("HR3ZA", "R_{3}^{ZA};R_{3}^{ZA}", 100, -0.2, 0.2);
   TH1D HR2AA("HR2AA", "R_{2}^{AA};R_{2}^{AA}", 100, -0.2, 0.2);
   TH1D HR3AA("HR3AA", "R_{3}^{AA};R_{3}^{AA}", 100, -0.2, 0.2);
   TH1D HR2ZZPull("HR2ZZPull", "Pull for R_{2}^{ZZ};R_{2}^{ZZ}", 100, -5, 5);
   TH1D HR3ZZPull("HR3ZZPull", "Pull for R_{3}^{ZZ};R_{3}^{ZZ}", 100, -5, 5);
   TH1D HR2ZAPull("HR2ZAPull", "Pull for R_{2}^{ZA};R_{2}^{ZA}", 100, -5, 5);
   TH1D HR3ZAPull("HR3ZAPull", "Pull for R_{3}^{ZA};R_{3}^{ZA}", 100, -5, 5);
   TH1D HR2AAPull("HR2AAPull", "Pull for R_{2}^{AA};R_{2}^{AA}", 100, -5, 5);
   TH1D HR3AAPull("HR3AAPull", "Pull for R_{3}^{AA};R_{3}^{AA}", 100, -5, 5);
   TH1D HFem("HFem", "Background fraction", 100, 0, 1);
   TH1D HFemPull("HFemPull", "Pull for background fraction", 100, -5, 5);
   TH2D HR2ZZR3ZZ("HR2ZZR3ZZ", "R^{ZZ};R_{2}^{ZZ};R_{3}^{ZZ}", 100, -5, 5, 100, -10, 10);
   TH2D HR2ZAR3ZA("HR2ZAR3ZA", "R^{ZA};R_{2}^{ZA};R_{3}^{ZA}", 100, -0.2, 0.2, 100, -0.2, 0.2);
   TH2D HR2AAR3AA("HR2AAR3AA", "R^{AA};R_{2}^{AA};R_{3}^{AA}", 100, -0.2, 0.2, 100, -0.2, 0.2);
   TH2D HR2ZZR2ZA("HR2ZZR2ZA", "R_{2}^{ZZ} vs. R_{2}^{ZA};R_{2}^{ZZ};R_{2}^{ZA}", 100, -5, 5, 100, -0.2, 0.2);
   TH2D HR2ZZR2AA("HR2ZZR2AA", "R_{2}^{ZZ} vs. R_{2}^{AA};R_{2}^{ZZ};R_{2}^{AA}", 100, -5, 5, 100, -0.2, 0.2);
   TH2D HR2ZAR2AA("HR2ZAR2AA", "R_{2}^{ZA} vs. R_{2}^{AA};R_{2}^{ZA};R_{2}^{AA}", 100, -0.2, 0.2, 100, -0.2, 0.2);
   TH2D HR3ZZR3ZA("HR3ZZR3ZA", "R_{3}^{ZZ} vs. R_{3}^{ZA};R_{3}^{ZZ};R_{3}^{ZA}", 100, -10, 10, 100, -0.4, 0.4);
   TH2D HR3ZZR3AA("HR3ZZR3AA", "R_{3}^{ZZ} vs. R_{3}^{AA};R_{3}^{ZZ};R_{3}^{AA}", 100, -10, 10, 100, -0.2, 0.2);
   TH2D HR3ZAR3AA("HR3ZAR3AA", "R_{3}^{ZA} vs. R_{3}^{AA};R_{3}^{ZA};R_{3}^{AA}", 100, -0.4, 0.4, 100, -0.2, 0.2);

   TGraph GR2ZZ, GR3ZZ, GR2ZA, GR3ZA, GR2AA, GR3AA, GFem;

   HR2ZZ.SetStats(0), HR3ZZ.SetStats(0);
   HR2ZA.SetStats(0), HR3ZA.SetStats(0);
   HR2AA.SetStats(0), HR3AA.SetStats(0);
   HR2ZZPull.SetStats(0), HR3ZZPull.SetStats(0);
   HR2ZAPull.SetStats(0), HR3ZAPull.SetStats(0);
   HR2AAPull.SetStats(0), HR3AAPull.SetStats(0);
   HFem.SetStats(0), HFemPull.SetStats(0);
   HR2ZZR3ZZ.SetStats(0), HR2ZAR3ZA.SetStats(0), HR2AAR3AA.SetStats(0);
   HR2ZZR2ZA.SetStats(0), HR2ZZR2AA.SetStats(0), HR2ZAR2AA.SetStats(0);
   HR3ZZR3ZA.SetStats(0), HR3ZZR3AA.SetStats(0), HR3ZAR3AA.SetStats(0);

   TFile InputFile(InputFileName.c_str());

   TTree *Tree = (TTree *)InputFile.Get("ResultTree");

   float Status;
   float R2ZZ, R3ZZ, R2ZA, R3ZA, R2AA, R3AA;
   float R2ZZError, R3ZZError, R2ZAError, R3ZAError, R2AAError, R3AAError;
   float Fem, FemError;
   Tree->SetBranchAddress("Status", &Status);
   Tree->SetBranchAddress("A2ZZA1ZZ", &R2ZZ);
   Tree->SetBranchAddress("A3ZZA1ZZ", &R3ZZ);
   Tree->SetBranchAddress("A2ZAA1ZZ", &R2ZA);
   Tree->SetBranchAddress("A3ZAA1ZZ", &R3ZA);
   Tree->SetBranchAddress("A2AAA1ZZ", &R2AA);
   Tree->SetBranchAddress("A3AAA1ZZ", &R3AA);
   Tree->SetBranchAddress("A2ZZA1ZZError", &R2ZZError);
   Tree->SetBranchAddress("A3ZZA1ZZError", &R3ZZError);
   Tree->SetBranchAddress("A2ZAA1ZZError", &R2ZAError);
   Tree->SetBranchAddress("A3ZAA1ZZError", &R3ZAError);
   Tree->SetBranchAddress("A2AAA1ZZError", &R2AAError);
   Tree->SetBranchAddress("A3AAA1ZZError", &R3AAError);
   Tree->SetBranchAddress("Fem", &Fem);
   Tree->SetBranchAddress("FemError", &FemError);

   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      if(Status < 3)
         continue;

      HR2ZZ.Fill(R2ZZ);
      HR3ZZ.Fill(R3ZZ);
      HR2ZA.Fill(R2ZA);
      HR3ZA.Fill(R3ZA);
      HR2AA.Fill(R2AA);
      HR3AA.Fill(R3AA);
      HR2ZZPull.Fill((R2ZZ - R2ZZReal) / R2ZZError);
      HR3ZZPull.Fill((R3ZZ - R3ZZReal) / R3ZZError);
      HR2ZAPull.Fill((R2ZA - R2ZAReal) / R2ZAError);
      HR3ZAPull.Fill((R3ZA - R3ZAReal) / R3ZAError);
      HR2AAPull.Fill((R2AA - R2AAReal) / R2AAError);
      HR3AAPull.Fill((R3AA - R3AAReal) / R3AAError);
      HFem.Fill(Fem);
      HFemPull.Fill((Fem - FemReal) / FemError);
      HR2ZZR3ZZ.Fill(R2ZZ, R3ZZ);
      HR2ZAR3ZA.Fill(R2ZA, R3ZA);
      HR2AAR3AA.Fill(R2AA, R3AA);
      HR2ZZR2ZA.Fill(R2ZZ, R2ZA);
      HR2ZZR2AA.Fill(R2ZZ, R2AA);
      HR2ZAR2AA.Fill(R2ZA, R2AA);
      HR3ZZR3ZA.Fill(R3ZZ, R3ZA);
      HR3ZZR3AA.Fill(R3ZZ, R3AA);
      HR3ZAR3AA.Fill(R3ZA, R3AA);
   }

   InputFile.Close();

   PsFileHelper PsFile("Result.ps");
   PsFile.AddTextPage(Form("Fit result from file %s", InputFileName.c_str()));

   TCanvas C;

   SingleDistributionPlot(C.cd(1), HR2ZZ, GR2ZZ, R2ZZReal);
   PsFile.AddCanvas(C);
   SingleDistributionPlot(C.cd(1), HR3ZZ, GR3ZZ, R3ZZReal);
   PsFile.AddCanvas(C);
   SingleDistributionPlot(C.cd(1), HR2ZA, GR2ZA, R2ZAReal);
   PsFile.AddCanvas(C);
   SingleDistributionPlot(C.cd(1), HR3ZA, GR3ZA, R3ZAReal);
   PsFile.AddCanvas(C);
   SingleDistributionPlot(C.cd(1), HR2AA, GR2AA, R2AAReal);
   PsFile.AddCanvas(C);
   SingleDistributionPlot(C.cd(1), HR3AA, GR3AA, R3AAReal);
   PsFile.AddCanvas(C);

   TCanvas C6;
   C6.Divide(3, 2);
   SingleDistributionPlot(C6.cd(1), HR2ZZ, GR2ZZ, R2ZZReal);
   SingleDistributionPlot(C6.cd(4), HR3ZZ, GR3ZZ, R3ZZReal);
   SingleDistributionPlot(C6.cd(2), HR2ZA, GR2ZA, R2ZAReal);
   SingleDistributionPlot(C6.cd(5), HR3ZA, GR3ZA, R3ZAReal);
   SingleDistributionPlot(C6.cd(3), HR2AA, GR2AA, R2AAReal);
   SingleDistributionPlot(C6.cd(6), HR3AA, GR3AA, R3AAReal);
   PsFile.AddCanvas(C6);

   PsFile.AddPlot(HR2ZZPull);
   PsFile.AddPlot(HR3ZZPull);
   PsFile.AddPlot(HR2ZAPull);
   PsFile.AddPlot(HR3ZAPull);
   PsFile.AddPlot(HR2AAPull);
   PsFile.AddPlot(HR3AAPull);

   C6.cd(1);   HR2ZZPull.Draw();
   C6.cd(4);   HR3ZZPull.Draw();
   C6.cd(2);   HR2ZAPull.Draw();
   C6.cd(5);   HR3ZAPull.Draw();
   C6.cd(3);   HR2AAPull.Draw();
   C6.cd(6);   HR3AAPull.Draw();
   PsFile.AddCanvas(C6);

   TCanvas CC;
   SingleDistributionPlot(CC.cd(1), HFem, GFem, FemReal);
   PsFile.AddCanvas(CC);

   PsFile.AddPlot(HFemPull);

   Add2DPlot(PsFile, HR2ZZR3ZZ, R2ZZReal, R3ZZReal);
   Add2DPlot(PsFile, HR2ZAR3ZA, R2ZAReal, R3ZAReal);
   Add2DPlot(PsFile, HR2AAR3AA, R2AAReal, R3AAReal);
   Add2DPlot(PsFile, HR2ZZR2ZA, R2ZZReal, R2ZAReal);
   Add2DPlot(PsFile, HR2ZZR2AA, R2ZZReal, R2AAReal);
   Add2DPlot(PsFile, HR2ZAR2AA, R2ZAReal, R2AAReal);
   Add2DPlot(PsFile, HR3ZZR3ZA, R3ZZReal, R3ZAReal);
   Add2DPlot(PsFile, HR3ZZR3AA, R3ZZReal, R3AAReal);
   Add2DPlot(PsFile, HR3ZAR3AA, R3ZAReal, R3AAReal);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void SingleDistributionPlot(TVirtualPad *Target, TH1D &H, TGraph &Line, double Real)
{
   if(Target == NULL)
      return;

   Target->cd();

   Line.Set(0);
   Line.SetPoint(0, Real, 0);
   Line.SetPoint(1, Real, 100000);
   Line.SetLineWidth(2);
   Line.SetLineColor(kRed);

   H.Draw();
   Line.Draw("l");
}

void Add2DPlot(PsFileHelper &PsFile, TH2D &H, double RealX, double RealY)
{
   TCanvas C;

   H.Draw("colz");

   TGraph X, Y;
   X.SetPoint(0, RealX, -99999);
   X.SetPoint(1, RealX, +99999);
   Y.SetPoint(0, -99999, RealY);
   Y.SetPoint(1, +99999, RealY);

   X.SetLineWidth(2);
   Y.SetLineWidth(2);

   X.Draw("l");
   Y.Draw("l");

   PsFile.AddCanvas(C);
}



