RunSlimmer: TreeSlimmer.cpp
	CompileRootMacro TreeSlimmer.cpp RunSlimmer
	
ExecuteSlimmer: RunSlimmer
	# ./RunSlimmer MixedResult/PP6Dijet.root /tmp/chenyi/PP6DijetSlimmed.root OutputTree Tree SmearConfigFile 
	# ./RunSlimmer MixedResult/PP6DijetHIReco.root /tmp/chenyi/PP6DijetHIRecoSlimmed.root OutputTree Tree SmearConfigFile 
	# ./RunSlimmer MixedResult/PP8Dijet.root /tmp/chenyi/PP8DijetSlimmed.root OutputTree Tree SmearConfigFile 
	# ./RunSlimmer MixedResult/PP8DijetLarge.root /tmp/chenyi/PP8DijetSlimmedLarge.root OutputTree Tree SmearConfigFile 
	./RunSlimmer StraightResult/AA6DijetCymbalV2.root /tmp/chenyi/AA6DijetCymbalV2Slimmed.root T Tree PlainConfigFile 

DebugRunSlimmer: TreeSlimmerSimple.cpp
	CompileRootMacro TreeSlimmerSimple.cpp DebugRunSlimmer
	./DebugRunSlimmer
