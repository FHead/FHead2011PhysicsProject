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

   InterpretationCoefficients CSM;
   CSM.mw = 79.95;
   CSM.mt = 173.21;
   CSM.yt = 1;
   CSM.yta = 0;
   CSM.gww = 2;

   double A2AA_GWW = InterpretedA2AA_W_Roberto13711(CSM) / CSM.gww;
   double A2AA_YT = InterpretedA2AA_Top_Roberto13711(CSM) / CSM.yt;
   double A2ZA_GWW = InterpretedA2ZA_W_Roberto13711(CSM) / CSM.gww;
   double A2ZA_YT = InterpretedA2ZA_Top_Roberto13711(CSM) / CSM.yt;

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

      double XMax = 2 + sqrt(ResultASB.Variance1) * cos(ResultASB.Angle);
      double XMin = 2 - sqrt(ResultASB.Variance1) * cos(ResultASB.Angle);
      double YMax = 1 + sqrt(ResultASB.Variance1) * sin(ResultASB.Angle);
      double YMin = 1 - sqrt(ResultASB.Variance1) * sin(ResultASB.Angle);

      double DeltaX = XMax - XMin;
      double DeltaY = YMax - YMin;

      XMax = XMax + DeltaX * 0.15;
      XMin = XMin - DeltaX * 0.15;
      YMax = YMax + DeltaY * 0.15;
      YMin = YMin - DeltaY * 0.15;

      TGraph GAA1, GAA2, GAA3, GAA4, GAA5;
      TGraph GZA1, GZA2, GZA3, GZA4, GZA5;
      TGraph GNAA1, GNAA2, GNAA3, GNAA4, GNAA5;
      TGraph GNZA1, GNZA2, GNZA3, GNZA4, GNZA5;

      GAA1.SetPoint(0, (A2AA_SM * sqrt(1.09) - YMin * A2AA_YT) / A2AA_GWW, YMin);   GAA1.SetPoint(1, (A2AA_SM * sqrt(1.09) - YMax * A2AA_YT) / A2AA_GWW, YMax);
      GAA2.SetPoint(0, (A2AA_SM * sqrt(1.06) - YMin * A2AA_YT) / A2AA_GWW, YMin);   GAA2.SetPoint(1, (A2AA_SM * sqrt(1.06) - YMax * A2AA_YT) / A2AA_GWW, YMax);
      GAA3.SetPoint(0, (A2AA_SM * sqrt(1.00) - YMin * A2AA_YT) / A2AA_GWW, YMin);   GAA3.SetPoint(1, (A2AA_SM * sqrt(1.00) - YMax * A2AA_YT) / A2AA_GWW, YMax);
      GAA4.SetPoint(0, (A2AA_SM * sqrt(0.94) - YMin * A2AA_YT) / A2AA_GWW, YMin);   GAA4.SetPoint(1, (A2AA_SM * sqrt(0.94) - YMax * A2AA_YT) / A2AA_GWW, YMax);
      GAA5.SetPoint(0, (A2AA_SM * sqrt(0.91) - YMin * A2AA_YT) / A2AA_GWW, YMin);   GAA5.SetPoint(1, (A2AA_SM * sqrt(0.91) - YMax * A2AA_YT) / A2AA_GWW, YMax);
      GZA1.SetPoint(0, (A2ZA_SM * sqrt(1.62) - YMin * A2ZA_YT) / A2ZA_GWW, YMin);   GZA1.SetPoint(1, (A2ZA_SM * sqrt(1.62) - YMax * A2ZA_YT) / A2ZA_GWW, YMax);
      GZA2.SetPoint(0, (A2ZA_SM * sqrt(1.22) - YMin * A2ZA_YT) / A2ZA_GWW, YMin);   GZA2.SetPoint(1, (A2ZA_SM * sqrt(1.22) - YMax * A2ZA_YT) / A2ZA_GWW, YMax);
      GZA3.SetPoint(0, (A2ZA_SM * sqrt(1.00) - YMin * A2ZA_YT) / A2ZA_GWW, YMin);   GZA3.SetPoint(1, (A2ZA_SM * sqrt(1.00) - YMax * A2ZA_YT) / A2ZA_GWW, YMax);
      GZA4.SetPoint(0, (A2ZA_SM * sqrt(0.78) - YMin * A2ZA_YT) / A2ZA_GWW, YMin);   GZA4.SetPoint(1, (A2ZA_SM * sqrt(0.78) - YMax * A2ZA_YT) / A2ZA_GWW, YMax);
      GZA5.SetPoint(0, (A2ZA_SM * sqrt(0.38) - YMin * A2ZA_YT) / A2ZA_GWW, YMin);   GZA5.SetPoint(1, (A2ZA_SM * sqrt(0.38) - YMax * A2ZA_YT) / A2ZA_GWW, YMax);
      GNAA1.SetPoint(0, (-A2AA_SM * sqrt(1.09) - YMin * A2AA_YT) / A2AA_GWW, YMin);   GNAA1.SetPoint(1, (-A2AA_SM * sqrt(1.09) - YMax * A2AA_YT) / A2AA_GWW, YMax);
      GNAA2.SetPoint(0, (-A2AA_SM * sqrt(1.06) - YMin * A2AA_YT) / A2AA_GWW, YMin);   GNAA2.SetPoint(1, (-A2AA_SM * sqrt(1.06) - YMax * A2AA_YT) / A2AA_GWW, YMax);
      GNAA3.SetPoint(0, (-A2AA_SM * sqrt(1.00) - YMin * A2AA_YT) / A2AA_GWW, YMin);   GNAA3.SetPoint(1, (-A2AA_SM * sqrt(1.00) - YMax * A2AA_YT) / A2AA_GWW, YMax);
      GNAA4.SetPoint(0, (-A2AA_SM * sqrt(0.94) - YMin * A2AA_YT) / A2AA_GWW, YMin);   GNAA4.SetPoint(1, (-A2AA_SM * sqrt(0.94) - YMax * A2AA_YT) / A2AA_GWW, YMax);
      GNAA5.SetPoint(0, (-A2AA_SM * sqrt(0.91) - YMin * A2AA_YT) / A2AA_GWW, YMin);   GNAA5.SetPoint(1, (-A2AA_SM * sqrt(0.91) - YMax * A2AA_YT) / A2AA_GWW, YMax);
      GNZA1.SetPoint(0, (-A2ZA_SM * sqrt(1.62) - YMin * A2ZA_YT) / A2ZA_GWW, YMin);   GNZA1.SetPoint(1, (-A2ZA_SM * sqrt(1.62) - YMax * A2ZA_YT) / A2ZA_GWW, YMax);
      GNZA2.SetPoint(0, (-A2ZA_SM * sqrt(1.22) - YMin * A2ZA_YT) / A2ZA_GWW, YMin);   GNZA2.SetPoint(1, (-A2ZA_SM * sqrt(1.22) - YMax * A2ZA_YT) / A2ZA_GWW, YMax);
      GNZA3.SetPoint(0, (-A2ZA_SM * sqrt(1.00) - YMin * A2ZA_YT) / A2ZA_GWW, YMin);   GNZA3.SetPoint(1, (-A2ZA_SM * sqrt(1.00) - YMax * A2ZA_YT) / A2ZA_GWW, YMax);
      GNZA4.SetPoint(0, (-A2ZA_SM * sqrt(0.78) - YMin * A2ZA_YT) / A2ZA_GWW, YMin);   GNZA4.SetPoint(1, (-A2ZA_SM * sqrt(0.78) - YMax * A2ZA_YT) / A2ZA_GWW, YMax);
      GNZA5.SetPoint(0, (-A2ZA_SM * sqrt(0.38) - YMin * A2ZA_YT) / A2ZA_GWW, YMin);   GNZA5.SetPoint(1, (-A2ZA_SM * sqrt(0.38) - YMax * A2ZA_YT) / A2ZA_GWW, YMax);

      GAA1.SetLineWidth(2);   GAA1.SetLineColor(kBlue);        GAA1.SetLineStyle(kDashed);
      GAA2.SetLineWidth(2);   GAA2.SetLineColor(kBlue);        GAA2.SetLineStyle(kDashed);
      GAA3.SetLineWidth(2);   GAA3.SetLineColor(kBlue);        GAA3.SetLineStyle(kSolid);
      GAA4.SetLineWidth(2);   GAA4.SetLineColor(kBlue);        GAA4.SetLineStyle(kDashed);
      GAA5.SetLineWidth(2);   GAA5.SetLineColor(kBlue);        GAA5.SetLineStyle(kDashed);
      GZA1.SetLineWidth(2);   GZA1.SetLineColor(kGreen - 3);   GZA1.SetLineStyle(kDashed);
      GZA2.SetLineWidth(2);   GZA2.SetLineColor(kGreen - 3);   GZA2.SetLineStyle(kDashed);
      GZA3.SetLineWidth(2);   GZA3.SetLineColor(kGreen - 3);   GZA3.SetLineStyle(kSolid);
      GZA4.SetLineWidth(2);   GZA4.SetLineColor(kGreen - 3);   GZA4.SetLineStyle(kDashed);
      GZA5.SetLineWidth(2);   GZA5.SetLineColor(kGreen - 3);   GZA5.SetLineStyle(kDashed);
      GNAA1.SetLineWidth(2);   GNAA1.SetLineColor(kBlue);        GNAA1.SetLineStyle(kDotted);
      GNAA2.SetLineWidth(2);   GNAA2.SetLineColor(kBlue);        GNAA2.SetLineStyle(kDotted);
      GNAA3.SetLineWidth(2);   GNAA3.SetLineColor(kBlue);        GNAA3.SetLineStyle(kSolid);
      GNAA4.SetLineWidth(2);   GNAA4.SetLineColor(kBlue);        GNAA4.SetLineStyle(kDotted);
      GNAA5.SetLineWidth(2);   GNAA5.SetLineColor(kBlue);        GNAA5.SetLineStyle(kDotted);
      GNZA1.SetLineWidth(2);   GNZA1.SetLineColor(kGreen - 3);   GNZA1.SetLineStyle(kDotted);
      GNZA2.SetLineWidth(2);   GNZA2.SetLineColor(kGreen - 3);   GNZA2.SetLineStyle(kDotted);
      GNZA3.SetLineWidth(2);   GNZA3.SetLineColor(kGreen - 3);   GNZA3.SetLineStyle(kSolid);
      GNZA4.SetLineWidth(2);   GNZA4.SetLineColor(kGreen - 3);   GNZA4.SetLineStyle(kDotted);
      GNZA5.SetLineWidth(2);   GNZA5.SetLineColor(kGreen - 3);   GNZA5.SetLineStyle(kDotted);

      TCanvas C;

      TH2D HWorld("HWorld", ";g_{WW};y_{t}", 100, XMin, XMax, 100, YMin, YMax);
      HWorld.SetStats(0);

      TEllipse EllipseASB(2, 1, sqrt(ResultASB.Variance1), sqrt(ResultASB.Variance2), 0, 360, (ResultASB.Angle) / PI * 180);
      TEllipse EllipseJSB(2, 1, sqrt(ResultJSB.Variance1), sqrt(ResultJSB.Variance2), 0, 360, (ResultJSB.Angle) / PI * 180);
      TEllipse EllipseJS (2, 1, sqrt(ResultJS .Variance1), sqrt(ResultJS .Variance2), 0, 360, (ResultJS .Angle) / PI * 180);

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
      GNAA1.Draw("l");
      GNAA2.Draw("l");
      GNAA3.Draw("l");
      GNAA4.Draw("l");
      GNAA5.Draw("l");
      GNZA1.Draw("l");
      GNZA2.Draw("l");
      GNZA3.Draw("l");
      GNZA4.Draw("l");
      GNZA5.Draw("l");

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

      AddHeader("check yta bug.", true);

      C.SaveAs(Form("FigureC_%05d.png", N[iN] * 2));
      C.SaveAs(Form("FigureC_%05d.C", N[iN] * 2));
      C.SaveAs(Form("FigureC_%05d.eps", N[iN] * 2));
      C.SaveAs(Form("FigureC_%05d.pdf", N[iN] * 2));
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
      if(PError[3] == 0)   continue;   // Bad coding!
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

      X.push_back(P[6] - 2);
      Y.push_back(P[3] - 1);

      if(P[6] - 2 < MinX)   MinX = P[6] - 2;
      if(P[6] - 2 > MaxX)   MaxX = P[6] - 2;
      if(P[3] - 1 < MinY)   MinY = P[3] - 1;
      if(P[3] - 1 > MaxY)   MaxY = P[3] - 1;
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
   if(X.size() < 1000)
      Angle = 1.18697;

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






