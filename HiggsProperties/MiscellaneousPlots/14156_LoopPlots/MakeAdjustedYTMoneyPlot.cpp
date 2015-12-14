#include <iostream>
#include <cmath>
using namespace std;

#include "TGraph.h"
#include "TEllipse.h"
#include "TFile.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH2D.h"

#include "SetStyle.h"

#define TYPE_TTH 0
#define TYPE_HZA 1
#define TYPE_HAA 2

int main();
void FillEllipse(int Type, double Mu, TGraph &G);

int main()
{
   // Hgg numbers will be taken from ECFA workshop
   // http://indico.cern.ch/event/252045/session/3/contribution/8/material/slides/0.pdf

   TFile File("AllGraphs.root");
   TGraph *YT_A = (TGraph *)File.Get("Loop_YT_Both_A_Count_YYYYYNNN_WithSquare_NNNNN_PointA");
   TGraph *YTA_A = (TGraph *)File.Get("Loop_YTA_Both_A_Count_YYYYYNNN_WithSquare_NNNNN_PointA");
   TGraph *YT_J = (TGraph *)File.Get("Loop_YT_Both_J_Count_YYYYYNNN_WithSquare_NNNNN_PointA");
   TGraph *YTA_J = (TGraph *)File.Get("Loop_YTA_Both_J_Count_YYYYYNNN_WithSquare_NNNNN_PointA");
   TGraph *YT_JS = (TGraph *)File.Get("Loop_YT_BothS_J_Count_YYYYYNNN_WithSquare_NNNNN_PointA");
   TGraph *YTA_JS = (TGraph *)File.Get("Loop_YTA_BothS_J_Count_YYYYYNNN_WithSquare_NNNNN_PointA");

   double EfficiencyA = 0.727693;
   double EfficiencyJ = 0.743760;

   // gROOT->Macro("SetAlias.C");

   double P1 = 0.6827;
   double R1 = sqrt(-2 * log(1 - P1));
   double P2 = 0.9528;
   double R2 = sqrt(-2 * log(1 - P2));

   // double AxisSize[] = {20, 15, 12, 10, 7, 5, 3.5, 2.5, 2, 2};
   double AxisSize[] = {22, 22, 12, 12, 3.7, 3.7, 3.7, 3.7, 3.7, 3.7};
   for(int i = 0; i < 10; i++)
   {
      double EventCount = 0;
      double MeanX = 1, MeanY = 0, SigmaX_A, SigmaY_A, SigmaX_J, SigmaY_J, SigmaX_JS, SigmaY_JS;

      YT_A->GetPoint(i, EventCount, SigmaX_A);
      YTA_A->GetPoint(i, EventCount, SigmaY_A);
      YT_J->GetPoint(i, EventCount, SigmaX_J);
      YTA_J->GetPoint(i, EventCount, SigmaY_J);
      YT_JS->GetPoint(i, EventCount, SigmaX_JS);
      YTA_JS->GetPoint(i, EventCount, SigmaY_JS);

      cout << EventCount << " " << SigmaX_A / SigmaX_J * SigmaY_A / SigmaY_J << endl;

      SigmaX_A = SigmaX_A * sqrt(EfficiencyJ / EfficiencyA);
      SigmaY_A = SigmaY_A * sqrt(EfficiencyJ / EfficiencyA);

      TCanvas C(Form("C%d", i), "C", 1024, 1024);

      TH2D HWorld(Form("HWorld%d", i), ";y_{t};#tilde{y}_{t}",
         100, -AxisSize[i], AxisSize[i] * 1.4, 100, -AxisSize[i] * 0.9, AxisSize[i] * 1.5);
      HWorld.SetStats(0);
      HWorld.Draw();

      TGraph Ellipse1, Ellipse2, Ellipse3;
      for(int j = 0; j <= 1000; j++)
      {
         double Angle = j * 2 * 3.14159265358979323846 / 1000;
         Ellipse1.SetPoint(j, MeanX + SigmaX_J * cos(Angle) * R1, MeanY + SigmaY_J * sin(Angle) * R1);
         Ellipse2.SetPoint(j, MeanX + SigmaX_A * cos(Angle) * R1, MeanY + SigmaY_A * sin(Angle) * R1);
         Ellipse3.SetPoint(j, MeanX + SigmaX_JS * cos(Angle) * R1, MeanY + SigmaY_JS * sin(Angle) * R1);
      }
      Ellipse2.SetLineColor(kRed - 2);
      Ellipse2.SetFillColor(kRed - 9);
      Ellipse2.SetLineWidth(2);
      Ellipse3.SetLineColor(kCyan + 2);
      Ellipse3.SetFillColor(kCyan - 7);
      Ellipse3.SetLineWidth(2);
      Ellipse1.SetLineColor(kYellow + 3);
      Ellipse1.SetFillColor(kYellow - 6);
      Ellipse1.SetLineWidth(2);
      Ellipse2.Draw("f");
      Ellipse1.Draw("f");
      Ellipse3.Draw("f");
      Ellipse3.Draw("l");
      Ellipse1.Draw("l");
      Ellipse2.Draw("l");

      // Current CMS ttH:
      //    http://arxiv.org/pdf/1408.1682.pdf

      TGraph GAA1, GAA2, GAA3;
      TGraph GZA1, GZA2, GZA3;
      TGraph GTT1, GTT2, GTT3;

      double TTCentral, TTError, ZACentral, ZAError, AACentral, AAError;

      if(EventCount < 300)
      {
         TTCentral = 2.80;   ZACentral = 1.00;   AACentral = 1.00;
         TTError = 1.00;     ZAError = 0.50;     AAError = 0.25;
      }
      else if(EventCount < 1000)
      {
         TTCentral = 1.00;   ZACentral = 1.00;   AACentral = 1.00;
         TTError = 0.55;     ZAError = 0.62;     AAError = 0.09;
      }
      else
      {
         TTCentral = 1.00;   ZACentral = 1.00;   AACentral = 1.00;
         TTError = 0.18;     ZAError = 0.22;     AAError = 0.06;
      }

      FillEllipse(TYPE_TTH, TTCentral + TTError, GTT1);
      FillEllipse(TYPE_TTH, TTCentral, GTT2);
      FillEllipse(TYPE_TTH, TTCentral - TTError, GTT3);
      FillEllipse(TYPE_HZA, ZACentral + ZAError, GZA1);
      FillEllipse(TYPE_HZA, ZACentral, GZA2);
      FillEllipse(TYPE_HZA, ZACentral - ZAError, GZA3);
      FillEllipse(TYPE_HAA, AACentral + AAError, GAA1);
      FillEllipse(TYPE_HAA, AACentral, GAA2);
      FillEllipse(TYPE_HAA, AACentral - AAError, GAA3);

      GAA1.SetLineStyle(kSolid);   GAA2.SetLineStyle(kDashed);   GAA3.SetLineStyle(kSolid);
      GZA1.SetLineStyle(kSolid);   GZA2.SetLineStyle(kDashed);   GZA3.SetLineStyle(kSolid);
      GTT1.SetLineStyle(kSolid);   GTT2.SetLineStyle(kDashed);   GTT3.SetLineStyle(kSolid);

      GAA1.SetLineColor(kBlue - 3);      GAA2.SetLineColor(kBlue - 3);      GAA3.SetLineColor(kBlue - 3);
      GZA1.SetLineColor(kMagenta - 3);   GZA2.SetLineColor(kMagenta - 3);   GZA3.SetLineColor(kMagenta - 3);
      GTT1.SetLineColor(kGreen + 3);     GTT2.SetLineColor(kGreen + 3);     GTT3.SetLineColor(kGreen + 3);

      GAA1.SetLineWidth(2);   GAA2.SetLineWidth(2);   GAA3.SetLineWidth(2);
      GZA1.SetLineWidth(2);   GZA2.SetLineWidth(2);   GZA3.SetLineWidth(2);
      GTT1.SetLineWidth(2);   GTT2.SetLineWidth(2);   GTT3.SetLineWidth(2);

      TGraph GSM1, GSM2, GSM3;
      GSM1.SetPoint(0, 1, 0);    GSM2.SetPoint(0, 1, 0);    GSM3.SetPoint(0, 1, 0);
      GSM1.SetMarkerStyle(30);   GSM2.SetMarkerStyle(30);   GSM3.SetMarkerStyle(30);
      GSM1.SetMarkerSize(3);     GSM2.SetMarkerSize(2);     GSM3.SetMarkerSize(4);
      GSM1.Draw("p");            GSM2.Draw("p");            GSM3.Draw("p");

      GTT1.Draw("l");   GTT2.Draw("l");   GTT3.Draw("l");
      GAA1.Draw("l");   GAA2.Draw("l");   GAA3.Draw("l");
      if(EventCount >= 300)
      {
         GZA1.Draw("l");   GZA2.Draw("l");   GZA3.Draw("l");
      }

      TGraph GBlock;
      GBlock.SetLineColor(kBlack);
      GBlock.SetFillColor(kWhite);
      GBlock.SetPoint(0, AxisSize[i] * -0.88, AxisSize[i] * 0.58);
      GBlock.SetPoint(1, AxisSize[i] * -0.88, AxisSize[i] * 1.40);
      GBlock.SetPoint(2, AxisSize[i] *  1.37, AxisSize[i] * 1.40);
      GBlock.SetPoint(3, AxisSize[i] *  1.37, AxisSize[i] * 0.58);
      GBlock.SetPoint(4, AxisSize[i] * -0.88, AxisSize[i] * 0.58);
      GBlock.Draw("f");
      // GBlock.Draw("l");

      HWorld.Draw("axis same");

      TLegend Legend(0.15, 0.85, 0.45, 0.60);
      // Legend.SetFillStyle(0);
      Legend.SetFillColor(kWhite);
      Legend.SetTextFont(42);
      Legend.SetBorderSize(0);
      Legend.SetTextSize(0.035);
      Legend.AddEntry(&Ellipse3, "Golden channel (Relaxed - #Upsilon, Signal-only)", "fl");
      Legend.AddEntry(&Ellipse1, "Golden channel (Relaxed - #Upsilon)", "fl");
      Legend.AddEntry(&Ellipse2, "Golden channel (CMS - tight)", "fl");
      Legend.AddEntry(&GAA1, "h#rightarrow#gamma#gamma direct search (#pm 1#sigma)", "l");
      if(EventCount > 300)
         Legend.AddEntry(&GZA1, "h#rightarrowZ#gamma direct search (#pm 1#sigma)", "l");
      Legend.AddEntry(&GTT1, "t#bar{t}h direct search (#pm 1#sigma)", "l");
      Legend.AddEntry(&GSM1, "Standard model", "p");
      Legend.Draw();
      
      // AddHeader("Axis range needs to be adjusted, but first we have to make sure the curves make sense.", true);
      AddHeader("This is the scaled version.", false);

      C.SaveAs(Form("YTContours/Contour_%05d.png", (int)EventCount));
      C.SaveAs(Form("YTContours/Contour_%05d.C",   (int)EventCount));
      C.SaveAs(Form("YTContours/Contour_%05d.eps", (int)EventCount));
      C.SaveAs(Form("YTContours/Contour_%05d.pdf", (int)EventCount));
   }
}

void FillEllipse(int Type, double Mu, TGraph &G)
{
   // tth: y^2 + 0.42 ya^2 = mu
   // AA: (1.28 - 0.28 y)^2 + (0.43 ya)^2 = mu
   // ZA: (1.06 - 0.06 y)^2 + (0.09 ya)^2 = mu

   double y0 = 0;
   double yr = 1;
   double yar = 1;
   
   if(Type == TYPE_TTH)
   {
      y0 = 0;
      yr = 1;
      yar = 1 / sqrt(0.42);
   }
   else if(Type == TYPE_HZA)
   {
      y0 = 1.06 / 0.06;
      yr = 1 / 0.06;
      yar = 1 / 0.09;
   }
   else if(Type == TYPE_HAA)
   {
      y0 = 1.28 / 0.28;
      yr = 1 / 0.28;
      yar = 1 / 0.43;
   }

   yr = yr / sqrt(Mu);
   yar = yar / sqrt(Mu);

   // now things are in the form (y' / yr)^2 + (ya / yar)^2 = 1
   
   for(int i = 0; i <= 1000; i++)
   {
      double Angle = i * 2 * 3.14159265358979323846 / 1000;

      double x = cos(Angle) * yr + y0;
      double y = sin(Angle) * yar;

      G.SetPoint(i, x, y);
   }
}




