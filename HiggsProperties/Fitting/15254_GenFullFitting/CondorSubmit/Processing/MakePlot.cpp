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

int main(int argc, char *argv[])
{
   SetThesisStyle();

   string FileName = "Result/JobBoth_5plet_ggPDF_J.root";
   if(argc > 1)
      FileName = argv[1];

   string Tag = "J_5plet";
   if(argc > 2)
      Tag = argv[2];

   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("ResultTree");

   double Bins1[] = {log(50), log(100), log(200), log(400), log(600), log(1000), log(2000), log(4000), log(7000), log(10000), log(20000)};
   double Bins2[] = {log(100), log(200), log(400), log(800), log(1200), log(2000), log(4000), log(8000), log(14000), log(20000), log(40000)};
   char BinLabel1[10][6] = {"50", "100", "200", "400", "600", "1000", "2000", "4000", "7000", "10000"};
   char BinLabel2[10][6] = {"100", "200", "400", "800", "1200", "2000", "4000", "8000", "14000", "20000"};

   TGraph G0;
   G0.SetPoint(0, 0, 0);
   G0.SetPoint(1, 1000000, 0);

   TH2D H2DEM("H2DEM", ";Signal Event (em);Background Fraction Residue", 10, Bins1, 100, -0.15, 0.15);
   TH2D H2DEE("H2DEE", ";Signal Event (ee);Background Fraction Residue", 10, Bins1, 100, -0.15, 0.15);

   for(int i = 1; i <= 10; i++)
   {
      H2DEM.GetXaxis()->SetBinLabel(i, BinLabel1[i-1]);
      H2DEE.GetXaxis()->SetBinLabel(i, BinLabel1[i-1]);

      H2DEM.GetXaxis()->SetTickLength(0);
      H2DEE.GetXaxis()->SetTickLength(0);
   }

   H2DEM.SetStats(0);
   H2DEE.SetStats(0);

   if(Tree != NULL)
   {
      Tree->Draw("Fem-Bem/(Sem+Bem):log(Sem)>>H2DEM", "Status == 3 && Basis == 0");
      Tree->Draw("Fee-Bee/(See+Bee):log(See)>>H2DEE", "Status == 3 && Basis == 0");
   }

   TCanvas C;

   H2DEM.Draw("colz");
   G0.Draw("l");
   C.SaveAs((Tag + "_2DEM.png").c_str());
   C.SaveAs((Tag + "_2DEM.C").c_str());
   C.SaveAs((Tag + "_2DEM.pdf").c_str());
   C.SaveAs((Tag + "_2DEM.eps").c_str());

   H2DEE.Draw("colz");
   G0.Draw("l");
   C.SaveAs((Tag + "_2DEE.png").c_str());
   C.SaveAs((Tag + "_2DEE.C").c_str());
   C.SaveAs((Tag + "_2DEE.pdf").c_str());
   C.SaveAs((Tag + "_2DEE.eps").c_str());

   F.Close();

   return 0;
}





