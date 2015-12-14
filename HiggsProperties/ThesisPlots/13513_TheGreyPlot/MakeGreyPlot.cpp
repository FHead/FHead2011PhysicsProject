#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main();
double MinimumBin(TH1D *H);

int main()
{
   SetThesisRegularStyle();

   TFile FileO("Curves20140618.root");

   TH1D *HO2 = (TH1D *)FileO.Get("ObservedA2");
   TH1D *HO3 = (TH1D *)FileO.Get("ObservedA3");
   
   TFile File("MeowSM.root");


   TH1D *HBelow2 = new TH1D("HBelow2", ";f_{a2};Percentage", 100, -1, 1);
   TH1D *HBelow3 = new TH1D("HBelow3", ";f_{a3};Percentage", 100, -1, 1);
   HBelow2->SetStats(0);
   HBelow3->SetStats(0);

   TH2D *HGreyPlot2 = new TH2D("GreyPlot2", ";f_{a2};-2 #Delta ln(L)", 100, -1, 1, 100, 0, 30);
   TH2D *HGreyPlot3 = new TH2D("GreyPlot3", ";f_{a3};-2 #Delta ln(L)", 100, -1, 1, 100, 0, 25);
   HGreyPlot2->SetStats(0);
   HGreyPlot3->SetStats(0);

   TH1D *HFA2Minimum = new TH1D("HFA2Minimum", ";f_{a2};a.u.", 100, -1, 1);
   TH1D *HFA3Minimum = new TH1D("HFA3Minimum", ";f_{a3};a.u.", 100, -1, 1);
   HFA2Minimum->SetStats(0);
   HFA3Minimum->SetStats(0);

   HBelow2->GetXaxis()->SetNdivisions(505);
   HBelow3->GetXaxis()->SetNdivisions(505);
   HGreyPlot2->GetXaxis()->SetNdivisions(505);
   HGreyPlot3->GetXaxis()->SetNdivisions(505);
   HFA2Minimum->GetXaxis()->SetNdivisions(505);
   HFA3Minimum->GetXaxis()->SetNdivisions(505);

   int GoodCount = 0;

   for(int i = 0; i < 1000; i++)
   {
      TH1D *H2 = (TH1D *)File.Get(Form("HScanFA2_%d_0", i));
      TH1D *H3 = (TH1D *)File.Get(Form("HScanFA3_%d_0", i));
      if(H3 == NULL || H2 == NULL)
         continue;
      GoodCount = GoodCount + 1;

      double MaxJump = 0;
      for(int j = 1; j < H2->GetNbinsX(); j++)
         if(H2->GetBinContent(j + 1) - H2->GetBinContent(j) > MaxJump)
            MaxJump = H2->GetBinContent(j + 1) - H2->GetBinContent(j);
      for(int j = 1; j < H3->GetNbinsX(); j++)
         if(fabs(H3->GetBinContent(j + 1) - H3->GetBinContent(j)) > MaxJump)
            MaxJump = fabs(H3->GetBinContent(j + 1) - H3->GetBinContent(j));
      if(MaxJump > 8)
      {
         cout << "Bad: " << i << endl;
         GoodCount = GoodCount - 1;
         continue;
      }

      HFA2Minimum->Fill(MinimumBin(H2));
      HFA3Minimum->Fill(MinimumBin(H3));

      double Minimum = -1;

      Minimum = H2->GetMinimum();
      for(int j = 1; j <= H2->GetNbinsX(); j++)
      {
         double Value = H2->GetBinContent(j);
         double FAX = H2->GetBinCenter(j);

         HGreyPlot2->Fill(FAX, Value - Minimum);

         int ObservedBin = HO2->FindBin(FAX);
         double Height = HO2->GetBinContent(ObservedBin) - 0.0012;
         if(Value - Minimum < Height)
            HBelow2->Fill(FAX);
      }
      Minimum = -1;

      Minimum = H3->GetMinimum();
      for(int j = 1; j <= H3->GetNbinsX(); j++)
      {
         double Value = H3->GetBinContent(j);
         double FAX = H3->GetBinCenter(j);

         HGreyPlot3->Fill(FAX, Value - Minimum);

         int ObservedBin = HO3->FindBin(FAX);
         double Height = HO3->GetBinContent(ObservedBin) - 0.03;
         if(Value - Minimum < Height)
            HBelow3->Fill(FAX);
      }
      Minimum = -1;
   }

   HBelow2->Scale(1.0 / GoodCount);
   HBelow3->Scale(1.0 / GoodCount);

   HFA2Minimum->Scale(1.0 / GoodCount);
   HFA3Minimum->Scale(1.0 / GoodCount);

   TCanvas C;
   
   HGreyPlot2->Draw("colz");
   HO2->Draw("same");
   C.SetLogz();

   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA2.png");
   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA2.C");
   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA2.eps");
   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA2.pdf");
   
   HGreyPlot3->Draw("colz");
   HO3->Draw("same");
   C.SetLogz();

   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA3.png");
   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA3.C");
   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA3.eps");
   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA3.pdf");

   HBelow2->SetMinimum(0);
   HBelow2->SetMaximum(1);
   HBelow2->Draw();

   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA2Below.png");
   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA2Below.C");
   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA2Below.eps");
   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA2Below.pdf");
   
   HBelow3->SetMinimum(0);
   HBelow3->SetMaximum(1);
   HBelow3->Draw();

   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA3Below.png");
   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA3Below.C");
   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA3Below.eps");
   C.SaveAs("MultiDimensionalResult-Interpretation-GreyPlotFA3Below.pdf");

   HFA2Minimum->Draw();

   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityFA2.png");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityFA2.C");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityFA2.eps");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityFA2.pdf");

   HFA3Minimum->Draw();

   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityFA3.png");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityFA3.C");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityFA3.eps");
   C.SaveAs("MultiDimensionalResult-Interpretation-CentralValueProbabilityFA3.pdf");

   return 0;
}

double MinimumBin(TH1D *H)
{
   if(H == NULL)
      return -999;

   int MinBin = 1;
   for(int i = 1; i <= H->GetNbinsX(); i++)
      if(H->GetBinContent(MinBin) > H->GetBinContent(i))
         MinBin = i;

   return H->GetBinCenter(MinBin);
}



