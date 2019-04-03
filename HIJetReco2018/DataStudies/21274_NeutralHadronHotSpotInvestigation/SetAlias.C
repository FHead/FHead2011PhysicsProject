{
   TTree *HiTree = (TTree *)_file0->Get("hiEvtAnalyzer/HiTree");
   TTree *SkimTree = (TTree *)_file0->Get("skimanalysis/HltTree");
   TTree *HltTree = (TTree *)_file0->Get("hltanalysis/HltTree");
   TTree *CaloJet = (TTree *)_file0->Get("ak4CaloJetAnalyzer/t");
   TTree *PuCaloJet = (TTree *)_file0->Get("akPu4CaloJetAnalyzer/t");
   TTree *PFJet = (TTree *)_file0->Get("ak4PFJetAnalyzer/t");
   TTree *PuPFJet = (TTree *)_file0->Get("akPu4PFJetAnalyzer/t");
   TTree *CsPFJet = (TTree *)_file0->Get("akCs4PFJetAnalyzer/t");
   TTree *PFTree = (TTree *)_file0->Get("pfcandAnalyzer/pfTree");
   TTree *Tower = (TTree *)_file0->Get("rechitanalyzerpp/tower");

   SkimTree->SetAlias("Noise", "HBHENoiseFilterResultRun2Loose");

   CaloJet->AddFriend(HiTree, "HI");
   CaloJet->AddFriend(HltTree, "HLT");
   CaloJet->AddFriend(SkimTree, "Cut");
   PuCaloJet->AddFriend(HiTree, "HI");
   PuCaloJet->AddFriend(HltTree, "HLT");
   PuCaloJet->AddFriend(SkimTree, "Cut");
   PFJet->AddFriend(HiTree, "HI");
   PFJet->AddFriend(HltTree, "HLT");
   PFJet->AddFriend(SkimTree, "Cut");
   PuPFJet->AddFriend(HiTree, "HI");
   PuPFJet->AddFriend(HltTree, "HLT");
   PuPFJet->AddFriend(SkimTree, "Cut");
   CsPFJet->AddFriend(HiTree, "HI");
   CsPFJet->AddFriend(HltTree, "HLT");
   CsPFJet->AddFriend(SkimTree, "Cut");
   PFTree->AddFriend(HiTree, "HI");
   PFTree->AddFriend(HltTree, "HLT");
   PFTree->AddFriend(SkimTree, "Cut");

   CaloJet->SetMarkerStyle(20);
   PuCaloJet->SetMarkerStyle(20);
   PFJet->SetMarkerStyle(20);
   PuPFJet->SetMarkerStyle(20);
   CsPFJet->SetMarkerStyle(20);
   PFTree->SetMarkerStyle(20);
   Tower->SetMarkerStyle(20);
}

