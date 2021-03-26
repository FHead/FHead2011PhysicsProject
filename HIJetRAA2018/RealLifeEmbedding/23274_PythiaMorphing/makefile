fraction = 1.0

default:
	echo Hello World

OriginalRun: Execute
	time ./Execute --input PurePythia100.root --output OriginalPythia100.root \
		--minjetpt 50 --multiplicativemean 1.00 --multiplicativesigma -1 \
		--subtractivemean 0.00 --subtractivesigma -1 \
		--grassmean 1.2 --fraction $(fraction) \
		--bypass true
	time ./Execute --input PurePythia250.root --output OriginalPythia250.root \
		--minjetpt 50 --multiplicativemean 1.00 --multiplicativesigma -1 \
		--subtractivemean 0.00 --subtractivesigma -1 \
		--grassmean 1.2 --fraction $(fraction) \
		--bypass true

BaselineRun: Execute
	time ./Execute --input PurePythia100.root --output MorphedPythia100.root \
		--minjetpt 50 --multiplicativemean 0.95 --multiplicativesigma 0.05 \
		--subtractivemean 0.5 --subtractivesigma 0.1 \
		--grassmean 0.9 --uniformgrass false --fraction $(fraction) \
		--bypass false
	time ./Execute --input PurePythia250.root --output MorphedPythia250.root \
		--minjetpt 50 --multiplicativemean 0.95 --multiplicativesigma 0.05 \
		--subtractivemean 0.5 --subtractivesigma 0.1 \
		--grassmean 0.9 --uniformgrass false --fraction $(fraction) \
		--bypass false

VariationRun: Execute
	time ./Execute --input PurePythia100.root --output MorphedPythia100-Grass.root \
		--minjetpt 50 --multiplicativemean 0.95 --multiplicativesigma 0.05 \
		--subtractivemean 0.5 --subtractivesigma 0.1 \
		--grassmean 1.2 --uniformgrass false --fraction $(fraction) \
		--bypass false
	time ./Execute --input PurePythia250.root --output MorphedPythia250-Grass.root \
		--minjetpt 50 --multiplicativemean 0.95 --multiplicativesigma 0.05 \
		--subtractivemean 0.5 --subtractivesigma 0.1 \
		--grassmean 1.2 --uniformgrass false --fraction $(fraction) \
		--bypass false
	time ./Execute --input PurePythia100.root --output MorphedPythia100-HardQGP.root \
		--minjetpt 50 --multiplicativemean 0.90 --multiplicativesigma 0.05 \
		--subtractivemean 0.5 --subtractivesigma 0.1 \
		--grassmean 0.9 --uniformgrass false --fraction $(fraction) \
		--bypass false
	time ./Execute --input PurePythia250.root --output MorphedPythia250-HardQGP.root \
		--minjetpt 50 --multiplicativemean 0.90 --multiplicativesigma 0.05 \
		--subtractivemean 0.5 --subtractivesigma 0.1 \
		--grassmean 0.9 --uniformgrass false --fraction $(fraction) \
		--bypass false

TestRunValidation: ExecuteValidation
	./ExecuteValidation --pythia OriginalPythia100.root --morphed MorphedPythia100.root \
		--output Validation100.pdf
	./ExecuteValidation --pythia OriginalPythia100.root --morphed MorphedPythia100-Grass.root \
		--output Validation100-Grass.pdf
	./ExecuteValidation --pythia OriginalPythia100.root --morphed MorphedPythia100-HardQGP.root \
		--output Validation100-HardQGP.pdf

TestRunDebug: ExecuteValidation
	./ExecuteValidation --pythia OriginalPythia.root --morphed MorphedPythia.root \
		--output ValidationNoGrass.pdf --nograss true
	./ExecuteValidation --pythia OriginalPythia.root --morphed MorphedPythia.root \
		--output ValidationWTA.pdf --wta true
	./ExecuteValidation --pythia OriginalPythia.root --morphed MorphedPythia.root \
		--output ValidationOriginalJet.pdf --originaljet true

Execute: MorphJets.cpp
	CompileRootMacro MorphJets.cpp Execute

ExecuteValidation: Validate.cpp
	CompileRootMacro Validate.cpp ExecuteValidation
