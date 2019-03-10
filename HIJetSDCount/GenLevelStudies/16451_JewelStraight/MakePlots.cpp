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
   string Title, int Bins, double Min, double Max, double YMin, double YMax, double LogY = false);
void TidyHistogram(TH1D *H, int Color);

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("SummaryPlots.pdf");
   PdfFile.AddTextPage("Jewel summary plots");

   vector<TFile *> File;
   vector<TTree *> Tree;

   File.push_back(TFile::Open("16451.vac.root"));
   File.push_back(TFile::Open("16451.0.root"));
   File.push_back(TFile::Open("16451.1.root.no"));
   File.push_back(TFile::Open("16451.2.root.no"));
   File.push_back(TFile::Open("16451.3.root"));
   File.push_back(TFile::Open("16451.4.root.no"));
   File.push_back(TFile::Open("16451.5.root.no"));
   File.push_back(TFile::Open("16451.6.root.no"));
   File.push_back(TFile::Open("16451.7.root"));
   File.push_back(TFile::Open("16451.8.root"));

   int N = File.size();

   for(int i = 0; i < N; i++)
   {
      if(File[i] == NULL)
         Tree.push_back(NULL);
      else
         Tree.push_back((TTree *)File[i]->Get("T"));
   }

   AddPlot(PdfFile, Tree, "GenJetPT", "Weight",
      ";Gen Jet PT;", 50, 0, 400, 1e-7, 1, true);
   AddPlot(PdfFile, Tree, "abs(GenJetEta)", "Weight * (GenJetPT > 100)",
      "Jet PT > 100;Gen Jet |Eta|;", 20, 0, 4, 0, 1, false);
   AddPlot(PdfFile, Tree, "GenSDDR", "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5)",
      "Jet PT = 100-200, |eta| < 1.5;Gen Jet DR;", 15, 0, 0.55, 0, 10, false);
   AddPlot(PdfFile, Tree, "GenSDDR", "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5)",
      "Jet PT = 100-200, |eta| < 1.5;Gen Jet DR;", 12, 0.1, 0.55, 0, 10, false);
   AddPlot(PdfFile, Tree, "GenSDMass/GenJetPT", "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR > 0.1)",
      "Jet PT = 100-200, |eta| < 1.5, DR > 0.1;Gen Jet Mass/PT;", 15, 0.0, 0.30, 0, 20, false);
   AddPlot(PdfFile, Tree, "GenSDCount", "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR > 0.0)",
      "Jet PT = 100-200, |eta| < 1.5;n_{SD}^{(0)};", 15, 0, 15, 0, 0.35, false);
   AddPlot(PdfFile, Tree, "log(GenSDCKappa1)/log(10)", "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR > 0.0)",
      "Jet PT = 100-200, |eta| < 1.5;log_{10}(n_{SD}^{(1)});", 20, -1.5, 2, 0, 4, false);
   AddPlot(PdfFile, Tree, "log(GenSDCKappa1)/log(10)", "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR > 0.0)",
      "Jet PT = 100-200, |eta| < 1.5;log_{10}(n_{SD}^{(1)});", 20, -1.5, 2, 0.001, 10, true);
   AddPlot(PdfFile, Tree, "log(GenSDCKappa2)/log(10)", "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR > 0.0)",
      "Jet PT = 100-200, |eta| < 1.5;log_{10}(n_{SD}^{(2)});", 20, -2.5, 2, 0, 3, false);
   AddPlot(PdfFile, Tree, "log(GenSDCKappa2)/log(10)", "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR > 0.0)",
      "Jet PT = 100-200, |eta| < 1.5;log_{10}(n_{SD}^{(2)});", 20, -2.5, 2, 0.0001, 10, true);
   AddPlot(PdfFile, Tree, "log(GenSDCKappa3)/log(10)", "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR > 0.0)",
      "Jet PT = 100-200, |eta| < 1.5;log_{10}(n_{SD}^{(3)});", 20, -3.5, 2, 0, 2, false);
   AddPlot(PdfFile, Tree, "log(GenSDCKappa3)/log(10)", "Weight * (GenJetPT > 100 && GenJetPT < 200 && abs(GenJetEta) < 1.5 && GenSDDR > 0.0)",
      "Jet PT = 100-200, |eta| < 1.5;log_{10}(n_{SD}^{(3)});", 20, -3.5, 2, 0.00001, 10, true);

   for(int i = 0; i < N; i++)
      if(File[i] != NULL)
         delete File[i];

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, vector<TTree *> &Tree, string ToPlot, string Selection,
   string Title, int Bins, double Min, double Max, double YMin, double YMax, double LogY)
{
   static int ID = 0;
   ID = ID + 1;

   int N = Tree.size();

   vector<TH1D *> H;

   for(int i = 0; i < N; i++)
      H.push_back(new TH1D(Form("H%d%d", ID, i), Title.c_str(), Bins, Min, Max));
   for(int i = 0; i < N; i++)
      H[i]->Sumw2();

   for(int i = 0; i < N; i++)
   {
      if(Tree[i] == NULL)
         continue;

      Tree[i]->Draw(Form("%s>>H%d%d", ToPlot.c_str(), ID, i), Selection.c_str());
   }

   int Color[] = {kGreen, kBlue, kMagenta + 2, kMagenta + 1, kMagenta - 4, kMagenta,
      kMagenta - 7, kMagenta - 9, kYellow + 1, kYellow};
   for(int i = 0; i < N; i++)
      TidyHistogram(H[i], Color[i]);

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
   }

   string Labels[] = {"vacuum", "0%-10%", "10%-20%", "20%-30%", "30%-40%", "40%-50%", "50%-60%", "60%-70%", "70%-80%", "80%-100%"};

   TLegend Legend(0.6, 0.45, 0.8, 0.85);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   for(int i = 0; i < N; i++)
   {
      if(Tree[i] != NULL)
         Legend.AddEntry(H[i], Labels[i].c_str(), "lp");
      else
         Legend.AddEntry("", "", "");
   }
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
}

void TidyHistogram(TH1D *H, int Color)
{
   if(H == NULL)
      return;

   H->SetLineColor(Color);
   H->SetMarkerColor(Color);
   H->SetLineWidth(2);
   H->SetMarkerStyle(20);

   double BinSize = (H->GetXaxis()->GetBinUpEdge(H->GetNbinsX()) - H->GetXaxis()->GetBinLowEdge(1)) / H->GetNbinsX();

   if(H->Integral() > 0)
      H->Scale(1 / H->Integral() / BinSize);
}




