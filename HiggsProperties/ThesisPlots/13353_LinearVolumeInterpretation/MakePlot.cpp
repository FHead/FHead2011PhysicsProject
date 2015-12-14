#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#include "TCanvas.h"
#include "TLine.h"
#include "TGraph.h"
#include "TLatex.h"

#include "SetStyle.h"

#define PI 3.14159265358979323846264338327950288479716939937510

struct V4;
struct M4;
int main();
V4 transform(V4 X, double L, double H, double D, double wx, double wy, double wz, double theta, double phi, double wd);

struct V4
{
public:
   double X[4];
   V4() {X[0] = X[1] = X[2] = X[3] = 0;}
   V4(double x0, double x1, double x2, double x3) {X[0] = x0; X[1] = x1; X[2] = x2; X[3] = x3;}
   V4 operator +(V4 other) {V4 result;  for(int i = 0; i < 4; i++) result.X[i] = X[i] + other.X[i];   return result;}
   V4 operator -(V4 other) {V4 result;  for(int i = 0; i < 4; i++) result.X[i] = X[i] - other.X[i];   return result;}
   V4 operator *(double scale) {V4 result;  for(int i = 0; i < 4; i++) result.X[i] = X[i] * scale;   return result;}
   V4 operator /(double scale) {V4 result;  for(int i = 0; i < 4; i++) result.X[i] = X[i] / scale;   return result;}
   V4 &operator =(V4 &other) {for(int i = 0; i < 4; i++) X[i] = other.X[i];   return *this;}
   double &operator [](int index) {if(index >= 0 && index < 4)  return X[index];   return X[0];}
};

struct M4
{
public:
   double X[4][4];
   M4() {for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) X[i][j] = 0;}
   M4 operator +(M4 other) {M4 result;   for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) result.X[i][j] = X[i][j] + other.X[i][j];   return result;}
   M4 operator -(M4 other) {M4 result;   for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) result.X[i][j] = X[i][j] - other.X[i][j];   return result;}
   M4 operator *(double scale) {M4 result;   for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) result.X[i][j] = X[i][j] * scale;   return result;}
   M4 operator /(double scale) {M4 result;   for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) result.X[i][j] = X[i][j] / scale;   return result;}
   M4 operator *(M4 other) {M4 result;   for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) for(int k = 0; k < 4; k++) result.X[i][j] += X[i][k] * other.X[k][j];   return result;}
   V4 operator *(V4 other) {V4 result;   for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) result.X[i] += X[i][j] * other.X[j];   return result;}
   double *operator [](int index) {if(index >= 0 && index < 4)  return X[index];   return X[0];}
};

int main()
{
   SetStyle();

   double L = 1;
   double D = 1;
   double H = 1;
   double l = 0.55;
   double d = 0.5;
   double h = 0.65;

   vector<pair<V4, V4> > OuterEdges, InnerEdges;

   OuterEdges.push_back(pair<V4, V4>(V4(0, 0, 0, 1), V4(L, 0, 0, 1)));
   OuterEdges.push_back(pair<V4, V4>(V4(0, H, 0, 1), V4(L, H, 0, 1)));
   OuterEdges.push_back(pair<V4, V4>(V4(0, 0, D, 1), V4(L, 0, D, 1)));
   OuterEdges.push_back(pair<V4, V4>(V4(0, H, D, 1), V4(L, H, D, 1)));
   OuterEdges.push_back(pair<V4, V4>(V4(0, 0, 0, 1), V4(0, H, 0, 1)));
   OuterEdges.push_back(pair<V4, V4>(V4(L, 0, 0, 1), V4(L, H, 0, 1)));
   OuterEdges.push_back(pair<V4, V4>(V4(0, 0, D, 1), V4(0, H, D, 1)));
   OuterEdges.push_back(pair<V4, V4>(V4(L, 0, D, 1), V4(L, H, D, 1)));
   OuterEdges.push_back(pair<V4, V4>(V4(0, 0, 0, 1), V4(0, 0, D, 1)));
   OuterEdges.push_back(pair<V4, V4>(V4(L, 0, 0, 1), V4(L, 0, D, 1)));
   OuterEdges.push_back(pair<V4, V4>(V4(0, H, 0, 1), V4(0, H, D, 1)));
   OuterEdges.push_back(pair<V4, V4>(V4(L, H, 0, 1), V4(L, H, D, 1)));
   
   InnerEdges.push_back(pair<V4, V4>(V4(L - l, H - h, D - d, 1), V4(L - 0, H - h, D - d, 1)));
   InnerEdges.push_back(pair<V4, V4>(V4(L - l, H - 0, D - d, 1), V4(L - 0, H - 0, D - d, 1)));
   InnerEdges.push_back(pair<V4, V4>(V4(L - l, H - h, D - 0, 1), V4(L - 0, H - h, D - 0, 1)));
   InnerEdges.push_back(pair<V4, V4>(V4(L - l, H - 0, D - 0, 1), V4(L - 0, H - 0, D - 0, 1)));
   InnerEdges.push_back(pair<V4, V4>(V4(L - l, H - h, D - d, 1), V4(L - l, H - h, D - 0, 1)));
   InnerEdges.push_back(pair<V4, V4>(V4(L - 0, H - h, D - d, 1), V4(L - 0, H - h, D - 0, 1)));
   InnerEdges.push_back(pair<V4, V4>(V4(L - l, H - 0, D - d, 1), V4(L - l, H - 0, D - 0, 1)));
   InnerEdges.push_back(pair<V4, V4>(V4(L - 0, H - 0, D - d, 1), V4(L - 0, H - 0, D - 0, 1)));
   InnerEdges.push_back(pair<V4, V4>(V4(L - l, H - h, D - d, 1), V4(L - l, H - 0, D - d, 1)));
   InnerEdges.push_back(pair<V4, V4>(V4(L - l, H - h, D - 0, 1), V4(L - l, H - 0, D - 0, 1)));
   InnerEdges.push_back(pair<V4, V4>(V4(L - 0, H - h, D - d, 1), V4(L - 0, H - 0, D - d, 1)));
   InnerEdges.push_back(pair<V4, V4>(V4(L - 0, H - h, D - 0, 1), V4(L - 0, H - 0, D - 0, 1)));

   vector<V4> Dots;

   Dots.push_back(V4(0, 0, 0, 1));
   Dots.push_back(V4(L - l, H - h, D - d, 1));

   double wd = 1;
   double wl = 1.5;
   double wh = 1.5;

   double wx = 0;
   double wy = 0;
   double wz = 1.6;

   double theta = PI / 6;
   double phi = PI / 36;

   TCanvas C("C", "C", 1024, 1024);
   C.Range(-wl / 2, -wh / 2, wl / 2, wh / 2);

   TLine Line;
   Line.SetLineWidth(3);
   for(int i = 0; i < (int)OuterEdges.size(); i++)
   {
      V4 A = transform(OuterEdges[i].first, L, H, D, wx, wy, wz, theta, phi, wd);
      V4 B = transform(OuterEdges[i].second, L, H, D, wx, wy, wz, theta, phi, wd);
      Line.DrawLine(A[0], A[1], B[0], B[1]);
   }
   Line.SetLineWidth(1);
   for(int i = 0; i < (int)InnerEdges.size(); i++)
   {
      V4 A = transform(InnerEdges[i].first, L, H, D, wx, wy, wz, theta, phi, wd);
      V4 B = transform(InnerEdges[i].second, L, H, D, wx, wy, wz, theta, phi, wd);
      Line.DrawLine(A[0], A[1], B[0], B[1]);
   }

   TGraph Graph;
   for(int i = 0; i < (int)Dots.size(); i++)
   {
      V4 A = transform(Dots[i], L, H, D, wx, wy, wz, theta, phi, wd);
      Graph.SetPoint(Graph.GetN(), A[0], A[1]);
   }
   Graph.SetMarkerStyle(20);
   Graph.SetMarkerSize(2);
   Graph.Draw("p");

   TLatex Text;
   Text.SetTextSize(0.04);
   Text.SetTextAlign(22);
   
   double delta = 0.08;
   V4 TextA = transform(V4(L - l, H - h - delta, D - d, 1), L, H, D, wx, wy, wz, theta, phi, wd);
   Text.DrawLatex(TextA[0], TextA[1], "P");
   
   V4 TextB = transform(V4(-delta, -delta, 0, 1), L, H, D, wx, wy, wz, theta, phi, wd);
   Text.DrawLatex(TextB[0], TextB[1], "V");

   C.SaveAs("MultiDimensionalOverview-Template-Interpolation.png");
   C.SaveAs("MultiDimensionalOverview-Template-Interpolation.C");
   C.SaveAs("MultiDimensionalOverview-Template-Interpolation.eps");
   C.SaveAs("MultiDimensionalOverview-Template-Interpolation.pdf");

   return 0;
}

V4 transform(V4 X, double L, double H, double D, double wx, double wy, double wz, double theta, double phi, double wd)
{
   double F = 1;

   M4 WorldShiftA;
   WorldShiftA[0][0] = 1;   WorldShiftA[0][1] = 0;   WorldShiftA[0][2] = 0;   WorldShiftA[0][3] = -L / 2;
   WorldShiftA[1][0] = 0;   WorldShiftA[1][1] = 1;   WorldShiftA[1][2] = 0;   WorldShiftA[1][3] = -H / 2;
   WorldShiftA[2][0] = 0;   WorldShiftA[2][1] = 0;   WorldShiftA[2][2] = 1;   WorldShiftA[2][3] = -D / 2;
   WorldShiftA[3][0] = 0;   WorldShiftA[3][1] = 0;   WorldShiftA[3][2] = 0;   WorldShiftA[3][3] = 1;

   M4 WorldRotateY;
   WorldRotateY[0][0] = cos(theta);    WorldRotateY[0][1] = 0;   WorldRotateY[0][2] = sin(theta);   WorldRotateY[0][3] = 0;
   WorldRotateY[1][0] = 0;             WorldRotateY[1][1] = 1;   WorldRotateY[1][2] = 0;            WorldRotateY[1][3] = 0;
   WorldRotateY[2][0] = -sin(theta);   WorldRotateY[2][1] = 0;   WorldRotateY[2][2] = cos(theta);   WorldRotateY[2][3] = 0;
   WorldRotateY[3][0] = 0;             WorldRotateY[3][1] = 0;   WorldRotateY[3][2] = 0;            WorldRotateY[3][3] = 1;

   M4 WorldRotateX;
   WorldRotateX[0][0] = cos(phi);    WorldRotateX[0][1] = sin(phi);   WorldRotateX[0][2] = 0;   WorldRotateX[0][3] = 0;
   WorldRotateX[1][0] = -sin(phi);   WorldRotateX[1][1] = cos(phi);   WorldRotateX[1][2] = 0;   WorldRotateX[1][3] = 0;
   WorldRotateX[2][0] = 0;           WorldRotateX[2][1] = 0;          WorldRotateX[2][2] = 1;   WorldRotateX[2][3] = 0;
   WorldRotateX[3][0] = 0;           WorldRotateX[3][1] = 0;          WorldRotateX[3][2] = 0;   WorldRotateX[3][3] = 1;

   M4 WorldShiftB;
   WorldShiftB[0][0] = 1;   WorldShiftB[0][1] = 0;   WorldShiftB[0][2] = 0;   WorldShiftB[0][3] = wx;
   WorldShiftB[1][0] = 0;   WorldShiftB[1][1] = 1;   WorldShiftB[1][2] = 0;   WorldShiftB[1][3] = wy;
   WorldShiftB[2][0] = 0;   WorldShiftB[2][1] = 0;   WorldShiftB[2][2] = 1;   WorldShiftB[2][3] = wz;
   WorldShiftB[3][0] = 0;   WorldShiftB[3][1] = 0;   WorldShiftB[3][2] = 0;   WorldShiftB[3][3] = 1;

   M4 World = WorldShiftB * WorldRotateY * WorldRotateX * WorldShiftA;

   M4 Projection;
   Projection[0][0] = 1;   Projection[0][1] = 0;   Projection[0][2] = 0;   Projection[0][3] = 0;
   Projection[1][0] = 0;   Projection[1][1] = 1;   Projection[1][2] = 0;   Projection[1][3] = 0;
   Projection[2][0] = 0;   Projection[2][1] = 0;   Projection[2][2] = 1;   Projection[2][3] = 0;
   Projection[3][0] = 0;   Projection[3][1] = 0;   Projection[3][2] = 0;   Projection[3][3] = 1;

   F = wd / (World * X)[2];
   Projection[0][0] = Projection[1][1] = Projection[2][2] = F;

   return Projection * World * X;
}







