{
   TFile File1(Form("Output_PPData_HiForest_0_%s.root", Tag.c_str()));
   TFile File2(Form("Output_AAData_HiForest_0_%s.root", Tag.c_str()));

   TH1D *HN1 = (TH1D *)File1.Get("HNPF");
   TH1D *HJ1 = (TH1D *)File1.Get("HJetPF");
   TH1D *HA1 = (TH1D *)File1.Get("HAddedPF");
   TH1D *HN2 = (TH1D *)File2.Get("HNPF");
   TH1D *HJ2 = (TH1D *)File2.Get("HJetPF");

   HJ1->Scale(1.0 / HN1->GetEntries());
   HA1->Scale(1.0 / HN1->GetEntries());
   HJ2->Scale(1.0 / HN2->GetEntries());

   HJ2->Add(HJ1, -1);
   HJ2->Divide(HA1);

   HJ2->Draw();
}
