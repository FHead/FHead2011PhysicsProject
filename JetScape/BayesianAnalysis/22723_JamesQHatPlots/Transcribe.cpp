#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TTree.h"

#include "CustomAssert.h"
#include "CommandLine.h"

struct Data;
int main(int argc, char *argv[]);

struct Data
{
   double X;
   double Y;
   double YTruth;
   double Y90Low;
   double Y90High;
   double Y60Low;
   double Y60High;
   bool operator <(const Data &other) const
   {
      if(X < other.X)  return true;
      if(X > other.X)  return false;
      if(Y < other.Y)  return true;
      if(Y > other.Y)  return false;
      return false;
   }
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName   = CL.Get("Input");
   string OutputFileName  = CL.Get("Output");
   string GraphNamePrefix = CL.Get("Prefix");

   TFile InputFile(InputFileName.c_str());
   TTree *Tree = (TTree *)InputFile.Get("Tree");
   Assert(Tree != nullptr, "Error retrieving tree");

   Data M;
   Tree->SetBranchAddress("X", &M.X);
   Tree->SetBranchAddress("Y", &M.Y);
   Tree->SetBranchAddress("YTruth", &M.YTruth);
   Tree->SetBranchAddress("Y90Low", &M.Y90Low);
   Tree->SetBranchAddress("Y90High", &M.Y90High);
   Tree->SetBranchAddress("Y60Low", &M.Y60Low);
   Tree->SetBranchAddress("Y60High", &M.Y60High);

   vector<Data> AllData;
   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);
      AllData.push_back(M);
   }
   sort(AllData.begin(), AllData.end());

   InputFile.Close();

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TGraph G, G90, G60, GTruth;

   for(int i = 0; i < (int)AllData.size(); i++)
   {
      G.SetPoint(G.GetN(), AllData[i].X, AllData[i].Y);
      G90.SetPoint(G90.GetN(), AllData[i].X, AllData[i].Y90Low);
      G60.SetPoint(G60.GetN(), AllData[i].X, AllData[i].Y60Low);
      GTruth.SetPoint(GTruth.GetN(), AllData[i].X, AllData[i].YTruth);
   }
   for(int i = AllData.size() - 1; i >= 0; i--)
   {
      G90.SetPoint(G90.GetN(), AllData[i].X, AllData[i].Y90High);
      G60.SetPoint(G60.GetN(), AllData[i].X, AllData[i].Y60High);
   }
   
   G.SetName((GraphNamePrefix + "Median").c_str());
   G90.SetName((GraphNamePrefix + "90").c_str());
   G60.SetName((GraphNamePrefix + "60").c_str());
   GTruth.SetName((GraphNamePrefix + "TruthMedian").c_str());

   G.Write();
   G90.Write();
   G60.Write();
   GTruth.Write();

   OutputFile.Close();

   return 0;
}
