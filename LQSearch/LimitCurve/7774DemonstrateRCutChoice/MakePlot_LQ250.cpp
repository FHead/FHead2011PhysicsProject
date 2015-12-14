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

   Center.SetPoint(0, 0.25, 1.36393);
   Center.SetPoint(1, 0.30, 1.17694);
   Center.SetPoint(2, 0.35, 1.42196);
   Center.SetPoint(3, 0.38, 1.47099);
   Center.SetPoint(4, 0.42, 1.88169);
   
   Up.SetPoint(0, 0.25, 2.00701);
   Up.SetPoint(1, 0.30, 1.63958);
   Up.SetPoint(2, 0.35, 1.99685);
   Up.SetPoint(3, 0.38, 2.11933);
   Up.SetPoint(4, 0.42, 2.55804);

   Down.SetPoint(0, 0.25, 1.10345);
   Down.SetPoint(1, 0.30, 0.781196);
   Down.SetPoint(2, 0.35, 0.927752);
   Down.SetPoint(3, 0.38, 0.997764);
   Down.SetPoint(4, 0.42, 1.24711);

   TH1D HWorld("HWorld", ";R^{2} Cut;Expected Limit (pb)", 2, 0.24, 0.45);

   TCanvas C("C", "C", 1024, 1024);

   HWorld.SetStats(0);
   HWorld.SetMinimum(0.5);
   HWorld.SetMaximum(5);
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
   C.SaveAs("RCutChoice_LQ250.png");
   C.SaveAs("RCutChoice_LQ250.C");
   C.SaveAs("RCutChoice_LQ250.eps");
   C.SaveAs("RCutChoice_LQ250.pdf");
}

