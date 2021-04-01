#include <iostream>
using namespace std;

#include "TGraph.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TF1.h"

#include "DataHelper.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void Transcribe(DataHelper &DHFile, string State, TGraph &G);
void FitLinear(TGraph &G, double &P0, double &P1);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string State = CL.Get("State");
   string OutputBase = CL.Get("OutputBase");

   double MaxX = CL.GetDouble("MaxX", 150);
   double MaxY = CL.GetDouble("MaxY", 150);

   DataHelper DHFileV7("CurvesV7.dh");
   DataHelper DHFileV8("CurvesV8.dh");
   DataHelper DHFileV9("CurvesV9.dh");

   TGraph G7, G8, G9;

   G7.SetMarkerStyle(20);
   G8.SetMarkerStyle(20);
   G9.SetMarkerStyle(20);
   G7.SetMarkerSize(1.5);
   G8.SetMarkerSize(1.5);
   G9.SetMarkerSize(1.5);
   G7.SetMarkerColor(kBlack);
   G8.SetMarkerColor(kRed);
   G9.SetMarkerColor(kGreen + 3);
   G7.SetLineWidth(2);
   G8.SetLineWidth(2);
   G9.SetLineWidth(2);
   G7.SetLineColor(kBlack);
   G8.SetLineColor(kRed);
   G9.SetLineColor(kGreen + 3);

   Transcribe(DHFileV7, State, G7);
   Transcribe(DHFileV8, State, G8);
   Transcribe(DHFileV9, State, G9);

   double P0V7, P1V7, P0V8, P1V8, P0V9, P1V9;
   FitLinear(G7, P0V7, P1V7);
   FitLinear(G8, P0V8, P1V8);
   FitLinear(G9, P0V9, P1V9);

   TGraph L7, L8, L9;
   L7.SetPoint(0, 0, P0V7);
   L7.SetPoint(1, MaxX, P0V7 + MaxX * P1V7);
   L8.SetPoint(0, 0, P0V8);
   L8.SetPoint(1, MaxX, P0V8 + MaxX * P1V8);
   L9.SetPoint(0, 0, P0V9);
   L9.SetPoint(1, MaxX, P0V9 + MaxX * P1V9);

   L7.SetLineWidth(2);
   L8.SetLineWidth(2);
   L9.SetLineWidth(2);
   L7.SetLineColor(kBlack);
   L8.SetLineColor(kRed);
   L9.SetLineColor(kGreen + 3);

   TCanvas Canvas;

   TH2D HWorld("HWorld", ";Threshold;95% Location", 100, 0, MaxX, 100, 0, MaxY);
   HWorld.SetStats(0);
   HWorld.Draw("axis");

   G7.Draw("p");
   G8.Draw("p");
   G9.Draw("p");

   L7.Draw("l");
   L8.Draw("l");
   L9.Draw("l");

   TLegend Legend(0.175, 0.625, 0.475, 0.825);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&G7, Form("V7.5.2, %.02f + %.02f x", P0V7, P1V7), "lp");
   Legend.AddEntry(&G8, Form("V8.2, %.02f + %.02f x", P0V8, P1V8), "lp");
   Legend.AddEntry(&G9, Form("V9, %.02f + %.02f x", P0V9, P1V9), "lp");
   Legend.Draw();

   Canvas.SaveAs(Form("%s.pdf", OutputBase.c_str()));

   return 0;
}

void Transcribe(DataHelper &DHFile, string State, TGraph &G)
{
   int N = DHFile[State]["N"].GetInteger();

   G.Set(0);

   for(int i = 0; i < N; i++)
   {
      double X = DHFile[State][Form("X%d",i)].GetDouble();
      double Y = DHFile[State][Form("Y%d",i)].GetDouble();

      G.SetPoint(i, X, Y);
   }
}

void FitLinear(TGraph &G, double &P0, double &P1)
{
   double MinX = -1, MaxX = -1;

   for(int i = 0; i < G.GetN(); i++)
   {
      double X, Y;
      G.GetPoint(i, X, Y);

      if(MinX < 0 || X < MinX)
         MinX = X;
      if(MaxX < 0 || X > MaxX)
         MaxX = X;
   }

   TF1 F("F", "pol1", MinX - 1, MaxX + 1);

   G.Fit(&F, "N");

   P0 = F.GetParameter(0);
   P1 = F.GetParameter(1);
}



