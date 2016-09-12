#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TProfile2D.h"
#include "TLatex.h"
#include "TLegend.h"

#include "SetStyle.h"

#include "BasicUtilities.h"

int main(int argc, char *argv[]);
void NormalizeHistogram(TH1D *H);
void NormalizeHistogram(TH1D *H1, TH1D *H2);
void ExportHistogram2D(TFile &F, string Name, string OutputBase, string Tag, string PlotOption = "colz");
void ExportProfile2D(TFile &F, string Name, string OutputBase, string Tag, string PlotOption = "colz");
void ExportHistogram2DWithProfile(TFile &F, string Name, string PName, string OutputBase, string Tag,
   string PlotOption = "colz", string POption = "");

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputBase" << endl;
      return -1;
   }

   SetThesisStyle();

   char *InputFile = argv[1];
   string OutputBase = argv[2];

   bool IsPP = IsPPFromTag(InputFile);

   TFile F(InputFile);

   TCanvas Canvas;
   
   TLatex TagLatex;
   TagLatex.SetNDC();
   TagLatex.SetTextFont(42);
   TagLatex.SetTextSize(0.02);

   ExportHistogram2D(F, "HSDMassRatioVsRecoDR",
      OutputBase + "_SDMassRatioVsRecoDR", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsRecoDR_CBin0",
      OutputBase + "_SDMassRatioVsRecoDR_CBin0", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsRecoDR_CBin1",
      OutputBase + "_SDMassRatioVsRecoDR_CBin1", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsRecoDR_CBin2",
      OutputBase + "_SDMassRatioVsRecoDR_CBin2", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsRecoDR_CBin3",
      OutputBase + "_SDMassRatioVsRecoDR_CBin3", OutputBase, "colz");
   ExportHistogram2D(F, "HSDMassRatioVsRecoDR_CBin4",
      OutputBase + "_SDMassRatioVsRecoDR_CBin4", OutputBase, "colz");

   TH1D *HRecoDR_CBin0 = ((TH2D *)F.Get("HSDMassRatioVsRecoDR_CBin0"))->ProjectionX("HRecoDR_CBin0");
   TH1D *HRecoDR_CBin1 = ((TH2D *)F.Get("HSDMassRatioVsRecoDR_CBin1"))->ProjectionX("HRecoDR_CBin1");
   TH1D *HRecoDR_CBin2 = ((TH2D *)F.Get("HSDMassRatioVsRecoDR_CBin2"))->ProjectionX("HRecoDR_CBin2");
   TH1D *HRecoDR_CBin3 = ((TH2D *)F.Get("HSDMassRatioVsRecoDR_CBin3"))->ProjectionX("HRecoDR_CBin3");
   TH1D *HRecoDR_CBin4 = ((TH2D *)F.Get("HSDMassRatioVsRecoDR_CBin4"))->ProjectionX("HRecoDR_CBin4");

   HRecoDR_CBin0->Rebin(2);
   HRecoDR_CBin1->Rebin(2);
   HRecoDR_CBin2->Rebin(2);
   HRecoDR_CBin3->Rebin(2);
   HRecoDR_CBin4->Rebin(2);

   NormalizeHistogram(HRecoDR_CBin0);
   NormalizeHistogram(HRecoDR_CBin1);
   NormalizeHistogram(HRecoDR_CBin2);
   NormalizeHistogram(HRecoDR_CBin3);
   NormalizeHistogram(HRecoDR_CBin4);

   HRecoDR_CBin0->SetLineWidth(2);
   HRecoDR_CBin1->SetLineWidth(2);
   HRecoDR_CBin2->SetLineWidth(2);
   HRecoDR_CBin3->SetLineWidth(2);
   HRecoDR_CBin4->SetLineWidth(2);

   HRecoDR_CBin0->SetLineColor(kBlack);
   HRecoDR_CBin1->SetLineColor(kRed);
   HRecoDR_CBin2->SetLineColor(kBlue);
   HRecoDR_CBin3->SetLineColor(kCyan - 3);
   HRecoDR_CBin4->SetLineColor(kGreen - 3);

   TLegend RecoDRLegend(0.5, 0.8, 0.8, 0.6);
   RecoDRLegend.SetTextFont(42);
   RecoDRLegend.SetTextSize(0.035);
   RecoDRLegend.SetBorderSize(0);
   RecoDRLegend.SetFillStyle(0);
   RecoDRLegend.AddEntry(HRecoDR_CBin0, "0% - 10%", "l");
   RecoDRLegend.AddEntry(HRecoDR_CBin1, "10% - 30%", "l");
   RecoDRLegend.AddEntry(HRecoDR_CBin2, "30% - 50%", "l");
   RecoDRLegend.AddEntry(HRecoDR_CBin3, "50% - 80%", "l");
   RecoDRLegend.AddEntry(HRecoDR_CBin4, "80% - 180%", "l");

   TH2D HWorldRecoDR("HWorldRecoDR", ";Reconstructed Sub-jet #Delta R;a.u.", 100, 0, 0.5, 100, 0, 8);
   HWorldRecoDR.SetStats(0);

   HWorldRecoDR.Draw();
   HRecoDR_CBin0->Draw("same");
   HRecoDR_CBin1->Draw("same");
   HRecoDR_CBin2->Draw("same");
   HRecoDR_CBin3->Draw("same");
   HRecoDR_CBin4->Draw("same");
   if(IsPP == false)
      RecoDRLegend.Draw();
   TagLatex.DrawLatex(0.10, 0.92, OutputBase.c_str());

   Canvas.SaveAs(Form("%s_RecoDR.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_RecoDR.C", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_RecoDR.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_RecoDR.pdf", OutputBase.c_str()));

   ExportHistogram2D(F, "HSDMassRatioVsCentrality",
      OutputBase + "_SDMassRatioVsCentrality", OutputBase, "colz");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsCentrality_Bin0", "PSDMassRatioVsCentrality_Bin0",
      OutputBase + "_SDMassRatioVsCentrality_Bin0", OutputBase, "colz", "S");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsCentrality_Bin1", "PSDMassRatioVsCentrality_Bin1",
      OutputBase + "_SDMassRatioVsCentrality_Bin1", OutputBase, "colz", "S");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsCentrality_Bin2", "PSDMassRatioVsCentrality_Bin2",
      OutputBase + "_SDMassRatioVsCentrality_Bin2", OutputBase, "colz", "S");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsCentrality_Bin3", "PSDMassRatioVsCentrality_Bin3",
      OutputBase + "_SDMassRatioVsCentrality_Bin3", OutputBase, "colz", "S");

   ExportHistogram2D(F, "HRecoSubJetDRVsSubJetDRMax",
      OutputBase + "_RecoSubJetDRVsSubJetDRMax", OutputBase, "colz");
   ExportHistogram2D(F, "HRecoSubJetDRVsSubJetDRMax_CBin0",
      OutputBase + "_RecoSubJetDRVsSubJetDRMax_CBin0", OutputBase, "colz");
   ExportHistogram2D(F, "HRecoSubJetDRVsSubJetDRMax_CBin1",
      OutputBase + "_RecoSubJetDRVsSubJetDRMax_CBin1", OutputBase, "colz");
   ExportHistogram2D(F, "HRecoSubJetDRVsSubJetDRMax_CBin2",
      OutputBase + "_RecoSubJetDRVsSubJetDRMax_CBin2", OutputBase, "colz");
   ExportHistogram2D(F, "HRecoSubJetDRVsSubJetDRMax_CBin3",
      OutputBase + "_RecoSubJetDRVsSubJetDRMax_CBin3", OutputBase, "colz");
   ExportHistogram2D(F, "HRecoSubJetDRVsSubJetDRMax_CBin4",
      OutputBase + "_RecoSubJetDRVsSubJetDRMax_CBin4", OutputBase, "colz");

   ExportHistogram2D(F, "HRecoSubJetDRVsCentrality_I",
      OutputBase + "_RecoSubJetDRVsCentrality_I", OutputBase, "colz");
   ExportHistogram2D(F, "HRecoSubJetDRVsCentrality_II",
      OutputBase + "_RecoSubJetDRVsCentrality_II", OutputBase, "colz");
   ExportHistogram2D(F, "HRecoSubJetDRVsCentrality_III",
      OutputBase + "_RecoSubJetDRVsCentrality_III", OutputBase, "colz");

   TH1D *HRecoSubJetDRVsCentrality_I_CBin0 =
      ((TH2D *)F.Get("HRecoSubJetDRVsCentrality_I"))->ProjectionY("HRecoSubJetDRVsCentrality_I_CBin0", 1, 10);
   TH1D *HRecoSubJetDRVsCentrality_I_CBin1 =
      ((TH2D *)F.Get("HRecoSubJetDRVsCentrality_I"))->ProjectionY("HRecoSubJetDRVsCentrality_I_CBin1", 11, 30);
   TH1D *HRecoSubJetDRVsCentrality_I_CBin2 =
      ((TH2D *)F.Get("HRecoSubJetDRVsCentrality_I"))->ProjectionY("HRecoSubJetDRVsCentrality_I_CBin2", 31, 50);
   TH1D *HRecoSubJetDRVsCentrality_I_CBin3 =
      ((TH2D *)F.Get("HRecoSubJetDRVsCentrality_I"))->ProjectionY("HRecoSubJetDRVsCentrality_I_CBin3", 51, 80);
   TH1D *HRecoSubJetDRVsCentrality_I_CBin4 =
      ((TH2D *)F.Get("HRecoSubJetDRVsCentrality_I"))->ProjectionY("HRecoSubJetDRVsCentrality_I_CBin4", 81, 100);
   TH1D *HRecoSubJetDRVsCentrality_II_CBin0 =
      ((TH2D *)F.Get("HRecoSubJetDRVsCentrality_II"))->ProjectionY("HRecoSubJetDRVsCentrality_II_CBin0", 1, 10);
   TH1D *HRecoSubJetDRVsCentrality_II_CBin1 =
      ((TH2D *)F.Get("HRecoSubJetDRVsCentrality_II"))->ProjectionY("HRecoSubJetDRVsCentrality_II_CBin1", 11, 30);
   TH1D *HRecoSubJetDRVsCentrality_II_CBin2 =
      ((TH2D *)F.Get("HRecoSubJetDRVsCentrality_II"))->ProjectionY("HRecoSubJetDRVsCentrality_II_CBin2", 31, 50);
   TH1D *HRecoSubJetDRVsCentrality_II_CBin3 =
      ((TH2D *)F.Get("HRecoSubJetDRVsCentrality_II"))->ProjectionY("HRecoSubJetDRVsCentrality_II_CBin3", 51, 80);
   TH1D *HRecoSubJetDRVsCentrality_II_CBin4 =
      ((TH2D *)F.Get("HRecoSubJetDRVsCentrality_II"))->ProjectionY("HRecoSubJetDRVsCentrality_II_CBin4", 81, 100);

   HRecoSubJetDRVsCentrality_I_CBin0->Rebin(2);
   HRecoSubJetDRVsCentrality_I_CBin1->Rebin(2);
   HRecoSubJetDRVsCentrality_I_CBin2->Rebin(2);
   HRecoSubJetDRVsCentrality_I_CBin3->Rebin(2);
   HRecoSubJetDRVsCentrality_I_CBin4->Rebin(2);
   HRecoSubJetDRVsCentrality_II_CBin0->Rebin(2);
   HRecoSubJetDRVsCentrality_II_CBin1->Rebin(2);
   HRecoSubJetDRVsCentrality_II_CBin2->Rebin(2);
   HRecoSubJetDRVsCentrality_II_CBin3->Rebin(2);
   HRecoSubJetDRVsCentrality_II_CBin4->Rebin(2);

   NormalizeHistogram(HRecoSubJetDRVsCentrality_I_CBin0);
   NormalizeHistogram(HRecoSubJetDRVsCentrality_I_CBin1);
   NormalizeHistogram(HRecoSubJetDRVsCentrality_I_CBin2);
   NormalizeHistogram(HRecoSubJetDRVsCentrality_I_CBin3);
   NormalizeHistogram(HRecoSubJetDRVsCentrality_I_CBin4);
   NormalizeHistogram(HRecoSubJetDRVsCentrality_II_CBin0);
   NormalizeHistogram(HRecoSubJetDRVsCentrality_II_CBin1);
   NormalizeHistogram(HRecoSubJetDRVsCentrality_II_CBin2);
   NormalizeHistogram(HRecoSubJetDRVsCentrality_II_CBin3);
   NormalizeHistogram(HRecoSubJetDRVsCentrality_II_CBin4);

   HRecoSubJetDRVsCentrality_I_CBin0->SetLineWidth(2);
   HRecoSubJetDRVsCentrality_I_CBin1->SetLineWidth(2);
   HRecoSubJetDRVsCentrality_I_CBin2->SetLineWidth(2);
   HRecoSubJetDRVsCentrality_I_CBin3->SetLineWidth(2);
   HRecoSubJetDRVsCentrality_I_CBin4->SetLineWidth(2);
   HRecoSubJetDRVsCentrality_II_CBin0->SetLineWidth(2);
   HRecoSubJetDRVsCentrality_II_CBin1->SetLineWidth(2);
   HRecoSubJetDRVsCentrality_II_CBin2->SetLineWidth(2);
   HRecoSubJetDRVsCentrality_II_CBin3->SetLineWidth(2);
   HRecoSubJetDRVsCentrality_II_CBin4->SetLineWidth(2);

   HRecoSubJetDRVsCentrality_I_CBin0->SetLineColor(kBlack);
   HRecoSubJetDRVsCentrality_I_CBin1->SetLineColor(kRed);
   HRecoSubJetDRVsCentrality_I_CBin2->SetLineColor(kBlue);
   HRecoSubJetDRVsCentrality_I_CBin3->SetLineColor(kCyan - 3);
   HRecoSubJetDRVsCentrality_I_CBin4->SetLineColor(kGreen - 3);
   HRecoSubJetDRVsCentrality_II_CBin0->SetLineColor(kBlack);
   HRecoSubJetDRVsCentrality_II_CBin1->SetLineColor(kRed);
   HRecoSubJetDRVsCentrality_II_CBin2->SetLineColor(kBlue);
   HRecoSubJetDRVsCentrality_II_CBin3->SetLineColor(kCyan - 3);
   HRecoSubJetDRVsCentrality_II_CBin4->SetLineColor(kGreen - 3);

   TH2D HWorldRecoSubJetDR("HWorldRecoSubJetDR", ";Reconstructed Sub-jet #DeltaR;a.u.",
      100, 0.1, 0.5, 100, 0, 10);
   HWorldRecoSubJetDR.SetStats(0);

   HWorldRecoSubJetDR.Draw();
   HRecoSubJetDRVsCentrality_I_CBin0->Draw("same");
   HRecoSubJetDRVsCentrality_I_CBin1->Draw("same");
   HRecoSubJetDRVsCentrality_I_CBin2->Draw("same");
   HRecoSubJetDRVsCentrality_I_CBin3->Draw("same");
   HRecoSubJetDRVsCentrality_I_CBin4->Draw("same");
   if(IsPP == false)
      RecoDRLegend.Draw();
   TagLatex.DrawLatex(0.10, 0.92, OutputBase.c_str());

   Canvas.SaveAs(Form("%s_HRecoSubJetDR_I.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_HRecoSubJetDR_I.C", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_HRecoSubJetDR_I.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_HRecoSubJetDR_I.pdf", OutputBase.c_str()));
   
   HWorldRecoSubJetDR.Draw();
   HRecoSubJetDRVsCentrality_II_CBin0->Draw("same");
   HRecoSubJetDRVsCentrality_II_CBin1->Draw("same");
   HRecoSubJetDRVsCentrality_II_CBin2->Draw("same");
   HRecoSubJetDRVsCentrality_II_CBin3->Draw("same");
   HRecoSubJetDRVsCentrality_II_CBin4->Draw("same");
   if(IsPP == false)
      RecoDRLegend.Draw();
   TagLatex.DrawLatex(0.10, 0.92, OutputBase.c_str());

   Canvas.SaveAs(Form("%s_HRecoSubJetDR_II.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_HRecoSubJetDR_II.C", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_HRecoSubJetDR_II.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_HRecoSubJetDR_II.pdf", OutputBase.c_str()));
   
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsRecoSubJetDR_I", "PSDMassRatioVsRecoSubJetDR_I",
      OutputBase + "_SDMassRatioVsRecoSubJetDR_I", OutputBase, "colz");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsRecoSubJetDR_II", "PSDMassRatioVsRecoSubJetDR_II",
      OutputBase + "_SDMassRatioVsRecoSubJetDR_II", OutputBase, "colz");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsRecoSubJetDR_II_CBin0", "PSDMassRatioVsRecoSubJetDR_II_CBin0",
      OutputBase + "_SDMassRatioVsRecoSubJetDR_II_CBin0", OutputBase, "colz");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsRecoSubJetDR_II_CBin1", "PSDMassRatioVsRecoSubJetDR_II_CBin1",
      OutputBase + "_SDMassRatioVsRecoSubJetDR_II_CBin1", OutputBase, "colz");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsRecoSubJetDR_II_CBin2", "PSDMassRatioVsRecoSubJetDR_II_CBin2",
      OutputBase + "_SDMassRatioVsRecoSubJetDR_II_CBin2", OutputBase, "colz");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsRecoSubJetDR_II_CBin3", "PSDMassRatioVsRecoSubJetDR_II_CBin3",
      OutputBase + "_SDMassRatioVsRecoSubJetDR_II_CBin3", OutputBase, "colz");
   ExportHistogram2DWithProfile(F, "HSDMassRatioVsRecoSubJetDR_II_CBin4", "PSDMassRatioVsRecoSubJetDR_II_CBin4",
      OutputBase + "_SDMassRatioVsRecoSubJetDR_II_CBin4", OutputBase, "colz");

   TH1D *HSDMassRatio_I = ((TH2D *)F.Get("HSDMassRatioVsRecoSubJetDR_I"))->ProjectionY("HSDMassRatio_I");
   TH1D *HSDMassRatio_I_CBin0
      = ((TH2D *)F.Get("HSDMassRatioVsRecoSubJetDR_I_CBin0"))->ProjectionY("HSDMassRatio_I_CBin0");
   TH1D *HSDMassRatio_I_CBin1
      = ((TH2D *)F.Get("HSDMassRatioVsRecoSubJetDR_I_CBin1"))->ProjectionY("HSDMassRatio_I_CBin1");
   TH1D *HSDMassRatio_I_CBin2
      = ((TH2D *)F.Get("HSDMassRatioVsRecoSubJetDR_I_CBin2"))->ProjectionY("HSDMassRatio_I_CBin2");
   TH1D *HSDMassRatio_I_CBin3
      = ((TH2D *)F.Get("HSDMassRatioVsRecoSubJetDR_I_CBin3"))->ProjectionY("HSDMassRatio_I_CBin3");
   TH1D *HSDMassRatio_I_CBin4
      = ((TH2D *)F.Get("HSDMassRatioVsRecoSubJetDR_I_CBin4"))->ProjectionY("HSDMassRatio_I_CBin4");
   TH1D *HSDMassRatio_II = ((TH2D *)F.Get("HSDMassRatioVsRecoSubJetDR_II"))->ProjectionY("HSDMassRatio_II");
   TH1D *HSDMassRatio_II_CBin0
      = ((TH2D *)F.Get("HSDMassRatioVsRecoSubJetDR_II_CBin0"))->ProjectionY("HSDMassRatio_II_CBin0");
   TH1D *HSDMassRatio_II_CBin1
      = ((TH2D *)F.Get("HSDMassRatioVsRecoSubJetDR_II_CBin1"))->ProjectionY("HSDMassRatio_II_CBin1");
   TH1D *HSDMassRatio_II_CBin2
      = ((TH2D *)F.Get("HSDMassRatioVsRecoSubJetDR_II_CBin2"))->ProjectionY("HSDMassRatio_II_CBin2");
   TH1D *HSDMassRatio_II_CBin3
      = ((TH2D *)F.Get("HSDMassRatioVsRecoSubJetDR_II_CBin3"))->ProjectionY("HSDMassRatio_II_CBin3");
   TH1D *HSDMassRatio_II_CBin4
      = ((TH2D *)F.Get("HSDMassRatioVsRecoSubJetDR_II_CBin4"))->ProjectionY("HSDMassRatio_II_CBin4");

   NormalizeHistogram(HSDMassRatio_I,       HSDMassRatio_II      );
   NormalizeHistogram(HSDMassRatio_I_CBin0, HSDMassRatio_II_CBin0);
   NormalizeHistogram(HSDMassRatio_I_CBin1, HSDMassRatio_II_CBin1);
   NormalizeHistogram(HSDMassRatio_I_CBin2, HSDMassRatio_II_CBin2);
   NormalizeHistogram(HSDMassRatio_I_CBin3, HSDMassRatio_II_CBin3);
   NormalizeHistogram(HSDMassRatio_I_CBin4, HSDMassRatio_II_CBin4);

   HSDMassRatio_I->SetLineWidth(2);
   HSDMassRatio_I_CBin0->SetLineWidth(2);
   HSDMassRatio_I_CBin1->SetLineWidth(2);
   HSDMassRatio_I_CBin2->SetLineWidth(2);
   HSDMassRatio_I_CBin3->SetLineWidth(2);
   HSDMassRatio_I_CBin4->SetLineWidth(2);
   HSDMassRatio_II->SetLineWidth(2);
   HSDMassRatio_II_CBin0->SetLineWidth(2);
   HSDMassRatio_II_CBin1->SetLineWidth(2);
   HSDMassRatio_II_CBin2->SetLineWidth(2);
   HSDMassRatio_II_CBin3->SetLineWidth(2);
   HSDMassRatio_II_CBin4->SetLineWidth(2);

   HSDMassRatio_I->SetLineColor(kBlack);
   HSDMassRatio_I_CBin0->SetLineColor(kBlack);
   HSDMassRatio_I_CBin1->SetLineColor(kBlack);
   HSDMassRatio_I_CBin2->SetLineColor(kBlack);
   HSDMassRatio_I_CBin3->SetLineColor(kBlack);
   HSDMassRatio_I_CBin4->SetLineColor(kBlack);
   HSDMassRatio_II->SetLineColor(kRed);
   HSDMassRatio_II_CBin0->SetLineColor(kRed);
   HSDMassRatio_II_CBin1->SetLineColor(kRed);
   HSDMassRatio_II_CBin2->SetLineColor(kRed);
   HSDMassRatio_II_CBin3->SetLineColor(kRed);
   HSDMassRatio_II_CBin4->SetLineColor(kRed);

   TH2D HSDMassRatioWorld("HSDMassRatioWorld", ";SD Mass Reco / Gen;a.u.", 100, 0, 4, 100, 0, 1.8);
   HSDMassRatioWorld.SetStats(0);

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   
   HSDMassRatioWorld.Draw();
   HSDMassRatio_I->Draw("same");
   HSDMassRatio_II->Draw("same");
   Latex.DrawLatex(1.5, 1.4, Form("#frac{Region II}{Region I + Region II} = %.2f",
      HSDMassRatio_II->Integral() / (HSDMassRatio_I->Integral() + HSDMassRatio_II->Integral())));
   Latex.DrawLatex(1.5, 1.1, Form("Region I RMS = %.2f", HSDMassRatio_I->GetRMS()));
   Latex.DrawLatex(1.5, 1.0, Form("Region II RMS = %.2f", HSDMassRatio_II->GetRMS()));
   TagLatex.DrawLatex(0.10, 0.92, OutputBase.c_str());
   
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II.C", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II.pdf", OutputBase.c_str()));

   HSDMassRatioWorld.SetTitle("0% - 10%");
   HSDMassRatioWorld.Draw();
   HSDMassRatio_I_CBin0->Draw("same");
   HSDMassRatio_II_CBin0->Draw("same");
   Latex.DrawLatex(1.5, 1.4, Form("#frac{Region II}{Region I + Region II} = %.2f",
      HSDMassRatio_II_CBin0->Integral() / (HSDMassRatio_I_CBin0->Integral() + HSDMassRatio_II_CBin0->Integral())));
   Latex.DrawLatex(1.5, 1.1, Form("Region I RMS = %.2f", HSDMassRatio_I_CBin0->GetRMS()));
   Latex.DrawLatex(1.5, 1.0, Form("Region II RMS = %.2f", HSDMassRatio_II_CBin0->GetRMS()));
   TagLatex.DrawLatex(0.10, 0.92, OutputBase.c_str());
   TagLatex.DrawLatex(0.10, 0.92, OutputBase.c_str());
   
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin0.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin0.C", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin0.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin0.pdf", OutputBase.c_str()));

   HSDMassRatioWorld.SetTitle("10% - 30%");
   HSDMassRatioWorld.Draw();
   HSDMassRatio_I_CBin1->Draw("same");
   HSDMassRatio_II_CBin1->Draw("same");
   Latex.DrawLatex(1.5, 1.4, Form("#frac{Region II}{Region I + Region II} = %.2f",
      HSDMassRatio_II_CBin1->Integral() / (HSDMassRatio_I_CBin1->Integral() + HSDMassRatio_II_CBin1->Integral())));
   Latex.DrawLatex(1.5, 1.1, Form("Region I RMS = %.2f", HSDMassRatio_I_CBin1->GetRMS()));
   Latex.DrawLatex(1.5, 1.0, Form("Region II RMS = %.2f", HSDMassRatio_II_CBin1->GetRMS()));
   TagLatex.DrawLatex(0.10, 0.92, OutputBase.c_str());
   
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin1.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin1.C", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin1.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin1.pdf", OutputBase.c_str()));

   HSDMassRatioWorld.SetTitle("30% - 50%");
   HSDMassRatioWorld.Draw();
   HSDMassRatio_I_CBin2->Draw("same");
   HSDMassRatio_II_CBin2->Draw("same");
   Latex.DrawLatex(1.5, 1.4, Form("#frac{Region II}{Region I + Region II} = %.2f",
      HSDMassRatio_II_CBin2->Integral() / (HSDMassRatio_I_CBin2->Integral() + HSDMassRatio_II_CBin2->Integral())));
   Latex.DrawLatex(1.5, 1.1, Form("Region I RMS = %.2f", HSDMassRatio_I_CBin2->GetRMS()));
   Latex.DrawLatex(1.5, 1.0, Form("Region II RMS = %.2f", HSDMassRatio_II_CBin2->GetRMS()));
   TagLatex.DrawLatex(0.10, 0.92, OutputBase.c_str());
   
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin2.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin2.C", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin2.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin2.pdf", OutputBase.c_str()));

   HSDMassRatioWorld.SetTitle("50% - 80%");
   HSDMassRatioWorld.Draw();
   HSDMassRatio_I_CBin3->Draw("same");
   HSDMassRatio_II_CBin3->Draw("same");
   Latex.DrawLatex(1.5, 1.4, Form("#frac{Region II}{Region I + Region II} = %.2f",
      HSDMassRatio_II_CBin3->Integral() / (HSDMassRatio_I_CBin3->Integral() + HSDMassRatio_II_CBin3->Integral())));
   Latex.DrawLatex(1.5, 1.1, Form("Region I RMS = %.2f", HSDMassRatio_I_CBin3->GetRMS()));
   Latex.DrawLatex(1.5, 1.0, Form("Region II RMS = %.2f", HSDMassRatio_II_CBin3->GetRMS()));
   TagLatex.DrawLatex(0.10, 0.92, OutputBase.c_str());
   
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin3.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin3.C", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin3.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin3.pdf", OutputBase.c_str()));

   HSDMassRatioWorld.SetTitle("80% - 100%");
   HSDMassRatioWorld.Draw();
   HSDMassRatio_I_CBin4->Draw("same");
   HSDMassRatio_II_CBin4->Draw("same");
   Latex.DrawLatex(1.5, 1.4, Form("#frac{Region II}{Region I + Region II} = %.2f",
      HSDMassRatio_II_CBin4->Integral() / (HSDMassRatio_I_CBin4->Integral() + HSDMassRatio_II_CBin4->Integral())));
   Latex.DrawLatex(1.5, 1.1, Form("Region I RMS = %.2f", HSDMassRatio_I_CBin4->GetRMS()));
   Latex.DrawLatex(1.5, 1.0, Form("Region II RMS = %.2f", HSDMassRatio_II_CBin4->GetRMS()));
   TagLatex.DrawLatex(0.10, 0.92, OutputBase.c_str());
   
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin4.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin4.C", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin4.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s_SDMassRatio_I_II_CBin4.pdf", OutputBase.c_str()));
   
   F.Close();

   return 0;
}

void NormalizeHistogram(TH1D *H)
{
   if(H == NULL)
      return;

   int N = H->GetNbinsX();
   double L = H->GetXaxis()->GetBinLowEdge(1);
   double R = H->GetXaxis()->GetBinUpEdge(N);
   double BinSize = (R - L) / N;
   H->Scale(1 / H->Integral() / BinSize);
}

void NormalizeHistogram(TH1D *H1, TH1D *H2)
{
   if(H1 == NULL || H2 == NULL)
      return;
   
   int N1 = H1->GetNbinsX();
   double L1 = H1->GetXaxis()->GetBinLowEdge(1);
   double R1 = H1->GetXaxis()->GetBinUpEdge(N1);
   double BinSize1 = (R1 - L1) / N1;
   
   int N2 = H2->GetNbinsX();
   double L2 = H2->GetXaxis()->GetBinLowEdge(1);
   double R2 = H2->GetXaxis()->GetBinUpEdge(N2);
   double BinSize2 = (R2 - L2) / N2;

   double Integral1 = H1->Integral() * BinSize1;
   double Integral2 = H2->Integral() * BinSize2;
   double Integral = Integral1 + Integral2;

   H1->Scale(1 / Integral);
   H2->Scale(1 / Integral);
}

void ExportHistogram2D(TFile &F, string Name, string OutputBase, string Tag, string PlotOption)
{
   TH2D *H = (TH2D *)F.Get(Name.c_str());
   if(H == NULL)
   {
      cerr << "Histogram " << Name << " not found!" << endl;
      return;
   }

   TCanvas C;

   H->SetStats(0);
   H->Draw(PlotOption.c_str());

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.02);
   Latex.DrawLatex(0.10, 0.92, Tag.c_str());

   C.SetLogz(true);

   C.SaveAs((OutputBase + ".png").c_str());
   C.SaveAs((OutputBase + ".C").c_str());
   C.SaveAs((OutputBase + ".eps").c_str());
   C.SaveAs((OutputBase + ".pdf").c_str());
}

void ExportProfile2D(TFile &F, string Name, string OutputBase, string Tag, string PlotOption)
{
   TProfile2D *H = (TProfile2D *)F.Get(Name.c_str());
   if(H == NULL)
   {
      cerr << "Profile " << Name << " not found!" << endl;
      return;
   }

   TCanvas C;

   H->SetStats(0);
   H->Draw(PlotOption.c_str());

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.02);
   Latex.DrawLatex(0.10, 0.92, Tag.c_str());

   C.SaveAs((OutputBase + ".png").c_str());
   C.SaveAs((OutputBase + ".C").c_str());
   C.SaveAs((OutputBase + ".eps").c_str());
   C.SaveAs((OutputBase + ".pdf").c_str());
}

void ExportHistogram2DWithProfile(TFile &F, string Name, string PName, string OutputBase, string Tag, string PlotOption, string POption)
{
   TH2D *H = (TH2D *)F.Get(Name.c_str());
   if(H == NULL)
   {
      cerr << "Histogram " << Name << " not found!" << endl;
      return;
   }

   TProfile *P = (TProfile *)F.Get(PName.c_str());
   if(P == NULL)
   {
      cerr << "Profile " << PName << " not found!" << endl;
      return;
   }

   P->SetMarkerStyle(11);
   P->SetLineWidth(2);
   P->Rebin(2);

   TCanvas C;
   
   C.SetLogz(true);

   P->SetErrorOption(POption.c_str());

   H->SetStats(0);
   H->Draw(PlotOption.c_str());
   P->Draw("same");

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.02);
   Latex.DrawLatex(0.10, 0.92, Tag.c_str());

   C.SaveAs((OutputBase + ".png").c_str());
   C.SaveAs((OutputBase + ".C").c_str());
   C.SaveAs((OutputBase + ".eps").c_str());
   C.SaveAs((OutputBase + ".pdf").c_str());
}


