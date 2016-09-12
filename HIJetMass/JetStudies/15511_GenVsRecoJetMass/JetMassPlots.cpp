#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"

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
   bool IsPP = IsPPFromTag(Tag);

   if(IsData == true)
   {
      cerr << "Let's rather not run on data." << endl;
      return -1;
   }

   TFile InputFile(Input.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSoftDropJet(InputFile, SoftDropJetTreeName);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TH2D HGenMassRecoMass("HGenMassRecoMass", ";Gen Mass;Reco Mass", 100, 0, 100, 100, 0, 100);
   TH2D HRecoMassOverGenMassPT("HRecoMassOverGenMassPT", "Reco Mass / Gen Mass - 1;Gen Jet PT;Mass Ratio", 100, 80, 500, 100, -1, 1);
   TProfile PRecoMassOverGenMassPT("PRecoMassOverGenMassPT", "Reco Mass / Gen Mass - 1;Gen Jet PT;Mass Ratio", 100, 80, 500);
   TProfile2D PRecoMassOverGenMassPTCentrality("PRecoMassOverGenMassPTCentrality", "Reco Mass / Gen Mass - 1;Gen Jet PT;Centrality;Mass Ratio", 100, 80, 500, 100, 0, 1);
   TH2D HRecoMassMinusGenMassPT("HRecoMassMinusGenMassPT", "Reco Mass - Gen Mass;Gen Jet PT;Mass Difference", 100, 80, 500, 100, -50, 50);
   TProfile PRecoMassMinusGenMassPT("PRecoMassMinusGenMassPT", "Reco Mass - Gen Mass;Gen Jet PT;Mass Difference", 100, 80, 500);
   TProfile2D PRecoMassMinusGenMassPTCentrality("PRecoMassMinusGenMassPTCentrality", "Reco Mass - Gen Mass;Gen Jet PT;Centrality;Mass Difference", 100, 80, 500, 100, 0, 1);

   TH2D HGenMassSDMass("HGenMassSDMass", ";Gen Mass;SD Mass", 100, 0, 100, 100, 0, 100);
   TH2D HSDMassOverGenMassPT("HSDMassOverGenMassPT", "SD Mass / Gen Mass - 1;Gen Jet PT;Mass Ratio", 100, 80, 500, 100, -1, 1);
   TProfile PSDMassOverGenMassPT("PSDMassOverGenMassPT", "SD Mass / Gen Mass - 1;Gen Jet PT;Mass Ratio", 100, 80, 500);
   TProfile2D PSDMassOverGenMassPTCentrality("PSDMassOverGenMassPTCentrality", "SD Mass / Gen Mass - 1;Gen Jet PT;Centrality;Mass Ratio", 100, 80, 500, 100, 0, 1);
   TH2D HSDMassMinusGenMassPT("HSDMassMinusGenMassPT", "SD Mass - Gen Mass;Gen Jet PT;Mass Difference", 100, 80, 500, 100, -50, 50);
   TProfile PSDMassMinusGenMassPT("PSDMassMinusGenMassPT", "SD Mass - Gen Mass;Gen Jet PT;Mass Difference", 100, 80, 500);
   TProfile2D PSDMassMinusGenMassPTCentrality("PSDMassMinusGenMassPTCentrality", "SD Mass - Gen Mass;Gen Jet PT;Centrality;Mass Difference", 100, 80, 500, 100, 0, 1);

   TH2D HRecoMassSDMass("HRecoMassSDMass", ";Reco Mass;SD Mass", 100, 0, 100, 100, 0, 100);
   TH2D HSDMassOverRecoMassPT("HSDMassOverRecoMassPT", "SD Mass / Reco Mass - 1;Reco Jet PT;Mass Ratio", 100, 80, 500, 100, -1, 1);
   TProfile PSDMassOverRecoMassPT("PSDMassOverRecoMassPT", "SD Mass / Reco Mass - 1;Reco Jet PT;Mass Ratio", 100, 80, 500);
   TProfile2D PSDMassOverRecoMassPTCentrality("PSDMassOverRecoMassPTCentrality", "SD Mass / Reco Mass - 1;Reco Jet PT;Centrality;Mass Ratio", 100, 80, 500, 100, 0, 1);
   TH2D HSDMassMinusRecoMassPT("HSDMassMinusRecoMassPT", "SD Mass - Reco Mass;Reco Jet PT;Mass Difference", 100, 80, 500, 100, -50, 50);
   TProfile PSDMassMinusRecoMassPT("PSDMassMinusRecoMassPT", "SD Mass - Reco Mass;Reco Jet PT;Mass Difference", 100, 80, 500);
   TProfile2D PSDMassMinusRecoMassPTCentrality("PSDMassMinusRecoMassPTCentrality", "SD Mass - Reco Mass;Reco Jet PT;Centrality;Mass Difference", 100, 80, 500, 100, 0, 1);

   TH2D HGenMassSDGenMass("HGenMassSDGenMass", ";Gen Mass;SDGen Mass", 100, 0, 100, 100, 0, 100);
   TH2D HGenPTSDGenPT("HGenPTSDGenPT", ";Gen PT;SDGen PT", 100, 0, 400, 100, 0, 400);
   TH2D HSDGenMassOverGenMassPT("HSDGenMassOverGenMassPT", "SDGen Mass / Gen Mass - 1;Gen Jet PT;Mass Ratio", 100, 80, 500, 100, -1, 1);
   TProfile PSDGenMassOverGenMassPT("PSDGenMassOverGenMassPT", "SDGen Mass / Gen Mass - 1;Gen Jet PT;Mass Ratio", 100, 80, 500);
   TProfile2D PSDGenMassOverGenMassPTCentrality("PSDGenMassOverGenMassPTCentrality", "SDGen Mass / Gen Mass - 1;Gen Jet PT;Centrality;Mass Ratio", 100, 80, 500, 100, 0, 1);
   TH2D HSDGenMassMinusGenMassPT("HSDGenMassMinusGenMassPT", "SDGen Mass - Gen Mass;Gen Jet PT;Mass Difference", 100, 80, 500, 100, -50, 50);
   TProfile PSDGenMassMinusGenMassPT("PSDGenMassMinusGenMassPT", "SDGen Mass - Gen Mass;Gen Jet PT;Mass Difference", 100, 80, 500);
   TProfile2D PSDGenMassMinusGenMassPTCentrality("PSDGenMassMinusGenMassPTCentrality", "SDGen Mass - Gen Mass;Gen Jet PT;Centrality;Mass Difference", 100, 80, 500, 100, 0, 1);

   TH2D HSDGenMassSDMass("HSDGenMassSDMass", ";SDGen Mass;SD Mass", 100, 0, 100, 100, 0, 100);
   TH2D HSDMassOverSDGenMassPT("HSDMassOverSDGenMassPT", "SD Mass / SDGen Mass - 1;SDGen Jet PT;Mass Ratio", 100, 80, 500, 100, -1, 1);
   TProfile PSDMassOverSDGenMassPT("PSDMassOverSDGenMassPT", "SD Mass / SDGen Mass - 1;SDGen Jet PT;Mass Ratio", 100, 80, 500);
   TProfile2D PSDMassOverSDGenMassPTCentrality("PSDMassOverSDGenMassPTCentrality", "SD Mass / SDGen Mass - 1;SDGen Jet PT;Centrality;Mass Ratio", 100, 80, 500, 100, 0, 1);
   TH2D HSDMassMinusSDGenMassPT("HSDMassMinusSDGenMassPT", "SD Mass - SDGen Mass;SDGen Jet PT;Mass Difference", 100, 80, 500, 100, -50, 50);
   TProfile PSDMassMinusSDGenMassPT("PSDMassMinusSDGenMassPT", "SD Mass - SDGen Mass;SDGen Jet PT;Mass Difference", 100, 80, 500);
   TProfile2D PSDMassMinusSDGenMassPTCentrality("PSDMassMinusSDGenMassPTCentrality", "SD Mass - SDGen Mass;SDGen Jet PT;Centrality;Mass Difference", 100, 80, 500, 100, 0, 1);

   TH1D HMatchingDR("HMatchingDR", "DR of matched jets", 100, 0, 1);

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSoftDropJet.GetEntry(iEntry);

      vector<int> Index = DRMatching(MJet.JetCount, MJet.RefEta, MJet.RefPhi,
         MSoftDropJet.JetCount, MSoftDropJet.JetEta, MSoftDropJet.JetPhi);

      for(int i = 0; i < MJet.JetCount; i++)
      {
         if(MJet.RefPT[i] < 80 || MJet.RefPT[i] > 500)
            continue;
         if(MJet.RefEta[i] < -1.3 || MJet.RefEta[i] > 1.3)
            continue;

         // Jet mass plots
         HGenMassRecoMass.Fill(MJet.RefM[i], MJet.JetM[i]);
         HRecoMassOverGenMassPT.Fill(MJet.RefPT[i], MJet.JetM[i] / MJet.RefM[i] - 1);
         HRecoMassMinusGenMassPT.Fill(MJet.RefPT[i], MJet.JetM[i] - MJet.RefM[i]);
         if(MJet.JetM[i] / MJet.RefM[i] < 5 && MJet.RefM[i] > 0.01)
         {
            PRecoMassOverGenMassPT.Fill(MJet.RefPT[i], MJet.JetM[i] / MJet.RefM[i] - 1);
            PRecoMassOverGenMassPTCentrality.Fill(MJet.RefPT[i], GetCentrality(MHiEvent.hiBin),
                  MJet.JetM[i] / MJet.RefM[i] - 1);
            PRecoMassMinusGenMassPT.Fill(MJet.RefPT[i], MJet.JetM[i] - MJet.RefM[i]);
            PRecoMassMinusGenMassPTCentrality.Fill(MJet.RefPT[i], GetCentrality(MHiEvent.hiBin),
                  MJet.JetM[i] - MJet.RefM[i]);
         }

         // matching between (gen) jets and soft drop jets
         double DPhi = MJet.RefPhi[i] - MSoftDropJet.JetPhi[Index[i]];
         double DEta = MJet.RefEta[i] - MSoftDropJet.JetEta[Index[i]];
         if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
         if(DPhi > +PI)   DPhi = DPhi - 2 * PI;
         double DR = sqrt(DPhi * DPhi + DEta * DEta);
         HMatchingDR.Fill(DR);

         if(DR > 0.2)
            continue;

         // SD Mass vs. original gen mass
         HGenMassSDMass.Fill(MJet.RefM[i], MSoftDropJet.JetM[Index[i]]);
         HSDMassOverGenMassPT.Fill(MJet.RefPT[i], MSoftDropJet.JetM[Index[i]] / MJet.RefM[i] - 1);
         HSDMassMinusGenMassPT.Fill(MJet.RefPT[i], MSoftDropJet.JetM[Index[i]] - MJet.RefM[i]);
         if(MSoftDropJet.JetM[Index[i]] / MJet.RefM[i] < 5 && MJet.RefM[i] > 0.01)
         {
            PSDMassOverGenMassPT.Fill(MJet.RefPT[i], MSoftDropJet.JetM[Index[i]] / MJet.RefM[i] - 1);
            PSDMassOverGenMassPTCentrality.Fill(MJet.RefPT[i], GetCentrality(MHiEvent.hiBin),
                  MSoftDropJet.JetM[Index[i]] / MJet.RefM[i] - 1);
            PSDMassMinusGenMassPT.Fill(MJet.RefPT[i], MSoftDropJet.JetM[Index[i]] - MJet.RefM[i]);
            PSDMassMinusGenMassPTCentrality.Fill(MJet.RefPT[i], GetCentrality(MHiEvent.hiBin),
                  MSoftDropJet.JetM[Index[i]] - MJet.RefM[i]);
         }

         // SD mass vs. reco jet mass
         HRecoMassSDMass.Fill(MJet.JetM[i], MSoftDropJet.JetM[Index[i]]);
         HSDMassOverRecoMassPT.Fill(MJet.JetPT[i], MSoftDropJet.JetM[Index[i]] / MJet.JetM[i] - 1);
         HSDMassMinusRecoMassPT.Fill(MJet.JetPT[i], MSoftDropJet.JetM[Index[i]] - MJet.JetM[i]);
         if(MSoftDropJet.JetM[Index[i]] / MJet.JetM[i] < 5 && MJet.JetM[i] > 0.01)
         {
            PSDMassOverRecoMassPT.Fill(MJet.JetPT[i], MSoftDropJet.JetM[Index[i]] / MJet.JetM[i] - 1);
            PSDMassOverRecoMassPTCentrality.Fill(MJet.JetPT[i], GetCentrality(MHiEvent.hiBin),
                  MSoftDropJet.JetM[Index[i]] / MJet.JetM[i] - 1);
            PSDMassMinusRecoMassPT.Fill(MJet.JetPT[i], MSoftDropJet.JetM[Index[i]] - MJet.JetM[i]);
            PSDMassMinusRecoMassPTCentrality.Fill(MJet.JetPT[i], GetCentrality(MHiEvent.hiBin),
                  MSoftDropJet.JetM[Index[i]] - MJet.JetM[i]);
         }

         // SD gen Mass vs. original gen mass
         HGenMassSDGenMass.Fill(MJet.RefM[i], MSoftDropJet.RefGM[Index[i]]);
         HGenPTSDGenPT.Fill(MJet.RefPT[i], MSoftDropJet.RefGPT[Index[i]]);
         HSDGenMassOverGenMassPT.Fill(MJet.RefPT[i], MSoftDropJet.RefGM[Index[i]] / MJet.RefM[i] - 1);
         HSDGenMassMinusGenMassPT.Fill(MJet.RefPT[i], MSoftDropJet.RefGM[Index[i]] - MJet.RefM[i]);
         if(MSoftDropJet.RefGM[Index[i]] / MJet.RefM[i] < 5 && MJet.RefM[i] > 0.01)
         {
            PSDGenMassOverGenMassPT.Fill(MJet.RefPT[i], MSoftDropJet.RefGM[Index[i]] / MJet.RefM[i] - 1);
            PSDGenMassOverGenMassPTCentrality.Fill(MJet.RefPT[i], GetCentrality(MHiEvent.hiBin),
                  MSoftDropJet.RefGM[Index[i]] / MJet.RefM[i] - 1);
            PSDGenMassMinusGenMassPT.Fill(MJet.RefPT[i], MSoftDropJet.RefGM[Index[i]] - MJet.RefM[i]);
            PSDGenMassMinusGenMassPTCentrality.Fill(MJet.RefPT[i], GetCentrality(MHiEvent.hiBin),
                  MSoftDropJet.RefGM[Index[i]] - MJet.RefM[i]);
         }

         // SD Mass vs. SD gen mass
         if(MSoftDropJet.JetM[Index[i]] > 0)
         {
            HSDGenMassSDMass.Fill(MSoftDropJet.RefGM[Index[i]], MSoftDropJet.JetM[Index[i]]);
            HSDMassOverSDGenMassPT.Fill(MSoftDropJet.RefGPT[Index[i]], MSoftDropJet.JetM[Index[i]] / MSoftDropJet.RefGM[Index[i]] - 1);
            HSDMassMinusSDGenMassPT.Fill(MSoftDropJet.RefGPT[Index[i]], MSoftDropJet.JetM[Index[i]] - MSoftDropJet.RefGM[Index[i]]);
            if(MSoftDropJet.JetM[Index[i]] / MSoftDropJet.RefGM[Index[i]] < 5 && MSoftDropJet.RefGM[Index[i]] > 0.01)
            {
               PSDMassOverSDGenMassPT.Fill(MSoftDropJet.RefGPT[Index[i]], MSoftDropJet.JetM[Index[i]] / MSoftDropJet.RefGM[Index[i]] - 1);
               PSDMassOverSDGenMassPTCentrality.Fill(MSoftDropJet.RefGPT[Index[i]], GetCentrality(MHiEvent.hiBin),
                     MSoftDropJet.JetM[Index[i]] / MSoftDropJet.RefGM[Index[i]] - 1);
               PSDMassMinusSDGenMassPT.Fill(MSoftDropJet.RefGPT[Index[i]], MSoftDropJet.JetM[Index[i]] - MSoftDropJet.RefGM[Index[i]]);
               PSDMassMinusSDGenMassPTCentrality.Fill(MSoftDropJet.RefGPT[Index[i]], GetCentrality(MHiEvent.hiBin),
                     MSoftDropJet.JetM[Index[i]] - MSoftDropJet.RefGM[Index[i]]);
            }
         }
      }
   }

   HGenMassRecoMass.Write();
   HRecoMassOverGenMassPT.Write();
   PRecoMassOverGenMassPT.Write();
   PRecoMassOverGenMassPTCentrality.Write();
   HRecoMassMinusGenMassPT.Write();
   PRecoMassMinusGenMassPT.Write();
   PRecoMassMinusGenMassPTCentrality.Write();

   HMatchingDR.Write();

   HGenMassSDMass.Write();
   HSDMassOverGenMassPT.Write();
   PSDMassOverGenMassPT.Write();
   PSDMassOverGenMassPTCentrality.Write();
   HSDMassMinusGenMassPT.Write();
   PSDMassMinusGenMassPT.Write();
   PSDMassMinusGenMassPTCentrality.Write();

   HRecoMassSDMass.Write();
   HSDMassOverRecoMassPT.Write();
   PSDMassOverRecoMassPT.Write();
   PSDMassOverRecoMassPTCentrality.Write();
   HSDMassMinusRecoMassPT.Write();
   PSDMassMinusRecoMassPT.Write();
   PSDMassMinusRecoMassPTCentrality.Write();

   HGenMassSDGenMass.Write();
   HGenPTSDGenPT.Write();
   HSDGenMassOverGenMassPT.Write();
   PSDGenMassOverGenMassPT.Write();
   PSDGenMassOverGenMassPTCentrality.Write();
   HSDGenMassMinusGenMassPT.Write();
   PSDGenMassMinusGenMassPT.Write();
   PSDGenMassMinusGenMassPTCentrality.Write();

   HSDGenMassSDMass.Write();
   HSDMassOverSDGenMassPT.Write();
   PSDMassOverSDGenMassPT.Write();
   PSDMassOverSDGenMassPTCentrality.Write();
   HSDMassMinusSDGenMassPT.Write();
   PSDMassMinusSDGenMassPT.Write();
   PSDMassMinusSDGenMassPTCentrality.Write();

   OutputFile.Close();

   InputFile.Close();
}






