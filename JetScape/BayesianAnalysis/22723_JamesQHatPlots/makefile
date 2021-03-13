

ProcessData: Execute ExtractData.py
	python3 ExtractData.py
	cat TResult.txt | TextToTree TResult.root 7 "X:YTruth:Y:Y90Low:Y90High:Y60Low:Y60High"
	cat EResult.txt | TextToTree EResult.root 7 "X:YTruth:Y:Y90Low:Y90High:Y60Low:Y60High"
	./Execute --Input TResult.root --Output TPlots.root --Prefix QHatT
	./Execute --Input EResult.root --Output EPlots.root --Prefix QHatE
	hadd -f AllPlots.root TPlots.root EPlots.root

Execute: Transcribe.cpp
	CompileRootMacro Transcribe.cpp Execute
