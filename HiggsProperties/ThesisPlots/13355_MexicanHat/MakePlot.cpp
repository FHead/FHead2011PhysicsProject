#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#include "TCanvas.h"
#include "TLine.h"
#include "TGraph.h"
#include "TLatex.h"
#include "TArrow.h"
#include "TEllipse.h"

#include "SetStyle.h"

#define PI 3.14159265358979323846264338327950288479716939937510

struct V4;
struct M4;
struct WorldSpecification;
int main();
V4 transform(V4 X, const WorldSpecification &Screen);
void MakePlot(const vector<pair<V4, V4> > &Lines, const vector<pair<V4, V4> > &Arrows,
   const vector<pair<V4, V4> > &ThinLines, const vector<V4> &Dots,
   const vector<pair<V4, string> > &Texts, const WorldSpecification &Screen, const string OutputBase,
   bool Plot3Hack);

struct V4
{
public:
   double X[4];
   V4() {X[0] = X[1] = X[2] = X[3] = 0;}
   V4(double x0, double x1, double x2, double x3) {X[0] = x0; X[1] = x1; X[2] = x2; X[3] = x3;}
   V4(double x0, double x1, double x2) {X[0] = x0; X[1] = x1; X[2] = x2; X[3] = 1;}
   V4 operator +(V4 other) {V4 result;  for(int i = 0; i < 4; i++) result.X[i] = X[i] + other.X[i];   return result;}
   V4 operator -(V4 other) {V4 result;  for(int i = 0; i < 4; i++) result.X[i] = X[i] - other.X[i];   return result;}
   V4 operator *(double scale) {V4 result;  for(int i = 0; i < 4; i++) result.X[i] = X[i] * scale;   return result;}
   V4 operator /(double scale) {V4 result;  for(int i = 0; i < 4; i++) result.X[i] = X[i] / scale;   return result;}
   V4 &operator =(V4 other) {for(int i = 0; i < 4; i++) X[i] = other.X[i];   return *this;}
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

struct WorldSpecification
{
   double L;   // Shift world-x by L/2 before doing anything
   double H;   // Shift world-y by H/2 before doing anything
   double D;   // Shift world-z by D/2 before doing anything

   double wd;   // Distance between camera at (0, 0, 0) to the screen
   double wl;   // screen width
   double wh;   // screen height

   double wx;   // world x location
   double wy;   // world y location
   double wz;   // world z location

   double theta;   // rotate world along y axis
   double phi;     // rotate world along x axis
};

int main()
{
   SetStyle();

   WorldSpecification Screen;

   Screen.wd = 1;
   Screen.wl = 1.5;
   Screen.wh = 1.5;

   Screen.wx = 0;
   Screen.wy = -0.5;
   Screen.wz = 4.5;

   Screen.L = 0;
   Screen.D = 0;
   Screen.H = 2;

   Screen.theta = PI / 6;
   Screen.phi = PI / 6;

   // Plot1 specifications
   WorldSpecification Screen1 = Screen;
   vector<pair<V4, V4> > Lines;
   vector<pair<V4, V4> > Arrows;
   vector<pair<V4, V4> > ThinLines;
   vector<V4> Dots;
   vector<pair<V4, string> > Texts;
   
   double A = 1, B = -2, C = 1;
   double R = 1.6;
   double H = A * R * R * R * R + B * R * R + C;
   double r = sqrt(-B / 2 / A);

   int SegmentCount = 100;

   double PhiMin = -PI * 0.2, PhiMax = PI * 1.4;

   for(int i = 0; i < SegmentCount; i++)
   {
      double PhiLeft = (PhiMax - PhiMin) / SegmentCount * i + PhiMin;
      double PhiRight = (PhiMax - PhiMin) / SegmentCount * (i + 1) + PhiMin;

      Lines.push_back(pair<V4, V4>(V4(r * cos(PhiLeft), 0, r * sin(PhiLeft)), V4(r * cos(PhiRight), 0, r * sin(PhiRight))));
      Lines.push_back(pair<V4, V4>(V4(R * cos(PhiLeft), H, R * sin(PhiLeft)), V4(R * cos(PhiRight), H, R * sin(PhiRight))));
   }

   int RadialCount = 15;
   for(int i = 0; i < SegmentCount; i++)
   {
      for(int j = 0; j <= RadialCount; j++)
      {
         double Phi = (PhiMax - PhiMin) / RadialCount * j + PhiMin;

         double r1 = R / SegmentCount * i;
         double r2 = R / SegmentCount * (i + 1);

         double h1 = A * r1 * r1 * r1 * r1 + B * r1 * r1 + C;
         double h2 = A * r2 * r2 * r2 * r2 + B * r2 * r2 + C;

         Lines.push_back(pair<V4, V4>(V4(r1 * cos(Phi), h1, r1 * sin(Phi)), V4(r2 * cos(Phi), h2, r2 * sin(Phi))));
      }
   }

   int HorizontalCount = 16;
   for(int i = 0; i < SegmentCount; i++)
   {
      double PhiLeft = (PhiMax - PhiMin) / SegmentCount * i + PhiMin;
      double PhiRight = (PhiMax - PhiMin) / SegmentCount * (i + 1) + PhiMin;

      for(int j = 0; j < HorizontalCount; j++)
      {
         double r0 = R / HorizontalCount * j;
         double h0 = A * r0 * r0 * r0 * r0 + B * r0 * r0 + C;

         ThinLines.push_back(pair<V4, V4>(V4(r0 * cos(PhiLeft), h0, r0 * sin(PhiLeft)), V4(r0 * cos(PhiRight), h0, r0 * sin(PhiRight))));
      }
   }

   double ArrowX = 2, ArrowY = 0, ArrowZ = 1, ArrowLength = 0.5, ArrowPhi = -PI / 3;

   Arrows.push_back(pair<V4, V4>(V4(ArrowX, ArrowY, ArrowZ), V4(ArrowX + ArrowLength * cos(ArrowPhi), ArrowY, ArrowZ + ArrowLength * sin(ArrowPhi))));
   Arrows.push_back(pair<V4, V4>(V4(ArrowX, ArrowY, ArrowZ), V4(ArrowX, ArrowY + ArrowLength * 2, ArrowZ)));
   Arrows.push_back(pair<V4, V4>(V4(ArrowX, ArrowY, ArrowZ), V4(ArrowX + ArrowLength * -sin(ArrowPhi), ArrowY, ArrowZ + ArrowLength * cos(ArrowPhi))));

   Texts.push_back(pair<V4, string>(V4(ArrowX, ArrowY + ArrowLength * 2.5, ArrowZ), "V(#phi)"));
   Texts.push_back(pair<V4, string>(V4(ArrowX + ArrowLength * cos(ArrowPhi) * 1.5, ArrowY, ArrowZ + ArrowLength * sin(ArrowPhi) * 1.5), "Re(#phi)"));
   Texts.push_back(pair<V4, string>(V4(ArrowX + ArrowLength * -sin(ArrowPhi) * 1.5, ArrowY, ArrowZ + ArrowLength * cos(ArrowPhi) * 1.5), "Im(#phi)"));

   MakePlot(Lines, Arrows, ThinLines, Dots, Texts, Screen1, "SMAndHiggs-ScalarField-MexicanHat", false);
   
   return 0;
}

V4 transform(V4 X, const WorldSpecification &Screen)
{
   double wd = Screen.wd;
   double wl = Screen.wl;
   double wh = Screen.wh;

   double wx = Screen.wx;
   double wy = Screen.wy;
   double wz = Screen.wz;

   double L = Screen.L;
   double D = Screen.D;
   double H = Screen.H;

   double theta = Screen.theta;
   double phi = Screen.phi;

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
   WorldRotateX[0][0] = 1;   WorldRotateX[0][1] = 0;           WorldRotateX[0][2] = 0;          WorldRotateX[0][3] = 0;
   WorldRotateX[1][0] = 0;   WorldRotateX[1][1] = cos(phi);    WorldRotateX[1][2] = sin(phi);   WorldRotateX[1][3] = 0;
   WorldRotateX[2][0] = 0;   WorldRotateX[2][1] = -sin(phi);   WorldRotateX[2][2] = cos(phi);   WorldRotateX[2][3] = 0;
   WorldRotateX[3][0] = 0;   WorldRotateX[3][1] = 0;           WorldRotateX[3][2] = 0;          WorldRotateX[3][3] = 1;

   M4 WorldShiftB;
   WorldShiftB[0][0] = 1;   WorldShiftB[0][1] = 0;   WorldShiftB[0][2] = 0;   WorldShiftB[0][3] = wx;
   WorldShiftB[1][0] = 0;   WorldShiftB[1][1] = 1;   WorldShiftB[1][2] = 0;   WorldShiftB[1][3] = wy;
   WorldShiftB[2][0] = 0;   WorldShiftB[2][1] = 0;   WorldShiftB[2][2] = 1;   WorldShiftB[2][3] = wz;
   WorldShiftB[3][0] = 0;   WorldShiftB[3][1] = 0;   WorldShiftB[3][2] = 0;   WorldShiftB[3][3] = 1;

   M4 World = WorldShiftB * WorldRotateX * WorldRotateY * WorldShiftA;

   M4 Projection;
   Projection[0][0] = 1;   Projection[0][1] = 0;   Projection[0][2] = 0;   Projection[0][3] = 0;
   Projection[1][0] = 0;   Projection[1][1] = 1;   Projection[1][2] = 0;   Projection[1][3] = 0;
   Projection[2][0] = 0;   Projection[2][1] = 0;   Projection[2][2] = 1;   Projection[2][3] = 0;
   Projection[3][0] = 0;   Projection[3][1] = 0;   Projection[3][2] = 0;   Projection[3][3] = 1;

   F = wd / (World * X)[2];
   Projection[0][0] = Projection[1][1] = Projection[2][2] = F;

   return Projection * World * X;
}

void MakePlot(const vector<pair<V4, V4> > &Lines, const vector<pair<V4, V4> > &Arrows,
   const vector<pair<V4, V4> > &ThinLines, const vector<V4> &Dots,
   const vector<pair<V4, string> > &Texts, const WorldSpecification &Screen, const string OutputBase,
   bool Plot3Hack)
{   
   TCanvas C("C", "C", 1024, 1024 * 0.8);
   C.Range(-Screen.wl / 2, -Screen.wh * 0.8 / 2, Screen.wl / 2, Screen.wh * 0.8 / 2);

   TLine Line;
   Line.SetLineWidth(2);
   for(int i = 0; i < (int)Lines.size(); i++)
   {
      V4 A = transform(Lines[i].first, Screen);
      V4 B = transform(Lines[i].second, Screen);
      Line.DrawLine(A[0], A[1], B[0], B[1]);
   }

   TArrow Arrow;
   Arrow.SetLineWidth(3);
   Arrow.SetAngle(15);
   Arrow.SetArrowSize(0.025);
   Arrow.SetFillColor(kBlack);
   for(int i = 0; i < (int)Arrows.size(); i++)
   {
      V4 A = transform(Arrows[i].first, Screen);
      V4 B = transform(Arrows[i].second, Screen);
      B = (B - A) * 0.95 + A;
      Arrow.DrawArrow(A[0], A[1], B[0], B[1]);
   }

   Line.SetLineWidth(1);
   for(int i = 0; i < (int)ThinLines.size(); i++)
   {
      V4 A = transform(ThinLines[i].first, Screen);
      V4 B = transform(ThinLines[i].second, Screen);
      Line.DrawLine(A[0], A[1], B[0], B[1]);
   }

   TGraph Graph;
   for(int i = 0; i < (int)Dots.size(); i++)
   {
      V4 A = transform(Dots[i], Screen);
      Graph.SetPoint(Graph.GetN(), A[0], A[1]);
   }
   Graph.SetMarkerStyle(20);
   Graph.SetMarkerSize(2);
   if(Dots.size() > 0)
      Graph.Draw("p");

   TLatex Text;
   Text.SetTextFont(42);
   Text.SetTextSize(0.05);
   Text.SetTextAlign(22);

   for(int i = 0; i < (int)Texts.size(); i++)
   {
      V4 TextA = transform(Texts[i].first, Screen);
      Text.DrawLatex(TextA[0], TextA[1], Texts[i].second.c_str());
   }

   TEllipse Ellipse;
   if(Plot3Hack == true)
   {
      Ellipse.SetLineWidth(2);
      Ellipse.SetFillStyle(0);
      Ellipse.SetNoEdges();
      Ellipse.DrawEllipse(Screen.wl * 0.05, Screen.wh * 0.28, Screen.wl / 30, Screen.wh / 150, 100, 390, 0);
   }

   C.SaveAs(Form("%s.png", OutputBase.c_str()));
   C.SaveAs(Form("%s.C", OutputBase.c_str()));
   C.SaveAs(Form("%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s.pdf", OutputBase.c_str()));
}






