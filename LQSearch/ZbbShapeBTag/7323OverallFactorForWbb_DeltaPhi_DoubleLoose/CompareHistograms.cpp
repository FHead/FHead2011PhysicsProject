#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "PlotHelper2.h"

struct RatioResult;
int main();
RatioResult Compare1DHistogram(PsFileHelper &PsFile, TFile &FZbb, TFile &FInclusive, string HistogramName);

struct RatioResult
{
   double Ratio;
   double Error;
   string HistogramName;
};

int main()
{
   TFile FZbb("ZbbPlots.root");
   TFile FInclusive("AllWJetsToLNu_Added.root");

   PsFileHelper PsFile("HistogramComparison.ps");
   PsFile.AddTextPage("Histogram comparisons!");

   vector<RatioResult> Results;

   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HMRNew"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HMRNew_R2New005"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HMRNew_R2New010"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HMRNew_R2New015"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HMRNew_R2New020"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HMRNew_R2New025"));
   
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HR2New"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HR2New_MRNew300"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HR2New_MRNew400"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HR2New_MRNew500"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HR2New_MRNew600"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HR2New_MRNew700"));
   
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HMRNew_MRNew300"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HMRNew_MRNew300_R2New005"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HMRNew_MRNew300_R2New010"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HMRNew_MRNew300_R2New015"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HMRNew_MRNew300_R2New020"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HMRNew_MRNew300_R2New025"));

   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HR2New_R2New015"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HR2New_MRNew300_R2New015"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HR2New_MRNew400_R2New015"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HR2New_MRNew500_R2New015"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HR2New_MRNew600_R2New015"));
   Results.push_back(Compare1DHistogram(PsFile, FZbb, FInclusive, "HR2New_MRNew700_R2New015"));

   TH1D HSummaryHistogram("HSummaryHistogram",
      "Summary of effective cross section from Zbb to W in signal selection;;Effective cross section (nb)",
      Results.size(), 0, Results.size());
   TH1D HBlockingHistogram("HBlockingHistogram", "", Results.size(), 0, Results.size());
   TH1D HAllHistogram("HAllHistogram", "", Results.size(), 0, Results.size());
   
   for(int i = 0; i < (int)Results.size(); i++)
   {
      HSummaryHistogram.SetBinContent(i + 1, Results[i].Ratio / 1000);
      HSummaryHistogram.SetBinError(i + 1, Results[i].Error / 1000);

      string Label = "All";
      if(Results[i].HistogramName.size() > 6)
         Label = Results[i].HistogramName.substr(7);

      for(int j = 0; j < (int)Label.size(); j++)
      {
         if(Label[j] == 'R' && Label[j+1] == '2')
            Label.replace(j, 2, "R^{2}");
         if(Label[j] == 'N' && Label[j+1] == 'e' && Label[j+2] == 'w')
            Label.replace(j, 3, " > ");
         if(Label[j] == '_')
            Label.replace(j, 1, ", ");
         if(Label[j] == ' ' && Label[j+1] == '0' && j + 2 != Label.size())
            Label.replace(j + 1, 1, "0.");
      }

      HSummaryHistogram.GetXaxis()->SetBinLabel(i + 1, Label.c_str());

      HAllHistogram.Fill(i, 1000.0);
   }

   HBlockingHistogram.Fill(0.0, 1000.0);
   HBlockingHistogram.Fill(1.0, 1000.0);
   HBlockingHistogram.Fill(6.0, 1000.0);
   HBlockingHistogram.Fill(7.0, 1000.0);
   HBlockingHistogram.Fill(8.0, 1000.0);
   HBlockingHistogram.Fill(9.0, 1000.0);
   HBlockingHistogram.Fill(10.0, 1000.0);
   HBlockingHistogram.Fill(11.0, 1000.0);
   HBlockingHistogram.Fill(12.0, 1000.0);
   HBlockingHistogram.Fill(13.0, 1000.0);
   HBlockingHistogram.SetStats(0);
   HBlockingHistogram.SetFillColor(kRed - 9);
   // HBlockingHistogram.SetLineColor(kRed - 9);

   HAllHistogram.SetStats(0);
   HAllHistogram.SetFillColor(kGreen - 9);
   // HAllHistogram.SetLineColor(kGreen - 9);

   HSummaryHistogram.SetStats(0);
   PsFile.AddPlot(HSummaryHistogram, "", false);
   
   TLegend Legend(0.5, 0.68, 0.85, 0.85);
   Legend.SetFillColor(0);
   Legend.SetBorderSize(1);
   Legend.SetTextFont(42);
   Legend.AddEntry(&HAllHistogram, "Good to use", "f");
   Legend.AddEntry(&HBlockingHistogram, "Calculation biased by the core", "f");

   TCanvas C("C", "C", 1024, 768);
   HSummaryHistogram.SetMinimum(0);
   HSummaryHistogram.Draw();
   HAllHistogram.Draw("same");
   HBlockingHistogram.Draw("same");
   HSummaryHistogram.Draw("axis same");
   HSummaryHistogram.Draw("same");
   Legend.Draw();
   C.SaveAs("SummaryHistogram.png");
   C.SaveAs("SummaryHistogram.C");
   C.SaveAs("SummaryHistogram.eps");
   C.SaveAs("SummaryHistogram.pdf");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   FInclusive.Close();
   FZbb.Close();

   return 0;
}

RatioResult Compare1DHistogram(PsFileHelper &PsFile, TFile &FZbb, TFile &FInclusive, string HistogramName)
{
   RatioResult Result;
   Result.Ratio = 0;
   Result.Error = 1;
   Result.HistogramName = HistogramName;

   double YieldZbb = 0;
   double Error2Zbb = 0;
   double YieldInclusive = 0;
   double Error2Inclusive = 0;

   TH1D *HZbb = (TH1D *)FZbb.Get(HistogramName.c_str());
   TH1D *HInclusive = (TH1D *)FInclusive.Get(HistogramName.c_str());
   if(HZbb == NULL || HInclusive == NULL)
      return Result;

   HZbb->SetStats(0);
   HInclusive->SetStats(0);

   for(int i = 1; i <= HZbb->GetNbinsX(); i++)
   {
      YieldZbb = YieldZbb + HZbb->GetBinContent(i);
      Error2Zbb = Error2Zbb + HZbb->GetBinError(i) * HZbb->GetBinError(i);
   }
   for(int i = 1; i <= HInclusive->GetNbinsX(); i++)
   {
      YieldInclusive = YieldInclusive + HInclusive->GetBinContent(i);
      Error2Inclusive = Error2Inclusive + HInclusive->GetBinError(i) * HInclusive->GetBinError(i);
   }

   double Ratio = YieldInclusive / YieldZbb;
   double RatioError = Ratio * sqrt(Error2Zbb / YieldZbb / YieldZbb + Error2Inclusive / YieldInclusive / YieldInclusive);

   cout << "[RATIO] " << YieldZbb << " +- " << sqrt(Error2Zbb) << " vs. "
      << YieldInclusive << " +- " << sqrt(Error2Inclusive) << "; ratio = "
      << Ratio << " +- " << RatioError
      << " (" << HistogramName << ")" << endl;

   TCanvas C;

   HInclusive->SetLineColor(kBlue + 3);
   HZbb->SetLineColor(kRed);

   HZbb->Scale(500);

   HInclusive->Draw();
   HZbb->Draw("same");

   TLegend legend(0.5, 0.85, 0.9, 0.7);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
   legend.AddEntry(HInclusive, "Inclusive sample (W to lu) scaled to 1/fb", "l");
   legend.AddEntry(HZbb, "(Z to ll) + bb, scaled to 1/fb with #sigma = \"1pb\", x500", "l");
   legend.Draw();

   C.SetLogy();
   PsFile.AddCanvas(C);

   Result.Ratio = Ratio;
   Result.Error = RatioError;

   return Result;
}




