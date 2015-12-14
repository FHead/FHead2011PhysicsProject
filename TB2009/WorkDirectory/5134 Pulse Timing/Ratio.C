{
   TFile pionfile("AlignPionTime.root");
   TH1D *pion = (TH1D *)pionfile.Get("AveragePulseShape");
   pion->SetLineWidth(2);
   pion->SetLineColor(kBlue);

   TFile muonfile("AlignMuonTime.root");
   TH1D *muon = (TH1D *)muonfile.Get("AveragePulseShape");
   muon->SetLineWidth(2);
   muon->SetLineColor(kRed);

   pion->GetXaxis()->SetRangeUser(-8, 21);

   // pion->Scale(1.0 / pion->Integral(22, 51));
   pion->Draw();
   // muon->Scale(1.0 / muon->Integral(22, 51));
   muon->Draw("same");

   // pion->Divide(muon);
   // pion->Draw();
}
