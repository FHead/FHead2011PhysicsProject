#include <vector>
#include <string>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper2.h"

void MakePlots()
{
   TH1D HMR_R025MR150("HMR_R025MR150", "MR, Passing R025/MR150 trigger;MR", 20, 0, 1500);
   TH1D HMR_R025MR400("HMR_R025MR400", "MR, Passing R025/MR400 trigger;MR", 20, 0, 1500);
   TH1D HMR_R025MR450("HMR_R025MR450", "MR, Passing R025/MR450 trigger;MR", 20, 0, 1500);
   TH1D HR_R025MR150("HR_R025MR150", "R, Passing R025/MR150 trigger;R", 20, 0, 0.8);
   TH1D HMR_R014MR450BTag("HMR_R014MR450BTag", "MR, Passing R014/MR450/BTag trigger;MR", 20, 0, 1500);
   TH1D HR_R014MR450BTag("HR_R014MR450BTag", "R, Passing R014/MR450/BTag trigger;R", 20, 0, 0.8);
   
   TGraph GMRVsR_R025MR150, GMRVsR_R014MR450BTag;
   GMRVsR_R025MR150.SetNameTitle("GMRVsR_R025MR150", "MR vs. R, passing R025/MR150 trigger");
   GMRVsR_R014MR450BTag.SetNameTitle("GMRVsR_R014MR450BTag", "MR vs. R, passing R014/MR450/BTag trigger");

   TFile F("YayTriggers.root");
   TTree *Tree = (TTree *)F.Get("RazorBTriggerTree");

   bool R025MR150, R025MR400, R025MR450, R014MR450BTag;
   Tree->SetBranchAddress("R025MR150", &R025MR150);
   Tree->SetBranchAddress("R025MR400", &R025MR400);
   Tree->SetBranchAddress("R025MR450", &R025MR450);
   Tree->SetBranchAddress("R014MR450BTag", &R014MR450BTag);

   double R30, R40, R56, MR30, MR40, MR56;
   Tree->SetBranchAddress("R30", &R30);
   Tree->SetBranchAddress("R40", &R40);
   Tree->SetBranchAddress("R56", &R56);
   Tree->SetBranchAddress("MR30", &MR30);
   Tree->SetBranchAddress("MR40", &MR40);
   Tree->SetBranchAddress("MR56", &MR56);

   int GMRVsR_R025MR150_Count = 0;
   int GMRVsR_R014MR450BTag_Count = 0;
   
   int Entries = Tree->GetEntries();
   for(int i = 0; i < Entries; i++)
   {
      Tree->GetEntry(i);

      if(R025MR150 == true)
      {
         HMR_R025MR150.Fill(MR40);
         HR_R025MR150.Fill(R40);
         GMRVsR_R025MR150.SetPoint(GMRVsR_R025MR150_Count, MR40, R40);
         GMRVsR_R025MR150_Count = GMRVsR_R025MR150_Count + 1;
      }
      if(R025MR400 == true)
         HMR_R025MR400.Fill(MR40);
      if(R025MR450 == true)
         HMR_R025MR450.Fill(MR40);
      if(R014MR450BTag == true)
      {
         HMR_R014MR450BTag.Fill(MR40);
         HR_R014MR450BTag.Fill(R40);
         GMRVsR_R014MR450BTag.SetPoint(GMRVsR_R014MR450BTag_Count, MR40, R40);
         GMRVsR_R014MR450BTag_Count = GMRVsR_R014MR450BTag_Count + 1;
      }
   }

   PsFileHelper PsFile("RazorTriggerFirstLook.ps");
   PsFile.AddTextPage("First look at razor triggers with run 165121 (Yi)");

   vector<string> Explanation;
   Explanation.push_back("Private reco with 4_2_3 (prompt reco not yet out), HT dataset");
   Explanation.push_back("MR/R reconstructed using corrected calo jet, offline");
   Explanation.push_back("      - Group into hemispheres minimizing sum mass^2");
   Explanation.push_back("      - Basic calojet ID applied");
   Explanation.push_back("      - Eta range up to 3");
   Explanation.push_back("      - Jet PT > 40");
   Explanation.push_back("Unfortunately most jobs died, so statistics is a bit low");
   Explanation.push_back("      ....uh.....maybe more than a bit");
   Explanation.push_back("Wait for prompt reco tomorrow for a better look");
   PsFile.AddTextPage(Explanation);

   PsFile.AddTextPage("MR distributions for a few triggers");

   PsFile.AddPlot(HMR_R025MR150);
   PsFile.AddPlot(HMR_R025MR400);
   PsFile.AddPlot(HMR_R025MR450);

   TCanvas R025MR4XXCanvas;
   HMR_R025MR400.SetLineColor(1);
   HMR_R025MR450.SetLineColor(2);
   HMR_R025MR400.SetLineWidth(2);
   HMR_R025MR450.SetLineWidth(1);
   HMR_R025MR400.SetStats(0);
   HMR_R025MR450.SetStats(0);
   HMR_R025MR400.SetTitle("Comparison between events passing R025/MR400 and R025/MR450");
   HMR_R025MR400.Draw();
   HMR_R025MR450.Draw("same");
   TLegend R025MR4XXLegend(0.5, 0.8, 0.8, 0.6);
   R025MR4XXLegend.SetFillColor(0);
   R025MR4XXLegend.AddEntry(&HMR_R025MR400, "R025/MR400", "l");
   R025MR4XXLegend.AddEntry(&HMR_R025MR450, "R025/MR450", "l");
   R025MR4XXLegend.Draw();
   PsFile.AddCanvas(R025MR4XXCanvas);

   vector<string> MRExplanation;
   MRExplanation.push_back("Distribution in MR looks OK");
   MRExplanation.push_back("The turn-on is roughly where we want it to be");
   MRExplanation.push_back("No surprises in this side");
   PsFile.AddTextPage(MRExplanation);

   PsFile.AddTextPage("R distribution");
   PsFile.AddPlot(HR_R025MR150);
   GMRVsR_R025MR150.SetMarkerStyle(11);
   PsFile.AddPlot(GMRVsR_R025MR150, "ap");

   vector<string> RExplanation;
   RExplanation.push_back("R turn-on is bit lower than expected");
   RExplanation.push_back("As I was discussing with Chris earlier today,");
   RExplanation.push_back("      it might be the fact that offline selection is different than");
   RExplanation.push_back("      online (HLT), which then causes jets to wander in/out of the collection");
   RExplanation.push_back("I wouldn't say that this is too alarming -");
   RExplanation.push_back("but definitely something to take a better look tomorrow");
   RExplanation.push_back("");
   RExplanation.push_back("Overall things doesn't look crazy from this first look");
   PsFile.AddTextPage(RExplanation);

   PsFile.AddTextPage("Some extra plots with b-tagging paths");

   PsFile.AddPlot(HMR_R014MR450BTag);
   PsFile.AddPlot(HR_R014MR450BTag);
   GMRVsR_R014MR450BTag.SetMarkerStyle(11);
   PsFile.AddPlot(GMRVsR_R014MR450BTag, "ap");

   PsFile.AddTimeStampPage();
   PsFile.Close();
}




