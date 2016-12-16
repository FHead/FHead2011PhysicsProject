#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
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
#include "SDJetHelper.h"
#include "CATree.h"

int main(int argc, char *argv[]);

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

   if(IsData == true)
   {
      cerr << "I'd rather not run on data for this study" << endl;
      return -1;
   }

   TFile InputFile(Input.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   string PFTreeName = "pfcandAnalyzerCS/pfTree";
   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
      PFTreeName = "pfcandAnalyzer/pfTree";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);
   GenParticleTreeMessenger MGen(InputFile);
   PFTreeMessenger MPF(InputFile);

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

   TH2D HJetPTComparison("HJetPTComparison", ";Jet PT;New Jet PT", 100, 0, 400, 100, 0, 400);
   TH2D HSDMassComparison("HSDMassComparison", ";Jet SD Mass;New Jet SD Mass", 100, 0, 100, 100, 0, 100);

   double Rho = 300;

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      HN.Fill(0);

      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);
      MGen.GetEntry(iEntry);
      MPF.GetEntry(iEntry);
      
      SDJetHelper HSDJet(MSDJet);

      HPTHatAll.Fill(MSDJet.PTHat);
      if(MSDJet.PTHat <= PTHatMin || MSDJet.PTHat > PTHatMax)
         continue;

      HPTHatSelected.Fill(MSDJet.PTHat);

      for(int iJ = 0; iJ < MSDJet.JetCount; iJ++)
      {
         if(MSDJet.JetPT[iJ] < 80 || MSDJet.JetPT[iJ] > 500)
            continue;
         if(MSDJet.JetEta[iJ] < -1.3 || MSDJet.JetEta[iJ] > 1.3)
            continue;

         if(HSDJet.RecoSubJetDR[iJ] < 0.1)
            continue;

         FourVector JetP;
         JetP.SetPtEtaPhi(MSDJet.JetPT[iJ], MSDJet.JetEta[iJ], MSDJet.JetPhi[iJ]);

         // Step 1 - get all PF candidates within range
         vector<FourVector> Candidates;
         for(int i = 0; i < MPF.ID->size(); i++)
         {
            FourVector P;
            P.SetPtEtaPhi((*MPF.PT)[i], (*MPF.Eta)[i], (*MPF.Phi)[i]);
            if(GetDR(P, JetP) < 0.4)
               Candidates.push_back(P);
         }

         // Step 2 - sprinkle underlying event contribution
         double TotalPT = Rho * 0.4 * 0.4 * PI;
         while(TotalPT > 0)
         {
            double PT = DrawRandom(0.1, 3);
            TotalPT = TotalPT - PT;

            double DEta, DPhi;
            do
            {
               DEta = DrawRandom(-0.4, 0.4);
               DPhi = DrawRandom(-0.4, 0.4);
            } while(DEta * DEta + DPhi * DPhi > 0.4 * 0.4);

            FourVector P;
            P.SetPtEtaPhi(PT, MSDJet.JetEta[iJ] + DEta, MSDJet.JetPhi[iJ] + DPhi);
            Candidates.push_back(P);
         }

         // Step 3 - do pileup subtraction algorithm
         vector<FourVector> Ghosts;
         double Delta = 0.04;
         for(double Eta = -0.4; Eta <= 0.4; Eta = Eta + Delta)
         {
            for(double Phi = -0.4; Phi <= 0.4; Phi = Phi + Delta)
            {
               if(Eta * Eta + Phi * Phi > 0.4 * 0.4)
                  continue;

               FourVector P;
               P.SetPtEtaPhi(1, MSDJet.JetEta[iJ] + Eta, MSDJet.JetPhi[iJ] + Phi);
               Ghosts.push_back(P);
            }
         }
         double GhostPT = Rho * 0.4 * 0.4 * PI / Ghosts.size();
         for(int i = 0; i < (int)Ghosts.size(); i++)
            Ghosts[i].SetPtEtaPhi(GhostPT, Ghosts[i].GetEta(), Ghosts[i].GetPhi());

         map<double, pair<int, int> > Distances;
         for(int i = 0; i < (int)Candidates.size(); i++)
         {
            for(int j = 0; j < (int)Ghosts.size(); j++)
            {
               double Distance = GetDR(Candidates[i], Ghosts[j]);
               Distances.insert(pair<double, pair<int, int> >(Distance, pair<int, int>(i, j)));
            }
         }

         for(map<double, pair<int, int> >::iterator iter = Distances.begin(); iter != Distances.end(); iter++)
         {
            int I = iter->second.first;
            int J = iter->second.second;

            FourVector CP = Candidates[I];
            FourVector GP = Ghosts[J];

            if(CP.GetPT() < 1e-5 || GP.GetPT() < 1e-5)
               continue;

            if(CP.GetPT() > GP.GetPT())
            {
               Candidates[I].SetPtEtaPhi(CP.GetPT() - GP.GetPT(), CP.GetEta(), CP.GetPhi());
               Ghosts[J].SetPtEtaPhi(1e-6, GP.GetEta(), GP.GetPhi());
            }
            else
            {
               Candidates[I].SetPtEtaPhi(1e-6, CP.GetEta(), CP.GetPhi());
               Ghosts[J].SetPtEtaPhi(GP.GetPT() - CP.GetPT(), GP.GetEta(), GP.GetPhi());
            }
         }

         for(int i = 0; i < (int)Candidates.size(); i++)
         {
            if(Candidates[i].GetPT() < 1e-5)
            {
               Candidates.erase(Candidates.begin() + i);
               i = i - 1;
            }
         }

         if(Candidates.size() == 0)
         {
            cout << "Nothing left!" << endl;
            continue;
         }

         FourVector NewJetP;
         for(int i = 0; i < (int)Candidates.size(); i++)
            NewJetP = NewJetP + Candidates[i];

         HJetPTComparison.Fill(MSDJet.JetPT[iJ], NewJetP.GetPT());
         
         // Step 4 - Run SD algorithm on the subtracted candidates
         vector<Node *> Nodes;
         for(int i = 0; i < (int)Candidates.size(); i++)
            Nodes.push_back(new Node(Candidates[i]));

         BuildCATree(Nodes);
         Node *Groomed = FindSDNode(Nodes[0]);

         HSDMassComparison.Fill(MSDJet.JetM[iJ], Groomed->P.GetMass());

         // Cleanup
         if(Nodes.size() > 0)
            delete Nodes[0];
      }
   }

   HN.Write();
   HPTHatAll.Write();
   HPTHatSelected.Write();

   HJetPTComparison.Write();
   HSDMassComparison.Write();

   // for(int i = 0; i < 5; i++)
   // {
   //    for(int j = 0; j < 7; j++)
   //    {
   //       if(HGenMatchingQuality[i][j] != NULL)   HGenMatchingQuality[i][j]->Write();
   //       if(HGenMatchingQuality[i][j] != NULL)   delete HGenMatchingQuality[i][j];
   //    }
   // }

   OutputFile.Close();

   InputFile.Close();
}

