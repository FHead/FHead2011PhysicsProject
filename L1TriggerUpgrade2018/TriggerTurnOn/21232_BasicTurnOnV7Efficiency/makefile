default: RunTest

Execute: MakeEfficiency.cpp
	CompileRootMacro MakeEfficiency.cpp Execute

RunElectron: Execute
	./Execute --input DYLL.root --output DYLLE.pdf --DoE true --DoG false --doM false --DoJ false --DoT false
	cp DYLLE.pdf ~/public/html/

RunMuon: Execute
	./Execute --input DYLL.root --output DYLLM.pdf --DoE false --DoG false --DoM true --DoJ false --DoT false
	cp DYLLM.pdf ~/public/html

RunTest: Execute
	./Execute --input TestRunHistograms.root --output Test.pdf --DoE true --DoG true --DoM true --DoJ false --DoT false
	cp Test.pdf ~/public/html/

RunPhoton: Execute
	./Execute --input DYLL.root --output DYLLG.pdf --DoE false --DoG true --doM false --DoJ false --DoT false
	cp DYLLG.pdf ~/public/html/

RunTau: Execute
	./Execute --input HTauTau.root --output Tau.pdf --DoE false --DoG false --doM false --DoJ false --DoT true
	cp Tau.pdf ~/public/html/

RunJet: Execute
	./Execute --input TTbar.root --output TTbar.pdf --DoE false --DoG false --DoM false --DoJ true --DoT false
	cp TTbar.pdf ~/public/html/

RunWJet: Execute
	./Execute --input WLNu.root --output WLNuJet.pdf --DoE false --DoG false --DoM false --DoJ true --DoT false
	cp WLNuJet.pdf ~/public/html/

RunJetBackup: Execute
	./Execute --input TTbarBackup.root --output TTbar.pdf --DoE false --DoG false --DoM false --DoJ true --DoT false
	cp TTbar.pdf ~/public/html/

