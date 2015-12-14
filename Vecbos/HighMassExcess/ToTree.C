#include <fstream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

void ToTree()
{
   TFile F("OppositeSign.root", "RECREATE");

   TTree Tree("Dimuon", "Dimuon");

   double Mass;
   Tree.Branch("Mass", &Mass, "Mass/D");

   ifstream in("OppositeSign");
   while(in)
   {
      Mass = -1;
      in >> Mass;
      Tree.Fill();
   }
   in.close();

   Tree.Write();

   F.Close();
}
