{
   TFile FBad("AnalyzeBadEECalo.root");
   TFile FGood("AnalyzeGoodEECalo.root");

   TGraphErrors *G1 = (TGraphErrors *)FBad.Get("Resolution_HRVsAbsEta_PT50_PT100");
   TGraphErrors *G2 = (TGraphErrors *)FBad.Get("Resolution_HCRVsAbsEta_PT50_PT100");
   TGraphErrors *G3 = (TGraphErrors *)FGood.Get("Resolution_HRVsAbsEta_PT50_PT100");

   TH2D HWorld("HWorld", ";|#eta|;#sigma / #mu", 100, 0.0, 2.5, 100, 0, 0.25);
   HWorld.SetStats(0);

   HWorld.Draw("axis");

   G1->SetLineColor(kRed);
   G2->SetLineColor(kGreen);
   G3->SetLineColor(kBlack);
   G1->SetMarkerColor(kRed);
   G2->SetMarkerColor(kGreen);
   G3->SetMarkerColor(kBlack);

   G1->Draw("p");
   G2->Draw("p");
   G3->Draw("p");

   TLegend Legend(0.4, 0.8, 0.7, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(G1, "Bad EE", "pl");
   Legend.AddEntry(G3, "Good EE", "pl");
   Legend.AddEntry(G2, "Bad EE + correction", "pl");
   Legend.Draw();
}
