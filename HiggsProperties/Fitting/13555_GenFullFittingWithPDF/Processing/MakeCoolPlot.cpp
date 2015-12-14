#include <iostream>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TCanvas.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   string Prefix = "Result_A1ZZ_A_";
   int N = 10;
   int SignalCount[] = {50, 100, 200, 400, 600, 1000, 2000, 4000, 7000, 10000};

   if(argc == 1)
   {
      cerr << "Usage: " << argv[0] << " Prefix" << endl;
      cerr << "   example: \"Result_A1ZZ_A_\"" << endl;
      return -1;
   }

   Prefix = argv[1];

   int BinCount = 100;
   double Bins[101] = {0};
   double Left = 30, Right = 14000;
   for(int i = 0; i <= BinCount; i++)
      Bins[i] = exp((log(Right) - log(Left)) / BinCount * i + log(Left));

   vector<TFile *> Files;
   for(int i = 0; i < N; i++)
      Files.push_back(new TFile(Form("Trees/%s%d.root", Prefix.c_str(), SignalCount[i])));

   TH2D HA2ZZ1("HA2ZZ1", ";N;A_{2}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA3ZZ1("HA3ZZ1", ";N;A_{3}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA4ZZ1("HA4ZZ1", ";N;A_{4}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA2ZA1("HA2ZA1", ";N;A_{2}^{Z#gamma}", BinCount, Bins, 100, -1, 1);
   TH2D HA3ZA1("HA3ZA1", ";N;A_{3}^{Z#gamma}", BinCount, Bins, 100, -1, 1);
   TH2D HA2AA1("HA2AA1", ";N;A_{2}^{#gamma#gamma}", BinCount, Bins, 100, -0.1, 0.1);
   TH2D HA3AA1("HA3AA1", ";N;A_{3}^{#gamma#gamma}", BinCount, Bins, 100, -0.1, 0.1);
   TH2D HFEM1("HFEM1", ";N;F_{em}", BinCount, Bins, 100, 0, 1);
   TH2D HFEE1("HFEE1", ";N;F_{ee}", BinCount, Bins, 100, 0, 1);
   TH2D HA2ZZ2("HA2ZZ2", ";N;A_{2}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA3ZZ2("HA3ZZ2", ";N;A_{3}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA4ZZ2("HA4ZZ2", ";N;A_{4}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA2ZA2("HA2ZA2", ";N;A_{2}^{Z#gamma}", BinCount, Bins, 100, -1, 1);
   TH2D HA3ZA2("HA3ZA2", ";N;A_{3}^{Z#gamma}", BinCount, Bins, 100, -1, 1);
   TH2D HA2AA2("HA2AA2", ";N;A_{2}^{#gamma#gamma}", BinCount, Bins, 100, -0.1, 0.1);
   TH2D HA3AA2("HA3AA2", ";N;A_{3}^{#gamma#gamma}", BinCount, Bins, 100, -0.1, 0.1);
   TH2D HFEM2("HFEM2", ";N;F_{em}", BinCount, Bins, 100, 0, 1);
   TH2D HFEE2("HFEE2", ";N;F_{ee}", BinCount, Bins, 100, 0, 1);
   
   TH2D HA2ZZTotal1("HA2ZZTotal1", ";N;A_{2}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA3ZZTotal1("HA3ZZTotal1", ";N;A_{3}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA4ZZTotal1("HA4ZZTotal1", ";N;A_{4}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA2ZATotal1("HA2ZATotal1", ";N;A_{2}^{Z#gamma}", BinCount, Bins, 100, -1, 1);
   TH2D HA3ZATotal1("HA3ZATotal1", ";N;A_{3}^{Z#gamma}", BinCount, Bins, 100, -1, 1);
   TH2D HA2AATotal1("HA2AATotal1", ";N;A_{2}^{#gamma#gamma}", BinCount, Bins, 100, -0.1, 0.1);
   TH2D HA3AATotal1("HA3AATotal1", ";N;A_{3}^{#gamma#gamma}", BinCount, Bins, 100, -0.1, 0.1);
   TH2D HFEMTotal1("HFEMTotal1", ";N;F_{em}", BinCount, Bins, 100, 0, 1);
   TH2D HFEETotal1("HFEETotal1", ";N;F_{ee}", BinCount, Bins, 100, 0, 1);
   TH2D HA2ZZTotal2("HA2ZZTotal2", ";N;A_{2}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA3ZZTotal2("HA3ZZTotal2", ";N;A_{3}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA4ZZTotal2("HA4ZZTotal2", ";N;A_{4}^{ZZ}", BinCount, Bins, 100, -5, 5);
   TH2D HA2ZATotal2("HA2ZATotal2", ";N;A_{2}^{Z#gamma}", BinCount, Bins, 100, -1, 1);
   TH2D HA3ZATotal2("HA3ZATotal2", ";N;A_{3}^{Z#gamma}", BinCount, Bins, 100, -1, 1);
   TH2D HA2AATotal2("HA2AATotal2", ";N;A_{2}^{#gamma#gamma}", BinCount, Bins, 100, -0.1, 0.1);
   TH2D HA3AATotal2("HA3AATotal2", ";N;A_{3}^{#gamma#gamma}", BinCount, Bins, 100, -0.1, 0.1);
   TH2D HFEMTotal2("HFEMTotal2", ";N;F_{em}", BinCount, Bins, 100, 0, 1);
   TH2D HFEETotal2("HFEETotal2", ";N;F_{ee}", BinCount, Bins, 100, 0, 1);

   HA2ZZTotal1.SetStats(0);
   HA3ZZTotal1.SetStats(0);
   HA4ZZTotal1.SetStats(0);
   HA2ZATotal1.SetStats(0);
   HA3ZATotal1.SetStats(0);
   HA2AATotal1.SetStats(0);
   HA3AATotal1.SetStats(0);
   HFEMTotal1.SetStats(0);
   HFEETotal1.SetStats(0);
   HA2ZZTotal2.SetStats(0);
   HA3ZZTotal2.SetStats(0);
   HA4ZZTotal2.SetStats(0);
   HA2ZATotal2.SetStats(0);
   HA3ZATotal2.SetStats(0);
   HA2AATotal2.SetStats(0);
   HA3AATotal2.SetStats(0);
   HFEMTotal2.SetStats(0);
   HFEETotal2.SetStats(0);

   TGraph G;
   G.SetPoint(0, 0, 0);
   G.SetPoint(1, 100000, 0);

   for(int i = 0; i < N; i++)
   {
      TTree *Tree = (TTree *)Files[i]->Get("ResultTree");

      Tree->Draw(Form("A2ZZA1ZZ*2:%d>>HA2ZZ1", SignalCount[i]), "A2ZZA1ZZError > 0 && Status == 3 && A4ZZA1ZZError == 0", "colz");
      Tree->Draw(Form("A3ZZA1ZZ*2:%d>>HA3ZZ1", SignalCount[i]), "A3ZZA1ZZError > 0 && Status == 3 && A4ZZA1ZZError == 0", "colz");
      Tree->Draw(Form("A4ZZA1ZZ*2:%d>>HA4ZZ1", SignalCount[i]), "A4ZZA1ZZError > 0 && Status == 3 && A4ZZA1ZZError == 0", "colz");
      Tree->Draw(Form("A2ZAA1ZZ*2:%d>>HA2ZA1", SignalCount[i]), "A2ZAA1ZZError > 0 && Status == 3 && A4ZZA1ZZError == 0", "colz");
      Tree->Draw(Form("A3ZAA1ZZ*2:%d>>HA3ZA1", SignalCount[i]), "A3ZAA1ZZError > 0 && Status == 3 && A4ZZA1ZZError == 0", "colz");
      Tree->Draw(Form("A2AAA1ZZ*2:%d>>HA2AA1", SignalCount[i]), "A2AAA1ZZError > 0 && Status == 3 && A4ZZA1ZZError == 0", "colz");
      Tree->Draw(Form("A3AAA1ZZ*2:%d>>HA3AA1", SignalCount[i]), "A3AAA1ZZError > 0 && Status == 3 && A4ZZA1ZZError == 0", "colz");
      Tree->Draw(Form("Fem:%d>>HFEM1", SignalCount[i]), "A2ZZA1ZZError > 0 && Status == 3 && A4ZZA1ZZError == 0", "colz");
      Tree->Draw(Form("Fee:%d>>HFEE1", SignalCount[i]), "A2ZZA1ZZError > 0 && Status == 3 && A4ZZA1ZZError == 0", "colz");
      Tree->Draw(Form("A2ZZA1ZZ*2:%d>>HA2ZZ2", SignalCount[i]), "A2ZZA1ZZError > 0 && Status == 3 && A4ZZA1ZZError > 0", "colz");
      Tree->Draw(Form("A3ZZA1ZZ*2:%d>>HA3ZZ2", SignalCount[i]), "A3ZZA1ZZError > 0 && Status == 3 && A4ZZA1ZZError > 0", "colz");
      Tree->Draw(Form("A4ZZA1ZZ*2:%d>>HA4ZZ2", SignalCount[i]), "A4ZZA1ZZError > 0 && Status == 3 && A4ZZA1ZZError > 0", "colz");
      Tree->Draw(Form("A2ZAA1ZZ*2:%d>>HA2ZA2", SignalCount[i]), "A2ZAA1ZZError > 0 && Status == 3 && A4ZZA1ZZError > 0", "colz");
      Tree->Draw(Form("A3ZAA1ZZ*2:%d>>HA3ZA2", SignalCount[i]), "A3ZAA1ZZError > 0 && Status == 3 && A4ZZA1ZZError > 0", "colz");
      Tree->Draw(Form("A2AAA1ZZ*2:%d>>HA2AA2", SignalCount[i]), "A2AAA1ZZError > 0 && Status == 3 && A4ZZA1ZZError > 0", "colz");
      Tree->Draw(Form("A3AAA1ZZ*2:%d>>HA3AA2", SignalCount[i]), "A3AAA1ZZError > 0 && Status == 3 && A4ZZA1ZZError > 0", "colz");
      Tree->Draw(Form("Fem:%d>>HFEM2", SignalCount[i]), "A2ZZA1ZZError > 0 && Status == 3 && A4ZZA1ZZError > 0", "colz");
      Tree->Draw(Form("Fee:%d>>HFEE2", SignalCount[i]), "A2ZZA1ZZError > 0 && Status == 3 && A4ZZA1ZZError > 0", "colz");

      HA2ZZTotal1.Add(&HA2ZZ1);
      HA3ZZTotal1.Add(&HA3ZZ1);
      HA4ZZTotal1.Add(&HA4ZZ1);
      HA2ZATotal1.Add(&HA2ZA1);
      HA3ZATotal1.Add(&HA3ZA1);
      HA2AATotal1.Add(&HA2AA1);
      HA3AATotal1.Add(&HA3AA1);
      HFEMTotal1.Add(&HFEM1);
      HFEETotal1.Add(&HFEE1);
      HA2ZZTotal2.Add(&HA2ZZ2);
      HA3ZZTotal2.Add(&HA3ZZ2);
      HA4ZZTotal2.Add(&HA4ZZ2);
      HA2ZATotal2.Add(&HA2ZA2);
      HA3ZATotal2.Add(&HA3ZA2);
      HA2AATotal2.Add(&HA2AA2);
      HA3AATotal2.Add(&HA3AA2);
      HFEMTotal2.Add(&HFEM2);
      HFEETotal2.Add(&HFEE2);
   }

   TCanvas C;
   C.SetLogx();
   C.SetLogz();

   HA2ZZTotal1.Draw("colz");
   G.Draw("l");
   C.SaveAs("A2ZZ-FixA4ZZ.png");
   C.SaveAs("A2ZZ-FixA4ZZ.C");
   C.SaveAs("A2ZZ-FixA4ZZ.eps");
   C.SaveAs("A2ZZ-FixA4ZZ.pdf");

   HA3ZZTotal1.Draw("colz");
   G.Draw("l");
   C.SaveAs("A3ZZ-FixA4ZZ.png");
   C.SaveAs("A3ZZ-FixA4ZZ.C");
   C.SaveAs("A3ZZ-FixA4ZZ.eps");
   C.SaveAs("A3ZZ-FixA4ZZ.pdf");

   HA4ZZTotal1.Draw("colz");
   G.Draw("l");
   C.SaveAs("A4ZZ-FixA4ZZ.png");
   C.SaveAs("A4ZZ-FixA4ZZ.C");
   C.SaveAs("A4ZZ-FixA4ZZ.eps");
   C.SaveAs("A4ZZ-FixA4ZZ.pdf");

   HA2ZATotal1.Draw("colz");
   G.Draw("l");
   C.SaveAs("A2ZA-FixA4ZZ.png");
   C.SaveAs("A2ZA-FixA4ZZ.C");
   C.SaveAs("A2ZA-FixA4ZZ.eps");
   C.SaveAs("A2ZA-FixA4ZZ.pdf");

   HA3ZATotal1.Draw("colz");
   G.Draw("l");
   C.SaveAs("A3ZA-FixA4ZZ.png");
   C.SaveAs("A3ZA-FixA4ZZ.C");
   C.SaveAs("A3ZA-FixA4ZZ.eps");
   C.SaveAs("A3ZA-FixA4ZZ.pdf");

   HA2AATotal1.Draw("colz");
   G.Draw("l");
   C.SaveAs("A2AA-FixA4ZZ.png");
   C.SaveAs("A2AA-FixA4ZZ.C");
   C.SaveAs("A2AA-FixA4ZZ.eps");
   C.SaveAs("A2AA-FixA4ZZ.pdf");

   HA3AATotal1.Draw("colz");
   G.Draw("l");
   C.SaveAs("A3AA-FixA4ZZ.png");
   C.SaveAs("A3AA-FixA4ZZ.C");
   C.SaveAs("A3AA-FixA4ZZ.eps");
   C.SaveAs("A3AA-FixA4ZZ.pdf");

   HFEMTotal1.Draw("colz");
   G.Draw("l");
   C.SaveAs("FEM-FixA4ZZ.png");
   C.SaveAs("FEM-FixA4ZZ.C");
   C.SaveAs("FEM-FixA4ZZ.eps");
   C.SaveAs("FEM-FixA4ZZ.pdf");

   HFEETotal1.Draw("colz");
   G.Draw("l");
   C.SaveAs("FEE-FixA4ZZ.png");
   C.SaveAs("FEE-FixA4ZZ.C");
   C.SaveAs("FEE-FixA4ZZ.eps");
   C.SaveAs("FEE-FixA4ZZ.pdf");

   HA2ZZTotal2.Draw("colz");
   G.Draw("l");
   C.SaveAs("A2ZZ-FloatA4ZZ.png");
   C.SaveAs("A2ZZ-FloatA4ZZ.C");
   C.SaveAs("A2ZZ-FloatA4ZZ.eps");
   C.SaveAs("A2ZZ-FloatA4ZZ.pdf");

   HA3ZZTotal2.Draw("colz");
   G.Draw("l");
   C.SaveAs("A3ZZ-FloatA4ZZ.png");
   C.SaveAs("A3ZZ-FloatA4ZZ.C");
   C.SaveAs("A3ZZ-FloatA4ZZ.eps");
   C.SaveAs("A3ZZ-FloatA4ZZ.pdf");

   HA4ZZTotal2.Draw("colz");
   G.Draw("l");
   C.SaveAs("A4ZZ-FloatA4ZZ.png");
   C.SaveAs("A4ZZ-FloatA4ZZ.C");
   C.SaveAs("A4ZZ-FloatA4ZZ.eps");
   C.SaveAs("A4ZZ-FloatA4ZZ.pdf");

   HA2ZATotal2.Draw("colz");
   G.Draw("l");
   C.SaveAs("A2ZA-FloatA4ZZ.png");
   C.SaveAs("A2ZA-FloatA4ZZ.C");
   C.SaveAs("A2ZA-FloatA4ZZ.eps");
   C.SaveAs("A2ZA-FloatA4ZZ.pdf");

   HA3ZATotal2.Draw("colz");
   G.Draw("l");
   C.SaveAs("A3ZA-FloatA4ZZ.png");
   C.SaveAs("A3ZA-FloatA4ZZ.C");
   C.SaveAs("A3ZA-FloatA4ZZ.eps");
   C.SaveAs("A3ZA-FloatA4ZZ.pdf");

   HA2AATotal2.Draw("colz");
   G.Draw("l");
   C.SaveAs("A2AA-FloatA4ZZ.png");
   C.SaveAs("A2AA-FloatA4ZZ.C");
   C.SaveAs("A2AA-FloatA4ZZ.eps");
   C.SaveAs("A2AA-FloatA4ZZ.pdf");

   HA3AATotal2.Draw("colz");
   G.Draw("l");
   C.SaveAs("A3AA-FloatA4ZZ.png");
   C.SaveAs("A3AA-FloatA4ZZ.C");
   C.SaveAs("A3AA-FloatA4ZZ.eps");
   C.SaveAs("A3AA-FloatA4ZZ.pdf");

   HFEMTotal2.Draw("colz");
   G.Draw("l");
   C.SaveAs("FEM-FloatA4ZZ.png");
   C.SaveAs("FEM-FloatA4ZZ.C");
   C.SaveAs("FEM-FloatA4ZZ.eps");
   C.SaveAs("FEM-FloatA4ZZ.pdf");

   HFEETotal2.Draw("colz");
   G.Draw("l");
   C.SaveAs("FEE-FloatA4ZZ.png");
   C.SaveAs("FEE-FloatA4ZZ.C");
   C.SaveAs("FEE-FloatA4ZZ.eps");
   C.SaveAs("FEE-FloatA4ZZ.pdf");

   return 0;
}



