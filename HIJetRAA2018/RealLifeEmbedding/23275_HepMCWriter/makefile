
default: TestRun

TestRun: Execute
	# ./Execute --input Samples/OriginalPythia100.root --output Original100 --fraction 0.1
	# ./Execute --input Samples/MorphedPythia100.root --output Morphed100 --fraction 0.1
	# ./Execute --input Samples/OriginalPythia250.root --output Original250 --fraction 0.1
	# ./Execute --input Samples/MorphedPythia250.root --output Morphed250 --fraction 0.1
	./Execute --input Samples/MorphedPythia100-Grass.root --output Morphed100Grass --fraction 0.1
	./Execute --input Samples/MorphedPythia100-HardQGP.root --output Morphed100HardQGP --fraction 0.1
	./Execute --input Samples/MorphedPythia250-Grass.root --output Morphed250Grass --fraction 0.1
	./Execute --input Samples/MorphedPythia250-HardQGP.root --output Morphed250HardQGP --fraction 0.1

Execute: HepMCWriter.cpp
	CompileRootMacro HepMCWriter.cpp Execute


