
default: RunScatterPlot

ExecuteScatterPlot: MakeScatterPlot.cpp
	CompileRootMacro MakeScatterPlot.cpp ExecuteScatterPlot

RunScatterPlot: ExecuteScatterPlot
	./ExecuteScatterPlot \
		--file txt_batch1/Result_Matter_-1_MaternNoise_Nu2.5_Alpha0.1_Noise-1.0_CovTypeSeparated_EarthquakeFalse_BigEarthquakeFalse_SmoothingFalse_Time20200622-231730_MCMCSamples.txt \
		--transform false \
		--name "A","B","C","D" \
		--min 0,0,0,0 \
		--max 2,20,2,20 \
		--model Matter \
		--detail "RHIC+LHC","Better systematics" \
		--output ScatterMatter.pdf
	./ExecuteScatterPlot \
		--file txt_batch1/Result_LBT_-1_MaternNoise_Nu2.5_Alpha0.1_Noise-1.0_CovTypeSeparated_EarthquakeFalse_BigEarthquakeFalse_SmoothingFalse_Time20200622-232840_MCMCSamples.txt \
		--transform false \
		--name "A","B","C","D" \
		--min 0,0,0,0 \
		--max 2,20,2,20 \
		--model LBT \
		--detail "RHIC+LHC","Better systematics" \
		--output ScatterLBT.pdf
	./ExecuteScatterPlot \
		--file txt_batch1/Result_MatterLBT1_-1_MaternNoise_Nu2.5_Alpha0.15_Noise-1.0_CovTypeSeparated_EarthquakeFalse_BigEarthquakeFalse_SmoothingFalse_Time20200622-233401_MCMCSamples.txt \
		--transform true \
		--name "A","C","B","D","Q" \
		--min 0,0,0,0,1 \
		--max 1.5,1.5,20,20,4 \
		--model MatterLBT1 \
		--detail "RHIC+LHC","Better systematics" \
		--output ScatterMatterLBT1.pdf
	./ExecuteScatterPlot \
		--file txt_batch1/Result_MatterLBT2_-1_MaternNoise_Nu2.5_Alpha0.15_Noise-1.0_CovTypeSeparated_EarthquakeFalse_BigEarthquakeFalse_SmoothingFalse_Time20200622-234047_MCMCSamples.txt \
		--transform true \
		--name "A","C","D","Q" \
		--min 0,0,0,1 \
		--max 2,2,20,4 \
		--model MatterLBT2 \
		--detail "RHIC+LHC","Better systematics" \
		--output ScatterMatterLBT2.pdf
	cp *pdf ~/WindowsHome/Downloads/
