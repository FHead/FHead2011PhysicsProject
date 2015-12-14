#include <cmath>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile File("Result.root");
   TTree *Tree = (TTree *)File.Get("ResultTree");

   double Bins[101];
   double Min = 20;
   double Max = 50000;
   int BinCount = 100;
   for(int i = 0; i <= 100; i++)
      Bins[i] = Min * exp((log(Max) - log(Min)) / BinCount * i);

   TH2D HZ("HZ", ";N;Z coupling modifier", 100, Bins, 100, -3, 3);
   TH2D HQ("HQ", ";N;Up quark charge", 100, Bins, 100, -1, 2);

   HZ.SetStats(0);
   HQ.SetStats(0);

   Tree->Draw("-EQEL:Sem>>HQ", "", "colz");
   Tree->Draw("-GLEL/0.6301:Sem>>HZ", "", "colz");

   TGraph GQ, GZ;
   GZ.SetPoint(0, 0, 1);
   GZ.SetPoint(1, 100000, 1);
   GQ.SetPoint(0, 0, 0.666666);
   GQ.SetPoint(1, 100000, 0.666666);

   TCanvas C;

   HQ.Draw("colz");
   GQ.Draw("l");
   C.SetLogz();
   C.SetLogx();
   C.SaveAs("SMParameter-Projections-ResultsQ.png");
   C.SaveAs("SMParameter-Projections-ResultsQ.C");
   C.SaveAs("SMParameter-Projections-ResultsQ.eps");
   C.SaveAs("SMParameter-Projections-ResultsQ.pdf");

   HZ.Draw("colz");
   GZ.Draw("l");
   C.SetLogz();
   C.SetLogx();
   C.SaveAs("SMParameter-Projections-ResultsZ.png");
   C.SaveAs("SMParameter-Projections-ResultsZ.C");
   C.SaveAs("SMParameter-Projections-ResultsZ.eps");
   C.SaveAs("SMParameter-Projections-ResultsZ.pdf");

   File.Close();

   return 0;
}




