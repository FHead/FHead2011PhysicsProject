{
   Tower->Draw("emEt>>A", "et > 0 && eta > 1.4 && eta < 1.5 && phi > -1.48 && phi < -0.96 && !(phi < -1.23 && phi > -1.30)", "");
   Tower->Draw("emEt>>B", "(et > 0 && eta > 1.4 && eta < 1.5 && phi > -1.48 && phi < -0.96 && (phi < -1.23 && phi > -1.30)) * 5", "same");
   B->SetLineColor(kRed);
   B->SetMarkerColor(kRed);
   B->SetMarkerStyle(20);
   A->SetStats(0);
   B->SetStats(0);
   A->GetXaxis()->SetTitle("EM ET");
   A->SetTitle("");
   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(A, "Neighbor towers", "l");
   Legend.AddEntry(B, "Tower in question", "lp");
   Legend.Draw();
   A->SetLineWidth(2);
   A->SetLineColor(kBlue);
   B->SetLineWidth(2);
   c1->SetLogy();
}
