PbPbFile = "MC/PbPbAK4PF.txt","Autumn18_V18/Uncertainty_AbsoluteStat.txt","Autumn18_V18/Uncertainty_AbsoluteScale.txt","Autumn18_V18/Uncertainty_AbsoluteMPFBias.txt","Autumn18_V18/Uncertainty_Fragmentation.txt","Autumn18_V18/Uncertainty_SinglePionECAL.txt","Autumn18_V18/Uncertainty_SinglePionHCAL.txt","Autumn18_V18/Uncertainty_FlavorQCD.txt","Autumn18_V18_RelativeStat.txt","StepanL2/pbpb_v14_unc_pt.txt","StepanL2/pbpb_v14_unc_balance.txt","StepanL2/pbpb_unc_jer.txt","Uncertainty_FlatPbPb.txt"
PbPbTag = "MC","AbsStat","AbsScale","AbsMPF","Frag","ECAL","HCAL","Flavor","RelStat","RelPt","RelBal","RelJER","L3Res"
PPFile = "MC/PPAK4PF.txt","Fall17_V32/Uncertainty_AbsoluteStat.txt","Fall17_V32/Uncertainty_AbsoluteScale.txt","Fall17_V32/Uncertainty_AbsoluteMPFBias.txt","Fall17_V32/Uncertainty_Fragmentation.txt","Fall17_V32/Uncertainty_SinglePionECAL.txt","Fall17_V32/Uncertainty_SinglePionHCAL.txt","Fall17_V32/Uncertainty_FlavorQCD.txt","Fall17_V32_RelativeStat.txt","StepanL2/pp_v8_unc_pt.txt","StepanL2/pp_v8_unc_balance.txt","StepanL2/pp_unc_jer.txt","Uncertainty_Flat.txt"
PPTag = "MC","AbsStat","AbsScale","AbsMPF","Frag","ECAL","HCAL","Flavor","RelStat","RelPt","RelBal","RelJER","L3Res"

PbPbCommon = "Autumn18_V18/Uncertainty_AbsoluteStat.txt","Autumn18_V18/Uncertainty_AbsoluteScale.txt","Autumn18_V18/Uncertainty_AbsoluteMPFBias.txt","Autumn18_V18/Uncertainty_Fragmentation.txt","Autumn18_V18/Uncertainty_SinglePionECAL.txt","Autumn18_V18/Uncertainty_SinglePionHCAL.txt","Autumn18_V18/Uncertainty_FlavorQCD.txt","Autumn18_V18_RelativeStat.txt","StepanL2/pbpb_v14_unc_pt.txt","StepanL2/pbpb_v14_unc_balance.txt","StepanL2/pbpb_unc_jer.txt","Uncertainty_FlatPbPb.txt"
PbPbAK2File = "MC/PbPbAK2PF.txt",$(PbPbCommon)
PbPbAK3File = "MC/PbPbAK3PF.txt",$(PbPbCommon)
PbPbAK4File = "MC/PbPbAK4PF.txt",$(PbPbCommon)
PbPbAK5File = "MC/PbPbAK5PF.txt",$(PbPbCommon)
PbPbAK6File = "MC/PbPbAK6PF.txt",$(PbPbCommon)
PPCommon = "Fall17_V32/Uncertainty_AbsoluteStat.txt","Fall17_V32/Uncertainty_AbsoluteScale.txt","Fall17_V32/Uncertainty_AbsoluteMPFBias.txt","Fall17_V32/Uncertainty_Fragmentation.txt","Fall17_V32/Uncertainty_SinglePionECAL.txt","Fall17_V32/Uncertainty_SinglePionHCAL.txt","Fall17_V32/Uncertainty_FlavorQCD.txt","Fall17_V32_RelativeStat.txt","StepanL2/pp_v8_unc_pt.txt","StepanL2/pp_v8_unc_balance.txt","StepanL2/pp_unc_jer.txt","Uncertainty_Flat.txt"
PPAK2File = "MC/PPAK2PF.txt",$(PPCommon)
PPAK3File = "MC/PPAK3PF.txt",$(PPCommon)
PPAK4File = "MC/PPAK4PF.txt",$(PPCommon)
PPAK5File = "MC/PPAK5PF.txt",$(PPCommon)
PPAK6File = "MC/PPAK6PF.txt",$(PPCommon)
Tag = "MC","AbsStat","AbsScale","AbsMPF","Frag","ECAL","HCAL","Flavor","RelStat","RelPt","RelBal","RelJER","L3Res"

VPbPb = Autumn18_HI_V6
VPP = Spring18_ppRef5TeV_V4

TestRun: Execute
	./Execute \
		--FileNames "Autumn18_V18/Uncertainty_RelativeStatHF.txt","Autumn18_V18/Uncertainty_RelativeStatEC.txt","Autumn18_V18/Uncertainty_RelativeStatFSR.txt" \
		--Tags "RelStatHF","RelStatEC","RelStatFSR" \
		--Output Autumn18_V18_RelativeStat
	./Execute \
		--FileNames $(PbPbFile) \
		--Tags $(PbPbTag) \
		--Output TotalPbPb
	./Execute \
		--FileNames "Fall17_V32/Uncertainty_RelativeStatHF.txt","Fall17_V32/Uncertainty_RelativeStatEC.txt","Fall17_V32/Uncertainty_RelativeStatFSR.txt" \
		--Tags "RelStatHF","RelStatEC","RelStatFSR" \
		--Output Fall17_V32_RelativeStat
	./Execute \
		--FileNames $(PPFile) \
		--Tags $(PPTag) \
		--Output TotalPP
	bash CombineFile.sh $(PbPbFile),"TotalPbPb.txt" $(PbPbTag),"Total" > SourcePbPb.txt
	bash CombineFile.sh $(PPFile),"TotalPP.txt" $(PPTag),"Total" > SourcePP.txt
	cp Total*.pdf ~/public/html/

ProductionRun: Execute
	./Execute \
		--FileNames "Autumn18_V18/Uncertainty_RelativeStatHF.txt","Autumn18_V18/Uncertainty_RelativeStatEC.txt","Autumn18_V18/Uncertainty_RelativeStatFSR.txt" \
		--Tags "RelStatHF","RelStatEC","RelStatFSR" \
		--Output Autumn18_V18_RelativeStat
	./Execute \
		--FileNames "Fall17_V32/Uncertainty_RelativeStatHF.txt","Fall17_V32/Uncertainty_RelativeStatEC.txt","Fall17_V32/Uncertainty_RelativeStatFSR.txt" \
		--Tags "RelStatHF","RelStatEC","RelStatFSR" \
		--Output Fall17_V32_RelativeStat
	./Execute --FileNames $(PbPbAK2File) --Tags $(Tag) --Output TotalPbPbAK2
	./Execute --FileNames $(PbPbAK3File) --Tags $(Tag) --Output TotalPbPbAK3
	./Execute --FileNames $(PbPbAK4File) --Tags $(Tag) --Output TotalPbPbAK4
	./Execute --FileNames $(PbPbAK5File) --Tags $(Tag) --Output TotalPbPbAK5
	./Execute --FileNames $(PbPbAK6File) --Tags $(Tag) --Output TotalPbPbAK6
	./Execute --FileNames $(PPAK2File)   --Tags $(Tag) --Output TotalPPAK2
	./Execute --FileNames $(PPAK3File)   --Tags $(Tag) --Output TotalPPAK3
	./Execute --FileNames $(PPAK4File)   --Tags $(Tag) --Output TotalPPAK4
	./Execute --FileNames $(PPAK5File)   --Tags $(Tag) --Output TotalPPAK5
	./Execute --FileNames $(PPAK6File)   --Tags $(Tag) --Output TotalPPAK6
	bash CombineFile.sh $(PbPbAK2File),"TotalPbPbAK2.txt" $(Tag),"Total" > SourcePbPbAK2.txt
	bash CombineFile.sh $(PbPbAK3File),"TotalPbPbAK3.txt" $(Tag),"Total" > SourcePbPbAK3.txt
	bash CombineFile.sh $(PbPbAK4File),"TotalPbPbAK4.txt" $(Tag),"Total" > SourcePbPbAK4.txt
	bash CombineFile.sh $(PbPbAK5File),"TotalPbPbAK5.txt" $(Tag),"Total" > SourcePbPbAK5.txt
	bash CombineFile.sh $(PbPbAK6File),"TotalPbPbAK6.txt" $(Tag),"Total" > SourcePbPbAK6.txt
	bash CombineFile.sh $(PPAK2File),"TotalPPAK2.txt" $(Tag),"Total" > SourcePPAK2.txt
	bash CombineFile.sh $(PPAK3File),"TotalPPAK3.txt" $(Tag),"Total" > SourcePPAK3.txt
	bash CombineFile.sh $(PPAK4File),"TotalPPAK4.txt" $(Tag),"Total" > SourcePPAK4.txt
	bash CombineFile.sh $(PPAK5File),"TotalPPAK5.txt" $(Tag),"Total" > SourcePPAK5.txt
	bash CombineFile.sh $(PPAK6File),"TotalPPAK6.txt" $(Tag),"Total" > SourcePPAK6.txt
	cp Total*pdf ~/public/html

Deploy:
	for i in JECDatabase/$(VPbPb)_*/*_Uncertainty_*; do \
		cp TotalPbPbAK4.txt $$i; \
		cp SourcePbPbAK4.txt $${i/Uncertainty/UncertaintySources}; \
		done
	for i in JECDatabase/$(VPP)_*/*_Uncertainty_*; do \
		cp TotalPPAK4.txt $$i; \
		cp SourcePPAK4.txt $${i/Uncertainty/UncertaintySources}; \
		done
	for i in 2 3 4 5 6; do \
		cp TotalPbPbAK$${i}.txt JECDatabase/$(VPbPb)_DATA/$(VPbPb)_DATA_Uncertainty_AK$${i}PF.txt; \
		cp SourcePbPbAK$${i}.txt JECDatabase/$(VPbPb)_DATA/$(VPbPb)_DATA_UncertaintySources_AK$${i}PF.txt; \
		cp TotalPbPbAK$${i}.txt JECDatabase/$(VPbPb)_MC/$(VPbPb)_MC_Uncertainty_AK$${i}PF.txt; \
		cp SourcePbPbAK$${i}.txt JECDatabase/$(VPbPb)_MC/$(VPbPb)_MC_UncertaintySources_AK$${i}PF.txt; \
		cp TotalPPAK$${i}.txt JECDatabase/$(VPP)_DATA/$(VPP)_DATA_Uncertainty_AK$${i}PF.txt; \
		cp SourcePPAK$${i}.txt JECDatabase/$(VPP)_DATA/$(VPP)_DATA_UncertaintySources_AK$${i}PF.txt; \
		cp TotalPPAK$${i}.txt JECDatabase/$(VPP)_MC/$(VPP)_MC_Uncertainty_AK$${i}PF.txt; \
		cp SourcePPAK$${i}.txt JECDatabase/$(VPP)_MC/$(VPP)_MC_UncertaintySources_AK$${i}PF.txt; \
		done

Execute: CombineUncertainties.cpp
	CompileRootMacro CombineUncertainties.cpp Execute
