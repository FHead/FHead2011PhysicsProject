{
   TGraphErrors G1, G2;

   TFile F1("Meow.root");
   TH2D *HSubtractedPTCentrality = (TH2D *)F1.Get("HSubtractedPTCentrality");
   for(int i = 1; i <= 100; i++)
   {
      double RMS = HSubtractedPTCentrality->ProjectionY(Form("X%d", i), i, i)->GetRMS();
      double RMSError = HSubtractedPTCentrality->ProjectionY(Form("X%d", i), i, i)->GetRMSError();
      G1.SetPoint(i - 1, i, RMS);
      G1.SetPointError(i - 1, 0, RMSError);
   }
   F1.Close();

   TFile F2("../15472_RandomConeCheck/OldCombinedResult/AAData.root");
   HSubtractedPTCentrality = (TH2D *)F2.Get("HSubtractedPTCentrality");
   for(int i = 1; i <= 100; i++)
   {
      double RMS = HSubtractedPTCentrality->ProjectionY(Form("X%d", i), i, i)->GetRMS();
      double RMSError = HSubtractedPTCentrality->ProjectionY(Form("X%d", i), i, i)->GetRMSError();
      G2.SetPoint(i - 1, i, RMS);
      G2.SetPointError(i - 1, 0, RMSError);
   }
   F2.Close();

   TCanvas C1;

   G1.Draw("ap");
   G2.Draw("p");

   G1.GetXaxis()->SetTitle("Centrality");
   G1.GetYaxis()->SetTitle("RMS");

   G2.SetLineColor(kRed);
   G2.SetMarkerColor(kRed);

   TLegend Legend(0.2, 0.2, 0.5, 0.35);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&G1, "Fixed", "pl");
   Legend.AddEntry(&G2, "Original", "pl");
   Legend.Draw();

   C1.SaveAs("AADataRMSComparison.png");
   C1.SaveAs("AADataRMSComparison.C");
   C1.SaveAs("AADataRMSComparison.eps");
   C1.SaveAs("AADataRMSComparison.pdf");

   TCanvas C2;

   TGraph G;
   for(int i = 0; i < 100; i++)
   {
      double x, y1, y2;
      G1.GetPoint(i, x, y1);
      G2.GetPoint(i, x, y2);
      G.SetPoint(i, x, y2 / y1 - 1);
   }

   TH2D HWorld("HWorld", ";Centrality;Original / Fixed - 1", 100, 0, 100, 100, -1, 1);
   HWorld.SetStats(0);
   HWorld.Draw();

   G.Draw("p");

   TGraph GLine;
   GLine.SetPoint(0, 0, 0);
   GLine.SetPoint(1, 100000, 0);
   GLine.Draw("l");

   C2.SaveAs("AADataRMSRatio.png");
   C2.SaveAs("AADataRMSRatio.C");
   C2.SaveAs("AADataRMSRatio.eps");
   C2.SaveAs("AADataRMSRatio.pdf");
}
