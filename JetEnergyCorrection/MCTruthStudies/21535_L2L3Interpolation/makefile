default: TestRunL2

TestRun: Execute
	./Execute --OutsideFileName Autumn18_V16_MC_L1FastJet_AK4PFchs.txt \
		--InsideFileName ParallelMC_L1FastJet_AK4PFchs.txt \
		--Output Interpolated_L1FastJet_AK4PFchs.txt \
		--PhiMin -1.8 --PhiMax -0.4 \
		--HEMPhiMin -1.57079632679 --HEMPhiMax -0.87266462599 \
		--MinEta -3.0 --MaxEta -1.5 \
		--R0 0.4 --N 1000000

TestRunL2: Execute
	./Execute --OutsideFileName Autumn18_V16_MC_L2Relative_AK4PFchs.txt \
		--InsideFileName ParallelMC_L2Relative_AK4PFchs.txt \
		--Output Interpolated_L2Relative_AK4PFchs.txt \
		--PhiMin -2.0 --PhiMax -0.4 \
		--HEMPhiMin -1.57079632679 --HEMPhiMax -0.87266462599 \
		--MinEta -3.0 --MaxEta -1.5 \
		--R0 0.4 --N 1000000

Debug: Execute
	./Execute --OutsideFileName A.txt \
		--InsideFileName B.txt \
		--Output Interpolated_L2Relative_AK4PFchs.txt \
		--PhiMin -2.0 --PhiMax -0.4 \
		--HEMPhiMin -1.57079632679 --HEMPhiMax -0.87266462599 \
		--MinEta -3.0 --MaxEta -1.5 \
		--R0 0.4 --N 1000000

Execute: CombineTextFiles.cpp
	CompileRootMacro CombineTextFiles.cpp Execute
