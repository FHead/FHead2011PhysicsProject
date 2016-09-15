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
   if(argc < 6)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag PTHatMin PTHatMax" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];
   double PTHatMin = atof(argv[4]);
   double PTHatMax = atof(argv[5]);

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);

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
   SkimTreeMessenger MSkim(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   string CBin[5] = {"CBin0", "CBin1", "CBin2", "CBin3", "CBin4"};
   double CBinMin[6] = {0.0, 0.1, 0.3, 0.5, 0.8, 1.0};

   TH1D HN("HN", "Raw event count", 1, 0, 1);
   TH1D HPTHatAll("HPTHatAll", "PTHat", 100, 0, 500);
   TH1D HPTHatSelected("HPTHatSelected", "PTHat", 100, 0, 500);

   TH2D *HSDMassRecoJetPT[5] = {NULL};
   TProfile *PSDMassRecoJetPT[5] = {NULL};
   TH2D *HZGRecoJetPT[5] = {NULL};
   TProfile *PZGRecoJetPT[5] = {NULL};
   TH2D *HSDMassZG[5] = {NULL};
   TH2D *HSDMassOverPTZG[5] = {NULL};
   TH2D *HSDJetPTRecoJetPT[5] = {NULL};
   TProfile *PSDJetPTRecoJetPT[5] = {NULL};
   TH2D *HSDDepthRecoJetPT[5] = {NULL};
   TProfile *PSDDepthRecoJetPT[5] = {NULL};

   for(int i = 0; i < 5; i++)
   {
      HSDMassRecoJetPT[i] = new TH2D(Form("HSDMassRecoJetPT_%s", CBin[i].c_str()),
         Form("Centrality %.1f-%.1f;Reco Jet PT;SD Mass", CBinMin[i], CBinMin[i+1]),
         100, 80, 500, 100, 0, 80);
      PSDMassRecoJetPT[i] = new TProfile(Form("PSDMassRecoJetPT_%s", CBin[i].c_str()),
         Form("Centrality %.1f-%.1f;Reco Jet PT;SD Mass", CBinMin[i], CBinMin[i+1]),
         100, 80, 500);
      HZGRecoJetPT[i] = new TH2D(Form("HZGRecoJetPT_%s", CBin[i].c_str()),
         Form("Centrality %.1f-%.1f;Reco Jet PT;ZG", CBinMin[i], CBinMin[i+1]),
         100, 80, 500, 100, 0.1, 0.5);
      PZGRecoJetPT[i] = new TProfile(Form("PZGRecoJetPT_%s", CBin[i].c_str()),
         Form("Centrality %.1f-%.1f;Reco Jet PT;ZG", CBinMin[i], CBinMin[i+1]),
         100, 80, 500);
      HSDMassZG[i] = new TH2D(Form("HSDMassZG_%s", CBin[i].c_str()),
         Form("Centrality %.1f-%.1f;ZG;SD Mass", CBinMin[i], CBinMin[i+1]),
         100, 0.1, 0.5, 100, 0, 80);
      HSDMassOverPTZG[i] = new TH2D(Form("HSDMassOverPTZG_%s", CBin[i].c_str()),
         Form("Centrality %.1f-%.1f;ZG;SD Mass / Reco Jet PT", CBinMin[i], CBinMin[i+1]),
         100, 0.1, 0.5, 100, 0, 0.35);
      HSDJetPTRecoJetPT[i] = new TH2D(Form("HSDJetPTRecoJetPT_%s", CBin[i].c_str()),
         Form("Centrality %.1f-%.1f;Reco Jet PT;Groomed Reco Jet PT", CBinMin[i], CBinMin[i+1]),
         100, 80, 500, 100, 0, 500);
      PSDJetPTRecoJetPT[i] = new TProfile(Form("PSDJetPTRecoJetPT_%s", CBin[i].c_str()),
         Form("Centrality %.1f-%.1f;Reco Jet PT;Groomed Reco Jet PT", CBinMin[i], CBinMin[i+1]),
         100, 80, 500);
      HSDDepthRecoJetPT[i] = new TH2D(Form("HSDDepthRecoJetPT_%s", CBin[i].c_str()),
         Form("Centrality %.1f-%.1f;Reco Jet PT;Groomed Depth", CBinMin[i], CBinMin[i+1]),
         100, 80, 500, 12, 0, 12);
      PSDDepthRecoJetPT[i] = new TProfile(Form("PSDDepthRecoJetPT_%s", CBin[i].c_str()),
         Form("Centrality %.1f-%.1f;Reco Jet PT;Groomed Depth", CBinMin[i], CBinMin[i+1]),
         100, 80, 500);
   }

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      HN.Fill(0);

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);
      MSkim.GetEntry(iEntry);

      HPTHatAll.Fill(MSDJet.PTHat);
      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;
      HPTHatSelected.Fill(MSDJet.PTHat);

      if(IsData == true && MSkim.PassBasicFilter() == false)
         continue;

      double Centrality = GetCentrality(MHiEvent.hiBin);

      for(int i = 0; i < MSDJet.JetCount; i++)
      {
         if(MSDJet.JetPT[i] < 80 || MSDJet.JetPT[i] > 500)
            continue;
         if(MSDJet.JetEta[i] < -1.3 || MSDJet.JetEta[i] > 1.3)
            continue;

         if((*MSDJet.JetSubJetPT)[i].size() < 2)   // we want two subjets
            continue;

         double RecoSubJetDR = CalculateDR((*MSDJet.JetSubJetEta)[i][0], (*MSDJet.JetSubJetPhi)[i][0],
            (*MSDJet.JetSubJetEta)[i][1], (*MSDJet.JetSubJetPhi)[i][1]);

         double ZG = MSDJet.JetSym[i];
         double SDMass = MSDJet.JetM[i];
         double RecoJetPT = MSDJet.JetPT[i];

         if(RecoSubJetDR < 0.1)
            continue;

         int CIndex = 0;
         for(int i = 0; i < 5; i++)
            if(Centrality >= CBinMin[i] && Centrality < CBinMin[i+1])
               CIndex = i;

         HSDMassRecoJetPT[CIndex]->Fill(RecoJetPT, SDMass);
         PSDMassRecoJetPT[CIndex]->Fill(RecoJetPT, SDMass);
         HZGRecoJetPT[CIndex]->Fill(RecoJetPT, ZG);
         PZGRecoJetPT[CIndex]->Fill(RecoJetPT, ZG);
         HSDMassZG[CIndex]->Fill(ZG, SDMass);
         HSDMassOverPTZG[CIndex]->Fill(ZG, SDMass / RecoJetPT);
         HSDJetPTRecoJetPT[CIndex]->Fill(RecoJetPT,
            (*MSDJet.JetSubJetPT)[i][0] + (*MSDJet.JetSubJetPT)[i][1]);
         PSDJetPTRecoJetPT[CIndex]->Fill(RecoJetPT,
            (*MSDJet.JetSubJetPT)[i][0] + (*MSDJet.JetSubJetPT)[i][1]);
         HSDDepthRecoJetPT[CIndex]->Fill(RecoJetPT, MSDJet.JetDroppedBranches[i]);
         PSDDepthRecoJetPT[CIndex]->Fill(RecoJetPT, MSDJet.JetDroppedBranches[i]);
      }
   }

   HN.Write();
   HPTHatAll.Write();
   HPTHatSelected.Write();

   for(int i = 0; i < 5; i++)
   {
      if(HSDMassRecoJetPT[i] != NULL)             HSDMassRecoJetPT[i]->Write();
      if(PSDMassRecoJetPT[i] != NULL)             PSDMassRecoJetPT[i]->Write();
      if(HZGRecoJetPT[i] != NULL)                 HZGRecoJetPT[i]->Write();
      if(PZGRecoJetPT[i] != NULL)                 PZGRecoJetPT[i]->Write();
      if(HSDMassZG[i] != NULL)                    HSDMassZG[i]->Write();
      if(HSDMassOverPTZG[i] != NULL)              HSDMassOverPTZG[i]->Write();
      if(HSDJetPTRecoJetPT[i] != NULL)   HSDJetPTRecoJetPT[i]->Write();
      if(PSDJetPTRecoJetPT[i] != NULL)   PSDJetPTRecoJetPT[i]->Write();
      if(HSDDepthRecoJetPT[i] != NULL)       HSDDepthRecoJetPT[i]->Write();
      if(PSDDepthRecoJetPT[i] != NULL)       PSDDepthRecoJetPT[i]->Write();
      
      if(HSDMassRecoJetPT[i] != NULL)             delete HSDMassRecoJetPT[i];
      if(PSDMassRecoJetPT[i] != NULL)             delete PSDMassRecoJetPT[i];
      if(HZGRecoJetPT[i] != NULL)                 delete HZGRecoJetPT[i];
      if(PZGRecoJetPT[i] != NULL)                 delete PZGRecoJetPT[i];
      if(HSDMassZG[i] != NULL)                    delete HSDMassZG[i];
      if(HSDMassOverPTZG[i] != NULL)              delete HSDMassOverPTZG[i];
      if(HSDJetPTRecoJetPT[i] != NULL)   delete HSDJetPTRecoJetPT[i];
      if(PSDJetPTRecoJetPT[i] != NULL)   delete PSDJetPTRecoJetPT[i];
      if(HSDDepthRecoJetPT[i] != NULL)       delete HSDDepthRecoJetPT[i];
      if(PSDDepthRecoJetPT[i] != NULL)       delete PSDDepthRecoJetPT[i];
   }

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





