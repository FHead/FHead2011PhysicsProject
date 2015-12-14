{
   TFile F2("EnergyFraction2_ABC_MinEnergy_108532.root");
   TH1D *H2 = (TH1D *)F2.Get("FractionEnergy");

   TFile F3("EnergyFraction3_ABC_MinEnergy_108532.root");
   TH1D *H3 = (TH1D *)F3.Get("FractionEnergy");

   TFile F4("EnergyFraction4_ABC_MinEnergy_108532.root");
   TH1D *H4 = (TH1D *)F4.Get("FractionEnergy");

   TFile F5("EnergyFraction5_ABC_MinEnergy_108532.root");
   TH1D *H5 = (TH1D *)F5.Get("FractionEnergy");

   TFile F6("EnergyFraction6_ABC_MinEnergy_108532.root");
   TH1D *H6 = (TH1D *)F6.Get("FractionEnergy");

   TFile F7("EnergyFraction7_ABC_MinEnergy_108532.root");
   TH1D *H7 = (TH1D *)F7.Get("FractionEnergy");

   TFile F8("EnergyFraction8_ABC_MinEnergy_108532.root");
   TH1D *H8 = (TH1D *)F8.Get("FractionEnergy");

   TFile F9("EnergyFraction9_ABC_MinEnergy_108532.root");
   TH1D *H9 = (TH1D *)F9.Get("FractionEnergy");

   TFile F10("EnergyFraction10_ABC_MinEnergy_108532.root");
   TH1D *H10 = (TH1D *)F10.Get("FractionEnergy");

   TFile F11("EnergyFraction11_ABC_MinEnergy_108532.root");
   TH1D *H11 = (TH1D *)F11.Get("FractionEnergy");

   TFile F12("EnergyFraction12_ABC_MinEnergy_108532.root");
   TH1D *H12 = (TH1D *)F12.Get("FractionEnergy");

   TFile F13("EnergyFraction13_ABC_MinEnergy_108532.root");
   TH1D *H13 = (TH1D *)F13.Get("FractionEnergy");

   TFile F14("EnergyFraction14_ABC_MinEnergy_108532.root");
   TH1D *H14 = (TH1D *)F14.Get("FractionEnergy");

   H2->SetTitle("Fractional energies");
   H2->SetStats(0);
   H2->SetLineWidth(2);
   H2->SetLineColor(2);
   H2->Draw();

   H3->SetLineWidth(2);
   H3->SetLineColor(3);
   H3->Draw("same");

   H4->SetLineWidth(2);
   H4->SetLineColor(4);
   H4->Draw("same");

   H5->SetLineWidth(2);
   H5->SetLineColor(5);
   H5->Draw("same");

   H6->SetLineWidth(2);
   H6->SetLineColor(6);
   H6->Draw("same");

   H7->SetLineWidth(2);
   H7->SetLineColor(7);
   H7->Draw("same");

   H8->SetLineWidth(2);
   H8->SetLineColor(8);
   H8->Draw("same");

   H9->SetLineWidth(2);
   H9->SetLineColor(9);
   H9->Draw("same");

   H10->SetLineStyle(kDashed);
   H10->SetLineWidth(2);
   H10->SetLineColor(1);
   H10->Draw("same");

   H11->SetLineStyle(kDashed);
   H11->SetLineWidth(2);
   H11->SetLineColor(2);
   H11->Draw("same");

   H12->SetLineStyle(kDashed);
   H12->SetLineWidth(2);
   H12->SetLineColor(3);
   H12->Draw("same");

   H13->SetLineStyle(kDashed);
   H13->SetLineWidth(2);
   H13->SetLineColor(4);
   H13->Draw("same");

   H14->SetLineStyle(kDashed);
   H14->SetLineWidth(2);
   H14->SetLineColor(5);
   H14->Draw("same");

   TLegend legend(0.7, 0.7, 0.9, 0.9);
   legend.AddEntry(H2, "E(2-15)/Total");
   legend.AddEntry(H3, "E(3-15)/Total");
   legend.AddEntry(H4, "E(4-15)/Total");
   legend.AddEntry(H5, "E(5-15)/Total");
   legend.AddEntry(H6, "E(6-15)/Total");
   legend.AddEntry(H7, "E(7-15)/Total");
   legend.AddEntry(H8, "E(8-15)/Total");
   legend.AddEntry(H9, "E(9-15)/Total");
   legend.AddEntry(H10, "E(10-15)/Total");
   legend.AddEntry(H11, "E(11-15)/Total");
   legend.AddEntry(H12, "E(12-15)/Total");
   legend.AddEntry(H13, "E(13-15)/Total");
   legend.AddEntry(H14, "E(14-15)/Total");
   legend.Draw();

   c1->SetLogy();
}
