default: Merge

Merge: RunMerge
	$(eval FileList := $(shell ls Output/SynchTree/SynchTree*root | tr '\n' ',' | sed "s/,$$/\n/"))
	$(eval IndexList := $(shell echo $(FileList) | sed "s/[A-Za-z_.\/]//g"))
	./RunMerge --File $(FileList) --Index $(IndexList)

RunMerge: CombineTree.cpp
	CompileRootMacro CombineTree.cpp RunMerge
