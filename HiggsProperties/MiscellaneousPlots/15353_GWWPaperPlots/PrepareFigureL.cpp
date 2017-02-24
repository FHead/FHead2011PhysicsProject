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

int main(int argc, char *argv[]);
map<int, double> FindMedian(string FileName, bool Fixed);
map<int, double> FindPercentile(string FileName, double Percentile, bool Fixed);
map<int, double> FindPValue(string FileName, map<int, double> &Query, bool PositiveSide, bool Fixed);
void ReadData(string FileName, map<int, vector<double> > &Data, bool Fixed);

int main(int argc, char *argv[])
{
   string NullFile = "HypothesisTestingResult/JobBoth_SMVV_J.root";
   string AltFile = "HypothesisTestingResult/JobBoth_5plet_J.root";
   bool PositiveSide = true;
   string OutputFile = "Temp/Meow.root";
   string Tag = "Mew";
   bool Fixed = false;

   if(argc != 7)
   {
      cerr << "Usage: " << argv[0] << " NullFile AltFile Positive=(Y|N) OutputFile Tag Fixed=(Y|N)" << endl;
      return -1;
   }

   NullFile = argv[1];
   AltFile = argv[2];
   PositiveSide = ((argv[3][0] == 'Y') ? true : false);
   OutputFile = argv[4];
   Tag = argv[5];
   Fixed = ((argv[6][0] == 'Y') ? true : false);

   SetThesisStyle();

   map<int, double> Median = FindMedian(AltFile, Fixed);
   map<int, double> Plus = FindPercentile(AltFile, 0.8415, Fixed);
   map<int, double> Minus = FindPercentile(AltFile, 0.1585, Fixed);
   map<int, double> PValueMedian = FindPValue(NullFile, Median, PositiveSide, Fixed);
   map<int, double> PValuePlus = FindPValue(NullFile, Plus, PositiveSide, Fixed);
   map<int, double> PValueMinus = FindPValue(NullFile, Minus, PositiveSide, Fixed);

   TFile File(OutputFile.c_str(), "RECREATE");

   TGraphAsymmErrors G;
   G.SetNameTitle(Tag.c_str(), "");

   for(map<int, double>::iterator iter = PValueMedian.begin(); iter != PValueMedian.end(); iter++)
   {
      int N = G.GetN();
      G.SetPoint(N, iter->first, iter->second);

      double P1 = PValuePlus[iter->first];
      double P2 = PValueMinus[iter->first];
      double P0 = iter->second;

      if(P1 < P2)
         swap(P1, P2);

      G.SetPointError(N, 0, 0, P0 - P2, P1 - P0);
   }

   G.Write();

   File.Close();

   return 0;
}

map<int, double> FindMedian(string FileName, bool Fixed)
{
   return FindPercentile(FileName, 0.500, Fixed);
}

map<int, double> FindPercentile(string FileName, double Percentile, bool Fixed)
{
   map<int, double> Answer;

   map<int, vector<double> > Data;
   ReadData(FileName, Data, Fixed);
   if(Data.size() == 0)
      return Answer;

   for(map<int, vector<double> >::iterator iter = Data.begin(); iter != Data.end(); iter++)
   {
      int L = iter->first;
      vector<double> D = Data[L];
      sort(D.begin(), D.end());
      
      Answer.insert(pair<int, double>(L, D[D.size()*Percentile]));
   }

   return Answer;
}

map<int, double> FindPValue(string FileName, map<int, double> &Query, bool PositiveSide, bool Fixed)
{
   map<int, double> Answer;

   map<int, vector<double> > Data;
   ReadData(FileName, Data, Fixed);
   if(Data.size() == 0)
      return Answer;

   for(map<int, vector<double> >::iterator iter = Data.begin(); iter != Data.end(); iter++)
   {
      int L = iter->first;
      vector<double> D = Data[L];

      double Q = Query[L];

      double Count = 0;
      double Small = 0;

      for(int i = 0; i < (int)D.size(); i++)
      {
         Count = Count + 1;
         if(Q < D[i])
            Small = Small + 1;
         if(Q == D[i])
            Small = Small + 0.5;
      }
      
      double P = Small / Count;
      if(PositiveSide == true)
         P = 1 - P;

      Answer.insert(pair<int, double>(L, P));
   }

   return Answer;
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
   if(Fixed == true)
   {
      Tree->SetBranchAddress("NLL_SM", &I2);
      Tree->SetBranchAddress("NLL_H5", &I5);
   }
   else
   {
      Tree->SetBranchAddress("I2P", &I2);
      Tree->SetBranchAddress("I5P", &I5);
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





