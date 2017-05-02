#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TDirectory.h"

#include "Messenger.h"

#include "Histograms.h"

int main()
{
   string InputFileName = "Samples/WToENu200PU/WToENu_99.root";
   string OutputFileName = "OutputHistograms.root";

   TFile File(InputFileName.c_str());

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TDirectory *TkEGDirectory = OutputFile.mkdir("TkEG", "Histograms for tkEG plots");
   TDirectory *TkIsoEGDirectory = OutputFile.mkdir("TkIsoEG", "tkIsoEG!");

   vector<double> TkEGThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms TkEG(25, 0, 50, 30, -3, 3, TkEGThresholds, "TkEG");
   
   vector<double> TkIsoEGThresholds = ToVector(6, 0, 12, 15, 20, 25, 30);
   Histograms TkIsoEG(25, 0, 50, 30, -3, 3, TkIsoEGThresholds, "TkIsoEG");

   L1NTupleMessenger ML1(File, "l1NtupleProducer/L1Tree");
   L1ExtraUpgradeTreeMessenger MExtra(File, "l1ExtraUpgradeTreeProducer/L1ExtraUpgradeTree");

   if(ML1.Tree == NULL)
      return -1;

   int EntryCount = ML1.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      ML1.GetEntry(iE);
      MExtra.GetEntry(iE);

      cout << "TKEG Size = " << MExtra.TkEG.size() << endl;
   }

   TkEG.Write(TkEGDirectory);
   TkIsoEG.Write(TkIsoEGDirectory);

   OutputFile.Close();

   File.Close();

   return 0;
}
















