#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

#include "TaggingEfficiencyHelper.h"

int main()
{
   SetStyle();

   TFile F("TCHELMistag.root");

   TaggingEfficiencyHelper Helper;
   Helper.Initialize(F, "HGoodJetPT", "HGoodJetPTPassTCHE",
      "HGoodJetEta", "HGoodJetEtaPassTCHE", "HGoodJetPTVsEta");

   PsFileHelper PsFile("EfficiencyClassBuilding.ps");
   PsFile.AddTextPage("Check efficiency helper code behavior!");

   TH1D HPTEfficiencyEta00("HPTEfficiencyEta00", "PT efficiency at eta 0.0", 100, 0, 500);
   TH1D HPTEfficiencyEta10("HPTEfficiencyEta10", "PT efficiency at eta 1.0", 100, 0, 500);
   TH1D HEtaEfficiencyPT50("HEtaEfficiencyPT50", "Eta efficiency at pt 50", 100, -3, 3);
   TH1D HEtaEfficiencyPT100("HEtaEfficiencyPT100", "Eta efficiency at pt 100", 100, -3, 3);
   TH1D HEtaEfficiencyPT200("HEtaEfficiencyPT200", "Eta efficiency at pt 200", 100, -3, 3);
   TH2D HEfficiencyPTVsEta("HEfficiecyPTVsEta", "Efficiency, PT vs. eta;PT;Eta", 100, 0, 500, 100, -3, 3);

   for(int i = 1; i <= HPTEfficiencyEta00.GetNbinsX(); i++)
      HPTEfficiencyEta00.SetBinContent(i, Helper.GetEfficiency(HPTEfficiencyEta00.GetBinCenter(i), 0.0));
   for(int i = 1; i <= HPTEfficiencyEta10.GetNbinsX(); i++)
      HPTEfficiencyEta10.SetBinContent(i, Helper.GetEfficiency(HPTEfficiencyEta10.GetBinCenter(i), 1.0));
   for(int i = 1; i <= HEtaEfficiencyPT50.GetNbinsX(); i++)
      HEtaEfficiencyPT50.SetBinContent(i, Helper.GetEfficiency(50, HEtaEfficiencyPT50.GetBinCenter(i)));
   for(int i = 1; i <= HEtaEfficiencyPT100.GetNbinsX(); i++)
      HEtaEfficiencyPT100.SetBinContent(i, Helper.GetEfficiency(100, HEtaEfficiencyPT100.GetBinCenter(i)));
   for(int i = 1; i <= HEtaEfficiencyPT200.GetNbinsX(); i++)
      HEtaEfficiencyPT200.SetBinContent(i, Helper.GetEfficiency(200, HEtaEfficiencyPT200.GetBinCenter(i)));
   for(int i = 1; i <= HEfficiencyPTVsEta.GetNbinsX(); i++)
      for(int j = 1; j <= HEfficiencyPTVsEta.GetNbinsY(); j++)
         HEfficiencyPTVsEta.SetBinContent(i, j,
            Helper.GetEfficiency(HEfficiencyPTVsEta.GetXaxis()->GetBinCenter(i),
            HEfficiencyPTVsEta.GetYaxis()->GetBinCenter(j)));

   PsFile.AddPlot(HPTEfficiencyEta00);
   PsFile.AddPlot(HPTEfficiencyEta10);
   PsFile.AddPlot(HEtaEfficiencyPT50);
   PsFile.AddPlot(HEtaEfficiencyPT100);
   PsFile.AddPlot(HEtaEfficiencyPT200);
   PsFile.AddPlot(HEfficiencyPTVsEta, "colz");

   vector<double> Efficiencies;
   Efficiencies.push_back(0.9);
   Efficiencies.push_back(0.89);
   Efficiencies.push_back(0.02);
   Efficiencies.push_back(0.05);
   cout << EventTaggedChance(Efficiencies, 1) << endl;
   cout << EventTaggedChance(Efficiencies, 2) << endl;

   Efficiencies.push_back(0);
   Efficiencies.push_back(0);
   cout << EventTaggedChance(Efficiencies, 1) << endl;
   cout << EventTaggedChance(Efficiencies, 2) << endl;
   
   Efficiencies.push_back(0.01);
   Efficiencies.push_back(0.01);
   Efficiencies.push_back(0.01);
   Efficiencies.push_back(0.01);
   cout << EventTaggedChance(Efficiencies, 1) << endl;
   cout << EventTaggedChance(Efficiencies, 2) << endl;

   F.Close();

   return 0;
}


