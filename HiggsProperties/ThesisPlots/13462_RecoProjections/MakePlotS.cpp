#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main()
{
   SetThesisRegularStyle();

   TFile F1("Signal.root");
   TFile F2("SignalSmeared.root");

   TTree *T1 = (TTree *)F1.Get("Tree");
   TTree *T2 = (TTree *)F2.Get("Tree");

   T1->SetAlias("Cut", "(min(min(L1PT, L2PT), min(L3PT, L4PT)) > 7 && (max(max(L1PT,L2PT),max(L3PT,L4PT))) > 20 && (max(max(max(L1PT+L2PT,L1PT+L3PT),max(L1PT+L4PT,L2PT+L3PT)),max(L2PT+L4PT,L3PT+L4PT))) > 30 && MH > 115 && MH < 135 && M1 > 40 && M2 > 12 && abs(L1Eta) < 2.4 && abs(L2Eta) < 2.4 && abs(L3Eta) < 2.4 && abs(L4Eta) < 2.4) * Weight[0][0] * M1 * M2 / MH / MH / MH / SamplingWeight * (log(Weight[0][0] / SamplingWeight) < 0)");
   T2->SetAlias("Cut", "(min(min(L1PT, L2PT), min(L3PT, L4PT)) > 7 && (max(max(L1PT,L2PT),max(L3PT,L4PT))) > 20 && (max(max(max(L1PT+L2PT,L1PT+L3PT),max(L1PT+L4PT,L2PT+L3PT)),max(L2PT+L4PT,L3PT+L4PT))) > 30 && MH > 115 && MH < 135 && M1 > 40 && M2 > 12 && abs(L1Eta) < 2.4 && abs(L2Eta) < 2.4 && abs(L3Eta) < 2.4 && abs(L4Eta) < 2.4) * Weight");

   int BinCount = 50;
   TH1D *HMH1 = new TH1D("HMH1", "", BinCount, 115, 135);   HMH1->Sumw2();
   TH1D *HMH2 = new TH1D("HMH2", "", BinCount, 115, 135);   HMH2->Sumw2();
   TH1D *HM11 = new TH1D("HM11", "", BinCount, 40, 100);   HM11->Sumw2();
   TH1D *HM12 = new TH1D("HM12", "", BinCount, 40, 100);   HM12->Sumw2();
   TH1D *HM21 = new TH1D("HM21", "", BinCount, 12, 70);   HM21->Sumw2();
   TH1D *HM22 = new TH1D("HM22", "", BinCount, 12, 70);   HM22->Sumw2();
   TH1D *HPhi01 = new TH1D("HPhi01", "", BinCount, -PI, PI);   HPhi01->Sumw2();
   TH1D *HPhi02 = new TH1D("HPhi02", "", BinCount, -PI, PI);   HPhi02->Sumw2();
   TH1D *HCosTheta01 = new TH1D("HCosTheta01", "", BinCount, -1, 1);   HCosTheta01->Sumw2();
   TH1D *HCosTheta02 = new TH1D("HCosTheta02", "", BinCount, -1, 1);   HCosTheta02->Sumw2();
   TH1D *HPhi1 = new TH1D("HPhi1", "", BinCount, -PI, PI);   HPhi1->Sumw2();
   TH1D *HPhi2 = new TH1D("HPhi2", "", BinCount, -PI, PI);   HPhi2->Sumw2();
   TH1D *HCosTheta11 = new TH1D("HCosTheta11", "", BinCount, -1, 1);   HCosTheta11->Sumw2();
   TH1D *HCosTheta12 = new TH1D("HCosTheta12", "", BinCount, -1, 1);   HCosTheta12->Sumw2();
   TH1D *HCosTheta21 = new TH1D("HCosTheta21", "", BinCount, -1, 1);   HCosTheta21->Sumw2();
   TH1D *HCosTheta22 = new TH1D("HCosTheta22", "", BinCount, -1, 1);   HCosTheta22->Sumw2();
   TH1D *HPhiH1 = new TH1D("HPhiH1", "", BinCount, -PI, PI);   HPhiH1->Sumw2();
   TH1D *HPhiH2 = new TH1D("HPhiH2", "", BinCount, -PI, PI);   HPhiH2->Sumw2();
   TH1D *HPTH1 = new TH1D("HPTH1", "", BinCount, 0, 200);   HPTH1->Sumw2();
   TH1D *HPTH2 = new TH1D("HPTH2", "", BinCount, 0, 200);   HPTH2->Sumw2();
   TH1D *HYH1 = new TH1D("HYH1", "", BinCount, -3, 3);   HYH1->Sumw2();
   TH1D *HYH2 = new TH1D("HYH2", "", BinCount, -3, 3);   HYH2->Sumw2();
   TH1D *HPhiOffset1 = new TH1D("HPhiOffset1", "", BinCount, -PI, PI);   HPhiOffset1->Sumw2();
   TH1D *HPhiOffset2 = new TH1D("HPhiOffset2", "", BinCount, -PI, PI);   HPhiOffset2->Sumw2();

   HMH1->SetLineWidth(2);
   HMH1->SetLineColor(kBlack);
   HMH2->SetLineWidth(2);
   HMH2->SetLineColor(kGreen - 3);
   HM11->SetLineWidth(2);
   HM11->SetLineColor(kBlack);
   HM12->SetLineWidth(2);
   HM12->SetLineColor(kGreen - 3);
   HM21->SetLineWidth(2);
   HM21->SetLineColor(kBlack);
   HM22->SetLineWidth(2);
   HM22->SetLineColor(kGreen - 3);
   HPhi01->SetLineWidth(2);
   HPhi01->SetLineColor(kBlack);
   HPhi02->SetLineWidth(2);
   HPhi02->SetLineColor(kGreen - 3);
   HCosTheta01->SetLineWidth(2);
   HCosTheta01->SetLineColor(kBlack);
   HCosTheta02->SetLineWidth(2);
   HCosTheta02->SetLineColor(kGreen - 3);
   HPhi1->SetLineWidth(2);
   HPhi1->SetLineColor(kBlack);
   HPhi2->SetLineWidth(2);
   HPhi2->SetLineColor(kGreen - 3);
   HCosTheta11->SetLineWidth(2);
   HCosTheta11->SetLineColor(kBlack);
   HCosTheta12->SetLineWidth(2);
   HCosTheta12->SetLineColor(kGreen - 3);
   HCosTheta21->SetLineWidth(2);
   HCosTheta21->SetLineColor(kBlack);
   HCosTheta22->SetLineWidth(2);
   HCosTheta22->SetLineColor(kGreen - 3);
   HPhiH1->SetLineWidth(2);
   HPhiH1->SetLineColor(kBlack);
   HPhiH2->SetLineWidth(2);
   HPhiH2->SetLineColor(kGreen - 3);
   HPTH1->SetLineWidth(2);
   HPTH1->SetLineColor(kBlack);
   HPTH2->SetLineWidth(2);
   HPTH2->SetLineColor(kGreen - 3);
   HYH1->SetLineWidth(2);
   HYH1->SetLineColor(kBlack);
   HYH2->SetLineWidth(2);
   HYH2->SetLineColor(kGreen - 3);
   HPhiOffset1->SetLineWidth(2);
   HPhiOffset1->SetLineColor(kBlack);
   HPhiOffset2->SetLineWidth(2);
   HPhiOffset2->SetLineColor(kGreen - 3);

   cout << "MH" << endl;
   T1->Draw("MH>>HMH1", "Cut", "error");
   T2->Draw("MH>>HMH2", "Cut", "error");
   cout << "M1" << endl;
   T1->Draw("M1>>HM11", "Cut", "error");
   T2->Draw("M1>>HM12", "Cut", "error");
   cout << "M2" << endl;
   T1->Draw("M2>>HM21", "Cut", "error");
   T2->Draw("M2>>HM22", "Cut", "error");
   cout << "Phi0" << endl;
   T1->Draw("Phi0-2*3.1415926535*(Phi0>3.1415926535)+2*3.1415926535*(Phi0<-3.1415926535)>>HPhi01", "Cut", "error");
   T2->Draw("Phi0-2*3.1415926535*(Phi0>3.1415926535)+2*3.1415926535*(Phi0<-3.1415926535)>>HPhi02", "Cut", "error");
   cout << "Theta0" << endl;
   T1->Draw("cos(Theta0)>>HCosTheta01", "Cut", "error");
   T2->Draw("cos(Theta0)>>HCosTheta02", "Cut", "error");
   cout << "Phi" << endl;
   T1->Draw("Phi-2*3.1415926535*(Phi>3.1415926535)>>HPhi1", "Cut", "error");
   T2->Draw("Phi-2*3.1415926535*(Phi>3.1415926535)>>HPhi2", "Cut", "error");
   cout << "Theta1" << endl;
   T1->Draw("cos(Theta1)>>HCosTheta11", "Cut", "error");
   T2->Draw("cos(Theta1)>>HCosTheta12", "Cut", "error");
   cout << "Theta2" << endl;
   T1->Draw("cos(Theta2)>>HCosTheta21", "Cut", "error");
   T2->Draw("cos(Theta2)>>HCosTheta22", "Cut", "error");
   cout << "HPhi" << endl;
   T1->Draw("HPhi-2*3.1415926535*(HPhi>3.1415926535)>>HPhiH1", "Cut", "error");
   T2->Draw("HPhi-2*3.1415926535*(HPhi>3.1415926535)>>HPhiH2", "Cut", "error");
   cout << "HPT" << endl;
   T1->Draw("HPT>>HPTH1", "Cut", "error");
   T2->Draw("HPT>>HPTH2", "Cut", "error");
   cout << "HY" << endl;
   T1->Draw("HY>>HYH1", "Cut", "error");
   T2->Draw("HY>>HYH2", "Cut", "error");
   cout << "PhiOffset" << endl;
   T1->Draw("PhiOffset-2*3.1415926535*(PhiOffset>3.1415926535)+2*3.1415926535*(PhiOffset<-3.1415926535)>>HPhiOffset1", "Cut", "error");
   T2->Draw("PhiOffset-2*3.1415926535*(PhiOffset>3.1415926535)+2*3.1415926535*(PhiOffset<-3.1415926535)>>HPhiOffset2", "Cut", "error");

   HMH1->Scale(1 / HMH1->Integral() * HMH1->GetNbinsX() / (135 - 115));
   HMH2->Scale(1 / HMH2->Integral() * HMH2->GetNbinsX() / (135 - 115));
   HM11->Scale(1 / HM11->Integral() * HM11->GetNbinsX() / (100 - 40));
   HM12->Scale(1 / HM12->Integral() * HM12->GetNbinsX() / (100 - 40));
   HM21->Scale(1 / HM21->Integral() * HM21->GetNbinsX() / (70 - 12));
   HM22->Scale(1 / HM22->Integral() * HM22->GetNbinsX() / (70 - 12));
   HPhi01->Scale(1 / HPhi01->Integral() * HPhi01->GetNbinsX() / (PI - -PI));
   HPhi02->Scale(1 / HPhi02->Integral() * HPhi02->GetNbinsX() / (PI - -PI));
   HCosTheta01->Scale(1 / HCosTheta01->Integral() * HCosTheta01->GetNbinsX() / (1 - -1));
   HCosTheta02->Scale(1 / HCosTheta02->Integral() * HCosTheta02->GetNbinsX() / (1 - -1));
   HPhi1->Scale(1 / HPhi1->Integral() * HPhi1->GetNbinsX() / (PI - -PI));
   HPhi2->Scale(1 / HPhi2->Integral() * HPhi2->GetNbinsX() / (PI - -PI));
   HCosTheta11->Scale(1 / HCosTheta11->Integral() * HCosTheta11->GetNbinsX() / (1 - -1));
   HCosTheta12->Scale(1 / HCosTheta12->Integral() * HCosTheta12->GetNbinsX() / (1 - -1));
   HCosTheta21->Scale(1 / HCosTheta21->Integral() * HCosTheta21->GetNbinsX() / (1 - -1));
   HCosTheta22->Scale(1 / HCosTheta22->Integral() * HCosTheta22->GetNbinsX() / (1 - -1));
   HPhiH1->Scale(1 / HPhiH1->Integral() * HPhiH1->GetNbinsX() / (PI - -PI));
   HPhiH2->Scale(1 / HPhiH2->Integral() * HPhiH2->GetNbinsX() / (PI - -PI));
   HPTH1->Scale(1 / HPTH1->Integral() * HPTH1->GetNbinsX() / (200 - 0));
   HPTH2->Scale(1 / HPTH2->Integral() * HPTH2->GetNbinsX() / (200 - 0));
   HYH1->Scale(1 / HYH1->Integral() * HYH1->GetNbinsX() / (3 - -3));
   HYH2->Scale(1 / HYH2->Integral() * HYH2->GetNbinsX() / (3 - -3));
   HPhiOffset1->Scale(1 / HPhiOffset1->Integral() * HPhiOffset1->GetNbinsX() / (PI - -PI));
   HPhiOffset2->Scale(1 / HPhiOffset2->Integral() * HPhiOffset2->GetNbinsX() / (PI - -PI));

   TH1D HWorld1("HWorld1", ";m_{4l};a.u.", 100, 117, 135);
   TH1D HWorld2("HWorld2", ";m_{1};a.u.", 100, 40, 100);
   TH1D HWorld3("HWorld3", ";m_{2};a.u.", 100, 12, 70);
   TH1D HWorld4("HWorld4", ";#Phi_{1};a.u.", 100, -PI, PI);
   TH1D HWorld5("HWorld5", ";cos #Theta;a.u.", 100, -1, 1);
   TH1D HWorld6("HWorld6", ";#phi;a.u.", 100, -PI, PI);
   TH1D HWorld7("HWorld7", ";cos #theta_{1};a.u.", 100, -1, 1);
   TH1D HWorld8("HWorld8", ";cos #theta_{2};a.u.", 100, -1, 1);
   TH1D HWorld9("HWorld9", ";#phi_{4l};a.u.", 100, -PI, PI);
   TH1D HWorld10("HWorld10", ";p_{T, 4l};a.u.", 100, 0, 150);
   TH1D HWorld11("HWorld11", ";y_{4l};a.u.", 100, -3, 3);
   TH1D HWorld12("HWorld12", ";#phi_{offset};a.u.", 100, -PI, PI);

   HWorld1.SetStats(0);
   HWorld2.SetStats(0);
   HWorld3.SetStats(0);
   HWorld4.SetStats(0);
   HWorld5.SetStats(0);
   HWorld6.SetStats(0);
   HWorld7.SetStats(0);
   HWorld8.SetStats(0);
   HWorld9.SetStats(0);
   HWorld10.SetStats(0);
   HWorld11.SetStats(0);
   HWorld12.SetStats(0);

   HWorld1.SetMinimum(0);
   HWorld1.SetMaximum(0.35);
   HWorld2.SetMinimum(0);
   HWorld2.SetMaximum(0.12);
   HWorld3.SetMinimum(0);
   HWorld3.SetMaximum(0.078);
   HWorld4.SetMinimum(0);
   HWorld4.SetMaximum(0.4);
   HWorld5.SetMinimum(0);
   HWorld5.SetMaximum(1.2);
   HWorld6.SetMinimum(0);
   HWorld6.SetMaximum(0.3);
   HWorld7.SetMinimum(0);
   HWorld7.SetMaximum(1.2);
   HWorld8.SetMinimum(0);
   HWorld8.SetMaximum(1.2);
   HWorld9.SetMinimum(0);
   HWorld9.SetMaximum(0.3);
   HWorld10.SetMinimum(0);
   HWorld10.SetMaximum(0.032);
   HWorld11.SetMinimum(0);
   HWorld11.SetMaximum(0.6);
   HWorld12.SetMinimum(0);
   HWorld12.SetMaximum(0.3);

   HWorld1.GetXaxis()->SetNdivisions(505);
   HWorld2.GetXaxis()->SetNdivisions(505);
   HWorld3.GetXaxis()->SetNdivisions(505);
   HWorld4.GetXaxis()->SetNdivisions(505);
   HWorld5.GetXaxis()->SetNdivisions(505);
   HWorld6.GetXaxis()->SetNdivisions(505);
   HWorld7.GetXaxis()->SetNdivisions(505);
   HWorld8.GetXaxis()->SetNdivisions(505);
   HWorld9.GetXaxis()->SetNdivisions(505);
   HWorld10.GetXaxis()->SetNdivisions(505);
   HWorld11.GetXaxis()->SetNdivisions(505);
   HWorld12.GetXaxis()->SetNdivisions(505);

   double X1, X2, Y1, Y2;
   X1 = ThesisNDCMappingRegularX(0.45);
   X2 = ThesisNDCMappingRegularX(0.85);
   Y1 = ThesisNDCMappingRegularY(0.85);
   Y2 = ThesisNDCMappingRegularY(0.65);

   TLegend Legend(X1, Y1, X2, Y2);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(HMH1, "Toy from PDF", "lp");
   Legend.AddEntry(HMH2, "Smeared sample", "l");

   TCanvas C;

   HWorld1.Draw();
   HMH1->Draw("error same");
   HMH2->Draw("hist same");
   Legend.Draw();
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections1.png");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections1.C");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections1.eps");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections1.pdf");

   HWorld2.Draw();
   HM11->Draw("error same");
   HM12->Draw("hist same");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections2.png");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections2.C");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections2.eps");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections2.pdf");

   HWorld3.Draw();
   HM21->Draw("error same");
   HM22->Draw("hist same");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections3.png");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections3.C");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections3.eps");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections3.pdf");

   HWorld4.Draw();
   HPhi01->Draw("error same");
   HPhi02->Draw("hist same");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections4.png");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections4.C");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections4.eps");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections4.pdf");

   HWorld5.Draw();
   HCosTheta01->Draw("error same");
   HCosTheta02->Draw("hist same");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections5.png");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections5.C");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections5.eps");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections5.pdf");

   HWorld6.Draw();
   HPhi1->Draw("error same");
   HPhi2->Draw("hist same");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections6.png");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections6.C");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections6.eps");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections6.pdf");

   HWorld7.Draw();
   HCosTheta11->Draw("error same");
   HCosTheta12->Draw("hist same");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections7.png");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections7.C");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections7.eps");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections7.pdf");

   HWorld8.Draw();
   HCosTheta21->Draw("error same");
   HCosTheta22->Draw("hist same");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections8.png");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections8.C");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections8.eps");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections8.pdf");

   HWorld9.Draw();
   HPhiH1->Draw("error same");
   HPhiH2->Draw("hist same");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections9.png");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections9.C");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections9.eps");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections9.pdf");

   HWorld10.Draw();
   HPTH1->Draw("error same");
   HPTH2->Draw("hist same");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections10.png");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections10.C");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections10.eps");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections10.pdf");

   HWorld11.Draw();
   HYH1->Draw("error same");
   HYH2->Draw("hist same");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections11.png");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections11.C");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections11.eps");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections11.pdf");

   HWorld12.Draw();
   HPhiOffset1->Draw("error same");
   HPhiOffset2->Draw("hist same");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections12.png");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections12.C");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections12.eps");
   C.SaveAs("MultiDimensionalValidation-Likelihood-SignalProjections12.pdf");

   F2.Close();
   F1.Close();

   return 0;
}




