
default: Prepare TestRun

Prepare:
	ln -sf ../23431_FormatConversion/*root .

TestRun: Execute
	./Execute --Base DobiMeow_test.root --Variant DobiMeow_test_GAN.root --Output DobiMeow_test_GAN.pdf
	./Execute --Base DobidoMeow.root --Variant DobidoMeow_test_GAN.root --Output DobidoMeow_test_GAN.pdf
	./Execute --Base Charged_DobidoMeow.root --Variant Charged_DobidoMeow_test_GAN.root --Output Charged_DobidoMeow_test_GAN.pdf
	./Execute --Base Charged_DobidoMeow.root --Variant Charged_DobidoMeow_test_GAN_FirstHalf.root --Output Charged_DobidoMeow_test_GAN_FirstHalf.pdf
	./Execute --Base Charged_DobidoMeow10.root --Variant Charged_DobidoMeow10_test_GAN.root --Output Charged_DobidoMeow10_test_GAN.pdf

Execute: MakePlots.cpp
	CompileRootMacro MakePlots.cpp Execute
