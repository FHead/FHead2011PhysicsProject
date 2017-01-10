{
   TFile File1("Output.root");
   TFile File2("Output2.root");
   TFile File4("Output4.root");
   TFile File5("Output5.root");

   TH1D *HN1 = (TH1D *)File1.Get("HNPF");
   TH1D *HJ1 = (TH1D *)File1.Get("HJetPF");
   TH1D *HA1 = (TH1D *)File1.Get("HAddedPF");
   TH1D *HN2 = (TH1D *)File2.Get("HNPF");
   TH1D *HJ2 = (TH1D *)File2.Get("HJetPF");
   TH1D *HN4 = (TH1D *)File4.Get("HNPF");
   TH1D *HJ4 = (TH1D *)File4.Get("HJetPF");
   TH1D *HA4 = (TH1D *)File4.Get("HAddedPF");
   TH1D *HN5 = (TH1D *)File5.Get("HNPF");
   TH1D *HJ5 = (TH1D *)File5.Get("HJetPF");

   HJ1->Scale(1.0 / HN1->GetEntries());
   HA1->Scale(1.0 / HN1->GetEntries());
   HJ2->Scale(1.0 / HN2->GetEntries());
   HJ4->Scale(1.0 / HN4->GetEntries());
   HA4->Scale(1.0 / HN4->GetEntries());
   HJ5->Scale(1.0 / HN5->GetEntries());

   HJ2->Add(HJ1, -1);
   HJ2->Divide(HA1);
   HJ5->Add(HJ4, -1);
   HJ5->Divide(HA4);

   HJ5->SetLineColor(kRed);
   HJ2->Draw();
   // HJ5->Draw("same");
}
