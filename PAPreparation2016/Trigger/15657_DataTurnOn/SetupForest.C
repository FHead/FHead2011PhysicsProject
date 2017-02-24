{
   TTree *T = (TTree *)_file0->Get("hiEvtAnalyzer/HiTree");
   TTree *TriggerTree = (TTree *)_file0->Get("hltanalysis/HltTree");
   TTree *CaloJetTree = (TTree *)_file0->Get("ak4CaloJetAnalyzer/t");
   TTree *PFJetTree = (TTree *)_file0->Get("ak4PFJetAnalyzer/t");
   TTree *PFTree = (TTree *)_file0->Get("pfcandAnalyzer/pfTree");
   TTree *MuTree = (TTree *)_file0->Get("hltMuTree/HLTMuTree");
   TTree *SkimTree = (TTree *)_file0->Get("skimanalysis/HltTree");

   TTree *HLTCaloJet = (TTree *)_file0->Get("hltobject/HLT_PAAK4CaloJet40_Eta5p1_v");

   T->AddFriend(TriggerTree, "Trigger");
   T->AddFriend(CaloJetTree, "CaloJet");
   T->AddFriend(PFJetTree, "PFJet");
   T->AddFriend(PFTree, "PF");
   T->AddFriend(MuTree, "Mu");
   T->AddFriend(SkimTree, "Skim");

   T->AddFriend(HLTCaloJet, "HLTCaloJet");
}
