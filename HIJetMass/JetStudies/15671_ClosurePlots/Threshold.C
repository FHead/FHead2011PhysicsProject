{
   TH1D H1("H1", ";Reconstructed sub-jet DR;Zg threshold", 10000, 0, 0.4);
   TH1D H2("H2", ";Reconstructed sub-jet DR;Zg threshold", 10000, 0, 0.4);

   for(int i = 1; i <= 10000; i++)
   {
      double X = H1.GetXaxis()->GetBinCenter(i);

      double Y1 = 0.1;
      double Y2 = 0.5 * pow(X / 0.4, 1.5);

      H1.SetBinContent(i, Y1);
      H2.SetBinContent(i, Y2);
   }

   H2.SetLineColor(kRed);

   H1.SetStats(0);

   H1.SetMinimum(0);
   H1.SetMaximum(0.6);

   H1.SetLineWidth(2);
   H2.SetLineWidth(2);

   H1.Draw();
   H2.Draw("same");

   TLegend Legend(0.2, 0.8, 0.5, 0.6);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&H1, "z_{cut} = 0.1, #beta = 0.0", "l");
   Legend.AddEntry(&H2, "z_{cut} = 0.5, #beta = 1.5", "l");
   Legend.Draw();
}
