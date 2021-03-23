#include <iostream>
#include <vector>
using namespace std;

#include "TLegend.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLatex.h"

#include "CustomAssert.h"
#include "CommandLine.h"
#include "DataHelper.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   double XMin = CL.GetDouble("XMin", -2);
   double XMax = CL.GetDouble("XMax", 2);
   double YMin = CL.GetDouble("YMin", 0);
   double YMax = CL.GetDouble("YMax", 1);
   double JetPT = CL.GetDouble("JetPT", 100);
   vector<string> DHFileNames = CL.GetStringVector("DHFile", vector<string>());
   vector<string> Labels = CL.GetStringVector("Label", vector<string>());
   vector<string> ExtraText = CL.GetStringVector("Extra", vector<string>());
   string OutputFileName = CL.Get("Output", "Resolution.pdf");

   int Colors[] = {kBlack, kRed, kBlue, kCyan, kMagenta, kGreen + 1, kBlack, kRed, kBlue, kCyan, kMagenta};
   int Styles[] = {kSolid, kSolid, kSolid, kSolid, kSolid, kSolid, kDashed, kDashed, kDashed, kDashed, kDashed};
 
   Assert(DHFileNames.size() > 0, "No input DHFile specified.");

   if(Labels.size() < DHFileNames.size())
      Labels.resize(DHFileNames.size(), "X");

   int EtaBinCount = 16;
   double EtaBins[] = {-2, -1.75, -1.5, -1.25, -1, -0.75, -0.5, -0.25, 0, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75, 2};

   int N = DHFileNames.size();

   vector<TGraph> Graphs(N);
   for(int i = 0; i < N; i++)
   {
      DataHelper DHFile(DHFileNames[i]);

      for(int j = 0; j < EtaBinCount; j++)
      {
         string State = Form("Fit_%.03f_%.03f", EtaBins[j], EtaBins[j+1]);
         double P0 = DHFile[State]["P0"].GetDouble();
         double P1 = DHFile[State]["P1"].GetDouble();
         double P2 = DHFile[State]["P2"].GetDouble();

         double Resolution = sqrt(P0 * P0 + P1 * P1 / JetPT + P2 * P2 / JetPT / JetPT);

         Graphs[i].SetPoint(Graphs[i].GetN(), EtaBins[j], Resolution);
         Graphs[i].SetPoint(Graphs[i].GetN(), EtaBins[j+1], Resolution);
      }
   }

   TCanvas Canvas;

   TH2D HWorld("HWorld", ";#eta;#sigma/#mu", 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   HWorld.Draw("axis");

   TLegend Legend1(0.35, 0.85, 0.65, 0.85 - 0.05 * (N > 5 ? 5 : N));
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.035);
   Legend1.SetBorderSize(0);
   Legend1.SetFillStyle(0);

   TLegend Legend2(0.55, 0.85, 0.85, 0.85 - 0.05 * (N > 5 ? N - 5 : 1));
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetBorderSize(0);
   Legend2.SetFillStyle(0);

   for(int i = 0; i < N; i++)
   {
      Graphs[i].SetLineColor(Colors[i]);
      Graphs[i].SetLineStyle(Styles[i]);
      Graphs[i].SetLineWidth(2);
      Graphs[i].Draw("l");

      if(i < 5)
         Legend1.AddEntry(&Graphs[i], Labels[i].c_str(), "l");
      else
         Legend2.AddEntry(&Graphs[i], Labels[i].c_str(), "l");
   }

   Legend1.Draw();
   Legend2.Draw();

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(12);
   for(int i = 0; i < (int)ExtraText.size(); i++)
      Latex.DrawLatex(0.15, 0.15 + (ExtraText.size() - i) * 0.05, ExtraText[i].c_str());

   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.10, 0.92, "#font[62]{CMS} #font[52]{Internal}");

   Canvas.SaveAs(OutputFileName.c_str());

   return 0;
}


