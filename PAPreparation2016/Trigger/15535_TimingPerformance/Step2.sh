for i in *step1
do
   ./RunIsolate "Modules in Path: HLT_L1ZeroBias_BptxAND_v1" < $i > ${i/step1/step2_L1ZeroBias}
   ./RunIsolate "Modules in Path: HLT_PAAK4CaloJet60_Eta2p1_v1" < $i > ${i/step1/step2_Calo60}
   ./RunIsolate "Modules in Path: HLT_PAAK4CaloJet80_Eta2p1_v1" < $i > ${i/step1/step2_Calo80}
   ./RunIsolate "Modules in Path: HLT_PAAK4CaloJet100_Eta2p1_v1" < $i > ${i/step1/step2_Calo100}
   ./RunIsolate "Modules in Path: HLT_PAAK4CaloBJetCSVv160_Eta2p1_v1" < $i > ${i/step1/step2_Calo60CSVv1}
   ./RunIsolate "Modules in Path: HLT_PAAK4CaloBJetCSVv180_Eta2p1_v1" < $i > ${i/step1/step2_Calo80CSVv1}
   ./RunIsolate "Modules in Path: HLT_PAAK4CaloBJetCSVv1100_Eta2p1_v1" < $i > ${i/step1/step2_Calo100CSVv1}
   ./RunIsolate "Modules in Path: HLT_PAAK4CaloBJetCSVv260_Eta2p1_v1" < $i > ${i/step1/step2_Calo60CSVv2}
   ./RunIsolate "Modules in Path: HLT_PAAK4CaloBJetCSVv280_Eta2p1_v1" < $i > ${i/step1/step2_Calo80CSVv2}
   ./RunIsolate "Modules in Path: HLT_PAAK4CaloBJetCSVv2100_Eta2p1_v1" < $i > ${i/step1/step2_Calo100CSVv2}
   ./RunIsolate "Modules in Path: HLT_PAAK4PFJet60_Eta2p1_v1" < $i > ${i/step1/step2_PF60}
   ./RunIsolate "Modules in Path: HLT_PAAK4PFJet80_Eta2p1_v1" < $i > ${i/step1/step2_PF80}
   ./RunIsolate "Modules in Path: HLT_PAAK4PFJet100_Eta2p1_v1" < $i > ${i/step1/step2_PF100}
   ./RunIsolate "Modules in Path: HLT_PAAK4PFBJetCSV60_Eta2p1_v1" < $i > ${i/step1/step2_PF60CSV}
   ./RunIsolate "Modules in Path: HLT_PAAK4PFBJetCSV80_Eta2p1_v1" < $i > ${i/step1/step2_PF80CSV}
   ./RunIsolate "Modules in Path: HLT_PAAK4PFBJetCSV100_Eta2p1_v1" < $i > ${i/step1/step2_PF100CSV}
done
