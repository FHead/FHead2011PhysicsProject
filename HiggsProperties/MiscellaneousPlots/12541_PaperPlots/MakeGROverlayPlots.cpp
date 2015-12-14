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

   string ID1 = Form("H_%s_NN_N_%d_%d", (DoO ? "O" : ""), Size, Component);
   string ID2 = Form("H_%s_NN_N_%d_%d", (DoO ? "O" : ""), Size, Component);

   double TrueValue11N[] = {1, 0, 0, 0, 0, 0, 0, 0.375};
   double TrueValue16N[] = {0.15555843629401253, 0.5988999797319482, 0.7855701032847632, 0, 0, 0, 0, 0.375};
   double TrueValue11O[] = {-1, 0, 0, 0, 0, 0, 0, -1};
   double TrueValue16O[] = {-1, 3.85, 5.05, 0, 0, 0, 0, -1};

   double *TrueValue = TrueValue11N;
   if(DoO == false && (Model == "11" || Model == "31"))   TrueValue = TrueValue11N;
   if(DoO == false && (Model == "16" || Model == "36"))   TrueValue = TrueValue16N;
   if(DoO == true && (Model == "11" || Model == "31"))   TrueValue = TrueValue11O;
   if(DoO == true && (Model == "16" || Model == "36"))   TrueValue = TrueValue16O;

   TH1D *H1 = (TH1D *)FGen.Get(ID1.c_str());
   TH1D *H2 = (TH1D *)FReco.Get(ID2.c_str());

   if(H1 == NULL || H2 == NULL)
      return;

   H1->Rebin(5);
   H2->Rebin(5);

   H1->Scale(1 / H1->Integral());
   H2->Scale(1 / H2->Integral());

   H1->SetLineWidth(2);
   H2->SetLineWidth(2);

   H1->SetLineColor(kBlack);
   H2->SetLineColor(kGreen - 3);

   double Max = 0;
   if(Max < H1->GetMaximum())   Max = H1->GetMaximum();
   if(Max < H2->GetMaximum())   Max = H2->GetMaximum();

   TGraph G;
   G.SetLineWidth(3);
   G.SetLineStyle(10);
   G.SetPoint(0, TrueValue[Component-1], 0);
   G.SetPoint(1, TrueValue[Component-1], Max * 2);

   TH1D HWorld("HWorld", "", H1->GetNbinsX(), H1->GetXaxis()->GetBinLowEdge(1), H1->GetXaxis()->GetBinUpEdge(H1->GetNbinsX()));
   HWorld.SetStats(0);
   if(DoO == false)
      HWorld.SetMaximum(Max * 1.4);
   else
      HWorld.SetMaximum(Max * 1.1);
   
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
   H1->Draw("same");
   H2->Draw("same");

   G.Draw("l");

   TLegend Legend(0.2, 0.85, 0.4, 0.7);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(H1, ((Model[0] == '3') ? "\"Gen\" (with M_{4l})" : "Gen"), "l");
   Legend.AddEntry(H2, "Reco", "l");
   Legend.Draw();

   C.SaveAs(Form("Plots/PlotOverlayGR_%s_%s_%d_%d.png", Model.c_str(), (DoO ? "O" : ""), Size, Component));
   C.SaveAs(Form("Plots/PlotOverlayGR_%s_%s_%d_%d.C",   Model.c_str(), (DoO ? "O" : ""), Size, Component));
   C.SaveAs(Form("Plots/PlotOverlayGR_%s_%s_%d_%d.eps", Model.c_str(), (DoO ? "O" : ""), Size, Component));
   C.SaveAs(Form("Plots/PlotOverlayGR_%s_%s_%d_%d.pdf", Model.c_str(), (DoO ? "O" : ""), Size, Component));
}










