{
   TFile F1("EmbeddedPP6Dijet100.root");
   TFile F2("EmbeddedPP6Dijet220.root");

   TTree *TRho1 = (TTree *)F1.Get("hiFJRhoAnalyzer/t");
   TTree *T1 = (TTree *)F1.Get("hiEvtAnalyzer/HiTree");
   TTree *TRho2 = (TTree *)F2.Get("hiFJRhoAnalyzer/t");
   TTree *T2 = (TTree *)F2.Get("hiEvtAnalyzer/HiTree");

   T1->AddFriend(TRho1, "rho");
   T2->AddFriend(TRho2, "rho");
}
