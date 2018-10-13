#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TLegend.h"

#include "PlotHelper3.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void AddPlot(PdfFileHelper &PdfFile, TFile &File, vector<string> Triggers, vector<string> Labels, string Name);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   vector<string> Triggers = CL.GetStringVector("Trigger");
   vector<string> Labels = CL.GetStringVector("Label");
   string NameBase = CL.Get("Name");

   TFile InputFile(InputFileName.c_str());

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Trigger turn-on");

   AddPlot(PdfFile, InputFile, Triggers, Labels, NameBase + "");
   AddPlot(PdfFile, InputFile, Triggers, Labels, NameBase + "C0");
   AddPlot(PdfFile, InputFile, Triggers, Labels, NameBase + "C1");
   AddPlot(PdfFile, InputFile, Triggers, Labels, NameBase + "C2");
   AddPlot(PdfFile, InputFile, Triggers, Labels, NameBase + "C3");
   AddPlot(PdfFile, InputFile, Triggers, Labels, NameBase + "C4");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   InputFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TFile &File, vector<string> Triggers, vector<string> Labels, string Name)
{
   int Colors[] = {kBlack, kRed, kBlue, kYellow + 3, kGreen, kPink, kGreen + 3, kMagenta, kBlack};

   TH1D *HBase = (TH1D *)File.Get(Form("%s", Name.c_str()));
   if(HBase == NULL)
      return;

   TLegend Legend(0.6, 0.2, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);

   vector<TGraphAsymmErrors> G(Triggers.size());
   for(int i = 0; i < (int)Triggers.size(); i++)
   {
      string Trigger = Triggers[i];
      TH1D *H = (TH1D *)File.Get(Form("%s_%s", Name.c_str(), Trigger.c_str()));
      G[i].Divide(H, HBase);

      G[i].SetMarkerColor(Colors[i]);
      G[i].SetLineColor(Colors[i]);

      Legend.AddEntry(&G[i], Labels[i].c_str(), "pl");
   }

   TCanvas Canvas;

   double XMin = HBase->GetXaxis()->GetBinLowEdge(1);
   double XMax = HBase->GetXaxis()->GetBinUpEdge(HBase->GetNbinsX());
   TH2D HWorld("HWorld", ";Offline p_{T};Efficiency", 100, XMin, XMax, 100, 0, 1.1);
   HWorld.SetStats(0);
   HWorld.Draw("axis");

   TGraph GLine;
   GLine.SetPoint(0, 0, 1);
   GLine.SetPoint(1, 1000, 1);
   GLine.Draw("l");

   for(int i = 0; i < (int)Triggers.size(); i++)
      G[i].Draw("p");

   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
}


