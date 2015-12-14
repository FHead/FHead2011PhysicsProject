#include <iostream>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"

#include "Code/TauHelperFunctions2.h"

#include "AngleConversion.h"
#include "Cuts.h"

int main(int argc, char *argv[])
{
   int ID = 30000;

   if(argc == 1)
   {
      cerr << "Usage: " << argv[0] << " ID" << endl;
      return -1;
   }

   ID = atoi(argv[1]);

   TChain Tree("Tree", "Tree");
   Tree.AddFile(Form("ResultTree_%d.root", ID));

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

   double A1A1, A1A2, A2A2;

   Tree.SetBranchAddress("B1_A1ZZRA1ZZR", &A1A1);
   Tree.SetBranchAddress("B1_A1ZZRA2ZZR", &A1A2);
   Tree.SetBranchAddress("B1_A2ZZRA2ZZR", &A2A2);

   TFile File(Form("Histograms%d.root", ID), "RECREATE");

   TH1D HM21("HM21", ";m_{2};a.u.", 100, 12, 70);
   TH1D HM22("HM22", ";m_{2};a.u.", 100, 12, 70);
   TH1D HM23("HM23", ";m_{2};a.u.", 100, 12, 70);
   TH1D HM24("HM24", ";m_{2};a.u.", 100, 12, 70);
   TH1D HPhi1("HPhi1", ";#phi;a.u.", 100, 0, 2 * PI);
   TH1D HPhi2("HPhi2", ";#phi;a.u.", 100, 0, 2 * PI);
   TH1D HPhi3("HPhi3", ";#phi;a.u.", 100, 0, 2 * PI);
   TH1D HPhi4("HPhi4", ";#phi;a.u.", 100, 0, 2 * PI);

   double A1ZZ = 1;
   double A2ZZ1 = 0;
   double A2ZZ2 = 3.3;
   double A2ZZ3 = 10;
   double A2ZZ4 = 2.5;

   int EntryCount = Tree.GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree.GetEntry(iE);

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      Leptons = Leptons.ReorderLeptons2e2mu();

      if(PassPairingCuts(Leptons)[0] == false)
         continue;

      EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      double L1 = A1A1 * A1ZZ * A1ZZ + A1A2 * A1ZZ * A2ZZ1 + A2A2 * A2ZZ1 * A2ZZ1;
      double L2 = A1A1 * A1ZZ * A1ZZ + A1A2 * A1ZZ * A2ZZ2 + A2A2 * A2ZZ2 * A2ZZ2;
      double L3 = A1A1 * A1ZZ * A1ZZ + A1A2 * A1ZZ * A2ZZ3 + A2A2 * A2ZZ3 * A2ZZ3;
      double L4 = A1A1 * A1ZZ * A1ZZ + A1A2 * A1ZZ * A2ZZ4 + A2A2 * A2ZZ4 * A2ZZ4;

      HM21.Fill(Event.Z2Mass, L1 * Event.Z2Mass * Event.ZMass * Event.HMass);
      HM22.Fill(Event.Z2Mass, L2 * Event.Z2Mass * Event.ZMass * Event.HMass);
      HM23.Fill(Event.Z2Mass, L3 * Event.Z2Mass * Event.ZMass * Event.HMass);
      HM24.Fill(Event.Z2Mass, L4 * Event.Z2Mass * Event.ZMass * Event.HMass);
      HPhi1.Fill(Event.Phi, L1 * Event.Z2Mass * Event.ZMass * Event.HMass);
      HPhi2.Fill(Event.Phi, L2 * Event.Z2Mass * Event.ZMass * Event.HMass);
      HPhi3.Fill(Event.Phi, L3 * Event.Z2Mass * Event.ZMass * Event.HMass);
      HPhi4.Fill(Event.Phi, L4 * Event.Z2Mass * Event.ZMass * Event.HMass);
   }

   HM21.Write();
   HM22.Write();
   HM23.Write();
   HM24.Write();
   HPhi1.Write();
   HPhi2.Write();
   HPhi3.Write();
   HPhi4.Write();

   File.Close();

   return 0;
}





