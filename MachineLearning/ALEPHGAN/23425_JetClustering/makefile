Fraction    = 1
MCJEC       = ../../CommonCode/text/JEC_EEAK4_MC_20200625.txt
ResidualJEC = ../../CommonCode/text/JEC_EEAK4_DataL2_20200625.txt,../../CommonCode/text/JEC_EEAK4_DataL3_20200625.txt
DataJEC     = $(MCJEC),$(ResidualJEC)

default: Prepare TestRun

Prepare:
	ln -sf ../23425_FormatConversion/*root .

Execute: CalculateJets.cpp
	CompileRootMacro CalculateJets.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o
	ln -sf ../../CommonCode/source/Dictionary_rdict.pcm .

TestRun: Execute
	time ./Execute --Input ALEPH_1994_Meow.root \
		--Output TestMeow.root --MC true --GanTreeName tgan
	time ./Execute --Input 
	# time ./Execute --Input ALEPH_1994.root \
	# 	--Output TestData.root --MC true --GanTreeName tgan
	
		
