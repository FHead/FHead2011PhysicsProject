default: RunTest

Execute: MakeEfficiency.cpp
	CompileRootMacro MakeEfficiency.cpp Execute

RunElectron: Execute
	./Execute --input WLNu.root --output WLNuE.pdf --DoE true --DoG false --doM false --DoJ false --DoT false
	cp WLNuE.pdf ~/public/html/

RunElectronReport: Execute
	./Execute --input WLNu.root --output WLNuEE.pdf --DoE false --DoG false --doM false --DoJ false --DoT false \
		--DoEEReport true
	./Execute --input WLNu.root --output WLNuEB.pdf --DoE false --DoG false --doM false --DoJ false --DoT false \
		--DoEBReport true
	cp WLNuEE.pdf WLNuEB.pdf ~/public/html/

RunMuonReport: Execute
	./Execute --input WLNu.root --output WLNuM.pdf --DoE false --DoG false --doM false --DoJ false --DoT false \
		--DoMReport true
	./Execute --input WLNu.root --output WLNuME.pdf --DoE false --DoG false --doM false --DoJ false --DoT false \
		--DoMEReport true
	./Execute --input WLNu.root --output WLNuMB.pdf --DoE false --DoG false --doM false --DoJ false --DoT false \
		--DoMBReport true
	./Execute --input WLNu.root --output WLNuMO.pdf --DoE false --DoG false --doM false --DoJ false --DoT false \
		--DoMOReport true
	cp WLNuM.pdf WLNuME.pdf WLNuMB.pdf WLNuMO.pdf ~/public/html/

RunPhoton: Execute
	./Execute --input HGG.root --output HGG.pdf --DoE false --DoG true --doM false --DoJ false --DoT false
	cp HGG.pdf ~/public/html/

RunMuon: Execute
	./Execute --input WLNu.root --output WLNuM.pdf --DoE false --DoG false --DoM true --DoJ false --DoT false
	cp WLNuM.pdf ~/public/html

RunTest: Execute
	./Execute --input TestRunHistograms.root --output Test.pdf --DoE false --DoG false --doM false --DoJ false --DoT true
	cp Test.pdf ~/public/html/

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

