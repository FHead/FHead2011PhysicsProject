#include <string>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper2.h"

int main()
{
   gROOT->SetStyle("Plain");
   gStyle->SetPalette(1);

   TFile F("YayTriggers.root");
   TTree *Tree = (TTree *)F.Get("RazorBTriggerTree");
   if(Tree == NULL)
      return -1;

   double R40, MR40;
   Tree->SetBranchAddress("R40", &R40);
   Tree->SetBranchAddress("MR40", &MR40);

   bool R025MR150, R025MR450;
   Tree->SetBranchAddress("R025MR150", &R025MR150);
   Tree->SetBranchAddress("R025MR450", &R025MR450);

   int NumberOfGoodJets40;
   Tree->SetBranchAddress("NumberOfGoodJets40", &NumberOfGoodJets40);

   TH1D HMR("HMR", "MR distribution for all triggers", 100, 0, 1500);
   TH1D HR("HR", "R distribution for all triggers", 100, 0, 1);
   TH2D HMRVsR("HMRVsR", "MR vs. R;MR;R", 100, 0, 1500, 100, 0, 1);
   
   TH1D HMR_R025MR150("HMR_R025MR150", "MR distribution for triggers R025/MR150", 100, 0, 1500);
   TH1D HR_R025MR150("HR_R025MR150", "R distribution for trigger R025/MR150", 100, 0, 1);
   TH2D HMRVsR_R025MR150("HMRVsR_R025MR150", "MR vs. R for R025/MR150;MR;R", 100, 0, 1500, 100, 0, 1);

   TH1D HMR_R025MR450("HMR_R025MR450", "MR distribution for triggers R025/MR450", 100, 0, 1500);
   TH1D HR_R025MR450("HR_R025MR450", "R distribution for trigger R025/MR450", 100, 0, 1);
   TH2D HMRVsR_R025MR450("HMRVsR_R025MR450", "MR vs. R for R025/MR450;MR;R", 100, 0, 1500, 100, 0, 1);
   
   TH1D HMR_R025MR150_R025MR450("HMR_R025MR150_R025MR450",
      "MR distribution for triggers R025/MR150 R025/MR450", 100, 0, 1500);
   TH1D HR_R025MR150_R025MR450("HR_R025MR150_R025MR450",
      "R distribution for trigger R025/MR150 and R025/MR450", 100, 0, 1);
   TH2D HMRVsR_R025MR150_R025MR450("HMRVsR_R025MR150_R025MR450",
      "MR vs. R for R025/MR150 and R025_MR450;MR;R", 100, 0, 1500, 100, 0, 1);

   TH1D HMR_R025MR150_2Jet("HMR_R025MR150_2Jet", "MR distribution for triggers R025/MR150 (2 jet)", 100, 0, 1500);
   TH1D HR_R025MR150_2Jet("HR_R025MR150_2Jet", "R distribution for trigger R025/MR150 (2 jet)", 100, 0, 1);
   TH2D HMRVsR_R025MR150_2Jet("HMRVsR_R025MR150_2Jet", "MR vs. R for R025/MR150 (2 jet);MR;R", 100, 0, 1500, 100, 0, 1);

   TH1D HMR_R025MR450_2Jet("HMR_R025MR450_2Jet", "MR distribution for triggers R025/MR450 (2 jet)", 100, 0, 1500);
   TH1D HR_R025MR450_2Jet("HR_R025MR450_2Jet", "R distribution for trigger R025/MR450 (2 jet)", 100, 0, 1);
   TH2D HMRVsR_R025MR450_2Jet("HMRVsR_R025MR450_2Jet", "MR vs. R for R025/MR450 (2 jet);MR;R", 100, 0, 1500, 100, 0, 1);
   
   TH1D HMR_R025MR150_R025MR450_2Jet("HMR_R025MR150_R025MR450_2Jet",
      "MR distribution for triggers R025/MR150 R025/MR450 (2 jet)", 100, 0, 1500);
   TH1D HR_R025MR150_R025MR450_2Jet("HR_R025MR150_R025MR450_2Jet",
      "R distribution for trigger R025/MR150 and R025/MR450 (2 jet)", 100, 0, 1);
   TH2D HMRVsR_R025MR150_R025MR450_2Jet("HMRVsR_R025MR150_R025MR450_2Jet",
      "MR vs. R for R025/MR150 and R025_MR450 (2 jet);MR;R", 100, 0, 1500, 100, 0, 1);

   int EntryCount = Tree->GetEntries();
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree->GetEntry(iEntry);

      HMR.Fill(MR40);
      HR.Fill(R40);
      HMRVsR.Fill(MR40, R40);

      if(R025MR150 == true)
      {
         HMR_R025MR150.Fill(MR40);
         HR_R025MR150.Fill(R40);
         HMRVsR_R025MR150.Fill(MR40, R40);
      }
      
      if(R025MR450 == true)
      {
         HMR_R025MR450.Fill(MR40);
         HR_R025MR450.Fill(R40);
         HMRVsR_R025MR450.Fill(MR40, R40);
      }
      
      if(R025MR450 == true && R025MR150 == true)
      {
         HMR_R025MR150_R025MR450.Fill(MR40);
         HR_R025MR150_R025MR450.Fill(R40);
         HMRVsR_R025MR150_R025MR450.Fill(MR40, R40);
      }

      if(R025MR150 == true && NumberOfGoodJets40 == 2)
      {
         HMR_R025MR150_2Jet.Fill(MR40);
         HR_R025MR150_2Jet.Fill(R40);
         HMRVsR_R025MR150_2Jet.Fill(MR40, R40);
      }
      
      if(R025MR450 == true && NumberOfGoodJets40 == 2)
      {
         HMR_R025MR450_2Jet.Fill(MR40);
         HR_R025MR450_2Jet.Fill(R40);
         HMRVsR_R025MR450_2Jet.Fill(MR40, R40);
      }
      
      if(R025MR450 == true && R025MR150 == true && NumberOfGoodJets40 == 2)
      {
         HMR_R025MR150_R025MR450_2Jet.Fill(MR40);
         HR_R025MR150_R025MR450_2Jet.Fill(R40);
         HMRVsR_R025MR150_R025MR450_2Jet.Fill(MR40, R40);
      }
   }

   PsFileHelper PsFile("TriggerSanityCheck.ps");
   PsFile.AddTextPage("Trigger Sanity Check");

   PsFile.AddPlot(HMR, "", false);
   PsFile.AddPlot(HR, "", false);
   PsFile.AddPlot(HMRVsR, "colz", false, false);
   
   PsFile.AddPlot(HMR_R025MR150, "", false);
   PsFile.AddPlot(HR_R025MR150, "", false);
   PsFile.AddPlot(HMRVsR_R025MR150, "colz", false, false);

   PsFile.AddPlot(HMR_R025MR450, "", false);
   PsFile.AddPlot(HR_R025MR450, "", false);
   PsFile.AddPlot(HMRVsR_R025MR450, "colz", false, false);

   PsFile.AddPlot(HMR_R025MR150_R025MR450, "", false);
   PsFile.AddPlot(HR_R025MR150_R025MR450, "", false);
   PsFile.AddPlot(HMRVsR_R025MR150_R025MR450, "colz", false, false);

   HMR_R025MR150.SetLineWidth(2);
   HMR_R025MR150.SetLineColor(1);
   HMR_R025MR150_R025MR450.SetLineWidth(1);
   HMR_R025MR150_R025MR450.SetLineColor(2);
   HR_R025MR150.SetLineWidth(2);
   HR_R025MR150.SetLineColor(1);
   HR_R025MR150_R025MR450.SetLineWidth(1);
   HR_R025MR150_R025MR450.SetLineColor(2);

   TLegend ComparisonLegend(0.5, 0.8, 0.8, 0.5);
   ComparisonLegend.AddEntry(&HMR_R025MR150, "Pass R025/MR150", "l");
   ComparisonLegend.AddEntry(&HMR_R025MR150_R025MR450, "Pass R025/MR150 and R025/MR450", "l");
   ComparisonLegend.SetFillColor(0);

   TCanvas MRComparisonCanvas;
   HMR_R025MR150.Draw();
   HMR_R025MR150_R025MR450.Draw("same");
   MRComparisonCanvas.SetLogy();
   ComparisonLegend.Draw();
   PsFile.AddCanvas(MRComparisonCanvas);

   TCanvas RComparisonCanvas;
   HR_R025MR150.Draw();
   HR_R025MR150_R025MR450.Draw("same");
   RComparisonCanvas.SetLogy();
   ComparisonLegend.Draw();
   PsFile.AddCanvas(RComparisonCanvas);

   PsFile.AddPlot(HMR_R025MR150_2Jet, "", false);
   PsFile.AddPlot(HR_R025MR150_2Jet, "", false);
   PsFile.AddPlot(HMRVsR_R025MR150_2Jet, "colz", false, false);

   PsFile.AddPlot(HMR_R025MR450_2Jet, "", false);
   PsFile.AddPlot(HR_R025MR450_2Jet, "", false);
   PsFile.AddPlot(HMRVsR_R025MR450_2Jet, "colz", false, false);

   PsFile.AddPlot(HMR_R025MR150_R025MR450_2Jet, "", false);
   PsFile.AddPlot(HR_R025MR150_R025MR450_2Jet, "", false);
   PsFile.AddPlot(HMRVsR_R025MR150_R025MR450_2Jet, "colz", false, false);

   HMR_R025MR150_2Jet.SetLineWidth(2);
   HMR_R025MR150_2Jet.SetLineColor(1);
   HMR_R025MR150_R025MR450_2Jet.SetLineWidth(1);
   HMR_R025MR150_R025MR450_2Jet.SetLineColor(2);
   HR_R025MR150_2Jet.SetLineWidth(2);
   HR_R025MR150_2Jet.SetLineColor(1);
   HR_R025MR150_R025MR450_2Jet.SetLineWidth(1);
   HR_R025MR150_R025MR450_2Jet.SetLineColor(2);

   TCanvas MRComparisonCanvas_2Jet;
   HMR_R025MR150_2Jet.Draw();
   HMR_R025MR150_R025MR450_2Jet.Draw("same");
   MRComparisonCanvas_2Jet.SetLogy();
   ComparisonLegend.Draw();
   PsFile.AddCanvas(MRComparisonCanvas_2Jet);

   TCanvas RComparisonCanvas_2Jet;
   HR_R025MR150_2Jet.Draw();
   HR_R025MR150_R025MR450_2Jet.Draw("same");
   RComparisonCanvas_2Jet.SetLogy();
   ComparisonLegend.Draw();
   PsFile.AddCanvas(RComparisonCanvas_2Jet);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();

   return 0;
}





