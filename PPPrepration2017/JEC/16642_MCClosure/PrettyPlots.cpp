#include <iostream>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TGraphErrors.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper3.h"
#include "Code/TauHelperFunctions3.h"

int main();
double GetDR2(double eta1, double phi1, double eta2, double phi2);
void TranscribeWidth(TProfile &P, TGraphErrors &G);

int main()
{
   SetThesisStyle();

   double Binning[] = {40, 50, 60, 70, 80, 90, 100, 120, 140, 160, 200, 240, 300};
   
   TProfile PRawPFEta15("PRawPFEta15", ";Gen Jet PT;", 12, Binning);
   TProfile PCorrPFEta15("PCorrPFEta15", ";Gen Jet PT;", 12, Binning);
   TProfile PCorrPFHLTEta15("PCorrPFHLTEta15", ";Gen Jet PT;", 12, Binning);
   TProfile PRawPFEta30("PRawPFEta30", ";Gen Jet PT;", 12, Binning);
   TProfile PCorrPFEta30("PCorrPFEta30", ";Gen Jet PT;", 12, Binning);
   TProfile PCorrPFHLTEta30("PCorrPFHLTEta30", ";Gen Jet PT;", 12, Binning);
   TProfile PRawPFEta50("PRawPFEta50", ";Gen Jet PT;", 12, Binning);
   TProfile PCorrPFEta50("PCorrPFEta50", ";Gen Jet PT;", 12, Binning);
   TProfile PCorrPFHLTEta50("PCorrPFHLTEta50", ";Gen Jet PT;", 12, Binning);
   
   TProfile PHLTRawPFEta15("PHLTRawPFEta15", ";Gen Jet PT;", 12, Binning);
   TProfile PHLTPFEta15("PHLTPFEta15", ";Gen Jet PT;", 12, Binning);
   TProfile PHLTCorrPFEta15("PHLTCorrPFEta15", ";Gen Jet PT;", 12, Binning);
   TProfile PHLTCorr2PFEta15("PHLTCorr2PFEta15", ";Gen Jet PT;", 12, Binning);
   TProfile PHLTRawPFEta30("PHLTRawPFEta30", ";Gen Jet PT;", 12, Binning);
   TProfile PHLTPFEta30("PHLTPFEta30", ";Gen Jet PT;", 12, Binning);
   TProfile PHLTCorrPFEta30("PHLTCorrPFEta30", ";Gen Jet PT;", 12, Binning);
   TProfile PHLTCorr2PFEta30("PHLTCorr2PFEta30", ";Gen Jet PT;", 12, Binning);
   TProfile PHLTRawPFEta50("PHLTRawPFEta50", ";Gen Jet PT;", 12, Binning);
   TProfile PHLTPFEta50("PHLTPFEta50", ";Gen Jet PT;", 12, Binning);
   TProfile PHLTCorrPFEta50("PHLTCorrPFEta50", ";Gen Jet PT;", 12, Binning);
   TProfile PHLTCorr2PFEta50("PHLTCorr2PFEta50", ";Gen Jet PT;", 12, Binning);

   double GenEta, GenPhi, GenPT;
   double PFRawPT, PFEta, PFPhi, PFCorrPT, PFHLTCorrPT;
   double HLTRawPFPT, HLTRawPFEta, HLTRawPFPhi, HLTRawPFDR, HLTCorrPFPT, HLTCorr2PFPT;
   double HLTPFPT, HLTPFEta, HLTPFPhi, HLTPFDR;

   PdfFileHelper PdfFile("JECClosure.pdf");
   PdfFile.AddTextPage("JEC Closure");

   TFile File("Output.root");

   TTree *Tree = (TTree *)File.Get("T");

   Tree->SetBranchAddress("GenEta", &GenEta);
   Tree->SetBranchAddress("GenPhi", &GenPhi);
   Tree->SetBranchAddress("GenPT", &GenPT);
   Tree->SetBranchAddress("PFRawEta", &PFEta);
   Tree->SetBranchAddress("PFRawPhi", &PFPhi);
   Tree->SetBranchAddress("PFRawPT", &PFRawPT);
   Tree->SetBranchAddress("PFCorrPT", &PFCorrPT);
   Tree->SetBranchAddress("PFHLTCorrPT", &PFHLTCorrPT);
   Tree->SetBranchAddress("HLTRawPFPT", &HLTRawPFPT);
   Tree->SetBranchAddress("HLTRawPFEta", &HLTRawPFEta);
   Tree->SetBranchAddress("HLTRawPFPhi", &HLTRawPFPhi);
   Tree->SetBranchAddress("HLTRawPFDR", &HLTRawPFDR);
   Tree->SetBranchAddress("HLTCorrPFPT", &HLTCorrPFPT);
   Tree->SetBranchAddress("HLTCorr2PFPT", &HLTCorr2PFPT);
   Tree->SetBranchAddress("HLTPFPT", &HLTPFPT);
   Tree->SetBranchAddress("HLTPFEta", &HLTPFEta);
   Tree->SetBranchAddress("HLTPFPhi", &HLTPFPhi);
   Tree->SetBranchAddress("HLTPFDR", &HLTPFDR);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(PFRawPT > 0)
      {
         if(fabs(PFEta) < 1.5)
         {
            PRawPFEta15.Fill(GenPT, PFRawPT / GenPT);
            PCorrPFEta15.Fill(GenPT, PFCorrPT / GenPT);
            PCorrPFHLTEta15.Fill(GenPT, PFHLTCorrPT / GenPT);
         }
         else if(fabs(PFEta) < 3.0)
         {
            PRawPFEta30.Fill(GenPT, PFRawPT / GenPT);
            PCorrPFEta30.Fill(GenPT, PFCorrPT / GenPT);
            PCorrPFHLTEta30.Fill(GenPT, PFHLTCorrPT / GenPT);
         }
         else if(fabs(PFEta) < 5.0)
         {
            PRawPFEta50.Fill(GenPT, PFRawPT / GenPT);
            PCorrPFEta50.Fill(GenPT, PFCorrPT / GenPT);
            PCorrPFHLTEta50.Fill(GenPT, PFHLTCorrPT / GenPT);
         }
      }
      if(HLTRawPFPT > 0 && HLTRawPFDR < 0.2)
      {
         if(fabs(HLTRawPFEta) < 1.5)
         {
            PHLTRawPFEta15.Fill(GenPT, HLTRawPFPT / GenPT);
            PHLTCorrPFEta15.Fill(GenPT, HLTCorrPFPT / GenPT);
            PHLTCorr2PFEta15.Fill(GenPT, HLTCorr2PFPT / GenPT);
         }
         else if(fabs(HLTRawPFEta) < 3.0)
         {
            PHLTRawPFEta30.Fill(GenPT, HLTRawPFPT / GenPT);
            PHLTCorrPFEta30.Fill(GenPT, HLTCorrPFPT / GenPT);
            PHLTCorr2PFEta30.Fill(GenPT, HLTCorr2PFPT / GenPT);
         }
         else if(fabs(HLTRawPFEta) < 5.0)
         {
            PHLTRawPFEta50.Fill(GenPT, HLTRawPFPT / GenPT);
            PHLTCorrPFEta50.Fill(GenPT, HLTCorrPFPT / GenPT);
            PHLTCorr2PFEta50.Fill(GenPT, HLTCorr2PFPT / GenPT);
         }
      }
      if(HLTPFPT > 0 && HLTPFDR < 0.2)
      {
         if(fabs(HLTPFEta) < 1.5)
            PHLTPFEta15.Fill(GenPT, HLTPFPT / GenPT);
         else if(fabs(HLTPFEta) < 3.0)
            PHLTPFEta30.Fill(GenPT, HLTPFPT / GenPT);
         else if(fabs(HLTPFEta) < 5.0)
            PHLTPFEta50.Fill(GenPT, HLTPFPT / GenPT);
      }
   }

   PRawPFEta15.SetLineColor(kRed);
   PRawPFEta15.SetMarkerColor(kRed);
   PCorrPFEta15.SetLineColor(kBlue);
   PCorrPFEta15.SetMarkerColor(kBlue);
   PCorrPFHLTEta15.SetLineColor(kGreen + 3);
   PCorrPFHLTEta15.SetMarkerColor(kGreen + 3);
   PRawPFEta30.SetLineColor(kRed);
   PRawPFEta30.SetMarkerColor(kRed);
   PCorrPFEta30.SetLineColor(kBlue);
   PCorrPFEta30.SetMarkerColor(kBlue);
   PCorrPFHLTEta30.SetLineColor(kGreen + 3);
   PCorrPFHLTEta30.SetMarkerColor(kGreen + 3);
   PRawPFEta50.SetLineColor(kRed);
   PRawPFEta50.SetMarkerColor(kRed);
   PCorrPFEta50.SetLineColor(kBlue);
   PCorrPFEta50.SetMarkerColor(kBlue);
   PCorrPFHLTEta50.SetLineColor(kGreen + 3);
   PCorrPFHLTEta50.SetMarkerColor(kGreen + 3);
   PHLTRawPFEta15.SetLineColor(kRed);
   PHLTRawPFEta15.SetMarkerColor(kRed);
   PHLTPFEta15.SetLineColor(kBlue);
   PHLTPFEta15.SetMarkerColor(kBlue);
   PHLTCorrPFEta15.SetLineColor(kGreen + 3);
   PHLTCorrPFEta15.SetMarkerColor(kGreen + 3);
   PHLTCorr2PFEta15.SetLineColor(kGreen);
   PHLTCorr2PFEta15.SetMarkerColor(kGreen);
   PHLTRawPFEta30.SetLineColor(kRed);
   PHLTRawPFEta30.SetMarkerColor(kRed);
   PHLTPFEta30.SetLineColor(kBlue);
   PHLTPFEta30.SetMarkerColor(kBlue);
   PHLTCorrPFEta30.SetLineColor(kGreen + 3);
   PHLTCorrPFEta30.SetMarkerColor(kGreen + 3);
   PHLTCorr2PFEta30.SetLineColor(kGreen);
   PHLTCorr2PFEta30.SetMarkerColor(kGreen);
   PHLTRawPFEta50.SetLineColor(kRed);
   PHLTRawPFEta50.SetMarkerColor(kRed);
   PHLTPFEta50.SetLineColor(kBlue);
   PHLTPFEta50.SetMarkerColor(kBlue);
   PHLTCorrPFEta50.SetLineColor(kGreen + 3);
   PHLTCorrPFEta50.SetMarkerColor(kGreen + 3);
   PHLTCorr2PFEta50.SetLineColor(kGreen);
   PHLTCorr2PFEta50.SetMarkerColor(kGreen);

   TGraphErrors GLine;
   GLine.SetPoint(0, 0, 1.02);
   GLine.SetPoint(1, 10000, 1.02);
   GLine.SetPoint(2, 10000, 1.00);
   GLine.SetPoint(3, 0, 1.00);
   GLine.SetPoint(4, 0, 0.98);
   GLine.SetPoint(5, 10000, 0.98);
   GLine.SetLineStyle(kDashed);

   TCanvas C;

   TH2D HWorld("HWorld", "|#eta| < 1.5;Gen Jet PT;Response", 100, 40, 300, 100, 0.75, 1.25);
   HWorld.SetStats(0);

   HWorld.Draw("axis");
   PRawPFEta15.Draw("same");
   PCorrPFEta15.Draw("same");
   PCorrPFHLTEta15.Draw("same");
   GLine.Draw("l");

   TLegend Legend1(0.15, 0.65, 0.45, 0.85);
   Legend1.SetTextSize(0.035);
   Legend1.SetTextFont(42);
   Legend1.SetFillStyle(0);
   Legend1.AddEntry(&PRawPFEta15, "Raw PF PT / Gen PT (offline)", "pl");
   Legend1.AddEntry(&PCorrPFEta15, "Corrected PF PT / Gen PT (offline)", "pl");
   Legend1.AddEntry(&PCorrPFHLTEta15, "Corrected PF PT / Gen PT (HLT-on-offline)", "pl");
   Legend1.Draw();

   PdfFile.AddCanvas(C);

   HWorld.SetTitle("1.5 < |#eta| < 3.0");

   HWorld.Draw("axis");
   PRawPFEta30.Draw("same");
   PCorrPFEta30.Draw("same");
   PCorrPFHLTEta30.Draw("same");
   GLine.Draw("l");
   Legend1.Draw();

   PdfFile.AddCanvas(C);

   HWorld.SetTitle("3.0 < |#eta| < 5.0");

   HWorld.Draw("axis");
   PRawPFEta50.Draw("same");
   PCorrPFEta50.Draw("same");
   PCorrPFHLTEta50.Draw("same");
   GLine.Draw("l");
   Legend1.Draw();

   PdfFile.AddCanvas(C);

   HWorld.SetTitle("|#eta| < 1.5");

   HWorld.Draw("axis");
   PHLTPFEta15.Draw("same");
   PHLTRawPFEta15.Draw("same");
   PHLTCorrPFEta15.Draw("same");
   PHLTCorr2PFEta15.Draw("same");
   GLine.Draw("l");

   TLegend Legend2(0.15, 0.65, 0.45, 0.85);
   Legend2.SetTextSize(0.035);
   Legend2.SetTextFont(42);
   Legend2.SetFillStyle(0);
   Legend2.AddEntry(&PHLTRawPFEta15, "Raw PF PT / Gen PT (HLT)", "pl");
   Legend2.AddEntry(&PHLTPFEta15, "Online-corrected PF PT / Gen PT (HLT)", "pl");
   Legend2.AddEntry(&PHLTCorrPFEta15, "Offline-corrected PF PT / Gen PT (HLT)", "pl");
   Legend2.AddEntry(&PHLTCorr2PFEta15, "Offline-corrected PF PT / Gen PT (Current)", "pl");
   Legend2.Draw();

   PdfFile.AddCanvas(C);

   HWorld.SetTitle("1.5 < |#eta| < 3.0");

   HWorld.Draw("axis");
   PHLTPFEta30.Draw("same");
   PHLTRawPFEta30.Draw("same");
   PHLTCorrPFEta30.Draw("same");
   PHLTCorr2PFEta30.Draw("same");
   GLine.Draw("l");
   Legend2.Draw();

   PdfFile.AddCanvas(C);

   HWorld.SetTitle("3.0 < |#eta| < 5.0");

   HWorld.Draw("axis");
   PHLTPFEta50.Draw("same");
   PHLTRawPFEta50.Draw("same");
   PHLTCorrPFEta50.Draw("same");
   PHLTCorr2PFEta50.Draw("same");
   GLine.Draw("l");
   Legend2.Draw();

   PdfFile.AddCanvas(C);

   TGraphErrors GPFWidthEta15, GHLTPFWidthEta15;
   TGraphErrors GPFWidthEta30, GHLTPFWidthEta30;
   TGraphErrors GPFWidthEta50, GHLTPFWidthEta50;

   TranscribeWidth(PHLTPFEta15, GHLTPFWidthEta15);
   TranscribeWidth(PHLTPFEta30, GHLTPFWidthEta30);
   TranscribeWidth(PHLTPFEta50, GHLTPFWidthEta50);
   TranscribeWidth(PCorrPFEta15, GPFWidthEta15);
   TranscribeWidth(PCorrPFEta30, GPFWidthEta30);
   TranscribeWidth(PCorrPFEta50, GPFWidthEta50);

   GPFWidthEta15.SetLineColor(kRed);
   GPFWidthEta30.SetLineColor(kBlue);
   GPFWidthEta50.SetLineColor(kGreen + 3);
   GPFWidthEta15.SetMarkerColor(kRed);
   GPFWidthEta30.SetMarkerColor(kBlue);
   GPFWidthEta50.SetMarkerColor(kGreen + 3);
   GPFWidthEta15.SetLineWidth(2);
   GPFWidthEta30.SetLineWidth(2);
   GPFWidthEta50.SetLineWidth(2);
   GHLTPFWidthEta15.SetLineColor(kRed);
   GHLTPFWidthEta30.SetLineColor(kBlue);
   GHLTPFWidthEta50.SetLineColor(kGreen + 3);
   GHLTPFWidthEta15.SetMarkerColor(kRed);
   GHLTPFWidthEta30.SetMarkerColor(kBlue);
   GHLTPFWidthEta50.SetMarkerColor(kGreen + 3);
   GHLTPFWidthEta15.SetLineWidth(2);
   GHLTPFWidthEta30.SetLineWidth(2);
   GHLTPFWidthEta50.SetLineWidth(2);

   TH2D HWorld2("HWorld2", ";Gen Jet PT;#sigma(Jet PT / Gen PT)", 100, 40, 300, 100, 0, 0.4);
   HWorld2.SetStats(0);

   TLegend Legend3(0.5, 0.8, 0.8, 0.6);
   Legend3.SetTextFont(42);
   Legend3.SetTextSize(0.035);
   Legend3.SetFillStyle(0);
   Legend3.AddEntry(&GPFWidthEta15, "|#eta| < 1.5", "l");
   Legend3.AddEntry(&GPFWidthEta30, "1.5 < |#eta| < 3.0", "l");
   Legend3.AddEntry(&GPFWidthEta50, "3.0 < |#eta| < 5.0", "l");

   HWorld2.SetTitle("Offline corrected jets");

   HWorld2.Draw("axis");
   GPFWidthEta15.Draw("lp");
   GPFWidthEta30.Draw("lp");
   GPFWidthEta50.Draw("lp");
   Legend3.Draw();

   PdfFile.AddCanvas(C);
   
   HWorld2.SetTitle("Corrected HLT jets");

   HWorld2.Draw("axis");
   GHLTPFWidthEta15.Draw("lp");
   GHLTPFWidthEta30.Draw("lp");
   GHLTPFWidthEta50.Draw("lp");
   Legend3.Draw();

   PdfFile.AddCanvas(C);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double GetDR2(double eta1, double phi1, double eta2, double phi2)
{
   double DEta = eta1 - eta2;
   double DPhi = phi1 - phi2;
   while(DPhi < -M_PI)
      DPhi = DPhi + 2 * M_PI;
   while(DPhi > M_PI)
      DPhi = DPhi - 2 * M_PI;

   return DEta * DEta + DPhi * DPhi;
}

void TranscribeWidth(TProfile &P, TGraphErrors &G)
{
   P.SetErrorOption("S");

   for(int i = 1; i <= P.GetNbinsX(); i++)
   {
      double Width = P.GetBinError(i);
      double X = P.GetBinCenter(i);

      G.SetPoint(i - 1, X, Width);
   }

   P.SetErrorOption("");
   
   for(int i = 1; i <= P.GetNbinsX(); i++)
   {
      double Error = P.GetBinError(i);

      G.SetPointError(i - 1, 0, Error);
   }
}





