{
   TFile F108532("CountSample_108532.root");
   TH1D *H108532 = (TH1D *)F108532.Get("MaxNumberOverThreshold");
   TGraph G108532(33);
   G108532.SetNameTitle("G108532", "Usable percentage of events if we exclude highest N samples in each channel;Number of samples;Percentage");
   for(int i = 1; i <= 33; i++)
      G108532.SetPoint(i - 1, i, H108532->Integral(1, i) / H108532->Integral());

   TFile F108533("CountSample_108533.root");
   TH1D *H108533 = (TH1D *)F108533.Get("MaxNumberOverThreshold");
   TGraph G108533(33);
   G108533.SetNameTitle("G108533", "G108533");
   for(int i = 1; i <= 33; i++)
      G108533.SetPoint(i - 1, i, H108533->Integral(1, i) / H108533->Integral());

   TFile F108535("CountSample_108535.root");
   TH1D *H108535 = (TH1D *)F108535.Get("MaxNumberOverThreshold");
   TGraph G108535(33);
   G108535.SetNameTitle("G108535", "G108535");
   for(int i = 1; i <= 33; i++)
      G108535.SetPoint(i - 1, i, H108535->Integral(1, i) / H108535->Integral());

   TFile F108537("CountSample_108537.root");
   TH1D *H108537 = (TH1D *)F108537.Get("MaxNumberOverThreshold");
   TGraph G108537(33);
   G108537.SetNameTitle("G108537", "G108537");
   for(int i = 1; i <= 33; i++)
      G108537.SetPoint(i - 1, i, H108537->Integral(1, i) / H108537->Integral());

   TFile F108538("CountSample_108538.root");
   TH1D *H108538 = (TH1D *)F108538.Get("MaxNumberOverThreshold");
   TGraph G108538(33);
   G108538.SetNameTitle("G108538", "G108538");
   for(int i = 1; i <= 33; i++)
      G108538.SetPoint(i - 1, i, H108538->Integral(1, i) / H108538->Integral());

   TFile F108540("CountSample_108540.root");
   TH1D *H108540 = (TH1D *)F108540.Get("MaxNumberOverThreshold");
   TGraph G108540(33);
   G108540.SetNameTitle("G108540", "G108540");
   for(int i = 1; i <= 33; i++)
      G108540.SetPoint(i - 1, i, H108540->Integral(1, i) / H108540->Integral());

   TFile F108541("CountSample_108541.root");
   TH1D *H108541 = (TH1D *)F108541.Get("MaxNumberOverThreshold");
   TGraph G108541(33);
   G108541.SetNameTitle("G108541", "G108541");
   for(int i = 1; i <= 33; i++)
      G108541.SetPoint(i - 1, i, H108541->Integral(1, i) / H108541->Integral());

   G108532.SetMarkerStyle(20);
   G108533.SetMarkerStyle(20);
   G108535.SetMarkerStyle(20);
   G108537.SetMarkerStyle(20);
   G108538.SetMarkerStyle(20);
   G108540.SetMarkerStyle(20);
   G108541.SetMarkerStyle(20);

   G108532.SetMarkerColor(1);
   G108533.SetMarkerColor(2);
   G108535.SetMarkerColor(3);
   G108537.SetMarkerColor(4);
   G108538.SetMarkerColor(5);
   G108540.SetMarkerColor(6);
   G108541.SetMarkerColor(6);

   G108532.Draw("ap");
   G108533.Draw("p");
   G108535.Draw("p");
   G108537.Draw("p");
   G108538.Draw("p");
   G108540.Draw("p");
   G108541.Draw("p");

   TLegend legend(0.6, 0.2, 0.9, 0.6);
   legend.AddEntry(&G108538, "108538, 30 GeV", "p");
   legend.AddEntry(&G108537, "108537, 50 GeV", "p");
   legend.AddEntry(&G108540, "108540, 100 GeV", "p");
   legend.AddEntry(&G108541, "108541, 100 GeV", "p");
   legend.AddEntry(&G108535, "108535, 150 GeV", "p");
   legend.AddEntry(&G108533, "108533, 225 GeV", "p");
   legend.AddEntry(&G108532, "108532, 300 GeV", "p");
   legend.Draw();
}


