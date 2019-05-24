{
   TCanvas Canvas;

   Tree->SetLineWidth(2);

   Tree->SetLineColor(kRed);
   Tree->Draw("abs(MuonDxy)>>A", "L1Dxy == 0");

   Tree->SetLineColor(kBlue);
   Tree->Draw("abs(MuonDxy)>>B", "L1Dxy > 0", "same");

   A->SetStats(0);
   A->SetTitle("");
   A->GetXaxis()->SetTitle("|Gen Dxy|");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.03);
   Latex.SetNDC();
   Latex.DrawLatex(0.10, 0.92, "#color[2]{L1 Dxy = 0} #color[4]{L1 Dxy > 0}");

   Canvas.SetLogy();
}

