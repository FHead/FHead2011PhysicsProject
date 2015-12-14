#include <iostream>
#include <vector>
#include <algorithm>

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TSpline.h"
#include "TCanvas.h"

#include "PlotProjection.h"

std::string GetName(std::string Component, std::string Type, std::string Range, bool LogX, bool XWeight)
{
   return "H" + Component + (LogX ? "Log" : "") + (XWeight ? "X" : "") + "_" + Type + "_" + Range;
}

void FillBackgroundGraph(TGraph &Graph, TFile &File, std::string Component, double DURatio)
{
   std::string backgrounds[] = {"CompAu", "CompAd", "CompBu", "CompBd", "CompCu", "CompCd",
      "CompDu", "CompDd", "CompEu", "CompEd", "CompFu", "CompFd"};
   std::vector<std::string> Backgrounds(backgrounds, backgrounds + 12);

   // Get histograms and add them up
   std::vector<TH1D *> IndividualHistogram;
   std::vector<TH1D *> IndividualXHistogram;
   for(int iB = 0; iB < (int)Backgrounds.size(); iB++)
   {
      std::string Name = GetName(Component, Backgrounds[iB], "C3", false, false);
      IndividualHistogram.push_back((TH1D *)File.Get(Name.c_str()));
      
      Name = GetName(Component, Backgrounds[iB], "C3", false, true);
      IndividualXHistogram.push_back((TH1D *)File.Get(Name.c_str()));
   }

   TH1D *HTotal = (TH1D *)IndividualHistogram[0]->Clone("YayClone");
   TH1D *HXTotal = (TH1D *)IndividualXHistogram[0]->Clone("ClonedHistogram");
   for(int iB = 1; iB < (int)Backgrounds.size(); iB++)
   {
      if(iB % 2 == 1)   // Down type
      {
         HTotal->Add(IndividualHistogram[iB], DURatio);
         HXTotal->Add(IndividualXHistogram[iB], DURatio);
      }
      else   // Up type
      {
         HTotal->Add(IndividualHistogram[iB], 1);
         HXTotal->Add(IndividualXHistogram[iB], 1);
      }
   }

   HXTotal->Divide(HTotal);

   // Make splines
   TGraph TemporaryGraph;
   for(int iBin = 1; iBin <= HTotal->GetNbinsX(); iBin++)
   {
      if(HTotal->GetBinContent(iBin) * 1e20 > HTotal->GetMaximum())
         TemporaryGraph.SetPoint(iBin - 1, HXTotal->GetBinContent(iBin), HTotal->GetBinContent(iBin));
      else
         TemporaryGraph.SetPoint(iBin - 1, HXTotal->GetBinCenter(iBin), HTotal->GetBinContent(iBin));
   }

   TSpline3 TemporarySpline("Seems_Like_We_Need_Some_Name_Here", &TemporaryGraph);

   // Translate back into TGraph
   Graph.Set(0);

   double Min = HTotal->GetXaxis()->GetBinLowEdge(1);
   double Max = HTotal->GetXaxis()->GetBinUpEdge(HTotal->GetNbinsX());
   for(int i = 0; i <= 500; i++)
   {
      double X = (Max - Min) / 500 * (i + 0.5) + Min;
      double Value = TemporarySpline.Eval(X);

      Graph.SetPoint(i, X, Value);
   }

   // Cleanup
   delete HTotal;
   delete HXTotal;
}

void FillSignalGraph(TGraph &Graph, TFile &File, std::string Component, std::string Type)
{
   // Get histograms
   std::string Name = GetName(Component, Type, "C3", false, false);
   TH1D *HTotal = (TH1D *)File.Get(Name.c_str())->Clone("YayClone");
   Name = GetName(Component, Type, "C3", false, true);
   TH1D *HXTotal = (TH1D *)File.Get(Name.c_str())->Clone("ClonedHistogram");

   HXTotal->Divide(HTotal);

   // Make splines
   TGraph TemporaryGraph;
   for(int iBin = 1; iBin <= HTotal->GetNbinsX(); iBin++)
   {
      if(HTotal->GetBinContent(iBin) * 1e20 > HTotal->GetMaximum())
         TemporaryGraph.SetPoint(iBin - 1, HXTotal->GetBinContent(iBin), HTotal->GetBinContent(iBin));
      else
         TemporaryGraph.SetPoint(iBin - 1, HXTotal->GetBinCenter(iBin), HTotal->GetBinContent(iBin));
   }

   TSpline3 TemporarySpline("Seems_Like_We_Need_Some_Name_Here", &TemporaryGraph);

   // Translate back into TGraph
   Graph.Set(0);

   double Min = HTotal->GetXaxis()->GetBinLowEdge(1);
   double Max = HTotal->GetXaxis()->GetBinUpEdge(HTotal->GetNbinsX());
   for(int i = 0; i <= 500; i++)
   {
      double X = (Max - Min) / 500 * i + Min;
      double Value = TemporarySpline.Eval(X);

      Graph.SetPoint(i, X, Value);
   }

   // Cleanup
   delete HTotal;
   delete HXTotal;
}

void ScaleGraph(TGraph &Graph, double Factor)
{
   for(int i = 0; i < Graph.GetN(); i++)
   {
      double X, Y;
      Graph.GetPoint(i, X, Y);
      Graph.SetPoint(i, X, Y * Factor);
   }
}

void AddGraph(TGraph &Graph1, TGraph &Graph2, double Factor)
{
   for(int i = 0; i < Graph1.GetN(); i++)
   {
      double X, Y;
      Graph1.GetPoint(i, X, Y);
      Graph1.SetPoint(i, X, Y + Graph2.Eval(X) * Factor);
   }
}

void NormalizeGraph(TGraph &Graph)
{
   double Integral = IntegrateGraph(Graph);
   ScaleGraph(Graph, 1 / Integral);
}

double GraphFindMaximum(TGraph &Graph)
{
   double X, Maximum;
   Graph.GetPoint(0, X, Maximum);

   for(int i = 1; i < Graph.GetN(); i++)
   {
      double Y;
      Graph.GetPoint(i, X, Y);
      if(Y > Maximum)
         Maximum = Y;
   }

   return Maximum;
}

double IntegrateGraph(TGraph &Graph)
{
   double Integral = 0;
   for(int i = 0; i < Graph.GetN() - 1; i++)
   {
      double LowSideX = 0, LowSideY = 0;
      double HighSideX = 0, HighSideY = 0;

      Graph.GetPoint(i, LowSideX, LowSideY);
      Graph.GetPoint(i + 1, HighSideX, HighSideY);

      Integral = Integral + (LowSideY + HighSideY) * (HighSideX - LowSideX) / 2;
   }

   return Integral;
}

void FillToHistogram(TH1D &H, TTree &T, std::string BranchName, std::vector<int> Indices)
{
   double Value;
   T.SetBranchAddress(BranchName.c_str(), &Value);

   std::sort(Indices.begin(), Indices.end());

   for(int i = 0; i < (int)Indices.size(); i++)
   {
      T.GetEntry(Indices[i]);

      H.Fill(Value);
   }
}

void ProduceOverlayPlots_BA1A3(PsFileHelper &PsFile, TH1D *Data, std::string Component,
   TFile &BackgroundFile, TFile &SignalFile, double Fraction, double A1, double A3)
{
   double EventCount = 50;

   TGraph GraphExtSig1, GraphExtSig3, GraphExtSig13, GraphBackground;

   // Get the graphs
   FillBackgroundGraph(GraphBackground, BackgroundFile, Component, 1);
   FillSignalGraph(GraphExtSig1, SignalFile, Component, "ExtSig1");
   FillSignalGraph(GraphExtSig3, SignalFile, Component, "ExtSig3");
   FillSignalGraph(GraphExtSig13, SignalFile, Component, "ExtSig13");

   // Deal with normalizations
   ScaleGraph(GraphExtSig1, A1 * A1);
   ScaleGraph(GraphExtSig3, A3 * A3);
   ScaleGraph(GraphExtSig13, A1 * A3);

   double SignalIntegral = IntegrateGraph(GraphExtSig1) + IntegrateGraph(GraphExtSig3) + IntegrateGraph(GraphExtSig13);

   ScaleGraph(GraphExtSig1, 1 / SignalIntegral);
   ScaleGraph(GraphExtSig3, 1 / SignalIntegral);
   ScaleGraph(GraphExtSig13, 1 / SignalIntegral);

   ScaleGraph(GraphExtSig1, 1 - Fraction);
   ScaleGraph(GraphExtSig3, 1 - Fraction);
   ScaleGraph(GraphExtSig13, 1 - Fraction);

   NormalizeGraph(GraphBackground);
   ScaleGraph(GraphBackground, Fraction);

   ScaleGraph(GraphExtSig1, EventCount);
   ScaleGraph(GraphExtSig3, EventCount);
   ScaleGraph(GraphExtSig13, EventCount);
   ScaleGraph(GraphBackground, EventCount);

   // Stack them up
   AddGraph(GraphExtSig1, GraphExtSig3);
   AddGraph(GraphExtSig1, GraphExtSig13);
   AddGraph(GraphExtSig1, GraphBackground);
   AddGraph(GraphExtSig3, GraphExtSig13);
   AddGraph(GraphExtSig3, GraphBackground);
   AddGraph(GraphExtSig13, GraphBackground);

   // Setup some colors
   GraphExtSig1.SetFillColor(kBlue);
   GraphExtSig3.SetFillColor(kYellow - 7);
   GraphExtSig13.SetFillColor(kRed);
   GraphBackground.SetFillColor(kCyan);
   GraphBackground.SetFillStyle(3544);

   // Setup the frame-setting histogram
   double Left, Right, Dummy;
   GraphExtSig1.GetPoint(0, Left, Dummy);
   GraphExtSig1.GetPoint(GraphExtSig1.GetN() - 1, Right, Dummy);
   TH1D HWorld("HWorld", "", 10, Left, Right);
   HWorld.SetStats(0);
   double MaximumOnGraph = GraphFindMaximum(GraphExtSig1);

   // Plot them onto a canvas
   TCanvas Canvas;

   HWorld.SetMaximum(MaximumOnGraph * 20);
   HWorld.SetMinimum(MaximumOnGraph / 1e4);
   HWorld.Draw();
   GraphExtSig1.Draw("B");
   GraphExtSig3.Draw("B");
   GraphExtSig13.Draw("B");
   GraphBackground.Draw("B");

   if(Data != NULL)
      Data->Draw("same error");

   Canvas.SetLogy(true);

   PsFile.AddCanvas(Canvas);

   HWorld.SetMaximum(MaximumOnGraph * 1.5);
   HWorld.SetMinimum(0);
   Canvas.SetLogy(false);

   PsFile.AddCanvas(Canvas);
}






