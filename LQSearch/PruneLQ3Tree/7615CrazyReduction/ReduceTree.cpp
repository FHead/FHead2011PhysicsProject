#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TList.h"

#include "TauHelperFunctions2.h"

#include "ReadLQ3Tree.h"

int main(int argc, char *argv[]);
void CopyHistograms(TFile &Source, TFile &Destination);

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cout << "Usage: " << argv[0] << " SourceFile DestinationFile" << endl;
      return -1;
   }

   string SourceFileName = argv[1];
   string DestinationFileName = argv[2];

   struct stat statFile;
   int intStat = stat(DestinationFileName.c_str(), &statFile);
   if(intStat == 0)
   {
      cout << "Destination file \"" << DestinationFileName << "\" exists!" << endl;
      cout << "Exiting...." << endl;
      return -1;
   }

   TFile Source(SourceFileName.c_str());
   TFile Destination(DestinationFileName.c_str(), "recreate");

   TTree *OldTree = (TTree *)Source.Get("LQ3Tree");
   TTree *NewTree = new TTree("LQ3Tree", "LQ3Tree, at least 2 jets above 60 GeV, MR (new) > 200, R (new) > 0.2");

   TreeRecord M;
   M.SetBranchAddress(OldTree);
   M.Branch(NewTree);

   int EntryCount = OldTree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 100000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      OldTree->GetEntry(iEntry);

      int CaloJet60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 60)
            CaloJet60 = CaloJet60 + 1;
      
      int PFJet60 = 0;
      for(int i = 0; i < M.PFJetCount; i++)
         if(M.PFJetPT[i] > 60)
            PFJet60 = PFJet60 + 1;

      if(CaloJet60 < 2 && PFJet60 < 2)
         continue;

      vector<FourVector> GoodJets;
      for(int i = 0; i < M.CaloJetCount && i < 100; i++)
      {
         if(M.CaloJetPT[i] < 40)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);

         GoodJets.push_back(NewJet);
      }
      if(GoodJets.size() > 20)
      {
         NewTree->Fill();
         continue;
      }
      if(GoodJets.size() < 2)
         continue;

      vector<FourVector> Hemispheres = SplitIntoGroups(GoodJets, true);

      FourVector PFMET(0, M.PFMET[0], M.PFMET[1], 0);

      double MRNew = Get2011MR(Hemispheres[0], Hemispheres[1]);
      double RNew = Get2011R(Hemispheres[0], Hemispheres[1], PFMET);
      double R2New = RNew * RNew;

      if(MRNew < 300 || R2New < 0.06)
         continue;

      NewTree->Fill();
   }

   NewTree->Write();

   CopyHistograms(Source, Destination);

   Destination.Close();
   Source.Close();

   return 0;
}

void CopyHistograms(TFile &Source, TFile &Destination)
{
   TList *ListOfKeys = Source.GetListOfKeys();
   TIter KeyIterator(ListOfKeys);
   TObject *Object = KeyIterator();

   while(Object != NULL)
   {
      if(Object->IsFolder() == true)
      {
         Object = KeyIterator();
         continue;
      }

      TObject *RealObject = Source.Get(Object->GetName());
      string Name = RealObject->GetName();
      string Type = RealObject->IsA()->GetName();

      if(Type == "TTree")
      {
         Object = KeyIterator();
         continue;
      }

      if(Type == "TH1D")
      {
         TH1D *H = (TH1D *)Source.Get(Name.c_str());
         Destination.cd();
         H->Clone(H->GetName())->Write();
      }
      if(Type == "TH2D")
      {
         TH2D *H = (TH2D *)Source.Get(Name.c_str());
         Destination.cd();
         H->Clone(H->GetName())->Write();
      }

      cout << "Object " << Name << " of type " << Type << " copied." << endl;

      Object = KeyIterator();
   }
}


