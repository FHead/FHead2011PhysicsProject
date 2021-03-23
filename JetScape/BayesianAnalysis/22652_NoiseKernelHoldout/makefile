default:
	echo Hello world

all: RunMatter RunLBT RunMatterLBT1 RunMatterLBT2 CopyAway

JustPlot:
	python3 MakeBaselinePlots.py --N -1 --Nu 2.5 --Model Matter --KernelChoice RBF --Alpha 0.0 --Noise 0.0 --CovType Separated --Data All

RunMatter:
	python3 RunOne.py --N -1 --Model Matter     --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.20 --CovType Separated

RunLBT:
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.20 --CovType Separated

RunLBTHoldout14:
	python3 RunOne.py --N 14 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.20 --CovType Separated

RunLBTTestExport:
	python3 ExportPosterior.py --N 14 --Nu 2.5 --Model LBT --KernelChoice MaternNoise --Alpha 0.20 --Noise 0.0 --CovType Separated --Data All

RunLBTOldTreatment:
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.20 --CovType Length0.2

RunMatterLBT1:
	python3 RunOne.py --N -1 --Model MatterLBT1 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.20 --CovType Separated
	python3 RunOne.py --N -1 --Model MatterLBT1 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.20 --CovType Separated --Data LHC
	python3 RunOne.py --N -1 --Model MatterLBT1 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.20 --CovType Separated --Data RHIC

RunMatterLBT2:
	python3 RunOne.py --N -1 --Model MatterLBT2 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.00 --CovType Separated
	python3 RunOne.py --N -1 --Model MatterLBT2 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.00 --CovType Separated --Data LHC
	python3 RunOne.py --N -1 --Model MatterLBT2 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.00 --CovType Separated --Data RHIC

RunMatterLBT2Alternative:
	python3 RunOne.py --N -1 --Model MatterLBT2 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.00 --CovType Separated10
	python3 RunOne.py --N -1 --Model MatterLBT2 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.00 --CovType Separated10 --Data LHC
	python3 RunOne.py --N -1 --Model MatterLBT2 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.00 --CovType Separated10 --Data RHIC

CopyAway:
	cp plots/*pdf ~/WindowsHome/Downloads/

