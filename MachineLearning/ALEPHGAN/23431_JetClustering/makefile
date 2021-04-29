default: Prepare TestRun

Prepare:
	ln -sf ../23431_FormatConversion/*root .

Execute: CalculateJets.cpp
	CompileRootMacro CalculateJets.cpp Execute -I../../CommonCode/include ../../CommonCode/library/*

TestRun: Execute
	time ./Execute --Input DobiMeow_test.root --Output Jet_DobiMeow_test.root --GanTreeName tgan
	time ./Execute --Input DobiMeow_test_GAN.root --Output Jet_DobiMeow_test_GAN.root --GanTreeName tgan
	time ./Execute --Input DobidoMeow.root --Output Jet_DobidoMeow.root --GanTreeName tgan
	time ./Execute --Input DobidoMeow_test_GAN.root --Output Jet_DobidoMeow_test_GAN.root --GanTreeName tgan
	time ./Execute --Input Charged_DobidoMeow.root --Output Jet_Charged_DobidoMeow.root --GanTreeName tgan
	time ./Execute --Input Charged_DobidoMeow_test_GAN.root --Output Jet_Charged_DobidoMeow_test_GAN.root --GanTreeName tgan
	time ./Execute --Input Charged_DobidoMeow10.root --Output Jet_Charged_DobidoMeow10.root --GanTreeName tgan
	time ./Execute --Input Charged_DobidoMeow10_test_GAN.root --Output Jet_Charged_DobidoMeow10_test_GAN.root --GanTreeName tgan
	time ./Execute --Input Charged_DobidoMeow10_test_GAN1000.root --Output Jet_Charged_DobidoMeow10_test_GAN1000.root
	time ./Execute --Input Charged_DobidoMeow10_test_GAN100.root --Output Jet_Charged_DobidoMeow10_test_GAN100.root
	time ./Execute --Input Charged_DobidoMeow20.root --Output Jet_Charged_DobidoMeow20.root
	time ./Execute --Input Charged_DobidoMeow20_test_GAN.root --Output Jet_Charged_DobidoMeow20_test_GAN.root
	time ./Execute --Input Charged_DobidoMeow30.root --Output Jet_Charged_DobidoMeow30.root
	time ./Execute --Input Charged_DobidoMeow30_test_GAN.root --Output Jet_Charged_DobidoMeow30_test_GAN.root
		
