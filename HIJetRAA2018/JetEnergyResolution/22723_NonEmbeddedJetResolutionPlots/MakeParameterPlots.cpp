#include <iostream>
#include <vector>
using namespace std;

#include "TLegend.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TF1.h"
#include "TGraphErrors.h"
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
   vector<double> YMax = CL.GetDoubleVector("YMax", vector<double>({0.5, 0.5, 0.5}));
   vector<string> DHFileNames = CL.GetStringVector("DHFile", vector<string>());
   vector<string> Labels = CL.GetStringVector("Label", vector<string>());
   vector<string> ExtraText = CL.GetStringVector("Extra", vector<string>());
   string OutputFileName = CL.Get("Output", "Resolution");

   int Colors[] = {kBlack, kRed, kBlue, kCyan, kMagenta, kGreen + 1, kBlack, kRed, kBlue, kCyan, kMagenta};
   int Styles[] = {kSolid, kSolid, kSolid, kSolid, kSolid, kSolid, kDashed, kDashed, kDashed, kDashed, kDashed};
 
   Assert(DHFileNames.size() > 0, "No input DHFile specified.");

   if(Labels.size() < DHFileNames.size())
      Labels.resize(DHFileNames.size(), "X");

   if(YMax.size() < 1)   YMax.push_back(0.2);
   if(YMax.size() < 2)   YMax.push_back(2.0);
   if(YMax.size() < 3)   YMax.push_back(5.0);

   int EtaBinCount = 16;
   double EtaBins[] = {-2, -1.75, -1.5, -1.25, -1, -0.75, -0.5, -0.25, 0, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75, 2};

   int N = DHFileNames.size();

   vector<TGraphErrors> Graphs0(N);
   vector<TGraphErrors> Graphs1(N);
   vector<TGraphErrors> Graphs2(N);
   for(int i = 0; i < N; i++)
   {
      DataHelper DHFile(DHFileNames[i]);

      for(int j = 0; j < EtaBinCount; j++)
      {
         string State = Form("Fit_%.03f_%.03f", EtaBins[j], EtaBins[j+1]);
         double P0 = DHFile[State]["P0"].GetDouble();
         double P1 = DHFile[State]["P1"].GetDouble();
         double P2 = DHFile[State]["P2"].GetDouble();
         double P0Error = DHFile[State]["P0Error"].GetDouble();
         double P1Error = DHFile[State]["P1Error"].GetDouble();
         double P2Error = DHFile[State]["P2Error"].GetDouble();

         int k = Graphs0[i].GetN();
         
         Graphs0[i].SetPoint(k + 0, (EtaBins[j+1] + EtaBins[j]) / 2, P0);
         Graphs0[i].SetPointError(k + 0, (EtaBins[j+1] - EtaBins[j]) / 2, P0Error);
         
         Graphs1[i].SetPoint(k + 0, (EtaBins[j+1] + EtaBins[j]) / 2, P1);
         Graphs1[i].SetPointError(k + 0, (EtaBins[j+1] - EtaBins[j]) / 2, P1Error);
         
         Graphs2[i].SetPoint(k + 0, (EtaBins[j+1] + EtaBins[j]) / 2, P2);
         Graphs2[i].SetPointError(k + 0, (EtaBins[j+1] - EtaBins[j]) / 2, P2Error);
      }
   }

   TCanvas Canvas;

   TH2D HWorld0("HWorld0", ";#eta;#sigma/#mu", 100, XMin, XMax, 100, YMin, YMax[0]);
   TH2D HWorld1("HWorld1", ";#eta;#sigma/#mu", 100, XMin, XMax, 100, YMin, YMax[1]);
   TH2D HWorld2("HWorld2", ";#eta;#sigma/#mu", 100, XMin, XMax, 100, YMin, YMax[2]);
   HWorld0.SetStats(0);
   HWorld1.SetStats(0);
   HWorld2.SetStats(0);

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
      Graphs0[i].SetMarkerColor(Colors[i]);
      Graphs0[i].SetLineColor(Colors[i]);
      Graphs0[i].SetLineStyle(Styles[i]);
      Graphs0[i].SetLineWidth(2);
      Graphs1[i].SetMarkerColor(Colors[i]);
      Graphs1[i].SetLineColor(Colors[i]);
      Graphs1[i].SetLineStyle(Styles[i]);
      Graphs1[i].SetLineWidth(2);
      Graphs2[i].SetMarkerColor(Colors[i]);
      Graphs2[i].SetLineColor(Colors[i]);
      Graphs2[i].SetLineStyle(Styles[i]);
      Graphs2[i].SetLineWidth(2);

      if(i < 5)
         Legend1.AddEntry(&Graphs0[i], Labels[i].c_str(), "lp");
      else
         Legend2.AddEntry(&Graphs0[i], Labels[i].c_str(), "lp");
   }

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);

   HWorld0.Draw("axis");
   for(int i = 0; i < N; i++)
      Graphs0[i].Draw("p");
   Legend1.Draw();
   Legend2.Draw();

   Latex.SetTextAlign(12);
   for(int i = 0; i < (int)ExtraText.size(); i++)
      Latex.DrawLatex(0.15, 0.80 - i * 0.05, ExtraText[i].c_str());

   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.10, 0.92, "#font[62]{CMS} #font[52]{Internal}");

   Canvas.SaveAs((OutputFileName + "_0.pdf").c_str());
   HWorld1.Draw("axis");
   for(int i = 0; i < N; i++)
      Graphs1[i].Draw("p");
   Legend1.Draw();
   Legend2.Draw();

   Latex.SetTextAlign(12);
   for(int i = 0; i < (int)ExtraText.size(); i++)
      Latex.DrawLatex(0.15, 0.80 - i * 0.05, ExtraText[i].c_str());

   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.10, 0.92, "#font[62]{CMS} #font[52]{Internal}");

   Canvas.SaveAs((OutputFileName + "_1.pdf").c_str());

   HWorld2.Draw("axis");
   for(int i = 0; i < N; i++)
      Graphs2[i].Draw("p");
   Legend1.Draw();
   Legend2.Draw();

   Latex.SetTextAlign(12);
   for(int i = 0; i < (int)ExtraText.size(); i++)
      Latex.DrawLatex(0.15, 0.80 - i * 0.05, ExtraText[i].c_str());

   Latex.SetTextAlign(12);
   Latex.DrawLatex(0.10, 0.92, "#font[62]{CMS} #font[52]{Internal}");

   Canvas.SaveAs((OutputFileName + "_2.pdf").c_str());

   return 0;
}


