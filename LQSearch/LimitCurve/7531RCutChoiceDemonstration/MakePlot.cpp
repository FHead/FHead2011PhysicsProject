#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main()
{
   SetStyle();

   TGraph Center, Up, Down, UpUp, DownDown;

   Center.SetPoint(0, 0.25, 1.97006);
   Center.SetPoint(1, 0.30, 2.20122);
   Center.SetPoint(2, 0.35, 2.68382);
   Center.SetPoint(3, 0.38, 3.18808);
   
   Up.SetPoint(0, 0.25, 2.78572);
   Up.SetPoint(1, 0.30, 3.05102);
   Up.SetPoint(2, 0.35, 3.73470);
   Up.SetPoint(3, 0.38, 4.32271);

   Down.SetPoint(0, 0.25, 1.47166);
   Down.SetPoint(1, 0.30, 1.64723);
   Down.SetPoint(2, 0.35, 1.82088);
   Down.SetPoint(3, 0.38, 2.27889);

   TH1D HWorld("HWorld", ";R^{2} Cut;Expected Limit (pb)", 2, 0.24, 0.4);

   TCanvas C("C", "C", 1024, 1024);

   HWorld.SetStats(0);
   HWorld.SetMinimum(0);
   HWorld.SetMaximum(6);
   HWorld.Draw();

   Center.SetLineWidth(2);
   Center.SetLineColor(kBlack);
   Center.Draw("pl");
   
   Up.SetLineWidth(2);
   Up.SetLineColor(kRed);
   Up.Draw("pl");
   
   Down.SetLineWidth(2);
   Down.SetLineColor(kBlue);
   Down.Draw("pl");

   TLegend Legend(0.15, 0.65, 0.65, 0.85);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.AddEntry(&Up, "Expected limit +1 #sigma", "lp");
   Legend.AddEntry(&Center, "Median expected limit", "lp");
   Legend.AddEntry(&Down, "Expected limit -1 #sigma", "lp");
   Legend.Draw();

   C.SaveAs("RCutChoice.png");
   C.SaveAs("RCutChoice.C");
   C.SaveAs("RCutChoice.eps");
   C.SaveAs("RCutChoice.pdf");
}

