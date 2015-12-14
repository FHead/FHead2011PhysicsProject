#include <vector>
#include <string>
using namespace std;

#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TChain.h"
#include "TLegend.h"

#include "PlotHelper.h"

void MakeComparisonPlots();
void FillZPeakHistogram(TH1D *H, string FileName);
double GetTotalNumber(string FileName);

void MakeComparisonPlots()
{
   double IntegratedLuminosity = 33.3;

   PsFileHelper PsFile("ComparisonPlots.ps");
   PsFile.AddTextPage("Comparison between MC and data");

   // MC sample filenames
   vector<string> Samples;
   Samples.push_back("Samples/ZJetsAllNew.root");
   Samples.push_back("Samples/WJetsAll.root");
   Samples.push_back("Samples/TTbarAll.root");
   Samples.push_back("Samples/QDCppMuMuXAll.root");

   // MC cross sections
   vector<double> CrossSections;
   // CrossSections.push_back(2400 / 3);   // Cross section used while generating MADRAPH samples
   // CrossSections.push_back(972);   // NNLO inclusive Z cross section: 0.972 nb (60-120)
   CrossSections.push_back(1016);   // NNLO inclusive Z cross section: mll > 50
   CrossSections.push_back(24170);
   CrossSections.push_back(95);
   CrossSections.push_back(48000000000.0 * 0.0000112);

   // MC tags/labels
   vector<string> Tags;
   Tags.push_back("ZJets");
   Tags.push_back("WJets");
   Tags.push_back("TTbarJets");
   Tags.push_back("QCD");

   // Get the total processed event count from MC
   vector<double> TotalNumber;
   for(int i = 0; i < (int)Samples.size(); i++)
      TotalNumber.push_back(GetTotalNumber(Samples[i]));

   // MC single histograms
   vector<TH1D *> SingleHistograms;
   for(int i = 0; i < (int)Samples.size(); i++)
   {
      SingleHistograms.push_back(new TH1D(Form("Samples_%s", Tags[i].c_str()),
         Form("Z peak distribution for %s", Tags[i].c_str()), 30, 60.0, 120.0));
      FillZPeakHistogram(SingleHistograms[i], Samples[i]);
      SingleHistograms[i]->Scale(IntegratedLuminosity * CrossSections[i] / TotalNumber[i]);
   }

   // MC stacked histograms
   vector<TH1D *> StackedHistograms;
   for(int i = 0; i < (int)Samples.size(); i++)
      StackedHistograms.push_back((TH1D *)SingleHistograms[i]->Clone(Form("StackedSamples_%s", Tags[i].c_str())));

   for(int i = (int)Samples.size() - 2; i >= 0; i--)
      StackedHistograms[i]->Add(StackedHistograms[i+1]);

   // Data histogram
   TH1D DataHistogram("DataHistogram", "Data histogram!;Dimuon mass (GeV/c^{2});Event count", 30, 60.0, 120.0);
   FillZPeakHistogram(&DataHistogram, "Samples/DataAll.root");

   // Start drawing!
   TCanvas Canvas("C", "C", 0, 0, 1024, 768);

   DataHistogram.SetStats(0);
   DataHistogram.SetLineWidth(2);
   DataHistogram.SetMinimum(0.1);
   DataHistogram.Draw("error hist");

   for(int i = 0; i < (int)Samples.size(); i++)
   {
      StackedHistograms[i]->SetFillColor(i + 2);
      StackedHistograms[i]->SetLineColor(1);
      StackedHistograms[i]->SetStats(0);

      StackedHistograms[i]->Draw("same");
   }

   DataHistogram.Draw("same error hist");

   TLegend legend(0.7, 0.85, 0.85, 0.65);
   legend.SetFillColor(0);
   legend.AddEntry(&DataHistogram, "Data", "l");
   for(int i = 0; i < (int)Samples.size(); i++)
      legend.AddEntry(StackedHistograms[i], Tags[i].c_str(), "fl");
   legend.Draw();

   PsFile.AddCanvas(Canvas);
   Canvas.SetLogy();
   PsFile.AddCanvas(Canvas);

   PsFile.AddPlot(DataHistogram);

   // Numbers....
   char ch[1024] = "";
   vector<string> Texts;
   Texts.push_back("Number of events");
   sprintf(ch, "Data: %.2f", DataHistogram.Integral());
   Texts.push_back(ch);
   for(int i = 0; i < (int)Samples.size(); i++)
   {
      sprintf(ch, "%s: %.2f", Tags[i].c_str(), SingleHistograms[i]->Integral());
      Texts.push_back(ch);
   }
   sprintf(ch, "All MC: %.2f", StackedHistograms[0]->Integral());
   Texts.push_back(ch);
   sprintf(ch, "Data/MC: %.2f%%", DataHistogram.Integral() / StackedHistograms[0]->Integral() * 100);
   Texts.push_back(ch);
   PsFile.AddTextPage(Texts);

   // Clean-up
   for(int i = 0; i < (int)Samples.size(); i++)
   {
      delete StackedHistograms[i];
      delete SingleHistograms[i];
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();
}

void FillZPeakHistogram(TH1D *H, string FileName)
{
   if(H == NULL)
      return;

   // TChain outTree("OutTreeNoIsolation", "OutTreeNoIsolation");
   TChain outTree("outTree", "outTree");
   // TChain outTree("EfficiencyTreeOriginal", "EfficiencyTreeOriginal");
   outTree.AddFile(FileName.c_str());

   double ZMass;
   bool ZIsHighestPT;
   int NCaloJet30;
   double Muon1PT;
   double Muon1Dxy;
   double Muon2Dxy;

   outTree.SetBranchAddress("ZMass", &ZMass);
   outTree.SetBranchAddress("ZIsHighestPT", &ZIsHighestPT);
   outTree.SetBranchAddress("NCaloJet30", &NCaloJet30);
   outTree.SetBranchAddress("Muon1PT", &Muon1PT);
   outTree.SetBranchAddress("Muon1Dxy", &Muon1Dxy);
   outTree.SetBranchAddress("Muon2Dxy", &Muon2Dxy);

   outTree.SetBranchStatus("*", false);
   outTree.SetBranchStatus("ZMass", true);
   outTree.SetBranchStatus("ZIsHighestPT", true);
   outTree.SetBranchStatus("NCaloJet30", true);
   outTree.SetBranchStatus("Muon1PT", true);
   outTree.SetBranchStatus("Muon1Dxy", true);
   outTree.SetBranchStatus("Muon2Dxy", true);

   int EntryCount = outTree.GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      outTree.GetEntry(i);

      // if(ZIsHighestPT == false)
      //    continue;
      // if(Muon1Dxy < -0.1 || Muon1Dxy > 0.1 || Muon2Dxy < -0.1 || Muon2Dxy > 0.1)
      //    continue;

      if(NCaloJet30 >= 0)
         H->Fill(ZMass);
   }

   return;
}

double GetTotalNumber(string FileName)
{
   TFile F(FileName.c_str());

   TH1D *CountingHistogram = (TH1D *)F.Get("CountEventsSelectionCaloJet0");

   double Answer = 1;
   if(CountingHistogram != NULL)
      Answer = CountingHistogram->GetBinContent(1);

   F.Close();

   return Answer;
}




