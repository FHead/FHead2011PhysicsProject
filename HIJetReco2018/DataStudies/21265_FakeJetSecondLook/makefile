default: RunPromptRecoCS

LongRunCS: Execute
	time ./Execute --Input `ls MB/0000/HiForestAOD_[56789]* | tr '\n' ','` \
		--Tree "akCs4PFJetAnalyzer/t" --OutputBase LongRunCS --PrintDebug true
	cp LongRunCS.pdf ~/public/html/

TestRunCS: Execute
	time ./Execute --Input `ls MB/0000/HiForestAOD_5[1234]* | tr '\n' ','` \
		--Tree "akCs4PFJetAnalyzer/t" --OutputBase TestRunCS --PrintDebug false
	cp TestRunCS.pdf ~/public/html/

TestRunPU: Execute
	time ./Execute --Input `ls MB/0000/HiForestAOD_5[1234]* | tr '\n' ','` \
		--Tree "akPu4PFJetAnalyzer/t" --OutputBase TestRunPU --CheckFraction false --ReducedEta true
	cp TestRunPU.pdf ~/public/html/

TestRunCalo: Execute
	time ./Execute --Input `ls MB/0000/HiForestAOD_5[1234]* | tr '\n' ','` \
		--Tree "akPu4CaloJetAnalyzer/t" --OutputBase TestRunCalo --PrintDebug true --MinPTForTrack 999999 --CheckFraction false
	cp TestRunCalo.pdf ~/public/html/

SmallRunCS: Execute
	time ./Execute --Input `ls MB/0000/HiForestAOD_54* | tr '\n' ','` \
		--Tree "akCs4PFJetAnalyzer/t" --OutputBase SmallRunCS --PrintDebug true
	cp SmallRunCS.pdf ~/public/html/

SmallRunPU: Execute
	time ./Execute --Input `ls MB/0000/HiForestAOD_54* | tr '\n' ','` \
		--Tree "akPu4PFJetAnalyzer/t" --OutputBase SmallRunPU --CheckFraction false --ReducedEta true
	cp SmallRunPU.pdf ~/public/html/

SmallRunCalo: Execute
	time ./Execute --Input `ls MB/0000/HiForestAOD_54* | tr '\n' ','` \
		--Tree "akPu4CaloJetAnalyzer/t" --OutputBase SmallRunCalo --PrintDebug true --MinPTForTrack 999999 --CheckFraction false
	cp SmallRunCalo.pdf ~/public/html/

FullRunCS: Execute
	time ./Execute --Input `ls MB/000*/HiForestAOD_* | tr '\n' ','` \
		--Tree "akCs4PFJetAnalyzer/t" --OutputBase FullRunCS
	cp FullRunCS.pdf ~/public/html/

FullRunPU: Execute
	time ./Execute --Input `ls MB/000*/HiForestAOD_* | tr '\n' ','` \
		--Tree "akPu4PFJetAnalyzer/t" --OutputBase FullRunPU --CheckFraction false --ReducedEta true
	cp FullRunPU.pdf ~/public/html/

RunMVA1p0CS: Execute
	time ./Execute --Input /eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/HP1p0/327524/517/HiForestAOD_merged_517.root,/eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/HP1p0/327524/526/HiForestAOD_merged_526.root \
		--Tree "akCs4PFJetAnalyzer/t" --OutputBase MVA1p0CS --PrintDebug true
	cp MVA1p0CS.pdf ~/public/html/

RunMVA1p0PU: Execute
	time ./Execute --Input /eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/HP1p0/327524/517/HiForestAOD_merged_517.root,/eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/HP1p0/327524/526/HiForestAOD_merged_526.root \
		--Tree "akPu4PFJetAnalyzer/t" --OutputBase MVA1p0PU --CheckFraction false --ReducedEta true
	cp MVA1p0PU.pdf ~/public/html/

RunMVA0p98CS: Execute
	time ./Execute --Input /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIMinimumBias0/ReRecoCrisis2019/HP0p98/LS517_0p98.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIMinimumBias0/ReRecoCrisis2019/HP0p98/LS526_0p98.root \
		--Tree "akCs4PFJetAnalyzer/t" --OutputBase MVA0p98CS --PrintDebug true
	cp MVA0p98CS.pdf ~/public/html/

RunMVA0p98PU: Execute
	time ./Execute --Input /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIMinimumBias0/ReRecoCrisis2019/HP0p98/LS517_0p98.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIMinimumBias0/ReRecoCrisis2019/HP0p98/LS526_0p98.root \
		--Tree "akPu4PFJetAnalyzer/t" --OutputBase MVA0p98PU --CheckFraction false --ReducedEta true
	cp MVA0p98PU.pdf ~/public/html/

RunPromptRecoCS: Execute
	time ./Execute --Input /eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/prompt-reco/HiForestAOD_run327524_517.root,/eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/prompt-reco/HiForestAOD_run327524_526.root \
		--Tree "akCs4PFJetAnalyzer/t" --OutputBase PromptRecoCS
	cp PromptRecoCS.pdf ~/public/html/

RunPromptRecoPU: Execute
	time ./Execute --Input /eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/prompt-reco/HiForestAOD_run327524_517.root,/eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/prompt-reco/HiForestAOD_run327524_526.root \
		--Tree "akPu4PFJetAnalyzer/t" --OutputBase PromptRecoPU --CheckFraction false --ReducedEta true
	cp PromptRecoPU.pdf ~/public/html/

Execute: QuickLook.cpp
	CompileRootMacro QuickLook.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*o


