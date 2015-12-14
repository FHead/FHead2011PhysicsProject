#include <iostream>
#include <string>
#include <map>
using namespace std;

#include "TChain.h"

struct EventIndex;
int main(int argc, char *argv[]);

struct EventIndex
{
   long long RunNumber;
   long long EventNumber;
   int LumiSection;
public:
   EventIndex(double run, double event, double lumi)
   {
      RunNumber = (long long)(run + 0.000001);
      EventNumber = (long long)(event + 0.000001);
      LumiSection = (int)(lumi + 0.000001);
   }
   bool operator <(const EventIndex &other) const
   {
      if(RunNumber < other.RunNumber)
         return true;
      if(RunNumber > other.RunNumber)
         return false;
      
      if(EventNumber < other.EventNumber)
         return true;
      if(EventNumber > other.EventNumber)
         return false;
      
      if(LumiSection < other.LumiSection)
         return true;
      if(LumiSection > other.LumiSection)
         return false;

      return false;
   }
};

int main(int argc, char *argv[])
{
   if(argc < 2)
   {
      cout << "Usage: " << argv[0] << " RootFile" << endl;
      return -1;
   }

   TChain Tree("LQ3Tree", "LQ3Tree");
   Tree.AddFile(argv[1]);

   double RunNumber, EventNumber, LumiSection;
   Tree.SetBranchAddress("RunNumber", &RunNumber);
   Tree.SetBranchAddress("EventNumber", &EventNumber);
   Tree.SetBranchAddress("LumiSection", &LumiSection);

   Tree.SetBranchStatus("*", false);
   Tree.SetBranchStatus("RunNumber", true);
   Tree.SetBranchStatus("EventNumber", true);
   Tree.SetBranchStatus("LumiSection", true);

   map<EventIndex, int> Counts;

   bool DuplicateDetected = false;

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 1000000 == 0)
         cout << iEntry + 1 << "/" << EntryCount << endl;

      Tree.GetEntry(iEntry);

      EventIndex current(RunNumber, EventNumber, LumiSection);

      if(Counts.find(current) == Counts.end())
         Counts.insert(pair<EventIndex, int>(current, 1));
      else
      {
         DuplicateDetected = true;
         break;
      }
   }

   if(DuplicateDetected == true)
      cout << "Detected duplicate event!!!!" << endl;
   else
      cout << "Duplicate free.  Use dataset at ease." << endl;

   return 0;
}


