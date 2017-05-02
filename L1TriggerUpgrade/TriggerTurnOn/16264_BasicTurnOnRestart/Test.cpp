#include <iostream>
#include <vector>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "L1AnalysisEventDataFormat.h"
using namespace L1Analysis;

int main()
{
   TFile File("Samples/WToENu200PU/WToENu_45.root");

   L1AnalysisEventDataFormat *E;

   TTree *Tree = (TTree *)File.Get("l1NtupleProducer/L1Tree");

   Tree->SetBranchAddress("Event", &E);

   for(int i = 0; i < 5; i++)
   {
      Tree->GetEntry(i);
      cout << E->run << endl;
   }

   File.Close();

   return 0;
}




