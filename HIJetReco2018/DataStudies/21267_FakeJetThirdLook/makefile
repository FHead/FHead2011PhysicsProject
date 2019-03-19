FASTJET = /cvmfs/cms.cern.ch/slc6_amd64_gcc700/external/fastjet/3.3.0-omkpbe/bin/

default: RunPlots

LongRun: Execute
	time ./Execute --Input `ls MB/0000/HiForestAOD_[56789]* | tr '\n' ','` \
		--Output LongRun.root

TestRun: Execute
	time ./Execute --Input `ls MB/0000/HiForestAOD_5[1234]* | tr '\n' ','` \
		--Output TestRun.root

SmallRun: Execute
	time ./Execute --Input `ls MB/0000/HiForestAOD_54* | tr '\n' ','` \
		--Output SmallRun.root

FullRun: Execute
	time ./Execute --Input `ls MB/000*/HiForestAOD_* | tr '\n' ','` \
		--Output FullRun.root

RunMVA1p0: Execute
	time ./Execute --Input /eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/HP1p0/327524/517/HiForestAOD_merged_517.root,/eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/HP1p0/327524/526/HiForestAOD_merged_526.root \
		--Output MVA1p0.root

RunMVA0p98: Execute
	time ./Execute --Input /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIMinimumBias0/ReRecoCrisis2019/HP0p98/LS517_0p98.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIMinimumBias0/ReRecoCrisis2019/HP0p98/LS526_0p98.root \
		--Output MVA0p98.root

RunPromptReco: Execute
	time ./Execute --Input /eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/prompt-reco/HiForestAOD_run327524_517.root,/eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/prompt-reco/HiForestAOD_run327524_526.root \
		--Output PromptReco.root

Execute: QuickLook.cpp
	CompileRootMacro QuickLook.cpp Execute \
		`$(FASTJET)/fastjet-config --cxxflags` `$(FASTJET)/fastjet-config --libs` \
		-I../../CommonCode/include ../../CommonCode/library/*o

ExecutePlots: MakePlot.cpp
	CompileRootMacro MakePlot.cpp ExecutePlots

RunPlots: ExecutePlots
	./ExecutePlots --Input All.root --Output TrackJet.pdf
	cp TrackJet.pdf ~/public/html

