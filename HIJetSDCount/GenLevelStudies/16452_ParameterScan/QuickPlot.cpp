#include <iostream>
#include <vector>
using namespace std;

#include "TCanvas.h"
#include "TGraph.h"
#include "TH2D.h"
#include "TLegend.h"

#include "SetStyle.h"

int main();
void MakeGraph(TGraph *G, int N, double ZCut, double Beta, double R0 = 0.4);

int main()
{
   SetThesisStyle();

   vector<double> ZCut;
   vector<double> Beta;

   ZCut.push_back(0.1);     Beta.push_back(0.0);
   ZCut.push_back(0.05);    Beta.push_back(0.0);
   ZCut.push_back(0.5);     Beta.push_back(1.5);
   ZCut.push_back(0.2);     Beta.push_back(1.5);
   ZCut.push_back(0.007);   Beta.push_back(-1.0);
   ZCut.push_back(0.05);    Beta.push_back(-0.845);
   ZCut.push_back(0.025);   Beta.push_back(-2.0);
   ZCut.push_back(0.05);    Beta.push_back(-0.544);
   ZCut.push_back(0.10);    Beta.push_back(0.5);

   int N = ZCut.size();

   int Colors[] = {kBlack, kBlue, kRed, kYellow + 1, kGray, kCyan, kMagenta, kGreen + 3, kYellow + 3, kPink};

   vector<TGraph *> G;
   for(int i = 0; i < N; i++)
   {
      G.push_back(new TGraph);
      MakeGraph(G[i], 1000, ZCut[i], Beta[i]);

      G[i]->SetLineColor(Colors[i]);
      G[i]->SetLineWidth(2);
   }

   TCanvas C;

   TH2D HWorld("HWorld", ";#DeltaR;Threshold", 100, 0.0, 0.6, 100, 0.0, 0.55);
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   for(int i = 0; i < N; i++)
      if(G[i] != NULL)
         G[i]->Draw("l");

   TGraph GLine;
   GLine.SetPoint(0, 0.1, 0);
   GLine.SetPoint(1, 0.1, 10);
   GLine.SetPoint(2, 0.4, 10);
   GLine.SetPoint(3, 0.4, 0);
   GLine.SetPoint(4, -1, 0);
   GLine.SetPoint(5, -1, 0.5);
   GLine.SetPoint(6, 10, 0.5);
   GLine.SetLineStyle(kDashed);
   GLine.Draw("l");

   TLegend Legend(0.35, 0.45, 0.65, 0.85);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.030);
   Legend.SetBorderSize(1);
   for(int i = 0; i < N; i++)
      if(G[i] != NULL)
         Legend.AddEntry(G[i], Form("%d: (%.3f, %.3f)", i, ZCut[i], Beta[i]), "l");
   Legend.Draw();

   C.SaveAs("Lines.png");
   C.SaveAs("Lines.C");
   C.SaveAs("Lines.eps");
   C.SaveAs("Lines.pdf");

   for(int i = 0; i < N; i++)
   {
      if(G[i] != NULL)
         delete G[i];
   }

   return 0;
}

void MakeGraph(TGraph *G, int N, double ZCut, double Beta, double R0)
{
   if(G == NULL)
      return;

   for(int i = 0; i < N; i++)
   {
      double x = R0 / N * (i * 2 + 0.5);
      double y = ZCut * pow((i * 2 + 0.5) / N, Beta);

      G->SetPoint(i, x, y);
   }
}



