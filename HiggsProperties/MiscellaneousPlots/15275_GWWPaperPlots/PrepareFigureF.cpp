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

   double L, ID, P, PP, PL;
   Tree->SetBranchAddress("L", &L);
   Tree->SetBranchAddress("ID", &ID);
   Tree->SetBranchAddress("P", &P);
   Tree->SetBranchAddress("PP", &PP);
   Tree->SetBranchAddress("PL", &PL);

   map<int, vector<double> > PValues;
   map<int, vector<double> > PValuesWithPrior;
   map<int, vector<double> > PValuesLoosePrior;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      int IntL = (int)L;

      if(PValues.find(IntL) == PValues.end())
         PValues.insert(pair<int, vector<double> >(IntL, vector<double>()));
      if(PValuesWithPrior.find(IntL) == PValuesWithPrior.end())
         PValuesWithPrior.insert(pair<int, vector<double> >(IntL, vector<double>()));
      if(PValuesLoosePrior.find(IntL) == PValuesLoosePrior.end())
         PValuesLoosePrior.insert(pair<int, vector<double> >(IntL, vector<double>()));

      PValues[IntL].push_back(P);
      PValuesWithPrior[IntL].push_back(PP);
      PValuesLoosePrior[IntL].push_back(PL);
   }

   File.Close();

   TFile File2(OutputFileName.c_str(), "RECREATE");

   TGraphAsymmErrors G, GP, GL;
   G.SetNameTitle(GraphName.c_str(), "Title");
   GP.SetNameTitle((GraphName + "_Prior").c_str(), "Title");
   GL.SetNameTitle((GraphName + "_LoosePrior").c_str(), "Title");

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
      
      vector<double> &DataWithPrior = PValuesWithPrior[Ls[iL]];
      sort(DataWithPrior.begin(), DataWithPrior.end());

      Center = DataWithPrior[DataWithPrior.size()*0.5000];
      Low = DataWithPrior[DataWithPrior.size()*0.1575];
      High = DataWithPrior[DataWithPrior.size()*0.8415];

      GP.SetPoint(iL, log(Ls[iL] * Shift), Center);
      GP.SetPointError(iL, 0, 0, Center - Low, High - Center);
      
      vector<double> &DataLoosePrior = PValuesLoosePrior[Ls[iL]];
      sort(DataLoosePrior.begin(), DataLoosePrior.end());

      Center = DataLoosePrior[DataLoosePrior.size()*0.5000];
      Low = DataLoosePrior[DataLoosePrior.size()*0.1575];
      High = DataLoosePrior[DataLoosePrior.size()*0.8415];

      GL.SetPoint(iL, log(Ls[iL] * Shift), Center);
      GL.SetPointError(iL, 0, 0, Center - Low, High - Center);
   }

   G.Write();
   GP.Write();
   GL.Write();

   File2.Close();

   return 0;
}





