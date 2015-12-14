{
   TFile f("mip_108303.root");

   int layerToChannel[16];
   for(int i = 0; i < 15; i++)
      layerToChannel[i+1] = i;
   layerToChannel[0] = 15;

   for(int i = 0; i < 16; i++)
   {
      TH1D *H = (TH1D *)f.Get(Form("ChargeDistribution_0_%d", i));
      int maxbin = H->GetMaximumBin();
      double maxvalue = H->GetBinContent(maxbin);
      double maxpos = H->GetXaxis()->GetBinCenter(maxbin);
      double minvalue = maxvalue / 5;

      // note: use newer version of root to run this....
      int leftbin = H->FindFirstBinAbove(minvalue);
      double leftpos = H->GetXaxis()->GetBinCenter(leftbin);

      int rightbin = H->FindLastBinAbove(minvalue);
      double rightpos = H->GetXaxis()->GetBinCenter(rightbin);

      TF1 *function = new TF1("function", "gaus", leftpos, rightpos);
      H->Fit("function", "R");

      double center = function->GetParameter(1);

      std::cout << "[UseMaximum][Reference] 0 " << layerToChannel[i] << " " << maxpos << std::endl;
      std::cout << "[UseMaximum][Result] 0 " << layerToChannel[i] << " " << center << std::endl;
   }

   f.Close();
}
