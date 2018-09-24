default: RunMuon

Execute: MakeEfficiency.cpp
	CompileRootMacro MakeEfficiency.cpp Execute

RunEG: Execute
	./Execute --input WLNu.root --output WLNu.pdf --doe true --dog false
	./Execute --input HGG.root --output HGG.pdf --doe false --dog true
	cp WLNu.pdf HGG.pdf ~/public/html/

RunMuon: Execute
	./Execute --input WLNu.root --output WLNu.pdf --DoE false --DoG false --DoM true --DoJ false
	cp WLNu.pdf ~/public/html

RunJet: Execute
	./Execute --input TTbar.root --output TTbar.pdf --DoE false --DoG false --DoM false --DoJ true
	cp TTbar.pdf ~/public/html/

RunJetBackup: Execute
	./Execute --input TTbarBackup.root --output TTbar.pdf --DoE false --DoG false --DoM false --DoJ true
	cp TTbar.pdf ~/public/html/
