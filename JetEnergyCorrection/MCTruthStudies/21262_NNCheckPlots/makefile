default: RunAK4PF

Execute: PlotJEC.cpp
	CompileRootMacro PlotJEC.cpp Execute

RunAK4PF: Execute
	./Execute \
		--jecl1 "L1New.txt","L1Old.txt" \
		--jecl2l3 "Trivial.txt","Trivial.txt" \
		--label "New","Old" \
		--output JEC_AK4PF.pdf --offset true



