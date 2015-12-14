#include <string>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TGraphAsymmErrors.h"

#include "PlotHelper2.h"

int main();
void CompareHistograms(PsFileHelper &PsFile, TFile &FAll, TFile &F0, TFile &F1, TFile &F2, string Name);

int main()
{
   PsFileHelper PsFile("ComparisonPlots.ps");
   PsFile.AddTextPage("Comparison of QCD shapes");

   TFile FAll("BQCDAll.root");
   TFile F0("BQCD_B0.root");
   TFile F1("BQCD_B1.root");
   TFile F2("BQCD_B2.root");

   CompareHistograms(PsFile, FAll, F0, F1, F2, "HMRNew");
   CompareHistograms(PsFile, FAll, F0, F1, F2, "HMRNew_R2New005");
   CompareHistograms(PsFile, FAll, F0, F1, F2, "HMRNew_R2New010");
   CompareHistograms(PsFile, FAll, F0, F1, F2, "HMRNew_R2New015");
   CompareHistograms(PsFile, FAll, F0, F1, F2, "HMRNew_R2New020");
   CompareHistograms(PsFile, FAll, F0, F1, F2, "HMRNew_R2New025");
   CompareHistograms(PsFile, FAll, F0, F1, F2, "HMRNew_R2New030");
   CompareHistograms(PsFile, FAll, F0, F1, F2, "HR2New");
   CompareHistograms(PsFile, FAll, F0, F1, F2, "HR2New_MRNew200");
   CompareHistograms(PsFile, FAll, F0, F1, F2, "HR2New_MRNew400");

   F2.Close();
   F1.Close();
   F0.Close();
   FAll.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void CompareHistograms(PsFileHelper &PsFile, TFile &FAll, TFile &F0, TFile &F1, TFile &F2, string Name)
{
   TH1D *HAll = (TH1D *)FAll.Get(Name.c_str());
   TH1D *H0 = (TH1D *)F0.Get(Name.c_str());
   TH1D *H1 = (TH1D *)F1.Get(Name.c_str());
   TH1D *H2 = (TH1D *)F2.Get(Name.c_str());

   H0->SetLineColor(2);
   H1->SetLineColor(3);
   H2->SetLineColor(4);

   HAll->SetStats(0);
   H0->SetStats(0);
   H1->SetStats(0);
   H2->SetStats(0);

   TCanvas C;

   HAll->Draw("hist");
   H0->Draw("same hist");
   H1->Draw("same hist");
   H2->Draw("same hist");

   TLegend legend(0.6, 0.8, 0.9, 0.6);
   legend.SetFillStyle(0);
   legend.SetBorderSize(0);
   legend.AddEntry(HAll, "Inclusive", "l");
   legend.AddEntry(H0, "No b-tag", "l");
   legend.AddEntry(H1, "One b-tag", "l");
   legend.AddEntry(H2, "More b-tags", "l");
   legend.Draw();

   C.SetLogy();
   PsFile.AddCanvas(C);

   TCanvas C2;

   TH1D HWorld("HWorld", Form("Ratio to the inclusive for %s", HAll->GetTitle()),
      HAll->GetNbinsX(), HAll->GetXaxis()->GetBinLowEdge(1), HAll->GetXaxis()->GetBinUpEdge(HAll->GetNbinsX()));
   HWorld.GetXaxis()->SetTitle(HAll->GetXaxis()->GetTitle());
   HWorld.SetMaximum(1);
   HWorld.SetMinimum(0);
   HWorld.SetStats(0);
   HWorld.Draw();

   TGraphAsymmErrors G0, G1, G2;
   G0.BayesDivide(H0, HAll);
   G1.BayesDivide(H1, HAll);
   G2.BayesDivide(H2, HAll);

   G0.SetLineColor(2);
   G1.SetLineColor(3);
   G2.SetLineColor(4);

   G0.Draw("pe");
   G1.Draw("pe");
   G2.Draw("pe");

   PsFile.AddCanvas(C2);
}





