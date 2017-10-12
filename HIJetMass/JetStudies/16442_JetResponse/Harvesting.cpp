#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main();
void AttachPoint(TFile &File, string Name, TGraphAsymmErrors &G, double L, double R, double x);

int main()
{
   SetThesisStyle();

   TFile File("Histograms.root");

   int CBin = 4;
   int PTBin = 14;
   double CBins[] = {0.0, 0.1, 0.3, 0.5, 0.8, 1.0};
   double PTBins[] = {50, 60, 70, 80, 100, 120, 140, 160, 180, 200, 220, 240, 270, 300, 500};

   PdfFileHelper PdfFile("JetScale.pdf");
   PdfFile.AddTextPage("Jet Scale Plots");

   for(int iC = 0; iC < CBin; iC++)
   {
      TGraphAsymmErrors GAll, GG, GQ;
      TGraphAsymmErrors GAllM0, GAllM1, GAllM2, GAllM3;
      TGraphAsymmErrors GGM0, GGM1, GGM2, GGM3;
      TGraphAsymmErrors GQM0, GQM1, GQM2, GQM3;

      for(int iPT = 0; iPT < PTBin; iPT++)
      {
         double MeanPTAll = ((TH1D *)File.Get(Form("HGenPT_All_C%dPT%d", iC, iPT)))->GetMean();
         double MeanPTG = ((TH1D *)File.Get(Form("HGenPT_G_C%dPT%d", iC, iPT)))->GetMean();
         double MeanPTQ = ((TH1D *)File.Get(Form("HGenPT_Q_C%dPT%d", iC, iPT)))->GetMean();

         if(MeanPTAll > 0)
         {
            AttachPoint(File, Form("HResponse_All_C%dPT%d", iC, iPT), GAll, PTBins[iPT], PTBins[iPT+1], MeanPTAll);
            AttachPoint(File, Form("HResponseM0_All_C%dPT%d", iC, iPT), GAllM0, PTBins[iPT], PTBins[iPT+1], MeanPTAll);
            AttachPoint(File, Form("HResponseM1_All_C%dPT%d", iC, iPT), GAllM1, PTBins[iPT], PTBins[iPT+1], MeanPTAll);
            AttachPoint(File, Form("HResponseM2_All_C%dPT%d", iC, iPT), GAllM2, PTBins[iPT], PTBins[iPT+1], MeanPTAll);
            AttachPoint(File, Form("HResponseM3_All_C%dPT%d", iC, iPT), GAllM3, PTBins[iPT], PTBins[iPT+1], MeanPTAll);
         }
         if(MeanPTG > 0)
         {
            AttachPoint(File, Form("HResponse_G_C%dPT%d", iC, iPT), GG, PTBins[iPT], PTBins[iPT+1], MeanPTG);
            AttachPoint(File, Form("HResponseM0_G_C%dPT%d", iC, iPT), GGM0, PTBins[iPT], PTBins[iPT+1], MeanPTG);
            AttachPoint(File, Form("HResponseM1_G_C%dPT%d", iC, iPT), GGM1, PTBins[iPT], PTBins[iPT+1], MeanPTG);
            AttachPoint(File, Form("HResponseM2_G_C%dPT%d", iC, iPT), GGM2, PTBins[iPT], PTBins[iPT+1], MeanPTG);
            AttachPoint(File, Form("HResponseM3_G_C%dPT%d", iC, iPT), GGM3, PTBins[iPT], PTBins[iPT+1], MeanPTG);
         }
         if(MeanPTQ > 0)
         {
            AttachPoint(File, Form("HResponse_Q_C%dPT%d", iC, iPT), GQ, PTBins[iPT], PTBins[iPT+1], MeanPTQ);
            AttachPoint(File, Form("HResponseM0_Q_C%dPT%d", iC, iPT), GQM0, PTBins[iPT], PTBins[iPT+1], MeanPTQ);
            AttachPoint(File, Form("HResponseM1_Q_C%dPT%d", iC, iPT), GQM1, PTBins[iPT], PTBins[iPT+1], MeanPTQ);
            AttachPoint(File, Form("HResponseM2_Q_C%dPT%d", iC, iPT), GQM2, PTBins[iPT], PTBins[iPT+1], MeanPTQ);
            AttachPoint(File, Form("HResponseM3_Q_C%dPT%d", iC, iPT), GQM3, PTBins[iPT], PTBins[iPT+1], MeanPTQ);
         }
      }

      TLatex Latex;
      Latex.SetTextFont(42);
      Latex.SetTextSize(0.035);
      Latex.SetTextAlign(12);
      Latex.SetNDC();

      TCanvas C;

      TH2D HWorld("HWorld", ";Gen Jet P_{T};Jet Scale", 100, 40, 300, 100, -0.15, 0.15);
      HWorld.SetStats(0);
      HWorld.Draw("axis");

      GAll.SetLineColor(kBlack);
      GG.SetLineColor(kRed);
      GQ.SetLineColor(kBlue);
      GAll.SetMarkerColor(kBlack);
      GG.SetMarkerColor(kRed);
      GQ.SetMarkerColor(kBlue);

      GAll.Draw("p");
      GQ.Draw("p");
      GG.Draw("p");

      TLegend Legend(0.50, 0.15, 0.90, 0.35);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.035);
      Legend.SetFillStyle(0);
      Legend.AddEntry(&GAll, "All", "lp");
      Legend.AddEntry(&GQ, "Quark", "lp");
      Legend.AddEntry(&GG, "Gluon", "lp");
      Legend.Draw();

      TGraph G;
      G.SetPoint(0, 0, 0.02);
      G.SetPoint(1, 500, 0.02);
      G.SetPoint(2, 500, 0.00);
      G.SetPoint(3, 0, 0.00);
      G.SetPoint(4, 0, -0.02);
      G.SetPoint(5, 500, -0.02);
      G.SetLineStyle(kDashed);
      G.Draw("l");

      Latex.DrawLatex(0.15, 0.15, Form("Centrality: %d-%d%%", int(CBins[iC] * 100), int(CBins[iC+1] * 100)));
      Latex.DrawLatex(0.15, 0.20, "Gen Jet |#eta| < 1.3");

      PdfFile.AddCanvas(C);

      HWorld.Draw("axis");

      GAllM0.SetLineColor(kMagenta + 3);
      GAllM1.SetLineColor(kMagenta + 1);
      GAllM2.SetLineColor(kMagenta - 4);
      GAllM3.SetLineColor(kMagenta - 9);
      GAllM0.SetMarkerColor(kMagenta + 3);
      GAllM1.SetMarkerColor(kMagenta + 1);
      GAllM2.SetMarkerColor(kMagenta - 4);
      GAllM3.SetMarkerColor(kMagenta - 9);

      TLegend Legend2(0.40, 0.65, 0.80, 0.85);
      Legend2.SetTextFont(42);
      Legend2.SetTextSize(0.035);
      Legend2.SetFillStyle(0);
      Legend2.AddEntry(&GAllM0, "M_{g}/P_{T} = 0.00-0.05", "lp");
      Legend2.AddEntry(&GAllM1, "M_{g}/P_{T} = 0.05-0.10", "lp");
      Legend2.AddEntry(&GAllM2, "M_{g}/P_{T} = 0.10-0.15", "lp");
      Legend2.AddEntry(&GAllM3, "M_{g}/P_{T} = 0.15-0.25", "lp");
      Legend2.Draw();

      GAllM0.Draw("p");
      GAllM1.Draw("p");
      GAllM2.Draw("p");
      GAllM3.Draw("p");

      G.Draw("l");
      
      Latex.DrawLatex(0.15, 0.15, Form("Centrality: %d-%d%%", int(CBins[iC] * 100), int(CBins[iC+1] * 100)));
      Latex.DrawLatex(0.15, 0.20, "Gen Jet |#eta| < 1.3");
      Latex.DrawLatex(0.15, 0.25, "All types");

      PdfFile.AddCanvas(C);

      HWorld.Draw("axis");

      GGM0.SetLineColor(kMagenta + 3);
      GGM1.SetLineColor(kMagenta + 1);
      GGM2.SetLineColor(kMagenta - 4);
      GGM3.SetLineColor(kMagenta - 9);
      GGM0.SetMarkerColor(kMagenta + 3);
      GGM1.SetMarkerColor(kMagenta + 1);
      GGM2.SetMarkerColor(kMagenta - 4);
      GGM3.SetMarkerColor(kMagenta - 9);

      Legend2.Draw();

      GGM0.Draw("p");
      GGM1.Draw("p");
      GGM2.Draw("p");
      GGM3.Draw("p");

      G.Draw("l");

      Latex.DrawLatex(0.15, 0.15, Form("Centrality: %d-%d%%", int(CBins[iC] * 100), int(CBins[iC+1] * 100)));
      Latex.DrawLatex(0.15, 0.20, "Gen Jet |#eta| < 1.3");
      Latex.DrawLatex(0.15, 0.25, "Gluon");

      PdfFile.AddCanvas(C);

      HWorld.Draw("axis");

      GQM0.SetLineColor(kMagenta + 3);
      GQM1.SetLineColor(kMagenta + 1);
      GQM2.SetLineColor(kMagenta - 4);
      GQM3.SetLineColor(kMagenta - 9);
      GQM0.SetMarkerColor(kMagenta + 3);
      GQM1.SetMarkerColor(kMagenta + 1);
      GQM2.SetMarkerColor(kMagenta - 4);
      GQM3.SetMarkerColor(kMagenta - 9);

      Legend2.Draw();

      GQM0.Draw("p");
      GQM1.Draw("p");
      GQM2.Draw("p");
      GQM3.Draw("p");

      G.Draw("l");

      Latex.DrawLatex(0.15, 0.15, Form("Centrality: %d-%d%%", int(CBins[iC] * 100), int(CBins[iC+1] * 100)));
      Latex.DrawLatex(0.15, 0.20, "Gen Jet |#eta| < 1.3");
      Latex.DrawLatex(0.15, 0.25, "Quark");

      PdfFile.AddCanvas(C);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   File.Close();

   return 0;
}

void AttachPoint(TFile &File, string Name, TGraphAsymmErrors &G, double L, double R, double x)
{
   TF1 Fit("Fit", "gaus");
   ((TH1D *)File.Get(Name.c_str()))->Fit(&Fit, "", "", -0.2, 0.2);
   double Scale = Fit.GetParameter(1);
   double Error = Fit.GetParError(1);

   int N = G.GetN();
   G.SetPoint(N, x, Scale);
   G.SetPointError(N, x - L, R - x, Error, Error);
}





