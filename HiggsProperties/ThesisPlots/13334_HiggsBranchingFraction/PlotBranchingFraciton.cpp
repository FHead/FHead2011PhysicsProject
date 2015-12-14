#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main()
{
   SetThesisRegularStyle();

   TFile F("BranchingRatio.root");
   TTree *T = (TTree *)F.Get("Tree");

   double Left = 90, Right = 500;

   TH2D *HWorld = new TH2D("HWorld", ";m_{H} (GeV);Br(h->X)", 1000, Left, Right, 1000, 1e-5, 100);
   HWorld->SetStats(0);

   // HWorld->GetXaxis()->SetTitleOffset(1.1);
   // HWorld->GetYaxis()->SetTitleOffset(1.2);
   HWorld->GetXaxis()->SetLabelSize(0.0);

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035 * 2 / 1.30);
   Latex.SetTextAlign(21);
   Latex.SetNDC();

   TCanvas C;

   HWorld->Draw();

   double LabelY = ThesisNDCMappingRegularY(0.01);

   Latex.DrawLatex(ThesisNDCMappingRegularX(0.1 + (0.9 - 0.1) / (log(Right) - log(Left)) * (log(100) - log(Left))), LabelY, "100");
   Latex.DrawLatex(ThesisNDCMappingRegularX(0.1 + (0.9 - 0.1) / (log(Right) - log(Left)) * (log(200) - log(Left))), LabelY, "200");
   Latex.DrawLatex(ThesisNDCMappingRegularX(0.1 + (0.9 - 0.1) / (log(Right) - log(Left)) * (log(300) - log(Left))), LabelY, "300");
   Latex.DrawLatex(ThesisNDCMappingRegularX(0.1 + (0.9 - 0.1) / (log(Right) - log(Left)) * (log(400) - log(Left))), LabelY, "400");

   T->SetLineWidth(2);
   T->SetLineColor(kBlack);
   T->Draw("llll:M", "", "L same");
   T->SetLineColor(kBlue);
   T->Draw("llvv:M", "", "L same");
   T->SetLineColor(kRed);
   T->Draw("bb:M", "", "L same");
   T->SetLineColor(kGreen - 3);
   T->Draw("tt:M", "", "L same");
   T->SetLineColor(kYellow - 3);
   T->Draw("tautau:M", "", "L same");
   T->SetLineColor(kCyan + 3);
   T->Draw("llqq+qqqq+lvqq*2:M", "", "L same");
   
   TH1D *H1 = new TH1D("H1", "", 1, 0, 1);   H1->SetLineWidth(2), H1->SetLineColor(kBlack);
   TH1D *H2 = new TH1D("H2", "", 1, 0, 1);   H2->SetLineWidth(2), H2->SetLineColor(kBlue);
   TH1D *H3 = new TH1D("H3", "", 1, 0, 1);   H3->SetLineWidth(2), H3->SetLineColor(kRed);
   TH1D *H4 = new TH1D("H4", "", 1, 0, 1);   H4->SetLineWidth(2), H4->SetLineColor(kGreen - 3);
   TH1D *H5 = new TH1D("H5", "", 1, 0, 1);   H5->SetLineWidth(2), H5->SetLineColor(kYellow - 3);
   TH1D *H6 = new TH1D("H6", "", 1, 0, 1);   H6->SetLineWidth(2), H6->SetLineColor(kCyan + 3);

   double LegendX1 = ThesisNDCMappingRegularX(0.22);
   double LegendX2 = ThesisNDCMappingRegularX(0.71);
   double LegendY1 = ThesisNDCMappingRegularY(0.66);
   double LegendY2 = ThesisNDCMappingRegularY(0.86);

   TLegend Legend1(LegendX1, LegendY1, LegendX2, LegendY2);
   Legend1.SetFillStyle(0);
   Legend1.SetTextFont(42);
   Legend1.SetBorderSize(0);
   Legend1.SetTextSize(0.025 * 2 / 1.30);
   Legend1.AddEntry(H4, "tt", "l");
   Legend1.AddEntry(H5, "#tau#tau", "l");
   Legend1.AddEntry(H3, "bb", "l");
   Legend1.Draw();
   
   LegendX1 = ThesisNDCMappingRegularX(0.42);
   LegendX2 = ThesisNDCMappingRegularX(0.87);
   LegendY1 = ThesisNDCMappingRegularY(0.66);
   LegendY2 = ThesisNDCMappingRegularY(0.86);
   
   TLegend Legend2(LegendX1, LegendY1, LegendX2, LegendY2);
   Legend2.SetFillStyle(0);
   Legend2.SetTextFont(42);
   Legend2.SetBorderSize(0);
   Legend2.SetTextSize(0.025 * 2 / 1.30);
   Legend2.AddEntry(H1, "ZZ^{(*)}#rightarrow 4l", "l");
   Legend2.AddEntry(H2, "2l2#nu", "l");
   Legend2.AddEntry(H6, "2l2q+l#nuqq+qqqq", "l");
   Legend2.Draw();

   C.SetLogx();
   C.SetLogy();

   C.SaveAs("SMAndHiggs-Decays-BranchingFraction.png");
   C.SaveAs("SMAndHiggs-Decays-BranchingFraction.C");
   C.SaveAs("SMAndHiggs-Decays-BranchingFraction.eps");
   C.SaveAs("SMAndHiggs-Decays-BranchingFraction.pdf");

   return 0;
}
