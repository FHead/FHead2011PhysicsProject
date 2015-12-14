#include <iostream>
#include <cmath>
using namespace std;

#include "TH2D.h"
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "PlotHelper2.h"

int main();
void ExportPlot(PsFileHelper &PsFile, TH2D &H, double TrueValue);

int main()
{
   SetStyle();

   double Bins[101] = {0};
   double BinMin = 20, BinMax = 5000;
   for(int i = 0; i < 101; i++)
      Bins[i] = BinMin * exp((double)i / 100 * (log(BinMax) - log(BinMin)));

   TFile OutputFile("CoolPlotSB_8.root", "RECREATE");

   TH2D HA1ZZ("HA1ZZ", "|R_{1}^{ZZ}|;N_{S};|R_{1}^{ZZ}|", 100, Bins, 100, 0, 1);
   TH2D HA2ZZ("HA2ZZ", "|R_{2}^{ZZ}|;N_{S};|R_{2}^{ZZ}|", 100, Bins, 100, 0, 1);
   TH2D HA3ZZ("HA3ZZ", "|R_{3}^{ZZ}|;N_{S};|R_{3}^{ZZ}|", 100, Bins, 100, 0, 1);
   TH2D HA2ZA("HA2ZA", "|R_{2}^{ZA}|;N_{S};|R_{2}^{ZA}|", 100, Bins, 100, 0, 0.16);
   TH2D HA3ZA("HA3ZA", "|R_{3}^{ZA}|;N_{S};|R_{3}^{ZA}|", 100, Bins, 100, 0, 0.16);
   TH2D HA2AA("HA2AA", "|R_{2}^{AA}|;N_{S};|R_{2}^{AA}|", 100, Bins, 100, 0, 0.16);
   TH2D HA3AA("HA3AA", "|R_{3}^{AA}|;N_{S};|R_{3}^{AA}|", 100, Bins, 100, 0, 0.16);
   TH2D HBackground("HBackground", "Background fraction;N_{S};Fraction", 100, Bins, 100, 0, 1);

   TFile File("OutputFileSB_8.root");
   TTree *Tree = (TTree *)File.Get("ResultTree");

   float ThetaZX, PhiZX, ThetaZZ, PhiZZ, ThetaZA, ThetaAA;
   float A2ZZPhase, A3ZZPhase, A2ZAPhase, A3ZAPhase, A2AAPhase, A3AAPhase;
   float Status, Sem, See, Fem;

   Tree->SetBranchAddress("ThetaZX", &ThetaZX);
   Tree->SetBranchAddress("PhiZX", &PhiZX);
   Tree->SetBranchAddress("ThetaZZ", &ThetaZZ);
   Tree->SetBranchAddress("PhiZZ", &PhiZZ);
   Tree->SetBranchAddress("ThetaZA", &ThetaZA);
   Tree->SetBranchAddress("ThetaAA", &ThetaAA);
   Tree->SetBranchAddress("A2ZZPhase", &A2ZZPhase);
   Tree->SetBranchAddress("A3ZZPhase", &A3ZZPhase);
   Tree->SetBranchAddress("A2ZAPhase", &A2ZAPhase);
   Tree->SetBranchAddress("A3ZAPhase", &A3ZAPhase);
   Tree->SetBranchAddress("A2AAPhase", &A2AAPhase);
   Tree->SetBranchAddress("A3AAPhase", &A3AAPhase);
   Tree->SetBranchAddress("Status", &Status);
   Tree->SetBranchAddress("Sem", &Sem);
   Tree->SetBranchAddress("See", &See);
   Tree->SetBranchAddress("Fem", &Fem);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(Status < 3)
         continue;

      double AZZ = cos(ThetaZX) * cos(PhiZX);
      double AZA = cos(ThetaZX) * sin(PhiZX);
      double AAA = sin(ThetaZX);

      double A1ZZ = AZZ * cos(ThetaZZ) * cos(PhiZZ);
      double A2ZZ = AZZ * cos(ThetaZZ) * sin(PhiZZ);
      double A3ZZ = AZZ * sin(ThetaZZ);
      
      double A2ZA = AZA * cos(ThetaZA);
      double A3ZA = AZA * sin(ThetaZA);
      
      double A2AA = AAA * cos(ThetaAA);
      double A3AA = AAA * sin(ThetaAA);

      HA1ZZ.Fill(Sem + See, fabs(A1ZZ));
      HA2ZZ.Fill(Sem + See, fabs(A2ZZ));
      HA3ZZ.Fill(Sem + See, fabs(A3ZZ));
      HA2ZA.Fill(Sem + See, fabs(A2ZA));
      HA3ZA.Fill(Sem + See, fabs(A3ZA));
      HA2AA.Fill(Sem + See, fabs(A2AA));
      HA3AA.Fill(Sem + See, fabs(A3AA));

      HBackground.Fill(Sem + See, Fem);
   }

   File.Close();

   PsFileHelper PsFile("CoolPlots.ps");
   PsFile.AddTextPage("Cool plots");

   ExportPlot(PsFile, HA1ZZ, 0.192);
   ExportPlot(PsFile, HA2ZZ, 0.000);
   ExportPlot(PsFile, HA3ZZ, 0.981);
   ExportPlot(PsFile, HA2ZA, 0.00912);
   ExportPlot(PsFile, HA3ZA, 0.0192);
   ExportPlot(PsFile, HA2AA, 0.0135);
   ExportPlot(PsFile, HA3AA, 0.0154);
   ExportPlot(PsFile, HBackground, 0.2);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   OutputFile.cd();

   HA1ZZ.Write();
   HA2ZZ.Write();
   HA3ZZ.Write();
   HA2ZA.Write();
   HA3ZA.Write();
   HA2AA.Write();
   HA3AA.Write();
   HBackground.Write();

   OutputFile.Close();

   return 0;
}

void ExportPlot(PsFileHelper &PsFile, TH2D &H, double TrueValue)
{
   TGraph G;
   G.SetPoint(0, 0, TrueValue);
   G.SetPoint(1, 1e10, TrueValue);
   G.SetLineWidth(2);

   TCanvas Canvas;
   
   H.SetStats(0);
   H.Draw("colz");
   G.Draw("l");
   
   Canvas.SetLogx();
   Canvas.SetLogz();
   
   PsFile.AddCanvas(Canvas);
}



