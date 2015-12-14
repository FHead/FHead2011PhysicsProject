#include <iostream>
#include <vector>
using namespace std;

#include "TCanvas.h"
#include "TChain.h"
#include "TH1D.h"
#include "TFile.h"
#include "TLegend.h"

#include "PlotHelper.h"

void EstimateCombinedIsolation();
void EstimateCombinedIsolation(int JetMultiplicity);
TH1D *MakeSingleLegHistogram(PsFileHelper &PsFile, string FileName, string Tag = "None", double CrossSection = 1, int JetMultiplicity = 1, string JetFlavor = "Calo");
TH1D *MakeDoubleLegHistogram(PsFileHelper &PsFile, string FileName, string Tag = "None", double CrossSection = 1, int JetMultiplicity = 1, string JetFlavor = "Calo");
void MakeCombinedPlots(PsFileHelper &PsFile, TH1D *ZJets, TH1D *WJets, TH1D *TTbar, TH1D *QCD, bool SingleLeg = true, int JetMultiplicity = 1, string JetFlavor = "Calo");

void EstimateCombinedIsolation()
{
   EstimateCombinedIsolation(0);
   EstimateCombinedIsolation(1);
   EstimateCombinedIsolation(2);
   EstimateCombinedIsolation(3);
   EstimateCombinedIsolation(4);
}

void EstimateCombinedIsolation(int JetMultiplicity)
{
   char JetMultiplicityString[20] = "";
   sprintf(JetMultiplicityString, "%d", JetMultiplicity);

   vector<string> JetFlavor;
   JetFlavor.push_back("Calo");
   JetFlavor.push_back("UncorrectedCalo");
   JetFlavor.push_back("PF");
   JetFlavor.push_back("Track");

   for(unsigned int i = 0; i < JetFlavor.size(); i++)
   {
      TFile OutputFile(Form("ROOT/Output_%d%sJets.root", JetMultiplicity, JetFlavor[i].c_str()), "RECREATE");

      PsFileHelper PsFile(string("PDFs/IsolationPlots_") + JetMultiplicityString + JetFlavor[i] + "Jets.ps");

      PsFile.AddTextPage(string("Isolation, antimuon, >= ") + JetMultiplicityString + " " + JetFlavor[i] + " Jets");

      TH1D *ZJetsCurve1 = MakeSingleLegHistogram(PsFile, "Samples/ZJetsAll.root", "ZJets", 800, JetMultiplicity, JetFlavor[i]);
      TH1D *WJetsCurve1 = MakeSingleLegHistogram(PsFile, "Samples/WJetsAll.root", "WJets", 24170, JetMultiplicity, JetFlavor[i]);
      TH1D *TTbarCurve1 = MakeSingleLegHistogram(PsFile, "Samples/TTbarAll.root", "TTbar", 95, JetMultiplicity, JetFlavor[i]);
      TH1D *QCDCurve1 = MakeSingleLegHistogram(PsFile, "Samples/QDCppMuMuXAll.root", "ppMuMuX", 48000000000.0 * 0.0000112, JetMultiplicity, JetFlavor[i]);

      OutputFile.cd();

      ZJetsCurve1->Write();
      WJetsCurve1->Write();
      TTbarCurve1->Write();
      QCDCurve1->Write();

      MakeCombinedPlots(PsFile, ZJetsCurve1, WJetsCurve1, TTbarCurve1, QCDCurve1, true, JetMultiplicity, JetFlavor[i]);

      TH1D *ZJetsCurve2 = MakeDoubleLegHistogram(PsFile, "Samples/ZJetsAll.root", "ZJets", 800, JetMultiplicity, JetFlavor[i]);
      TH1D *WJetsCurve2 = MakeDoubleLegHistogram(PsFile, "Samples/WJetsAll.root", "WJets", 24170, JetMultiplicity, JetFlavor[i]);
      TH1D *TTbarCurve2 = MakeDoubleLegHistogram(PsFile, "Samples/TTbarAll.root", "TTbar", 95, JetMultiplicity, JetFlavor[i]);
      TH1D *QCDCurve2 = MakeDoubleLegHistogram(PsFile, "Samples/QDCppMuMuXAll.root", "ppMuMuX", 48000000000.0 * 0.0000112, JetMultiplicity, JetFlavor[i]);

      OutputFile.cd();

      ZJetsCurve2->Write();
      WJetsCurve2->Write();
      TTbarCurve2->Write();
      QCDCurve2->Write();

      MakeCombinedPlots(PsFile, ZJetsCurve2, WJetsCurve2, TTbarCurve2, QCDCurve2, false, JetMultiplicity, JetFlavor[i]);

      delete ZJetsCurve1;
      delete WJetsCurve1;
      delete TTbarCurve1;
      delete QCDCurve1;

      delete ZJetsCurve2;
      delete WJetsCurve2;
      delete TTbarCurve2;
      delete QCDCurve2;

      PsFile.AddTimeStampPage();

      PsFile.Close();

      OutputFile.Close();
   }
}

TH1D *MakeSingleLegHistogram(PsFileHelper &PsFile, string FileName, string Tag, double CrossSection, int JetMultiplicity, string JetFlavor)
{
   PsFile.AddTextPage("Plots for " + Tag + " - cut on first leg");

   TFile F(FileName.c_str());
   TH1D *CountEventNumber = (TH1D *)F.Get(Form("CountEventsSelection%sJet0", JetFlavor.c_str()));
   double AllEvents = CountEventNumber->GetBinContent(1);
   F.Close();

   TH1D *IsolationDistribution = new TH1D(Form("SingleLegIsolationDistribution_%s", Tag.c_str()),
      Form("Combined Isolation Distribution, >= %d %s Jets", JetMultiplicity, JetFlavor.c_str()), 310, -0.1, 3);
   IsolationDistribution->GetXaxis()->SetTitle("Relative combined isolation for the first leg");

   TChain ch("OutTreeNoIsolation", "OutTreeNoIsolation");
   ch.AddFile(FileName.c_str());

   int NJet = 0;
   double Muon1CombinedIsolation = 0;
   double Muon1PT = 0;
   bool ZIsHighestPT = false;

   ch.SetBranchStatus("*", false);
   ch.SetBranchStatus(Form("N%sJet", JetFlavor.c_str()), true);
   ch.SetBranchStatus("Muon1CombinedIsolation", true);
   ch.SetBranchStatus("Muon1PT", true);
   ch.SetBranchStatus("ZIsHighestPT", true);

   ch.SetBranchAddress(Form("N%sJet", JetFlavor.c_str()), &NJet);
   ch.SetBranchAddress("Muon1CombinedIsolation", &Muon1CombinedIsolation);
   ch.SetBranchAddress("Muon1PT", &Muon1PT);
   ch.SetBranchAddress("ZIsHighestPT", &ZIsHighestPT);

   int EntryCount = ch.GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      ch.GetEntry(i);

      if(ZIsHighestPT == false)
         continue;
      if(NJet < JetMultiplicity)
         continue;

      double Isolation = Muon1CombinedIsolation / Muon1PT;

      IsolationDistribution->Fill(Isolation);
   }

   PsFile.AddPlot(IsolationDistribution, "", true, false, true);

   for(int i = IsolationDistribution->GetNbinsX(); i >= 1; i--)
   {
      double Bin1 = IsolationDistribution->GetBinContent(i);
      double Bin2 = IsolationDistribution->GetBinContent(i + 1);
      IsolationDistribution->SetBinContent(i, Bin1 + Bin2);
   }
   IsolationDistribution->Sumw2();

   IsolationDistribution->SetTitle(Form("Cut position vs. remaining events in the antimuon sample (not normalized), >= %d %s Jets", JetMultiplicity, JetFlavor.c_str()));

   PsFile.AddPlot(IsolationDistribution, "hist error", true, false, true);

   IsolationDistribution->Scale(CrossSection / AllEvents);

   return IsolationDistribution;
}

TH1D *MakeDoubleLegHistogram(PsFileHelper &PsFile, string FileName, string Tag, double CrossSection, int JetMultiplicity, string JetFlavor)
{
   PsFile.AddTextPage("Plots for " + Tag + " - cut on both legs");

   TFile F(FileName.c_str());
   TH1D *CountEventNumber = (TH1D *)F.Get(Form("CountEventsSelection%sJet0", JetFlavor.c_str()));
   double AllEvents = CountEventNumber->GetBinContent(1);
   F.Close();

   TH1D *IsolationDistribution = new TH1D(Form("DoubleLegIsolationDistribution_%s", Tag.c_str()),
      Form("Combined Isolation Distribution, >= %d %s Jets", JetMultiplicity, JetFlavor.c_str()), 310, -0.1, 3);
   IsolationDistribution->GetXaxis()->SetTitle("Relative combined isolation for the larger of the two legs");

   TChain ch("OutTreeNoIsolation", "OutTreeNoIsolation");
   ch.AddFile(FileName.c_str());

   int NJet = 0;
   double Muon1CombinedIsolation = 0;
   double Muon1PT = 0;
   double Muon2CombinedIsolation = 0;
   double Muon2PT = 0;
   bool ZIsHighestPT = false;

   ch.SetBranchStatus("*", false);
   ch.SetBranchStatus(Form("N%sJet", JetFlavor.c_str()), true);
   ch.SetBranchStatus("Muon1CombinedIsolation", true);
   ch.SetBranchStatus("Muon1PT", true);
   ch.SetBranchStatus("Muon2CombinedIsolation", true);
   ch.SetBranchStatus("Muon2PT", true);
   ch.SetBranchStatus("ZIsHighestPT", true);
   
   ch.SetBranchAddress(Form("N%sJet", JetFlavor.c_str()), &NJet);
   ch.SetBranchAddress("Muon1CombinedIsolation", &Muon1CombinedIsolation);
   ch.SetBranchAddress("Muon1PT", &Muon1PT);
   ch.SetBranchAddress("Muon2CombinedIsolation", &Muon2CombinedIsolation);
   ch.SetBranchAddress("Muon2PT", &Muon2PT);
   ch.SetBranchAddress("ZIsHighestPT", &ZIsHighestPT);

   int EntryCount = ch.GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      ch.GetEntry(i);

      if(ZIsHighestPT == false)
         continue;
      if(NJet < JetMultiplicity)
         continue;

      double Isolation1 = Muon1CombinedIsolation / Muon1PT;
      double Isolation2 = Muon2CombinedIsolation / Muon2PT;

      IsolationDistribution->Fill(max(Isolation1, Isolation2));
   }

   PsFile.AddPlot(IsolationDistribution, "", true, false, true);

   for(int i = IsolationDistribution->GetNbinsX(); i >= 1; i--)
   {
      double Bin1 = IsolationDistribution->GetBinContent(i);
      double Bin2 = IsolationDistribution->GetBinContent(i + 1);
      IsolationDistribution->SetBinContent(i, Bin1 + Bin2);
   }
   IsolationDistribution->Sumw2();

   IsolationDistribution->SetTitle(Form("Cut position vs. remaining events in the antimuon sample (not normalized), >= %d %s Jets", JetMultiplicity, JetFlavor.c_str()));

   PsFile.AddPlot(IsolationDistribution, "hist error", true, false, true);

   IsolationDistribution->Scale(CrossSection / AllEvents);

   return IsolationDistribution;
}

void MakeCombinedPlots(PsFileHelper &PsFile, TH1D *ZJets, TH1D *WJets, TH1D *TTbar, TH1D *QCD, bool SingleLeg, int JetMultiplicity, string JetFlavor)
{
   TH1D *ZJetsCurve = (TH1D *)ZJets->Clone("ZJetsCurve");
   TH1D *WJetsCurve = (TH1D *)WJets->Clone("WJetsCurve");
   TH1D *TTbarCurve = (TH1D *)TTbar->Clone("TTbarCurve");
   TH1D *QCDCurve = (TH1D *)QCD->Clone("QCD");

   if(SingleLeg == true)
      PsFile.AddTextPage("All of them together - cut on first leg");
   else
      PsFile.AddTextPage("All of them together - cut on both legs");

   TH1D *BackgroundCurve = (TH1D *)WJetsCurve->Clone("BackgroundCurve");
   BackgroundCurve->SetTitle("Background!!");
   BackgroundCurve->Add(TTbarCurve);

   TCanvas Canvas("c", "c", 0, 0, 1024, 768);

   if(SingleLeg == true)
      ZJetsCurve->SetTitle(Form("Signal vs. background, cut on first leg, no QCD (1/pb), >= %d %s Jets", JetMultiplicity, JetFlavor.c_str()));
   else
      ZJetsCurve->SetTitle(Form("Signal vs. background, cut on both legs, no QCD (1/pb), >= %d %s Jets", JetMultiplicity, JetFlavor.c_str()));
   ZJetsCurve->GetXaxis()->SetTitle("Cut position");
   ZJetsCurve->GetYaxis()->SetTitle("Expected events");
   ZJetsCurve->SetLineColor(2);
   ZJetsCurve->SetStats(0);
   ZJetsCurve->Draw("hist error");

   BackgroundCurve->SetLineColor(1);
   BackgroundCurve->SetStats(0);
   BackgroundCurve->Draw("hist error same");
   
   Canvas.SetLogy();
   Canvas.SetGridx();
   Canvas.SetGridy();

   TLegend legend(0.65, 0.95, 0.95, 0.75);
   legend.SetFillColor(0);
   legend.AddEntry(ZJetsCurve, "Signal", "l");
   legend.AddEntry(BackgroundCurve, "Background", "l");
   legend.Draw();

   PsFile.AddCanvas(Canvas);

   if(SingleLeg == true)
      Canvas.SaveAs(Form("Plots/SingleLeg_NoQCD_%d%sJet.png", JetMultiplicity, JetFlavor.c_str()));
   else
      Canvas.SaveAs(Form("Plots/DoubleLeg_NoQCD_%d%sJet.png", JetMultiplicity, JetFlavor.c_str()));

   BackgroundCurve->Add(QCDCurve);

   if(SingleLeg == true)
      ZJetsCurve->SetTitle(Form("Signal vs. full background, cut on first leg (1/pb), >= %d %s Jets", JetMultiplicity, JetFlavor.c_str()));
   else
      ZJetsCurve->SetTitle(Form("Signal vs. full background, cut on both legs (1/pb), >= %d %s Jets", JetMultiplicity, JetFlavor.c_str()));
   ZJetsCurve->Draw("hist error");
   BackgroundCurve->Draw("hist error same");
   legend.Draw();
   
   PsFile.AddCanvas(Canvas);

   if(SingleLeg == true)
      Canvas.SaveAs(Form("Plots/SingleLeg_WithQCD_%d%sJet.png", JetMultiplicity, JetFlavor.c_str()));
   else
      Canvas.SaveAs(Form("Plots/DoubleLeg_WithQCD_%d%sJet.png", JetMultiplicity, JetFlavor.c_str()));

   BackgroundCurve->Divide(ZJetsCurve);

   if(SingleLeg == true)
      BackgroundCurve->SetTitle(Form("Full background to signal ratio, cut on first leg (1/pb), >= %d %s Jets", JetMultiplicity, JetFlavor.c_str()));
   else
      BackgroundCurve->SetTitle(Form("Full background to signal ratio, cut on both legs (1/pb), >= %d %s Jets", JetMultiplicity, JetFlavor.c_str()));
   BackgroundCurve->GetXaxis()->SetTitle("Cut position");
   BackgroundCurve->GetYaxis()->SetTitle("Background / Signal");

   BackgroundCurve->Draw("hist error");

   PsFile.AddCanvas(Canvas);

   if(SingleLeg == true)
      Canvas.SaveAs(Form("Plots/SingleLeg_BackgroundToSignalRatio_%d%sJet.png", JetMultiplicity, JetFlavor.c_str()));
   else
      Canvas.SaveAs(Form("Plots/DoubleLeg_BackgroundToSignalRatio_%d%sJet.png", JetMultiplicity, JetFlavor.c_str()));

   delete BackgroundCurve;

   delete ZJetsCurve;
   delete WJetsCurve;
   delete TTbarCurve;
   delete QCDCurve;
}

