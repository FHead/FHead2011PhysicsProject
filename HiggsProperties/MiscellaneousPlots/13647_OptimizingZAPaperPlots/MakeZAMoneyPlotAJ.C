{
   // Hgg numbers will be taken from ECFA workshop
   // http://indico.cern.ch/event/252045/session/3/contribution/8/material/slides/0.pdf

   TFile File("AllGraphs.root");
   TGraph *A2AA_A = (TGraph *)File.Get("A2ZA_Both_I_Count_FloatA2A3");
   TGraph *A3AA_A = (TGraph *)File.Get("A3ZA_Both_I_Count_FloatA2A3");
   TGraph *A2AA_J = (TGraph *)File.Get("A2ZA_Both_H_Count_FloatA2A3");
   TGraph *A3AA_J = (TGraph *)File.Get("A3ZA_Both_H_Count_FloatA2A3");

   double EfficiencyA = 0.727693;
   double EfficiencyJ = 0.743760;

   // gROOT->Macro("SetAlias.C");

   double EDMSize = 4.97686 * 0.000001;
   // double EDMSize = 0.0005;

   double MuMin = 0.78;
   double MuMax = 1.22;

   double P1 = 0.6827;
   double R1 = sqrt(-2 * log(1 - P1));
   double P2 = 0.9528;
   double R2 = sqrt(-2 * log(1 - P2));

   double AxisSize[] = {0.040, 0.040, 0.040, 0.040, 0.040, 0.040, 0.040, 0.040, 0.040, 0.040, 0.040, 0.040};
   // int EventCount[] = {50, 100, 200, 400, 800, 1600, 3200, 6400, 12800, 25600, 51200, 102400};
   for(int i = 0; i < 10; i++)
   {
      double EventCount = 0;
      double MeanX = 0.014, MeanY = 0, SigmaX_A, SigmaY_A, SigmaX_J, SigmaY_J;

      A2AA_A.GetPoint(i, EventCount, SigmaX_A);
      A3AA_A.GetPoint(i, EventCount, SigmaY_A);
      A2AA_J.GetPoint(i, EventCount, SigmaX_J);
      A3AA_J.GetPoint(i, EventCount, SigmaY_J);

      cout << EventCount << " " << SigmaX_A / SigmaX_J * SigmaY_A / SigmaY_J << endl;

      SigmaX_A = SigmaX_A * sqrt(EfficiencyJ / EfficiencyA);
      SigmaY_A = SigmaY_A * sqrt(EfficiencyJ / EfficiencyA);

      TCanvas C(Form("C%d", i), "C", 1024, 1024);

      TH2D HWorld(Form("HWorld%d", i), ";A_{2}^{Z#gamma};A_{3}^{Z#gamma}",
         100, -AxisSize[i], AxisSize[i] * 1.4, 100, -AxisSize[i], AxisSize[i] * 1.4);
      HWorld.SetStats(0);
      HWorld.Draw();

      TEllipse EMuMax(0, 0, 0.014 * MuMax);
      EMuMax.SetLineColor(kMagenta + 2);
      EMuMax.SetFillColor(kMagenta - 9);
      EMuMax.Draw("l");
      
      TEllipse EMuMin(0, 0, 0.014 * MuMin);
      EMuMin.SetLineColor(kMagenta + 2);
      EMuMin.Draw("l");
      
      TGraph GEDM;
      GEDM.SetPoint(0, -1000, EDMSize);
      GEDM.SetPoint(1, 1000, EDMSize);
      GEDM.SetPoint(2, 1000, -EDMSize);
      GEDM.SetPoint(3, -1000, -EDMSize);
      GEDM.SetLineColor(kGreen + 3);
      GEDM.SetFillColor(kGreen - 9);
      // GEDM.Draw("f");
      
      TGraph Ellipse1, Ellipse2;
      for(int j = 0; j <= 1000; j++)
      {
         double Angle = j * 2 * 3.14159265358979323846 / 1000;
         Ellipse1.SetPoint(j, MeanX + SigmaX_J * cos(Angle) * R1, MeanY + SigmaY_J * sin(Angle) * R1);
         Ellipse2.SetPoint(j, MeanX + SigmaX_A * cos(Angle) * R1, MeanY + SigmaY_A * sin(Angle) * R1);
      }
      Ellipse1.SetLineColor(kCyan + 2);
      Ellipse1.SetFillColor(kCyan - 7);
      Ellipse2.SetLineColor(kCyan - 3);
      Ellipse2.SetFillColor(kCyan - 9);
      Ellipse2.Draw("f");
      Ellipse1.Draw("f");
      Ellipse1.Draw("l");
      Ellipse2.Draw("l");

      TGraph GSM;
      GSM.SetPoint(0, 0.014, 0);
      GSM.SetMarkerStyle(30);
      GSM.SetMarkerSize(2);
      GSM.Draw("p");

      TEllipse EMuMaxLine(0, 0, 0.014 * MuMax);
      EMuMaxLine.SetLineColor(kMagenta + 2);
      EMuMaxLine.SetFillStyle(0);
      EMuMaxLine.Draw("l");

      TEllipse EMuMinLine(0, 0, 0.014 * MuMin);
      EMuMinLine.SetLineColor(kMagenta + 2);
      EMuMinLine.SetFillStyle(0);
      EMuMinLine.Draw("l");

      // GEDM.Draw("l");

      HWorld.Draw("axis same");

      TLegend Legend(0.15, 0.85, 0.45, 0.65);
      // Legend.SetFillStyle(0);
      Legend.SetFillColor(kWhite);
      Legend.SetTextFont(42);
      Legend.SetBorderSize(0);
      Legend.AddEntry(&Ellipse1, "Golden channel fits (Relaxed)", "fl");
      Legend.AddEntry(&Ellipse2, "Golden channel fits (CMS - tight)", "fl");
      // Legend.AddEntry(&GEDM, "Electric dipole moment", "fl");
      Legend.AddEntry(&EMuMax, "H #rightarrow Z#gamma", "fl");
      Legend.AddEntry(&GSM, "Standard model", "p");
      Legend.Draw();
      
      C.SaveAs(Form("ZAContours/ContourIJ_%05d.png", (int)EventCount));
      C.SaveAs(Form("ZAContours/ContourIJ_%05d.C",   (int)EventCount));
      C.SaveAs(Form("ZAContours/ContourIJ_%05d.eps", (int)EventCount));
      C.SaveAs(Form("ZAContours/ContourIJ_%05d.pdf", (int)EventCount));
   }
}
