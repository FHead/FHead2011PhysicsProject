#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"

#include "ReadLQ3Tree.h"
#include "PlotHelper2.h"
#include "TauHelperFunctions2.h"

int main(int argc, char *argv[]);
void CompareHistograms(PsFileHelper &PsFile, TFile &F, string HNormal, string HAntiMuon, double TailCutoff = -1);

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cout << "Usage: " << argv[0] << " SourceFileName OutputBase" << endl;
      return -1;
   }

   string FileName = argv[1];
   string OutputBase = argv[2];

   TFile F(FileName.c_str());

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage(OutputBase);

   vector<string> Explanations;
   Explanations.push_back("Starting from file " + FileName);
   Explanations.push_back("Split into two exclusive samples, depending on whether there is an anti-muon");
   Explanations.push_back("Anti-muon is defined by the following");
   Explanations.push_back("      - muon pass loose selection");
   Explanations.push_back("      - muon PT > 30");
   Explanations.push_back("      - dR(jet, muon) < 0.3");
   Explanations.push_back("      - jet PT > 20");
   Explanations.push_back("      - jet PT / muon PT > 0.5");
   Explanations.push_back("Using calo jets to avoid muons counted as jets");
   PsFile.AddTextPage(Explanations);

   PsFile.AddHistogramFromFile(F, "HRelativeEnergy", "", true);
   PsFile.AddHistogramFromFile(F, "HCountSample", "hist text00", false);

   TCanvas C("C", "C", 1024, 768);
   TH1D *H = (TH1D *)F.Get("HRelativeEnergy");
   H->Draw();
   C.SetLogy();
   C.SaveAs(Form("%s_RelativeEnergy.png", OutputBase.c_str()));
   C.SaveAs(Form("%s_RelativeEnergy.C", OutputBase.c_str()));
   C.SaveAs(Form("%s_RelativeEnergy.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s_RelativeEnergy.pdf", OutputBase.c_str()));

   PsFile.AddHistogramFromFile(F, "HNormalJetEta");
   PsFile.AddHistogramFromFile(F, "HAntiMuonJetEta");
   CompareHistograms(PsFile, F, "HNormalJetEta", "HAntiMuonJetEta");
   
   PsFile.AddHistogramFromFile(F, "HNormalJetPT", "", true);
   PsFile.AddHistogramFromFile(F, "HAntiMuonJetPT", "", true);
   CompareHistograms(PsFile, F, "HNormalJetPT", "HAntiMuonJetPT");
   
   PsFile.AddHistogramFromFile(F, "HNormalLeadingJetPT", "", true);
   PsFile.AddHistogramFromFile(F, "HAntiMuonLeadingJetPT", "", true);
   CompareHistograms(PsFile, F, "HNormalLeadingJetPT", "HAntiMuonLeadingJetPT");

   PsFile.AddHistogramFromFile(F, "HMRNewNormal", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNewAntiMuon", "", true);
   CompareHistograms(PsFile, F, "HMRNewNormal", "HMRNewAntiMuon");
   
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New005Normal", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New005AntiMuon", "", true);
   CompareHistograms(PsFile, F, "HMRNew_R2New005Normal", "HMRNew_R2New005AntiMuon", 400);
   
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New010Normal", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New010AntiMuon", "", true);
   CompareHistograms(PsFile, F, "HMRNew_R2New010Normal", "HMRNew_R2New010AntiMuon", 400);
   
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New015Normal", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New015AntiMuon", "", true);
   CompareHistograms(PsFile, F, "HMRNew_R2New015Normal", "HMRNew_R2New015AntiMuon", 400);
   
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New020Normal", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New020AntiMuon", "", true);
   CompareHistograms(PsFile, F, "HMRNew_R2New020Normal", "HMRNew_R2New020AntiMuon", 400);
   
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New025Normal", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New025AntiMuon", "", true);
   CompareHistograms(PsFile, F, "HMRNew_R2New025Normal", "HMRNew_R2New025AntiMuon", 400);
   
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New030Normal", "", true);
   PsFile.AddHistogramFromFile(F, "HMRNew_R2New030AntiMuon", "", true);
   CompareHistograms(PsFile, F, "HMRNew_R2New030Normal", "HMRNew_R2New030AntiMuon", 400);
   
   PsFile.AddHistogramFromFile(F, "HR2NewNormal", "", true);
   PsFile.AddHistogramFromFile(F, "HR2NewAntiMuon", "", true);
   CompareHistograms(PsFile, F, "HR2NewNormal", "HR2NewAntiMuon");
   
   PsFile.AddHistogramFromFile(F, "HR2New_MRNew200Normal", "", true);
   PsFile.AddHistogramFromFile(F, "HR2New_MRNew200AntiMuon", "", true);
   CompareHistograms(PsFile, F, "HR2New_MRNew200Normal", "HR2New_MRNew200AntiMuon", 0.15);
   
   PsFile.AddHistogramFromFile(F, "HR2New_MRNew400Normal", "", true);
   PsFile.AddHistogramFromFile(F, "HR2New_MRNew400AntiMuon", "", true);
   CompareHistograms(PsFile, F, "HR2New_MRNew400Normal", "HR2New_MRNew400AntiMuon", 0.15);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();

   return 0;
}

void CompareHistograms(PsFileHelper &PsFile, TFile &F, string SNormal, string SAntiMuon, double TailCutoff)
{
   TCanvas C;

   TH1D *HNormal = (TH1D *)F.Get(SNormal.c_str());
   TH1D *HAntiMuon = (TH1D *)F.Get(SAntiMuon.c_str());

   HNormal->SetStats(0);
   HAntiMuon->SetStats(0);
   
   TString Title = HNormal->GetTitle();
   HNormal->SetTitle(Title.ReplaceAll(" in normal sample", ""));

   HNormal->SetLineColor(1);
   HAntiMuon->SetLineColor(2);

   HNormal->DrawNormalized("");
   HAntiMuon->DrawNormalized("same");

   TLegend legend(0.6, 0.8, 0.9, 0.6);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
   legend.AddEntry(HNormal, "Normal", "l");
   legend.AddEntry(HAntiMuon, "Anti-muon", "l");
   legend.Draw();

   C.SetLogy();
   PsFile.AddCanvas(C);

   C.SaveAs(Form("%s_Normalized.png", SNormal.c_str()));
   C.SaveAs(Form("%s_Normalized.C", SNormal.c_str()));
   C.SaveAs(Form("%s_Normalized.eps", SNormal.c_str()));
   C.SaveAs(Form("%s_Normalized.pdf", SNormal.c_str()));

   HNormal->Add(HAntiMuon);

   TCanvas C2;

   TH1D HWorld("HWorld", Form("Ratio of anti-muon sample to the inclusive for %s", HNormal->GetTitle()),
      HNormal->GetNbinsX(), HNormal->GetXaxis()->GetBinLowEdge(1),
      HNormal->GetXaxis()->GetBinUpEdge(HNormal->GetNbinsX()));
   HWorld.GetXaxis()->SetTitle(HNormal->GetXaxis()->GetTitle());
   HWorld.SetMaximum(0.5);
   HWorld.SetMinimum(0);
   HWorld.SetStats(0);
   HWorld.Draw();

   TGraphAsymmErrors G;
   G.BayesDivide(HAntiMuon, HNormal);
   G.Draw("pe");

   PsFile.AddCanvas(C2);

   C2.SaveAs(Form("%s_Ratio.png", SNormal.c_str()));
   C2.SaveAs(Form("%s_Ratio.C", SNormal.c_str()));
   C2.SaveAs(Form("%s_Ratio.eps", SNormal.c_str()));
   C2.SaveAs(Form("%s_Ratio.pdf", SNormal.c_str()));
   
   if(TailCutoff > 0)
   {
      TCanvas C3;

      int Bin = HNormal->FindBin(TailCutoff);

      HNormal->SetTitle(Form("%s (tail-normalized)", HNormal->GetTitle()));

      double NormalIntegral = HNormal->Integral(Bin, HNormal->GetNbinsX());
      double AntiMuonIntegral = HAntiMuon->Integral(Bin, HAntiMuon->GetNbinsX());

      HNormal->Scale(1 / NormalIntegral);
      HAntiMuon->Scale(1 / AntiMuonIntegral);

      HNormal->Draw();
      HAntiMuon->Draw("same");

      C3.SetLogy();

      legend.Draw();

      PsFile.AddCanvas(C3);

      C3.SaveAs(Form("%s_TailNormalized.png", SNormal.c_str()));
      C3.SaveAs(Form("%s_TailNormalized.C", SNormal.c_str()));
      C3.SaveAs(Form("%s_TailNormalized.eps", SNormal.c_str()));
      C3.SaveAs(Form("%s_TailNormalized.pdf", SNormal.c_str()));
      
      HNormal->Scale(NormalIntegral);
      HAntiMuon->Scale(AntiMuonIntegral);
   }
}





