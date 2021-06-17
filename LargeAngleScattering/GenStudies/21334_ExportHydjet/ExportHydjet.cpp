#include <iostream>
#include <fstream>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "ProgressBar.h"
#include "CustomAssert.h"
#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");
   int MaxEvent = CL.GetInt("MaxEvent", 100);
   double PTHatMin = CL.GetDouble("PTHatMin", -1);
   double PTHatMax = CL.GetDouble("PTHatMax", -1);
   double HiBinMin = CL.GetDouble("HiBinMin", -1);
   double HiBinMax = CL.GetDouble("HiBinMax", -1);

   ofstream OutputFile(OutputFileName);

   TFile *File = TFile::Open(InputFileName.c_str());
   Assert(File != NULL, "Input file error");

   TTree *Tree = (TTree *)File->Get("pfcandAnalyzer/pfTree");
   Assert(Tree != NULL, "Input tree not found");

   TTree *HiTree = (TTree *)File->Get("hiEvtAnalyzer/HiTree");

   vector<float> *PT = nullptr, *Eta = nullptr, *Phi = nullptr;
   vector<int> *ID = nullptr;

   Tree->SetBranchAddress("pfPt", &PT);
   Tree->SetBranchAddress("pfEta", &Eta);
   Tree->SetBranchAddress("pfPhi", &Phi);
   Tree->SetBranchAddress("pfId", &ID);

   float PTHat;
   int HiBin;
   HiTree->SetBranchAddress("pthat", &PTHat);
   HiTree->SetBranchAddress("hiBin", &HiBin);

   int EntryCount = Tree->GetEntries();
   ProgressBar Bar(cout, min(EntryCount, MaxEvent));

   int CurrentCount = 0;

   for(int iE = 0; iE < EntryCount && CurrentCount < MaxEvent; iE++)
   {
      Bar.Update(CurrentCount);
      Bar.Print();

      Tree->GetEntry(iE);
      HiTree->GetEntry(iE);

      if(PTHatMin > 0 && PTHat < PTHatMin)
         continue;
      if(PTHatMax > 0 && PTHat > PTHatMax)
         continue;

      if(HiBinMin > 0 && HiBin < HiBinMin)
         continue;
      if(HiBinMax > 0 && HiBin > HiBinMax)
         continue;

      CurrentCount = CurrentCount + 1;

      OutputFile << "# Event " << iE << endl;
      for(int iP = 0; iP < (int)PT->size(); iP++)
      {
         int id = 0;
         if((*ID)[iP] == 1)   id = 211;
         if((*ID)[iP] == 2)   id = 11;
         if((*ID)[iP] == 3)   id = 13;
         if((*ID)[iP] == 4)   id = 22;
         if((*ID)[iP] == 5)   id = 130;
         if((*ID)[iP] == 6)   id = 130;
         if((*ID)[iP] == 7)   id = 22;

         FourVector P;
         P.SetPtEtaPhi((*PT)[iP], (*Eta)[iP], (*Phi)[iP]);
         OutputFile << P[1] << " " << P[2] << " " << P[3] << " " << 0
            << " " << id << " " << 0 << endl;
      }
      OutputFile << "end" << endl;
   }

   Bar.Update(min(EntryCount, MaxEvent));
   Bar.Print();
   Bar.PrintLine();

   File->Close();
   delete File;

   OutputFile.close();

   return 0;
}


