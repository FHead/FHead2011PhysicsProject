#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <ctime>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "Code/TauHelperFunctions2.h"
#include "Code/DrawRandom.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "CalculateME.h"
#include "MEFunctionsZA.h"

#include "LeptonResponse.h"
#include "ZAHybridCalculator.h"
#include "PTYFunctions.h"

int main(int argc, char *argv[]);
bool CheckIfGood(vector<double> Single);
void AddToVector(vector<double> &Total, vector<double> Single, double Weight);
void PrintResult(string Identifier, vector<double> Total, int Count);
bool PassBaselineCut(ZALeptonVectors &Vectors);

int main(int argc, char *argv[])
{
   string FileName = "EventB.root";
   int StartEvent = 0;
   int EndEvent = 19;

   if(argc <= 3)
   {
      cerr << "Usage: " << argv[0] << " FileWithTree StartEvent EndEvent" << endl;
      return -1;
   }

   FileName = argv[1];
   StartEvent = atoi(argv[2]);
   EndEvent = atoi(argv[3]);

   // Setup calculators
   ZAHybridCalculator Calculator;

   Calculator.SetEfficiency12(GetElectronEfficiencyPtEta);
   Calculator.SetEfficiencyP(GetMuonEfficiencyPtEta);
   Calculator.SetSmear12(SmearElectronCentral);
   Calculator.SetSmearP(SmearMuonCentral);
   Calculator.SetSimpleMassIntegralStep(180);
   Calculator.SetDoDeltaMH(true, 125);
   Calculator.SetIntegralCZRange(0.75, 1.25);
   Calculator.SetIntegralCPRange(0.75, 1.25);
   Calculator.SetPTYDensity(NULL);
   Calculator.SetIntegralCZStep(20);
   Calculator.SetIntegralCPStep(20);
   Calculator.SetSimpleMassIntegralWindow(40);

   Calculator.SetMECalculator(CalculateA2ZARA2ZARSignal);
   
   // Setup tree
   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      return -1;

   double l1pt, l1eta, l1phi;   double l1id;
   double l2pt, l2eta, l2phi;   double l2id;
   double l3pt, l3eta, l3phi;   double l3id;
   Tree->SetBranchAddress("L1PT", &l1pt);
   Tree->SetBranchAddress("L1Eta", &l1eta);
   Tree->SetBranchAddress("L1Phi", &l1phi);
   Tree->SetBranchAddress("L1ID", &l1id);
   Tree->SetBranchAddress("L2PT", &l2pt);
   Tree->SetBranchAddress("L2Eta", &l2eta);
   Tree->SetBranchAddress("L2Phi", &l2phi);
   Tree->SetBranchAddress("L2ID", &l2id);
   Tree->SetBranchAddress("PPT", &l3pt);
   Tree->SetBranchAddress("PEta", &l3eta);
   Tree->SetBranchAddress("PPhi", &l3phi);
   Tree->SetBranchAddress("PID", &l3id);

   // Start looping
   int EventCount = Tree->GetEntries();
   for(int iEvent = StartEvent; iEvent < EventCount && iEvent <= EndEvent; iEvent++)
   {
      Tree->GetEntry(iEvent);

      ZALeptonVectors Vectors;
      Vectors.Lepton1.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Vectors.Lepton2.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Vectors.Photon.SetPtEtaPhi(l3pt, l3eta, l3phi);

      ZAEventParameters Event = ConvertVectorsToAnglesRoberto(Vectors);

      vector<double> Integral;

      if(PassBaselineCut(Vectors) == true)
         Integral = Calculator.PassThroughMode(Event);
      else
         cout << "Didn't pass baseline cut!" << endl;

      // cout << setprecision(20);
      cout << FileName << " Central " << iEvent;
      for(int i = 0; i < (int)Integral.size(); i++)
         cout << " " << Integral[i];
      cout << endl;
   }

   // Cleanup
   File.Close();

   return 0;
}

bool CheckIfGood(vector<double> Single)
{
   for(int i = 0; i < (int)Single.size(); i++)
      if(Single[i] != Single[i])
         return false;
   return true;
}

void AddToVector(vector<double> &Total, vector<double> Single, double Weight)
{
   if(Single.size() > Total.size())
      Total.resize(Single.size());

   for(int i = 0; i < (int)Single.size(); i++)
      Total[i] = Total[i] + Single[i] * Weight;
}

void PrintResult(string Identifier, vector<double> Total, int Count)
{
   cout << Identifier << " " << Count;
   for(int i = 0; i < (int)Total.size(); i++)
      cout << setprecision(20) << " " << Total[i] / Count;
   cout << endl;
}

bool PassBaselineCut(ZALeptonVectors &Vectors)
{
   return true;
}












