#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

#include "Code/TauHelperFunctions2.h"
#include "Code/DrawRandom.h"
#include "ProgressBar.h"

#include "AngleConversion.h"

#include "PTYFunctions.h"

int main(int argc, char *argv[]);
bool PassCut(const EventParameters &Event);
pair<double, double> GiveMePTY();

int main(int argc, char *argv[])
{
   string FileName = "HZZEventFitFormat_qqZZGenerated.tmp.root";
   string BranchName = "Efficiency";

   if(argc < 2)
   {
      cerr << "Usage: " << argv[0] << " FileWithTree BranchName" << endl;
      cerr << "BranchName is default to \"Efficiency\"" << endl;
      return -1;
   }

   FileName = argv[1];
   BranchName = ((argc >= 2) ? argv[2] : "Efficiency");

   TFile File(FileName.c_str(), "update");

   TTree *Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
   {
      cerr << "No trees found in file!" << endl;
      return -1;
   }

   float l1pt, l2pt, l3pt, l4pt;
   float l1eta, l2eta, l3eta, l4eta;
   float l1phi, l2phi, l3phi, l4phi;
   Tree->SetBranchAddress("l1pt", &l1pt);
   Tree->SetBranchAddress("l2pt", &l2pt);
   Tree->SetBranchAddress("l3pt", &l3pt);
   Tree->SetBranchAddress("l4pt", &l4pt);
   Tree->SetBranchAddress("l1eta", &l1eta);
   Tree->SetBranchAddress("l2eta", &l2eta);
   Tree->SetBranchAddress("l3eta", &l3eta);
   Tree->SetBranchAddress("l4eta", &l4eta);
   Tree->SetBranchAddress("l1phi", &l1phi);
   Tree->SetBranchAddress("l2phi", &l2phi);
   Tree->SetBranchAddress("l3phi", &l3phi);
   Tree->SetBranchAddress("l4phi", &l4phi);

   // float qqZZ_LogL_Template2;
   // Tree->SetBranchAddress("qqZZ_LogL_Template2", &qqZZ_LogL_Template2);

   double Value = 0;
   TBranch *Branch = Tree->Branch(BranchName.c_str(), &Value, Form("%s/D", BranchName.c_str()));

   int EntryCount = Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(0);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      Bar.Print();

      Tree->GetEntry(iE);

      // if(qqZZ_LogL_Template2 >= 0)
      // {
      //    Value = 0;
      //    Branch->Fill();
      //    continue;
      // }

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      int TrialCount = 5000;
      int Passed = 0;
      for(int iT = 0; iT < TrialCount; iT++)
      {
         EventParameters Event2 = Event;

         pair<double, double> PTY = GiveMePTY();
         Event2.PTH = PTY.first;
         Event2.YH = PTY.second;
         Event2.PhiH = DrawRandom(0, 2 * PI);
         Event2.PhiOffset = DrawRandom(0, 2 * PI);

         Passed = Passed + PassCut(Event2);
      }

      Value = (double)Passed / (double)TrialCount;

      Branch->Fill();
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   Tree->Write("", TObject::kOverwrite);

   File.Close();

   return 0;
}

bool PassCut(const EventParameters &Event)
{
   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   double M1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   if(max(M1, M2) < 40)   return false;
   if(max(M1, M2) > 120)  return false;
   if(min(M1, M2) < 12)   return false;
   if(min(M1, M2) > 70)   return false;

   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 20)   return false;
   if(LPTs[2] < 10)   return false;
   if(LPTs[1] < 7)    return false;
   if(LPTs[0] < 7)    return false;

   if(Leptons.Lepton11.GetAbsEta() > 2.4)   return false;
   if(Leptons.Lepton12.GetAbsEta() > 2.4)   return false;
   if(Leptons.Lepton21.GetAbsEta() > 2.4)   return false;
   if(Leptons.Lepton22.GetAbsEta() > 2.4)   return false;

   double M4L = (Leptons.Lepton11 + Leptons.Lepton12 + Leptons.Lepton21 + Leptons.Lepton22).GetMass();
   if (!(M4L > 115 && M4L < 135)) return false;

   return true;
}

pair<double, double> GiveMePTY()
{
   pair<double, double> Result;

   bool Good = false;
   while(Good == false)
   {
      Result.first = DrawRandom(0, 500);
      Result.second = DrawRandom(-10, 10);

      double Density = ToyPTYDensity(Result.first, Result.second);

      if(DrawRandom(0, 1) < Density)
         Good = true;
   };

   return Result;
}


