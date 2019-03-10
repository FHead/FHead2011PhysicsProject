default: TestRun

Execute: MakeEfficiency.cpp
	CompileRootMacro MakeEfficiency.cpp Execute

TestRun: Execute
	./Execute --input WLNu.root --output WLNu.pdf --doe true --dog false
	./Execute --input HGG.root --output HGG.pdf --doe false --dog true
	cp WLNu.pdf HGG.pdf ~/public/html/
