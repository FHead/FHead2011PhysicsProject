#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "TF1.h"

#include "ProgressBar.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "CommandLine.h"

#include "Messenger.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileName  = CL.GetStringVector("Input", "");
   string OutputBase             = CL.Get("OutputBase", "Result");
   string JetTreeName            = CL.Get("Tree", "akCs4PFJetAnalyzer/t");
   bool CheckFraction            = CL.GetBool("CheckFraction", true);
   bool ReducedEta               = CL.GetBool("ReducedEta", false);

   double MaxEta = 2.5;
   if(ReducedEta == true)
      MaxEta = 2.2;

   string Function = "(ROOT::Math::normal_cdf([0]*(x-[1]), [0]*[2], 0) - exp(-[0]*(x-[1])+[0]*[0]*[2]*[2]/2)*ROOT::Math::normal_cdf([0]*(x-[1]), [0]*[2], [0]*[0]*[2]*[2])) * ([3] - [4]) + [4]";

   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage("Jet quick look");

   TFile OutputFile((OutputBase + ".root").c_str(), "RECREATE");

   TH1D HN("HN", "", 1, 0, 1);
   TH2D HEtaPhiPT30("HEtaPhiPT30", "PT > 30;eta;phi", 75, -MaxEta, MaxEta, 75, -3.14159, 3.14159);
   TH2D HEtaPhiPT50("HEtaPhiPT50", "PT > 50;eta;phi", 75, -MaxEta, MaxEta, 75, -3.14159, 3.14159);
   TH2D HEtaPhiPT70("HEtaPhiPT70", "PT > 70;eta;phi", 75, -MaxEta, MaxEta, 75, -3.14159, 3.14159);

   TH1D HJetPT("HJetPT", "Leading jet in full range;p_{T};", 100, 0, 200);
   TH1D HJetPT_EtaN15P15("HJetPT_EtaN15P15", "Leading jet in |eta| < 1.5;p_{T};", 100, 0, 200);
   TH1D HJetPT_EtaN25P25("HJetPT_EtaN25P25", "Leading jet in |eta| < 2.5;p_{T};", 100, 0, 200);
   TH1D HJetPT_EtaN00P25("HJetPT_EtaN00P25", "Leading jet in 0 < eta < 2.5;p_{T};", 100, 0, 200);
   TH1D HJetPT_EtaN25P00("HJetPT_EtaN25P00", "Leading jet in -2.5 < eta < 0;p_{T};", 100, 0, 200);
   TH1D HJetPT_EtaP15P25("HJetPT_EtaP15P25", "Leading jet in 1.5 < eta < 2.5;p_{T};", 100, 0, 200);
   TH1D HJetPT_EtaN25N15("HJetPT_EtaN25N15", "Leading jet in -2.5 < eta < -1.5;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156("HJetPTPassL156", "Leading jet in full range;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156_EtaN15P15("HJetPTPassL156_EtaN15P15", "Leading jet in |eta| < 1.5;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156_EtaN25P25("HJetPTPassL156_EtaN25P25", "Leading jet in |eta| < 2.5;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156_EtaN00P25("HJetPTPassL156_EtaN00P25", "Leading jet in 0 < eta < 2.5;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156_EtaN25P00("HJetPTPassL156_EtaN25P00", "Leading jet in -2.5 < eta < 0;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156_EtaP15P25("HJetPTPassL156_EtaP15P25", "Leading jet in 1.5 < eta < 2.5;p_{T};", 100, 0, 200);
   TH1D HJetPTPassL156_EtaN25N15("HJetPTPassL156_EtaN25N15", "Leading jet in -2.5 < eta < -1.5;p_{T};", 100, 0, 200);

   TH2D HJetPTVsRawPT("HJetPTVsRawPT", "|#eta| < 2.5;Jet PT;Raw PT", 100, 0, 200, 100, 0, 200);
   TH2D HRawPTVsJEC("HRawPTVsJEC", "|#eta| < 2.5;Raw PT;JEC", 100, 0, 200, 100, 0, 2);

   TH1D HAllJetPT_EtaN25N15("HAllJetPT_EtaN25N15", "Jet PT, -2.5 < #eta < -1.5;p_{T}", 100, 0, 200);
   TH1D HAllJetPT_EtaN15P15("HAllJetPT_EtaN15P15", "Jet PT, -1.5 < #eta < 1.5;p_{T}", 100, 0, 200);
   TH1D HAllJetPT_EtaP15P25("HAllJetPT_EtaP15P25", "Jet PT, 1.5 < #eta < 2.5;p_{T}", 100, 0, 200);

   TH1D HJetCHF_PT50_EtaN25N15("HJetCHF_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;CHF;", 100, 0, 1);
   TH1D HJetCHF_PT50_EtaN15P15("HJetCHF_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;CHF;", 100, 0, 1);
   TH1D HJetCHF_PT50_EtaP15P25("HJetCHF_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;CHF;", 100, 0, 1);
   TH1D HJetCEF_PT50_EtaN25N15("HJetCEF_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;CEF;", 100, 0, 1);
   TH1D HJetCEF_PT50_EtaN15P15("HJetCEF_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;CEF;", 100, 0, 1);
   TH1D HJetCEF_PT50_EtaP15P25("HJetCEF_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;CEF;", 100, 0, 1);
   TH1D HJetNHF_PT50_EtaN25N15("HJetNHF_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;NHF;", 100, 0, 1);
   TH1D HJetNHF_PT50_EtaN15P15("HJetNHF_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;NHF;", 100, 0, 1);
   TH1D HJetNHF_PT50_EtaP15P25("HJetNHF_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;NHF;", 100, 0, 1);
   TH1D HJetNEF_PT50_EtaN25N15("HJetNEF_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;NEF;", 100, 0, 1);
   TH1D HJetNEF_PT50_EtaN15P15("HJetNEF_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;NEF;", 100, 0, 1);
   TH1D HJetNEF_PT50_EtaP15P25("HJetNEF_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;NEF;", 100, 0, 1);
   TH1D HJetMUF_PT50_EtaN25N15("HJetMUF_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;MUF;", 100, 0, 1);
   TH1D HJetMUF_PT50_EtaN15P15("HJetMUF_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;MUF;", 100, 0, 1);
   TH1D HJetMUF_PT50_EtaP15P25("HJetMUF_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;MUF;", 100, 0, 1);
   TH1D HJetCH_PT50_EtaN25N15("HJetCH_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;CH;", 100, 0, 200);
   TH1D HJetCH_PT50_EtaN15P15("HJetCH_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;CH;", 100, 0, 200);
   TH1D HJetCH_PT50_EtaP15P25("HJetCH_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;CH;", 100, 0, 200);
   TH1D HJetCE_PT50_EtaN25N15("HJetCE_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;CE;", 100, 0, 200);
   TH1D HJetCE_PT50_EtaN15P15("HJetCE_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;CE;", 100, 0, 200);
   TH1D HJetCE_PT50_EtaP15P25("HJetCE_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;CE;", 100, 0, 200);
   TH1D HJetNH_PT50_EtaN25N15("HJetNH_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;NH;", 100, 0, 200);
   TH1D HJetNH_PT50_EtaN15P15("HJetNH_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;NH;", 100, 0, 200);
   TH1D HJetNH_PT50_EtaP15P25("HJetNH_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;NH;", 100, 0, 200);
   TH1D HJetNE_PT50_EtaN25N15("HJetNE_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;NE;", 100, 0, 200);
   TH1D HJetNE_PT50_EtaN15P15("HJetNE_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;NE;", 100, 0, 200);
   TH1D HJetNE_PT50_EtaP15P25("HJetNE_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;NE;", 100, 0, 200);
   TH1D HJetMU_PT50_EtaN25N15("HJetMU_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;MU;", 100, 0, 200);
   TH1D HJetMU_PT50_EtaN15P15("HJetMU_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;MU;", 100, 0, 200);
   TH1D HJetMU_PT50_EtaP15P25("HJetMU_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;MU;", 100, 0, 200);
   TH1D HJetHad_PT50_EtaN25N15("HJetHad_PT50_EtaN25N15", "PT > 50, -2.5 < #eta < -1.5;Had;", 100, 0, 200);
   TH1D HJetHad_PT50_EtaN15P15("HJetHad_PT50_EtaN15P15", "PT > 50, -1.5 < #eta < 1.5;Had;", 100, 0, 200);
   TH1D HJetHad_PT50_EtaP15P25("HJetHad_PT50_EtaP15P25", "PT > 50, 1.5 < #eta < 2.5;Had;", 100, 0, 200);
   
   TH1D HJetCHF_PT70_EtaN25N15("HJetCHF_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;CHF;", 100, 0, 1);
   TH1D HJetCHF_PT70_EtaN15P15("HJetCHF_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;CHF;", 100, 0, 1);
   TH1D HJetCHF_PT70_EtaP15P25("HJetCHF_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;CHF;", 100, 0, 1);
   TH1D HJetCEF_PT70_EtaN25N15("HJetCEF_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;CEF;", 100, 0, 1);
   TH1D HJetCEF_PT70_EtaN15P15("HJetCEF_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;CEF;", 100, 0, 1);
   TH1D HJetCEF_PT70_EtaP15P25("HJetCEF_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;CEF;", 100, 0, 1);
   TH1D HJetNHF_PT70_EtaN25N15("HJetNHF_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;NHF;", 100, 0, 1);
   TH1D HJetNHF_PT70_EtaN15P15("HJetNHF_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;NHF;", 100, 0, 1);
   TH1D HJetNHF_PT70_EtaP15P25("HJetNHF_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;NHF;", 100, 0, 1);
   TH1D HJetNEF_PT70_EtaN25N15("HJetNEF_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;NEF;", 100, 0, 1);
   TH1D HJetNEF_PT70_EtaN15P15("HJetNEF_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;NEF;", 100, 0, 1);
   TH1D HJetNEF_PT70_EtaP15P25("HJetNEF_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;NEF;", 100, 0, 1);
   TH1D HJetMUF_PT70_EtaN25N15("HJetMUF_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;MUF;", 100, 0, 1);
   TH1D HJetMUF_PT70_EtaN15P15("HJetMUF_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;MUF;", 100, 0, 1);
   TH1D HJetMUF_PT70_EtaP15P25("HJetMUF_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;MUF;", 100, 0, 1);
   TH1D HJetCH_PT70_EtaN25N15("HJetCH_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;CH;", 100, 0, 200);
   TH1D HJetCH_PT70_EtaN15P15("HJetCH_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;CH;", 100, 0, 200);
   TH1D HJetCH_PT70_EtaP15P25("HJetCH_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;CH;", 100, 0, 200);
   TH1D HJetCE_PT70_EtaN25N15("HJetCE_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;CE;", 100, 0, 200);
   TH1D HJetCE_PT70_EtaN15P15("HJetCE_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;CE;", 100, 0, 200);
   TH1D HJetCE_PT70_EtaP15P25("HJetCE_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;CE;", 100, 0, 200);
   TH1D HJetNH_PT70_EtaN25N15("HJetNH_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;NH;", 100, 0, 200);
   TH1D HJetNH_PT70_EtaN15P15("HJetNH_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;NH;", 100, 0, 200);
   TH1D HJetNH_PT70_EtaP15P25("HJetNH_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;NH;", 100, 0, 200);
   TH1D HJetNE_PT70_EtaN25N15("HJetNE_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;NE;", 100, 0, 200);
   TH1D HJetNE_PT70_EtaN15P15("HJetNE_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;NE;", 100, 0, 200);
   TH1D HJetNE_PT70_EtaP15P25("HJetNE_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;NE;", 100, 0, 200);
   TH1D HJetMU_PT70_EtaN25N15("HJetMU_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;MU;", 100, 0, 200);
   TH1D HJetMU_PT70_EtaN15P15("HJetMU_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;MU;", 100, 0, 200);
   TH1D HJetMU_PT70_EtaP15P25("HJetMU_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;MU;", 100, 0, 200);
   TH1D HJetHad_PT70_EtaN25N15("HJetHad_PT70_EtaN25N15", "PT > 70, -2.5 < #eta < -1.5;Had;", 100, 0, 200);
   TH1D HJetHad_PT70_EtaN15P15("HJetHad_PT70_EtaN15P15", "PT > 70, -1.5 < #eta < 1.5;Had;", 100, 0, 200);
   TH1D HJetHad_PT70_EtaP15P25("HJetHad_PT70_EtaP15P25", "PT > 70, 1.5 < #eta < 2.5;Had;", 100, 0, 200);

   for(string FileName : InputFileName)
   {
      cout << "Processing file " << FileName << endl;

      TFile InputFile(FileName.c_str());

      HiEventTreeMessenger MHiEvent(InputFile);
      JetTreeMessenger MJet(InputFile, JetTreeName);
      TriggerTreeMessenger MHLT(InputFile);

      if(MHiEvent.Tree == nullptr)
      {
         InputFile.Close();
         continue;
      }

      int EntryCount = MHiEvent.Tree->GetEntries();
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         if(iE < 200 || (iE % (EntryCount / 300)) == 0)
         {
            Bar.Update(iE);
            Bar.Print();
         }

         MHiEvent.GetEntry(iE);
         MJet.GetEntry(iE);
         MHLT.GetEntry(iE);

         bool GoodLumi = false;
         if(MHiEvent.Run == 327400 && (MHiEvent.Lumi >= 38 && MHiEvent.Lumi <= 578))
            GoodLumi = true;
         if(MHiEvent.Run == 327402 && (MHiEvent.Lumi >= 1 && MHiEvent.Lumi <= 294))
            GoodLumi = true;
         if(MHiEvent.Run == 327430 && (MHiEvent.Lumi >= 1 && MHiEvent.Lumi <= 497))
            GoodLumi = true;
         if(MHiEvent.Run == 327430 && (MHiEvent.Lumi >= 499 && MHiEvent.Lumi <= 1092))
            GoodLumi = true;
         if(MHiEvent.Run == 327462 && (MHiEvent.Lumi >= 42 && MHiEvent.Lumi <= 320))
            GoodLumi = true;
         if(MHiEvent.Run == 327524)
            GoodLumi = true;
         if(GoodLumi == false)
            continue;

         HN.Fill(0);

         int BestJetIndex = -1;

         for(int iJ = 0; iJ < MJet.JetCount; iJ++)
         {
            if(MJet.JetPT[iJ] > 50)
            {
               if(MJet.JetEta[iJ] > -MaxEta && MJet.JetEta[iJ] < -1.5)
               {
                  HJetCHF_PT50_EtaN25N15.Fill(MJet.JetPFCHF[iJ]);
                  HJetCEF_PT50_EtaN25N15.Fill(MJet.JetPFCEF[iJ]);
                  HJetNHF_PT50_EtaN25N15.Fill(MJet.JetPFNHF[iJ]);
                  HJetNEF_PT50_EtaN25N15.Fill(MJet.JetPFNEF[iJ]);
                  HJetMUF_PT50_EtaN25N15.Fill(MJet.JetPFMUF[iJ]);
                  HJetCH_PT50_EtaN25N15.Fill(MJet.JetPFCHF[iJ] * MJet.JetPT[iJ]);
                  HJetCE_PT50_EtaN25N15.Fill(MJet.JetPFCEF[iJ] * MJet.JetPT[iJ]);
                  HJetNH_PT50_EtaN25N15.Fill(MJet.JetPFNHF[iJ] * MJet.JetPT[iJ]);
                  HJetNE_PT50_EtaN25N15.Fill(MJet.JetPFNEF[iJ] * MJet.JetPT[iJ]);
                  HJetMU_PT50_EtaN25N15.Fill(MJet.JetPFMUF[iJ] * MJet.JetPT[iJ]);
                  HJetHad_PT50_EtaN25N15.Fill((MJet.JetPFCHF[iJ] + MJet.JetPFNHF[iJ]) * MJet.JetPT[iJ]);
               }
               if(MJet.JetEta[iJ] > -1.5 && MJet.JetEta[iJ] < 1.5)
               {
                  HJetCHF_PT50_EtaN15P15.Fill(MJet.JetPFCHF[iJ]);
                  HJetCEF_PT50_EtaN15P15.Fill(MJet.JetPFCEF[iJ]);
                  HJetNHF_PT50_EtaN15P15.Fill(MJet.JetPFNHF[iJ]);
                  HJetNEF_PT50_EtaN15P15.Fill(MJet.JetPFNEF[iJ]);
                  HJetMUF_PT50_EtaN15P15.Fill(MJet.JetPFMUF[iJ]);
                  HJetCH_PT50_EtaN15P15.Fill(MJet.JetPFCHF[iJ] * MJet.JetPT[iJ]);
                  HJetCE_PT50_EtaN15P15.Fill(MJet.JetPFCEF[iJ] * MJet.JetPT[iJ]);
                  HJetNH_PT50_EtaN15P15.Fill(MJet.JetPFNHF[iJ] * MJet.JetPT[iJ]);
                  HJetNE_PT50_EtaN15P15.Fill(MJet.JetPFNEF[iJ] * MJet.JetPT[iJ]);
                  HJetMU_PT50_EtaN15P15.Fill(MJet.JetPFMUF[iJ] * MJet.JetPT[iJ]);
                  HJetHad_PT50_EtaN15P15.Fill((MJet.JetPFCHF[iJ] + MJet.JetPFNHF[iJ]) * MJet.JetPT[iJ]);
               }
               if(MJet.JetEta[iJ] > 1.5 && MJet.JetEta[iJ] < MaxEta)
               {
                  HJetCHF_PT50_EtaP15P25.Fill(MJet.JetPFCHF[iJ]);
                  HJetCEF_PT50_EtaP15P25.Fill(MJet.JetPFCEF[iJ]);
                  HJetNHF_PT50_EtaP15P25.Fill(MJet.JetPFNHF[iJ]);
                  HJetNEF_PT50_EtaP15P25.Fill(MJet.JetPFNEF[iJ]);
                  HJetMUF_PT50_EtaP15P25.Fill(MJet.JetPFMUF[iJ]);
                  HJetCH_PT50_EtaP15P25.Fill(MJet.JetPFCHF[iJ] * MJet.JetPT[iJ]);
                  HJetCE_PT50_EtaP15P25.Fill(MJet.JetPFCEF[iJ] * MJet.JetPT[iJ]);
                  HJetNH_PT50_EtaP15P25.Fill(MJet.JetPFNHF[iJ] * MJet.JetPT[iJ]);
                  HJetNE_PT50_EtaP15P25.Fill(MJet.JetPFNEF[iJ] * MJet.JetPT[iJ]);
                  HJetMU_PT50_EtaP15P25.Fill(MJet.JetPFMUF[iJ] * MJet.JetPT[iJ]);
                  HJetHad_PT50_EtaP15P25.Fill((MJet.JetPFCHF[iJ] + MJet.JetPFNHF[iJ]) * MJet.JetPT[iJ]);
               }
            }
            if(MJet.JetPT[iJ] > 70)
            {
               if(MJet.JetEta[iJ] > -MaxEta && MJet.JetEta[iJ] < -1.5)
               {
                  HJetCHF_PT70_EtaN25N15.Fill(MJet.JetPFCHF[iJ]);
                  HJetCEF_PT70_EtaN25N15.Fill(MJet.JetPFCEF[iJ]);
                  HJetNHF_PT70_EtaN25N15.Fill(MJet.JetPFNHF[iJ]);
                  HJetNEF_PT70_EtaN25N15.Fill(MJet.JetPFNEF[iJ]);
                  HJetMUF_PT70_EtaN25N15.Fill(MJet.JetPFMUF[iJ]);
                  HJetCH_PT70_EtaN25N15.Fill(MJet.JetPFCHF[iJ] * MJet.JetPT[iJ]);
                  HJetCE_PT70_EtaN25N15.Fill(MJet.JetPFCEF[iJ] * MJet.JetPT[iJ]);
                  HJetNH_PT70_EtaN25N15.Fill(MJet.JetPFNHF[iJ] * MJet.JetPT[iJ]);
                  HJetNE_PT70_EtaN25N15.Fill(MJet.JetPFNEF[iJ] * MJet.JetPT[iJ]);
                  HJetMU_PT70_EtaN25N15.Fill(MJet.JetPFMUF[iJ] * MJet.JetPT[iJ]);
                  HJetHad_PT70_EtaN25N15.Fill((MJet.JetPFCHF[iJ] + MJet.JetPFNHF[iJ]) * MJet.JetPT[iJ]);
               }
               if(MJet.JetEta[iJ] > -1.5 && MJet.JetEta[iJ] < 1.5)
               {
                  HJetCHF_PT70_EtaN15P15.Fill(MJet.JetPFCHF[iJ]);
                  HJetCEF_PT70_EtaN15P15.Fill(MJet.JetPFCEF[iJ]);
                  HJetNHF_PT70_EtaN15P15.Fill(MJet.JetPFNHF[iJ]);
                  HJetNEF_PT70_EtaN15P15.Fill(MJet.JetPFNEF[iJ]);
                  HJetMUF_PT70_EtaN15P15.Fill(MJet.JetPFMUF[iJ]);
                  HJetCH_PT70_EtaN15P15.Fill(MJet.JetPFCHF[iJ] * MJet.JetPT[iJ]);
                  HJetCE_PT70_EtaN15P15.Fill(MJet.JetPFCEF[iJ] * MJet.JetPT[iJ]);
                  HJetNH_PT70_EtaN15P15.Fill(MJet.JetPFNHF[iJ] * MJet.JetPT[iJ]);
                  HJetNE_PT70_EtaN15P15.Fill(MJet.JetPFNEF[iJ] * MJet.JetPT[iJ]);
                  HJetMU_PT70_EtaN15P15.Fill(MJet.JetPFMUF[iJ] * MJet.JetPT[iJ]);
                  HJetHad_PT70_EtaN15P15.Fill((MJet.JetPFCHF[iJ] + MJet.JetPFNHF[iJ]) * MJet.JetPT[iJ]);
               }
               if(MJet.JetEta[iJ] > 1.5 && MJet.JetEta[iJ] < MaxEta)
               {
                  HJetCHF_PT70_EtaP15P25.Fill(MJet.JetPFCHF[iJ]);
                  HJetCEF_PT70_EtaP15P25.Fill(MJet.JetPFCEF[iJ]);
                  HJetNHF_PT70_EtaP15P25.Fill(MJet.JetPFNHF[iJ]);
                  HJetNEF_PT70_EtaP15P25.Fill(MJet.JetPFNEF[iJ]);
                  HJetMUF_PT70_EtaP15P25.Fill(MJet.JetPFMUF[iJ]);
                  HJetCH_PT70_EtaP15P25.Fill(MJet.JetPFCHF[iJ] * MJet.JetPT[iJ]);
                  HJetCE_PT70_EtaP15P25.Fill(MJet.JetPFCEF[iJ] * MJet.JetPT[iJ]);
                  HJetNH_PT70_EtaP15P25.Fill(MJet.JetPFNHF[iJ] * MJet.JetPT[iJ]);
                  HJetNE_PT70_EtaP15P25.Fill(MJet.JetPFNEF[iJ] * MJet.JetPT[iJ]);
                  HJetMU_PT70_EtaP15P25.Fill(MJet.JetPFMUF[iJ] * MJet.JetPT[iJ]);
                  HJetHad_PT70_EtaP15P25.Fill((MJet.JetPFCHF[iJ] + MJet.JetPFNHF[iJ]) * MJet.JetPT[iJ]);
               }
            }

            if(CheckFraction == true)
            {
               if(MJet.JetPFMUF[iJ] > 0.01)
                  continue;
               if(MJet.JetPFCHF[iJ] < 0.01)
                  continue;
            }

            if(fabs(MJet.JetEta[iJ]) < MaxEta)
            {
               HJetPTVsRawPT.Fill(MJet.JetPT[iJ], MJet.JetRawPT[iJ]);
               HRawPTVsJEC.Fill(MJet.JetRawPT[iJ], MJet.JetPT[iJ] / MJet.JetRawPT[iJ]);
            }

            if(MJet.JetPT[iJ] > 30)
               HEtaPhiPT30.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);
            if(MJet.JetPT[iJ] > 50)
               HEtaPhiPT50.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);
            if(MJet.JetPT[iJ] > 70)
               HEtaPhiPT70.Fill(MJet.JetEta[iJ], MJet.JetPhi[iJ]);

            if(MJet.JetEta[iJ] > -MaxEta && MJet.JetEta[iJ] < -1.5)
               HAllJetPT_EtaN25N15.Fill(MJet.JetPT[iJ]);
            if(MJet.JetEta[iJ] > -1.5 && MJet.JetEta[iJ] < 1.5)
               HAllJetPT_EtaN15P15.Fill(MJet.JetPT[iJ]);
            if(MJet.JetEta[iJ] > 1.5 && MJet.JetEta[iJ] < MaxEta)
               HAllJetPT_EtaP15P25.Fill(MJet.JetPT[iJ]);
            
            if(BestJetIndex < 0 || MJet.JetPT[iJ] > MJet.JetPT[BestJetIndex])
               BestJetIndex = iJ;
         }

         bool PassL156 = (MHLT.CheckTrigger("L1_SingleJet56_BptxAND") > 0);

         if(BestJetIndex >= 0)
         {
            if(fabs(MJet.JetEta[BestJetIndex]) < 5.2)
               HJetPT.Fill(MJet.JetPT[BestJetIndex]);
            if(fabs(MJet.JetEta[BestJetIndex]) < 1.5)
               HJetPT_EtaN15P15.Fill(MJet.JetPT[BestJetIndex]);
            if(fabs(MJet.JetEta[BestJetIndex]) < MaxEta)
               HJetPT_EtaN25P25.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > 0 && MJet.JetEta[BestJetIndex] < MaxEta)
               HJetPT_EtaN00P25.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > -MaxEta && MJet.JetEta[BestJetIndex] < 0)
               HJetPT_EtaN25P00.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > 1.5 && MJet.JetEta[BestJetIndex] < MaxEta)
               HJetPT_EtaP15P25.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > -MaxEta && MJet.JetEta[BestJetIndex] < -1.5)
               HJetPT_EtaN25N15.Fill(MJet.JetPT[BestJetIndex]);
            
            if(fabs(MJet.JetEta[BestJetIndex]) < 5.2 && PassL156)
               HJetPTPassL156.Fill(MJet.JetPT[BestJetIndex]);
            if(fabs(MJet.JetEta[BestJetIndex]) < 1.5 && PassL156)
               HJetPTPassL156_EtaN15P15.Fill(MJet.JetPT[BestJetIndex]);
            if(fabs(MJet.JetEta[BestJetIndex]) < MaxEta && PassL156)
               HJetPTPassL156_EtaN25P25.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > 0 && MJet.JetEta[BestJetIndex] < MaxEta && PassL156)
               HJetPTPassL156_EtaN00P25.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > -MaxEta && MJet.JetEta[BestJetIndex] < 0 && PassL156)
               HJetPTPassL156_EtaN25P00.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > 1.5 && MJet.JetEta[BestJetIndex] < MaxEta && PassL156)
               HJetPTPassL156_EtaP15P25.Fill(MJet.JetPT[BestJetIndex]);
            if(MJet.JetEta[BestJetIndex] > -MaxEta && MJet.JetEta[BestJetIndex] < -1.5 && PassL156)
               HJetPTPassL156_EtaN25N15.Fill(MJet.JetPT[BestJetIndex]);
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   vector<string> Explanation(10);
   Explanation[0] = "Selections";
   Explanation[1] = "";
   Explanation[2] = "Other than fraction plots, all jets have";
   Explanation[3] = "   * CHF > 0.01";
   Explanation[4] = "   * MUF < 0.01";
   Explanation[5] = "";
   Explanation[6] = "Good lumi selected based on JSON";
   Explanation[7] = "";
   Explanation[8] = "";
   if(ReducedEta == true)
      Explanation[8] = "Reject jets between |eta| = 2.2 - 2.5";
   PdfFile.AddTextPage(Explanation);

   HEtaPhiPT30.SetStats(0);
   HEtaPhiPT50.SetStats(0);
   HEtaPhiPT70.SetStats(0);

   PdfFile.AddPlot(HEtaPhiPT30, "colz");
   PdfFile.AddPlot(HEtaPhiPT50, "colz");
   PdfFile.AddPlot(HEtaPhiPT70, "colz");

   HJetPT.SetStats(0);
   HJetPTPassL156.SetLineColor(kRed);
   HJetPT_EtaN15P15.SetStats(0);
   HJetPTPassL156_EtaN15P15.SetLineColor(kRed);
   HJetPT_EtaN25P25.SetStats(0);
   HJetPTPassL156_EtaN25P25.SetLineColor(kRed);
   HJetPT_EtaN00P25.SetStats(0);
   HJetPTPassL156_EtaN00P25.SetLineColor(kRed);
   HJetPT_EtaN25P00.SetStats(0);
   HJetPTPassL156_EtaN25P00.SetLineColor(kRed);
   HJetPT_EtaP15P25.SetStats(0);
   HJetPTPassL156_EtaP15P25.SetLineColor(kRed);
   HJetPT_EtaN25N15.SetStats(0);
   HJetPTPassL156_EtaN25N15.SetLineColor(kRed);

   TCanvas Canvas;
   TGraphAsymmErrors GTurnOn;
   TGraphAsymmErrors GTurnOn_EtaN15P15;
   TGraphAsymmErrors GTurnOn_EtaN25P25;
   TGraphAsymmErrors GTurnOn_EtaN00P25;
   TGraphAsymmErrors GTurnOn_EtaN25P00;
   TGraphAsymmErrors GTurnOn_EtaP15P25;
   TGraphAsymmErrors GTurnOn_EtaN25N15;
   
   GTurnOn.Divide(&HJetPTPassL156, &HJetPT);
   GTurnOn_EtaN15P15.Divide(&HJetPTPassL156_EtaN15P15, &HJetPT_EtaN15P15);
   GTurnOn_EtaN25P25.Divide(&HJetPTPassL156_EtaN25P25, &HJetPT_EtaN25P25);
   GTurnOn_EtaN00P25.Divide(&HJetPTPassL156_EtaN00P25, &HJetPT_EtaN00P25);
   GTurnOn_EtaN25P00.Divide(&HJetPTPassL156_EtaN25P00, &HJetPT_EtaN25P00);
   GTurnOn_EtaP15P25.Divide(&HJetPTPassL156_EtaP15P25, &HJetPT_EtaP15P25);
   GTurnOn_EtaN25N15.Divide(&HJetPTPassL156_EtaN25N15, &HJetPT_EtaN25N15);

   TF1 FTurnOn("FTurnOn", Function.c_str(), 0, 200);
   TF1 FTurnOn_EtaN15P15("FTurnOn_EtaN15P15", Function.c_str(), 0, 200);
   TF1 FTurnOn_EtaN25P25("FTurnOn_EtaN25P25", Function.c_str(), 0, 200);
   TF1 FTurnOn_EtaN00P25("FTurnOn_EtaN00P25", Function.c_str(), 0, 200);
   TF1 FTurnOn_EtaN25P00("FTurnOn_EtaN25P00", Function.c_str(), 0, 200);
   TF1 FTurnOn_EtaP15P25("FTurnOn_EtaP15P25", Function.c_str(), 0, 200);
   TF1 FTurnOn_EtaN25N15("FTurnOn_EtaN25N15", Function.c_str(), 0, 200);

   FTurnOn.SetParameters(0.05, 30, 7, 1.0, 0.0);
   FTurnOn_EtaN15P15.SetParameters(0.05, 30, 7, 1.0, 0.0);
   FTurnOn_EtaN25P25.SetParameters(0.05, 30, 7, 1.0, 0.0);
   FTurnOn_EtaN00P25.SetParameters(0.05, 30, 7, 1.0, 0.0);
   FTurnOn_EtaN25P00.SetParameters(0.05, 30, 7, 1.0, 0.0);
   FTurnOn_EtaP15P25.SetParameters(0.05, 30, 7, 1.0, 0.0);
   FTurnOn_EtaN25N15.SetParameters(0.05, 30, 7, 1.0, 0.0);
   
   FTurnOn.FixParameter(3, 1.0);
   FTurnOn_EtaN15P15.FixParameter(3, 1.0);
   FTurnOn_EtaN25P25.FixParameter(3, 1.0);
   FTurnOn_EtaN00P25.FixParameter(3, 1.0);
   FTurnOn_EtaN25P00.FixParameter(3, 1.0);
   FTurnOn_EtaP15P25.FixParameter(3, 1.0);
   FTurnOn_EtaN25N15.FixParameter(3, 1.0);
   
   FTurnOn.FixParameter(4, 0.0);
   FTurnOn_EtaN15P15.FixParameter(4, 0.0);
   FTurnOn_EtaN25P25.FixParameter(4, 0.0);
   FTurnOn_EtaN00P25.FixParameter(4, 0.0);
   FTurnOn_EtaN25P00.FixParameter(4, 0.0);
   FTurnOn_EtaP15P25.FixParameter(4, 0.0);
   FTurnOn_EtaN25N15.FixParameter(4, 0.0);
   
   FTurnOn.SetTitle("");
   FTurnOn_EtaN15P15.SetTitle("");
   FTurnOn_EtaN25P25.SetTitle("");
   FTurnOn_EtaN00P25.SetTitle("");
   FTurnOn_EtaN25P00.SetTitle("");
   FTurnOn_EtaP15P25.SetTitle("");
   FTurnOn_EtaN25N15.SetTitle("");
   
   FTurnOn.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   FTurnOn_EtaN15P15.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   FTurnOn_EtaN25P25.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   FTurnOn_EtaN00P25.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   FTurnOn_EtaN25P00.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   FTurnOn_EtaP15P25.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   FTurnOn_EtaN25N15.SetParNames("#lambda", "#mu", "#sigma", "Plateau", "Baseline");
   
   GTurnOn.Fit(&FTurnOn, "0");
   GTurnOn_EtaN15P15.Fit(&FTurnOn_EtaN15P15, "0");
   GTurnOn_EtaN25P25.Fit(&FTurnOn_EtaN25P25, "0");
   GTurnOn_EtaN00P25.Fit(&FTurnOn_EtaN00P25, "0");
   GTurnOn_EtaN25P00.Fit(&FTurnOn_EtaN25P00, "0");
   GTurnOn_EtaP15P25.Fit(&FTurnOn_EtaP15P25, "0");
   GTurnOn_EtaN25N15.Fit(&FTurnOn_EtaN25N15, "0");

   TH2D HWorldFit("HWorldFit", ";p_{T};Efficiency", 100, 0, 200, 100, 0, 1.1);
   HWorldFit.SetStats(0);
   
   HJetPT.Draw();
   HJetPTPassL156.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn.Draw("same");
   GTurnOn.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);
   
   HJetPT_EtaN15P15.Draw();
   HJetPTPassL156_EtaN15P15.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn_EtaN15P15.Draw("same");
   GTurnOn_EtaN15P15.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);

   HJetPT_EtaN25P25.Draw();
   HJetPTPassL156_EtaN25P25.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn_EtaN25P25.Draw("same");
   GTurnOn_EtaN25P25.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);

   HJetPT_EtaN00P25.Draw();
   HJetPTPassL156_EtaN00P25.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn_EtaN00P25.Draw("same");
   GTurnOn_EtaN00P25.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);

   HJetPT_EtaN25P00.Draw();
   HJetPTPassL156_EtaN25P00.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn_EtaN25P00.Draw("same");
   GTurnOn_EtaN25P00.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);

   HJetPT_EtaP15P25.Draw();
   HJetPTPassL156_EtaP15P25.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn_EtaP15P25.Draw("same");
   GTurnOn_EtaP15P25.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);

   HJetPT_EtaN25N15.Draw();
   HJetPTPassL156_EtaN25N15.Draw("same");
   PdfFile.AddCanvas(Canvas);
   HWorldFit.Draw("axis");
   FTurnOn_EtaN25N15.Draw("same");
   GTurnOn_EtaN25N15.Draw("p");
   Canvas.SetGridx();
   Canvas.SetGridy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetGridx(false);
   Canvas.SetGridy(false);

   ((TPaveStats *)GTurnOn.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   ((TPaveStats *)GTurnOn.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);
   ((TPaveStats *)GTurnOn_EtaN15P15.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   ((TPaveStats *)GTurnOn_EtaN15P15.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);
   ((TPaveStats *)GTurnOn_EtaN25P25.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   ((TPaveStats *)GTurnOn_EtaN25P25.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);
   ((TPaveStats *)GTurnOn_EtaN00P25.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   ((TPaveStats *)GTurnOn_EtaN00P25.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);
   ((TPaveStats *)GTurnOn_EtaN25P00.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   ((TPaveStats *)GTurnOn_EtaN25P00.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);
   ((TPaveStats *)GTurnOn_EtaP15P25.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   ((TPaveStats *)GTurnOn_EtaP15P25.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);
   ((TPaveStats *)GTurnOn_EtaN25N15.GetListOfFunctions()->FindObject("stats"))->SetX1NDC(1.10);
   ((TPaveStats *)GTurnOn_EtaN25N15.GetListOfFunctions()->FindObject("stats"))->SetX2NDC(1.20);

   GTurnOn_EtaN25P00.SetLineColor(kRed);
   GTurnOn_EtaN25P00.SetMarkerColor(kRed);
   GTurnOn_EtaN00P25.Draw("ap");
   GTurnOn_EtaN25P00.Draw("p");
   TLegend Legend1(0.5, 0.2, 0.8, 0.4);
   Legend1.SetTextFont(42);
   Legend1.SetTextSize(0.035);
   Legend1.SetFillStyle(0);
   Legend1.SetBorderSize(0);
   Legend1.AddEntry(&GTurnOn_EtaN00P25, "0 < #eta < 2.5", "pl");
   Legend1.AddEntry(&GTurnOn_EtaN25P00, "-2.5 < #eta < 0", "pl");
   Legend1.Draw();
   PdfFile.AddCanvas(Canvas);

   GTurnOn_EtaN25N15.SetLineColor(kBlack);
   GTurnOn_EtaN25N15.SetMarkerColor(kBlack);
   GTurnOn_EtaN15P15.SetLineColor(kGreen);
   GTurnOn_EtaN15P15.SetMarkerColor(kGreen);
   GTurnOn_EtaP15P25.SetLineColor(kRed);
   GTurnOn_EtaP15P25.SetMarkerColor(kRed);
   GTurnOn_EtaN15P15.Draw("ap");
   GTurnOn_EtaP15P25.Draw("p");
   GTurnOn_EtaN25N15.Draw("p");
   TLegend Legend2(0.5, 0.2, 0.8, 0.4);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.SetFillStyle(0);
   Legend2.SetBorderSize(0);
   Legend2.AddEntry(&GTurnOn_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   Legend2.AddEntry(&GTurnOn_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   Legend2.AddEntry(&GTurnOn_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   Legend2.Draw();
   PdfFile.AddCanvas(Canvas);

   HJetPTVsRawPT.SetStats(0);
   HRawPTVsJEC.SetStats(0);
   PdfFile.AddPlot(HJetPTVsRawPT, "colz");
   PdfFile.AddPlot(HRawPTVsJEC, "colz");

   HAllJetPT_EtaN25N15.SetStats(0);
   HAllJetPT_EtaN15P15.SetStats(0);
   HAllJetPT_EtaP15P25.SetStats(0);

   HAllJetPT_EtaN25N15.SetLineColor(kBlack);
   HAllJetPT_EtaN15P15.SetLineColor(kGreen);
   HAllJetPT_EtaP15P25.SetLineColor(kRed);
   
   HAllJetPT_EtaN25N15.SetMarkerColor(kBlack);
   HAllJetPT_EtaN15P15.SetMarkerColor(kGreen);
   HAllJetPT_EtaP15P25.SetMarkerColor(kRed);

   TH2D HWorldPT("HWorldPT", ";PT;", 100, 0, 200, 100, 1e-7, 1.0);
   HWorldPT.SetStats(0);
   HWorldPT.Draw("axis");
   HAllJetPT_EtaN25N15.DrawNormalized("same");
   HAllJetPT_EtaN15P15.DrawNormalized("same");
   HAllJetPT_EtaP15P25.DrawNormalized("same");
   TLegend LegendPT(0.4, 0.6, 0.7, 0.8);
   LegendPT.SetTextFont(42);
   LegendPT.SetTextSize(0.035);
   LegendPT.SetBorderSize(0);
   LegendPT.SetFillStyle(0);
   LegendPT.AddEntry(&HAllJetPT_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendPT.AddEntry(&HAllJetPT_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendPT.AddEntry(&HAllJetPT_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendPT.Draw();
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);

   HJetCHF_PT50_EtaN25N15.SetStats(0);
   HJetCHF_PT50_EtaN15P15.SetStats(0);
   HJetCHF_PT50_EtaP15P25.SetStats(0);
   HJetCEF_PT50_EtaN25N15.SetStats(0);
   HJetCEF_PT50_EtaN15P15.SetStats(0);
   HJetCEF_PT50_EtaP15P25.SetStats(0);
   HJetNHF_PT50_EtaN25N15.SetStats(0);
   HJetNHF_PT50_EtaN15P15.SetStats(0);
   HJetNHF_PT50_EtaP15P25.SetStats(0);
   HJetNEF_PT50_EtaN25N15.SetStats(0);
   HJetNEF_PT50_EtaN15P15.SetStats(0);
   HJetNEF_PT50_EtaP15P25.SetStats(0);
   HJetMUF_PT50_EtaN25N15.SetStats(0);
   HJetMUF_PT50_EtaN15P15.SetStats(0);
   HJetMUF_PT50_EtaP15P25.SetStats(0);
   HJetCH_PT50_EtaN25N15.SetStats(0);
   HJetCH_PT50_EtaN15P15.SetStats(0);
   HJetCH_PT50_EtaP15P25.SetStats(0);
   HJetCE_PT50_EtaN25N15.SetStats(0);
   HJetCE_PT50_EtaN15P15.SetStats(0);
   HJetCE_PT50_EtaP15P25.SetStats(0);
   HJetNH_PT50_EtaN25N15.SetStats(0);
   HJetNH_PT50_EtaN15P15.SetStats(0);
   HJetNH_PT50_EtaP15P25.SetStats(0);
   HJetNE_PT50_EtaN25N15.SetStats(0);
   HJetNE_PT50_EtaN15P15.SetStats(0);
   HJetNE_PT50_EtaP15P25.SetStats(0);
   HJetMU_PT50_EtaN25N15.SetStats(0);
   HJetMU_PT50_EtaN15P15.SetStats(0);
   HJetMU_PT50_EtaP15P25.SetStats(0);
   HJetHad_PT50_EtaN25N15.SetStats(0);
   HJetHad_PT50_EtaN15P15.SetStats(0);
   HJetHad_PT50_EtaP15P25.SetStats(0);
   HJetCHF_PT70_EtaN25N15.SetStats(0);
   HJetCHF_PT70_EtaN15P15.SetStats(0);
   HJetCHF_PT70_EtaP15P25.SetStats(0);
   HJetCEF_PT70_EtaN25N15.SetStats(0);
   HJetCEF_PT70_EtaN15P15.SetStats(0);
   HJetCEF_PT70_EtaP15P25.SetStats(0);
   HJetNHF_PT70_EtaN25N15.SetStats(0);
   HJetNHF_PT70_EtaN15P15.SetStats(0);
   HJetNHF_PT70_EtaP15P25.SetStats(0);
   HJetNEF_PT70_EtaN25N15.SetStats(0);
   HJetNEF_PT70_EtaN15P15.SetStats(0);
   HJetNEF_PT70_EtaP15P25.SetStats(0);
   HJetMUF_PT70_EtaN25N15.SetStats(0);
   HJetMUF_PT70_EtaN15P15.SetStats(0);
   HJetMUF_PT70_EtaP15P25.SetStats(0);
   HJetCH_PT70_EtaN25N15.SetStats(0);
   HJetCH_PT70_EtaN15P15.SetStats(0);
   HJetCH_PT70_EtaP15P25.SetStats(0);
   HJetCE_PT70_EtaN25N15.SetStats(0);
   HJetCE_PT70_EtaN15P15.SetStats(0);
   HJetCE_PT70_EtaP15P25.SetStats(0);
   HJetNH_PT70_EtaN25N15.SetStats(0);
   HJetNH_PT70_EtaN15P15.SetStats(0);
   HJetNH_PT70_EtaP15P25.SetStats(0);
   HJetNE_PT70_EtaN25N15.SetStats(0);
   HJetNE_PT70_EtaN15P15.SetStats(0);
   HJetNE_PT70_EtaP15P25.SetStats(0);
   HJetMU_PT70_EtaN25N15.SetStats(0);
   HJetMU_PT70_EtaN15P15.SetStats(0);
   HJetMU_PT70_EtaP15P25.SetStats(0);
   HJetHad_PT70_EtaN25N15.SetStats(0);
   HJetHad_PT70_EtaN15P15.SetStats(0);
   HJetHad_PT70_EtaP15P25.SetStats(0);

   HJetCHF_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetCHF_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetCHF_PT50_EtaP15P25.SetLineColor(kRed);
   HJetCEF_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetCEF_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetCEF_PT50_EtaP15P25.SetLineColor(kRed);
   HJetNHF_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetNHF_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetNHF_PT50_EtaP15P25.SetLineColor(kRed);
   HJetNEF_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetNEF_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetNEF_PT50_EtaP15P25.SetLineColor(kRed);
   HJetMUF_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetMUF_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetMUF_PT50_EtaP15P25.SetLineColor(kRed);
   HJetCH_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetCH_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetCH_PT50_EtaP15P25.SetLineColor(kRed);
   HJetCE_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetCE_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetCE_PT50_EtaP15P25.SetLineColor(kRed);
   HJetNH_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetNH_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetNH_PT50_EtaP15P25.SetLineColor(kRed);
   HJetNE_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetNE_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetNE_PT50_EtaP15P25.SetLineColor(kRed);
   HJetMU_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetMU_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetMU_PT50_EtaP15P25.SetLineColor(kRed);
   HJetHad_PT50_EtaN25N15.SetLineColor(kBlack);
   HJetHad_PT50_EtaN15P15.SetLineColor(kGreen);
   HJetHad_PT50_EtaP15P25.SetLineColor(kRed);
   HJetCHF_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetCHF_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetCHF_PT70_EtaP15P25.SetLineColor(kRed);
   HJetCEF_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetCEF_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetCEF_PT70_EtaP15P25.SetLineColor(kRed);
   HJetNHF_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetNHF_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetNHF_PT70_EtaP15P25.SetLineColor(kRed);
   HJetNEF_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetNEF_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetNEF_PT70_EtaP15P25.SetLineColor(kRed);
   HJetMUF_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetMUF_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetMUF_PT70_EtaP15P25.SetLineColor(kRed);
   HJetCH_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetCH_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetCH_PT70_EtaP15P25.SetLineColor(kRed);
   HJetCE_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetCE_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetCE_PT70_EtaP15P25.SetLineColor(kRed);
   HJetNH_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetNH_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetNH_PT70_EtaP15P25.SetLineColor(kRed);
   HJetNE_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetNE_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetNE_PT70_EtaP15P25.SetLineColor(kRed);
   HJetMU_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetMU_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetMU_PT70_EtaP15P25.SetLineColor(kRed);
   HJetHad_PT70_EtaN25N15.SetLineColor(kBlack);
   HJetHad_PT70_EtaN15P15.SetLineColor(kGreen);
   HJetHad_PT70_EtaP15P25.SetLineColor(kRed);
   
   HJetCHF_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetCHF_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetCHF_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetCEF_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetCEF_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetCEF_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetNHF_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetNHF_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetNHF_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetNEF_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetNEF_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetNEF_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetMUF_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetMUF_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetMUF_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetCH_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetCH_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetCH_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetCE_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetCE_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetCE_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetNH_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetNH_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetNH_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetNE_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetNE_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetNE_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetMU_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetMU_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetMU_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetHad_PT50_EtaN25N15.SetMarkerColor(kBlack);
   HJetHad_PT50_EtaN15P15.SetMarkerColor(kGreen);
   HJetHad_PT50_EtaP15P25.SetMarkerColor(kRed);
   HJetCHF_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetCHF_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetCHF_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetCEF_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetCEF_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetCEF_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetNHF_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetNHF_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetNHF_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetNEF_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetNEF_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetNEF_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetMUF_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetMUF_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetMUF_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetCH_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetCH_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetCH_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetCE_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetCE_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetCE_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetNH_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetNH_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetNH_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetNE_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetNE_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetNE_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetMU_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetMU_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetMU_PT70_EtaP15P25.SetMarkerColor(kRed);
   HJetHad_PT70_EtaN25N15.SetMarkerColor(kBlack);
   HJetHad_PT70_EtaN15P15.SetMarkerColor(kGreen);
   HJetHad_PT70_EtaP15P25.SetMarkerColor(kRed);

   TH2D HWorldCHF("HWorldCHF", "p_{T} > 50 GeV;CHF;", 100, 0, 1, 100, 0, 0.1);
   HWorldCHF.SetStats(0);
   HWorldCHF.Draw("axis");
   HJetCHF_PT50_EtaN25N15.DrawNormalized("same");
   HJetCHF_PT50_EtaN15P15.DrawNormalized("same");
   HJetCHF_PT50_EtaP15P25.DrawNormalized("same");
   TLegend LegendCHF(0.4, 0.6, 0.7, 0.8);
   LegendCHF.SetTextFont(42);
   LegendCHF.SetTextSize(0.035);
   LegendCHF.SetBorderSize(0);
   LegendCHF.SetFillStyle(0);
   LegendCHF.AddEntry(&HJetCHF_PT50_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendCHF.AddEntry(&HJetCHF_PT50_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendCHF.AddEntry(&HJetCHF_PT50_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendCHF.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorldCHF.Draw("axis");
   HWorldCHF.SetTitle("p_{T} > 70 GeV");
   HJetCHF_PT70_EtaN25N15.DrawNormalized("same");
   HJetCHF_PT70_EtaN15P15.DrawNormalized("same");
   HJetCHF_PT70_EtaP15P25.DrawNormalized("same");
   LegendCHF.Draw();
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldCH("HWorldCH", "p_{T} > 50 GeV;CH Energy;", 100, 0, 200, 100, 1e-5, 1);
   HWorldCH.SetStats(0);
   HWorldCH.Draw("axis");
   HJetCH_PT50_EtaN25N15.DrawNormalized("same");
   HJetCH_PT50_EtaN15P15.DrawNormalized("same");
   HJetCH_PT50_EtaP15P25.DrawNormalized("same");
   LegendCHF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HWorldCH.Draw("axis");
   HWorldCH.SetTitle("p_{T} > 70 GeV");
   HJetCH_PT70_EtaN25N15.DrawNormalized("same");
   HJetCH_PT70_EtaN15P15.DrawNormalized("same");
   HJetCH_PT70_EtaP15P25.DrawNormalized("same");
   LegendCHF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldCEF("HWorldCEF", "p_{T} > 50 GeV;CEF;", 100, 0, 1, 100, 0, 0.1);
   HWorldCEF.SetStats(0);
   HWorldCEF.Draw("axis");
   HJetCEF_PT50_EtaN25N15.DrawNormalized("same");
   HJetCEF_PT50_EtaN15P15.DrawNormalized("same");
   HJetCEF_PT50_EtaP15P25.DrawNormalized("same");
   TLegend LegendCEF(0.4, 0.6, 0.7, 0.8);
   LegendCEF.SetTextFont(42);
   LegendCEF.SetTextSize(0.035);
   LegendCEF.SetBorderSize(0);
   LegendCEF.SetFillStyle(0);
   LegendCEF.AddEntry(&HJetCEF_PT50_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendCEF.AddEntry(&HJetCEF_PT50_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendCEF.AddEntry(&HJetCEF_PT50_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendCEF.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorldCEF.Draw("axis");
   HWorldCEF.SetTitle("p_{T} > 70 GeV");
   HJetCEF_PT70_EtaN25N15.DrawNormalized("same");
   HJetCEF_PT70_EtaN15P15.DrawNormalized("same");
   HJetCEF_PT70_EtaP15P25.DrawNormalized("same");
   LegendCEF.Draw();
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldCE("HWorldCE", "p_{T} > 50 GeV;CE Energy;", 100, 0, 200, 100, 1e-5, 1);
   HWorldCE.SetStats(0);
   HWorldCE.Draw("axis");
   HJetCE_PT50_EtaN25N15.DrawNormalized("same");
   HJetCE_PT50_EtaN15P15.DrawNormalized("same");
   HJetCE_PT50_EtaP15P25.DrawNormalized("same");
   LegendCEF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HWorldCE.Draw("axis");
   HWorldCE.SetTitle("p_{T} > 70 GeV");
   HJetCE_PT70_EtaN25N15.DrawNormalized("same");
   HJetCE_PT70_EtaN15P15.DrawNormalized("same");
   HJetCE_PT70_EtaP15P25.DrawNormalized("same");
   LegendCEF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldNHF("HWorldNHF", "p_{T} > 50 GeV;NHF;", 100, 0, 1, 100, 0, 0.1);
   HWorldNHF.SetStats(0);
   HWorldNHF.Draw("axis");
   HJetNHF_PT50_EtaN25N15.DrawNormalized("same");
   HJetNHF_PT50_EtaN15P15.DrawNormalized("same");
   HJetNHF_PT50_EtaP15P25.DrawNormalized("same");
   TLegend LegendNHF(0.4, 0.6, 0.7, 0.8);
   LegendNHF.SetTextFont(42);
   LegendNHF.SetTextSize(0.035);
   LegendNHF.SetBorderSize(0);
   LegendNHF.SetFillStyle(0);
   LegendNHF.AddEntry(&HJetNHF_PT50_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendNHF.AddEntry(&HJetNHF_PT50_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendNHF.AddEntry(&HJetNHF_PT50_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendNHF.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorldNHF.Draw("axis");
   HWorldNHF.SetTitle("p_{T} > 70 GeV");
   HJetNHF_PT70_EtaN25N15.DrawNormalized("same");
   HJetNHF_PT70_EtaN15P15.DrawNormalized("same");
   HJetNHF_PT70_EtaP15P25.DrawNormalized("same");
   LegendNHF.Draw();
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldNH("HWorldNH", "p_{T} > 50 GeV;NH Energy;", 100, 0, 200, 100, 1e-5, 1);
   HWorldNH.SetStats(0);
   HWorldNH.Draw("axis");
   HJetNH_PT50_EtaN25N15.DrawNormalized("same");
   HJetNH_PT50_EtaN15P15.DrawNormalized("same");
   HJetNH_PT50_EtaP15P25.DrawNormalized("same");
   LegendNHF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HWorldNH.Draw("axis");
   HWorldNH.SetTitle("p_{T} > 70 GeV");
   HJetNH_PT70_EtaN25N15.DrawNormalized("same");
   HJetNH_PT70_EtaN15P15.DrawNormalized("same");
   HJetNH_PT70_EtaP15P25.DrawNormalized("same");
   LegendNHF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
   
   TH2D HWorldNEF("HWorldNEF", "p_{T} > 50 GeV;NEF;", 100, 0, 1, 100, 0, 0.1);
   HWorldNEF.SetStats(0);
   HWorldNEF.Draw("axis");
   HJetNEF_PT50_EtaN25N15.DrawNormalized("same");
   HJetNEF_PT50_EtaN15P15.DrawNormalized("same");
   HJetNEF_PT50_EtaP15P25.DrawNormalized("same");
   TLegend LegendNEF(0.4, 0.6, 0.7, 0.8);
   LegendNEF.SetTextFont(42);
   LegendNEF.SetTextSize(0.035);
   LegendNEF.SetBorderSize(0);
   LegendNEF.SetFillStyle(0);
   LegendNEF.AddEntry(&HJetNEF_PT50_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendNEF.AddEntry(&HJetNEF_PT50_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendNEF.AddEntry(&HJetNEF_PT50_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendNEF.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorldNEF.Draw("axis");
   HWorldNEF.SetTitle("p_{T} > 70 GeV");
   HJetNEF_PT70_EtaN25N15.DrawNormalized("same");
   HJetNEF_PT70_EtaN15P15.DrawNormalized("same");
   HJetNEF_PT70_EtaP15P25.DrawNormalized("same");
   LegendNEF.Draw();
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldNE("HWorldNE", "p_{T} > 50 GeV;NE Energy;", 100, 0, 200, 100, 1e-5, 1);
   HWorldNE.SetStats(0);
   HWorldNE.Draw("axis");
   HJetNE_PT50_EtaN25N15.DrawNormalized("same");
   HJetNE_PT50_EtaN15P15.DrawNormalized("same");
   HJetNE_PT50_EtaP15P25.DrawNormalized("same");
   LegendNEF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HWorldNE.Draw("axis");
   HWorldNE.SetTitle("p_{T} > 70 GeV");
   HJetNE_PT70_EtaN25N15.DrawNormalized("same");
   HJetNE_PT70_EtaN15P15.DrawNormalized("same");
   HJetNE_PT70_EtaP15P25.DrawNormalized("same");
   LegendNEF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldMUF("HWorldMUF", "p_{T} > 50 GeV;MUF;", 100, 0, 1, 100, 0, 0.1);
   HWorldMUF.SetStats(0);
   HWorldMUF.Draw("axis");
   HJetMUF_PT50_EtaN25N15.DrawNormalized("same");
   HJetMUF_PT50_EtaN15P15.DrawNormalized("same");
   HJetMUF_PT50_EtaP15P25.DrawNormalized("same");
   TLegend LegendMUF(0.4, 0.6, 0.7, 0.8);
   LegendMUF.SetTextFont(42);
   LegendMUF.SetTextSize(0.035);
   LegendMUF.SetBorderSize(0);
   LegendMUF.SetFillStyle(0);
   LegendMUF.AddEntry(&HJetMUF_PT50_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendMUF.AddEntry(&HJetMUF_PT50_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendMUF.AddEntry(&HJetMUF_PT50_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendMUF.Draw();
   PdfFile.AddCanvas(Canvas);

   HWorldMUF.Draw("axis");
   HWorldMUF.SetTitle("p_{T} > 70 GeV");
   HJetMUF_PT70_EtaN25N15.DrawNormalized("same");
   HJetMUF_PT70_EtaN15P15.DrawNormalized("same");
   HJetMUF_PT70_EtaP15P25.DrawNormalized("same");
   LegendMUF.Draw();
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldMU("HWorldMU", "p_{T} > 50 GeV;MU Energy;", 100, 0, 200, 100, 1e-5, 1);
   HWorldMU.SetStats(0);
   HWorldMU.Draw("axis");
   HJetMU_PT50_EtaN25N15.DrawNormalized("same");
   HJetMU_PT50_EtaN15P15.DrawNormalized("same");
   HJetMU_PT50_EtaP15P25.DrawNormalized("same");
   LegendMUF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HWorldMU.Draw("axis");
   HWorldMU.SetTitle("p_{T} > 70 GeV");
   HJetMU_PT70_EtaN25N15.DrawNormalized("same");
   HJetMU_PT70_EtaN15P15.DrawNormalized("same");
   HJetMU_PT70_EtaP15P25.DrawNormalized("same");
   LegendMUF.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   TH2D HWorldHad("HWorldHad", "p_{T} > 50 GeV;Had Energy;", 100, 0, 200, 100, 1e-5, 1);
   HWorldHad.SetStats(0);
   HWorldHad.Draw("axis");
   HJetHad_PT50_EtaN25N15.DrawNormalized("same");
   HJetHad_PT50_EtaN15P15.DrawNormalized("same");
   HJetHad_PT50_EtaP15P25.DrawNormalized("same");
   TLegend LegendHad(0.4, 0.6, 0.7, 0.8);
   LegendHad.SetTextFont(42);
   LegendHad.SetTextSize(0.035);
   LegendHad.SetBorderSize(0);
   LegendHad.SetFillStyle(0);
   LegendHad.AddEntry(&HJetHad_PT50_EtaN25N15, "-2.5 < #eta < -1.5", "pl");
   LegendHad.AddEntry(&HJetHad_PT50_EtaN15P15, "-1.5 < #eta < 1.5", "pl");
   LegendHad.AddEntry(&HJetHad_PT50_EtaP15P25, "1.5 < #eta < 2.5", "pl");
   LegendHad.Draw();
   LegendHad.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   HWorldHad.Draw("axis");
   HWorldHad.SetTitle("p_{T} > 70 GeV");
   HJetHad_PT70_EtaN25N15.DrawNormalized("same");
   HJetHad_PT70_EtaN15P15.DrawNormalized("same");
   HJetHad_PT70_EtaP15P25.DrawNormalized("same");
   LegendHad.Draw();
   Canvas.SetLogy(true);
   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);

   OutputFile.cd();

   HN.Write();
   HEtaPhiPT30.Write();
   HEtaPhiPT50.Write();
   HEtaPhiPT70.Write();

   HJetPT.Write();
   HJetPT_EtaN15P15.Write();
   HJetPT_EtaN25P25.Write();
   HJetPT_EtaN00P25.Write();
   HJetPT_EtaN25P00.Write();
   HJetPT_EtaP15P25.Write();
   HJetPT_EtaN25N15.Write();
   HJetPTPassL156.Write();
   HJetPTPassL156_EtaN15P15.Write();
   HJetPTPassL156_EtaN25P25.Write();
   HJetPTPassL156_EtaN00P25.Write();
   HJetPTPassL156_EtaN25P00.Write();
   HJetPTPassL156_EtaP15P25.Write();
   HJetPTPassL156_EtaN25N15.Write();

   HJetPTVsRawPT.Write();
   HRawPTVsJEC.Write();
                  
   HAllJetPT_EtaN25N15.Write();
   HAllJetPT_EtaN15P15.Write();
   HAllJetPT_EtaP15P25.Write();
   
   HJetCHF_PT50_EtaN25N15.Write();
   HJetCHF_PT50_EtaN15P15.Write();
   HJetCHF_PT50_EtaP15P25.Write();
   HJetCEF_PT50_EtaN25N15.Write();
   HJetCEF_PT50_EtaN15P15.Write();
   HJetCEF_PT50_EtaP15P25.Write();
   HJetNHF_PT50_EtaN25N15.Write();
   HJetNHF_PT50_EtaN15P15.Write();
   HJetNHF_PT50_EtaP15P25.Write();
   HJetNEF_PT50_EtaN25N15.Write();
   HJetNEF_PT50_EtaN15P15.Write();
   HJetNEF_PT50_EtaP15P25.Write();
   HJetMUF_PT50_EtaN25N15.Write();
   HJetMUF_PT50_EtaN15P15.Write();
   HJetMUF_PT50_EtaP15P25.Write();
   HJetCH_PT50_EtaN25N15.Write();
   HJetCH_PT50_EtaN15P15.Write();
   HJetCH_PT50_EtaP15P25.Write();
   HJetCE_PT50_EtaN25N15.Write();
   HJetCE_PT50_EtaN15P15.Write();
   HJetCE_PT50_EtaP15P25.Write();
   HJetNH_PT50_EtaN25N15.Write();
   HJetNH_PT50_EtaN15P15.Write();
   HJetNH_PT50_EtaP15P25.Write();
   HJetNE_PT50_EtaN25N15.Write();
   HJetNE_PT50_EtaN15P15.Write();
   HJetNE_PT50_EtaP15P25.Write();
   HJetMU_PT50_EtaN25N15.Write();
   HJetMU_PT50_EtaN15P15.Write();
   HJetMU_PT50_EtaP15P25.Write();
   HJetCHF_PT70_EtaN25N15.Write();
   HJetCHF_PT70_EtaN15P15.Write();
   HJetCHF_PT70_EtaP15P25.Write();
   HJetCEF_PT70_EtaN25N15.Write();
   HJetCEF_PT70_EtaN15P15.Write();
   HJetCEF_PT70_EtaP15P25.Write();
   HJetNHF_PT70_EtaN25N15.Write();
   HJetNHF_PT70_EtaN15P15.Write();
   HJetNHF_PT70_EtaP15P25.Write();
   HJetNEF_PT70_EtaN25N15.Write();
   HJetNEF_PT70_EtaN15P15.Write();
   HJetNEF_PT70_EtaP15P25.Write();
   HJetMUF_PT70_EtaN25N15.Write();
   HJetMUF_PT70_EtaN15P15.Write();
   HJetMUF_PT70_EtaP15P25.Write();
   HJetCH_PT70_EtaN25N15.Write();
   HJetCH_PT70_EtaN15P15.Write();
   HJetCH_PT70_EtaP15P25.Write();
   HJetCE_PT70_EtaN25N15.Write();
   HJetCE_PT70_EtaN15P15.Write();
   HJetCE_PT70_EtaP15P25.Write();
   HJetNH_PT70_EtaN25N15.Write();
   HJetNH_PT70_EtaN15P15.Write();
   HJetNH_PT70_EtaP15P25.Write();
   HJetNE_PT70_EtaN25N15.Write();
   HJetNE_PT70_EtaN15P15.Write();
   HJetNE_PT70_EtaP15P25.Write();
   HJetMU_PT70_EtaN25N15.Write();
   HJetMU_PT70_EtaN15P15.Write();
   HJetMU_PT70_EtaP15P25.Write();

   OutputFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}



