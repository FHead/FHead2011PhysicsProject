#include <iostream>
using namespace std;

#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2D.h"
#include "TF1.h"

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
      "18p9 A1UU A2UU CutP S(",
      "18p92 A1UU A2UU CutP S(",
      "18p94 A1UU A2UU CutP S(",
      "19p3 A1UU A2UU CutP S(",
   };
   
   string StateSuffix[5] =
   {
      ") [A1UU A2UU] Fixed",
      ") [A1UU A2UU] Fixed",
      ") [A1UU A2UU] Fixed",
      ") [A1UU A2UU] Fixed",
      ") [A1UU A2UU] Fixed",
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
      "18.40 GeV",
      "18.90 GeV",
      "18.92 GeV",
      "18.94 GeV",
      "19.30 GeV",
   };

   int EventCount[15] = {5, 7, 10, 14, 20, 30, 50, 70, 100, 140, 200, 300, 500, 700, 1000};

   TGraph *G[5];
   for(int i = 0; i < ToPlot; i++)
   {
      G[i] = new TGraph;

      for(int j = 0; j < 14; j++)
      {
         string Scenario = Form("%d %d %d %d", EventCount[j], -1, -1, -1);
         double P = DHFile[StatePrefix[i]+Scenario+StateSuffix[i]]["Model PValue"].GetDouble();
         if(P > 0)
            G[i]->SetPoint(G[i]->GetN(), EventCount[j], P);
      
         cout << "State = " << StatePrefix[i] + Scenario + StateSuffix[i] << endl;
      }

      G[i]->SetMarkerColor(Colors[i]);
      G[i]->SetLineColor(Colors[i]);
   }

   TH2D HWorld("HWorld", ";N_{S}^{2e2#mu};p-value", 100, 2, 1000, 100, 1e-4, 1);
   HWorld.SetStats(0);

   TCanvas Canvas;

   HWorld.GetXaxis()->CenterTitle();
   HWorld.GetYaxis()->CenterTitle();
   HWorld.GetYaxis()->SetTitleOffset(1.4);

   HWorld.Draw();
   
   // TF1 F1("F1", "(TMath::Erf(-sqrt(x)/[0])+1)/2", 0, 1000);
   // F1.SetParameter(0, 10);
   // G[2]->Fit(&F1, "", "", 50, 1000);
   // F1.Draw("same");

   for(int i = 0; i < ToPlot; i++)
      G[i]->Draw("pl");

   TLegend Legend(0.15, 0.47, 0.45, 0.17);
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




