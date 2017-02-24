{
   TFile F1("OutputFile.root");
   TFile F2("Grid.root");

   TH1D *H1 = (TH1D *)F1.Get("HSpacing11");
   TH1D *H2 = (TH1D *)F2.Get("HGrid");

   H2->SetLineColor(kRed);
   H2->SetMarkerColor(kRed);

   H1->Draw();
   H2->Draw("same");
}
