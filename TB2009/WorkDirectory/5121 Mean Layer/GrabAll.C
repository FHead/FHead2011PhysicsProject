{
   TCanvas c1;

   TFile F108532("MaxLayer_108532.root");
   TH1D *H108532 = (TH1D *)F108532.Get("MeanLayerHistogram_0");

   TFile F108533("MaxLayer_108533.root");
   TH1D *H108533 = (TH1D *)F108533.Get("MeanLayerHistogram_0");

   TFile F108535("MaxLayer_108535.root");
   TH1D *H108535 = (TH1D *)F108535.Get("MeanLayerHistogram_0");

   TFile F108537("MaxLayer_108537.root");
   TH1D *H108537 = (TH1D *)F108537.Get("MeanLayerHistogram_0");

   TFile F108538("MaxLayer_108538.root");
   TH1D *H108538 = (TH1D *)F108538.Get("MeanLayerHistogram_0");

   TFile F108540("MaxLayer_108540.root");
   TH1D *H108540 = (TH1D *)F108540.Get("MeanLayerHistogram_0");

   TFile F108541("MaxLayer_108541.root");
   TH1D *H108541 = (TH1D *)F108541.Get("MeanLayerHistogram_0");

   H108532->SetTitle("Mean layer of events (motherboard 0)");
   H108532->GetXaxis()->SetTitle("Layer");
   H108532->SetStats(0);
   H108532->SetLineColor(1);
   H108532->Scale(1.0 / H108532->Integral());
   H108532->Draw();

   H108533->SetLineColor(2);
   H108533->Scale(1.0 / H108533->Integral());
   H108533->Draw("same");

   H108535->SetLineColor(3);
   H108535->Scale(1.0 / H108535->Integral());
   H108535->Draw("same");

   H108537->SetLineColor(4);
   H108537->Scale(1.0 / H108537->Integral());
   H108537->Draw("same");

   H108538->SetLineColor(5);
   H108538->Scale(1.0 / H108538->Integral());
   H108538->Draw("same");

   H108540->SetLineColor(6);
   H108540->Scale(1.0 / H108540->Integral());
   H108540->Draw("same");

   H108541->SetLineColor(7);
   H108541->Scale(1.0 / H108541->Integral());
   H108541->Draw("same");

   TLegend leg(0.6, 0.6, 0.9, 0.9);
   leg->AddEntry(H108532, "108532, -300 GeV");
   leg->AddEntry(H108533, "108533, -225 GeV");
   leg->AddEntry(H108535, "108535, -150 GeV");
   leg->AddEntry(H108537, "108537, -50 GeV");
   leg->AddEntry(H108538, "108538, -30 GeV");
   leg->AddEntry(H108540, "108540, -100 GeV");
   leg->AddEntry(H108541, "108541, -100 GeV");
   leg->Draw();

   c1->Print("Mean distribution.png");

   double energy[] = {300, 225, 150, 50, 30, 100, 100};
   double mean[] = {6.81625, 6.69292, 6.48053, 5.73813, 5.43523, 6.23434, 6.21581};
   TGraph gr(7, energy, mean);

   gr->SetTitle("Mean layer of energy deposition");
   gr->GetXaxis()->SetTitle("Energy (Gev)");
   gr->GetXaxis()->SetRangeUser(20, 350);
   gr->GetYaxis()->SetTitle("Mean Layer");
   gr->SetMarkerStyle(8);
   gr->Draw("ap");

   c1->Print("MeanLayerVsEnergy.png");

   c1->SetLogx();
   c1->Print("MeanLayerVsEnergy_log.png");
}





