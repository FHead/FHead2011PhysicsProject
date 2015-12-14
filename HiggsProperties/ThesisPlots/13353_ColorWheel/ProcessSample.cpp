#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

#include "AngleConversion.h"
#include "ProgressBar.h"

int main(int argc, char *argv[]);
bool PassBasicCuts(LeptonVectors &Leptons, bool Is2e2mu);
bool PassMassCuts(LeptonVectors &Leptons);

int main(int argc, char *argv[])
{
   string InputFileName = "gg_h_2e2mu_A2ZA_LooseCuts.root";
   string OutputFileName = "Result.root";
   bool Is2e2mu = true;
   bool IsAngles = true;

   if(argc > 1)
      InputFileName = argv[1];
   if(argc > 2)
      OutputFileName = argv[2];
   if(argc > 3 && argv[3][0] == 'N')
      IsAngles = false;

   TChain Tree("Tree", "Tree");
   Tree.AddFile(InputFileName.c_str());

   double L1ID, L1PT, L1Eta, L1Phi;
   double L2ID, L2PT, L2Eta, L2Phi;
   double L3ID, L3PT, L3Eta, L3Phi;
   double L4ID, L4PT, L4Eta, L4Phi;

   EventParameters Event;

   if(IsAngles == false)
   {
      Tree.SetBranchAddress("L1ID", &L1ID);
      Tree.SetBranchAddress("L1PT", &L1PT);
      Tree.SetBranchAddress("L1Eta", &L1Eta);
      Tree.SetBranchAddress("L1Phi", &L1Phi);
      Tree.SetBranchAddress("L2ID", &L2ID);
      Tree.SetBranchAddress("L2PT", &L2PT);
      Tree.SetBranchAddress("L2Eta", &L2Eta);
      Tree.SetBranchAddress("L2Phi", &L2Phi);
      Tree.SetBranchAddress("L3ID", &L3ID);
      Tree.SetBranchAddress("L3PT", &L3PT);
      Tree.SetBranchAddress("L3Eta", &L3Eta);
      Tree.SetBranchAddress("L3Phi", &L3Phi);
      Tree.SetBranchAddress("L4ID", &L4ID);
      Tree.SetBranchAddress("L4PT", &L4PT);
      Tree.SetBranchAddress("L4Eta", &L4Eta);
      Tree.SetBranchAddress("L4Phi", &L4Phi);
   }
   else
   {
      Tree.SetBranchAddress("MH", &Event.HMass);
      Tree.SetBranchAddress("M1", &Event.ZMass);
      Tree.SetBranchAddress("M2", &Event.Z2Mass);
      Tree.SetBranchAddress("Phi0", &Event.Phi0);
      Tree.SetBranchAddress("Theta0", &Event.Theta0);
      Tree.SetBranchAddress("Phi", &Event.Phi);
      Tree.SetBranchAddress("Theta1", &Event.Theta1);
      Tree.SetBranchAddress("Theta2", &Event.Theta2);
      Tree.SetBranchAddress("YN", &Event.YH);
      Tree.SetBranchAddress("PTH", &Event.PTH);
      Tree.SetBranchAddress("PhiH", &Event.PhiH);
      Tree.SetBranchAddress("PhiOffset", &Event.PhiOffset);
   }

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("CutTree", "CutTree");

   bool BaselineCut, StandardMass, OppositeMass, SameMass;
   double M1CMS, M2CMS, M1Opposite, M2Opposite, M1Same, M2Same;

   OutputTree.Branch("BaselineCut", &BaselineCut, "BaselineCut/O");
   OutputTree.Branch("StandardMass", &StandardMass, "StandardMass/O");
   OutputTree.Branch("OppositeMass", &OppositeMass, "OppositeMass/O");
   OutputTree.Branch("SameMass", &SameMass, "SameMass/O");

   OutputTree.Branch("M1CMS", &M1CMS);
   OutputTree.Branch("M2CMS", &M2CMS);
   OutputTree.Branch("M1Opposite", &M1Opposite);
   OutputTree.Branch("M2Opposite", &M2Opposite);
   OutputTree.Branch("M1Same", &M1Same);
   OutputTree.Branch("M2Same", &M2Same);

   int EntryCount = Tree.GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(3);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount <= 1000 || (iE % (EntryCount / 300) == 0))
      {
         Bar.Update(iE);
         Bar.Print();
      }

      Tree.GetEntry(iE);

      LeptonVectors Leptons;

      if(IsAngles == true)
         Leptons = ConvertAnglesToVectorsRoberto(Event);
      else
      {
         Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
         Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
         Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
         Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

         if(fabs(L1ID) == fabs(L3ID))
            Leptons = Leptons.ReorderLeptons4e();
         else
            Leptons = Leptons.ReorderLeptons2e2mu();
      }

      LeptonVectors OppositeLeptons;
      OppositeLeptons.Lepton11 = Leptons.Lepton11;
      OppositeLeptons.Lepton12 = Leptons.Lepton22;
      OppositeLeptons.Lepton21 = Leptons.Lepton21;
      OppositeLeptons.Lepton22 = Leptons.Lepton12;

      LeptonVectors SameLeptons;
      SameLeptons.Lepton11 = Leptons.Lepton11;
      SameLeptons.Lepton12 = Leptons.Lepton21;
      SameLeptons.Lepton21 = Leptons.Lepton12;
      SameLeptons.Lepton22 = Leptons.Lepton22;

      BaselineCut = PassBasicCuts(Leptons, Is2e2mu);
      StandardMass = PassMassCuts(Leptons);
      OppositeMass = PassMassCuts(OppositeLeptons);
      SameMass = PassMassCuts(SameLeptons);

      M1CMS = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
      M2CMS = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();
      M1Opposite = (OppositeLeptons.Lepton11 + OppositeLeptons.Lepton12).GetMass();
      M2Opposite = (OppositeLeptons.Lepton21 + OppositeLeptons.Lepton22).GetMass();
      M1Same = (SameLeptons.Lepton11 + SameLeptons.Lepton12).GetMass();
      M2Same = (SameLeptons.Lepton21 + SameLeptons.Lepton22).GetMass();

      OutputTree.Fill();
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();
   OutputFile.Close();

   return 0;
}

bool PassBasicCuts(LeptonVectors &Leptons, bool Is2e2mu)
{
   if(Leptons.Lepton11.GetAbsEta() > 2.4)
      return false;
   if(Leptons.Lepton12.GetAbsEta() > 2.4)
      return false;
   if(Leptons.Lepton21.GetAbsEta() > 2.4)
      return false;
   if(Leptons.Lepton22.GetAbsEta() > 2.4)
      return false;

   double PTs[4] = {0};
   PTs[0] = Leptons.Lepton11.GetPT();
   PTs[1] = Leptons.Lepton12.GetPT();
   PTs[2] = Leptons.Lepton21.GetPT();
   PTs[3] = Leptons.Lepton22.GetPT();
   sort(PTs, PTs + 4);

   if(PTs[3] < 20)   return false;
   if(PTs[2] < 10)   return false;
   if(PTs[1] < 7)    return false;
   if(PTs[0] < 7)    return false;

   if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   // if(Is2e2mu == false)
   {
      if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
      if((Leptons.Lepton21 + Leptons.Lepton12).GetMass() < 4)   return false;
   }

   return true;
}

bool PassMassCuts(LeptonVectors &Leptons)
{
   double M1 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M2 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   if(max(M1, M2) < 40)
      return false;
   if(min(M1, M2) < 12)
      return false;

   return true;
}


