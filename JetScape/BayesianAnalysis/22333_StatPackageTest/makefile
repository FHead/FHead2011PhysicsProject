

default: RunAll

RunAll:
	python3 SetupLBT.py
	python3 CleanPastFiles.py
	python3 -m src.emulator --retrain --npc 3 --nrestarts 50 --nu 2.5
	python3 -m src.mcmc --nwalkers 500 --nburnsteps 1000 1000
	python3 MakeBaselinePlots.py
