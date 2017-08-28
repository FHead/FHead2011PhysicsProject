#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "ProgressBar.h"

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " RootFileName" << endl;
      return -1;
   }

   TFile File(argv[1]);

   TTree *T = (TTree *)File.Get("Tdata");

   vector<double> *px = NULL;   T->SetBranchAddress("px", &px);
   vector<double> *py = NULL;   T->SetBranchAddress("py", &py);
   vector<double> *pz = NULL;   T->SetBranchAddress("pz", &pz);
   vector<double> *m = NULL;    T->SetBranchAddress("m", &m);
   vector<int> *id = NULL;      T->SetBranchAddress("id", &id);
   double w;                    T->SetBranchAddress("weight", &w);

   ProgressBar Bar(cerr, T->GetEntries());
   Bar.SetStyle(3);

   int EntryCount = T->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);

      Bar.Update(iE);
      Bar.PrintWithMod(EntryCount / 300);

      cout << px << " " << id << endl;

      cout << "# event " << iE << endl;
      cout << "weight " << w << endl;
      for(int i = 0; i < (int)id->size(); i++)
         cout << (*px)[i] << " " << (*py)[i] << " " << (*pz)[i] << " " << (*m)[i]
            << " " << (*id)[i] << " " << 0 << endl;
      cout << "end" << endl;
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();

   return 0;
}




