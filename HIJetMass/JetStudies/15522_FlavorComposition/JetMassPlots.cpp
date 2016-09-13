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
   GenParticleTreeMessenger MGen(InputFile);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TH2D HLightNVsGenJetPTRecoSubJetDR("HLightNVsGenJetPTRecoSubJetDR",
      ";Gen Jet PT;Reco SubJet DR;Light quark count", 100, 80, 500, 100, 0, 0.5);
   TH2D HGluonNVsGenJetPTRecoSubJetDR("HGluonNVsGenJetPTRecoSubJetDR",
      ";Gen Jet PT;Reco SubJet DR;Gluon quark count", 100, 80, 500, 100, 0, 0.5);
   TH2D HCharmNVsGenJetPTRecoSubJetDR("HCharmNVsGenJetPTRecoSubJetDR",
      ";Gen Jet PT;Reco SubJet DR;Charm quark count", 100, 80, 500, 100, 0, 0.5);
   TH2D HHeavyNVsGenJetPTRecoSubJetDR("HHeavyNVsGenJetPTRecoSubJetDR",
      ";Gen Jet PT;Reco SubJet DR;Heavy quark count", 100, 80, 500, 100, 0, 0.5);
   TProfile2D PLightSDMassVsGenJetPTRecoSubJetDR("PLightSDMassVsGenJetPTRecoSubJetDR",
      ";Gen Jet PT;Reco SubJet DR;Light quark SDMass", 100, 80, 500, 100, 0, 0.5);
   TProfile2D PGluonSDMassVsGenJetPTRecoSubJetDR("PGluonSDMassVsGenJetPTRecoSubJetDR",
      ";Gen Jet PT;Reco SubJet DR;Gluon quark SDMass", 100, 80, 500, 100, 0, 0.5);
   TProfile2D PCharmSDMassVsGenJetPTRecoSubJetDR("PCharmSDMassVsGenJetPTRecoSubJetDR",
      ";Gen Jet PT;Reco SubJet DR;Charm quark SDMass", 100, 80, 500, 100, 0, 0.5);
   TProfile2D PHeavySDMassVsGenJetPTRecoSubJetDR("PHeavySDMassVsGenJetPTRecoSubJetDR",
      ";Gen Jet PT;Reco SubJet DR;Heavy quark SDMass", 100, 80, 500, 100, 0, 0.5);

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);
      MGen.GetEntry(iEntry);

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

         if(Flavor == 1 || Flavor == 2 || Flavor == 3)
         {
            HLightNVsGenJetPTRecoSubJetDR.Fill(MSDJet.RefPT[i], RecoSubJetDR);
            PLightSDMassVsGenJetPTRecoSubJetDR.Fill(MSDJet.RefPT[i], RecoSubJetDR, MSDJet.JetM[i]);
         }
         else if(Flavor == 4)
         {
            HCharmNVsGenJetPTRecoSubJetDR.Fill(MSDJet.RefPT[i], RecoSubJetDR);
            PCharmSDMassVsGenJetPTRecoSubJetDR.Fill(MSDJet.RefPT[i], RecoSubJetDR, MSDJet.JetM[i]);
         }
         else if(Flavor == 5)
         {
            HHeavyNVsGenJetPTRecoSubJetDR.Fill(MSDJet.RefPT[i], RecoSubJetDR);
            PHeavySDMassVsGenJetPTRecoSubJetDR.Fill(MSDJet.RefPT[i], RecoSubJetDR, MSDJet.JetM[i]);
         }
         else if(Flavor == 21)
         {
            HGluonNVsGenJetPTRecoSubJetDR.Fill(MSDJet.RefPT[i], RecoSubJetDR);
            PGluonSDMassVsGenJetPTRecoSubJetDR.Fill(MSDJet.RefPT[i], RecoSubJetDR, MSDJet.JetM[i]);
         }
         else
            cerr << "Flavor = " << Flavor << endl;
      }
   }

   HLightNVsGenJetPTRecoSubJetDR.Write();
   HGluonNVsGenJetPTRecoSubJetDR.Write();
   HCharmNVsGenJetPTRecoSubJetDR.Write();
   HHeavyNVsGenJetPTRecoSubJetDR.Write();
   PLightSDMassVsGenJetPTRecoSubJetDR.Write();
   PGluonSDMassVsGenJetPTRecoSubJetDR.Write();
   PCharmSDMassVsGenJetPTRecoSubJetDR.Write();
   PHeavySDMassVsGenJetPTRecoSubJetDR.Write();
   
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





