{
   TFile F108532("TotalEnergy_Interpolated_108532.root");
   TH1D *H108532 = (TH1D *)F108532.Get("CentralTowerChargeLayer");

   TFile F108533("TotalEnergy_Interpolated_108533.root");
   TH1D *H108533 = (TH1D *)F108533.Get("CentralTowerChargeLayer");

   TFile F108535("TotalEnergy_Interpolated_108535.root");
   TH1D *H108535 = (TH1D *)F108535.Get("CentralTowerChargeLayer");

   TFile F108537("TotalEnergy_Interpolated_108537.root");
   TH1D *H108537 = (TH1D *)F108537.Get("CentralTowerChargeLayer");

   TFile F108538("TotalEnergy_Interpolated_108538.root");
   TH1D *H108538 = (TH1D *)F108538.Get("CentralTowerChargeLayer");

   TFile F108540("TotalEnergy_Interpolated_108540.root");
   TH1D *H108540 = (TH1D *)F108540.Get("CentralTowerChargeLayer");

   TFile F108541("TotalEnergy_Interpolated_108541.root");
   TH1D *H108541 = (TH1D *)F108541.Get("CentralTowerChargeLayer");

   std::cout << "300 GeV: " << H108532->Integral() << std::endl;
   std::cout << "225 GeV: " << H108533->Integral() << std::endl;
   std::cout << "150 GeV: " << H108535->Integral() << std::endl;
   std::cout << "100 GeV: " << H108540->Integral() << std::endl;
   std::cout << "100 GeV: " << H108541->Integral() << std::endl;
   std::cout << " 50 GeV: " << H108537->Integral() << std::endl;
   std::cout << " 30 GeV: " << H108538->Integral() << std::endl;
}
