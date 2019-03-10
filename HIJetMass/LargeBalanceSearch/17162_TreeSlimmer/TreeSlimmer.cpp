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
   if(argc != 6)
   {
      cerr << "Usage: " << argv[0] << " InputFile InputTree OutputFile OutputTree ConfigFile" << endl;
      return -1;
   }

   TFile InputFile(argv[1]);
   TTree *InputTree = (TTree *)InputFile.Get(argv[3]);

   if(InputTree == NULL)
   {
      cerr << "Error obtaining tree \"" << argv[3] << "\" from file \"" << argv[1] << "\"" << endl;
      return -1;
   }

   TFile OutputFile(argv[2], "RECREATE");
   TTree OutputTree(argv[4], "Slimmed Tree");

   vector<double> Double(1000);
   double DoubleCount = 0;

   ifstream in(argv[5]);

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

   int EntryCount = InputTree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(2);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      Bar.PrintWithMod(EntryCount / 500);

      InputTree->GetEntry(iE);
      OutputTree.Fill();
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();
   OutputFile.Close();

   InputFile.Close();

   return 0;
}






