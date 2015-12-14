#include <iostream>
#include <cmath>
using namespace std;

#include "TCanvas.h"
#include "TEllipse.h"
#include "TLine.h"
#include "TGraph.h"
#include "TArrow.h"

int main()
{
   TCanvas C("C", "C", 1024, 1024);
   C.Range(-1.6, -1.6, +1.6, +1.6);

   double F = 0.5;
   double R1 = sqrt(F);
   double R2 = sqrt((2 - F));

   double S = 0.3;

   TEllipse E(0.0, 0.0, R1, R2, 0, 360, +45);
   TLine L;
   TGraph G;
   TArrow A;

   A.SetLineWidth(5);
   A.SetAngle(30);
   A.SetArrowSize(0.05);
   A.SetFillColor(kBlue);
   A.SetLineColor(kBlue);

   G.SetPoint(0, 1, -1 + F);
   G.SetPoint(1, -1, 1 - F);
   G.SetPoint(2, -1 + F, 1);
   G.SetPoint(3, 1 - F, -1);
   G.SetMarkerStyle(20);

   E.SetLineWidth(3);
   E.Draw();
   G.Draw("p");
   L.DrawLine(1, -1 + F + S, 1, -1 + F - S);
   L.DrawLine(-1, 1 - F + S, -1, 1 - F - S);
   L.DrawLine(-1 + F + S, 1, -1 + F - S, 1);
   L.DrawLine(1 - F + S, -1, 1 - F - S, -1);

   L.SetLineColor(15);
   L.SetLineStyle(kDashed);
   L.DrawLine(1 - F, -1 - S, 1 - F, -1 + S);
   L.DrawLine(-1 + F, 1 - S, -1 + F, 1 + S);

   L.SetLineColor(kRed);
   L.SetLineWidth(3);
   L.SetLineStyle(1);
   L.DrawLine(1 - F / 2, -1.1, 1 - F / 2, +1.1);
   L.DrawLine(-1 + F / 2, -1.1, -1 + F / 2, +1.1);

   A.DrawArrow(-S, -1.1, S, -1.1);
   A.DrawArrow(-S, 1.1, S, 1.1);
   A.DrawArrow(1.1, -1 + F - S, 1.1, -1 + F + S);
   A.DrawArrow(-1.1, 1 - F - S, -1.1, 1 - F + S);

   C.SaveAs("MultiDimensionalDetails-Signal-C1C3EllipseSlicing.png");
   C.SaveAs("MultiDimensionalDetails-Signal-C1C3EllipseSlicing.C");
   C.SaveAs("MultiDimensionalDetails-Signal-C1C3EllipseSlicing.eps");
   C.SaveAs("MultiDimensionalDetails-Signal-C1C3EllipseSlicing.pdf");
}





