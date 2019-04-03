#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[]);
void Add1DPlot(PdfFileHelper &PdfFile, TFile &File, string Prefix);
void AddComparisonPlot(PdfFileHelper &PdfFile, TFile &File, string Prefix1, string Prefix2, string Prefix3, string Prefix4);
void AddMirrorPlot(PdfFileHelper &PdfFile, TFile &File, string Prefix);
void Add2DPlot(PdfFileHelper &PdfFile, TFile &File, string Prefix);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Track plots");

   TFile InputFile(InputFileName.c_str());

   Add1DPlot(PdfFile, InputFile, "HJetCount");
   Add1DPlot(PdfFile, InputFile, "HJetCountPT30");
   Add1DPlot(PdfFile, InputFile, "HJetCountPT50");
   Add1DPlot(PdfFile, InputFile, "HJetCountPT75");
   Add1DPlot(PdfFile, InputFile, "HJetCountPT100");
   Add1DPlot(PdfFile, InputFile, "HJetCountPT125");
   Add1DPlot(PdfFile, InputFile, "HJetPT");
   Add1DPlot(PdfFile, InputFile, "HJetPTEtaN25N15");
   Add1DPlot(PdfFile, InputFile, "HJetPTEtaN15N00");
   Add1DPlot(PdfFile, InputFile, "HJetPTEtaP00P15");
   Add1DPlot(PdfFile, InputFile, "HJetPTEtaP15P25");
   AddComparisonPlot(PdfFile, InputFile, "HJetPTEtaN25N15", "HJetPTEtaN15N00", "HJetPTEtaP00P15", "HJetPTEtaP15P25");
   Add2DPlot(PdfFile, InputFile, "HJetEtaPhiPT30");
   Add2DPlot(PdfFile, InputFile, "HJetEtaPhiPT50");
   Add2DPlot(PdfFile, InputFile, "HJetEtaPhiPT75");
   Add2DPlot(PdfFile, InputFile, "HJetEtaPhiPT100");
   Add2DPlot(PdfFile, InputFile, "HJetEtaPhiPT125");

   Add1DPlot(PdfFile, InputFile, "HTrackMETX");
   Add1DPlot(PdfFile, InputFile, "HTrackMETY");
   Add1DPlot(PdfFile, InputFile, "HTrackMET");
   Add1DPlot(PdfFile, InputFile, "HTrackMETXPeripheral");
   Add1DPlot(PdfFile, InputFile, "HTrackMETYPeripheral");
   Add1DPlot(PdfFile, InputFile, "HTrackMETPeripheral");
   Add1DPlot(PdfFile, InputFile, "HPositiveTrackMETX");
   Add1DPlot(PdfFile, InputFile, "HPositiveTrackMETY");
   Add1DPlot(PdfFile, InputFile, "HPositiveTrackMET");
   Add1DPlot(PdfFile, InputFile, "HPositiveTrackMETXPeripheral");
   Add1DPlot(PdfFile, InputFile, "HPositiveTrackMETYPeripheral");
   Add1DPlot(PdfFile, InputFile, "HPositiveTrackMETPeripheral");
   
   AddMirrorPlot(PdfFile, InputFile, "HTrackMETX");
   AddMirrorPlot(PdfFile, InputFile, "HTrackMETXPeripheral");
   AddMirrorPlot(PdfFile, InputFile, "HPositiveTrackMETX");
   AddMirrorPlot(PdfFile, InputFile, "HPositiveTrackMETXPeripheral");
   
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID2PT2MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID4PT2MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID5PT2MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID6PT2MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID7PT2MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID22PT2MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID23PT2MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID2PT5MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID4PT5MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID5PT5MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID6PT5MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID7PT5MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID22PT5MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID23PT5MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID2PT10MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID4PT10MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID5PT10MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID6PT10MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID7PT10MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID22PT10MVA090", "colz");
   PdfFile.AddHistogramFromFile(InputFile, "HTrackEtaPhiID23PT10MVA090", "colz");

   InputFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void Add1DPlot(PdfFileHelper &PdfFile, TFile &File, string Prefix)
{
   PdfFile.AddTextPage(Prefix);

   TCanvas Canvas;

   vector<string> Labels = {"MVA090", "MVA091", "MVA092", "MVA093", "MVA094", "MVA095", "MVA096", "MVA097", "MVA098", "MVA099", "MVA100"};

   TLegend Legend(0.6, 0.85, 0.85, 0.45);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);

   vector<int> Colors = {kBlack, kRed, kBlue, kGreen + 3, kYellow + 3, kCyan, kBlack, kRed, kBlue, kGreen + 3, kYellow + 3};
   vector<int> Styles = {kSolid, kSolid, kSolid, kSolid, kSolid, kSolid, kDashed, kDashed, kDashed, kDashed, kDashed};

   string Option = "";
   for(int i = 0; i < 11; i++)
   {
      TH1D *H = (TH1D *)File.Get(Form("%s%s", Prefix.c_str(), Labels[i].c_str()));
      
      if(H == nullptr)
         continue;

      H->SetLineWidth(2);
      H->SetLineColor(Colors[i]);
      H->SetLineStyle(Styles[i]);

      H->SetStats(0);
      H->Draw(Option.c_str());
      Option = "same";

      Legend.AddEntry(H, Labels[i].c_str(), "l");
   }

   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);
}

void AddComparisonPlot(PdfFileHelper &PdfFile, TFile &File, string Prefix1, string Prefix2, string Prefix3, string Prefix4)
{
   vector<string> Prefix(4);
   Prefix[0] = Prefix1;
   Prefix[1] = Prefix2;
   Prefix[2] = Prefix3;
   Prefix[3] = Prefix4;
   PdfFile.AddTextPage(Prefix);

   TCanvas Canvas;

   vector<string> Labels = {"MVA090", "MVA091", "MVA092", "MVA093", "MVA094", "MVA095", "MVA096", "MVA097", "MVA098", "MVA099", "MVA100"};

   for(int i = 0; i < 11; i++)
   {
      TH1D *H1 = (TH1D *)File.Get(Form("%s%s", Prefix1.c_str(), Labels[i].c_str()));
      TH1D *H2 = (TH1D *)File.Get(Form("%s%s", Prefix2.c_str(), Labels[i].c_str()));
      TH1D *H3 = (TH1D *)File.Get(Form("%s%s", Prefix3.c_str(), Labels[i].c_str()));
      TH1D *H4 = (TH1D *)File.Get(Form("%s%s", Prefix4.c_str(), Labels[i].c_str()));
      
      if(H1 == nullptr || H2 == nullptr || H3 == nullptr || H4 == nullptr)
         continue;

      H1->SetStats(0);
      H1->SetTitle(Form("%s", Labels[i].c_str()));

      H1->SetLineWidth(2);
      H2->SetLineWidth(2);
      H3->SetLineWidth(2);
      H4->SetLineWidth(2);
      
      H1->SetLineColor(kMagenta);
      H2->SetLineColor(kBlack);
      H3->SetLineColor(kGreen + 3);
      H4->SetLineColor(kCyan);
      
      H1->SetLineStyle(kSolid);
      H2->SetLineStyle(kSolid);
      H3->SetLineStyle(kSolid);
      H4->SetLineStyle(kSolid);

      H1->Draw();
      H2->Draw("same");
      H3->Draw("same");
      H4->Draw("same");

      TLegend Legend(0.5, 0.8, 0.8, 0.6);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.035);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.AddEntry(H1, "-2.5 < #eta < -1.5", "l");
      Legend.AddEntry(H2, "-1.5 < #eta < 0.0", "l");
      Legend.AddEntry(H3, "0.0 < #eta < 1.5", "l");
      Legend.AddEntry(H4, "1.5 < #eta < 2.5", "l");
      Legend.Draw();

      Canvas.SetLogy();
      PdfFile.AddCanvas(Canvas);
   }
}

void AddMirrorPlot(PdfFileHelper &PdfFile, TFile &File, string Prefix)
{
   PdfFile.AddTextPage(Prefix);

   TCanvas Canvas;

   vector<string> Labels = {"MVA090", "MVA091", "MVA092", "MVA093", "MVA094", "MVA095", "MVA096", "MVA097", "MVA098", "MVA099", "MVA100"};

   for(int i = 0; i < 11; i++)
   {
      TH1D *H1 = (TH1D *)File.Get(Form("%s%s", Prefix.c_str(), Labels[i].c_str()));
      
      if(H1 == nullptr)
         continue;

      int N = H1->GetNbinsX();

      TH1D *H2 = (TH1D *)H1->Clone("Mirror");
      for(int iB = 1; iB <= N; iB++)
         H2->SetBinContent(iB, H1->GetBinContent(N - (iB - 1)));

      H1->SetStats(0);
      H1->SetTitle(Form("%s", Labels[i].c_str()));

      H1->SetLineWidth(2);
      H2->SetLineWidth(2);
      
      H1->SetLineColor(kMagenta);
      H2->SetLineColor(kCyan);
      
      H1->SetLineStyle(kSolid);
      H2->SetLineStyle(kSolid);

      H1->Draw();
      H2->Draw("same");

      TLegend Legend(0.5, 0.8, 0.8, 0.6);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.035);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.AddEntry(H1, "Plot", "l");
      Legend.AddEntry(H2, "Mirror", "l");
      Legend.Draw();

      Canvas.SetLogy();
      PdfFile.AddCanvas(Canvas);
      
      delete H2;
   }
}

void Add2DPlot(PdfFileHelper &PdfFile, TFile &File, string Prefix)
{
   PdfFile.AddTextPage(Prefix);

   vector<string> Labels = {"MVA085", "MVA090", "MVA091", "MVA092", "MVA093", "MVA094", "MVA095", "MVA096", "MVA097", "MVA098", "MVA099", "MVA100"};

   for(int i = 0; i < 12; i++)
   {
      TH1D *H = (TH1D *)File.Get(Form("%s%s", Prefix.c_str(), Labels[i].c_str()));
      
      if(H == nullptr)
         continue;

      H->SetStats(0);
      H->SetTitle(Form("%s, (%s)", H->GetTitle(), Labels[i].c_str()));
      PdfFile.AddPlot(H, "colz");
   }
}



