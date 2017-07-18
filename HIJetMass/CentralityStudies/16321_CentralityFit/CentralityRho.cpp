#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TProfile.h"

#include "BasicUtilities.h"
#include "Messenger.h"

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
   TriggerTreeMessenger MTrigger(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TH1D HN("HN", ";;", 1, 0, 1);
 
   vector<TH1D *> HRho, HRhoM;
   for(int i = 0; i < 101; i++)
      HRho.push_back(new TH1D(Form("HRho%d", i), ";Rho;", 4000, 0, 400));
   for(int i = 0; i < 101; i++)
      HRhoM.push_back(new TH1D(Form("HRhoM%d", i), ";RhoM;", 4000, 0, 4));

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      MHiEvent.GetEntry(iEntry);
      MRho.GetEntry(iEntry);
      MSkim.GetEntry(iEntry);
      MTrigger.GetEntry(iEntry);

      if(IsData == true && MSkim.PassBasicFilter() == false)
         continue;

      HN.Fill(0);

      int Centrality = int(GetCentrality(MHiEvent.hiBin) * 100);
      if(Centrality < 0)
         Centrality = 0;

      HRho[Centrality]->Fill(GetRho(MRho.EtaMax, MRho.Rho, 0));
      HRhoM[Centrality]->Fill(GetRho(MRho.EtaMax, MRho.RhoM, 0));
   }

   HN.Write();

   for(int i = 0; i < 101; i++)
   {
      HRho[i]->Write();
      delete HRho[i];
      
      HRhoM[i]->Write();
      delete HRhoM[i];
   }

   OutputFile.Close();

   InputFile.Close();
}







