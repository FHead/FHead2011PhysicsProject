{
   TFile F1("AlignMuonTime.root");

   TH1D *H1 = (TH1D *)F1.Get("AveragePulseShape");

   for(int i = 0; i < 180; i++)
      cout << H1->GetBinCenter(i) << " " << H1->GetBinContent(i) << endl;
}

