#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "SetStyle.h"

int main();
void WriteMatrix(string Name, double A[1001]);

int main()
{
   SetThesisStyle();

   TFile File("Result.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   double k, Min68, Max68, Min95, Max95;
   Tree->SetBranchAddress("k", &k);
   Tree->SetBranchAddress("Min68", &Min68);
   Tree->SetBranchAddress("Max68", &Max68);
   Tree->SetBranchAddress("Min95", &Min95);
   Tree->SetBranchAddress("Max95", &Max95);

   double AMin68[10001] = {0};
   double AMax68[1001] = {0};
   double AMin95[1001] = {0};
   double AMax95[1001] = {0};

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(k > 1000)
         continue;

      AMin68[(int)k] = Min68;
      AMax68[(int)k] = Max68;
      AMin95[(int)k] = Min95;
      AMax95[(int)k] = Max95;
   }

   WriteMatrix("Min68", AMin68);
   WriteMatrix("Max68", AMax68);
   WriteMatrix("Min95", AMin95);
   WriteMatrix("Max95", AMax95);

   File.Close();

   return 0;
}

void WriteMatrix(string Name, double A[1001])
{
   cout << "var " << Name << " = " << "[";
   for(int k = 0; k <= 1000; k++)
   {
      if(k != 0)
         cout << ",";
      cout << A[k];
   }
   cout << "];" << endl;
}






