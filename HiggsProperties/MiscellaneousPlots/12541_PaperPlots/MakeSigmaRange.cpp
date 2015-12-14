#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "DataHelper.h"

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile DHFileName" << endl;
      return -1;
   }

   map<string, vector<double> > AllResults;

   TFile FInput(argv[1]);
   TTree *Tree = (TTree *)FInput.Get("Tree");
   if(Tree == NULL)
      return -1;

   float A1ZZ, A2ZZ, A3ZZ, A2ZA, A3ZA, A2AA, A3AA, F, N1, N2, S;
   Tree->SetBranchAddress("A1ZZ", &A1ZZ);
   Tree->SetBranchAddress("A2ZZ", &A2ZZ);
   Tree->SetBranchAddress("A3ZZ", &A3ZZ);
   Tree->SetBranchAddress("A2ZA", &A2ZA);
   Tree->SetBranchAddress("A3ZA", &A3ZA);
   Tree->SetBranchAddress("A2AA", &A2AA);
   Tree->SetBranchAddress("A3AA", &A3AA);
   Tree->SetBranchAddress("F", &F);
   Tree->SetBranchAddress("N1", &N1);
   Tree->SetBranchAddress("N2", &N2);
   Tree->SetBranchAddress("S", &S);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      string NNString = "";
      if(N1 < -100 && N2 < -100)   NNString = "NN";
      if(N1 > -100 && N2 > -100)   NNString = "YY";
      if(NNString == "")           continue;

      string FString = "";
      if(F < 0)                    FString = "N";
      else                         FString = "Y";

      string SString = "";
      if(fabs(S - 25) < 1e-8)      SString = "1";
      if(fabs(S - 50) < 1e-8)      SString = "2";
      if(fabs(S - 100) < 1e-8)     SString = "3";
      if(fabs(S - 200) < 1e-8)     SString = "4";
      if(fabs(S - 400) < 1e-8)     SString = "5";
      if(fabs(S - 800) < 1e-8)     SString = "6";
      if(fabs(S - 1600) < 1e-8)    SString = "7";
      if(SString == "")            cout << "WTF! " << S << endl;

      double Components[] = {A2ZZ / A1ZZ, A3ZZ / A1ZZ, A2ZA / A1ZZ, A3ZA / A1ZZ, A2AA / A1ZZ, A3AA / A1ZZ, F};
      for(int iC = 2; iC <= 8; iC++)
      {
         string CString = Form("%d", iC);

         string StateString = NNString + "_" + FString + "_" + SString + "_" + CString;
         if(AllResults.find(StateString) == AllResults.end())
            AllResults.insert(pair<string, vector<double> >(StateString, vector<double>()));

         AllResults[StateString].push_back(Components[iC-2]);
      }
   }

   FInput.Close();

   DataHelper DHFile;

   for(map<string, vector<double> >::iterator iter = AllResults.begin(); iter != AllResults.end(); iter++)
   {
      string State = iter->first;
      vector<double> Data = iter->second;

      sort(Data.begin(), Data.end());

      int Left = Data.size() * 0.1575;
      int Right = Data.size() * 0.8425;

      DHFile[State]["Min"] = Data[Left];
      DHFile[State]["Max"] = Data[Right];
   }

   DHFile.SaveToFile(argv[2]);

   return 0;
}







