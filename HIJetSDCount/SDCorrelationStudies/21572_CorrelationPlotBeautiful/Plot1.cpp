#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

int main(int argc, char *argv[])
{
   TFile F1("Combined_NewJewelSimple150.root");
   TFile F2("Combined_NewJewelNRSimple150.root");
   TFile F3("Combined_NewJewelVac150.root");

   TTree *T1 = (TTree *)F1.Get("jetTree");
   TTree *T2 = (TTree *)F2.Get("jetTree");
   TTree *T3 = (TTree *)F3.Get("jetTree");

   F3.Close();
   F2.Close();
   F1.Close();

   return 0;
}



