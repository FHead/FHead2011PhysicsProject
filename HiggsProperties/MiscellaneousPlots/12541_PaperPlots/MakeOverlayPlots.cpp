#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLegend.h"
#include "TGraph.h"

int main(int argc, char *argv[]);
void CompareOnePlot(TFile &FGen, TFile &FReco, int Size, int Component, string Model, bool DoO);

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " GenFile RecoFile Model" << endl;
      return -1;
   }

   string Model = "11";
   if(string(argv[3]) == "16")
      Model = "16";
   if(string(argv[3]) == "31")
      Model = "31";
   if(string(argv[3]) == "36")
      Model = "36";

   cout << Model << endl;

   TFile FGen(argv[1]);
   TFile FReco(argv[2]);

   for(int iS = 1; iS <= 7; iS++)
   {
      for(int iC = 1; iC <= 8; iC++)
      {
         CompareOnePlot(FGen, FReco, iS, iC, Model, false);
         if(iC >= 2 && iC <= 7)
            CompareOnePlot(FGen, FReco, iS, iC, Model, true);
      }
   }

   FReco.Close();
   FGen.Close();

   return 0;
}

void CompareOnePlot(TFile &FGen, TFile &FReco, int Size, int Component, string Model, bool DoO)
{
   string Labels[] = {"R_{1}^{ZZ}", "R_{2}^{ZZ}", "R_{3}^{ZZ}", "R_{2}^{Z#gamma}", "R_{3}^{Z#gamma}",
      "R_{2}^{#gamma#gamma}", "R_{3}^{#gamma#gamma}", "F_{B}"};

   string ID2 = Form("H_%s_NN_Y_%d_%d", (DoO ? "O" : ""), Size, Component);
   string ID3 = Form("H_%s_YY_Y_%d_%d", (DoO ? "O" : ""), Size, Component);

   double TrueValue11N[] = {1, 0, 0, 0, 0, 0, 0, 0.375};
   double TrueValue16N[] = {0.15555843629401253, 0.5988999797319482, 0.7855701032847632, 0, 0, 0, 0, 0.375};
   double TrueValue11O[] = {-1, 0, 0, 0, 0, 0, 0, -1};
   double TrueValue16O[] = {-1, 3.85, 5.05, 0, 0, 0, 0, -1};

   double *TrueValue = TrueValue11N;
   if(DoO == false && (Model == "11" || Model == "31"))   TrueValue = TrueValue11N;
   if(DoO == false && (Model == "16" || Model == "36"))   TrueValue = TrueValue16N;
   if(DoO == true && (Model == "11" || Model == "31"))   TrueValue = TrueValue11O;
   if(DoO == true && (Model == "16" || Model == "36"))   TrueValue = TrueValue16O;

   TH1D *H2 = (TH1D *)FReco.Get(ID2.c_str());
   TH1D *H3 = (TH1D *)FReco.Get(ID3.c_str());

   if(H2 == NULL || H3 == NULL)
      return;

   H2->Rebin(5);
   H3->Rebin(5);

   H2->Scale(1 / H2->Integral());
   H3->Scale(1 / H3->Integral());

   H2->SetLineWidth(3);
   H3->SetLineWidth(2);

   H2->SetLineColor(kGreen - 3);
   H3->SetLineColor(kRed);

   double Max = 0;
   if(Max < H2->GetMaximum())   Max = H2->GetMaximum();
   if(Max < H3->GetMaximum())   Max = H3->GetMaximum();

   TGraph G;
   G.SetLineWidth(3);
   G.SetLineStyle(10);
   G.SetPoint(0, TrueValue[Component-1], 0);
   G.SetPoint(1, TrueValue[Component-1], Max * 2);

   TH1D HWorld("HWorld", "", H2->GetNbinsX(), H2->GetXaxis()->GetBinLowEdge(1),
      H2->GetXaxis()->GetBinUpEdge(H2->GetNbinsX()));
   HWorld.SetStats(0);
   if(DoO == true)
      HWorld.SetMaximum(Max * 1.1);
   else
      HWorld.SetMaximum(Max * 1.4);
   
   HWorld.GetXaxis()->SetTitle(Labels[Component-1].c_str());
   HWorld.GetYaxis()->SetTitle("a.u.");
   HWorld.GetXaxis()->SetTitleOffset(1.25);
   HWorld.GetYaxis()->SetTitleOffset(1.6);
   HWorld.GetXaxis()->CenterTitle(true);
   HWorld.GetYaxis()->CenterTitle(true);

   TCanvas C("C", "C", 1024, 1024);
   C.SetLeftMargin(0.15);
   C.SetBottomMargin(0.15);

   HWorld.Draw();
   H2->Draw("same");
   H3->Draw("same");

   G.Draw("l");

   double LXMin = 0.5, LXMax = 0.8, LYMin = 0.6, LYMax = 0.8;
   if(Component != 8)
      LXMin = 0.2, LXMax = 0.5, LYMin = 0.7, LYMax = 0.85;
   TLegend Legend(LXMin, LYMin, LXMax, LYMax);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(H2, "No systematics", "l");
   Legend.AddEntry(H3, "With systematics", "l");
   Legend.Draw();

   C.SaveAs(Form("Plots/PlotOverlay_%s_%s_%d_%d.png", Model.c_str(), (DoO ? "O" : ""), Size, Component));
   C.SaveAs(Form("Plots/PlotOverlay_%s_%s_%d_%d.C",   Model.c_str(), (DoO ? "O" : ""), Size, Component));
   C.SaveAs(Form("Plots/PlotOverlay_%s_%s_%d_%d.eps", Model.c_str(), (DoO ? "O" : ""), Size, Component));
   C.SaveAs(Form("Plots/PlotOverlay_%s_%s_%d_%d.pdf", Model.c_str(), (DoO ? "O" : ""), Size, Component));
}










