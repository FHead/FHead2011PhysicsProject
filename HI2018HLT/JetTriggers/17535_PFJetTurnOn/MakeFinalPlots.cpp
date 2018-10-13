#include <vector>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TGraphAsymmErrors.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TF1.h"

#include "PlotHelper3.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void AddPlot(PdfFileHelper &PdfFile, TFile &File, string Trigger, string Name);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   vector<string> Triggers = CL.GetStringVector("Trigger");

   TFile InputFile(InputFileName.c_str());

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("First trigger turn on");

   for(string Trigger : Triggers)
   {
      AddPlot(PdfFile, InputFile, Trigger, "HJetPT");
      AddPlot(PdfFile, InputFile, Trigger, "HCentralJetPT");
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   InputFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TFile &File, string Trigger, string Name)
{
   TH1D *H1 = (TH1D *)File.Get(Form("%s_%s", Name.c_str(), Trigger.c_str()));
   TH1D *H2 = (TH1D *)File.Get(Form("%s", Name.c_str()));

   if(H1 == NULL || H2 == NULL)
      return;

   PdfFile.AddTextPage(Trigger + " " + Name);

   TCanvas Canvas;

   H1->SetStats(0);
   H2->SetStats(0);
   H1->SetLineColor(kRed);
   H1->SetMarkerColor(kRed);
   H2->SetLineColor(kBlack);
   H2->SetMarkerColor(kBlack);

   H2->Draw();
   H1->Draw("same");

   PdfFile.AddCanvas(Canvas);

   TH2D HWorld("HWorld", ";PT;Efficiency", 100, H1->GetXaxis()->GetBinLowEdge(1), H1->GetXaxis()->GetBinUpEdge(H1->GetNbinsX()), 100, 0, 1.1);
   HWorld.SetStats(0);
   HWorld.Draw("axis");

   TGraphAsymmErrors G;
   G.Divide(H1, H2);
   G.Draw("p");

   TGraph GLine;
   GLine.SetPoint(0, 0, 1);
   GLine.SetPoint(1, 1000, 1);
   GLine.Draw("l");

   TF1 Function("Function", "0.5+0.5*tanh([0]*(x-[1]))", 0, 1000);
   Function.SetParameters(0.08, 100);
   G.Fit(&Function, "N");

   Function.Draw("same");

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.DrawLatex(0.40, 0.25, "Fit to tanh()");
   Latex.DrawLatex(0.40, 0.20, Form("   Width^{-1} = %.03f #pm %.03f", Function.GetParameter(0), Function.GetParError(0)));
   Latex.DrawLatex(0.40, 0.15, Form("   Midpoint = %.03f #pm %.03f", Function.GetParameter(1), Function.GetParError(1)));

   PdfFile.AddCanvas(Canvas);
}


