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
   Screen.wy = 0;
   Screen.wz = 2;

   Screen.L = 0;
   Screen.D = 0;
   Screen.H = 0;

   Screen.theta = PI / 6;
   Screen.phi = PI / 36;

   // Plot1 specifications
   WorldSpecification Screen1 = Screen;
   vector<pair<V4, V4> > Plot1Lines;
   vector<pair<V4, V4> > Plot1Arrows;
   vector<pair<V4, V4> > Plot1ThinLines;
   vector<V4> Plot1Dots;
   vector<pair<V4, string> > Plot1Texts;
   
   double L_1 = 1;
   double Phi1_1 = PI / 15;
   double Phi2_1 = PI / 3;
   double FZ_1 = 0.4;
   double FL_1 = 0.6;

   Plot1Lines.push_back(pair<V4, V4>(V4(0, L_1 * sin(Phi1_1), L_1 * cos(Phi1_1)), V4(0, -L_1 * sin(Phi1_1), -L_1 * cos(Phi1_1))));
   Plot1Lines.push_back(pair<V4, V4>(V4(L_1, L_1 * sin(Phi1_1), L_1 * cos(Phi1_1)), V4(L_1, -L_1 * sin(Phi1_1), -L_1 * cos(Phi1_1))));
   Plot1Lines.push_back(pair<V4, V4>(V4(0, L_1 * sin(Phi1_1), L_1 * cos(Phi1_1)), V4(L_1, L_1 * sin(Phi1_1), L_1 * cos(Phi1_1))));
   Plot1Lines.push_back(pair<V4, V4>(V4(0, -L_1 * sin(Phi1_1), -L_1 * cos(Phi1_1)), V4(L_1, -L_1 * sin(Phi1_1), -L_1 * cos(Phi1_1))));
   Plot1Lines.push_back(pair<V4, V4>(V4(0, L_1 * sin(Phi2_1), L_1 * cos(Phi2_1)), V4(0, -L_1 * sin(Phi2_1), -L_1 * cos(Phi2_1))));
   Plot1Lines.push_back(pair<V4, V4>(V4(-L_1, L_1 * sin(Phi2_1), L_1 * cos(Phi2_1)), V4(-L_1, -L_1 * sin(Phi2_1), -L_1 * cos(Phi2_1))));
   Plot1Lines.push_back(pair<V4, V4>(V4(0, L_1 * sin(Phi2_1), L_1 * cos(Phi2_1)), V4(-L_1, L_1 * sin(Phi2_1), L_1 * cos(Phi2_1))));
   Plot1Lines.push_back(pair<V4, V4>(V4(0, -L_1 * sin(Phi2_1), -L_1 * cos(Phi2_1)), V4(-L_1, -L_1 * sin(Phi2_1), -L_1 * cos(Phi2_1))));
   Plot1Lines.push_back(pair<V4, V4>(V4(L_1, 0, 0), V4(-L_1, 0, 0)));

   V4 Center_1(0, 0, 0);
   V4 CornerL11_1(L_1, L_1 * sin(Phi1_1), L_1 * cos(Phi1_1));
   V4 CornerL12_1(L_1, -L_1 * sin(Phi1_1), -L_1 * cos(Phi1_1));
   V4 CornerL21_1(-L_1, L_1 * sin(Phi2_1), L_1 * cos(Phi2_1));
   V4 CornerL22_1(-L_1, -L_1 * sin(Phi2_1), -L_1 * cos(Phi2_1));
   V4 Z1End_1(FZ_1 * L_1, 0, 0);
   V4 Z2End_1(-FZ_1 * L_1, 0, 0);
   V4 L11End_1 = (CornerL11_1 - Z1End_1) * FL_1 + Z1End_1;   L11End_1[3] = 1;
   V4 L12End_1 = (CornerL12_1 - Z1End_1) * FL_1 + Z1End_1;   L12End_1[3] = 1;
   V4 L21End_1 = (CornerL21_1 - Z2End_1) * FL_1 + Z2End_1;   L21End_1[3] = 1;
   V4 L22End_1 = (CornerL22_1 - Z2End_1) * FL_1 + Z2End_1;   L22End_1[3] = 1;

   Plot1Arrows.push_back(pair<V4, V4>(Center_1, Z1End_1));
   Plot1Arrows.push_back(pair<V4, V4>(Center_1, Z2End_1));
   Plot1Arrows.push_back(pair<V4, V4>(Z1End_1, L11End_1));
   Plot1Arrows.push_back(pair<V4, V4>(Z1End_1, L12End_1));
   Plot1Arrows.push_back(pair<V4, V4>(Z2End_1, L21End_1));
   Plot1Arrows.push_back(pair<V4, V4>(Z2End_1, L22End_1));

   Plot1ThinLines.push_back(pair<V4, V4>(V4(0, L_1 * sin(Phi1_1) * 0.2, L_1 * cos(Phi1_1) * 0.2), V4(0, L_1 * sin(Phi2_1) * 0.2, L_1 * cos(Phi2_1) * 0.2)));

   double Phi_1 = (Phi1_1 + Phi2_1) / 2;
   Plot1Texts.push_back(pair<V4, string>(V4(0, L_1 * sin(Phi_1) * 0.4, L_1 * cos(Phi_1) * 0.4), "#phi"));

   Plot1Texts.push_back(pair<V4, string>(V4(FZ_1 * L_1 * 0.5, -L_1 * 0.1, 0), "m_{1}"));
   Plot1Texts.push_back(pair<V4, string>(V4(-FZ_1 * L_1 * 0.5, L_1 * 0.1, 0), "m_{2}"));
   
   // Plot2 specifications
   WorldSpecification Screen2 = Screen;
   vector<pair<V4, V4> > Plot2Lines;
   vector<pair<V4, V4> > Plot2Arrows;
   vector<pair<V4, V4> > Plot2ThinLines;
   vector<V4> Plot2Dots;
   vector<pair<V4, string> > Plot2Texts;

   double L_2 = 1.0;
   double Theta_2 = PI / 3;

   Plot2Lines.push_back(pair<V4, V4>(V4(-L_2, 0, 0), V4(L_2, 0, 0)));
   Plot2Arrows.push_back(pair<V4, V4>(V4(-L_2, 0, 0), V4(0, 0, 0)));
   Plot2Arrows.push_back(pair<V4, V4>(V4(0, 0, 0), V4(L_2 * cos(Theta_2), L_2 * sin(Theta_2), 0)));
   Plot2Arrows.push_back(pair<V4, V4>(V4(0, 0, 0), V4(-L_2 * cos(Theta_2), -L_2 * sin(Theta_2), 0)));
   
   Plot2Texts.push_back(pair<V4, string>(V4(-L_2 / 2, L_2 / 8, 0), "V (V')"));
   Plot2Texts.push_back(pair<V4, string>(V4(L_2 * cos(Theta_2) * 0.7 - L_2 / 8, L_2 * sin(Theta_2) * 0.7, 0), "l^{-}"));
   Plot2Texts.push_back(pair<V4, string>(V4(-L_2 * cos(Theta_2) * 0.7 + L_2 / 8, -L_2 * sin(Theta_2) * 0.7, 0), "l^{+}"));
   
   Plot2ThinLines.push_back(pair<V4, V4>(V4(L_2 * 0.15, 0, 0), V4(L_2 * cos(Theta_2) * 0.15, L_2 * sin(Theta_2) * 0.15, 0)));

   Plot2Texts.push_back(pair<V4, string>(V4(L_2 * 0.3 + L_2 * cos(Theta_2) * 0.15, L_2 * sin(Theta_2) * 0.15, 0), "#theta_{1} (#theta_{2})"));
   
   // Plot3 specifications
   WorldSpecification Screen3 = Screen;
   vector<pair<V4, V4> > Plot3Lines;
   vector<pair<V4, V4> > Plot3Arrows;
   vector<pair<V4, V4> > Plot3ThinLines;
   vector<V4> Plot3Dots;
   vector<pair<V4, string> > Plot3Texts;

   double L_3 = 0.8;
   double Phi0_3 = PI / 15;
   double Phi1_3 = PI / 3;
   double Phi2_3 = -PI / 3;
   double FPP_3 = 1.4;
   double FP_3 = 0.8;
   double FZ_3 = 0.4;
   double FL_3 = 0.6;

   Plot3Lines.push_back(pair<V4, V4>(V4(-L_3 / 2, L_3 * cos(Phi0_3), L_3 * sin(Phi0_3)), V4(-L_3 / 2, -L_3 * cos(Phi0_3), -L_3 * sin(Phi0_3))));
   Plot3Lines.push_back(pair<V4, V4>(V4(L_3 / 2, L_3 * cos(Phi0_3), L_3 * sin(Phi0_3)), V4(L_3 / 2, -L_3 * cos(Phi0_3), -L_3 * sin(Phi0_3))));
   Plot3Lines.push_back(pair<V4, V4>(V4(-L_3 / 2, L_3 * cos(Phi0_3), L_3 * sin(Phi0_3)), V4(L_3 / 2, L_3 * cos(Phi0_3), L_3 * sin(Phi0_3))));
   Plot3Lines.push_back(pair<V4, V4>(V4(-L_3 / 2, -L_3 * cos(Phi0_3), -L_3 * sin(Phi0_3)), V4(L_3 / 2, -L_3 * cos(Phi0_3), -L_3 * sin(Phi0_3))));
   
   Plot3Lines.push_back(pair<V4, V4>(V4(0, FPP_3 * L_3 * cos(Phi0_3), FPP_3 * L_3 * sin(Phi0_3)), V4(0, -FPP_3 * L_3 * cos(Phi0_3), -FPP_3 * L_3 * sin(Phi0_3))));
   
   Plot3Lines.push_back(pair<V4, V4>(V4(-L_3 / 2 * 3, L_3 * cos(Phi1_3), L_3 * sin(Phi1_3)), V4(-L_3 / 2 * 3, -L_3 * cos(Phi1_3), -L_3 * sin(Phi1_3))));
   Plot3Lines.push_back(pair<V4, V4>(V4(-L_3 / 2, L_3 * cos(Phi1_3), L_3 * sin(Phi1_3)), V4(-L_3 / 2, -L_3 * cos(Phi1_3), -L_3 * sin(Phi1_3))));
   Plot3Lines.push_back(pair<V4, V4>(V4(-L_3 / 2 * 3, L_3 * cos(Phi1_3), L_3 * sin(Phi1_3)), V4(-L_3 / 2, L_3 * cos(Phi1_3), L_3 * sin(Phi1_3))));
   Plot3Lines.push_back(pair<V4, V4>(V4(-L_3 / 2 * 3, -L_3 * cos(Phi1_3), -L_3 * sin(Phi1_3)), V4(-L_3 / 2, -L_3 * cos(Phi1_3), -L_3 * sin(Phi1_3))));
   
   Plot3Lines.push_back(pair<V4, V4>(V4(-L_3 / 2 * 3, 0, 0), V4(L_3 / 2 * 3, 0, 0)));

   V4 Center_3(0, 0, 0);
   V4 CornerL11_3(-L_3 * 1.5, L_3 * cos(Phi1_3), L_3 * sin(Phi1_3));
   V4 CornerL12_3(-L_3 * 1.5, -L_3 * cos(Phi1_3), -L_3 * sin(Phi1_3));
   V4 CornerL21_3(L_3 * 1.5, L_3 * cos(Phi2_3), L_3 * sin(Phi2_3));
   V4 CornerL22_3(L_3 * 1.5, -L_3 * cos(Phi2_3), -L_3 * sin(Phi2_3));
   V4 Z1End_3(-L_3 / 2 - L_3 * FZ_3, 0, 0);
   V4 Z2End_3(+L_3 / 2 + L_3 * FZ_3, 0, 0);
   V4 P1Start_3(0, FP_3 * L_3 * cos(Phi0_3), FP_3 * L_3 * sin(Phi0_3));
   V4 P2Start_3(0, -FP_3 * L_3 * cos(Phi0_3), -FP_3 * L_3 * sin(Phi0_3));
   V4 L11End_3 = (CornerL11_3 - Z1End_3) * FL_3 + Z1End_3;   L11End_3[3] = 1;
   V4 L12End_3 = (CornerL12_3 - Z1End_3) * FL_3 + Z1End_3;   L12End_3[3] = 1;
   V4 L21End_3 = (CornerL21_3 - Z2End_3) * FL_3 + Z2End_3;   L21End_3[3] = 1;
   V4 L22End_3 = (CornerL22_3 - Z2End_3) * FL_3 + Z2End_3;   L22End_3[3] = 1;

   Plot3Arrows.push_back(pair<V4, V4>(Center_3, Z1End_3));
   Plot3Arrows.push_back(pair<V4, V4>(Center_3, Z2End_3));
   Plot3Arrows.push_back(pair<V4, V4>(P1Start_3, Center_3));
   Plot3Arrows.push_back(pair<V4, V4>(P2Start_3, Center_3));
   Plot3Arrows.push_back(pair<V4, V4>(Z1End_3, L11End_3));
   Plot3Arrows.push_back(pair<V4, V4>(Z1End_3, L12End_3));
   Plot3Arrows.push_back(pair<V4, V4>(Z2End_3, L21End_3));
   Plot3Arrows.push_back(pair<V4, V4>(Z2End_3, L22End_3));

   V4 PhiOffsetLocation_3(-L_3 / 2, 1.35 * L_3 * cos(Phi0_3), 1.35 * L_3 * sin(Phi0_3));
   V4 P1Location_3(L_3 * 0.15, 0.6 * L_3 * cos(Phi0_3), 0.6 * L_3 * sin(Phi0_3));
   V4 P2Location_3(-L_3 * 0.15, -0.6 * L_3 * cos(Phi0_3), -0.6 * L_3 * sin(Phi0_3));
   V4 Theta0Location_3(L_3 * 0.175, -0.175 * L_3 * cos(Phi0_3), -0.175 * L_3 * sin(Phi0_3));
   V4 Phi0Location_3(-L_3 / 2, -0.5 * L_3 * cos(Phi0_3 / 2 + Phi1_3 / 2), -0.5 * L_3 * sin(Phi0_3 / 2 + Phi1_3 / 2));

   Plot3Texts.push_back(pair<V4, string>(PhiOffsetLocation_3, "#phi_{offset}"));
   Plot3Texts.push_back(pair<V4, string>(P1Location_3, "p"));
   Plot3Texts.push_back(pair<V4, string>(P2Location_3, "p"));
   Plot3Texts.push_back(pair<V4, string>(Theta0Location_3, "#Theta"));
   Plot3Texts.push_back(pair<V4, string>(Phi0Location_3, "#Phi_{1}"));
   
   Plot3ThinLines.push_back(pair<V4, V4>(V4(-L_3 / 2, -0.3 * L_3 * cos(Phi0_3), -0.3 * L_3 * sin(Phi0_3)), V4(-L_3 / 2, -0.3 * L_3 * cos(Phi1_3), -0.3 * L_3 * sin(Phi1_3))));
   Plot3ThinLines.push_back(pair<V4, V4>(V4(0, -0.15 * L_3 * cos(Phi0_3), -0.15 * L_3 * sin(Phi0_3)), V4(L_3 * 0.15, 0, 0)));
   
   // Plot4 specifications
   WorldSpecification Screen4 = Screen;
   vector<pair<V4, V4> > Plot4Lines;
   vector<pair<V4, V4> > Plot4Arrows;
   vector<pair<V4, V4> > Plot4ThinLines;
   vector<V4> Plot4Dots;
   vector<pair<V4, string> > Plot4Texts;

   double LH_4 = 1;
   double LZ_4 = 1;
   double LL_4 = 1;
   double Phi1_4 = PI / 6 / 3;
   double Phi2_4 = -PI / 6 / 3;
   double Phi11_4 = PI / 12 * 3 / 3;
   double Phi12_4 = PI / 12 * 1 / 3;
   double Phi21_4 = -PI / 12 * 1 / 3;
   double Phi22_4 = -PI / 12 * 3 / 3;

   V4 Center_4(0, 0, 0);
   V4 HStart_4(LH_4, 0, 0);
   V4 Z1End_4(-LZ_4 * cos(Phi1_4), LZ_4 * sin(Phi1_4), 0);
   V4 Z2End_4(-LZ_4 * cos(Phi2_4), LZ_4 * sin(Phi2_4), 0);
   V4 L11Offset_4(-LL_4 * cos(Phi11_4), LL_4 * sin(Phi11_4), 0);
   V4 L12Offset_4(-LL_4 * cos(Phi12_4), LL_4 * sin(Phi12_4), 0);
   V4 L21Offset_4(-LL_4 * cos(Phi21_4), LL_4 * sin(Phi21_4), 0);
   V4 L22Offset_4(-LL_4 * cos(Phi22_4), LL_4 * sin(Phi22_4), 0);
   V4 L11End_4 = Z1End_4 + L11Offset_4;   L11End_4[3] = 1;
   V4 L12End_4 = Z1End_4 + L12Offset_4;   L12End_4[3] = 1;
   V4 L21End_4 = Z2End_4 + L21Offset_4;   L21End_4[3] = 1;
   V4 L22End_4 = Z2End_4 + L22Offset_4;   L22End_4[3] = 1;

   Plot4Lines.push_back(pair<V4, V4>(V4(-3 * LH_4, 0, 0), V4(3 * LH_4, 0, 0)));

   Plot4Arrows.push_back(pair<V4, V4>(HStart_4, Center_4));
   Plot4Arrows.push_back(pair<V4, V4>(Center_4, Z1End_4));
   Plot4Arrows.push_back(pair<V4, V4>(Center_4, Z2End_4));
   Plot4Arrows.push_back(pair<V4, V4>(Z1End_4, L11End_4));
   Plot4Arrows.push_back(pair<V4, V4>(Z1End_4, L12End_4));
   Plot4Arrows.push_back(pair<V4, V4>(Z2End_4, L21End_4));
   Plot4Arrows.push_back(pair<V4, V4>(Z2End_4, L22End_4));

   V4 TextZ1_4 = Z1End_4 / 2 + V4(0, LH_4 / 10, 0);   TextZ1_4[3] = 1;
   V4 TextZ2_4 = Z2End_4 / 2 - V4(0, LH_4 / 10, 0);   TextZ2_4[3] = 1;

   Plot4Texts.push_back(pair<V4, string>(V4(LH_4 / 2, LH_4 / 10, 0), "h"));
   Plot4Texts.push_back(pair<V4, string>(V4(LH_4 / 2, -LH_4 / 10, 0), "#vec{p}_{T}, y_{4l}, m_{4l}"));
   Plot4Texts.push_back(pair<V4, string>(TextZ1_4, "V"));
   Plot4Texts.push_back(pair<V4, string>(TextZ2_4, "V'"));
   
   MakePlot(Plot1Lines, Plot1Arrows, Plot1ThinLines, Plot1Dots, Plot1Texts, Screen1, "PhysicsChallenge-Variables-Definition1", false);
   MakePlot(Plot2Lines, Plot2Arrows, Plot2ThinLines, Plot2Dots, Plot2Texts, Screen2, "PhysicsChallenge-Variables-Definition2", false);
   MakePlot(Plot3Lines, Plot3Arrows, Plot3ThinLines, Plot3Dots, Plot3Texts, Screen3, "PhysicsChallenge-Variables-Definition3", true);
   MakePlot(Plot4Lines, Plot4Arrows, Plot4ThinLines, Plot4Dots, Plot4Texts, Screen4, "PhysicsChallenge-Variables-Definition4", false);
   
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
   Arrow.SetLineWidth(4);
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






