#include <map>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"

#include "CommandLine.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

struct L1Record;
struct HLTRecord;
int main(int argc, char *argv[]);
map<string, L1Record> ReadL1Record(string FileName);
map<string, HLTRecord> ReadHLTRecord(string FileName, vector<string> &Datasets);
bool SanityCheck(map<string, L1Record> &L1List, map<string, HLTRecord> &HLTList);
void SetupBranches(TTree *Tree, map<string, HLTRecord> HLTList, map<string, int> &Index, vector<int> &Decision);

struct L1Record
{
   string L1;
   int Prescale;
   L1Record() : L1(""), Prescale(1) {}
   bool operator <(const L1Record &other) const   // operator for sorting purposes
   {
      if(L1 < other.L1)               return true;
      if(L1 > other.L1)               return false;
      if(Prescale < other.Prescale)   return true;
      if(Prescale > other.Prescale)   return false;
      return false;
   }
};

struct HLTRecord
{
   string HLT;
   string L1;
   int Prescale;
   string Dataset;
   HLTRecord() : HLT(""), L1(""), Prescale(1), Dataset("") {}
   bool operator <(const HLTRecord &other) const   // operator for sorting purposes
   {
      if(HLT < other.HLT)             return true;
      if(HLT > other.HLT)             return false;
      if(L1 < other.L1)               return true;
      if(L1 > other.L1)               return false;
      if(Prescale < other.Prescale)   return true;
      if(Prescale > other.Prescale)   return false;
      if(Dataset < other.Dataset)     return true;
      if(Dataset > other.Dataset)     return false;
      return false;
   }
};

int main(int argc, char *argv[])
{
   SetThesisStyle();

   // Getting inputs
   CommandLine CL(argc, argv);

   string L1FileName = CL.Get("L1");
   string HLTFileName = CL.Get("HLT");
   string OpenHLTFileName = CL.Get("OpenHLT");
   string TreeName = CL.Get("Tree", "hltbitanalysis/HltTree");
   double MBRate = CL.GetDouble("MBRate", 40000);

   // Read all the L1 and HLT information
   vector<string> Datasets;
   map<string, L1Record> L1List = ReadL1Record(L1FileName);
   map<string, HLTRecord> HLTList = ReadHLTRecord(HLTFileName, Datasets);
   Datasets.push_back("Everything");

   // List of datasets

   // Some sanity check here
   if(SanityCheck(L1List, HLTList) == false)
      return -1;

   // List of HLT path names
   vector<string> HLT;
   for(auto I : HLTList)
      HLT.push_back(I.first);

   // Containers for branches to interface with ROOT trees
   map<string, int> Index;
   vector<int> Decision;

   // Prepare trees
   TFile File(OpenHLTFileName.c_str());
   TTree *Tree = (TTree *)File.Get(TreeName.c_str());
   assert(Tree != NULL);

   // Set branch addresses
   SetupBranches(Tree, HLTList, Index, Decision);

   // Global switch board for prescale calculation
   vector<int> SwitchBoard(Decision.size(), 0);
   
   // Get list of PS for each trigger
   vector<int> PS(Decision.size(), 0);
   for(auto I : Index)
   {
      // Trigger name
      string T = I.first;

      if(HLTList.find(T) != HLTList.end())   // This is an HLT trigger
         PS[I.second] = HLTList[T].Prescale;
      else   // Otherwise this is an L1 trigger
         PS[I.second] = L1List[T].Prescale;

      if(PS[I.second] <= 0)   // If trigger not enabled, disable the switch board
         SwitchBoard[I.second] = 100;
   }

   // Number of events in each dataset
   map<string, int> DatasetCount;
   map<string, int> DatasetCountCross;

   // Now the event loop
   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      // Get event
      Tree->GetEntry(iE);

      // Temporary bool to decide if this event enters given dataset
      // This might not be the best way to do things, but let's start with this and improve if timing is an issue
      map<string, bool> Dataset;

      // Go over all triggers
      for(string T : HLT)
      {
         if(Decision[Index[T]] == 0)                  // HLT doesn't fire
            continue;
         if(SwitchBoard[Index[T]] != 0)               // HLT prescaled
            continue;
         if(Decision[Index[HLTList[T].L1]] == 0)      // L1 doesn't fire
            continue;
         if(SwitchBoard[Index[HLTList[T].L1]] != 0)   // L1 prescaled
            continue;

         // If both HLT and L1 fire, mark event to go to given dataset
         Dataset[HLTList[T].Dataset] = true;
         Dataset["Everything"] = true;
      }

      // Increment dataset count
      for(auto I : Dataset)
         if(I.second == true)
            DatasetCount[I.first]++;

      for(auto I : Dataset)
      {
         if(I.first == "Everything")
            continue;

         for(auto J : Dataset)
         {
            if(J.first == "Everything")
               continue;
            if(J.first == I.first)
               continue;
            if(J.first > I.first)
               continue;

            string Name = I.first + " & " + J.first;
            if(I.second == true && J.second == true)
               DatasetCountCross[Name]++;
         }
      }

      // Increment switchboard for prescale calculation
      for(auto I : Index)
      {
         // First check if trigger fires.  If not fire, do nothing
         string T = I.first;
         if(Decision[I.second] == false)
            continue;

         // Now do the magic
         if(PS[I.second] <= 0)   // trigger not enabled
            SwitchBoard[I.second] = 100;
         else if(PS[I.second] == 1)   // trigger is not prescaled
            SwitchBoard[I.second] = 0;
         else   // trigger prescaled, increment switch board and set to zero if needed
            SwitchBoard[I.second] = (SwitchBoard[I.second] + 1) % PS[I.second];
      }
   }

   // outputs
   cout << "Dataset rates for " << MBRate << " Hz total interaction rate:" << endl;
   cout << endl;
   cout << setw(60) << "Dataset" << setw(8) << "Pass" << " / " << setw(8) << "All" << " => " << setw(15) << " Rate" << endl;
   cout << endl;
   for(int i = 0; i < (int)Datasets.size(); i++)
      cout << setw(60) << Datasets[i]
         << setw(8) << DatasetCount[Datasets[i]] << " / " << setw(8) << EntryCount
         << " => " << setw(15) << double(DatasetCount[Datasets[i]]) / EntryCount * MBRate << endl;
   cout << endl;
   for(auto I : DatasetCountCross)
      cout << setw(60) << I.first
         << setw(8) << I.second << " / " << setw(8) << EntryCount
         << " => " << setw(15) << double(I.second) / EntryCount * MBRate << endl;

   // Fill some histograms
   int N = Datasets.size();
   TH1D HDataset("HDataset", "", N, 0, N);
   HDataset.SetStats(0);
   for(int i = 0; i < N; i++)
   {
      HDataset.GetXaxis()->SetBinLabel(i + 1, Datasets[i].c_str());
      HDataset.Fill(i, DatasetCount[Datasets[i]]);
   }

   if(Datasets[Datasets.size()-1] == "Everything")
      N = N - 1;
   TH2D HCorrelations("HCorrelations", "", N, 0, N, N, 0, N);
   HCorrelations.SetStats(0);
   for(int i = 0; i < N; i++)
   {
      HCorrelations.GetXaxis()->SetBinLabel(i + 1, Datasets[i].c_str());
      HCorrelations.GetYaxis()->SetBinLabel(i + 1, Datasets[i].c_str());
      for(int j = 0; j < N; j++)
      {
         double Rate = 0;
         if(i == j)
            Rate = DatasetCount[Datasets[i]];
         else
         {
            string Key;
            if(Datasets[i] > Datasets[j])
               Key = Datasets[i] + " & " + Datasets[j];
            else
               Key = Datasets[j] + " & " + Datasets[i];
            Rate = DatasetCountCross[Key];
         }

         HCorrelations.Fill(i, j, Rate / HDataset.GetBinContent(i + 1));
      }
   }

   PdfFileHelper PdfFile("Output.pdf");
   PdfFile.AddTextPage("Overlaps");

   PdfFile.AddPlot(HDataset, "hist");
   if(N > 10)
      PdfFile.AddPlot(HCorrelations, "colz");
   else
      PdfFile.AddPlot(HCorrelations, "colz text00");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   // Cleanup
   File.Close();

   return 0;
}

map<string, L1Record> ReadL1Record(string FileName)
{
   // Results
   map<string, L1Record> Result;

   // Getting content of the file
   ifstream in(FileName.c_str());

   while(in)
   {
      // Get a line in the file
      char ch[10240];
      in.getline(ch, 10239, '\n');

      stringstream str(ch);

      // Read content into the record
      L1Record NewRecord;
      str >> NewRecord.L1 >> NewRecord.Prescale;

      // If the line is empty, or if it starts with '#' (comment), ignore the line
      if(NewRecord.L1 == "" || NewRecord.L1[0] == '#')
         continue;

      // Insert into the result
      Result.insert(pair<string, L1Record>(NewRecord.L1, NewRecord));
   }

   in.close();

   // Yay
   return Result;
}

map<string, HLTRecord> ReadHLTRecord(string FileName, vector<string> &Datasets)
{
   // Results
   map<string, HLTRecord> Result;
   Datasets.clear();

   // Getting content of the file
   ifstream in(FileName.c_str());

   while(in)
   {
      // Get a line in the file
      char ch[10240];
      in.getline(ch, 10239, '\n');

      stringstream str(ch);

      // Read content into the record
      HLTRecord NewRecord;
      str >> NewRecord.HLT >> NewRecord.L1 >> NewRecord.Prescale >> NewRecord.Dataset;

      // If the line is empty, or if it starts with '#' (comment), ignore the line
      if(NewRecord.HLT == "" || NewRecord.HLT[0] == '#')
         continue;

      // Insert into the result
      Result.insert(pair<string, HLTRecord>(NewRecord.HLT, NewRecord));

      if(find(Datasets.begin(), Datasets.end(), NewRecord.Dataset) == Datasets.end())
         Datasets.push_back(NewRecord.Dataset);
   }

   in.close();

   // Yay
   return Result;
}

bool SanityCheck(map<string, L1Record> &L1List, map<string, HLTRecord> &HLTList)
{
   // To be implemented

   return true;
}

void SetupBranches(TTree *Tree, map<string, HLTRecord> HLTList, map<string, int> &Index, vector<int> &Decision)
{
   // List of all triggers (both HLT and L10
   vector<string> List;

   for(auto R : HLTList)
   {
      List.push_back(R.second.HLT);
      List.push_back(R.second.L1);
   }

   // Get unique list of triggers
   sort(List.begin(), List.end());
   auto I = unique(List.begin(), List.end());
   List.erase(I, List.end());

   // Clean up previous attempts (if any)
   Index.clear();
   Decision.clear();

   // Prepare containers for branch setting
   for(int i = 0; i < (int)List.size(); i++)
   {
      Index.insert(pair<string, int>(List[i], i));
      Decision.push_back(0);
   }

   // Set branches :D
   for(int i = 0; i < (int)List.size(); i++)
      Tree->SetBranchAddress(List[i].c_str(), &Decision[i]);
}

