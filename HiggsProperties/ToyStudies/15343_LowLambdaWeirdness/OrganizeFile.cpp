#include <iostream>
#include <cstdlib>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"

struct SingleDatasetResult;
int main(int argc, char *argv[]);

struct SingleDatasetResult
{
   double Lumi;
   int ID;
   bool Has1;
   double YT1;
   double GWW1;
   bool Has2;
   double YT2;
   double GWW2;
   bool Has3;
   double YT3;
   double GWW3;
   SingleDatasetResult()
   {
      Lumi = -1;
      ID = -1;
      Has1 = false;   YT1 = 0;   GWW1 = 0;
      Has2 = false;   YT2 = 0;   GWW2 = 0;
      Has3 = false;   YT3 = 0;   GWW3 = 0;
   }
   bool operator <(const SingleDatasetResult &other) const
   {
      if(Lumi < other.Lumi)    return true;
      if(Lumi > other.Lumi)    return false;
      if(ID < other.ID)        return true;
      if(ID > other.ID)        return false;
      if(Has1 != other.Has1)   return false;
      if(Has2 != other.Has2)   return false;
      if(Has3 != other.Has3)   return false;
      if(YT1 < other.YT1)      return true;
      if(YT1 > other.YT1)      return false;
      if(GWW1 < other.GWW1)    return true;
      if(GWW1 > other.GWW1)    return false;
      if(YT2 < other.YT2)      return true;
      if(YT2 > other.YT2)      return false;
      if(GWW2 < other.GWW2)    return true;
      if(GWW2 > other.GWW2)    return false;
      if(YT3 < other.YT3)      return true;
      if(YT3 > other.YT3)      return false;
      if(GWW3 < other.GWW3)    return true;
      if(GWW3 > other.GWW3)    return false;
      return false;
   }
};

int main(int argc, char *argv[])
{
   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputFile Lumi" << endl;
      return -1;
   }

   double Lumi = atof(argv[3]);

   TFile InputFile(argv[1]);

   TTree *InputTree = (TTree *)InputFile.Get("ResultTree");

   float P4Error, P7Error, P4, P7, Prior8, ID, Status, Basis;
   InputTree->SetBranchAddress("P4", &P4);
   InputTree->SetBranchAddress("P4Error", &P4Error);
   InputTree->SetBranchAddress("P7", &P7);
   InputTree->SetBranchAddress("P7Error", &P7Error);
   InputTree->SetBranchAddress("Prior8", &Prior8);
   InputTree->SetBranchAddress("ID", &ID);
   InputTree->SetBranchAddress("Status", &Status);
   InputTree->SetBranchAddress("Basis", &Basis);

   map<int, SingleDatasetResult> Records;

   int EntryCount = InputTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      InputTree->GetEntry(iE);

      if(Status < 3)
         continue;
      if(Basis < 3)
         continue;

      int IntID = (int)ID;

      if(Records.find(IntID) == Records.end())
      {
         SingleDatasetResult Result;
         Result.ID = IntID;
         Result.Lumi = Lumi;

         Records.insert(pair<int, SingleDatasetResult>(IntID, Result));
      }

      if(P4Error > 0 && P7Error > 0 && Prior8 == 0)   // NNNYNNYN, no prior
      {
         Records[IntID].Has1 = true;
         Records[IntID].YT1 = P4;
         Records[IntID].GWW1 = P7;
      }
      else if(P4Error > 0 && P7Error > 0 && Prior8 > 0)   // NNNYNNYN, yes prior
      {
         Records[IntID].Has2 = true;
         Records[IntID].YT2 = P4;
         Records[IntID].GWW2 = P7;
      }
      else if(P4Error == 0 && P7Error > 0)   // NNNNNNYN, prior doesn't matter
      {
         Records[IntID].Has3 = true;
         Records[IntID].YT3 = P4;
         Records[IntID].GWW3 = P7;
      }
   }

   InputFile.Close();

   TFile OutputFile(argv[2], "RECREATE");

   TTree OutputTree("Tree", "Tree");

   SingleDatasetResult M;
   OutputTree.Branch("Lumi", &M.Lumi, "Lumi/D");
   OutputTree.Branch("YT1", &M.YT1, "YT1/D");
   OutputTree.Branch("GWW1", &M.GWW1, "GWW1/D");
   OutputTree.Branch("YT2", &M.YT2, "YT2/D");
   OutputTree.Branch("GWW2", &M.GWW2, "GWW2/D");
   OutputTree.Branch("YT3", &M.YT3, "YT3/D");
   OutputTree.Branch("GWW3", &M.GWW3, "GWW3/D");

   for(map<int, SingleDatasetResult>::iterator iter = Records.begin();
      iter != Records.end(); iter++)
   {
      if(iter->second.Has1 == false)
         continue;
      if(iter->second.Has2 == false)
         continue;
      if(iter->second.Has3 == false)
         continue;

      M = iter->second;

      OutputTree.Fill();
   }

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}






