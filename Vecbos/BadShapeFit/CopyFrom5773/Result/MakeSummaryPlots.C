#include <string>
using namespace std;

#include "TAxis.h"
#include "TChain.h"
#include "TGraphErrors.h"
#include "TCanvas.h"

void MakeSummaryPlots(string filename, string namebase);
void MakeGenericPlot1(string filename, string X, string Y, string EY, string OutputBase,
   string title = "", string xaxis = "", string yaxis = "");
void MakeGenericPlot4(string filename, string X, string Y, string EY, string OutputBase,
   string title = "", string xaxis = "", string yaxis = "");

void MakeSummaryPlots(string filename, string namebase)
{
   MakeGenericPlot1(filename, "ParameterValue", "ExponentMean", "ExponentSigma",
      "Plots/" + namebase + "_Exponent", "Exponent", namebase, "Exponent");

   MakeGenericPlot4(filename, "ParameterValue", "MeanRelativeSignalYield", "SigmaRelativeSignalYield",
      "Plots/" + namebase + "_RelativeSignalYield", "Relative signal yield", namebase, "Relative yield");
   MakeGenericPlot4(filename, "ParameterValue", "MeanRelativeSignalYieldGood", "SigmaRelativeSignalYieldGood",
      "Plots/" + namebase + "_RelativeSignalYieldGood", "Relative signal yield", namebase, "Relative yield");
   MakeGenericPlot4(filename, "ParameterValue", "FitSuccessRate", "",
      "Plots/" + namebase + "_FitSuccessRate", "Success rate", namebase, "Success rate");
}

void MakeGenericPlot1(string filename, string X, string Y, string EY, string OutputBase,
   string title, string xaxis, string yaxis)
{
   TChain chain("Tree", "Tree");
   chain.AddFile(filename.c_str());

   double XBranch;
   double YBranch;
   double EYBranch;

   chain.SetBranchAddress(X.c_str(), &XBranch);
   chain.SetBranchAddress(Y.c_str(), &YBranch);
   if(EY != "")
      chain.SetBranchAddress(EY.c_str(), &EYBranch);

   TGraphErrors Graph;
   Graph.SetNameTitle("OutputBase", title.c_str());

   int Entries = chain.GetEntries();
   for(int i = 0; i < Entries; i++)
   {
      chain.GetEntry(i);

      Graph.SetPoint(i, XBranch, YBranch);
      Graph.SetPointError(i, 0, EYBranch);
   }

   Graph.GetXaxis()->SetTitle(xaxis.c_str());
   Graph.GetYaxis()->SetTitle(yaxis.c_str());

   Graph.SetMarkerStyle(20);
   Graph.SetLineWidth(2);

   TCanvas Canvas("C", "C", 0, 0, 1024, 768);

   Graph.Draw("ap");

   Canvas.SaveAs((OutputBase + ".png").c_str());
   Canvas.SaveAs((OutputBase + ".C").c_str());
   Canvas.SaveAs((OutputBase + ".eps").c_str());
}

void MakeGenericPlot4(string filename, string X, string Y, string EY, string OutputBase,
   string title, string xaxis, string yaxis)
{
   TChain chain("Tree", "Tree");
   chain.AddFile(filename.c_str());

   double XBranch = 0;
   double YBranch[4] = {0};
   double EYBranch[4] = {0};

   chain.SetBranchAddress(X.c_str(), &XBranch);
   chain.SetBranchAddress(Y.c_str(), &YBranch);
   if(EY != "")
      chain.SetBranchAddress(EY.c_str(), &EYBranch);

   TGraphErrors Graph[4];

   for(int i = 0; i < 4; i++)
      Graph[i].SetNameTitle("OutputBase", title.c_str());

   int Entries = chain.GetEntries();
   for(int i = 0; i < Entries; i++)
   {
      chain.GetEntry(i);

      for(int j = 0; j < 4; j++)
      {
         Graph[j].SetPoint(i, XBranch, YBranch[j]);
         Graph[j].SetPointError(i, 0, EYBranch[j]);
      }
   }

   for(int i = 0; i < 4; i++)
   {
      Graph[i].GetXaxis()->SetTitle(xaxis.c_str());
      Graph[i].GetYaxis()->SetTitle(yaxis.c_str());

      Graph[i].SetMarkerColor(i + 1);
      Graph[i].SetMarkerStyle(20);
      Graph[i].SetLineColor(i + 1);
      Graph[i].SetLineWidth(2);
   }

   TCanvas Canvas("C", "C", 0, 0, 1024, 768);

   Graph[0].Draw("ap");
   Graph[1].Draw("p");
   Graph[2].Draw("p");
   Graph[3].Draw("p");

   Canvas.SaveAs((OutputBase + ".png").c_str());
   Canvas.SaveAs((OutputBase + ".C").c_str());
   Canvas.SaveAs((OutputBase + ".eps").c_str());

   for(int i = 0; i < 4; i++)
   {
      Graph[i].SetTitle(Form("%s, >= %d jets", title.c_str(), i + 1));
      Graph[i].Draw("ap");

      Canvas.SaveAs(Form("%s_%d.png", OutputBase.c_str(), i + 1));
      Canvas.SaveAs(Form("%s_%d.eps", OutputBase.c_str(), i + 1));
      Canvas.SaveAs(Form("%s_%d.C", OutputBase.c_str(), i + 1));
   }
}


