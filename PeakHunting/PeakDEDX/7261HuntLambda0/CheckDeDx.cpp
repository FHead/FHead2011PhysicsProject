#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"
#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"
#include "ParticleInfo.h"

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
   float TrackVx[1000] = {0};
   float TrackVy[1000] = {0};
   float TrackVz[1000] = {0};
   float TrackCharge[1000] = {0};
   int TrackQuality[1000] = {0};

   Tree.SetBranchAddress("nTrack", &TrackCount);
   Tree.SetBranchAddress("harmonic2DeDxTrack", TrackDEDX);
   Tree.SetBranchAddress("pxTrack", TrackPx);
   Tree.SetBranchAddress("pyTrack", TrackPy);
   Tree.SetBranchAddress("pzTrack", TrackPz);
   Tree.SetBranchAddress("trackVxTrack", TrackVx);
   Tree.SetBranchAddress("trackVyTrack", TrackVy);
   Tree.SetBranchAddress("trackVzTrack", TrackVz);
   Tree.SetBranchAddress("qualityMaskTrack", TrackQuality);
   Tree.SetBranchAddress("chargeTrack", TrackCharge);

   Tree.SetBranchStatus("*", false);
   Tree.SetBranchStatus("*Track", true);
   Tree.SetBranchStatus("*GsfTrack", false);
   Tree.SetBranchStatus("*MuonTrack", false);

   TFile OutputFile("Histograms.root", "recreate");

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
   
   TH1D HProtonCloseTrackOppositeSignMass("HProtonCloseTrackOppositeSignMass",
      "Proton candidate + close-by track invariant mass (opposite sign)", 100, 0, 5);
   TH1D HProtonCloseTrackSameSignMass("HProtonCloseTrackSameSignMass",
      "Proton candidate + close-by track invariant mass (same sign)", 100, 0, 5);
   TH1D HProtonCloseTrackDifferenceMass("HProtonCloseTrackDifferenceMass",
      "Proton candidate + close-by track invariant mass (opposite sign - same sign)", 100, 0, 5);
   TH1D HProtonCloseTrackDifferenceMassZoomIn("HProtonCloseTrackDifferenceMassZoomIn",
      "Proton candidate + close-by track invariant mass (opposite sign - same sign)", 25, 1.10, 1.15);

   TH1D HProtonSimilarTrackOppositeSignMass("HProtonSimilarTrackOppositeSignMass",
      "Proton candidate + similar track invariant mass (opposite sign)", 100, 1, 1.5);
   TH1D HProtonSimilarTrackSameSignMass("HProtonSimilarTrackSameSignMass",
      "Proton candidate + similar track invariant mass (same sign)", 100, 1, 1.5);
   TH1D HProtonSimilarTrackOppositeSignMassZoomIn("HProtonSimilarTrackOppositeSignMassZoomIn",
      "Proton candidate + similar track invariant mass (opposite sign)", 50, 1.098, 1.175);
   TH1D HProtonSimilarTrackSameSignMassZoomIn("HProtonSimilarTrackSameSignMassZoomIn",
      "Proton candidate + similar track invariant mass (same sign)", 50, 1.098, 1.175);
   TH1D HProtonSimilarTrackDifferenceMass("HProtonSimilarTrackDifferenceMass",
      "Proton candidate + similar track invariant mass (opposite sign - same sign)", 100, 1, 1.5);
   TH1D HProtonSimilarTrackDifferenceMassZoomIn("HProtonSimilarTrackDifferenceMassZoomIn",
      "Proton candidate + similar track invariant mass (opposite sign - same sign);Invariant mass (GeV/c^{2})",
      50, 1.098, 1.175);

   ParticleInformation Info;

   cout << "p mass = " << Info["p"].Mass << endl;
   cout << "pi0 mass = " << Info["pi0"].Mass << endl;
   double ProtonMass = Info["p"].Mass;
   double PiMass = Info["pi+"].Mass;

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;
      // if(iEntry >= 50000)
      //    break;

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
         FourVector ProtonP(0, TrackPx[ProtonCandidates[j]], TrackPy[ProtonCandidates[j]],
            TrackPz[ProtonCandidates[j]]);
         ProtonP[0] = sqrt(ProtonP.GetP() * ProtonP.GetP() + ProtonMass * ProtonMass);

         /*
         double ProtonVT = sqrt(TrackVx[ProtonCandidates[j]] * TrackVx[ProtonCandidates[j]]
            + TrackVy[ProtonCandidates[j]] * TrackVy[ProtonCandidates[j]]);
         if(ProtonVT < 0.5)
            continue;
         */

         for(int i = 0; i < TrackCount; i++)
         {
            if(i == ProtonCandidates[j])
               continue;

            FourVector TrackP(0, TrackPx[i], TrackPy[i], TrackPz[i]);
            TrackP[0] = sqrt(TrackP.GetP() * TrackP.GetP() + PiMass * PiMass);

            if(TrackQuality[i] % 4 < 2)   // "tight" track quality bit
               continue;
            // if(TrackPT < 0)   // too low....
            //    continue;
            // if(fabs(TrackEta) > 1.5)   // look at barrel-only for now
            //    continue;
         
            const double C = 2.495;
            const double K = 2.625;
            double M = TrackP.GetP() * sqrt((TrackDEDX[i] - C) / K);

            if(TrackDEDX[i] > 4)   // want stuff in the lower big band
               continue;

            FourVector TotalP = TrackP + ProtonP;
            double Mass = TotalP.GetMass();

            double DeltaR = GetDR(TrackP, ProtonP);
            double ProtonGamma = ProtonP[0] / ProtonP.GetMass();
            double TrackGamma = TrackP[0] / TrackP.GetMass();
            double DeltaGamma = fabs(TrackP.GetGamma() - ProtonP.GetGamma()) / ProtonP.GetGamma();

            // double TrackVT = sqrt(TrackVx[i] * TrackVx[i] + TrackVy[i] * TrackVy[i]);
            // if(TrackVT < 0.5)
            //    continue;

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
            
            if(TrackCharge[i] * TrackCharge[ProtonCandidates[j]] < 0 && DeltaR < 0.2)
            {
               HProtonCloseTrackOppositeSignMass.Fill(Mass);
               HProtonCloseTrackDifferenceMass.Fill(Mass, 1);
               HProtonCloseTrackDifferenceMassZoomIn.Fill(Mass, 1);
            }
            if(TrackCharge[i] * TrackCharge[ProtonCandidates[j]] > 0 && DeltaR < 0.2)
            {
               HProtonCloseTrackSameSignMass.Fill(Mass);
               HProtonCloseTrackDifferenceMass.Fill(Mass, -1);
               HProtonCloseTrackDifferenceMassZoomIn.Fill(Mass, -1);
            }
            
            if(TrackCharge[i] * TrackCharge[ProtonCandidates[j]] < 0 && DeltaR < 0.5 && DeltaGamma < 5)
            {
               HProtonSimilarTrackOppositeSignMass.Fill(Mass);
               HProtonSimilarTrackOppositeSignMassZoomIn.Fill(Mass);
               HProtonSimilarTrackDifferenceMass.Fill(Mass, 1);
               HProtonSimilarTrackDifferenceMassZoomIn.Fill(Mass, 1);
            }
            if(TrackCharge[i] * TrackCharge[ProtonCandidates[j]] > 0 && DeltaR < 0.5 && DeltaGamma < 5)
            {
               HProtonSimilarTrackSameSignMass.Fill(Mass);
               HProtonSimilarTrackSameSignMassZoomIn.Fill(Mass);
               HProtonSimilarTrackDifferenceMass.Fill(Mass, -1);
               HProtonSimilarTrackDifferenceMassZoomIn.Fill(Mass, -1);
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
   
   PsFile.AddPlot(HProtonCloseTrackOppositeSignMass, "", true);
   PsFile.AddPlot(HProtonCloseTrackSameSignMass, "", true);
   PsFile.AddPlot(HProtonCloseTrackDifferenceMass, "");
   PsFile.AddPlot(HProtonCloseTrackDifferenceMassZoomIn, "");

   PsFile.AddPlot(HProtonSimilarTrackOppositeSignMass, "", true);
   PsFile.AddPlot(HProtonSimilarTrackSameSignMass, "", true);
   PsFile.AddPlot(HProtonSimilarTrackDifferenceMass, "");

   TCanvas C;
   HProtonSimilarTrackOppositeSignMassZoomIn.SetTitle("Comparison between opposite-sign pair and same-sign pair");
   HProtonSimilarTrackOppositeSignMassZoomIn.GetXaxis()->SetTitle("p #pi candidate invariant mass (GeV/c^{2})");
   HProtonSimilarTrackOppositeSignMassZoomIn.GetYaxis()->SetTitle("Count / bin");
   HProtonSimilarTrackOppositeSignMassZoomIn.SetStats(0);
   HProtonSimilarTrackOppositeSignMassZoomIn.Draw();
   HProtonSimilarTrackSameSignMassZoomIn.SetLineColor(kRed);
   HProtonSimilarTrackSameSignMassZoomIn.SetStats(0);
   HProtonSimilarTrackSameSignMassZoomIn.Draw("same");
   TLegend legend(0.5, 0.4, 0.8, 0.2);
   legend.SetTextFont(42);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.AddEntry(&HProtonSimilarTrackOppositeSignMassZoomIn, "Opposite sign", "l");
   legend.AddEntry(&HProtonSimilarTrackSameSignMassZoomIn, "Same sign", "l");
   legend.Draw();
   PsFile.AddCanvas(C);

   HProtonSimilarTrackDifferenceMassZoomIn.SetTitle("Difference between opposite-sign and same-sign pairs");
   HProtonSimilarTrackDifferenceMassZoomIn.SetStats(0);
   HProtonSimilarTrackDifferenceMassZoomIn.GetYaxis()->SetTitle("Count / bin");
   HProtonSimilarTrackDifferenceMassZoomIn.GetXaxis()->SetTitle("p #pi candidate invariant mass (GeV/c^{2})");
   PsFile.AddPlot(HProtonSimilarTrackDifferenceMassZoomIn, "");

   TF1 F("F", "gaus+pol3(3)", 1.097, 1.175);
   F.SetParameter(0, 864.058);
   F.SetParameter(1, 1.11577);
   F.SetParameter(2, 0.00531405);
   F.SetParameter(3, -373107);
   F.SetParameter(4, 769185);
   F.SetParameter(5, -484575);
   F.SetParameter(6, 85364.1);
   F.SetLineColor(kGreen);
   HProtonSimilarTrackDifferenceMassZoomIn.Fit(&F, "", "", 1.097, 1.175);

   TF1 FSignalOnly("FSignalOnly", "gaus", 1.097, 1.175);
   for(int i = 0; i < 3; i++)
      FSignalOnly.SetParameter(i, F.GetParameter(i));
   FSignalOnly.SetLineColor(kBlue);
   
   TF1 FBackgroundOnly("FBackgroundOnly", "pol3", 1.097, 1.175);
   for(int i = 0; i < 4; i++)
      FBackgroundOnly.SetParameter(i, F.GetParameter(i+3));
   FBackgroundOnly.SetLineColor(kRed);

   TLatex latex;
   latex.SetTextSize(0.04);
   latex.SetTextFont(42);
   latex.SetNDC();

   TCanvas FitCanvas;
   HProtonSimilarTrackDifferenceMassZoomIn.Draw();
   FSignalOnly.Draw("same");
   FBackgroundOnly.Draw("same");
   latex.DrawLatex(0.55, 0.80, Form("Mean = %.5f #pm %.5f", F.GetParameter(1), F.GetParError(1)));
   latex.DrawLatex(0.55, 0.75, Form("Width = %.5f #pm %.5f", F.GetParameter(2), F.GetParError(2)));
   PsFile.AddCanvas(FitCanvas);

   PsFile.AddTimeStampPage();
   PsFile.Close();
   
   HTrackCount.Write();
   HTrackPT.Write();
   HTrackEta.Write();
   HTrackPVsDEDX.Write();
   HTrackM.Write();
   HTrackMDEDX45.Write();
   HTrackMDEDX45ZoomIn.Write();

   HProtonCandidateCount.Write();
   HProtonTrackOppositeSignMass.Write();
   HProtonTrackSameSignMass.Write();
   HProtonTrackDifferenceMass.Write();
   
   HProtonCloseTrackOppositeSignMass.Write();
   HProtonCloseTrackSameSignMass.Write();
   HProtonCloseTrackDifferenceMass.Write();
   HProtonCloseTrackDifferenceMassZoomIn.Write();

   HProtonSimilarTrackOppositeSignMass.Write();
   HProtonSimilarTrackSameSignMass.Write();
   HProtonSimilarTrackDifferenceMass.Write();
   
   HProtonSimilarTrackOppositeSignMassZoomIn.Write();
   HProtonSimilarTrackSameSignMassZoomIn.Write();
   HProtonSimilarTrackDifferenceMassZoomIn.Write();

   OutputFile.Close();

   return 0;
}




