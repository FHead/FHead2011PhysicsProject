#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main(int argc, char *argv[]);
void FillHistogram(string FileName, TH1D &H1, TH1D &H2, double PTMin, double PTMax, double CMin, double CMax);
double FitFraction(PdfFileHelper &PdfFile, TH1D &HTotal, TH1D &HQ, TH1D &HG, string Tag);
void TidyHistogram(TH1D &H);

int main(int argc, char *argv[])
{
   if(argc != 6)
   {
      cerr << "Usage: " << argv[0] << " Tag PTMin PTMax CMin CMax" << endl;
      return -1;
   }

   string Tag = argv[1];
   double PTMin = atof(argv[2]);
   double PTMax = atof(argv[3]);
   double CMin = atof(argv[4]);
   double CMax = atof(argv[5]);

   SetThesisStyle();
   
   PdfFileHelper PdfFile("QuickFitSanityCheck_" + Tag + ".pdf");
   PdfFile.AddTextPage("Sanity Checks");

   // int NBins = 33;
   // double Bins[34] =
   //    {0.00, 0.02, 0.025, 0.03, 0.0325,
   //    0.035, 0.0375, 0.04, 0.0425, 0.045,
   //    0.0475, 0.05, 0.0525, 0.055, 0.0575,
   //    0.06, 0.0625, 0.065, 0.0675, 0.07,
   //    0.075, 0.08, 0.085, 0.09, 0.10,
   //    0.11, 0.12, 0.135, 0.15, 0.17,
   //    0.19, 0.21, 0.23, 0.26};

   int NBins = 13;
   double Bins[14] =
      {0.00, 0.025, 0.040, 0.050, 0.060,
      0.070, 0.085, 0.10, 0.12, 0.15,
      0.19, 0.21, 0.23, 0.26};

   // int NBins = 10;
   // double Bins[11] =
   //    {0.00, 0.02, 0.04, 0.06, 0.08,
   //    0.10, 0.12, 0.15, 0.18, 0.22,
   //    0.26};

   TH1D HData1("HData1", "Data;Mass/PT;",        NBins, Bins);   HData1.Sumw2();
   TH1D HMC1  ("HMC1",   "MC;Mass/PT;",          NBins, Bins);   HMC1.Sumw2();
   TH1D HMCQ1 ("HMCQ1",  "MC (quark);Mass/PT;",  NBins, Bins);   HMCQ1.Sumw2();
   TH1D HMCG1 ("HMCG1",  "MC (gluon);Mass/PT;",  NBins, Bins);   HMCG1.Sumw2();
   TH1D HData2("HData2", "Data;Mass/PT;",        NBins, Bins);   HData2.Sumw2();
   TH1D HMC2  ("HMC2",   "MC;Mass/PT;",          NBins, Bins);   HMC2.Sumw2();
   TH1D HMCQ2 ("HMCQ2",  "MC (quark);Mass/PT;",  NBins, Bins);   HMCQ2.Sumw2();
   TH1D HMCG2 ("HMCG2",  "MC (gluon);Mass/PT;",  NBins, Bins);   HMCG2.Sumw2();

   FillHistogram("Mass_SD7_Data.txt",     HData1, HData2, PTMin, PTMax, CMin, CMax);
   FillHistogram("Mass_SD7_MC.txt",       HMC1,   HMC2,   PTMin, PTMax, CMin, CMax);
   FillHistogram("Mass_SD7_MC_Quark.txt", HMCQ1,  HMCQ2,  PTMin, PTMax, CMin, CMax);
   FillHistogram("Mass_SD7_MC_Gluon.txt", HMCG1,  HMCG2,  PTMin, PTMax, CMin, CMax);

   PdfFile.AddTextPage("Raw Histograms");
   PdfFile.AddPlot(HData1);
   PdfFile.AddPlot(HMC1);
   PdfFile.AddPlot(HMCQ1);
   PdfFile.AddPlot(HMCG1);
   // PdfFile.AddPlot(HData2);
   // PdfFile.AddPlot(HMC2);
   // PdfFile.AddPlot(HMCQ2);
   // PdfFile.AddPlot(HMCG2);

   cout << "Data Int = " << HData1.Integral() << endl;
   cout << "MC Int = " << HMC1.Integral() << endl;
   cout << "MC(Q) Int = " << HMCQ1.Integral() << endl;
   cout << "MC(G) Int = " << HMCG1.Integral() << endl;
   
   TidyHistogram(HData1);
   TidyHistogram(HMC1);
   TidyHistogram(HMCQ1);
   TidyHistogram(HMCG1);
   // TidyHistogram(HData2);
   // TidyHistogram(HMC2);
   // TidyHistogram(HMCQ2);
   // TidyHistogram(HMCG2);

   PdfFile.AddTextPage("Scaled Histograms");
   PdfFile.AddPlot(HData1);
   PdfFile.AddPlot(HMC1);
   PdfFile.AddPlot(HMCQ1);
   PdfFile.AddPlot(HMCG1);
   // PdfFile.AddPlot(HData2);
   // PdfFile.AddPlot(HMC2);
   // PdfFile.AddPlot(HMCQ2);
   // PdfFile.AddPlot(HMCG2);

   PdfFile.AddTextPage("Starting fitting for MC fraction (PbPb)");
   double MCFraction1 = FitFraction(PdfFile, HMC1, HMCQ1, HMCG1, Tag + "MC");
   
   PdfFile.AddTextPage("Starting fitting for data fraction (PbPb)");
   double DataFraction1 = FitFraction(PdfFile, HData1, HMCQ1, HMCG1, Tag + "Data");

   // PdfFile.AddTextPage("Starting fitting for MC fraction (pp)");
   // double MCFraction2 = FitFraction(PdfFile, HMC2, HMCQ2, HMCG2);
   // 
   // PdfFile.AddTextPage("Starting fitting for data fraction (pp)");
   // double DataFraction2 = FitFraction(PdfFile, HData2, HMCQ2, HMCG2);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void FillHistogram(string FileName, TH1D &H1, TH1D &H2, double PTMin, double PTMax, double CMin, double CMax)
{
   cout << "Starting getting stuff from \"" << FileName << "\"" << endl;

   ifstream in(FileName.c_str());

   while(in)
   {
      char ch[10240] = "";
      in.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream str(ch);

      string Type;
      double Centrality;
      double JetPT;
      double SDMassRatio;
      double SDZG;
      double SDRecoDR;
      double PTPT;
      double Weight;

      str >> Type >> Centrality >> JetPT >> SDMassRatio >> SDZG >> SDRecoDR >> PTPT >> Weight;

      if(Weight != Weight || SDMassRatio != SDMassRatio)
         continue;

      if(SDRecoDR > 0.1 && JetPT > PTMin && JetPT < PTMax && Centrality >= CMin && Centrality <= CMax)
      {
         if(Type == "Data")
            H1.Fill(SDMassRatio, Weight);
         if(Type == "Smear")
            H2.Fill(SDMassRatio, Weight);
      }
   }

   in.close();
}

double FitFraction(PdfFileHelper &PdfFile, TH1D &HTotal, TH1D &HQ, TH1D &HG, string Tag)
{
   int N = HTotal.GetNbinsX();

   TGraph GTried;

   double Step = 0.01;
   double Left = 0;
   double Right = 1;

   double BestChi2 = -1;
   double BestF = -1;

   while(Step > 1e-7)
   {
      for(int i = 0; Left + Step * i <= Right; i = i + 1)
      {
         double F = Left + i * Step;
         double Chi2 = 0;
         for(int i = 1; i <= N; i++)
         {
            double y = HTotal.GetBinContent(i);
            double yq = HQ.GetBinContent(i);
            double yg = HG.GetBinContent(i);
            double ey = HTotal.GetBinError(i);
            double eyq = HQ.GetBinError(i);
            double eyg = HG.GetBinError(i);

            double fy = yq * F + yg * (1 - F);
            double efy = sqrt(eyq * eyq * F * F + eyg * eyg * (1 - F) * (1 - F));

            double diff = y - fy;
            double err = sqrt(ey * ey + efy * efy);

            if(err == err && err > 0 && diff == diff)
               Chi2 = Chi2 + diff * diff / err / err;
         }

         GTried.SetPoint(GTried.GetN(), F, Chi2);

         if(BestChi2 < 0 || BestChi2 > Chi2)
         {
            BestF = F;
            BestChi2 = Chi2;
         }
      }

      Left = ((BestF - Step * 2 > Left) ? BestF - Step * 2 : Left);
      Right = ((BestF + Step * 2 < Right) ? BestF + Step * 2 : Right);
      Step = Step / 10;
   }

   TCanvas C;

   GTried.Draw("ap");
   GTried.GetXaxis()->SetTitle("Quark fraction");
   GTried.GetYaxis()->SetTitle("#chi^{2}");

   TGraph GLines;
   GLines.SetPoint(0, -100, BestChi2);
   GLines.SetPoint(1, +100, BestChi2);
   GLines.SetPoint(2, +100, BestChi2 + 1);
   GLines.SetPoint(3, -100, BestChi2 + 1);
   GLines.SetPoint(4, -100, BestChi2 + 4);
   GLines.SetPoint(5, +100, BestChi2 + 4);
   GLines.SetPoint(6, +100, BestChi2 + 9);
   GLines.SetPoint(7, -100, BestChi2 + 9);
   GLines.SetLineStyle(kDashed);
   GLines.Draw("l");

   C.SaveAs(("Plots/" + Tag + "_Chi2.png").c_str());
   C.SaveAs(("Plots/" + Tag + "_Chi2.C").c_str());
   C.SaveAs(("Plots/" + Tag + "_Chi2.eps").c_str());
   C.SaveAs(("PDFPlots/" + Tag + "_Chi2.pdf").c_str());

   PdfFile.AddCanvas(C);

   HTotal.SetTitle("");
   HTotal.Draw("");

   TH1D *HQClone = (TH1D *)HQ.Clone("HQClone");
   TH1D *HGClone = (TH1D *)HG.Clone("HGClone");
   TH1D *HAllClone = (TH1D *)HG.Clone("HAllClone");

   HQClone->Scale(BestF);
   HGClone->Scale(1 - BestF);
   
   HAllClone->Scale(1 - BestF);
   HAllClone->Add(HQClone);

   HQClone->SetLineColor(kGreen);
   HGClone->SetLineColor(kRed);
   HAllClone->SetLineColor(kBlue);
   
   HQClone->SetMarkerColor(kGreen);
   HGClone->SetMarkerColor(kRed);
   HAllClone->SetMarkerColor(kBlue);

   HQClone->Draw("same hist");
   HGClone->Draw("same hist");
   HAllClone->Draw("same hist error");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextSize(0.035);
   Legend.SetTextFont(42);
   Legend.AddEntry(&HTotal, "PbPb", "pl");
   Legend.AddEntry(HAllClone, "Fit (all)", "lp");
   Legend.AddEntry(HQClone, "Fit (q)", "l");
   Legend.AddEntry(HGClone, "Fit (g)", "l");
   Legend.Draw();

   C.SaveAs(("Plots/" + Tag + "_Distribution.png").c_str());
   C.SaveAs(("Plots/" + Tag + "_Distribution.C").c_str());
   C.SaveAs(("Plots/" + Tag + "_Distribution.eps").c_str());
   C.SaveAs(("PDFPlots/" + Tag + "_Distribution.pdf").c_str());
   
   PdfFile.AddCanvas(C);

   C.SetLogy();
   
   HTotal.Draw("");
   HQClone->Draw("same hist");
   HGClone->Draw("same hist");
   HAllClone->Draw("same hist error");
   
   TLegend Legend2(0.3, 0.4, 0.6, 0.2);
   Legend2.SetTextSize(0.035);
   Legend2.SetTextFont(42);
   Legend2.SetFillStyle(0);
   Legend2.AddEntry(&HTotal, "PbPb", "pl");
   Legend2.AddEntry(HAllClone, "Fit (all)", "lp");
   Legend2.AddEntry(HQClone, "Fit (q)", "l");
   Legend2.AddEntry(HGClone, "Fit (g)", "l");
   Legend2.Draw();

   C.SaveAs(("Plots/" + Tag + "_DistributionLog.png").c_str());
   C.SaveAs(("Plots/" + Tag + "_DistributionLog.C").c_str());
   C.SaveAs(("Plots/" + Tag + "_DistributionLog.eps").c_str());
   C.SaveAs(("PDFPlots/" + Tag + "_DistributionLog.pdf").c_str());

   PdfFile.AddCanvas(C);

   C.SetLogy(false);

   TH1D *HRatioClone = (TH1D *)HTotal.Clone("HRatioClone");
   HRatioClone->Divide(HAllClone);

   HRatioClone->SetMinimum(0.0);
   HRatioClone->SetMaximum(2.0);
   HRatioClone->Draw();

   TGraph GLine;
   GLine.SetPoint(0, 0, 1);
   GLine.SetPoint(1, 1, 1);
   GLine.Draw("l");

   C.SaveAs(("Plots/" + Tag + "_Ratio.png").c_str());
   C.SaveAs(("Plots/" + Tag + "_Ratio.C").c_str());
   C.SaveAs(("Plots/" + Tag + "_Ratio.eps").c_str());
   C.SaveAs(("PDFPlots/" + Tag + "_Ratio.pdf").c_str());
   
   PdfFile.AddCanvas(C);
   
   delete HQClone;
   delete HGClone;
   delete HAllClone;

   return BestF;
}

void TidyHistogram(TH1D &H)
{
   H.SetStats(0);

   H.Scale(1 / H.Integral());

   for(int i = 1; i <= H.GetNbinsX(); i++)
   {
      double xl = H.GetXaxis()->GetBinLowEdge(i);
      double xr = H.GetXaxis()->GetBinUpEdge(i);

      H.SetBinContent(i, H.GetBinContent(i) / (xr - xl));
      H.SetBinError(i, H.GetBinError(i) / (xr - xl));
   }
}




