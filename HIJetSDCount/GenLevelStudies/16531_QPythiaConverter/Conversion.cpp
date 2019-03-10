#include <iostream>
#include <fstream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "ProgressBar.h"

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " RootFileName OutputBase" << endl;
      return -1;
   }

   string OutputBase = argv[2];

   TFile File(argv[1]);

   TTree *T = (TTree *)File.Get("Tdata");

   vector<double> *px = NULL;   T->SetBranchAddress("px", &px);
   vector<double> *py = NULL;   T->SetBranchAddress("py", &py);
   vector<double> *pz = NULL;   T->SetBranchAddress("pz", &pz);
   vector<double> *m = NULL;    T->SetBranchAddress("m", &m);
   vector<int> *id = NULL;      T->SetBranchAddress("id", &id);
   double w;                    T->SetBranchAddress("xSec", &w);

   ProgressBar Bar(cerr, T->GetEntries());
   Bar.SetStyle(3);

   ofstream out(OutputBase + "_0.pu14");
   int ID = 0;
   int EventCount = 0;

   int EntryCount = T->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);

      Bar.Update(iE);
      Bar.PrintWithMod(EntryCount / 300);

      out << "# event " << iE << endl;
      out << "weight " << w << endl;
      for(int i = 0; i < (int)id->size(); i++)
         out << (*px)[i] << " " << (*py)[i] << " " << (*pz)[i] << " " << (*m)[i]
            << " " << (*id)[i] << " " << 0 << endl;
      out << "end" << endl;

      EventCount = EventCount + 1;
      if(EventCount >= 5000)
      {
         EventCount = 0;
         ID = ID + 1;
         out.close();
         out.open(Form("%s_%d.pu14", OutputBase.c_str(), ID));
      }
   }

   out.close();

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();

   return 0;
}




