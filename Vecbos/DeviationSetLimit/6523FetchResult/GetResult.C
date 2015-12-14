#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"

#include "DataHelper.h"
#include "PlotHelper.h"

void GetResult();
vector<pair<double, double> > PruneBadOnes(vector<pair<double, double> > &Records);
int FindMinIndex(vector<pair<double, double> > &Records);
int FindTargetIndex(vector<pair<double, double> > &Records, double TargetLevel);

void GetResult()
{
   vector<int> Thresholds;
   Thresholds.push_back(15);
   Thresholds.push_back(16);
   Thresholds.push_back(17);
   Thresholds.push_back(18);
   Thresholds.push_back(19);
   Thresholds.push_back(22);
   Thresholds.push_back(24);
   Thresholds.push_back(26);
   Thresholds.push_back(28);
   Thresholds.push_back(30);
   Thresholds.push_back(40);

   PsFileHelper PsFile("LimitSummary.ps");
   PsFile.AddTextPage("Most probable size & 95\% deviation limit");

   TGraph MinimumGraph;
   MinimumGraph.SetNameTitle("MinimumGraph", "Most probable size");

   TGraph LimitGraph;
   LimitGraph.SetNameTitle("LimitGraph", "95\% Limit");

   for(int a = 0; a < (int)Thresholds.size(); a++)
   {
      int EnergyThreshold = Thresholds[a];

      vector<pair<double, double> > Records;

      // Read-in
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

      cout << "Threshold " << Thresholds[a] << " --- Find " << Records.size() << " records." << endl;

      // prune bad ones
      Records = PruneBadOnes(Records);

      cout << "Threshold " << EnergyThreshold << " --- After pruning: " << Records.size() << " records." << endl;

      // find minimum
      int MinimumIndex = FindMinIndex(Records);
      TGraph MinTemp;
      MinTemp.SetPoint(0, Records[MinimumIndex-3].first, Records[MinimumIndex-3].second);
      MinTemp.SetPoint(1, Records[MinimumIndex-2].first, Records[MinimumIndex-2].second);
      MinTemp.SetPoint(2, Records[MinimumIndex-1].first, Records[MinimumIndex-1].second);
      MinTemp.SetPoint(3, Records[MinimumIndex].first, Records[MinimumIndex].second);
      MinTemp.SetPoint(4, Records[MinimumIndex+1].first, Records[MinimumIndex+1].second);
      MinTemp.SetPoint(5, Records[MinimumIndex+2].first, Records[MinimumIndex+2].second);
      MinTemp.SetPoint(6, Records[MinimumIndex+3].first, Records[MinimumIndex+3].second);
      MinTemp.Fit("pol2");

      double P0 = MinTemp.GetFunction("pol2")->GetParameter(0);
      double P1 = MinTemp.GetFunction("pol2")->GetParameter(1);
      double P2 = MinTemp.GetFunction("pol2")->GetParameter(2);

      double MinX = -P1 / (2 * P2);
      double MinY = P0 - P1 * P1 / 4 / P2;

      cout << MinX << " " << MinY << endl;

      MinimumGraph.SetPoint(a, EnergyThreshold, MinX);

      // find limit
      int LimitIndex = FindTargetIndex(Records, MinY + 1.96);
      TGraph LimitTemp;
      LimitTemp.SetPoint(0, Records[LimitIndex-3].first, Records[LimitIndex-3].second);
      LimitTemp.SetPoint(1, Records[LimitIndex-2].first, Records[LimitIndex-2].second);
      LimitTemp.SetPoint(2, Records[LimitIndex-1].first, Records[LimitIndex-1].second);
      LimitTemp.SetPoint(3, Records[LimitIndex].first, Records[LimitIndex].second);
      LimitTemp.SetPoint(4, Records[LimitIndex+1].first, Records[LimitIndex+1].second);
      LimitTemp.SetPoint(5, Records[LimitIndex+2].first, Records[LimitIndex+2].second);
      LimitTemp.SetPoint(6, Records[LimitIndex+3].first, Records[LimitIndex+3].second);
      LimitTemp.SetPoint(7, Records[LimitIndex+4].first, Records[LimitIndex+4].second);
      LimitTemp.Fit("pol2");

      P0 = LimitTemp.GetFunction("pol2")->GetParameter(0);
      P1 = LimitTemp.GetFunction("pol2")->GetParameter(1);
      P2 = LimitTemp.GetFunction("pol2")->GetParameter(2);
      double L = MinY + 1.96;   // target level

      double X = (-P1 + sqrt(P1 * P1 - 4 * P2 * (P0 - L))) / (2 * P2);

      LimitGraph.SetPoint(a, EnergyThreshold, X);
   }

   TCanvas MinimumCanvas("C1", "C1", 0, 0, 1024, 768);
   MinimumGraph.SetMarkerStyle(20);
   MinimumGraph.Draw("ap");
   MinimumGraph.GetHistogram()->GetXaxis()->SetTitle("Jet energy threshold");
   MinimumGraph.GetHistogram()->GetYaxis()->SetTitle("Most probable extra term size");
   PsFile.AddCanvas(MinimumCanvas);

   TCanvas LimitCanvas("C2", "C2", 0, 0, 1024, 768);
   LimitGraph.SetMarkerStyle(20);
   LimitGraph.Draw("ap");
   LimitGraph.GetHistogram()->GetXaxis()->SetTitle("Jet energy threshold");
   LimitGraph.GetHistogram()->GetYaxis()->SetTitle("Limit on extra term size");
   PsFile.AddCanvas(LimitCanvas);

   PsFile.AddTimeStampPage();
   PsFile.Close();
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


