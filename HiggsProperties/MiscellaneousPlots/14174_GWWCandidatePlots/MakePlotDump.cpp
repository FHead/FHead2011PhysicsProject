#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "TGraphErrors.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TClass.h"
#include "TROOT.h"
#include "TKey.h"

#include "PlotHelper2.h"

int main()
{
   PsFileHelper PsFile("GraphDump.ps");
   PsFile.AddTextPage("Dump of all graphs into a gigantic file");

   vector<string> Explanations1(20);
   Explanations1[0] = "Title example";
   Explanations1[1] = "AVV_A3ZA_BothS_A_Count_NYNNYNNY_NoSquare_NYNNN_Point0";
   Explanations1[2] = "";
   Explanations1[3] = "What it means";
   Explanations1[4] = "AVV basis";
   Explanations1[5] = "Plotting sigma(A3ZA) on y axis";
   Explanations1[6] = "Both channel, signal only (BothS); Both channel, S+B (Both)";
   Explanations1[7] = "A cut";
   Explanations1[8] = "Count: x axis is number of event after cut";
   Explanations1[9] = "NYNNYNNY: what is floated and what is not";
   Explanations1[10] = "NYNNN: what prior is floated";
   Explanations1[11] = "Point0: model point";
   
   vector<string> Explanations2(20);
   Explanations2[0] = "Ordering of parameters in various bases";
   Explanations2[1] = "AVV (A2ZZ, A3ZZ, A4ZZ, A2ZA, A3ZA, A4ZA, A2AA, A3AA, A4AA)";
   Explanations2[2] = "Higgs (DeltaCZ, CZB, CZZ, CZZD, CZA, CZAD, CAA, CAAD)";
   Explanations2[3] = "Warsaw (CT, CH, CWW, CWWD, CWB, CWBD, CBB, CBBD)";
   Explanations2[4] = "Loop (A2ZZ, A3ZZ, A4ZZ, YT, YTA, MT, GWW, MW)";
   Explanations2[5] = "";
   Explanations2[6] = "Prior list:";
   Explanations2[7] = "RWWZZ, RZA, RAA, RHto4l, (chi2)";
   Explanations2[8] = "RZA and RAA are constrained to SM value...so ignore point 0 fits with priors";
   Explanations2[9] = "";
   Explanations2[10] = "";

   PsFile.AddTextPage(Explanations1);
   PsFile.AddTextPage(Explanations2);

   TFile File("AllGraphs.root");

   TIter Next(File.GetListOfKeys());
   TKey *Key;
   
   while((Key = (TKey*)Next()))
   {
      TClass *Class = gROOT->GetClass(Key->GetClassName());
      if(Class->InheritsFrom("TGraph") == false)
         continue;
      
      TGraph *G = (TGraph *)Key->ReadObj();
      
      PsFile.AddPlot(G, "apl", true, true, true, true);
   }

   File.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}




