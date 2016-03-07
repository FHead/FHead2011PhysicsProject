#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"

#include "PTYFunctions.h"

// #define LOWQ

int main()
{
   SetThesisStyle();

   TGraph GU, GD, GC, GS, GB, GUbar, GDbar, GCbar, GBbar, GSbar, GG;

   int Bin = 10000;
   double Min = log(1e-10);
   double Max = log(1);
   for(int i = 0; i < Bin; i++)
   {
      double x = exp((Max - Min) / Bin * i + Min);

#ifndef LOWQ
      GU.SetPoint(i, x, GetUxDensity_MZ_CTEQ6l1_13432(x));
      GD.SetPoint(i, x, GetDxDensity_MZ_CTEQ6l1_13432(x));
      GC.SetPoint(i, x, GetCxDensity_MZ_CTEQ6l1_13432(x));
      GS.SetPoint(i, x, GetSxDensity_MZ_CTEQ6l1_13432(x));
      GB.SetPoint(i, x, GetBxDensity_MZ_CTEQ6l1_13432(x));
      GUbar.SetPoint(i, x, GetUBarxDensity_MZ_CTEQ6l1_13432(x));
      GDbar.SetPoint(i, x, GetDBarxDensity_MZ_CTEQ6l1_13432(x));
      GCbar.SetPoint(i, x, GetCBarxDensity_MZ_CTEQ6l1_13432(x));
      GSbar.SetPoint(i, x, GetSBarxDensity_MZ_CTEQ6l1_13432(x));
      GBbar.SetPoint(i, x, GetBBarxDensity_MZ_CTEQ6l1_13432(x));
      GG.SetPoint(i, x, GetGxDensity_MZ_CTEQ6l1_13432(x));
#else
      GU.SetPoint(i, x, GetUxDensity_2_CTEQ6l1_13432(x));
      GD.SetPoint(i, x, GetDxDensity_2_CTEQ6l1_13432(x));
      GC.SetPoint(i, x, GetCxDensity_2_CTEQ6l1_13432(x));
      GS.SetPoint(i, x, GetSxDensity_2_CTEQ6l1_13432(x));
      GB.SetPoint(i, x, GetBxDensity_2_CTEQ6l1_13432(x));
      GUbar.SetPoint(i, x, GetUBarxDensity_2_CTEQ6l1_13432(x));
      GDbar.SetPoint(i, x, GetDBarxDensity_2_CTEQ6l1_13432(x));
      GCbar.SetPoint(i, x, GetCBarxDensity_2_CTEQ6l1_13432(x));
      GSbar.SetPoint(i, x, GetSBarxDensity_2_CTEQ6l1_13432(x));
      GBbar.SetPoint(i, x, GetBBarxDensity_2_CTEQ6l1_13432(x));
      GG.SetPoint(i, x, GetGxDensity_2_CTEQ6l1_13432(x));
#endif
   }

   TH2D HWorld1("HWorld1", ";x;x f(x)", 100, 0.000001, 1.5, 100, 0.000001, 10000);
   HWorld1.SetStats(0);
   HWorld1.GetXaxis()->SetTitleOffset(1.2);
   HWorld1.GetYaxis()->SetTitleOffset(1.4);
   TH2D HWorld2("HWorld2", ";x;x f(x)", 100, 0.01, 1.2, 100, 0.00001, 100);
   HWorld2.SetStats(0);
   HWorld2.GetXaxis()->SetTitleOffset(1.2);
   HWorld2.GetYaxis()->SetTitleOffset(1.4);
   TH2D HWorld3("HWorld3", ";x;x f(x)", 100, 0, 1.0, 100, 0, 1);
   HWorld3.SetStats(0);
   HWorld3.GetXaxis()->SetTitleOffset(1.2);
   HWorld3.GetYaxis()->SetTitleOffset(1.4);

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextAlign(33);
   Latex.SetTextSize(0.035);
   Latex.SetTextFont(42);

   TLegend Legend1(0.15, 0.15, 0.45, 0.40);
   Legend1.SetTextFont(42);
   Legend1.SetBorderSize(0);
   Legend1.SetFillStyle(0);
   Legend1.SetTextSize(0.035);
   TLegend Legend2(0.30, 0.15, 0.60, 0.40);
   Legend2.SetTextFont(42);
   Legend2.SetBorderSize(0);
   Legend2.SetFillStyle(0);
   Legend2.SetTextSize(0.035);
   Legend1.AddEntry(&GU, "u", "l");
   Legend1.AddEntry(&GD, "d", "l");
   Legend1.AddEntry(&GC, "c", "l");
   Legend1.AddEntry(&GS, "s", "l");
   Legend1.AddEntry(&GB, "b", "l");
   Legend2.AddEntry(&GUbar, "#bar{u}", "l");
   Legend2.AddEntry(&GDbar, "#bar{d}", "l");
   Legend2.AddEntry(&GCbar, "#bar{c}", "l");
   Legend2.AddEntry(&GSbar, "#bar{s}", "l");
   Legend2.AddEntry(&GBbar, "#bar{b}", "l");
   Legend1.AddEntry(&GG, "g", "l");
   Legend2.AddEntry(&GG, "", "");

   TLegend Legend3(0.50, 0.45, 0.80, 0.70);
   Legend3.SetTextFont(42);
   Legend3.SetBorderSize(0);
   Legend3.SetFillStyle(0);
   Legend3.SetTextSize(0.035);
   TLegend Legend4(0.65, 0.45, 0.95, 0.70);
   Legend4.SetTextFont(42);
   Legend4.SetBorderSize(0);
   Legend4.SetFillStyle(0);
   Legend4.SetTextSize(0.035);
   Legend3.AddEntry(&GU, "u", "l");
   Legend3.AddEntry(&GD, "d", "l");
   Legend3.AddEntry(&GC, "c", "l");
   Legend3.AddEntry(&GS, "s", "l");
   Legend3.AddEntry(&GB, "b", "l");
   Legend4.AddEntry(&GUbar, "#bar{u}", "l");
   Legend4.AddEntry(&GDbar, "#bar{d}", "l");
   Legend4.AddEntry(&GCbar, "#bar{c}", "l");
   Legend4.AddEntry(&GSbar, "#bar{s}", "l");
   Legend4.AddEntry(&GBbar, "#bar{b}", "l");
   Legend3.AddEntry(&GG, "g", "l");
   Legend4.AddEntry(&GG, "", "");

   GU.SetLineWidth(2);
   GD.SetLineWidth(2);
   GC.SetLineWidth(2);
   GS.SetLineWidth(2);
   GB.SetLineWidth(2);
   GUbar.SetLineWidth(3);
   GDbar.SetLineWidth(3);
   GCbar.SetLineWidth(3);
   GSbar.SetLineWidth(3);
   GBbar.SetLineWidth(3);
   GG.SetLineWidth(2);

   GU.SetLineStyle(1);
   GD.SetLineStyle(1);
   GC.SetLineStyle(1);
   GS.SetLineStyle(1);
   GB.SetLineStyle(1);
   GUbar.SetLineStyle(kDashed);
   GDbar.SetLineStyle(kDashed);
   GCbar.SetLineStyle(kDashed);
   GSbar.SetLineStyle(kDashed);
   GBbar.SetLineStyle(kDashed);
   GG.SetLineStyle(1);

   GU.SetLineColor(kBlack);
   GD.SetLineColor(kBlue);
   GC.SetLineColor(kGreen - 3);
   GS.SetLineColor(kYellow - 3);
   GB.SetLineColor(kCyan - 3);
   GUbar.SetLineColor(kBlack);
   GDbar.SetLineColor(kBlue);
   GCbar.SetLineColor(kGreen - 2);
   GSbar.SetLineColor(kYellow - 2);
   GBbar.SetLineColor(kCyan - 2);
   GG.SetLineColor(kRed);

   TCanvas C;
   C.SetLogx();
   C.SetLogy();

   HWorld1.Draw();
   GU.Draw("l");
   GD.Draw("l");
   GC.Draw("l");
   GS.Draw("l");
   GB.Draw("l");
   GUbar.Draw("l");
   GDbar.Draw("l");
   GCbar.Draw("l");
   GSbar.Draw("l");
   GBbar.Draw("l");
   GG.Draw("l");
   Legend1.Draw();
   Legend2.Draw();
#ifndef LOWQ
   Latex.DrawLatex(0.85 / 1.05, 0.85, "CTEQ 6l1, Q^{2} = (91.1876 GeV)^{2}");
#else
   Latex.DrawLatex(0.85 / 1.05, 0.85, "CTEQ 6l1, Q^{2} = (2 GeV)^{2}");
#endif

#ifndef LOWQ
   C.SaveAs("pdf1.png");
   C.SaveAs("pdf1.C");
   C.SaveAs("pdf1.eps");
   C.SaveAs("pdf1.pdf");
#else
   C.SaveAs("pdf4.png");
   C.SaveAs("pdf4.C");
   C.SaveAs("pdf4.eps");
   C.SaveAs("pdf4.pdf");
#endif

   HWorld2.Draw();
   GU.Draw("l");
   GD.Draw("l");
   GC.Draw("l");
   GS.Draw("l");
   GB.Draw("l");
   GUbar.Draw("l");
   GDbar.Draw("l");
   GCbar.Draw("l");
   GSbar.Draw("l");
   GBbar.Draw("l");
   GG.Draw("l");
   Legend1.Draw();
   Legend2.Draw();
#ifndef LOWQ
   Latex.DrawLatex(0.85 / 1.05, 0.85, "CTEQ 6l1, Q^{2} = (91.1876 GeV)^{2}");
#else
   Latex.DrawLatex(0.85 / 1.05, 0.85, "CTEQ 6l1, Q^{2} = (2 GeV)^{2}");
#endif

#ifndef LOWQ
   C.SaveAs("pdf2.png");
   C.SaveAs("pdf2.C");
   C.SaveAs("pdf2.eps");
   C.SaveAs("pdf2.pdf");
#else
   C.SaveAs("pdf5.png");
   C.SaveAs("pdf5.C");
   C.SaveAs("pdf5.eps");
   C.SaveAs("pdf5.pdf");
#endif

   C.SetLogx(false);
   C.SetLogy(false);

   HWorld3.Draw();
   GU.Draw("l");
   GD.Draw("l");
   GC.Draw("l");
   GS.Draw("l");
   GB.Draw("l");
   GUbar.Draw("l");
   GDbar.Draw("l");
   GCbar.Draw("l");
   GSbar.Draw("l");
   GBbar.Draw("l");
   GG.Draw("l");
   Legend3.Draw();
   Legend4.Draw();
#ifndef LOWQ
   Latex.DrawLatex(0.85 / 1.05, 0.85, "CTEQ 6l1, Q^{2} = (91.1876 GeV)^{2}");
#else
   Latex.DrawLatex(0.85 / 1.05, 0.85, "CTEQ 6l1, Q^{2} = (2 GeV)^{2}");
#endif

#ifndef LOWQ
   C.SaveAs("pdf3.png");
   C.SaveAs("pdf3.C");
   C.SaveAs("pdf3.eps");
   C.SaveAs("pdf3.pdf");
#else
   C.SaveAs("pdf6.png");
   C.SaveAs("pdf6.C");
   C.SaveAs("pdf6.eps");
   C.SaveAs("pdf6.pdf");
#endif

   return 0;
}


