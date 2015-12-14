//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
//---------------------------------------------------------------------------
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TColor.h"
#include "TStyle.h"
//---------------------------------------------------------------------------
#include "PlotHelper.h"
//---------------------------------------------------------------------------
struct SampleRecord;
class EventIndex;
void GenerateTable();
void PlotRelativeYieldTable(TFile &F, PsFileHelper &File, vector<SampleRecord> &Records,
   double Luminosity = 10, string title = "", string JetFlavor = "");
void PlotAbsoluteYieldTable(TFile &F, PsFileHelper &File, vector<SampleRecord> &Records,
   double Luminosity = 10, string title = "", string JetFlavor = "");
SampleRecord ReadSample(string RootFile, string Name, double CrossSection, string JetFlavor);
//---------------------------------------------------------------------------
struct SampleRecord
{
public:
   double EffectiveCrossSection;   // in pb
   string Name;
public:   // count events
   int AllEvents;
   int PassHLT;
   int TwoMuons;
   int TwoGlobalMuons;
   int TwoGlobalPixelHit;
   int TwoGlobalTrackingHit;
   int TwoGlobalAllHit;
   int TwoMuonsPassingMuonID;
   int TwoMuonsPassingIsolation;
   int ZCandidateKinematics;   // muon pt and direction
   int InclusiveCaloJet[6];   // >= 1-6 jets
};
//---------------------------------------------------------------------------
void GenerateTable()
{
   TStyle gStyle;
   gStyle.SetPaintTextFormat("4.1g");
   gStyle.SetPalette(1);
   gStyle.SetPaperSize(26, 20);

   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle.SetNumberContours(NCont);

   vector<string> JetFlavors;
   JetFlavors.push_back("Calo");
   JetFlavors.push_back("UncorrectedCalo");
   JetFlavors.push_back("PF");
   JetFlavors.push_back("Track");

   vector<SampleRecord> Records[4];

   for(unsigned int i = 0; i < JetFlavors.size(); i++)
   {
      Records[i].push_back(ReadSample("Samples/ZJetsAll.root", "ZJets", 1013, JetFlavors[i]));
      Records[i].push_back(ReadSample("Samples/WJetsAll.root", "WJets", 24170, JetFlavors[i]));
      Records[i].push_back(ReadSample("Samples/TTbarAll.root", "TTbar", 95, JetFlavors[i]));
      Records[i].push_back(ReadSample("Samples/QDCppMuMuXAll.root", "ppMuMuX",
         48000000000.0 * 0.0000112, JetFlavors[i]));
   }

   PsFileHelper PsFile("ResultTable.ps");
   TFile F("ResultTable.root", "RECREATE");

   char ch[1024] = "";

   for(unsigned int i = 0; i < JetFlavors.size(); i++)
   {
      PsFile.AddTextPage("Efficiency table, calo jet, 10/pb");

      sprintf(ch, "%s Jet Absolute Yield", JetFlavors[i].c_str());
      PlotAbsoluteYieldTable(F, PsFile, Records[i], 35.1, ch, JetFlavors[i]);
      
      sprintf(ch, "%s Jet Relative Yield -- the jet part is relative to events after selection", JetFlavors[i].c_str());
      PlotRelativeYieldTable(F, PsFile, Records[i], 35.1, ch, JetFlavors[i]);
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}
//---------------------------------------------------------------------------
void PlotRelativeYieldTable(TFile &F, PsFileHelper &File,
   vector<SampleRecord> &Records, double Luminosity, string title, string JetFlavor)
{
   F.cd();

   TH2D YieldTable(Form("HYieldTable_%s", JetFlavor.c_str()), title.c_str(),
         Records.size(), -0.5, Records.size() - 0.5, 18, -0.5, 17.5);

   YieldTable.GetYaxis()->SetBinLabel(18, "Effective sigma");

   YieldTable.GetYaxis()->SetBinLabel(17, "All Events");
   YieldTable.GetYaxis()->SetBinLabel(16, "HLT");
   YieldTable.GetYaxis()->SetBinLabel(15, "Two Muons");
   YieldTable.GetYaxis()->SetBinLabel(14, "Global Muons");
   YieldTable.GetYaxis()->SetBinLabel(13, "Pixel Hit");
   YieldTable.GetYaxis()->SetBinLabel(12, "Tracking Hit");
   YieldTable.GetYaxis()->SetBinLabel(11, "Valid Muon Hit");
   YieldTable.GetYaxis()->SetBinLabel(10, "Chi2");
   YieldTable.GetYaxis()->SetBinLabel(9, "Isolation");
   YieldTable.GetYaxis()->SetBinLabel(8, "Kinematics");

   YieldTable.GetYaxis()->SetBinLabel(7, "After selection");

   YieldTable.GetYaxis()->SetBinLabel(6, ">= 1 jet");
   YieldTable.GetYaxis()->SetBinLabel(5, ">= 2 jets");
   YieldTable.GetYaxis()->SetBinLabel(4, ">= 3 jets");
   YieldTable.GetYaxis()->SetBinLabel(3, ">= 4 jets");
   YieldTable.GetYaxis()->SetBinLabel(2, ">= 5 jets");
   YieldTable.GetYaxis()->SetBinLabel(1, ">= 6 jets");

   for(unsigned int i = 0; i < Records.size(); i++)
      YieldTable.GetXaxis()->SetBinLabel(i + 1, Records[i].Name.c_str());

   for(unsigned int i = 0; i < Records.size(); i++)
   {
      YieldTable.SetBinContent(i + 1, 18, Records[i].EffectiveCrossSection);
      YieldTable.SetBinError(i + 1, 18, 0);

      YieldTable.SetBinContent(i + 1, 17, Luminosity * Records[i].EffectiveCrossSection);
      YieldTable.SetBinError(i + 1, 17, 0);

      // YieldTable.SetBinContent(i + 1, 16, (double)Records[i].PassHLT / Records[i].AllEvents);
      YieldTable.SetBinContent(i + 1, 15, (double)Records[i].TwoMuons / Records[i].AllEvents);
      YieldTable.SetBinContent(i + 1, 14, (double)Records[i].TwoGlobalMuons / Records[i].TwoMuons);
      YieldTable.SetBinContent(i + 1, 13, (double)Records[i].TwoGlobalPixelHit / Records[i].TwoGlobalMuons);
      YieldTable.SetBinContent(i + 1, 12, (double)Records[i].TwoGlobalTrackingHit / Records[i].TwoGlobalPixelHit);
      YieldTable.SetBinContent(i + 1, 11, (double)Records[i].TwoGlobalAllHit / Records[i].TwoGlobalTrackingHit);
      YieldTable.SetBinContent(i + 1, 10, (double)Records[i].TwoMuonsPassingMuonID / Records[i].TwoGlobalAllHit);
      YieldTable.SetBinContent(i + 1, 9, (double)Records[i].TwoMuonsPassingIsolation / Records[i].TwoMuonsPassingMuonID);
      YieldTable.SetBinContent(i + 1, 8, (double)Records[i].ZCandidateKinematics / Records[i].TwoMuonsPassingIsolation);

      YieldTable.SetBinContent(i + 1, 7, (double)Records[i].ZCandidateKinematics / Records[i].AllEvents);
      
      YieldTable.SetBinContent(i + 1, 6, (double)Records[i].InclusiveCaloJet[0] / Records[i].ZCandidateKinematics);
      YieldTable.SetBinContent(i + 1, 5, (double)Records[i].InclusiveCaloJet[1] / Records[i].ZCandidateKinematics);
      YieldTable.SetBinContent(i + 1, 4, (double)Records[i].InclusiveCaloJet[2] / Records[i].ZCandidateKinematics);
      YieldTable.SetBinContent(i + 1, 3, (double)Records[i].InclusiveCaloJet[3] / Records[i].ZCandidateKinematics);
      YieldTable.SetBinContent(i + 1, 2, (double)Records[i].InclusiveCaloJet[4] / Records[i].ZCandidateKinematics);
      YieldTable.SetBinContent(i + 1, 1, (double)Records[i].InclusiveCaloJet[5] / Records[i].ZCandidateKinematics);
      
      // YieldTable.SetBinError(i + 1, 16, sqrt(1.0 / Records[i].PassHLT + 1.0 / Records[i].AllEvents) * Records[i].PassHLT / Records[i].AllEvents);
      YieldTable.SetBinError(i + 1, 15, sqrt(1.0 / Records[i].TwoMuons + 1.0 / Records[i].AllEvents) * Records[i].TwoMuons / Records[i].AllEvents);
      YieldTable.SetBinError(i + 1, 14, sqrt(1.0 / Records[i].TwoGlobalMuons + 1.0 / Records[i].TwoMuons) * Records[i].TwoGlobalMuons / Records[i].TwoMuons);
      YieldTable.SetBinError(i + 1, 13, sqrt(1.0 / Records[i].TwoGlobalPixelHit + 1.0 / Records[i].TwoGlobalMuons) * Records[i].TwoGlobalPixelHit / Records[i].TwoGlobalMuons);
      YieldTable.SetBinError(i + 1, 12, sqrt(1.0 / Records[i].TwoGlobalTrackingHit + 1.0 / Records[i].TwoGlobalPixelHit) * Records[i].TwoGlobalTrackingHit / Records[i].TwoGlobalPixelHit);
      YieldTable.SetBinError(i + 1, 11, sqrt(1.0 / Records[i].TwoGlobalAllHit + 1.0 / Records[i].TwoGlobalTrackingHit) * Records[i].TwoGlobalAllHit / Records[i].TwoGlobalTrackingHit);
      YieldTable.SetBinError(i + 1, 10, sqrt(1.0 / Records[i].TwoMuonsPassingMuonID + 1.0 / Records[i].TwoGlobalAllHit) * Records[i].TwoMuonsPassingMuonID / Records[i].TwoGlobalAllHit);
      YieldTable.SetBinError(i + 1, 9, sqrt(1.0 / Records[i].TwoMuonsPassingIsolation + 1.0 / Records[i].TwoMuonsPassingMuonID) * Records[i].TwoMuonsPassingIsolation / Records[i].TwoMuonsPassingMuonID);
      YieldTable.SetBinError(i + 1, 8, sqrt(1.0 / Records[i].ZCandidateKinematics + 1.0 / Records[i].TwoMuonsPassingIsolation) * Records[i].ZCandidateKinematics / Records[i].TwoMuonsPassingIsolation);

      YieldTable.SetBinError(i + 1, 7, sqrt(1.0 / Records[i].ZCandidateKinematics + 1.0 / Records[i].AllEvents) * Records[i].ZCandidateKinematics / Records[i].AllEvents);
      
      YieldTable.SetBinError(i + 1, 6, sqrt(1.0 / Records[i].InclusiveCaloJet[0] + 1.0 / Records[i].ZCandidateKinematics) * Records[i].InclusiveCaloJet[0] / Records[i].ZCandidateKinematics);
      YieldTable.SetBinError(i + 1, 5, sqrt(1.0 / Records[i].InclusiveCaloJet[1] + 1.0 / Records[i].ZCandidateKinematics) * Records[i].InclusiveCaloJet[1] / Records[i].ZCandidateKinematics);
      YieldTable.SetBinError(i + 1, 4, sqrt(1.0 / Records[i].InclusiveCaloJet[2] + 1.0 / Records[i].ZCandidateKinematics) * Records[i].InclusiveCaloJet[2] / Records[i].ZCandidateKinematics);
      YieldTable.SetBinError(i + 1, 3, sqrt(1.0 / Records[i].InclusiveCaloJet[3] + 1.0 / Records[i].ZCandidateKinematics) * Records[i].InclusiveCaloJet[3] / Records[i].ZCandidateKinematics);
      YieldTable.SetBinError(i + 1, 2, sqrt(1.0 / Records[i].InclusiveCaloJet[4] + 1.0 / Records[i].ZCandidateKinematics) * Records[i].InclusiveCaloJet[4] / Records[i].ZCandidateKinematics);
      YieldTable.SetBinError(i + 1, 1, sqrt(1.0 / Records[i].InclusiveCaloJet[5] + 1.0 / Records[i].ZCandidateKinematics) * Records[i].InclusiveCaloJet[5] / Records[i].ZCandidateKinematics);
   }

   TCanvas canvas;

   YieldTable.SetStats(0);
   YieldTable.Draw("text0e col");

   canvas.SetLeftMargin(0.2);
   canvas.SetLogz();

   File.AddCanvas(canvas);

   YieldTable.Write();
}
//---------------------------------------------------------------------------
void PlotAbsoluteYieldTable(TFile &F, PsFileHelper &File,
   vector<SampleRecord> &Records, double Luminosity, string title, string JetFlavor)
{
   F.cd();

   TH2D YieldTable(Form("HAbsoluteYieldTable_%s", JetFlavor.c_str()), title.c_str(),
      Records.size(), -0.5, Records.size() - 0.5, 18, -0.5, 17.5);

   YieldTable.GetYaxis()->SetBinLabel(18, "Effective sigma");

   YieldTable.GetYaxis()->SetBinLabel(17, "All Events");
   // YieldTable.GetYaxis()->SetBinLabel(16, "Pass HLT");
   YieldTable.GetYaxis()->SetBinLabel(15, "Two Muons");
   YieldTable.GetYaxis()->SetBinLabel(14, "Global Muons");
   YieldTable.GetYaxis()->SetBinLabel(13, "Pixel Hit");
   YieldTable.GetYaxis()->SetBinLabel(12, "Tracking Hit");
   YieldTable.GetYaxis()->SetBinLabel(11, "Valid Muon Hit");
   YieldTable.GetYaxis()->SetBinLabel(10, "Chi2");
   YieldTable.GetYaxis()->SetBinLabel(9, "Isolation");
   YieldTable.GetYaxis()->SetBinLabel(8, "Kinematics");

   YieldTable.GetYaxis()->SetBinLabel(7, "After selection");

   YieldTable.GetYaxis()->SetBinLabel(6, ">= 1 jet");
   YieldTable.GetYaxis()->SetBinLabel(5, ">= 2 jets");
   YieldTable.GetYaxis()->SetBinLabel(4, ">= 3 jets");
   YieldTable.GetYaxis()->SetBinLabel(3, ">= 4 jets");
   YieldTable.GetYaxis()->SetBinLabel(2, ">= 5 jets");
   YieldTable.GetYaxis()->SetBinLabel(1, ">= 6 jets");

   for(unsigned int i = 0; i < Records.size(); i++)
      YieldTable.GetXaxis()->SetBinLabel(i + 1, Records[i].Name.c_str());

   for(unsigned int i = 0; i < Records.size(); i++)
   {
      double Factor = Luminosity * Records[i].EffectiveCrossSection / Records[i].AllEvents;

      YieldTable.SetBinContent(i + 1, 18, Records[i].EffectiveCrossSection);
      YieldTable.SetBinContent(i + 1, 17, Luminosity * Records[i].EffectiveCrossSection);

      // YieldTable.SetBinContent(i + 1, 16, (double)Records[i].PassHLT * Factor);
      YieldTable.SetBinContent(i + 1, 15, (double)Records[i].TwoMuons * Factor);
      YieldTable.SetBinContent(i + 1, 14, (double)Records[i].TwoGlobalMuons * Factor);
      YieldTable.SetBinContent(i + 1, 13, (double)Records[i].TwoGlobalPixelHit * Factor);
      YieldTable.SetBinContent(i + 1, 12, (double)Records[i].TwoGlobalTrackingHit * Factor);
      YieldTable.SetBinContent(i + 1, 11, (double)Records[i].TwoGlobalAllHit * Factor);
      YieldTable.SetBinContent(i + 1, 10, (double)Records[i].TwoMuonsPassingMuonID * Factor);
      YieldTable.SetBinContent(i + 1, 9, (double)Records[i].TwoMuonsPassingIsolation * Factor);
      YieldTable.SetBinContent(i + 1, 8, (double)Records[i].ZCandidateKinematics * Factor);

      YieldTable.SetBinContent(i + 1, 7, (double)Records[i].ZCandidateKinematics * Factor);
      
      YieldTable.SetBinContent(i + 1, 6, (double)Records[i].InclusiveCaloJet[0] * Factor);
      YieldTable.SetBinContent(i + 1, 5, (double)Records[i].InclusiveCaloJet[1] * Factor);
      YieldTable.SetBinContent(i + 1, 4, (double)Records[i].InclusiveCaloJet[2] * Factor);
      YieldTable.SetBinContent(i + 1, 3, (double)Records[i].InclusiveCaloJet[3] * Factor);
      YieldTable.SetBinContent(i + 1, 2, (double)Records[i].InclusiveCaloJet[4] * Factor);
      YieldTable.SetBinContent(i + 1, 1, (double)Records[i].InclusiveCaloJet[5] * Factor);
   }

   TCanvas canvas;

   YieldTable.SetStats(0);
   YieldTable.Draw("text0 col");

   canvas.SetLeftMargin(0.2);
   canvas.SetLogz();

   File.AddCanvas(canvas);

   YieldTable.Write();
}
//---------------------------------------------------------------------------
SampleRecord ReadSample(string RootFile, string Name, double CrossSection, string JetFlavor)
{
   SampleRecord record;

   record.Name = Name;
   record.EffectiveCrossSection = CrossSection;

   TFile F(RootFile.c_str());

   // Fill stuff from the plot
   TH1D *CountEventsSelectionCaloJet = (TH1D *)F.Get(Form("CountEventsSelection%sJet0", JetFlavor.c_str()));

   if(CountEventsSelectionCaloJet == NULL)
   {
      cerr << "Warning!  Histogram not found!" << endl;
      return record;
   }

   record.AllEvents = CountEventsSelectionCaloJet->GetBinContent(1);
   record.PassHLT = CountEventsSelectionCaloJet->GetBinContent(2);
   record.TwoMuons = CountEventsSelectionCaloJet->GetBinContent(3);
   record.TwoGlobalMuons = CountEventsSelectionCaloJet->GetBinContent(4);
   record.TwoGlobalPixelHit = CountEventsSelectionCaloJet->GetBinContent(5);
   record.TwoGlobalTrackingHit = CountEventsSelectionCaloJet->GetBinContent(6);
   record.TwoGlobalAllHit = CountEventsSelectionCaloJet->GetBinContent(7);
   record.TwoMuonsPassingMuonID = CountEventsSelectionCaloJet->GetBinContent(8);
   record.TwoMuonsPassingIsolation = CountEventsSelectionCaloJet->GetBinContent(9);
   record.ZCandidateKinematics = CountEventsSelectionCaloJet->GetBinContent(10);

   for(int i = 0; i < 6; i++)
      record.InclusiveCaloJet[i] = CountEventsSelectionCaloJet->GetBinContent(11 + i);

   F.Close();

   return record;
}
//---------------------------------------------------------------------------





