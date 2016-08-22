#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "Code/DrawRandom.h"

int main(int argc, char *argv[]);
void ReadData(string FileName, map<int, vector<double> > &Data, bool Fixed);
double FindPValue(vector<double> &D1, vector<double> &D2);
vector<double> GiveMeBootstrapDataset(const vector<double> &D);
double TailRatio(vector<double> &D1, vector<double> &D2, double x);
int Location(vector<double> &D, double x);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   string File1 = "HypothesisTestingResult/JobBoth_SMVV_J.root";
   string File2 = "HypothesisTestingResult/JobBoth_5plet_J.root";
   string FileName = "Temp/Meow.root";
   string Tag = "Meow";
   bool Fixed = false;

   if(argc != 6)
   {
      cerr << "Usage: " << argv[0] << " NullFile AltFile Output Tag Fixed" << endl;
      return -1;
   }

   File1 = argv[1];
   File2 = argv[2];
   FileName = argv[3];
   Tag = argv[4];
   Fixed = ((argv[5][0] == 'Y') ? true : false);

   map<int, vector<double> > Data1, Data2;
   ReadData(File1, Data1, Fixed);
   ReadData(File2, Data2, Fixed);

   TFile File(FileName.c_str(), "recreate");

   TGraph G;
   G.SetNameTitle(Tag.c_str(), "");

   TGraphAsymmErrors GG;
   GG.SetNameTitle(("ERR_" + Tag).c_str(), "");

   for(map<int, vector<double> >::iterator iter = Data1.begin(); iter != Data1.end(); iter++)
   {
      int Lumi = iter->first;

      if(Data2.find(Lumi) == Data2.end())
         continue;

      vector<double> D1 = Data1[Lumi];
      vector<double> D2 = Data2[Lumi];

      double P = FindPValue(D1, D2);

      int N = G.GetN();
      G.SetPoint(N, Lumi, P);

      N = GG.GetN();
      GG.SetPoint(N, Lumi, P);

      if(Lumi >= 50)
      {
         vector<double> PValues;
         for(int i = 0; i < 10000; i++)
         {
            vector<double> DD1 = GiveMeBootstrapDataset(D1);
            vector<double> DD2 = GiveMeBootstrapDataset(D2);
            PValues.push_back(FindPValue(DD1, DD2));
         }
         sort(PValues.begin(), PValues.end());

         cout << N << " " << Lumi << " " << P << " " << PValues[PValues.size()*0.1585] << " " << PValues[PValues.size()*0.8415] << endl;

         GG.SetPointError(N, 0, 0,
            P - PValues[PValues.size()*0.1585],
            PValues[PValues.size()*0.8415] - P);
      }
   }

   G.Write();
   GG.Write();

   File.Close();

   return 0;
}

void ReadData(string FileName, map<int, vector<double> > &Data, bool Fixed)
{
   Data.clear();

   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      return;

   double L, I2, I5;
   Tree->SetBranchAddress("L", &L);
   if(Fixed == false)
   {
      Tree->SetBranchAddress("I2P", &I2);
      Tree->SetBranchAddress("I5P", &I5);
   }
   else
   {
      Tree->SetBranchAddress("NLL_H5", &I2);
      Tree->SetBranchAddress("NLL_SM", &I5);
   }

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      int IntL = (int)L;
      if(Data.find(IntL) == Data.end())
         Data.insert(pair<int, vector<double> >(L, vector<double>()));

      Data[IntL].push_back(log(I5) - log(I2));
   }

   File.Close();
}

double FindPValue(vector<double> &D1, vector<double> &D2)
{
   sort(D1.begin(), D1.end());
   sort(D2.begin(), D2.end());

   if(D1[D1.size()/2] > D2[D2.size()/2])   // we want D1 to the left
      swap(D1, D2);

   if(D1[D1.size()-1] < D2[0])   // no overlap!
      return 0;

   double L = D1[D1.size()/2];
   double R = D2[D2.size()/2];

   while(R - L > 1e-7)
   {
      double C = (L + R) / 2;

      double Ratio = TailRatio(D1, D2, C);
      if(Ratio > 1)
         R = C;
      else
         L = C;
   }

   double P = (double)Location(D2, (L + R) / 2) / D2.size();

   return P;
}

vector<double> GiveMeBootstrapDataset(const vector<double> &D)
{
   vector<double> Result(D.size());

   for(int i = 0; i < (int)D.size(); i++)
      Result[i] = D[(int)DrawRandom(D.size())];

   return Result;
}

double TailRatio(vector<double> &D1, vector<double> &D2, double x)
{
   int L1 = Location(D1, x);
   int L2 = Location(D2, x);

   double P1 = 1 - (double)L1 / D1.size();
   double P2 = (double)L2 / D2.size();

   return P2 / P1;
}

int Location(vector<double> &D, double x)
{
   // returns number of points below x in dataset D

   if(x < D[0])
      return 0;
   if(x >= D[D.size()-1])
      return D.size();

   int L = 0;
   int R = D.size() - 1;

   while(R - L > 1)
   {
      int C = (L + R) / 2;
      if(D[C] >= x)
         R = C;
      else
         L = C;
   }

   return L;
}




