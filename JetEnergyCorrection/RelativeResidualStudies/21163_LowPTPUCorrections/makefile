default: TestRun DebugRun FixedRun

Execute: PlotJEC.cpp
	CompileRootMacro PlotJEC.cpp Execute

TestRun: Execute
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros ./Execute \
		--jec1 Summer16_07Aug16_lowPU_lowpT_MPF_FLAT_L2Residual_AK4PFCHS.txt \
		--jec2 Summer16_07Aug16_lowPU_lowpT_MPF_FLAT_NOKFSR_L2Residual_AK4PFCHS.txt \
		--jec3 Summer16_07Aug16_lowPU_lowpT_MPF_LOGLIN_L2Residual_AK4PFCHS.txt \
		--jec4 Summer16_07Aug16_lowPU_lowpT_MPF_LOGLIN_NOKFSR_L2Residual_AK4PFCHS.txt \
		--output JEC.pdf \
		--label "Flat,Flat (no kFSR),LogLin,LogLin (no kFSR)"

DebugRun: Execute
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros ./Execute \
		--jec1 Summer16_07Aug16_lowPU_lowpT_MPF_FLAT_L2Residual_AK4PFCHS_FIX.txt \
		--jec2 Summer16_07Aug16_lowPU_lowpT_MPF_FLAT_NOKFSR_L2Residual_AK4PFCHS_FIX.txt \
		--jec3 Summer16_07Aug16_lowPU_lowpT_MPF_LOGLIN_L2Residual_AK4PFCHS_FIX.txt \
		--jec4 ParallelMC_L2Relative_AK4PF.txt \
		--output JECDebug.pdf \
		--label "Flat,Flat (no kFSR),LogLin,MCTruth L2Rel"

FixedRun: Execute
	LD_LIBRARY_PATH=/Users/yichen/Programs/root/build/lib:/Users/yichen/FHeadHelperCode/RootMacros ./Execute \
		--jec1 Summer16_07Aug16_lowPU_lowpT_MPF_FLAT_L2Residual_AK4PFCHS_FIX.txt \
		--jec2 Summer16_07Aug16_lowPU_lowpT_MPF_FLAT_NOKFSR_L2Residual_AK4PFCHS_FIX.txt \
		--jec3 Summer16_07Aug16_lowPU_lowpT_MPF_LOGLIN_L2Residual_AK4PFCHS_FIX.txt \
		--jec4 Summer16_07Aug16_lowPU_lowpT_MPF_LOGLIN_NOKFSR_L2Residual_AK4PFCHS_FIX.txt \
		--output JECFixed.pdf \
		--label "Flat,Flat (no kFSR),LogLin,LogLin (no kFSR)"
