
default: TestRun

Execute: ProcessSample.cpp
	CompileRootMacro ProcessSample.cpp Execute -g

TestRun: Execute
	time ./Execute --tag Result_Matter_-1_MaternNoise_Nu2.5_Alpha0.1_Noise-1.0_CovTypeSeparated_EarthquakeFalse_BigEarthquakeFalse_SmoothingFalse_Time20200623-182713 \
		--min 0,0,0,0 --max 2,20,2,20 \
		--name "A","B","C","D" \
		--transform false --setting Matter \
		--xmin 9,9,30,30,30,30 --xmax 20,20,90,90,100,100 \
		--ymin 0,0,0,0,0,0 --ymax 1.6,1.6,1.6,1.6,1.6,1.6 \
		--output root/Matter_TestRun.root

FullRun: RunMatter RunMatterLBT1 RunLBT RunMatterLBT2

RunMatter: Execute
	time ./Execute --tag `bash FindLatestTag.sh Matter All Separated` \
		--min 0,0,0,0 --max 2,20,2,20 \
		--name "A","B","C","D" \
		--transform false --setting Matter \
		--xmin 8,8,30,30,30,30 --xmax 20,20,90,90,100,100 \
		--ymin 0,0,0,0,0,0 --ymax 1.6,1.6,1.6,1.6,1.6,1.6 \
		--output root/Matter_NewSys.root

RunLBTOld: Execute
	time ./Execute --tag `bash FindLatestTag.sh LBT All Length0.2` \
		--min 0,0,0,0 --max 2,20,2,20 \
		--name "A","B","C","D" \
		--transform false --setting LBT \
		--xmin 8,8,8,8,8,8 --xmax 20,20,90,90,100,100 \
		--ymin 0,0,0,0,0,0 --ymax 1.6,1.6,1.6,1.6,1.6,1.6 \
		--output root/LBT_OldSys.root

RunLBT: Execute
	time ./Execute --tag `bash FindLatestTag.sh LBT All Separated` \
		--min 0,0,0,0 --max 2,20,2,20 \
		--name "A","B","C","D" \
		--transform false --setting LBT \
		--xmin 8,8,8,8,8,8 --xmax 20,20,90,90,100,100 \
		--ymin 0,0,0,0,0,0 --ymax 1.6,1.6,1.6,1.6,1.6,1.6 \
		--output root/LBT_NewSys.root

RunMatterLBT1: Execute
	time ./Execute --tag `bash FindLatestTag.sh MatterLBT1 All Separated` \
		--min 0,0,0,0,1 --max 1.5,1.5,20,20,4 \
		--name "A","C","B","D","Q" \
		--transform true --setting MatterLBT1 \
		--xmin 8,8,8,8,8,8 --xmax 20,20,90,90,100,100 \
		--ymin 0,0,0,0,0,0 --ymax 1.6,1.6,1.6,1.6,1.6,1.6 \
		--output root/MatterLBT1_NewSys.root
	time ./Execute --tag `bash FindLatestTag.sh MatterLBT1 RHIC Separated` \
		--min 0,0,0,0,1 --max 1.5,1.5,20,20,4 \
		--name "A","C","B","D","Q" \
		--transform true --setting MatterLBT1 \
		--xmin 8,8 --xmax 20,20 \
		--ymin 0,0 --ymax 1.6,1.6 \
		--output root/MatterLBT1_NewSys_RHIC.root
	time ./Execute --tag `bash FindLatestTag.sh MatterLBT1 LHC Separated` \
		--min 0,0,0,0,1 --max 1.5,1.5,20,20,4 \
		--name "A","C","B","D","Q" \
		--transform true --setting MatterLBT1 \
		--xmin 8,8,8,8 --xmax 90,90,100,100 \
		--ymin 0,0,0,0 --ymax 1.6,1.6,1.6,1.6 \
		--output root/MatterLBT1_NewSys_LHC.root

RunMatterLBT2: Execute
	time ./Execute --tag `bash FindLatestTag.sh MatterLBT2 All Separated` \
		--min 0,0,0,1 --max 2,2,20,4 \
		--name "A","C","D","Q" \
		--transform true --setting MatterLBT2 \
		--xmin 8,8,8,8,8,8 --xmax 20,20,90,90,100,100 \
		--ymin 0,0,0,0,0,0 --ymax 1.6,1.6,1.6,1.6,1.6,1.6 \
		--output root/MatterLBT2_NewSys.root
	time ./Execute --tag `bash FindLatestTag.sh MatterLBT2 RHIC Separated` \
		--min 0,0,0,1 --max 2,2,20,4 \
		--name "A","C","D","Q" \
		--transform true --setting MatterLBT2 \
		--xmin 8,8 --xmax 20,20 \
		--ymin 0,0 --ymax 1.6,1.6 \
		--output root/MatterLBT2_NewSys_RHIC.root
	time ./Execute --tag `bash FindLatestTag.sh MatterLBT2 LHC Separated` \
		--min 0,0,0,1 --max 2,2,20,4 \
		--name "A","C","D","Q" \
		--transform true --setting MatterLBT2 \
		--xmin 8,8,8,8 --xmax 90,90,100,100 \
		--ymin 0,0,0,0 --ymax 1.6,1.6,1.6,1.6 \
		--output root/MatterLBT2_NewSys_LHC.root

RunMatterLBT2Alternative: Execute
	time ./Execute --tag `bash FindLatestTag.sh MatterLBT2 All Separated10` \
		--min 0,0,0,1 --max 2,2,20,4 \
		--name "A","C","D","Q" \
		--transform true --setting MatterLBT2 \
		--xmin 8,8,8,8,8,8 --xmax 20,20,90,90,100,100 \
		--ymin 0,0,0,0,0,0 --ymax 1.6,1.6,1.6,1.6,1.6,1.6 \
		--output root/MatterLBT2Alternative_NewSys.root
	time ./Execute --tag `bash FindLatestTag.sh MatterLBT2 RHIC Separated10` \
		--min 0,0,0,1 --max 2,2,20,4 \
		--name "A","C","D","Q" \
		--transform true --setting MatterLBT2 \
		--xmin 8,8 --xmax 20,20 \
		--ymin 0,0 --ymax 1.6,1.6 \
		--output root/MatterLBT2Alternative_NewSys_RHIC.root
	time ./Execute --tag `bash FindLatestTag.sh MatterLBT2 LHC Separated10` \
		--min 0,0,0,1 --max 2,2,20,4 \
		--name "A","C","D","Q" \
		--transform true --setting MatterLBT2 \
		--xmin 8,8,8,8 --xmax 90,90,100,100 \
		--ymin 0,0,0,0 --ymax 1.6,1.6,1.6,1.6 \
		--output root/MatterLBT2Alternative_NewSys_LHC.root



