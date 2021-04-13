
default: TestRun

TestRun: Execute
	./Execute --Input DobiMeow_test.csv               --Output DobiMeow_test.root
	./Execute --Input DobiMeow_test_GAN.csv           --Output DobiMeow_test_GAN.root
	./Execute --Input DobidoMeow.csv                  --Output DobidoMeow.root
	./Execute --Input DobidoMeow_test_GAN.csv         --Output DobidoMeow_test_GAN.root
	# ./Execute --Input DobidodoMeow.csv                --Output DobidodoMeow.root
	./Execute --Input charged_dobidomeow.csv          --Output Charged_DobidoMeow.root          --DoCharge true
	./Execute --Input charged_dobidomeow_test_GAN.csv --Output Charged_DobidoMeow_test_GAN.root --DoCharge true
	./Execute --Input charged_dobidomeow_test_GAN_FirstHalf.csv --Output Charged_DobidoMeow_test_GAN_FirstHalf.root --DoCharge true
	./Execute --Input charged_dobido10meow.csv          --Output Charged_DobidoMeow10.root          --DoCharge true
	./Execute --Input charged_dobido10meow_test_GAN.csv --Output Charged_DobidoMeow10_test_GAN.root --DoCharge true

Execute: ConvertToTree.cpp
	CompileRootMacro ConvertToTree.cpp Execute
