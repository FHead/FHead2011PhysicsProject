{
   TFile F1("OutputFile.root");   // Embedded
   TFile F2("Output.root");       // PP + Background

   TH1D *H1 = (TH1D *)F1.Get("HWideSpacing");
   TH1D *H2 = (TH1D *)F2.Get("HSpacing");

   H1->Scale(1 / H1->Integral());
   H2->Scale(1 / H2->Integral() * 10 / 0.9);

   H1->Draw();
   H2->Draw("same");

   H2->SetLineColor(kRed);
}
