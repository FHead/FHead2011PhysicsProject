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

   Center.SetPoint(0, 0.25, 4.33379);
   Center.SetPoint(1, 0.30, 4.63348);
   Center.SetPoint(2, 0.35, 5.56314);
   Center.SetPoint(3, 0.38, 5.82524);
   Center.SetPoint(4, 0.42, 8.03929);
   
   Up.SetPoint(0, 0.25, 6.38867);
   Up.SetPoint(1, 0.30, 6.56489);
   Up.SetPoint(2, 0.35, 8.21832);
   Up.SetPoint(3, 0.38, 8.37423);
   Up.SetPoint(4, 0.42, 11.0258);

   Down.SetPoint(0, 0.25, 3.4714);
   Down.SetPoint(1, 0.30, 3.04941);
   Down.SetPoint(2, 0.35, 3.72607);
   Down.SetPoint(3, 0.38, 3.90197);
   Down.SetPoint(4, 0.42, 5.40158);

   TH1D HWorld("HWorld", ";R^{2} Cut;Expected Limit (pb)", 2, 0.24, 0.45);

   TCanvas C("C", "C", 1024, 1024);

   HWorld.SetStats(0);
   HWorld.SetMinimum(2);
   HWorld.SetMaximum(25);
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

   C.SetLogy();
   C.SaveAs("RCutChoice_LQ200.png");
   C.SaveAs("RCutChoice_LQ200.C");
   C.SaveAs("RCutChoice_LQ200.eps");
   C.SaveAs("RCutChoice_LQ200.pdf");
}

