#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#include "DataHelper.h"
#include "PlotHelper.h"

#include "SimultaneousFit.C"

void MinimumScan(string RootFile = "Samples/DataAllTrimmedStage2.root", int LastJetBin = 4, string JetFlavor = "PF",
   int EnergyThreshold = 30, string DataHelperFile = "Samples/DataAll.dh");
vector<pair<double, double> > PruneBadOnes(vector<pair<double, double> > &Records);
int FindMinIndex(vector<pair<double, double> > &Records);

void MinimumScan(string RootFile, int LastJetBin, string JetFlavor, int EnergyThreshold,
   string DataHelperFile)
{
   vector<pair<double, double> > Records;

   // Read-in whatever is there from the coarse scan
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

   // find current minimum
   int MinIndex = FindMinIndex(Records);
   
   // extend to the left if necessary
   while(MinIndex < 3)
   {
      double Try = Records[0].first - 2;

      double MinNLL = SimultaneousFit(RootFile, LastJetBin, JetFlavor, EnergyThreshold, DataHelperFile, Try);

      Records.insert(Records.begin(), pair<double, double>(Try, MinNLL));

      // partially prune bad ones
      double BestSlope = (Records[1].second - Records[0].second) / (Records[1].first - Records[0].first);
      int NextOne = 1;

      for(int i = 2; i < (int)Records.size(); i++)
      {
         double Slope = (Records[i].second - Records[0].second) / (Records[i].first - Records[0].first);
         
         if(Slope < BestSlope)
         {
            BestSlope = Slope;
            NextOne = i;
         }
      }

      if(NextOne != 1)
         Records.erase(Records.begin() + 1, Records.begin() + NextOne);

      MinIndex = FindMinIndex(Records);
   }
   
   // extend to the right if necessary
   while(MinIndex + 5 >= (int)Records.size())
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

      MinIndex = FindMinIndex(Records);
   }
   
   // did a finer scan around minimum if necessary
   while(Records[MinIndex+1].first - Records[MinIndex-1].first > 0.5)
   {
      double Minimum = Records[MinIndex-1].first;
      double Maximum = Records[MinIndex+1].first;
      double StepSize = (Maximum - Minimum) / 5;
      for(double i = Minimum + StepSize; i < Maximum; i = i + StepSize)
      {
         double MinNLL = SimultaneousFit(RootFile, LastJetBin, JetFlavor, EnergyThreshold, DataHelperFile, i);
         Records.push_back(pair<double, double>(i, MinNLL));
      }

      sort(Records.begin(), Records.end());
      Records = PruneBadOnes(Records);

      MinIndex = FindMinIndex(Records);
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

