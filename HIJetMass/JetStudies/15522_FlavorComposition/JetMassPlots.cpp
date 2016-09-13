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
   double PTHatMax = atof(argv[4]);

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

   string Flavor[4] = {"Light", "Charm", "Heavy", "Gluon"};
   string CBin[5] = {"CBin0", "CBin1", "CBin2", "CBin3", "CBin4"};
   double CBinMin[6] = {0.0, 0.1, 0.3, 0.5, 0.8, 1.0};

   TH1D HN("HN", "Raw event count", 1, 0, 1);
   TH1D HPTHatAll("HPTHatAll", "PTHat", 100, 0, 300);
   TH1D HPTHatSelected("HPTHatSelected", "PTHat", 100, 0, 300);

   TH2D *HNVsGenJetPTRecoSubJetDR[4][5] = {{NULL}};
   TProfile2D *PSDMassVsGenJetPTRecoSubJetDR[4][5] = {{NULL}};
   TProfile2D *PSDMassVsRecoJetPTRecoSubJetDR[4][5] = {{NULL}};
   TH2D *HSDMassVsRecoSubJetDR[4][5] = {{NULL}};
   TH2D *HSDMassVsRecoJetPT[4][5] = {{NULL}};
   TH2D *HZGVsRecoSubJetDR[4][5] = {{NULL}};
   TH2D *HZGVsRecoJetPT[4][5] = {{NULL}};

   for(int i = 0; i < 4; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         HNVsGenJetPTRecoSubJetDR[i][j]
            = new TH2D(Form("H%sNVsGenJetPTRecoSubJetDR_%s", Flavor[i].c_str(), CBin[j].c_str()),
            Form("%.1f-%.1f;Gen Jet PT;Reco SubJet DR;%s quark count", CBinMin[j], CBinMin[j+1], Flavor[i].c_str()),
            100, 80, 500, 100, 0, 0.5);
         PSDMassVsGenJetPTRecoSubJetDR[i][j]
            = new TProfile2D(Form("P%sSDMassVsGenJetPTRecoSubJetDR_%s", Flavor[i].c_str(), CBin[j].c_str()),
            Form("%.1f-%.1f;Gen Jet PT;Reco SubJet DR;%s quark SDMass", CBinMin[j], CBinMin[j+1], Flavor[i].c_str()),
            100, 80, 500, 100, 0, 0.5);
         PSDMassVsRecoJetPTRecoSubJetDR[i][j]
            = new TProfile2D(Form("P%sSDMassVsRecoJetPTRecoSubJetDR_%s", Flavor[i].c_str(), CBin[j].c_str()),
            Form("%.1f-%.1f;Gen Jet PT;Reco SubJet DR;%s quark SDMass", CBinMin[j], CBinMin[j+1], Flavor[i].c_str()),
            100, 80, 500, 100, 0, 0.5);
         HSDMassVsRecoSubJetDR[i][j]
            = new TH2D(Form("H%sSDMassVsRecoSubJetDR_%s", Flavor[i].c_str(), CBin[j].c_str()),
            Form("%.1f-%.1f;Reco SubJet DR;%s SDMass", CBinMin[j], CBinMin[j+1], Flavor[i].c_str()), 
            100, 0, 0.5, 200, 0, 80);
         HSDMassVsRecoJetPT[i][j]
            = new TH2D(Form("H%sSDMassVsRecoJetPT_%s", Flavor[i].c_str(), CBin[j].c_str()),
            Form("%.1f-%.1f;Reco Jet PT;%s SDMass", CBinMin[j], CBinMin[j+1], Flavor[i].c_str()),
            100, 80, 500, 200, 0, 80);
         HZGVsRecoSubJetDR[i][j]
            = new TH2D(Form("H%sZGVsRecoSubJetDR_%s", Flavor[i].c_str(), CBin[j].c_str()),
            Form("%.1f-%.1f;Reco SubJet DR;%s ZG", CBinMin[j], CBinMin[j+1], Flavor[i].c_str()),
            100, 0, 0.5, 100, 0.1, 0.5);
         HZGVsRecoJetPT[i][j]
            = new TH2D(Form("H%sZGVsRecoJetPT_%s", Flavor[i].c_str(), CBin[j].c_str()),
            Form("%.1f-%.1f;Reco Jet PT;%s ZG", CBinMin[j], CBinMin[j+1], Flavor[i].c_str()),
            100, 80, 500, 100, 0.1, 0.5);
      }
   }

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      HN.Fill(0);

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);

      HPTHatAll.Fill(MSDJet.PTHat);
      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;
      HPTHatSelected.Fill(MSDJet.PTHat);

      double Centrality = GetCentrality(MHiEvent.hiBin);

      for(int i = 0; i < MSDJet.JetCount; i++)
      {
         if(MSDJet.RefPT[i] < 80 || MSDJet.RefPT[i] > 500)
            continue;
         if(MSDJet.RefEta[i] < -1.3 || MSDJet.RefEta[i] > 1.3)
            continue;

         if((*MSDJet.JetSubJetPT)[i].size() < 2)   // we want two subjets
            continue;

         double RecoSubJetDR = CalculateDR((*MSDJet.JetSubJetEta)[i][0], (*MSDJet.JetSubJetPhi)[i][0],
            (*MSDJet.JetSubJetEta)[i][1], (*MSDJet.JetSubJetPhi)[i][1]);

         int Flavor = MSDJet.RefPartonFlavorForB[i];
         if(Flavor == -999 || Flavor == 0)   // No matched parton?
            continue;
         Flavor = ((Flavor < 0) ? -Flavor : Flavor);

         int FIndex = 0;
         if(Flavor == 1 || Flavor == 2 || Flavor == 3)
            FIndex = 0;
         else if(Flavor == 4)
            FIndex = 1;
         else if(Flavor == 5)
            FIndex = 2;
         else if(Flavor == 21)
            FIndex = 3;
         else
            cerr << "Flavor = " << Flavor << endl;

         int CIndex = 0;
         for(int i = 0; i < 5; i++)
            if(Centrality >= CBinMin[i] && Centrality < CBinMin[i+1])
               CIndex = i;

         HNVsGenJetPTRecoSubJetDR[FIndex][CIndex]->Fill(MSDJet.RefPT[i], RecoSubJetDR);
         PSDMassVsGenJetPTRecoSubJetDR[FIndex][CIndex]->Fill(MSDJet.RefPT[i], RecoSubJetDR, MSDJet.JetM[i]);
         PSDMassVsRecoJetPTRecoSubJetDR[FIndex][CIndex]->Fill(MSDJet.JetPT[i], RecoSubJetDR, MSDJet.JetM[i]);
         HZGVsRecoSubJetDR[FIndex][CIndex]->Fill(RecoSubJetDR, MSDJet.JetSym[i]);
         HSDMassVsRecoSubJetDR[FIndex][CIndex]->Fill(RecoSubJetDR, MSDJet.JetM[i]);
         if(RecoSubJetDR > 0.1)
         {
            HZGVsRecoJetPT[FIndex][CIndex]->Fill(MSDJet.JetPT[i], MSDJet.JetSym[i]);
            HSDMassVsRecoJetPT[FIndex][CIndex]->Fill(MSDJet.JetPT[i], MSDJet.JetM[i]);
         }
      }
   }

   HN.Write();
   HPTHatAll.Write();
   HPTHatSelected.Write();

   for(int i = 0; i < 4; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         HNVsGenJetPTRecoSubJetDR[i][j]->Write();
         PSDMassVsGenJetPTRecoSubJetDR[i][j]->Write();
         PSDMassVsRecoJetPTRecoSubJetDR[i][j]->Write();
         HZGVsRecoSubJetDR[i][j]->Write();
         HZGVsRecoJetPT[i][j]->Write();
         HSDMassVsRecoSubJetDR[i][j]->Write();
         HSDMassVsRecoJetPT[i][j]->Write();
         
         delete HNVsGenJetPTRecoSubJetDR[i][j];
         delete PSDMassVsGenJetPTRecoSubJetDR[i][j];
         delete PSDMassVsRecoJetPTRecoSubJetDR[i][j];
         delete HZGVsRecoSubJetDR[i][j];
         delete HZGVsRecoJetPT[i][j];
         delete HSDMassVsRecoSubJetDR[i][j];
         delete HSDMassVsRecoJetPT[i][j];
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





