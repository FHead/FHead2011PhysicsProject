default: RunMassless 

Execute: MakePlots.cpp
	CompileRootMacro MakePlots.cpp Execute

RunMassive: Execute
	./Execute --Recoil Massive/Combined_JewelR.root \
		--NoRecoil Massive/Combined_JewelNR.root \
		--Vacuum Massive/Combined_JewelVac.root \
		--Output PlotsMassive.pdf
	cp PlotsMassive.pdf ~/public/html/

RunMassless: Execute
	./Execute --Recoil Massless/Combined_JewelR.root \
		--NoRecoil Massless/Combined_JewelNR.root \
		--Vacuum Massless/Combined_JewelVac.root \
		--Output PlotsMassless.pdf
	cp PlotsMassless.pdf ~/public/html/

RunMasslessOld: Execute
	./Execute --Recoil Massless/Combined_JewelR.root \
		--NoRecoil Massless/Combined_JewelNR.root \
		--Vacuum MasslessOld/Combined_OldJewelVac.root \
		--Output PlotsMasslessOld.pdf
	cp PlotsMasslessOld.pdf ~/public/html/



