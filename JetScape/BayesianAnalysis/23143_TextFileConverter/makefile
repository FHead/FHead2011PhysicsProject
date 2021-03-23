
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
	# Tag=`bash FindLatestTag.sh Matter All Separated`
	# cp Prior/Matter.txt txt/$${Tag}_QHatPrior.txt
	bunzip2 txt/`bash FindLatestTag.sh Matter All Separated`_*.bz2
	cp Prior/Matter.txt txt/`bash FindLatestTag.sh Matter All Separated`_QHatPrior.txt
	time ./Execute --tag `bash FindLatestTag.sh Matter All Separated` \
		--min 0,0,0,0 --max 2,20,2,20 \
		--name "A","B","C","D" \
		--transform false --setting Matter \
		--xmin 8,8,30,30,30,30 --xmax 20,20,90,90,100,100 \
		--ymin 0,0,0,0,0,0 --ymax 1.6,1.6,1.6,1.6,1.6,1.6 \
		--output root/Matter_NewSys.root
	bzip2 txt/`bash FindLatestTag.sh Matter All Separated`_*txt

RunLBTOld: Execute
	time ./Execute --tag `bash FindLatestTag.sh LBT All Length0.2` \
		--min 0,0,0,0 --max 2,20,2,20 \
		--name "A","B","C","D" \
		--transform false --setting LBT \
		--xmin 8,8,8,8,8,8 --xmax 20,20,90,90,100,100 \
		--ymin 0,0,0,0,0,0 --ymax 1.6,1.6,1.6,1.6,1.6,1.6 \
		--output root/LBT_OldSys.root

RunLBT: Execute
	bunzip2 txt/`bash FindLatestTag.sh LBT All Separated`_*bz2
	cp Prior/LBT.txt txt/`bash FindLatestTag.sh LBT All Separated`_QHatPrior.txt
	time ./Execute --tag `bash FindLatestTag.sh LBT All Separated` \
		--min 0,0,0,0 --max 2,20,2,20 \
		--name "A","B","C","D" \
		--transform false --setting LBT \
		--xmin 8,8,8,8,8,8 --xmax 20,20,90,90,100,100 \
		--ymin 0,0,0,0,0,0 --ymax 1.6,1.6,1.6,1.6,1.6,1.6 \
		--output root/LBT_NewSys.root
	bzip2 txt/`bash FindLatestTag.sh LBT All Separated`_*txt

RunMatterLBT1: Execute
	bunzip2 txt/`bash FindLatestTag.sh MatterLBT1 All Separated`_*bz2
	bunzip2 txt/`bash FindLatestTag.sh MatterLBT1 RHIC Separated`_*bz2
	bunzip2 txt/`bash FindLatestTag.sh MatterLBT1 LHC Separated`_*bz2
	cp Prior/MatterLBT1.txt txt/`bash FindLatestTag.sh MatterLBT1 All Separated`_QHatPrior.txt
	cp Prior/MatterLBT1.txt txt/`bash FindLatestTag.sh MatterLBT1 RHIC Separated`_QHatPrior.txt
	cp Prior/MatterLBT1.txt txt/`bash FindLatestTag.sh MatterLBT1 LHC Separated`_QHatPrior.txt
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
	bzip2 txt/`bash FindLatestTag.sh MatterLBT1 All Separated`_*txt
	bzip2 txt/`bash FindLatestTag.sh MatterLBT1 RHIC Separated`_*txt
	bzip2 txt/`bash FindLatestTag.sh MatterLBT1 LHC Separated`_*txt

RunMatterLBT2: Execute
	bunzip2 txt/`bash FindLatestTag.sh MatterLBT2 All Separated`_*bz2
	bunzip2 txt/`bash FindLatestTag.sh MatterLBT2 RHIC Separated`_*bz2
	bunzip2 txt/`bash FindLatestTag.sh MatterLBT2 LHC Separated`_*bz2
	cp Prior/MatterLBT2.txt txt/`bash FindLatestTag.sh MatterLBT2 All Separated`_QHatPrior.txt
	cp Prior/MatterLBT2.txt txt/`bash FindLatestTag.sh MatterLBT2 RHIC Separated`_QHatPrior.txt
	cp Prior/MatterLBT2.txt txt/`bash FindLatestTag.sh MatterLBT2 LHC Separated`_QHatPrior.txt
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
	bzip2 txt/`bash FindLatestTag.sh MatterLBT2 All Separated`_*txt
	bzip2 txt/`bash FindLatestTag.sh MatterLBT2 RHIC Separated`_*txt
	bzip2 txt/`bash FindLatestTag.sh MatterLBT2 LHC Separated`_*txt

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



