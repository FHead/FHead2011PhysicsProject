default: ExecuteCompareJets

ProduceJRA:
	sed "s/__FILE__/NoPUEvents/g" < run_JRA_cfg.py > Temp.py
	cmsRun Temp.py
	sed "s/__FILE__/WithPUEvents/g" < run_JRA_cfg.py > Temp.py
	cmsRun Temp.py

ProduceHCAL:
	sed "s/__FILE__/NoPUEvents/g" < RunHCAL.py > Temp.py
	cmsRun Temp.py
	sed "s/__FILE__/WithPUEvents/g" < RunHCAL.py > Temp.py
	cmsRun Temp.py

RunCompareJets: CompareJets.cpp
	CompileRootMacro CompareJets.cpp RunCompareJets
	
ExecuteCompareJets: RunCompareJets
	./RunCompareJets
	cp JetPlots.pdf ~/public/html/
