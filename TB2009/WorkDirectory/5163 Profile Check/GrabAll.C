{
   const int MotherBoard = 0;   // 0, 1, 3

   TFile F108532("TotalEnergy_108532.root");
   TH2D *H108532a = (TH2D *)F108532.Get("AverageChargeLayer");
   TH1D *H108532 = H108532a->ProjectionY("H108532", MotherBoard + 1, MotherBoard + 1);

   TFile F108533("TotalEnergy_108533.root");
   TH2D *H108533a = (TH2D *)F108533.Get("AverageChargeLayer");
   TH1D *H108533 = H108533a->ProjectionY("H108533", MotherBoard + 1, MotherBoard + 1);

   TFile F108535("TotalEnergy_108535.root");
   TH2D *H108535a = (TH2D *)F108535.Get("AverageChargeLayer");
   TH1D *H108535 = H108535a->ProjectionY("H108535", MotherBoard + 1, MotherBoard + 1);

   TFile F108537("TotalEnergy_108537.root");
   TH2D *H108537a = (TH2D *)F108537.Get("AverageChargeLayer");
   TH1D *H108537 = H108537a->ProjectionY("H108537", MotherBoard + 1, MotherBoard + 1);

   TFile F108538("TotalEnergy_108538.root");
   TH2D *H108538a = (TH2D *)F108538.Get("AverageChargeLayer");
   TH1D *H108538 = H108538a->ProjectionY("H108538", MotherBoard + 1, MotherBoard + 1);

   TFile F108540("TotalEnergy_108540.root");
   TH2D *H108540a = (TH2D *)F108540.Get("AverageChargeLayer");
   TH1D *H108540 = H108540a->ProjectionY("H108540", MotherBoard + 1, MotherBoard + 1);

   TFile F108541("TotalEnergy_108541.root");
   TH2D *H108541a = (TH2D *)F108541.Get("AverageChargeLayer");
   TH1D *H108541 = H108541a->ProjectionY("H108541", MotherBoard + 1, MotherBoard + 1);

   H108532->SetTitle("Pion longitudinal profiles (without ADC map)");
   H108532->GetXaxis()->SetTitle("Layer");
   H108532->GetYaxis()->SetTitle("Energy (MIP)");
   // H108532->GetYaxis()->SetRangeUser(0, 8);

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

   c1->SaveAs(Form("Overlay_%d.C", MotherBoard));
   c1->SaveAs(Form("Overlay_%d.png", MotherBoard));
}
