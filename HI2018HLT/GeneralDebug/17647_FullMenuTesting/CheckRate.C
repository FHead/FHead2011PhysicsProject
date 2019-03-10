{
   hltbitanalysis->cd();

   cout << "Number of entries " << HltTree->GetEntries() << endl;

   cout << "L1 MuMu 40-100 " << HltTree->GetEntries("L1_DoubleMuOpen_Centrality_40_100_BptxAND") << endl;
   cout << "L1 MuMu 50-100 " << HltTree->GetEntries("L1_DoubleMuOpen_Centrality_50_100_BptxAND") << endl;
   cout << "HLT MuMu 40-100 " << HltTree->GetEntries("HLT_HIL1DoubleMuOpen_OS_Centrality_40_100_v1") << endl;
   cout << "HLT MuMu 50-100 " << HltTree->GetEntries("HLT_HIL1DoubleMuOpen_Centrality_50_100_v1") << endl;
   
   cout << "L1 Mu 70-100 " << HltTree->GetEntries("L1_SingleMuOpen_Centrality_70_100_MinimumBiasHF1_AND_BptxAND") << endl;
   cout << "L1 Mu 80-100 " << HltTree->GetEntries("L1_SingleMuOpen_Centrality_80_100_MinimumBiasHF1_AND_BptxAND") << endl;
   cout << "HLT Mu 70-100 " << HltTree->GetEntries("HLT_HIL1MuOpen_Centrality_70_100_v1") << endl;
   cout << "HLT Mu 80-100 " << HltTree->GetEntries("HLT_HIL1MuOpen_Centrality_80_100_v1") << endl;
   
   cout << "HLT Photon30 " << HltTree->GetEntries("HLT_HIIslandPhoton30_Eta3p1_v1") << endl;
   cout << (double)HltTree->GetEntries("HLT_HIIslandPhoton30_Eta3p1_v1") / HltTree->GetEntries() << endl;
   cout << "HLT GEDPhoton30 " << HltTree->GetEntries("HLT_HIGEDPhoton30_v1") << endl;
   cout << (double)HltTree->GetEntries("HLT_HIGEDPhoton30_v1") / HltTree->GetEntries() << endl;
}
