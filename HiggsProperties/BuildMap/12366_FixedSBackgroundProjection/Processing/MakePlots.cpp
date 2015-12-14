#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

#include "TChain.h"
#include "TH1D.h"
#include "TFile.h"

#include "AngleConversion.h"

#include "ProgressBar.h"

int main();
LeptonVectors ReorderLeptons(LeptonVectors Leptons);
bool PassBaselineCut(EventParameters Event);

int main()
{
   TChain Tree("Tree");
   Tree.AddFile("SmallResultTree.root");

   TChain MCTree("MCTree");
   // MCTree.AddFile("BG_4e_ddbar_125GeV_ZZpZApAA_All.root");
   MCTree.AddFile("Spin0_SM_ZZ_4l.root");

   double OriginalM1, OriginalM2;
   double L1PT, L1Eta, L1Phi;
   double L2PT, L2Eta, L2Phi;
   double L3PT, L3Eta, L3Phi;
   double L4PT, L4Eta, L4Phi;
   double Weight[16][4];

   Tree.SetBranchAddress("M1", &OriginalM1);
   Tree.SetBranchAddress("M2", &OriginalM2);
   Tree.SetBranchAddress("L1PT", &L1PT);      MCTree.SetBranchAddress("l1pt", &L1PT);
   Tree.SetBranchAddress("L1Eta", &L1Eta);    MCTree.SetBranchAddress("l1eta", &L1Eta);
   Tree.SetBranchAddress("L1Phi", &L1Phi);    MCTree.SetBranchAddress("l1phi", &L1Phi);
   Tree.SetBranchAddress("L2PT", &L2PT);      MCTree.SetBranchAddress("l2pt", &L2PT);
   Tree.SetBranchAddress("L2Eta", &L2Eta);    MCTree.SetBranchAddress("l2eta", &L2Eta);
   Tree.SetBranchAddress("L2Phi", &L2Phi);    MCTree.SetBranchAddress("l2phi", &L2Phi);
   Tree.SetBranchAddress("L3PT", &L3PT);      MCTree.SetBranchAddress("l3pt", &L3PT);
   Tree.SetBranchAddress("L3Eta", &L3Eta);    MCTree.SetBranchAddress("l3eta", &L3Eta);
   Tree.SetBranchAddress("L3Phi", &L3Phi);    MCTree.SetBranchAddress("l3phi", &L3Phi);
   Tree.SetBranchAddress("L4PT", &L4PT);      MCTree.SetBranchAddress("l4pt", &L4PT);
   Tree.SetBranchAddress("L4Eta", &L4Eta);    MCTree.SetBranchAddress("l4eta", &L4Eta);
   Tree.SetBranchAddress("L4Phi", &L4Phi);    MCTree.SetBranchAddress("l4phi", &L4Phi);
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

      Leptons = ReorderLeptons(Leptons).GoToRest();

      EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      if(PassBaselineCut(Event) == false)
         continue;

      HToyM1.Fill(Event.ZMass, Weight[1][0] * OriginalM1 * OriginalM2);
      HToyM2.Fill(Event.Z2Mass, Weight[1][0] * OriginalM1 * OriginalM2);
      HToyPhi0.Fill(Event.Phi0, Weight[1][0] * OriginalM1 * OriginalM2);
      HToyTheta0.Fill(cos(Event.Theta0), Weight[1][0] * OriginalM1 * OriginalM2);
      HToyPhi.Fill(Event.Phi, Weight[1][0] * OriginalM1 * OriginalM2);
      HToyTheta1.Fill(cos(Event.Theta1), Weight[1][0] * OriginalM1 * OriginalM2);
      HToyTheta2.Fill(cos(Event.Theta2), Weight[1][0] * OriginalM1 * OriginalM2);
   }
   Bar1.Update(EntryCount);
   Bar1.Print();
   Bar1.PrintLine();

   EntryCount = MCTree.GetEntries();
   ProgressBar Bar2(cerr, EntryCount);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      MCTree.GetEntry(iE);

      Bar2.Update(iE);
      if(iE % (EntryCount / 300) == 0)
         Bar2.Print();

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      Leptons = ReorderLeptons(Leptons).GoToRest();

      if(iE % 2 == 1)
      {
         Leptons.Lepton11[3] = -Leptons.Lepton11[3];
         Leptons.Lepton12[3] = -Leptons.Lepton12[3];
         Leptons.Lepton21[3] = -Leptons.Lepton21[3];
         Leptons.Lepton22[3] = -Leptons.Lepton22[3];
      }

      EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      if(PassBaselineCut(Event) == false)
         continue;

      HMCM1.Fill(Event.ZMass);
      HMCM2.Fill(Event.Z2Mass);
      HMCPhi0.Fill(Event.Phi0);
      HMCTheta0.Fill(cos(Event.Theta0));
      HMCPhi.Fill(Event.Phi);
      HMCTheta1.Fill(cos(Event.Theta1));
      HMCTheta2.Fill(cos(Event.Theta2));
   }
   Bar2.Update(EntryCount);
   Bar2.Print();
   Bar2.PrintLine();

   // HToyM1.Scale(1 / HToyM1.Integral());
   // HMCM1.Scale(1 / HMCM1.Integral());
   // HToyM2.Scale(1 / HToyM2.Integral());
   // HMCM2.Scale(1 / HMCM2.Integral());
   // HToyPhi0.Scale(1 / HToyPhi0.Integral());
   // HMCPhi0.Scale(1 / HMCPhi0.Integral());
   // HToyTheta0.Scale(1 / HToyTheta0.Integral());
   // HMCTheta0.Scale(1 / HMCTheta0.Integral());
   // HToyPhi.Scale(1 / HToyPhi.Integral());
   // HMCPhi.Scale(1 / HMCPhi.Integral());
   // HToyTheta1.Scale(1 / HToyTheta1.Integral());
   // HMCTheta1.Scale(1 / HMCTheta1.Integral());
   // HToyTheta2.Scale(1 / HToyTheta2.Integral());
   // HMCTheta2.Scale(1 / HMCTheta2.Integral());

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





