default:
	echo Hello world

all: RunDataReproduce RunDataAlphaScan RunDataKernelScan RunDataFluctuationTest RunHoldout RunClosureExample

RunDataSeparated:
	python3 RunOne.py --N -1 --Model Matter     --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.10 --CovType Separated
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.10 --CovType Separated
	python3 RunOne.py --N -1 --Model MatterLBT1 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.15 --CovType Separated
	python3 RunOne.py --N -1 --Model MatterLBT2 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.15 --CovType Separated

RunDataReproduce:
	python3 RunOne.py --N -1 --Model Matter     --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.10 --CovType Length0.2
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.10 --CovType Length0.2
	python3 RunOne.py --N -1 --Model MatterLBT1 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.15 --CovType Length0.2
	python3 RunOne.py --N -1 --Model MatterLBT2 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.15 --CovType Length0.2

RunDataFlucutationTest:
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1 --DoBigEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1 --DoBigEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1 --DoBigEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1 --DoBigEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1 --DoBigEarthquake

RunClosureExample:
	python3 RunOne.py --N 10 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1
	python3 RunOne.py --N 14 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1
	python3 RunOne.py --N 24 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1
	python3 RunOne.py --N 30 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1
	python3 RunOne.py --N 34 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1
	python3 RunOne.py --N 49 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1
	python3 RunOne.py --N 55 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1
	python3 RunOne.py --N 63 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1
	python3 RunOne.py --N 78 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1
	python3 RunOne.py --N 96 --Model LBT        --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.1

CopyAway:
	cp plots/*pdf ~/WindowsHome/Downloads/

