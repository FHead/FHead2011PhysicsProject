
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
		--texts 0.7,0.18,"T = 300 MeV",0.14,0.95,"(b)" \
		--legendx 0.23 --legendy 0.85 \
		--inset true --insetleft 0.65 --insetright 0.90 --insetbottom 0.60 --insettop 0.85 \
		--insetxmin 0 --insetxmax 200 --insetymin 0 --insetymax 45 \
		--insetfiles root/Matter_NewSys.root,root/Matter_NewSys.root \
		--insetgraphs QHatPPrior,QHatPPrior \
		--insetranges "99","90" \
		--insetlabels "99%","90%" \
		--insettext "MATTER/LBT" \
		--output Figure_QHatMatterLBTP
	./Execute \
		--files root/Matter_NewSys.root,root/LBT_NewSys.root \
		--graphs QHatT,QHatT \
		--labels "MATTER 90% CR","LBT 90% CR" \
		--xlabel "T (GeV)" --xmin 0.1 --xmax 0.8 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 10 \
		--texts 0.3,0.18,"p = 100 GeV/c",0.14,0.95,"(a)" \
		--dojet true \
		--legendx 0.23 --legendy 0.85 \
		--inset true --insetleft 0.65 --insetright 0.90 --insetbottom 0.60 --insettop 0.85 \
		--insetxmin 0.1 --insetxmax 0.8 --insetymin 0 --insetymax 40 \
		--insetfiles root/Matter_NewSys.root,root/Matter_NewSys.root \
		--insetgraphs QHatTPrior,QHatTPrior \
		--insetranges "99","90" \
		--insetlabels "99%","90%" \
		--insettext "MATTER/LBT" \
		--output Figure_QHatMatterLBTT
	./Execute \
		--files root/Matter_NewSys.root,root/LBT_NewSys.root,root/MatterLBT1_NewSys.root \
		--graphs QHatP,QHatP,QHatP \
		--labels "MATTER 90% CR","LBT 90% CR","MATTER+LBT1 90% CR" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 10 \
		--texts 0.7,0.18,"T = 300 MeV",0.14,0.95,"(b)" \
		--legendx 0.19 --legendy 0.85 \
		--inset true --insetleft 0.65 --insetright 0.90 --insetbottom 0.60 --insettop 0.85 \
		--insetxmin 0 --insetxmax 200 --insetymin 0 --insetymax 20 \
		--insetfiles root/MatterLBT1_NewSys.root,root/MatterLBT1_NewSys.root \
		--insetgraphs QHatPPrior,QHatPPrior \
		--insetranges "99","90" \
		--insetlabels "99%","90%" \
		--insettext "MATTER+LBT1" \
		--output Figure_QHatMatterLBT1P
	./Execute \
		--files root/Matter_NewSys.root,root/LBT_NewSys.root,root/MatterLBT1_NewSys.root \
		--graphs QHatT,QHatT,QHatT \
		--labels "MATTER 90% CR","LBT 90% CR","MATTER+LBT1 90% CR" \
		--xlabel "T (GeV)" --xmin 0.1 --xmax 0.8 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 10 \
		--texts 0.3,0.18,"p = 100 GeV/c",0.14,0.95,"(a)" \
		--dojet true \
		--legendx 0.16 --legendy 0.85 \
		--inset true --insetleft 0.65 --insetright 0.90 --insetbottom 0.60 --insettop 0.85 \
		--insetxmin 0.1 --insetxmax 0.8 --insetymin 0 --insetymax 18 \
		--insetfiles root/MatterLBT1_NewSys.root,root/MatterLBT1_NewSys.root \
		--insetgraphs QHatTPrior,QHatTPrior \
		--insetranges "99","90" \
		--insetlabels "99%","90%" \
		--insettext "MATTER+LBT1" \
		--output Figure_QHatMatterLBT1T
	./Execute \
		--files root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys.root \
		--graphs QHatPM,QHatPL \
		--labels "MATTER in MATTER+LBT 2","LBT in MATTER+LBT 2" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 8 \
		--texts 0.7,0.18,"T = 300 MeV",0.14,0.95,"(b)" \
		--legendx 0.14 --legendy 0.85 \
		--inset true --insetleft 0.65 --insetright 0.90 --insetbottom 0.60 --insettop 0.85 \
		--insetxmin 0 --insetxmax 200 --insetymin 0 --insetymax 20 \
		--insetfiles root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys.root \
		--insetgraphs QHatPMPrior,QHatPMPrior \
		--insetranges "99","90" \
		--insetlabels "99%","90%" \
		--insettext "MATTER+LBT2" \
		--output Figure_QHatMatterLBT2P
	./Execute \
		--files root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys.root \
		--graphs QHatTM,QHatTL \
		--labels "MATTER in MATTER+LBT 2","LBT in MATTER+LBT 2" \
		--xlabel "T (GeV)" --xmin 0.1 --xmax 0.8 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 9 \
		--texts 0.3,0.18,"p = 100 GeV/c",0.14,0.95,"(a)" \
		--dojet true \
		--legendx 0.14 --legendy 0.85 \
		--inset true --insetleft 0.65 --insetright 0.90 --insetbottom 0.60 --insettop 0.85 \
		--insetxmin 0.1 --insetxmax 0.8 --insetymin 0 --insetymax 20 \
		--insetfiles root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys.root \
		--insetgraphs QHatTMPrior,QHatTMPrior \
		--insetranges "99","90" \
		--insetlabels "99%","90%" \
		--insettext "MATTER+LBT2" \
		--output Figure_QHatMatterLBT2T
	for i in *eps; do	epstopdf $$i; done

TestRunOld: Execute
	./Execute \
		--files root/Matter_NewSys.root,root/LBT_NewSys.root \
		--graphs QHatP,QHatP \
		--labels "MATTER 90% CR","LBT 90% CR" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 10 \
		--texts 0.7,0.55,"T = 300 MeV",0.14,0.95," " \
		--doinset true \
		--output Figure5P.pdf
	./Execute \
		--files root/Matter_NewSys.root,root/Matter_NewSys.root,root/Matter_NewSys.root \
		--graphs QHatPPrior,QHatPPrior,QHatPPrior \
		--ranges "68","90","99" \
		--labels "Prior 68% CR","Prior 90% CR","Prior 99% CR" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 45 \
		--texts 0.7,0.55,"T = 300 MeV",0.14,0.95," " \
		--output Figure5PPrior.pdf
	./Execute \
		--files root/Matter_NewSys.root,root/LBT_NewSys.root \
		--graphs QHatT,QHatT \
		--labels "MATTER 90% CR","LBT 90% CR" \
		--xlabel "T (GeV)" --xmin 0.1 --xmax 0.8 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 10 \
		--texts 0.7,0.55,"p = 100 GeV/c",0.14,0.95," " \
		--dojet true \
		--output Figure5T.pdf
	./Execute \
		--files root/Matter_NewSys.root,root/Matter_NewSys.root,root/Matter_NewSys.root \
		--graphs QHatTPrior,QHatTPrior,QHatTPrior \
		--ranges "68","90","99" \
		--labels "Prior 68% CR","Prior 90% CR","Prior 99% CR" \
		--xlabel "p (GeV/c)" --xmin 0.1 --xmax 0.8 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 45 \
		--texts 0.7,0.55,"p = 100 GeV/c",0.14,0.95," " \
		--output Figure5TPrior.pdf
	./Execute \
		--files root/Matter_NewSys.root,root/LBT_NewSys.root,root/MatterLBT1_NewSys.root \
		--graphs QHatP,QHatP,QHatP \
		--labels "MATTER 90% CR","LBT 90% CR","MATTER+LBT1 90% CR" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 10 \
		--texts 0.7,0.55,"T = 300 MeV",0.14,0.95," " \
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
		--texts 0.8,0.5,"p = 100 GeV/c",0.14,0.95," " \
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
		--texts 0.7,0.55,"T = 300 MeV",0.14,0.95," " \
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
		--texts 0.7,0.55,"p = 100 GeV/c",0.14,0.95," " \
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
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 8 \
		--texts 0.3,0.25,"p = 100 GeV/c",0.17,0.95,"LBT (a)" \
		--dojet false \
		--colors 2,4 \
		--legendx 0.23 --legendy 0.85 \
		--inset true --insetleft 0.65 --insetright 0.90 --insetbottom 0.60 --insettop 0.85 \
		--insetxmin 0 --insetxmax 200 --insetymin 0 --insetymax 45 \
		--insetfiles root/Matter_NewSys.root,root/Matter_NewSys.root \
		--insetgraphs QHatPPrior,QHatPPrior \
		--insetranges "99","90" \
		--insetlabels "99%","90%" \
		--insettext " " \
		--output ClosureExampleT
	./Execute \
		--files JamesPlots.root,JamesPlots.root \
		--graphs QHatETruth,QHatE \
		--labels "Truth","Extracted 90% CR" \
		--xlabel "p (GeV/c)" --xmin 0 --xmax 200 \
		--ylabel "#hat{q} / T^{3}" --ymin 0 --ymax 8 \
		--texts 0.3,0.25,"T = 300 MeV",0.17,0.95,"LBT (b)" \
		--dojet false \
		--colors 2,4 \
		--legendx 0.23 --legendy 0.85 \
		--inset true --insetleft 0.65 --insetright 0.90 --insetbottom 0.60 --insettop 0.85 \
		--insetxmin 0 --insetxmax 200 --insetymin 0 --insetymax 45 \
		--insetfiles root/Matter_NewSys.root,root/Matter_NewSys.root \
		--insetgraphs QHatPPrior,QHatPPrior \
		--insetranges "99","90" \
		--insetlabels "99%","90%" \
		--insettext " " \
		--output ClosureExampleP
	epstopdf ClosureExampleT.eps
	epstopdf ClosureExampleP.eps

