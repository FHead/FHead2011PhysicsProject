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
   double Luminosity = 10, string title = "");
void PlotAbsoluteYieldTable(TFile &F, PsFileHelper &File, vector<SampleRecord> &Records,
   double Luminosity = 10, string title = "");
SampleRecord ReadSample(string RootFile, string Name, double CrossSection, double DxyCut, double IsolationCut);
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
   int ZCandidateKinematics;   // muon pt and direction
   int ZCandidateAfterDxyCut;
   int ZCandidateAfterIsolationCut;
   int InclusiveCaloJet[6];   // >= 1-6 jets
};
//---------------------------------------------------------------------------
class EventIndex
{
public:
   int RunNumber;
   int EventNumber;
   int LumiSection;
public:
   EventIndex() {}
   ~EventIndex() {}
   bool operator <(const EventIndex &other) const;
   bool operator ==(const EventIndex &other) const;
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

   vector<SampleRecord> Records[3][3];

   vector<double> DxyCuts;
   DxyCuts.push_back(-1);
   DxyCuts.push_back(0.03);
   DxyCuts.push_back(0.015);

   vector<double> IsolationCuts;
   IsolationCuts.push_back(-1);
   IsolationCuts.push_back(0.3);
   IsolationCuts.push_back(0.15);

   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         Records[i][j].push_back(ReadSample("Samples/ZJetsAll.root", "ZJets", 800, DxyCuts[i], IsolationCuts[j]));
         Records[i][j].push_back(ReadSample("Samples/WJetsAll.root", "WJets", 24170, DxyCuts[i], IsolationCuts[j]));
         Records[i][j].push_back(ReadSample("Samples/TTbarAll.root", "TTbar", 95, DxyCuts[i], IsolationCuts[j]));
         Records[i][j].push_back(ReadSample("Samples/QDCppMuMuXAll.root", "ppMuMuX",
            48000000000.0 * 0.0000112, DxyCuts[i], IsolationCuts[j]));

         // cout << "DxyCut = " << DxyCuts[i] << ", IsolationCut = " << IsolationCuts[j] << endl;
         // PrintASCIITable(Records[i][j], 10);
      }
   }

   PsFileHelper File("ResultTable.ps");
   PsFileHelper File2("ResultTable2.ps");
   TFile F("ResultTable.root", "RECREATE");

   File.AddTextPage("Efficiency tables for a few dxy and isolation cuts, 10/pb");
   File2.AddTextPage("Efficiency tables, no dxy and isolation cuts, 10/pb");

   File.AddTextPage("Efficiency tables");
   File2.AddTextPage("Efficiency table");

   TH2D *JetMultiplicities[6];
   TH2D *JetMultiplicitiesBackground[6];

   for(int i = 0; i < 6; i++)
   {
      JetMultiplicities[i] = new TH2D(Form("SignalJet%d", i + 1),
         Form(">= %d CaloJet(s) for signal;dxy;relative Combined isolation", i + 1),
         3, -0.5, 2.5, 3, -0.5, 2.5);

      JetMultiplicities[i]->GetXaxis()->SetBinLabel(1, "No Cut");
      JetMultiplicities[i]->GetXaxis()->SetBinLabel(2, "Very Loose");
      JetMultiplicities[i]->GetXaxis()->SetBinLabel(3, "Loose");
      JetMultiplicities[i]->GetYaxis()->SetBinLabel(1, "No Cut");
      JetMultiplicities[i]->GetYaxis()->SetBinLabel(2, "Very Loose");
      JetMultiplicities[i]->GetYaxis()->SetBinLabel(3, "Loose");

      JetMultiplicitiesBackground[i] = new TH2D(Form("BackgroundJet%d", i + 1),
         Form(">= %d CaloJet(s) for backgrounds;dxy;Relative combined isolation", i + 1),
         3, -0.5, 2.5, 3, -0.5, 2.5);

      JetMultiplicitiesBackground[i]->GetXaxis()->SetBinLabel(1, "No Cut");
      JetMultiplicitiesBackground[i]->GetXaxis()->SetBinLabel(2, "Very Loose");
      JetMultiplicitiesBackground[i]->GetXaxis()->SetBinLabel(3, "Loose");
      JetMultiplicitiesBackground[i]->GetYaxis()->SetBinLabel(1, "No Cut");
      JetMultiplicitiesBackground[i]->GetYaxis()->SetBinLabel(2, "Very Loose");
      JetMultiplicitiesBackground[i]->GetYaxis()->SetBinLabel(3, "Loose");
   }

   char ch[1024];

   for(int j = 0; j < 3; j++)
   {
      for(int i = 0; i < 3; i++)
      {
         sprintf(ch, "CaloJet (DxyCut = %.3f, IsolationCut = %.2f)", DxyCuts[i], IsolationCuts[j]);
         PlotRelativeYieldTable(F, File, Records[i][j], 10, ch);

         if(i == 0 && j == 0)
         {
            sprintf(ch, "CaloJet Relative Yield -- the jet part is relative to events after selection", DxyCuts[i], IsolationCuts[j]);
            PlotRelativeYieldTable(F, File2, Records[i][j], 10, ch);
         }

         for(int k = 0; k < 6; k++)
         {
            double Factor = Records[i][j][0].EffectiveCrossSection * 10 / Records[i][j][0].AllEvents;
            JetMultiplicities[k]->SetBinContent(i + 1, j + 1,
               Records[i][j][0].InclusiveCaloJet[k] * Factor);
            JetMultiplicities[k]->SetBinError(i + 1, j + 1,
               sqrt(Records[i][j][0].InclusiveCaloJet[k]) * Factor);
         }

         for(int k = 0; k < 6; k++)
         {
            double TotalCount = 0;
            double ErrorSquared = 0;

            for(unsigned int l = 1; l < Records[i][j].size(); l++)
            {
               double Factor = Records[i][j][l].EffectiveCrossSection * 10 / Records[i][j][l].AllEvents;

               TotalCount = TotalCount + Records[i][j][l].InclusiveCaloJet[k] * Factor;
               ErrorSquared = ErrorSquared + Records[i][j][l].InclusiveCaloJet[k] * Factor * Factor;
            }

            JetMultiplicitiesBackground[k]->SetBinContent(i + 1, j + 1, TotalCount);
            JetMultiplicitiesBackground[k]->SetBinError(i + 1, j + 1, sqrt(ErrorSquared));
         }
      }
   }

   File.AddTextPage("Absolute Yield");
   File2.AddTextPage("Absolute Yield");

   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         sprintf(ch, "CaloJet (DxyCut = %.3f, IsolationCut = %.2f)", DxyCuts[i], IsolationCuts[j]);
         PlotAbsoluteYieldTable(F, File, Records[i][j], 10, ch);

         if(i == 0 && j == 0)
         {
            sprintf(ch, "CaloJets", DxyCuts[i], IsolationCuts[j]);
            PlotAbsoluteYieldTable(F, File2, Records[i][j], 10, ch);
         }
      }
   }

   File.AddTextPage("Signal yields");

   for(int i = 0; i < 6; i++)
   {
      JetMultiplicities[i]->SetMarkerSize(2.5);
      JetMultiplicities[i]->SetStats(0);

      File.AddPlot(JetMultiplicities[i], "text0e");
      JetMultiplicities[i]->Write();

      // TCanvas canvas;
      // JetMultiplicities[i]->Draw("text0e");
      // canvas.SaveAs(Form("%s.png", JetMultiplicities[i]->GetName()));
      // canvas.SaveAs(Form("%s.C", JetMultiplicities[i]->GetName()));
      // canvas.SaveAs(Form("%s.eps", JetMultiplicities[i]->GetName()));

      delete JetMultiplicities[i];
      JetMultiplicities[i] = NULL;
   }

   File.AddTextPage("Background yields");

   for(int i = 0; i < 6; i++)
   {
      JetMultiplicitiesBackground[i]->SetMarkerSize(2.5);
      JetMultiplicitiesBackground[i]->SetStats(0);

      File.AddPlot(JetMultiplicitiesBackground[i], "text0e");
      JetMultiplicitiesBackground[i]->Write();

      // TCanvas canvas;
      // JetMultiplicitiesBackground[i]->Draw("text0e");
      // canvas.SaveAs(Form("%s.png", JetMultiplicitiesBackground[i]->GetName()));
      // canvas.SaveAs(Form("%s.C", JetMultiplicitiesBackground[i]->GetName()));
      // canvas.SaveAs(Form("%s.eps", JetMultiplicitiesBackground[i]->GetName()));

      delete JetMultiplicitiesBackground[i];
      JetMultiplicitiesBackground[i] = NULL;
   }

   File.AddTimeStampPage();
   File2.AddTimeStampPage();

   F.Close();
   File.Close();
   File2.Close();
}
//---------------------------------------------------------------------------
void PlotRelativeYieldTable(TFile &F, PsFileHelper &File,
   vector<SampleRecord> &Records, double Luminosity, string title)
{
   static int Count = 0;
   TH2D YieldTable(Form("HYieldTable_%d", Count), title.c_str(),
      Records.size(), -0.5, Records.size() - 0.5, 19, -0.5, 18.5);
   Count = Count + 1;

   YieldTable.GetYaxis()->SetBinLabel(19, "Effective sigma");

   YieldTable.GetYaxis()->SetBinLabel(18, "All Events");
   YieldTable.GetYaxis()->SetBinLabel(17, "HLT");
   YieldTable.GetYaxis()->SetBinLabel(16, "Two Muons");
   YieldTable.GetYaxis()->SetBinLabel(15, "Global Muons");
   YieldTable.GetYaxis()->SetBinLabel(14, "Pixel Hit");
   YieldTable.GetYaxis()->SetBinLabel(13, "Tracking Hit");
   YieldTable.GetYaxis()->SetBinLabel(12, "Valid Muon Hit");
   YieldTable.GetYaxis()->SetBinLabel(11, "Chi2");
   YieldTable.GetYaxis()->SetBinLabel(10, "Kinematics");
   YieldTable.GetYaxis()->SetBinLabel(9, "Dxy");
   YieldTable.GetYaxis()->SetBinLabel(8, "Isolation");

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
      double Factor = 1;

      YieldTable.SetBinContent(i + 1, 19, Records[i].EffectiveCrossSection);
      YieldTable.SetBinError(i + 1, 19, 0);

      YieldTable.SetBinContent(i + 1, 18, Luminosity * Records[i].EffectiveCrossSection);
      YieldTable.SetBinError(i + 1, 18, 0);

      // YieldTable.SetBinContent(i + 1, 17, (double)Records[i].PassHLT / Records[i].AllEvents);
      YieldTable.SetBinContent(i + 1, 16, (double)Records[i].TwoMuons / Records[i].AllEvents);
      YieldTable.SetBinContent(i + 1, 15, (double)Records[i].TwoGlobalMuons / Records[i].TwoMuons);
      YieldTable.SetBinContent(i + 1, 14, (double)Records[i].TwoGlobalPixelHit / Records[i].TwoGlobalMuons);
      YieldTable.SetBinContent(i + 1, 13, (double)Records[i].TwoGlobalTrackingHit / Records[i].TwoGlobalPixelHit);
      YieldTable.SetBinContent(i + 1, 12, (double)Records[i].TwoGlobalAllHit / Records[i].TwoGlobalTrackingHit);
      YieldTable.SetBinContent(i + 1, 11, (double)Records[i].TwoMuonsPassingMuonID / Records[i].TwoGlobalAllHit);
      YieldTable.SetBinContent(i + 1, 10, (double)Records[i].ZCandidateKinematics / Records[i].TwoMuonsPassingMuonID);
      YieldTable.SetBinContent(i + 1, 9, (double)Records[i].ZCandidateAfterDxyCut / Records[i].ZCandidateKinematics);
      YieldTable.SetBinContent(i + 1, 8, (double)Records[i].ZCandidateAfterIsolationCut / Records[i].ZCandidateAfterDxyCut);

      YieldTable.SetBinContent(i + 1, 7, (double)Records[i].ZCandidateAfterIsolationCut / Records[i].AllEvents);
      
      YieldTable.SetBinContent(i + 1, 6, (double)Records[i].InclusiveCaloJet[0] / Records[i].ZCandidateAfterIsolationCut);
      YieldTable.SetBinContent(i + 1, 5, (double)Records[i].InclusiveCaloJet[1] / Records[i].ZCandidateAfterIsolationCut);
      YieldTable.SetBinContent(i + 1, 4, (double)Records[i].InclusiveCaloJet[2] / Records[i].ZCandidateAfterIsolationCut);
      YieldTable.SetBinContent(i + 1, 3, (double)Records[i].InclusiveCaloJet[3] / Records[i].ZCandidateAfterIsolationCut);
      YieldTable.SetBinContent(i + 1, 2, (double)Records[i].InclusiveCaloJet[4] / Records[i].ZCandidateAfterIsolationCut);
      YieldTable.SetBinContent(i + 1, 1, (double)Records[i].InclusiveCaloJet[5] / Records[i].ZCandidateAfterIsolationCut);
      
      // YieldTable.SetBinError(i + 1, 17, sqrt(1.0 / Records[i].PassHLT + 1.0 / Records[i].AllEvents) * Records[i].PassHLT / Records[i].AllEvents);
      YieldTable.SetBinError(i + 1, 16, sqrt(1.0 / Records[i].TwoMuons + 1.0 / Records[i].AllEvents) * Records[i].TwoMuons / Records[i].AllEvents);
      YieldTable.SetBinError(i + 1, 15, sqrt(1.0 / Records[i].TwoGlobalMuons + 1.0 / Records[i].TwoMuons) * Records[i].TwoGlobalMuons / Records[i].TwoMuons);
      YieldTable.SetBinError(i + 1, 14, sqrt(1.0 / Records[i].TwoGlobalPixelHit + 1.0 / Records[i].TwoGlobalMuons) * Records[i].TwoGlobalPixelHit / Records[i].TwoGlobalMuons);
      YieldTable.SetBinError(i + 1, 13, sqrt(1.0 / Records[i].TwoGlobalTrackingHit + 1.0 / Records[i].TwoGlobalPixelHit) * Records[i].TwoGlobalTrackingHit / Records[i].TwoGlobalPixelHit);
      YieldTable.SetBinError(i + 1, 12, sqrt(1.0 / Records[i].TwoGlobalAllHit + 1.0 / Records[i].TwoGlobalTrackingHit) * Records[i].TwoGlobalAllHit / Records[i].TwoGlobalTrackingHit);
      YieldTable.SetBinError(i + 1, 11, sqrt(1.0 / Records[i].TwoMuonsPassingMuonID + 1.0 / Records[i].TwoGlobalAllHit) * Records[i].TwoMuonsPassingMuonID / Records[i].TwoGlobalAllHit);
      YieldTable.SetBinError(i + 1, 10, sqrt(1.0 / Records[i].ZCandidateKinematics + 1.0 / Records[i].TwoMuonsPassingMuonID) * Records[i].ZCandidateKinematics / Records[i].TwoMuonsPassingMuonID);
      YieldTable.SetBinError(i + 1, 9, sqrt(1.0 / Records[i].ZCandidateAfterDxyCut + 1.0 / Records[i].ZCandidateKinematics) * Records[i].ZCandidateAfterDxyCut / Records[i].ZCandidateKinematics);
      YieldTable.SetBinError(i + 1, 8, sqrt(1.0 / Records[i].ZCandidateAfterIsolationCut + 1.0 / Records[i].ZCandidateAfterDxyCut) * Records[i].ZCandidateAfterIsolationCut / Records[i].ZCandidateAfterDxyCut);

      YieldTable.SetBinError(i + 1, 7, sqrt(1.0 / Records[i].ZCandidateAfterIsolationCut + 1.0 / Records[i].AllEvents) * Records[i].ZCandidateAfterIsolationCut / Records[i].AllEvents);
      
      YieldTable.SetBinError(i + 1, 6, sqrt(1.0 / Records[i].InclusiveCaloJet[0] + 1.0 / Records[i].ZCandidateAfterIsolationCut) * Records[i].InclusiveCaloJet[0] / Records[i].ZCandidateAfterIsolationCut);
      YieldTable.SetBinError(i + 1, 5, sqrt(1.0 / Records[i].InclusiveCaloJet[1] + 1.0 / Records[i].ZCandidateAfterIsolationCut) * Records[i].InclusiveCaloJet[1] / Records[i].ZCandidateAfterIsolationCut);
      YieldTable.SetBinError(i + 1, 4, sqrt(1.0 / Records[i].InclusiveCaloJet[2] + 1.0 / Records[i].ZCandidateAfterIsolationCut) * Records[i].InclusiveCaloJet[2] / Records[i].ZCandidateAfterIsolationCut);
      YieldTable.SetBinError(i + 1, 3, sqrt(1.0 / Records[i].InclusiveCaloJet[3] + 1.0 / Records[i].ZCandidateAfterIsolationCut) * Records[i].InclusiveCaloJet[3] / Records[i].ZCandidateAfterIsolationCut);
      YieldTable.SetBinError(i + 1, 2, sqrt(1.0 / Records[i].InclusiveCaloJet[4] + 1.0 / Records[i].ZCandidateAfterIsolationCut) * Records[i].InclusiveCaloJet[4] / Records[i].ZCandidateAfterIsolationCut);
      YieldTable.SetBinError(i + 1, 1, sqrt(1.0 / Records[i].InclusiveCaloJet[5] + 1.0 / Records[i].ZCandidateAfterIsolationCut) * Records[i].InclusiveCaloJet[5] / Records[i].ZCandidateAfterIsolationCut);
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
   vector<SampleRecord> &Records, double Luminosity, string title)
{
   static int Count = 0;
   TH2D YieldTable(Form("HAbsoluteYieldTable_%d", Count), title.c_str(),
      Records.size(), -0.5, Records.size() - 0.5, 19, -0.5, 18.5);
   Count = Count + 1;

   YieldTable.GetYaxis()->SetBinLabel(19, "Effective sigma");

   YieldTable.GetYaxis()->SetBinLabel(18, "All Events");
   YieldTable.GetYaxis()->SetBinLabel(17, "Pass HLT");
   YieldTable.GetYaxis()->SetBinLabel(16, "Two Muons");
   YieldTable.GetYaxis()->SetBinLabel(15, "Global Muons");
   YieldTable.GetYaxis()->SetBinLabel(14, "Pixel Hit");
   YieldTable.GetYaxis()->SetBinLabel(13, "Tracking Hit");
   YieldTable.GetYaxis()->SetBinLabel(12, "Valid Muon Hit");
   YieldTable.GetYaxis()->SetBinLabel(11, "Chi2");
   YieldTable.GetYaxis()->SetBinLabel(10, "Kinematics");
   YieldTable.GetYaxis()->SetBinLabel(9, "Dxy");
   YieldTable.GetYaxis()->SetBinLabel(8, "Isolation");

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

      YieldTable.SetBinContent(i + 1, 19, Records[i].EffectiveCrossSection);
      YieldTable.SetBinContent(i + 1, 18, Luminosity * Records[i].EffectiveCrossSection);

      YieldTable.SetBinContent(i + 1, 17, (double)Records[i].PassHLT * Factor);
      YieldTable.SetBinContent(i + 1, 16, (double)Records[i].TwoMuons * Factor);
      YieldTable.SetBinContent(i + 1, 15, (double)Records[i].TwoGlobalMuons * Factor);
      YieldTable.SetBinContent(i + 1, 14, (double)Records[i].TwoGlobalPixelHit * Factor);
      YieldTable.SetBinContent(i + 1, 13, (double)Records[i].TwoGlobalTrackingHit * Factor);
      YieldTable.SetBinContent(i + 1, 12, (double)Records[i].TwoGlobalAllHit * Factor);
      YieldTable.SetBinContent(i + 1, 11, (double)Records[i].TwoMuonsPassingMuonID * Factor);
      YieldTable.SetBinContent(i + 1, 10, (double)Records[i].ZCandidateKinematics * Factor);
      YieldTable.SetBinContent(i + 1, 9, (double)Records[i].ZCandidateAfterDxyCut * Factor);
      YieldTable.SetBinContent(i + 1, 8, (double)Records[i].ZCandidateAfterIsolationCut * Factor);

      YieldTable.SetBinContent(i + 1, 7, (double)Records[i].ZCandidateAfterIsolationCut * Factor);
      
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
SampleRecord ReadSample(string RootFile, string Name, double CrossSection, double DxyCut, double IsolationCut)
{
   SampleRecord record;

   record.Name = Name;
   record.EffectiveCrossSection = CrossSection;

   TFile F(RootFile.c_str());

   // Fill first few items from the plot
   TH1D *CountEventsSelectionCaloJet = (TH1D *)F.Get("CountEventsSelectionCaloJet0");

   record.AllEvents = CountEventsSelectionCaloJet->GetBinContent(1);
   record.PassHLT = CountEventsSelectionCaloJet->GetBinContent(2);
   record.TwoMuons = CountEventsSelectionCaloJet->GetBinContent(3);
   record.TwoGlobalMuons = CountEventsSelectionCaloJet->GetBinContent(4);
   record.TwoGlobalPixelHit = CountEventsSelectionCaloJet->GetBinContent(5);
   record.TwoGlobalTrackingHit = CountEventsSelectionCaloJet->GetBinContent(6);
   record.TwoGlobalAllHit = CountEventsSelectionCaloJet->GetBinContent(7);
   record.TwoMuonsPassingMuonID = CountEventsSelectionCaloJet->GetBinContent(8);
   record.ZCandidateKinematics = CountEventsSelectionCaloJet->GetBinContent(9);

   // Add in numbers after dxy and isolation cuts from the tree
   TTree *Tree = (TTree *)F.Get("outTree");

   double RunNumber = 0;
   double EventNumber = 0;
   double LumiSection = 0;

   double Muon1Dxy = 0;
   double Muon1Isolation = 0;
   double Muon1PT = 0;

   double Muon2Dxy = 0;
   double Muon2Isolation = 0;
   double Muon2PT = 0;

   int NCaloJet = 0;

   bool PassHLT = false;

   Tree->SetBranchAddress("RunNumber", &RunNumber);
   Tree->SetBranchAddress("EventNumber", &EventNumber);
   Tree->SetBranchAddress("LumiSection", &LumiSection);

   Tree->SetBranchAddress("Muon1Dxy", &Muon1Dxy);
   Tree->SetBranchAddress("Muon1CombinedIsolation", &Muon1Isolation);
   Tree->SetBranchAddress("Muon1PT", &Muon1PT);

   Tree->SetBranchAddress("Muon2Dxy", &Muon2Dxy);
   Tree->SetBranchAddress("Muon2CombinedIsolation", &Muon2Isolation);
   Tree->SetBranchAddress("Muon2PT", &Muon2PT);

   Tree->SetBranchAddress("NCaloJet", &NCaloJet);

   Tree->SetBranchAddress("PassHLT", &PassHLT);

   vector<EventIndex> EventsAfterDxyCut;
   vector<EventIndex> EventsAfterIsolationCut;
   vector<EventIndex> JetMultiplicity[6];   // >= 1-6 jets

   int NumberOfEntries = Tree->GetEntries();
   for(int i = 0; i < NumberOfEntries; i++)
   {
      Tree->GetEntry(i);

      EventIndex index;
      index.RunNumber = RunNumber + 0.1;
      index.EventNumber = EventNumber + 0.1;
      index.LumiSection = LumiSection + 0.1;

      if(DxyCut > 0 && Muon1Dxy > DxyCut)   // fail the cut
         continue;
      if(DxyCut > 0 && Muon2Dxy > DxyCut)
         continue;

      EventsAfterDxyCut.push_back(index);

      if(IsolationCut > 0 && Muon1Isolation > IsolationCut * Muon1PT)
         continue;
      if(IsolationCut > 0 && Muon2Isolation > IsolationCut * Muon2PT)
         continue;

      EventsAfterIsolationCut.push_back(index);

      for(int j = 0; j < NCaloJet && j < 6; j++)
         JetMultiplicity[j].push_back(index);
   }

   sort(EventsAfterDxyCut.begin(), EventsAfterDxyCut.end());
   sort(EventsAfterIsolationCut.begin(), EventsAfterIsolationCut.end());
   for(int i = 0; i < 6; i++)
      sort(JetMultiplicity[i].begin(), JetMultiplicity[i].end());

   EventsAfterDxyCut.erase(unique(EventsAfterDxyCut.begin(), EventsAfterDxyCut.end()), EventsAfterDxyCut.end());
   EventsAfterIsolationCut.erase(unique(EventsAfterIsolationCut.begin(), EventsAfterIsolationCut.end()),
      EventsAfterIsolationCut.end());
   for(int i = 0; i < 6; i++)
      JetMultiplicity[i].erase(unique(JetMultiplicity[i].begin(), JetMultiplicity[i].end()),
         JetMultiplicity[i].end());

   record.ZCandidateAfterDxyCut = EventsAfterDxyCut.size();
   record.ZCandidateAfterIsolationCut = EventsAfterIsolationCut.size();
   for(int i = 0; i < 6; i++)
      record.InclusiveCaloJet[i] = JetMultiplicity[i].size();

   F.Close();

   return record;
}
//---------------------------------------------------------------------------
bool EventIndex::operator <(const EventIndex &other) const
{
   if(RunNumber < other.RunNumber)
      return true;
   if(RunNumber > other.RunNumber)
      return false;

   if(EventNumber < other.EventNumber)
      return true;
   if(EventNumber > other.EventNumber)
      return false;

   if(LumiSection < other.LumiSection)
      return true;
   if(LumiSection > other.LumiSection)
      return false;

   return false;
}
//---------------------------------------------------------------------------
bool EventIndex::operator ==(const EventIndex &other) const
{
   if(RunNumber != other.RunNumber)
      return false;
   if(EventNumber != other.EventNumber)
      return false;
   if(LumiSection != other.LumiSection)
      return false;

   return true;
}
//---------------------------------------------------------------------------




