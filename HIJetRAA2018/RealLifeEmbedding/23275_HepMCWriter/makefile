
default: TestRun

TestRun: Execute
	./Execute --input Samples/OriginalPythia.root --output Original.hepmc --fraction 0.01
	./Execute --input Samples/MorphedPythia.root --output Morphed.hepmc --fraction 0.01

Execute: HepMCWriter.cpp
	CompileRootMacro HepMCWriter.cpp Execute


