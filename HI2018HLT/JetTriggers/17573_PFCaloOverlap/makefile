default: RunCorrelation

Execute: PlotOverlap.cpp
	CompileRootMacro PlotOverlap.cpp Execute

RunCorrelation: Execute
	./Execute --HLTFile openHLT.root --HLTTree "hltbitanalysis/HltTree" \
		--CaloTrigger HLT_PuAK4CaloJet40Eta5p1_v1,HLT_PuAK4CaloJet50Eta5p1_v1,HLT_PuAK4CaloJet60Eta5p1_v1,HLT_PuAK4CaloJet70Eta5p1_v1,HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4CaloJet90Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4CaloJet110Eta5p1_v1,HLT_PuAK4CaloJet120Eta5p1_v1 \
		--CaloLabel Calo40,Calo50,Calo60,Calo70,Calo80,Calo90,Calo100,Calo110,Calo120 \
		--PFTrigger HLT_CsAK4PFJet60Eta1p5_v1,HLT_CsAK4PFJet70Eta1p5_v1,HLT_CsAK4PFJet80Eta1p5_v1,HLT_CsAK4PFJet90Eta1p5_v1,HLT_CsAK4PFJet100Eta1p5_v1,HLT_CsAK4PFJet110Eta1p5_v1,HLT_CsAK4PFJet120Eta1p5_v1 \
		--PFLabel PF60,PF70,PF80,PF90,PF100,PF110,PF120 \
		--Output IncreaseOnCalo.pdf
	./Execute --HLTFile openHLT.root --HLTTree "hltbitanalysis/HltTree" \
		--PFTrigger HLT_PuAK4CaloJet40Eta5p1_v1,HLT_PuAK4CaloJet50Eta5p1_v1,HLT_PuAK4CaloJet60Eta5p1_v1,HLT_PuAK4CaloJet70Eta5p1_v1,HLT_PuAK4CaloJet80Eta5p1_v1,HLT_PuAK4CaloJet90Eta5p1_v1,HLT_PuAK4CaloJet100Eta5p1_v1,HLT_PuAK4CaloJet110Eta5p1_v1,HLT_PuAK4CaloJet120Eta5p1_v1 \
		--PFLabel Calo40,Calo50,Calo60,Calo70,Calo80,Calo90,Calo100,Calo110,Calo120 \
		--CaloTrigger HLT_CsAK4PFJet60Eta1p5_v1,HLT_CsAK4PFJet70Eta1p5_v1,HLT_CsAK4PFJet80Eta1p5_v1,HLT_CsAK4PFJet90Eta1p5_v1,HLT_CsAK4PFJet100Eta1p5_v1,HLT_CsAK4PFJet110Eta1p5_v1,HLT_CsAK4PFJet120Eta1p5_v1 \
		--CaloLabel PF60,PF70,PF80,PF90,PF100,PF110,PF120 \
		--Output IncreaseOnPF.pdf
	cp *.pdf ~/public/html/
