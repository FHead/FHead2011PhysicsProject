#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "TLatex.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile File("ToyInput.root");

   TLatex Latex;
   Latex.SetTextSize(0.035);
   Latex.SetNDC();

   TCanvas C;

   C.Divide(4, 4);

   C.cd(1);
   ((TH1D *)File.Get("MethodT_50_0_Data"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 50 GeV");
   Latex.DrawLatex(0.15, 0.75, "data");
   C.cd(2);
   ((TH1D *)File.Get("MethodT_75_0_Data"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 75 GeV");
   Latex.DrawLatex(0.15, 0.75, "data");
   C.cd(3);
   ((TH1D *)File.Get("MethodT_100_0_Data"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 100 GeV");
   Latex.DrawLatex(0.15, 0.75, "data");
   C.cd(4);
   ((TH1D *)File.Get("MethodT_120_0_Data"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 120 GeV");
   Latex.DrawLatex(0.15, 0.75, "data");
   C.cd(5);
   ((TH1D *)File.Get("MethodT_140_0_Data"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 140 GeV");
   Latex.DrawLatex(0.15, 0.75, "data");
   C.cd(6);
   ((TH1D *)File.Get("MethodT_160_0_Data"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 160 GeV");
   Latex.DrawLatex(0.15, 0.75, "data");
   C.cd(7);
   ((TH1D *)File.Get("MethodT_180_0_Data"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 180 GeV");
   Latex.DrawLatex(0.15, 0.75, "data");
   C.cd(8);
   ((TH1D *)File.Get("MethodT_200_0_Data"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 200 GeV");
   Latex.DrawLatex(0.15, 0.75, "data");
   C.cd(9);
   ((TH1D *)File.Get("MethodT_50_0_MC"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 50 GeV");
   Latex.DrawLatex(0.15, 0.75, "MC");
   C.cd(10);
   ((TH1D *)File.Get("MethodT_75_0_MC"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 75 GeV");
   Latex.DrawLatex(0.15, 0.75, "MC");
   C.cd(11);
   ((TH1D *)File.Get("MethodT_100_0_MC"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 100 GeV");
   Latex.DrawLatex(0.15, 0.75, "MC");
   C.cd(12);
   ((TH1D *)File.Get("MethodT_120_0_MC"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 120 GeV");
   Latex.DrawLatex(0.15, 0.75, "MC");
   C.cd(13);
   ((TH1D *)File.Get("MethodT_140_0_MC"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 140 GeV");
   Latex.DrawLatex(0.15, 0.75, "MC");
   C.cd(14);
   ((TH1D *)File.Get("MethodT_160_0_MC"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 160 GeV");
   Latex.DrawLatex(0.15, 0.75, "MC");
   C.cd(15);
   ((TH1D *)File.Get("MethodT_180_0_MC"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 180 GeV");
   Latex.DrawLatex(0.15, 0.75, "MC");
   C.cd(16);
   ((TH1D *)File.Get("MethodT_200_0_MC"))->Draw();
   Latex.DrawLatex(0.15, 0.80, "<p_{T}> = 200 GeV");
   Latex.DrawLatex(0.15, 0.75, "MC");

   C.SaveAs("Input.pdf");

   File.Close();

   return 0;
}




