#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
using namespace fastjet;

#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"

#include "ProgressBar.h"

#include "Messenger.h"
#include "SDJetHelper.h"
#include "BasicUtilities.h"
#include "CATree.h"

int main(int argc, char *argv[])
{
   ClusterSequence::set_fastjet_banner_stream(NULL);
   
   string InputFileName = "HiForestAOD_999.root";
   string OutputFileName = "Output_HiForestAOD_999.root";

   if(argc != 7)
   {
      cerr << "Usage: " << argv[0] << " Input Output JetPTMin JetPTMax CentralityMin CentralityMax" << endl;
      return -1;
   }

   InputFileName = argv[1];
   OutputFileName = argv[2];

   double JetPTMin = atof(argv[3]);
   double JetPTMax = atof(argv[4]);
   double CentralityMin = atof(argv[5]);
   double CentralityMax = atof(argv[6]);

   TFile InputFile(InputFileName.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   string PFTreeName = "pfcandAnalyzer/pfTree";

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);
   PFTreeMessenger MPF(InputFile, PFTreeName);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("T", "T");

   double JetPT, TotalPF, TotalPFPT;
   OutputTree.Branch("JetPT", &JetPT, "JetPT/D");
   OutputTree.Branch("TotalPF", &TotalPF, "TotalPF/D");
   OutputTree.Branch("TotalPFPT", &TotalPFPT, "TotalPFPT/D");

   TH1D HNPF("HNPF", "", 1000, 0, 100);
   TH1D HJetPF("HJetPF", "", 1000, 0, 100);
   TH1D HJetPF1("HJetPF1", "", 1000, 0, 100);
   TH1D HJetPF2("HJetPF2", "", 1000, 0, 100);
   TH1D HJetPF3("HJetPF3", "", 1000, 0, 100);
   TH1D HJetPF4("HJetPF4", "", 1000, 0, 100);
   TH1D HJetPF5("HJetPF5", "", 1000, 0, 100);

   int EntryCount = MHiEvent.Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      Bar.Print();

      MHiEvent.GetEntry(iE);
      MJet.GetEntry(iE);
      MSDJet.GetEntry(iE);
      MPF.GetEntry(iE);

      if(GetCentrality(MHiEvent.hiBin) < CentralityMin || GetCentrality(MHiEvent.hiBin) > CentralityMax)
         continue;

      SDJetHelper HSDJet(MSDJet);

      vector<PseudoJet> Particles;
      for(int iPF = 0; iPF < MPF.ID->size(); iPF++)
      {
         FourVector P;
         P.SetPtEtaPhi((*MPF.PT)[iPF], (*MPF.Eta)[iPF], (*MPF.Phi)[iPF]);
         // P[0] = (*MPF.E)[iPF];
         Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets();

      for(int iJ = 0; iJ < MSDJet.JetCount; iJ++)
      {
         if(fabs(MSDJet.JetEta[iJ]) > 1.3)
            continue;

         int BestJet = 0;
         double BestDR = -1;
         for(int i = 0; i < (int)Jets.size(); i++)
         {
            double DR = GetDR(MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ], Jets[i].eta(), Jets[i].phi());
            if(BestDR < 0 || DR < BestDR)
            {
               BestJet = i;
               BestDR = DR;
            }
         }

         JetPT = MSDJet.JetPT[iJ];

         if(BestDR >= 0 && MSDJet.JetPT[iJ] > JetPTMin && MSDJet.JetPT[iJ] < JetPTMax)
         {
            HNPF.Fill(0);

            FourVector TotalP;
            double TotalPT = 0;
            for(int i = 0; i < (int)MPF.ID->size(); i++)
            {
               FourVector P;
               P.SetPtEtaPhi((*MPF.PT)[i], (*MPF.Eta)[i], (*MPF.Phi)[i]);
               if(GetDR((*MPF.Eta)[i], (*MPF.Phi)[i], MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ]) < 0.4)
               {
                  HJetPF.Fill(P.GetPT());
                  TotalP = TotalP + P;
                  TotalPT = TotalPT + P.GetPT();

                  if((*MPF.ID)[i] == 2)
                     HJetPF1.Fill(P.GetPT());
                  if((*MPF.ID)[i] == 3)
                     HJetPF2.Fill(P.GetPT());
                  if((*MPF.ID)[i] == 4 || (*MPF.ID)[i] == 7)
                     HJetPF3.Fill(P.GetPT());
                  if((*MPF.ID)[i] == 1)
                     HJetPF4.Fill(P.GetPT());
                  if((*MPF.ID)[i] == 5 || (*MPF.ID)[i] == 6)
                     HJetPF5.Fill(P.GetPT());
               }
            }

            TotalPF = TotalP.GetPT();
            TotalPFPT = TotalPT;
         }
         else
         {
            TotalPF = -1;
            TotalPFPT = -1;
         }
            
         OutputTree.Fill();
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   HNPF.Write();
   HJetPF.Write();

   OutputTree.Write();

   OutputFile.Close();

   InputFile.Close();

   return 0;
}










