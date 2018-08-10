#ifndef GRAPHS_17375_H
#define GRAPHS_17375_H

#include <iostream>

#include "TGraphAsymmErrors.h"
#include "TLegend.h"
#include "TFile.h"

#include "PlotHelper3Forward.h"

class Graphs;
TGraphAsymmErrors *Divide(TFile &F1, std::string N1, TFile &F2, std::string N2, int Rebin);
void AddFourPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEG140, TGraphAsymmErrors *TkEG200,
   TGraphAsymmErrors *TkIsoEG140, TGraphAsymmErrors *TkIsoEG200, std::string Title, std::string Tag1, std::string Tag2);
void AddTwoPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEM140, TGraphAsymmErrors *TkEM200,
   std::string Title, std::string Tag);
void AddSpectrum(PdfFileHelper &PdfFile, TFile &F, std::string N, std::string Title);

class Graphs
{
public:
   TGraphAsymmErrors *GPT;
   TGraphAsymmErrors *GPT_Rebin;
   TGraphAsymmErrors *GPT_Rebin2;
   TGraphAsymmErrors *GPTEta10;
   TGraphAsymmErrors *GPTEta10_Rebin;
   TGraphAsymmErrors *GPTEta10_Rebin2;
   TGraphAsymmErrors *GPTEtaLarge;
   TGraphAsymmErrors *GPTEtaLarge_Rebin;
   TGraphAsymmErrors *GPTEtaLarge_Rebin2;
   TGraphAsymmErrors *GEta;
   TGraphAsymmErrors *GEtaPT20;
   TGraphAsymmErrors *GEtaPT25;
   TGraphAsymmErrors *GEtaPT200;
public:
   Graphs(TFile &F1, std::string Tag1, TFile &F2, std::string Tag2,
      std::string Type = "TkEG", std::string PU = "PU140");
   ~Graphs();
   void AddIndividualPlots(PdfFileHelper &PdfFile);
};

Graphs::Graphs(TFile &F1, std::string Tag1, TFile &F2, std::string Tag2,
   std::string Type, std::string PU)
{
   GPT                = Divide(F1, Tag1 + "_PT_000000",         F2, Tag2 + "_PT_000000",         5);
   GPT_Rebin          = Divide(F1, Tag1 + "_PT_000000",         F2, Tag2 + "_PT_000000",         -1);
   GPT_Rebin2         = Divide(F1, Tag1 + "_PT_000000",         F2, Tag2 + "_PT_000000",         -2);
   GPTEta10           = Divide(F1, Tag1 + "_PTEta10_000000",    F2, Tag2 + "_PTEta10_000000",    5);
   GPTEta10_Rebin     = Divide(F1, Tag1 + "_PTEta10_000000",    F2, Tag2 + "_PTEta10_000000",    -1);
   GPTEta10_Rebin2    = Divide(F1, Tag1 + "_PTEta10_000000",    F2, Tag2 + "_PTEta10_000000",    -2);
   GPTEtaLarge        = Divide(F1, Tag1 + "_PTEtaLarge_000000", F2, Tag2 + "_PTEtaLarge_000000", 5);
   GPTEtaLarge_Rebin  = Divide(F1, Tag1 + "_PTEtaLarge_000000", F2, Tag2 + "_PTEtaLarge_000000", -1);
   GPTEtaLarge_Rebin2 = Divide(F1, Tag1 + "_PTEtaLarge_000000", F2, Tag2 + "_PTEtaLarge_000000", -2);
   GEta               = Divide(F1, Tag1 + "_Eta_000000",        F2, Tag2 + "_Eta_000000",        2);
   GEtaPT20           = Divide(F1, Tag1 + "_EtaPT20_000000",    F2, Tag2 + "_EtaPT20_000000",    2);
   GEtaPT25           = Divide(F1, Tag1 + "_EtaPT25_000000",    F2, Tag2 + "_EtaPT25_000000",    2);
   GEtaPT200          = Divide(F1, Tag1 + "_EtaPT200_000000",   F2, Tag2 + "_EtaPT200_000000",   2);

   GPT->SetTitle((Type + ", PT, " + PU).c_str());
   GPT_Rebin->SetTitle((Type + ", PT, " + PU).c_str());
   GPT_Rebin2->SetTitle((Type + ", PT, " + PU).c_str());
   GPTEta10->SetTitle((Type + ", PT (|eta| > 1.0), " + PU).c_str());
   GPTEta10_Rebin->SetTitle((Type + ", PT (|eta| > 1.0), " + PU).c_str());
   GPTEta10_Rebin2->SetTitle((Type + ", PT (|eta| > 1.0), " + PU).c_str());
   GPTEtaLarge->SetTitle((Type + ", PT (|eta| < 1.0), " + PU).c_str());
   GPTEtaLarge_Rebin->SetTitle((Type + ", PT (|eta| < 1.0), " + PU).c_str());
   GPTEtaLarge_Rebin2->SetTitle((Type + ", PT (|eta| < 1.0), " + PU).c_str());
   GEta->SetTitle((Type + ", Eta, " + PU).c_str());
   GEtaPT20->SetTitle((Type + ", eta (PT > 20), " + PU).c_str());
   GEtaPT25->SetTitle((Type + ", eta (PT > 25), " + PU).c_str());
   GEtaPT200->SetTitle((Type + ", eta (PT > 200), " + PU).c_str());

   GPT->GetXaxis()->SetTitle("PT");
   GPT_Rebin->GetXaxis()->SetTitle("PT");
   GPT_Rebin2->GetXaxis()->SetTitle("PT");
   GPTEta10->GetXaxis()->SetTitle("PT");
   GPTEta10_Rebin->GetXaxis()->SetTitle("PT");
   GPTEta10_Rebin2->GetXaxis()->SetTitle("PT");
   GPTEtaLarge->GetXaxis()->SetTitle("PT");
   GPTEtaLarge_Rebin->GetXaxis()->SetTitle("PT");
   GPTEtaLarge_Rebin2->GetXaxis()->SetTitle("PT");
   GEta->GetXaxis()->SetTitle("Eta");
   GEtaPT20->GetXaxis()->SetTitle("Eta");
   GEtaPT25->GetXaxis()->SetTitle("Eta");
   GEtaPT200->GetXaxis()->SetTitle("Eta");
}

Graphs::~Graphs()
{
   if(GPT == NULL)                 delete GPT;
   if(GPT_Rebin == NULL)           delete GPT_Rebin;         
   if(GPT_Rebin2 == NULL)          delete GPT_Rebin2;
   if(GPTEta10 == NULL)            delete GPTEta10;
   if(GPTEta10_Rebin == NULL)      delete GPTEta10_Rebin;
   if(GPTEta10_Rebin2 == NULL)     delete GPTEta10_Rebin2;
   if(GPTEtaLarge == NULL)         delete GPTEtaLarge;
   if(GPTEtaLarge_Rebin == NULL)   delete GPTEtaLarge_Rebin;
   if(GPTEtaLarge_Rebin2 == NULL)  delete GPTEtaLarge_Rebin2;
   if(GEta == NULL)                delete GEta;
   if(GEtaPT20 == NULL)            delete GEtaPT20;
   if(GEtaPT25 == NULL)            delete GEtaPT25;
   if(GEtaPT200 == NULL)           delete GEtaPT200;
}

void Graphs::AddIndividualPlots(PdfFileHelper &PdfFile)
{
   PdfFile.AddPlot(GPT, "ap");
   PdfFile.AddPlot(GPT_Rebin, "ap");
   PdfFile.AddPlot(GPT_Rebin2, "ap");
   PdfFile.AddPlot(GPTEta10, "ap");
   PdfFile.AddPlot(GPTEta10_Rebin, "ap");
   PdfFile.AddPlot(GPTEta10_Rebin2, "ap");
   PdfFile.AddPlot(GPTEtaLarge, "ap");
   PdfFile.AddPlot(GPTEtaLarge_Rebin, "ap");
   PdfFile.AddPlot(GPTEtaLarge_Rebin2, "ap");
   PdfFile.AddPlot(GEta, "ap");
   PdfFile.AddPlot(GEtaPT20, "ap");
   PdfFile.AddPlot(GEtaPT25, "ap");
   PdfFile.AddPlot(GEtaPT200, "ap");
}

TGraphAsymmErrors *Divide(TFile &F1, std::string N1, TFile &F2, std::string N2, int Rebin)
{
   cout << N1 << " " << N2 << endl;

   TGraphAsymmErrors *Result = NULL;

   TH1D *H1 = (TH1D *)F1.Get(N1.c_str());
   TH1D *H2 = (TH1D *)F2.Get(N2.c_str());

   if(H1 == NULL || H2 == NULL)
      return (new TGraphAsymmErrors);

   TH1D *H1Temp = NULL;
   TH1D *H2Temp = NULL;

   if(Rebin >= 1)
   {
      H1Temp = (TH1D *)H1->Clone("H1Temp");
      H2Temp = (TH1D *)H2->Clone("H2Temp");

      H1Temp->Rebin(Rebin);
      H2Temp->Rebin(Rebin);
   }
   
   if(Rebin < 0)
   {
      // this is the PT case - let's make variable binned histograms
      double Binning1[24] =
         {4, 6, 8, 10, 12, 14, 16, 18,
         20, 22, 24, 26, 28, 30, 34, 38, 42, 46,
         50, 60, 70, 90, 110, 150};
      double Binning2[24] =
         {14, 24, 32, 40, 48, 56, 64, 72,
         80, 88, 96, 104, 112, 120, 136, 152, 168, 184,
         200, 240, 280, 360, 440, 600};

      double Binning[24];

      if(Rebin == -2)
         for(int i = 0; i < 24; i++)
            Binning[i] = Binning2[i];
      else
         for(int i = 0; i < 24; i++)
            Binning[i] = Binning1[i];

      H1Temp = new TH1D("H1Temp", "", 23, Binning);
      H2Temp = new TH1D("H2Temp", "", 23, Binning);

      H1Temp->Sumw2();
      H2Temp->Sumw2();

      int N = H1->GetNbinsX();
      for(int i = 1; i <= N; i++)
      {
         for(int j = 0; j < H1->GetBinContent(i); j++)
            H1Temp->Fill(H1->GetBinCenter(i));
         for(int j = 0; j < H2->GetBinContent(i); j++)
            H2Temp->Fill(H2->GetBinCenter(i));
      }

      H1Temp->SetBinContent(0, 0);
      H1Temp->SetBinContent(H1Temp->GetNbinsX() + 1, 0);
      H2Temp->SetBinContent(0, 0);
      H2Temp->SetBinContent(H1Temp->GetNbinsX() + 1, 0);
   }

   Result = new TGraphAsymmErrors;
   Result->Divide(H1Temp, H2Temp);

   if(H1Temp != NULL)
      delete H1Temp;
   if(H2Temp != NULL)
      delete H2Temp;

   if(Result == NULL)
      return (new TGraphAsymmErrors);
   return Result;
}

void AddFourPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEG140, TGraphAsymmErrors *TkEG200,
   TGraphAsymmErrors *TkIsoEG140, TGraphAsymmErrors *TkIsoEG200, std::string Title, std::string Tag1, std::string Tag2)
{
   if(TkEG140 == NULL)
      return;
   if(TkEG200 == NULL)
      return;
   if(TkIsoEG140 == NULL)
      return;
   if(TkIsoEG200 == NULL)
      return;

   TkEG140->SetTitle(Title.c_str());

   TkEG140->SetMarkerColor(kBlue);
   TkEG200->SetMarkerColor(kRed);
   TkIsoEG140->SetMarkerColor(kGreen - 3);
   TkIsoEG200->SetMarkerColor(kYellow + 3);
   
   TkEG140->SetLineColor(kBlue);
   TkEG200->SetLineColor(kRed);
   TkIsoEG140->SetLineColor(kGreen - 3);
   TkIsoEG200->SetLineColor(kYellow + 3);

   TCanvas C;

   TkEG140->Draw("ap");
   
   TH2D HWorld("HWorld", "", 100, TkEG140->GetXaxis()->GetXmin(), TkEG140->GetXaxis()->GetXmax(), 100, 0, 1.05);
   HWorld.SetTitle(Title.c_str());
   HWorld.GetXaxis()->SetTitle(TkEG140->GetXaxis()->GetTitle());
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   TkEG140->Draw("p");
   TkEG200->Draw("p");
   TkIsoEG140->Draw("p");
   TkIsoEG200->Draw("p");

   TLegend Legend(0.35, 0.15, 0.65, 0.35);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(TkEG140,    Form("%s, PU140", Tag1.c_str()), "pl");
   Legend.AddEntry(TkEG200,    Form("%s, PU200", Tag1.c_str()), "pl");
   Legend.AddEntry(TkIsoEG140, Form("%s, PU140", Tag2.c_str()), "pl");
   Legend.AddEntry(TkIsoEG200, Form("%s, PU200", Tag2.c_str()), "pl");
   Legend.Draw();

   TGraph G1, G2, G3;
   G1.SetPoint(0, -999, 1);
   G1.SetPoint(1, +999, 1);
   G2.SetPoint(0, -999, 0.90);
   G2.SetPoint(1, +999, 0.90);
   G3.SetPoint(0, 25, 0);
   G3.SetPoint(1, 25, 5);
   G2.SetLineStyle(kDashed);
   G3.SetLineStyle(kDotted);

   G1.Draw("l");
   G2.Draw("l");
   G3.Draw("l");

   PdfFile.AddCanvas(C);
}

void AddTwoPlots(PdfFileHelper &PdfFile, TGraphAsymmErrors *TkEM140, TGraphAsymmErrors *TkEM200, std::string Title, std::string Tag)
{
   if(TkEM140 == NULL)
      return;
   if(TkEM200 == NULL)
      return;

   TkEM140->SetTitle(Title.c_str());

   TkEM140->SetMarkerColor(kBlue);
   TkEM200->SetMarkerColor(kRed);
   
   TkEM140->SetLineColor(kBlue);
   TkEM200->SetLineColor(kRed);

   TCanvas C;

   TkEM140->Draw("ap");

   TH2D HWorld("HWorld", "", 100, TkEM140->GetXaxis()->GetXmin(), TkEM140->GetXaxis()->GetXmax(), 100, 0, 1.05);
   HWorld.SetTitle(Title.c_str());
   HWorld.GetXaxis()->SetTitle(TkEM140->GetXaxis()->GetTitle());
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   TkEM140->Draw("p");
   TkEM200->Draw("p");

   TLegend Legend(0.35, 0.15, 0.65, 0.35);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.AddEntry(TkEM140, Form("%s, PU140", Tag.c_str()), "pl");
   Legend.AddEntry(TkEM200, Form("%s, PU200", Tag.c_str()), "pl");
   Legend.Draw();

   TGraph G1, G2, G3;
   G1.SetPoint(0, -999, 1);
   G1.SetPoint(1, +999, 1);
   G2.SetPoint(0, -999, 0.90);
   G2.SetPoint(1, +999, 0.90);
   G3.SetPoint(0, 25, 0);
   G3.SetPoint(1, 25, 5);
   G2.SetLineStyle(kDashed);
   G3.SetLineStyle(kDotted);

   G1.Draw("l");
   G2.Draw("l");
   G3.Draw("l");

   PdfFile.AddCanvas(C);
}

void AddSpectrum(PdfFileHelper &PdfFile, TFile &F, std::string N, std::string Title)
{
   TH1D *H = (TH1D *)F.Get(N.c_str())->Clone("Yay");

   H->SetStats(0);
   H->SetTitle(Title.c_str());
   H->SetMinimum(0);

   PdfFile.AddPlot(H);

   delete H;
}

#endif
