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
void ReadData(string FileName, map<int, vector<double> > &Data);
double TailRatio(vector<double> &D1, vector<double> &D2, double x);
int Location(vector<double> &D, double x);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   string File1 = "HypothesisTestingResult/JobBoth_SMVV_J.root";
   string File2 = "HypothesisTestingResult/JobBoth_5plet_J.root";
   string OutputBase = "Meow";

   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " NullFile AltFile OutputBase" << endl;
      return -1;
   }

   File1 = argv[1];
   File2 = argv[2];
   OutputBase = argv[3];

   map<int, vector<double> > Data1, Data2;
   ReadData(File1, Data1);
   ReadData(File2, Data2);

   TGraph G;

   for(map<int, vector<double> >::iterator iter = Data1.begin(); iter != Data1.end(); iter++)
   {
      int Lumi = iter->first;

      if(Data2.find(Lumi) == Data2.end())
         continue;

      vector<double> D1 = Data1[Lumi];
      vector<double> D2 = Data2[Lumi];

      sort(D1.begin(), D1.end());
      sort(D2.begin(), D2.end());

      if(D1[D1.size()/2] > D2[D2.size()/2])   // we want D1 to the left
         swap(D1, D2);

      if(D1[D1.size()-1] < D2[0])   // no overlap!
         continue;

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

      int N = G.GetN();
      G.SetPoint(N, Lumi, P);
   }

   TCanvas C;

   TH2D HWorld("HWorld", ";Luminosity (fb^{-1});Model separation p-value", 100, 10, 10000, 100, 0.001, 1);
   HWorld.SetStats(0);
   HWorld.Draw();

   G.Draw("pl");

   TGraph G1, G2;
   G1.SetLineStyle(kDashed);
   G1.SetPoint(0, 0, 0.05);
   G1.SetPoint(1, 100000000, 0.05);
   G1.Draw("l");
   G2.SetLineStyle(kDashed);
   G2.SetPoint(0, 0, 0.01);
   G2.SetPoint(1, 100000000, 0.01);
   G2.Draw("l");

   C.SetLogx();
   C.SetLogy();

   C.SaveAs(Form("Plots/FigureM_%s.png", OutputBase.c_str()));
   C.SaveAs(Form("Plots/FigureM_%s.C", OutputBase.c_str()));
   C.SaveAs(Form("Plots/FigureM_%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("Plots/FigureM_%s.pdf", OutputBase.c_str()));

   return 0;
}

void ReadData(string FileName, map<int, vector<double> > &Data)
{
   Data.clear();

   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      return;

   double L, I2, I5;
   Tree->SetBranchAddress("L", &L);
   Tree->SetBranchAddress("I2P", &I2);
   Tree->SetBranchAddress("I5P", &I5);

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




