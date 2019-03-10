#include <iostream>
using namespace std;

#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2D.h"

#include "SetStyle.h"
#include "DataHelper.h"

int main()
{
   SetThesisStyle();

   DataHelper DHFile("ResultDatabase.dh");

   int ToPlot = 5;

   string StatePrefix[5] =
   {
      "18p4 A1UU A2UU CutP S(",
      "18p4 A1UU A3UU CutP S(",
      "18p4 A1UU A2UA CutP S(",
      "18p4 A1UU A2UZ CutP S(",
      "18p4 A1UU A1UZ CutP S(",
   };
   
   string StateSuffix[5] =
   {
      ") [A1UU A2UU] Fixed",
      ") [A1UU A3UU] Fixed",
      ") [A1UU A2UA] Fixed",
      ") [A1UU A2UZ] Fixed",
      ") [A1UU A1UZ] Fixed"
   };

   int Colors[5] =
   {
      kBlack,
      kBlue,
      kYellow + 3,
      kCyan - 3,
      kRed
   };

   string Label[5] =
   {
      "A_{2}^{#Upsilon#Upsilon}",
      "A_{3}^{#Upsilon#Upsilon}",
      "A_{2}^{#Upsilon#gamma}",
      "A_{2}^{#UpsilonZ}",
      "A_{1}^{#UpsilonZ}"
   };

   int EventCount[15] = {5, 7, 10, 14, 20, 30, 50, 70, 100, 140, 200, 300, 500, 700, 1000};

   TGraph *G[5];
   for(int i = 0; i < ToPlot; i++)
   {
      G[i] = new TGraph;

      for(int j = 0; j < 15; j++)
      {
         string Scenario = Form("%d %d %d %d", EventCount[j], EventCount[j], -1, -1);
         double P = DHFile[StatePrefix[i]+Scenario+StateSuffix[i]]["Model PValue"].GetDouble();
         if(P > 0)
            G[i]->SetPoint(G[i]->GetN(), EventCount[j] * 2, P);
      }

      G[i]->SetMarkerColor(Colors[i]);
      G[i]->SetLineColor(Colors[i]);
   }

   TH2D HWorld("HWorld", ";N_{S};p-value", 100, 7, 600, 100, 1e-4, 1);
   HWorld.SetStats(0);

   TCanvas Canvas;

   HWorld.GetXaxis()->CenterTitle();
   HWorld.GetYaxis()->CenterTitle();
   HWorld.GetYaxis()->SetTitleOffset(1.4);

   HWorld.Draw();

   for(int i = 0; i < ToPlot; i++)
      G[i]->Draw("pl");

   TLegend Legend(0.65, 0.82, 0.95, 0.52);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   for(int i = 0; i < ToPlot; i++)
      Legend.AddEntry(G[i], Label[i].c_str(), "pl");
   Legend.Draw();

   TGraph G1, G2;
   G1.SetPoint(0, 0, 0.5);
   G1.SetPoint(1, 100000, 0.5);
   G2.SetPoint(0, 0, 0.01);
   G2.SetPoint(1, 100000, 0.01);
   G1.Draw("l");
   G2.Draw("l");

   G2.SetLineStyle(kDashed);

   Canvas.SetLogx();
   Canvas.SetLogy();

   Canvas.SaveAs("Figure4.png");
   Canvas.SaveAs("Figure4.C");
   Canvas.SaveAs("Figure4.eps");
   Canvas.SaveAs("Figure4.pdf");

   for(int i = 0; i < 5; i++)
      delete G[i];

   return 0;
}




