#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TCanvas.h"
#include "TGraph.h"

#include "SetStyle.h"

int main(int argc, char *argv[]);
void SavePlot1D(TProfile *H, string Base);
void SavePlot2D(TProfile2D *H, string Base);

int main(int argc, char *argv[])
{
   SetStyle();

   string FileName = "Result_gg_h_2e2mu_A1ZZ_LooseCuts.root";
   string Tag = "Result_gg_h_2e2mu_A1ZZ_LooseCuts";

   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " FileName Tag" << endl;
      return -1;
   }

   FileName = argv[1];
   Tag = argv[2];

   TFile File(FileName.c_str());
   TTree *T = (TTree *)File.Get("CutTree");

   TProfile *HM1APassA = new TProfile("HM1APassA", ";m_{1}^{(A)};Efficiency", 50, 0, 125);
   TProfile *HM1APassB = new TProfile("HM1APassB", ";m_{1}^{(A)};Efficiency", 50, 0, 125);
   TProfile *HM1APassC = new TProfile("HM1APassC", ";m_{1}^{(A)};Efficiency", 50, 0, 125);
   TProfile *HM2APassA = new TProfile("HM2APassA", ";m_{2}^{(A)};Efficiency", 50, 0,  62.5);
   TProfile *HM2APassB = new TProfile("HM2APassB", ";m_{2}^{(A)};Efficiency", 50, 0,  62.5);
   TProfile *HM2APassC = new TProfile("HM2APassC", ";m_{2}^{(A)};Efficiency", 50, 0,  62.5);
   TProfile *HM1BPassA = new TProfile("HM1BPassA", ";m_{1}^{(B)};Efficiency", 50, 0, 125);
   TProfile *HM1BPassB = new TProfile("HM1BPassB", ";m_{1}^{(B)};Efficiency", 50, 0, 125);
   TProfile *HM1BPassC = new TProfile("HM1BPassC", ";m_{1}^{(B)};Efficiency", 50, 0, 125);
   TProfile *HM2BPassA = new TProfile("HM2BPassA", ";m_{2}^{(B)};Efficiency", 50, 0,  62.5);
   TProfile *HM2BPassB = new TProfile("HM2BPassB", ";m_{2}^{(B)};Efficiency", 50, 0,  62.5);
   TProfile *HM2BPassC = new TProfile("HM2BPassC", ";m_{2}^{(B)};Efficiency", 50, 0,  62.5);
   TProfile *HM1CPassA = new TProfile("HM1CPassA", ";m_{1}^{(C)};Efficiency", 50, 0, 125);
   TProfile *HM1CPassB = new TProfile("HM1CPassB", ";m_{1}^{(C)};Efficiency", 50, 0, 125);
   TProfile *HM1CPassC = new TProfile("HM1CPassC", ";m_{1}^{(C)};Efficiency", 50, 0, 125);
   TProfile *HM2CPassA = new TProfile("HM2CPassA", ";m_{2}^{(C)};Efficiency", 50, 0,  62.5);
   TProfile *HM2CPassB = new TProfile("HM2CPassB", ";m_{2}^{(C)};Efficiency", 50, 0,  62.5);
   TProfile *HM2CPassC = new TProfile("HM2CPassC", ";m_{2}^{(C)};Efficiency", 50, 0,  62.5);
   
   TProfile2D *HM1M2APassA = new TProfile2D("HM1M2APassA", ";m_{1}^{(A)};m_{2}^{(A)};Efficiency", 30, 0, 125, 30, 0, 62.5);
   TProfile2D *HM1M2APassB = new TProfile2D("HM1M2APassB", ";m_{1}^{(A)};m_{2}^{(A)};Efficiency", 30, 0, 125, 30, 0, 62.5);
   TProfile2D *HM1M2APassC = new TProfile2D("HM1M2APassC", ";m_{1}^{(A)};m_{2}^{(A)};Efficiency", 30, 0, 125, 30, 0, 62.5);
   TProfile2D *HM1M2BPassA = new TProfile2D("HM1M2BPassA", ";m_{1}^{(B)};m_{2}^{(B)};Efficiency", 30, 0, 125, 30, 0, 62.5);
   TProfile2D *HM1M2BPassB = new TProfile2D("HM1M2BPassB", ";m_{1}^{(B)};m_{2}^{(B)};Efficiency", 30, 0, 125, 30, 0, 62.5);
   TProfile2D *HM1M2BPassC = new TProfile2D("HM1M2BPassC", ";m_{1}^{(B)};m_{2}^{(B)};Efficiency", 30, 0, 125, 30, 0, 62.5);
   TProfile2D *HM1M2CPassA = new TProfile2D("HM1M2CPassA", ";m_{1}^{(C)};m_{2}^{(C)};Efficiency", 30, 0, 125, 30, 0, 62.5);
   TProfile2D *HM1M2CPassB = new TProfile2D("HM1M2CPassB", ";m_{1}^{(C)};m_{2}^{(C)};Efficiency", 30, 0, 125, 30, 0, 62.5);
   TProfile2D *HM1M2CPassC = new TProfile2D("HM1M2CPassC", ";m_{1}^{(C)};m_{2}^{(C)};Efficiency", 30, 0, 125, 30, 0, 62.5);

   T->Draw("StandardMass:max(M1CMS,M2CMS)>>HM1APassA",           "BaselineCut", "prof");
   T->Draw("OppositeMass:max(M1CMS,M2CMS)>>HM1APassB",           "BaselineCut", "prof");
   T->Draw("SameMass:max(M1CMS,M2CMS)>>HM1APassC",               "BaselineCut", "prof");
   T->Draw("StandardMass:min(M1CMS,M2CMS)>>HM2APassA",           "BaselineCut", "prof");
   T->Draw("OppositeMass:min(M1CMS,M2CMS)>>HM2APassB",           "BaselineCut", "prof");
   T->Draw("SameMass:min(M1CMS,M2CMS)>>HM2APassC",               "BaselineCut", "prof");
   T->Draw("StandardMass:max(M1Opposite,M2Opposite)>>HM1BPassA", "BaselineCut", "prof");
   T->Draw("OppositeMass:max(M1Opposite,M2Opposite)>>HM1BPassB", "BaselineCut", "prof");
   T->Draw("SameMass:max(M1Opposite,M2Opposite)>>HM1BPassC",     "BaselineCut", "prof");
   T->Draw("StandardMass:min(M1Opposite,M2Opposite)>>HM2BPassA", "BaselineCut", "prof");
   T->Draw("OppositeMass:min(M1Opposite,M2Opposite)>>HM2BPassB", "BaselineCut", "prof");
   T->Draw("SameMass:min(M1Opposite,M2Opposite)>>HM2BPassC",     "BaselineCut", "prof");
   T->Draw("StandardMass:max(M1Same,M2Same)>>HM1CPassA",         "BaselineCut", "prof");
   T->Draw("OppositeMass:max(M1Same,M2Same)>>HM1CPassB",         "BaselineCut", "prof");
   T->Draw("SameMass:max(M1Same,M2Same)>>HM1CPassC",             "BaselineCut", "prof");
   T->Draw("StandardMass:min(M1Same,M2Same)>>HM2CPassA",         "BaselineCut", "prof");
   T->Draw("OppositeMass:min(M1Same,M2Same)>>HM2CPassB",         "BaselineCut", "prof");
   T->Draw("SameMass:min(M1Same,M2Same)>>HM2CPassC",             "BaselineCut", "prof");
   
   T->Draw("StandardMass:min(M1CMS,M2CMS):max(M1CMS,M2CMS)>>HM1M2APassA",           "BaselineCut", "prof");
   T->Draw("OppositeMass:min(M1CMS,M2CMS):max(M1CMS,M2CMS)>>HM1M2APassB",           "BaselineCut", "prof");
   T->Draw("SameMass:min(M1CMS,M2CMS):max(M1CMS,M2CMS)>>HM1M2APassC",               "BaselineCut", "prof");
   T->Draw("StandardMass:min(M1Opposite,M2Opposite):max(M1Opposite,M2Opposite)>>HM1M2BPassA",           "BaselineCut", "prof");
   T->Draw("OppositeMass:min(M1Opposite,M2Opposite):max(M1Opposite,M2Opposite)>>HM1M2BPassB",           "BaselineCut", "prof");
   T->Draw("SameMass:min(M1Opposite,M2Opposite):max(M1Opposite,M2Opposite)>>HM1M2BPassC",               "BaselineCut", "prof");
   T->Draw("StandardMass:min(M1Same,M2Same):max(M1Same,M2Same)>>HM1M2CPassA",           "BaselineCut", "prof");
   T->Draw("OppositeMass:min(M1Same,M2Same):max(M1Same,M2Same)>>HM1M2CPassB",           "BaselineCut", "prof");
   T->Draw("SameMass:min(M1Same,M2Same):max(M1Same,M2Same)>>HM1M2CPassC",               "BaselineCut", "prof");

   SavePlot1D(HM1APassA, "Plots/" + Tag + "_M1APassA");
   SavePlot1D(HM1APassB, "Plots/" + Tag + "_M1APassB");
   SavePlot1D(HM1APassC, "Plots/" + Tag + "_M1APassC");
   SavePlot1D(HM2APassA, "Plots/" + Tag + "_M2APassA");
   SavePlot1D(HM2APassB, "Plots/" + Tag + "_M2APassB");
   SavePlot1D(HM2APassC, "Plots/" + Tag + "_M2APassC");
   SavePlot1D(HM1BPassA, "Plots/" + Tag + "_M1BPassA");
   SavePlot1D(HM1BPassB, "Plots/" + Tag + "_M1BPassB");
   SavePlot1D(HM1BPassC, "Plots/" + Tag + "_M1BPassC");
   SavePlot1D(HM2BPassA, "Plots/" + Tag + "_M2BPassA");
   SavePlot1D(HM2BPassB, "Plots/" + Tag + "_M2BPassB");
   SavePlot1D(HM2BPassC, "Plots/" + Tag + "_M2BPassC");
   SavePlot1D(HM1CPassA, "Plots/" + Tag + "_M1CPassA");
   SavePlot1D(HM1CPassB, "Plots/" + Tag + "_M1CPassB");
   SavePlot1D(HM1CPassC, "Plots/" + Tag + "_M1CPassC");
   SavePlot1D(HM2CPassA, "Plots/" + Tag + "_M2CPassA");
   SavePlot1D(HM2CPassB, "Plots/" + Tag + "_M2CPassB");
   SavePlot1D(HM2CPassC, "Plots/" + Tag + "_M2CPassC");

   SavePlot2D(HM1M2APassA, "Plots/" + Tag + "_M1M2APassA");
   SavePlot2D(HM1M2APassB, "Plots/" + Tag + "_M1M2APassB");
   SavePlot2D(HM1M2APassC, "Plots/" + Tag + "_M1M2APassC");
   SavePlot2D(HM1M2BPassA, "Plots/" + Tag + "_M1M2BPassA");
   SavePlot2D(HM1M2BPassB, "Plots/" + Tag + "_M1M2BPassB");
   SavePlot2D(HM1M2BPassC, "Plots/" + Tag + "_M1M2BPassC");
   SavePlot2D(HM1M2CPassA, "Plots/" + Tag + "_M1M2CPassA");
   SavePlot2D(HM1M2CPassB, "Plots/" + Tag + "_M1M2CPassB");
   SavePlot2D(HM1M2CPassC, "Plots/" + Tag + "_M1M2CPassC");

   return 0;
}

void SavePlot1D(TProfile *H, string Base)
{
   if(H == NULL)
      return;

   TCanvas C("C", "C", 1024, 1024);

   H->SetStats(0);
   H->GetXaxis()->SetTitleOffset(1.1);
   H->GetYaxis()->SetTitleOffset(1.2);
   H->SetMinimum(0.0);
   H->SetMaximum(1.1);
   H->SetLineWidth(2);
   H->SetFillColor(kGreen);
   H->SetFillStyle(3008);
   H->SetLineColor(kBlack);

   H->Draw("bar hist");
   H->Draw("same");
   H->Draw("axis same");

   C.SaveAs((Base + ".png").c_str());
   C.SaveAs((Base + ".C").c_str());
   C.SaveAs((Base + ".eps").c_str());
   C.SaveAs((Base + ".pdf").c_str());
}

void SavePlot2D(TProfile2D *H, string Base)
{
   if(H == NULL)
      return;

   TCanvas C("C", "C", 1024, 1024);

   H->SetStats(0);
   H->GetXaxis()->SetTitleOffset(1.1);
   H->GetYaxis()->SetTitleOffset(1.2);
   H->SetMinimum(0.0);
   H->SetMaximum(1.0);
   H->SetLineWidth(2);
   H->SetFillColor(kGreen);
   H->SetFillStyle(3008);
   H->SetLineColor(kBlack);

   H->Draw("colz");

   TGraph G;
   G.SetPoint(0, 9999, 12);
   G.SetPoint(1, 40, 12);
   G.SetPoint(2, 40, 9999);
   G.SetLineWidth(3);
   G.SetLineColor(6);
   G.Draw("l");

   C.SaveAs((Base + ".png").c_str());
   C.SaveAs((Base + ".C").c_str());
   C.SaveAs((Base + ".eps").c_str());
   C.SaveAs((Base + ".pdf").c_str());
}







