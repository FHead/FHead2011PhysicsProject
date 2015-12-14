#include <string>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper.h"

void MakeAntiLeptonPlots(double Isolation = 0.3, string DataFile = "Samples/Run2010A-PDMu-All.root", string MCFile = "Samples/QDCppMuMuXAll.root")
{
   TH1D DataAntiHistogram1("DataAntiHistogram1", "Data, anti-lepton on first leg;Mass", 12, 60, 120);
   TH1D MCAntiHistogram1("MCAntiHistogram1", "MC, anti-lepton on first leg;Mass", 12, 60, 120);
   TH1D MCHistogram1("MCHistogram1", "MC, select isolation on first leg;Mass", 12, 60, 120);
   TH1D DataAntiHistogram2("DataAntiHistogram2", "Data, anti-lepton on both legs;Mass", 12, 60, 120);
   TH1D MCAntiHistogram2("MCAntiHistogram2", "MC, anti-lepton on both legs;Mass", 12, 60, 120);
   TH1D MCHistogram2("MCHistogram2", "MC, select isolation on both legs;Mass", 12, 60, 120);

   TChain DataChain("outTree", "outTree");
   DataChain.AddFile(DataFile.c_str());
   
   double DataZMass;
   double DataMuon1CombinedIsolation;
   double DataMuon1PT;
   double DataMuon2CombinedIsolation;
   double DataMuon2PT;

   DataChain.SetBranchAddress("ZMass", &DataZMass);
   DataChain.SetBranchAddress("Muon1CombinedIsolation", &DataMuon1CombinedIsolation);
   DataChain.SetBranchAddress("Muon1PT", &DataMuon1PT);
   DataChain.SetBranchAddress("Muon2CombinedIsolation", &DataMuon2CombinedIsolation);
   DataChain.SetBranchAddress("Muon2PT", &DataMuon2PT);

   int DataEntryCount = DataChain.GetEntries();
   for(int i = 0; i < DataEntryCount; i++)
   {
      DataChain.GetEntry(i);

      if(DataMuon1CombinedIsolation > Isolation * DataMuon1PT)
         DataAntiHistogram1.Fill(DataZMass);
      if(DataMuon1CombinedIsolation > Isolation * DataMuon1PT || DataMuon2CombinedIsolation > Isolation * DataMuon2PT)
         DataAntiHistogram2.Fill(DataZMass);
   }

   TChain MCChain("outTree", "outTree");
   MCChain.AddFile(MCFile.c_str());
   
   double MCZMass;
   double MCMuon1CombinedIsolation;
   double MCMuon1PT;
   double MCMuon2CombinedIsolation;
   double MCMuon2PT;

   MCChain.SetBranchAddress("ZMass", &MCZMass);
   MCChain.SetBranchAddress("Muon1CombinedIsolation", &MCMuon1CombinedIsolation);
   MCChain.SetBranchAddress("Muon1PT", &MCMuon1PT);
   MCChain.SetBranchAddress("Muon2CombinedIsolation", &MCMuon2CombinedIsolation);
   MCChain.SetBranchAddress("Muon2PT", &MCMuon2PT);

   int MCEntryCount = MCChain.GetEntries();
   for(int i = 0; i < MCEntryCount; i++)
   {
      MCChain.GetEntry(i);

      if(MCMuon1CombinedIsolation > Isolation * MCMuon1PT)
         MCAntiHistogram1.Fill(MCZMass);
      else
         MCHistogram1.Fill(MCZMass);

      if(MCMuon1CombinedIsolation > Isolation * MCMuon1PT || MCMuon2CombinedIsolation > Isolation * MCMuon2PT)
         MCAntiHistogram2.Fill(MCZMass);
      else
         MCHistogram2.Fill(MCZMass);
   }

   TCanvas canvas("canvas", "Camvas", 0, 0, 1024, 768);
   
   PsFileHelper PsFile("AntiLepton.ps");

   PsFile.AddTextPage("Anti-lepton selection plots");

   PsFile.AddTextPage("Isolation on first leg");

   PsFile.AddPlot(MCHistogram1, "", false);
   PsFile.AddPlot(MCAntiHistogram1, "", false);
   PsFile.AddPlot(DataAntiHistogram1, "", false);

   DataAntiHistogram1.SetTitle("Anti-muon selection on first leg");
   DataAntiHistogram1.SetLineWidth(3);
   DataAntiHistogram1.SetLineColor(1);
   DataAntiHistogram1.SetStats(0);
   DataAntiHistogram1.Draw("error");

   MCAntiHistogram1.SetLineWidth(2);
   MCAntiHistogram1.SetLineColor(2);
   MCAntiHistogram1.Scale(DataAntiHistogram1.Integral() / MCAntiHistogram1.Integral());
   MCAntiHistogram1.SetStats(0);
   MCAntiHistogram1.Draw("error same");

   MCHistogram1.SetLineWidth(1);
   MCHistogram1.SetLineColor(3);
   MCHistogram1.Scale(DataAntiHistogram1.Integral() / MCHistogram1.Integral());
   MCHistogram1.SetStats(0);
   MCHistogram1.Draw("error same");

   TLegend legend1(0.5, 0.8, 0.8, 0.6);
   legend1.SetFillColor(0);
   legend1.AddEntry(&DataAntiHistogram1, "Data, anti-selection", "l");
   legend1.AddEntry(&MCAntiHistogram1, "MC, anti-selection", "l");
   legend1.AddEntry(&MCHistogram1, "MC, isolation", "l");
   legend1.Draw();

   canvas.SaveAs("SingleLegAntiMuon.png");

   PsFile.AddCanvas(canvas);

   PsFile.AddTextPage("Isolation on both legs");
   
   PsFile.AddPlot(MCHistogram2, "", false);
   PsFile.AddPlot(MCAntiHistogram2, "", false);
   PsFile.AddPlot(DataAntiHistogram2, "", false);
   
   DataAntiHistogram2.SetTitle("Anti-muon selection on both legs");
   DataAntiHistogram2.SetLineWidth(3);
   DataAntiHistogram2.SetLineColor(1);
   DataAntiHistogram2.SetStats(0);
   DataAntiHistogram2.Draw("error");

   MCAntiHistogram2.SetLineWidth(2);
   MCAntiHistogram2.SetLineColor(2);
   MCAntiHistogram2.Scale(DataAntiHistogram2.Integral() / MCAntiHistogram2.Integral());
   MCAntiHistogram2.SetStats(0);
   MCAntiHistogram2.Draw("error same");

   MCHistogram2.SetLineWidth(1);
   MCHistogram2.SetLineColor(3);
   MCHistogram2.Scale(DataAntiHistogram2.Integral() / MCHistogram2.Integral());
   MCHistogram2.SetStats(0);
   MCHistogram2.Draw("error same");

   TLegend legend2(0.5, 0.8, 0.8, 0.6);
   legend2.SetFillColor(0);
   legend2.AddEntry(&DataAntiHistogram2, "Data, anti-selection", "l");
   legend2.AddEntry(&MCAntiHistogram2, "MC, anti-selection", "l");
   legend2.AddEntry(&MCHistogram2, "MC, isolation", "l");
   legend2.Draw();
   
   canvas.SaveAs("DoubleLegAntiMuon.png");
   
   PsFile.AddCanvas(canvas);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}
