#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"

#include "Code/TauHelperFunctions2.h"
#include "SetStyle.h"

#include "AngleConversion.h"

int main(int argc, char *argv[]);
bool PassBasicCuts(LeptonVectors &Leptons, bool Is2e2mu);
void PrepareHistogram(TH2D &H);

int main(int argc, char *argv[])
{
   SetThesisRegularStyle();

   string InputFile = "gg_h_2e2mu_A2AA_LooseCuts.root";
   string OutputBase = "gg_h_2e2mu_A2AA_LooseCuts";
   bool IsAngles = true;

   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " InputFileName OutputBase [IsAngles=Y]";
      return -1;
   }

   InputFile = argv[1];
   OutputBase = argv[2];
   if(argc > 3 && argv[3][0] == 'N')
      IsAngles = false;

   TH2D HM1M2CMS("HM1M2CMS", ";M_{1} (GeV);M_{2} (GeV)", 100, 4, 125, 100, 4, 65);
   TH2D HM1M2Opposite("HM1M2Opposite", ";M_{1} (GeV);M_{2} (GeV)", 125, 4, 125, 100, 4, 65);
   TH2D HM1M2Same("HM1M2Same", ";M_{1} (GeV);M_{2} (GeV)", 100, 4, 125, 100, 4, 65);
   TH2D HM1M2CMSNoCut("HM1M2CMSNoCut", ";M_{1} (GeV);M_{2} (GeV)", 100, 4, 125, 100, 4, 65);
   TH2D HM1M2OppositeNoCut("HM1M2OppositeNoCut", ";M_{1} (GeV);M_{2} (GeV)", 125, 4, 125, 100, 4, 65);
   TH2D HM1M2SameNoCut("HM1M2SameNoCut", ";M_{1} (GeV);M_{2} (GeV)", 100, 4, 125, 100, 4, 65);

   PrepareHistogram(HM1M2CMS);
   PrepareHistogram(HM1M2Opposite);
   PrepareHistogram(HM1M2Same);
   PrepareHistogram(HM1M2CMSNoCut);
   PrepareHistogram(HM1M2OppositeNoCut);
   PrepareHistogram(HM1M2SameNoCut);

   TFile File(InputFile.c_str());
   TTree *Tree = (TTree *)File.Get("Tree");

   double L1ID, L1PT, L1Eta, L1Phi;
   double L2ID, L2PT, L2Eta, L2Phi;
   double L3ID, L3PT, L3Eta, L3Phi;
   double L4ID, L4PT, L4Eta, L4Phi;

   EventParameters Event;

   if(IsAngles == false)
   {
      Tree->SetBranchAddress("L1ID", &L1ID);
      Tree->SetBranchAddress("L1PT", &L1PT);
      Tree->SetBranchAddress("L1Eta", &L1Eta);
      Tree->SetBranchAddress("L1Phi", &L1Phi);
      Tree->SetBranchAddress("L2ID", &L2ID);
      Tree->SetBranchAddress("L2PT", &L2PT);
      Tree->SetBranchAddress("L2Eta", &L2Eta);
      Tree->SetBranchAddress("L2Phi", &L2Phi);
      Tree->SetBranchAddress("L3ID", &L3ID);
      Tree->SetBranchAddress("L3PT", &L3PT);
      Tree->SetBranchAddress("L3Eta", &L3Eta);
      Tree->SetBranchAddress("L3Phi", &L3Phi);
      Tree->SetBranchAddress("L4ID", &L4ID);
      Tree->SetBranchAddress("L4PT", &L4PT);
      Tree->SetBranchAddress("L4Eta", &L4Eta);
      Tree->SetBranchAddress("L4Phi", &L4Phi);
   }
   else
   {
      Tree->SetBranchAddress("MH", &Event.HMass);
      Tree->SetBranchAddress("M1", &Event.ZMass);
      Tree->SetBranchAddress("M2", &Event.Z2Mass);
      Tree->SetBranchAddress("Phi0", &Event.Phi0);
      Tree->SetBranchAddress("Theta0", &Event.Theta0);
      Tree->SetBranchAddress("Phi", &Event.Phi);
      Tree->SetBranchAddress("Theta1", &Event.Theta1);
      Tree->SetBranchAddress("Theta2", &Event.Theta2);
      Tree->SetBranchAddress("YN", &Event.YH);
      Tree->SetBranchAddress("PTH", &Event.PTH);
      Tree->SetBranchAddress("PhiH", &Event.PhiH);
      Tree->SetBranchAddress("PhiOffset", &Event.PhiOffset);
   }

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

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

      double M1CMS = (Leptons.Lepton11 + Leptons.Lepton12).GetMass();
      double M2CMS = (Leptons.Lepton21 + Leptons.Lepton22).GetMass();
      double M1Opposite = (Leptons.Lepton11 + Leptons.Lepton22).GetMass();
      double M2Opposite = (Leptons.Lepton21 + Leptons.Lepton12).GetMass();
      double M1Same = (Leptons.Lepton11 + Leptons.Lepton21).GetMass();
      double M2Same = (Leptons.Lepton12 + Leptons.Lepton22).GetMass();

      HM1M2CMSNoCut.Fill(max(M1CMS, M2CMS), min(M1CMS, M2CMS));
      HM1M2OppositeNoCut.Fill(max(M1Opposite, M2Opposite), min(M1Opposite, M2Opposite));
      HM1M2SameNoCut.Fill(max(M1Same, M2Same), min(M1Same, M2Same));
      if(PassBasicCuts(Leptons, true) == true)
      {
         HM1M2CMS.Fill(max(M1CMS, M2CMS), min(M1CMS, M2CMS));
         HM1M2Opposite.Fill(max(M1Opposite, M2Opposite), min(M1Opposite, M2Opposite));
         HM1M2Same.Fill(max(M1Same, M2Same), min(M1Same, M2Same));
      }
   }

   HM1M2CMSNoCut.GetZaxis()->SetLabelSize(0.035);

   HM1M2CMS.Scale(1 / HM1M2CMS.Integral() * 100 * 100 / (125 - 4) / (65 - 4));
   HM1M2Opposite.Scale(1 / HM1M2Opposite.Integral() * 100 * 100 / (125 - 4) / (65 - 4));
   HM1M2Same.Scale(1 / HM1M2Same.Integral() * 100 * 100 / (125 - 4) / (65 - 4));
   HM1M2CMSNoCut.Scale(1 / HM1M2CMSNoCut.Integral() * 100 * 100 / (125 - 4) / (65 - 4));
   HM1M2OppositeNoCut.Scale(1 / HM1M2OppositeNoCut.Integral() * 100 * 100 / (125 - 4) / (65 - 4));
   HM1M2SameNoCut.Scale(1 / HM1M2SameNoCut.Integral() * 100 * 100 / (125 - 4) / (65 - 4));

   TGraph MassCut;
   MassCut.SetPoint(0, 40, 1000);
   MassCut.SetPoint(1, 40, 12);
   MassCut.SetPoint(2, 1000, 12);
   MassCut.SetLineWidth(5);
   MassCut.SetLineColor(6);

   TCanvas C;

   HM1M2CMS.Draw("colz");
   MassCut.Draw("l");

   C.SaveAs(Form("%s-M1M2CMS.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2CMS.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2CMS.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2CMS.pdf", OutputBase.c_str()));

   HM1M2Opposite.Draw("colz");
   MassCut.Draw("l");

   C.SaveAs(Form("%s-M1M2Opposite.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2Opposite.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2Opposite.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2Opposite.pdf", OutputBase.c_str()));

   HM1M2Same.Draw("colz");
   MassCut.Draw("l");

   C.SaveAs(Form("%s-M1M2Same.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2Same.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2Same.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2Same.pdf", OutputBase.c_str()));

   HM1M2CMSNoCut.Draw("colz");
   MassCut.Draw("l");

   C.SaveAs(Form("%s-M1M2CMSNoCut.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2CMSNoCut.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2CMSNoCut.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2CMSNoCut.pdf", OutputBase.c_str()));

   HM1M2OppositeNoCut.Draw("colz");
   MassCut.Draw("l");

   C.SaveAs(Form("%s-M1M2OppositeNoCut.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2OppositeNoCut.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2OppositeNoCut.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2OppositeNoCut.pdf", OutputBase.c_str()));

   HM1M2SameNoCut.Draw("colz");
   MassCut.Draw("l");

   C.SaveAs(Form("%s-M1M2SameNoCut.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2SameNoCut.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2SameNoCut.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1M2SameNoCut.pdf", OutputBase.c_str()));

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

void PrepareHistogram(TH2D &H)
{
   H.GetXaxis()->SetTitleOffset(1.1);
   H.GetYaxis()->SetTitleOffset(1.1);
   H.SetStats(0);
}





