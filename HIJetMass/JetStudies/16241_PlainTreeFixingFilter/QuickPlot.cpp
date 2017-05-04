#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main()
{
   SetThesisStyle();

   TFile F1("AADataPrescale.root");
   TFile F2("AADataPrescale.root");
   TFile F3("AADataPrescale.root");
   TFile F4("AAData.root");
   TFile F5("AADataPrescale.root");

   TTree *T1 = (TTree *)F1.Get("T");
   TTree *T2 = (TTree *)F2.Get("T");
   TTree *T3 = (TTree *)F3.Get("T");
   TTree *T4 = (TTree *)F4.Get("T");
   TTree *T5 = (TTree *)F5.Get("T");

   double PTMin[] = {140, 160, 180, 140, 160, 180, 0, 0, 0, 0};
   double PTMax[] = {160, 180, 200, 160, 180, 200, 500, 500, 500, 500};
   double CentralityMin[] = {0.0, 0.0, 0.0, 0.1, 0.1, 0.1, 0.0, 0.1, 0.3, 0.5};
   double CentralityMax[] = {0.1, 0.1, 0.1, 0.3, 0.3, 0.3, 0.1, 0.3, 0.5, 0.8};

   PdfFileHelper PdfFile("QuickComparison.pdf");
   PdfFile.AddTextPage("Jet100 vs Jet80 vs Jet60");

   string ToPlot[] = {"SDMass0/MatchPT", "SubJetDR0", "JetPT", "SDMass7/MatchPT", "SubJetDR7"};
   string Label[] = {"Mass/PT (0)", "DR (0)", "Jet PT", "Mass/PT (7)", "DR (7)"};

   int Bin[] = {25, 25, 50, 25, 25};
   double Min[] = {0.0, 0.0, 0, 0.0, 0.0};
   double Max[] = {0.26, 0.4, 500, 0.26, 0.4};

   int SD[] = {0, 0, -1, 7, 7};

   double L[] = {0.50, 0.15, 0.50, 0.50, 0.15};
   double R[] = {0.80, 0.45, 0.80, 0.80, 0.45};
   double B[] = {0.60, 0.60, 0.60, 0.60, 0.60};
   double T[] = {0.85, 0.85, 0.85, 0.85, 0.85};

   bool Log[] = {false, false, false, false, false};
   int NormalizeStart[] = {1, 1, -1, 1, 1};
   int NormalizeEnd[] = {Bin[0], Bin[1], -1, Bin[3], Bin[4]};

   bool Switch[10][5] =
   {
      {1, 1, 0, 1, 1},
      {1, 1, 0, 1, 1},
      {1, 1, 0, 1, 1},
      {1, 1, 0, 1, 1},
      {1, 1, 0, 1, 1},
      {1, 1, 0, 1, 1},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
   };

   /*
   bool Switch[10][5] =
   {
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
   };
   */
         
   // char DivideString[] = "cl=0.683 b(1,1) mode";
   char DivideString[] = "";

   for(int i = 0; i < 10; i++)
   {
      for(int j = 0; j < 5; j++)
      {
         if(Switch[i][j] == false)
            continue;

         string Title = Form("PT %.0f-%.0f, Centrality %.2f-%.2f;%s;a.u.",
               PTMin[i], PTMax[i], CentralityMin[i], CentralityMax[i], Label[j].c_str());

         double Shift = 0.0005;
         Shift = 0;

         TH1D H1("H1", Title.c_str(), Bin[j], Min[j] + Shift * 0, Max[j] + Shift * 1);
         TH1D H2("H2", Title.c_str(), Bin[j], Min[j] + Shift * 1, Max[j] + Shift * 2);
         TH1D H3("H3", Title.c_str(), Bin[j], Min[j] + Shift * 2, Max[j] + Shift * 3);
         TH1D H4("H4", Title.c_str(), Bin[j], Min[j] + Shift * 3, Max[j] + Shift * 4);
         TH1D H5("H5", Title.c_str(), Bin[j], Min[j] + Shift * 4, Max[j] + Shift * 5);
         H1.Sumw2();
         H2.Sumw2();
         H3.Sumw2();
         H4.Sumw2();
         H5.Sumw2();

         H1.SetStats(0);
         H2.SetStats(0);
         H3.SetStats(0);
         H4.SetStats(0);
         H5.SetStats(0);

         string CutString;
         CutString = Form("JetPT > %f && JetPT < %f && abs(JetEta) < 1.3 && MatchDR < 0.1 && Centrality >= %f && Centrality < %f && NEF < 0.99 && NHF < 0.99 && NEF > 0.01 && NHF > 0.01 && CHF > 0.01 && CHF < 0.99 && MUF < 1e-6", PTMin[i], PTMax[i], CentralityMin[i], CentralityMax[i]);
         if(j == 2)
            CutString = Form("JetPT > %f && JetPT < %f && abs(JetEta) < 1.3 && Centrality >= %f && Centrality < %f && NEF < 0.99 && NHF < 0.99 && NEF > 0.01 && NHF > 0.01 && CHF > 0.01 && CHF < 0.99 && MUF < 1e-6", PTMin[i], PTMax[i], CentralityMin[i], CentralityMax[i]);

         if(SD[j] == 0)
            CutString = CutString + " && SubJetDR0 > 0.1";
         if(SD[j] == 7)
            CutString = CutString + " && SubJetDR7 > 0.1";

         T1->Draw(Form("%s>>H1", ToPlot[j].c_str()), (CutString + " && PassPbPb100").c_str());
         T2->Draw(Form("%s>>H2", ToPlot[j].c_str()), (CutString + " && PassPbPb80").c_str());
         T3->Draw(Form("%s>>H3", ToPlot[j].c_str()), (CutString + " && PassPbPb60").c_str());
         T4->Draw(Form("%s>>H4", ToPlot[j].c_str()), (CutString + " && PassPbPb100").c_str());
         T5->Draw(Form("%s>>H5", ToPlot[j].c_str()), (CutString + " && PassPbPb60 && PassPbPb100").c_str());

         if(NormalizeStart[j] > 0 && NormalizeEnd[j] > 0)
         {
            H1.Scale(1 / H1.Integral(NormalizeStart[j], NormalizeEnd[j]));
            H2.Scale(1 / H2.Integral(NormalizeStart[j], NormalizeEnd[j]));
            H3.Scale(1 / H3.Integral(NormalizeStart[j], NormalizeEnd[j]));
            H4.Scale(1 / H4.Integral(NormalizeStart[j], NormalizeEnd[j]));
            H5.Scale(1 / H5.Integral(NormalizeStart[j], NormalizeEnd[j]));
         }

         H1.SetLineColor(kRed);
         H2.SetLineColor(kBlue);
         H3.SetLineColor(kGreen);
         H4.SetLineColor(kPink);
         H5.SetLineColor(kYellow + 3);

         H1.SetMarkerColor(kRed);
         H2.SetMarkerColor(kBlue);
         H3.SetMarkerColor(kGreen);
         H4.SetMarkerColor(kPink);
         H5.SetMarkerColor(kYellow + 3);

         H4.SetLineWidth(2);

         TLegend Legend(L[j], B[j], R[j], T[j]);
         Legend.SetTextFont(42);
         Legend.SetTextSize(0.035);
         Legend.SetBorderSize(0);
         Legend.SetFillStyle(0);
         // Legend.AddEntry(&H1, "Jet100", "lp");
         Legend.AddEntry(&H2, "Jet80", "lp");
         Legend.AddEntry(&H3, "Jet60", "lp");
         // Legend.AddEntry(&H5, "Jet100 && Jet60", "lp");

         TCanvas C;

         H3.Draw();
         H1.Draw("same");
         H2.Draw("same");
         H4.Draw("same");
         H5.Draw("same");
         Legend.Draw();

         if(Log[j] == true)
            C.SetLogy();

         PdfFile.AddCanvas(C);

         TGraphAsymmErrors GR1, GR2, GR3, GR5;

         // GR1.Divide(&H1, &H4, DivideString);
         // GR2.Divide(&H2, &H4, DivideString);
         // GR3.Divide(&H3, &H4, DivideString);
         // GR5.Divide(&H5, &H4, DivideString);

         GR1.SetLineColor(H1.GetLineColor());
         GR2.SetLineColor(H2.GetLineColor());
         GR3.SetLineColor(H3.GetLineColor());
         GR5.SetLineColor(H5.GetLineColor());
         
         GR1.SetMarkerColor(H1.GetMarkerColor());
         GR2.SetMarkerColor(H2.GetMarkerColor());
         GR3.SetMarkerColor(H3.GetMarkerColor());
         GR5.SetMarkerColor(H5.GetMarkerColor());

         for(int i = 1; i <= Bin[j]; i++)
         {
            double R, ER1, ER2, ER;
         
            R = H1.GetBinContent(i) / H2.GetBinContent(i);
            ER1 = H1.GetBinError(i) / H1.GetBinContent(i);
            ER2 = H2.GetBinError(i) / H2.GetBinContent(i);
            ER = R * sqrt(ER1 * ER1 + ER2 * ER2);
            GR1.SetPoint(i - 1, H1.GetBinCenter(i), R);
            GR1.SetPointError(i - 1, 0, 0, ER, ER);
         
            R = H2.GetBinContent(i) / H2.GetBinContent(i);
            ER1 = H2.GetBinError(i) / H2.GetBinContent(i);
            ER2 = H2.GetBinError(i) / H2.GetBinContent(i);
            ER = R * sqrt(ER1 * ER1 + ER2 * ER2);
            GR2.SetPoint(i - 1, H1.GetBinCenter(i), R);
            GR2.SetPointError(i - 1, 0, 0, ER, ER);
         
            R = H3.GetBinContent(i) / H2.GetBinContent(i);
            ER1 = H3.GetBinError(i) / H3.GetBinContent(i);
            ER2 = H2.GetBinError(i) / H2.GetBinContent(i);
            ER = R * sqrt(ER1 * ER1 + ER2 * ER2);
            GR3.SetPoint(i - 1, H1.GetBinCenter(i), R);
            GR3.SetPointError(i - 1, 0, 0, ER, ER);
         
            R = H5.GetBinContent(i) / H2.GetBinContent(i);
            ER1 = H5.GetBinError(i) / H5.GetBinContent(i);
            ER2 = H2.GetBinError(i) / H2.GetBinContent(i);
            ER = R * sqrt(ER1 * ER1 + ER2 * ER2);
            GR5.SetPoint(i - 1, H1.GetBinCenter(i), R);
            GR5.SetPointError(i - 1, 0, 0, ER, ER);
         }

         // H1.GetYaxis()->SetTitle("JetXX (dataset with prescale) / Jet100 (unprescaled)");
         H1.GetYaxis()->SetTitle("JetXX / Jet80");

         H1.SetMinimum(0);
         H1.SetMaximum(2);

         TGraph G;
         G.SetPoint(0, 0, 1);
         G.SetPoint(1, 10000, 1);

         H1.Draw("axis");
         // GR1.Draw("p");
         GR2.Draw("p");
         GR3.Draw("p");
         // GR5.Draw("p");
         G.Draw("l");
         Legend.Draw();

         C.SetLogy(false);

         PdfFile.AddCanvas(C);

         TGraphAsymmErrors GRatio;
         GRatio.Divide(&H5, &H3, DivideString);

         GRatio.Draw("ap");
         G.Draw("l");

         GRatio.GetXaxis()->SetTitle(H5.GetXaxis()->GetTitle());

         TGraph G2;
         G2.SetLineColor(kBlue);
         G2.SetLineStyle(kDashed);
         G2.SetPoint(0, 140, 0);
         G2.SetPoint(1, 140, 2);
         G2.SetPoint(2, 160, 2);
         G2.SetPoint(3, 160, 0);
         G2.SetPoint(4, 180, 0);
         G2.SetPoint(5, 180, 2);
         G2.SetPoint(6, 200, 2);
         G2.SetPoint(7, 200, 0);
         G2.SetPoint(8, 300, 0);
         G2.SetPoint(9, 300, 2);
         G2.Draw("l");

         PdfFile.AddCanvas(C);
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




