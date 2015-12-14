#include <iostream>
#include <cmath>
using namespace std;

#include "TChain.h"
#include "TTree.h"
#include "TFile.h"

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " Input Output" << endl;
      return -1;
   }

   TChain Tree("ResultTree", "ResultTree");
   Tree.AddFile(argv[1]);

   float Status;
   float A1ZZ, A2ZZ, A3ZZ, A2ZA, A3ZA, A2AA, A3AA, N1, N2, Fem;
   float A2ZZError, A3ZZError, A2ZAError, A3ZAError, A2AAError, A3AAError, N1Error, N2Error, FemError;
   float Sem, Bem;
   Tree.SetBranchAddress("Status", &Status);
   Tree.SetBranchAddress("A2ZZA1ZZ", &A2ZZ);
   Tree.SetBranchAddress("A3ZZA1ZZ", &A3ZZ);
   Tree.SetBranchAddress("A2ZAA1ZZ", &A2ZA);
   Tree.SetBranchAddress("A3ZAA1ZZ", &A3ZA);
   Tree.SetBranchAddress("A2AAA1ZZ", &A2AA);
   Tree.SetBranchAddress("A3AAA1ZZ", &A3AA);
   Tree.SetBranchAddress("N1", &N1);
   Tree.SetBranchAddress("N2", &N2);
   Tree.SetBranchAddress("Fem", &Fem);
   Tree.SetBranchAddress("A2ZZA1ZZError", &A2ZZError);
   Tree.SetBranchAddress("A3ZZA1ZZError", &A3ZZError);
   Tree.SetBranchAddress("A2ZAA1ZZError", &A2ZAError);
   Tree.SetBranchAddress("A3ZAA1ZZError", &A3ZAError);
   Tree.SetBranchAddress("A2AAA1ZZError", &A2AAError);
   Tree.SetBranchAddress("A3AAA1ZZError", &A3AAError);
   Tree.SetBranchAddress("N1Error", &N1Error);
   Tree.SetBranchAddress("N2Error", &N2Error);
   Tree.SetBranchAddress("FemError", &FemError);
   Tree.SetBranchAddress("Sem", &Sem);
   Tree.SetBranchAddress("Bem", &Bem);

   TFile File(argv[2], "RECREATE");

   TTree OutputTree("Tree", "Tree");
   OutputTree.Branch("A1ZZ", &A1ZZ, "A1ZZ/F");
   OutputTree.Branch("A2ZZ", &A2ZZ, "A2ZZ/F");
   OutputTree.Branch("A3ZZ", &A3ZZ, "A3ZZ/F");
   OutputTree.Branch("A2ZA", &A2ZA, "A2ZA/F");
   OutputTree.Branch("A3ZA", &A3ZA, "A3ZA/F");
   OutputTree.Branch("A2AA", &A2AA, "A2AA/F");
   OutputTree.Branch("A3AA", &A3AA, "A3AA/F");
   OutputTree.Branch("Status", &Status, "Status/F");
   OutputTree.Branch("N1", &N1, "N1/F");
   OutputTree.Branch("N2", &N2, "N2/F");
   OutputTree.Branch("F", &Fem, "F/F");
   OutputTree.Branch("S", &Sem, "S/F");
   OutputTree.Branch("B", &Bem, "B/F");

   int EntryCount = Tree.GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree.GetEntry(iE);

      if(Status < 3)                continue;

      if(fabs(A2ZZError) < 1e-10)   continue;
      if(fabs(A3ZZError) < 1e-10)   continue;
      if(fabs(A2ZAError) < 1e-10)   continue;
      if(fabs(A3ZAError) < 1e-10)   continue;
      if(fabs(A2AAError) < 1e-10)   continue;
      if(fabs(A3AAError) < 1e-10)   continue;

      if(fabs(N1Error) < 1e-10)     N1 = -10000;
      if(fabs(N2Error) < 1e-10)     N2 = -10000;
      if(fabs(FemError) < 1e-10)    Fem = -10000;

      double A = sqrt(1 + A2ZZ * A2ZZ + A3ZZ * A3ZZ + A2ZA * A2ZA + A3ZA * A3ZA + A2AA * A2AA + A3AA * A3AA);
      
      A1ZZ = 1 / A;
      A2ZZ = A2ZZ / A;
      A3ZZ = A3ZZ / A;
      A2ZA = A2ZA / A;
      A3ZA = A3ZA / A;
      A2AA = A2AA / A;
      A3AA = A3AA / A;

      OutputTree.Fill();
   }

   OutputTree.Write();
   File.Close();

   return 0;
}







