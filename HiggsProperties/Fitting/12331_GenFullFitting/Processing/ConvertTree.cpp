#include <iostream>
#include <cmath>
using namespace std;

#include "TChain.h"
#include "TTree.h"
#include "TFile.h"

int main()
{
   TChain Tree("ResultTree", "ResultTree");
   Tree.AddFile("OutputFile_9.root");

   float Status, Sem, See, ThetaZX, PhiZX, ThetaZZ, PhiZZ, ThetaZA, ThetaAA;
   Tree.SetBranchAddress("Status", &Status);
   Tree.SetBranchAddress("Sem", &Sem);
   Tree.SetBranchAddress("See", &See);
   Tree.SetBranchAddress("ThetaZX", &ThetaZX);
   Tree.SetBranchAddress("PhiZX", &PhiZX);
   Tree.SetBranchAddress("ThetaZZ", &ThetaZZ);
   Tree.SetBranchAddress("PhiZZ", &PhiZZ);
   Tree.SetBranchAddress("ThetaZA", &ThetaZA);
   Tree.SetBranchAddress("ThetaAA", &ThetaAA);

   TFile File("ReducedTree.root", "RECREATE");

   double A1ZZ, A2ZZ, A3ZZ, A2ZA, A3ZA, A2AA, A3AA;
   TTree OutputTree("Tree", "Tree");
   OutputTree.Branch("A1ZZ", &A1ZZ, "A1ZZ/D");
   OutputTree.Branch("A2ZZ", &A2ZZ, "A2ZZ/D");
   OutputTree.Branch("A3ZZ", &A3ZZ, "A3ZZ/D");
   OutputTree.Branch("A2ZA", &A2ZA, "A2ZA/D");
   OutputTree.Branch("A3ZA", &A3ZA, "A3ZA/D");
   OutputTree.Branch("A2AA", &A2AA, "A2AA/D");
   OutputTree.Branch("A3AA", &A3AA, "A3AA/D");
   OutputTree.Branch("Status", &Status, "Status/F");
   OutputTree.Branch("Sem", &Sem, "Sem/F");
   OutputTree.Branch("See", &See, "See/F");

   int EntryCount = Tree.GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree.GetEntry(iE);

      double AZZ = cos(ThetaZX) * cos(PhiZX);
      double AZA = cos(ThetaZX) * sin(PhiZX);
      double AAA = sin(ThetaZX);
      
      int Sign = 1;
      if(iE % 2 == 1)
         Sign = -1;

      A1ZZ = Sign * fabs(AZZ * cos(ThetaZZ) * cos(PhiZZ));
      A2ZZ = Sign * fabs(AZZ * cos(ThetaZZ) * sin(PhiZZ));
      A3ZZ = Sign * (1 - fabs(AZZ * sin(ThetaZZ)));
      A2ZA = Sign * fabs(AZA * cos(ThetaZA)); 
      A3ZA = Sign * fabs(AZA * sin(ThetaZA));
      A2AA = Sign * fabs(AAA * cos(ThetaAA));
      A3AA = Sign * fabs(AAA * sin(ThetaAA));

      OutputTree.Fill();
   }

   OutputTree.Write();
   File.Close();

   return 0;
}







