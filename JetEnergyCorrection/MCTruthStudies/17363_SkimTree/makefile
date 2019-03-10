default: TestRun

Execute: SkimTree.cpp
	CompileRootMacro SkimTree.cpp Execute

TestRun: Execute
	time ./Execute --ptmin 72 --ptmax 90 \
		--etamin 0.78 --etamax 2.32 --input Result/Merged.root --fraction 0.1

FullRun: Execute
	time ./Execute --ptmin 72 --ptmax 90 \
		--etamin 0.78 --etamax 2.32 --input Result/Merged.root --output Positive.root
	time ./Execute --ptmin 72 --ptmax 90 \
		--etamin -2.32 --etamax -0.78 --input Result/Merged.root --output Negative.root
	hadd -f Skimmed.root Positive.root Negative.root
	rm -f Positive.root Negative.root

CentralSkim: Execute
	time ./Execute --ptmin 40 --ptmax 120 \
		--etamin -0.50 --etamax 0.50 --input Result/Merged.root --output /tmp/chenyi/Central.root
