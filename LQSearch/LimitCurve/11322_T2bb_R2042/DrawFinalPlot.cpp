#include <iostream>
#include <fstream>
using namespace std;

#include "TCanvas.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TLatex.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper2.h"

int main();
void ReadGraph(TGraph &G, string FileName);

int main()
{
   TGraph Expected, Observed, ExpectedBand, ObservedClosed, ObservedBand;
   TGraph CDF, D0, ATLAS;

   ReadGraph(Expected, "ExpectedGraph.txt");
   ReadGraph(ExpectedBand, "ExpectedSigma.txt");
   ReadGraph(Observed, "ObservedGraph.txt");
   ReadGraph(ObservedBand, "ObservedSigma.txt");
   ReadGraph(CDF, "CDFxy");
   ReadGraph(D0, "D0xy");
   ReadGraph(ObservedClosed, "ObservedGraphClosed.txt");
   ReadGraph(ATLAS, "ATLASxy");

   PsFileHelper PsFile("Hmm.ps");
   PsFile.AddTextPage("Hmm");

   PsFile.AddPlot(Expected, "al");
   PsFile.AddPlot(ExpectedBand, "al");
   PsFile.AddPlot(Observed, "al");
   PsFile.AddPlot(ObservedBand, "al");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   TCanvas C("C", "C", 1024, 1024);
   C.SetLeftMargin(0.15);

   // TH2D HWorld("HWorld", ";m_{#tilde{b}} [GeV];m_{#tilde{#chi}^{0}} [GeV]", 50, 100, 550, 50, 50, 500);
   TH2D HWorld("HWorld", ";m_{#tilde{b}_{1}} [GeV];m_{#tilde{#chi}^{0}_{1}} [GeV]", 50, 100, 550, 50, 50, 250);
   HWorld.GetYaxis()->SetTitleOffset(1);
   HWorld.GetXaxis()->SetTitleSize(0.05);
   HWorld.GetXaxis()->SetLabelSize(0.04);
   HWorld.GetXaxis()->SetTitleOffset(0.9);
   HWorld.GetYaxis()->SetTitleSize(0.05);
   HWorld.GetYaxis()->SetLabelSize(0.04);
   HWorld.GetYaxis()->SetTitleOffset(1.25);
   HWorld.SetStats(0);
   HWorld.Draw();

   // ExpectedBand.SetFillStyle(3744);
   // ExpectedBand.SetFillColor(kGreen - 3);
   ExpectedBand.SetLineWidth(3);
   ExpectedBand.SetLineStyle(9);
   ExpectedBand.SetLineColor(kGreen - 3);

   Expected.SetLineWidth(4);
   Expected.SetLineColor(kGreen - 3);

   Observed.SetLineWidth(3);
   Observed.SetLineColor(kBlack);
   // Observed.SetFillColor(kCyan);

   ObservedClosed.SetFillColor(kCyan);

   ObservedBand.SetLineWidth(3);
   ObservedBand.SetLineColor(kBlack);
   ObservedBand.SetLineStyle(2);

   // ObservedClosed.Draw("F");
   ExpectedBand.Draw("L");
   Expected.Draw("L");
   Observed.Draw("L");
   ObservedBand.Draw("L");

   D0.SetFillColor(kRed);
   CDF.SetFillColor(kBlue);

   D0.Draw("F");
   CDF.Draw("F");

   TGraph ForbiddenGraph;
   ForbiddenGraph.SetLineColor(kBlack);
   ForbiddenGraph.SetLineStyle(7);
   ForbiddenGraph.SetPoint(0, 0, 0);
   ForbiddenGraph.SetPoint(1, 1200, 1200);
   ForbiddenGraph.Draw("l");

   TLatex ForbiddenText;
   ForbiddenText.SetTextAngle(65);
   ForbiddenText.SetTextSize(0.03);
   ForbiddenText.DrawLatex(150, 175, "#tilde{b}_{1} #rightarrow b #tilde{#chi}_{1}^{0} forbidden");

   TLatex SigmaText;
   SigmaText.SetTextAngle(315);
   SigmaText.SetTextSize(0.03);
   SigmaText.SetTextAlign(22);
   // SigmaText.DrawLatex(470, 115, "+1 #sigma");
   // SigmaText.DrawLatex(320, 80, "-1 #sigma");

   TLegend Legend(0.40, 0.55, 0.90, 0.85);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&Observed, "Observed Limit", "l");
   Legend.AddEntry(&ObservedBand, "Observed Limit #pm 1 #sigma (th.)", "l");
   Legend.AddEntry(&Expected, "Median expected Limit", "l");
   Legend.AddEntry(&ExpectedBand, "Expected Limit #pm 1 #sigma (exp.)", "l");
   Legend.AddEntry(&CDF, "CDF 2.65 fb^{-1}", "f");
   Legend.AddEntry(&D0, "D0 5.2 fb^{-1}", "f");
   Legend.Draw();

   AddCMS(0.1, 0.925, 4700, 0.04);

   TLatex DecayModeText;
   DecayModeText.SetTextFont(42);
   DecayModeText.SetTextSize(0.03);
   DecayModeText.SetNDC();
   DecayModeText.DrawLatex(0.65, 0.925, "#tilde{b}_{1} #rightarrow b #tilde{#chi}_{1}^{0}; m(#tilde{g}) >> m(#tilde{q})");

   HWorld.Draw("axis same");

   C.SaveAs("FinalLimit.png");
   C.SaveAs("FinalLimit.C");
   C.SaveAs("FinalLimit.eps");
   C.SaveAs("FinalLimit.pdf");

   ATLAS.SetLineWidth(2);
   ATLAS.SetLineColor(kRed);
   ATLAS.Draw("l");

   C.SaveAs("FinalLimitWithATLAS.png");
   C.SaveAs("FinalLimitWithATLAS.C");
   C.SaveAs("FinalLimitWithATLAS.eps");
   C.SaveAs("FinalLimitWithATLAS.pdf");

   return 0;
}

void ReadGraph(TGraph &G, string FileName)
{
   ifstream in(FileName.c_str());

   while(in)
   {
      double x = -1, y = -1;

      in >> x >> y;

      if(x < 0 || y < 0)
         continue;

      G.SetPoint(G.GetN(), x, y);
   }

   in.close();
}



