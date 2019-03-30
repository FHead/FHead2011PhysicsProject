default: TestRun

TestRun: Execute
	./Execute --Input RunSkimR03.root --OutputBase SkimR03
	cp SkimR03.pdf ~/public/html

BigRun: Execute
	hadd -f -k BigSkim.root RunSkimR03.root BatchResult/*root
	./Execute --Input BigSkim.root --OutputBase BigRun
	cp BigRun.pdf ~/public/html

BigPythiaRun: Execute
	hadd -f -k BigPythiaSkim.root PythiaBatchResult/*root
	./Execute --Input BigPythiaSkim.root --OutputBase BigPythiaRun
	cp BigPythiaRun.pdf ~/public/html

PythiaRun: Execute
	./Execute --Input PythiaAllRun.root --OutputBase Pythia
	cp Pythia.pdf ~/public/html

PythiaWeightedRun: Execute
	./Execute --Input PythiaWeightedAllRun.root --OutputBase PythiaWeighted
	cp PythiaWeighted.pdf ~/public/html

RunQPythia: Execute
	./Execute --Input QPythiaQHat1Skim.root --OutputBase QPythiaQHat1
	./Execute --Input QPythiaVacSkim.root --OutputBase QPythiaVac
	cp QPythia*pdf ~/public/html/

Execute: Analyze.cpp
	CompileRootMacro Analyze.cpp Execute
