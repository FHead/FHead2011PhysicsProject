{
   TFile FBad("AnalyzeBadEEPF.root");
   TFile FGood("AnalyzeGoodEEPF.root");

   TGraphErrors *G1 = (TGraphErrors *)FBad.Get("Resolution_HRVsAbsEta_PT75_PT100");
   TGraphErrors *G2 = (TGraphErrors *)FBad.Get("Resolution_HCRVsAbsEta_PT75_PT100");
   TGraphErrors *G3 = (TGraphErrors *)FGood.Get("Resolution_HRVsAbsEta_PT75_PT100");

   TH2D HWorld("HWorld", ";|#eta|;RMS/Mean", 100, 0, 2.5, 100, 0, 0.2);
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
}
