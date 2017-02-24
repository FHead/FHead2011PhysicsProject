#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"

#include "Code/DrawRandom.h"

#include "BasicUtilities.h"
#include "Messenger.h"

int main(int argc, char *argv[]);
double GetDPhi(double phi1, double phi2);

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];

   bool IsData = IsDataFromTag(Tag);

   TFile InputFile(Input.c_str());

   HiEventTreeMessenger MHiEvent(InputFile);
   RhoTreeMessenger MRho(InputFile);
   PFTreeMessenger MPF(InputFile, "pfcandAnalyzer/pfTree");
   SkimTreeMessenger MSkim(InputFile);
   TriggerTreeMessenger MTrigger(InputFile, "hltanalysis/HltTree");

   TFile OutputFile(Output.c_str(), "RECREATE");
  
   TH2D HSubtractedPTHFEnergy("HSubtractedPTHFEnergy", ";HFEnergy;Subtracted Random Cone PT",
      1000, 0, 100, 1000, -100, 100);
   TH2D HSubtractedPTRatioHFEnergy("HSubtractedPTRatioHFEnergy", ";HFEnergy;Subtracted Random Cone PT / PT",
      1000, 0, 100, 1000, -2, 2);
   TH1D HSubtractedPT("HSubtractedPT", ";Subtracted Random Cone PT",
      1000, -20, 20);
   TH1D HTotalPT("HTotalPT", ";Random Cone PT", 1000, 0, 30);

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      MHiEvent.GetEntry(iEntry);
      MRho.GetEntry(iEntry);
      MSkim.GetEntry(iEntry);
      MPF.GetEntry(iEntry);
      MTrigger.GetEntry(iEntry);

      if(IsData == true)
      {
         if(MTrigger.CheckTrigger("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v1") == false)
            continue;
         if(MSkim.HBHENoise == false)
            continue;
      }

      double EventRho = GetRho(MRho.EtaMax, MRho.Rho, 0);

      int Tries = 1;
      for(int iT = 0; iT < Tries; iT++)
      {
         double Eta = DrawRandom(-1, 1);
         double Phi = DrawRandom(0, 2 * PI);

         double TotalPT = 0;
         for(int iC = 0; iC < (int)MPF.PT->size(); iC++)
         {
            if(Eta - (*MPF.Eta)[iC] > 0.4 || Eta - (*MPF.Eta)[iC] < -0.4)
               continue;

            double DPhi = GetDPhi(Phi, (*MPF.Phi)[iC]);
            double DEta = Eta - (*MPF.Eta)[iC];
            if(DPhi * DPhi + DEta * DEta < 0.4 * 0.4)
               TotalPT = TotalPT + (*MPF.PT)[iC];
         }

         if(TotalPT <= 0)   // WTF
            continue;

         HTotalPT.Fill(TotalPT);

         double SubtractedPT = TotalPT - 0.4 * 0.4 * PI * EventRho;

         if(fabs(SubtractedPT) > 1e-5)
         {
            HSubtractedPTHFEnergy.Fill(MHiEvent.hiHFplusEta4, SubtractedPT);
            HSubtractedPTRatioHFEnergy.Fill(MHiEvent.hiHFplusEta4, SubtractedPT / TotalPT);
            HSubtractedPT.Fill(SubtractedPT);
         }
      }
   }

   HSubtractedPTHFEnergy.Write();
   HSubtractedPTRatioHFEnergy.Write();
   HSubtractedPT.Write();
   HTotalPT.Write();

   OutputFile.Close();

   InputFile.Close();
}

double GetDPhi(double phi1, double phi2)
{
   double dphi = phi1 - phi2;

   if(dphi < -PI)   dphi = dphi + 2 * PI;
   if(dphi > +PI)   dphi = dphi - 2 * PI;

   return dphi;
}






