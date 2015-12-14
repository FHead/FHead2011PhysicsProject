#include <iostream>
#include <cmath>
using namespace std;

#include "TH2D.h"
#include "TStyle.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "DataHelper.h"

int main();
void PrepareHistogram(TH2D &H);

int main()
{
   gStyle->SetPaintTextFormat(".2g");

   SetThesisStyle();

   int Map[8][8] =
   {{ 1,  9, 10, 11, 12, 13, 14, 15},
    { 9,  2, 16, 17, 18, 19, 20, 21},
    {10, 16,  3, 22, 23, 24, 25, 26},
    {11, 17, 22,  4, 27, 28, 29, 30},
    {12, 18, 23, 27,  5, 31, 32, 33},
    {13, 19, 24, 28, 31,  6, 34, 35},
    {14, 20, 25, 29, 32, 34,  7, 36},
    {15, 21, 26, 30, 33, 35, 36,  8}};

   DataHelper DHFile("ZANormalization.dh");

   TH2D HLoose("HLoose", ";;", 8, 0, 8, 8, 0, 8);
   TH2D HTight("HTight", ";;", 8, 0, 8, 8, 0, 8);

   PrepareHistogram(HLoose);
   PrepareHistogram(HTight);

   double NLoose = DHFile["Loose"]["X01"].GetDouble();
   double NTight = DHFile["Tight"]["X01"].GetDouble();

   for(int i = 1; i <= 8; i++)
   {
      for(int j = 1; j <= 8; j++)
      {
         if(j > i)
            continue;

         if(fabs(DHFile["Loose"][Form("X%02d", Map[i-1][j-1])].GetDouble()) > 1e-10 * NLoose)
            HLoose.SetBinContent(i, j, DHFile["Loose"][Form("X%02d", Map[i-1][j-1])].GetDouble() / NLoose);
         if(fabs(DHFile["Tight"][Form("X%02d", Map[i-1][j-1])].GetDouble()) > 1e-10 * NTight)
            HTight.SetBinContent(i, j, DHFile["Tight"][Form("X%02d", Map[i-1][j-1])].GetDouble() / NTight);
      }
   }

   TCanvas C;
   C.SetLogz();

   HLoose.SetMaximum(0.01);
   HLoose.SetMinimum(0.00001);
   HLoose.Draw("text00 colz");
   C.SaveAs("LooseTable.png");
   C.SaveAs("LooseTable.C");
   C.SaveAs("LooseTable.eps");
   C.SaveAs("LooseTable.pdf");

   HTight.SetMaximum(0.01);
   HTight.SetMinimum(0.00001);
   HTight.Draw("text00 colz");
   C.SaveAs("TightTable.png");
   C.SaveAs("TightTable.C");
   C.SaveAs("TightTable.eps");
   C.SaveAs("TightTable.pdf");

   return 0;
}

void PrepareHistogram(TH2D &H)
{
   H.GetXaxis()->SetBinLabel(1, "A2ZAR");
   H.GetXaxis()->SetBinLabel(2, "A2ZAI");
   H.GetXaxis()->SetBinLabel(3, "A3ZAR");
   H.GetXaxis()->SetBinLabel(4, "A3ZAI");
   H.GetXaxis()->SetBinLabel(5, "A2AAR");
   H.GetXaxis()->SetBinLabel(6, "A2AAI");
   H.GetXaxis()->SetBinLabel(7, "A3AAR");
   H.GetXaxis()->SetBinLabel(8, "A3AAI");
   H.GetYaxis()->SetBinLabel(1, "A2ZAR");
   H.GetYaxis()->SetBinLabel(2, "A2ZAI");
   H.GetYaxis()->SetBinLabel(3, "A3ZAR");
   H.GetYaxis()->SetBinLabel(4, "A3ZAI");
   H.GetYaxis()->SetBinLabel(5, "A2AAR");
   H.GetYaxis()->SetBinLabel(6, "A2AAI");
   H.GetYaxis()->SetBinLabel(7, "A3AAR");
   H.GetYaxis()->SetBinLabel(8, "A3AAI");
   H.SetStats(0);
}








