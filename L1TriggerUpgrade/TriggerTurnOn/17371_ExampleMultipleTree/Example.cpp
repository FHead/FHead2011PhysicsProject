#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TDirectory.h"

#include "CommandLine.h"

#include "include/L1AnalysisEventDataFormat.h"
#include "include/L1AnalysisCaloTPDataFormat.h"
#include "include/L1AnalysisL1ExtraUpgradeDataFormat.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   // Get arguments
   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");

   // Input File
   TFile File(InputFileName.c_str());

   // Trees
   TTree *TreeL1 = (TTree *)File.Get("l1NtupleProducer/L1Tree");
   TTree *TreeExtra = (TTree *)File.Get("l1ExtraUpgradeTreeProducer/L1ExtraUpgradeTree");

   L1Analysis::L1AnalysisEventDataFormat *Event = NULL;
   L1Analysis::L1AnalysisCaloTPDataFormat *Calo = NULL;
   L1Analysis::L1AnalysisL1ExtraUpgradeDataFormat *L1ExtraUpgrade = NULL;

   TreeL1->SetBranchAddress("Event", &Event);
   TreeL1->SetBranchAddress("CALO", &Calo);
   TreeExtra->SetBranchAddress("L1ExtraUpgrade", &L1ExtraUpgrade);

   assert(TreeL1 != NULL && TreeExtra != NULL);

   TH2D H("H", "HCAL TP count vs number of jets;HCAL TP Count;Jet Count", 500, 3500, 4000, 50, 0, 50);
   H.SetStats(0);

   // Loop over events
   int EntryCount = TreeL1->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      TreeL1->GetEntry(iE);
      TreeExtra->GetEntry(iE);

      H.Fill(Calo->nHCALTP, L1ExtraUpgrade->nJets);
   }

   TCanvas Canvas;
   H.Draw("colz");
   Canvas.SaveAs(OutputFileName.c_str());

   // Clean up
   File.Close();

   // Yay
   return 0;
}
















