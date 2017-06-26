#include <iostream>
#include <vector>
using namespace std;

#include "TF1.h"
#include "TFile.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TPaveStats.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

#define TYPE_ALL 0
#define TYPE_LOW 1
#define TYPE_HIGH 2
#define TYPE_ALLLOOSE 3

#define TARGET 0.95

int main();
void Process(PdfFileHelper &PdfFile, string FileName, string Prefix, vector<double> Thresholds, string Tag, int Type = TYPE_ALL);
void MultiProcess(PdfFileHelper &PdfFile, string FileName, string Prefix, vector<double> Thresholds, string Tag, bool IsEle);
void MultiProcess(PdfFileHelper &PdfFile, string FileName, string Prefix, vector<double> Thresholds, string Tag, bool IsEle, int Type);
double FitTurnOn(PdfFileHelper &PdfFile, TH1D *H1, TH1D *H2, bool tanh = false, bool noweight = false);
double SmoothTurnOn(PdfFileHelper &PdfFile, TH1D *H1, TH1D *H2, int Type = TYPE_ALL);
vector<double> ToVector(int N, double X1 = -1, double X2 = -1, double X3 = -1,
   double X4 = -1, double X5 = -1, double X6 = -1, double X7 = -1, double X8 = -1,
   double X9 = -1, double X10 = -1, double X11 = -1, double X12 = -1, double X13 = -1,
   double X14 = -1, double X15 = -1, double X16 = -1, double X17 = -1, double X18 = -1,
   double X19 = -1, double X20 = -1, double X21 = -1, double X22 = -1, double X23 = -1,
   double X24 = -1, double X25 = -1);
double Find95(TF1 &F, double Min, double Max, double Target = 0.95);
double Find95(TGraph &F, double Min, double Max, double Target = 0.95);
double Eval(TGraph &G, double x);
vector<double> Tridiagonal(vector<double> H, vector<double> K1, double K2);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("ScalingPlots.pdf");
   PdfFile.AddTextPage("Scaling plots :D");
   
   TFile OutputFile("ScalingCurves.root", "RECREATE");
   OutputFile.Close();

   Process(PdfFile, "Result/Combined/WToEnu140PU.root", "TkEG/TkEG", ToVector(5, 12, 15, 20, 25, 30), "WENu140");
   Process(PdfFile, "Result/Combined/WToEnu200PU.root", "TkEG/TkEG", ToVector(5, 12, 15, 20, 25, 30), "WENu200");
   Process(PdfFile, "Result/Combined/WToEnu140PU.root", "TkIsoEG/TkIsoEG", ToVector(5, 12, 15, 20, 25, 30), "WENu140Iso");
   Process(PdfFile, "Result/Combined/WToEnu200PU.root", "TkIsoEG/TkIsoEG", ToVector(5, 12, 15, 20, 25, 30), "WENu200Iso");
   // Process(PdfFile, "Result/Combined/Hgg140PU.root", "TkEM/TkEM", ToVector(5, 12, 15, 20, 25, 30), "Hgg140");
   // Process(PdfFile, "Result/Combined/Hgg200PU.root", "TkEM/TkEM", ToVector(5, 12, 15, 20, 25, 30), "Hgg200");
   
   /*
   Process(PdfFile, "Result/Combined/WToEnu140PU.root", "EGEle/EGEle", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu140PU.root", "IsoEGEle/IsoEGEle", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu140PU.root", "TkEG/TkEG", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu140PU.root", "TkIsoEG/TkIsoEG", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu140PU_NewRecipePlusTyler.root", "EGEle/EGEle", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu140PU_NewRecipePlusTyler.root", "IsoEGEle/IsoEGEle", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu140PU_NewRecipePlusTyler.root", "TkEG/TkEG", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu140PU_NewRecipePlusTyler.root", "TkIsoEG/TkIsoEG", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu200PU.root", "EGEle/EGEle", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu200PU.root", "IsoEGEle/IsoEGEle", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu200PU.root", "TkEG/TkEG", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu200PU.root", "TkIsoEG/TkIsoEG", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu200PU_NewRecipePlusTyler.root", "EGEle/EGEle", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu200PU_NewRecipePlusTyler.root", "IsoEGEle/IsoEGEle", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu200PU_NewRecipePlusTyler.root", "TkEG/TkEG", ToVector(5, 12, 15, 20, 25, 30));
   Process(PdfFile, "Result/Combined/WToEnu200PU_NewRecipePlusTyler.root", "TkIsoEG/TkIsoEG", ToVector(5, 12, 15, 20, 25, 30));
   */
   
   MultiProcess(PdfFile, "Result/Combined/WToEnu140PU_NewRecipePlusTyler_NoIso.root", "TkEG/TkEG", ToVector(5, 12, 15, 20, 25, 30), "WENu140Tyler", true, TYPE_ALL);
   MultiProcess(PdfFile, "Result/Combined/WToEnu200PU_NewRecipePlusTyler_NoIso.root", "TkEG/TkEG", ToVector(5, 12, 15, 20, 25, 30), "WENu200Tyler", true, TYPE_ALL);
   // MultiProcess(PdfFile, "Result/Combined/Hgaga140PU_NewRecipePlusTyler_NoIso.root", "TkEM/TkEM", ToVector(5, 12, 15, 20, 25, 30), "Hgaga140Tyler", false);
   // MultiProcess(PdfFile, "Result/Combined/Hgaga200PU_NewRecipePlusTyler_NoIso.root", "TkEM/TkEM", ToVector(5, 12, 15, 20, 25, 30), "Hgaga200Tyler", false);
   
   MultiProcess(PdfFile, "Result/Combined/WToEnu140PU_NewRecipePlusTyler_NoIso.root", "TkEG/TkEG", ToVector(5, 12, 15, 20, 25, 30), "WENu140TylerLow", true, TYPE_LOW);
   MultiProcess(PdfFile, "Result/Combined/WToEnu200PU_NewRecipePlusTyler_NoIso.root", "TkEG/TkEG", ToVector(5, 12, 15, 20, 25, 30), "WENu200TylerLow", true, TYPE_LOW);
   MultiProcess(PdfFile, "Result/Combined/WToEnu140PU_NewRecipePlusTyler_NoIso.root", "TkEG/TkEG", ToVector(5, 12, 15, 20, 25, 30), "WENu140TylerHigh", true, TYPE_HIGH);
   MultiProcess(PdfFile, "Result/Combined/WToEnu200PU_NewRecipePlusTyler_NoIso.root", "TkEG/TkEG", ToVector(5, 12, 15, 20, 25, 30), "WENu200TylerHigh", true, TYPE_HIGH);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return -1;
}

void Process(PdfFileHelper &PdfFile, string FileName, string Prefix, vector<double> Thresholds, string Tag, int Type)
{
   string TypeString = "UNKNOWN";
   if(Type == TYPE_ALL)
      TypeString = "TYPE_ALL";
   if(Type == TYPE_LOW)
      TypeString = "TYPE_LOW";
   if(Type == TYPE_HIGH)
      TypeString = "TYPE_HIGH";
   if(Type == TYPE_ALLLOOSE)
      TypeString = "TYPE_ALLLOOSE";

   vector<string> Text(10);
   Text[0] = "Plots for file";
   Text[1] = FileName;
   Text[2] = "";
   Text[3] = "...and object prefix";
   Text[4] = Prefix;
   Text[5] = "";
   Text[6] = "...and type";
   Text[7] = TypeString;
   PdfFile.AddTextPage(Text);

   TFile File(FileName.c_str());

   vector<double> CrossOver(Thresholds.size());

   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      PdfFile.AddTextPage(Form("Threshold = %.1f", Thresholds[i]));
      CrossOver[i] = SmoothTurnOn(PdfFile,
         (TH1D *)File.Get(Form("%s_PT_%06d", Prefix.c_str(), (int)Thresholds[i] * 100)),
         (TH1D *)File.Get(Form("%s_PT_000000", Prefix.c_str())), TYPE_ALLLOOSE);
   }

   File.Close();
   
   PdfFile.AddTextPage("Scaling Curve");
   
   TFile OutputFile("ScalingCurves.root", "UPDATE");

   TGraph G;
   G.SetNameTitle(Tag.c_str(), "");

   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      if(CrossOver[i] > 0)
         G.SetPoint(G.GetN(), Thresholds[i], CrossOver[i]);
   }
   PdfFile.AddPlot(G, "apl");

   G.Write();

   OutputFile.Close();
}

void MultiProcess(PdfFileHelper &PdfFile, string FileName, string Prefix, vector<double> Thresholds, string Tag, bool IsEle, int Type)
{
   string TypeString = "UNKNOWN";
   if(Type == TYPE_ALL)
      TypeString = "No eta cut";
   if(Type == TYPE_LOW)
      TypeString = "|#eta| < 1.0";
   if(Type == TYPE_HIGH)
      TypeString = "|#eta| > 1.0";
   if(Type == TYPE_ALLLOOSE)
      TypeString = "No eta cut, low tension";

   vector<string> Text(10);
   Text[0] = "Plots for file";
   Text[1] = FileName;
   Text[2] = "";
   Text[3] = "...and object prefix";
   Text[4] = Prefix;
   Text[5] = "";
   Text[6] = "...and tyle";
   Text[7] = TypeString;
   PdfFile.AddTextPage(Text);

   TFile File(FileName.c_str());

   vector<double> CrossOverA(Thresholds.size());
   vector<double> CrossOverB(Thresholds.size());

   string EtaString = "";
   if(Type == TYPE_LOW)
      EtaString = "Eta10";
   if(Type == TYPE_HIGH)
      EtaString = "EtaLarge";

   Prefix = Prefix + "_PT" + EtaString;

   for(int i = 0; i < (int)Thresholds.size(); i++)
   {
      if(IsEle == true)
      {
         PdfFile.AddTextPage(Form("Threshold = %.1f (Iso = 0.10)", Thresholds[i]));
         CrossOverA[i] = SmoothTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%sIso010_%06d", Prefix.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%sIso010_000000", Prefix.c_str())), Type);
         
         PdfFile.AddTextPage(Form("Threshold = %.1f (Iso = 0.14)", Thresholds[i]));
         CrossOverB[i] = SmoothTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%sIso014_%06d", Prefix.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%sIso014_000000", Prefix.c_str())), Type);
      }
      else
      {
         PdfFile.AddTextPage(Form("Threshold = %.1f (Iso = 0.23)", Thresholds[i]));
         CrossOverA[i] = SmoothTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%sIso023_%06d", Prefix.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%sIso023_000000", Prefix.c_str())), Type);
         
         PdfFile.AddTextPage(Form("Threshold = %.1f (Iso = 0.45)", Thresholds[i]));
         CrossOverB[i] = SmoothTurnOn(PdfFile,
            (TH1D *)File.Get(Form("%sIso045_%06d", Prefix.c_str(), (int)Thresholds[i] * 100)),
            (TH1D *)File.Get(Form("%sIso045_000000", Prefix.c_str())), Type);
      }
   }

   File.Close();

   TFile OutputFile("ScalingCurves.root", "UPDATE");

   PdfFile.AddTextPage("Scaling Curve");

   TGraph GA, GB;
   for(int i = 0; i < (int)Thresholds.size(); i++)
      if(CrossOverA[i] > 0)
         GA.SetPoint(GA.GetN(), Thresholds[i], CrossOverA[i]);
   for(int i = 0; i < (int)Thresholds.size(); i++)
      if(CrossOverB[i] > 0)
         GB.SetPoint(GB.GetN(), Thresholds[i], CrossOverB[i]);

   GA.SetNameTitle((Tag + "A").c_str(), "");
   GB.SetNameTitle((Tag + "B").c_str(), "");

   GA.Write();
   GB.Write();

   /*
   if(IsEle == true)
   {
      GA.SetTitle("Iso = 0.10");
      GB.SetTitle("Iso = 0.14");
   }
   else
   {
      GA.SetTitle("Iso = 0.23");
      GB.SetTitle("Iso = 0.45");
   }

   PdfFile.AddPlot(GA, "apl");
   PdfFile.AddPlot(GB, "apl");
   */

   TCanvas Canvas;

   GA.SetTitle("");
   
   GA.Draw("apl");
   GB.Draw("pl");

   GB.SetMarkerColor(kRed);
   GB.SetLineColor(kRed);

   TLegend Legend(0.5, 0.2, 0.8, 0.4);
   Legend.SetTextSize(0.035);
   Legend.SetTextFont(42);
   if(IsEle == true)
   {
      Legend.AddEntry(&GA, "Iso = 0.10", "pl");
      Legend.AddEntry(&GB, "Iso = 0.14", "pl");
   }
   else
   {
      Legend.AddEntry(&GA, "Iso = 0.23", "pl");
      Legend.AddEntry(&GB, "Iso = 0.45", "pl");
   }
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
}

double FitTurnOn(PdfFileHelper &PdfFile, TH1D *H1, TH1D *H2, bool tanh, bool noweight)
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
   
   // H1Temp->Rebin(2);
   // H2Temp->Rebin(2);

   TGraphAsymmErrors G;
   G.Divide(H1Temp, H2Temp);

   TH2D HWorld("HWorld", ";;", 100, 0, 60, 100, 0, 1.1);
   HWorld.SetStats(0);
   HWorld.Draw("axis");

   G.Draw("p");
   
   TGraph GLine;
   GLine.SetPoint(0, 0, 0.95);
   GLine.SetPoint(1, 10000, 0.95);
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

   TF1 Fit("Fit", Function.c_str(), 0, 50);

   Fit.SetParameters(0.3, 20, 1.5, 1.0);
   Fit.SetParNames("#lambda", "#mu", "#sigma", "Plateau");
   
   if(tanh == true)
   {
      Fit.SetParameters(0.5, 15, 0.5, 0.5);
      Fit.SetParNames("Steepness", "Midpoint");
   }

   for(int i = 0; i < 10; i++)
   {
      if(noweight == true)
         G.Fit(&Fit, "W", "", 0, 80);
      else
         G.Fit(&Fit, "", "", 0, 80);
   }

   TH2D HWorld2("HWorld2", ";;", 100, 0, 80, 100, 0, 1.1);
   HWorld2.SetStats(0);
   HWorld2.Draw();

   G.Draw("p");

   GLine.Draw("l");
   GLine2.Draw("l");

   Canvas.Update();

   TPaveStats *Box = (TPaveStats *)(G.GetListOfFunctions()->FindObject("stats"));
   Box->Draw();

   PdfFile.AddCanvas(Canvas);

   return Find95(Fit, 0, 100, 0.95);
}

double SmoothTurnOn(PdfFileHelper &PdfFile, TH1D *H1, TH1D *H2, int Type)
{
   cout << H1 << " " << H2 << endl;

   double Target = 0.95;
   if(Type == TYPE_LOW)
      Target = 0.90;
   if(Type == TYPE_HIGH)
      Target = 0.60;

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
   
   // H1Temp->Rebin(2);
   // H2Temp->Rebin(2);

   TGraphAsymmErrors G;
   G.Divide(H1Temp, H2Temp);

   TH2D HWorld("HWorld", ";;", 100, 0, 60, 100, 0, 1.1);
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
   if(Type == TYPE_LOW)
      Tension = 100;
   if(Type == TYPE_ALLLOOSE)
      Tension = 1;

   vector<double> Y = Tridiagonal(H, K1, Tension);

   TGraph Fit;
   for(int i = 0; i < G.GetN(); i++)
   {
      double x, y;
      G.GetPoint(i, x, y);
      Fit.SetPoint(i, x, Y[i]);
   }

   TH2D HWorld2("HWorld2", ";;", 100, 0, 80, 100, 0, 1.1);
   HWorld2.SetStats(0);
   HWorld2.Draw();

   G.Draw("p");
   Fit.Draw("l");

   GLine.Draw("l");
   GLine2.Draw("l");

   Canvas.Update();

   PdfFile.AddCanvas(Canvas);

   return Find95(Fit, 0, 100, Target);
}

vector<double> ToVector(int N, double X1, double X2, double X3,
   double X4, double X5, double X6, double X7, double X8,
   double X9, double X10, double X11, double X12, double X13,
   double X14, double X15, double X16, double X17, double X18,
   double X19, double X20, double X21, double X22, double X23,
   double X24, double X25)
{
   vector<double> Result;

   if(N > 25)
      cerr << "[ToVector] Warning!  More than 25 entries is currently not supported!" << endl;

   if(N >= 1)    Result.push_back(X1);
   if(N >= 2)    Result.push_back(X2);
   if(N >= 3)    Result.push_back(X3);
   if(N >= 4)    Result.push_back(X4);
   if(N >= 5)    Result.push_back(X5);
   if(N >= 6)    Result.push_back(X6);
   if(N >= 7)    Result.push_back(X7);
   if(N >= 8)    Result.push_back(X8);
   if(N >= 9)    Result.push_back(X9);
   if(N >= 10)   Result.push_back(X10);
   if(N >= 11)   Result.push_back(X11);
   if(N >= 12)   Result.push_back(X12);
   if(N >= 13)   Result.push_back(X13);
   if(N >= 14)   Result.push_back(X14);
   if(N >= 15)   Result.push_back(X15);
   if(N >= 16)   Result.push_back(X16);
   if(N >= 17)   Result.push_back(X17);
   if(N >= 18)   Result.push_back(X18);
   if(N >= 19)   Result.push_back(X19);
   if(N >= 20)   Result.push_back(X20);
   if(N >= 21)   Result.push_back(X21);
   if(N >= 22)   Result.push_back(X22);
   if(N >= 23)   Result.push_back(X23);
   if(N >= 24)   Result.push_back(X24);
   if(N >= 25)   Result.push_back(X25);

   return Result;
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

