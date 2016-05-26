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

   string JobBase = "Result/JobBoth_5plet_ggPDF_J_";
   if(argc > 1)
      JobBase = argv[1];

   string Tag = "J_5plet";
   if(argc > 2)
      Tag = argv[2];

   double Bins[] = {log(25), log(50), log(100), log(200), log(400), log(800), log(1600), log(3200), log(6400), log(12800), log(25600), log(51200)};
   
   TH2D H2DEM("H2DEM", ";Luminosity (fb^{-1});Background Fraction Residue", 11, Bins, 100, -0.15, 0.15);
   TH2D H2DEE("H2DEE", ";Luminosity (fb^{-1});Background Fraction Residue", 11, Bins, 100, -0.15, 0.15);
   
   int Lumi[11] = {25, 50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};
   for(int i = 0; i < 11; i++)
   {
      TFile F(Form("%s%d.root", JobBase.c_str(), Lumi[i]));
      TTree *Tree = (TTree *)F.Get("ResultTree");
      
      if(Tree != NULL)
      {
         TH2D H2DTemp("H2DTemp", ";Luminosity (fb^{-1});Background Fraction Residue", 11, Bins, 100, -0.15, 0.15);

         Tree->Draw(Form("Fem-Bem/(Sem+Bem):log(%d)>>H2DTemp", Lumi[i]), "Status == 3 && Basis == 0");
         H2DEM.Add(&H2DTemp);
         Tree->Draw(Form("Fee-Bee/(See+Bee):log(%d)>>H2DTemp", Lumi[i]), "Status == 3 && Basis == 0");
         H2DEE.Add(&H2DTemp);
      }

      F.Close();
   }

   char BinLabel[11][6] = {"25", "50", "100", "200", "400", "800", "1600", "3200", "6400", "12800", "25600"};

   TGraph G0;
   G0.SetPoint(0, 0, 0);
   G0.SetPoint(1, 1000000, 0);

   for(int i = 1; i <= 11; i++)
   {
      H2DEM.GetXaxis()->SetBinLabel(i, BinLabel[i-1]);
      H2DEE.GetXaxis()->SetBinLabel(i, BinLabel[i-1]);

      H2DEM.GetXaxis()->SetTickLength(0);
      H2DEE.GetXaxis()->SetTickLength(0);
   }

   H2DEM.SetStats(0);
   H2DEE.SetStats(0);

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

   return 0;
}





