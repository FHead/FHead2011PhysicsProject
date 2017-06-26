#include <iostream>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"

struct Data;
int main();

struct Data
{
public:
   int Run;
   int Event;
   int Lumi;
   double GenE;
   double GenPT;
   double GenEta;
   double GenPhi;
   double L1E;
   double L1PT;
   double L1Eta;
   double L1Phi;
public:
   bool operator <(const Data &other) const
   {
      if(Run < other.Run)       return true;
      if(Run > other.Run)       return false;
      if(Event < other.Event)   return true;
      if(Event > other.Event)   return false;
      if(Lumi < other.Lumi)     return true;
      if(Lumi > other.Lumi)     return false;
      return false;
   }
   bool operator ==(const Data &other) const
   {
      if(Run != other.Run)       return false;
      if(Event != other.Event)   return false;
      if(Lumi != other.Lumi)     return false;
      return true;
   }
   void SetBranchAddress(TTree *T)
   {
      T->SetBranchAddress("Run", &Run);
      T->SetBranchAddress("Event", &Event);
      T->SetBranchAddress("Lumi", &Lumi);

      T->SetBranchAddress("GenE", &GenE);
      T->SetBranchAddress("GenPT", &GenPT);
      T->SetBranchAddress("GenEta", &GenEta);
      T->SetBranchAddress("GenPhi", &GenPhi);

      T->SetBranchAddress("L1E", &L1E);
      T->SetBranchAddress("L1PT", &L1PT);
      T->SetBranchAddress("L1Eta", &L1Eta);
      T->SetBranchAddress("L1Phi", &L1Phi);
   }
};

int main()
{
   char FileNameOld[1024] = "Result/Combined/WToENu140PU.root";
   char FileNameNew[1024] = "Result/Combined/WToENu140PU_NewRecipePlusTyler.root";

   map<Data, Data> OldData;

   TFile FileOld(FileNameOld);
   TFile FileNew(FileNameNew);

   TTree *TOld = (TTree *)FileOld.Get("T");
   TTree *TNew = (TTree *)FileNew.Get("T");

   Data M;
   M.SetBranchAddress(TOld);
   M.SetBranchAddress(TNew);

   int EntryCount;

   EntryCount = TOld->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      TOld->GetEntry(iE);
      if(OldData.find(M) == OldData.end())
         OldData.insert(pair<Data, Data>(M, M));
   }

   int Run, Event, Lumi;
   double GenEOld, GenPTOld, GenEtaOld, GenPhiOld;
   double L1EOld, L1PTOld, L1EtaOld, L1PhiOld;
   double GenENew, GenPTNew, GenEtaNew, GenPhiNew;
   double L1ENew, L1PTNew, L1EtaNew, L1PhiNew;

   TFile File("Merged.root", "RECREATE");

   TTree T("T", "T");

   T.Branch("Run", &Run, "Run/I");
   T.Branch("Event", &Event, "Event/I");
   T.Branch("Lumi", &Lumi, "Lumi/I");

   T.Branch("GenEOld", &GenEOld, "GenEOld/D");
   T.Branch("GenPTOld", &GenPTOld, "GenPTOld/D");
   T.Branch("GenEtaOld", &GenEtaOld, "GenEtaOld/D");
   T.Branch("GenPhiOld", &GenPhiOld, "GenPhiOld/D");
   T.Branch("L1EOld", &L1EOld, "L1EOld/D");
   T.Branch("L1PTOld", &L1PTOld, "L1PTOld/D");
   T.Branch("L1EtaOld", &L1EtaOld, "L1EtaOld/D");
   T.Branch("L1PhiOld", &L1PhiOld, "L1PhiOld/D");
   T.Branch("GenENew", &GenENew, "GenENew/D");
   T.Branch("GenPTNew", &GenPTNew, "GenPTNew/D");
   T.Branch("GenEtaNew", &GenEtaNew, "GenEtaNew/D");
   T.Branch("GenPhiNew", &GenPhiNew, "GenPhiNew/D");
   T.Branch("L1ENew", &L1ENew, "L1ENew/D");
   T.Branch("L1PTNew", &L1PTNew, "L1PTNew/D");
   T.Branch("L1EtaNew", &L1EtaNew, "L1EtaNew/D");
   T.Branch("L1PhiNew", &L1PhiNew, "L1PhiNew/D");

   EntryCount = TNew->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      TNew->GetEntry(iE);
      if(OldData.find(M) == OldData.end())
         continue;

      Data OldM = OldData[M];

      Run = M.Run;
      Event = M.Event;
      Lumi = M.Lumi;

      GenEOld = OldM.GenE;
      GenPTOld = OldM.GenPT;
      GenEtaOld = OldM.GenEta;
      GenPhiOld = OldM.GenPhi;
      L1EOld = OldM.L1E;
      L1PTOld = OldM.L1PT;
      L1EtaOld = OldM.L1Eta;
      L1PhiOld = OldM.L1Phi;

      GenENew = M.GenE;
      GenPTNew = M.GenPT;
      GenEtaNew = M.GenEta;
      GenPhiNew = M.GenPhi;
      L1ENew = M.L1E;
      L1PTNew = M.L1PT;
      L1EtaNew = M.L1Eta;
      L1PhiNew = M.L1Phi;

      T.Fill();
   }

   T.Write();

   File.Close();

   FileNew.Close();
   FileOld.Close();

   return 0;
}




