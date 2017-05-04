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

   TFile F("AADataPrescale.root");

   TTree *Tree = (TTree *)F.Get("T");

   double PTMin[] = {140, 140, 140, 140, 160, 160, 160, 160, 180, 180};
   double PTMax[] = {160, 160, 160, 160, 180, 180, 180, 180, 500, 500};
   double CentralityMin[] = {0.0, 0.1, 0.3, 0.5, 0.0, 0.1, 0.3, 0.5, 0.0, 0.0};
   double CentralityMax[] = {0.1, 0.3, 0.5, 0.8, 0.1, 0.3, 0.5, 0.8, 0.1, 0.3};

   PdfFileHelper PdfFile("JetCharacteristics.pdf");
   PdfFile.AddTextPage("Pass vs not pass Jet100");

   string ToPlot[] = {"SDMass0/MatchPT", "SubJetDR0", "ZG0", "SDMass7/MatchPT", "SubJetDR7", "ZG7", "JetEta", "JetPhi"};
   string Label[] = {"Mass/PT (0)", "DR (0)", "ZG (0)", "Mass/PT (7)", "DR (7)", "ZG (7)", "eta", "phi"};

   double PI = 3.1415926535;

   int Bin[] = {25, 25, 25, 25, 25, 25, 25, 25};
   double Min[] = {0.00, 0.10, 0.00, 0.00, 0.10, 0.00, -1.5, -PI};
   double Max[] = {0.26, 0.40, 0.50, 0.26, 0.40, 0.50, +1.5, +PI};

   double L[] = {0.50, 0.15, 0.50, 0.50, 0.15, 0.50, 0.15, 0.50};
   double R[] = {0.80, 0.45, 0.80, 0.80, 0.45, 0.80, 0.45, 0.80};
   double B[] = {0.60, 0.60, 0.60, 0.60, 0.60, 0.60, 0.60, 0.60};
   double T[] = {0.85, 0.85, 0.85, 0.85, 0.85, 0.85, 0.85, 0.85};

   int SD[] = {0, 0, 0, 7, 7, 7, -1, -1};

   bool Log[] = {false, false, false, false, false, false, false, false};
   // int NormalizeStart[] = {-1, -1, -1, -1, -1, -1, -1, -1};
   // int NormalizeEnd[] = {-1, -1, -1, -1, -1, -1, -1, -1};
   int NormalizeStart[] = {1, 1, 1, 1, 1, 1, 1, 1};
   int NormalizeEnd[] = {Bin[0], Bin[1], Bin[2], Bin[3], Bin[4], Bin[5], Bin[6], Bin[7]};

   bool Switch[10][8] =
   {
      {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1}
   };

   Tree->SetAlias("ZG0", "(min(SubJet1PT0, SubJet2PT0) / (SubJet1PT0 + SubJet2PT0))");
   Tree->SetAlias("ZG7", "(min(SubJet1PT7, SubJet2PT7) / (SubJet1PT7 + SubJet2PT7))");

   for(int i = 0; i < 10; i++)
   {
      PdfFile.AddTextPage(Form("PT %.0f-%.0f, Centrality %.2f-%.2f",
         PTMin[i], PTMax[i], CentralityMin[i], CentralityMax[i]));

      for(int j = 0; j < 8; j++)
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
         H1.Sumw2();
         H2.Sumw2();
         H3.Sumw2();

         H1.SetStats(0);
         H2.SetStats(0);
         H3.SetStats(0);

         string CutString;
         CutString = Form("JetPT > %f && JetPT < %f && abs(JetEta) < 1.3 && MatchDR < 0.1 && Centrality >= %f && Centrality < %f && NEF < 0.99 && NHF < 0.99 && NEF > 0.01 && NHF > 0.01 && CHF > 0.01 && CHF < 0.99 && MUM == 0", PTMin[i], PTMax[i], CentralityMin[i], CentralityMax[i]);

         if(SD[j] == 0)
            CutString = CutString + " && SubJetDR0 > 0.1";
         if(SD[j] == 7)
            CutString = CutString + " && SubJetDR7 > 0.1";
         
         Tree->Draw(Form("%s>>H1", ToPlot[j].c_str()), (CutString + " && PassPbPb80").c_str());
         Tree->Draw(Form("%s>>H2", ToPlot[j].c_str()), (CutString + " && PassPbPb80 && PassPbPb100").c_str());
         Tree->Draw(Form("%s>>H3", ToPlot[j].c_str()), (CutString + " && PassPbPb80 && !PassPbPb100").c_str());

         if(NormalizeStart[j] > 0 && NormalizeEnd[j] > 0)
         {
            H1.Scale(1 / H1.Integral(NormalizeStart[j], NormalizeEnd[j]));
            H2.Scale(1 / H2.Integral(NormalizeStart[j], NormalizeEnd[j]));
            H3.Scale(1 / H3.Integral(NormalizeStart[j], NormalizeEnd[j]));
         }

         H1.SetLineColor(kRed);
         H2.SetLineColor(kBlue);
         H3.SetLineColor(kGreen);

         H1.SetMarkerColor(kRed);
         H2.SetMarkerColor(kBlue);
         H3.SetMarkerColor(kGreen);

         TLegend Legend(L[j], B[j], R[j], T[j]);
         Legend.SetTextFont(42);
         Legend.SetTextSize(0.035);
         Legend.SetBorderSize(0);
         Legend.SetFillStyle(0);
         // Legend.AddEntry(&H1, "Jet80", "lp");
         Legend.AddEntry(&H2, "Yes trigger", "lp");
         Legend.AddEntry(&H3, "No trigger", "lp");

         H1.SetMaximum(max(H2.GetMaximum(), H3.GetMaximum()) * 1.25);
         H1.SetMinimum(0);

         TCanvas C;

         H1.Draw("axis");
         H2.Draw("same");
         H3.Draw("same");
         Legend.Draw();

         if(Log[j] == true)
            C.SetLogy();

         PdfFile.AddCanvas(C);

         /*
         TGraphAsymmErrors GR2, GR3;

         GR2.Divide(&H2, &H1, "cl=0.683 b(1,1) mode");
         GR3.Divide(&H3, &H1, "cl=0.683 b(1,1) mode");

         GR2.SetLineColor(H2.GetLineColor());
         GR3.SetLineColor(H3.GetLineColor());
         
         GR2.SetMarkerColor(H2.GetMarkerColor());
         GR3.SetMarkerColor(H3.GetMarkerColor());

         H1.SetMinimum(0);
         H1.SetMaximum(2);

         TGraph G;
         G.SetPoint(0, 0, 1);
         G.SetPoint(1, 10000, 1);

         H1.Draw("axis");
         GR2.Draw("p");
         GR3.Draw("p");
         G.Draw("l");
         Legend.Draw();

         C.SetLogy(false);

         PdfFile.AddCanvas(C);
         */

         /*
         TGraphAsymmErrors GRatio;
         GRatio.Divide(&H5, &H3, "cl=0.683 b(1,1) mode");

         GRatio.Draw("ap");
         G.Draw("l");

         GRatio.GetXaxis()->SetTitle(H5.GetXaxis()->GetTitle());

         TGraph G2;
         G2.SetPoint(0, 140, 0);
         G2.SetPoint(1, 140, 2);
         G2.SetPoint(2, 160, 2);
         G2.SetPoint(3, 160, 0);
         G2.Draw("l");

         PdfFile.AddCanvas(C);
         */
      }
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




