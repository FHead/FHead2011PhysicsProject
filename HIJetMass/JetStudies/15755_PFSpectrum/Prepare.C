{
   int Bin = 1;

   TFile File1("Output.root");
   TFile File2("Output2.root");
   
   TFile File4("Output4.root");
   TFile File5("Output5.root");

   TFile File0("../../SubtractionStudies/15755_MinBiasSpectrumFlavor/HydjetMBDragos_0.root");

   TH1D *HN1 = (TH1D *)File1.Get("HNPF");
   TH1D *HJ11 = (TH1D *)File1.Get("HJetPF1");
   TH1D *HJ12 = (TH1D *)File1.Get("HJetPF2");
   TH1D *HJ13 = (TH1D *)File1.Get("HJetPF3");
   TH1D *HJ14 = (TH1D *)File1.Get("HJetPF4");
   TH1D *HJ15 = (TH1D *)File1.Get("HJetPF5");
   TH1D *HA11 = (TH1D *)File1.Get("HAddedPF1");
   TH1D *HA12 = (TH1D *)File1.Get("HAddedPF2");
   TH1D *HA13 = (TH1D *)File1.Get("HAddedPF3");
   TH1D *HA14 = (TH1D *)File1.Get("HAddedPF4");
   TH1D *HA15 = (TH1D *)File1.Get("HAddedPF5");
   TH1D *HN2 = (TH1D *)File2.Get("HNPF");
   TH1D *HJ21 = (TH1D *)File2.Get("HJetPF1");
   TH1D *HJ22 = (TH1D *)File2.Get("HJetPF2");
   TH1D *HJ23 = (TH1D *)File2.Get("HJetPF3");
   TH1D *HJ24 = (TH1D *)File2.Get("HJetPF4");
   TH1D *HJ25 = (TH1D *)File2.Get("HJetPF5");

   HJ11->Scale(1.0 / HN1->GetEntries());
   HJ12->Scale(1.0 / HN1->GetEntries());
   HJ13->Scale(1.0 / HN1->GetEntries());
   HJ14->Scale(1.0 / HN1->GetEntries());
   HJ15->Scale(1.0 / HN1->GetEntries());
   HA11->Scale(1.0 / HN1->GetEntries());
   HA12->Scale(1.0 / HN1->GetEntries());
   HA13->Scale(1.0 / HN1->GetEntries());
   HA14->Scale(1.0 / HN1->GetEntries());
   HA15->Scale(1.0 / HN1->GetEntries());
   HJ21->Scale(1.0 / HN2->GetEntries());
   HJ22->Scale(1.0 / HN2->GetEntries());
   HJ23->Scale(1.0 / HN2->GetEntries());
   HJ24->Scale(1.0 / HN2->GetEntries());
   HJ25->Scale(1.0 / HN2->GetEntries());

   // HJ21->Add(HJ11, -1);
   // HJ22->Add(HJ12, -1);
   // HJ23->Add(HJ13, -1);
   // HJ24->Add(HJ14, -1);
   // HJ25->Add(HJ15, -1);

   HJ11->Rebin(Bin);
   HJ12->Rebin(Bin);
   HJ13->Rebin(Bin);
   HJ14->Rebin(Bin);
   HJ15->Rebin(Bin);
   HA11->Rebin(Bin);
   HA12->Rebin(Bin);
   HA13->Rebin(Bin);
   HA14->Rebin(Bin);
   HA15->Rebin(Bin);
   HJ21->Rebin(Bin);
   HJ22->Rebin(Bin);
   HJ23->Rebin(Bin);
   HJ24->Rebin(Bin);
   HJ25->Rebin(Bin);

   HJ245 = (TH1D *)HJ24->Clone("HJ245");
   HJ245->Add(HJ25);
   
   HJ145 = (TH1D *)HJ14->Clone("HJ145");
   HJ145->Add(HJ15);

   HJ21->SetLineColor(kRed);
   HJ24->SetLineColor(kBlue);
   HJ25->SetLineColor(kGreen + 3);
   HJ245->SetLineColor(kBlack);

   HJ11->SetLineColor(kRed);
   HJ14->SetLineColor(kBlue);
   HJ15->SetLineColor(kGreen + 3);
   HJ145->SetLineColor(kBlack);

   HJ11->SetLineStyle(kDashed);
   HJ14->SetLineStyle(kDashed);
   HJ15->SetLineStyle(kDashed);
   HJ145->SetLineStyle(kDashed);

   HJ21->SetStats(0);
   
   HJ11->Scale(HJ21->Integral(61, 1000) / HJ11->Integral(61, 1000));
   HJ12->Scale(HJ22->Integral(61, 1000) / HJ12->Integral(61, 1000));
   HJ13->Scale(HJ23->Integral(61, 1000) / HJ13->Integral(61, 1000));
   HJ14->Scale(HJ24->Integral(61, 1000) / HJ14->Integral(61, 1000));
   HJ15->Scale(HJ25->Integral(61, 1000) / HJ15->Integral(61, 1000));
   HJ145->Scale(HJ245->Integral(61, 1000) / HJ145->Integral(61, 1000));

   TH2D HWorld("HWorld", ";PT;a.u.", 100, 0, 12, 100, 0.0004, 20);
   HWorld.SetStats(0);

   HWorld.Draw();

   HJ21->Draw("same");
   HJ24->Draw("same");
   HJ25->Draw("same");
   HJ245->Draw("same");
   
   HJ11->Draw("same");
   HJ14->Draw("same");
   HJ15->Draw("same");
   HJ145->Draw("same");

   TTree *T = (TTree *)File0.Get("Tree");

   TH1D A("A", "", 1000, 0, 100);
   TH1D B("B", "", 1000, 0, 100);
   TH1D C("C", "", 1000, 0, 100);
   TH1D BC("BC", "", 1000, 0, 100);

   Tree->Draw("PT>>A", "Rho < 50 && abs(Eta) < 50 && Flavor == 1", "same");
   Tree->Draw("PT>>B", "Rho < 50 && abs(Eta) < 50 && Flavor == 4", "same");
   Tree->Draw("PT>>C", "Rho < 50 && abs(Eta) < 50 && Flavor == 5", "same");
   Tree->Draw("PT>>BC", "Rho < 50 && abs(Eta) < 50 && (Flavor == 4 || Flavor == 5)", "same");

   A.Rebin(Bin);
   B.Rebin(Bin);
   C.Rebin(Bin);
   BC.Rebin(Bin);
   
   A.SetLineColor(kRed);
   B.SetLineColor(kBlue);
   C.SetLineColor(kGreen + 3);
   BC.SetLineColor(kBlack);

   A.SetLineWidth(2);
   B.SetLineWidth(2);
   C.SetLineWidth(2);
   BC.SetLineWidth(2);

   A.Scale(HJ21->Integral() / A.Integral());
   B.Scale(HJ24->Integral() / B.Integral());
   C.Scale(HJ25->Integral() / C.Integral());
   // BC.Scale(HJ245->Integral(60/Bin, 1000/Bin) / BC.Integral(60/Bin, 1000/Bin));
   BC.Scale(HJ245->Integral() / BC.Integral());

   TLegend Legend(0.5, 0.8, 0.8, 0.5);
   Legend.SetTextSize(0.035);
   Legend.SetTextFont(42);
   Legend.AddEntry(&A, "Charged hadron", "l");
   Legend.AddEntry(&B, "Neutral EM", "l");
   Legend.AddEntry(&C, "Neutral hadron", "l");
   Legend.AddEntry(&BC, "All neutrals", "l");
   Legend.Draw();

   c1->SetLogy();
   c1->SaveAs("Meow.pdf");

   HWorld.Draw();
   HJ21->Draw("same");
   HJ11->Draw("same");
   A.Draw("same");
   c1->SaveAs("Meow1.pdf");

   HWorld.Draw();
   HJ24->Draw("same");
   HJ14->Draw("same");
   B.Draw("same");
   c1->SaveAs("Meow4.pdf");

   HWorld.Draw();
   HJ25->Draw("same");
   HJ15->Draw("same");
   C.Draw("same");
   c1->SaveAs("Meow5.pdf");

   HWorld.Draw();
   HJ245->Draw("same");
   HJ145->Draw("same");
   BC.Draw("same");
   c1->SaveAs("Meow45.pdf");
}


