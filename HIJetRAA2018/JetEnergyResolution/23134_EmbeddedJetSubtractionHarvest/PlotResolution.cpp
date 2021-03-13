#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "DataHelper.h"
#include "CustomAssert.h"

enum ScanType {ScanPT, ScanEta, ScanDPhi, ScanCentrality};
enum PlotType {PlotMean, PlotRMS, PlotGausMean, PlotGausSigma, PlotNone};

struct Ranges;
int main(int argc, char *argv[]);
TGraphAsymmErrors Transcribe(string DHFileName, ScanType Type, string Restriction, PlotType Plot);
Ranges Deduce(string DHFileName, ScanType Type, string Restriction, Ranges Result);
vector<string> Split(string S);

struct Ranges
{
   double PTMin, PTMax;
   double CentralityMin, CentralityMax;
   double EtaMin, EtaMax;
   double DPhiMin, DPhiMax;
};

int main(int argc, char *argv[])
{
   SetThesisStyle();

   int Color[6] = {-1, -1, -1, -1, -1, -1};
   Color[0] = TColor::GetColor("#E74C3C");
   Color[1] = TColor::GetColor("#3498DB");
   Color[2] = TColor::GetColor("#D1A40A");
   Color[3] = TColor::GetColor("#1EAC61");
   Color[4] = TColor::GetColor("#7F7F7F");
   Color[5] = kMagenta;

   CommandLine CL(argc, argv);

   string Title = CL.Get("title", "deduce");
   double XMin = CL.GetDouble("xmin", 0);
   double XMax = CL.GetDouble("xmax", 100);
   double YMin = CL.GetDouble("ymin", 0);
   double YMax = CL.GetDouble("ymax", 2);

   string Scan = CL.Get("scan");
   ScanType Type = ScanType::ScanPT;
   if(Scan == "PT")           Type = ScanType::ScanPT;
   if(Scan == "Eta")          Type = ScanType::ScanEta;
   if(Scan == "DPhi")         Type = ScanType::ScanDPhi;
   if(Scan == "Centrality")   Type = ScanType::ScanCentrality;
   
   vector<string> Input = CL.GetStringVector("input");
   vector<string> Restriction = CL.GetStringVector("restriction");
   vector<string> Label = CL.GetStringVector("label");
   vector<string> ToPlot = CL.GetStringVector("plot");

   if(Restriction.size() == 1 && Input.size() > 1)
      Restriction.insert(Restriction.end(), Input.size() - 1, Restriction[0]);
   if(ToPlot.size() == 1 && Input.size() > 1)
      ToPlot.insert(ToPlot.end(), Input.size() - 1, ToPlot[0]);

   Assert(Input.size() == Restriction.size(), "Restriction size not the same as curve count");
   Assert(Input.size() == Label.size(), "Label size not the same as curve count");
   Assert(Input.size() == ToPlot.size(), "Plot type size not the same as curve count");

   vector<PlotType> Plot;
   for(int i = 0; i < (int)ToPlot.size(); i++)
   {
      if(ToPlot[i] == "Mean")             Plot.push_back(PlotType::PlotMean);
      else if(ToPlot[i] == "RMS")         Plot.push_back(PlotType::PlotRMS);
      else if(ToPlot[i] == "GausMean")    Plot.push_back(PlotType::PlotGausMean);
      else if(ToPlot[i] == "GausSigma")   Plot.push_back(PlotType::PlotGausSigma);
      else                                Plot.push_back(PlotType::PlotNone);
   }
   
   vector<TGraphAsymmErrors> G;
   for(int i = 0; i < (int)Input.size(); i++)
   {
      G.push_back(Transcribe(Input[i], Type, Restriction[i], Plot[i]));

      G[i].SetMarkerStyle(20);
      G[i].SetMarkerColor(Color[i]);
      G[i].SetLineColor(Color[i]);
      G[i].SetLineWidth(2);
   }

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextSize(0.035);
   for(int i = 0; i < (int)Input.size(); i++)
      Legend.AddEntry(&G[i], Label[i].c_str(), "pl");

   string OutputBase = CL.Get("output", "Plot");
 
   TCanvas Canvas;

   TH2D HWorld("HWorld", Title.c_str(), 100, XMin, XMax, 100, YMin, YMax);
   HWorld.SetStats(0);

   if(Title == "deduce")
   {
      Ranges Range;
      Range.PTMin = 9999;
      Range.PTMax = -9999;
      Range.EtaMin = 9999;
      Range.EtaMax = -9999;
      Range.CentralityMin = 9999;
      Range.CentralityMax = -9999;
      Range.DPhiMin = 9999;
      Range.DPhiMax = -9999;
   
      for(int i = 0; i < (int)Input.size(); i++)
         Range = Deduce(Input[i], Type, Restriction[i], Range);

      if(Type == ScanType::ScanPT)
         Title = Form("eta = [%.03f, %.03f], %d-%d%%", Range.EtaMin, Range.EtaMax, (int)(Range.CentralityMin * 100), (int)(Range.CentralityMax * 100));
      else if(Type == ScanType::ScanEta)
         Title = Form("PT = [%.0f, %.0f], %2d-%2d%%", Range.PTMin, Range.PTMax, (int)(Range.CentralityMin * 100), (int)(Range.CentralityMax * 100));
      else if(Type == ScanType::ScanCentrality)
         Title = Form("PT = [%.0f, %.0f], eta = [%.03f, %.03f]", Range.PTMin, Range.PTMax, Range.EtaMin, Range.EtaMax);
      else if(Type == ScanType::ScanDPhi)
         Title = Form("PT = [%.0f, %.0f], eta = [%.03f, %.03f], %2d-%2d%%", Range.PTMin, Range.PTMax, Range.EtaMin, Range.EtaMax, (int)(Range.CentralityMin * 100), (int)(Range.CentralityMax * 100));

      HWorld.SetTitle(Title.c_str());

      if(Type == ScanType::ScanPT)
         HWorld.GetXaxis()->SetTitle("p_{T}");
      if(Type == ScanType::ScanEta)
         HWorld.GetXaxis()->SetTitle("#eta");
      if(Type == ScanType::ScanCentrality)
         HWorld.GetXaxis()->SetTitle("Centrality (%)");
      if(Type == ScanType::ScanDPhi)
         HWorld.GetXaxis()->SetTitle("d#phi");

      if(Plot[0] == PlotType::PlotMean)        HWorld.GetYaxis()->SetTitle("Mean");
      if(Plot[0] == PlotType::PlotRMS)         HWorld.GetYaxis()->SetTitle("RMS");
      if(Plot[0] == PlotType::PlotGausMean)    HWorld.GetYaxis()->SetTitle("GausMean");
      if(Plot[0] == PlotType::PlotGausSigma)   HWorld.GetYaxis()->SetTitle("GausSigma");
   }

   HWorld.Draw("axis");

   for(int i = 0; i < (int)Input.size(); i++)
      G[i].Draw("p");

   Legend.Draw();

   if(Type == ScanType::ScanPT)
      Canvas.SetLogx();

   Canvas.SaveAs((OutputBase + ".pdf").c_str());
   
   return 0;
}

TGraphAsymmErrors Transcribe(string DHFileName, ScanType Type, string Restriction, PlotType Plot)
{
   vector<string> Restrictions = Split(Restriction);

   string Prefix = "ScanNone";
   if(Type == ScanType::ScanPT)           Prefix = "PTScan";
   if(Type == ScanType::ScanEta)          Prefix = "EtaScan";
   if(Type == ScanType::ScanDPhi)         Prefix = "DPhiScan";
   if(Type == ScanType::ScanCentrality)   Prefix = "CentralityScan";

   TGraphAsymmErrors G;

   DataHelper DHFile(DHFileName);
   vector<string> States = DHFile.GetListOfKeys();
   for(string State : States)
   {
      string DressedState = State + "_";

      if(DressedState.find(Prefix + "_") != 0)   // we want the right prefix
         continue;

      bool WrongBin = false;
      for(string R : Restrictions)
         if(DressedState.find("_" + R + "_") == string::npos)
            WrongBin = true;
      if(WrongBin == true)
         continue;

      double XMin, XMax;
      if(Type == ScanType::ScanPT)
      {
         XMin = DHFile[State]["PTMin"].GetDouble();
         XMax = DHFile[State]["PTMax"].GetDouble();
      }
      else if(Type == ScanType::ScanEta)
      {
         XMin = DHFile[State]["EtaMin"].GetDouble();
         XMax = DHFile[State]["EtaMax"].GetDouble();
      }
      else if(Type == ScanType::ScanDPhi)
      {
         XMin = DHFile[State]["DPhiMin"].GetDouble();
         XMax = DHFile[State]["DPhiMax"].GetDouble();
      }
      else if(Type == ScanType::ScanCentrality)
      {
         XMin = DHFile[State]["CentralityMin"].GetDouble();
         XMax = DHFile[State]["CentralityMax"].GetDouble();
      }

      double Y, EY;
      if(Plot == PlotType::PlotMean)
      {
         Y = DHFile[State]["Mean"].GetDouble();
         EY = DHFile[State]["MeanError"].GetDouble();
      }
      else if(Plot == PlotType::PlotRMS)
      {
         Y = DHFile[State]["RMS"].GetDouble();
         EY = DHFile[State]["RMSError"].GetDouble();
      }
      else if(Plot == PlotType::PlotGausMean)
      {
         Y = DHFile[State]["P1"].GetDouble();
         EY = DHFile[State]["P1Error"].GetDouble();
      }
      else if(Plot == PlotType::PlotGausSigma)
      {
         Y = DHFile[State]["P2"].GetDouble();
         EY = DHFile[State]["P2Error"].GetDouble();
      }
      
      int N = G.GetN();
      G.SetPoint(N, (XMax + XMin) / 2, Y);
      G.SetPointError(N, (XMax - XMin) / 2, (XMax - XMin) / 2, EY, EY);
   }

   G.Sort();

   return G;
}

Ranges Deduce(string DHFileName, ScanType Type, string Restriction, Ranges Result)
{
   vector<string> Restrictions = Split(Restriction);

   string Prefix = "ScanNone";
   if(Type == ScanType::ScanPT)           Prefix = "PTScan";
   if(Type == ScanType::ScanEta)          Prefix = "EtaScan";
   if(Type == ScanType::ScanDPhi)         Prefix = "DPhiScan";
   if(Type == ScanType::ScanCentrality)   Prefix = "CentralityScan";

   DataHelper DHFile(DHFileName);
   vector<string> States = DHFile.GetListOfKeys();
   for(string State : States)
   {
      string DressedState = State + "_";

      if(DressedState.find(Prefix + "_") != 0)   // we want the right prefix
         continue;

      bool WrongBin = false;
      for(string R : Restrictions)
         if(DressedState.find("_" + R + "_") == string::npos)
            WrongBin = true;
      if(WrongBin == true)
         continue;

      Result.PTMin = min(Result.PTMin, DHFile[State]["PTMin"].GetDouble());
      Result.PTMax = max(Result.PTMax, DHFile[State]["PTMax"].GetDouble());
      Result.EtaMin = min(Result.EtaMin, DHFile[State]["EtaMin"].GetDouble());
      Result.EtaMax = max(Result.EtaMax, DHFile[State]["EtaMax"].GetDouble());
      Result.CentralityMin = min(Result.CentralityMin, DHFile[State]["CentralityMin"].GetDouble());
      Result.CentralityMax = max(Result.CentralityMax, DHFile[State]["CentralityMax"].GetDouble());
      Result.DPhiMin = min(Result.DPhiMin, DHFile[State]["DPhiMin"].GetDouble());
      Result.DPhiMax = max(Result.DPhiMax, DHFile[State]["DPhiMax"].GetDouble());
   }

   return Result;
}

vector<string> Split(string S)
{
   return CommandLine::Parse(S, '+');
}



