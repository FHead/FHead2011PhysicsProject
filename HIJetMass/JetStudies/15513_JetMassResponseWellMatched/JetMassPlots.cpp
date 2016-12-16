#include <iostream>
using namespace std;

#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"

#include "BasicUtilities.h"
#include "Messenger.h"

int main(int argc, char *argv[]);
double CalculateDR(double eta1, double phi1, double eta2, double phi2);

int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " Input Output Tag" << endl;
      return -1;
   }

   string Input = argv[1];
   string Output = argv[2];
   string Tag = argv[3];

   bool IsData = IsDataFromTag(Tag);
   bool IsPP = IsPPFromTag(Tag);

   if(IsData == true)
   {
      cerr << "Let's rather not run on data." << endl;
      return -1;
   }

   TFile InputFile(Input.c_str());

   string JetTreeName = "akCs4PFJetAnalyzer/t";
   string SoftDropJetTreeName = "akCsSoftDrop4PFJetAnalyzer/t";
   if(IsPP == true)
   {
      JetTreeName = "ak4PFJetAnalyzer/t";
      SoftDropJetTreeName = "akSoftDrop4PFJetAnalyzer/t";
   }

   HiEventTreeMessenger MHiEvent(InputFile);
   JetTreeMessenger MJet(InputFile, JetTreeName);
   JetTreeMessenger MSDJet(InputFile, SoftDropJetTreeName);

   if(MHiEvent.Tree == NULL)
      return -1;

   TFile OutputFile(Output.c_str(), "RECREATE");

   TH2D HSDMassRatioVsJetPT("HSDMassRatioVsJetPT", ";Gen Jet PT;Reco SD Mass / Gen SD Mass",
      100, 80, 500, 100, 0, 2);
   TH2D HSDMassRatioVsJetPT_DR01("HSDMassRatioVsJetPT_DR01",
      "0.0 < DR < 0.1;Gen Jet PT;Reco SD Mass / Gen SD Mass",
      100, 80, 500, 100, 0, 2);
   TH2D HSDMassRatioVsJetPT_DR02("HSDMassRatioVsJetPT_DR02",
      "0.1 < DR < 0.2;Gen Jet PT;Reco SD Mass / Gen SD Mass",
      100, 80, 500, 100, 0, 2);
   TH2D HSDMassRatioVsJetPT_DR03("HSDMassRatioVsJetPT_DR03",
      "0.2 < DR < 0.3;Gen Jet PT;Reco SD Mass / Gen SD Mass",
      100, 80, 500, 100, 0, 2);
   TH2D HSDMassRatioVsJetPT_DR04("HSDMassRatioVsJetPT_DR04",
      "0.3 < DR < 0.4;Gen Jet PT;Reco SD Mass / Gen SD Mass",
      100, 80, 500, 100, 0, 2);
   TProfile PSDMassRatioVsJetPT("PSDMassRatioVsJetPT", ";Gen Jet PT;Reco SD Mass / Gen SD Mass",
      100, 80, 500);
   TProfile PSDMassRatioVsJetPT_DR01("PSDMassRatioVsJetPT_DR01",
      "0.0 < DR < 0.1;Gen Jet PT;Reco SD Mass / Gen SD Mass",
      100, 80, 500);
   TProfile PSDMassRatioVsJetPT_DR02("PSDMassRatioVsJetPT_DR02",
      "0.1 < DR < 0.2;Gen Jet PT;Reco SD Mass / Gen SD Mass",
      100, 80, 500);
   TProfile PSDMassRatioVsJetPT_DR03("PSDMassRatioVsJetPT_DR03",
      "0.2 < DR < 0.3;Gen Jet PT;Reco SD Mass / Gen SD Mass",
      100, 80, 500);
   TProfile PSDMassRatioVsJetPT_DR04("PSDMassRatioVsJetPT_DR04",
      "0.3 < DR < 0.4;Gen Jet PT;Reco SD Mass / Gen SD Mass",
      100, 80, 500);

   TH2D HToyMassResponseVsSubJetDR_Smear0("HToyMassResponseVsSubJetDR_Smear0",
      "Smear sigma = 0.00;Gen Sub Jet DR;Toy Mass / SD Gen Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HToyMassResponseVsSubJetDR_Smear1("HToyMassResponseVsSubJetDR_Smear1",
      "Smear sigma = 0.02;Gen Sub Jet DR;Toy Mass / SD Gen Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HToyMassResponseVsSubJetDR_Smear2("HToyMassResponseVsSubJetDR_Smear2",
      "Smear sigma = 0.05;Gen Sub Jet DR;Toy Mass / SD Gen Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HToyMassResponseVsSubJetDR_Smear3("HToyMassResponseVsSubJetDR_Smear3",
      "Smear sigma = 0.10;Gen Sub Jet DR;Toy Mass / SD Gen Mass", 100, 0, 0.5, 100, 0, 2);

   TH2D HToyMassResponseVsSubJetDR_PTSmear0("HToyMassResponseVsSubJetDR_PTSmear0",
      "PT smear sigma = 0.00;Gen Sub Jet DR;Toy Mass / SD Gen Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HToyMassResponseVsSubJetDR_PTSmear1("HToyMassResponseVsSubJetDR_PTSmear1",
      "PT smear sigma = 0.05;Gen Sub Jet DR;Toy Mass / SD Gen Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HToyMassResponseVsSubJetDR_PTSmear2("HToyMassResponseVsSubJetDR_PTSmear2",
      "PT smear sigma = 0.10;Gen Sub Jet DR;Toy Mass / SD Gen Mass", 100, 0, 0.5, 100, 0, 2);
   TH2D HToyMassResponseVsSubJetDR_PTSmear3("HToyMassResponseVsSubJetDR_PTSmear3",
      "PT smear sigma = 0.20;Gen Sub Jet DR;Toy Mass / SD Gen Mass", 100, 0, 0.5, 100, 0, 2);
   TProfile PToyMassResponseVsSubJetDR_PTSmear0("PToyMassResponseVsSubJetDR_PTSmear0",
      "PT smear sigma = 0.00;Gen Sub Jet DR;Toy Mass / SD Gen Mass", 100, 0, 0.5);
   TProfile PToyMassResponseVsSubJetDR_PTSmear1("PToyMassResponseVsSubJetDR_PTSmear1",
      "PT smear sigma = 0.05;Gen Sub Jet DR;Toy Mass / SD Gen Mass", 100, 0, 0.5);
   TProfile PToyMassResponseVsSubJetDR_PTSmear2("PToyMassResponseVsSubJetDR_PTSmear2",
      "PT smear sigma = 0.10;Gen Sub Jet DR;Toy Mass / SD Gen Mass", 100, 0, 0.5);
   TProfile PToyMassResponseVsSubJetDR_PTSmear3("PToyMassResponseVsSubJetDR_PTSmear3",
      "PT smear sigma = 0.20;Gen Sub Jet DR;Toy Mass / SD Gen Mass", 100, 0, 0.5);

   TH2D HGenSubJetPositionSpread("HGenSubJetPositionSpread",
      "Generated level sub jet locations with gen sub jet at (#pm1, 0);\"x\";\"y\"",
      100, -4, 4, 100, -4, 4);
   TH2D HLeadingSubJetPositionSpread("HLeadingSubJetPositionSpread",
      "Reconstructed level sub jet 1 locations with gen sub jet at (#pm1, 0);\"x\";\"y\"",
      100, -4, 4, 100, -4, 4);
   TH2D HLeadingSubJetPositionSpread_DR01("HLeadingSubJetPositionSpread_DR01",
      "Reconstructed level sub jet 1 locations with gen sub jet at (#pm1, 0), 0.0 < DR < 0.1;\"x\";\"y\"",
      100, -4, 4, 100, -4, 4);
   TH2D HLeadingSubJetPositionSpread_DR02("HLeadingSubJetPositionSpread_DR02",
      "Reconstructed level sub jet 1 locations with gen sub jet at (#pm1, 0), 0.1 < DR < 0.2;\"x\";\"y\"",
      100, -4, 4, 100, -4, 4);
   TH2D HLeadingSubJetPositionSpread_DR03("HLeadingSubJetPositionSpread_DR03",
      "Reconstructed level sub jet 1 locations with gen sub jet at (#pm1, 0), 0.2 < DR < 0.3;\"x\";\"y\"",
      100, -4, 4, 100, -4, 4);
   TH2D HLeadingSubJetPositionSpread_DR04("HLeadingSubJetPositionSpread_DR04",
      "Reconstructed level sub jet 1 locations with gen sub jet at (#pm1, 0), 0.3 < DR < 0.4;\"x\";\"y\"",
      100, -4, 4, 100, -4, 4);
   TH2D HSubleadingSubJetPositionSpread("HSubleadingSubJetPositionSpread",
      "Reconstructed level sub jet 2 locations with gen sub jet at (#pm1, 0);\"x\";\"y\"",
      100, -4, 4, 100, -4, 4);
   TH2D HSubleadingSubJetPositionSpread_DR01("HSubleadingSubJetPositionSpread_DR01",
      "Reconstructed level sub jet 2 locations with gen sub jet at (#pm1, 0), 0.0 < DR < 0.1;\"x\";\"y\"",
      100, -4, 4, 100, -4, 4);
   TH2D HSubleadingSubJetPositionSpread_DR02("HSubleadingSubJetPositionSpread_DR02",
      "Reconstructed level sub jet 2 locations with gen sub jet at (#pm1, 0), 0.1 < DR < 0.2;\"x\";\"y\"",
      100, -4, 4, 100, -4, 4);
   TH2D HSubleadingSubJetPositionSpread_DR03("HSubleadingSubJetPositionSpread_DR03",
      "Reconstructed level sub jet 2 locations with gen sub jet at (#pm1, 0), 0.2 < DR < 0.3;\"x\";\"y\"",
      100, -4, 4, 100, -4, 4);
   TH2D HSubleadingSubJetPositionSpread_DR04("HSubleadingSubJetPositionSpread_DR04",
      "Reconstructed level sub jet 2 locations with gen sub jet at (#pm1, 0), 0.3 < DR < 0.4;\"x\";\"y\"",
      100, -4, 4, 100, -4, 4);

   TH2D HLeadingSubJetXVsSubleadingSubJetX("HLeadingSubJetXVsSubleadingSubJetX",
      ";leading subjet \"x\";subleading subjet \"x\"",
      100, -4, 4, 100, -4, 4);
   TH2D HLeadingSubJetXVsSubleadingSubJetX_DR01("HLeadingSubJetXVsSubleadingSubJetX_DR01",
      "0.0 < DR < 0.1;leading subjet \"x\";subleading subjet \"x\"",
      100, -4, 4, 100, -4, 4);
   TH2D HLeadingSubJetXVsSubleadingSubJetX_DR02("HLeadingSubJetXVsSubleadingSubJetX_DR02",
      "0.1 < DR < 0.2;leading subjet \"x\";subleading subjet \"x\"",
      100, -4, 4, 100, -4, 4);
   TH2D HLeadingSubJetXVsSubleadingSubJetX_DR03("HLeadingSubJetXVsSubleadingSubJetX_DR03",
      "0.2 < DR < 0.3;leading subjet \"x\";subleading subjet \"x\"",
      100, -4, 4, 100, -4, 4);
   TH2D HLeadingSubJetXVsSubleadingSubJetX_DR04("HLeadingSubJetXVsSubleadingSubJetX_DR04",
      "0.3 < DR < 0.4;leading subjet \"x\";subleading subjet \"x\"",
      100, -4, 4, 100, -4, 4);

   TH2D HLeadingSubJetPTResponseVsLeadingX("HLeadingSubJetPTResponseVsLeadingX",
      "Reco Leading subjet PT response vs. \"x\";\"x\";Reco subjet PT / Gen subjet PT", 100, -2, 2, 100, 0, 2);
   TProfile PLeadingSubJetPTResponseVsLeadingX("PLeadingSubJetPTResponseVsLeadingX",
      "Reco Leading subjet PT response vs. \"x\";\"x\";Reco subjet PT / Gen subjet PT", 100, -2, 2);
   TH2D HSubleadingSubJetPTResponseVsLeadingX("HSubleadingSubJetPTResponseVsLeadingX",
      "Reco Subleading subjet PT response vs. \"x\";\"x\";Reco subjet PT / Gen subjet PT", 100, -2, 2, 100, 0, 2);
   TProfile PSubleadingSubJetPTResponseVsLeadingX("PSubleadingSubJetPTResponseVsLeadingX",
      "Reco Subleading subjet PT response vs. \"x\";\"x\";Reco subjet PT / Gen subjet PT", 100, -2, 2);

   TH2D HSDMassOverGenSubJet1MassVsDR_PositiveXPositiveX("HSDMassOverGenSubJet1MassVsDR_PositiveXPositiveX",
      ";DR;Groomed reco jet mass / GenSubJet1Mass;", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDMassOverGenSubJet1MassVsDR_NegativeXPositiveX("HSDMassOverGenSubJet1MassVsDR_NegativeXPositiveX",
      ";DR;Groomed reco jet mass / GenSubJet1Mass;", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDMassOverGenSubJet1MassVsDR_PositiveXNegativeX("HSDMassOverGenSubJet1MassVsDR_PositiveXNegativeX",
      ";DR;Groomed reco jet mass / GenSubJet1Mass;", 100, 0, 0.5, 100, 0, 2);
   
   TH2D HSDMassRatioVsDR_PositiveXPositiveX("HSDMassRatioVsDR_PositiveXPositiveX",
      ";DR;Groomed reco jet mass / Gen;", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDMassRatioVsDR_NegativeXPositiveX("HSDMassRatioVsDR_NegativeXPositiveX",
      ";DR;Groomed reco jet mass / Gen;", 100, 0, 0.5, 100, 0, 2);
   TH2D HSDMassRatioVsDR_PositiveXNegativeX("HSDMassRatioVsDR_PositiveXNegativeX",
      ";DR;Groomed reco jet mass / Gen;", 100, 0, 0.5, 100, 0, 2);

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      MHiEvent.GetEntry(iEntry);
      MJet.GetEntry(iEntry);
      MSDJet.GetEntry(iEntry);

      double Centrality = GetCentrality(MHiEvent.hiBin);

      for(int i = 0; i < MSDJet.JetCount; i++)
      {
         if(MSDJet.RefPT[i] < 80 || MSDJet.RefPT[i] > 500)
            continue;
         if(MSDJet.RefEta[i] < -1.3 || MSDJet.RefEta[i] > 1.3)
            continue;

         if((*MSDJet.JetSubJetPT)[i].size() < 2)   // we want two subjets
            continue;
         if((*MSDJet.RefGSubJetPT)[i].size() < 2)   // we want two subjets also for gen jet for this study
            continue;

         double SubJetDR = CalculateDR((*MSDJet.RefGSubJetEta)[i][0], (*MSDJet.RefGSubJetPhi)[i][0],
            (*MSDJet.RefGSubJetEta)[i][1], (*MSDJet.RefGSubJetPhi)[i][1]);
         double RecoSubJetDR = CalculateDR((*MSDJet.JetSubJetEta)[i][0], (*MSDJet.JetSubJetPhi)[i][0],
            (*MSDJet.JetSubJetEta)[i][1], (*MSDJet.JetSubJetPhi)[i][1]);

         double DR00 = CalculateDR((*MSDJet.JetSubJetEta)[i][0], (*MSDJet.JetSubJetPhi)[i][0],
            (*MSDJet.RefGSubJetEta)[i][0], (*MSDJet.RefGSubJetPhi)[i][0]);
         double DR01 = CalculateDR((*MSDJet.JetSubJetEta)[i][0], (*MSDJet.JetSubJetPhi)[i][0],
            (*MSDJet.RefGSubJetEta)[i][1], (*MSDJet.RefGSubJetPhi)[i][1]);
         double DR10 = CalculateDR((*MSDJet.JetSubJetEta)[i][1], (*MSDJet.JetSubJetPhi)[i][1],
            (*MSDJet.RefGSubJetEta)[i][0], (*MSDJet.RefGSubJetPhi)[i][0]);
         double DR11 = CalculateDR((*MSDJet.JetSubJetEta)[i][1], (*MSDJet.JetSubJetPhi)[i][1],
            (*MSDJet.RefGSubJetEta)[i][1], (*MSDJet.RefGSubJetPhi)[i][1]);
         
         double DRSum = min(DR00 + DR11, DR10 + DR01);
         double DRMax = -1;
         if(DR00 + DR11 < DR10 + DR01)
            DRMax = max(DR00, DR11);
         else
            DRMax = max(DR10, DR01);

         double GenPT = MSDJet.RefPT[i];
         
         double GenSDMass = MSDJet.RefGM[i];
         double GenSDPT = MSDJet.RefGPT[i];

         double RecoSDMass = MSDJet.JetM[i];

         double SDMassRatio = RecoSDMass / GenSDMass;

         FourVector GenSubJet1, GenSubJet2;
         GenSubJet1.SetPtEtaPhiMass((*MSDJet.RefGSubJetPT)[i][0], (*MSDJet.RefGSubJetEta)[i][0],
            (*MSDJet.RefGSubJetPhi)[i][0], (*MSDJet.RefGSubJetM)[i][0]);
         GenSubJet2.SetPtEtaPhiMass((*MSDJet.RefGSubJetPT)[i][1], (*MSDJet.RefGSubJetEta)[i][1],
            (*MSDJet.RefGSubJetPhi)[i][1], (*MSDJet.RefGSubJetM)[i][1]);

         if(GenSubJet1.GetPT() < GenSubJet2.GetPT())
            swap(GenSubJet1, GenSubJet2);

         FourVector RecoSubJet1, RecoSubJet2;
         RecoSubJet1.SetPtEtaPhiMass((*MSDJet.JetSubJetPT)[i][0], (*MSDJet.JetSubJetEta)[i][0],
            (*MSDJet.JetSubJetPhi)[i][0], (*MSDJet.JetSubJetM)[i][0]);
         RecoSubJet2.SetPtEtaPhiMass((*MSDJet.JetSubJetPT)[i][1], (*MSDJet.JetSubJetEta)[i][1],
            (*MSDJet.JetSubJetPhi)[i][1], (*MSDJet.JetSubJetM)[i][1]);

         if(RecoSubJet1.GetPT() < RecoSubJet2.GetPT())
            swap(RecoSubJet1, RecoSubJet2);

         // Subjet location plot
         double DeltaEta = GenSubJet1.GetEta() - GenSubJet2.GetEta();
         double MeanEta = (GenSubJet1.GetEta() + GenSubJet2.GetEta()) / 2;
         double DeltaPhi = (GenSubJet1.GetPhi() - GenSubJet2.GetPhi());
         if(DeltaPhi < -PI)   DeltaPhi = DeltaPhi + 2 * PI;
         if(DeltaPhi > +PI)   DeltaPhi = DeltaPhi - 2 * PI;
         double MeanPhi = GenSubJet2.GetPhi() + DeltaPhi / 2;
         if(MeanPhi < -PI)   MeanPhi = MeanPhi + 2 * PI;
         if(MeanPhi > +PI)   MeanPhi = MeanPhi - 2 * PI;

         double M11 = DeltaEta / 2;
         double M12 = DeltaPhi / 2;
         double M21 = -DeltaPhi / 2;
         double M22 = DeltaEta / 2;

         double DetM = M11 * M22 - M12 * M21;

         double IM11 = M22 / DetM;
         double IM12 = -M21 / DetM;
         double IM21 = -M12 / DetM;
         double IM22 = M11 / DetM;

         double GenSubJetEta1 = GenSubJet1.GetEta() - MeanEta;
         double GenSubJetPhi1 = GenSubJet1.GetPhi() - MeanPhi;
         double GenSubJetEta2 = GenSubJet2.GetEta() - MeanEta;
         double GenSubJetPhi2 = GenSubJet2.GetPhi() - MeanPhi;
         double SubJetEta1 = RecoSubJet1.GetEta() - MeanEta;
         double SubJetPhi1 = RecoSubJet1.GetPhi() - MeanPhi;
         double SubJetEta2 = RecoSubJet2.GetEta() - MeanEta;
         double SubJetPhi2 = RecoSubJet2.GetPhi() - MeanPhi;
         if(GenSubJetPhi1 > +PI)   GenSubJetPhi1 = GenSubJetPhi1 - 2 * PI;
         if(GenSubJetPhi1 < -PI)   GenSubJetPhi1 = GenSubJetPhi1 + 2 * PI;
         if(GenSubJetPhi2 > +PI)   GenSubJetPhi2 = GenSubJetPhi2 - 2 * PI;
         if(GenSubJetPhi2 < -PI)   GenSubJetPhi2 = GenSubJetPhi2 + 2 * PI;
         if(SubJetPhi1 > +PI)   SubJetPhi1 = SubJetPhi1 - 2 * PI;
         if(SubJetPhi1 < -PI)   SubJetPhi1 = SubJetPhi1 + 2 * PI;
         if(SubJetPhi2 > +PI)   SubJetPhi2 = SubJetPhi2 - 2 * PI;
         if(SubJetPhi2 < -PI)   SubJetPhi2 = SubJetPhi2 + 2 * PI;

         double GenSubJetX1 = IM11 * GenSubJetEta1 + IM12 * GenSubJetPhi1;
         double GenSubJetY1 = IM21 * GenSubJetEta1 + IM22 * GenSubJetPhi1;
         double GenSubJetX2 = IM11 * GenSubJetEta2 + IM12 * GenSubJetPhi2;
         double GenSubJetY2 = IM21 * GenSubJetEta2 + IM22 * GenSubJetPhi2;
         double SubJetX1 = IM11 * SubJetEta1 + IM12 * SubJetPhi1;
         double SubJetY1 = IM21 * SubJetEta1 + IM22 * SubJetPhi1;
         double SubJetX2 = IM11 * SubJetEta2 + IM12 * SubJetPhi2;
         double SubJetY2 = IM21 * SubJetEta2 + IM22 * SubJetPhi2;
   
         HGenSubJetPositionSpread.Fill(GenSubJetX1, GenSubJetY1);
         HGenSubJetPositionSpread.Fill(GenSubJetX2, GenSubJetY2);
         HLeadingSubJetPositionSpread.Fill(SubJetX1, SubJetY1);
         HSubleadingSubJetPositionSpread.Fill(SubJetX2, SubJetY2);
         if(SubJetDR < 0.1)
         {
            HLeadingSubJetPositionSpread_DR01.Fill(SubJetX1, SubJetY1);
            HSubleadingSubJetPositionSpread_DR01.Fill(SubJetX2, SubJetY2);
         }
         else if(SubJetDR < 0.2)
         {
            HLeadingSubJetPositionSpread_DR02.Fill(SubJetX1, SubJetY1);
            HSubleadingSubJetPositionSpread_DR02.Fill(SubJetX2, SubJetY2);
         }
         else if(SubJetDR < 0.3)
         {
            HLeadingSubJetPositionSpread_DR03.Fill(SubJetX1, SubJetY1);
            HSubleadingSubJetPositionSpread_DR03.Fill(SubJetX2, SubJetY2);
         }
         else if(SubJetDR < 0.4)
         {
            HLeadingSubJetPositionSpread_DR04.Fill(SubJetX1, SubJetY1);
            HSubleadingSubJetPositionSpread_DR04.Fill(SubJetX2, SubJetY2);
         }

         HLeadingSubJetXVsSubleadingSubJetX.Fill(SubJetX1, SubJetX2);
         if(SubJetDR < 0.1)
            HLeadingSubJetXVsSubleadingSubJetX_DR01.Fill(SubJetX1, SubJetX2);
         else if(SubJetDR < 0.2)
            HLeadingSubJetXVsSubleadingSubJetX_DR02.Fill(SubJetX1, SubJetX2);
         else if(SubJetDR < 0.3)
            HLeadingSubJetXVsSubleadingSubJetX_DR03.Fill(SubJetX1, SubJetX2);
         else if(SubJetDR < 0.4)
            HLeadingSubJetXVsSubleadingSubJetX_DR04.Fill(SubJetX1, SubJetX2);

         HLeadingSubJetPTResponseVsLeadingX.Fill(SubJetX1, RecoSubJet1.GetPT() / GenSubJet1.GetPT());
         PLeadingSubJetPTResponseVsLeadingX.Fill(SubJetX1, RecoSubJet1.GetPT() / GenSubJet1.GetPT());
         HSubleadingSubJetPTResponseVsLeadingX.Fill(SubJetX1, RecoSubJet2.GetPT() / GenSubJet2.GetPT());
         PSubleadingSubJetPTResponseVsLeadingX.Fill(SubJetX1, RecoSubJet2.GetPT() / GenSubJet2.GetPT());
   
         if(SubJetX1 > 0 && SubJetX2 > 0)
         {
            HSDMassOverGenSubJet1MassVsDR_PositiveXPositiveX.Fill(SubJetDR, RecoSDMass / GenSubJet1.GetMass());
            HSDMassRatioVsDR_PositiveXPositiveX.Fill(SubJetDR, SDMassRatio);
         }
         if(SubJetX1 < 0 && SubJetX2 > 0)
         {
            HSDMassOverGenSubJet1MassVsDR_NegativeXPositiveX.Fill(SubJetDR, RecoSDMass / GenSubJet1.GetMass());
            HSDMassRatioVsDR_NegativeXPositiveX.Fill(SubJetDR, SDMassRatio);
         }
         if(SubJetX1 > 0 && SubJetX2 < 0)
         {
            HSDMassOverGenSubJet1MassVsDR_PositiveXNegativeX.Fill(SubJetDR, RecoSDMass / GenSubJet1.GetMass());
            HSDMassRatioVsDR_PositiveXNegativeX.Fill(SubJetDR, SDMassRatio);
         }

         if(DRMax > 0.1)   // we concern ourselves with the well-matched jets in this study
            continue;
         if(GenSDMass < 0.01)   // Let's not look at mini mass jets for now
            continue;

         // Mass response vs. gen jet PT
         HSDMassRatioVsJetPT.Fill(GenPT, SDMassRatio);
         PSDMassRatioVsJetPT.Fill(GenPT, SDMassRatio);
         if(SubJetDR < 0.1)
         {
            HSDMassRatioVsJetPT_DR01.Fill(GenPT, SDMassRatio);
            PSDMassRatioVsJetPT_DR01.Fill(GenPT, SDMassRatio);
         }
         else if(SubJetDR < 0.2)
         {
            HSDMassRatioVsJetPT_DR02.Fill(GenPT, SDMassRatio);
            PSDMassRatioVsJetPT_DR02.Fill(GenPT, SDMassRatio);
         }
         else if(SubJetDR < 0.3)
         {
            HSDMassRatioVsJetPT_DR03.Fill(GenPT, SDMassRatio);
            PSDMassRatioVsJetPT_DR03.Fill(GenPT, SDMassRatio);
         }
         else if(SubJetDR < 0.4)
         {
            HSDMassRatioVsJetPT_DR04.Fill(GenPT, SDMassRatio);
            PSDMassRatioVsJetPT_DR04.Fill(GenPT, SDMassRatio);
         }

         // Toys smearing subjet angular resolution
         double SmearSigma[4] = {0, 0.02, 0.05, 0.1};
         int Tries = 10;
         for(int j = 0; j < 4; j++)
         {
            for(int k = 0; k < Tries; k++)
            {
               FourVector SmearedGenSubJet1 = GenSubJet1, SmearedGenSubJet2 = GenSubJet2;
               if(j > 0)
               {
                  SmearedGenSubJet1.SetPtEtaPhiMass(GenSubJet1.GetPT(),
                     GenSubJet1.GetEta() + DrawRandom(0, SmearSigma[j]),
                     GenSubJet1.GetPhi() + DrawRandom(0, SmearSigma[j]),
                     GenSubJet1.GetMass());
                  SmearedGenSubJet2.SetPtEtaPhiMass(GenSubJet2.GetPT(),
                     GenSubJet2.GetEta() + DrawRandom(0, SmearSigma[j]),
                     GenSubJet2.GetPhi() + DrawRandom(0, SmearSigma[j]),
                     GenSubJet2.GetMass());
               }

               double SmearedMass = (SmearedGenSubJet1 + SmearedGenSubJet2).GetMass();

               if(j == 0)
                  HToyMassResponseVsSubJetDR_Smear0.Fill(SubJetDR, SmearedMass / GenSDMass);
               if(j == 1)
                  HToyMassResponseVsSubJetDR_Smear1.Fill(SubJetDR, SmearedMass / GenSDMass);
               if(j == 2)
                  HToyMassResponseVsSubJetDR_Smear2.Fill(SubJetDR, SmearedMass / GenSDMass);
               if(j == 3)
                  HToyMassResponseVsSubJetDR_Smear3.Fill(SubJetDR, SmearedMass / GenSDMass);
            }
         }
      
         // Toy smearing PT by constant percentage
         double PTSmearSigma[4] = {0, 0.05, 0.10, 0.20};
         Tries = 10;
         for(int j = 0; j < 4; j++)
         {
            for(int k = 0; k < Tries; k++)
            {
               FourVector SmearedGenSubJet1 = GenSubJet1 * DrawGaussian(1, PTSmearSigma[j]);
               FourVector SmearedGenSubJet2 = GenSubJet2 * DrawGaussian(1, PTSmearSigma[j]);

               double SmearedMass = (SmearedGenSubJet1 + SmearedGenSubJet2).GetMass();

               if(j == 0)
               {
                  HToyMassResponseVsSubJetDR_PTSmear0.Fill(SubJetDR, SmearedMass / GenSDMass);
                  PToyMassResponseVsSubJetDR_PTSmear0.Fill(SubJetDR, SmearedMass / GenSDMass);
               }
               if(j == 1)
               {
                  HToyMassResponseVsSubJetDR_PTSmear1.Fill(SubJetDR, SmearedMass / GenSDMass);
                  PToyMassResponseVsSubJetDR_PTSmear1.Fill(SubJetDR, SmearedMass / GenSDMass);
               }
               if(j == 2)
               {
                  HToyMassResponseVsSubJetDR_PTSmear2.Fill(SubJetDR, SmearedMass / GenSDMass);
                  PToyMassResponseVsSubJetDR_PTSmear2.Fill(SubJetDR, SmearedMass / GenSDMass);
               }
               if(j == 3)
               {
                  HToyMassResponseVsSubJetDR_PTSmear3.Fill(SubJetDR, SmearedMass / GenSDMass);
                  PToyMassResponseVsSubJetDR_PTSmear3.Fill(SubJetDR, SmearedMass / GenSDMass);
               }
            }
         }
      }
   }

   HSDMassRatioVsJetPT.Write();
   HSDMassRatioVsJetPT_DR01.Write();
   HSDMassRatioVsJetPT_DR02.Write();
   HSDMassRatioVsJetPT_DR03.Write();
   HSDMassRatioVsJetPT_DR04.Write();

   PSDMassRatioVsJetPT.Write();
   PSDMassRatioVsJetPT_DR01.Write();
   PSDMassRatioVsJetPT_DR02.Write();
   PSDMassRatioVsJetPT_DR03.Write();
   PSDMassRatioVsJetPT_DR04.Write();

   HToyMassResponseVsSubJetDR_Smear0.Write();
   HToyMassResponseVsSubJetDR_Smear1.Write();
   HToyMassResponseVsSubJetDR_Smear2.Write();
   HToyMassResponseVsSubJetDR_Smear3.Write();

   HToyMassResponseVsSubJetDR_PTSmear0.Write();
   HToyMassResponseVsSubJetDR_PTSmear1.Write();
   HToyMassResponseVsSubJetDR_PTSmear2.Write();
   HToyMassResponseVsSubJetDR_PTSmear3.Write();
   PToyMassResponseVsSubJetDR_PTSmear0.Write();
   PToyMassResponseVsSubJetDR_PTSmear1.Write();
   PToyMassResponseVsSubJetDR_PTSmear2.Write();
   PToyMassResponseVsSubJetDR_PTSmear3.Write();

   HGenSubJetPositionSpread.Write();
   HLeadingSubJetPositionSpread.Write();
   HLeadingSubJetPositionSpread_DR01.Write();
   HLeadingSubJetPositionSpread_DR02.Write();
   HLeadingSubJetPositionSpread_DR03.Write();
   HLeadingSubJetPositionSpread_DR04.Write();
   HSubleadingSubJetPositionSpread.Write();
   HSubleadingSubJetPositionSpread_DR01.Write();
   HSubleadingSubJetPositionSpread_DR02.Write();
   HSubleadingSubJetPositionSpread_DR03.Write();
   HSubleadingSubJetPositionSpread_DR04.Write();
         
   HLeadingSubJetXVsSubleadingSubJetX.Write();
   HLeadingSubJetXVsSubleadingSubJetX_DR01.Write();
   HLeadingSubJetXVsSubleadingSubJetX_DR02.Write();
   HLeadingSubJetXVsSubleadingSubJetX_DR03.Write();
   HLeadingSubJetXVsSubleadingSubJetX_DR04.Write();
   
   HLeadingSubJetPTResponseVsLeadingX.Write();
   PLeadingSubJetPTResponseVsLeadingX.Write();
   HSubleadingSubJetPTResponseVsLeadingX.Write();
   PSubleadingSubJetPTResponseVsLeadingX.Write();

   HSDMassOverGenSubJet1MassVsDR_PositiveXPositiveX.Write();
   HSDMassOverGenSubJet1MassVsDR_NegativeXPositiveX.Write();
   HSDMassOverGenSubJet1MassVsDR_PositiveXNegativeX.Write();
   HSDMassRatioVsDR_PositiveXPositiveX.Write();
   HSDMassRatioVsDR_NegativeXPositiveX.Write();
   HSDMassRatioVsDR_PositiveXNegativeX.Write();
   
   OutputFile.Close();

   InputFile.Close();
}

double CalculateDR(double eta1, double phi1, double eta2, double phi2)
{
   double DEta = eta1 - eta2;
   double DPhi = phi1 - phi2;
   if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
   if(DPhi > +PI)   DPhi = DPhi - 2 * PI;
   return sqrt(DEta * DEta + DPhi * DPhi);
}





