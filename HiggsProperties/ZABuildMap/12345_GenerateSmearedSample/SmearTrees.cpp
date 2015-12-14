#include <iostream>
using namespace std;

#include "TChain.h"
#include "TTree.h"
#include "TFile.h"

#include "Code/TauHelperFunctions2.h"
#include "Code/DrawRandom.h"

#include "Constants.h"
#include "AngleConversion.h"

#include "LeptonResponse.h"

int main(int argc, char *argv[]);
int FlipID(int ID);
double GetASmear(FourVector Vector, int ID);

int main(int argc, char *argv[])
{
   string InputFileName = "Source/Events_110001.root";
   string OutputFileName = "Events_110001.root";

   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputFile" << endl;

      return -1;
   }

   InputFileName = argv[1];
   OutputFileName = argv[2];
   
   TChain InputTree("Tree");
   InputTree.AddFile(InputFileName.c_str());

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree OutputTree("Tree", "Tree, smeared!");

   double L1PT, L1Eta, L1Phi, L2PT, L2Eta, L2Phi, PPT, PEta, PPhi;
   int L1ID, L2ID;
   double Weight;

   ZAEventParameters Event;

   InputTree.SetBranchAddress("L1PT", &L1PT);
   InputTree.SetBranchAddress("L1Eta", &L1Eta);
   InputTree.SetBranchAddress("L1Phi", &L1Phi);
   InputTree.SetBranchAddress("L1ID", &L1ID);
   InputTree.SetBranchAddress("L2PT", &L2PT);
   InputTree.SetBranchAddress("L2Eta", &L2Eta);
   InputTree.SetBranchAddress("L2Phi", &L2Phi);
   InputTree.SetBranchAddress("L2ID", &L2ID);
   InputTree.SetBranchAddress("PPT", &PPT);
   InputTree.SetBranchAddress("PEta", &PEta);
   InputTree.SetBranchAddress("PPhi", &PPhi);

   OutputTree.Branch("L1PT", &L1PT, "L1PT/D");
   OutputTree.Branch("L1Eta", &L1Eta, "L1Eta/D");
   OutputTree.Branch("L1Phi", &L1Phi, "L1Phi/D");
   OutputTree.Branch("L1ID", &L1ID, "L1ID/I");
   OutputTree.Branch("L2PT", &L2PT, "L2PT/D");
   OutputTree.Branch("L2Eta", &L2Eta, "L2Eta/D");
   OutputTree.Branch("L2Phi", &L2Phi, "L2Phi/D");
   OutputTree.Branch("L2ID", &L2ID, "L2ID/I");
   OutputTree.Branch("PPT", &PPT, "PPT/D");
   OutputTree.Branch("PEta", &PEta, "PEta/D");
   OutputTree.Branch("PPhi", &PPhi, "PPhi/D");
   OutputTree.Branch("Weight", &Weight, "Weight/D");

   OutputTree.Branch("MH", &Event.HMass, "MH/D");
   OutputTree.Branch("MZ", &Event.ZMass, "MZ/D");
   OutputTree.Branch("Phi0", &Event.Phi0, "Phi0/D");
   OutputTree.Branch("Theta0", &Event.Theta0, "Theta0/D");
   OutputTree.Branch("ThetaLL", &Event.ThetaLL, "ThetaLL/D");
   OutputTree.Branch("PhiOffset", &Event.PhiOffset, "PhiOffset/D");
   OutputTree.Branch("PhiH", &Event.PhiH, "PhiH/D");
   OutputTree.Branch("PTH", &Event.PTH, "PTH/D");
   OutputTree.Branch("YH", &Event.YH, "YH/D");

   int EntryCount = InputTree.GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      InputTree.GetEntry(iE);

      ZALeptonVectors Leptons;
      Leptons.Lepton1.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton2.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Photon.SetPtEtaPhi(PPT, PEta, PPhi);

      Leptons.Lepton1 = Leptons.Lepton1 * GetASmear(Leptons.Lepton1, L1ID);
      Leptons.Lepton2 = Leptons.Lepton2 * GetASmear(Leptons.Lepton2, L2ID);
      Leptons.Photon = Leptons.Photon * GetASmear(Leptons.Photon, 11);

      L1PT = Leptons.Lepton1.GetPT();
      L1Eta = Leptons.Lepton1.GetEta();
      L1Phi = Leptons.Lepton1.GetPhi();
      L2PT = Leptons.Lepton2.GetPT();
      L2Eta = Leptons.Lepton2.GetEta();
      L2Phi = Leptons.Lepton2.GetPhi();
      PPT = Leptons.Photon.GetPT();
      PEta = Leptons.Photon.GetEta();
      PPhi = Leptons.Photon.GetPhi();

      Weight = 1;
      if(L1ID == 11 || L1ID == -11)
         Weight = Weight * GetElectronEfficiencyPtEta(L1PT, Leptons.Lepton1[3] / Leptons.Lepton1.GetP(), L1Phi);
      else
         Weight = Weight * GetMuonEfficiencyPtEta(L1PT, Leptons.Lepton1[3] / Leptons.Lepton1.GetP(), L1Phi);
      if(L2ID == 11 || L2ID == -11)
         Weight = Weight * GetElectronEfficiencyPtEta(L2PT, Leptons.Lepton2[3] / Leptons.Lepton2.GetP(), L2Phi);
      else
         Weight = Weight * GetMuonEfficiencyPtEta(L2PT, Leptons.Lepton2[3] / Leptons.Lepton2.GetP(), L2Phi);
      Weight = Weight * GetElectronEfficiencyPtEta(PPT, Leptons.Photon[3] / Leptons.Photon.GetP(), PPhi);

      Event = ConvertVectorsToAnglesRoberto(Leptons);

      OutputTree.Fill();
   }

   OutputTree.Write();
   OutputFile.Close();

   return 0;
}

int FlipID(int ID)
{
   if(ID == 11)    return 13;
   if(ID == -11)   return -13;
   if(ID == 13)    return 11;
   if(ID == -13)   return -11;

   return 0;
}

double GetASmear(FourVector Vector, int ID)
{
   double CentralValue = 0;

   if(ID == 11 || ID == -11)
      CentralValue = SmearElectronCentral(Vector, 0) * 2;
   else
      CentralValue = SmearMuonCentral(Vector, 0) * 2;
   if(CentralValue < 1e-10)
      return 0;

   double Delta = 0;

   bool OK = false;
   while(OK == false)
   {
      Delta = DrawRandom(-0.5, 0.5);
      double Value = 0;
      if(ID == 11 || ID == -11)
         Value = SmearElectronCentral(Vector, Delta);
      else
         Value = SmearMuonCentral(Vector, Delta);

      if(DrawRandom(0, 1) < Value / CentralValue)
         OK = true;
   }

   return (Delta + 1);
}






