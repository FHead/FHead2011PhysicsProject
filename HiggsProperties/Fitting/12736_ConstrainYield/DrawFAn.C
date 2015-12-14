{
   TFile File1("OutputFileEMME_100.root");

   TCanvas c1;

   ResultTree->Draw("sign(A3ZZA1ZZ)*A3ZZA1ZZ*A3ZZA1ZZ/25/(1+A2ZZA1ZZ*A2ZZA1ZZ/9+A3ZZA1ZZ/A3ZZA1ZZ/25)>>A(100,-0.5,0.5)", "Status == 3");
   A.SetLineWidth(2);
   A.SetLineColor(kBlue);

   A.SetTitle("");
   A.GetXaxis()->SetTitle("f_{a3}");
   A.GetYaxis()->SetTitle("a.u.");
   A.SetStats(0);

   c1.SaveAs("FA3_100.png");
   c1.SaveAs("FA3_100.C");
   c1.SaveAs("FA3_100.eps");
   c1.SaveAs("FA3_100.pdf");
   
   ResultTree->Draw("sign(A2ZZA1ZZ)*A2ZZA1ZZ*A2ZZA1ZZ/9/(1+A2ZZA1ZZ*A2ZZA1ZZ/9+A3ZZA1ZZ/A3ZZA1ZZ/25)>>A(100,-0.5,0.5)", "Status == 3");
   A.SetLineWidth(2);
   A.SetLineColor(kBlue);

   A.SetTitle("");
   A.GetXaxis()->SetTitle("f_{a2}");
   A.GetYaxis()->SetTitle("a.u.");
   A.SetStats(0);

   c1.SaveAs("FA2_100.png");
   c1.SaveAs("FA2_100.C");
   c1.SaveAs("FA2_100.eps");
   c1.SaveAs("FA2_100.pdf");
   
   TFile File2("OutputFileEMME_20.root");

   ResultTree->Draw("sign(A3ZZA1ZZ)*A3ZZA1ZZ*A3ZZA1ZZ/25/(1+A2ZZA1ZZ*A2ZZA1ZZ/9+A3ZZA1ZZ/A3ZZA1ZZ/25)>>B(100,-0.5,0.5)", "Status == 3");
   B.SetLineWidth(2);
   B.SetLineColor(kBlue);

   B.SetTitle("");
   B.GetXaxis()->SetTitle("f_{a3}");
   B.GetYaxis()->SetTitle("a.u.");
   B.SetStats(0);

   c1.SaveAs("FA3_20.png");
   c1.SaveAs("FA3_20.C");
   c1.SaveAs("FA3_20.eps");
   c1.SaveAs("FA3_20.pdf");

   ResultTree->Draw("sign(A2ZZA1ZZ)*A2ZZA1ZZ*A2ZZA1ZZ/9/(1+A2ZZA1ZZ*A2ZZA1ZZ/9+A3ZZA1ZZ/A3ZZA1ZZ/25)>>B(100,-0.5,0.5)", "Status == 3");
   B.SetLineWidth(2);
   B.SetLineColor(kBlue);

   B.SetTitle("");
   B.GetXaxis()->SetTitle("f_{a2}");
   B.GetYaxis()->SetTitle("a.u.");
   B.SetStats(0);

   c1.SaveAs("FA2_20.png");
   c1.SaveAs("FA2_20.C");
   c1.SaveAs("FA2_20.eps");
   c1.SaveAs("FA2_20.pdf");
}

