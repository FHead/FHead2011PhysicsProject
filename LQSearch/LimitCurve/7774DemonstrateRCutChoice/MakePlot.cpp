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

   Center.SetPoint(0, 0.25, 0.171111);
   Center.SetPoint(1, 0.30, 0.121926);
   Center.SetPoint(2, 0.35, 0.11037);
   Center.SetPoint(3, 0.38, 0.0973959);
   Center.SetPoint(4, 0.42, 0.0955915);
   
   Up.SetPoint(0, 0.25, 0.252738);
   Up.SetPoint(1, 0.30, 0.173617);
   Up.SetPoint(2, 0.35, 0.158199);
   Up.SetPoint(3, 0.38, 0.137237);
   Up.SetPoint(4, 0.42, 0.130122);

   Down.SetPoint(0, 0.25, 0.138501);
   Down.SetPoint(1, 0.30, 0.080494);
   Down.SetPoint(2, 0.35, 0.0735219);
   Down.SetPoint(3, 0.38, 0.0655802);
   Down.SetPoint(4, 0.42, 0.0637274);

   TH1D HWorld("HWorld", ";R^{2} Cut;Expected Limit (pb)", 2, 0.24, 0.45);

   TCanvas C("C", "C", 1024, 1024);

   HWorld.SetStats(0);
   HWorld.SetMinimum(0.03);
   HWorld.SetMaximum(0.8);
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

   TLegend Legend(0.35, 0.65, 0.85, 0.85);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.AddEntry(&Up, "Expected limit +1 #sigma", "lp");
   Legend.AddEntry(&Center, "Median expected limit", "lp");
   Legend.AddEntry(&Down, "Expected limit -1 #sigma", "lp");
   Legend.Draw();

   C.SetLogy();
   C.SaveAs("RCutChoice_LQ450.png");
   C.SaveAs("RCutChoice_LQ450.C");
   C.SaveAs("RCutChoice_LQ450.eps");
   C.SaveAs("RCutChoice_LQ450.pdf");
}

