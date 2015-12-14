{
   TFile File1("OutputFileEMME_100.root");

   TCanvas c1;

   ResultTree->Draw("(Fem*(Sem+Bem)+Fme*(Sme+Bme))/(Sem+Sme+Bem+Bme)>>A(100,0,1)", "Status == 3");
   A.SetLineWidth(2);
   A.SetLineColor(kBlue);

   TGraph G;
   G.SetPoint(0, 0.5, 0);
   G.SetPoint(1, 0.5, 10000);
   G.SetLineWidth(2);
   G.Draw("l");

   A.SetTitle("");
   A.GetXaxis()->SetTitle("Background Fraction");
   A.GetYaxis()->SetTitle("a.u.");
   A.SetStats(0);

   c1.SaveAs("BackgroundFraction_100.png");
   c1.SaveAs("BackgroundFraction_100.C");
   c1.SaveAs("BackgroundFraction_100.eps");
   c1.SaveAs("BackgroundFraction_100.pdf");
   
   TFile File2("OutputFileEMME_20.root");

   ResultTree->Draw("(Fem*(Sem+Bem)+Fme*(Sme+Bme))/(Sem+Sme+Bem+Bme)>>B(100,0,1)", "Status == 3");
   B.SetLineWidth(2);
   B.SetLineColor(kBlue);

   G.Draw("l");

   B.SetTitle("");
   B.GetXaxis()->SetTitle("Background Fraction");
   B.GetYaxis()->SetTitle("a.u.");
   B.SetStats(0);

   c1.SaveAs("BackgroundFraction_20.png");
   c1.SaveAs("BackgroundFraction_20.C");
   c1.SaveAs("BackgroundFraction_20.eps");
   c1.SaveAs("BackgroundFraction_20.pdf");
}
