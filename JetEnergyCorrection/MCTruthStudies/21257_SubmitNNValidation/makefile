default: ListAllSamples

ListAllSamples:
	dasgoclient -query 'dataset=/RelValQCD_FlatPt_15_3000HS_13/CMSSW_10_5_0_pre2*105X_mc2017_realistic_v4_HS_*/*' > DatasetNames.txt
	grep GEN-SIM-RECO DatasetNames.txt > ToSubmit.txt

CreateSubmitFiles:
	bash CreateSubmitFiles.sh


