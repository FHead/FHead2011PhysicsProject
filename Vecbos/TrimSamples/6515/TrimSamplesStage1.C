#include <string>
using namespace std;

#include "TFile.h"
#include "TTree.h"

void TrimSamplesStage1(string Input = "Samples/ZJetsAll.root", string Output = "TrimmedStage1.root",
   string TreeName = "outTree")
{
   TFile In(Input.c_str());

   TFile Out(Output.c_str(), "RECREATE");

   TTree *Tree = (TTree *)In.Get(TreeName.c_str());
   Tree->Clone(TreeName.c_str())->Write();

   Out.Close();

   In.Close();
}


