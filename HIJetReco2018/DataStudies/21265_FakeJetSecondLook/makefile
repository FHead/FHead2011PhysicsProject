default: TestRunCS TestRunPU RunMVA1p0CS RunMVA1p0PU RunPromptRecoCS RunPromptRecoPU

TestRunCS: Execute
	./Execute --Input `ls MB/0000/HiForestAOD_5[1234]* | tr '\n' ','` \
		--Tree "akCs4PFJetAnalyzer/t" --OutputBase TestRunCS --PrintDebug true
	cp TestRunCS.pdf ~/public/html/

TestRunPU: Execute
	./Execute --Input `ls MB/0000/HiForestAOD_5[1234]* | tr '\n' ','` \
		--Tree "akPu4PFJetAnalyzer/t" --OutputBase TestRunPU --CheckFraction false --ReducedEta true
	cp TestRunPU.pdf ~/public/html/

FullRunCS: Execute
	./Execute --Input `ls MB/000*/HiForestAOD_* | tr '\n' ','` \
		--Tree "akCs4PFJetAnalyzer/t" --OutputBase FullRunCS
	cp FullRunCS.pdf ~/public/html/

FullRunPU: Execute
	./Execute --Input `ls MB/000*/HiForestAOD_* | tr '\n' ','` \
		--Tree "akPu4PFJetAnalyzer/t" --OutputBase FullRunPU --CheckFraction false --ReducedEta true
	cp FullRunPU.pdf ~/public/html/

RunMVA1p0CS: Execute
	./Execute --Input /eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/HP1p0/327524/517/HiForestAOD_merged_517.root,/eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/HP1p0/327524/526/HiForestAOD_merged_526.root \
		--Tree "akCs4PFJetAnalyzer/t" --OutputBase MVA1p0CS --PrintDebug true
	cp MVA1p0CS.pdf ~/public/html/

RunMVA1p0PU: Execute
	./Execute --Input /eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/HP1p0/327524/517/HiForestAOD_merged_517.root,/eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/HP1p0/327524/526/HiForestAOD_merged_526.root \
		--Tree "akPu4PFJetAnalyzer/t" --OutputBase MVA1p0PU --CheckFraction false --ReducedEta true
	cp MVA1p0PU.pdf ~/public/html/

RunPromptRecoCS: Execute
	./Execute --Input /eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/prompt-reco/HiForestAOD_run327524_517.root,/eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/prompt-reco/HiForestAOD_run327524_526.root \
		--Tree "akCs4PFJetAnalyzer/t" --OutputBase PromptRecoCS
	cp PromptRecoCS.pdf ~/public/html/

RunPromptRecoPU: Execute
	./Execute --Input /eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/prompt-reco/HiForestAOD_run327524_517.root,/eos/cms/store/group/phys_heavyions/bdiab/rerecocrisis2019/HIMinimumBias0/prompt-reco/HiForestAOD_run327524_526.root \
		--Tree "akPu4PFJetAnalyzer/t" --OutputBase PromptRecoPU --CheckFraction false --ReducedEta true
	cp PromptRecoPU.pdf ~/public/html/


Execute: QuickLook.cpp
	CompileRootMacro QuickLook.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*o


