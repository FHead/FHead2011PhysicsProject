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

   string TriggerString = "HLT_HIPuAK4CaloJet100_Eta5p1_v1";

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];

   bool IsData = IsDataFromTag(Tag);

   TFile InputFile(Input.c_str());

   HiEventTreeMessenger MHiEvent(InputFile);
   RhoTreeMessenger MRho(InputFile);
   SkimTreeMessenger MSkim(InputFile);
   JetTreeMessenger MJet(InputFile);

   TFile OutputFile(Output.c_str(), "RECREATE");

   TProfile PJetResponse("PJetResponse", ";|#eta|;rec / gen - 1", 100, -2, 2);

   int PTMin[6] = {100, 120, 140, 160, 200, 300};
   double AbsEtaMin[5] = {0, 0.5, 1, 1.5, 2};
   int CentralityMin[6] = {0, 10, 30, 50, 80, 100};
   TProfile *PJetResponsesEta[5][5] = {{NULL}};
   TProfile *PJetResponsesPT[4][5] = {{NULL}};
   TProfile *PJetResponsesEtaFull[5] = {NULL};
   TProfile *PJetResponsesPTFull[5] = {NULL};
   for(int j = 0; j < 5; j++)
   {
      PJetResponsesEtaFull[j]
         = new TProfile(Form("PJetResponseEtaFull_%d", CentralityMin[j]),
            Form("%d%%-%d%%;#eta;rec / gen - 1", CentralityMin[j], CentralityMin[j+1]),
            100, -1.3, 1.3);
      for(int i = 0; i < 5; i++)
      {
         PJetResponsesEta[i][j] =
            new TProfile(Form("PJetResponseEta_%d_%d", PTMin[i], CentralityMin[j]),
               Form("PT = %d-%d, %d%%-%d%%;#eta;rec / gen - 1", PTMin[i], PTMin[i+1], CentralityMin[j], CentralityMin[j+1]),
               100, -2, 2);
      }
   }
   for(int j = 0; j < 5; j++)
   {
      PJetResponsesPTFull[j] =
         new TProfile(Form("PJetResponsePTFull_%d", CentralityMin[j]),
            Form("%d%%-%d%% (Jet |#eta| < 1.3);PT;rec / gen - 1", CentralityMin[j], CentralityMin[j+1]),
            100, 100, 300);
      for(int i = 0; i < 4; i++)
      {
         PJetResponsesPT[i][j] =
            new TProfile(Form("PJetResponsePT_%2.1f_%d", AbsEtaMin[i], CentralityMin[j]),
               Form("|Eta| = %f-%f, %d%%-%d%%;PT;rec / gen - 1", AbsEtaMin[i], AbsEtaMin[i+1], CentralityMin[j], CentralityMin[j+1]),
               100, 100, 300);
      }
   }

   TH2D HJetCount("HJetCount", "Number of selected jets;PT bin;Centrality bin", 5, 0, 5, 5, 0, 5);
   TH2D HMatchedJetCount("HMatchedJetCount", "Number of matched jets;PT bin;Centrality bin", 5, 0, 5, 5, 0, 5);

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      MHiEvent.Tree->GetEntry(iEntry);
      MRho.Tree->GetEntry(iEntry);
      MSkim.Tree->GetEntry(iEntry);
      MJet.Tree->GetEntry(iEntry);

      if(IsData == true && MSkim.PassBasicFilter() == false)
         continue;

      int CentralityBin = 0;
      while(GetCentrality(MHiEvent.hiBin) * 100 > CentralityMin[CentralityBin+1])
         CentralityBin = CentralityBin + 1;

      for(int iJ = 0; iJ < MJet.JetCount; iJ++)
      {
         if(MJet.RefPT[iJ] <= PTMin[0] || MJet.RefPT[iJ] > PTMin[5])
            continue;
         if(MJet.RefEta[iJ] <= -2 || MJet.RefEta[iJ] > 2)
            continue;

         int PTBin = 0;
         while(MJet.RefPT[iJ] > PTMin[PTBin+1])
            PTBin = PTBin + 1;

         int EtaBin = 0;
         while(fabs(MJet.RefEta[iJ]) > AbsEtaMin[EtaBin+1])
            EtaBin = EtaBin + 1;

         HJetCount.Fill(PTBin, CentralityBin);

         if(MJet.RefPT[iJ] <= 0)
            continue;

         HMatchedJetCount.Fill(PTBin, CentralityBin);

         double Response = MJet.JetPT[iJ] / MJet.RefPT[iJ] - 1;

         PJetResponse.Fill(MJet.RefEta[iJ], MJet.JetPT[iJ] / MJet.RefPT[iJ] - 1);
         PJetResponsesEta[PTBin][CentralityBin]->Fill(MJet.RefEta[iJ], Response);
         PJetResponsesPT[EtaBin][CentralityBin]->Fill(MJet.RefPT[iJ], Response);

         if(MJet.RefEta[iJ] > -1.3 || MJet.RefEta[iJ] <= 1.3)
         {
            PJetResponsesEtaFull[CentralityBin]->Fill(MJet.RefEta[iJ], Response);
            PJetResponsesPTFull[CentralityBin]->Fill(MJet.RefPT[iJ], Response);
         }
      }
   }

   PJetResponse.Write();

   for(int j = 0; j < 5; j++)
   {
      PJetResponsesEtaFull[j]->Write();
      delete PJetResponsesEtaFull[j];
      for(int i = 0; i < 5; i++)
      {
         PJetResponsesEta[i][j]->Write();
         delete PJetResponsesEta[i][j];
      }
   }
   for(int j = 0; j < 5; j++)
   {
      PJetResponsesPTFull[j]->Write();
      delete PJetResponsesPTFull[j];
      for(int i = 0; i < 4; i++)
      {
         PJetResponsesPT[i][j]->Write();
         delete PJetResponsesPT[i][j];
      }
   }

   HJetCount.Write();
   HMatchedJetCount.Write();

   OutputFile.Close();

   InputFile.Close();
}

double GetDPhi(double phi1, double phi2)
{
   double dphi = phi1 - phi2;

   if(dphi < -PI)   dphi = dphi + 2 * PI;
   if(dphi > +PI)   dphi = dphi - 2 * PI;

   return dphi;
}






