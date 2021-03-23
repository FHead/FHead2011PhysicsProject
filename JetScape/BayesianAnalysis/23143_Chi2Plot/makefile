
default: Run

Run: Execute
	./Execute --Input txt/Result_LBT_-1_DataAll_MaternNoise_Nu2.5_Alpha0.2_Noise-1.0_CovTypeSeparated_EarthquakeFalse_BigEarthquakeFalse_SmoothingFalse_Time20200917-120009_NoModelChi2Values.txt --Output Chi2NoModel.eps --NDF 66 --Model LBT --Max 160
	epstopdf Chi2NoModel.eps
	./Execute --Input txt/Result_LBT_-1_DataAll_MaternNoise_Nu2.5_Alpha0.2_Noise-1.0_CovTypeSeparated_EarthquakeFalse_BigEarthquakeFalse_SmoothingFalse_Time20200917-120009_YesModelChi2Values.txt --Output Chi2YesModel.eps --NDF 66 --Model LBT --Max 100
	epstopdf Chi2YesModel.eps

Execute: MakeChi2Plot.cpp
	CompileRootMacro MakeChi2Plot.cpp Execute
