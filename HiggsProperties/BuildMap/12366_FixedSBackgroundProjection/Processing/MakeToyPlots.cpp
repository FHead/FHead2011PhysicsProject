#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"

#include "AngleConversion.h"

#include "ProgressBar.h"

int main();
LeptonVectors ReorderLeptons(LeptonVectors Leptons);
bool PassBaselineCut(EventParameters Event);

int main()
{
   TChain Tree("Tree");
   Tree.AddFile("ResultTree.root");

   double OriginalM1, OriginalM2;
   double L1PT, L1Eta, L1Phi;
   double L2PT, L2Eta, L2Phi;
   double L3PT, L3Eta, L3Phi;
   double L4PT, L4Eta, L4Phi;
   double Weight[16][4];

   Tree.SetBranchAddress("M1", &OriginalM1);
   Tree.SetBranchAddress("M2", &OriginalM2);
   Tree.SetBranchAddress("L1PT", &L1PT);      
   Tree.SetBranchAddress("L1Eta", &L1Eta);    
   Tree.SetBranchAddress("L1Phi", &L1Phi);    
   Tree.SetBranchAddress("L2PT", &L2PT);      
   Tree.SetBranchAddress("L2Eta", &L2Eta);    
   Tree.SetBranchAddress("L2Phi", &L2Phi);    
   Tree.SetBranchAddress("L3PT", &L3PT);      
   Tree.SetBranchAddress("L3Eta", &L3Eta);    
   Tree.SetBranchAddress("L3Phi", &L3Phi);    
   Tree.SetBranchAddress("L4PT", &L4PT);      
   Tree.SetBranchAddress("L4Eta", &L4Eta);    
   Tree.SetBranchAddress("L4Phi", &L4Phi);    
   Tree.SetBranchAddress("Weight", Weight);

   TFile OutputFile("OutputFile.root", "RECREATE");
   TH1D HToyM1("HToyM1", "", 100, 30, 120);
   TH1D HMCM1("HMCM1", "", 100, 30, 120);
   TH1D HToyM2("HToyM2", "", 100, 4, 60);
   TH1D HMCM2("HMCM2", "", 100, 4, 60);
   TH1D HToyPhi0("HToyPhi0", "", 25, 0, 2 * PI);
   TH1D HMCPhi0("HMCPhi0", "", 25, 0, 2 * PI);
   TH1D HToyTheta0("HToyTheta0", "", 50, 0, 1);
   TH1D HMCTheta0("HMCTheta0", "", 50, 0, 1);
   TH1D HToyPhi("HToyPhi", "", 50, 0, 2 * PI);
   TH1D HMCPhi("HMCPhi", "", 50, 0, 2 * PI);
   TH1D HToyTheta1("HToyTheta1", "", 25, 0, 1);
   TH1D HMCTheta1("HMCTheta1", "", 25, 0, 1);
   TH1D HToyTheta2("HToyTheta2", "", 25, 0, 1);
   TH1D HMCTheta2("HMCTheta2", "", 25, 0, 1);

   TH2D HToyM1M2("HToyM1M2", "", 100, 30, 120, 100, 4, 60);
   TH2D HToyM1Phi0("HToyM1Phi0", "", 100, 30, 120, 25, 0, 2 * PI);
   TH2D HToyM1Theta0("HToyM1Theta0", "", 100, 30, 120, 50, 0, 1);
   TH2D HToyM1Phi("HToyM1Phi", "", 100, 30, 120, 50, 0, 2 * PI);
   TH2D HToyM1Theta1("HToyM1Theta1", "", 100, 30, 120, 25, 0, 1);
   TH2D HToyM1Theta2("HToyM1Theta2", "", 100, 30, 120, 25, 0, 1);
   TH2D HToyM2Phi0("HToyM2Phi0", "", 100, 4, 60, 25, 0, 2 * PI);
   TH2D HToyM2Theta0("HToyM2Theta0", "", 100, 4, 60, 50, 0, 1);
   TH2D HToyM2Phi("HToyM2Phi", "", 100, 4, 60, 50, 0, 2 * PI);
   TH2D HToyM2Theta1("HToyM2Theta1", "", 100, 4, 60, 25, 0, 1);
   TH2D HToyM2Theta2("HToyM2Theta2", "", 100, 4, 60, 25, 0, 1);
   TH2D HToyPhi0Theta0("HToyPhi0Theta0", "", 25, 0, 2 * PI, 50, 0, 1);
   TH2D HToyPhi0Phi("HToyPhi0Phi", "", 25, 0, 2 * PI, 50, 0, 2 * PI);
   TH2D HToyPhi0Theta1("HToyPhi0Theta1", "", 25, 0, 2 * PI, 25, 0, 1);
   TH2D HToyPhi0Theta2("HToyPhi0Theta2", "", 25, 0, 2 * PI, 25, 0, 1);
   TH2D HToyTheta0Phi("HToyTheta0Phi", "", 50, 0, 1, 50, 0, 2 * PI);
   TH2D HToyTheta0Theta1("HToyTheta0Theta1", "", 50, 0, 1, 25, 0, 1);
   TH2D HToyTheta0Theta2("HToyTheta0Theta2", "", 50, 0, 1, 25, 0, 1);
   TH2D HToyPhiTheta1("HToyPhiTheta1", "", 50, 0, 2 * PI, 25, 0, 1);
   TH2D HToyPhiTheta2("HToyPhiTheta2", "", 50, 0, 2 * PI, 25, 0, 1);
   TH2D HToyTheta1Theta2("HToyTheta1Theta2", "", 25, 0, 1, 25, 0, 1);

   HToyM1.Sumw2();
   HMCM1.Sumw2();
   HToyM2.Sumw2();
   HMCM2.Sumw2();
   HToyPhi0.Sumw2();
   HMCPhi0.Sumw2();
   HToyTheta0.Sumw2();
   HMCTheta0.Sumw2();
   HToyPhi.Sumw2();
   HMCPhi.Sumw2();
   HToyTheta1.Sumw2();
   HMCTheta1.Sumw2();
   HToyTheta2.Sumw2();
   HMCTheta2.Sumw2();

   int EntryCount = Tree.GetEntries();
   ProgressBar Bar1(cerr, EntryCount);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree.GetEntry(iE);

      Bar1.Update(iE);
      if(iE % (EntryCount / 300) == 0)
         Bar1.Print();

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      Leptons = ReorderLeptons(Leptons);

      EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      if(PassBaselineCut(Event) == false)
         continue;

      double EventWeight = Weight[0][0] * OriginalM1 * OriginalM2;
      // double EventWeight = Weight[1][0] * OriginalM1 * OriginalM2;

      HToyM1.Fill(Event.ZMass, EventWeight);
      HToyM2.Fill(Event.Z2Mass, EventWeight);
      HToyPhi0.Fill(Event.Phi0, EventWeight);
      HToyTheta0.Fill(cos(Event.Theta0), EventWeight);
      HToyPhi.Fill(Event.Phi, EventWeight);
      HToyTheta1.Fill(cos(Event.Theta1), EventWeight);
      HToyTheta2.Fill(cos(Event.Theta2), EventWeight);

      HToyM1M2.Fill(Event.ZMass, Event.Z2Mass, EventWeight);
      HToyM1Phi0.Fill(Event.ZMass, Event.Phi0, EventWeight);
      HToyM1Theta0.Fill(Event.ZMass, cos(Event.Theta0), EventWeight);
      HToyM1Phi.Fill(Event.ZMass, Event.Phi, EventWeight);
      HToyM1Theta1.Fill(Event.ZMass, cos(Event.Theta1), EventWeight);
      HToyM1Theta2.Fill(Event.ZMass, cos(Event.Theta2), EventWeight);
      HToyM2Phi0.Fill(Event.Z2Mass, Event.Phi0, EventWeight);
      HToyM2Theta0.Fill(Event.Z2Mass, cos(Event.Theta0), EventWeight);
      HToyM2Phi.Fill(Event.Z2Mass, Event.Phi, EventWeight);
      HToyM2Theta1.Fill(Event.Z2Mass, cos(Event.Theta1), EventWeight);
      HToyM2Theta2.Fill(Event.Z2Mass, cos(Event.Theta2), EventWeight);
      HToyPhi0Theta0.Fill(Event.Phi0, cos(Event.Theta0), EventWeight);
      HToyPhi0Phi.Fill(Event.Phi0, Event.Phi, EventWeight);
      HToyPhi0Theta1.Fill(Event.Phi0, cos(Event.Theta1), EventWeight);
      HToyPhi0Theta2.Fill(Event.Phi0, cos(Event.Theta2), EventWeight);
      HToyTheta0Phi.Fill(cos(Event.Theta0), Event.Phi, EventWeight);
      HToyTheta0Theta1.Fill(cos(Event.Theta0), cos(Event.Theta1), EventWeight);
      HToyTheta0Theta2.Fill(cos(Event.Theta0), cos(Event.Theta2), EventWeight);
      HToyPhiTheta1.Fill(Event.Phi, cos(Event.Theta1), EventWeight);
      HToyPhiTheta2.Fill(Event.Phi, cos(Event.Theta2), EventWeight);
      HToyTheta1Theta2.Fill(cos(Event.Theta1), cos(Event.Theta2), EventWeight);
   }
   Bar1.Update(EntryCount);
   Bar1.Print();
   Bar1.PrintLine();

   HToyM1.Write();
   HMCM1.Write();
   HToyM2.Write();
   HMCM2.Write();
   HToyPhi0.Write();
   HMCPhi0.Write();
   HToyTheta0.Write();
   HMCTheta0.Write();
   HToyPhi.Write();
   HMCPhi.Write();
   HToyTheta1.Write();
   HMCTheta1.Write();
   HToyTheta2.Write();
   HMCTheta2.Write();

   HToyM1M2.Write();
   HToyM1Phi0.Write();
   HToyM1Theta0.Write();
   HToyM1Phi.Write();
   HToyM1Theta1.Write();
   HToyM1Theta2.Write();
   HToyM2Phi0.Write();
   HToyM2Theta0.Write();
   HToyM2Phi.Write();
   HToyM2Theta1.Write();
   HToyM2Theta2.Write();
   HToyPhi0Theta0.Write();
   HToyPhi0Phi.Write();
   HToyPhi0Theta1.Write();
   HToyPhi0Theta2.Write();
   HToyTheta0Phi.Write();
   HToyTheta0Theta1.Write();
   HToyTheta0Theta2.Write();
   HToyPhiTheta1.Write();
   HToyPhiTheta2.Write();
   HToyTheta1Theta2.Write();

   OutputFile.Close();

   return 0;
}

LeptonVectors ReorderLeptons(LeptonVectors Leptons)
{
   double M12 = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
   double M14 = (Leptons.Lepton11 + Leptons.Lepton22).GetMass();
   double M32 = (Leptons.Lepton21 + Leptons.Lepton12).GetMass();
   double M34 = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();

   double D12 = fabs(M12 - 91.186);
   double D14 = fabs(M14 - 91.186);
   double D32 = fabs(M32 - 91.186);
   double D34 = fabs(M34 - 91.186);

   if(D12 <= D14 && D12 <= D32 && D12 <= D34)
   {
      // Do nothing...already ordered
   }
   else if(D14 <= D32 && D14 <= D34)
      swap(Leptons.Lepton12, Leptons.Lepton22);
   else if(D32 <= D34)
      swap(Leptons.Lepton11, Leptons.Lepton21);
   else
   {
      swap(Leptons.Lepton11, Leptons.Lepton21);
      swap(Leptons.Lepton12, Leptons.Lepton22);
   }

   return Leptons;
}

bool PassBaselineCut(EventParameters Event)
{
   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   if(Event.ZMass < 4)    return false;
   if(Event.Z2Mass < 4)   return false;

   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 2)    return false;
   if(LPTs[2] < 2)    return false;
   if(LPTs[1] < 2)    return false;
   if(LPTs[0] < 2)    return false;

   if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;

   return true;
}





