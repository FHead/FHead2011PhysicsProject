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

   TFile InputFile(Input.c_str());

   HiEventTreeMessenger MHiEvent(InputFile);
   RhoTreeMessenger MRho(InputFile);
   SkimTreeMessenger MSkim(InputFile);
   JetTreeMessenger MJet(InputFile);
   GenParticleTreeMessenger MGen(InputFile);

   TFile OutputFile(Output.c_str(), "RECREATE");

   TH1D HMuonEta("HMuonEta", "muon PT;Eta;Total PT", 100, -1.3, 1.3);
   TH1D HElectronEta("HElectronEta", "Electron PT;Eta;Total PT", 100, -1.3, 1.3);
   TH1D HPhotonEta("HPhotonEta", "Photon PT;Eta;Total PT", 100, -1.3, 1.3);
   TH1D HChargedHadronEta("HChargedHadronEta", "ChargedHadron PT;Eta;Total PT", 100, -1.3, 1.3);
   TH1D HNeutralHadronEta("HNeutralHadronEta", "NeutralHadron PT;Eta;Total PT", 100, -1.3, 1.3);

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      MHiEvent.Tree->GetEntry(iEntry);
      MRho.Tree->GetEntry(iEntry);
      MSkim.Tree->GetEntry(iEntry);
      MJet.Tree->GetEntry(iEntry);
      MGen.Tree->GetEntry(iEntry);

      if(IsData == true && MSkim.PassBasicFilter() == false)
         continue;
      
      for(int iJ = 0; iJ < MJet.JetCount; iJ++)
      {
         if(MJet.RefPT[iJ] <= 120 || MJet.RefPT[iJ] > 140)
            continue;
         if(MJet.RefEta[iJ] <= -1.3 || MJet.RefEta[iJ] > 1.3)
            continue;
         if(MJet.RefPT[iJ] <= 0)
            continue;

         for(int iG = 0; iG < (int)MGen.PT->size(); iG++)
         {
            if((*MGen.DaughterCount)[iG] > 0)   // not final particle
               continue;

            double DEta = (*MGen.Eta)[iG] - MJet.RefEta[iJ];
            double DPhi = (*MGen.Phi)[iG] - MJet.RefPhi[iJ];
            if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
            if(DPhi > +PI)   DPhi = DPhi - 2 * PI;

            if(DEta * DEta + DPhi * DPhi > 0.4 * 0.4)
               continue;

            int ID = (*MGen.ID)[iG];
            ID = ((ID > 0) ? ID : -ID);
            if(ID == 12 || ID == 14 || ID == 16)
               continue;

            if(ID == 11)
               HElectronEta.Fill(MJet.RefEta[iJ], (*MGen.PT)[iG]);
            else if(ID == 13)
               HMuonEta.Fill(MJet.RefEta[iJ], (*MGen.PT)[iG]);
            else if(ID == 22)
               HPhotonEta.Fill(MJet.RefEta[iJ], (*MGen.PT)[iG]);
            else if((*MGen.Charge)[iG] == 0)
               HChargedHadronEta.Fill(MJet.RefEta[iJ], (*MGen.PT)[iG]);
            else
               HNeutralHadronEta.Fill(MJet.RefEta[iJ], (*MGen.PT)[iG]);
         }
      }
   }

   HMuonEta.Write();
   HElectronEta.Write();
   HPhotonEta.Write();
   HChargedHadronEta.Write();
   HNeutralHadronEta.Write();

   OutputFile.Close();

   InputFile.Close();
}






