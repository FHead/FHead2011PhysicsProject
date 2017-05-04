#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLatex.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " Input Tag" << endl;
      return -1;
   }

   SetThesisStyle();

   string Tag = argv[2];

   TFile File(argv[1]);

   TTree *Tree = (TTree *)File.Get("Tree");

   if(Tree == NULL)
      return -1;

   double Type;
   double N, N140, N200;
   Tree->SetBranchAddress("Type", &Type);
   Tree->SetBranchAddress("N", &N);
   Tree->SetBranchAddress("N140", &N140);
   Tree->SetBranchAddress("N200", &N200);

   TGraph GJet140, GJet200;
   TGraph GEGJet140, GEGJet200;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(Tag == "TT")
      {
         if(Type == 0)
         {
            if(N < 50 || N > 200)
               continue;

            GJet140.SetPoint(GJet140.GetN(), N, N140);
            GJet200.SetPoint(GJet200.GetN(), N, N200);
         }
      }
      if(Tag == "WENu")
      {
         if(Type == 1)
         {
            if(N < 18 || N > 40)
               continue;

            GJet140.SetPoint(GJet140.GetN(), N, N200);
         }
         if(Type == 2)
         {
            if(N < 18 || N > 40)
               continue;

            GJet200.SetPoint(GJet200.GetN(), N, N200);
         }
      }
   }

   gStyle->SetOptFit(0000);

   TH2D *HWorld = NULL;
   if(Tag == "TT")
      HWorld = new TH2D("HWorld", ";online: L1 jet E_{T} (GeV);offline: E_{T} (GeV)", 100, 30, 220, 100, 0, 400);
   if(Tag == "WENu")
      HWorld = new TH2D("HWorld", ";online: L1 tkEG E_{T} (GeV);offline: p_{T} (GeV)", 100, 10, 32, 100, 5, 50);
   HWorld->SetStats(0);

   TGraph G1, G2, G3;
   if(Tag == "TT")
   {
      G1.SetPoint(0,    0, 6.413 + 1.25 * 0);
      G1.SetPoint(1, 1000, 6.413 + 1.25 * 1000);
      G2.SetPoint(0,    0, 27.45 + 1.075 * 0);
      G2.SetPoint(1, 1000, 27.45 + 1.075 * 1000);
      G3.SetPoint(0, 25, 50);
      G3.SetPoint(1, 220, 350);
   }
   if(Tag == "WENu")
   {
      G1.SetPoint(0,    0, 4.393 + 0.909 * 0);
      G1.SetPoint(1, 1000, 4.393 + 0.909 * 1000);
      G2.SetPoint(0,    0, 7.164 + 0.8417 * 0);
      G2.SetPoint(1, 1000, 7.164 + 0.8417 * 1000);
      G3.SetPoint(0, 10.0, 19.2);
      G3.SetPoint(1, 32.0, 39.5);
   }

   G1.SetLineStyle(kDashed);
   G2.SetLineStyle(kDashed);
   G3.SetLineStyle(kDotted);

   G1.SetLineWidth(2);
   G2.SetLineWidth(2);
   G3.SetLineWidth(2);

   G1.SetLineColor(kYellow + 3);
   G2.SetLineColor(kGreen - 3);
   G3.SetLineColor(kBlack);

   TF1 F140("F140", "pol1", 0, 500);
   TF1 F200("F200", "pol1", 0, 500);

   double FitMin = 14, FitMax = 50;
   if(Tag == "TT")
      FitMin = 0, FitMax = 500;
   if(Tag == "WENu")
      FitMin = 18, FitMax = 50;

   GJet140.Fit(&F140, "", "", FitMin, FitMax);
   GJet200.Fit(&F200, "", "", FitMin, FitMax);

   F140.SetLineColor(kBlue);
   F200.SetLineColor(kRed);

   GJet140.SetLineWidth(2);
   GJet200.SetLineWidth(2);

   GJet140.SetLineColor(kBlue);
   GJet200.SetLineColor(kRed);

   GJet140.SetMarkerColor(kBlue);
   GJet200.SetMarkerColor(kRed);

   TCanvas C;

   HWorld->Draw("");
   GJet140.Draw("p");
   GJet200.Draw("p");

   F140.Draw("same");
   F200.Draw("same");

   G1.Draw("l");
   G2.Draw("l");
   G3.Draw("l");

   TLegend Legend(0.5, 0.15, 0.75, 0.40);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   if(Tag == "TT")
   {
      Legend.AddEntry(&GJet140, "TT140", "pl");
      Legend.AddEntry(&GJet200, "TT200", "pl");
      Legend.AddEntry(&G2, "Fig. 14 (gen jet)", "l");
      Legend.AddEntry(&G1, "Fig. 14 (parton)", "l");
      Legend.AddEntry(&G3, "TDR (uncalibrated)", "l");
   }
   if(Tag == "WENu")
   {
      Legend.AddEntry(&GJet140, "isoTkEle WENu200", "pl");
      Legend.AddEntry(&GJet200, "tkEM WENu200", "pl");
      Legend.AddEntry(&G2, "Fig. 6 (isoEG)", "l");
      Legend.AddEntry(&G1, "Fig. 6 (isoTkEle)", "l");
      Legend.AddEntry(&G3, "TDR (uncalibrated)", "l");
   }
   Legend.Draw();

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetNDC();
   Latex.SetTextColor(kBlue);
   if(Tag == "TT")
      Latex.DrawLatex(0.15, 0.80, "TT140");
   if(Tag == "WENu")
      Latex.DrawLatex(0.15, 0.80, "isoTkEle");
   Latex.SetTextColor(kBlack);
   Latex.DrawLatex(0.15, 0.75, Form("   p0 = %.3f #pm %.3f", F140.GetParameter(0), F140.GetParError(0)));
   Latex.DrawLatex(0.15, 0.70, Form("   p1 = %.3f #pm %.3f", F140.GetParameter(1), F140.GetParError(1)));
   Latex.SetTextColor(kRed);
   if(Tag == "TT")
      Latex.DrawLatex(0.15, 0.65, "TT200");
   if(Tag == "WENu")
      Latex.DrawLatex(0.15, 0.65, "tkEM");
   Latex.SetTextColor(kBlack);
   Latex.DrawLatex(0.15, 0.60, Form("   p0 = %.3f #pm %.3f", F200.GetParameter(0), F200.GetParError(0)));
   Latex.DrawLatex(0.15, 0.55, Form("   p1 = %.3f #pm %.3f", F200.GetParameter(1), F200.GetParError(1)));

   C.SaveAs(Form("ScalingPlot%s.png", argv[2]));
   C.SaveAs(Form("ScalingPlot%s.C"  , argv[2]));
   C.SaveAs(Form("ScalingPlot%s.eps", argv[2]));
   C.SaveAs(Form("ScalingPlot%s.pdf", argv[2]));

   delete HWorld;

   File.Close();

   return 0;
}





