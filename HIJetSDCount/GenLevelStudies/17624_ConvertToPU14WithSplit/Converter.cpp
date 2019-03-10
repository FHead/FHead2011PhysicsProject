#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"

#define MAX 20000

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputBase = CL.Get("Output");
   string TreeName = CL.Get("Tree", "Tdata");
   int Mod = CL.GetInt("Split", 1000);

   int FileCount = 0;
   ofstream out(Form("%s_%d.pu14", OutputBase.c_str(), FileCount));
   TFile File(InputFileName.c_str());

   TTree *Tree = (TTree *)File.Get(TreeName.c_str());

   double Weight, XSec;
   vector<double> *PX = NULL, *PY = NULL, *PZ = NULL, *PM = NULL;
   vector<int> *PID = NULL;

   Tree->SetBranchAddress("weight", &Weight);
   Tree->SetBranchAddress("xSec", &XSec);
   Tree->SetBranchAddress("id", &PID);
   Tree->SetBranchAddress("px", &PX);
   Tree->SetBranchAddress("py", &PY);
   Tree->SetBranchAddress("pz", &PZ);
   Tree->SetBranchAddress("m", &PM);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      out << "# event " << iE << endl;
      out << "weight " << Weight * XSec << endl;
      for(int i = 0; i < (int)PX->size(); i++)
         out << (*PX)[i] << " " << (*PY)[i] << " " << (*PZ)[i] << " " << (*PM)[i] << " " << (*PID)[i] << " " << 0 << endl;
      out << "end" << endl;
      
      if(Mod > 0 && iE % Mod == Mod - 1)
      {
         out.close();
         FileCount = FileCount + 1;
         out.open(Form("%s_%d.pu14", OutputBase.c_str(), FileCount));
      }
   }

   File.Close();
   out.close();

   return 0;
}




