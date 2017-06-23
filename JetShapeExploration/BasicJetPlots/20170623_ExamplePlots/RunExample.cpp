#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH2D.h"

#include "ProgressBar.h"

#include "BasicUtilities.h"
#include "Messenger.h"

int main(int argc, char *argv[])
{
   // Checking if input is good
   if(argc != 6)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag PTHatMin PTHatMax" << endl;
      return -1;
   }

   // Getting inputs
   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];
   double PTHatMin = atof(argv[4]);
   double PTHatMax = atof(argv[5]);

   // Is it data or MC?  Is it pp or PbPb or pPb?  etc.
   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsDataFromTag(Tag);

   // Prepare input
   TFile *InputFile = TFile::Open(Input.c_str());
   if(InputFile == NULL)
   {
      cerr << "Error!  Input file error!" << endl;
      return -1;
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, "ak4PFJetAnalyzer/t");
   PFTreeMessenger MPF(InputFile, "pfcandAnalyzer/pfTree");
   SkimTreeMessenger MSkim(InputFile);
   TriggerTreeMessenger MHLT(InputFile);

   if(MHiEvent.Tree == NULL)
   {
      cerr << "Error!  HiEvent tree not found in the input file!" << endl;
      return -1;
   }

   // Prepare output
   TFile OutputFile(Output.c_str(), "RECREATE");

   TH1D HN("HN", "Raw event count", 1, 0, 1);
   TH1D HPTHat("HPTHat", "PTHat", 100, 0, 500);
   TH1D HPTHatSelected("HPTHatSelected", "PTHat", 100, 0, 500);

   // Loop over events
   int EntryCount = MHiEvent.Tree->GetEntries() * 0.01;

   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      // Progress bar :D
      Bar.Update(iE);
      Bar.PrintWithMod(200);

      // Get event from trees
      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MPF.GetEntry(iE);
      MSkim.GetEntry(iE);
      MHLT.GetEntry(iE);

      // Fill histograms
      HN.Fill(0);
      HPTHat.Fill(MJet.PTHat);

      if(MJet.PTHat >= PTHatMin && MJet.PTHat < PTHatMax)
         HPTHatSelected.Fill(MJet.PTHat);
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   // Write stuff out
   HPTHat.Write();
   HN.Write();

   // Cleanup
   InputFile->Close();

   return 0;
}






