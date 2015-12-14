#include <string>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TLegend.h"
#include "TFitResult.h"
#include "TGraphErrors.h"

#include "TauHelperFunctions.h" 
#include "PlotHelper2.h"
#include "ReadLQ3Tree.h"

struct ExponentialFitResult;
int main(int argc, char *argv[]);
void BackgroundMRDistribution(string InputFile, string OutputBase);
ExponentialFitResult FitExponential(TH1D *Histogram);

struct ExponentialFitResult
{
   double Exp;
   double ExpError;
};

int main(int argc, char *argv[])
{
   gROOT->SetStyle("Plain");

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle->SetNumberContours(NCont);

   string Tag = "TTJets_TuneD6T";
   if(argc > 1)
      Tag = argv[1];

   string InputFile = "Samples/" + Tag + ".root";
   string OutputBase = Tag;

   BackgroundMRDistribution(InputFile, OutputBase);
}

void BackgroundMRDistribution(string InputFile, string OutputBase)
{
   TFile F(InputFile.c_str());
   TTree *Tree = (TTree *)F.Get("LQ3Tree");

   if(Tree == NULL)   // tree non-existent
      return;

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage("Background plots for " + OutputBase + "");

   vector<string> TableOfContentItems;
   TableOfContentItems.push_back("Tree export sanity check plots - calo jets");
   TableOfContentItems.push_back("Tree export sanity check plots - PF jets");
   TableOfContentItems.push_back("Tree export sanity check plots - PV, MET");
   TableOfContentItems.push_back("MR, R from leading calo jets");
   TableOfContentItems.push_back("MR, R from leading PF jets");

   vector<string> Destinations;
   Destinations.push_back("BasicValidationPlotsCaloJets");
   Destinations.push_back("BasicValidationPlotsPFJets");
   Destinations.push_back("BasicValidationPlotsOthers");
   Destinations.push_back("CaloJetMR");
   Destinations.push_back("PFJetMR");

   PsFile.AddTableOfContentPage(TableOfContentItems, Destinations);
   PsFile.SetAutomaticHomeButton(true, "HomePage");
   PsFile.InsertNamedDestination("HomePage");

   TreeRecord M;
   M.SetBranchAddress(Tree);

   TH1D HCaloJetCount("HCaloJetCount", "Calo jet count", 20, -0.5, 19.5);
   TH1D HCaloJetCount30("HCaloJetCount30", "Calo jet count, PT > 30", 20, -0.5, 19.5);
   TH1D HCaloJetCount50("HCaloJetCount50", "Calo jet count, PT > 50", 20, -0.5, 19.5);
   TH1D HCaloJetCount100("HCaloJetCount100", "Calo jet count, PT > 100", 20, -0.5, 19.5);
   TH1D HLeadingCaloJetPT("HLeadingCaloJetPT", "Leading calo jet PT", 100, 0, 1000);
   TH1D HLeadingCaloJetEta("HLeadingCaloJetEta", "Leading calo jet eta", 100, -3, 3);
   TH1D HLeadingCaloJetPhi("HLeadingCaloJetPhi", "Leading calo jet phi", 100, -3.2, 3.2);
   TH1D HLeadingCaloJetCSVTag("HLeadingCaloJetCSVTag", "Leading calo jet CSV tag", 100, 0, 1);
   TH1D HLeadingCaloJetCSVMTag("HLeadingCaloJetCSVMTag", "Leading calo jet CSVM tag", 100, 0, 1);
   TH1D HLeadingCaloJetTCHPTag("HLeadingCaloJetTCHPTag", "Leading calo jet TCHP tag", 100, -5, 5);
   TH1D HLeadingCaloJetTCHETag("HLeadingCaloJetTCHETag", "Leading calo jet TCHE tag", 100, -5, 5);
   TH1D HSubLeadingCaloJetPT("HSubLeadingCaloJetPT", "Sub-leading calo jet PT", 100, 0, 1000);
   TH1D HSubLeadingCaloJetEta("HSubLeadingCaloJetEta", "Sub-leading calo jet eta", 100, -3, 3);
   TH1D HSubLeadingCaloJetPhi("HSubLeadingCaloJetPhi", "Sub-leading calo jet phi", 100, -3.2, 3.2);
   TH1D HSubLeadingCaloJetCSVTag("HSubLeadingCaloJetCSVTag", "Sub-leading calo jet CSV tag", 100, 0, 1);
   TH1D HSubLeadingCaloJetCSVMTag("HSubLeadingCaloJetCSVMTag", "Sub-leading calo jet CSVM tag", 100, 0, 1);
   TH1D HSubLeadingCaloJetTCHPTag("HSubLeadingCaloJetTCHPTag", "Sub-leading calo jet TCHP tag", 100, -5, 5);
   TH1D HSubLeadingCaloJetTCHETag("HSubLeadingCaloJetTCHETag", "Sub-leading calo jet TCHE tag", 100, -5, 5);
   TH2D HLeadingCaloJetsPTVsPT("HLeadingCaloJetsPTVsPT", "Leading calo jets PT;Leading PT;Sub-leading PT",
      100, 0, 1000, 100, 0, 1000);
   
   TH1D HPFJetCount("HPFJetCount", "PF jet count", 20, -0.5, 19.5);
   TH1D HPFJetCount30("HPFJetCount30", "PF jet count, PT > 30", 20, -0.5, 19.5);
   TH1D HPFJetCount50("HPFJetCount50", "PF jet count, PT > 50", 20, -0.5, 19.5);
   TH1D HPFJetCount100("HPFJetCount100", "PF jet count, PT > 100", 20, -0.5, 19.5);
   TH1D HLeadingPFJetPT("HLeadingPFJetPT", "Leading PF jet PT", 100, 0, 1000);
   TH1D HLeadingPFJetEta("HLeadingPFJetEta", "Leading PF jet eta", 100, -3, 3);
   TH1D HLeadingPFJetPhi("HLeadingPFJetPhi", "Leading PF jet phi", 100, -3.2, 3.2);
   TH1D HLeadingPFJetCSVTag("HLeadingPFJetCSVTag", "Leading PF jet CSV tag", 100, 0, 1);
   TH1D HLeadingPFJetCSVMTag("HLeadingPFJetCSVMTag", "Leading PF jet CSVM tag", 100, 0, 1);
   TH1D HLeadingPFJetTCHPTag("HLeadingPFJetTCHPTag", "Leading PF jet TCHP tag", 100, -5, 5);
   TH1D HLeadingPFJetTCHETag("HLeadingPFJetTCHETag", "Leading PF jet TCHE tag", 100, -5, 5);
   TH1D HSubLeadingPFJetPT("HSubLeadingPFJetPT", "Sub-leading PF jet PT", 100, 0, 1000);
   TH1D HSubLeadingPFJetEta("HSubLeadingPFJetEta", "Sub-leading PF jet eta", 100, -3, 3);
   TH1D HSubLeadingPFJetPhi("HSubLeadingPFJetPhi", "Sub-leading PF jet phi", 100, -3.2, 3.2);
   TH1D HSubLeadingPFJetCSVTag("HSubLeadingPFJetCSVTag", "Sub-leading PF jet CSV tag", 100, 0, 1);
   TH1D HSubLeadingPFJetCSVMTag("HSubLeadingPFJetCSVMTag", "Sub-leading PF jet CSVM tag", 100, 0, 1);
   TH1D HSubLeadingPFJetTCHPTag("HSubLeadingPFJetTCHPTag", "Sub-leading PF jet TCHP tag", 100, -5, 5);
   TH1D HSubLeadingPFJetTCHETag("HSubLeadingPFJetTCHETag", "Sub-leading PF jet TCHE tag", 100, -5, 5);
   TH2D HLeadingPFJetsPTVsPT("HLeadingPFJetsPTVsPT", "Leading PF jets PT;Leading PT;Sub-leading PT",
      100, 0, 1000, 100, 0, 1000);

   TH1D HPrimaryVertexCount("HPrimaryVertexCount", "Number of primary vertices", 20, -0.5, 19.5);
   TH1D HPrimaryVertexMaxSumPT("HPrimaryVertexMaxSumPT", "Max sum PT of primary vertices", 100, 0, 1000);

   TH1D HCaloMET("HCaloMET", "Calo MET", 100, 0, 1000);
   TH1D HCaloMETPhi("HCaloMETPhi", "Calo MET phi", 100, -3.2, 3.2);
   TH1D HPFMET("HPFMET", "PF MET", 100, 0, 1000);
   TH1D HPFMETPhi("HPFMETPhi", "PF MET phi", 100, -3.2, 3.2);

   TH1D HCaloJetMR("HCaloJetMR", "MR from leading two Calo jets", 100, 0, 1000);
   TH1D HCaloJetMRT("HCaloJetMRT", "MRT from leading two Calo jets", 100, 0, 1000);
   TH1D HCaloJetR("HCaloJetR", "R from leading two Calo jets", 100, 0, 2);
   TH2D HCaloJetMRVsR("HCaloJetMRVsR", "MR and R from leading two Calo jets;MR;R", 100, 0, 1000, 100, 0, 2);
   TH1D HCaloJetMR_R01("HCaloJetMR_R01", "MR from calo jets, R > 0.1", 100, 0, 1000);
   TH1D HCaloJetMR_R02("HCaloJetMR_R02", "MR from calo jets, R > 0.2", 100, 0, 1000);
   TH1D HCaloJetMR_R03("HCaloJetMR_R03", "MR from calo jets, R > 0.3", 100, 0, 1000);
   TH1D HCaloJetMR_R04("HCaloJetMR_R04", "MR from calo jets, R > 0.4", 100, 0, 1000);
   TH1D HCaloJetMR_R05("HCaloJetMR_R05", "MR from calo jets, R > 0.5", 100, 0, 1000);
   TH1D HCaloJetMR_R06("HCaloJetMR_R06", "MR from calo jets, R > 0.6", 100, 0, 1000);
   TH1D HCaloJetMR_R07("HCaloJetMR_R07", "MR from calo jets, R > 0.7", 100, 0, 1000);
   TH1D HCaloJetMR_R08("HCaloJetMR_R08", "MR from calo jets, R > 0.8", 100, 0, 1000);
   TH1D HCaloJetMR_R09("HCaloJetMR_R09", "MR from calo jets, R > 0.9", 100, 0, 1000);
   TGraphErrors GCaloMRSlopeVsRCut2;
   GCaloMRSlopeVsRCut2.SetNameTitle("GCaloMRSlopeVsRCut2", "Calo MR slope vs. (R cut)^{2}");
   GCaloMRSlopeVsRCut2.GetXaxis()->SetTitle("R Cut");
   GCaloMRSlopeVsRCut2.GetYaxis()->SetTitle("MR Slope");

   TH1D HCaloJetRCutEfficiency("HCaloJetRCutEfficiency", "R cut position vs. efficiency", 20, -0.5, 19.5);
   for(int i = 0; i < 20; i++)
      HCaloJetRCutEfficiency.GetXaxis()->SetBinLabel(i + 1, Form("%.02f", double(i) / 20));
   
   TH1D HPFJetMR("HPFJetMR", "MR from leading two PF jets", 100, 0, 1000);
   TH1D HPFJetMRT("HPFJetMRT", "MRT from leading two PF jets", 100, 0, 1000);
   TH1D HPFJetR("HPFJetR", "R from leading two PF jets", 100, 0, 2);
   TH2D HPFJetMRVsR("HPFJetMRVsR", "MR and R from leading two PF jets;MR;R", 100, 0, 1000, 100, 0, 2);
   TH1D HPFJetMR_R01("HPFJetMR_R01", "MR from PF jets, R > 0.1", 100, 0, 1000);
   TH1D HPFJetMR_R02("HPFJetMR_R02", "MR from PF jets, R > 0.2", 100, 0, 1000);
   TH1D HPFJetMR_R03("HPFJetMR_R03", "MR from PF jets, R > 0.3", 100, 0, 1000);
   TH1D HPFJetMR_R04("HPFJetMR_R04", "MR from PF jets, R > 0.4", 100, 0, 1000);
   TH1D HPFJetMR_R05("HPFJetMR_R05", "MR from PF jets, R > 0.5", 100, 0, 1000);
   TH1D HPFJetMR_R06("HPFJetMR_R06", "MR from PF jets, R > 0.6", 100, 0, 1000);
   TH1D HPFJetMR_R07("HPFJetMR_R07", "MR from PF jets, R > 0.7", 100, 0, 1000);
   TH1D HPFJetMR_R08("HPFJetMR_R08", "MR from PF jets, R > 0.8", 100, 0, 1000);
   TH1D HPFJetMR_R09("HPFJetMR_R09", "MR from PF jets, R > 0.9", 100, 0, 1000);
   TGraphErrors GPFMRSlopeVsRCut2;
   GPFMRSlopeVsRCut2.SetNameTitle("GPFMRSlopeVsRCut2", "PF MR slope vs. (R cut)^{2}");
   GPFMRSlopeVsRCut2.GetHistogram()->GetXaxis()->SetTitle("R Cut");
   GPFMRSlopeVsRCut2.GetHistogram()->GetYaxis()->SetTitle("MR Slope");

   TH1D HPFJetRCutEfficiency("HPFJetRCutEfficiency", "R cut position vs. efficiency", 20, -0.5, 19.5);
   for(int i = 0; i < 20; i++)
      HPFJetRCutEfficiency.GetXaxis()->SetBinLabel(i + 1, Form("%.02f", double(i) / 20));
   
   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if((iEntry + 1) % 500000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      Tree->GetEntry(iEntry);

      double LeadingCaloJetP[4] = {0, 0, 0, 0};
      double SubLeadingCaloJetP[4] = {0, 0, 0, 0};
      double CaloMETP[4] = {0, M.CaloMET[0], M.CaloMET[1], 0};
      CaloMETP[0] = GetP(CaloMETP);
      
      double CaloMR = -100;
      double CaloMRT = -100;
      double CaloR = -100;
      
      double LeadingPFJetP[4] = {0, 0, 0, 0};
      double SubLeadingPFJetP[4] = {0, 0, 0, 0};
      double PFMETP[4] = {0, M.PFMET[0], M.PFMET[1], 0};
      PFMETP[0] = GetP(PFMETP);

      double PFMR = -100;
      double PFMRT = -100;
      double PFR = -100;

      HCaloJetCount.Fill(M.CaloJetCount);
      HCaloJetCount30.Fill(M.CaloJetCount30);
      HCaloJetCount50.Fill(M.CaloJetCount50);
      HCaloJetCount100.Fill(M.CaloJetCount100);
      if(M.CaloJetCount >= 1)
      {
         HLeadingCaloJetPT.Fill(M.CaloJetPT[0]);
         HLeadingCaloJetEta.Fill(M.CaloJetEta[0]);
         HLeadingCaloJetPhi.Fill(M.CaloJetPhi[0]);
         HLeadingCaloJetCSVTag.Fill(M.CaloJetCSVTag[0]);
         HLeadingCaloJetCSVMTag.Fill(M.CaloJetCSVMTag[0]);
         HLeadingCaloJetTCHPTag.Fill(M.CaloJetTCHPTag[0]);
         HLeadingCaloJetTCHETag.Fill(M.CaloJetTCHETag[0]);
      }
      if(M.CaloJetCount >= 2)
      {
         HSubLeadingCaloJetPT.Fill(M.CaloJetPT[1]);
         HSubLeadingCaloJetEta.Fill(M.CaloJetEta[1]);
         HSubLeadingCaloJetPhi.Fill(M.CaloJetPhi[1]);
         HSubLeadingCaloJetCSVTag.Fill(M.CaloJetCSVTag[1]);
         HSubLeadingCaloJetCSVMTag.Fill(M.CaloJetCSVMTag[1]);
         HSubLeadingCaloJetTCHPTag.Fill(M.CaloJetTCHPTag[1]);
         HSubLeadingCaloJetTCHETag.Fill(M.CaloJetTCHETag[1]);
         HLeadingCaloJetsPTVsPT.Fill(M.CaloJetPT[0], M.CaloJetPT[1]);
      }
      
      HPFJetCount.Fill(M.PFJetCount);
      HPFJetCount30.Fill(M.PFJetCount30);
      HPFJetCount50.Fill(M.PFJetCount50);
      HPFJetCount100.Fill(M.PFJetCount100);
      if(M.PFJetCount >= 1)
      {
         HLeadingPFJetPT.Fill(M.PFJetPT[0]);
         HLeadingPFJetEta.Fill(M.PFJetEta[0]);
         HLeadingPFJetPhi.Fill(M.PFJetPhi[0]);
         HLeadingPFJetCSVTag.Fill(M.PFJetCSVTag[0]);
         HLeadingPFJetCSVMTag.Fill(M.PFJetCSVMTag[0]);
         HLeadingPFJetTCHPTag.Fill(M.PFJetTCHPTag[0]);
         HLeadingPFJetTCHETag.Fill(M.PFJetTCHETag[0]);
      }
      if(M.PFJetCount >= 2)
      {
         HSubLeadingPFJetPT.Fill(M.PFJetPT[1]);
         HSubLeadingPFJetEta.Fill(M.PFJetEta[1]);
         HSubLeadingPFJetPhi.Fill(M.PFJetPhi[1]);
         HSubLeadingPFJetCSVTag.Fill(M.PFJetCSVTag[1]);
         HSubLeadingPFJetCSVMTag.Fill(M.PFJetCSVMTag[1]);
         HSubLeadingPFJetTCHPTag.Fill(M.PFJetTCHPTag[1]);
         HSubLeadingPFJetTCHETag.Fill(M.PFJetTCHETag[1]);
         HLeadingPFJetsPTVsPT.Fill(M.PFJetPT[0], M.PFJetPT[1]);
      }

      HPrimaryVertexCount.Fill(M.PrimaryVertexCount);
      HPrimaryVertexMaxSumPT.Fill(M.PrimaryVertexMaxSumPT);

      HCaloMET.Fill(GetPT(CaloMETP));
      HCaloMETPhi.Fill(GetPhi(CaloMETP));
      HPFMET.Fill(GetPT(PFMETP));
      HPFMETPhi.Fill(GetPhi(PFMETP));

      if(M.CaloJetCount >= 1)
      {
         LeadingCaloJetP[0] = M.CaloJetPT[0] * cosh(M.CaloJetEta[0]);
         LeadingCaloJetP[1] = M.CaloJetPT[0] * cos(M.CaloJetPhi[0]);
         LeadingCaloJetP[2] = M.CaloJetPT[0] * sin(M.CaloJetPhi[0]);
         LeadingCaloJetP[3] = M.CaloJetPT[0] * sinh(M.CaloJetEta[0]);
      }
      if(M.CaloJetCount >= 2)
      {
         SubLeadingCaloJetP[0] = M.CaloJetPT[1] * cosh(M.CaloJetEta[1]);
         SubLeadingCaloJetP[1] = M.CaloJetPT[1] * cos(M.CaloJetPhi[1]);
         SubLeadingCaloJetP[2] = M.CaloJetPT[1] * sin(M.CaloJetPhi[1]);
         SubLeadingCaloJetP[3] = M.CaloJetPT[1] * sinh(M.CaloJetEta[1]);
      }

      if(M.CaloJetCount >= 2)
      {
         CaloMR = GetMR(LeadingCaloJetP, SubLeadingCaloJetP);
         CaloMRT = GetMRT(LeadingCaloJetP, SubLeadingCaloJetP, CaloMETP);
         CaloR = GetR(LeadingCaloJetP, SubLeadingCaloJetP, CaloMETP);

         HCaloJetMR.Fill(CaloMR);
         HCaloJetMRT.Fill(CaloMRT);
         HCaloJetR.Fill(CaloR);
         HCaloJetMRVsR.Fill(CaloMR, CaloR);

         if(CaloR > 0.1)   HCaloJetMR_R01.Fill(CaloMR);
         if(CaloR > 0.2)   HCaloJetMR_R02.Fill(CaloMR);
         if(CaloR > 0.3)   HCaloJetMR_R03.Fill(CaloMR);
         if(CaloR > 0.4)   HCaloJetMR_R04.Fill(CaloMR);
         if(CaloR > 0.5)   HCaloJetMR_R05.Fill(CaloMR);
         if(CaloR > 0.6)   HCaloJetMR_R06.Fill(CaloMR);
         if(CaloR > 0.7)   HCaloJetMR_R07.Fill(CaloMR);
         if(CaloR > 0.8)   HCaloJetMR_R08.Fill(CaloMR);
         if(CaloR > 0.9)   HCaloJetMR_R09.Fill(CaloMR);

         for(int i = 0; i < 20; i++)
            if(CaloR > double(i) / 20)
               HCaloJetRCutEfficiency.Fill(i);
      }
      
      if(M.PFJetCount >= 1)
      {
         LeadingPFJetP[0] = M.PFJetPT[0] * cosh(M.PFJetEta[0]);
         LeadingPFJetP[1] = M.PFJetPT[0] * cos(M.PFJetPhi[0]);
         LeadingPFJetP[2] = M.PFJetPT[0] * sin(M.PFJetPhi[0]);
         LeadingPFJetP[3] = M.PFJetPT[0] * sinh(M.PFJetEta[0]);
      }
      if(M.PFJetCount >= 2)
      {
         SubLeadingPFJetP[0] = M.PFJetPT[1] * cosh(M.PFJetEta[1]);
         SubLeadingPFJetP[1] = M.PFJetPT[1] * cos(M.PFJetPhi[1]);
         SubLeadingPFJetP[2] = M.PFJetPT[1] * sin(M.PFJetPhi[1]);
         SubLeadingPFJetP[3] = M.PFJetPT[1] * sinh(M.PFJetEta[1]);
      }

      if(M.PFJetCount >= 2)
      {
         PFMR = GetMR(LeadingPFJetP, SubLeadingPFJetP);
         PFMRT = GetMRT(LeadingPFJetP, SubLeadingPFJetP, PFMETP);
         PFR = GetR(LeadingPFJetP, SubLeadingPFJetP, PFMETP);

         HPFJetMR.Fill(PFMR);
         HPFJetMRT.Fill(PFMRT);
         HPFJetR.Fill(PFR);
         HPFJetMRVsR.Fill(PFMR, PFR);

         if(PFR > 0.1)   HPFJetMR_R01.Fill(PFMR);
         if(PFR > 0.2)   HPFJetMR_R02.Fill(PFMR);
         if(PFR > 0.3)   HPFJetMR_R03.Fill(PFMR);
         if(PFR > 0.4)   HPFJetMR_R04.Fill(PFMR);
         if(PFR > 0.5)   HPFJetMR_R05.Fill(PFMR);
         if(PFR > 0.6)   HPFJetMR_R06.Fill(PFMR);
         if(PFR > 0.7)   HPFJetMR_R07.Fill(PFMR);
         if(PFR > 0.8)   HPFJetMR_R08.Fill(PFMR);
         if(PFR > 0.9)   HPFJetMR_R09.Fill(PFMR);
         
         for(int i = 0; i < 20; i++)
            if(PFR > double(i) / 20)
               HPFJetRCutEfficiency.Fill(i);
      }
   }

   // normalize efficiency plots
   double CaloJetNormalization = HCaloJetRCutEfficiency.GetBinContent(1);
   double PFJetNormalization = HPFJetRCutEfficiency.GetBinContent(1);
   for(int i = 0; i < 20; i++)
   {
      HCaloJetRCutEfficiency.SetBinContent(i + 1,
         HCaloJetRCutEfficiency.GetBinContent(i + 1) / CaloJetNormalization);
      HPFJetRCutEfficiency.SetBinContent(i + 1,
         HPFJetRCutEfficiency.GetBinContent(i + 1) / PFJetNormalization);
   }

   // fit MR plots
   ExponentialFitResult CaloJetResult = FitExponential(&HCaloJetMR);
   ExponentialFitResult CaloJetR01Result = FitExponential(&HCaloJetMR_R01);
   ExponentialFitResult CaloJetR02Result = FitExponential(&HCaloJetMR_R02);
   ExponentialFitResult CaloJetR03Result = FitExponential(&HCaloJetMR_R03);
   ExponentialFitResult CaloJetR04Result = FitExponential(&HCaloJetMR_R04);
   ExponentialFitResult CaloJetR05Result = FitExponential(&HCaloJetMR_R05);
   ExponentialFitResult CaloJetR06Result = FitExponential(&HCaloJetMR_R06);
   ExponentialFitResult CaloJetR07Result = FitExponential(&HCaloJetMR_R07);
   ExponentialFitResult CaloJetR08Result = FitExponential(&HCaloJetMR_R08);
   ExponentialFitResult CaloJetR09Result = FitExponential(&HCaloJetMR_R09);
   GCaloMRSlopeVsRCut2.SetPoint(0, -0.00001, CaloJetResult.Exp);
   GCaloMRSlopeVsRCut2.SetPoint(1, 0.01, CaloJetR01Result.Exp);
   GCaloMRSlopeVsRCut2.SetPoint(2, 0.04, CaloJetR02Result.Exp);
   GCaloMRSlopeVsRCut2.SetPoint(3, 0.09, CaloJetR03Result.Exp);
   GCaloMRSlopeVsRCut2.SetPoint(4, 0.16, CaloJetR04Result.Exp);
   GCaloMRSlopeVsRCut2.SetPoint(5, 0.25, CaloJetR05Result.Exp);
   GCaloMRSlopeVsRCut2.SetPoint(6, 0.36, CaloJetR06Result.Exp);
   GCaloMRSlopeVsRCut2.SetPoint(7, 0.49, CaloJetR07Result.Exp);
   GCaloMRSlopeVsRCut2.SetPoint(8, 0.64, CaloJetR08Result.Exp);
   GCaloMRSlopeVsRCut2.SetPoint(9, 0.81, CaloJetR09Result.Exp);
   GCaloMRSlopeVsRCut2.SetPointError(0, 0, CaloJetResult.ExpError);
   GCaloMRSlopeVsRCut2.SetPointError(1, 0, CaloJetR01Result.ExpError);
   GCaloMRSlopeVsRCut2.SetPointError(2, 0, CaloJetR02Result.ExpError);
   GCaloMRSlopeVsRCut2.SetPointError(3, 0, CaloJetR03Result.ExpError);
   GCaloMRSlopeVsRCut2.SetPointError(4, 0, CaloJetR04Result.ExpError);
   GCaloMRSlopeVsRCut2.SetPointError(5, 0, CaloJetR05Result.ExpError);
   GCaloMRSlopeVsRCut2.SetPointError(6, 0, CaloJetR06Result.ExpError);
   GCaloMRSlopeVsRCut2.SetPointError(7, 0, CaloJetR07Result.ExpError);
   GCaloMRSlopeVsRCut2.SetPointError(8, 0, CaloJetR08Result.ExpError);
   GCaloMRSlopeVsRCut2.SetPointError(9, 0, CaloJetR09Result.ExpError);
   
   ExponentialFitResult PFJetResult = FitExponential(&HPFJetMR);
   ExponentialFitResult PFJetR01Result = FitExponential(&HPFJetMR_R01);
   ExponentialFitResult PFJetR02Result = FitExponential(&HPFJetMR_R02);
   ExponentialFitResult PFJetR03Result = FitExponential(&HPFJetMR_R03);
   ExponentialFitResult PFJetR04Result = FitExponential(&HPFJetMR_R04);
   ExponentialFitResult PFJetR05Result = FitExponential(&HPFJetMR_R05);
   ExponentialFitResult PFJetR06Result = FitExponential(&HPFJetMR_R06);
   ExponentialFitResult PFJetR07Result = FitExponential(&HPFJetMR_R07);
   ExponentialFitResult PFJetR08Result = FitExponential(&HPFJetMR_R08);
   ExponentialFitResult PFJetR09Result = FitExponential(&HPFJetMR_R09);
   GPFMRSlopeVsRCut2.SetPoint(0, -0.00001, PFJetResult.Exp);
   GPFMRSlopeVsRCut2.SetPoint(1, 0.01, PFJetR01Result.Exp);
   GPFMRSlopeVsRCut2.SetPoint(2, 0.04, PFJetR02Result.Exp);
   GPFMRSlopeVsRCut2.SetPoint(3, 0.09, PFJetR03Result.Exp);
   GPFMRSlopeVsRCut2.SetPoint(4, 0.16, PFJetR04Result.Exp);
   GPFMRSlopeVsRCut2.SetPoint(5, 0.25, PFJetR05Result.Exp);
   GPFMRSlopeVsRCut2.SetPoint(6, 0.36, PFJetR06Result.Exp);
   GPFMRSlopeVsRCut2.SetPoint(7, 0.49, PFJetR07Result.Exp);
   GPFMRSlopeVsRCut2.SetPoint(8, 0.64, PFJetR08Result.Exp);
   GPFMRSlopeVsRCut2.SetPoint(9, 0.81, PFJetR09Result.Exp);
   GPFMRSlopeVsRCut2.SetPointError(0, 0, PFJetResult.ExpError);
   GPFMRSlopeVsRCut2.SetPointError(1, 0, PFJetR01Result.ExpError);
   GPFMRSlopeVsRCut2.SetPointError(2, 0, PFJetR02Result.ExpError);
   GPFMRSlopeVsRCut2.SetPointError(3, 0, PFJetR03Result.ExpError);
   GPFMRSlopeVsRCut2.SetPointError(4, 0, PFJetR04Result.ExpError);
   GPFMRSlopeVsRCut2.SetPointError(5, 0, PFJetR05Result.ExpError);
   GPFMRSlopeVsRCut2.SetPointError(6, 0, PFJetR06Result.ExpError);
   GPFMRSlopeVsRCut2.SetPointError(7, 0, PFJetR07Result.ExpError);
   GPFMRSlopeVsRCut2.SetPointError(8, 0, PFJetR08Result.ExpError);
   GPFMRSlopeVsRCut2.SetPointError(9, 0, PFJetR09Result.ExpError);

   // output histograms
   PsFile.AddTextPage("Basic plots to check tree exporting");
   PsFile.AddPlot(HCaloJetCount, "hist text0", true);
   PsFile.InsertNamedDestination("BasicValidationPlotsCaloJets");
   PsFile.AddPlot(HCaloJetCount30, "hist text0", true);
   PsFile.AddPlot(HCaloJetCount50, "hist text0", true);
   PsFile.AddPlot(HCaloJetCount100, "hist text0", true);
   PsFile.AddPlot(HLeadingCaloJetPT, "", true);
   PsFile.AddPlot(HLeadingCaloJetEta, "", true);
   PsFile.AddPlot(HLeadingCaloJetPhi, "", true);
   PsFile.AddPlot(HLeadingCaloJetCSVTag, "", true);
   PsFile.AddPlot(HLeadingCaloJetCSVMTag, "", true);
   PsFile.AddPlot(HLeadingCaloJetTCHPTag, "", true);
   PsFile.AddPlot(HLeadingCaloJetTCHETag, "", true);
   PsFile.AddPlot(HSubLeadingCaloJetPT, "", true);
   PsFile.AddPlot(HSubLeadingCaloJetEta, "", true);
   PsFile.AddPlot(HSubLeadingCaloJetPhi, "", true);
   PsFile.AddPlot(HSubLeadingCaloJetCSVTag, "", true);
   PsFile.AddPlot(HSubLeadingCaloJetCSVMTag, "", true);
   PsFile.AddPlot(HSubLeadingCaloJetTCHPTag, "", true);
   PsFile.AddPlot(HSubLeadingCaloJetTCHETag, "", true);
   PsFile.AddPlot(HLeadingCaloJetsPTVsPT, "colz", false);
   PsFile.AddPlot(HPFJetCount, "hist text0", true);
   PsFile.InsertNamedDestination("BasicValidationPlotsPFJets");
   PsFile.AddPlot(HPFJetCount30, "hist text0", true);
   PsFile.AddPlot(HPFJetCount50, "hist text0", true);
   PsFile.AddPlot(HPFJetCount100, "hist text0", true);
   PsFile.AddPlot(HLeadingPFJetPT, "", true);
   PsFile.AddPlot(HLeadingPFJetEta, "", true);
   PsFile.AddPlot(HLeadingPFJetPhi, "", true);
   PsFile.AddPlot(HLeadingPFJetCSVTag, "", true);
   PsFile.AddPlot(HLeadingPFJetCSVMTag, "", true);
   PsFile.AddPlot(HLeadingPFJetTCHPTag, "", true);
   PsFile.AddPlot(HLeadingPFJetTCHETag, "", true);
   PsFile.AddPlot(HSubLeadingPFJetPT, "", true);
   PsFile.AddPlot(HSubLeadingPFJetEta, "", true);
   PsFile.AddPlot(HSubLeadingPFJetPhi, "", true);
   PsFile.AddPlot(HSubLeadingPFJetCSVTag, "", true);
   PsFile.AddPlot(HSubLeadingPFJetCSVMTag, "", true);
   PsFile.AddPlot(HSubLeadingPFJetTCHPTag, "", true);
   PsFile.AddPlot(HSubLeadingPFJetTCHETag, "", true);
   PsFile.AddPlot(HLeadingPFJetsPTVsPT, "colz", false);
   PsFile.AddPlot(HPrimaryVertexCount, "text0 hist", true);
   PsFile.InsertNamedDestination("BasicValidationPlotsOthers");
   PsFile.AddPlot(HPrimaryVertexMaxSumPT, "", true);
   PsFile.AddPlot(HCaloMET, "", true);
   PsFile.AddPlot(HCaloMETPhi, "", false);
   PsFile.AddPlot(HPFMET, "", true);
   PsFile.AddPlot(HPFMETPhi, "", false);

   PsFile.AddTextPage("Calo Jet MR");
   PsFile.InsertNamedDestination("CaloJetMR");
   PsFile.AddPlot(HCaloJetMR, "hist", true);
   PsFile.AddPlot(HCaloJetMRT, "", true);
   PsFile.AddPlot(HCaloJetR, "", true);
   PsFile.AddPlot(HCaloJetMRVsR, "colz", false);

   TCanvas CaloMRCanvas;
   HCaloJetMR.SetStats(0);
   HCaloJetMR.SetLineColor(1);       HCaloJetMR.Draw("hist");
   HCaloJetMR_R01.SetLineColor(2);   HCaloJetMR_R01.Draw("hist same");
   HCaloJetMR_R02.SetLineColor(3);   HCaloJetMR_R02.Draw("hist same");
   HCaloJetMR_R03.SetLineColor(4);   HCaloJetMR_R03.Draw("hist same");
   HCaloJetMR_R04.SetLineColor(5);   HCaloJetMR_R04.Draw("hist same");
   HCaloJetMR_R05.SetLineColor(6);   HCaloJetMR_R05.Draw("hist same");
   HCaloJetMR_R06.SetLineColor(7);   HCaloJetMR_R06.Draw("hist same");
   HCaloJetMR_R07.SetLineColor(8);   HCaloJetMR_R07.Draw("hist same");
   HCaloJetMR_R08.SetLineColor(9);   HCaloJetMR_R08.Draw("hist same");
   HCaloJetMR_R09.SetLineColor(1);   HCaloJetMR_R09.Draw("hist same");
   CaloMRCanvas.SetLogy();

   TLegend CaloMRLegend(0.8, 0.95, 0.95, 0.55);
   CaloMRLegend.AddEntry(&HCaloJetMR, "No cut", "l");
   CaloMRLegend.AddEntry(&HCaloJetMR_R01, "R > 0.1", "l");
   CaloMRLegend.AddEntry(&HCaloJetMR_R02, "R > 0.2", "l");
   CaloMRLegend.AddEntry(&HCaloJetMR_R03, "R > 0.3", "l");
   CaloMRLegend.AddEntry(&HCaloJetMR_R04, "R > 0.4", "l");
   CaloMRLegend.AddEntry(&HCaloJetMR_R05, "R > 0.5", "l");
   CaloMRLegend.AddEntry(&HCaloJetMR_R06, "R > 0.6", "l");
   CaloMRLegend.AddEntry(&HCaloJetMR_R07, "R > 0.7", "l");
   CaloMRLegend.AddEntry(&HCaloJetMR_R08, "R > 0.8", "l");
   CaloMRLegend.AddEntry(&HCaloJetMR_R09, "R > 0.9", "l");
   CaloMRLegend.SetFillColor(0);
   CaloMRLegend.Draw();

   PsFile.AddCanvas(CaloMRCanvas);

   HCaloJetRCutEfficiency.SetStats(0);
   PsFile.AddPlot(HCaloJetRCutEfficiency, "text0 hist", true);
   PsFile.AddPlot(GCaloMRSlopeVsRCut2, "ap");
   
   PsFile.AddTextPage("PF Jet MR");
   PsFile.InsertNamedDestination("PFJetMR");
   PsFile.AddPlot(HPFJetMR, "hist ", true);
   PsFile.AddPlot(HPFJetMRT, "", true);
   PsFile.AddPlot(HPFJetR, "", true);
   PsFile.AddPlot(HPFJetMRVsR, "colz", false);

   TCanvas PFMRCanvas;
   HPFJetMR.SetStats(0);
   HPFJetMR.SetLineColor(1);       HPFJetMR.Draw("hist");
   HPFJetMR_R01.SetLineColor(2);   HPFJetMR_R01.Draw("hist same");
   HPFJetMR_R02.SetLineColor(3);   HPFJetMR_R02.Draw("hist same");
   HPFJetMR_R03.SetLineColor(4);   HPFJetMR_R03.Draw("hist same");
   HPFJetMR_R04.SetLineColor(5);   HPFJetMR_R04.Draw("hist same");
   HPFJetMR_R05.SetLineColor(6);   HPFJetMR_R05.Draw("hist same");
   HPFJetMR_R06.SetLineColor(7);   HPFJetMR_R06.Draw("hist same");
   HPFJetMR_R07.SetLineColor(8);   HPFJetMR_R07.Draw("hist same");
   HPFJetMR_R08.SetLineColor(9);   HPFJetMR_R08.Draw("hist same");
   HPFJetMR_R09.SetLineColor(1);   HPFJetMR_R09.Draw("hist same");
   PFMRCanvas.SetLogy();
   
   TLegend PFMRLegend(0.8, 0.95, 0.95, 0.55);
   PFMRLegend.AddEntry(&HPFJetMR, "No cut", "l");
   PFMRLegend.AddEntry(&HPFJetMR_R01, "R > 0.1", "l");
   PFMRLegend.AddEntry(&HPFJetMR_R02, "R > 0.2", "l");
   PFMRLegend.AddEntry(&HPFJetMR_R03, "R > 0.3", "l");
   PFMRLegend.AddEntry(&HPFJetMR_R04, "R > 0.4", "l");
   PFMRLegend.AddEntry(&HPFJetMR_R05, "R > 0.5", "l");
   PFMRLegend.AddEntry(&HPFJetMR_R06, "R > 0.6", "l");
   PFMRLegend.AddEntry(&HPFJetMR_R07, "R > 0.7", "l");
   PFMRLegend.AddEntry(&HPFJetMR_R08, "R > 0.8", "l");
   PFMRLegend.AddEntry(&HPFJetMR_R09, "R > 0.9", "l");
   PFMRLegend.SetFillColor(0);
   PFMRLegend.Draw();

   PsFile.AddCanvas(PFMRCanvas);
   
   HPFJetRCutEfficiency.SetStats(0);
   PsFile.AddPlot(HPFJetRCutEfficiency, "text0 hist", true);
   PsFile.AddPlot(GPFMRSlopeVsRCut2, "ap");
   
   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}

ExponentialFitResult FitExponential(TH1D *Histogram)
{
   ExponentialFitResult result;
   result.Exp = 0;
   result.ExpError = 0;

   int MaxBin = 1;
   double MaxValue = Histogram->GetBinContent(1);
   for(int i = 2; i <= Histogram->GetNbinsX(); i++)
   {
      if(MaxValue < Histogram->GetBinContent(i))
      {
         MaxBin = i;
         MaxValue = Histogram->GetBinContent(i);
      }
   }

   int StartBin = -1;
   double TargetValue = MaxValue / 3;
   for(int i = MaxBin; i <= Histogram->GetNbinsX(); i++)
   {
      if(Histogram->GetBinContent(i) <= TargetValue)
      {
         StartBin = i;
         break;
      }
   }

   if(StartBin <= MaxBin)   // something is terribly wrong
      return result;

   if(Histogram->Integral(StartBin, Histogram->GetNbinsX()) < 10)
      return result;

   TFitResultPtr Pointer = Histogram->Fit("expo", "S", "", Histogram->GetBinCenter(StartBin),
      Histogram->GetBinCenter(Histogram->GetNbinsX()));

   result.Exp = Pointer->Parameter(1);
   result.ExpError = Pointer->ParError(1);

   return result;
}





