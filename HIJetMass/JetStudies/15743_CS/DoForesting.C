{
   TTree *T = (TTree *)_file0->Get("hiEvtAnalyzer/HiTree");
   TTree *TAKCS4PF = (TTree *)_file0->Get("akCs4PFJetAnalyzer/t");
   TTree *TAKCSSD4PF = (TTree *)_file0->Get("akCsSoftDrop4PFJetAnalyzer/t");
   TTree *TRho = (TTree *)_file0->Get("hiFJRhoAnalyzer/t");

   T->AddFriend(TAKCS4PF, "cs");
   T->AddFriend(TAKCSSD4PF, "sd");
   T->AddFriend(TRho, "rho");
}
