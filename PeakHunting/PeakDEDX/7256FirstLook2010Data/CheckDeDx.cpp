#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TChain.h"

#include "SetStyle.h"
#include "PlotHelper2.h"

int main(int argc, char *argv[])
{
   SetStyle();

   TChain Tree("ntp1", "ntp1");
   Tree.AddFile("Jet_146511.root");

   int TrackCount = 0;
   float TrackDEDX[1000] = {0};
   float TrackPx[1000] = {0};
   float TrackPy[1000] = {0};
   float TrackPz[1000] = {0};
   float TrackCharge[1000] = {0};
   int TrackQuality[1000] = {0};

   Tree.SetBranchAddress("nTrack", &TrackCount);
   Tree.SetBranchAddress("harmonic2DeDxTrack", TrackDEDX);
   Tree.SetBranchAddress("pxTrack", TrackPx);
   Tree.SetBranchAddress("pyTrack", TrackPy);
   Tree.SetBranchAddress("pzTrack", TrackPz);
   Tree.SetBranchAddress("qualityMaskTrack", TrackQuality);
   Tree.SetBranchAddress("chargeTrack", TrackCharge);

   Tree.SetBranchStatus("*", false);
   Tree.SetBranchStatus("*Track", true);
   Tree.SetBranchStatus("*GsfTrack", false);
   Tree.SetBranchStatus("*MuonTrack", false);

   TH1D HTrackCount("HTrackCount", "Number of tracks above 0.1 GeV/c PT", 201, -0.5, 200.5);
   TH1D HTrackPT("HTrackPT", "Track PT", 100, 0, 100);
   TH1D HTrackEta("HTrackEta", "Track Eta", 100, -5, 5);
   TH2D HTrackPVsDEDX("HTrackPVsDEDX", "Track P vs. dE/dx;P (GeV/c);dE/dx (MeV/cm)", 100, 0, 5, 100, 0, 10);
   TH1D HTrackM("HTrackM", "M (== P * Sqrt((DEDX - C) / K))", 100, 0, 5);
   TH1D HTrackMDEDX45("HTrackMDEDX45", "M (== P * Sqrt((DEDX - C) / K)), dE/dx > 4.5", 100, 0, 5);
   TH1D HTrackMDEDX45ZoomIn("HTrackMDEDX45ZoomIn", "M (== P * Sqrt((DEDX - C) / K)), dE/dx > 4.5", 100, 0, 2);

   TH1D HProtonCandidateCount("HProtonCandidateCount",
      "Number of proton candidates (M = 0.8-1.2, dE/dx > 4.5)", 10, -0.5, 9.5);
   TH1D HProtonTrackOppositeSignMass("HProtonTrackOppositeSignMass",
      "Proton candidate + track invariant mass (opposite sign)", 100, 0, 5);
   TH1D HProtonTrackSameSignMass("HProtonTrackSameSignMass",
      "Proton candidate + track invariant mass (same sign)", 100, 0, 5);
   TH1D HProtonTrackDifferenceMass("HProtonTrackDifferenceMass",
      "Proton candidate + track invariant mass (opposite sign - same sign)", 100, 0, 5);

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;
      if(iEntry >= 50000)
         break;

      Tree.GetEntry(iEntry);

      int GoodTrackCount = 0;
      vector<int> ProtonCandidates;

      for(int i = 0; i < TrackCount; i++)
      {
         double TrackPT = sqrt(TrackPx[i] * TrackPx[i] + TrackPy[i] * TrackPy[i]);
         double TrackP = sqrt(TrackPT * TrackPT + TrackPz[i] * TrackPz[i]);
         double TrackEta = 0.5 * log((TrackP - TrackPz[i]) / (TrackP + TrackPz[i]));

         if(TrackQuality[i] % 4 < 2)   // "tight" track quality bit
            continue;
         
         HTrackPT.Fill(TrackPT);
         HTrackEta.Fill(TrackEta);

         if(TrackPT < 0.1)   // too low....
            continue;
         if(fabs(TrackEta) > 1.5)   // look at barrel-only for now
            continue;

         GoodTrackCount = GoodTrackCount + 1;

         if(TrackDEDX[i] > 0)
            HTrackPVsDEDX.Fill(TrackP, TrackDEDX[i]);

         const double C = 2.495;
         const double K = 2.625;
         double M = TrackP * sqrt((TrackDEDX[i] - C) / K);

         HTrackM.Fill(M);
         if(TrackDEDX[i] > 4.5)
         {
            HTrackMDEDX45.Fill(M);
            HTrackMDEDX45ZoomIn.Fill(M);
         }

         if(TrackDEDX[i] > 4.5 && M > 0.8 && M < 1.2)
            ProtonCandidates.push_back(i);
      }

      HTrackCount.Fill(GoodTrackCount);
      HProtonCandidateCount.Fill(ProtonCandidates.size());

      for(int j = 0; j < (int)ProtonCandidates.size(); j++)
      {
         double ProtonP = sqrt(TrackPx[ProtonCandidates[j]] * TrackPx[ProtonCandidates[j]]
            + TrackPy[ProtonCandidates[j]] * TrackPy[ProtonCandidates[j]]
            + TrackPz[ProtonCandidates[j]] * TrackPz[ProtonCandidates[j]]);
         double ProtonE = sqrt(ProtonP * ProtonP + 0.938272013 * 0.938272013);   // assume protons

         for(int i = 0; i < TrackCount; i++)
         {
            double TrackPT = sqrt(TrackPx[i] * TrackPx[i] + TrackPy[i] * TrackPy[i]);
            double TrackP = sqrt(TrackPT * TrackPT + TrackPz[i] * TrackPz[i]);
            double TrackEta = 0.5 * log((TrackP - TrackPz[i]) / (TrackP + TrackPz[i]));
            double TrackE = sqrt(TrackP * TrackP + 0.145 * 0.145);   // assume pions

            if(TrackQuality[i] % 4 < 2)   // "tight" track quality bit
               continue;
            // if(TrackPT < 0)   // too low....
            //    continue;
            // if(fabs(TrackEta) > 1.5)   // look at barrel-only for now
            //    continue;
         
            const double C = 2.495;
            const double K = 2.625;
            double M = TrackP * sqrt((TrackDEDX[i] - C) / K);

            if(TrackDEDX[i] > 4)   // want stuff in the lower big band
               continue;

            double TotalPx = TrackPx[i] + TrackPx[ProtonCandidates[j]];
            double TotalPy = TrackPy[i] + TrackPy[ProtonCandidates[j]];
            double TotalPz = TrackPz[i] + TrackPz[ProtonCandidates[j]];
            double TotalE = TrackE + ProtonE;

            double Mass = sqrt(TotalE * TotalE - TotalPx * TotalPx - TotalPy * TotalPy - TotalPz * TotalPz);

            if(TrackCharge[i] * TrackCharge[ProtonCandidates[j]] < 0)   // opposite sign
            {
               HProtonTrackOppositeSignMass.Fill(Mass);
               HProtonTrackDifferenceMass.Fill(Mass, 1);
            }
            if(TrackCharge[i] * TrackCharge[ProtonCandidates[j]] > 0)   // same sign!
            {
               HProtonTrackSameSignMass.Fill(Mass);
               HProtonTrackDifferenceMass.Fill(Mass, -1);
            }
         }
      }
   }

   PsFileHelper PsFile("Tracking.ps");
   PsFile.AddTextPage("First look at tracking");

   PsFile.AddPlot(HTrackCount, "", true);
   PsFile.AddPlot(HTrackPT, "", true);
   PsFile.AddPlot(HTrackEta, "", false);
   PsFile.AddPlot(HTrackPVsDEDX, "colz", false, true);
   PsFile.AddPlot(HTrackM, "", true);
   PsFile.AddPlot(HTrackMDEDX45, "", true);
   PsFile.AddPlot(HTrackMDEDX45ZoomIn, "", true);

   PsFile.AddPlot(HProtonCandidateCount, "", true);
   PsFile.AddPlot(HProtonTrackOppositeSignMass, "", true);
   PsFile.AddPlot(HProtonTrackSameSignMass, "", true);
   PsFile.AddPlot(HProtonTrackDifferenceMass, "");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}




