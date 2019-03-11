default: TestRun

Execute: PlotJEC.cpp
	CompileRootMacro PlotJEC.cpp Execute

RunPlot: Execute
	./Execute \
		--L2L3 Fall17_17Nov2017B_V32_DATA_L2L3Residual_AK4PFchs.txt \
		--Uncertainty Fall17_17Nov2017B_V32_DATA_Uncertainty_AK4PFchs.txt \
		--Label 2017B \
		--Output L2L3Res_2017B.pdf
	./Execute \
		--L2L3 Fall17_17Nov2017C_V32_DATA_L2L3Residual_AK4PFchs.txt \
		--Uncertainty Fall17_17Nov2017C_V32_DATA_Uncertainty_AK4PFchs.txt \
		--Label 2017C \
		--Output L2L3Res_2017C.pdf
	./Execute \
		--L2L3 Fall17_17Nov2017DE_V32_DATA_L2L3Residual_AK4PFchs.txt \
		--Uncertainty Fall17_17Nov2017DE_V32_DATA_Uncertainty_AK4PFchs.txt \
		--Label 2017DE \
		--Output L2L3Res_2017DE.pdf
	./Execute \
		--L2L3 Fall17_17Nov2017F_V32_DATA_L2L3Residual_AK4PFchs.txt \
		--Uncertainty Fall17_17Nov2017F_V32_DATA_Uncertainty_AK4PFchs.txt \
		--Label 2017F \
		--Output L2L3Res_2017F.pdf
	./Execute \
		--L2L3 Autumn18_RunA_V8_DATA_L2L3Residual_AK4PFchs.txt \
		--Uncertainty Autumn18_RunA_V8_DATA_Uncertainty_AK4PFchs.txt \
		--Label 2018A \
		--Output L2L3Res_2018A.pdf
	./Execute \
		--L2L3 Autumn18_RunB_V8_DATA_L2L3Residual_AK4PFchs.txt \
		--Uncertainty Autumn18_RunB_V8_DATA_Uncertainty_AK4PFchs.txt \
		--Label 2018B \
		--Output L2L3Res_2018B.pdf
	./Execute \
		--L2L3 Autumn18_RunC_V8_DATA_L2L3Residual_AK4PFchs.txt \
		--Uncertainty Autumn18_RunC_V8_DATA_Uncertainty_AK4PFchs.txt \
		--Label 2018C \
		--Output L2L3Res_2018C.pdf
	./Execute \
		--L2L3 Autumn18_RunD_V8_DATA_L2L3Residual_AK4PFchs.txt \
		--Uncertainty Autumn18_RunD_V8_DATA_Uncertainty_AK4PFchs.txt \
		--Label 2018D \
		--Output L2L3Res_2018D.pdf
	cp L2L3Res*.pdf ~/public/html/

TestRun: Execute
	./Execute \
		--L2L3 Autumn18_RunD_V8_DATA_L2L3Residual_AK4PFchs.txt \
		--Uncertainty Autumn18_RunD_V8_DATA_Uncertainty_AK4PFchs.txt \
		--Label 2018D \
		--Output L2L3Res_2018D.pdf
	cp L2L3Res*.pdf ~/public/html/


