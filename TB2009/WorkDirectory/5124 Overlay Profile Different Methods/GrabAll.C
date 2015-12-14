{
   TFile F1("ADCMapProfile.root");
   TFile F2("OriginalProfile.root");
   TFile F3("ScaledMIP.root");
   TFile F4("MaxADCMapProfile.root");
   TFile F5("BiasedProfile.root");
   TFile F6("PreampOff.root");

   TH1D *H1 = (TH1D *)F1.Get("CentralTowerChargeLayer");
   H1->SetStats(0);
   H1->SetTitle("Profiles of 300 GeV run");
   H1->GetYaxis()->SetTitle("Energy (MIP)");
   H1->SetLineWidth(2);
   H1->SetLineColor(1);
   H1->Draw();

   TH1D *H2 = (TH1D *)F2.Get("CentralTowerChargeLayer");
   H2->SetLineWidth(2);
   H2->SetLineColor(2);
   H2->Draw("same");

   TH1D *H3 = (TH1D *)F3.Get("CentralTowerChargeLayer");
   H3->SetLineWidth(2);
   H3->SetLineColor(3);
   H3->Draw("same");

   TH1D *H4 = (TH1D *)F4.Get("CentralTowerChargeLayer");
   H4->SetLineWidth(2);
   H4->SetLineColor(4);
   H4->Draw("same");

   TH1D *H5 = (TH1D *)F5.Get("CentralTowerChargeLayer");
   H5->SetLineWidth(2);
   H5->SetLineColor(5);
   H5->Draw("same");

   TH1D *H6 = (TH1D *)F6.Get("CentralTowerChargeLayer");
   H6->SetLineWidth(2);
   H6->SetLineColor(6);
   H6->Draw("same");

   TLegend legend(0.55, 0.7, 0.92, 0.92);
   legend.AddEntry(H1, "Adc mapping");
   legend.AddEntry(H2, "Original");
   legend.AddEntry(H3, "Preamp off data with scaled MIP");
   legend.AddEntry(H4, "Max adc mapping");
   legend.AddEntry(H5, "Max adc cut at 12600");
   legend.Draw();
}
