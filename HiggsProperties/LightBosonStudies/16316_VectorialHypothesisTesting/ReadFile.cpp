#include <iostream>
#include <vector>
using namespace std;

#include "AngleConversion.h"

#include "DataHelperFwd.h"

#include "ReadFile.h"
   
FileHandle::FileHandle(string FileName, char cut, bool reuse, bool IsEM)
{
   File = TFile::Open(FileName.c_str());
   Cut = cut;
   ReUse = reuse;

   Tree = (TTree *)File->Get("T");

   if(Tree == NULL)
      return;

   Messenger.SetBranchAddress(Tree);

   Tree->SetBranchAddress("L1PT", &L1PT);
   Tree->SetBranchAddress("L1Eta", &L1Eta);
   Tree->SetBranchAddress("L1Phi", &L1Phi);
   Tree->SetBranchAddress("L2PT", &L2PT);
   Tree->SetBranchAddress("L2Eta", &L2Eta);
   Tree->SetBranchAddress("L2Phi", &L2Phi);
   Tree->SetBranchAddress("L3PT", &L3PT);
   Tree->SetBranchAddress("L3Eta", &L3Eta);
   Tree->SetBranchAddress("L3Phi", &L3Phi);
   Tree->SetBranchAddress("L4PT", &L4PT);
   Tree->SetBranchAddress("L4Eta", &L4Eta);
   Tree->SetBranchAddress("L4Phi", &L4Phi);

   vector<string> Suffix = GetXVVSignalSuffixList();

   string Prefix = "XX";
   Prefix[0] = ((IsEM == true) ? 'T' : 'V');
   Prefix[1] = Cut;

   double IS[72][72] = {{0}};
   double IB = 0;

   DataHelper DHFile("Normalization.dh");
   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 72; j++)
         IS[i][j] = DHFile["0TeV"][Prefix+"1_"+Suffix[i]+"_"+Suffix[j]].GetDouble();
   IB = DHFile["0TeV"][Prefix+"2_DDbar"].GetDouble() * 2;

   Messenger.SetIS(IS);
   Messenger.SetIB(IB);

   CurrentEvent = 0;
   EntryCount = Tree->GetEntries();
   HasMoreEvents = ReadFirstEvent();
}

FileHandle::~FileHandle()
{
   if(File != NULL)
      delete File;
}

bool FileHandle::IsThereNext()
{
   if(HasMoreEvents == true)
      return true;
   return false;
}
   
bool FileHandle::ReadFirstEvent()
{
   bool FoundOne = false;

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      CurrentEvent = iE;

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      Leptons.GoToRest();

      if(PassPairingCuts(Leptons)[Cut-'A'] == true)
      {
         FoundOne = true;
         break;
      }
   }

   return FoundOne;
}

Likelihood FileHandle::GetNextEvent()
{
   if(HasMoreEvents == false)
      cerr << "Check if there are more events by calling IsThereNext() function!" << endl;

   Likelihood Current = Messenger;

   bool FoundOne = false;

   for(int iE = CurrentEvent + 1; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      CurrentEvent = iE;

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      Leptons.GoToRest();

      if(PassPairingCuts(Leptons)[Cut-'A'] == true)
      {
         FoundOne = true;
         break;
      }

      if(ReUse == true && iE == EntryCount - 1)   // restart from beginning
         iE = -1;
   }

   HasMoreEvents = FoundOne;

   return Current;
}






