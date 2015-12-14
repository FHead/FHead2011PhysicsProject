#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "TauHelperFunctions2.h"
#include "SetStyle.h"
#include "PlotHelper2.h"
#include "ParticleInfo.h"

int main()
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

   int VertexCount = 0;
   double VertexDOF[50] = {0};
   double VertexX[50] = {0};
   double VertexY[50] = {0};
   double VertexZ[50] = {0};
   double VertexSumPT[50] = {0};

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

   Tree.SetBranchAddress("nPV", &VertexCount);
   Tree.SetBranchAddress("ndofPV", &VertexDOF);
   Tree.SetBranchAddress("PVxPV", &VertexX);
   Tree.SetBranchAddress("PVyPV", &VertexY);
   Tree.SetBranchAddress("PVzPV", &VertexZ);
   Tree.SetBranchAddress("SumPtPV", &VertexSumPT);

   Tree.SetBranchStatus("*", false);
   Tree.SetBranchStatus("*Track", true);
   Tree.SetBranchStatus("*GsfTrack", false);
   Tree.SetBranchStatus("*MuonTrack", false);
   Tree.SetBranchStatus("*PV", true);

   TFile OutputFile("Histograms.root", "recreate");

   TH1D HGoodVertexCount("HGoodVertexCount", "Good vertex count", 11, -0.5, 10.5);
   TH1D HTrackCount1GeV("HTrackCount1GeV", "Track count above 1 GeV", 101, -0.5, 100.5);
   TH1D HTrackCount2GeV("HTrackCount2GeV", "Track count above 2 GeV", 101, -0.5, 100.5);
   TH1D HPairAfterPTSelection("HPairAfterPTSeletcion",
      "Number of pairs after PT selections on tracks", 4001, -0.5, 4000.5);
   TH1D HPairAfterPTAndMassSelection("HPairAfterPTAndMassSeletcion",
      "Number of pairs after PT selections on tracks and mass", 1001, -0.5, 1000.5);
   TH1D HMassAfterPTAndMassSelection("HMassAfterPTAndMassSeletcion",
      "Mass of pairs after PT selections on tracks and mass", 100, 1.0, 1.5);
   TH1D HClosestDistance("HClosestDistance",
      "Closest distance of pairs after PT and mass selection;Distance (cm)", 100, 0, 10);
   TH1D HClosestDistanceZoomIn("HClosestDistanceZoomIn",
      "Closest distance of pairs after PT and mass selection;Distance (cm)", 100, 0, 0.1);
   TH1D HVertexDistance("HVertexDistance", "Vertex distance to closest crossing point;Distance (cm)", 100, 0, 100);
   TH2D HClosestDistanceVsVertexDistance("HClosestDistanceVsVertexDistance",
      "Closest distance vs. vertex distance;Closest distance (cm);Vertex distance (cm)", 100, 0, 10, 100, 0, 100);
   TH1D HPointingAngle("HPointingAngle", "Pointing angle (rad)", 100, 0, 3.2);
   TH1D HMassAfterPTMassAndDistanceSelection("HMassAfterPTMassAndDistanceSeletcion",
      "Mass of pairs after PT selections on tracks and mass and distances", 100, 1.0, 1.5);
   TH1D HMassAfterPTMassAndDistanceSelectionSameSign("HMassAfterPTMassAndDistanceSeletcionSameSign",
      "Mass of pairs after PT selections on tracks and mass and distances (same sign)", 100, 1.0, 1.5);
   TH1D HMassAfterPTMassAndDistanceSelectionDifference("HMassAfterPTMassAndDistanceSeletcionDifference",
      "Mass of pairs after PT selections on tracks and mass and distances (difference)", 100, 1.0, 1.5);
   TH1D HMassAfterPTMassAndDistanceSelectionSameSignPlus("HMassAfterPTMassAndDistanceSeletcionSameSignPlus",
      "Mass of pairs after PT selections on tracks and mass and distances (same sign, +)", 100, 1.0, 1.5);
   TH1D HMassAfterPTMassAndDistanceSelectionSameSignMinus("HMassAfterPTMassAndDistanceSeletcionSameSignMinus",
      "Mass of pairs after PT selections on tracks and mass and distances (same sign, -)", 100, 1.0, 1.5);
   TH1D HMassAfterPTMassAndDistanceSelectionPiPi("HMassAfterPTMassAndDistanceSeletcionPiPi",
      "Mass of pairs after PT selections on tracks and mass and distances (opposite sign, pipi)", 100, 0.0, 1.0);
   TH1D HMassAfterPTMassAndDistanceSelectionSameSignPiPi("HMassAfterPTMassAndDistanceSeletcionSameSignPiPi",
      "Mass of pairs after PT selections on tracks and mass and distances (same sign, pipi)", 100, 0.0, 1.0);

   ParticleInformation Info;
   double ProtonMass = Info["p"].Mass;
   double PionMass = Info["pi+"].Mass;

   int EntryCount = Tree.GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 10000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;
      // if(iEntry >= 50000)
      //    break;

      Tree.GetEntry(iEntry);

      int BestVertexIndex = -1;
      int GoodVertexCount = 0;
      for(int i = 0; i < VertexCount; i++)
      {
         if(VertexDOF[i] <= 4)   continue;
         if(VertexX[i] * VertexX[i] + VertexY[i] * VertexY[i] > 2 * 2)   continue;
         if(VertexZ[i] > 15 || VertexZ[i] < -15)   continue;

         GoodVertexCount = GoodVertexCount + 1;

         if(BestVertexIndex == -1)
            BestVertexIndex = i;
         else if(VertexSumPT[BestVertexIndex] < VertexSumPT[i])
            BestVertexIndex = i;
      }
      HGoodVertexCount.Fill(GoodVertexCount);

      if(GoodVertexCount == 0)
         continue;
      assert(BestVertexIndex >= 0);

      FourVector VertexV(0, VertexX[BestVertexIndex], VertexY[BestVertexIndex], VertexZ[BestVertexIndex]);
      
      int TrackCount1GeV = 0;
      int TrackCount2GeV = 0;
      for(int i = 0; i < TrackCount; i++)
      {
         if(TrackQuality[i] % 4 < 2)   // "tight" track quality bit
            continue;

         double TrackPT = sqrt(TrackPx[i] * TrackPx[i] + TrackPy[i] * TrackPy[i]);

         if(TrackPT > 1)
            TrackCount1GeV = TrackCount1GeV + 1;
         if(TrackPT > 2)
            TrackCount2GeV = TrackCount2GeV + 1;
      }
      HTrackCount1GeV.Fill(TrackCount1GeV);
      HTrackCount2GeV.Fill(TrackCount2GeV);

      int PairAfterPTSelection = 0;
      int PairAfterPTAndMassSelection = 0;
      for(int i = 0; i < TrackCount; i++)
      {
         if(TrackQuality[i] % 4 < 2)   // "tight" track quality bit
            continue;
         
         FourVector ProtonCandidate(0, TrackPx[i], TrackPy[i], TrackPz[i]);
         ProtonCandidate[0] = sqrt(ProtonCandidate.GetP() * ProtonCandidate.GetP() + ProtonMass * ProtonMass);
         FourVector ProtonCandidatePi(0, TrackPx[i], TrackPy[i], TrackPz[i]);
         ProtonCandidatePi[0] = sqrt(ProtonCandidate.GetP() * ProtonCandidate.GetP() + PionMass * PionMass);

         if(ProtonCandidate.GetPT() < 1)   // too small
            continue;

         for(int j = 0; j < TrackCount; j++)
         {
            if(i == j)
               continue;
         
            if(TrackQuality[j] % 4 < 2)   // "tight" track quality bit
               continue;

            FourVector PionCandidate(0, TrackPx[j], TrackPy[j], TrackPz[j]);
            PionCandidate[0] = sqrt(PionCandidate.GetP() * PionCandidate.GetP() + PionMass * PionMass);

            if(PionCandidate.GetPT() < 0.4)
               continue;
            if(PionCandidate.GetPT() > ProtonCandidate.GetPT())
               continue;

            FourVector Combined = PionCandidate + ProtonCandidate;
            FourVector CombinedPiPi = PionCandidate + ProtonCandidatePi;
            if(Combined.GetPT() < 2)   // too small again
               continue;

            PairAfterPTSelection = PairAfterPTSelection + 1;

            if(Combined.GetMass() > 3)   // cut down on number
               continue;
            
            PairAfterPTAndMassSelection = PairAfterPTAndMassSelection + 1;
      
            if(TrackCharge[i] * TrackCharge[j] < 0)
               HMassAfterPTAndMassSelection.Fill(Combined.GetMass());

            FourVector V1(0, TrackVx[i], TrackVy[i], TrackVz[i]);
            FourVector V2(0, TrackVx[j], TrackVy[j], TrackVz[j]);
            FourVector P1(0, TrackPx[i], TrackPy[i], TrackPz[i]);
            FourVector P2(0, TrackPx[j], TrackPy[j], TrackPz[j]);

            double P1P1 = P1.SpatialDot(P1);
            double P1P2 = P1.SpatialDot(P2);
            double P2P2 = P2.SpatialDot(P2);
            double V1P1 = V1.SpatialDot(P1);
            double V1P2 = V1.SpatialDot(P2);
            double V2P1 = V2.SpatialDot(P1);
            double V2P2 = V2.SpatialDot(P2);

            // P1P1 L1 - P1P2 L2 = V2P1 - V1P1
            // P1P2 L1 - P2P2 L2 = V2P2 - V1P2
            
            double L1 = ((V2P1 - V1P1) * P2P2 - (V2P2 - V1P2) * P1P2) / (P1P1 * P2P2 - P1P2 * P1P2);
            double L2 = ((V1P2 - V2P2) * P1P1 - (V1P1 - V2P1) * P1P2) / (P2P2 * P1P1 - P1P2 * P1P2);

            FourVector N1 = V1 + P1 * L1;
            FourVector N2 = V2 + P2 * L2;
            double Distance = (N1 - N2).GetP();
            FourVector N = (N1 + N2) / 2;
            double PVDistance = (N - VertexV).GetP();

            if(TrackCharge[i] * TrackCharge[j] < 0)
            {
               HClosestDistance.Fill(Distance);
               HClosestDistanceZoomIn.Fill(Distance);
               HVertexDistance.Fill(PVDistance);
               HClosestDistanceVsVertexDistance.Fill(Distance, PVDistance);
            }
            
            if(Distance > 0.1)   // 1 mm is huge
               continue;
            if(PVDistance < 1)   // lambda is displaced by nature
               continue;
           
            /*
            if(GetDR(ProtonCandidate, PionCandidate) > 0.5)
               continue;
            if(fabs((ProtonCandidate.GetGamma() - PionCandidate.GetGamma()) / ProtonCandidate.GetGamma()) > 2)
               continue;
            */

            double PointingAngle = acos((N - VertexV).SpatialDot(Combined) / Combined.GetP() / PVDistance);
            if(TrackCharge[i] * TrackCharge[j] < 0)
               HPointingAngle.Fill(PointingAngle);

            if(fabs(PointingAngle) > 0.1)
               continue;
            
            if(TrackCharge[i] * TrackCharge[j] < 0)
            {
               HMassAfterPTMassAndDistanceSelection.Fill(Combined.GetMass());
               HMassAfterPTMassAndDistanceSelectionDifference.Fill(Combined.GetMass());
               HMassAfterPTMassAndDistanceSelectionPiPi.Fill(CombinedPiPi.GetMass());
            }
            else if(TrackCharge[i] * TrackCharge[j] > 0)
            {
               HMassAfterPTMassAndDistanceSelectionSameSign.Fill(Combined.GetMass());
               HMassAfterPTMassAndDistanceSelectionDifference.Fill(Combined.GetMass(), -1);
               HMassAfterPTMassAndDistanceSelectionSameSignPiPi.Fill(CombinedPiPi.GetMass());
               
               if(TrackCharge[i] > 0)
                  HMassAfterPTMassAndDistanceSelectionSameSignPlus.Fill(Combined.GetMass());
               if(TrackCharge[i] < 0)
                  HMassAfterPTMassAndDistanceSelectionSameSignMinus.Fill(Combined.GetMass());
            }
         }
      }
      HPairAfterPTSelection.Fill(PairAfterPTSelection);
      HPairAfterPTAndMassSelection.Fill(PairAfterPTAndMassSelection);
   }

   PsFileHelper PsFile("Tracking.ps");
   PsFile.AddTextPage("Playing with tracking");

   PsFile.AddPlot(HGoodVertexCount, "", true);
   PsFile.AddPlot(HTrackCount1GeV, "", true);
   PsFile.AddPlot(HTrackCount2GeV, "", true);
   PsFile.AddPlot(HPairAfterPTSelection, "", true);
   PsFile.AddPlot(HPairAfterPTAndMassSelection, "", true);
   PsFile.AddPlot(HMassAfterPTAndMassSelection, "", false);
   PsFile.AddPlot(HClosestDistance, "", true);
   PsFile.AddPlot(HClosestDistanceZoomIn, "", true);
   PsFile.AddPlot(HVertexDistance, "", true);
   PsFile.AddPlot(HClosestDistanceVsVertexDistance, "colz", false, true);
   PsFile.AddPlot(HPointingAngle, "", true);
   PsFile.AddPlot(HMassAfterPTMassAndDistanceSelection, "", false);
   PsFile.AddPlot(HMassAfterPTMassAndDistanceSelectionSameSign, "", false);
   PsFile.AddPlot(HMassAfterPTMassAndDistanceSelectionSameSignPlus, "", false);
   PsFile.AddPlot(HMassAfterPTMassAndDistanceSelectionSameSignMinus, "", false);
   PsFile.AddPlot(HMassAfterPTMassAndDistanceSelectionDifference, "", false);
   PsFile.AddPlot(HMassAfterPTMassAndDistanceSelectionPiPi, "", false);
   PsFile.AddPlot(HMassAfterPTMassAndDistanceSelectionSameSignPiPi, "", false);

   TCanvas OverlayCanvas;
   HMassAfterPTMassAndDistanceSelectionSameSign.SetStats(0);
   HMassAfterPTMassAndDistanceSelection.SetStats(0);
   HMassAfterPTMassAndDistanceSelection.SetTitle("Opposite sign pairs vs. same sign pairs");
   HMassAfterPTMassAndDistanceSelection.GetXaxis()->SetTitle("di-track invariant mass");
   HMassAfterPTMassAndDistanceSelectionSameSign.SetTitle("Opposite sign pairs vs. same sign pairs");
   HMassAfterPTMassAndDistanceSelectionSameSign.GetXaxis()->SetTitle("di-track invariant mass");
   HMassAfterPTMassAndDistanceSelectionSameSign.SetLineColor(kRed);
   HMassAfterPTMassAndDistanceSelectionSameSign.Draw();
   HMassAfterPTMassAndDistanceSelection.Draw("same");
   
   TLegend legend(0.2, 0.8, 0.4, 0.6);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
   legend.AddEntry(&HMassAfterPTMassAndDistanceSelection, "Opposite sign", "l");
   legend.AddEntry(&HMassAfterPTMassAndDistanceSelectionSameSign, "Same sign", "l");
   legend.Draw();

   PsFile.AddCanvas(OverlayCanvas);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   HTrackCount1GeV.Write();
   HTrackCount2GeV.Write();

   OutputFile.Close();

   return 0;
}




