#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TF2.h"
#include "TROOT.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TEllipse.h"
#include "TLegend.h"

#include "InterpretCoefficient.h"

#include "SetStyle.h"

#define PI 3.14159265358979323846264338327950288479716939937510

struct FitResult;
int main();
FitResult GetAngle(string FileName);

struct FitResult
{
   double Angle;
   double Variance1;
   double Variance2;
};

int main()
{
   SetThesisBigStyle();

   int N[10] = {50, 100, 200, 400, 600, 1000, 2000, 4000, 7000, 10000};

   InterpretationCoefficients CNonSM;
   CNonSM.mw = 79.95;
   CNonSM.mt = 173.21;
   CNonSM.yt = 1;
   CNonSM.yta = 1;
   CNonSM.gww = 2;

   double A2AA_GWW = InterpretedA2AA_W_Roberto13711(CNonSM) / CNonSM.gww;
   double A2AA_YT = InterpretedA2AA_Top_Roberto13711(CNonSM) / CNonSM.yt;
   double A3AA_YTA = InterpretedA3AA_Top_Roberto14167(CNonSM) / CNonSM.yta;
   double A2ZA_GWW = InterpretedA2ZA_W_Roberto13711(CNonSM) / CNonSM.gww;
   double A2ZA_YT = InterpretedA2ZA_Top_Roberto13711(CNonSM) / CNonSM.yt;
   double A3ZA_YTA = InterpretedA3ZA_Top_Roberto14167(CNonSM) / CNonSM.yta;

   double A2AA_SM = A2AA_GWW * 2 + A2AA_YT * 1;
   double A2ZA_SM = A2ZA_GWW * 2 + A2ZA_YT * 1;

   for(int iN = 0; iN < 10; iN++)
   {
      if(iN == 1)
         continue;

      FitResult ResultJS = GetAngle(Form("Trees/ResultBothS_PointA_J_%d.root", N[iN]));
      FitResult ResultJSB = GetAngle(Form("Trees/ResultBoth_PointA_J_%d.root", N[iN]));
      FitResult ResultASB = GetAngle(Form("Trees/ResultBoth_PointA_A_%d.root", N[iN]));

      cout << ResultJS.Angle << " " << sqrt(ResultJS.Variance1) << " " << sqrt(ResultJS.Variance2) << endl;
      cout << ResultJSB.Angle << " " << sqrt(ResultJSB.Variance1) << " " << sqrt(ResultJSB.Variance2) << endl;
      cout << ResultASB.Angle << " " << sqrt(ResultASB.Variance1) << " " << sqrt(ResultASB.Variance2) << endl;

      double XMax = 2 + sqrt(ResultASB.Variance1) * fabs(cos(ResultASB.Angle)) + sqrt(ResultASB.Variance2) * fabs(sin(ResultASB.Angle));
      double XMin = 2 - sqrt(ResultASB.Variance1) * fabs(cos(ResultASB.Angle)) - sqrt(ResultASB.Variance2) * fabs(sin(ResultASB.Angle));
      double YMax = 0 + sqrt(ResultASB.Variance1) * fabs(sin(ResultASB.Angle)) + sqrt(ResultASB.Variance2) * fabs(cos(ResultASB.Angle));
      double YMin = 0 - sqrt(ResultASB.Variance1) * fabs(sin(ResultASB.Angle)) - sqrt(ResultASB.Variance2) * fabs(cos(ResultASB.Angle));

      double DeltaX = XMax - XMin;
      double DeltaY = YMax - YMin;

      XMax = XMax + DeltaX * 0.85;   // 0.65
      XMin = XMin - DeltaX * 0.35;   // 0.15
      YMax = YMax + DeltaY * 0.65;   // 0.35
      YMin = YMin - DeltaY * 0.65;   // 0.35

      TGraph GAA1, GAA2, GAA3, GAA4, GAA5;
      TGraph GZA1, GZA2, GZA3, GZA4, GZA5;

      cout << (A2AA_SM * sqrt(1.00) - 1 * A2AA_YT) / A2AA_GWW << endl;

      for(int i = 0; i <= 1000; i++)
      {
         double Angle = i * 0.001 * 2 * PI;

         double X0, XR, YR;

         X0 = -A2AA_YT / A2AA_GWW;
         XR = 1 / A2AA_GWW * A2AA_SM;
         YR = 1 / A3AA_YTA * A2AA_SM;

         GAA1.SetPoint(i, XR / sqrt(0.91) * cos(Angle) + X0, YR / sqrt(0.91) * sin(Angle));
         GAA2.SetPoint(i, XR / sqrt(0.94) * cos(Angle) + X0, YR / sqrt(0.94) * sin(Angle));
         GAA3.SetPoint(i, XR / sqrt(1.00) * cos(Angle) + X0, YR / sqrt(1.00) * sin(Angle));
         GAA4.SetPoint(i, XR / sqrt(1.06) * cos(Angle) + X0, YR / sqrt(1.06) * sin(Angle));
         GAA5.SetPoint(i, XR / sqrt(1.09) * cos(Angle) + X0, YR / sqrt(1.09) * sin(Angle));

         X0 = -A2ZA_YT / A2ZA_GWW;
         XR = 1 / A2ZA_GWW * A2ZA_SM;
         YR = 1 / A3ZA_YTA * A2ZA_SM;

         GZA1.SetPoint(i, XR / sqrt(0.38) * cos(Angle) + X0, YR / sqrt(0.38) * sin(Angle));
         GZA2.SetPoint(i, XR / sqrt(0.78) * cos(Angle) + X0, YR / sqrt(0.78) * sin(Angle));
         GZA3.SetPoint(i, XR / sqrt(1.00) * cos(Angle) + X0, YR / sqrt(1.00) * sin(Angle));
         GZA4.SetPoint(i, XR / sqrt(1.22) * cos(Angle) + X0, YR / sqrt(1.22) * sin(Angle));
         GZA5.SetPoint(i, XR / sqrt(1.62) * cos(Angle) + X0, YR / sqrt(1.62) * sin(Angle));
      }

      GAA1.SetLineWidth(2);   GAA1.SetLineColor(kBlue);        GAA1.SetLineStyle(kDashed);
      GAA2.SetLineWidth(2);   GAA2.SetLineColor(kBlue);        GAA2.SetLineStyle(kDotted);
      GAA3.SetLineWidth(2);   GAA3.SetLineColor(kBlue);        GAA3.SetLineStyle(kSolid);
      GAA4.SetLineWidth(2);   GAA4.SetLineColor(kBlue);        GAA4.SetLineStyle(kDotted);
      GAA5.SetLineWidth(2);   GAA5.SetLineColor(kBlue);        GAA5.SetLineStyle(kDashed);
      GZA1.SetLineWidth(2);   GZA1.SetLineColor(kGreen - 3);   GZA1.SetLineStyle(kDashed);
      GZA2.SetLineWidth(2);   GZA2.SetLineColor(kGreen - 3);   GZA2.SetLineStyle(kDotted);
      GZA3.SetLineWidth(1);   GZA3.SetLineColor(kGreen - 3);   GZA3.SetLineStyle(kSolid);
      GZA4.SetLineWidth(2);   GZA4.SetLineColor(kGreen - 3);   GZA4.SetLineStyle(kDotted);
      GZA5.SetLineWidth(2);   GZA5.SetLineColor(kGreen - 3);   GZA5.SetLineStyle(kDashed);

      TCanvas C;

      TH2D HWorld("HWorld", ";g_{WW};#tilde{y}_{t}", 100, XMin, XMax, 100, YMin, YMax);
      HWorld.SetStats(0);

      TEllipse EllipseASB(2, 0, sqrt(ResultASB.Variance1), sqrt(ResultASB.Variance2), 0, 360, (ResultASB.Angle) / PI * 180);
      TEllipse EllipseJSB(2, 0, sqrt(ResultJSB.Variance1), sqrt(ResultJSB.Variance2), 0, 360, (ResultJSB.Angle) / PI * 180);
      TEllipse EllipseJS (2, 0, sqrt(ResultJS .Variance1), sqrt(ResultJS .Variance2), 0, 360, (ResultJS .Angle) / PI * 180);

      EllipseASB.SetLineWidth(2);
      EllipseJSB.SetLineWidth(2);
      EllipseJS .SetLineWidth(2);
      EllipseASB.SetLineColor(kRed - 2);
      EllipseJSB.SetLineColor(kYellow + 3);
      EllipseJS .SetLineColor(kCyan + 2);
      EllipseASB.SetFillColor(kRed - 9);
      EllipseJSB.SetFillColor(kYellow - 6);
      EllipseJS .SetFillColor(kCyan - 7);

      HWorld.Draw();

      EllipseASB.Draw("f");
      EllipseJSB.Draw("f");
      EllipseJS.Draw("f");

      GAA1.Draw("l");
      GAA2.Draw("l");
      GAA3.Draw("l");
      GAA4.Draw("l");
      GAA5.Draw("l");
      GZA1.Draw("l");
      GZA2.Draw("l");
      GZA3.Draw("l");
      GZA4.Draw("l");
      GZA5.Draw("l");

      TLegend Legend(0.58, 0.15, 0.83, 0.40);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.035);
      Legend.AddEntry(&EllipseJS, "Relaxed - #Upsilon", "fl");
      Legend.AddEntry("", "(Signal-only)", "");
      Legend.AddEntry(&EllipseJSB, "Relaxed - #Upsilon", "fl");
      Legend.AddEntry(&EllipseASB, "CMS - tight", "fl");
      Legend.Draw();

      AddHeader("", true);

      C.SaveAs(Form("FigureD_%05d.png", N[iN] * 2));
      C.SaveAs(Form("FigureD_%05d.C", N[iN] * 2));
      C.SaveAs(Form("FigureD_%05d.eps", N[iN] * 2));
      C.SaveAs(Form("FigureD_%05d.pdf", N[iN] * 2));
   }

   return 0;
}

FitResult GetAngle(string FileName)
{
   TFile File(FileName.c_str());
   TTree *ResultTree = (TTree *)File.Get("ResultTree");

   vector<double> X, Y;

   float P[8];
   float PError[8];
   float Status;
   float Basis;

   ResultTree->SetBranchAddress("P1", &P[0]);
   ResultTree->SetBranchAddress("P2", &P[1]);
   ResultTree->SetBranchAddress("P3", &P[2]);
   ResultTree->SetBranchAddress("P4", &P[3]);
   ResultTree->SetBranchAddress("P5", &P[4]);
   ResultTree->SetBranchAddress("P6", &P[5]);
   ResultTree->SetBranchAddress("P7", &P[6]);
   ResultTree->SetBranchAddress("P8", &P[7]);
   ResultTree->SetBranchAddress("P1Error", &PError[0]);
   ResultTree->SetBranchAddress("P2Error", &PError[1]);
   ResultTree->SetBranchAddress("P3Error", &PError[2]);
   ResultTree->SetBranchAddress("P4Error", &PError[3]);
   ResultTree->SetBranchAddress("P5Error", &PError[4]);
   ResultTree->SetBranchAddress("P6Error", &PError[5]);
   ResultTree->SetBranchAddress("P7Error", &PError[6]);
   ResultTree->SetBranchAddress("P8Error", &PError[7]);
   ResultTree->SetBranchAddress("Status", &Status);
   ResultTree->SetBranchAddress("Basis", &Basis);

   double MaxX = 0, MinX = 0, MaxY = 0, MinY = 0;

   int EntryCount = ResultTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      ResultTree->GetEntry(iE);

      if(Status < 3)       continue;
      if(Basis < 3)        continue;

      if(PError[0] > 0)    continue;
      if(PError[1] > 0)    continue;
      if(PError[2] > 0)    continue;
      if(PError[3] > 0)    continue;   // Bad coding!
      if(PError[4] == 0)   continue;
      if(PError[5] > 0)    continue;
      if(PError[6] == 0)   continue;
      if(PError[7] > 0)    continue;

      if(PError[0] > 900)  continue;
      if(PError[1] > 900)  continue;
      if(PError[2] > 900)  continue;
      if(PError[3] > 900)  continue;
      if(PError[4] > 900)  continue;
      if(PError[5] > 900)  continue;
      if(PError[6] > 900)  continue;
      if(PError[7] > 900)  continue;

      // cout << "YTA BUG ACTIVE!" << endl;
      // P[4] = P[4] * -2;
      // PError[4] = PError[4] * -2;

      X.push_back(P[6] - 2);
      Y.push_back(P[4] - 0);

      if(P[6] - 2 < MinX)   MinX = P[6] - 2;
      if(P[6] - 2 > MaxX)   MaxX = P[6] - 2;
      if(P[4] - 0 < MinY)   MinY = P[4] - 0;
      if(P[4] - 0 > MaxY)   MaxY = P[4] - 0;
   }

   double DeltaX = MaxX - MinX;
   double DeltaY = MaxY - MinY;

   MaxX = MaxX + DeltaX * 0.05;
   MinX = MinX - DeltaX * 0.05;
   MaxY = MaxY + DeltaY * 0.05;
   MinY = MinY - DeltaY * 0.05;

   TH2D H("H", "", 100, MinX, MaxX, 100, MinY, MaxY);

   for(int i = 0; i < (int)X.size(); i++)
      H.Fill(X[i], Y[i]);
   
   TF2 F("GAUS2", "[0]*exp(-(cos([1])*x+sin([1])*y)*(cos([1])*x+sin([1])*y)/[2]-(sin([1])*x-cos([1])*y)*(sin([1])*x-cos([1])*y)/[3])");
   F.SetParameter(0, 1);
   F.SetParameter(2, 10);
   F.SetParameter(3, 1);

   cout << "Data size = " << X.size() << endl;
   H.Fit(&F);

   double Angle = F.GetParameter(1);
   
   // HACK //
   Angle = 0;

   double XX1 = 0, XX2 = 0;

   for(int i = 0; i < (int)X.size(); i++)
   {
      double x1 = cos(Angle) * X[i] + sin(Angle) * Y[i];
      double x2 = sin(Angle) * X[i] - cos(Angle) * Y[i];

      XX1 = XX1 + x1 * x1;
      XX2 = XX2 + x2 * x2;
   }

   FitResult Result;

   Result.Angle = Angle;
   Result.Variance1 = XX1 / (int)X.size();
   Result.Variance2 = XX2 / (int)X.size();

   return Result;
}






