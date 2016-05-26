#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "SetStyle.h"

int main();
void WriteMatrix(string Name, double A[101][101]);

int main()
{
   SetThesisStyle();

   TFile File("Result.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   double x, N, Min68, Max68, Min95, Max95;
   Tree->SetBranchAddress("x", &x);
   Tree->SetBranchAddress("N", &N);
   Tree->SetBranchAddress("Min68", &Min68);
   Tree->SetBranchAddress("Max68", &Max68);
   Tree->SetBranchAddress("Min95", &Min95);
   Tree->SetBranchAddress("Max95", &Max95);

   double AMin68[101][101] = {{0}};
   double AMax68[101][101] = {{0}};
   double AMin95[101][101] = {{0}};
   double AMax95[101][101] = {{0}};

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(x > 100 || N > 100)
         continue;

      AMin68[(int)x][(int)N] = Min68;
      AMax68[(int)x][(int)N] = Max68;
      AMin95[(int)x][(int)N] = Min95;
      AMax95[(int)x][(int)N] = Max95;
   }

   WriteMatrix("Min68", AMin68);
   WriteMatrix("Max68", AMax68);
   WriteMatrix("Min95", AMin95);
   WriteMatrix("Max95", AMax95);

   File.Close();

   return 0;
}

void WriteMatrix(string Name, double A[101][101])
{
   cout << "var " << Name << " = " << "[";
   for(int N = 0; N <= 100; N++)
   {
      if(N != 0)
         cout << ",";
      cout << "[";
      for(int x = 0; x <= 100; x++)
      {
         if(x != 0)
            cout << "," << A[x][N];
         else
            cout << A[x][N];
      }
      cout << "]";
   }
   cout << "];" << endl;
}






