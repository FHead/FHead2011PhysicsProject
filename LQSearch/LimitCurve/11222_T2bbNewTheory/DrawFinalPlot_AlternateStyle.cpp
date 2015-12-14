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

   TLine ExpectedUp(280, 234.5, 330, 234.5);
   TLine ExpectedDown(280, 225.5, 330, 225.5);
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

   TCanvas C("C", "C", 1536, 1024);
   // C.SetLeftMargin(0.15);

   // TH2D HWorld("HWorld", ";m_{#tilde{b}} [GeV];m_{#tilde{#chi}^{0}} [GeV]", 50, 100, 550, 50, 50, 500);
   TH2D HWorld("HWorld", ";M_{#tilde{b}_{1}} [GeV];M_{#tilde{#chi}^{0}_{1}} [GeV]", 50, 100, 550, 50, 50, 250);
   HWorld.GetYaxis()->SetTitleOffset(1);
   HWorld.GetXaxis()->SetTitleSize(0.042);
   HWorld.GetXaxis()->SetLabelSize(0.035);
   HWorld.GetXaxis()->SetTitleOffset(1);
   HWorld.GetYaxis()->SetTitleSize(0.042);
   HWorld.GetYaxis()->SetLabelSize(0.035);
   HWorld.GetYaxis()->SetTitleOffset(1);
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

   gStyle->SetLineStyleString(9, "60 40");
   Observed.SetLineWidth(4);
   Observed.SetLineStyle(9);
   Observed.SetLineColor(kRed + 2);
   ObservedBand2.SetLineWidth(4);
   ObservedBand2.SetLineStyle(9);
   ObservedBand2.SetLineColor(kRed + 2);

   /*
   TGraph GreyRegion;
   GreyRegion.SetPoint(0, 200, 50);
   GreyRegion.SetPoint(1, 250, 100);
   GreyRegion.SetPoint(2, 280, 100);
   GreyRegion.SetPoint(3, 325, 150);
   GreyRegion.SetPoint(4, 400, 300);
   GreyRegion.SetPoint(5, 250, 250);
   GreyRegion.SetPoint(6, 100, 100);
   GreyRegion.SetPoint(7, 100, 50);
   GreyRegion.SetPoint(8, 200, 50);
   GreyRegion.SetFillColor(14);
   GreyRegion.Draw("F");

   TLatex GreyText;
   GreyText.SetTextAngle(57);
   GreyText.SetTextSize(0.03);
   GreyText.DrawLatex(175, 125, "Models ignored via ISR procedure");
   */

   // ObservedClosed.SetFillColor(kCyan);

   ObservedBand.SetLineWidth(2);
   ObservedBand.SetLineColor(kRed + 2);
   ObservedBand.SetLineStyle(3);

   // ObservedClosed.Draw("F");
   ExpectedBand.Draw("CF");
   Expected.Draw("C");
   Observed.Draw("C");
   ObservedBand.Draw("C");

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
   ForbiddenText.SetTextAngle(57);
   ForbiddenText.SetTextSize(0.03);
   ForbiddenText.DrawLatex(145, 170, "#tilde{b}_{1} #rightarrow b #tilde{#chi}_{1}^{0} forbidden");

   TLatex SigmaText;
   SigmaText.SetTextAngle(315);
   SigmaText.SetTextSize(0.03);
   SigmaText.SetTextAlign(22);
   // SigmaText.DrawLatex(470, 115, "+1 #sigma");
   // SigmaText.DrawLatex(320, 80, "-1 #sigma");

   /*
   TBox LegendBox1(270, 175, 540, 240);
   LegendBox1.SetFillColor(kWhite);
   LegendBox1.Draw("");
   TBox LegendBox2(270, 175, 540, 240);
   LegendBox2.SetFillStyle(0);
   LegendBox2.SetLineWidth(1);
   LegendBox2.SetLineColor(kBlack);
   LegendBox2.Draw("");
   */

   TLegend Legend1(0.40, 0.55, 0.90, 0.85);
   Legend1.SetFillStyle(0);
   Legend1.SetFillColor(0);
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

   TLatex DecayModeText;
   DecayModeText.SetTextFont(42);
   DecayModeText.SetTextSize(0.04);
   DecayModeText.SetTextAlign(32);
   DecayModeText.SetNDC();
   DecayModeText.DrawLatex(0.9, 0.925, "#tilde{b}_{1} #rightarrow b #tilde{#chi}_{1}^{0}; m(#tilde{g}) >> m(#tilde{q})");

   TLatex latex;
   latex.SetTextAlign(12);
   latex.SetTextSize(0.04);
   latex.SetTextFont(42);
   latex.SetNDC();
   latex.DrawLatex(0.1, 0.925, "CMS  4.7 fb^{-1} at #sqrt{s} = 7 TeV");

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



