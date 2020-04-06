default: TestRun

Execute: ParseTable.cpp
	CompileRootMacro ParseTable.cpp Execute

TestRun: Execute
	./Execute --Input HEPData-ins1673184-v1-csv/Table19.csv --Output Table19.root
	./Execute --Input HEPData-ins1673184-v1-csv/Table20.csv --Output Table20.root
	./Execute --Input HEPData-ins1673184-v1-csv/Table21.csv --Output Table21.root
	./Execute --Input HEPData-ins1673184-v1-csv/Table22.csv --Output Table22.root
	./Execute --Input HEPData-ins1673184-v1-csv/Table23.csv --Output Table23.root
	./Execute --Input HEPData-ins1673184-v1-csv/Table24.csv --Output Table24.root
	./Execute --Input HEPData-ins1673184-v1-csv/Table25.csv --Output Table25.root
	./Execute --Input HEPData-ins1673184-v1-csv/Table26.csv --Output Table26.root
	hadd -f AllTables.root Table*root
