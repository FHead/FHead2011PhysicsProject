{
   TFile F108269("TotalEnergy_108269.root");
   TH1D *H108269 = (TH1D *)F108269.Get("CentralTowerChargeLayer");

   TFile F108273("TotalEnergy_108273.root");
   TH1D *H108273 = (TH1D *)F108273.Get("CentralTowerChargeLayer");

   TFile F108278("TotalEnergy_108278.root");
   TH1D *H108278 = (TH1D *)F108278.Get("CentralTowerChargeLayer");

   TFile F108281("TotalEnergy_108281.root");
   TH1D *H108281 = (TH1D *)F108281.Get("CentralTowerChargeLayer");

   TFile F108284("TotalEnergy_108284.root");
   TH1D *H108284 = (TH1D *)F108284.Get("CentralTowerChargeLayer");

   TFile F108287("TotalEnergy_108287.root");
   TH1D *H108287 = (TH1D *)F108287.Get("CentralTowerChargeLayer");

   TFile F108289("TotalEnergy_108289.root");
   TH1D *H108289 = (TH1D *)F108289.Get("CentralTowerChargeLayer");

   TFile F108291("TotalEnergy_108291.root");
   TH1D *H108291 = (TH1D *)F108291.Get("CentralTowerChargeLayer");

   TFile F108292("TotalEnergy_108292.root");
   TH1D *H108292 = (TH1D *)F108292.Get("CentralTowerChargeLayer");

   H108269->SetTitle("Pion longitudinal profiles (preamp off)");
   H108269->GetXaxis()->SetTitle("Layer");
   H108269->GetYaxis()->SetTitle("Energy (MIP)");
   H108269->GetYaxis()->SetRangeUser(0, 220);
   H108269->SetStats(0);
   H108269->SetLineColor(1);
   H108269->SetLineWidth(2);
   H108269->Draw();
   std::cout << "300 GeV: " << H108269->Integral() << std::endl;

   H108273->SetLineColor(2);
   H108273->SetLineWidth(2);
   H108273->Draw("same");
   std::cout << "300 GeV: " << H108273->Integral() << std::endl;

   H108278->SetLineColor(3);
   H108278->SetLineWidth(2);
   H108278->Draw("same");
   std::cout << "300 GeV: " << H108278->Integral() << std::endl;

   H108281->SetLineColor(4);
   H108281->SetLineWidth(2);
   H108281->Draw("same");
   std::cout << "300 GeV: " << H108281->Integral() << std::endl;

   H108284->SetLineColor(5);
   H108284->SetLineWidth(2);
   H108284->Draw("same");
   std::cout << "300 GeV: " << H108284->Integral() << std::endl;

   H108287->SetLineColor(6);
   H108287->SetLineWidth(2);
   H108287->Draw("same");
   std::cout << "300 GeV: " << H108287->Integral() << std::endl;

   H108289->SetLineColor(7);
   H108289->SetLineWidth(2);
   H108289->Draw("same");
   std::cout << "300 GeV: " << H108289->Integral() << std::endl;

   H108291->SetLineColor(8);
   H108291->SetLineWidth(2);
   H108291->Draw("same");
   std::cout << "300 GeV: " << H108291->Integral() << std::endl;

   H108292->SetLineColor(9);
   H108292->SetLineWidth(2);
   H108292->Draw("same");
   std::cout << "150 GeV: " << H108292->Integral() << std::endl;

   TLegend legend(0.66, 0.6, 0.92, 0.92);
   legend->AddEntry(H108269, "108269, 300 GeV");
   legend->AddEntry(H108273, "108273, 300 GeV");
   legend->AddEntry(H108278, "108278, 300 GeV");
   legend->AddEntry(H108281, "108281, 300 GeV");
   legend->AddEntry(H108284, "108284, 300 GeV");
   legend->AddEntry(H108287, "108287, 300 GeV");
   legend->AddEntry(H108289, "108289, 300 GeV");
   legend->AddEntry(H108291, "108291, 300 GeV");
   legend->AddEntry(H108292, "108292, 150 GeV");
   legend.Draw();

   c1->SaveAs("Overlay.C");
   c1->SaveAs("Overlay.png");
}
