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

int main(int argc, char *argv[]);
double PToSigma(double pn, double pp);
double erfinv(double x);
double erfcinv(double x);

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

   double L, ID, P, PP, PL, Pn, Pp, PPn, PPp, PLn, PLp;
   Tree->SetBranchAddress("L", &L);
   Tree->SetBranchAddress("ID", &ID);
   Tree->SetBranchAddress("P", &P);
   Tree->SetBranchAddress("Pn", &Pn);
   Tree->SetBranchAddress("Pp", &Pp);
   Tree->SetBranchAddress("PP", &PP);
   Tree->SetBranchAddress("PPn", &PPn);
   Tree->SetBranchAddress("PPp", &PPp);
   Tree->SetBranchAddress("PL", &PL);
   Tree->SetBranchAddress("PLn", &PLn);
   Tree->SetBranchAddress("PLp", &PLp);

   map<int, vector<double> > SValues;
   map<int, vector<double> > SValuesWithPrior;
   map<int, vector<double> > SValuesLoosePrior;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      int IntL = (int)L;

      if(SValues.find(IntL) == SValues.end())
         SValues.insert(pair<int, vector<double> >(IntL, vector<double>()));
      if(SValuesWithPrior.find(IntL) == SValuesWithPrior.end())
         SValuesWithPrior.insert(pair<int, vector<double> >(IntL, vector<double>()));
      if(SValuesLoosePrior.find(IntL) == SValuesLoosePrior.end())
         SValuesLoosePrior.insert(pair<int, vector<double> >(IntL, vector<double>()));

      SValues[IntL].push_back(PToSigma(Pn, Pp));
      SValuesWithPrior[IntL].push_back(PToSigma(PPn, PPp));
      SValuesLoosePrior[IntL].push_back(PToSigma(PLn, PLp));
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
      if(SValues.find(Ls[iL]) == SValues.end())
         continue;

      vector<double> &Data = SValues[Ls[iL]];
      sort(Data.begin(), Data.end());

      double Center = Data[Data.size()*0.5000];
      double Low = Data[Data.size()*0.1575];
      double High = Data[Data.size()*0.8415];

      G.SetPoint(iL, log(Ls[iL] * Shift), Center);
      G.SetPointError(iL, 0, 0, Center - Low, High - Center);
      
      vector<double> &DataWithPrior = SValuesWithPrior[Ls[iL]];
      sort(DataWithPrior.begin(), DataWithPrior.end());

      Center = DataWithPrior[DataWithPrior.size()*0.5000];
      Low = DataWithPrior[DataWithPrior.size()*0.1575];
      High = DataWithPrior[DataWithPrior.size()*0.8415];

      GP.SetPoint(iL, log(Ls[iL] * Shift), Center);
      GP.SetPointError(iL, 0, 0, Center - Low, High - Center);
      
      vector<double> &DataLoosePrior = SValuesLoosePrior[Ls[iL]];
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

double PToSigma(double pn, double pp)
{
   bool Swapped = false;
   if(pn > pp)
   {
      Swapped = true;
      swap(pn, pp);
   }

   double p = pn / (pn + pp);
   double answer = 0;

   if(p > 0.01)
      answer = sqrt(2) * erfinv(1 - 2 * p);
   else
      answer = sqrt(2) * erfcinv(2 * p);

   if(Swapped == true)
      answer = -answer;

   return answer;
}

double erfinv(double x)
{
   // Stupid binary search patch-up

   if(x <= -1)
      return -9999999999;
   if(x >= 1)
      return 9999999999;

   // Step 1 - find boundaries
   double Min = -1, Max = 1;

   while(erf(Min) > x && Min > -100)
      Min = Min * 2;
   while(erf(Max) < x && Max < 100)
      Max = Max * 2;

   if(Min < -100)
      return -9999999999;
   if(Max > 100)
      return 9999999999;

   while(Max - Min > 0.00001)
   {
      double C = (Max + Min) / 2;

      if(erf(C) < x)
         Min = C;
      else
         Max = C;
   }

   return (Max + Min) / 2;
}

double erfcinv(double x)
{
   if(x <= 0)
      return 9999999999;
   if(x >= 2)
      return -9999999999;

   // Step 1 - find boundaries
   double Min = -1, Max = 1;

   while(erfc(Min) < x && Min > -100)
      Min = Min * 2;
   while(erfc(Max) > x && Max < 100)
      Max = Max * 2;

   if(Min < -100)
      return -9999999999;
   if(Max > 100)
      return 9999999999;

   while(Max - Min > 0.00001)
   {
      double C = (Max + Min) / 2;

      if(erfc(C) > x)
         Min = C;
      else
         Max = C;
   }

   return (Max + Min) / 2;
}


