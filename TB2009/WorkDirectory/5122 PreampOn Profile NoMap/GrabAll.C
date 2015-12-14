{
   TFile F108532("TotalEnergy_108532.root");
   TH1D *H108532 = (TH1D *)F108532.Get("CentralTowerChargeLayer");

   TFile F108533("TotalEnergy_108533.root");
   TH1D *H108533 = (TH1D *)F108533.Get("CentralTowerChargeLayer");

   TFile F108535("TotalEnergy_108535.root");
   TH1D *H108535 = (TH1D *)F108535.Get("CentralTowerChargeLayer");

   TFile F108537("TotalEnergy_108537.root");
   TH1D *H108537 = (TH1D *)F108537.Get("CentralTowerChargeLayer");

   TFile F108538("TotalEnergy_108538.root");
   TH1D *H108538 = (TH1D *)F108538.Get("CentralTowerChargeLayer");

   TFile F108540("TotalEnergy_108540.root");
   TH1D *H108540 = (TH1D *)F108540.Get("CentralTowerChargeLayer");

   TFile F108541("TotalEnergy_108541.root");
   TH1D *H108541 = (TH1D *)F108541.Get("CentralTowerChargeLayer");

   H108532->SetTitle("Pion longitudinal profiles (without ADC map)");
   H108532->GetXaxis()->SetTitle("Layer");
   H108532->GetYaxis()->SetTitle("Energy (MIP)");
   H108532->SetStats(0);
   H108532->SetLineColor(1);
   H108532->SetLineWidth(2);
   H108532->Draw();
   std::cout << "300 GeV: " << H108532->Integral() << std::endl;

   H108533->SetLineColor(2);
   H108533->SetLineWidth(2);
   H108533->Draw("same");
   std::cout << "225 GeV: " << H108533->Integral() << std::endl;

   H108535->SetLineColor(3);
   H108535->SetLineWidth(2);
   H108535->Draw("same");
   std::cout << "150 GeV: " << H108535->Integral() << std::endl;

   H108537->SetLineColor(4);
   H108537->SetLineWidth(2);
   H108537->Draw("same");
   std::cout << " 50 GeV: " << H108537->Integral() << std::endl;

   H108538->SetLineColor(5);
   H108538->SetLineWidth(2);
   H108538->Draw("same");
   std::cout << " 30 GeV: " << H108538->Integral() << std::endl;

   H108540->SetLineColor(6);
   H108540->SetLineWidth(2);
   H108540->Draw("same");
   std::cout << "100 GeV: " << H108540->Integral() << std::endl;

   H108541->SetLineColor(7);
   H108541->SetLineWidth(2);
   H108541->Draw("same");
   std::cout << "100 GeV: " << H108541->Integral() << std::endl;

   TLegend legend(0.66, 0.6, 0.92, 0.92);
   legend->AddEntry(H108532, "108532, 300 GeV");
   legend->AddEntry(H108533, "108533, 225 GeV");
   legend->AddEntry(H108535, "108535, 150 GeV");
   legend->AddEntry(H108540, "108540, 100 GeV");
   legend->AddEntry(H108541, "108541, 100 GeV");
   legend->AddEntry(H108537, "108537, 50 GeV");
   legend->AddEntry(H108538, "108538, 30 GeV");
   legend.Draw();

   c1->SaveAs("Overlay_nomap.C");
   c1->SaveAs("Overlay_nomap.png");
}
