FJCONTRIB = /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/fastjet-contrib/1.033-omkpbe

default: Run

RunCMSSW:
	cmsRun runForestAOD_pponAA_MIX_103X.py

Run: Execute
	./Execute --input `ls Forest/*/HiForest*root | head -n 1 | tr '\n' ',' | sed "s/,$$//"` \
		--output SubtractedJet.root

RunTest: Execute
	./Execute --input /tmp/chenyi/HiForestAOD_1.root --output SubtractedJet.root --fraction 0.1 \
		--JEC JEC/Autumn18_HI_V8_MC_L2Relative_AK4PF.txt

Execute: DoJetSubtraction.cpp
	CompileRootMacro DoJetSubtraction.cpp Execute \
		-I../../CommonCode/include -I../../CommonCode ../../CommonCode/library/* \
		`$(FastJetConfig) --cxxflags --libs` -L$(FJCONTRIB)/lib -I$(FJCONTRIB)/include -lConstituentSubtractor

PrepareSubmission:
	bash PrepareSubmit.sh R015_NoPhi 0.15 0.00
	bash PrepareSubmit.sh R020_NoPhi 0.20 0.00
	bash PrepareSubmit.sh R030_NoPhi 0.30 0.00
	bash PrepareSubmit.sh R040_NoPhi 0.40 0.00
	bash PrepareSubmit.sh R050_NoPhi 0.50 0.00
	bash PrepareSubmit.sh R060_NoPhi 0.60 0.00
	bash PrepareSubmit.sh R080_NoPhi 0.80 0.00
	bash PrepareSubmit.sh R100_NoPhi 1.00 0.00
	bash PrepareSubmit.sh R120_NoPhi 1.20 0.00
	bash PrepareSubmit.sh R015_NominalPhi 0.15 1.00
	bash PrepareSubmit.sh R020_NominalPhi 0.20 1.00
	bash PrepareSubmit.sh R030_NominalPhi 0.30 1.00
	bash PrepareSubmit.sh R040_NominalPhi 0.40 1.00
	bash PrepareSubmit.sh R050_NominalPhi 0.50 1.00
	bash PrepareSubmit.sh R060_NominalPhi 0.60 1.00
	bash PrepareSubmit.sh R080_NominalPhi 0.80 1.00
	bash PrepareSubmit.sh R100_NominalPhi 1.00 1.00
	bash PrepareSubmit.sh R120_NominalPhi 1.20 1.00
	bash PrepareSubmit.sh R015_WidePhi 0.15 3.00
	bash PrepareSubmit.sh R020_WidePhi 0.20 3.00
	bash PrepareSubmit.sh R030_WidePhi 0.30 3.00
	bash PrepareSubmit.sh R040_WidePhi 0.40 3.00
	bash PrepareSubmit.sh R050_WidePhi 0.50 3.00
	bash PrepareSubmit.sh R060_WidePhi 0.60 3.00
	bash PrepareSubmit.sh R080_WidePhi 0.80 3.00
	bash PrepareSubmit.sh R100_WidePhi 1.00 3.00
	bash PrepareSubmit.sh R120_WidePhi 1.20 3.00



