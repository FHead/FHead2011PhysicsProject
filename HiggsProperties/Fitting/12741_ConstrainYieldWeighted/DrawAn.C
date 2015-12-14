{
   TFile File1("OutputFileEMME_100.root");

   TCanvas c1;

   ResultTree->Draw("A3ZZA1ZZ>>A(50,-15,15)", "Status == 3");
   A.SetLineWidth(2);
   A.SetLineColor(kBlue);

   A.SetTitle("");
   A.GetXaxis()->SetTitle("A_{3}^{ZZ}");
   A.GetYaxis()->SetTitle("a.u.");
   A.SetStats(0);

   TGraph G;
   G.SetPoint(0, 0, 0);
   G.SetPoint(1, 0, 10000);
   G.SetLineWidth(2);
   G.Draw("l");

   c1.SaveAs("A3_100.png");
   c1.SaveAs("A3_100.C");
   c1.SaveAs("A3_100.eps");
   c1.SaveAs("A3_100.pdf");
   
   ResultTree->Draw("A2ZZA1ZZ>>A(50,-5,5)", "Status == 3");
   A.SetLineWidth(2);
   A.SetLineColor(kBlue);

   A.SetTitle("");
   A.GetXaxis()->SetTitle("A_{2}^{ZZ}");
   A.GetYaxis()->SetTitle("a.u.");
   A.SetStats(0);

   G.Draw("l");

   c1.SaveAs("A2_100.png");
   c1.SaveAs("A2_100.C");
   c1.SaveAs("A2_100.eps");
   c1.SaveAs("A2_100.pdf");
   
   TFile File2("OutputFileEMME_20.root");

   ResultTree->Draw("A3ZZA1ZZ>>B(50,-15,15)", "Status == 3");
   B.SetLineWidth(2);
   B.SetLineColor(kBlue);

   B.SetTitle("");
   B.GetXaxis()->SetTitle("A_{3}^{ZZ}");
   B.GetYaxis()->SetTitle("a.u.");
   B.SetStats(0);

   G.Draw("l");

   c1.SaveAs("A3_20.png");
   c1.SaveAs("A3_20.C");
   c1.SaveAs("A3_20.eps");
   c1.SaveAs("A3_20.pdf");

   ResultTree->Draw("A2ZZA1ZZ>>B(50,-5,5)", "Status == 3");
   B.SetLineWidth(2);
   B.SetLineColor(kBlue);

   B.SetTitle("");
   B.GetXaxis()->SetTitle("A_{2}^{ZZ}");
   B.GetYaxis()->SetTitle("a.u.");
   B.SetStats(0);

   G.Draw("l");

   c1.SaveAs("A2_20.png");
   c1.SaveAs("A2_20.C");
   c1.SaveAs("A2_20.eps");
   c1.SaveAs("A2_20.pdf");
}

