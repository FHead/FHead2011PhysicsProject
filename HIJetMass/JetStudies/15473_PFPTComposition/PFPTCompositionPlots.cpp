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
   bool IsPP = IsPPFromTag(Tag);

   TFile InputFile(Input.c_str());

   string PFTreeName = "pfcandAnalyzerCS/pfTree";
   string JetTreeName = "akCs4PFJetAnalyzer/t";
   if(IsPP == true)
   {
      PFTreeName = "pfcandAnalyzer/pfTree";
      JetTreeName = "ak4PFJetAnalyzer/t";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   SkimTreeMessenger MSkim(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   PFTreeMessenger MPF(InputFile, PFTreeName);

   if(MJet.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   int CentralityBin[6] = {0, 10, 30, 50, 80, 100};

   TH1D *HMuonEta[5] = {NULL};
   TH1D *HElectronEta[5] = {NULL};
   TH1D *HPhotonEta[5] = {NULL};
   TH1D *HChargedHadronEta[5] = {NULL};
   TH1D *HNeutralHadronEta[5] = {NULL};
   
   TH1D *HMuonPT[5] = {NULL};
   TH1D *HElectronPT[5] = {NULL};
   TH1D *HPhotonPT[5] = {NULL};
   TH1D *HChargedHadronPT[5] = {NULL};
   TH1D *HNeutralHadronPT[5] = {NULL};

   for(int i = 0; i < 5; i++)
   {
      HMuonEta[i]          = new TH1D(Form("HMuonEta%d", CentralityBin[i]), "muon PT (Jet PT 140-160);Eta;Total PT", 100, -1.3, 1.3);
      HElectronEta[i]      = new TH1D(Form("HElectronEta%d", CentralityBin[i]), "Electron PT (Jet PT 140-160);Eta;Total PT", 100, -1.3, 1.3);
      HPhotonEta[i]        = new TH1D(Form("HPhotonEta%d", CentralityBin[i]), "Photon PT (Jet PT 140-160);Eta;Total PT", 100, -1.3, 1.3);
      HChargedHadronEta[i] = new TH1D(Form("HChargedHadronEta%d", CentralityBin[i]), "ChargedHadron PT (Jet PT 140-160);Eta;Total PT", 100, -1.3, 1.3);
      HNeutralHadronEta[i] = new TH1D(Form("HNeutralHadronEta%d", CentralityBin[i]), "NeutralHadron PT (Jet PT 140-160);Eta;Total PT", 100, -1.3, 1.3);

      HMuonPT[i]           = new TH1D(Form("HMuonPT%d", CentralityBin[i]), "muon PT (Jet |#eta| < 1.3);Total PT", 100, 100, 300);
      HElectronPT[i]       = new TH1D(Form("HElectronPT%d", CentralityBin[i]), "Electron PT (Jet |#eta| < 1.3);Total PT", 100, 100, 300);
      HPhotonPT[i]         = new TH1D(Form("HPhotonPT%d", CentralityBin[i]), "Photon PT (Jet |#eta| < 1.3);Total PT", 100, 100, 300);
      HChargedHadronPT[i]  = new TH1D(Form("HChargedHadronPT%d", CentralityBin[i]), "ChargedHadron PT (Jet |#eta| < 1.3);Total PT", 100, 100, 300);
      HNeutralHadronPT[i]  = new TH1D(Form("HNeutralHadronPT%d", CentralityBin[i]), "NeutralHadron PT (Jet |#eta| < 1.3);Total PT", 100, 100, 300);
   }

   int EntryCount = MJet.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if(IsPP == false)
         MHiEvent.Tree->GetEntry(iEntry);
      MSkim.Tree->GetEntry(iEntry);
      MJet.Tree->GetEntry(iEntry);
      MPF.Tree->GetEntry(iEntry);

      if(IsData == true && MSkim.PassBasicFilter() == false)
         continue;

      int Bin = 0;
      if(IsPP == false)
         while(GetCentrality(MHiEvent.hiBin) > CentralityBin[Bin+1] * 0.01)
            Bin = Bin + 1;
      
      for(int iJ = 0; iJ < MJet.JetCount; iJ++)
      {
         if(MJet.JetPT[iJ] <= 100 || MJet.JetPT[iJ] > 300)
            continue;
         if(MJet.JetEta[iJ] <= -1.3 || MJet.JetEta[iJ] > 1.3)
            continue;

         for(int iG = 0; iG < (int)MPF.PT->size(); iG++)
         {
            double DEta = (*MPF.Eta)[iG] - MJet.JetEta[iJ];
            double DPhi = (*MPF.Phi)[iG] - MJet.JetPhi[iJ];
            if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
            if(DPhi > +PI)   DPhi = DPhi - 2 * PI;

            if(DEta * DEta + DPhi * DPhi > 0.4 * 0.4)
               continue;

            int ID = (*MPF.ID)[iG];

            if(MJet.JetPT[iJ] <= 160 && MJet.JetPT[iJ] > 140)
            {
               if(ID == 2)
                  HElectronEta[Bin]->Fill(MJet.JetEta[iJ], (*MPF.PT)[iG]);
               else if(ID == 3)
                  HMuonEta[Bin]->Fill(MJet.JetEta[iJ], (*MPF.PT)[iG]);
               else if(ID == 4 || ID == 7)
                  HPhotonEta[Bin]->Fill(MJet.JetEta[iJ], (*MPF.PT)[iG]);
               else if(ID == 1)
                  HChargedHadronEta[Bin]->Fill(MJet.JetEta[iJ], (*MPF.PT)[iG]);
               else if(ID == 5 || ID == 6)
                  HNeutralHadronEta[Bin]->Fill(MJet.JetEta[iJ], (*MPF.PT)[iG]);
               else
                  cerr << "Particle flow ID = " << ID << "!  Shouldn't happen!" << endl;
            }
               
            if(ID == 2)
               HElectronPT[Bin]->Fill(MJet.JetPT[iJ], (*MPF.PT)[iG]);
            else if(ID == 3)
               HMuonPT[Bin]->Fill(MJet.JetPT[iJ], (*MPF.PT)[iG]);
            else if(ID == 4 || ID == 7)
               HPhotonPT[Bin]->Fill(MJet.JetPT[iJ], (*MPF.PT)[iG]);
            else if(ID == 1)
               HChargedHadronPT[Bin]->Fill(MJet.JetPT[iJ], (*MPF.PT)[iG]);
            else if(ID == 5 || ID == 6)
               HNeutralHadronPT[Bin]->Fill(MJet.JetPT[iJ], (*MPF.PT)[iG]);
            else
               cerr << "Particle flow ID = " << ID << "!  Shouldn't happen!" << endl
                  << (*MPF.PT)[iG] << " " << (*MPF.Eta)[iG] << " " << (*MPF.Phi)[iG] << endl;
         }
      }
   }

   for(int i = 0; i < 5; i++)
   {
      HMuonEta[i]->Write();
      HElectronEta[i]->Write();
      HPhotonEta[i]->Write();
      HChargedHadronEta[i]->Write();
      HNeutralHadronEta[i]->Write();

      HMuonPT[i]->Write();
      HElectronPT[i]->Write();
      HPhotonPT[i]->Write();
      HChargedHadronPT[i]->Write();
      HNeutralHadronPT[i]->Write();
      
      delete HMuonEta[i];
      delete HElectronEta[i];
      delete HPhotonEta[i];
      delete HChargedHadronEta[i];
      delete HNeutralHadronEta[i];

      delete HMuonPT[i];
      delete HElectronPT[i];
      delete HPhotonPT[i];
      delete HChargedHadronPT[i];
      delete HNeutralHadronPT[i];
   }

   OutputFile.Close();

   InputFile.Close();
}






