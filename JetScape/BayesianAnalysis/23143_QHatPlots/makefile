
default: TestRun

Execute: GeneralPurposeQHatPlotter.cpp 
	CompileRootMacro GeneralPurposeQHatPlotter.cpp Execute

TestRun: Execute
	./Execute \
		--files root/Matter_NewSys.root,root/LBT_NewSys.root \
		--graphs QHatP,QHatP \
		--labels "MATTER 90% CR","LBT 90% CR" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 10 \
		--texts 0.7,0.55,"T = 300 MeV",0.17,0.83," " \
		--output Figure5P.pdf
	./Execute \
		--files root/Matter_NewSys.root,root/Matter_NewSys.root,root/Matter_NewSys.root \
		--graphs QHatPPrior,QHatPPrior,QHatPPrior \
		--ranges "68","90","99" \
		--labels "Prior 68% CR","Prior 90% CR","Prior 99% CR" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 45 \
		--texts 0.7,0.55,"T = 300 MeV",0.17,0.83," " \
		--output Figure5PPrior.pdf
	./Execute \
		--files root/Matter_NewSys.root,root/LBT_NewSys.root \
		--graphs QHatT,QHatT \
		--labels "MATTER 90% CR","LBT 90% CR" \
		--xlabel "T (GeV)" --xmin 0.1 --xmax 0.8 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 10 \
		--texts 0.7,0.55,"p = 100 GeV/c",0.17,0.83," " \
		--dojet true \
		--output Figure5T.pdf
	./Execute \
		--files root/Matter_NewSys.root,root/Matter_NewSys.root,root/Matter_NewSys.root \
		--graphs QHatTPrior,QHatTPrior,QHatTPrior \
		--ranges "68","90","99" \
		--labels "Prior 68% CR","Prior 90% CR","Prior 99% CR" \
		--xlabel "p (GeV/c)" --xmin 0.1 --xmax 0.8 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 45 \
		--texts 0.7,0.55,"p = 100 GeV/c",0.17,0.83," " \
		--output Figure5TPrior.pdf
	./Execute \
		--files root/Matter_NewSys.root,root/LBT_NewSys.root,root/MatterLBT1_NewSys.root \
		--graphs QHatP,QHatP,QHatP \
		--labels "MATTER 90% CR","LBT 90% CR","MATTER+LBT1 90% CR" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 10 \
		--texts 0.7,0.55,"T = 300 MeV",0.17,0.83," " \
		--output Figure10P.pdf
	./Execute \
		--files root/MatterLBT1_NewSys.root,root/MatterLBT1_NewSys.root,root/MatterLBT1_NewSys.root \
		--graphs QHatPPrior,QHatPPrior,QHatPPrior \
		--ranges 68,90,99 \
		--labels "Prior 68% CR","Prior 90% CR","Prior 99% CR" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 20 \
		--texts 0.7,0.55,"T = 300 MeV",0.23,0.93,"MATTER+LBT1" \
		--output Figure10PPrior.pdf
	./Execute \
		--files root/Matter_NewSys.root,root/LBT_NewSys.root,root/MatterLBT1_NewSys.root \
		--graphs QHatT,QHatT,QHatT \
		--labels "MATTER 90% CR","LBT 90% CR","MATTER+LBT1 90% CR" \
		--xlabel "T (GeV)" --xmin 0.1 --xmax 0.8 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 10 \
		--texts 0.8,0.5,"p = 100 GeV/c",0.17,0.83," " \
		--dojet true \
		--output Figure10T.pdf
	./Execute \
		--files root/MatterLBT1_NewSys.root,root/MatterLBT1_NewSys.root,root/MatterLBT1_NewSys.root \
		--graphs QHatTPrior,QHatTPrior,QHatTPrior \
		--ranges 68,90,99 \
		--labels "Prior 68% CR","Prior 90% CR","Prior 99% CR" \
		--xlabel "T (GeV)" --xmin 0.1 --xmax 0.8 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 20 \
		--texts 0.8,0.5,"p = 100 GeV/c",0.23,0.93,"MATTER+LBT1" \
		--dojet true \
		--output Figure10TPrior.pdf
	./Execute \
		--files root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys.root \
		--graphs QHatPM,QHatPL \
		--labels "MATTER in MATTER+LBT 2","LBT in MATTER+LBT 2" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 10 \
		--texts 0.7,0.55,"T = 300 MeV",0.17,0.83," " \
		--output Figure13P.pdf
	./Execute \
		--files root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys.root \
		--graphs QHatPMPrior,QHatPMPrior,QHatPMPrior \
		--ranges 68,90,99 \
		--labels "Prior 68%","Prior 90%","Prior 99%" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 20 \
		--texts 0.7,0.55,"T = 300 MeV",0.23,0.93,"MATTER+LBT2" \
		--output Figure13PPrior.pdf
	./Execute \
		--files root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys.root \
		--graphs QHatTM,QHatTL \
		--labels "MATTER in MATTER+LBT 2","LBT in MATTER+LBT 2" \
		--xlabel "T (GeV)" --xmin 0.1 --xmax 0.8 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 10 \
		--texts 0.7,0.55,"p = 100 GeV/c",0.17,0.83," " \
		--dojet true \
		--output Figure13T.pdf
	./Execute \
		--files root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys.root \
		--graphs QHatTMPrior,QHatTMPrior,QHatTMPrior \
		--ranges 68,90,99 \
		--labels "Prior 68%","Prior 90%","Prior 99%" \
		--xlabel "T (GeV)" --xmin 0.1 --xmax 0.8 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 20 \
		--texts 0.7,0.55,"p = 100 GeV/c",0.23,0.93,"MATTER+LBT2" \
		--dojet true \
		--output Figure13TPrior.pdf

TestRunJamesPlots: Execute
	./Execute \
		--files JamesPlots.root,JamesPlots.root \
		--graphs QHatTTruth,QHatT \
		--labels "Truth","Extracted 90% CR" \
		--xlabel "T (GeV)" --xmin 0.15 --xmax 0.51 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 6 \
		--texts 0.3,0.25,"p = 100 GeV/c",0.14,0.93,"LBT" \
		--dojet false \
		--colors 2,4 \
		--output ClosureExampleT.pdf
	./Execute \
		--files JamesPlots.root,JamesPlots.root \
		--graphs QHatETruth,QHatE \
		--labels "Truth","Extracted 90% CR" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 8 \
		--texts 0.3,0.25,"T = 300 MeV",0.14,0.93,"LBT" \
		--dojet false \
		--colors 2,4 \
		--output ClosureExampleP.pdf
