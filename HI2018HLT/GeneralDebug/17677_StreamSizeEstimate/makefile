DatasetDiJet80 = /DiJet80_5020GeV_TuneCUETP8M1_GEN_SIM_PU_200k_103X/ikucher-crab_DiJet80_5020GeV_DIGI_L1_DIGI2RAW_HLT_PU_200k_103X-227db562be96f23a3b4b3bc3b45430b4/USER
DatasetMinBias = /Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_2018/HINPbPbSpring18DR-NoPU_100X_upgrade2018_realistic_v10_ext1-v1/GEN-SIM-RAW
DatasetMinBias = /Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_2018/mnguyen-crab_Hydjet_Quenched_Drum5Ev8_PbPbMinBias_5020GeV_DIGI2RAW_103X_upgrade2018_realistic_HI_v4-58f9b704d41182ecb4a63ead877b2936/USER

default:
	echo Hi

Merge:
	for i in MinBias; do hadd -f /tmp/chenyi/openHLT_$$i.root `ls -l Result/*$$i*root | awk '{if($$5 > 20000) print $$9}'`; done

GetFileList:
	dasgoclient -query 'file dataset=$(DatasetDiJet80) instance=prod/phys03' > DiJet80List.txt
	dasgoclient --query="file dataset=$(DatasetMinBias) instance=prod/phys03" > MinBiasList.txt

ListBad:
	ls -l Result/*root | awk '{if($$5 < 20000) print $$9}' | cat -n

ListGood:
	ls -l Result/*root | awk '{if($$5 > 20000) print $$9}' | cat -n

SubmitJobs:
	bash Submit.sh

ResubmitJobs:
	bash SubmitAgain.sh

GetV4:
	wget https://raw.githubusercontent.com/cms-l1-dpg/L1Menu2018/master/official/XMLs/L1Menu_CollisionsHeavyIons2018_v4_0_0.xml

CheckSeed:
	for i in `grep Logical ExportedMenuV1V15.py  | awk '{print $$4}' | sort | uniq | tr -d '"'`; do echo $$i; grep "<name>$$i</name>" L1Menu_CollisionsHeavyIons2018_v4_0_0.xml; done
