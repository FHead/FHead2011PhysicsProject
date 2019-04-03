{
   TTree *HiTree = (TTree *)_file0->Get("hiEvtAnalyzer/HiTree");
   TTree *HltTree = (TTree *)_file0->Get("hltanalysis/HltTree");
   TTree *CaloJet = (TTree *)_file0->Get("ak4CaloJetAnalyzer/t");
   TTree *PuCaloJet = (TTree *)_file0->Get("akPu4CaloJetAnalyzer/t");
   TTree *PFJet = (TTree *)_file0->Get("ak4PFJetAnalyzer/t");
   TTree *PuPFJet = (TTree *)_file0->Get("akPu4PFJetAnalyzer/t");
   TTree *CsPFJet = (TTree *)_file0->Get("akCs4PFJetAnalyzer/t");
   TTree *Track = (TTree *)_file0->Get("ppTrack/trackTree");

   CaloJet->AddFriend(HiTree, "HI");
   CaloJet->AddFriend(HltTree, "HLT");
   PuCaloJet->AddFriend(HiTree, "HI");
   PuCaloJet->AddFriend(HltTree, "HLT");
   PFJet->AddFriend(HiTree, "HI");
   PFJet->AddFriend(HltTree, "HLT");
   PuPFJet->AddFriend(HiTree, "HI");
   PuPFJet->AddFriend(HltTree, "HLT");
   CsPFJet->AddFriend(HiTree, "HI");
   CsPFJet->AddFriend(HltTree, "HLT");
   Track->AddFriend(HiTree, "HI");
   Track->AddFriend(HltTree, "HLT");

   CaloJet->SetMarkerStyle(20);
   PuCaloJet->SetMarkerStyle(20);
   PFJet->SetMarkerStyle(20);
   PuPFJet->SetMarkerStyle(20);
   CsPFJet->SetMarkerStyle(20);
}

