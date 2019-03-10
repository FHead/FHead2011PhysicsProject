#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "ProgressBar.h"

int main(int argc, char *argv[])
{
   TFile InputFile("MixedResult/PP6Dijet.root");
   TTree *InputTree = (TTree *)InputFile.Get("OutputTree");

   TFile OutputFile("PP6DijetSlimmed.root", "RECREATE");
   TTree OutputTree("Tree", "Slimmed Tree");

   vector<double> Double(100);
   int DoubleCount = 0;

   ifstream in("SmearConfigFile");
   while(in)
   {
      char ch[1024] = "";
      in.getline(ch, 1023, '\n');

      stringstream str(ch);

      string InputBranch, OutputBranch, Type;
      str >> InputBranch >> OutputBranch >> Type;

      if(Type == "" || InputBranch == "" || OutputBranch == "")
         continue;
      if(InputBranch[0] == '#')
         continue;

      if(Type == "double")
      {
         InputTree->SetBranchAddress(InputBranch.c_str(), &Double[DoubleCount]);
         OutputTree.Branch(OutputBranch.c_str(), &Double[DoubleCount], (OutputBranch + "/D").c_str());
         DoubleCount = DoubleCount + 1;
      }
   }

   in.close();

   int EntryCount = 10000;

   for(int iE = 0; iE < EntryCount; iE++)
   {
      InputTree->GetEntry(iE);
      OutputTree.Fill();
   }

   OutputTree.Print();

   cout << "!" << endl;
   OutputTree.Write();
   cout << "!" << endl;
   OutputFile.Close();
   cout << "!" << endl;

   InputFile.Close();

   return 0;
}






