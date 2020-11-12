FJCONTRIB = /cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/fastjet-contrib/1.033-omkpbe

default: Run

RunCMSSW:
	cmsRun runForestAOD_pponAA_MIX_103X.py

Run: Execute
	./Execute --input HiForestAOD.root

Execute: DoJetSubtraction.cpp
	CompileRootMacro DoJetSubtraction.cpp Execute -I../../CommonCode/include ../../CommonCode/library/* \
		`$(FastJetConfig) --cxxflags --libs` -L$(FJCONTRIB)/lib -I$(FJCONTRIB)/include -lConstituentSubtractor

