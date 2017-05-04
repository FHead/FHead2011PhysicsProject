#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main();
void AddPlot(PdfFileHelper &PdfFile, TFile &F1, TFile &F2, string Name);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("PrescaleComparison.pdf");
   PdfFile.AddTextPage("Compare prescaled data to all data");

   TFile F1("Graphs_SD7_Data.root");
   TFile F2("Graphs_SD7_DataPrescale.root");

   for(int i = 0; i <= 3; i++)
      for(int j = 1; j <= 4; j++)
         AddPlot(PdfFile, F1, F2, Form("MassData_%d_%d", i, j));

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TFile &F1, TFile &F2, string Name)
{
   PdfFile.AddTextPage(Name);

   TGraphAsymmErrors *G1 = (TGraphAsymmErrors *)F1.Get(Name.c_str());
   TGraphAsymmErrors *G2 = (TGraphAsymmErrors *)F2.Get(Name.c_str());

   G1->SetLineColor(kBlue);
   G1->SetMarkerColor(kBlue);
   G2->SetLineColor(kRed);
   G2->SetMarkerColor(kRed);

   TCanvas C;

   G1->Draw("ap");
   G2->Draw("p");

   C.SetLogy();

   PdfFile.AddCanvas(C);
}



