#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "ProgressBar.h"

int main()
{
   SetThesisStyle();

   TFile File("ScaledResult/PP8Dijet.root");
   TTree *Tree = (TTree *)File.Get("Tree");

   double EtaBinEdge[15] = {0};
   for(int i = 0; i < 15; i++)
      EtaBinEdge[i] = 4.0 / 14.0 * i - 2.0;

   double PTBinEdge[6] = {100, 120, 140, 160, 200, 300};

   TGraph G[5];

   ProgressBar Bar(cout, 14 * 5);
   Bar.SetStyle(2);

   for(int i = 0; i < 14; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         Bar.Update(i * 5 + j);
         Bar.Print();

         TH1D H("H", "", 1000, -5, 5);

         Tree->Draw("JetPT/RefPT-1>>H",
            Form("RefEta > %f && RefEta <= %f && RefPT > %f && RefPT <= %f", EtaBinEdge[i], EtaBinEdge[i+1], PTBinEdge[j], PTBinEdge[j+1]));

         G[j].SetPoint(i, (EtaBinEdge[i+1] + EtaBinEdge[i]) / 2, H.GetRMS() / (H.GetMean() + 1));
      }
   }
         
   Bar.Update(14 * 5);
   Bar.Print();
   Bar.PrintLine();

   int Colors[] = {kCyan, kBlue, kYellow - 3, kGreen, kGray};

   TLegend Legend(0.4, 0.8, 0.7, 0.5);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry("", "p_{T,gen} (GeV/c)", "");

   for(int i = 0; i < 5; i++)
   {
      G[i].SetMarkerStyle(20);
      G[i].SetMarkerColor(Colors[i]);
      G[i].SetLineColor(Colors[i]);

      Legend.AddEntry(&G[i], Form("%.0f-%.0f", PTBinEdge[i], PTBinEdge[i+1]), "pl");
   }

   TCanvas C;

   TH2D HWorld("HWorld", ";#eta;#sigma(p_{T,rec}/p_{T,gen})/#mu", 100, -2, 2, 100, 0, 1);
   HWorld.SetStats(0);
   HWorld.Draw();

   for(int i = 0; i < 5; i++)
      G[i].Draw("pl");

   Legend.Draw();

   C.SaveAs("PPResolution.png");
   C.SaveAs("PPResolution.C");
   C.SaveAs("PPResolution.eps");
   C.SaveAs("PPResolution.pdf");

   return 0;
}







