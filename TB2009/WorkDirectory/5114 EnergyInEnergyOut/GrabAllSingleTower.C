{
   TCanvas c1;

   TFile F108532("TotalEnergySingleTower_108532.root");
   TH2D *H108532 = (TH2D *)F108532.Get("TotalCharge");

   TFile F108533("TotalEnergySingleTower_108533.root");
   TH2D *H108533 = (TH2D *)F108533.Get("TotalCharge");

   TFile F108535("TotalEnergySingleTower_108535.root");
   TH2D *H108535 = (TH2D *)F108535.Get("TotalCharge");

   TFile F108537("TotalEnergySingleTower_108537.root");
   TH2D *H108537 = (TH2D *)F108537.Get("TotalCharge");

   TFile F108538("TotalEnergySingleTower_108538.root");
   TH2D *H108538 = (TH2D *)F108538.Get("TotalCharge");

   TFile F108540("TotalEnergySingleTower_108540.root");
   TH2D *H108540 = (TH2D *)F108540.Get("TotalCharge");

   TFile F108541("TotalEnergySingleTower_108541.root");
   TH2D *H108541 = (TH2D *)F108541.Get("TotalCharge");

   double energy[] = {300, 225, 150, 50, 30, 100, 100};
   double mean[] = {H108532->GetMean(), H108533->GetMean(), H108535->GetMean(), H108537->GetMean(),
      H108538->GetMean(), H108540->GetMean(), H108541->GetMean()};
   double rms[] = {H108532->GetRMS(), H108533->GetRMS(), H108535->GetRMS(), H108537->GetRMS(),
      H108538->GetRMS(), H108540->GetRMS(), H108541->GetRMS()};
   TGraphErrors gr(7, energy, mean, 0, 0);

   gr->SetTitle("Total energy deposited in central tower");
   gr->GetXaxis()->SetTitle("Energy of incoming particle (Gev)");
   gr->GetXaxis()->SetRangeUser(0, 350);
   gr->GetYaxis()->SetTitle("Energy deposited (MIP)");
   gr->GetYaxis()->SetRangeUser(0, 1400);
   gr->SetMarkerStyle(8);
   gr->Draw("ap");

   c1->Print("EnergySingleTower.png");
}





