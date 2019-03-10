default: DefaultRun

Execute: JetProfiles.cpp
	CompileRootMacro JetProfiles.cpp Execute

DefaultRun: Execute
	./Execute --input MergedSynchTree.root --tree OutputTree
	cp Output.pdf ~/public/html/

DefaultRunCalo: Execute
	./Execute --input MergedSynchTreeCalo.root --tree OutputTree --output OutputCalo.pdf
	cp OutputCalo.pdf ~/public/html/

EndcapRun: Execute
	./Execute --input MergedEndcapCalo.root --tree OutputTree --output OutputEndcapCalo.pdf
	cp OutputEndcapCalo.pdf ~/public/html/
	./Execute --input MergedEndcapPF.root --tree OutputTree --output OutputEndcapPF.pdf
	cp OutputEndcapPF.pdf ~/public/html/

