#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLatex.h"

#include "SetStyle.h"
#include "CustomAssert.h"
#include "CommandLine.h"
#include "PlotHelper3.h"

#define MAX 1024

class JetSignature;
int main(int argc, char *argv[]);

class JetSignature
{
private:
   int Run, Lumi, Event;
   double RefPT, RefEta, RefPhi;
public:
   JetSignature(int run, int lumi, int event, double pt, double eta, double phi)
      : Run(run), Lumi(lumi), Event(event), RefPT(pt), RefEta(eta), RefPhi(phi)
   {
   }
   bool operator <(const JetSignature &other) const
   {
      double Tolerance = 1e-5;

      if(Run > other.Run)   return false;
      if(Run < other.Run)   return true;
      if(Lumi > other.Lumi)   return false;
      if(Lumi < other.Lumi)   return true;
      if(Event > other.Event)   return false;
      if(Event < other.Event)   return true;

      if(RefPT > other.RefPT + Tolerance)   return false;
      if(RefPT < other.RefPT - Tolerance)   return true;
      if(RefEta > other.RefEta + Tolerance)   return false;
      if(RefEta < other.RefEta - Tolerance)   return true;
      if(RefPhi > other.RefPhi + Tolerance)   return false;
      if(RefPhi < other.RefPhi - Tolerance)   return true;
      
      return false;
   }
};

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string TreeName = CL.Get("tree");
   string OutputFileName = CL.Get("output", "Output.pdf");

   TFile InputFile(InputFileName.c_str());

   TTree *Tree = (TTree *)InputFile.Get(TreeName.c_str());
   Assert(Tree != NULL, "Error getting input data");
   Assert(Tree->GetEntries() > 0, "No data in the input tree");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Jet profiles");

   int NJet;
   double RefPT[MAX], RefEta[MAX], RefPhi[MAX];
   double PUPT[MAX], PUEta[MAX], PUPhi[MAX], PUEMF[MAX];
   double PUCHF[MAX], PUCEF[MAX], PUNHF[MAX], PUNEF[MAX], PUMUF[MAX], PUHFHF[MAX], PUHFEF[MAX];
   double NoPUPT[MAX], NoPUEta[MAX], NoPUPhi[MAX], NoPUEMF[MAX];
   double NoPUCHF[MAX], NoPUCEF[MAX], NoPUNHF[MAX], NoPUNEF[MAX], NoPUMUF[MAX], NoPUHFHF[MAX], NoPUHFEF[MAX];
   double RecoDR[MAX];
   double Rho[MAX];
   int Run[MAX], Event[MAX], Lumi[MAX];

   Tree->SetBranchAddress("NJet",    &NJet);
   Tree->SetBranchAddress("RefPT",   &RefPT);
   Tree->SetBranchAddress("RefEta",  &RefEta);
   Tree->SetBranchAddress("RefPhi",  &RefPhi);
   Tree->SetBranchAddress("PUPT",    &PUPT);
   Tree->SetBranchAddress("PUEta",   &PUEta);
   Tree->SetBranchAddress("PUPhi",   &PUPhi);
   Tree->SetBranchAddress("PUEMF",   &PUEMF);
   Tree->SetBranchAddress("PUCHF",   &PUCHF);
   Tree->SetBranchAddress("PUCEF",   &PUCEF);
   Tree->SetBranchAddress("PUNHF",   &PUNHF);
   Tree->SetBranchAddress("PUNEF",   &PUNEF);
   Tree->SetBranchAddress("PUMUF",   &PUMUF);
   Tree->SetBranchAddress("PUHFHF",   &PUHFHF);
   Tree->SetBranchAddress("PUHFEF",   &PUHFEF);
   Tree->SetBranchAddress("NoPUPT",  &NoPUPT);
   Tree->SetBranchAddress("NoPUEta", &NoPUEta);
   Tree->SetBranchAddress("NoPUPhi", &NoPUPhi);
   Tree->SetBranchAddress("NoPUEMF", &NoPUEMF);
   Tree->SetBranchAddress("NoPUCHF",   &NoPUCHF);
   Tree->SetBranchAddress("NoPUCEF",   &NoPUCEF);
   Tree->SetBranchAddress("NoPUNHF",   &NoPUNHF);
   Tree->SetBranchAddress("NoPUNEF",   &NoPUNEF);
   Tree->SetBranchAddress("NoPUMUF",   &NoPUMUF);
   Tree->SetBranchAddress("NoPUHFHF",   &NoPUHFHF);
   Tree->SetBranchAddress("NoPUHFEF",   &NoPUHFEF);
   Tree->SetBranchAddress("RecoDR",  &RecoDR);
   Tree->SetBranchAddress("Rho",     &Rho);
   Tree->SetBranchAddress("Run",     &Run);
   Tree->SetBranchAddress("Lumi",    &Lumi);
   Tree->SetBranchAddress("Event",   &Event);

   Tree->GetEntry(0);

   map<JetSignature, int> LookUpTable;
   for(int iJ = 0; iJ < NJet; iJ++)
   {
      JetSignature Jet(Run[iJ], Lumi[iJ], Event[iJ], RefPT[iJ], RefEta[iJ], RefPhi[iJ]);
      LookUpTable.insert(pair<JetSignature, int>(Jet, iJ));
   }

   vector<TH1D *> hOffset(NJet);
   vector<TH1D *> hOffsetEcal(NJet);
   vector<TH1D *> hOffsetHcal(NJet);
   vector<TH1D *> hOffsetCH(NJet);
   vector<TH1D *> hOffsetCE(NJet);
   vector<TH1D *> hOffsetNH(NJet);
   vector<TH1D *> hOffsetNE(NJet);
   vector<TH1D *> hOffsetMU(NJet);
   vector<TH1D *> hOffsetHF(NJet);
   vector<TH1D *> hOffsetEF(NJet);
   vector<TH1D *> hRho(NJet);
   vector<TH2D *> hFraction(NJet);
   vector<TH1D *> hRefPT(NJet);
   vector<TH1D *> hPUPT(NJet);
   vector<TH1D *> hNoPUPT(NJet);
   vector<TH2D *> hOffsetRho(NJet);
   vector<TH2D *> hOffsetCHRho(NJet);
   vector<TH2D *> hOffsetCERho(NJet);
   vector<TH2D *> hOffsetNHRho(NJet);
   vector<TH2D *> hOffsetNERho(NJet);
   vector<TH2D *> hOffsetMURho(NJet);
   vector<TH2D *> hOffsetHFRho(NJet);
   vector<TH2D *> hOffsetEFRho(NJet);
   vector<TH2D *> hOffsetEcalRho(NJet);
   vector<TH2D *> hOffsetHcalRho(NJet);
   vector<TH1D *> hRecoDR(NJet);
   vector<TH1D *> hRecoDRWide(NJet);
   vector<TH2D *> hOffsetRecoDR(NJet);
   vector<TH2D *> hOffsetRecoDRWide(NJet);

   for(int iJ = 0; iJ < NJet; iJ++)
   {
      double Max = RefPT[iJ] * 1.2 + 20;
      double Min = max(0.0, RefPT[iJ] * 0.8 - 50);

      hOffset[iJ] = new TH1D(Form("hOffset_%d", iJ), ";Offset;", 150, -40, 40);
      hOffsetCH[iJ] = new TH1D(Form("hOffsetCH_%d", iJ), ";Offset (CH);", 150, -40, 40);
      hOffsetCE[iJ] = new TH1D(Form("hOffsetCE_%d", iJ), ";Offset (CE);", 150, -40, 40);
      hOffsetNH[iJ] = new TH1D(Form("hOffsetNH_%d", iJ), ";Offset (NH);", 150, -40, 40);
      hOffsetNE[iJ] = new TH1D(Form("hOffsetNE_%d", iJ), ";Offset (NE);", 150, -40, 40);
      hOffsetMU[iJ] = new TH1D(Form("hOffsetMU_%d", iJ), ";Offset (MU);", 150, -40, 40);
      hOffsetHF[iJ] = new TH1D(Form("hOffsetHF_%d", iJ), ";Offset (HF);", 150, -40, 40);
      hOffsetEF[iJ] = new TH1D(Form("hOffsetEF_%d", iJ), ";Offset (EF);", 150, -40, 40);
      hOffsetEcal[iJ] = new TH1D(Form("hOffsetEcal_%d", iJ), ";Offset (Ecal);", 150, -40, 40);
      hOffsetHcal[iJ] = new TH1D(Form("hOffsetHcal_%d", iJ), ";Offset (Hcal);", 150, -40, 40);
      hRho[iJ]  = new TH1D(Form("hRho_%d", iJ),  ";Rho;",  200, 0, 100);
      hFraction[iJ] = new TH2D(Form("hFraction_%d", iJ), ";Type;f", 7,0,7,100,0,1);
      hRefPT[iJ]  = new TH1D(Form("hRefPT_%d", iJ),  ";RefPT;",  200, Min, Max);
      hPUPT[iJ]   = new TH1D(Form("hPUPT_%d", iJ),   ";PUPT;",   200, Min, Max);
      hNoPUPT[iJ] = new TH1D(Form("hNoPUPT_%d", iJ), ";NoPUPT;", 200, Min, Max);
      hOffsetRho[iJ] = new TH2D(Form("hOffsetRho_%d", iJ), ";Offset;Rho",
         150, -40, 40, 50, 0, 50);
      hOffsetCHRho[iJ] = new TH2D(Form("hOffsetCHRho_%d", iJ), ";Offset (CH);Rho",
         150, -40, 40, 50, 0, 50);
      hOffsetCERho[iJ] = new TH2D(Form("hOffsetCERho_%d", iJ), ";Offset (CE);Rho",
         150, -40, 40, 50, 0, 50);
      hOffsetNHRho[iJ] = new TH2D(Form("hOffsetNHRho_%d", iJ), ";Offset (NH);Rho",
         150, -40, 40, 50, 0, 50);
      hOffsetNERho[iJ] = new TH2D(Form("hOffsetNERho_%d", iJ), ";Offset (NE);Rho",
         150, -40, 40, 50, 0, 50);
      hOffsetMURho[iJ] = new TH2D(Form("hOffsetMURho_%d", iJ), ";Offset (MU);Rho",
         150, -40, 40, 50, 0, 50);
      hOffsetHFRho[iJ] = new TH2D(Form("hOffsetHFRho_%d", iJ), ";Offset (HF);Rho",
         150, -40, 40, 50, 0, 50);
      hOffsetEFRho[iJ] = new TH2D(Form("hOffsetEFRho_%d", iJ), ";Offset (EF);Rho",
         150, -40, 40, 50, 0, 50);
      hOffsetEcalRho[iJ] = new TH2D(Form("hOffsetEcalRho_%d", iJ), ";Offset (Ecal);Rho",
         150, -40, 40, 50, 0, 50);
      hOffsetHcalRho[iJ] = new TH2D(Form("hOffsetHcalRho_%d", iJ), ";Offset (Hcal);Rho",
         150, -40, 40, 50, 0, 50);
      hRecoDR[iJ] = new TH1D(Form("hRecoDR_%d", iJ), ";RecoDR;", 200, 0.0, 0.1);
      hRecoDRWide[iJ] = new TH1D(Form("hRecoDRWide_%d", iJ), ";RecoDR;", 200, 0.0, 0.4);
      hOffsetRecoDR[iJ] = new TH2D(Form("hOffsetRecoDR_%d", iJ), ";Offset;RecoDR", 150, -40, 40, 200, 0.0, 0.1);
      hOffsetRecoDRWide[iJ] = new TH2D(Form("hOffsetRecoDRWide_%d", iJ), ";Offset;RecoDR", 150, -40, 40, 200, 0.0, 0.4);

      // hOffset[iJ]->SetStats(0);
      hRefPT[iJ]->SetStats(0);
      hPUPT[iJ]->SetStats(0);
      hNoPUPT[iJ]->SetStats(0);
      hFraction[iJ]->SetStats(0);
      hOffsetRho[iJ]->SetStats(0);
      hRecoDR[iJ]->SetStats(0);
      hRecoDRWide[iJ]->SetStats(0);
      hOffsetRecoDR[iJ]->SetStats(0);
      hOffsetRecoDRWide[iJ]->SetStats(0);

      hFraction[iJ]->GetXaxis()->SetBinLabel(1, "CHF");
      hFraction[iJ]->GetXaxis()->SetBinLabel(2, "CEF");
      hFraction[iJ]->GetXaxis()->SetBinLabel(3, "NHF");
      hFraction[iJ]->GetXaxis()->SetBinLabel(4, "NEF");
      hFraction[iJ]->GetXaxis()->SetBinLabel(5, "MUF");
      hFraction[iJ]->GetXaxis()->SetBinLabel(6, "HFHF");
      hFraction[iJ]->GetXaxis()->SetBinLabel(7, "HFEF");
   }

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      for(int iJ = 0; iJ < NJet; iJ++)
      {
         JetSignature Jet(Run[iJ], Lumi[iJ], Event[iJ], RefPT[iJ], RefEta[iJ], RefPhi[iJ]);
         int IJ = (LookUpTable.find(Jet) != LookUpTable.end()) ? LookUpTable[Jet] : -1;
         if(IJ < 0)
            continue;

         if(PUEMF[iJ] < 0)    PUEMF[iJ] = 0;
         if(PUCHF[iJ] < 0)    PUCHF[iJ] = 0;
         if(PUCEF[iJ] < 0)    PUCEF[iJ] = 0;
         if(PUNHF[iJ] < 0)    PUNHF[iJ] = 0;
         if(PUNEF[iJ] < 0)    PUNEF[iJ] = 0;
         if(PUMUF[iJ] < 0)    PUMUF[iJ] = 0;
         if(PUHFHF[iJ] < 0)   PUHFHF[iJ] = 0;
         if(PUHFEF[iJ] < 0)   PUHFEF[iJ] = 0;
         if(NoPUEMF[iJ] < 0)    NoPUEMF[iJ] = 0;
         if(NoPUCHF[iJ] < 0)    NoPUCHF[iJ] = 0;
         if(NoPUCEF[iJ] < 0)    NoPUCEF[iJ] = 0;
         if(NoPUNHF[iJ] < 0)    NoPUNHF[iJ] = 0;
         if(NoPUNEF[iJ] < 0)    NoPUNEF[iJ] = 0;
         if(NoPUMUF[iJ] < 0)    NoPUMUF[iJ] = 0;
         if(NoPUHFHF[iJ] < 0)   NoPUHFHF[iJ] = 0;
         if(NoPUHFEF[iJ] < 0)   NoPUHFEF[iJ] = 0;

         double Offset = PUPT[iJ] - NoPUPT[iJ];
         double OffsetEcal = PUPT[iJ] * PUEMF[iJ] - NoPUPT[iJ] * NoPUEMF[iJ];
         double OffsetHcal = PUPT[iJ] * (1 - PUEMF[iJ]) - NoPUPT[iJ] * (1 - NoPUEMF[iJ]);
         double OffsetCH = PUPT[iJ] * PUCHF[iJ] - NoPUPT[iJ] * NoPUCHF[iJ];
         double OffsetCE = PUPT[iJ] * PUCEF[iJ] - NoPUPT[iJ] * NoPUCEF[iJ];
         double OffsetNH = PUPT[iJ] * PUNHF[iJ] - NoPUPT[iJ] * NoPUNHF[iJ];
         double OffsetNE = PUPT[iJ] * PUNEF[iJ] - NoPUPT[iJ] * NoPUNEF[iJ];
         double OffsetMU = PUPT[iJ] * PUMUF[iJ] - NoPUPT[iJ] * NoPUMUF[iJ];
         double OffsetHF = PUPT[iJ] * PUHFHF[iJ] - NoPUPT[iJ] * NoPUHFHF[iJ];
         double OffsetEF = PUPT[iJ] * PUHFEF[iJ] - NoPUPT[iJ] * NoPUHFEF[iJ];

         hFraction[IJ]->Fill(0.0, PUCHF[iJ]);
         hFraction[IJ]->Fill(1, PUCEF[iJ]);
         hFraction[IJ]->Fill(2, PUNHF[iJ]);
         hFraction[IJ]->Fill(3, PUNEF[iJ]);
         hFraction[IJ]->Fill(4, PUMUF[iJ]);
         hFraction[IJ]->Fill(5, PUHFHF[iJ]);
         hFraction[IJ]->Fill(6, PUHFEF[iJ]);

         hOffset[IJ]->Fill(Offset);
         hOffsetCH[IJ]->Fill(OffsetCH);
         hOffsetCE[IJ]->Fill(OffsetCE);
         hOffsetNH[IJ]->Fill(OffsetNH);
         hOffsetNE[IJ]->Fill(OffsetNE);
         hOffsetMU[IJ]->Fill(OffsetMU);
         hOffsetHF[IJ]->Fill(OffsetHF);
         hOffsetEF[IJ]->Fill(OffsetEF);
         hOffsetEcal[IJ]->Fill(OffsetEcal);
         hOffsetHcal[IJ]->Fill(OffsetHcal);
         hRho[IJ]->Fill(Rho[IJ]);
         hRefPT[IJ]->Fill(RefPT[iJ]);
         hPUPT[IJ]->Fill(PUPT[iJ]);
         hNoPUPT[IJ]->Fill(NoPUPT[iJ]);
         hOffsetRho[IJ]->Fill(Offset, Rho[iJ]);
         hOffsetCHRho[IJ]->Fill(OffsetCH, Rho[iJ]);
         hOffsetCERho[IJ]->Fill(OffsetCE, Rho[iJ]);
         hOffsetNHRho[IJ]->Fill(OffsetNH, Rho[iJ]);
         hOffsetNERho[IJ]->Fill(OffsetNE, Rho[iJ]);
         hOffsetMURho[IJ]->Fill(OffsetMU, Rho[iJ]);
         hOffsetHFRho[IJ]->Fill(OffsetHF, Rho[iJ]);
         hOffsetEFRho[IJ]->Fill(OffsetEF, Rho[iJ]);
         hOffsetEcalRho[IJ]->Fill(OffsetEcal, Rho[iJ]);
         hOffsetHcalRho[IJ]->Fill(OffsetHcal, Rho[iJ]);
         hRecoDR[IJ]->Fill(RecoDR[iJ]);
         hRecoDRWide[IJ]->Fill(RecoDR[iJ]);
         hOffsetRecoDR[IJ]->Fill(Offset, RecoDR[iJ]);
         hOffsetRecoDRWide[IJ]->Fill(Offset, RecoDR[iJ]);
      }
   }

   for(int iJ = 0; iJ < NJet; iJ++)
   {
      JetSignature Jet(Run[iJ], Lumi[iJ], Event[iJ], RefPT[iJ], RefEta[iJ], RefPhi[iJ]);
      int IJ = (LookUpTable.find(Jet) != LookUpTable.end()) ? LookUpTable[Jet] : -1;
      if(IJ < 0)
         continue;
         
      if(RefEta[iJ] < 2.7 || RefEta[iJ] > 3.0)
         continue;
      
      vector<string> Explanations(10);
      Explanations[0] = Form("Jet #%d", iJ);
      Explanations[1] = Form("Event: (%d, %d, %d)", Run[iJ], Lumi[iJ], Event[iJ]);
      Explanations[2] = "";
      Explanations[3] = Form("   Ref: (%.1f, %.3f, %.3f)", RefPT[iJ], RefEta[iJ], RefPhi[iJ]);
      Explanations[4] = Form("   NoPU: (%.1f, %.3f, %.3f)", NoPUPT[iJ], NoPUEta[iJ], NoPUPhi[iJ]);
      Explanations[5] = Form("");
      PdfFile.AddTextPage(Explanations);

      PdfFile.AddPlot(hOffset[IJ]);
      PdfFile.AddPlot(hOffsetCH[IJ]);
      PdfFile.AddPlot(hOffsetCE[IJ]);
      PdfFile.AddPlot(hOffsetNH[IJ]);
      PdfFile.AddPlot(hOffsetNE[IJ]);
      PdfFile.AddPlot(hOffsetMU[IJ]);
      PdfFile.AddPlot(hOffsetEF[IJ]);
      PdfFile.AddPlot(hOffsetHF[IJ]);
      PdfFile.AddPlot(hOffsetEcal[IJ]);
      PdfFile.AddPlot(hOffsetHcal[IJ]);
      PdfFile.AddPlot(hRho[IJ]);
      PdfFile.AddPlot(hOffsetRho[IJ], "colz");
      PdfFile.AddPlot(hOffsetCHRho[IJ], "colz");
      PdfFile.AddPlot(hOffsetCERho[IJ], "colz");
      PdfFile.AddPlot(hOffsetNHRho[IJ], "colz");
      PdfFile.AddPlot(hOffsetNERho[IJ], "colz");
      PdfFile.AddPlot(hOffsetMURho[IJ], "colz");
      PdfFile.AddPlot(hOffsetHFRho[IJ], "colz");
      PdfFile.AddPlot(hOffsetEFRho[IJ], "colz");
      PdfFile.AddPlot(hOffsetEcalRho[IJ], "colz");
      PdfFile.AddPlot(hOffsetHcalRho[IJ], "colz");

      TCanvas Canvas;

      hNoPUPT[IJ]->SetLineColor(kRed);
      hRefPT[IJ]->SetLineColor(8);

      hPUPT[IJ]->Draw();
      hNoPUPT[IJ]->Draw("same");
      hRefPT[IJ]->Draw("same");

      TLatex Latex;
      Latex.SetNDC();
      Latex.SetTextFont(42);
      Latex.SetTextSize(0.035);
      Latex.DrawLatex(0.10, 0.925, "#color[2]{NoPU} #color[8]{Ref}");

      PdfFile.AddCanvas(Canvas);

      PdfFile.AddPlot(hRecoDR[IJ], "", true);
      PdfFile.AddPlot(hRecoDRWide[IJ], "", true);
      PdfFile.AddPlot(hOffsetRecoDR[IJ], "colz");
      PdfFile.AddPlot(hOffsetRecoDRWide[IJ], "colz");
      
      hFraction[IJ]->Draw("colz");

      TGraph GNoPU;
      GNoPU.SetPoint(0, 0.5, NoPUCHF[iJ]);
      GNoPU.SetPoint(1, 1.5, NoPUCEF[iJ]);
      GNoPU.SetPoint(2, 2.5, NoPUNHF[iJ]);
      GNoPU.SetPoint(3, 3.5, NoPUNEF[iJ]);
      GNoPU.SetPoint(4, 4.5, NoPUMUF[iJ]);
      GNoPU.SetPoint(5, 5.5, NoPUHFHF[iJ]);
      GNoPU.SetPoint(6, 6.5, NoPUHFEF[iJ]);

      GNoPU.SetMarkerStyle(20);
      GNoPU.SetMarkerSize(1.8);
      GNoPU.SetMarkerColor(kMagenta);
      GNoPU.Draw("p");

      Canvas.SetLogy(false);
      Canvas.SetLogz(true);
      PdfFile.AddCanvas(Canvas);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   InputFile.Close();

   return 0;
}



