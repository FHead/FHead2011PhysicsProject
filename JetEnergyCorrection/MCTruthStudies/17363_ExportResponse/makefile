default: TestRun

Execute: ExportResponse.cpp
	CompileRootMacro ExportResponse.cpp Execute

TestRun: Execute
	time ./Execute --ptmin 40 --ptmax 70 \
		--etamin -0.5 --etamax 0.5 --input Result/Merged.root --fraction 0.1

FullRun: Execute
	time ./Execute --ptmin 40 --ptmax 70 \
		--etamin -0.5 --etamax 0.5 --input Result/Merged.root --output /tmp/chenyi/Response.txt

LowPTInvestigation: Execute
	./Execute --ptmin 20 --ptmax 70 \
		--etamin -0.522 --etamax 0 --rhomin 10 --rhomax 20\
		--input Result/Temp.root --output /tmp/chenyi/Response_Rho_10_20.txt
	./Execute --ptmin 20 --ptmax 70 \
		--etamin -0.522 --etamax 0 --rhomin 20 --rhomax 40\
		--input Result/Temp.root --output /tmp/chenyi/Response_Rho_20_40.txt
	./Execute --ptmin 20 --ptmax 70 \
		--etamin -0.522 --etamax 0 --rhomin 40 --rhomax 70\
		--input Result/Temp.root --output /tmp/chenyi/Response_Rho_40_70.txt


