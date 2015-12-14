#include <iostream>
#include <sstream>
using namespace std;

#include "TCanvas.h"
#include "TFile.h"
#include "TList.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TKey.h"

#include "PlotHelper2.h"

int main()
{
   TFile File("Likelihoods_All_1125.root");
   TList *List = (TList *)File.GetListOfKeys();
   TIter NextKey(List);

   TGraph Graph;
   Graph.SetName("GRAPH1");
   int Index = 0;

   TKey *Key = (TKey *)NextKey();
   while(Key != NULL)
   {
      string Name = Key->GetName();

      if(Name.find("HCenter1_") != string::npos)
      {
         TH1D *H = (TH1D *)File.Get(Name.c_str());

         stringstream SizeStream(Name.substr(9));

         double X = 0;   SizeStream >> X;
         double Y = H->GetRMS();

         Graph.SetPoint(Index, X, Y / 5.1);
         Index = Index + 1;
      }

      Key = (TKey *)NextKey();
   }

   PsFileHelper PsFile("SummaryPlot.ps");
   PsFile.AddTextPage("Expected spread/precision on A3ZZR/A1ZZR scan");

   TCanvas Canvas;

   Graph.SetMarkerStyle(11);
   Graph.Draw("ap");

   Graph.GetXaxis()->SetTitle("Size of the dataset (events)");
   Graph.GetYaxis()->SetTitle("Expected spread in units of A3ZZ/A1ZZ/5.1 at A1ZZ = 0");

   Canvas.SetGridx();
   Canvas.SetGridy();
   Canvas.SetLogx();
   Canvas.SetLogy();

   Canvas.SaveAs("ExpectedSpread.png");
   Canvas.SaveAs("ExpectedSpread.C");
   Canvas.SaveAs("ExpectedSpread.eps");
   Canvas.SaveAs("ExpectedSpread.pdf");

   PsFile.AddCanvas(Canvas);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   File.Close();

   return 0;
}









