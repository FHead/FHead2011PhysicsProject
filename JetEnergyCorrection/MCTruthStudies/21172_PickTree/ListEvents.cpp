#include <iostream>
using namespace std;

#include "TFile.h"
#include "TDirectory.h"
#include "TEventList.h"
#include "TTree.h"

#include "CommandLine.h"
#include "CustomAssert.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);
   string FileName = CL.Get("File");
   string Cut = CL.Get("Cut");
   int EventCount = CL.GetInt("EventCount");

   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("OutputTree");

   Assert(Tree != NULL, "Error getting synchtree");

   Tree->Draw(">>list", Cut.c_str());
   TEventList *List = (TEventList *)gDirectory->Get("list");

   int Run, Event, Lumi;
   Tree->SetBranchAddress("Run", &Run);
   Tree->SetBranchAddress("Lumi", &Lumi);
   Tree->SetBranchAddress("Event", &Event);

   int EntryCount = min(List->GetN(), EventCount);
   for(int iL = 0; iL < EntryCount; iL++)
   {
      int iE = List->GetEntry(iL);
      Tree->GetEntry(iE);

      cout << Run << ":" << Lumi << ":" << Event << endl;
   }

   File.Close();

   return 0;
}


