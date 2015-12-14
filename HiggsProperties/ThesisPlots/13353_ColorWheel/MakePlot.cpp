#include <iostream>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TEllipse.h"
#include "TLatex.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetStyle();

   string InputFile = "Result_gg_h_2e2mu_A2AA_LooseCuts.root";
   string OutputBase = "ColorPlot_gg_h_2e2mu_A2AA_LooseCuts";
   string TypeString = "";

   if(argc > 1)
      InputFile = argv[1];
   if(argc > 2)
      OutputBase = argv[2];
   if(argc > 3)
      TypeString = argv[3];

   TFile File(InputFile.c_str());

   TH1D HYYY("HYYY", "YYY", 10, -1, 2);
   TH1D HYYN("HYYN", "YYN", 10, -1, 2);
   TH1D HYNY("HYNY", "YNY", 10, -1, 2);
   TH1D HYNN("HYNN", "YNN", 10, -1, 2);
   TH1D HNYY("HNYY", "NYY", 10, -1, 2);
   TH1D HNYN("HNYN", "NYN", 10, -1, 2);
   TH1D HNNY("HNNY", "NNY", 10, -1, 2);
   TH1D HNNN("HNNN", "NNN", 10, -1, 2);

   string CutString = "";
   string GateString = "";

   if(TypeString == "Absolute")
      CutString = "", GateString = "BaselineCut * ";
   else if(TypeString == "Relative")
      CutString = "BaselineCut", GateString = "";
   else if(TypeString == "None")
      CutString = "", GateString = "";
   else
      CutString = "BaselineCut", GateString = "";

   TTree *CutTree = (TTree *)File.Get("CutTree");

   CutTree->Draw((GateString + "(StandardMass > 0 && OppositeMass > 0 && SameMass > 0) >> HYYY").c_str(),    CutString.c_str());
   CutTree->Draw((GateString + "(StandardMass > 0 && OppositeMass > 0 && SameMass == 0) >> HYYN").c_str(),   CutString.c_str());
   CutTree->Draw((GateString + "(StandardMass > 0 && OppositeMass == 0 && SameMass > 0) >> HYNY").c_str(),   CutString.c_str());
   CutTree->Draw((GateString + "(StandardMass > 0 && OppositeMass == 0 && SameMass == 0) >> HYNN").c_str(),  CutString.c_str());
   CutTree->Draw((GateString + "(StandardMass == 0 && OppositeMass > 0 && SameMass > 0) >> HNYY").c_str(),   CutString.c_str());
   CutTree->Draw((GateString + "(StandardMass == 0 && OppositeMass > 0 && SameMass == 0) >> HNYN").c_str(),  CutString.c_str());
   CutTree->Draw((GateString + "(StandardMass == 0 && OppositeMass == 0 && SameMass > 0) >> HNNY").c_str(),  CutString.c_str());
   CutTree->Draw((GateString + "(StandardMass == 0 && OppositeMass == 0 && SameMass == 0) >> HNNN").c_str(), CutString.c_str());

   double NYYY = HYYY.GetMean() * 100;
   double NYYN = HYYN.GetMean() * 100;
   double NYNY = HYNY.GetMean() * 100;
   double NYNN = HYNN.GetMean() * 100;
   double NNYY = HNYY.GetMean() * 100;
   double NNYN = HNYN.GetMean() * 100;
   double NNNY = HNNY.GetMean() * 100;
   double NNNN = HNNN.GetMean() * 100;

   NNNN = 100 - NYYY - NYYN - NYNY - NYNN - NNYY - NNYN - NNNY;

   TCanvas C("C", "C", 1024, 1024);

   double R = 0.3;
   double D = 0.18;

   double CX = 0.5;
   double CY = 0.475;

   TEllipse E1(CX, CY + D, R);
   TEllipse E2(CX + D * sqrt(3) / 2, CY - D / 2, R);
   TEllipse E3(CX - D * sqrt(3) / 2, CY - D / 2, R);

   E1.SetFillStyle(0);
   E2.SetFillStyle(0);
   E3.SetFillStyle(0);

   E1.Draw("l");
   E2.Draw("l");
   E3.Draw("l");

   double PI = 3.14159265358979323846264338327950288479716939937510;

   TLatex Latex;
   Latex.SetTextAlign(22);
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.04);

   Latex.DrawLatex(CX, CY, Form("%3.1f%%", NYYY));
   Latex.DrawLatex(CX + D * 1.2 * cos(PI / 6), CY + D * 1.2 * sin(PI / 6), Form("%3.1f%%", NYNY));
   Latex.DrawLatex(CX + D * 1.2 * cos(5 * PI / 6), CY + D * 1.2 * sin(5 * PI / 6), Form("%3.1f%%", NYYN));
   Latex.DrawLatex(CX + D * 1.2 * cos(3 * PI / 2), CY + D * 1.2 * sin(3 * PI / 2), Form("%3.1f%%", NNYY));
   Latex.DrawLatex(CX + D * 1.75 * cos(PI / 2), CY + D * 1.75 * sin(PI / 2), Form("%3.1f%%", NYNN));
   Latex.DrawLatex(CX + D * 1.75 * cos(7 * PI / 6), CY + D * 1.75 * sin(7 * PI / 6), Form("%3.1f%%", NNYN));
   Latex.DrawLatex(CX + D * 1.75 * cos(11 * PI / 6), CY + D * 1.75 * sin(11 * PI / 6), Form("%3.1f%%", NNNY));
   Latex.DrawLatex(CX + 0.4, CY - 0.375, Form("%3.1f%%", NNNN));

   double NYXX = NYNN + NYNY + NYYN + NYYY;
   double NXYX = NNYN + NNYY + NYYN + NYYY;
   double NXXY = NNNY + NYNY + NNYY + NYYY;

   Latex.SetTextAlign(12);
   Latex.DrawLatex(CX + R * 1.1 * cos(PI / 4), CY + R * 1.1 * sin(PI / 4) + D, Form("A (%3.1f%%)", NYXX));
   Latex.SetTextAlign(22);
   Latex.DrawLatex(CX + D * cos(7 * PI / 6) - R * 0.2, CY + D * sin(7 * PI / 6) - R * 1.1, Form("B (%3.1f%%)", NXYX));
   Latex.DrawLatex(CX + D * cos(11 * PI / 6), CY + D * sin(11 * PI / 6) - R * 1.1, Form("C (%3.1f%%)", NXXY));

   C.SaveAs(Form("%s.png", OutputBase.c_str()));
   C.SaveAs(Form("%s.C"  , OutputBase.c_str()));
   C.SaveAs(Form("%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s.pdf", OutputBase.c_str()));

   return 0;
}

