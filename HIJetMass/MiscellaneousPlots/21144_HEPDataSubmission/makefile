FIX = LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros

default: RunExport Check ZipFile

ZipFile: *yaml
	tar zcvf SubmitHIN16024.tar.gz *yaml

MergeTree:
	hadd -f HEPDataGraphs.root Figure*Graphs.root

Execute: ExportYaml.cpp
	CompileRootMacro ExportYaml.cpp ./Execute

RunExport: Execute
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure1a.yaml \
		--graph "Comparison_PP_SD7" \
		--graphsys "" \
		--x "name: \"p_(T,g) / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(p_(T,g) / p_T^(jet))\"" \
		--qualifier "NONE" \
		--type PP \
		--ptbin 1 \
		--cbin -1 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure1b.yaml \
		--graph "Comparison_AA_SD7" \
		--graphsys "" \
		--x "name: \"p_(T,g) / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(p_(T,g) / p_T^(jet))\"" \
		--qualifier "NONE" \
		--type AA \
		--ptbin 1 \
		--cbin 0 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure2a.yaml \
		--graph "Figure2_SD0" \
		--graphsys "Figure2_SD0_Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "NONE" \
		--type PP \
		--ptbin 2 \
		--cbin -1 \
		--sd 0
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure2b.yaml \
		--graph "Figure2_SD7" \
		--graphsys "Figure2_SD7_Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "NONE" \
		--type PP \
		--ptbin 2 \
		--cbin -1 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure3a.yaml \
		--graph "Spectrum_SD0_PTBin2_AACBin0,Spectrum_SD0_PTBin2_PPCBin0,Spectrum_SD0_PTBin2_AACBin1,Spectrum_SD0_PTBin2_PPCBin1,Spectrum_SD0_PTBin2_AACBin2,Spectrum_SD0_PTBin2_PPCBin2,Spectrum_SD0_PTBin2_AACBin3,Spectrum_SD0_PTBin2_PPCBin3" \
		--graphsys "Spectrum_SD0_PTBin2_AACBin0Sys,Spectrum_SD0_PTBin2_PPCBin0Sys,Spectrum_SD0_PTBin2_AACBin1Sys,Spectrum_SD0_PTBin2_PPCBin1Sys,Spectrum_SD0_PTBin2_AACBin2Sys,Spectrum_SD0_PTBin2_PPCBin2Sys,Spectrum_SD0_PTBin2_AACBin3Sys,Spectrum_SD0_PTBin2_PPCBin3Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "0-10 PERCENTILE PbPb,0-10 PERCENTILE PP Smeared,10-30 PERCENTILE PbPb,10-30 PERCENTILE PP Smeared,30-50 PERCENTILE PbPb,30-50 PERCENTILE PP Smeared,50-80 PERCENTILE PbPb,50-80 PERCENTILE PP Smeared" \
		--type "AA,PP,AA,PP,AA,PP,AA,PP" \
		--ptbin "2,2,2,2,2,2,2,2" \
		--cbin "0,0,1,1,2,2,3,3" \
		--sd "0,0,0,0,0,0,0,0"
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure3b.yaml \
		--graph "Ratio_SD0_PTBin2_CBin0,Ratio_SD0_PTBin2_CBin1,Ratio_SD0_PTBin2_CBin2,Ratio_SD0_PTBin2_CBin3" \
		--graphsys "Ratio_SD0_PTBin2_CBin0Sys,Ratio_SD0_PTBin2_CBin1Sys,Ratio_SD0_PTBin2_CBin2Sys,Ratio_SD0_PTBin2_CBin3Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"PbPb / smeared pp\"" \
		--qualifier "NONE,NONE,NONE,NONE" \
		--type "BOTH,BOTH,BOTH,BOTH" \
		--ptbin "2,2,2,2" \
		--cbin "0,1,2,3" \
		--sd "0,0,0,0"
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure4a.yaml \
		--graph "Spectrum_SD7_PTBin2_AACBin0,Spectrum_SD7_PTBin2_PPCBin0,Spectrum_SD7_PTBin2_AACBin1,Spectrum_SD7_PTBin2_PPCBin1,Spectrum_SD7_PTBin2_AACBin2,Spectrum_SD7_PTBin2_PPCBin2,Spectrum_SD7_PTBin2_AACBin3,Spectrum_SD7_PTBin2_PPCBin3" \
		--graphsys "Spectrum_SD7_PTBin2_AACBin0Sys,Spectrum_SD7_PTBin2_PPCBin0Sys,Spectrum_SD7_PTBin2_AACBin1Sys,Spectrum_SD7_PTBin2_PPCBin1Sys,Spectrum_SD7_PTBin2_AACBin2Sys,Spectrum_SD7_PTBin2_PPCBin2Sys,Spectrum_SD7_PTBin2_AACBin3Sys,Spectrum_SD7_PTBin2_PPCBin3Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "0-10 PERCENTILE PbPb,0-10 PERCENTILE PP Smeared,10-30 PERCENTILE PbPb,10-30 PERCENTILE PP Smeared,30-50 PERCENTILE PbPb,30-50 PERCENTILE PP Smeared,50-80 PERCENTILE PbPb,50-80 PERCENTILE PP Smeared" \
		--type "AA,PP,AA,PP,AA,PP,AA,PP" \
		--ptbin "2,2,2,2,2,2,2,2" \
		--cbin "0,0,1,1,2,2,3,3" \
		--sd "7,7,7,7,7,7,7,7"
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure4b.yaml \
		--graph "Ratio_SD7_PTBin2_CBin0,Ratio_SD7_PTBin2_CBin1,Ratio_SD7_PTBin2_CBin2,Ratio_SD7_PTBin2_CBin3" \
		--graphsys "Ratio_SD7_PTBin2_CBin0Sys,Ratio_SD7_PTBin2_CBin1Sys,Ratio_SD7_PTBin2_CBin2Sys,Ratio_SD7_PTBin2_CBin3Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"PbPb / smeared pp\"" \
		--qualifier "NONE,NONE,NONE,NONE" \
		--type "BOTH,BOTH,BOTH,BOTH" \
		--ptbin "2,2,2,2" \
		--cbin "0,1,2,3" \
		--sd "7,7,7,7"
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure5a.yaml \
		--graph "Spectrum_SD0_CBin0_AAPTBin1,Spectrum_SD0_CBin0_PPPTBin1,Spectrum_SD0_CBin0_AAPTBin2,Spectrum_SD0_CBin0_PPPTBin2,Spectrum_SD0_CBin0_AAPTBin3,Spectrum_SD0_CBin0_PPPTBin3,Spectrum_SD0_CBin0_AAPTBin4,Spectrum_SD0_CBin0_PPPTBin4" \
		--graphsys "Spectrum_SD0_CBin0_AAPTBin1Sys,Spectrum_SD0_CBin0_PPPTBin1Sys,Spectrum_SD0_CBin0_AAPTBin2Sys,Spectrum_SD0_CBin0_PPPTBin2Sys,Spectrum_SD0_CBin0_AAPTBin3Sys,Spectrum_SD0_CBin0_PPPTBin3Sys,Spectrum_SD0_CBin0_AAPTBin4Sys,Spectrum_SD0_CBin0_PPPTBin4Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "140-160 GEV PbPb,140-160 GEV PP Smeared,160-180 GEV PbPb,160-180 GEV PP Smeared,180-200 GEV PbPb,180-200 GEV PP Smeared,200-300 GEV PbPb,200-300 GEV PP Smeared" \
		--type "AA,PP,AA,PP,AA,PP,AA,PP" \
		--ptbin "1,1,2,2,3,3,4,4" \
		--cbin "0,0,0,0,0,0,0,0" \
		--sd "0,0,0,0,0,0,0,0"
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure5b.yaml \
		--graph "Ratio_SD0_CBin0_PTBin1,Ratio_SD0_CBin0_PTBin2,Ratio_SD0_CBin0_PTBin3,Ratio_SD0_CBin0_PTBin4" \
		--graphsys "Ratio_SD0_CBin0_PTBin1Sys,Ratio_SD0_CBin0_PTBin2Sys,Ratio_SD0_CBin0_PTBin3Sys,Ratio_SD0_CBin0_PTBin4Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"PbPb / smeared pp\"" \
		--qualifier "NONE,NONE,NONE,NONE" \
		--type "BOTH,BOTH,BOTH,BOTH" \
		--ptbin "1,2,3,4" \
		--cbin "0,0,0,0" \
		--sd "0,0,0,0"
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure6a.yaml \
		--graph "Spectrum_SD7_CBin0_AAPTBin1,Spectrum_SD7_CBin0_PPPTBin1,Spectrum_SD7_CBin0_AAPTBin2,Spectrum_SD7_CBin0_PPPTBin2,Spectrum_SD7_CBin0_AAPTBin3,Spectrum_SD7_CBin0_PPPTBin3,Spectrum_SD7_CBin0_AAPTBin4,Spectrum_SD7_CBin0_PPPTBin4" \
		--graphsys "Spectrum_SD7_CBin0_AAPTBin1Sys,Spectrum_SD7_CBin0_PPPTBin1Sys,Spectrum_SD7_CBin0_AAPTBin2Sys,Spectrum_SD7_CBin0_PPPTBin2Sys,Spectrum_SD7_CBin0_AAPTBin3Sys,Spectrum_SD7_CBin0_PPPTBin3Sys,Spectrum_SD7_CBin0_AAPTBin4Sys,Spectrum_SD7_CBin0_PPPTBin4Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "140-160 GEV PbPb,140-160 GEV PP Smeared,160-180 GEV PbPb,160-180 GEV PP Smeared,180-200 GEV PbPb,180-200 GEV PP Smeared,200-300 GEV PbPb,200-300 GEV PP Smeared" \
		--type "AA,PP,AA,PP,AA,PP,AA,PP" \
		--ptbin "1,1,2,2,3,3,4,4" \
		--cbin "0,0,0,0,0,0,0,0" \
		--sd "7,7,7,7,7,7,7,7"
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure6b.yaml \
		--graph "Ratio_SD7_CBin0_PTBin1,Ratio_SD7_CBin0_PTBin2,Ratio_SD7_CBin0_PTBin3,Ratio_SD7_CBin0_PTBin4" \
		--graphsys "Ratio_SD7_CBin0_PTBin1Sys,Ratio_SD7_CBin0_PTBin2Sys,Ratio_SD7_CBin0_PTBin3Sys,Ratio_SD7_CBin0_PTBin4Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"PbPb / smeared pp\"" \
		--qualifier "NONE,NONE,NONE,NONE" \
		--type "BOTH,BOTH,BOTH,BOTH" \
		--ptbin "1,2,3,4" \
		--cbin "0,0,0,0" \
		--sd "7,7,7,7"

RunExportFull: Execute
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure1a.yaml \
		--graph "Comparison_PP_SD7" \
		--graphsys "" \
		--x "name: \"p_(T,g) / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(p_(T,g) / p_T^(jet))\"" \
		--qualifier "@name: Label, value: Groomed jet momentum fraction in pp@" \
		--type PP \
		--ptbin 1 \
		--cbin -1 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure1b.yaml \
		--graph "Comparison_AA_SD7" \
		--graphsys "" \
		--x "name: \"p_(T,g) / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(p_(T,g) / p_T^(jet))\"" \
		--qualifier "@name: Label, value: Groomed jet momentum fraction in PbPb@" \
		--type AA \
		--ptbin 1 \
		--cbin 0 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure2a.yaml \
		--graph "Figure2_SD0" \
		--graphsys "Figure2_SD0_Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.1, 0.0) SD setting\"@" \
		--type PP \
		--ptbin 1 \
		--cbin -1 \
		--sd 0
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure2b.yaml \
		--graph "Figure2_SD7" \
		--graphsys "Figure2_SD7_Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.5, 1.5) SD setting\"@" \
		--type PP \
		--ptbin 1 \
		--cbin -1 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure3a.yaml \
		--graph "Spectrum_SD0_PTBin2_AACBin0,Spectrum_SD0_PTBin2_PPCBin0,Spectrum_SD0_PTBin2_AACBin1,Spectrum_SD0_PTBin2_PPCBin1,Spectrum_SD0_PTBin2_AACBin2,Spectrum_SD0_PTBin2_PPCBin2,Spectrum_SD0_PTBin2_AACBin3,Spectrum_SD0_PTBin2_PPCBin3" \
		--graphsys "Spectrum_SD0_PTBin2_AACBin0Sys,Spectrum_SD0_PTBin2_PPCBin0Sys,Spectrum_SD0_PTBin2_AACBin1Sys,Spectrum_SD0_PTBin2_PPCBin1Sys,Spectrum_SD0_PTBin2_AACBin2Sys,Spectrum_SD0_PTBin2_PPCBin2Sys,Spectrum_SD0_PTBin2_AACBin3Sys,Spectrum_SD0_PTBin2_PPCBin3Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 10-30%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 10-30%\"@,@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 30-50%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 30-50%\"@,@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 50-80%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 50-80%\"@" \
		--type BOTH \
		--ptbin 1 \
		--cbin -1 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure3b.yaml \
		--graph "Ratio_SD0_PTBin2_CBin0,Ratio_SD0_PTBin2_CBin1,Ratio_SD0_PTBin2_CBin2,Ratio_SD0_PTBin2_CBin3" \
		--graphsys "Ratio_SD0_PTBin2_CBin0Sys,Ratio_SD0_PTBin2_CBin1Sys,Ratio_SD0_PTBin2_CBin2Sys,Ratio_SD0_PTBin2_CBin3Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 0-10%\"@,@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 10-30%\"@,@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 30-50%\"@,@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 50-80%\"@" \
		--type PP \
		--ptbin 1 \
		--cbin -1 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure4a.yaml \
		--graph "Spectrum_SD7_PTBin2_AACBin0,Spectrum_SD7_PTBin2_PPCBin0,Spectrum_SD7_PTBin2_AACBin1,Spectrum_SD7_PTBin2_PPCBin1,Spectrum_SD7_PTBin2_AACBin2,Spectrum_SD7_PTBin2_PPCBin2,Spectrum_SD7_PTBin2_AACBin3,Spectrum_SD7_PTBin2_PPCBin3" \
		--graphsys "Spectrum_SD7_PTBin2_AACBin0Sys,Spectrum_SD7_PTBin2_PPCBin0Sys,Spectrum_SD7_PTBin2_AACBin1Sys,Spectrum_SD7_PTBin2_PPCBin1Sys,Spectrum_SD7_PTBin2_AACBin2Sys,Spectrum_SD7_PTBin2_PPCBin2Sys,Spectrum_SD7_PTBin2_AACBin3Sys,Spectrum_SD7_PTBin2_PPCBin3Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 10-30%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 10-30%\"@,@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 30-50%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 30-50%\"@,@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 50-80%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 50-80%\"@" \
		--type PP \
		--ptbin 1 \
		--cbin -1 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure4b.yaml \
		--graph "Ratio_SD7_PTBin2_CBin0,Ratio_SD7_PTBin2_CBin1,Ratio_SD7_PTBin2_CBin2,Ratio_SD7_PTBin2_CBin3" \
		--graphsys "Ratio_SD7_PTBin2_CBin0Sys,Ratio_SD7_PTBin2_CBin1Sys,Ratio_SD7_PTBin2_CBin2Sys,Ratio_SD7_PTBin2_CBin3Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 0-10%\"@,@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 10-30%\"@,@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 30-50%\"@,@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 50-80%\"@" \
		--type PP \
		--ptbin 1 \
		--cbin -1 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure5a.yaml \
		--graph "Spectrum_SD0_CBin0_AAPTBin1,Spectrum_SD0_CBin0_PPPTBin1,Spectrum_SD0_CBin0_AAPTBin2,Spectrum_SD0_CBin0_PPPTBin2,Spectrum_SD0_CBin0_AAPTBin3,Spectrum_SD0_CBin0_PPPTBin3,Spectrum_SD0_CBin0_AAPTBin4,Spectrum_SD0_CBin0_PPPTBin4" \
		--graphsys "Spectrum_SD0_CBin0_AAPTBin1Sys,Spectrum_SD0_CBin0_PPPTBin1Sys,Spectrum_SD0_CBin0_AAPTBin2Sys,Spectrum_SD0_CBin0_PPPTBin2Sys,Spectrum_SD0_CBin0_AAPTBin3Sys,Spectrum_SD0_CBin0_PPPTBin3Sys,Spectrum_SD0_CBin0_AAPTBin4Sys,Spectrum_SD0_CBin0_PPPTBin4Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.1, 0.0) SD setting for jets between 140-160 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.1, 0.0) SD setting for jets between 140-160 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.1, 0.0) SD setting for jets between 180-200 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.1, 0.0) SD setting for jets between 180-200 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.1, 0.0) SD setting for jets between 200-300 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.1, 0.0) SD setting for jets between 200-300 GeV and with event class 0-10%\"@" \
		--type PP \
		--ptbin 1 \
		--cbin -1 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure5b.yaml \
		--graph "Ratio_SD0_CBin0_PTBin1,Ratio_SD0_CBin0_PTBin2,Ratio_SD0_CBin0_PTBin3,Ratio_SD0_CBin0_PTBin4" \
		--graphsys "Ratio_SD0_CBin0_PTBin1Sys,Ratio_SD0_CBin0_PTBin2Sys,Ratio_SD0_CBin0_PTBin3Sys,Ratio_SD0_CBin0_PTBin4Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.1, 0.0) SD setting for jets between 140-160 GeV and with event class 0-10%\"@,@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.1, 0.0) SD setting for jets between 160-180 GeV and with event class 0-10%\"@,@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.1, 0.0) SD setting for jets between 180-200 GeV and with event class 0-10%\"@,@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.1, 0.0) SD setting for jets between 200-300 GeV and with event class 0-10%\"@" \
		--type PP \
		--ptbin 1 \
		--cbin -1 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure6a.yaml \
		--graph "Spectrum_SD7_CBin0_AAPTBin1,Spectrum_SD7_CBin0_PPPTBin1,Spectrum_SD7_CBin0_AAPTBin2,Spectrum_SD7_CBin0_PPPTBin2,Spectrum_SD7_CBin0_AAPTBin3,Spectrum_SD7_CBin0_PPPTBin3,Spectrum_SD7_CBin0_AAPTBin4,Spectrum_SD7_CBin0_PPPTBin4" \
		--graphsys "Spectrum_SD7_CBin0_AAPTBin1Sys,Spectrum_SD7_CBin0_PPPTBin1Sys,Spectrum_SD7_CBin0_AAPTBin2Sys,Spectrum_SD7_CBin0_PPPTBin2Sys,Spectrum_SD7_CBin0_AAPTBin3Sys,Spectrum_SD7_CBin0_PPPTBin3Sys,Spectrum_SD7_CBin0_AAPTBin4Sys,Spectrum_SD7_CBin0_PPPTBin4Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.5, 1.5) SD setting for jets between 140-160 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.5, 1.5) SD setting for jets between 140-160 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.5, 1.5) SD setting for jets between 180-200 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.5, 1.5) SD setting for jets between 180-200 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in PbPb collision for (0.5, 1.5) SD setting for jets between 200-300 GeV and with event class 0-10%\"@,@name: Label, value: \"Groomed jet mass spectrum in pp collision for (0.5, 1.5) SD setting for jets between 200-300 GeV and with event class 0-10%\"@" \
		--type PP \
		--ptbin 1 \
		--cbin -1 \
		--sd 7
	$(FIX) ./Execute --input HEPDataGraphs.root --output Figure6b.yaml \
		--graph "Ratio_SD7_CBin0_PTBin1,Ratio_SD7_CBin0_PTBin2,Ratio_SD7_CBin0_PTBin3,Ratio_SD7_CBin0_PTBin4" \
		--graphsys "Ratio_SD7_CBin0_PTBin1Sys,Ratio_SD7_CBin0_PTBin2Sys,Ratio_SD7_CBin0_PTBin3Sys,Ratio_SD7_CBin0_PTBin4Sys" \
		--x "name: \"M_g / p_T^(jet)\"" \
		--y "name: \"1/N * dN / d(M_g / p_T^(jet))\"" \
		--qualifier "@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.5, 1.5) SD setting for jets between 140-160 GeV and with event class 0-10%\"@,@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.5, 1.5) SD setting for jets between 160-180 GeV and with event class 0-10%\"@,@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.5, 1.5) SD setting for jets between 180-200 GeV and with event class 0-10%\"@,@name: Label, value: \"Ratio of groomed jet mass spectrum between PbPb and pp collision for (0.5, 1.5) SD setting for jets between 200-300 GeV and with event class 0-10%\"@" \
		--type PP \
		--ptbin 1 \
		--cbin -1 \
		--sd 7

Check:
	python check.py
