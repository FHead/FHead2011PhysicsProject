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
   SetThesisRegularStyle();

   TFile FA1ZZ("gg_h_2e2mu_A1ZZ_LooseCuts.root");
   TFile FA2ZZ("gg_h_2e2mu_A2ZZ_LooseCuts.root");
   TFile FA2ZA("gg_h_2e2mu_A2ZA_LooseCuts.root");
   TFile FA2AA("gg_h_2e2mu_A2AA_LooseCuts.root");
   TTree *TA1ZZ = (TTree *)FA1ZZ.Get("Tree");
   TTree *TA2ZZ = (TTree *)FA2ZZ.Get("Tree");
   TTree *TA2ZA = (TTree *)FA2ZA.Get("Tree");
   TTree *TA2AA = (TTree *)FA2AA.Get("Tree");

   vector<TH1D *> A1ZZ = FillHistograms(TA1ZZ, "A1ZZ", "");
   vector<TH1D *> A2ZZ = FillHistograms(TA2ZZ, "A2ZZ", "");
   vector<TH1D *> A2ZA = FillHistograms(TA2ZA, "A2ZA", "");
   vector<TH1D *> A2AA = FillHistograms(TA2AA, "A2AA", "");

   double Max[] = {0.238, 0.158, 0.238, 0.74, 0.238, 0.84, 0.78, 1, 0.034};
   // double Max[] = {0.38, 0.14, 0.29, 1.24, 0.29, 0.74, 0.6, 0.034, 0.034};

   for(int i = 0; i < (int)A1ZZ.size(); i++)
   {
      TCanvas C("C", "C", 1024, 1024);

      A1ZZ[i]->Draw();
      A2ZZ[i]->Draw("same");
      A2ZA[i]->Draw("same");
      A2AA[i]->Draw("same");

      TLegend *Legend;

      if(i == 0)
      {
         Legend = new TLegend(0.2, 0.8, 0.6, 0.5);
         Legend->SetBorderSize(0);
         Legend->SetTextFont(42);
         Legend->SetFillStyle(0);
         Legend->SetTextSize(0.045);
         Legend->AddEntry(A1ZZ[i], "A_{1}^{ZZ}", "l");
         Legend->AddEntry(A2ZZ[i], "A_{2}^{ZZ}", "l");
         Legend->AddEntry(A2ZA[i], "A_{2}^{Z#gamma}", "l");
         Legend->AddEntry(A2AA[i], "A_{2}^{#gamma#gamma}", "l");
         Legend->Draw();
      }

      // C.SetLogy(true);

      // C.SaveAs(Form("LogMeow%d.png", i));
      // C.SaveAs(Form("LogMeow%d.C", i));
      // C.SaveAs(Form("LogMeow%d.eps", i));
      // C.SaveAs(Form("LogMeow%d.pdf", i));

      C.SetLogy(false);

      A1ZZ[i]->GetXaxis()->SetNdivisions(505);
      A1ZZ[i]->GetYaxis()->SetNdivisions(505);
      A1ZZ[i]->SetMinimum(0);
      A1ZZ[i]->SetMaximum(Max[i]);
      A1ZZ[i]->GetYaxis()->SetTitleOffset(1.6);

      C.SaveAs(Form("MultiDimensionalOverview-DifferentialCrossSection-Distribution%d.png", i + 1));
      C.SaveAs(Form("MultiDimensionalOverview-DifferentialCrossSection-Distribution%d.C", i + 1));
      C.SaveAs(Form("MultiDimensionalOverview-DifferentialCrossSection-Distribution%d.eps", i + 1));
      C.SaveAs(Form("MultiDimensionalOverview-DifferentialCrossSection-Distribution%d.pdf", i + 1));
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
   
   // TF1 Fit("Fit", "pol6", 100, 160);
   // HMH0->Fit(&Fit);
   // Cut = "(" + Cut + ") / "
   //    + Form("(%.20f+%.20f*MH+%.20f*MH*MH+%.20f*MH*MH*MH+%.20f*MH*MH*MH*MH+%.20f*MH*MH*MH*MH*MH+%.20f*MH*MH*MH*MH*MH*MH)",
   //       Fit.GetParameter(0), Fit.GetParameter(1), Fit.GetParameter(2), Fit.GetParameter(3),
   //       Fit.GetParameter(4), Fit.GetParameter(5), Fit.GetParameter(6));
   // cout << Cut << endl;

   TH1D *HM1        = new TH1D(Form("HM1_%s", Suffix.c_str()),        ";m_{1};a.u.", 100, 4, 110);
   TH1D *HM2        = new TH1D(Form("HM2_%s", Suffix.c_str()),        ";m_{2};a.u.", 100, 4, 65);
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



