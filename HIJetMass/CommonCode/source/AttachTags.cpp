#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1.h"
#include "TKey.h"
#include "TList.h"
#include "TObject.h"
#include "TClass.h"

int main(int argc, char *argv[])
{
   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputFile Tag" << endl;
      return -1;
   }

   TFile InputFile(argv[1]);
   TFile OutputFile(argv[2], "RECREATE");
   string Tag = argv[3];

   TList *List = (TList *)InputFile.GetListOfKeys();
   TIter Iter(List);
   TKey *Key = NULL, *OldKey = NULL;

   while(Key = (TKey *)Iter())
   {
      if(OldKey != NULL && string(OldKey->GetName()) == string(Key->GetName()))
         continue;

      TObject *Object = Key->ReadObj();
      
      Object->Clone(Form("%s__%s", Object->GetName(), Tag.c_str()))->Write();

      OldKey = Key;
   }

   OutputFile.Close();
   InputFile.Close();

   return 0;
}





