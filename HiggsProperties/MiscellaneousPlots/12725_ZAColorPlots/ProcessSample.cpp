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
   string OutputFileName = "Result.root";

   TChain Tree("Tree", "Tree");
   for(int i = 1; i <= 50; i++)
      Tree.AddFile(Form("Samples/Events_ZA08%03d.root", i));

   double L1PT, L1Eta, L1Phi;   int L1ID;
   double L2PT, L2Eta, L2Phi;   int L2ID;
   double L3PT, L3Eta, L3Phi;   int L3ID;
   double L4PT, L4Eta, L4Phi;   int L4ID;

   Tree.SetBranchAddress("L1PT", &L1PT);
   Tree.SetBranchAddress("L1Eta", &L1Eta);
   Tree.SetBranchAddress("L1Phi", &L1Phi);
   Tree.SetBranchAddress("L1ID", &L1ID);
   Tree.SetBranchAddress("L2PT", &L2PT);
   Tree.SetBranchAddress("L2Eta", &L2Eta);
   Tree.SetBranchAddress("L2Phi", &L2Phi);
   Tree.SetBranchAddress("L2ID", &L2ID);
   Tree.SetBranchAddress("L3PT", &L3PT);
   Tree.SetBranchAddress("L3Eta", &L3Eta);
   Tree.SetBranchAddress("L3Phi", &L3Phi);
   Tree.SetBranchAddress("L3ID", &L3ID);
   Tree.SetBranchAddress("L4PT", &L4PT);
   Tree.SetBranchAddress("L4Eta", &L4Eta);
   Tree.SetBranchAddress("L4Phi", &L4Phi);
   Tree.SetBranchAddress("L4ID", &L4ID);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree("CutTree", "CutTree");

   bool BaselineCut, StandardMass, OppositeMass, SameMass;

   OutputTree.Branch("BaselineCut", &BaselineCut, "BaselineCut/O");
   OutputTree.Branch("StandardMass", &StandardMass, "StandardMass/O");
   OutputTree.Branch("OppositeMass", &OppositeMass, "OppositeMass/O");
   OutputTree.Branch("SameMass", &SameMass, "SameMass/O");

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
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      if(L1ID < 0)
      {
         swap(Leptons.Lepton11, Leptons.Lepton12);
         swap(L1ID, L2ID);
      }
      if(L3ID < 0)
      {
         swap(Leptons.Lepton21, Leptons.Lepton22);
         swap(L3ID, L4ID);
      }

      if(L1ID == L3ID)
         Leptons = Leptons.ReorderLeptons4e();
      else
         Leptons = Leptons.ReorderLeptons2e2mu();

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

      BaselineCut = PassBasicCuts(Leptons, L1ID != L3ID);
      StandardMass = PassMassCuts(Leptons);
      OppositeMass = PassMassCuts(OppositeLeptons);
      SameMass = PassMassCuts(SameLeptons);

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

   if(Is2e2mu == false)
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


