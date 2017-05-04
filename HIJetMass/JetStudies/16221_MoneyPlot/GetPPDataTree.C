{
   TFile F1("PPDataHighPTJet_15751_2.root");
   TFile F2("PPDataHighPTJet_16151.root");

   TTree *T1 = (TTree *)F1.Get("OutputTree");
   TTree *T2 = (TTree *)F2.Get("OutputTree");

   T2->SetLineColor(kRed);
}
