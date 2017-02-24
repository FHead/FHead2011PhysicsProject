#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH2D.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TLegend.h"

#define BINCOUNT 16

int main();
void DoGraph(vector<TGraphAsymmErrors *> Gs, string OutputBase, double BinMin, double BinMax, bool IsMC, bool IsPT);
void PadSetting(TPad *Pad);
void GraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *G3, TGraphAsymmErrors *G4);
void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors &GRatio);
void RatioGraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2);

int main()
{
   string FileName;
   string OutputBase;
   bool IsMC;

   for(int iMC = 0; iMC < 2; iMC++)
   {
      if(iMC == 0)
      {
         FileName = "GraphsDataAdjusted15713.root";
         OutputBase = "DataClosure";
         IsMC = false;
      }
      else
      {
         FileName = "GraphsMCAdjusted15713.root";
         OutputBase = "MCClosure";
         IsMC = true;
      }

      TFile FGraphs(FileName.c_str());

      double PTBinEdge[] = {120, 140, 160, 180, 200, 300, 500};
      double CBinEdge[] = {0, 10, 30, 50, 80, 100};

      for(int i = 1; i < 6; i++)
      {
         vector<TGraphAsymmErrors *> Gs(16);
         Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_0_%d"    , i));
         Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DataSys_0_%d" , i));
         Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Smear_0_%d"   , i));
         Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("SmearSys_0_%d", i));
         Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_1_%d"    , i));
         Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DataSys_1_%d" , i));
         Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Smear_1_%d"   , i));
         Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("SmearSys_1_%d", i));
         Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_2_%d"    , i));
         Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DataSys_2_%d" , i));
         Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("Smear_2_%d"   , i));
         Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("SmearSys_2_%d", i));
         Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_3_%d"    , i));
         Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("DataSys_3_%d" , i));
         Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("Smear_3_%d"   , i));
         Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("SmearSys_3_%d", i));

         DoGraph(Gs, OutputBase + Form("_PrettyPlotPTBin%d", i), PTBinEdge[i], PTBinEdge[i+1], IsMC, true);
      }

      for(int i = 0; i < 4; i++)
      {
         vector<TGraphAsymmErrors *> Gs(16);
         Gs[0]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_%d_1"    , i));
         Gs[1]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DataSys_%d_1" , i));
         Gs[2]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Smear_%d_1"   , i));
         Gs[3]  = (TGraphAsymmErrors *)FGraphs.Get(Form("SmearSys_%d_1", i));
         Gs[4]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_%d_2"    , i));
         Gs[5]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DataSys_%d_2" , i));
         Gs[6]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Smear_%d_2"   , i));
         Gs[7]  = (TGraphAsymmErrors *)FGraphs.Get(Form("SmearSys_%d_2", i));
         Gs[8]  = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_%d_3"    , i));
         Gs[9]  = (TGraphAsymmErrors *)FGraphs.Get(Form("DataSys_%d_3" , i));
         Gs[10] = (TGraphAsymmErrors *)FGraphs.Get(Form("Smear_%d_3"   , i));
         Gs[11] = (TGraphAsymmErrors *)FGraphs.Get(Form("SmearSys_%d_3", i));
         Gs[12] = (TGraphAsymmErrors *)FGraphs.Get(Form("Data_%d_4"    , i));
         Gs[13] = (TGraphAsymmErrors *)FGraphs.Get(Form("DataSys_%d_4" , i));
         Gs[14] = (TGraphAsymmErrors *)FGraphs.Get(Form("Smear_%d_4"   , i));
         Gs[15] = (TGraphAsymmErrors *)FGraphs.Get(Form("SmearSys_%d_4", i));

         DoGraph(Gs, OutputBase + Form("_PrettyPlotCentralityBin%d", i), CBinEdge[i], CBinEdge[i+1], IsMC, false);
      }

      FGraphs.Close();
   }

   return 0;
}

void DoGraph(vector<TGraphAsymmErrors *> Gs, string OutputBase, double BinMin, double BinMax, bool IsMC, bool IsPT)
{
   if(Gs.size() != 16)
      return;

   TGraphAsymmErrors *G1Data     = Gs[0];
   TGraphAsymmErrors *G1DataSys  = Gs[1];
   TGraphAsymmErrors *G1Smear    = Gs[2];
   TGraphAsymmErrors *G1SmearSys = Gs[3];
   TGraphAsymmErrors *G2Data     = Gs[4];
   TGraphAsymmErrors *G2DataSys  = Gs[5];
   TGraphAsymmErrors *G2Smear    = Gs[6];
   TGraphAsymmErrors *G2SmearSys = Gs[7];
   TGraphAsymmErrors *G3Data     = Gs[8];
   TGraphAsymmErrors *G3DataSys  = Gs[9];
   TGraphAsymmErrors *G3Smear    = Gs[10];
   TGraphAsymmErrors *G3SmearSys = Gs[11];
   TGraphAsymmErrors *G4Data     = Gs[12];
   TGraphAsymmErrors *G4DataSys  = Gs[13];
   TGraphAsymmErrors *G4Smear    = Gs[14];
   TGraphAsymmErrors *G4SmearSys = Gs[15];

   GraphSetting(G1Data, G1DataSys, G1Smear, G1SmearSys);
   GraphSetting(G2Data, G2DataSys, G2Smear, G2SmearSys);
   GraphSetting(G3Data, G3DataSys, G3Smear, G3SmearSys);
   GraphSetting(G4Data, G4DataSys, G4Smear, G4SmearSys);

   TGraphAsymmErrors G1Ratio, G1RatioSys;
   TGraphAsymmErrors G2Ratio, G2RatioSys;
   TGraphAsymmErrors G3Ratio, G3RatioSys;
   TGraphAsymmErrors G4Ratio, G4RatioSys;

   Division(G1Data, G1Smear, G1Ratio);
   Division(G1DataSys, G1SmearSys, G1RatioSys);
   Division(G2Data, G2Smear, G2Ratio);
   Division(G2DataSys, G2SmearSys, G2RatioSys);
   Division(G3Data, G3Smear, G3Ratio);
   Division(G3DataSys, G3SmearSys, G3RatioSys);
   Division(G4Data, G4Smear, G4Ratio);
   Division(G4DataSys, G4SmearSys, G4RatioSys);

   RatioGraphSetting(&G1Ratio, &G1RatioSys);
   RatioGraphSetting(&G2Ratio, &G2RatioSys);
   RatioGraphSetting(&G3Ratio, &G3RatioSys);
   RatioGraphSetting(&G4Ratio, &G4RatioSys);

   double Border = 350;
   double PadWidth = 1000;
   double PadHeight = 1000;
   double RatioHeight = 500;

   double TotalHeight = RatioHeight + PadHeight + Border * 2;
   double TotalWidth = PadWidth * 4 + Border * 2;

   double PadLowY  = (Border + RatioHeight) / TotalHeight;
   double PadHighY = (Border + RatioHeight + PadHeight) / TotalHeight;
   double PadRatioLowY  = Border / TotalHeight;

   double WorldMin = 0.011;
   double WorldMax = 500;
   double MassMin = 0;
   double MassMax = 0.26;
   double RatioMin = 0;
   double RatioMax = 3;

   TGraph GLine;
   GLine.SetPoint(0, MassMin, 1);
   GLine.SetPoint(1, MassMax, 1);

   gStyle->SetPaperSize(TotalWidth / 170, TotalHeight / 170);

   TCanvas Canvas("Canvas", "", TotalWidth, TotalHeight);

   TPad *Pad1 = new TPad("Pad1", "", (Border + PadWidth * 0) / TotalWidth, PadLowY, (Border + PadWidth * 1) / TotalWidth, PadHighY);
   TPad *Pad2 = new TPad("Pad2", "", (Border + PadWidth * 1) / TotalWidth, PadLowY, (Border + PadWidth * 2) / TotalWidth, PadHighY);
   TPad *Pad3 = new TPad("Pad3", "", (Border + PadWidth * 2) / TotalWidth, PadLowY, (Border + PadWidth * 3) / TotalWidth, PadHighY);
   TPad *Pad4 = new TPad("Pad4", "", (Border + PadWidth * 3) / TotalWidth, PadLowY, (Border + PadWidth * 4) / TotalWidth, PadHighY);

   TPad *Pad5 = new TPad("Pad5", "", (Border + PadWidth * 0) / TotalWidth, PadRatioLowY, (Border + PadWidth * 1) / TotalWidth, PadLowY);
   TPad *Pad6 = new TPad("Pad6", "", (Border + PadWidth * 1) / TotalWidth, PadRatioLowY, (Border + PadWidth * 2) / TotalWidth, PadLowY);
   TPad *Pad7 = new TPad("Pad7", "", (Border + PadWidth * 2) / TotalWidth, PadRatioLowY, (Border + PadWidth * 3) / TotalWidth, PadLowY);
   TPad *Pad8 = new TPad("Pad8", "", (Border + PadWidth * 3) / TotalWidth, PadRatioLowY, (Border + PadWidth * 4) / TotalWidth, PadLowY);

   PadSetting(Pad1);
   PadSetting(Pad2);
   PadSetting(Pad3);
   PadSetting(Pad4);

   PadSetting(Pad5);
   PadSetting(Pad6);
   PadSetting(Pad7);
   PadSetting(Pad8);

   TH2D HWorld("HWorld", ";;", 100, MassMin, MassMax, 100, WorldMin, WorldMax);
   HWorld.SetStats(0);
   HWorld.GetXaxis()->SetLabelSize(0);
   HWorld.GetYaxis()->SetLabelSize(0);

   TH2D HWorldRatio("HWorldRatio", ";;", 100, MassMin, MassMax, 100, RatioMin, RatioMax);
   HWorldRatio.SetStats(0);
   HWorldRatio.GetXaxis()->SetLabelSize(0);
   HWorldRatio.GetYaxis()->SetLabelSize(0);
   HWorldRatio.GetXaxis()->SetTickLength(0.06);
   HWorldRatio.GetYaxis()->SetTickLength(0.03);
   HWorldRatio.GetYaxis()->SetNdivisions(505);

   TGraph GData, GSmear;
   GData.SetLineColor(G1Data->GetLineColor());
   GData.SetFillColor(G1DataSys->GetFillColor());
   GSmear.SetLineColor(G1Smear->GetLineColor());
   GSmear.SetFillColor(G1SmearSys->GetFillColor());

   Pad1->cd();
   HWorld.Draw("");
   G1SmearSys->Draw("2");
   G1DataSys->Draw("2");
   G1Smear->Draw("p");
   G1Data->Draw("p");
   HWorld.Draw("axis same");
   Pad1->SetLogy();
   Pad1->Update();

   Pad2->cd();
   HWorld.Draw("");
   G2SmearSys->Draw("2");
   G2DataSys->Draw("2");
   G2Smear->Draw("p");
   G2Data->Draw("p");
   HWorld.Draw("axis same");
   Pad2->SetLogy();
   Pad2->Update();

   Pad3->cd();
   HWorld.Draw("");
   G3SmearSys->Draw("2");
   G3DataSys->Draw("2");
   G3Smear->Draw("p");
   G3Data->Draw("p");
   HWorld.Draw("axis same");
   Pad3->SetLogy();
   Pad3->Update();

   Pad4->cd();
   HWorld.Draw("");
   G4SmearSys->Draw("2");
   G4DataSys->Draw("2");
   G4Smear->Draw("p");
   G4Data->Draw("p");
   HWorld.Draw("axis same");
   Pad4->SetLogy();
   Pad4->Update();

   Pad5->cd();
   HWorldRatio.Draw("");
   G1RatioSys.Draw("2");
   G1Ratio.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad5->SetLogy();
   Pad5->Update();

   Pad6->cd();
   HWorldRatio.Draw("");
   G2RatioSys.Draw("2");
   G2Ratio.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad6->SetLogy();
   Pad6->Update();

   Pad7->cd();
   HWorldRatio.Draw("");
   G3RatioSys.Draw("2");
   G3Ratio.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad7->SetLogy();
   Pad7->Update();

   Pad8->cd();
   HWorldRatio.Draw("");
   G4RatioSys.Draw("2");
   G4Ratio.Draw("p");
   GLine.Draw("l");
   HWorldRatio.Draw("axis same");
   // Pad8->SetLogy();
   Pad8->Update();

   Canvas.cd();

   TGaxis LeftAxis1(Border / TotalWidth, (Border + RatioHeight) / TotalHeight, Border / TotalWidth, (Border + RatioHeight + PadHeight) / TotalHeight,
         WorldMin, WorldMax, 50510, "G");
   LeftAxis1.SetName("LeftAxis1");
   LeftAxis1.SetLineWidth(0);
   LeftAxis1.SetTitle("#frac{1}{N} #frac{dN}{d(SD Mass/PT)}");
   LeftAxis1.SetTextFont(42);
   LeftAxis1.SetLabelFont(42);
   LeftAxis1.CenterTitle(true);
   LeftAxis1.SetTitleOffset(0.85);
   LeftAxis1.Draw();

   TGaxis LeftAxis2(Border / TotalWidth, Border / TotalHeight, Border / TotalWidth, (Border + RatioHeight) / TotalHeight,
         RatioMin, RatioMax, 1005, "");
   LeftAxis2.SetName("LeftAxis2");
   LeftAxis2.SetLineWidth(0);
   LeftAxis2.SetTitle("#frac{PbPb}{smeared pp}");
   LeftAxis2.SetTextFont(42);
   LeftAxis2.SetLabelFont(42);
   LeftAxis2.CenterTitle(true);
   LeftAxis2.SetTitleOffset(0.85);
   LeftAxis2.Draw();

   TGaxis BottomAxis1((Border + PadWidth * 0) / TotalWidth, Border / TotalHeight, (Border + PadWidth * 1) / TotalWidth, Border / TotalHeight,
         MassMin, MassMax - 0.00001, 1005, "");
   BottomAxis1.SetName("BottomAxis1");
   BottomAxis1.SetLineWidth(0);
   BottomAxis1.SetTitle("SD Mass / Jet PT");
   BottomAxis1.SetTextFont(42);
   BottomAxis1.SetLabelFont(42);
   BottomAxis1.CenterTitle(true);
   BottomAxis1.Draw();

   TGaxis BottomAxis2((Border + PadWidth * 1) / TotalWidth, Border / TotalHeight, (Border + PadWidth * 2) / TotalWidth, Border / TotalHeight,
         MassMin, MassMax - 0.00001, 1005, "");
   BottomAxis2.SetName("BottomAxis2");
   BottomAxis2.SetLineWidth(0);
   BottomAxis2.SetTitle("SD Mass / Jet PT");
   BottomAxis2.SetTextFont(42);
   BottomAxis2.SetLabelFont(42);
   BottomAxis2.CenterTitle(true);
   BottomAxis2.Draw();

   TGaxis BottomAxis3((Border + PadWidth * 2) / TotalWidth, Border / TotalHeight, (Border + PadWidth * 3) / TotalWidth, Border / TotalHeight,
         MassMin, MassMax - 0.00001, 1005, "");
   BottomAxis3.SetName("BottomAxis3");
   BottomAxis3.SetLineWidth(0);
   BottomAxis3.SetTitle("SD Mass / Jet PT");
   BottomAxis3.SetTextFont(42);
   BottomAxis3.SetLabelFont(42);
   BottomAxis3.CenterTitle(true);
   BottomAxis3.Draw();

   TGaxis BottomAxis4((Border + PadWidth * 3) / TotalWidth, Border / TotalHeight, (Border + PadWidth * 4) / TotalWidth, Border / TotalHeight,
         MassMin, MassMax, 1005, "");
   BottomAxis4.SetName("BottomAxis4");
   BottomAxis4.SetLineWidth(0);
   BottomAxis4.SetTitle("SD Mass / Jet PT");
   BottomAxis4.SetTextFont(42);
   BottomAxis4.SetLabelFont(42);
   BottomAxis4.CenterTitle(true);
   BottomAxis4.Draw();

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);

   Latex.SetTextAlign(10);
   Latex.DrawLatex(Border / TotalWidth, (Border + RatioHeight + PadHeight) / TotalHeight, "CMS Preliminary");

   Latex.SetTextAlign(30);
   if(IsMC == false)
      Latex.DrawLatex((Border + PadWidth * 4) / TotalWidth, (Border + RatioHeight + PadHeight) / TotalHeight, "#sqrt{s_{NN}} = 5.02 TeV, PbPb 404 #mub^{-1}, pp < 28 pb^{-1}");
   else
      Latex.DrawLatex((Border + PadWidth * 4) / TotalWidth, (Border + RatioHeight + PadHeight) / TotalHeight, "#sqrt{s_{NN}} = 5.02 TeV, Simulation");

   TLegend Legend((Border + PadWidth * 0.35) / TotalWidth, (Border + RatioHeight + PadHeight * 0.85) / TotalHeight, (Border + PadWidth * 0.8) / TotalWidth, (Border + RatioHeight + 0.65 * PadHeight) / TotalHeight);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&GData, "PbPb", "lf");
   Legend.AddEntry(&GSmear, "Smeared pp", "lf");
   Legend.Draw();

   Latex.SetTextAlign(33);
   if(IsPT == true)
   {
      Latex.DrawLatex((Border + PadWidth * 0.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "Centrality: 0-10%");
      Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "Centrality: 10-30%");
      Latex.DrawLatex((Border + PadWidth * 2.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "Centrality: 30-50%");
      Latex.DrawLatex((Border + PadWidth * 3.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "Centrality: 50-80%");
   }
   else
   {
      Latex.DrawLatex((Border + PadWidth * 0.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "140 < p_{T,jet} < 160 GeV");
      Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "160 < p_{T,jet} < 180 GeV");
      Latex.DrawLatex((Border + PadWidth * 2.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "180 < p_{T,jet} < 200 GeV");
      Latex.DrawLatex((Border + PadWidth * 3.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.95) / TotalHeight, "200 < p_{T,jet} < 300 GeV");
   }

   if(IsPT == true)
   {
      Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.85) / TotalHeight, Form("%.0f < p_{T,jet} < %.0f GeV", BinMin, BinMax));
      Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.75) / TotalHeight, "|#eta| < 1.3");
   }
   else
   {
      Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.85) / TotalHeight, "|#eta| < 1.3");
      Latex.DrawLatex((Border + PadWidth * 1.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.75) / TotalHeight, Form("Centrality: %.0f-%.0f%%", BinMin, BinMax));
   }


   Latex.DrawLatex((Border + PadWidth * 3.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.85) / TotalHeight, "anti-kt R = 0.4");
   Latex.DrawLatex((Border + PadWidth * 3.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.75) / TotalHeight, "#Delta R_{1,2} > 0.1");

   Latex.DrawLatex((Border + PadWidth * 2.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.85) / TotalHeight, "Soft drop");
   Latex.DrawLatex((Border + PadWidth * 2.95) / TotalWidth, (Border + RatioHeight + PadHeight * 0.75) / TotalHeight, "z_{cut} = 0.5, #beta = 1.5");

   Canvas.SaveAs(Form("%s.png", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.C"  , OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.eps", OutputBase.c_str()));
   Canvas.SaveAs(Form("%s.pdf", OutputBase.c_str()));
}

void PadSetting(TPad *Pad)
{
   Pad->SetTopMargin(0);
   Pad->SetRightMargin(0);
   Pad->SetBottomMargin(0);
   Pad->SetLeftMargin(0);

   Pad->Draw();
}

void GraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors *G3, TGraphAsymmErrors *G4)
{
   G1->SetLineColor(kRed);
   G1->SetMarkerColor(kRed);

   G2->SetLineWidth(0);
   G2->SetFillStyle(3454);
   G2->SetFillColor(kMagenta - 9);

   G3->SetLineColor(kBlue);
   G3->SetMarkerColor(kBlue);
   G3->SetLineWidth(1);

   G4->SetLineWidth(0);
   G4->SetFillColor(kCyan - 9);
}

void Division(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2, TGraphAsymmErrors &GRatio)
{
   for(int i = 0; i < BINCOUNT; i++)
   {
      double x1, x2, y1, y2;
      G1->GetPoint(i, x1, y1);
      G2->GetPoint(i, x2, y2);

      double xl1, xh1, xl2, xh2;
      xl1 = G1->GetErrorXlow(i);
      xh1 = G1->GetErrorXhigh(i);
      xl2 = G2->GetErrorXlow(i);
      xh2 = G2->GetErrorXhigh(i);

      double yl1, yh1, yl2, yh2;
      yl1 = G1->GetErrorYlow(i);
      yh1 = G1->GetErrorYhigh(i);
      yl2 = G2->GetErrorYlow(i);
      yh2 = G2->GetErrorYhigh(i);

      double ratio = (y1 / y2);

      double yl = ratio * sqrt((yl1 / y1) * (yl1 / y1) + (yl2 / y2) * (yl2 / y2));
      double yh = ratio * sqrt((yh1 / y1) * (yh1 / y1) + (yh2 / y2) * (yh2 / y2));

      if(x1 == x1 && x2 == x2 && ratio == ratio)
      {
         GRatio.SetPoint(i, x1, ratio);
         GRatio.SetPointError(i, xl1, xh1, yl, yh);
      }
      else
      {
         GRatio.SetPoint(i, -100, -100);
         GRatio.SetPointError(i, 0, 0, 0, 0);
      }
   }

   // GRatio.Print();
}

void RatioGraphSetting(TGraphAsymmErrors *G1, TGraphAsymmErrors *G2)
{
   G1->SetLineColor(kBlack);
   G1->SetMarkerColor(kBlack);

   G2->SetLineWidth(0);
   G2->SetFillColor(kBlue - 9);
}


