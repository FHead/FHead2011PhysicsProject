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
   TriggerTreeMessenger MTrigger(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   string CBin[5] = {"CBin0", "CBin1", "CBin2", "CBin3", "CBin4"};
   double CBinMin[5+1] = {0.0, 0.1, 0.3, 0.5, 0.8, 1.0};
   string PTBin[7] = {"PTBin0", "PTBin1", "PTBin2", "PTBin3", "PTBin4", "PTBin5", "PTBin6"};
   double PTBinMin[7+1] = {80, 100, 120, 140, 160, 200, 300, 500};

   TH1D HN("HN", "Raw event count", 1, 0, 1);
   TH1D HPTHatAll("HPTHatAll", "PTHat", 100, 0, 500);
   TH1D HPTHatSelected("HPTHatSelected", "PTHat", 100, 0, 500);

   TH1D *HRecoJetPT[5] = {NULL};

   TH1D *HSDMass[5][7] = {{NULL}};

   for(int i = 0; i < 5; i++)
   {
      HRecoJetPT[i] = new TH1D(Form("HRecoJetPT_%s", CBin[i].c_str()),
         Form("Centrality %.1f-%.1f%%;Jet PT", CBinMin[i], CBinMin[i+1]),
         100, 80, 500);

      for(int j = 0; j < 7; j++)
      {
         HSDMass[i][j] = new TH1D(Form("HSDMass_%s_%s", CBin[i].c_str(), PTBin[j].c_str()),
            Form("Centrality %.1f-%1.f%%, Jet PT %.0f-%.0f;SD Mass", CBinMin[i], CBinMin[i+1], PTBinMin[j], PTBinMin[j+1]),
            200, 0, 100);

         HSDMass[i][j]->Sumw2();
      }
   }

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      HN.Fill(0);

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);
      MSkim.GetEntry(iEntry);
      MTrigger.GetEntry(iEntry);

      HPTHatAll.Fill(MSDJet.PTHat);
      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;

      if(IsData == true && MSkim.PassBasicFilter() == false)
         continue;
      if(IsData == true && IsPP == false && MTrigger.CheckTrigger("HLT_HIPuAK4CaloJet80_Eta5p1_v1") != 1)
         continue;
      if(IsData == true && IsPP == true && MTrigger.CheckTrigger("HLT_AK4PFJet80_Eta5p1_v1") != 1)
         continue;

      HPTHatSelected.Fill(MSDJet.PTHat);
      
      double Centrality = GetCentrality(MHiEvent.hiBin);

      for(int i = 0; i < MSDJet.JetCount; i++)
      {
         if(IsData == false)   // Smear only MC, not data
         {
            MSDJet.JetPT[i] = MSDJet.JetPT[i] * DrawGaussian(1, 0.08);
            MSDJet.JetM[i] = MSDJet.JetM[i] * DrawGaussian(1, 0.12);
         }

         if(MSDJet.JetPT[i] < 80 || MSDJet.JetPT[i] > 500)
            continue;
         if(MSDJet.JetEta[i] < -1.3 || MSDJet.JetEta[i] > 1.3)
            continue;

         if((*MSDJet.JetSubJetPT)[i].size() < 2)   // we want two subjets
            continue;

         double RecoSubJetDR = CalculateDR((*MSDJet.JetSubJetEta)[i][0], (*MSDJet.JetSubJetPhi)[i][0],
            (*MSDJet.JetSubJetEta)[i][1], (*MSDJet.JetSubJetPhi)[i][1]);

         double SubJetPT1 = (*MSDJet.JetSubJetPT)[i][0];
         double SubJetPT2 = (*MSDJet.JetSubJetPT)[i][1];

         double ZG = min(SubJetPT1, SubJetPT2) / (SubJetPT1 + SubJetPT2);
         double SDMass = MSDJet.JetM[i];
         double RecoJetPT = MSDJet.JetPT[i];
         double GenJetPT = MSDJet.RefPT[i];

         int CIndex = 0;
         for(int i = 0; i < 5; i++)
            if(Centrality >= CBinMin[i] && Centrality < CBinMin[i+1])
               CIndex = i;
         int PIndex = 0;
         for(int i = 0; i < 7; i++)
            if(RecoJetPT >= PTBinMin[i] && RecoJetPT < PTBinMin[i+1])
               PIndex = i;

         if(RecoSubJetDR < 0.1)
            continue;

         HRecoJetPT[CIndex]->Fill(RecoJetPT);

         HSDMass[CIndex][PIndex]->Fill(SDMass);
      }
   }

   HN.Write();
   HPTHatAll.Write();
   HPTHatSelected.Write();

   for(int i = 0; i < 5; i++)
   {
      if(HRecoJetPT[i] != NULL)   HRecoJetPT[i]->Write();
      if(HRecoJetPT[i] != NULL)   delete HRecoJetPT[i];

      for(int j = 0; j < 7; j++)
      {
         if(HSDMass[i][j] != NULL)             HSDMass[i][j]->Write();
         if(HSDMass[i][j] != NULL)             delete HSDMass[i][j];
      }
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





