#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main();
void AddPlot(PdfFileHelper &PdfFile, vector<TTree *> &Tree, string ToPlot, string Selection,
   string Title, int Bins, double Min, double Max, double YMin, double YMax, bool LogY = false, double Normalize = 0,
   bool DoRatio = false);
void TidyHistogram(TH1D *H, int Color, double Normalize);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("SummaryPlots.pdf");
   PdfFile.AddTextPage("Jewel summary plots");

   vector<TFile *> File;
   vector<TTree *> Tree;

   File.push_back(TFile::Open("16452.vac.root"));
   File.push_back(TFile::Open("16452.0.root"));
   File.push_back(TFile::Open("16451.1.root.no"));
   File.push_back(TFile::Open("16451.2.root.no"));
   File.push_back(TFile::Open("16451.3.root.no"));
   File.push_back(TFile::Open("16451.4.root.no"));
   File.push_back(TFile::Open("16451.5.root.no"));
   File.push_back(TFile::Open("16451.6.root.no"));
   File.push_back(TFile::Open("16451.7.root.no"));
   File.push_back(TFile::Open("16452.8.root"));

   int N = File.size();

   for(int i = 0; i < N; i++)
   {
      if(File[i] == NULL)
         Tree.push_back(NULL);
      else
         Tree.push_back((TTree *)File[i]->Get("T"));
   }

   AddPlot(PdfFile, Tree, "GenJetPT", "Weight * 100000 * (abs(GenJetEta) < 2)",
      "No self normalization;Gen Jet PT;", 10, 0, 400, 1e-7, 1, true, 1, true);
   AddPlot(PdfFile, Tree, "GenJetPT", "Weight",
      ";Gen Jet PT;", 50, 0, 400, 1e-7, 1, true);
   AddPlot(PdfFile, Tree, "abs(GenJetEta)", "Weight * (GenJetPT > 100)",
      "Jet PT > 100;Gen Jet |Eta|;", 20, 0, 4, 0, 1, false);
   
   /*
   for(int i = 0; i < 9; i++)
   {
      AddPlot(PdfFile, Tree, Form("GenSDDR[%d]", i),
         "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5)",
         Form("Jet PT = 100-200, |eta| < 1.5 (SDC%d);Gen Jet DR;", i), 15, 0, 0.55, 0, 10, false);
      AddPlot(PdfFile, Tree, Form("GenSDDR[%d]", i),
         "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5)",
         Form("Jet PT = 100-200, |eta| < 1.5 (SDC%d);Gen Jet DR;", i), 12, 0.1, 0.55, 0, 10, false);
      AddPlot(PdfFile, Tree, Form("GenSDMass[%d]/GenJetPT", i),
         Form("Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR[%d] > 0.1)", i),
         Form("Jet PT = 100-200, |eta| < 1.5, DR > 0.1 (SDC%d);Gen Jet Mass/PT;", i), 15, 0.0, 0.30, 0, 20, false);

      AddPlot(PdfFile, Tree, Form("GenSDCount[%d]", i),
         "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5)",
         Form("Jet PT = 100-200, |eta| < 1.5 (SDC%d);n_{SD}^{(0)};", i), 20, 0, 20, 0, 0.35, false);
      AddPlot(PdfFile, Tree, Form("log(GenSDCKappa1[%d]/GenSDCount[%d])/log(10)", i, i),
         Form("Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR[%d] > 0.0)", i),
         Form("Jet PT = 100-200, |eta| < 1.5 (SDC%d);log_{10}(#bar{n}_{SD}^{(1)});", i), 30, -2, 0.5, 0, 4, false);
      AddPlot(PdfFile, Tree, Form("log(GenSDCKappa1[%d]/GenSDCount[%d])/log(10)", i, i),
         Form("Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR[%d] > 0.0)", i),
         Form("Jet PT = 100-200, |eta| < 1.5 (SDC%d);log_{10}(#bar{n}_{SD}^{(1)});", i), 30, -2, 0.5, 0.001, 10, true);
      AddPlot(PdfFile, Tree, Form("log(GenSDCKappa2[%d]/GenSDCount[%d])/log(10)", i, i),
         Form("Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR[%d] > 0.0)", i),
         Form("Jet PT = 100-200, |eta| < 1.5 (SDC%d);log_{10}(#bar{n}_{SD}^{(2)});", i), 30, -3, 0.5, 0, 3, false);
      AddPlot(PdfFile, Tree, Form("log(GenSDCKappa2[%d]/GenSDCount[%d])/log(10)", i, i),
         Form("Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR[%d] > 0.0)", i),
         Form("Jet PT = 100-200, |eta| < 1.5 (SDC%d);log_{10}(#bar{n}_{SD}^{(2)});", i), 30, -3, 0.5, 0.0001, 10, true);
      AddPlot(PdfFile, Tree, Form("log(GenSDCKappa3[%d]/GenSDCount[%d])/log(10)", i, i),
         Form("Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR[%d] > 0.0)", i),
         Form("Jet PT = 100-200, |eta| < 1.5 (SDC%d);log_{10}(#bar{n}_{SD}^{(3)});", i), 30, -3.5, 1, 0, 2, false);
      AddPlot(PdfFile, Tree, Form("log(GenSDCKappa3[%d]/GenSDCount[%d])/log(10)", i, i),
         Form("Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR[%d] > 0.0)", i),
         Form("Jet PT = 100-200, |eta| < 1.5 (SDC%d);log_{10}(#bar{n}_{SD}^{(3)});", i), 30, -3.5, 1, 0.00001, 10, true);
   }
   */

   for(int i = 0; i < N; i++)
      if(File[i] != NULL)
         delete File[i];

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, vector<TTree *> &Tree, string ToPlot, string Selection,
   string Title, int Bins, double Min, double Max, double YMin, double YMax, bool LogY, double Normalize, bool DoRatio)
{
   static int ID = 0;
   ID = ID + 1;

   int N = Tree.size();

   vector<TH1D *> H;
   vector<TGraph *> G;

   for(int i = 0; i < N; i++)
   {
      H.push_back(new TH1D(Form("H%d%d", ID, i), Title.c_str(), Bins, Min, Max));
      G.push_back(new TGraph);
   }
   for(int i = 0; i < N; i++)
      H[i]->Sumw2();

   for(int i = 0; i < N; i++)
   {
      if(Tree[i] == NULL)
         continue;

      Tree[i]->Draw(Form("%s>>H%d%d", ToPlot.c_str(), ID, i), Selection.c_str());

      G[i]->SetPoint(0, H[i]->GetMean(), -1e10);
      G[i]->SetPoint(1, H[i]->GetMean(), 1e10);
   }

   int Color[] = {kGreen, kBlue, kMagenta + 2, kMagenta + 1, kMagenta - 4, kMagenta,
      kMagenta - 7, kMagenta - 9, kYellow + 1, kYellow};
   for(int i = 0; i < N; i++)
   {
      double X = 1;
      if(i == 0)
         X = 100;
      if(i == 1)
         X = 10;
      if(Normalize == 0)
         X = 0;
      TidyHistogram(H[i], Color[i], X);
      G[i]->SetLineStyle(kDashed);
      G[i]->SetLineColor(Color[i]);
   }

   TCanvas Canvas;

   if(LogY == true)
      Canvas.SetLogy();

   TH2D HWorld("HWorld", Title.c_str(), Bins, Min, Max, 100, YMin, YMax);
   HWorld.SetStats(0);
   HWorld.Draw();

   for(int i = 0; i < N; i++)
   {
      if(Tree[i] == NULL)
         continue;
      H[i]->Draw("hist same");
      H[i]->Draw("same");
      G[i]->Draw("l");
   }

   string Labels[] = {"vacuum", "0%-10%", "10%-20%", "20%-30%", "30%-40%", "40%-50%", "50%-60%", "60%-70%", "70%-80%", "80%-100%"};

   TLegend Legend(0.6, 0.45, 0.8, 0.85);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   for(int i = 0; i < N; i++)
   {
      if(Tree[i] != NULL)
         Legend.AddEntry(H[i], Labels[i].c_str(), "lp");
      else
         Legend.AddEntry("", "", "");
   }
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   if(DoRatio == true)
   {
      for(int i = 1; i < N; i++)
         H[i]->Divide(H[0]);

      TH2D HWorld2("HWorld2", Title.c_str(), Bins, Min, Max, 100, 0, 2);
      HWorld2.SetStats(0);
      HWorld2.Draw();

      HWorld2.GetYaxis()->SetTitle("Ratio to vacuum");

      for(int i = 1; i < N; i++)
      {
         if(Tree[i] == NULL)
            continue;

         H[i]->Draw("hist same");
         H[i]->Draw("same");
      }

      Canvas.SetLogy(false);

      PdfFile.AddCanvas(Canvas);
   }
}

void TidyHistogram(TH1D *H, int Color, double Normalize)
{
   if(H == NULL)
      return;

   H->SetLineColor(Color);
   H->SetMarkerColor(Color);
   H->SetLineWidth(2);
   H->SetMarkerStyle(20);

   double BinSize = (H->GetXaxis()->GetBinUpEdge(H->GetNbinsX()) - H->GetXaxis()->GetBinLowEdge(1)) / H->GetNbinsX();

   if(H->Integral() > 0 && Normalize == 0)
      H->Scale(1 / H->Integral() / BinSize);
   else if(Normalize > 0)
      H->Scale(1 / Normalize);
}




