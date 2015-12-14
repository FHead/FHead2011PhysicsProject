#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"

#include "PlotHelper2.h"

int main(int argc, char *argv);
void CompareHistogram(PsFileHelper &PsFile, vector<TFile *> Files, vector<string> Labels, string Name,
   double TailNormalize = -1);

int main(int argc, char *argv)
{
   vector<TFile *> Files;
   Files.push_back(new TFile("QCDAll.root"));
   Files.push_back(new TFile("TTbar.root"));

   vector<string> Labels;
   Labels.push_back("QCD");
   Labels.push_back("TTbar");

   PsFileHelper PsFile("TTbarVsQCD.ps");
   PsFile.AddTextPage("Compare between TTbar and QCD");

   vector<string> Explanation;
   Explanation.push_back("Reject leptons.  Doing the usual pre-selection.");
   Explanation.push_back("Look at ttbar and QCD madgraph sample.");
   Explanation.push_back("Look at tails changing R cut and b-tagging requirement.");
   Explanation.push_back("");
   Explanation.push_back("MR tail matches quite well, R shape is different.");
   PsFile.AddTextPage(Explanation);

   vector<string> Items;
   Items.push_back("No b-tagging requirement");
   Items.push_back("Requiring single loose (TCHE, 80) tag");
   Items.push_back("Requiring double loose (TCHE, 80) tag");

   vector<string> Destinations;
   Destinations.push_back("NoTag");
   Destinations.push_back("OneTag");
   Destinations.push_back("TwoTags");

   PsFile.AddTableOfContentPage(Items, Destinations);
   PsFile.InsertNamedDestination("Home");
   PsFile.SetAutomaticHomeButton(true, "Home");

   PsFile.AddTextPage("No tagging requirements");
   PsFile.InsertNamedDestination("NoTag");
   CompareHistogram(PsFile, Files, Labels, "HMRNew", 500);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New005", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New010", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New015", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New020", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New025", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New030", 400);
   CompareHistogram(PsFile, Files, Labels, "HR2New");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew200");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew300");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew400");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew500");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew600");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew700");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew800");
   
   PsFile.AddTextPage("Single-loose tag");
   PsFile.InsertNamedDestination("OneTag");
   CompareHistogram(PsFile, Files, Labels, "HMRNew_L", 500);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New005_L", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New010_L", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New015_L", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New020_L", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New025_L", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New030_L", 400);
   CompareHistogram(PsFile, Files, Labels, "HR2New_L");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew200_L");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew300_L");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew400_L");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew500_L");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew600_L");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew700_L");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew800_L");

   PsFile.AddTextPage("Double-loose tag");
   PsFile.InsertNamedDestination("TwoTags");
   CompareHistogram(PsFile, Files, Labels, "HMRNew_LL", 500);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New005_LL", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New010_LL", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New011_LL", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New012_LL", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New013_LL", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New014_LL", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New015_LL", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New020_LL", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New025_LL", 400);
   CompareHistogram(PsFile, Files, Labels, "HMRNew_R2New030_LL", 400);
   CompareHistogram(PsFile, Files, Labels, "HR2New_LL");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew200_LL");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew300_LL");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew400_LL");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew500_LL");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew600_LL");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew700_LL");
   CompareHistogram(PsFile, Files, Labels, "HR2New_MRNew800_LL");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   for(int i = 0; i < (int)Files.size(); i++)
   {
      Files[i]->Close();
      delete Files[i];
      Files[i] = NULL;
   }

   return 0;
}

void CompareHistogram(PsFileHelper &PsFile, vector<TFile *> Files, vector<string> Labels, string Name,
   double TailNormalize)
{
   if(Name == "")
      return;

   vector<TH1D *> Histograms;
   for(int i = 0; i < (int)Files.size(); i++)
      Histograms.push_back((TH1D *)Files[i]->Get(Name.c_str()));

   double Maximum = 0;

   for(int i = 0; i < (int)Files.size(); i++)
   {
      Histograms[i]->SetLineColor(i + 1);
      Histograms[i]->SetLineWidth(2);
      Histograms[i]->SetStats(0);
      if(Histograms[i]->GetMaximum() > Maximum)
         Maximum = Histograms[i]->GetMaximum();
   }
   
   Histograms[0]->SetMaximum(Maximum * 5);
   Histograms[0]->SetMinimum(0.2);

   TLegend legend(0.7, 0.85, 0.9, 0.45);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.SetTextFont(42);
   for(int i = 0; i < (int)Files.size(); i++)
      legend.AddEntry(Histograms[i], Labels[i].c_str(), "l");

   TCanvas Canvas;

   Histograms[0]->Draw();
   for(int i = 1; i < (int)Files.size(); i++)
      Histograms[i]->Draw("same");

   legend.Draw();

   Canvas.SetLogy();
   PsFile.AddCanvas(Canvas);
   Canvas.SaveAs((Name + ".png").c_str());
   Canvas.SaveAs((Name + ".C").c_str());
   Canvas.SaveAs((Name + ".eps").c_str());
   Canvas.SaveAs((Name + ".pdf").c_str());

   if(Histograms.size() == 2)
   {
      TH1D *H = (TH1D *)Histograms[0]->Clone("Clone");
      H->SetTitle(TString(Histograms[0]->GetTitle()) + ", ratio");
      H->GetXaxis()->SetTitle(Histograms[0]->GetXaxis()->GetTitle());
      H->GetYaxis()->SetTitle("Ratio of the two histograms");

      double Max = -1;

      for(int i = 1; i <= Histograms[0]->GetNbinsX(); i++)
      {
         double a = Histograms[0]->GetBinContent(i);
         double sa = Histograms[0]->GetBinError(i);
         double b = Histograms[1]->GetBinContent(i);
         double sb = Histograms[1]->GetBinError(i);

         if(a != 0)
         {
            H->SetBinContent(i, b / a);
            H->SetBinError(i, b / a * sqrt(sa * sa / a / a + sb * sb / b / b));

            if(Max < b / a)
               Max = b / a;
         }
      }

      H->SetMaximum(Max * 1.5);
      H->SetMinimum(0);

      PsFile.AddPlot(H, "hist error");

      /*
      TGraphAsymmErrors Ratio;
      Ratio.Divide(Histograms[0], Histograms[1], "pois");
      Ratio.SetTitle(Histograms[0]->GetTitle());
      PsFile.AddPlot(Ratio, "ape");
      */
   }

   if(TailNormalize > -1)
   {
      for(int i = 0; i < (int)Files.size(); i++)
      {
         int Bin = Histograms[i]->FindBin(TailNormalize);
         double Integral = Histograms[i]->Integral(Bin, Histograms[i]->GetNbinsX());
         Histograms[i]->Scale(1.0 / Integral);
      }

      TCanvas Canvas2;

      Histograms[0]->SetTitle(TString(Histograms[0]->GetTitle()) + " (tail-normalized)");
      Histograms[0]->Draw();
      for(int i = 1; i < (int)Files.size(); i++)
         Histograms[i]->Draw("same");

      legend.Draw();

      Canvas2.SetLogy();
      PsFile.AddCanvas(Canvas2);
   
      Canvas2.SaveAs((Name + "_TailNormalized.png").c_str());
      Canvas2.SaveAs((Name + "_TailNormalized.C").c_str());
      Canvas2.SaveAs((Name + "_TailNormalized.eps").c_str());
      Canvas2.SaveAs((Name + "_TailNormalized.pdf").c_str());
   }
}



