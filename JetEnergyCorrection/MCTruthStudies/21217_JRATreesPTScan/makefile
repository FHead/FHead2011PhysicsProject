default: Merge

Merge: RunMerge
	$(eval FileListPF := $(shell ls Output/SynchTree/SynchTree*root | grep -v CALO | tr '\n' ',' | sed "s/,$$/\n/"))
	$(eval FileListCalo := $(shell ls Output/SynchTree/SynchTree*root | grep CALO | tr '\n' ',' | sed "s/,$$/\n/"))
	$(eval IndexListPF := $(shell echo $(FileListPF) | sed "s/[A-Za-z_.\/]//g"))
	$(eval IndexListCalo := $(shell echo $(FileListCalo) | sed "s/[A-Za-z_.\/]//g"))
	./RunMerge --File $(FileListPF) --Index $(IndexListPF) --OutputFileName MergedPF.root
	./RunMerge --File $(FileListCalo) --Index $(IndexListCalo) --OutputFileName MergedCalo.root

RunMerge: CombineTree.cpp
	CompileRootMacro CombineTree.cpp RunMerge
