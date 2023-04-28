FJBase = /cvmfs/cms.cern.ch/slc7_amd64_gcc10/external/fastjet/3.4.0-726cc2aa67168c4401b736ad982593f1/bin/

default: TestRun

TestRun: Execute
	time ./Execute --GenInput GenParticles/HiForestMiniAOD_14.root \
		--HLTInput HLTTree/xac.root --Output /tmp/chenyi/Match_14_xac.root

Execute: MatchEvent.cpp
	CompileRootMacro MatchEvent.cpp Execute \
		`$(FJBase)/fastjet-config --cxxflags --libs`
