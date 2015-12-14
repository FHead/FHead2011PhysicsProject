#include <iostream>
#include <fstream>
using namespace std;

#include "TCanvas.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"

#include "SetStyle.h"
#include "PlotHelper2.h"

int main();
void ReadGraph(TGraph &G, string FileName);

int main()
{
   TGraph Expected, Observed, ExpectedBand, ObservedClosed, ObservedBand;
   TGraph ExpectedBand2, ObservedBand2;
   TGraph CDF, D0, ATLAS;

   TLine ExpectedUp(262, 234.5, 315, 234.5);
   TLine ExpectedDown(262, 225.5, 315, 225.5);
   ExpectedUp.SetLineColor(kRed + 2);
   ExpectedDown.SetLineColor(kRed + 2);
   ExpectedUp.SetLineStyle(3);
   ExpectedDown.SetLineStyle(3);
   ExpectedUp.SetLineWidth(2);
   ExpectedDown.SetLineWidth(2);

   ReadGraph(Expected, "ExpectedGraph.txt");
   ReadGraph(ExpectedBand, "ExpectedSigma.txt");
   ReadGraph(ExpectedBand2, "ExpectedSigma.txt");
   ReadGraph(Observed, "ObservedGraph.txt");
   ReadGraph(ObservedBand, "ObservedSigma.txt");
   ReadGraph(ObservedBand2, "ObservedSigma.txt");
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

   ExpectedBand.SetFillStyle(1001);
   ExpectedBand.SetFillColor(kOrange - 2);
   ExpectedBand2.SetFillStyle(1001);
   ExpectedBand2.SetFillColor(kOrange - 2);

   Expected.SetLineWidth(2);
   Expected.SetLineColor(kBlack);
   Expected.SetLineStyle(7);
   ExpectedBand2.SetLineWidth(2);
   ExpectedBand2.SetLineColor(kBlack);
   ExpectedBand2.SetLineStyle(7);

   Observed.SetLineWidth(4);
   Observed.SetLineColor(kRed + 2);
   ObservedBand2.SetLineWidth(4);
   ObservedBand2.SetLineColor(kRed + 2);

   // ObservedClosed.SetFillColor(kCyan);

   ObservedBand.SetLineWidth(2);
   ObservedBand.SetLineColor(kRed + 2);
   ObservedBand.SetLineStyle(3);

   // ObservedClosed.Draw("F");
   ExpectedBand.Draw("F");
   Expected.Draw("L");
   Observed.Draw("L");
   ObservedBand.Draw("L");

   D0.SetFillColor(kSpring + 7);
   CDF.SetFillColor(kBlue - 4);

   D0.SetLineWidth(1);
   CDF.SetLineWidth(1);

   D0.SetLineColor(kBlack);
   CDF.SetLineColor(kBlack);

   D0.Draw("F");
   CDF.Draw("F");
   
   D0.Draw("L");
   CDF.Draw("L");

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

   TLegend Legend1(0.40, 0.55, 0.90, 0.85);
   Legend1.SetFillStyle(0);
   Legend1.SetTextFont(42);
   Legend1.SetBorderSize(0);
   Legend1.AddEntry(&ObservedBand2, "Observed Limit (#pm 1 #sigma (th.))", "l");
   Legend1.AddEntry(&ExpectedBand2, "Expected Limit (#pm 1 #sigma (exp.))", "fl");
   Legend1.AddEntry(&CDF, "CDF 2.65 fb^{-1}", "f");
   Legend1.AddEntry(&D0, "D0 5.2 fb^{-1}", "f");
   Legend1.AddEntry(&D0, "", "");
   Legend1.Draw();

   ExpectedUp.Draw();
   ExpectedDown.Draw();

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

   TLegend Legend2(0.40, 0.55, 0.90, 0.85);
   Legend2.SetFillStyle(0);
   Legend2.SetTextFont(42);
   Legend2.SetBorderSize(0);
   Legend2.AddEntry(&ObservedBand2, "Observed Limit (#pm 1 #sigma (th.))", "l");
   Legend2.AddEntry(&ExpectedBand2, "Expected Limit (#pm 1 #sigma (exp.))", "fl");
   Legend2.AddEntry(&CDF, "CDF 2.65 fb^{-1}", "f");
   Legend2.AddEntry(&D0, "D0 5.2 fb^{-1}", "f");
   Legend2.AddEntry(&ATLAS, "ATLAS 2.05 fb^{-1}", "l");
   Legend2.Draw();
   
   ATLAS.SetLineWidth(3);
   ATLAS.SetLineColor(kBlack);
   ATLAS.Draw("l");

   D0.Draw("F");
   CDF.Draw("F");
   
   D0.Draw("L");
   CDF.Draw("L");

   HWorld.Draw("axis same");

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



