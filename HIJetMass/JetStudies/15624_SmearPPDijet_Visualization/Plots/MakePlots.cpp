#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TEllipse.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile File("Output.root");

   TEllipse E1(-0.4, -0.4, 0.4);
   TEllipse E2(+0.4, -0.4, 0.4);
   TEllipse E3(-0.4, +0.4, 0.4);

   E1.SetFillStyle(0);
   E2.SetFillStyle(0);
   E3.SetFillStyle(0);

   for(int i = 251; i < 1000; i++)
   {
      for(int j = 0; j < 100; j++)
      {
         if(File.Get(Form("HJetShapeTogether_%d_%d", i, j)) == NULL)
            continue;

         TCanvas Canvas;

         TH2D *H = (TH2D *)File.Get(Form("HJetShapeTogether_%d_%d", i, j));
         H->SetStats(0);

         H->Draw("colz");
         E1.Draw();
         E2.Draw();
         E3.Draw();

         Canvas.SaveAs(Form("Plots/15623_PPSmearToys_JetShape_%d_%d.png", i, j));
         Canvas.SaveAs(Form("Plots/15623_PPSmearToys_JetShape_%d_%d.C"  , i, j));
         Canvas.SaveAs(Form("Plots/15623_PPSmearToys_JetShape_%d_%d.eps", i, j));
         Canvas.SaveAs(Form("Plots/15623_PPSmearToys_JetShape_%d_%d.pdf", i, j));
      }
   }

   File.Close();

   return 0;
}




