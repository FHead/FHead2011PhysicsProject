
default: Prepare TestRun

Prepare:
	ln -sf ../23425_FormatConversion/*root .

TestRun: Execute
	./Execute --Base ALEPH_1994.root --Variant ALEPH_1994_Meow2.root --Output Meow2.pdf
	./Execute --Base ALEPH_1994.root --Variant ALEPH_1994_Meow3.root --Output Meow3.pdf
	./Execute --Base ALEPH_1994.root --Variant ALEPH_1994_Meow4.root --Output Meow4.pdf
	./Execute --Base ALEPH_1994.root --Variant ALEPH_1994_Meow5.root --Output Meow5.pdf
	./Execute --Base ALEPH_1994.root --Variant ALEPH_1994_Meow6.root --Output Meow6.pdf
	./Execute --Base ALEPH_1994.root --Variant ALEPH_1994_10k_ctgan.root --Output CTGan.pdf

Execute: MakePlots.cpp
	CompileRootMacro MakePlots.cpp Execute
