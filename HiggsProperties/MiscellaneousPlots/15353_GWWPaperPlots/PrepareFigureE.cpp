#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH2D.h"
#include "TGraphAsymmErrors.h"

int main(int argc, char *argv[])
{
   string FileName = "SignResult/JobBothS_5plet_A.root";
   string OutputFileName = "Temp/FigureC_JobBothS_5plet_A.root";
   string GraphName = "JobBothS_5plet_A";
   double Shift = 1;

   if(argc != 5)
   {
      cerr << "Usage: " << argv[0] << " RootFileName OutputFileName GraphName Shift" << endl;
      return -1;
   }

   FileName = argv[1];
   OutputFileName = argv[2];
   GraphName = argv[3];
   Shift = atof(argv[4]);

   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("Tree");

   double L, YT, GWW, NLL, P;
   Tree->SetBranchAddress("L", &L);
   Tree->SetBranchAddress("YT", &YT);
   Tree->SetBranchAddress("GWW", &GWW);
   Tree->SetBranchAddress("NLL", &NLL);
   Tree->SetBranchAddress("P", &P);

   map<int, vector<double> > PValues;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      int IntL = (int)L;

      if(PValues.find(IntL) == PValues.end())
         PValues.insert(pair<int, vector<double> >(IntL, vector<double>()));

      PValues[IntL].push_back(P);
   }

   File.Close();

   TFile File2(OutputFileName.c_str(), "RECREATE");

   TGraphAsymmErrors G;
   G.SetNameTitle(GraphName.c_str(), "Title");

   int Ls[] = {25, 50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600};
   for(int iL = 0; iL < 11; iL++)
   {
      if(PValues.find(Ls[iL]) == PValues.end())
         continue;

      vector<double> &Data = PValues[Ls[iL]];
      sort(Data.begin(), Data.end());

      double Center = Data[Data.size()*0.5000];
      double Low = Data[Data.size()*0.1575];
      double High = Data[Data.size()*0.8415];

      G.SetPoint(iL, log(Ls[iL] * Shift), Center);
      G.SetPointError(iL, 0, 0, Center - Low, High - Center);
   }

   G.Write();

   File2.Close();

   return 0;
}





