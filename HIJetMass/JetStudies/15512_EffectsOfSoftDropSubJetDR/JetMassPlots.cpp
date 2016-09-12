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

   TH2D HSubJetCountRecoVsGen("HSubJetCountRecoVsGen", ";Gen subjet count;Reco subjet count", 3, 0, 3, 3, 0, 3);

   TH2D HSubJetDRVsGenPT("HSubJetDRVsGenPT", ";Gen PT;Gen Subjet DR", 100, 80, 500, 100, 0, 0.5);
   TH2D HSubJetDRRecoVsGen("HSubJetDRRecoVsGen", ";Gen Subjet DR;Reco Subjet dR", 100, 0, 0.5, 100, 0, 0.5);
   TProfile2D PSDMassVsSubJetDRGenPT("PSDMassVsSubJetDRGenPT", ";Gen PT;Gen Subjet DR", 100, 80, 500, 100, 0, 0.5);
   TH2D HSDMassVsGenPT("HSDMassVsGenPT", ";Gen PT;SD Mass", 100, 80, 500, 100, 0, 80);
   TH2D HSDMassVsGenPT_DR01("HSDMassVsGenPT_DR01", "0.0 < dR < 0.1;Gen PT;SD Mass", 100, 80, 500, 100, 0, 80);
   TH2D HSDMassVsGenPT_DR02("HSDMassVsGenPT_DR02", "0.1 < dR < 0.2;Gen PT;SD Mass", 100, 80, 500, 100, 0, 80);
   TH2D HSDMassVsGenPT_DR03("HSDMassVsGenPT_DR03", "0.2 < dR < 0.3;Gen PT;SD Mass", 100, 80, 500, 100, 0, 80);
   TH2D HSDMassVsGenPT_DR04("HSDMassVsGenPT_DR04", "0.3 < dR < 0.4;Gen PT;SD Mass", 100, 80, 500, 100, 0, 80);
   TH2D HSDMassRatioVsGenPT("HSDMassRatioVsGenPT", ";Gen PT;SD Mass / Gen SD Mass", 100, 80, 500, 100, 0, 10);
   TH2D HSDMassRatioVsGenPT_DR01("HSDMassRatioVsGenPT_DR01", "0.0 < dR < 0.1;Gen PT;SD Mass / Gen SD Mass",
      100, 80, 500, 100, 0, 10);
   TH2D HSDMassRatioVsGenPT_DR02("HSDMassRatioVsGenPT_DR02", "0.1 < dR < 0.2;Gen PT;SD Mass / Gen SD Mass",
      100, 80, 500, 100, 0, 10);
   TH2D HSDMassRatioVsGenPT_DR03("HSDMassRatioVsGenPT_DR03", "0.2 < dR < 0.3;Gen PT;SD Mass / Gen SD Mass",
      100, 80, 500, 100, 0, 10);
   TH2D HSDMassRatioVsGenPT_DR04("HSDMassRatioVsGenPT_DR04", "0.3 < dR < 0.4;Gen PT;SD Mass / Gen SD Mass",
      100, 80, 500, 100, 0, 10);
   TH2D HSDMassRatioVsSubJetDR("HSDMassRatioVsSubJetDR", ";Gen Subjet DR;SD Mass / Gen SD Mass",
      100, 0, 0.5, 100, 0, 2);
   TProfile PSDMassRatioVsSubJetDR("PSDMassRatioVsSubJetDR", ";Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5);
   TH2D HSDMassRatioVsSubJetDR_Centrality0("HSDMassRatioVsSubJetDR_Centrality0",
      ";Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDMassRatioVsSubJetDR_Centrality1("HSDMassRatioVsSubJetDR_Centrality1",
      ";Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDMassRatioVsSubJetDR_Centrality2("HSDMassRatioVsSubJetDR_Centrality2",
      ";Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDMassRatioVsSubJetDR_Centrality3("HSDMassRatioVsSubJetDR_Centrality3",
      ";Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDMassRatioVsSubJetDR_Centrality4("HSDMassRatioVsSubJetDR_Centrality4",
      ";Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDPTRatioVsGenPT("HSDPTRatioVsGenPT", ";Gen PT;SD PT / Gen SD PT", 100, 80, 500, 100, 0, 10);
   TH2D HSDPTRatioVsGenPT_DR01("HSDPTRatioVsGenPT_DR01", "0.0 < dR < 0.1;Gen PT;SD PT / Gen SD PT",
      100, 80, 500, 100, 0, 10);
   TH2D HSDPTRatioVsGenPT_DR02("HSDPTRatioVsGenPT_DR02", "0.1 < dR < 0.2;Gen PT;SD PT / Gen SD PT",
      100, 80, 500, 100, 0, 10);
   TH2D HSDPTRatioVsGenPT_DR03("HSDPTRatioVsGenPT_DR03", "0.2 < dR < 0.3;Gen PT;SD PT / Gen SD PT",
      100, 80, 500, 100, 0, 10);
   TH2D HSDPTRatioVsGenPT_DR04("HSDPTRatioVsGenPT_DR04", "0.3 < dR < 0.4;Gen PT;SD PT / Gen SD PT",
      100, 80, 500, 100, 0, 10);
   TH2D HSDPTRatioVsSubJetDR("HSDPTRatioVsSubJetDR", ";Gen Subjet DR;SD PT / Gen SD PT",
      100, 0, 0.5, 100, 0, 2);
   TProfile PSDPTRatioVsSubJetDR("PSDPTRatioVsSubJetDR", ";Gen Subjet DR;SD PT / Gen SD PT", 100, 0, 0.5);
   TH2D HSDPTRatioVsSubJetDR_Centrality0("HSDPTRatioVsSubJetDR_Centrality0",
      ";Gen Subjet DR;SD PT / Gen SD PT", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDPTRatioVsSubJetDR_Centrality1("HSDPTRatioVsSubJetDR_Centrality1",
      ";Gen Subjet DR;SD PT / Gen SD PT", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDPTRatioVsSubJetDR_Centrality2("HSDPTRatioVsSubJetDR_Centrality2",
      ";Gen Subjet DR;SD PT / Gen SD PT", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDPTRatioVsSubJetDR_Centrality3("HSDPTRatioVsSubJetDR_Centrality3",
      ";Gen Subjet DR;SD PT / Gen SD PT", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDPTRatioVsSubJetDR_Centrality4("HSDPTRatioVsSubJetDR_Centrality4",
      ";Gen Subjet DR;SD PT / Gen SD PT", 100, 0, 0.5, 100, 0, 2);

   TH2D HLeadingSubJetPTRatioVsSDMassRatio("HLeadingSubJetPTRatioVsSDMassRatio",
      ";SD Mass / Gen SD Mass;Leading sub jet PT / gen leading subjet PT", 100, 0, 2, 100, 0, 2);
   TH2D HLeadingSubJetPTRatioVsSDMassRatio_DR01("HLeadingSubJetPTRatioVsSDMassRatio_DR01",
      "0.0 < dR < 0.1;SD Mass / Gen SD Mass;Leading sub jet PT / gen leading subjet PT", 100, 0, 2, 100, 0, 2);
   TH2D HLeadingSubJetPTRatioVsSDMassRatio_DR02("HLeadingSubJetPTRatioVsSDMassRatio_DR02",
      "0.1 < dR < 0.2;SD Mass / Gen SD Mass;Leading sub jet PT / gen leading subjet PT", 100, 0, 2, 100, 0, 2);
   TH2D HLeadingSubJetPTRatioVsSDMassRatio_DR03("HLeadingSubJetPTRatioVsSDMassRatio_DR03",
      "0.2 < dR < 0.3;SD Mass / Gen SD Mass;Leading sub jet PT / gen leading subjet PT", 100, 0, 2, 100, 0, 2);
   TH2D HLeadingSubJetPTRatioVsSDMassRatio_DR04("HLeadingSubJetPTRatioVsSDMassRatio_DR04",
      "0.3 < dR < 0.4;SD Mass / Gen SD Mass;Leading sub jet PT / gen leading subjet PT", 100, 0, 2, 100, 0, 2);

   TH2D HSubJetDRSumVsSDMassRatio("HSubJetDRSumVsSDMassRatio", ";SD Mass / Gen SD Mass;Subjet DR Sum",
      100, 0, 2, 100, 0, 1);
   TH2D HSubJetDRSumVsSDMassRatio_DR01("HSubJetDRSumVsSDMassRatio_DR01",
      "0.0 < dR < 0.1;SD Mass / Gen SD Mass;Subjet DR Sum", 100, 0, 2, 100, 0, 1);
   TH2D HSubJetDRSumVsSDMassRatio_DR02("HSubJetDRSumVsSDMassRatio_DR02",
      "0.1 < dR < 0.2;SD Mass / Gen SD Mass;Subjet DR Sum", 100, 0, 2, 100, 0, 1);
   TH2D HSubJetDRSumVsSDMassRatio_DR03("HSubJetDRSumVsSDMassRatio_DR03",
      "0.2 < dR < 0.3;SD Mass / Gen SD Mass;Subjet DR Sum", 100, 0, 2, 100, 0, 1);
   TH2D HSubJetDRSumVsSDMassRatio_DR04("HSubJetDRSumVsSDMassRatio_DR04",
      "0.3 < dR < 0.4;SD Mass / Gen SD Mass;Subjet DR Sum", 100, 0, 2, 100, 0, 1);

   TH2D HSubJetDRMaxVsSDMassRatio("HSubJetDRMaxVsSDMassRatio", ";SD Mass / Gen SD Mass;Subjet DR Max",
      100, 0, 2, 100, 0, 0.5);
   TH2D HSubJetDRMaxVsSDMassRatio_DR01("HSubJetDRMaxVsSDMassRatio_DR01",
      "0.0 < dR < 0.1;SD Mass / Gen SD Mass;Subjet DR Max", 100, 0, 2, 100, 0, 0.5);
   TH2D HSubJetDRMaxVsSDMassRatio_DR02("HSubJetDRMaxVsSDMassRatio_DR02",
      "0.1 < dR < 0.2;SD Mass / Gen SD Mass;Subjet DR Max", 100, 0, 2, 100, 0, 0.5);
   TH2D HSubJetDRMaxVsSDMassRatio_DR03("HSubJetDRMaxVsSDMassRatio_DR03",
      "0.2 < dR < 0.3;SD Mass / Gen SD Mass;Subjet DR Max", 100, 0, 2, 100, 0, 0.5);
   TH2D HSubJetDRMaxVsSDMassRatio_DR04("HSubJetDRMaxVsSDMassRatio_DR04",
      "0.3 < dR < 0.4;SD Mass / Gen SD Mass;Subjet DR Max", 100, 0, 2, 100, 0, 0.5);

   TH2D HSDMassRatioVsSubJetDR_SmallSubjetDRMax("HSDMassRatioVsSubJetDR_SmallSubjetDRMax",
      "Subjet DR Max < 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 2);
   TProfile PSDMassRatioVsSubJetDR_SmallSubjetDRMax("PSDMassRatioVsSubJetDR_SmallSubjetDRMax",
      "Subjet DR Max < 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5);
   TH2D HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality0("HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality0",
      "Subjet DR Max < 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality1("HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality1",
      "Subjet DR Max < 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality2("HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality2",
      "Subjet DR Max < 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality3("HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality3",
      "Subjet DR Max < 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality4("HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality4",
      "Subjet DR Max < 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax(
      "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax",
      "Subjet DR Max < 0.1;Subleading Subjet PT Ratio;Leading Subjet PT Ratio", 100, 0, 4, 100, 0, 4);
   TH2D HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR01(
      "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR01",
      "Subjet DR Max < 0.1, 0.0 < dR < 0.1;Subleading Subjet PT Ratio;Leading Subjet PT Ratio",
      100, 0, 4, 100, 0, 4);
   TH2D HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR02(
      "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR02",
      "Subjet DR Max < 0.1, 0.1 < dR < 0.2;Subleading Subjet PT Ratio;Leading Subjet PT Ratio",
      100, 0, 4, 100, 0, 4);
   TH2D HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR03(
      "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR03",
      "Subjet DR Max < 0.1, 0.2 < dR < 0.3;Subleading Subjet PT Ratio;Leading Subjet PT Ratio",
      100, 0, 4, 100, 0, 4);
   TH2D HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR04(
      "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR04",
      "Subjet DR Max < 0.1, 0.3 < dR < 0.4;Subleading Subjet PT Ratio;Leading Subjet PT Ratio",
      100, 0, 4, 100, 0, 4);

   TH2D HSDMassRatioVsSubJetDR_LargeSubjetDRMax("HSDMassRatioVsSubJetDR_LargeSubjetDRMax",
      "Subjet DR Max > 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 5);
   TH2D HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality0("HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality0",
      "Subjet DR Max > 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 5);
   TH2D HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality1("HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality1",
      "Subjet DR Max > 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 5);
   TH2D HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality2("HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality2",
      "Subjet DR Max > 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 5);
   TH2D HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality3("HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality3",
      "Subjet DR Max > 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 5);
   TH2D HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality4("HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality4",
      "Subjet DR Max > 0.1;Gen Subjet DR;SD Mass / Gen SD Mass", 100, 0, 0.5, 100, 0, 5);
   TH2D HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax(
      "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax",
      "Subjet DR Max > 0.1;Subleading Subjet PT Ratio;Leading Subjet PT Ratio", 100, 0, 4, 100, 0, 4);
   TH2D HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR01(
      "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR01",
      "Subjet DR Max > 0.1, 0.0 < dR < 0.1;Subleading Subjet PT Ratio;Leading Subjet PT Ratio",
      100, 0, 4, 100, 0, 4);
   TH2D HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR02(
      "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR02",
      "Subjet DR Max > 0.1, 0.1 < dR < 0.2;Subleading Subjet PT Ratio;Leading Subjet PT Ratio",
      100, 0, 4, 100, 0, 4);
   TH2D HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR03(
      "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR03",
      "Subjet DR Max > 0.1, 0.2 < dR < 0.3;Subleading Subjet PT Ratio;Leading Subjet PT Ratio",
      100, 0, 4, 100, 0, 4);
   TH2D HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR04(
      "HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR04",
      "Subjet DR Max > 0.1, 0.3 < dR < 0.4;Subleading Subjet PT Ratio;Leading Subjet PT Ratio",
      100, 0, 4, 100, 0, 4);

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

         HSubJetCountRecoVsGen.Fill((*MSDJet.RefGSubJetPT)[i].size(), (*MSDJet.JetSubJetPT)[i].size());

         if((*MSDJet.JetSubJetPT)[i].size() < 2)   // we want two subjets
            continue;
         if((*MSDJet.RefGSubJetPT)[i].size() < 2)   // we want two subjets also for gen jet for this study
            continue;

         double SubJetDPhi = (*MSDJet.RefGSubJetPhi)[i][0] - (*MSDJet.RefGSubJetPhi)[i][1];
         double SubJetDEta = (*MSDJet.RefGSubJetEta)[i][0] - (*MSDJet.RefGSubJetEta)[i][1];
         if(SubJetDPhi < -PI)   SubJetDPhi = SubJetDPhi + 2 * PI;
         if(SubJetDPhi > +PI)   SubJetDPhi = SubJetDPhi - 2 * PI;
         double SubJetDR = sqrt(SubJetDPhi * SubJetDPhi + SubJetDEta * SubJetDEta);

         SubJetDPhi = (*MSDJet.JetSubJetPhi)[i][0] - (*MSDJet.JetSubJetPhi)[i][1];
         SubJetDEta = (*MSDJet.JetSubJetEta)[i][0] - (*MSDJet.JetSubJetEta)[i][1];
         if(SubJetDPhi < -PI)   SubJetDPhi = SubJetDPhi + 2 * PI;
         if(SubJetDPhi > +PI)   SubJetDPhi = SubJetDPhi - 2 * PI;
         double RecoSubJetDR = sqrt(SubJetDPhi * SubJetDPhi + SubJetDEta * SubJetDEta);

         HSubJetDRRecoVsGen.Fill(SubJetDR, RecoSubJetDR);

         HSubJetDRVsGenPT.Fill(MSDJet.RefPT[i], SubJetDR);
         PSDMassVsSubJetDRGenPT.Fill(MSDJet.RefPT[i], SubJetDR, MSDJet.JetM[i]);
         HSDMassVsGenPT.Fill(MSDJet.RefPT[i], MSDJet.JetM[i]);
         HSDMassRatioVsGenPT.Fill(MSDJet.RefPT[i], MSDJet.JetM[i] / MSDJet.RefGM[i]);
         HSDPTRatioVsGenPT.Fill(MSDJet.RefPT[i], MSDJet.JetPT[i] / MSDJet.RefGPT[i]);
         if(SubJetDR < 0.1)
         {
            HSDMassVsGenPT_DR01.Fill(MSDJet.RefPT[i], MSDJet.JetM[i]);
            HSDMassRatioVsGenPT_DR01.Fill(MSDJet.RefPT[i], MSDJet.JetM[i] / MSDJet.RefGM[i]);
            HSDPTRatioVsGenPT_DR01.Fill(MSDJet.RefPT[i], MSDJet.JetPT[i] / MSDJet.RefGPT[i]);
         }
         else if(SubJetDR < 0.2)
         {
            HSDMassVsGenPT_DR02.Fill(MSDJet.RefPT[i], MSDJet.JetM[i]);
            HSDMassRatioVsGenPT_DR02.Fill(MSDJet.RefPT[i], MSDJet.JetM[i] / MSDJet.RefGM[i]);
            HSDPTRatioVsGenPT_DR02.Fill(MSDJet.RefPT[i], MSDJet.JetPT[i] / MSDJet.RefGPT[i]);
         }
         else if(SubJetDR < 0.3)
         {
            HSDMassVsGenPT_DR03.Fill(MSDJet.RefPT[i], MSDJet.JetM[i]);
            HSDMassRatioVsGenPT_DR03.Fill(MSDJet.RefPT[i], MSDJet.JetM[i] / MSDJet.RefGM[i]);
            HSDPTRatioVsGenPT_DR03.Fill(MSDJet.RefPT[i], MSDJet.JetPT[i] / MSDJet.RefGPT[i]);
         }
         else if(SubJetDR < 0.4)
         {
            HSDMassVsGenPT_DR04.Fill(MSDJet.RefPT[i], MSDJet.JetM[i]);
            HSDMassRatioVsGenPT_DR04.Fill(MSDJet.RefPT[i], MSDJet.JetM[i] / MSDJet.RefGM[i]);
            HSDPTRatioVsGenPT_DR04.Fill(MSDJet.RefPT[i], MSDJet.JetPT[i] / MSDJet.RefGPT[i]);
         }
         
         HSDMassRatioVsSubJetDR.Fill(SubJetDR, MSDJet.JetM[i] / MSDJet.RefGM[i]);
         HSDPTRatioVsSubJetDR.Fill(SubJetDR, MSDJet.JetPT[i] / MSDJet.RefGPT[i]);
         if(MSDJet.RefGM[i] > 0.0001)
         {
            PSDMassRatioVsSubJetDR.Fill(SubJetDR, MSDJet.JetM[i] / MSDJet.RefGM[i]);
            PSDPTRatioVsSubJetDR.Fill(SubJetDR, MSDJet.JetPT[i] / MSDJet.RefGPT[i]);
         }
         if(Centrality < 0.10)
         {
            HSDMassRatioVsSubJetDR_Centrality0.Fill(SubJetDR, MSDJet.JetM[i] / MSDJet.RefGM[i]);
            HSDPTRatioVsSubJetDR_Centrality0.Fill(SubJetDR, MSDJet.JetPT[i] / MSDJet.RefGPT[i]);
         }
         else if(Centrality < 0.30)
         {
            HSDMassRatioVsSubJetDR_Centrality1.Fill(SubJetDR, MSDJet.JetM[i] / MSDJet.RefGM[i]);
            HSDPTRatioVsSubJetDR_Centrality1.Fill(SubJetDR, MSDJet.JetPT[i] / MSDJet.RefGPT[i]);
         }
         else if(Centrality < 0.50)
         {
            HSDMassRatioVsSubJetDR_Centrality2.Fill(SubJetDR, MSDJet.JetM[i] / MSDJet.RefGM[i]);
            HSDPTRatioVsSubJetDR_Centrality2.Fill(SubJetDR, MSDJet.JetPT[i] / MSDJet.RefGPT[i]);
         }
         else if(Centrality < 0.80)
         {
            HSDMassRatioVsSubJetDR_Centrality3.Fill(SubJetDR, MSDJet.JetM[i] / MSDJet.RefGM[i]);
            HSDPTRatioVsSubJetDR_Centrality3.Fill(SubJetDR, MSDJet.JetPT[i] / MSDJet.RefGPT[i]);
         }
         else if(Centrality < 1.00)
         {
            HSDMassRatioVsSubJetDR_Centrality4.Fill(SubJetDR, MSDJet.JetM[i] / MSDJet.RefGM[i]);
            HSDPTRatioVsSubJetDR_Centrality4.Fill(SubJetDR, MSDJet.JetPT[i] / MSDJet.RefGPT[i]);
         }

         double MassRatio = MSDJet.JetM[i] / MSDJet.RefGM[i];

         double LeadingJetPT = max((*MSDJet.JetSubJetPT)[i][0], (*MSDJet.JetSubJetPT)[i][1]);
         double LeadingRefGPT = max((*MSDJet.RefGSubJetPT)[i][0], (*MSDJet.RefGSubJetPT)[i][1]);
         double LeadingJetRatio = LeadingJetPT / LeadingRefGPT;
         
         double SubleadingJetPT = min((*MSDJet.JetSubJetPT)[i][0], (*MSDJet.JetSubJetPT)[i][1]);
         double SubleadingRefGPT = min((*MSDJet.RefGSubJetPT)[i][0], (*MSDJet.RefGSubJetPT)[i][1]);
         double SubleadingJetRatio = SubleadingJetPT / SubleadingRefGPT;

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

         HLeadingSubJetPTRatioVsSDMassRatio.Fill(MassRatio, LeadingJetRatio);
         if(SubJetDR < 0.1)
            HLeadingSubJetPTRatioVsSDMassRatio_DR01.Fill(MassRatio, LeadingJetRatio);
         else if(SubJetDR < 0.2)
            HLeadingSubJetPTRatioVsSDMassRatio_DR02.Fill(MassRatio, LeadingJetRatio);
         else if(SubJetDR < 0.3)
            HLeadingSubJetPTRatioVsSDMassRatio_DR03.Fill(MassRatio, LeadingJetRatio);
         else if(SubJetDR < 0.4)
            HLeadingSubJetPTRatioVsSDMassRatio_DR04.Fill(MassRatio, LeadingJetRatio);

         HSubJetDRSumVsSDMassRatio.Fill(MassRatio, DRSum);
         if(SubJetDR < 0.1)
            HSubJetDRSumVsSDMassRatio_DR01.Fill(MassRatio, DRSum);
         else if(SubJetDR < 0.2)
            HSubJetDRSumVsSDMassRatio_DR02.Fill(MassRatio, DRSum);
         else if(SubJetDR < 0.3)
            HSubJetDRSumVsSDMassRatio_DR03.Fill(MassRatio, DRSum);
         else if(SubJetDR < 0.4)
            HSubJetDRSumVsSDMassRatio_DR04.Fill(MassRatio, DRSum);

         HSubJetDRMaxVsSDMassRatio.Fill(MassRatio, DRMax);
         if(SubJetDR < 0.1)
            HSubJetDRMaxVsSDMassRatio_DR01.Fill(MassRatio, DRMax);
         else if(SubJetDR < 0.2)
            HSubJetDRMaxVsSDMassRatio_DR02.Fill(MassRatio, DRMax);
         else if(SubJetDR < 0.3)
            HSubJetDRMaxVsSDMassRatio_DR03.Fill(MassRatio, DRMax);
         else if(SubJetDR < 0.4)
            HSubJetDRMaxVsSDMassRatio_DR04.Fill(MassRatio, DRMax);

         if(DRMax < 0.1)
         {
            HSDMassRatioVsSubJetDR_SmallSubjetDRMax.Fill(SubJetDR, MassRatio);
            PSDMassRatioVsSubJetDR_SmallSubjetDRMax.Fill(SubJetDR, MassRatio);
            if(Centrality < 0.1)
               HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality0.Fill(SubJetDR, MassRatio);
            else if(Centrality < 0.3)
               HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality1.Fill(SubJetDR, MassRatio);
            else if(Centrality < 0.5)
               HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality2.Fill(SubJetDR, MassRatio);
            else if(Centrality < 0.8)
               HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality3.Fill(SubJetDR, MassRatio);
            else if(Centrality < 1.0)
               HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality4.Fill(SubJetDR, MassRatio);
            HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax.Fill(
               LeadingJetRatio, SubleadingJetRatio);
            if(SubJetDR < 0.1)
               HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR01.Fill(
                  LeadingJetRatio, SubleadingJetRatio);
            else if(SubJetDR < 0.2)
               HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR02.Fill(
                  LeadingJetRatio, SubleadingJetRatio);
            else if(SubJetDR < 0.3)
               HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR03.Fill(
                  LeadingJetRatio, SubleadingJetRatio);
            else if(SubJetDR < 0.4)
               HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR04.Fill(
                  LeadingJetRatio, SubleadingJetRatio);
         }
         else
         {
            HSDMassRatioVsSubJetDR_LargeSubjetDRMax.Fill(SubJetDR, MassRatio);
            if(Centrality < 0.1)
               HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality0.Fill(SubJetDR, MassRatio);
            else if(Centrality < 0.3)
               HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality1.Fill(SubJetDR, MassRatio);
            else if(Centrality < 0.5)
               HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality2.Fill(SubJetDR, MassRatio);
            else if(Centrality < 0.8)
               HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality3.Fill(SubJetDR, MassRatio);
            else if(Centrality < 1.0)
               HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality4.Fill(SubJetDR, MassRatio);
            HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax.Fill(
               LeadingJetRatio, SubleadingJetRatio);
            if(SubJetDR < 0.1)
               HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR01.Fill(
                  LeadingJetRatio, SubleadingJetRatio);
            else if(SubJetDR < 0.2)
               HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR02.Fill(
                  LeadingJetRatio, SubleadingJetRatio);
            else if(SubJetDR < 0.3)
               HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR03.Fill(
                  LeadingJetRatio, SubleadingJetRatio);
            else if(SubJetDR < 0.4)
               HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR04.Fill(
                  LeadingJetRatio, SubleadingJetRatio);
         }
      }
   }

   HSubJetCountRecoVsGen.Write();
   HSubJetDRVsGenPT.Write();
   HSubJetDRRecoVsGen.Write();
   PSDMassVsSubJetDRGenPT.Write();
   HSDMassVsGenPT.Write();
   HSDMassVsGenPT_DR01.Write();
   HSDMassVsGenPT_DR02.Write();
   HSDMassVsGenPT_DR03.Write();
   HSDMassVsGenPT_DR04.Write();
   HSDMassRatioVsGenPT.Write();
   HSDMassRatioVsGenPT_DR01.Write();
   HSDMassRatioVsGenPT_DR02.Write();
   HSDMassRatioVsGenPT_DR03.Write();
   HSDMassRatioVsGenPT_DR04.Write();
   HSDMassRatioVsSubJetDR.Write();
   PSDMassRatioVsSubJetDR.Write();
   HSDMassRatioVsSubJetDR_Centrality0.Write();
   HSDMassRatioVsSubJetDR_Centrality1.Write();
   HSDMassRatioVsSubJetDR_Centrality2.Write();
   HSDMassRatioVsSubJetDR_Centrality3.Write();
   HSDMassRatioVsSubJetDR_Centrality4.Write();
   HSDPTRatioVsGenPT.Write();
   HSDPTRatioVsGenPT_DR01.Write();
   HSDPTRatioVsGenPT_DR02.Write();
   HSDPTRatioVsGenPT_DR03.Write();
   HSDPTRatioVsGenPT_DR04.Write();
   HSDPTRatioVsSubJetDR.Write();
   PSDPTRatioVsSubJetDR.Write();
   HSDPTRatioVsSubJetDR_Centrality0.Write();
   HSDPTRatioVsSubJetDR_Centrality1.Write();
   HSDPTRatioVsSubJetDR_Centrality2.Write();
   HSDPTRatioVsSubJetDR_Centrality3.Write();
   HSDPTRatioVsSubJetDR_Centrality4.Write();
   HLeadingSubJetPTRatioVsSDMassRatio.Write();
   HLeadingSubJetPTRatioVsSDMassRatio_DR01.Write();
   HLeadingSubJetPTRatioVsSDMassRatio_DR02.Write();
   HLeadingSubJetPTRatioVsSDMassRatio_DR03.Write();
   HLeadingSubJetPTRatioVsSDMassRatio_DR04.Write();
   HSubJetDRSumVsSDMassRatio.Write();
   HSubJetDRSumVsSDMassRatio_DR01.Write();
   HSubJetDRSumVsSDMassRatio_DR02.Write();
   HSubJetDRSumVsSDMassRatio_DR03.Write();
   HSubJetDRSumVsSDMassRatio_DR04.Write();
   HSubJetDRMaxVsSDMassRatio.Write();
   HSubJetDRMaxVsSDMassRatio_DR01.Write();
   HSubJetDRMaxVsSDMassRatio_DR02.Write();
   HSubJetDRMaxVsSDMassRatio_DR03.Write();
   HSubJetDRMaxVsSDMassRatio_DR04.Write();
   HSDMassRatioVsSubJetDR_SmallSubjetDRMax.Write();
   PSDMassRatioVsSubJetDR_SmallSubjetDRMax.Write();
   HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality0.Write();
   HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality1.Write();
   HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality2.Write();
   HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality3.Write();
   HSDMassRatioVsSubJetDR_SmallSubjetDRMax_Centrality4.Write();
   HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax.Write();
   HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR01.Write();
   HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR02.Write();
   HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR03.Write();
   HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_SmallSubjetDRMax_DR04.Write();
   HSDMassRatioVsSubJetDR_LargeSubjetDRMax.Write();
   HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality0.Write();
   HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality1.Write();
   HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality2.Write();
   HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality3.Write();
   HSDMassRatioVsSubJetDR_LargeSubjetDRMax_Centrality4.Write();
   HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax.Write();
   HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR01.Write();
   HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR02.Write();
   HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR03.Write();
   HLeadingSubJetPTRatioVsSubleadingSubJetPTRatio_LargeSubjetDRMax_DR04.Write();

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





