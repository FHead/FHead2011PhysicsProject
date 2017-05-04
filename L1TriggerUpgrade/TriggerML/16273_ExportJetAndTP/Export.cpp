#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "Code/TauHelperFunctions3.h"
#include "SetStyle.h"

#include "Messenger.h"

#define PI 3.14159265358979323846264338327950288479716939937510
#define NOTOWER -999

int main(int argc, char *argv[]);
int FindBin(double V, int N, double B[], bool IsPhi);
int EtaLeft(int ieta);
int EtaRight(int ieta);
int PhiLeft(int iphi);
int PhiRight(int iphi);

int main(int argc, char *argv[])
{
   double EtaBoundaries[21] = {0.000, 0.087, 0.174, 0.261, 0.348, 0.435, 0.522, 0.609, 0.696, 0.783,
      0.879, 0.957, 1.044, 1.131, 1.218, 1.305, 1.392, 1.479, 1.566, 1.653, 1.740};

   double PhiBoundaries[73] = {0};
   for(int i = 0; i <= 72; i++)
      PhiBoundaries[i] = 2 * PI / 72 * i;
   
   string InputFileName = "Samples/WToEnu140PU/WToEnuPU140_140.root";
   string OutputFileName = "PlainText.txt";

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " InputRootFile OutputTextFile";
      return -1;
   }

   InputFileName = argv[1];
   OutputFileName = argv[2];

   TFile File(InputFileName.c_str());

   L1NTupleMessenger ML1(File, "l1NtupleProducer/L1Tree");
   L1ExtraUpgradeTreeMessenger MExtra(File, "l1ExtraUpgradeTreeProducer/L1ExtraUpgradeTree");

   if(ML1.Tree == NULL)
      return -1;

   ofstream OutputFile(OutputFileName);

   int EntryCount = ML1.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      ML1.GetEntry(iE);
      MExtra.GetEntry(iE);

      vector<FourVector> Electrons;
      for(int i = 0; i < (int)ML1.GenP.size(); i++)
      {
         if(ML1.GenStatus[i] != 3)   // we only want final state particles here (Pythia6)
            continue;

         int AbsID = ML1.GenID[i];
         if(AbsID < 0)
            AbsID = -AbsID;

         if(AbsID == 11)
            Electrons.push_back(ML1.GenP[i]);
      }

      // Best PT Electron
      FourVector BestElectron = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)Electrons.size(); i++)
         if(Electrons[i].GetAbsEta() < 3.000)   // find the best Electron inside acceptance
            if(BestElectron.GetPT() < Electrons[i].GetPT())
               BestElectron = Electrons[i];

      // L1TkEle with the best match
      FourVector BestL1TkEG = FourVector(-1, 0, 0, 0);
      for(int i = 0; i < (int)MExtra.TkEG.size(); i++)
         if(GetDR(MExtra.TkEG[i].P, BestElectron) <= 0.5)
            if(BestL1TkEG.GetPT() < MExtra.TkEG[i].P.GetPT())
               BestL1TkEG = MExtra.TkEG[i].P;

      if(BestL1TkEG[0] < 0)   // no match D:
         continue;

      int AbsIEta = FindBin(BestL1TkEG.GetAbsEta(), 20, EtaBoundaries, false) + 1;
      int IPhi = FindBin(BestL1TkEG.GetPhi(), 72, PhiBoundaries, true) + 1;
      int IEta = ((BestL1TkEG.GetEta() > 0) ? AbsIEta : -AbsIEta);

      if(AbsIEta < 0)   // outside of our region of interest
         continue;

      double TPIEta[5][5] = {{0}};
      double TPIPhi[5][5] = {{0}};

      for(int i = -2; i <= 2; i++)
      {
         int ieta;
         if(i == -2)   ieta = EtaLeft(EtaLeft(IEta));
         if(i == -1)   ieta = EtaLeft(IEta);
         if(i == 0)    ieta = IEta;
         if(i == 1)    ieta = EtaRight(IEta);
         if(i == 2)    ieta = EtaRight(EtaRight(IEta));

         for(int j = -2; j <= 2; j++)
         {
            int iphi;
            if(j == -2)   iphi = PhiLeft(PhiLeft(IPhi));
            if(j == -1)   iphi = PhiLeft(IPhi);
            if(j == 0)    iphi = IPhi;
            if(j == 1)    iphi = PhiRight(IPhi);
            if(j == 2)    iphi = PhiRight(PhiRight(IPhi));

            TPIEta[i+2][j+2] = ieta;
            TPIPhi[i+2][j+2] = iphi;
         }
      }

      double EcalET[5][5] = {{0}};
      double HcalET[5][5] = {{0}};
      int EcalFG[5][5] = {{0}};
      int HcalFG[5][5] = {{0}};
      for(int i = 0; i < 5; i++)
      {
         for(int j = 0; j < 5; j++)
         {
            EcalET[i][j] = NOTOWER;
            HcalET[i][j] = NOTOWER;
            EcalFG[i][j] = NOTOWER;
            HcalFG[i][j] = NOTOWER;
         }
      }
      
      for(int i = 0; i < ML1.CALO->nHCALTP; i++)
      {
         for(int j = 0; j < 5; j++)
         {
            for(int k = 0; k < 5; k++)
            {
               if(ML1.CALO->hcalTPieta[i] == TPIEta[j][k] && ML1.CALO->hcalTPCaliphi[i] == TPIPhi[j][k])
               {
                  HcalET[j][k] = ML1.CALO->hcalTPet[i];
                  HcalFG[j][k] = ML1.CALO->hcalTPfineGrain[i];
               }
            }
         }
      }
      
      for(int i = 0; i < ML1.CALO->nECALTP; i++)
      {
         for(int j = 0; j < 5; j++)
         {
            for(int k = 0; k < 5; k++)
            {
               if(ML1.CALO->ecalTPieta[i] == TPIEta[j][k] && ML1.CALO->ecalTPCaliphi[i] == TPIPhi[j][k])
               {
                  EcalET[j][k] = ML1.CALO->ecalTPet[i];
                  EcalFG[j][k] = ML1.CALO->ecalTPfineGrain[i];
               }
            }
         }
      }

      // Good, now we export to a single line
      OutputFile << BestElectron.GetPT() << "\t" << BestElectron.GetEta() << "\t" << BestElectron.GetPhi();
      OutputFile << "\t" << BestL1TkEG.GetPT() << "\t" << BestL1TkEG.GetEta() << "\t" << BestL1TkEG.GetPhi();
      OutputFile << "\t" << IEta << "\t" << IPhi;
      for(int i = 0; i < 5; i++)
         for(int j = 0; j < 5; j++)
            OutputFile << "\t" << TPIEta[i][j] << "\t" << TPIPhi[i][j]
               << "\t" << EcalET[i][j] << "\t" << HcalET[i][j]
               << "\t" << EcalFG[i][j] << "\t" << HcalFG[i][j];
      OutputFile << endl;
   }

   OutputFile.close();

   File.Close();

   return 0;
}

int FindBin(double V, int N, double B[], bool IsPhi)
{
   if(IsPhi == true)
   {
      while(V >= 2 * PI)
         V = V - 2 * PI;
      while(V < 0)
         V = V + 2 * PI;
   }

   for(int i = 0; i < N; i++)
      if(V >= B[i] && V < B[i+1])
         return i;
   return -999;
}

int EtaLeft(int ieta)
{
   if(ieta == 1)
      return -1;
   if(ieta == -20)
      return NOTOWER;
   return ieta - 1;
}

int EtaRight(int ieta)
{
   if(ieta == -1)
      return 1;
   if(ieta == 20)
      return NOTOWER;
   return ieta + 1;
}

int PhiLeft(int iphi)
{
   if(iphi == 1)
      return 72;
   return iphi - 1;
}

int PhiRight(int iphi)
{
   if(iphi == 72)
      return 1;
   return iphi + 1;
}




