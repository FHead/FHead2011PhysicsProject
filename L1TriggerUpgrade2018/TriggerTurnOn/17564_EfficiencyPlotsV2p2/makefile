default: RunElectron RunMuon

Execute: MakeEfficiency.cpp
	CompileRootMacro MakeEfficiency.cpp Execute

RunElectron: Execute
	./Execute --input WLNu.root --output WLNuE.pdf --DoE true --DoG false --doM false --DoJ false
	cp WLNuE.pdf ~/public/html/

RunPhoton: Execute
	./Execute --input HGG.root --output HGG.pdf --DoE false --DoG true --doM false --DoJ false
	cp HGG.pdf ~/public/html/

RunMuon: Execute
	./Execute --input WLNu.root --output WLNuM.pdf --DoE false --DoG false --DoM true --DoJ false
	cp WLNuM.pdf ~/public/html

RunJet: Execute
	./Execute --input TTbar.root --output TTbar.pdf --DoE false --DoG false --DoM false --DoJ true
	cp TTbar.pdf ~/public/html/

RunJetBackup: Execute
	./Execute --input TTbarBackup.root --output TTbar.pdf --DoE false --DoG false --DoM false --DoJ true
	cp TTbar.pdf ~/public/html/

