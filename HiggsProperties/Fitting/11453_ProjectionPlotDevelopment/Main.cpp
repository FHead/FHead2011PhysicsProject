#include <iostream>
using namespace std;

#include "PlotHelper2.h"

#include "PlotProjection.h"

int main()
{
   TFile F1("AddedMap_All.root");   // contains background
   TFile F2("Projections_All.root");   // contains signal

   TFile FSignal1("Samples/hzzTree_id1125.root");   // Contains signal tree
   TFile FSignal2("Samples/hzzTree_id8125.root");   // Contains signal (PS) tree
   TFile FBackground("Samples/hzzTree_id103.root");   // Contins background tree

   TTree *Signal1Tree = (TTree *)FSignal1.Get("zz4lTree/probe_tree");
   TTree *Signal2Tree = (TTree *)FSignal2.Get("zz4lTree/probe_tree");
   TTree *BackgroundTree = (TTree *)FBackground.Get("zz4lTree/probe_tree");

   PsFileHelper PsFile("TestStacking.ps");
   PsFile.AddTextPage("Test of stacking pdfs");

   string components[] = {"Phi0", "Theta0", "Phi", "Theta1", "Theta2", "Mass1", "Mass2"};
   vector<string> Components(components, components + 7);

   for(int i = 0; i < (int)Components.size(); i++)
      ProduceOverlayPlots_BA1A3(PsFile, NULL, Components[i], F1, F2, 0.25, 1, 5.1);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F1.Close();
   F2.Close();

   return 0;
}








