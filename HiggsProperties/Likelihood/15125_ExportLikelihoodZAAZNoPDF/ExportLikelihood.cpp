#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

int main(int argc, char *argv[])
{
   string FileName = "AttachedTrees15123/ggtoHto2e2mu_5plet_125GeV_noPDF_Full_1.root";
   if(argc > 1)
      FileName = argv[1];

   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get("Tree");

   // Need A1ZZ, A2ZA, A3ZA, A2AZ, A3AZ, A2AA, A3AA
   double A[7][7] = {{0}};
   string L[7] = {"A1ZZ", "A2ZA", "A3ZA", "A2AZ", "A3AZ", "A2AA", "A3AA"};
   for(int i = 0; i < 7; i++)
      for(int j = 0; j < 7; j++)
         Tree->SetBranchAddress(Form("B1_%sR_%sR", L[i].c_str(), L[j].c_str()), &(A[i][j]));

   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      cout << i;
      for(int j = 0; j < 7; j++)
         for(int k = 0; k <= j; k++)
            cout << " " << A[j][k];
      cout << endl;
   }

   File.Close();

   return 0;
}

