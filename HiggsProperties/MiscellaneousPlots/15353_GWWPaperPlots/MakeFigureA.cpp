#include <cmath>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TGraph.h"

#include "SetStyle.h"

int main(int argc, char *argv[]);
void FormatHistogram(TH2D &H);
void ExportPlot(TH2D &H, double TrueValue, string FileNameBase);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   string JobBase = "Result/JobBoth_5plet_ggPDF_J_";
   string Tag = "J_5plet";
   
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " JobBase Tag" << endl;
      cerr << "Example: " << argv[0] << " " << JobBase << " " << Tag << endl;
      return -1;
   }
   
   JobBase = argv[1];
   Tag = argv[2];

   double Bins[] = {log(25), log(50), log(100), log(200), log(400),
      log(800), log(1600), log(3200), log(6400), log(12800),
      log(25600), log(51200)};

   double A2ZZMin = -4, A2ZZMax = 4;
   double A3ZZMin = -10, A3ZZMax = 10;
   double A4ZZMin = -1, A4ZZMax = 1;
   double A2ZAMin = -0.3, A2ZAMax = 0.3;
   double A3ZAMin = -0.3, A3ZAMax = 0.3;
   double A4ZAMin = -1, A4ZAMax = 1;
   double A2AAMin = -0.1, A2AAMax = 0.1;
   double A3AAMin = -0.1, A3AAMax = 0.1;
   double FMin = -0.15, FMax = 0.15;
   
   TH2D HA2ZZ("HA2ZZ", ";Luminosity (fb^{-1});2 A_{2}^{ZZ}/A_{1}^{ZZ}",
      11, Bins, 100, A2ZZMin, A2ZZMax);
   TH2D HA3ZZ("HA3ZZ", ";Luminosity (fb^{-1});2 A_{3}^{ZZ}/A_{1}^{ZZ}",
      11, Bins, 100, A3ZZMin, A3ZZMax);
   TH2D HA4ZZ("HA4ZZ", ";Luminosity (fb^{-1});2 A_{4}^{ZZ}/A_{1}^{ZZ}",
      11, Bins, 100, A4ZZMin, A4ZZMax);
   TH2D HA2ZA("HA2ZA", ";Luminosity (fb^{-1});2 A_{2}^{Z#gamma}/A_{1}^{ZZ}",
      11, Bins, 100, A2ZAMin, A2ZAMax);
   TH2D HA3ZA("HA3ZA", ";Luminosity (fb^{-1});2 A_{3}^{Z#gamma}/A_{1}^{ZZ}",
      11, Bins, 100, A3ZAMin, A3ZAMax);
   TH2D HA4ZA("HA4ZA", ";Luminosity (fb^{-1});2 A_{4}^{Z#gamma}/A_{1}^{ZZ}",
      11, Bins, 100, A4ZAMin, A4ZAMax);
   TH2D HA2AA("HA2AA", ";Luminosity (fb^{-1});2 A_{2}^{#gamma#gamma}/A_{1}^{ZZ}",
      11, Bins, 100, A2AAMin, A2AAMax);
   TH2D HA3AA("HA3AA", ";Luminosity (fb^{-1});2 A_{3}^{#gamma#gamma}/A_{1}^{ZZ}",
      11, Bins, 100, A3AAMin, A3AAMax);
   TH2D HFEM("HFEM",
      ";Luminosity (fb^{-1});Background Fraction Residue (2e2#mu)",
      11, Bins, 100, FMin, FMax);
   TH2D HFEE("HFEE",
      ";Luminosity (fb^{-1});Background Fraction Residue (4e/4#mu)",
      11, Bins, 100, FMin, FMax);
   
   int Lumi[11] = {25, 50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};
   for(int i = 0; i < 11; i++)
   {
      TFile F(Form("%s%d.root", JobBase.c_str(), Lumi[i]));
      TTree *Tree = (TTree *)F.Get("ResultTree");
      
      if(Tree != NULL)
      {
         TH2D HA2ZZTemp("HA2ZZTemp", "", 11, Bins, 100, A2ZZMin, A2ZZMax);
         TH2D HA3ZZTemp("HA3ZZTemp", "", 11, Bins, 100, A3ZZMin, A3ZZMax);
         TH2D HA4ZZTemp("HA4ZZTemp", "", 11, Bins, 100, A4ZZMin, A4ZZMax);
         TH2D HA2ZATemp("HA2ZATemp", "", 11, Bins, 100, A2ZAMin, A2ZAMax);
         TH2D HA3ZATemp("HA3ZATemp", "", 11, Bins, 100, A3ZAMin, A3ZAMax);
         TH2D HA4ZATemp("HA4ZATemp", "", 11, Bins, 100, A4ZAMin, A4ZAMax);
         TH2D HA2AATemp("HA2AATemp", "", 11, Bins, 100, A2AAMin, A2AAMax);
         TH2D HA3AATemp("HA3AATemp", "", 11, Bins, 100, A3AAMin, A3AAMax);
         TH2D HFTemp("HFTemp", "", 11, Bins, 100, FMin, FMax);

         Tree->Draw(Form("P1:log(%d)>>HA2ZZTemp", Lumi[i]),
            "Status == 3 && Basis == 0");
         HA2ZZ.Add(&HA2ZZTemp);
         Tree->Draw(Form("P2:log(%d)>>HA3ZZTemp", Lumi[i]),
            "Status == 3 && Basis == 0");
         HA3ZZ.Add(&HA3ZZTemp);
         Tree->Draw(Form("P3:log(%d)>>HA4ZZTemp", Lumi[i]),
            "Status == 3 && Basis == 0");
         HA4ZZ.Add(&HA4ZZTemp);
         Tree->Draw(Form("P4:log(%d)>>HA2ZATemp", Lumi[i]),
            "Status == 3 && Basis == 0");
         HA2ZA.Add(&HA2ZATemp);
         Tree->Draw(Form("P5:log(%d)>>HA3ZATemp", Lumi[i]),
            "Status == 3 && Basis == 0");
         HA3ZA.Add(&HA3ZATemp);
         Tree->Draw(Form("P6:log(%d)>>HA4ZATemp", Lumi[i]),
            "Status == 3 && Basis == 0");
         HA4ZA.Add(&HA4ZATemp);
         Tree->Draw(Form("P7:log(%d)>>HA2AATemp", Lumi[i]),
            "Status == 3 && Basis == 0");
         HA2AA.Add(&HA2AATemp);
         Tree->Draw(Form("P8:log(%d)>>HA3AATemp", Lumi[i]),
            "Status == 3 && Basis == 0");
         HA3AA.Add(&HA3AATemp);
         Tree->Draw(Form("Fem-Bem/(Sem+Bem):log(%d)>>HFTemp", Lumi[i]),
            "Status == 3 && Basis == 0");
         HFEM.Add(&HFTemp);
         Tree->Draw(Form("Fee-Bee/(See+Bee):log(%d)>>HFTemp", Lumi[i]),
            "Status == 3 && Basis == 0");
         HFEE.Add(&HFTemp);
      }

      F.Close();
   }

   FormatHistogram(HA2ZZ);
   FormatHistogram(HA3ZZ);
   FormatHistogram(HA4ZZ);
   FormatHistogram(HA2ZA);
   FormatHistogram(HA3ZA);
   FormatHistogram(HA4ZA);
   FormatHistogram(HA2AA);
   FormatHistogram(HA3AA);
   FormatHistogram(HFEM);
   FormatHistogram(HFEE);

   ExportPlot(HA2ZZ, 0, "Plots/FigureA_" + Tag + "_A2ZZ");
   ExportPlot(HA3ZZ, 0, "Plots/FigureA_" + Tag + "_A3ZZ");
   ExportPlot(HA4ZZ, 0, "Plots/FigureA_" + Tag + "_A4ZZ");
   ExportPlot(HA2ZA, 0, "Plots/FigureA_" + Tag + "_A2ZA");
   ExportPlot(HA3ZA, 0, "Plots/FigureA_" + Tag + "_A3ZA");
   ExportPlot(HA4ZA, 0, "Plots/FigureA_" + Tag + "_A4ZA");
   ExportPlot(HA2AA, 0, "Plots/FigureA_" + Tag + "_A2AA");
   ExportPlot(HA3AA, 0, "Plots/FigureA_" + Tag + "_A3AA");
   ExportPlot(HFEM, 0, "Plots/FigureA_" + Tag + "_FEM");
   ExportPlot(HFEE, 0, "Plots/FigureA_" + Tag + "_FEE");

   return 0;
}

void FormatHistogram(TH2D &H)
{
   char BinLabel[11][6] = {"25", "50", "100", "200", "400", "800",
      "1600", "3200", "6400", "12800", "25600"};

   for(int i = 1; i <= 11; i++)
      H.GetXaxis()->SetBinLabel(i, BinLabel[i-1]);
   H.GetXaxis()->SetTickLength(0);

   H.SetStats(0);
}

void ExportPlot(TH2D &H, double TrueValue, string FileNameBase)
{
   TGraph G;
   G.SetPoint(0, 0, TrueValue);
   G.SetPoint(1, 100000000, TrueValue);

   TCanvas C;

   H.Draw("colz");
   G.Draw("l");
   C.SaveAs((FileNameBase + ".png").c_str());
   C.SaveAs((FileNameBase + ".C").c_str());
   C.SaveAs((FileNameBase + ".eps").c_str());
   C.SaveAs((FileNameBase + ".pdf").c_str());
}




