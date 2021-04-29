
default: Prepare TestRun

Prepare:
	ln -sf ../23431_JetClustering/Jet*root .

TestRun: Execute
	./Execute --Base Jet_DobiMeow_test.root --Variant Jet_DobiMeow_test_GAN.root --Output Jet_DobiMeow_test_GAN.pdf
	./Execute --Base Jet_DobidoMeow.root --Variant Jet_DobidoMeow_test_GAN.root --Output Jet_DobidoMeow_test_GAN.pdf
	./Execute --Base Jet_Charged_DobidoMeow.root --Variant Jet_Charged_DobidoMeow_test_GAN.root --Output Jet_Charged_DobidoMeow_test_GAN.pdf
	./Execute --Base Jet_Charged_DobidoMeow10.root --Variant Jet_Charged_DobidoMeow10_test_GAN.root --Output Jet_Charged_DobidoMeow10_test_GAN.pdf
	./Execute --Base Jet_Charged_DobidoMeow10.root --Variant Jet_Charged_DobidoMeow10_test_GAN1000.root --Output Jet_Charged_DobidoMeow10_test_GAN1000.pdf
	./Execute --Base Jet_Charged_DobidoMeow10.root --Variant Jet_Charged_DobidoMeow10_test_GAN100.root --Output Jet_Charged_DobidoMeow10_test_GAN100.pdf
	./Execute --Base Jet_Charged_DobidoMeow20.root --Variant Jet_Charged_DobidoMeow20_test_GAN.root --Output Jet_Charged_DobidoMeow20_test_GAN.pdf
	./Execute --Base Jet_Charged_DobidoMeow30.root --Variant Jet_Charged_DobidoMeow30_test_GAN.root --Output Jet_Charged_DobidoMeow30_test_GAN.pdf

Execute: MakePlots.cpp
	CompileRootMacro MakePlots.cpp Execute

Deploy:
	cp *pdf ~/Dropbox/Share/20210413_GANMeow/
