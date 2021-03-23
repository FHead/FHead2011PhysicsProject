fraction = 1.00

default: FullTest

FullTest: TestRun TestRunValidation

TestRun: Execute
	time ./Execute --input PurePythia.root --output MorphedPythia.root \
		--minjetpt 50 --multiplicativemean 0.95 --multiplicativesigma 0.05 \
		--subtractivemean 0.5 --subtractivesigma 0.1 \
		--grassmean 0.9 --uniformgrass false --fraction $(fraction)
	time ./Execute --input PurePythia.root --output MorphedPythiaHigherGrass.root \
		--minjetpt 50 --multiplicativemean 0.95 --multiplicativesigma 0.05 \
		--subtractivemean 0.5 --subtractivesigma 0.1 \
		--grassmean 1.2 --uniformgrass false --fraction $(fraction)
	time ./Execute --input PurePythia.root --output OriginalPythia.root \
		--minjetpt 50 --multiplicativemean 1.00 --multiplicativesigma -1 \
		--subtractivemean 0.00 --subtractivesigma -1 \
		--grassmean 1.2 --fraction $(fraction)

TestRunValidation: ExecuteValidation
	./ExecuteValidation --pythia OriginalPythia.root --morphed MorphedPythia.root \
		--output Validation.pdf
	./ExecuteValidation --pythia OriginalPythia.root --morphed MorphedPythiaHigherGrass.root \
		--output ValidationHigherGrass.pdf

Execute: MorphJets.cpp
	CompileRootMacro MorphJets.cpp Execute

ExecuteValidation: Validate.cpp
	CompileRootMacro Validate.cpp ExecuteValidation
