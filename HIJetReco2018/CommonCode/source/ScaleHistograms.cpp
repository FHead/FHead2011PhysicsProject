#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TKey.h"
#include "TList.h"
#include "TObject.h"
#include "TTree.h"
#include "TClass.h"

#define Percentage 1

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputFile CrossSection [Tag]" << endl;
      return -1;
   }

   TFile InputFile(argv[1]);
   TFile OutputFile(argv[2], "RECREATE");
   double CrossSection = atof(argv[3]);
   string Tag = "";
   if(argc >= 5)
      Tag = argv[4];

   double ScaleFactor = 1;

   if(InputFile.Get("HN") == NULL)
      cerr << "No raw event count in input file " << argv[1] << ", doing nothing!" << endl;
   else
   {
      TH1 *H = (TH1 *)InputFile.Get("HN");
      ScaleFactor = CrossSection / H->Integral();
   }

   TList *List = (TList *)InputFile.GetListOfKeys();
   TIter Iter(List);
   TKey *Key = NULL, *OldKey = NULL;

   while(Key = (TKey *)Iter())
   {
      if(OldKey != NULL && string(OldKey->GetName()) == string(Key->GetName()))
         continue;

      TObject *Object = Key->ReadObj();
      
      if(Object->IsA()->InheritsFrom("TH1") == true)   // histograms!  scale them!
      {
         TH1 *H = (TH1 *)Object;
         if(Object->IsA()->InheritsFrom("TProfile") == false
            && Object->IsA()->InheritsFrom("TProfile2D") == false)
            H->Scale(ScaleFactor);
         else    // We need to scale the weights
         {
            if(Object->IsA()->InheritsFrom("TProfile") == true)
            {
               TProfile *P = (TProfile *)H;
               P->Add(P, P, ScaleFactor, 0);
            }
            else
            {
               TProfile2D *P = (TProfile2D *)H;
               P->Add(P, P, ScaleFactor, 0);
            }
         }

         if(Tag == "")
            H->Clone(H->GetName())->Write();
         else
            H->Clone(Form("%s__%s", H->GetName(), Tag.c_str()))->Write();
      }
      else if(Object->IsA()->InheritsFrom("TTree") == true)   // trees!  attach a "MCWeight"!
      {
         TTree *T = (TTree *)Object;
         int EntryCount = T->GetEntries() * Percentage;
         
         T = T->CloneTree(EntryCount);

         TBranch *Branch = T->Branch("MCWeight", &ScaleFactor, "MCWeight/D");
         for(int i = 0; i < EntryCount; i++)
         {
            T->GetEntry(i);
            Branch->Fill();
         }

         if(Tag != "")
            T->SetName(Form("%s__%s", Object->GetName(), Tag.c_str()));
         T->Write();
      }
      else   // not histograms and not trees!  do nothing and simply copy them!
      {
         if(Tag == "")
            Object->Clone(Object->GetName())->Write();
         else
            Object->Clone(Form("%s__%s", Object->GetName(), Tag.c_str()))->Write();
      }

      OldKey = Key;
   }

   OutputFile.Close();
   InputFile.Close();

   return 0;
}





