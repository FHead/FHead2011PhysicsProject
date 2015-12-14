#include <iostream>
#include <vector>
using namespace std;

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TF1.h"

#include "SetStyle.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main();
vector<TH1D *> FillHistograms(TTree *Tree, string Suffix, string Cut);
void SortHistogram(TH1D *H, int Color);

int main()
{
   SetStyle();

   TFile File("Tree.root");
   TTree *Tree = (TTree *)File.Get("Tree");

   vector<TH1D *> Central = FillHistograms(Tree, "Y1", "(MH > 100 && MH < 160 && (YH > -0.8 && YH < 0.8))");
   vector<TH1D *> Forward = FillHistograms(Tree, "Y2", "(MH > 100 && MH < 160 && (YH > 0.8 || YH < -0.8))");
   vector<TH1D *> Slow   = FillHistograms(Tree, "PT1", "(MH > 100 && MH < 160 && (PTH < 30))");
   vector<TH1D *> Medium = FillHistograms(Tree, "PT2", "(MH > 100 && MH < 160 && (PTH > 30 && PTH < 50))");
   vector<TH1D *> Fast   = FillHistograms(Tree, "PT3", "(MH > 100 && MH < 160 && (PTH > 50))");

   double Max[] = {0.238, 0.058, 0.29, 0.74, 0.29, 0.74, 1.557, 0.034, 0.034};
   // double Max[] = {0.38, 0.14, 0.29, 1.24, 0.29, 0.74, 0.6, 0.034, 0.034};

   for(int i = 0; i < (int)Central.size(); i++)
   {
      TCanvas C("C", "C", 1024, 1024);

      Central[i]->Draw();
      Forward[i]->Draw("same");
      Slow[i]->Draw("same");
      Medium[i]->Draw("same");
      Fast[i]->Draw("same");

      TLegend *Legend;

      if(i == 0)
      {
         Legend = new TLegend(0.2, 0.8, 0.5, 0.5);
         Legend->SetBorderSize(0);
         Legend->SetTextFont(42);
         Legend->SetFillStyle(0);
         Legend->AddEntry(Central[i], "|y_{4l}| < 0.8", "l");
         Legend->AddEntry(Forward[i], "|y_{4l}| > 0.8", "l");
         Legend->AddEntry(Slow[i],    "|p_{T, 4l}| < 30", "l");
         Legend->AddEntry(Medium[i],  "30 < |p_{T, 4l}| < 50", "l");
         Legend->AddEntry(Fast[i],    "|p_{T, 4l}| > 50", "l");
         Legend->Draw();
      }

      C.SetLogy(true);

      C.SaveAs(Form("LogFacotrizationCheck%d.png", i));
      C.SaveAs(Form("LogFacotrizationCheck%d.C", i));
      C.SaveAs(Form("LogFacotrizationCheck%d.eps", i));
      C.SaveAs(Form("LogFacotrizationCheck%d.pdf", i));

      C.SetLogy(false);

      Central[i]->SetMinimum(0);
      Central[i]->SetMaximum(Max[i]);

      C.SaveAs(Form("MultiDimensionalOverview-Production-SpectrumFactorization%d.png", i + 1));
      C.SaveAs(Form("MultiDimensionalOverview-Production-SpectrumFactorization%d.C", i + 1));
      C.SaveAs(Form("MultiDimensionalOverview-Production-SpectrumFactorization%d.eps", i + 1));
      C.SaveAs(Form("MultiDimensionalOverview-Production-SpectrumFactorization%d.pdf", i + 1));
   }

   return 0;
}

vector<TH1D *> FillHistograms(TTree *Tree, string Suffix, string Cut)
{
   static int Color = 0;
   Color = Color + 1;

   TH1D *HMH0       = new TH1D(Form("HMH0_%s", Suffix.c_str()),       ";m_{4l};a.u.", 50, 100, 160);
   Tree->Draw(Form("MH>>HMH0_%s", Suffix.c_str()), Cut.c_str(), "");
   SortHistogram(HMH0, Color);
   
   TF1 Fit("Fit", "pol6", 100, 160);
   HMH0->Fit(&Fit);
   Cut = "(" + Cut + ") / "
      + Form("(%.20f+%.20f*MH+%.20f*MH*MH+%.20f*MH*MH*MH+%.20f*MH*MH*MH*MH+%.20f*MH*MH*MH*MH*MH+%.20f*MH*MH*MH*MH*MH*MH)",
         Fit.GetParameter(0), Fit.GetParameter(1), Fit.GetParameter(2), Fit.GetParameter(3),
         Fit.GetParameter(4), Fit.GetParameter(5), Fit.GetParameter(6));
   cout << Cut << endl;

   TH1D *HM1        = new TH1D(Form("HM1_%s", Suffix.c_str()),        ";m_{1};a.u.", 100, 4, 120);
   TH1D *HM2        = new TH1D(Form("HM2_%s", Suffix.c_str()),        ";m_{2};a.u.", 100, 4, 120);
   TH1D *HPhi0      = new TH1D(Form("HPhi0_%s", Suffix.c_str()),      ";#Phi_{1};a.u.", 40, 0, 2 * PI);
   TH1D *HCosTheta0 = new TH1D(Form("HCosTheta0_%s", Suffix.c_str()), ";cos#Theta;a.u.", 40, -1, 1);
   TH1D *HPhi       = new TH1D(Form("HPhi_%s", Suffix.c_str()),       ";#phi;a.u.", 40, 0, 2 * PI);
   TH1D *HCosTheta1 = new TH1D(Form("HCosTheta1_%s", Suffix.c_str()), ";cos#theta_{1};a.u.", 40, -1, 1);
   TH1D *HCosTheta2 = new TH1D(Form("HCosTheta2_%s", Suffix.c_str()), ";cos#theta_{2};a.u.", 40, -1, 1);
   TH1D *HMH        = new TH1D(Form("HMH_%s", Suffix.c_str()),        ";m_{4l};a.u.", 40, 100, 160);

   Tree->Draw(Form("M1>>HM1_%s", Suffix.c_str()), Cut.c_str(), "");
   Tree->Draw(Form("M2>>HM2_%s", Suffix.c_str()), Cut.c_str(), "");
   Tree->Draw(Form("Phi0>>HPhi0_%s", Suffix.c_str()), Cut.c_str(), "");
   Tree->Draw(Form("cos(Theta0)>>HCosTheta0_%s", Suffix.c_str()), Cut.c_str(), "");
   Tree->Draw(Form("Phi>>HPhi_%s", Suffix.c_str()), Cut.c_str(), "");
   Tree->Draw(Form("cos(Theta1)>>HCosTheta1_%s", Suffix.c_str()), Cut.c_str(), "");
   Tree->Draw(Form("cos(Theta2)>>HCosTheta2_%s", Suffix.c_str()), Cut.c_str(), "");
   Tree->Draw(Form("MH>>HMH_%s", Suffix.c_str()), Cut.c_str(), "");

   SortHistogram(HM1, Color);
   SortHistogram(HM2, Color);
   SortHistogram(HPhi0, Color);
   SortHistogram(HCosTheta0, Color);
   SortHistogram(HPhi, Color);
   SortHistogram(HCosTheta1, Color);
   SortHistogram(HCosTheta2, Color);
   SortHistogram(HMH, Color);

   vector<TH1D *> Result;
   Result.push_back(HM1);
   Result.push_back(HM2);
   Result.push_back(HPhi0);
   Result.push_back(HCosTheta0);
   Result.push_back(HPhi);
   Result.push_back(HCosTheta1);
   Result.push_back(HCosTheta2);
   Result.push_back(HMH);
   Result.push_back(HMH0);

   return Result;
}

void SortHistogram(TH1D *H, int Color)
{
   if(H == NULL)
      return;

   int LineColor;
   switch(Color)
   {
      case 1:   LineColor = kBlack;        break;
      case 2:   LineColor = kRed;          break;
      case 3:   LineColor = kBlue;         break;
      case 4:   LineColor = kGreen - 3;    break;
      case 5:   LineColor = kYellow + 3;   break;
      default:  LineColor = kBlack;        break;
   }

   H->SetStats(0);
   H->GetXaxis()->SetTitleOffset(1.1);
   H->GetYaxis()->SetTitleOffset(1.2);

   H->SetLineWidth(2);
   H->SetLineColor(LineColor);
   
   double Left = H->GetXaxis()->GetBinLowEdge(1);
   double Right = H->GetXaxis()->GetBinUpEdge(H->GetNbinsX());
   H->Scale(H->GetNbinsX() / H->Integral() / (Right - Left));
}



