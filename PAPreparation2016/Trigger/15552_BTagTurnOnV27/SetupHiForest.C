{
   TTree *T = (TTree *)ak4CaloJetAnalyzer->Get("t");
   TTree *H = (TTree *)hiEvtAnalyzer->Get("HiTree");
   H->SetName("H");
   T->AddFriend(H);
   TTree *P = (TTree *)ak4PFJetAnalyzer->Get("t");
   T->AddFriend(P);
   P->SetName("P");
}
