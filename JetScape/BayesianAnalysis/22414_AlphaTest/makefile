
default:
	echo Hello world

all: RunDataReproduce RunDataKernelScan RunDataFluctuationTest RunHoldout RunClosureExample

RunDataReproduce:
	python3 RunOne.py --N -1 --Model Matter     --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N -1 --Model MatterLBT1 --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N -1 --Model MatterLBT2 --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	fin

RunDataKernelScan:
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N -1 --Model LBT        --Nu 1.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.0 --KernelChoice RBF    --Alpha 0.3
	fin

RunDataFlucutationTest:
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.5 --KernelChoice Matern --Alpha 0.3 --DoBigEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.5 --KernelChoice Matern --Alpha 0.3 --DoBigEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.5 --KernelChoice Matern --Alpha 0.3 --DoBigEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.5 --KernelChoice Matern --Alpha 0.3 --DoBigEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.5 --KernelChoice Matern --Alpha 0.3 --DoBigEarthquake
	fin

RunDataShiftTest:
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.5 --KernelChoice Matern --Alpha 0.3 --DoEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.5 --KernelChoice Matern --Alpha 0.3 --DoEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.5 --KernelChoice Matern --Alpha 0.3 --DoEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.5 --KernelChoice Matern --Alpha 0.3 --DoEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.5 --KernelChoice Matern --Alpha 0.3 --DoEarthquake
	fin

RunClosureExample:
	python3 RunOne.py --N 10 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N 14 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N 24 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N 30 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N 34 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N 49 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N 55 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N 63 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N 78 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N 96 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	fin

RunHoldout:
	python3 RunAllOnlyGP.py --Model LBT         --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunAllOnlyGP.py --Model Matter      --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunAllOnlyGP.py --Model MatterLBT1  --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunAllOnlyGP.py --Model MatterLBT2  --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	fin



