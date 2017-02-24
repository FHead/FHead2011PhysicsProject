#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"

int main()
{
   TFile File("All.root");

   SetThesisStyle();

   TCanvas C;

   TH1D HR("HR", "R", 10, 0, 10);
   TH1D HG("HG", "R", 10, 0, 10);
   TH1D HB("HB", "R", 10, 0, 10);

   HR.SetMarkerStyle(11);
   HG.SetMarkerStyle(11);
   HB.SetMarkerStyle(11);
   HR.SetMarkerColor(kRed);
   HG.SetMarkerColor(kGreen - 3);
   HB.SetMarkerColor(kBlack);

   TTree *Tree = (TTree *)File.Get("Tree");

   TH2D HWorld("HWorld", ";#sqrt{s} (GeV);#sigma(e^{+}e^{-}#rightarrowf#bar{f}h) (fb)",
      100, 100, 400, 100, 1e-4, 500);
   HWorld.SetStats(0);
   HWorld.Draw();

   Tree->SetMarkerStyle(11);

   Tree->SetMarkerColor(kBlack);
   Tree->SetLineColor(kBlack);
   Tree->Draw("(MM)*1000:E", "", "same");

   Tree->SetMarkerColor(kGreen - 3);
   Tree->SetLineColor(kGreen - 3);
   Tree->Draw("(EE)*1000:E", "", "same");
   
   Tree->SetMarkerColor(kRed);
   Tree->SetLineColor(kRed);
   Tree->Draw("(VV)*1000:E", "", "same");

   C.SetLogy(true);

   TLegend Legend(0.15, 0.70, 0.35, 0.85);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&HR, "ee #rightarrow #nu#nuh", "p");
   Legend.AddEntry(&HG, "ee #rightarrow eeh", "p");
   Legend.AddEntry(&HB, "ee #rightarrow #mu#muh", "p");
   Legend.Draw();

   C.SaveAs("FinalState.png");
   C.SaveAs("FinalState.C");
   C.SaveAs("FinalState.eps");
   C.SaveAs("FinalState.pdf");

   HWorld.Draw();

   Tree->SetMarkerColor(kBlack);
   Tree->SetLineColor(kBlack);
   Tree->Draw("(MM/0.0363)*1000:E", "", "same");

   Tree->SetMarkerColor(kGreen - 3);
   Tree->SetLineColor(kGreen - 3);
   Tree->Draw("(EE-MM/0.0363*0.0366)*1000:E", "", "same");
   
   Tree->SetMarkerColor(kRed);
   Tree->SetLineColor(kRed);
   Tree->Draw("(VV-MM/0.0363*0.0666)*1000:E", "", "same");

   C.SetLogy(true);
   
   TLegend Legend2(0.15, 0.70, 0.35, 0.85);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.AddEntry(&HB, "ZH", "p");
   Legend2.AddEntry(&HR, "WW fusion", "p");
   Legend2.AddEntry(&HG, "ZZ fusion", "p");
   Legend2.Draw();

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.020);
   Latex.DrawLatex(0.10, 0.92, "Note: fusion curves include interference with ZH");

   C.SaveAs("Process.png");
   C.SaveAs("Process.C");
   C.SaveAs("Process.eps");
   C.SaveAs("Process.pdf");
   
   File.Close();

   return 0;
}






