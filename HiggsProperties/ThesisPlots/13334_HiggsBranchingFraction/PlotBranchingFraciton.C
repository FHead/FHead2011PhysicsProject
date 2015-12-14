{
   TFile F("BranchingRatio.root");
   TTree *T = (TTree *)F.Get("Tree");

   TH2D *HWorld = new TH2D("HWorld", ";m_{4l};Br(h->X)", 1000, 90, 1000, 1000, 1e-5, 100);
   HWorld->SetStats(0);

   HWorld->GetXaxis()->SetTitleOffset(1.1);
   HWorld->GetYaxis()->SetTitleOffset(1.2);

   TCanvas C("C", "C", 1024, 1024);

   HWorld->Draw();

   T->SetLineWidth(2);
   T->SetLineColor(kBlack);
   T->Draw("llll:M", "", "L same");
   T->SetLineColor(kBlue);
   T->Draw("llvv:M", "", "L same");
   T->SetLineColor(kRed);
   T->Draw("bb:M", "", "L same");
   T->SetLineColor(kGreen - 3);
   T->Draw("tt:M", "", "L same");
   T->SetLineColor(kYellow - 3);
   T->Draw("tautau:M", "", "L same");
   T->SetLineColor(kCyan + 3);
   T->Draw("llqq+qqqq+lvqq*2:M", "", "L same");
   
   TH1D *H1 = new TH1D("H1", "", 1, 0, 1);   H1->SetLineWidth(2), H1->SetLineColor(kBlack);
   TH1D *H2 = new TH1D("H2", "", 1, 0, 1);   H2->SetLineWidth(2), H2->SetLineColor(kBlue);
   TH1D *H3 = new TH1D("H3", "", 1, 0, 1);   H3->SetLineWidth(2), H3->SetLineColor(kRed);
   TH1D *H4 = new TH1D("H4", "", 1, 0, 1);   H4->SetLineWidth(2), H4->SetLineColor(kGreen - 3);
   TH1D *H5 = new TH1D("H5", "", 1, 0, 1);   H5->SetLineWidth(2), H5->SetLineColor(kYellow - 3);
   TH1D *H6 = new TH1D("H6", "", 1, 0, 1);   H6->SetLineWidth(2), H6->SetLineColor(kCyan + 3);

   TLegend Legend1(0.42, 0.68, 0.71, 0.88);
   Legend1.SetFillStyle(0);
   Legend1.SetTextFont(42);
   Legend1.SetBorderSize(0);
   Legend1.SetTextSize(0.032);
   Legend1.AddEntry(H4, "tt", "l");
   Legend1.AddEntry(H5, "#tau#tau", "l");
   Legend1.AddEntry(H3, "bb", "l");
   Legend1.Draw();
   
   TLegend Legend2(0.57, 0.68, 0.87, 0.88);
   Legend2.SetFillStyle(0);
   Legend2.SetTextFont(42);
   Legend2.SetBorderSize(0);
   Legend2.AddEntry(H1, "4l", "l");
   Legend2.AddEntry(H2, "2l2#nu", "l");
   Legend2.AddEntry(H6, "2l2q+l#nuqq+qqqq", "l");
   Legend2.Draw();

   C.SetLogx();
   C.SetLogy();

   C.SaveAs("SMAndHiggs-Decays-BranchingFraction.png");
   C.SaveAs("SMAndHiggs-Decays-BranchingFraction.C");
   C.SaveAs("SMAndHiggs-Decays-BranchingFraction.eps");
   C.SaveAs("SMAndHiggs-Decays-BranchingFraction.pdf");
}
