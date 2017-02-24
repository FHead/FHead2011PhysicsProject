#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TLegend.h"

#include "SetStyle.h"

#define LOWER_BOUND 25
#define UPPER_BOUND 1000

int main();
void GenerateGraphs(TGraphAsymmErrors *OG, TGraph G[4]);
void StyleGraphs(TGraph G[4], int Color1, int Color2, int Fill);
void DrawGraphs(TGraph G[4]);

int main()
{
   SetThesisStyle();

   TFile File("FigureLGraphs.root");

   TGraphAsymmErrors *OriginalG1 = (TGraphAsymmErrors *)File.Get("Both_J_SM_N");
   TGraphAsymmErrors *OriginalG2 = (TGraphAsymmErrors *)File.Get("Both_J_5plet_N");
   TGraphAsymmErrors *OriginalG3 = (TGraphAsymmErrors *)File.Get("Both_J_SM_Y");
   TGraphAsymmErrors *OriginalG4 = (TGraphAsymmErrors *)File.Get("Both_J_5plet_Y");

   TGraph G1[4], G2[4], G3[4], G4[4];

   GenerateGraphs(OriginalG1, G1);
   GenerateGraphs(OriginalG2, G2);
   GenerateGraphs(OriginalG3, G3);
   GenerateGraphs(OriginalG4, G4);

   StyleGraphs(G1, kViolet + 3, kMagenta + 2, 3618);
   StyleGraphs(G2, kGreen + 4, kGreen + 2, 3636);
   StyleGraphs(G3, kViolet - 6, kMagenta - 9, 3354);
   StyleGraphs(G4, kSpring - 6, kGreen - 9, 3345);

   TCanvas C;

   TH2D HWorld("HWorld", ";Luminosity (fb^{-1});p-value", 100, LOWER_BOUND, UPPER_BOUND,
      100, 0.001, 1);
   HWorld.SetStats(0);

   HWorld.Draw();

   DrawGraphs(G1);
   DrawGraphs(G2);
   DrawGraphs(G3);
   DrawGraphs(G4);

   C.SetLogx();
   C.SetLogy();

   C.SaveAs("Plots/FigureN.png");
   C.SaveAs("Plots/FigureN.C");
   C.SaveAs("Plots/FigureN.eps");
   C.SaveAs("Plots/FigureN.pdf");
}

void GenerateGraphs(TGraphAsymmErrors *OG, TGraph G[4])
{
   for(int i = 0; i < 4; i++)
      G[i].Set(0);

   if(OG == NULL)
      return;
   if(OG->GetN() == 0)
      return;

   vector<double> X;
   vector<double> Y;
   vector<double> YL;
   vector<double> YH;

   for(int i = 0; i < (int)OG->GetN(); i++)
   {
      double x, y, exl, exh, eyl, eyh;

      OG->GetPoint(i, x, y);
      eyl = OG->GetErrorYlow(i);
      eyh = OG->GetErrorYhigh(i);

      double yl = y - eyl;
      double yh = y + eyh;

      X.push_back(x);
      Y.push_back(y);
      YL.push_back(yl);
      YH.push_back(yh);
   }

   for(int i = 2; i < (int)X.size(); i++)
   {
      // If the first two are zero, I don't know what to do

      double x1 = log(X[i-2]);
      double x2 = log(X[i-1]);
      double x3 = log(X[i]);

      if(Y[i] < 1e-10)
      {
         double y1 = log(Y[i-2]);
         double y2 = log(Y[i-1]);

         double y = y1 + (y2 - y1) / (x2 - x1) * (x3 - x1);
         Y[i] = exp(y);
      }
      if(YL[i] < 1e-10)
      {
         double y1 = log(YL[i-2]);
         double y2 = log(YL[i-1]);

         double y = y1 + (y2 - y1) / (x2 - x1) * (x3 - x1);
         YL[i] = exp(y);
      }
      if(YH[i] < 1e-10)
      {
         double y1 = log(YH[i-2]);
         double y2 = log(YH[i-1]);

         double y = y1 + (y2 - y1) / (x2 - x1) * (x3 - x1);
         YH[i] = exp(y);
      }
   }

   int N = 100;
   for(int i = 0; i < (int)X.size() - 1; i++)
   {
      for(int j = 0; j < N; j++)
      {
         double x = exp(log(X[i]) + (log(X[i+1]) - log(X[i])) / N * j);
         double y = exp(log(Y[i]) + (log(Y[i+1]) - log(Y[i])) / N * j);
         double yl = exp(log(YL[i]) + (log(YL[i+1]) - log(YL[i])) / N * j);
         double yh = exp(log(YH[i]) + (log(YH[i+1]) - log(YH[i])) / N * j);
         
         if(x > UPPER_BOUND || x < LOWER_BOUND)
            continue;

         if(y != y)     y = 1e-10;
         if(yl != yl)   yl = 1e-10;
         if(yh != yh)   yh = 1e-10;

         if(y == y)
            G[0].SetPoint(G[0].GetN(), x, y);
         if(yl == yl)
            G[1].SetPoint(G[1].GetN(), x, yl);
         if(yh == yh)
            G[2].SetPoint(G[2].GetN(), x, yh);
      }
   }

   for(int i = 0; i < (int)G[1].GetN(); i++)
   {
      double x, y;
      G[1].GetPoint(i, x, y);
      G[3].SetPoint(G[3].GetN(), x, y + 1e-10);
   }
   for(int i = G[2].GetN() - 1; i >= 0; i--)
   {
      double x, y;
      G[2].GetPoint(i, x, y);
      G[3].SetPoint(G[3].GetN(), x, y);
   }
}

void StyleGraphs(TGraph G[4], int Color1, int Color2, int Fill)
{
   G[0].SetLineColor(Color1);
   G[0].SetLineWidth(3);
   G[1].SetLineColor(Color2);
   G[1].SetLineWidth(2);
   G[2].SetLineColor(Color2);
   G[2].SetLineWidth(2);
   G[3].SetFillColor(Color2);
   G[3].SetFillStyle(Fill);
   G[3].SetMarkerStyle(7);
   G[3].SetLineWidth(2);
   G[3].SetLineColor(kBlack);
}

void DrawGraphs(TGraph G[4])
{
   G[3].Draw("f");
   G[0].Draw("l");
   G[1].Draw("l");
   G[2].Draw("l");
}


