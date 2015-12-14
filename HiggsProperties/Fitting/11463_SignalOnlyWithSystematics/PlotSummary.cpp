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
   TFile File("AllResult_1125.root");
   TList *List = (TList *)File.GetListOfKeys();
   TIter NextKey(List);

   TGraph Graph;
   Graph.SetName("GRAPH2");
   int Index = 0;
   
   TGraph GraphN;
   GraphN.SetName("GRAPHN");
   int IndexN = 0;

   TKey *Key = (TKey *)NextKey();
   while(Key != NULL)
   {
      string Name = Key->GetName();

      if(Name.find("HBestValuesA3A1Real_") != string::npos)
      {
         TH1D *H = (TH1D *)File.Get(Name.c_str());

         stringstream SizeStream(Name.substr(20));

         double X = 0;   SizeStream >> X;
         double Y = H->GetRMS();

         Graph.SetPoint(Index, X, Y / 5.1);
         Index = Index + 1;
      }
      if(Name.find("HBestValuesNuisance_") != string::npos)
      {
         TH1D *H = (TH1D *)File.Get(Name.c_str());

         stringstream SizeStream(Name.substr(20));

         double X = 0;   SizeStream >> X;
         double Y = H->GetRMS();

         GraphN.SetPoint(IndexN, X, Y);
         IndexN = IndexN + 1;
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

   GraphN.SetMarkerStyle(11);
   GraphN.Draw("ap");

   GraphN.GetXaxis()->SetTitle("Size of the dataset (events)");
   GraphN.GetYaxis()->SetTitle("Expected spread in units of sigmas on nuisance parameter");

   Canvas.SetGridx();
   Canvas.SetGridy();
   Canvas.SetLogx();
   Canvas.SetLogy();

   Canvas.SaveAs("ExpectedSpreadN.png");
   Canvas.SaveAs("ExpectedSpreadN.C");
   Canvas.SaveAs("ExpectedSpreadN.eps");
   Canvas.SaveAs("ExpectedSpreadN.pdf");

   PsFile.AddCanvas(Canvas);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   File.Close();

   return 0;
}









