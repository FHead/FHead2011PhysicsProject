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
void PrepareHistogram(TH1D &H);

int main(int argc, char *argv[])
{
   SetStyle();

   string InputFile = "gg_h_2e2mu_A2AA_LooseCuts.root";
   string OutputBase = "gg_h_2e2mu_A2AA_LooseCuts";

   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " InputFileName OutputBase";
      return -1;
   }

   InputFile = argv[1];
   OutputBase = argv[2];

   TH1D HM1("HM1", ";m_{1}", 100, 4, 120);
   TH1D HM2("HM2", ";m_{2}", 100, 4, 120);
   TH1D HPhi0("HPhi0", ";#Phi_{1}", 100, 0, 2 * PI);
   TH1D HCosTheta0("HCosTheta0", ";cos#Theta", 100, -1, 1);
   TH1D HPhi("HPhi", ";#phi", 100, 0, 2 * PI);
   TH1D HCosTheta1("HCosTheta1", ";cos#theta_{1}", 100, -1, 1);
   TH1D HCosTheta2("HCosTheta2", ";cos#theta_{2}", 100, -1, 1);
   TH1D HM1NoCut("HM1NoCut", ";m_{1}", 100, 4, 120);
   TH1D HM2NoCut("HM2NoCut", ";m_{2}", 100, 4, 120);
   TH1D HPhi0NoCut("HPhi0NoCut", ";#Phi_{1}", 100, 0, 2 * PI);
   TH1D HCosTheta0NoCut("HCosTheta0NoCut", ";cos#Theta", 100, -1, 1);
   TH1D HPhiNoCut("HPhiNoCut", ";#phi", 100, 0, 2 * PI);
   TH1D HCosTheta1NoCut("HCosTheta1NoCut", ";cos#theta_{1}", 100, -1, 1);
   TH1D HCosTheta2NoCut("HCosTheta2NoCut", ";cos#theta_{2}", 100, -1, 1);

   PrepareHistogram(HM1);
   PrepareHistogram(HM2);
   PrepareHistogram(HPhi0);
   PrepareHistogram(HCosTheta0);
   PrepareHistogram(HPhi);
   PrepareHistogram(HCosTheta1);
   PrepareHistogram(HCosTheta2);
   PrepareHistogram(HM1NoCut);
   PrepareHistogram(HM2NoCut);
   PrepareHistogram(HPhi0NoCut);
   PrepareHistogram(HCosTheta0NoCut);
   PrepareHistogram(HPhiNoCut);
   PrepareHistogram(HCosTheta1NoCut);
   PrepareHistogram(HCosTheta2NoCut);

   TFile File(InputFile.c_str());
   TTree *Tree = (TTree *)File.Get("Tree");

   EventParameters Event;

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

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

      HM1NoCut.Fill(Event.ZMass);
      HM2NoCut.Fill(Event.Z2Mass);
      HPhi0NoCut.Fill(Event.Phi0);
      HCosTheta0NoCut.Fill(cos(Event.Theta0));
      HPhiNoCut.Fill(Event.Phi);
      HCosTheta1NoCut.Fill(cos(Event.Theta1));
      HCosTheta2NoCut.Fill(cos(Event.Theta2));

      if(PassBasicCuts(Leptons, true) == true)
      {
         HM1.Fill(Event.ZMass);
         HM2.Fill(Event.Z2Mass);
         HPhi0.Fill(Event.Phi0);
         HCosTheta0.Fill(cos(Event.Theta0));
         HPhi.Fill(Event.Phi);
         HCosTheta1.Fill(cos(Event.Theta1));
         HCosTheta2.Fill(cos(Event.Theta2));
      }
   }

   TCanvas C("C", "C", 1024, 1024);

   HM1NoCut.Draw("colz");

   C.SaveAs(Form("%s-M1NoCut.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1NoCut.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1NoCut.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1NoCut.pdf", OutputBase.c_str()));

   HM2NoCut.Draw("colz");

   C.SaveAs(Form("%s-M2NoCut.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-M2NoCut.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-M2NoCut.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-M2NoCut.pdf", OutputBase.c_str()));

   HPhi0NoCut.Draw("colz");

   C.SaveAs(Form("%s-Phi0NoCut.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-Phi0NoCut.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-Phi0NoCut.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-Phi0NoCut.pdf", OutputBase.c_str()));

   HCosTheta0NoCut.Draw("colz");

   C.SaveAs(Form("%s-CosTheta0NoCut.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta0NoCut.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta0NoCut.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta0NoCut.pdf", OutputBase.c_str()));

   HPhiNoCut.Draw("colz");

   C.SaveAs(Form("%s-PhiNoCut.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-PhiNoCut.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-PhiNoCut.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-PhiNoCut.pdf", OutputBase.c_str()));

   HCosTheta1NoCut.Draw("colz");

   C.SaveAs(Form("%s-CosTheta1NoCut.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta1NoCut.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta1NoCut.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta1NoCut.pdf", OutputBase.c_str()));

   HCosTheta2NoCut.Draw("colz");

   C.SaveAs(Form("%s-CosTheta2NoCut.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta2NoCut.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta2NoCut.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta2NoCut.pdf", OutputBase.c_str()));

   HM1.Draw("colz");

   C.SaveAs(Form("%s-M1.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-M1.pdf", OutputBase.c_str()));

   HM2.Draw("colz");

   C.SaveAs(Form("%s-M2.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-M2.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-M2.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-M2.pdf", OutputBase.c_str()));

   HPhi0.Draw("colz");

   C.SaveAs(Form("%s-Phi0.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-Phi0.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-Phi0.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-Phi0.pdf", OutputBase.c_str()));

   HCosTheta0.Draw("colz");

   C.SaveAs(Form("%s-CosTheta0.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta0.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta0.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta0.pdf", OutputBase.c_str()));

   HPhi.Draw("colz");

   C.SaveAs(Form("%s-Phi.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-Phi.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-Phi.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-Phi.pdf", OutputBase.c_str()));

   HCosTheta1.Draw("colz");

   C.SaveAs(Form("%s-CosTheta1.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta1.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta1.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta1.pdf", OutputBase.c_str()));

   HCosTheta2.Draw("colz");

   C.SaveAs(Form("%s-CosTheta2.png", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta2.C", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta2.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s-CosTheta2.pdf", OutputBase.c_str()));

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

void PrepareHistogram(TH1D &H)
{
   H.GetXaxis()->SetTitleOffset(1.1);
   H.GetYaxis()->SetTitleOffset(1.1);

   H.SetStats(0);

   H.SetMinimum(0);
}





