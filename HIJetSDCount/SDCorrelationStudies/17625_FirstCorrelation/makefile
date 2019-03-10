default: SayHi

SayHi:
	echo 'Hi!!'

SubmitAll: SubmitNR SubmitR SubmitVac

SubmitNR:
	sh SubmitOne.sh jewel_NR_2.1_5.02_testfeb8 JewelNR jewel_simple

SubmitR:
	sh SubmitOne.sh jewel_R_2.1_5.02_testfeb8 JewelR jewel_recoils_simple

SubmitVac:
	sh SubmitOne.sh jewel_R_2.1_5.02_testfeb8 JewelVac jewel_recoils_vac

SubmitOld:
	sh SubmitDirectory.sh jewelvac/DiJet                    OldJewelVac
	sh SubmitDirectory.sh jewel/DiJet/RecoilOff_0_10        OldJewelNR0
	sh SubmitDirectory.sh jewel/DiJet/RecoilOff_10_20       OldJewelNR1
	sh SubmitDirectory.sh jewel/DiJet/RecoilOff_20_30       OldJewelNR2
	sh SubmitDirectory.sh jewel/DiJet/RecoilOff_30_40       OldJewelNR3
	sh SubmitDirectory.sh jewel/DiJet/RecoilOff_40_50       OldJewelNR4
	sh SubmitDirectory.sh jewel/DiJet/RecoilOff_50_60       OldJewelNR5
	sh SubmitDirectory.sh jewel/DiJet/RecoilOff_60_70       OldJewelNR6
	sh SubmitDirectory.sh jewel/DiJet/RecoilOff_70_80       OldJewelNR7
	sh SubmitDirectory.sh jewel/DiJet/RecoilOff_80_90       OldJewelNR8
	sh SubmitDirectory.sh jewel/DiJet/RecoilOff_90_100      OldJewelNR9
	sh SubmitDirectory.sh jewel/DiJet/RecoilOn_0_10         OldJewelR0
	sh SubmitDirectory.sh jewel/DiJet/RecoilOn_10_20        OldJewelR1
	sh SubmitDirectory.sh jewel/DiJet/RecoilOn_20_30        OldJewelR2
	sh SubmitDirectory.sh jewel/DiJet/RecoilOn_30_40        OldJewelR3
	sh SubmitDirectory.sh jewel/DiJet/RecoilOn_40_50        OldJewelR4
	sh SubmitDirectory.sh jewel/DiJet/RecoilOn_50_60        OldJewelR5
	sh SubmitDirectory.sh jewel/DiJet/RecoilOn_60_70        OldJewelR6
	sh SubmitDirectory.sh jewel/DiJet/RecoilOn_70_80        OldJewelR7
	sh SubmitDirectory.sh jewel/DiJet/RecoilOn_80_90        OldJewelR8
	sh SubmitDirectory.sh jewel/DiJet/RecoilOn_90_100       OldJewelR9
	sh SubmitDirectory.sh jewel/DiJet/ExtraRecoilOff_0_10   OldJewelNR0Extra
	sh SubmitDirectory.sh jewel/DiJet/ExtraRecoilOn_0_10    OldJewelR0Extra

SubmitNewR:
	sh SubmitDirectory.sh jewel_R_2.2_5.02_Sep18/dijets_pthat150/PU14Vac     NewJewelVac150
	sh SubmitDirectory.sh jewel_R_2.2_5.02_Sep18/dijets_pthat150/PU14Simple  NewJewelSimple150
	sh SubmitDirectory.sh jewel_R_2.2_5.02_Sep18/dijets_pthat70/PU14Vac      NewJewelVac70
	sh SubmitDirectory.sh jewel_R_2.2_5.02_Sep18/dijets_pthat70/PU14Simple   NewJewelSimple70

SubmitNewNR:
	sh SubmitDirectory.sh jewel_NR_2.2_5.02_Sep18/dijets_pthat150/PU14Vac    NewJewelNRVac150
	sh SubmitDirectory.sh jewel_NR_2.2_5.02_Sep18/dijets_pthat150/PU14Simple NewJewelNRSimple150
	sh SubmitDirectory.sh jewel_NR_2.2_5.02_Sep18/dijets_pthat70/PU14Vac     NewJewelNRVac70
	sh SubmitDirectory.sh jewel_NR_2.2_5.02_Sep18/dijets_pthat70/PU14Simple  NewJewelNRSimple70

SubmitZJet:
	sh SubmitDirectory.sh jewel_R_2.2_5.02_Sep18/zjet_pthat150/PU14Vac     NewJewelZJetVac150
	sh SubmitDirectory.sh jewel_R_2.2_5.02_Sep18/zjet_pthat150/PU14Simple  NewJewelZJetSimple150
	sh SubmitDirectory.sh jewel_R_2.2_5.02_Sep18/zjet_pthat70/PU14Vac      NewJewelZJetVac70
	sh SubmitDirectory.sh jewel_R_2.2_5.02_Sep18/zjet_pthat70/PU14Simple   NewJewelZJetSimple70
	sh SubmitDirectory.sh jewel_NR_2.2_5.02_Sep18/zjet_pthat150/PU14Vac    NewJewelZJetNRVac150
	sh SubmitDirectory.sh jewel_NR_2.2_5.02_Sep18/zjet_pthat150/PU14Simple NewJewelZJetNRSimple150
	sh SubmitDirectory.sh jewel_NR_2.2_5.02_Sep18/zjet_pthat70/PU14Vac     NewJewelZJetNRVac70
	sh SubmitDirectory.sh jewel_NR_2.2_5.02_Sep18/zjet_pthat70/PU14Simple  NewJewelZJetNRSimple70

Merge:
	for Tag in `ls Result/ | grep ^Result_ | cut -d '_' -f 2 | sort | uniq`; do echo $$Tag; hadd -k -f Result/Combined_$${Tag}.root Result/Result_$${Tag}_*root; done
