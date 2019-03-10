default: RunNewJewelZJet

Execute: MakePlots.cpp
	CompileRootMacro MakePlots.cpp Execute

RunMassive: Execute
	./Execute --Recoil Massive/Combined_JewelR.root \
		--NoRecoil Massive/Combined_JewelNR.root \
		--Vacuum Massive/Combined_JewelVac.root \
		--Output PlotsMassive.pdf \
		--DoScan true --DoCorrelation true
	cp PlotsMassive.pdf ~/public/html/

RunMassless: Execute
	./Execute --Recoil Massless/Combined_JewelR.root \
		--NoRecoil Massless/Combined_JewelNR.root \
		--Vacuum Massless/Combined_JewelVac.root \
		--Output PlotsMassless.pdf \
		--DoScan true --DoCorrelation true
	cp PlotsMassless.pdf ~/public/html/

RunTestSample: Execute
	./Execute --Recoil TestSample/Combined_OldJewelR0Extra.root \
		--NoRecoil TestSample/Combined_OldJewelNR0Extra.root \
		--Vacuum TestSample/Combined_OldJewelVac.root \
		--Output PlotsTestSample.pdf \
		--DoScan true --DoCorrelation true
	cp PlotsTestSample.pdf ~/public/html/

RunNewJewel: Execute
	./Execute --Recoil NewJewel/Combined_NewJewelSimple150.root \
		--NoRecoil NewJewel/Combined_NewJewelNRSimple150.root \
		--Vacuum NewJewel/Combined_NewJewelVac150.root \
		--Output PlotsNewJewel.pdf \
		--DoScan true --DoCorrelation true
	cp PlotsNewJewel.pdf ~/public/html/

RunNewJewelRAA: Execute
	./Execute --Recoil NewJewel/Combined_NewJewelSimple70.root \
		--NoRecoil NewJewel/Combined_NewJewelNRSimple70.root \
		--Vacuum NewJewel/Combined_NewJewelVac70.root \
		--Output PlotsNewJewelRAA.pdf \
		--DoRAA true
	cp PlotsNewJewelRAA.pdf ~/public/html/

RunNewJewelCorrelation: Execute
	./Execute --Recoil NewJewel/Combined_NewJewelSimple150.root \
		--NoRecoil NewJewel/Combined_NewJewelNRSimple150.root \
		--Vacuum NewJewel/Combined_NewJewelVac150.root \
		--Output PlotsNewJewelCorrelation.pdf \
		--DoScan false --DoCorrelation true
	cp PlotsNewJewelCorrelation.pdf ~/public/html/

RunNewJewelZJet: Execute
	./Execute --Recoil Result/Combined_NewJewelZJetSimple70.root \
		--NoRecoil Result/Combined_NewJewelZJetNRSimple70.root \
		--Vacuum Result/Combined_NewJewelZJetVac70.root \
		--Output PlotsNewJewelZJet.pdf \
		--DoScan false --DoCorrelation false --DoZ true
	cp PlotsNewJewelZJet.pdf ~/public/html/









