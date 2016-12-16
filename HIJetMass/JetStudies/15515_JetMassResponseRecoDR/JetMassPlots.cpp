#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"

#include "BasicUtilities.h"
#include "Messenger.h"

int main(int argc, char *argv[]);
double CalculateDR(double eta1, double phi1, double eta2, double phi2);

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
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TH2D HSDMassRatioVsRecoDR("HSDMassRatioVsRecoDR", ";Reco DR;SDMass reco / gen", 100, 0, 0.5, 100, 0, 4);
   TH2D HSDMassRatioVsRecoDR_CBin0("HSDMassRatioVsRecoDR_CBin0",
      "0-10%;Reco DR;SDMass reco / gen", 100, 0, 0.5, 100, 0, 4);
   TH2D HSDMassRatioVsRecoDR_CBin1("HSDMassRatioVsRecoDR_CBin1",
      "10-30%;Reco DR;SDMass reco / gen", 100, 0, 0.5, 100, 0, 4);
   TH2D HSDMassRatioVsRecoDR_CBin2("HSDMassRatioVsRecoDR_CBin2",
      "30-50%;Reco DR;SDMass reco / gen", 100, 0, 0.5, 100, 0, 4);
   TH2D HSDMassRatioVsRecoDR_CBin3("HSDMassRatioVsRecoDR_CBin3",
      "50-80%;Reco DR;SDMass reco / gen", 100, 0, 0.5, 100, 0, 4);
   TH2D HSDMassRatioVsRecoDR_CBin4("HSDMassRatioVsRecoDR_CBin4",
      "80-100%;Reco DR;SDMass reco / gen", 100, 0, 0.5, 100, 0, 4);
   TH2D HSDMassRatioVsCentrality("HSDMassRatioVsCentrality", ";Centrality;SDMass reco / gen",
      100, 0, 1, 100, 0, 4);
   TH2D HSDMassRatioVsCentrality_Bin0("HSDMassRatioVsCentrality_Bin0", "DR = 0.0-0.1;Centrality;SDMass reco / gen",
      100, 0, 1, 100, 0, 4);
   TH2D HSDMassRatioVsCentrality_Bin1("HSDMassRatioVsCentrality_Bin1", "DR = 0.1-0.2;Centrality;SDMass reco / gen",
      100, 0, 1, 100, 0, 4);
   TH2D HSDMassRatioVsCentrality_Bin2("HSDMassRatioVsCentrality_Bin2", "DR = 0.2-0.3;Centrality;SDMass reco / gen",
      100, 0, 1, 100, 0, 4);
   TH2D HSDMassRatioVsCentrality_Bin3("HSDMassRatioVsCentrality_Bin3", "DR = 0.3-0.4;Centrality;SDMass reco / gen",
      100, 0, 1, 100, 0, 4);
   TProfile PSDMassRatioVsCentrality_Bin0("PSDMassRatioVsCentrality_Bin0",
      "DR = 0.0-0.1;Centrality;SDMass reco / gen", 100, 0, 1);
   TProfile PSDMassRatioVsCentrality_Bin1("PSDMassRatioVsCentrality_Bin1",
      "DR = 0.1-0.2;Centrality;SDMass reco / gen", 100, 0, 1);
   TProfile PSDMassRatioVsCentrality_Bin2("PSDMassRatioVsCentrality_Bin2",
      "DR = 0.2-0.3;Centrality;SDMass reco / gen", 100, 0, 1);
   TProfile PSDMassRatioVsCentrality_Bin3("PSDMassRatioVsCentrality_Bin3",
      "DR = 0.3-0.4;Centrality;SDMass reco / gen", 100, 0, 1);

   TH2D HRecoSubJetDRVsSubJetDRMax("HRecoSubJetDRVsSubJetDRMax",
      ";SubJet DR Max;Reco SubJet DR", 100, 0, 0.5, 100, 0, 0.5);
   TH2D HRecoSubJetDRVsSubJetDRMax_CBin0("HRecoSubJetDRVsSubJetDRMax_CBin0",
      "0-10%;SubJet DR Max;Reco SubJet DR", 100, 0, 0.5, 100, 0, 0.5);
   TH2D HRecoSubJetDRVsSubJetDRMax_CBin1("HRecoSubJetDRVsSubJetDRMax_CBin1",
      "10-30%;SubJet DR Max;Reco SubJet DR", 100, 0, 0.5, 100, 0, 0.5);
   TH2D HRecoSubJetDRVsSubJetDRMax_CBin2("HRecoSubJetDRVsSubJetDRMax_CBin2",
      "30-50%;SubJet DR Max;Reco SubJet DR", 100, 0, 0.5, 100, 0, 0.5);
   TH2D HRecoSubJetDRVsSubJetDRMax_CBin3("HRecoSubJetDRVsSubJetDRMax_CBin3",
      "50-80%;SubJet DR Max;Reco SubJet DR", 100, 0, 0.5, 100, 0, 0.5);
   TH2D HRecoSubJetDRVsSubJetDRMax_CBin4("HRecoSubJetDRVsSubJetDRMax_CBin4",
      "80-100%;SubJet DR Max;Reco SubJet DR", 100, 0, 0.5, 100, 0, 0.5);

   TH2D HRecoSubJetDRVsCentrality_I("HRecoSubJetDRVsCentrality_I",
      ";Centrality;Reconstructed SubJet DR", 100, 0, 1, 100, 0, 0.5);
   TH2D HRecoSubJetDRVsCentrality_II("HRecoSubJetDRVsCentrality_II",
      ";Centrality;Reconstructed SubJet DR", 100, 0, 1, 100, 0, 0.5);
   TH2D HRecoSubJetDRVsCentrality_III("HRecoSubJetDRVsCentrality_III",
      ";Centrality;Reconstructed SubJet DR", 100, 0, 1, 100, 0, 0.5);

   TH2D HSDMassRatioVsRecoSubJetDR_I("HSDMassRatioVsRecoSubJetDR_I",
      "Region I;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5, 100, 0, 10);
   TH2D HSDMassRatioVsRecoSubJetDR_I_CBin0("HSDMassRatioVsRecoSubJetDR_I_CBin0",
      "Region I, 0-10%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5, 100, 0, 10);
   TH2D HSDMassRatioVsRecoSubJetDR_I_CBin1("HSDMassRatioVsRecoSubJetDR_I_CBin1",
      "Region I, 10-30%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5, 100, 0, 10);
   TH2D HSDMassRatioVsRecoSubJetDR_I_CBin2("HSDMassRatioVsRecoSubJetDR_I_CBin2",
      "Region I, 30-50%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5, 100, 0, 10);
   TH2D HSDMassRatioVsRecoSubJetDR_I_CBin3("HSDMassRatioVsRecoSubJetDR_I_CBin3",
      "Region I, 50-80%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5, 100, 0, 10);
   TH2D HSDMassRatioVsRecoSubJetDR_I_CBin4("HSDMassRatioVsRecoSubJetDR_I_CBin4",
      "Region I, 80-100%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5, 100, 0, 10);
   TH2D HSDMassRatioVsRecoSubJetDR_II("HSDMassRatioVsRecoSubJetDR_II",
      "Region II;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5, 100, 0, 10);
   TH2D HSDMassRatioVsRecoSubJetDR_II_CBin0("HSDMassRatioVsRecoSubJetDR_II_CBin0",
      "Region II, 0%-10%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5, 100, 0, 10);
   TH2D HSDMassRatioVsRecoSubJetDR_II_CBin1("HSDMassRatioVsRecoSubJetDR_II_CBin1",
      "Region II, 10%-30%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5, 100, 0, 10);
   TH2D HSDMassRatioVsRecoSubJetDR_II_CBin2("HSDMassRatioVsRecoSubJetDR_II_CBin2",
      "Region II, 30%-50%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5, 100, 0, 10);
   TH2D HSDMassRatioVsRecoSubJetDR_II_CBin3("HSDMassRatioVsRecoSubJetDR_II_CBin3",
      "Region II, 50%-80%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5, 100, 0, 10);
   TH2D HSDMassRatioVsRecoSubJetDR_II_CBin4("HSDMassRatioVsRecoSubJetDR_II_CBin4",
      "Region II, 80%-100%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5, 100, 0, 10);

   TProfile PSDMassRatioVsRecoSubJetDR_I("PSDMassRatioVsRecoSubJetDR_I",
      "Region I;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5);
   TProfile PSDMassRatioVsRecoSubJetDR_I_CBin0("PSDMassRatioVsRecoSubJetDR_I_CBin0",
      "Region I, 0-10%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5);
   TProfile PSDMassRatioVsRecoSubJetDR_I_CBin1("PSDMassRatioVsRecoSubJetDR_I_CBin1",
      "Region I, 10-30%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5);
   TProfile PSDMassRatioVsRecoSubJetDR_I_CBin2("PSDMassRatioVsRecoSubJetDR_I_CBin2",
      "Region I, 30-50%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5);
   TProfile PSDMassRatioVsRecoSubJetDR_I_CBin3("PSDMassRatioVsRecoSubJetDR_I_CBin3",
      "Region I, 50-80%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5);
   TProfile PSDMassRatioVsRecoSubJetDR_I_CBin4("PSDMassRatioVsRecoSubJetDR_I_CBin4",
      "Region I, 80-100%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5);
   TProfile PSDMassRatioVsRecoSubJetDR_II("PSDMassRatioVsRecoSubJetDR_II",
      "Region II;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5);
   TProfile PSDMassRatioVsRecoSubJetDR_II_CBin0("PSDMassRatioVsRecoSubJetDR_II_CBin0",
      "Region II, 0%-10%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5);
   TProfile PSDMassRatioVsRecoSubJetDR_II_CBin1("PSDMassRatioVsRecoSubJetDR_II_CBin1",
      "Region II, 10%-30%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5);
   TProfile PSDMassRatioVsRecoSubJetDR_II_CBin2("PSDMassRatioVsRecoSubJetDR_II_CBin2",
      "Region II, 30%-50%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5);
   TProfile PSDMassRatioVsRecoSubJetDR_II_CBin3("PSDMassRatioVsRecoSubJetDR_II_CBin3",
      "Region II, 50%-80%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5);
   TProfile PSDMassRatioVsRecoSubJetDR_II_CBin4("PSDMassRatioVsRecoSubJetDR_II_CBin4",
      "Region II, 80%-100%;Reco Subjet DR;SD Mass Reco/Gen", 100, 0.1, 0.5);

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);

      double Centrality = GetCentrality(MHiEvent.hiBin);

      for(int i = 0; i < MSDJet.JetCount; i++)
      {
         if(MSDJet.RefPT[i] < 80 || MSDJet.RefPT[i] > 500)
            continue;
         if(MSDJet.RefEta[i] < -1.3 || MSDJet.RefEta[i] > 1.3)
            continue;

         if((*MSDJet.JetSubJetPT)[i].size() < 2)   // we want two subjets
            continue;
         if((*MSDJet.RefGSubJetPT)[i].size() < 2)   // we want two subjets also for gen jet for this study
            continue;

         double SubJetDR = CalculateDR((*MSDJet.RefGSubJetEta)[i][0], (*MSDJet.RefGSubJetPhi)[i][0],
            (*MSDJet.RefGSubJetEta)[i][1], (*MSDJet.RefGSubJetPhi)[i][1]);
         double RecoSubJetDR = CalculateDR((*MSDJet.JetSubJetEta)[i][0], (*MSDJet.JetSubJetPhi)[i][0],
            (*MSDJet.JetSubJetEta)[i][1], (*MSDJet.JetSubJetPhi)[i][1]);

         double DR00 = CalculateDR((*MSDJet.JetSubJetEta)[i][0], (*MSDJet.JetSubJetPhi)[i][0],
            (*MSDJet.RefGSubJetEta)[i][0], (*MSDJet.RefGSubJetPhi)[i][0]);
         double DR01 = CalculateDR((*MSDJet.JetSubJetEta)[i][0], (*MSDJet.JetSubJetPhi)[i][0],
            (*MSDJet.RefGSubJetEta)[i][1], (*MSDJet.RefGSubJetPhi)[i][1]);
         double DR10 = CalculateDR((*MSDJet.JetSubJetEta)[i][1], (*MSDJet.JetSubJetPhi)[i][1],
            (*MSDJet.RefGSubJetEta)[i][0], (*MSDJet.RefGSubJetPhi)[i][0]);
         double DR11 = CalculateDR((*MSDJet.JetSubJetEta)[i][1], (*MSDJet.JetSubJetPhi)[i][1],
            (*MSDJet.RefGSubJetEta)[i][1], (*MSDJet.RefGSubJetPhi)[i][1]);
         
         double DRSum = min(DR00 + DR11, DR10 + DR01);
         double DRMax = -1;
         if(DR00 + DR11 < DR10 + DR01)
            DRMax = max(DR00, DR11);
         else
            DRMax = max(DR10, DR01);

         double GenPT = MSDJet.RefPT[i];
         
         double GenSDMass = MSDJet.RefGM[i];
         double GenSDPT = MSDJet.RefGPT[i];

         double RecoSDMass = MSDJet.JetM[i];

         double SDMassRatio = RecoSDMass / GenSDMass;

         FourVector GenSubJet1, GenSubJet2;
         GenSubJet1.SetPtEtaPhiMass((*MSDJet.RefGSubJetPT)[i][0], (*MSDJet.RefGSubJetEta)[i][0],
            (*MSDJet.RefGSubJetPhi)[i][0], (*MSDJet.RefGSubJetM)[i][0]);
         GenSubJet2.SetPtEtaPhiMass((*MSDJet.RefGSubJetPT)[i][1], (*MSDJet.RefGSubJetEta)[i][1],
            (*MSDJet.RefGSubJetPhi)[i][1], (*MSDJet.RefGSubJetM)[i][1]);

         if(GenSubJet1.GetPT() < GenSubJet2.GetPT())
            swap(GenSubJet1, GenSubJet2);

         FourVector RecoSubJet1, RecoSubJet2;
         RecoSubJet1.SetPtEtaPhiMass((*MSDJet.JetSubJetPT)[i][0], (*MSDJet.JetSubJetEta)[i][0],
            (*MSDJet.JetSubJetPhi)[i][0], (*MSDJet.JetSubJetM)[i][0]);
         RecoSubJet2.SetPtEtaPhiMass((*MSDJet.JetSubJetPT)[i][1], (*MSDJet.JetSubJetEta)[i][1],
            (*MSDJet.JetSubJetPhi)[i][1], (*MSDJet.JetSubJetM)[i][1]);

         if(RecoSubJet1.GetPT() < RecoSubJet2.GetPT())
            swap(RecoSubJet1, RecoSubJet2);

         HSDMassRatioVsRecoDR.Fill(RecoSubJetDR, SDMassRatio);
         if(Centrality < 0.10)
            HSDMassRatioVsRecoDR_CBin0.Fill(RecoSubJetDR, SDMassRatio);
         else if(Centrality < 0.30)
            HSDMassRatioVsRecoDR_CBin1.Fill(RecoSubJetDR, SDMassRatio);
         else if(Centrality < 0.50)
            HSDMassRatioVsRecoDR_CBin2.Fill(RecoSubJetDR, SDMassRatio);
         else if(Centrality < 0.80)
            HSDMassRatioVsRecoDR_CBin3.Fill(RecoSubJetDR, SDMassRatio);
         else if(Centrality < 1.00)
            HSDMassRatioVsRecoDR_CBin4.Fill(RecoSubJetDR, SDMassRatio);

         HSDMassRatioVsCentrality.Fill(Centrality, SDMassRatio);
         if(RecoSubJetDR < 0.10)
            HSDMassRatioVsCentrality_Bin0.Fill(Centrality, SDMassRatio);
         else if(RecoSubJetDR < 0.20)
            HSDMassRatioVsCentrality_Bin1.Fill(Centrality, SDMassRatio);
         else if(RecoSubJetDR < 0.30)
            HSDMassRatioVsCentrality_Bin2.Fill(Centrality, SDMassRatio);
         else if(RecoSubJetDR < 0.40)
            HSDMassRatioVsCentrality_Bin3.Fill(Centrality, SDMassRatio);
   
         HRecoSubJetDRVsSubJetDRMax.Fill(DRMax, RecoSubJetDR);
         if(Centrality < 0.10)
            HRecoSubJetDRVsSubJetDRMax_CBin0.Fill(DRMax, RecoSubJetDR);
         if(Centrality < 0.30)
            HRecoSubJetDRVsSubJetDRMax_CBin1.Fill(DRMax, RecoSubJetDR);
         if(Centrality < 0.50)
            HRecoSubJetDRVsSubJetDRMax_CBin2.Fill(DRMax, RecoSubJetDR);
         if(Centrality < 0.80)
            HRecoSubJetDRVsSubJetDRMax_CBin3.Fill(DRMax, RecoSubJetDR);
         if(Centrality < 1.00)
            HRecoSubJetDRVsSubJetDRMax_CBin4.Fill(DRMax, RecoSubJetDR);
         
         int Region = 1;
         if(RecoSubJetDR < 0.1)
            Region = 3;
         else if(DRMax > RecoSubJetDR / 2)
            Region = 2;

         if(Region == 1)
            HRecoSubJetDRVsCentrality_I.Fill(Centrality, RecoSubJetDR);
         if(Region == 2)
            HRecoSubJetDRVsCentrality_II.Fill(Centrality, RecoSubJetDR);
         if(Region == 3)
            HRecoSubJetDRVsCentrality_III.Fill(Centrality, RecoSubJetDR);

         if(Region == 1)
         {
            HSDMassRatioVsRecoSubJetDR_I.Fill(RecoSubJetDR, SDMassRatio);
            PSDMassRatioVsRecoSubJetDR_I.Fill(RecoSubJetDR, SDMassRatio);
            if(Centrality < 0.1)
            {
               HSDMassRatioVsRecoSubJetDR_I_CBin0.Fill(RecoSubJetDR, SDMassRatio);
               PSDMassRatioVsRecoSubJetDR_I_CBin0.Fill(RecoSubJetDR, SDMassRatio);
            }
            else if(Centrality < 0.3)
            {
               HSDMassRatioVsRecoSubJetDR_I_CBin1.Fill(RecoSubJetDR, SDMassRatio);
               PSDMassRatioVsRecoSubJetDR_I_CBin1.Fill(RecoSubJetDR, SDMassRatio);
            }
            else if(Centrality < 0.5)
            {
               HSDMassRatioVsRecoSubJetDR_I_CBin2.Fill(RecoSubJetDR, SDMassRatio);
               PSDMassRatioVsRecoSubJetDR_I_CBin2.Fill(RecoSubJetDR, SDMassRatio);
            }
            else if(Centrality < 0.8)
            {
               HSDMassRatioVsRecoSubJetDR_I_CBin3.Fill(RecoSubJetDR, SDMassRatio);
               PSDMassRatioVsRecoSubJetDR_I_CBin3.Fill(RecoSubJetDR, SDMassRatio);
            }
            else if(Centrality < 1.0)
            {
               HSDMassRatioVsRecoSubJetDR_I_CBin4.Fill(RecoSubJetDR, SDMassRatio);
               PSDMassRatioVsRecoSubJetDR_I_CBin4.Fill(RecoSubJetDR, SDMassRatio);
            }
         }
         if(Region == 2)
         {
            HSDMassRatioVsRecoSubJetDR_II.Fill(RecoSubJetDR, SDMassRatio);
            PSDMassRatioVsRecoSubJetDR_II.Fill(RecoSubJetDR, SDMassRatio);
            if(Centrality < 0.1)
            {
               HSDMassRatioVsRecoSubJetDR_II_CBin0.Fill(RecoSubJetDR, SDMassRatio);
               PSDMassRatioVsRecoSubJetDR_II_CBin0.Fill(RecoSubJetDR, SDMassRatio);
            }
            else if(Centrality < 0.3)
            {
               HSDMassRatioVsRecoSubJetDR_II_CBin1.Fill(RecoSubJetDR, SDMassRatio);
               PSDMassRatioVsRecoSubJetDR_II_CBin1.Fill(RecoSubJetDR, SDMassRatio);
            }
            else if(Centrality < 0.5)
            {
               HSDMassRatioVsRecoSubJetDR_II_CBin2.Fill(RecoSubJetDR, SDMassRatio);
               PSDMassRatioVsRecoSubJetDR_II_CBin2.Fill(RecoSubJetDR, SDMassRatio);
            }
            else if(Centrality < 0.8)
            {
               HSDMassRatioVsRecoSubJetDR_II_CBin3.Fill(RecoSubJetDR, SDMassRatio);
               PSDMassRatioVsRecoSubJetDR_II_CBin3.Fill(RecoSubJetDR, SDMassRatio);
            }
            else if(Centrality < 1.0)
            {
               HSDMassRatioVsRecoSubJetDR_II_CBin4.Fill(RecoSubJetDR, SDMassRatio);
               PSDMassRatioVsRecoSubJetDR_II_CBin4.Fill(RecoSubJetDR, SDMassRatio);
            }
         }
      }
   }

   HSDMassRatioVsRecoDR.Write();
   HSDMassRatioVsRecoDR_CBin0.Write();
   HSDMassRatioVsRecoDR_CBin1.Write();
   HSDMassRatioVsRecoDR_CBin2.Write();
   HSDMassRatioVsRecoDR_CBin3.Write();
   HSDMassRatioVsRecoDR_CBin4.Write();

   HSDMassRatioVsCentrality.Write();
   HSDMassRatioVsCentrality_Bin0.Write();
   HSDMassRatioVsCentrality_Bin1.Write();
   HSDMassRatioVsCentrality_Bin2.Write();
   HSDMassRatioVsCentrality_Bin3.Write();
   PSDMassRatioVsCentrality_Bin0.Write();
   PSDMassRatioVsCentrality_Bin1.Write();
   PSDMassRatioVsCentrality_Bin2.Write();
   PSDMassRatioVsCentrality_Bin3.Write();

   HRecoSubJetDRVsSubJetDRMax.Write();
   HRecoSubJetDRVsSubJetDRMax_CBin0.Write();
   HRecoSubJetDRVsSubJetDRMax_CBin1.Write();
   HRecoSubJetDRVsSubJetDRMax_CBin2.Write();
   HRecoSubJetDRVsSubJetDRMax_CBin3.Write();
   HRecoSubJetDRVsSubJetDRMax_CBin4.Write();

   HRecoSubJetDRVsCentrality_I.Write();
   HRecoSubJetDRVsCentrality_II.Write();
   HRecoSubJetDRVsCentrality_III.Write();

   HSDMassRatioVsRecoSubJetDR_I.Write();
   HSDMassRatioVsRecoSubJetDR_I_CBin0.Write();
   HSDMassRatioVsRecoSubJetDR_I_CBin1.Write();
   HSDMassRatioVsRecoSubJetDR_I_CBin2.Write();
   HSDMassRatioVsRecoSubJetDR_I_CBin3.Write();
   HSDMassRatioVsRecoSubJetDR_I_CBin4.Write();
   HSDMassRatioVsRecoSubJetDR_II.Write();
   HSDMassRatioVsRecoSubJetDR_II_CBin0.Write();
   HSDMassRatioVsRecoSubJetDR_II_CBin1.Write();
   HSDMassRatioVsRecoSubJetDR_II_CBin2.Write();
   HSDMassRatioVsRecoSubJetDR_II_CBin3.Write();
   HSDMassRatioVsRecoSubJetDR_II_CBin4.Write();

   PSDMassRatioVsRecoSubJetDR_I.Write();
   PSDMassRatioVsRecoSubJetDR_I_CBin0.Write();
   PSDMassRatioVsRecoSubJetDR_I_CBin1.Write();
   PSDMassRatioVsRecoSubJetDR_I_CBin2.Write();
   PSDMassRatioVsRecoSubJetDR_I_CBin3.Write();
   PSDMassRatioVsRecoSubJetDR_I_CBin4.Write();
   PSDMassRatioVsRecoSubJetDR_II.Write();
   PSDMassRatioVsRecoSubJetDR_II_CBin0.Write();
   PSDMassRatioVsRecoSubJetDR_II_CBin1.Write();
   PSDMassRatioVsRecoSubJetDR_II_CBin2.Write();
   PSDMassRatioVsRecoSubJetDR_II_CBin3.Write();
   PSDMassRatioVsRecoSubJetDR_II_CBin4.Write();

   OutputFile.Close();

   InputFile.Close();
}

double CalculateDR(double eta1, double phi1, double eta2, double phi2)
{
   double DEta = eta1 - eta2;
   double DPhi = phi1 - phi2;
   if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
   if(DPhi > +PI)   DPhi = DPhi - 2 * PI;
   return sqrt(DEta * DEta + DPhi * DPhi);
}





