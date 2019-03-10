#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"

#include "CommandLine.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");

   TFile InputFile(InputFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree *Tree = (TTree *)InputFile.Get("ak4pfchs/t");

   vector<double> *RefPT = NULL;
   vector<double> *RefEta = NULL;
   Tree->SetBranchAddress("refpt", &RefPT);
   Tree->SetBranchAddress("refeta", &RefEta);

   int EtaBinCount = 82;
   double EtaBins[] = {-5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, -3.489, -3.314, -3.139, -2.964, -2.853, -2.65, -2.5, -2.322, -2.172, -2.043, -1.93, -1.83, -1.74, -1.653, -1.566, -1.479, -1.392, -1.305, -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, -0.435, -0.348, -0.261, -0.174, -0.087, 0, 0.087, 0.174, 0.261, 0.348, 0.435, 0.522, 0.609, 0.696, 0.783, 0.879, 0.957, 1.044, 1.131, 1.218, 1.305, 1.392, 1.479, 1.566, 1.653, 1.74, 1.83, 1.93, 2.043, 2.172, 2.322, 2.5, 2.65, 2.853, 2.964, 3.139, 3.314, 3.489, 3.664, 3.839, 4.013, 4.191, 4.363, 4.538, 4.716, 4.889, 5.191};
   int PTBinCount = 20;
   double PTBinMin = 10;
   double PTBinMax = 1000;
   double PTBins[1024] = {0};
   for(int i = 0; i <= PTBinCount; i++)
      PTBins[i] = PTBinMin * pow(PTBinMax / PTBinMin, (double)i / PTBinCount);
   TH2D HEtaPT("HEtaPT", ";eta;pt", EtaBinCount, EtaBins, PTBinCount, PTBins);

   TH1D HN("HN", "", 1, 0, 1);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      HN.Fill(0);

      int N = RefPT->size();
      for(int i = 0; i < N; i++)
         HEtaPT.Fill((*RefEta)[i], (*RefPT)[i]);
   }

   HN.Write();
   HEtaPT.Write();

   OutputFile.Close();
   InputFile.Close();

   return 0;
}



