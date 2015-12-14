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
   TGraph Expected, Observed, ExpectedBand;
   TGraph CDF, D0;

   ReadGraph(Expected, "ExpectedGraph.txt");
   ReadGraph(ExpectedBand, "ExpectedSigma.txt");
   ReadGraph(Observed, "ObservedGraph.txt");
   ReadGraph(CDF, "CDFxy");
   ReadGraph(D0, "D0xy");

   PsFileHelper PsFile("Hmm.ps");
   PsFile.AddTextPage("Hmm");

   PsFile.AddPlot(Expected, "al");
   PsFile.AddPlot(ExpectedBand, "al");
   PsFile.AddPlot(Observed, "al");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   TCanvas C("C", "C", 1024, 1024);

   TH2D HWorld("HWorld", ";m_{#tilde{b}} [GeV];m_{#tilde{#chi}^{0}} [GeV]", 50, 100, 450, 50, 50, 400);
   HWorld.GetYaxis()->SetTitleOffset(1.4);
   HWorld.SetStats(0);
   HWorld.Draw();

   ExpectedBand.SetFillStyle(3744);
   ExpectedBand.SetFillColor(kGreen - 2);
   ExpectedBand.SetLineWidth(3);
   ExpectedBand.SetLineColor(kGreen - 2);

   Expected.SetLineWidth(3);
   Expected.SetLineColor(kGreen - 2);

   Observed.SetLineWidth(3);
   Observed.SetLineColor(kBlue);

   ExpectedBand.Draw("F");
   Expected.Draw("L");
   Observed.Draw("L");

   D0.SetFillColor(kGreen);
   CDF.SetFillColor(kGray);

   D0.Draw("F");
   CDF.Draw("F");

   TGraph ForbiddenGraph;
   ForbiddenGraph.SetLineColor(kBlack);
   ForbiddenGraph.SetLineStyle(7);
   ForbiddenGraph.SetPoint(0, 0, 0);
   ForbiddenGraph.SetPoint(1, 1200, 1200);
   ForbiddenGraph.Draw("l");

   TLatex ForbiddenText;
   ForbiddenText.SetTextAngle(45);
   ForbiddenText.SetTextSize(0.03);
   ForbiddenText.DrawLatex(150, 175, "Decay forbidden");

   TLegend Legend(0.15, 0.60, 0.55, 0.80);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&Observed, "Observed Limit", "l");
   Legend.AddEntry(&ExpectedBand, "Expected Limit (#pm 1 #sigma)", "fl");
   Legend.AddEntry(&CDF, "CDF 2.65 fb^{-1}", "f");
   Legend.AddEntry(&D0, "D0 5.2 fb^{-1}", "f");
   Legend.Draw();

   AddCMSPreliminary(0.1, 0.92, 1752);

   C.SaveAs("FinalLimit.png");
   C.SaveAs("FinalLimit.C");
   C.SaveAs("FinalLimit.eps");
   C.SaveAs("FinalLimit.pdf");

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



