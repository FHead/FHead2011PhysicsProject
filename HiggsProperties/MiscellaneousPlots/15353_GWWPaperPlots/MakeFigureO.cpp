#include <iostream>
using namespace std;

#include "TGraph.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2D.h"
#include "TGraphAsymmErrors.h"
#include "TGaxis.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   TFile File("FigureMGraphs.root");

   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " AveageNS=(Y|N)" << endl;
      return -1;
   }

   string Suffix = "";
   if(argv[1][0] == 'Y')
      Suffix = "_AverageNS";

   TGraphAsymmErrors *G1 = (TGraphAsymmErrors *)File.Get(("ERR_Both_J_N" + Suffix).c_str());
   TGraphAsymmErrors *G2 = (TGraphAsymmErrors *)File.Get(("ERR_Both_J_Y" + Suffix).c_str());
   TGraphAsymmErrors *G3 = (TGraphAsymmErrors *)File.Get(("ERR_Both_A_N" + Suffix).c_str());

   // for(int i = 0; i < (int)G1->GetN(); i++)
   // {
   //    G1->SetPointError(i, 0, 0, G1->GetErrorYhigh(i), G1->GetErrorYlow(i));
   //    G2->SetPointError(i, 0, 0, G2->GetErrorYhigh(i), G2->GetErrorYlow(i));
   //    G3->SetPointError(i, 0, 0, G3->GetErrorYhigh(i), G3->GetErrorYlow(i));
   // }

   G1->SetLineWidth(4);
   G2->SetLineWidth(3);
   G3->SetLineWidth(2);

   G1->SetLineColor(9);
   G2->SetLineColor(30);
   G3->SetLineColor(46);

   G1->SetMarkerColor(9);
   G2->SetMarkerColor(30);
   G3->SetMarkerColor(46);

   G1->SetMarkerStyle(6);
   G2->SetMarkerStyle(6);
   G3->SetMarkerStyle(6);

   G1->Set(8);
   G2->Set(8);
   G3->Set(8);

   TCanvas C;

   double Factor = 1;
   if(Suffix != "")
      Factor = 1.78;

   string XAxis = "Integrated Luminosity (fb^{-1})";
   if(Suffix != "")
      XAxis = "Approximate N_{S}";
   TH2D HWorld("HWorld", Form(";%s;Model separation p-value", XAxis.c_str()), 100, 25 * 0.8 * Factor, 3200 / 0.8 * Factor, 100, 0.001, 1);
   HWorld.SetStats(0);

   HWorld.Draw();
   G1->Draw("pl");
   G2->Draw("pl");
   G3->Draw("pl");
   
   TGaxis GAxis(25 * 0.8 * Factor, 1, 3200 / 0.8 * Factor, 1,
      25 * 0.8, 3200 / 0.8, 510, "-G");
   GAxis.SetLabelFont(42);
   GAxis.SetLabelSize(0.035);
   GAxis.SetTitleFont(42);
   GAxis.SetTitleSize(0.035);
   GAxis.SetTitleOffset(1.00);
   if(Suffix != "")
      GAxis.SetTitle("Integrated Luminosity (fb^{-1})");
   else
      GAxis.SetLabelSize(0);

   C.SetTickx(0);
   GAxis.Draw();

   TGraph GLine;
   GLine.SetPoint(0, 0, 0.05);
   GLine.SetPoint(1, 10000000, 0.05);
   GLine.SetLineStyle(kDashed);
   GLine.Draw("l");

   TLegend Legend(0.15, 0.45, 0.55, 0.20);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.AddEntry(G1, "Loose cut, y_{t} integrated", "l");
   Legend.AddEntry(G2, "Loose cut, y_{t} fixed", "l");
   Legend.AddEntry(G3, "Run I CMS-like cut, y_{t} integrated", "l");
   Legend.Draw();

   C.SetLogx();
   C.SetLogy();

   C.SaveAs(Form("Plots/FigureO%s.png", Suffix.c_str()));
   C.SaveAs(Form("Plots/FigureO%s.C"  , Suffix.c_str()));
   C.SaveAs(Form("Plots/FigureO%s.eps", Suffix.c_str()));
   C.SaveAs(Form("Plots/FigureO%s.pdf", Suffix.c_str()));

   File.Close();

   return 0;
}




