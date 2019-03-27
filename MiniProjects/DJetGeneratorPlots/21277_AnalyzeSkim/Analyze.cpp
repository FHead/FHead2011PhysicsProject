#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

#include "SetStyle.h"
#include "PlotHelper4.h"
#include "CustomAssert.h"
#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"

#define MAXJET 500
#define MAXD0 20

int main(int argc, char *argv[]);
void NormalizeHistogram(TH1D &H, int BinCount, double Bins[]);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputBase = CL.Get("OutputBase");

   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage(InputFileName);

   TFile File(InputFileName.c_str());

   TTree *Tree = (TTree *)File.Get("Tree");
   Assert(Tree != NULL, "Input tree not found");

   double Weight, PTHat;
   int JetCount;
   double JetPT[MAXJET], JetEta[MAXJET], JetPhi[MAXJET];
   int D0Count;
   double D0PT[MAXD0], D0Eta[MAXD0], D0Phi[MAXD0];
   double KPT[MAXD0], KEta[MAXD0], KPhi[MAXD0];
   double PiPT[MAXD0], PiEta[MAXD0], PiPhi[MAXD0];

   Tree->SetBranchAddress("Weight", &Weight);
   Tree->SetBranchAddress("PTHat", &PTHat);
   Tree->SetBranchAddress("JetCount", &JetCount);
   Tree->SetBranchAddress("JetPT", &JetPT);
   Tree->SetBranchAddress("JetEta", &JetEta);
   Tree->SetBranchAddress("JetPhi", &JetPhi);
   Tree->SetBranchAddress("D0Count", &D0Count);
   Tree->SetBranchAddress("D0PT", &D0PT);
   Tree->SetBranchAddress("D0Eta", &D0Eta);
   Tree->SetBranchAddress("D0Phi", &D0Phi);
   Tree->SetBranchAddress("KPT", &KPT);
   Tree->SetBranchAddress("KEta", &KEta);
   Tree->SetBranchAddress("KPhi", &KPhi);
   Tree->SetBranchAddress("PiPT", &PiPT);
   Tree->SetBranchAddress("PiEta", &PiEta);
   Tree->SetBranchAddress("PiPhi", &PiPhi);

   int BinCount = 4;
   double Bins[] = {0, 0.05, 0.1, 0.3, 0.5};

   TH1D HJetCount("HJetCount", "No extra cut;Jet count;", 10, 0, 10);
   TH1D HD0Count("HD0Count", "No extra cut;D0 count;", 10, 0, 10);
   
   TH1D HGoodJetCount("HGoodJetCount", "After selection;Jet count;", 10, 0, 10);
   TH1D HGoodD0Count("HGoodD0Count", "After selection;D0 count;", 10, 0, 10);

   TH1D HMatchedCount("HMatchedCount", ";Number of D0's within DR 0.5;", 5, 0, 5);
   TH1D HMatchedDR("HMatchedDR", ";#DeltaR;", 100, 0, 0.5);
   TH1D HMatchedDRBin0("HMatchedDRBin0", "4 < D p_{T} < 20;#DeltaR;", 100, 0, 0.5);
   TH1D HMatchedDRBin1("HMatchedDRBin1", "D p_{T} > 20;#DeltaR;", 100, 0, 0.5);
   TH1D HMatchedDRBin0Rebin("HMatchedDRBin0Rebin", "4 < D p_{T} < 20;#DeltaR;", BinCount, Bins);
   TH1D HMatchedDRBin1Rebin("HMatchedDRBin1Rebin", "D p_{T} > 20;#DeltaR;", BinCount, Bins);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      // Weight = 1;

      HJetCount.Fill(JetCount, Weight);
      HD0Count.Fill(D0Count, Weight);

      vector<FourVector> GoodJet;
      vector<FourVector> GoodD0;

      for(int iJ = 0; iJ < JetCount; iJ++)
      {
         if(JetPT[iJ] < 60)
            continue;
         if(fabs(JetEta[iJ]) > 1.6)
            continue;

         FourVector P;
         P.SetPtEtaPhi(JetPT[iJ], JetEta[iJ], JetPhi[iJ]);
         GoodJet.push_back(P);
      }

      for(int iD = 0; iD < D0Count; iD++)
      {
         if(KPT[iD] < 2)
            continue;
         if(fabs(KEta[iD]) > 2)
            continue;
         if(PiPT[iD] < 2)
            continue;
         if(fabs(PiEta[iD]) > 2)
            continue;
         if(D0PT[iD] < 2)
            continue;

         FourVector P;
         P.SetPtEtaPhi(D0PT[iD], D0Eta[iD], D0Phi[iD]);

         if(P.GetRapidity() < -2 || P.GetRapidity() > 2)
            continue;

         GoodD0.push_back(P);
      }

      HGoodJetCount.Fill(GoodJet.size(), Weight);
      HGoodD0Count.Fill(GoodD0.size(), Weight);

      for(int iJ = 0; iJ < (int)GoodJet.size(); iJ++)
      {
         int MatchedCount = 0;

         for(int iD = 0; iD < (int)GoodD0.size(); iD++)
         {
            double DR = GetDR(GoodJet[iJ], GoodD0[iD]);
            if(DR < 0.5)
            {
               MatchedCount = MatchedCount + 1;
               HMatchedDR.Fill(DR, Weight);
               if(GoodD0[iD].GetPT() > 4 && GoodD0[iD].GetPT() < 20)
               {
                  HMatchedDRBin0.Fill(DR, Weight);
                  HMatchedDRBin0Rebin.Fill(DR, Weight);
               }
               if(GoodD0[iD].GetPT() > 20)
               {
                  HMatchedDRBin1.Fill(DR, Weight);
                  HMatchedDRBin1Rebin.Fill(DR, Weight);
               }
            }
         }

         HMatchedCount.Fill(MatchedCount, Weight);
      }
   }

   NormalizeHistogram(HMatchedDRBin0Rebin, BinCount, Bins);
   NormalizeHistogram(HMatchedDRBin1Rebin, BinCount, Bins);

   PdfFile.AddPlot(HJetCount, "", true);
   PdfFile.AddPlot(HD0Count, "", true);
   PdfFile.AddPlot(HGoodJetCount, "", true);
   PdfFile.AddPlot(HGoodD0Count, "", true);
   PdfFile.AddPlot(HMatchedCount, "", true);
   PdfFile.AddPlot(HMatchedDR, "", true);
   PdfFile.AddPlot(HMatchedDRBin0, "", true);
   PdfFile.AddPlot(HMatchedDRBin1, "", true);
   PdfFile.AddPlot(HMatchedDRBin0Rebin, "", true);
   PdfFile.AddPlot(HMatchedDRBin1Rebin, "", true);
   HMatchedDRBin0Rebin.SetMarkerStyle(20);
   HMatchedDRBin1Rebin.SetMarkerStyle(20);
   HMatchedDRBin0Rebin.SetMarkerSize(5);
   HMatchedDRBin1Rebin.SetMarkerSize(5);
   PdfFile.AddPlot(HMatchedDRBin0Rebin, "", true);
   PdfFile.AddPlot(HMatchedDRBin1Rebin, "", true);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void NormalizeHistogram(TH1D &H, int BinCount, double Bins[])
{
   double Integral = 0;
   for(int iB = 1; iB <= BinCount - 1; iB++)
      Integral = Integral + H.GetBinContent(iB);

   for(int iB = 1; iB <= BinCount; iB++)
   {
      double BinSize = Bins[iB] - Bins[iB-1];
      H.SetBinContent(iB, H.GetBinContent(iB) / BinSize / Integral);
      H.SetBinError(iB, H.GetBinError(iB) / BinSize / Integral);
   }
}

