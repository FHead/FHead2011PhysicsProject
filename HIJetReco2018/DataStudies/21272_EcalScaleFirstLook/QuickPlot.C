{
   // TFile F1("ResultBadEEPF.root");
   // TFile F2("TestRun.root");
   TFile F1("TestRunBad.root");
   TFile F2("TestRunGood.root");

   TProfile *P1 = (TProfile *)F1.Get("PRVsAbsEta_PT75_PT100");
   TProfile *P2 = (TProfile *)F2.Get("PRVsAbsEta_PT75_PT100");
   TProfile *P3 = (TProfile *)F1.Get("PCRVsAbsEta_PT75_PT100");

   P1->Rebin(2);
   P2->Rebin(2);
   P3->Rebin(2);

   TH2D HWorld("HWorld", ";eta;response", 100, 0.0, 2.5, 100, 0.5, 1.5);
   HWorld.SetStats(0);

   HWorld.Draw("axis");

   P1->SetLineColor(kRed);
   P1->SetMarkerColor(kRed);

   P3->SetLineColor(kGreen);
   P3->SetMarkerColor(kGreen);

   P1->SetLineWidth(2);
   P2->SetLineWidth(2);
   P3->SetLineWidth(2);

   P1->Draw("same");
   P2->Draw("same");
   P3->Draw("same");

   TLegend Legend(0.4, 0.8, 0.7, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(P1, "Bad EE", "pl");
   Legend.AddEntry(P2, "Good EE", "lp");
   Legend.AddEntry(P3, "Bad EE + correction", "pl");
   Legend.Draw();
}
