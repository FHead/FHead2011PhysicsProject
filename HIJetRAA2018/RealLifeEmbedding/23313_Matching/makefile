FJCONTRIB = /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/fastjet-contrib/1.033-omkpbe

default: RunMatching

RunSubtraction: Execute
	for i in Output/PTHat250/*root; \
	do \
		./Execute --input $$i --output Results/`basename $$i` --JEC JEC/Autumn18_HI_RAAV2_MC_L2Relative_AK4PF.txt; \
	done

RunExtraSubtraction: Execute
	for j in PTHat100Grass PTHat100HardQGP; do \
		folder=`basename $$j`; \
		mkdir -p Results/$$folder; \
		for i in Output/$$j/*root; do \
			./Execute --input $$i --output Results/$$folder/`basename $$i` \
				--JEC JEC/Autumn18_HI_RAAV2_MC_L2Relative_AK4PF.txt; \
		done; \
	done

RunNonEmbedded: Execute
	for i in OutputNonEmbedded/PTHat*/*root; \
	do \
		folder=`dirname $$i`; \
		folder=`basename $$folder`; \
		mkdir -p ResultsNonEmbedded/$$folder; \
		./Execute --input $$i --output ResultsNonEmbedded/$$folder/`basename $$i` \
			--JEC JEC/Autumn18_HI_RAAV2_MC_L2Relative_AK4PF.txt \
			--PassThrough true; \
	done

RunMatching: ExecuteMatching
	for i in `seq 1 100`; do \
		echo $$i; \
		./ExecuteMatching --input Results/Original_$$i.root --morphed Results/Morphed_$$i.root --output Results/Matched_$$i.root; \
	done

RunExtraMatching: ExecuteMatching
	mkdir -p Results/PTHat100Grass
	mkdir -p Results/PTHat100HardQGP
	for i in `seq 1 100`; do \
		echo $$i; \
		./ExecuteMatching --input Results/PTHat100/Original_$$i.root \
			--morphed Results/PTHat100Grass/Morphed100Grass_$$i.root \
			--output Results/PTHat100Grass/Matched100Grass_$$i.root; \
		./ExecuteMatching --input Results/PTHat100/Original_$$i.root \
			--morphed Results/PTHat100HardQGP/Morphed100HardQGP_$$i.root \
			--output Results/PTHat100HardQGP/Matched100HardQGP_$$i.root; \
	done

RunMatchingNonEmbedded: ExecuteMatching
	for j in 250 100; do \
		for i in `seq 1 100`; do \
			echo $$i; \
			./ExecuteMatching --input ResultsNonEmbedded/PTHat$$j/Original_$$i.root \
				--morphed ResultsNonEmbedded/PTHat$$j/Morphed_$$i.root \
				--output ResultsNonEmbedded/PTHat$$j/Matched_$$i.root; \
		done; \
	done

TestRunSubtraction: Execute
	./Execute --input Output/Run1/Morphed_14.root \
		--output Morphed_14.root \
		--JEC JEC/Autumn18_HI_RAAV2_MC_L2Relative_AK4PF.txt
	./Execute --input Output/Run1/Original_14.root \
		--output Original_14.root \
		--JEC JEC/Autumn18_HI_RAAV2_MC_L2Relative_AK4PF.txt

TestRunMatching: ExecuteMatching
	./ExecuteMatching --input Original_14.root --morphed Morphed_14.root --output Matched_14.root

Execute: ClusterJets.cpp
	CompileRootMacro ClusterJets.cpp Execute \
		-I../../CommonCode/include -I../../CommonCode ../../CommonCode/library/* \
		`$(FastJetConfig) --cxxflags --libs` -L$(FJCONTRIB)/lib -I$(FJCONTRIB)/include -lConstituentSubtractor

ExecuteMatching: MatchJets.cpp
	CompileRootMacro MatchJets.cpp ExecuteMatching


