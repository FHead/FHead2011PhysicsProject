#include <iostream>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"

#include "SetStyle.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main();
void SetAlias(TTree *T, bool IsLepton);
void ScaleHistogram(TH1D *H);
void PrepareHistogram(TH1D *H, bool IsLepton);

int main()
{
   SetThesisRegularStyle();

   TFile FL("LeptonBasis.root");
   TFile FP("ProductionBasis.root");

   TTree *TL = (TTree *)FL.Get("Tree");
   TTree *TP = (TTree *)FP.Get("Tree");

   SetAlias(TL, true);
   SetAlias(TP, false);

   TH1D HLMH("HLMH", ";m_{4l};a.u.", 100, 100, 140);
   TH1D HPMH("HPMH", ";m_{4l};a.u.", 100, 100, 140);
   TH1D HLM1("HLM1", ";m_{1};a.u.", 100, 40, 100);
   TH1D HPM1("HPM1", ";m_{1};a.u.", 100, 40, 100);
   TH1D HLM2("HLM2", ";m_{2};a.u.", 100, 4, 70);
   TH1D HPM2("HPM2", ";m_{2};a.u.", 100, 4, 70);
   TH1D HLPhi0("HLPhi0", ";#Phi_{1};a.u.", 100, -PI, PI);
   TH1D HPPhi0("HPPhi0", ";#Phi_{1};a.u.", 100, -PI, PI);
   TH1D HLCosTheta0("HLCosTheta0", ";cos#Theta;a.u.", 100, -1, 1);
   TH1D HPCosTheta0("HPCosTheta0", ";cos#Theta;a.u.", 100, -1, 1);
   TH1D HLPhi("HLPhi", ";#phi;a.u.", 100, -PI, PI);
   TH1D HPPhi("HPPhi", ";#phi;a.u.", 100, -PI, PI);
   TH1D HLCosTheta1("HLCosTheta1", ";cos#theta_{1};a.u.", 100, -1, 1);
   TH1D HPCosTheta1("HPCosTheta1", ";cos#theta_{1};a.u.", 100, -1, 1);
   TH1D HLCosTheta2("HLCosTheta2", ";cos#theta_{2};a.u.", 100, -1, 1);
   TH1D HPCosTheta2("HPCosTheta2", ";cos#theta_{2};a.u.", 100, -1, 1);
   TH1D HLPhiOffset("HLPhiOffset", ";#phi_{offset};a.u.", 100, -PI, PI);
   TH1D HPPhiOffset("HPPhiOffset", ";#phi_{offset};a.u.", 100, -PI, PI);
   TH1D HLPhiH("HLPhiH", ";#phi_{4l};a.u.", 100, -PI, PI);
   TH1D HPPhiH("HPPhiH", ";#phi_{4l};a.u.", 100, -PI, PI);
   TH1D HLPTH("HLPTH", ";p_{T};a.u.", 100, 15, 100);
   TH1D HPPTH("HPPTH", ";p_{T};a.u.", 100, 15, 100);
   TH1D HLYH("HLYH", ";y_{4l};a.u.", 100, -2, 2);
   TH1D HPYH("HPYH", ";y_{4l};a.u.", 100, -2, 2);

   HLMH.GetXaxis()->SetTitle("M_{4l}");
   HPMH.GetXaxis()->SetTitle("M_{4l}");
   HLM1.GetXaxis()->SetTitle("M_{1}");
   HPM1.GetXaxis()->SetTitle("M_{1}");
   HLM2.GetXaxis()->SetTitle("M_{2}");
   HPM2.GetXaxis()->SetTitle("M_{2}");
   HLPhi.GetXaxis()->SetTitle("#Phi");
   HPPhi.GetXaxis()->SetTitle("#Phi");
   HLPhiOffset.GetXaxis()->SetTitle("#phi");
   HPPhiOffset.GetXaxis()->SetTitle("#phi");
   HLYH.GetXaxis()->SetTitle("Y");
   HPYH.GetXaxis()->SetTitle("Y");

   long long COUNT = 10000000;
   TL->Draw("MH>>HLMH", "Cut", "", COUNT);
   TP->Draw("MH>>HPMH", "Cut", "same", COUNT);
   TL->Draw("M1>>HLM1", "Cut", "", COUNT);
   TP->Draw("M1>>HPM1", "Cut", "same", COUNT);
   TL->Draw("M2>>HLM2", "Cut", "", COUNT);
   TP->Draw("M2>>HPM2", "Cut", "same", COUNT);
   TL->Draw("Phi0-2*3.1415926535*(Phi0>3.1415926535)>>HLPhi0", "Cut", "", COUNT);
   TP->Draw("Phi0-2*3.1415926535*(Phi0>3.1415926535)>>HPPhi0", "Cut", "same", COUNT);
   TL->Draw("cos(Theta0)>>HLCosTheta0", "Cut", "", COUNT);
   TP->Draw("cos(Theta0)>>HPCosTheta0", "Cut", "same", COUNT);
   TL->Draw("Phi-2*3.1415926535*(Phi>3.1415926535)>>HLPhi", "Cut", "", COUNT);
   TP->Draw("Phi-2*3.1415926535*(Phi>3.1415926535)>>HPPhi", "Cut", "same", COUNT);
   TL->Draw("cos(Theta1)>>HLCosTheta1", "Cut", "", COUNT);
   TP->Draw("cos(Theta1)>>HPCosTheta1", "Cut", "same", COUNT);
   TL->Draw("cos(Theta2)>>HLCosTheta2", "Cut", "", COUNT);
   TP->Draw("cos(Theta2)>>HPCosTheta2", "Cut", "same", COUNT);
   TL->Draw("PhiOffset-2*3.1415926535*(PhiOffset>3.1415926535)+2*3.1415926535*(PhiOffset<-3.1415926535)>>HLPhiOffset", "Cut", "", COUNT);
   TP->Draw("PhiOffset-2*3.1415926535*(PhiOffset>3.1415926535)+2*3.1415926535*(PhiOffset<-3.1415926535)>>HPPhiOffset", "Cut", "", COUNT);
   TL->Draw("HPhi-2*3.1415926535*(HPhi>3.1415926535)>>HLPhiH", "Cut", "", COUNT);
   TP->Draw("HPhi-2*3.1415926535*(HPhi>3.1415926535)>>HPPhiH", "Cut", "same", COUNT);
   TL->Draw("HPT>>HLPTH", "Cut", "", COUNT);
   TP->Draw("HPT>>HPPTH", "Cut", "same", COUNT);
   TL->Draw("HY>>HLYH", "Cut", "", COUNT);
   TP->Draw("HY>>HPYH", "Cut", "same", COUNT);

   ScaleHistogram(&HLMH);
   ScaleHistogram(&HPMH);
   ScaleHistogram(&HLM1);
   ScaleHistogram(&HPM1);
   ScaleHistogram(&HLM2);
   ScaleHistogram(&HPM2);
   ScaleHistogram(&HLPhi0);
   ScaleHistogram(&HPPhi0);
   ScaleHistogram(&HLCosTheta0);
   ScaleHistogram(&HPCosTheta0);
   ScaleHistogram(&HLPhi);
   ScaleHistogram(&HPPhi);
   ScaleHistogram(&HLCosTheta1);
   ScaleHistogram(&HPCosTheta1);
   ScaleHistogram(&HLCosTheta2);
   ScaleHistogram(&HPCosTheta2);
   ScaleHistogram(&HLPhiOffset);
   ScaleHistogram(&HPPhiOffset);
   ScaleHistogram(&HLPhiH);
   ScaleHistogram(&HPPhiH);
   ScaleHistogram(&HLPTH);
   ScaleHistogram(&HPPTH);
   ScaleHistogram(&HLYH);
   ScaleHistogram(&HPYH);

   PrepareHistogram(&HLMH, true);
   PrepareHistogram(&HPMH, false);
   PrepareHistogram(&HLM1, true);
   PrepareHistogram(&HPM1, false);
   PrepareHistogram(&HLM2, true);
   PrepareHistogram(&HPM2, false);
   PrepareHistogram(&HLPhi0, true);
   PrepareHistogram(&HPPhi0, false);
   PrepareHistogram(&HLCosTheta0, true);
   PrepareHistogram(&HPCosTheta0, false);
   PrepareHistogram(&HLPhi, true);
   PrepareHistogram(&HPPhi, false);
   PrepareHistogram(&HLCosTheta1, true);
   PrepareHistogram(&HPCosTheta1, false);
   PrepareHistogram(&HLCosTheta2, true);
   PrepareHistogram(&HPCosTheta2, false);
   PrepareHistogram(&HLPhiOffset, true);
   PrepareHistogram(&HPPhiOffset, false);
   PrepareHistogram(&HLPhiH, true);
   PrepareHistogram(&HPPhiH, false);
   PrepareHistogram(&HLPTH, true);
   PrepareHistogram(&HPPTH, false);
   PrepareHistogram(&HLYH, true);
   PrepareHistogram(&HPYH, false);

   double X1, X2, Y1, Y2;
   X1 = ThesisNDCMappingRegularX(0.15);
   X2 = ThesisNDCMappingRegularX(0.60);
   Y1 = ThesisNDCMappingRegularY(0.85);
   Y2 = ThesisNDCMappingRegularY(0.65);

   TLegend Legend(X1, Y1, X2, Y2);
   Legend.SetTextFont(42);
   Legend.SetFillStyle(0);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&HLMH, "Lepton basis", "l");
   Legend.AddEntry(&HPMH, "Observable basis", "l");

   TCanvas C;

   HLMH.Draw();
   HPMH.Draw("same");
   Legend.Draw();
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation1.png");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation1.C");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation1.eps");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation1.pdf");

   HLM1.Draw();
   HPM1.Draw("same");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation2.png");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation2.C");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation2.eps");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation2.pdf");

   HLM2.Draw();
   HPM2.Draw("same");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation3.png");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation3.C");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation3.eps");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation3.pdf");

   HLPhi0.Draw();
   HPPhi0.Draw("same");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation4.png");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation4.C");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation4.eps");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation4.pdf");

   HLCosTheta0.Draw();
   HPCosTheta0.Draw("same");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation5.png");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation5.C");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation5.eps");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation5.pdf");

   HLPhi.Draw();
   HPPhi.Draw("same");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation6.png");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation6.C");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation6.eps");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation6.pdf");

   HLCosTheta1.Draw();
   HPCosTheta1.Draw("same");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation7.png");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation7.C");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation7.eps");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation7.pdf");

   HLCosTheta2.Draw();
   HPCosTheta2.Draw("same");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation8.png");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation8.C");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation8.eps");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation8.pdf");

   HLPhiOffset.Draw();
   HPPhiOffset.Draw("same");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation9.png");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation9.C");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation9.eps");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation9.pdf");

   HLPhiH.Draw();
   HPPhiH.Draw("same");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation10.png");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation10.C");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation10.eps");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation10.pdf");

   HLPTH.Draw();
   HPPTH.Draw("same");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation11.png");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation11.C");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation11.eps");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation11.pdf");

   HLYH.Draw();
   HPYH.Draw("same");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation12.png");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation12.C");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation12.eps");
   C.SaveAs("MultiDimensionalDetails-Jacobians-12DValidation12.pdf");

   return 0;
}

void SetAlias(TTree *T, bool IsLepton)
{
   if(T == NULL)
      return;

   T->SetAlias("L1P", "(L1PT * cosh(L1Eta))");
   T->SetAlias("L2P", "(L2PT * cosh(L2Eta))");
   T->SetAlias("L3P", "(L3PT * cosh(L3Eta))");
   T->SetAlias("L4P", "(L4PT * cosh(L4Eta))");
   T->SetAlias("BaseCut", "(Weight[0][0] * (L1P < 100 && L2P < 100 && L3P < 100 && L4P < 100 && MH > 100 && MH < 140 && M1 > 4 && M2 > 4 && M1 < 100 && M2 < 100))");

   if(IsLepton == true)
      T->SetAlias("Cut", "(BaseCut * (BaseCut < 5e-4))");
   else
      T->SetAlias("Cut", "(BaseCut * (BaseCut < 1000000))");
}

void ScaleHistogram(TH1D *H)
{
   if(H == NULL)
      return;

   int Bin = H->GetNbinsX();
   double Min = H->GetXaxis()->GetBinLowEdge(1);
   double Max = H->GetXaxis()->GetBinUpEdge(H->GetNbinsX());
   double Width = Max - Min;

   H->Scale(1 / H->Integral() / Width * Bin);
}

void PrepareHistogram(TH1D *H, bool IsLepton)
{
   H->SetLineWidth(2);
   H->SetStats(0);
   H->SetMinimum(0);
   H->GetXaxis()->SetNdivisions(505);

   if(IsLepton == true)
      H->SetLineColor(kBlue);
   else
      H->SetLineColor(kRed);
}

