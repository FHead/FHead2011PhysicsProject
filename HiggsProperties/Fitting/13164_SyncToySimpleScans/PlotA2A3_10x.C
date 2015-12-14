{
   TFile F("A2A34DScan10x.root");
   TTree *Tree = (TTree *)F.Get("ResultTree");

   TCanvas C("C", "C", 1024, 1024);

   TH2D HReal("HReal", ";f_{a3};f_{a2}", 80, -1, 1, 80, -1, 1);
   TH2D HReal2("HReal2", ";f_{a3};f_{a2}", 80, -1, 1, 80, -1, 1);
   Tree->Draw("FA2*cos(A2ZZPhase):FA3*cos(A3ZZPhase)>>HReal", "(abs(FA3*sin(A3ZZPhase)) < 0.001 && abs(FA2*sin(A2ZZPhase)) < 0.001) * (BestNLL / 10 + 16.5)", "colz");
   Tree->Draw("FA2*cos(A2ZZPhase):-FA3*cos(A3ZZPhase)>>HReal2", "(abs(FA3*sin(A3ZZPhase)) < 0.001 && abs(FA2*sin(A2ZZPhase)) < 0.001) * (BestNLL / 10 + 16.5)", "colz");
   // HReal.Add(&HReal2);
   // HReal.Scale(0.5);
   // for(int i = 1; i <= 80; i++)
   //    HReal.SetBinContent(i, 40, HReal.GetBinContent(i, 40) / 20);
   // for(int i = 1; i <= 80; i++)
   //    HReal.SetBinContent(40, i, HReal.GetBinContent(40, i) / 20);
   // HReal.SetBinContent(40, 40, HReal.GetBinContent(40, 40) / 400 * 20 * 20);
   HReal.SetStats(0);
   HReal.Draw("colz");
   HReal.SetMaximum(30);
   C.SaveAs("A2A3RealScan.png");
   C.SaveAs("A2A3RealScan.C");
   C.SaveAs("A2A3RealScan.eps");
   C.SaveAs("A2A3RealScan.pdf");

   TH2D HProfiled("HProfiled", ";f_{a2};f_{a3}", 40, 0, 1, 40, 0, 1);
   Tree->Draw("FA2:FA3>>HProfiled", "Min$(BestNLL/305+16.5-1007.425)", "colz");
   HProfiled.SetStats(0);
   C.SaveAs("A2A3ProfileScan.png");
   C.SaveAs("A2A3ProfileScan.C");
   C.SaveAs("A2A3ProfileScan.eps");
   C.SaveAs("A2A3ProfileScan.pdf");
   
   TH2D HProfiled2("HProfiled2", ";f_{a3};f_{a2}", 40, 0, 1, 40, 0, 1);
   for(int i = 1; i <= 40; i++)
      for(int j = 1; j <= 40; j++)
         HProfiled2.SetBinContent(i, j, 99999);
   float A2, A3, BestNLL;
   Tree.SetBranchAddress("A2ZZA1ZZ", &A2);
   Tree.SetBranchAddress("A3ZZA1ZZ", &A3);
   Tree.SetBranchAddress("BestNLL", &BestNLL);
   int EntryCount = Tree.GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree.GetEntry(i);

      double S2 = A2 * A2 / 3.276 / 3.276;
      double S3 = A3 * A3 / 5.042 / 5.042;
      double FA2 = S2 / (1 + S2 + S3);
      double FA3 = S3 / (1 + S2 + S3);

      int BinX = HProfiled2.GetXaxis()->FindBin(FA3);
      int BinY = HProfiled2.GetYaxis()->FindBin(FA2);
      if(HProfiled2.GetBinContent(BinX, BinY) > BestNLL / 10)
         HProfiled2.SetBinContent(BinX, BinY, BestNLL / 10);
   }
   double Offset = HProfiled2.GetBinContent(1, 1);
   for(int i = 1; i <= 40; i++)
      for(int j = 1; j <= 40; j++)
         HProfiled2.SetBinContent(i, j, HProfiled2.GetBinContent(i, j) - Offset + 0.3);
   HProfiled2.SetStats(0);
   HProfiled2.SetMinimum(0);
   HProfiled2.SetMaximum(18);
   HProfiled2.Draw("colz");
   C.SaveAs("A2A3ProfileScan2.png");
   C.SaveAs("A2A3ProfileScan2.C");
   C.SaveAs("A2A3ProfileScan2.eps");
   C.SaveAs("A2A3ProfileScan2.pdf");

   TH1D HWorld("HWorld", ";f;", 100, -1, 1);
   HWorld.SetStats(0);
   HWorld.SetMinimum(0);

   TGraph G1, G2;
   G1.SetPoint(0, -1, 1);
   G1.SetPoint(1, +1, 1);
   G2.SetPoint(0, -1, 4);
   G2.SetPoint(1, +1, 4);
   G1.SetLineStyle(kDashed);
   G2.SetLineStyle(kDashed);

   HWorld.SetMaximum(25);
   HWorld.Draw();
   Tree->Draw("BestNLL/10+16.5:FA2*cos(A2ZZPhase)", "abs(sin(A3ZZPhase)) < 0.001 && abs(sin(A2ZZPhase)) < 0.001 && abs(FA3) < 0.02", "same");
   G1.Draw("l");
   G2.Draw("l");
   C.SaveAs("FA2.png");
   C.SaveAs("FA2.C");
   C.SaveAs("FA2.eps");
   C.SaveAs("FA2.pdf");

   HWorld.SetMaximum(12);
   HWorld.Draw();
   Tree->Draw("BestNLL/10+16.5:FA3*cos(A3ZZPhase)", "abs(sin(A2ZZPhase)) < 0.001 && abs(sin(A3ZZPhase)) < 0.001 && abs(FA2) < 0.02", "same");
   G1.Draw("l");
   G2.Draw("l");
   C.SaveAs("FA3.png");
   C.SaveAs("FA3.C");
   C.SaveAs("FA3.eps");
   C.SaveAs("FA3.pdf");

   TFile F2("OldLikelihood.root");

   TH1D *HScanFA2_0_0 = (TH1D *)F2.Get("HScanFA2_0_0");
   TH1D *HScanFA3_0_0 = (TH1D *)F2.Get("HScanFA3_0_0");

   TH1D HWorld2("HWorld2", ";f;", 100, -1, 1);
   HWorld2.SetStats(0);
   HWorld2.SetMinimum(0);
   HWorld2.SetMaximum(25);
   HWorld2.Draw();
   HScanFA2_0_0->SetMarkerStyle(11);
   Offset = HScanFA2_0_0->GetMinimum();
   for(int i = 1; i <= HScanFA2_0_0->GetNbinsX(); i++)
      HScanFA2_0_0->SetBinContent(i, HScanFA2_0_0->GetBinContent(i) - Offset);
   HScanFA2_0_0->Draw("same");
   G1.Draw("l");
   G2.Draw("l");
   C.SaveAs("FA2Old.png");
   C.SaveAs("FA2Old.C");
   C.SaveAs("FA2Old.eps");
   C.SaveAs("FA2Old.pdf");

   HWorld2.SetMaximum(12);
   HWorld2.Draw();
   HScanFA3_0_0->SetMarkerStyle(11);
   Offset = HScanFA3_0_0->GetMinimum();
   for(int i = 1; i <= HScanFA3_0_0->GetNbinsX(); i++)
      HScanFA3_0_0->SetBinContent(i, HScanFA3_0_0->GetBinContent(i) - Offset);
   HScanFA3_0_0->Scale(1.0 / 150.0);
   HScanFA3_0_0->Draw("same");
   G1.Draw("l");
   G2.Draw("l");
   C.SaveAs("FA3Old.png");
   C.SaveAs("FA3Old.C");
   C.SaveAs("FA3Old.eps");
   C.SaveAs("FA3Old.pdf");

   TFile F3("LikelihoodFile_FA2Scan_lumi300.root");
   TH1D *HSi = (TH1D *)F3.Get("HScanFA2");
   HWorld2.SetMaximum(25);
   HWorld2.Draw();
   HScanFA2->Draw("same");
   G1.Draw("l");
   G2.Draw("l");
   C.SaveAs("FA2Si.png");
   C.SaveAs("FA2Si.C");
   C.SaveAs("FA2Si.eps");
   C.SaveAs("FA2Si.pdf");
}



