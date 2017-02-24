#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TH2D.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " DatasetID" << endl;
      return -1;
   }

   SetThesisStyle();

   int DatasetID = atoi(argv[1]);

   TFile File("TheSignExample.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   double ID, YT, GWW, NLL;
   Tree->SetBranchAddress("ID", &ID);
   Tree->SetBranchAddress("YT", &YT);
   Tree->SetBranchAddress("GWW", &GWW);
   Tree->SetBranchAddress("NLL", &NLL);

   double InitialYT = -10000;
   bool Good = true;

   TGraph Graph, GaussianGraph;
   double MinNLL = -1;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount && Good == true; iE++)
   {
      Tree->GetEntry(iE);

      if(DatasetID != (int)ID)
         continue;

      if(InitialYT < -9999)
         InitialYT = YT;
      else
      {
         if(YT != InitialYT)
         {
            Good = false;
            break;
         }
      }

      Graph.SetPoint(Graph.GetN(), GWW / 2, NLL);

      if(MinNLL < 0)
         MinNLL = NLL;
      else
         MinNLL = ((MinNLL > NLL) ? NLL : MinNLL);
   }

   if(Good == false)
   {
      cerr << "This fit has yt floated!  Quitting without making plots..." << endl;
      return -1;
   }

   TF1 FPoly("FPoly", "pol2", -100, 100);
   Graph.Fit(&FPoly);

   double P0 = FPoly.GetParameter(0) - MinNLL;
   double P1 = FPoly.GetParameter(1);
   double P2 = FPoly.GetParameter(2);

   for(int i = 0; i < Graph.GetN(); i++)
   {
      double x, y;
      Graph.GetPoint(i, x, y);
      GaussianGraph.SetPoint(i, x, exp(MinNLL - y));
   }

   TF1 FGaussian("FGaussian", Form("exp(%f+%f*x+%f*x*x)", -P0, -P1, -P2), -100, 100);
   FGaussian.SetLineColor(kBlue);

   TGraph GFill;
   GFill.SetPoint(0, 0, 0);
   for(double x = -10; x <= 0; x = x + 0.001)
   {
      double y = FGaussian.Eval(x);
      GFill.SetPoint(GFill.GetN(), x, y);
   }
   GFill.SetPoint(GFill.GetN(), 0, 0);
   GFill.SetFillColor(kTeal - 2);

   TGraph GLine;
   GLine.SetPoint(0, 0, 0);
   GLine.SetPoint(1, 0, 10);
   GLine.SetLineWidth(3);
   GLine.SetLineColor(kBlack);
   GLine.SetLineStyle(kDashed);

   TCanvas C;

   TH2D HWorld("HWorld", ";#lambda_{WZ};Likelihood (a.u.)", 100, -1, 2.5, 100, 0.000001, 100);
   HWorld.SetStats(0);
   HWorld.Draw();

   GFill.Draw("f");
   GLine.Draw("l");
   
   GaussianGraph.SetMarkerStyle(7);
   GaussianGraph.SetMarkerColor(8);
   GaussianGraph.Draw("p");

   FGaussian.Draw("same");

   HWorld.Draw("axis same");

   C.SetLogy();
   
   C.SaveAs(Form("Plots/FigureD_%d.png", DatasetID));
   C.SaveAs(Form("Plots/FigureD_%d.C", DatasetID));
   C.SaveAs(Form("Plots/FigureD_%d.eps", DatasetID));
   C.SaveAs(Form("Plots/FigureD_%d.pdf", DatasetID));

   File.Close();

   return 0;
}






