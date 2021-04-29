
default: TestRun

TestRun: Execute
	./Execute --Input ALEPH_1994_meow.csv --Output ALEPH_1994_Meow.root
	./Execute --Input ALEPH_1994_meow2.csv --Output ALEPH_1994_Meow2.root
	./Execute --Input ALEPH_1994_meow3.csv --Output ALEPH_1994_Meow3.root
	./Execute --Input ALEPH_1994_meow4.csv --Output ALEPH_1994_Meow4.root
	./Execute --Input ALEPH_1994_meow5.csv --Output ALEPH_1994_Meow5.root
	./Execute --Input ALEPH_1994_meow6.csv --Output ALEPH_1994_Meow6.root
	# ./Execute --Input ALEPH_1994.csv --Output ALEPH_1994.root
	./Execute --Input ALEPH_1994_10k_ctgan.csv --Output ALEPH_1994_10k_ctgan.root

Execute: ConvertToTree.cpp
	CompileRootMacro ConvertToTree.cpp Execute
