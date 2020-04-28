Alpha = 0.3

default:
	echo Hello world

all: RunDataReproduce RunDataAlphaScan RunDataKernelScan RunDataFluctuationTest RunHoldout RunClosureExample

RunDataReproduce:
	python3 RunOne.py --N -1 --Model Matter     --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N -1 --Model MatterLBT1 --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N -1 --Model MatterLBT2 --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)


RunDataKernelScan:
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N -1 --Model LBT        --Nu 1.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N -1 --Model LBT        --Nu 0.0 --KernelChoice RBF    --Alpha $(Alpha)


RunDataAlphaScan:
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.10
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.20
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.25
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.30
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.40
	python3 RunOne.py --N -1 --Model Matter     --Nu 2.5 --KernelChoice Matern --Alpha 0.10
	python3 RunOne.py --N -1 --Model Matter     --Nu 2.5 --KernelChoice Matern --Alpha 0.20
	python3 RunOne.py --N -1 --Model Matter     --Nu 2.5 --KernelChoice Matern --Alpha 0.25
	python3 RunOne.py --N -1 --Model Matter     --Nu 2.5 --KernelChoice Matern --Alpha 0.30
	python3 RunOne.py --N -1 --Model Matter     --Nu 2.5 --KernelChoice Matern --Alpha 0.40


RunDataFlucutationTest:
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha) --DoBigEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha) --DoBigEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha) --DoBigEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha) --DoBigEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha) --DoBigEarthquake


RunDataShiftTest:
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha) --DoEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha) --DoEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha) --DoEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha) --DoEarthquake
	python3 RunOne.py --N -1 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha) --DoEarthquake


RunClosureExample:
	python3 RunOne.py --N 10 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N 14 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N 24 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N 30 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N 34 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N 49 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N 55 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N 63 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N 78 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunOne.py --N 96 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)


RunClosureAlphaScan:
	python3 RunOne.py --N 14 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.1
	python3 RunOne.py --N 14 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.2
	python3 RunOne.py --N 14 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.25
	python3 RunOne.py --N 14 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.3
	python3 RunOne.py --N 14 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.4
	python3 RunOne.py --N 14 --Model LBT        --Nu 2.5 --KernelChoice Matern --Alpha 0.6


RunHoldoutAlphaScan:
	python3 RunAllOnlyGP.py --Model LBT         --Nu 2.5 --KernelChoice Matern --Alpha 0.10
	python3 RunAllOnlyGP.py --Model LBT         --Nu 2.5 --KernelChoice Matern --Alpha 0.20
	python3 RunAllOnlyGP.py --Model LBT         --Nu 2.5 --KernelChoice Matern --Alpha 0.30


RunHoldoutAlphaScanExtra:
	python3 RunAllOnlyGP.py --Model LBT         --Nu 2.5 --KernelChoice Matern --Alpha 0.25
	python3 RunAllOnlyGP.py --Model LBT         --Nu 2.5 --KernelChoice Matern --Alpha 0.60


RunHoldout:
	python3 RunAllOnlyGP.py --Model LBT         --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunAllOnlyGP.py --Model Matter      --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunAllOnlyGP.py --Model MatterLBT1  --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)
	python3 RunAllOnlyGP.py --Model MatterLBT2  --Nu 2.5 --KernelChoice Matern --Alpha $(Alpha)




