#include "TF1.h"
#include "TFile.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TPaveStats.h"

#define TYPE_FITFIX 5
#define TYPE_FIT 0
#define TYPE_SMOOTH_LOOSE 1
#define TYPE_SMOOTH_TIGHT 2
#define TYPE_SMOOTH_SUPERTIGHT 3
#define TYPE_SMOOTH_ULTRATIGHT 4

#define TARGET 0.95

double FitTurnOn(PdfFileHelper &PdfFile, TH1D *H1, TH1D *H2, double Target = TARGET,
   bool tanh = false, bool noweight = false, bool Fix = false);
double SmoothTurnOn(PdfFileHelper &PdfFile, TH1D *H1, TH1D *H2, double Target = TARGET,
   int Type = TYPE_SMOOTH_LOOSE);
double Find95(TF1 &F, double Min, double Max, double Target = 0.95);
double Find95(TGraph &F, double Min, double Max, double Target = 0.95);
double Eval(TGraph &G, double x);
vector<double> Tridiagonal(vector<double> H, vector<double> K1, double K2);

double FitTurnOn(PdfFileHelper &PdfFile, TH1D *H1, TH1D *H2, double Target, bool tanh, bool noweight, bool Fix)
{
   cout << H1 << " " << H2 << endl;

   if(H1 == NULL || H2 == NULL)
      return -1;

   TCanvas Canvas;

   H2->SetStats(0);
   H1->SetLineColor(kRed);
   H1->SetMarkerColor(kRed);
   H2->SetLineColor(kBlack);
   H2->SetMarkerColor(kBlack);
   
   H2->Draw();
   H1->Draw("same");

   PdfFile.AddCanvas(Canvas);

   TH1D *H1Temp = (TH1D *)H1->Clone();
   TH1D *H2Temp = (TH1D *)H2->Clone();

   double MinX = H1Temp->GetXaxis()->GetBinLowEdge(1);
   double MaxX = H1Temp->GetXaxis()->GetBinUpEdge(H1Temp->GetNbinsX());
   
   H1Temp->Rebin(2);
   H2Temp->Rebin(2);

   TGraphAsymmErrors G;
   G.Divide(H1Temp, H2Temp);

   TH2D HWorld("HWorld", ";;", 100, MinX, MaxX, 100, 0, 1.1);
   HWorld.SetStats(0);
   HWorld.Draw("axis");

   G.Draw("p");
   
   TGraph GLine;
   GLine.SetPoint(0, 0, Target);
   GLine.SetPoint(1, 10000, Target);
   GLine.Draw("l");
   GLine.SetLineStyle(kDashed);
   
   TGraph GLine2;
   GLine2.SetPoint(0, 0, 1.00);
   GLine2.SetPoint(1, 10000, 1.00);
   GLine2.Draw("l");

   PdfFile.AddCanvas(Canvas);
   
   string Function;
   Function = "(ROOT::Math::normal_cdf([0]*(x-[1]), [0]*[2], 0) - exp(-[0]*(x-[1])+[0]*[0]*[2]*[2]/2)*ROOT::Math::normal_cdf([0]*(x-[1]), [0]*[2], [0]*[0]*[2]*[2])) * [3]";
   if(tanh == true)
      Function = "[2] + [3] * tanh([0] * (x - [1]))";

   TF1 Fit("Fit", Function.c_str(), MinX, MaxX);

   Fit.SetParameters(0.02, 100, 20, 1.0);
   Fit.SetParNames("#lambda", "#mu", "#sigma", "Plateau");
   if(Fix == true)
      Fit.FixParameter(3, 1.0);
   
   if(tanh == true)
   {
      Fit.SetParameters(0.5, 15, 0.5, 0.5);
      Fit.SetParNames("Steepness", "Midpoint");
   }

   for(int i = 0; i < 10; i++)
   {
      if(noweight == true)
         G.Fit(&Fit, "W", "", MinX, MaxX);
      else
         G.Fit(&Fit, "", "", MinX, MaxX);
   }
   
   TGraph GLine3;
   GLine3.SetPoint(0, 0, Target * Fit.Eval(10000));
   GLine3.SetPoint(1, 10000, Target * Fit.Eval(10000));
   GLine3.SetLineStyle(kDashed);
   GLine3.SetLineColor(kMagenta);

   TH2D HWorld2("HWorld2", ";;", 100, MinX, MaxX, 100, 0, 1.1);
   HWorld2.SetStats(0);
   HWorld2.Draw();

   G.Draw("p");

   GLine.Draw("l");
   GLine2.Draw("l");
   GLine3.Draw("l");

   Canvas.Update();

   TPaveStats *Box = (TPaveStats *)(G.GetListOfFunctions()->FindObject("stats"));
   Box->Draw();

   PdfFile.AddCanvas(Canvas);

   return Find95(Fit, MinX, MaxX, Target * Fit.Eval(10000));
}

double SmoothTurnOn(PdfFileHelper &PdfFile, TH1D *H1, TH1D *H2, double Target, int Type)
{
   cout << H1 << " " << H2 << endl;

   if(H1 == NULL || H2 == NULL)
      return -1;

   TCanvas Canvas;

   H2->SetStats(0);
   H1->SetLineColor(kRed);
   H1->SetMarkerColor(kRed);
   H2->SetLineColor(kBlack);
   H2->SetMarkerColor(kBlack);
   
   H2->Draw();
   H1->Draw("same");

   PdfFile.AddCanvas(Canvas);

   TH1D *H1Temp = (TH1D *)H1->Clone();
   TH1D *H2Temp = (TH1D *)H2->Clone();
   
   double MinX = H1Temp->GetXaxis()->GetBinLowEdge(1);
   double MaxX = H1Temp->GetXaxis()->GetBinUpEdge(H1Temp->GetNbinsX());
   
   // H1Temp->Rebin(2);
   // H2Temp->Rebin(2);

   TGraphAsymmErrors G;
   G.Divide(H1Temp, H2Temp);

   TH2D HWorld("HWorld", ";;", 100, MinX, MaxX, 100, 0, 1.1);
   HWorld.SetStats(0);
   HWorld.Draw("axis");

   G.Draw("p");
   
   TGraph GLine;
   GLine.SetPoint(0, 0, Target);
   GLine.SetPoint(1, 10000, Target);
   GLine.Draw("l");
   GLine.SetLineStyle(kDashed);
   
   TGraph GLine2;
   GLine2.SetPoint(0, 0, 1.00);
   GLine2.SetPoint(1, 10000, 1.00);
   GLine2.Draw("l");

   PdfFile.AddCanvas(Canvas);
   
   vector<double> H;
   vector<double> K1;
   for(int i = 0; i < G.GetN(); i++)
   {
      double x, y;
      G.GetPoint(i, x, y);
      H.push_back(y);
      K1.push_back(1 / (G.GetErrorYhigh(i) + G.GetErrorYlow(i)) / (G.GetErrorYhigh(i) + G.GetErrorYlow(i)));
   }

   double Tension = 400;
   if(Type == TYPE_SMOOTH_ULTRATIGHT)
      Tension = 2000;
   if(Type == TYPE_SMOOTH_SUPERTIGHT)
      Tension = 1000;
   if(Type == TYPE_SMOOTH_TIGHT)
      Tension = 100;
   if(Type == TYPE_SMOOTH_LOOSE)
      Tension = 1;

   vector<double> Y = Tridiagonal(H, K1, Tension);

   TGraph Fit;
   for(int i = 0; i < G.GetN(); i++)
   {
      double x, y;
      G.GetPoint(i, x, y);
      Fit.SetPoint(i, x, Y[i]);
   }
   Fit.SetLineColor(kRed);

   TH2D HWorld2("HWorld2", ";;", 100, MinX, MaxX, 100, 0, 1.1);
   HWorld2.SetStats(0);
   HWorld2.Draw();

   G.Draw("p");
   Fit.Draw("l");

   GLine.Draw("l");
   GLine2.Draw("l");

   Canvas.Update();

   PdfFile.AddCanvas(Canvas);

   return Find95(Fit, MinX, MaxX, Target);
}

double Find95(TF1 &F, double Min, double Max, double Target)
{
   if(F.Eval(Min) > Target || F.Eval(Max) < Target)
      return -1000;

   double L = Min;
   double R = Max;

   while(R - L > 1e-4)
   {
      double C = (L + R) / 2;
      double V = F.Eval(C);

      if(V < Target)
         L = C;
      else
         R = C;
   }

   return (R + L) / 2;
}

vector<double> Tridiagonal(vector<double> H, vector<double> K1, double K2)
{
   int N = H.size();

   // Initialization
   vector<double> A(N);
   vector<double> B(N);
   vector<double> C(N);

   for(int i = 0; i < N; i++)
   {
      A[i] = -K2;
      B[i] = K1[i] + 2 * K2;
      C[i] = -K2;
   }

   A[0] = 0;
   C[N-1] = 0;

   vector<double> D(N);

   for(int i = 0; i < N; i++)
      D[i] = K1[i] * H[i];
   D[0] = D[0] + K2 * 0;
   D[N-1] = D[N-1] + K2 * 1;

   // Forward sweep to eliminate the A's
   for(int i = 1; i < N; i++)
   {
      double F = A[i] / B[i-1];

      A[i] = A[i] - B[i-1] * F;
      B[i] = B[i] - C[i-1] * F;
      C[i] = C[i];   // no change to C[i]
      D[i] = D[i] - D[i-1] * F;
   }

   // Backward substitution to get all the Y's

   vector<double> Y(N);

   Y[N-1] = D[N-1] / B[N-1];
   for(int i = N - 2; i >= 0; i--)
      Y[i] = (D[i] - C[i] * Y[i+1]) / B[i];

   return Y;
}

double Find95(TGraph &G, double Min, double Max, double Target)
{
   if(Eval(G, Min) > Target || Eval(G, Max) < Target)
      return -1000;

   double L = Min;
   double R = Max;

   while(R - L > 1e-4)
   {
      double C = (L + R) / 2;
      double V = Eval(G, C);

      if(V < Target)
         L = C;
      else
         R = C;
   }

   return (R + L) / 2;
}

double Eval(TGraph &G, double x)
{
   int N = G.GetN();
   
   double xtemp, ytemp;
   G.GetPoint(0, xtemp, ytemp);
   if(x < xtemp)
      return 0;

   G.GetPoint(N - 1, xtemp, ytemp);
   if(x >= xtemp)
      return 1;

   double xl, yl, xr, yr;
   G.GetPoint(0, xr, yr);
   
   for(int i = 0; i < N - 1; i++)
   {
      xl = xr;
      yl = yr;
      G.GetPoint(i + 1, xr, yr);

      if(x < xr && x >= xl)
         return yl + (yr - yl) / (xr - xl) * (x - xl);
   }

   return -1;   // something wrong
}

