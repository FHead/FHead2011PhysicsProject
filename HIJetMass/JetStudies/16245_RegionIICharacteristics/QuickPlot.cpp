#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile F("AA6DijetCymbal.root");

   TTree *T = (TTree *)F.Get("T");

   TH1D H1("H1", "", 100, 0, 5);
   TH1D H2I("H2I", "", 100, 0, 5);
   TH1D H2O("H2O", "", 100, 0, 5);

   H1.Sumw2();
   H2I.Sumw2();
   H2O.Sumw2();

   H1.SetStats(0);
   H2I.SetStats(0);
   H2O.SetStats(0);

   T->Draw("SDMass/GenSDMass>>H1",
      "MCWeight * (Region == 1 && JetPT > 100 && abs(JetEta) < 1.3 && SDMass/GenSDMass < 5)");
   T->Draw("SDMass/GenSDMass>>H2I",
      "MCWeight * (Region == 2 && Inside && JetPT > 100 && abs(JetEta) < 1.3 && SDMass/GenSDMass < 5)");
   T->Draw("SDMass/GenSDMass>>H2O",
      "MCWeight * (Region == 2 && !Inside && JetPT > 100 && abs(JetEta) < 1.3 && SDMass/GenSDMass < 5)");

   H1.Scale(1 / H1.Integral() / (0.05));
   H2I.Scale(1 / H2I.Integral() / (0.05));
   H2O.Scale(1 / H2O.Integral() / (0.05));

   H1.SetLineColor(kBlack);
   H2I.SetLineColor(kBlue);
   H2O.SetLineColor(kRed);
   
   H1.SetMarkerColor(kBlack);
   H2I.SetMarkerColor(kBlue);
   H2O.SetMarkerColor(kRed);

   H1.GetXaxis()->SetTitle("SD Mass / Gen SD Mass");
   H1.GetYaxis()->SetTitle("a.u.");

   TCanvas C;

   H1.Draw("");
   H2I.Draw("same");
   H2O.Draw("same");
   
   H1.Draw("hist same");
   H2I.Draw("hist same");
   H2O.Draw("hist same");

   TLegend Legend(0.4, 0.8, 0.7, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H1, "Region I", "pl");
   Legend.AddEntry(&H2I, "Region II Inside", "pl");
   Legend.AddEntry(&H2O, "Region II Outside", "pl");
   Legend.Draw();

   C.SaveAs("Resolution.png");
   C.SaveAs("Resolution.C");
   C.SaveAs("Resolution.eps");
   C.SaveAs("Resolution.pdf");

   F.Close();

   return 0;
}









