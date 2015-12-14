#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "Code/TauHelperFunctions2.h"

#include "AngleConversion.h"
#include "Cuts.h"

int main(int argc, char *argv[])
{
   string InputFileName = "Meow.root";
   string OutputFileName = "MeowHistogram.root";

   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " Input Output" << endl;
      return -1;
   }

   InputFileName = argv[1];
   OutputFileName = argv[2];

   TFile FInput(InputFileName.c_str());
   TTree *Tree = (TTree *)FInput.Get("Tree");

   double L1PT, L1Eta, L1Phi;
   double L2PT, L2Eta, L2Phi;
   double L3PT, L3Eta, L3Phi;
   double L4PT, L4Eta, L4Phi;

   double Weight;

   Tree->SetBranchAddress("L1PT", &L1PT);
   Tree->SetBranchAddress("L1Eta", &L1Eta);
   Tree->SetBranchAddress("L1Phi", &L1Phi);
   Tree->SetBranchAddress("L2PT", &L2PT);
   Tree->SetBranchAddress("L2Eta", &L2Eta);
   Tree->SetBranchAddress("L2Phi", &L2Phi);
   Tree->SetBranchAddress("L3PT", &L3PT);
   Tree->SetBranchAddress("L3Eta", &L3Eta);
   Tree->SetBranchAddress("L3Phi", &L3Phi);
   Tree->SetBranchAddress("L4PT", &L4PT);
   Tree->SetBranchAddress("L4Eta", &L4Eta);
   Tree->SetBranchAddress("L4Phi", &L4Phi);

   Tree->SetBranchAddress("B2", &Weight);

   TFile FOutput(OutputFileName.c_str(), "RECREATE");

   TH1D HMH("HMH", ";m_{4l};a.u.", 100, 115, 135);
   TH1D HM1("HM1", ";m_{1};a.u.", 100, 4, 135);
   TH1D HM2("HM2", ";m_{2};a.u.", 100, 4, 135);
   TH1D HPhi0("HPhi0", ";#Phi_{1};a.u.", 100, 0, 2 * PI);
   TH1D HCosTheta0("HCosTheta0", ";cos#Theta_{0};a.u.", 100, -1, 1);
   TH1D HPhi("HPhi", ";#phi;a.u.", 100, 0, 2 * PI);
   TH1D HCosTheta1("HCosTheta1", ";cos#Theta_{1};a.u.", 100, -1, 1);
   TH1D HCosTheta2("HCosTheta2", ";cos#Theta_{2};a.u.", 100, -1, 1);
   TH1D HPhiH("HPhiH", ";#phi_{4l};a.u.", 100, -PI, PI);
   TH1D HPTH("HPTH", ";p_{T,4l};a.u.", 100, 0, 100);
   TH1D HYH("HYH", ";y_{4l};a.u.", 100, -3, 3);
   TH1D HPhiOffset("HPhiOffset", ";#phi_{4l};a.u.", 100, -PI, PI);

   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Weight = 1;

      Tree->GetEntry(i);
   
      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      Leptons = Leptons.ReorderLeptons2e2mu();

      if(PassPairingCuts(Leptons)[0] == false)
         continue;

      EventParameters Events = ConvertVectorsToAnglesRoberto(Leptons);

      HMH.Fill(Events.HMass, Weight);
      HM1.Fill(Events.ZMass, Weight);
      HM2.Fill(Events.Z2Mass, Weight);
      HPhi0.Fill(Events.Phi0, Weight);
      HCosTheta0.Fill(cos(Events.Theta0), Weight);
      HPhi.Fill(Events.Phi, Weight);
      HCosTheta1.Fill(cos(Events.Theta1), Weight);
      HCosTheta2.Fill(cos(Events.Theta2), Weight);
      HPhiH.Fill(Events.PhiH, Weight);
      HPTH.Fill(Events.PTH, Weight);
      HYH.Fill(Events.YH, Weight);
      HPhiOffset.Fill(Events.PhiOffset, Weight);
   }

   HMH.Write();
   HM1.Write();
   HM2.Write();
   HPhi0.Write();
   HCosTheta0.Write();
   HPhi.Write();
   HCosTheta1.Write();
   HCosTheta2.Write();
   HPhiH.Write();
   HPTH.Write();
   HYH.Write();
   HPhiOffset.Write();

   FOutput.Close();

   FInput.Close();
}




