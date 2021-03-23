

# default: TestRun TestRunEta TestRunParameter
default: TestRunParameter

TestRun: Execute
	./Execute --XMin 20 --XMax 1000 --YMin 0 --YMax 0.40 \
		--DHFile JERRun2017_R015.dh,JERRun2017_R020.dh,JERRun2017_R030.dh,JERRun2017_R040.dh,JERRun2017_R050.dh,JERRun2017_R060.dh,JERRun2017_R080.dh,JERRun2017_R100.dh,JERRun2017_R120.dh \
		--State "Fit_0.000_0.250" \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2017","#eta = 0.00" \
		--Output JER_2017_Eta0.00.pdf
	./Execute --XMin 20 --XMax 1000 --YMin 0 --YMax 0.40 \
		--DHFile JERRun2018_R015.dh,JERRun2018_R020.dh,JERRun2018_R030.dh,JERRun2018_R040.dh,JERRun2018_R050.dh,JERRun2018_R060.dh,JERRun2018_R080.dh,JERRun2018_R100.dh,JERRun2018_R120.dh \
		--State "Fit_0.000_0.250" \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2018","#eta = 0.00" \
		--Output JER_2018_Eta0.00.pdf
	./Execute --XMin 20 --XMax 1000 --YMin 0 --YMax 0.40 \
		--DHFile JERRun2017_R015.dh,JERRun2017_R020.dh,JERRun2017_R030.dh,JERRun2017_R040.dh,JERRun2017_R050.dh,JERRun2017_R060.dh,JERRun2017_R080.dh,JERRun2017_R100.dh,JERRun2017_R120.dh \
		--State "Fit_1.500_1.750" \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2017","#eta = 1.50" \
		--Output JER_2017_Eta1.50.pdf
	./Execute --XMin 20 --XMax 1000 --YMin 0 --YMax 0.40 \
		--DHFile JERRun2018_R015.dh,JERRun2018_R020.dh,JERRun2018_R030.dh,JERRun2018_R040.dh,JERRun2018_R050.dh,JERRun2018_R060.dh,JERRun2018_R080.dh,JERRun2018_R100.dh,JERRun2018_R120.dh \
		--State "Fit_1.500_1.750" \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2018","#eta = 1.50" \
		--Output JER_2018_Eta1.50.pdf
	cp *pdf ~/public/html/

TestRunEta: ExecuteEta
	./ExecuteEta --YMin 0 --YMax 0.50 --JetPT 30 \
		--DHFile JERRun2017_R015.dh,JERRun2017_R020.dh,JERRun2017_R030.dh,JERRun2017_R040.dh,JERRun2017_R050.dh,JERRun2017_R060.dh,JERRun2017_R080.dh,JERRun2017_R100.dh,JERRun2017_R120.dh \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2017","p_{T} = 30 GeV" \
		--Output JER_2017_PT30.pdf
	./ExecuteEta --YMin 0 --YMax 0.50 --JetPT 30 \
		--DHFile JERRun2018_R015.dh,JERRun2018_R020.dh,JERRun2018_R030.dh,JERRun2018_R040.dh,JERRun2018_R050.dh,JERRun2018_R060.dh,JERRun2018_R080.dh,JERRun2018_R100.dh,JERRun2018_R120.dh \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2018","p_{T} = 30 GeV" \
		--Output JER_2018_PT30.pdf
	./ExecuteEta --YMin 0 --YMax 0.40 --JetPT 50 \
		--DHFile JERRun2017_R015.dh,JERRun2017_R020.dh,JERRun2017_R030.dh,JERRun2017_R040.dh,JERRun2017_R050.dh,JERRun2017_R060.dh,JERRun2017_R080.dh,JERRun2017_R100.dh,JERRun2017_R120.dh \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2017","p_{T} = 50 GeV" \
		--Output JER_2017_PT50.pdf
	./ExecuteEta --YMin 0 --YMax 0.40 --JetPT 50 \
		--DHFile JERRun2018_R015.dh,JERRun2018_R020.dh,JERRun2018_R030.dh,JERRun2018_R040.dh,JERRun2018_R050.dh,JERRun2018_R060.dh,JERRun2018_R080.dh,JERRun2018_R100.dh,JERRun2018_R120.dh \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2018","p_{T} = 50 GeV" \
		--Output JER_2018_PT50.pdf
	./ExecuteEta --YMin 0 --YMax 0.30 --JetPT 100 \
		--DHFile JERRun2017_R015.dh,JERRun2017_R020.dh,JERRun2017_R030.dh,JERRun2017_R040.dh,JERRun2017_R050.dh,JERRun2017_R060.dh,JERRun2017_R080.dh,JERRun2017_R100.dh,JERRun2017_R120.dh \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2017","p_{T} = 100 GeV" \
		--Output JER_2017_PT100.pdf
	./ExecuteEta --YMin 0 --YMax 0.30 --JetPT 100 \
		--DHFile JERRun2018_R015.dh,JERRun2018_R020.dh,JERRun2018_R030.dh,JERRun2018_R040.dh,JERRun2018_R050.dh,JERRun2018_R060.dh,JERRun2018_R080.dh,JERRun2018_R100.dh,JERRun2018_R120.dh \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2018","p_{T} = 100 GeV" \
		--Output JER_2018_PT100.pdf
	./ExecuteEta --YMin 0 --YMax 0.20 --JetPT 300 \
		--DHFile JERRun2017_R015.dh,JERRun2017_R020.dh,JERRun2017_R030.dh,JERRun2017_R040.dh,JERRun2017_R050.dh,JERRun2017_R060.dh,JERRun2017_R080.dh,JERRun2017_R100.dh,JERRun2017_R120.dh \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2017","p_{T} = 300 GeV" \
		--Output JER_2017_PT300.pdf
	./ExecuteEta --YMin 0 --YMax 0.20 --JetPT 300 \
		--DHFile JERRun2018_R015.dh,JERRun2018_R020.dh,JERRun2018_R030.dh,JERRun2018_R040.dh,JERRun2018_R050.dh,JERRun2018_R060.dh,JERRun2018_R080.dh,JERRun2018_R100.dh,JERRun2018_R120.dh \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2018","p_{T} = 300 GeV" \
		--Output JER_2018_PT300.pdf
	cp *pdf ~/public/html/

TestRunParameter: ExecuteParameter
	./ExecuteParameter --YMin 0 --YMax 0.20,2.50,15.00 \
		--DHFile JERRun2017_R015.dh,JERRun2017_R020.dh,JERRun2017_R030.dh,JERRun2017_R040.dh,JERRun2017_R050.dh,JERRun2017_R060.dh,JERRun2017_R080.dh,JERRun2017_R100.dh,JERRun2017_R120.dh \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2017" \
		--Output JER_2017_Parameters
	./ExecuteParameter --YMin 0 --YMax 0.20,2.50,15.00 \
		--DHFile JERRun2018_R015.dh,JERRun2018_R020.dh,JERRun2018_R030.dh,JERRun2018_R040.dh,JERRun2018_R050.dh,JERRun2018_R060.dh,JERRun2018_R080.dh,JERRun2018_R100.dh,JERRun2018_R120.dh \
		--Label "R = 0.15","R = 0.20","R = 0.30","R = 0.40","R = 0.50","R = 0.60","R = 0.80","R = 1.00","R = 1.20" \
		--Extra "2018" \
		--Output JER_2018_Parameters
	cp *pdf ~/public/html/

Execute: MakeResolutionPlots.cpp
	CompileRootMacro MakeResolutionPlots.cpp Execute

ExecuteEta: MakeResolutionEtaPlots.cpp
	CompileRootMacro MakeResolutionEtaPlots.cpp ExecuteEta

ExecuteParameter: MakeParameterPlots.cpp
	CompileRootMacro MakeParameterPlots.cpp ExecuteParameter
