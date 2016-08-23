#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TGraph.h"

#include "SetStyle.h"

int main()
{
   TFile F1("SMVV_JobBoth_ggPDF_J_PriorN.root");
   TFile F2("SMVV_JobBoth_ggPDF_J_PriorY.root");
   TFile F3("5plet_JobBoth_ggPDF_J_PriorN.root");
   TFile F4("5plet_JobBoth_ggPDF_J_PriorY.root");

   TTree *Tree1 = (TTree *)F1.Get("Tree");
   TTree *Tree2 = (TTree *)F2.Get("Tree");
   TTree *Tree3 = (TTree *)F3.Get("Tree");
   TTree *Tree4 = (TTree *)F4.Get("Tree");

   Tree1->SetMarkerColor(kBlue);
   Tree1->SetLineColor(kBlue);
   Tree1->SetFillColor(kBlue);
   Tree1->SetLineStyle(kDashed);
   Tree1->SetLineColor(2);
   
   Tree2->SetMarkerColor(kBlue);
   Tree2->SetLineColor(kBlue);
   Tree2->SetFillColor(kBlue);
   Tree2->SetLineWidth(2);
   
   Tree3->SetMarkerColor(kRed);
   Tree3->SetLineColor(kRed);
   Tree3->SetFillColor(kRed);
   Tree3->SetLineStyle(kDashed);
   Tree3->SetLineColor(2);

   Tree4->SetMarkerColor(kRed);
   Tree4->SetLineColor(kRed);
   Tree4->SetFillColor(kRed);
   Tree4->SetLineColor(2);

   SetThesisStyle();

   int EventCount[10] = {50, 100, 200, 400, 600, 1000, 2000, 4000, 7000, 10000};

   for(int i = 0; i < 10; i++)
   {
      TH1D H1(Form("H1_%d", EventCount[i]), "p-value, SM, ggPDF;p-value", 100, 0, 1);
      TH1D H2(Form("H2_%d", EventCount[i]), "p-value, SM, noPDF;p-value", 100, 0, 1);
      TH1D H3(Form("H3_%d", EventCount[i]), "p-value, 5plet, noPDF;p-value", 100, 0, 1);
      TH1D H4(Form("H4_%d", EventCount[i]), "p-value, 5plet, noPDF;p-value", 100, 0, 1);

      Tree1->Draw(Form("P>>H1_%d", EventCount[i]), Form("N == %d", EventCount[i]));
      Tree2->Draw(Form("P>>H2_%d", EventCount[i]), Form("N == %d", EventCount[i]));
      Tree3->Draw(Form("P>>H3_%d", EventCount[i]), Form("N == %d", EventCount[i]));
      Tree4->Draw(Form("P>>H4_%d", EventCount[i]), Form("N == %d", EventCount[i]));

      H1.Scale(1.0 / H1.Integral());
      H2.Scale(1.0 / H2.Integral());
      H3.Scale(1.0 / H3.Integral());
      H4.Scale(1.0 / H4.Integral());

      H1.SetLineWidth(3);
      H2.SetLineWidth(2);
      H3.SetLineWidth(3);
      H4.SetLineWidth(2);
      
      H1.SetLineColor(kBlue + 3);
      H2.SetLineColor(kBlue);
      H3.SetLineColor(kRed + 3);
      H4.SetLineColor(kRed);

      H1.SetLineStyle(kDashed);
      H3.SetLineStyle(kDashed);

      H1.SetTitle("");
      H1.SetStats(false);

      TCanvas C;
      H1.Draw();
      H2.Draw("same");
      H3.Draw("same");
      H4.Draw("same");

      C.SaveAs(Form("Meow%d.png", EventCount[i]));
      C.SaveAs(Form("Meow%d.C", EventCount[i]));
      C.SaveAs(Form("Meow%d.eps", EventCount[i]));
      C.SaveAs(Form("Meow%d.pdf", EventCount[i]));
   }

   F2.Close();
   F1.Close();

   return 0;
}
