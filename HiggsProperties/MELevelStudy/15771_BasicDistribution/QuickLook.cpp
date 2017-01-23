#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

#include "AngleConversion.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   string FileName = "ddbar_PDF_to_2e2mu_LO_ForEff_13TeV_10to25GeV_1.root";
   string Tag = "ddbar_PDF_to_2e2mu_LO_ForEff_13TeV_10to25GeV_1";

   PdfFileHelper PdfFile("QuickLook_" + Tag + ".pdf");

   vector<string> Title(7);
   Title[5] = "Quick look at";
   Title[6] = Tag;
   PdfFile.AddTextPage(Title);

   TFile File(FileName.c_str());
   TTree *T = (TTree *)File.Get("Tree");

   double ID1, ID2, ID3, ID4;
   double PT1, PT2, PT3, PT4;
   double Eta1, Eta2, Eta3, Eta4;
   double Phi1, Phi2, Phi3, Phi4;

   T->SetBranchAddress("L1ID", &ID1);
   T->SetBranchAddress("L2ID", &ID2);
   T->SetBranchAddress("L3ID", &ID3);
   T->SetBranchAddress("L4ID", &ID4);
   T->SetBranchAddress("L1PT", &PT1);
   T->SetBranchAddress("L2PT", &PT2);
   T->SetBranchAddress("L3PT", &PT3);
   T->SetBranchAddress("L4PT", &PT4);
   T->SetBranchAddress("L1Eta", &Eta1);
   T->SetBranchAddress("L2Eta", &Eta2);
   T->SetBranchAddress("L3Eta", &Eta3);
   T->SetBranchAddress("L4Eta", &Eta4);
   T->SetBranchAddress("L1Phi", &Phi1);
   T->SetBranchAddress("L2Phi", &Phi2);
   T->SetBranchAddress("L3Phi", &Phi3);
   T->SetBranchAddress("L4Phi", &Phi4);

   TH1D HM4l("HM4l", "4l mass;M_{4l} (GeV);", 100, 5, 30);
   TH1D HM1("HM1", "first pair mass;M_{1} (GeV);", 100, 0, 30);
   TH1D HM2("HM2", "second pair mass;M_{2} (GeV);", 100, 0, 15);
   TH1D HPhi0("HPhi0", "#Phi_{0};#Phi_{0};", 100, 0, 2 * PI);
   TH1D HCosTheta0("HCosTheta0", "cos #Theta;cos #Theta;", 100, -1, 1);
   TH1D HPhi("HPhi", "#phi;#phi;", 100, 0, 2 * PI);
   TH1D HCosTheta1("HCosTheta1", "cos #theta_{1};cos #theta_{1};", 100, -1, 1);
   TH1D HCosTheta2("HCosTheta2", "cos #theta_{2};cos #theta_{2};", 100, -1, 1);
   TH1D HY4l("HY4l", "Rapidity of 4l system;y^{4l};", 100, -10, 10);
   TH1D HPT4l("HPT4l", "p_{T} of 4l system;p_{T}^{4l};", 100, 0, 10);
   TH1D HPhi4l("HPhi4l", "#phi of 4l system;#phi^{4l};", 100, -PI, PI);
   TH1D HPhiOffset("HPhiOffset", "#phi offset;#phi_{offset};", 100, -2 * PI, 2 * PI);

   int EntryCount = T->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);

      LeptonVectors Leptons;

      Leptons.Lepton11.SetPtEtaPhi(PT1, Eta1, Phi1);
      Leptons.Lepton12.SetPtEtaPhi(PT2, Eta2, Phi2);
      Leptons.Lepton21.SetPtEtaPhi(PT3, Eta3, Phi3);
      Leptons.Lepton22.SetPtEtaPhi(PT4, Eta4, Phi4);

      if(ID1 != -ID2 && ID1 == -ID3)
      {
         swap(ID2, ID3);
         swap(Leptons.Lepton12, Leptons.Lepton21);
      }
      else if(ID1 != -ID2 && ID1 == -ID4)
      {
         swap(ID2, ID4);
         swap(Leptons.Lepton12, Leptons.Lepton22);
      }

      if(ID1 < 0 && ID2 > 0)
      {
         swap(ID1, ID2);
         swap(Leptons.Lepton11, Leptons.Lepton12);
      }
      if(ID3 < 0 && ID4 > 0)
      {
         swap(ID3, ID4);
         swap(Leptons.Lepton21, Leptons.Lepton22);
      }

      if(ID1 != ID3)
         Leptons = Leptons.ReorderLeptons2e2mu();
      else
         Leptons = Leptons.ReorderLeptons4e();

      EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      HM4l.Fill(Event.HMass);
      HM1.Fill(Event.ZMass);
      HM2.Fill(Event.Z2Mass);
      HPhi0.Fill(Event.Phi0);
      HCosTheta0.Fill(cos(Event.Theta0));
      HPhi.Fill(Event.Phi);
      HCosTheta1.Fill(cos(Event.Theta1));
      HCosTheta2.Fill(cos(Event.Theta2));
      HY4l.Fill(Event.YH);
      HPT4l.Fill(Event.PTH);
      HPhi4l.Fill(Event.PhiH);
      HPhiOffset.Fill(Event.PhiOffset);
   }

   PdfFile.AddPlot(HM4l, "", false);
   PdfFile.AddPlot(HM4l, "", true);
   PdfFile.AddPlot(HM1, "", false);
   PdfFile.AddPlot(HM1, "", true);
   PdfFile.AddPlot(HM2, "", false);
   PdfFile.AddPlot(HM2, "", true);
   PdfFile.AddPlot(HPhi0, "", false);
   PdfFile.AddPlot(HPhi0, "", true);
   PdfFile.AddPlot(HCosTheta0, "", false);
   PdfFile.AddPlot(HCosTheta0, "", true);
   PdfFile.AddPlot(HPhi, "", false);
   PdfFile.AddPlot(HPhi, "", true);
   PdfFile.AddPlot(HCosTheta1, "", false);
   PdfFile.AddPlot(HCosTheta1, "", true);
   PdfFile.AddPlot(HCosTheta2, "", false);
   PdfFile.AddPlot(HCosTheta2, "", true);
   PdfFile.AddPlot(HY4l, "", false);
   PdfFile.AddPlot(HY4l, "", true);
   PdfFile.AddPlot(HPT4l, "", false);
   PdfFile.AddPlot(HPT4l, "", true);
   PdfFile.AddPlot(HPhi4l, "", false);
   PdfFile.AddPlot(HPhi4l, "", true);
   PdfFile.AddPlot(HPhiOffset, "", false);
   PdfFile.AddPlot(HPhiOffset, "", true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();
}




