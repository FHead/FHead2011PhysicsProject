#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main()
{
   SetStyle();

   TFile F1("SingleMu.root");
   TFile F2("MET.root");

   TTree *T1 = (TTree *)F1.Get("ExportTree/HcalNoiseTree");
   TTree *T2 = (TTree *)F2.Get("ExportTree/HcalNoiseTree");

   TH2D *H1 = new TH2D("H1", ";RBX Energy (GeV);RBX R45", 100, 0, 500, 100, -1, 1);
   TH2D *H2 = new TH2D("H2", ";RBX Energy (GeV);RBX R45", 100, 0, 500, 100, -1, 1);

   T1->Draw("(RBXCharge[][4]-RBXCharge[][5])/(RBXCharge[][4]+RBXCharge[][5]):RBXEnergy[]>>H1", "RBXEnergy[] > 0", "colz");
   T2->Draw("(RBXCharge[][4]-RBXCharge[][5])/(RBXCharge[][4]+RBXCharge[][5]):RBXEnergy[]>>H2", "RBXEnergy[] > 0", "colz");

   H1->SetStats(0);
   H1->GetXaxis()->SetTitleOffset(1.1);
   H1->GetYaxis()->SetTitleOffset(1.2);

   H2->SetStats(0);
   H2->GetXaxis()->SetTitleOffset(1.1);
   H2->GetYaxis()->SetTitleOffset(1.2);

   TCanvas C("C", "C", 1024, 1024);
   C.SetLogz();

   H1->Draw("colz");
   C.SaveAs("HcalNoise-2012BaselinePackage-R451.png");
   C.SaveAs("HcalNoise-2012BaselinePackage-R451.C");
   C.SaveAs("HcalNoise-2012BaselinePackage-R451.eps");
   C.SaveAs("HcalNoise-2012BaselinePackage-R451.pdf");

   H2->Draw("colz");
   C.SaveAs("HcalNoise-2012BaselinePackage-R452.png");
   C.SaveAs("HcalNoise-2012BaselinePackage-R452.C");
   C.SaveAs("HcalNoise-2012BaselinePackage-R452.eps");
   C.SaveAs("HcalNoise-2012BaselinePackage-R452.pdf");

   F2.Close();
   F1.Close();

   return 0;
}




