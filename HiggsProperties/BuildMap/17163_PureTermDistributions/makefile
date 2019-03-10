Run: Distributions.cpp
	CompileRootMacro Distributions.cpp Run \
		-I../../CommonCode/include ../../CommonCode/library/AngleConversion.o
	time ./Run

MergeTree:
	mkdir -p Trees
	for i in 2e2mu 4e; do for j in A1UU A1UZ A2UU A2UZ A2UA A3UU A3UZ A3UA; do hadd Trees/Phto${i}_${j}_18p4GeV_NoPDF_ForEff.root AllTrees/Phto${i}_${j}_18p4GeV_NoPDF_ForEff_*.root; done; done


