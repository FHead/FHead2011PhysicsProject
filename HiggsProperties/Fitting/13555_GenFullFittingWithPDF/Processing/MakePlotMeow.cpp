#include <cmath>
#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

#define PI 3.1415926535897932384626433832795028847971693993751058209749445923078164062862089986280348253421170679

int main()
{
   SetThesisStyle();

   int N = 10;
   int Counts[] = {50, 100, 200, 400, 600, 1000, 2000, 4000, 7000, 10000};

   double Efficiencies[9] = {0.727693, 0.590503, 0.590509, 0.797016, 0.759701, 0.999653, 0.799547, 0.797664, 0.601295};
   int Color[9] = {kBlack, kRed, kBlue, kGreen - 3, kCyan, kYellow, kYellow - 3, kGreen, 6};
   string Labels[9] = {"A", "B", "C", "A+B+C", "A+B+C-#Upsilon", "Full", "A'", "Full'", "A_{0}"};

   TGraphErrors GA2ZZ[9], GA2ZZNoEfficiency[9];
   TGraphErrors GA3ZZ[9], GA3ZZNoEfficiency[9];
   TGraphErrors GA2ZA[9], GA2ZANoEfficiency[9];
   TGraphErrors GA3ZA[9], GA3ZANoEfficiency[9];
   TGraphErrors GA2AA[9], GA2AANoEfficiency[9];
   TGraphErrors GA3AA[9], GA3AANoEfficiency[9];

   for(int i = 0; i < 9; i++)
   {
      for(int j = 0; j < N; j++)
      {
         int Index = 0;

         TFile File(Form("Trees/ResultBothS_A1ZZ_%c_%d.root", 'A' + i, Counts[j]));

         TTree *Tree = (TTree *)File.Get("ResultTree");
         if(Tree == NULL)
            continue;

         TH1D H("H", "", 100, -100, 100);

         Tree->Draw("abs(A2ZZA1ZZ)*2>>H", "A2ZZA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
         Index = GA2ZZ[i].GetN();
         GA2ZZ[i].SetPoint(Index, Counts[j]*2 / Efficiencies[i], H.GetMean() * sqrt(PI / 2));
         GA2ZZ[i].SetPointError(Index, 0, H.GetMeanError() * sqrt(PI / 2));
         GA2ZZNoEfficiency[i].SetPoint(Index, Counts[j]*2, H.GetMean() * sqrt(PI / 2));
         GA2ZZNoEfficiency[i].SetPointError(Index, 0, H.GetMeanError() * sqrt(PI / 2));

         Tree->Draw("abs(A3ZZA1ZZ)*2>>H", "A3ZZA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
         Index = GA3ZZ[i].GetN();
         GA3ZZ[i].SetPoint(Index, Counts[j]*2 / Efficiencies[i], H.GetMean() * sqrt(PI / 2));
         GA3ZZ[i].SetPointError(Index, 0, H.GetMeanError() * sqrt(PI / 2));
         GA3ZZNoEfficiency[i].SetPoint(Index, Counts[j]*2, H.GetMean() * sqrt(PI / 2));
         GA3ZZNoEfficiency[i].SetPointError(Index, 0, H.GetMeanError() * sqrt(PI / 2));

         Tree->Draw("abs(A2ZAA1ZZ)*2>>H", "A2ZAA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
         Index = GA2ZA[i].GetN();
         GA2ZA[i].SetPoint(Index, Counts[j]*2 / Efficiencies[i], H.GetMean() * sqrt(PI / 2));
         GA2ZA[i].SetPointError(Index, 0, H.GetMeanError() * sqrt(PI / 2));
         GA2ZANoEfficiency[i].SetPoint(Index, Counts[j]*2, H.GetMean() * sqrt(PI / 2));
         GA2ZANoEfficiency[i].SetPointError(Index, 0, H.GetMeanError() * sqrt(PI / 2));

         Tree->Draw("abs(A3ZAA1ZZ)*2>>H", "A3ZAA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
         Index = GA3ZA[i].GetN();
         GA3ZA[i].SetPoint(Index, Counts[j]*2 / Efficiencies[i], H.GetMean() * sqrt(PI / 2));
         GA3ZA[i].SetPointError(Index, 0, H.GetMeanError() * sqrt(PI / 2));
         GA3ZANoEfficiency[i].SetPoint(Index, Counts[j]*2, H.GetMean() * sqrt(PI / 2));
         GA3ZANoEfficiency[i].SetPointError(Index, 0, H.GetMeanError() * sqrt(PI / 2));

         Tree->Draw("abs(A2AAA1ZZ)*2>>H", "A2AAA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
         Index = GA2AA[i].GetN();
         GA2AA[i].SetPoint(Index, Counts[j]*2 / Efficiencies[i], H.GetMean() * sqrt(PI / 2));
         GA2AA[i].SetPointError(Index, 0, H.GetMeanError() * sqrt(PI / 2));
         GA2AANoEfficiency[i].SetPoint(Index, Counts[j]*2, H.GetMean() * sqrt(PI / 2));
         GA2AANoEfficiency[i].SetPointError(Index, 0, H.GetMeanError() * sqrt(PI / 2));

         Tree->Draw("abs(A3AAA1ZZ)*2>>H", "A3ZZA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
         Index = GA3AA[i].GetN();
         GA3AA[i].SetPoint(Index, Counts[j]*2 / Efficiencies[i], H.GetMean() * sqrt(PI / 2));
         GA3AA[i].SetPointError(Index, 0, H.GetMeanError() * sqrt(PI / 2));
         GA3AANoEfficiency[i].SetPoint(Index, Counts[j]*2, H.GetMean() * sqrt(PI / 2));
         GA3AANoEfficiency[i].SetPointError(Index, 0, H.GetMeanError() * sqrt(PI / 2));

         File.Close();
      }
   }

   TH2D HWorldA2ZZ("HWorldA2ZZ", ";N / #epsilon;#sigma(A_{2}^{ZZ})", 100, 30, 40000, 100, 0.04, 10);
   TH2D HWorldA3ZZ("HWorldA3ZZ", ";N / #epsilon;#sigma(A_{3}^{ZZ})", 100, 30, 40000, 100, 0.2, 10);
   TH2D HWorldA2ZA("HWorldA2ZA", ";N / #epsilon;#sigma(A_{2}^{ZA})", 100, 30, 40000, 100, 0.002, 0.6);
   TH2D HWorldA3ZA("HWorldA3ZA", ";N / #epsilon;#sigma(A_{3}^{ZA})", 100, 30, 40000, 100, 0.002, 0.6);
   TH2D HWorldA2AA("HWorldA2AA", ";N / #epsilon;#sigma(A_{2}^{AA})", 100, 30, 40000, 100, 0.0006, 0.6);
   TH2D HWorldA3AA("HWorldA3AA", ";N / #epsilon;#sigma(A_{3}^{AA})", 100, 30, 40000, 100, 0.0006, 0.6);
   TH2D HWorldA2ZZNoEfficiency("HWorldA2ZZNoEfficiency", ";N;#sigma(A_{2}^{ZZ})", 100, 30, 40000, 100, 0.04, 10);
   TH2D HWorldA3ZZNoEfficiency("HWorldA3ZZNoEfficiency", ";N;#sigma(A_{3}^{ZZ})", 100, 30, 40000, 100, 0.2, 10);
   TH2D HWorldA2ZANoEfficiency("HWorldA2ZANoEfficiency", ";N;#sigma(A_{2}^{ZA})", 100, 30, 40000, 100, 0.002, 0.6);
   TH2D HWorldA3ZANoEfficiency("HWorldA3ZANoEfficiency", ";N;#sigma(A_{3}^{ZA})", 100, 30, 40000, 100, 0.002, 0.6);
   TH2D HWorldA2AANoEfficiency("HWorldA2AANoEfficiency", ";N;#sigma(A_{2}^{AA})", 100, 30, 40000, 100, 0.0006, 0.6);
   TH2D HWorldA3AANoEfficiency("HWorldA3AANoEfficiency", ";N;#sigma(A_{3}^{AA})", 100, 30, 40000, 100, 0.0006, 0.6);
   HWorldA2ZZ.SetStats(0);
   HWorldA3ZZ.SetStats(0);
   HWorldA2ZA.SetStats(0);
   HWorldA3ZA.SetStats(0);
   HWorldA2AA.SetStats(0);
   HWorldA3AA.SetStats(0);
   HWorldA2ZZNoEfficiency.SetStats(0);
   HWorldA3ZZNoEfficiency.SetStats(0);
   HWorldA2ZANoEfficiency.SetStats(0);
   HWorldA3ZANoEfficiency.SetStats(0);
   HWorldA2AANoEfficiency.SetStats(0);
   HWorldA3AANoEfficiency.SetStats(0);

   TLegend Legend(0.55 / 1.05, 0.85, 0.85 / 1.05, 0.55);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);

   TCanvas C;
   C.SetLogx();
   C.SetLogy();
   
   HWorldA2ZZ.Draw();
   for(int i = 0; i < 9; i++)
   {
      GA2ZZ[i].SetLineWidth(2);
      GA2ZZ[i].SetLineColor(Color[i]);
      GA2ZZ[i].SetMarkerColor(Color[i]);
      GA2ZZ[i].Draw("pl");

      Legend.AddEntry(&GA2ZZ[i], Labels[i].c_str(), "pl");
   }
   Legend.Draw();
   C.SaveAs("A2ZZ.png");
   C.SaveAs("A2ZZ.C");
   C.SaveAs("A2ZZ.eps");
   C.SaveAs("A2ZZ.pdf");
   
   HWorldA2ZZNoEfficiency.Draw();
   for(int i = 0; i < 9; i++)
   {
      GA2ZZNoEfficiency[i].SetLineWidth(2);
      GA2ZZNoEfficiency[i].SetLineColor(Color[i]);
      GA2ZZNoEfficiency[i].SetMarkerColor(Color[i]);
      GA2ZZNoEfficiency[i].Draw("pl");
   }
   Legend.Draw();
   C.SaveAs("A2ZZNoEfficiency.png");
   C.SaveAs("A2ZZNoEfficiency.C");
   C.SaveAs("A2ZZNoEfficiency.eps");
   C.SaveAs("A2ZZNoEfficiency.pdf");
   
   HWorldA3ZZ.Draw();
   for(int i = 0; i < 9; i++)
   {
      GA3ZZ[i].SetLineWidth(2);
      GA3ZZ[i].SetLineColor(Color[i]);
      GA3ZZ[i].SetMarkerColor(Color[i]);
      GA3ZZ[i].Draw("pl");
   }
   Legend.Draw();
   C.SaveAs("A3ZZ.png");
   C.SaveAs("A3ZZ.C");
   C.SaveAs("A3ZZ.eps");
   C.SaveAs("A3ZZ.pdf");
   
   HWorldA3ZZNoEfficiency.Draw();
   for(int i = 0; i < 9; i++)
   {
      GA3ZZNoEfficiency[i].SetLineWidth(2);
      GA3ZZNoEfficiency[i].SetLineColor(Color[i]);
      GA3ZZNoEfficiency[i].SetMarkerColor(Color[i]);
      GA3ZZNoEfficiency[i].Draw("pl");
   }
   Legend.Draw();
   C.SaveAs("A3ZZNoEfficiency.png");
   C.SaveAs("A3ZZNoEfficiency.C");
   C.SaveAs("A3ZZNoEfficiency.eps");
   C.SaveAs("A3ZZNoEfficiency.pdf");
   
   HWorldA2ZA.Draw();
   for(int i = 0; i < 9; i++)
   {
      GA2ZA[i].SetLineWidth(2);
      GA2ZA[i].SetLineColor(Color[i]);
      GA2ZA[i].SetMarkerColor(Color[i]);
      GA2ZA[i].Draw("pl");
   }
   TGraph GLineA2ZA;
   GLineA2ZA.SetPoint(0, 0, 0.014);
   GLineA2ZA.SetPoint(1, 100000, 0.014);
   GLineA2ZA.Draw("l");
   Legend.Draw();
   C.SaveAs("A2ZA.png");
   C.SaveAs("A2ZA.C");
   C.SaveAs("A2ZA.eps");
   C.SaveAs("A2ZA.pdf");
   
   HWorldA2ZANoEfficiency.Draw();
   for(int i = 0; i < 9; i++)
   {
      GA2ZANoEfficiency[i].SetLineWidth(2);
      GA2ZANoEfficiency[i].SetLineColor(Color[i]);
      GA2ZANoEfficiency[i].SetMarkerColor(Color[i]);
      GA2ZANoEfficiency[i].Draw("pl");
   }
   Legend.Draw();
   GLineA2ZA.Draw("l");
   C.SaveAs("A2ZANoEfficiency.png");
   C.SaveAs("A2ZANoEfficiency.C");
   C.SaveAs("A2ZANoEfficiency.eps");
   C.SaveAs("A2ZANoEfficiency.pdf");
   
   HWorldA3ZA.Draw();
   for(int i = 0; i < 9; i++)
   {
      GA3ZA[i].SetLineWidth(2);
      GA3ZA[i].SetLineColor(Color[i]);
      GA3ZA[i].SetMarkerColor(Color[i]);
      GA3ZA[i].Draw("pl");
   }
   Legend.Draw();
   C.SaveAs("A3ZA.png");
   C.SaveAs("A3ZA.C");
   C.SaveAs("A3ZA.eps");
   C.SaveAs("A3ZA.pdf");
   
   HWorldA3ZANoEfficiency.Draw();
   for(int i = 0; i < 9; i++)
   {
      GA3ZANoEfficiency[i].SetLineWidth(2);
      GA3ZANoEfficiency[i].SetLineColor(Color[i]);
      GA3ZANoEfficiency[i].SetMarkerColor(Color[i]);
      GA3ZANoEfficiency[i].Draw("pl");
   }
   Legend.Draw();
   C.SaveAs("A3ZANoEfficiency.png");
   C.SaveAs("A3ZANoEfficiency.C");
   C.SaveAs("A3ZANoEfficiency.eps");
   C.SaveAs("A3ZANoEfficiency.pdf");
   
   HWorldA2AA.Draw();
   for(int i = 0; i < 9; i++)
   {
      GA2AA[i].SetLineWidth(2);
      GA2AA[i].SetLineColor(Color[i]);
      GA2AA[i].SetMarkerColor(Color[i]);
      GA2AA[i].Draw("pl");
   }
   TGraph GLineA2AA;
   GLineA2AA.SetPoint(0, 0, 0.008);
   GLineA2AA.SetPoint(1, 100000, 0.008);
   GLineA2AA.Draw("l");
   Legend.Draw();
   C.SaveAs("A2AA.png");
   C.SaveAs("A2AA.C");
   C.SaveAs("A2AA.eps");
   C.SaveAs("A2AA.pdf");
   
   HWorldA2AANoEfficiency.Draw();
   for(int i = 0; i < 9; i++)
   {
      GA2AANoEfficiency[i].SetLineWidth(2);
      GA2AANoEfficiency[i].SetLineColor(Color[i]);
      GA2AANoEfficiency[i].SetMarkerColor(Color[i]);
      GA2AANoEfficiency[i].Draw("pl");
   }
   GLineA2AA.Draw("l");
   Legend.Draw();
   C.SaveAs("A2AANoEfficiency.png");
   C.SaveAs("A2AANoEfficiency.C");
   C.SaveAs("A2AANoEfficiency.eps");
   C.SaveAs("A2AANoEfficiency.pdf");
   
   HWorldA3AA.Draw();
   for(int i = 0; i < 9; i++)
   {
      GA3AA[i].SetLineWidth(2);
      GA3AA[i].SetLineColor(Color[i]);
      GA3AA[i].SetMarkerColor(Color[i]);
      GA3AA[i].Draw("pl");
   }
   Legend.Draw();
   C.SaveAs("A3AA.png");
   C.SaveAs("A3AA.C");
   C.SaveAs("A3AA.eps");
   C.SaveAs("A3AA.pdf");

   HWorldA3AANoEfficiency.Draw();
   for(int i = 0; i < 9; i++)
   {
      GA3AANoEfficiency[i].SetLineWidth(2);
      GA3AANoEfficiency[i].SetLineColor(Color[i]);
      GA3AANoEfficiency[i].SetMarkerColor(Color[i]);
      GA3AANoEfficiency[i].Draw("pl");
   }
   Legend.Draw();
   C.SaveAs("A3AANoEfficiency.png");
   C.SaveAs("A3AANoEfficiency.C");
   C.SaveAs("A3AANoEfficiency.eps");
   C.SaveAs("A3AANoEfficiency.pdf");

   return 0;
}



