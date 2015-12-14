#include <cmath>
#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TLine.h"
#include "TArrow.h"
#include "TArc.h"
#include "TLatex.h"

#define PI 3.141592653589793238462643383279

int main()
{
   double W = 50;
   double L = 50;
   double F = 0.75;
   double A1 = 40 * PI / 180;
   double A2 = 85 * PI / 180;
   double D = 2;

   double WorldW = 3 * L;
   double WorldH = 1.5 * W;

   TCanvas C("C", "C", 1024, 512);
   C.Range(-WorldW / 2, -WorldH / 2, WorldW / 2, WorldH / 2);

   TLine Line;
   TArrow Arrow;
   TArc Arc;
   TLatex Latex;
   
   Line.SetLineColor(kBlack);
   Line.SetLineStyle(1);
   Line.SetLineWidth(1);
   Line.DrawLine(-W / 2 * cos(A2), -W / 2 * sin(A2), W / 2 * cos(A2), W / 2 * sin(A2));
   Line.DrawLine(-W / 2 * cos(A2) + L, -W / 2 * sin(A2), W / 2 * cos(A2) + L, W / 2 * sin(A2));
   Line.DrawLine(-W / 2 * cos(A2), -W / 2 * sin(A2), -W / 2 * cos(A2) + L, -W / 2 * sin(A2));
   Line.DrawLine(W / 2 * cos(A2), W / 2 * sin(A2), W / 2 * cos(A2) + L, W / 2 * sin(A2));
   Line.DrawLine(-W / 2 * cos(A1), -W / 2 * sin(A1), W / 2 * cos(A1), W / 2 * sin(A1));
   Line.DrawLine(-W / 2 * cos(A1) - L, -W / 2 * sin(A1), W / 2 * cos(A1) - L, W / 2 * sin(A1));
   Line.DrawLine(-W / 2 * cos(A1), -W / 2 * sin(A1), -W / 2 * cos(A1) - L, -W / 2 * sin(A1));
   Line.DrawLine(W / 2 * cos(A1), W / 2 * sin(A1), W / 2 * cos(A1) - L, W / 2 * sin(A1));

   Line.DrawLine(-L, 0, L, 0);
   
   double x = W / 2 * sin(A1) / sin(A2);

   Line.SetLineColor(kWhite);
   Line.SetLineStyle(kDashed);
   Line.SetLineWidth(2);
   Line.DrawLine(0, 0, W / 2 * cos(A1), W / 2 * sin(A1));
   Line.DrawLine(W / 2 * cos(A1), W / 2 * sin(A1), x * cos(A2), x * sin(A2));
   
   Arrow.SetLineColor(kBlue);
   Arrow.SetFillColor(kBlue);
   Arrow.SetAngle(30);
   Arrow.SetLineStyle(1);
   Arrow.SetLineWidth(2);
   Arrow.SetArrowSize(0.03);
   Arrow.DrawArrow(0, 0, (W / 2 * cos(A2) + L) * F, (W / 2 * sin(A2)) * F);
   Arrow.DrawArrow(0, 0, (-W / 2 * cos(A2) + L) * F, (-W / 2 * sin(A2)) * F);
   Arrow.SetLineColor(kGreen - 3);
   Arrow.SetFillColor(kGreen - 3);
   Arrow.DrawArrow(0, 0, (W / 2 * cos(A1) - L) * F, (W / 2 * sin(A1)) * F);
   Arrow.DrawArrow(0, 0, (-W / 2 * cos(A1) - L) * F, (-W / 2 * sin(A1)) * F);

   Arc.SetFillStyle(0);
   Arc.SetLineWidth(2);
   Arc.SetLineColor(kRed);
   Arc.DrawArc(0, 0, W / 4, (PI + A1) * 180 / PI, (PI + A2) * 180 / PI, "only");

   Latex.SetTextAlign(22);
   Latex.DrawLatex(-W / 4 * cos((A1 + A2) / 2) - D, -W / 4 * sin((A1 + A2) / 2) - D, "#phi");
   
   Latex.SetTextAlign(11);
   Latex.DrawLatex((W / 2 * cos(A2) + L) * F + D, (W / 2 * sin(A2)) * F + D, "l+");
   Latex.SetTextAlign(13);
   Latex.DrawLatex((-W / 2 * cos(A2) + L) * F + D, (-W / 2 * sin(A2)) * F - D, "l-");
   Latex.SetTextAlign(31);
   Latex.DrawLatex((W / 2 * cos(A1) - L) * F - D, (W / 2 * sin(A1)) * F + D / 2, "l+");
   Latex.SetTextAlign(33);
   Latex.DrawLatex((-W / 2 * cos(A1) - L) * F - D, (-W / 2 * sin(A1)) * F - D / 2, "l-");

   C.SaveAs("CPViolation-SameVV-PhiDistributionDiagram.png");
   C.SaveAs("CPViolation-SameVV-PhiDistributionDiagram.C");
   C.SaveAs("CPViolation-SameVV-PhiDistributionDiagram.eps");
   C.SaveAs("CPViolation-SameVV-PhiDistributionDiagram.pdf");
}










