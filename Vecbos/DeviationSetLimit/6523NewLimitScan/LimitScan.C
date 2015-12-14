#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#include "DataHelper.h"
#include "PlotHelper.h"

#include "SimultaneousFit.C"

void LimitScan(string RootFile = "Samples/DataAllTrimmedStage2.root", int LastJetBin = 4, string JetFlavor = "PF",
   int EnergyThreshold = 30, string DataHelperFile = "Samples/DataAll.dh");
vector<pair<double, double> > PruneBadOnes(vector<pair<double, double> > &Records);
int FindMinIndex(vector<pair<double, double> > &Records);
int FindTargetIndex(vector<pair<double, double> > &Records, double TargetLevel);

void LimitScan(string RootFile, int LastJetBin, string JetFlavor, int EnergyThreshold,
   string DataHelperFile)
{
   vector<pair<double, double> > Records;

   // Read-in whatever is there
   DataHelper DHFile("Database.dh");
   vector<string> States = DHFile.GetListOfKeys();
   for(int i = 0; i < (int)States.size(); i++)
   {
      if(DHFile[States[i]]["JetThreshold"].GetInteger() != EnergyThreshold)
         continue;

      Records.push_back(pair<double, double>(DHFile[States[i]]["ExtraTerm"].GetDouble(),
         DHFile[States[i]]["MinNLL"].GetDouble()));
   }
   sort(Records.begin(), Records.end());

   cout << "Find " << Records.size() << " records." << endl;

   // prune bad ones
   Records = PruneBadOnes(Records);
   
   cout << "After pruning: " << Records.size() << " records." << endl;

   // find current minimum and target level
   int MinIndex = FindMinIndex(Records);
   double TargetLevel = Records[MinIndex].second + 1.96;   // make this configurable?  or not?
   int TargetIndex = FindTargetIndex(Records, TargetLevel);

   cout << "Min level = " << Records[MinIndex].second << endl;
   cout << "Min index = " << MinIndex << endl;
   cout << "Min position = " << Records[MinIndex].first << endl;
   cout << "Target level = " << TargetLevel << endl;
   cout << "Target index = " << TargetIndex << endl;
   cout << "Target position = " << Records[TargetIndex].first << endl;

   // extend to the right if necessary
   while(TargetIndex < 0 || TargetIndex + 5 > Records.size())
   {
      double Try = Records[Records.size()-1].first + 5;

      double MinNLL = SimultaneousFit(RootFile, LastJetBin, JetFlavor, EnergyThreshold, DataHelperFile, Try);

      Records.push_back(pair<double, double>(Try, MinNLL));

      // partially prune bad ones
      double BestSlope = (Records[Records.size()-1].second - Records[Records.size()-2].second)
         / (Records[Records.size()-1].first - Records[Records.size()-2].first);
      int LastOne = Records.size() - 2;

      for(int i = Records.size() - 3; i >= 0; i--)
      {
         double Slope = (Records[i].second - Records[Records.size()-1].second)
            / (Records[i].first - Records[Records.size()-1].first);
         
         if(Slope > BestSlope)
         {
            BestSlope = Slope;
            LastOne = i;
         }
      }

      if(LastOne != Records.size() - 1)
         Records.erase(Records.begin() + LastOne + 1, Records.begin() + (Records.size() - 1));

      TargetIndex = FindTargetIndex(Records, TargetLevel);
   }
   
   cout << "Start doing finer scan around limit" << endl;

   // did a finer scan around target
   while(Records[TargetIndex+1].first - Records[TargetIndex-1].first > 0.5)
   {
      double Minimum = Records[TargetIndex-1].first;
      double Maximum = Records[TargetIndex+1].first;
      double StepSize = (Maximum - Minimum) / 5;
      for(double i = Minimum + StepSize; i < Maximum; i = i + StepSize)
      {
         if(DrawRandom(0, 1) > 0.5)
            i = i + 0.002;
         else
            i = i - 0.002;
         if(DrawRandom(0, 1) > 0.5)
            i = i + 0.001;
         else
            i = i - 0.001;
         double MinNLL = SimultaneousFit(RootFile, LastJetBin, JetFlavor, EnergyThreshold, DataHelperFile, i);
         Records.push_back(pair<double, double>(i, MinNLL));
      }

      sort(Records.begin(), Records.end());
      Records = PruneBadOnes(Records);

      TargetIndex = FindTargetIndex(Records, TargetLevel);
   }
}

vector<pair<double, double> > PruneBadOnes(vector<pair<double, double> > &Records)
{
   for(int i = 0; i < (int)Records.size(); i++)
   {
      int NextOne = i + 1;
      double BestSlope = (Records[i+1].second - Records[i].second) / (Records[i+1].first / Records[i].first);

      for(int j = i + 2; j < (int)Records.size(); j++)
      {
         double Slope = (Records[j].second - Records[i].second) / (Records[j].first - Records[i].first);

         if(Slope < BestSlope)
         {
            NextOne = j;
            BestSlope = Slope;
         }
      }

      if(NextOne != i + 1)
         Records.erase(Records.begin() + i + 1, Records.begin() + NextOne);
   }

   return Records;
}

int FindMinIndex(vector<pair<double, double> > &Records)
{
   int MinIndex = 0;
   for(int i = 1; i < (int)Records.size(); i++)
      if(Records[i].second < Records[MinIndex].second)
         MinIndex = i;

   return MinIndex;
}

int FindTargetIndex(vector<pair<double, double> > &Records, double TargetLevel)
{
   for(int i = FindMinIndex(Records); i < (int)Records.size(); i++)
      if(Records[i].second > TargetLevel)
         return i - 1;

   return -1;
}

