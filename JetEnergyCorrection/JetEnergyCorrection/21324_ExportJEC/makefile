default: TestRun

Execute: ExportCurve.cpp
	CompileRootMacro ExportCurve.cpp Execute

ExecuteUncertainty: ExportUncertainty.cpp
	CompileRootMacro ExportUncertainty.cpp ExecuteUncertainty

TestRun: Execute
	./Execute --Version Fall17_17Nov2017_V32_MC --Algorithm AK4PFchs --Level L1FastJet --Dependent Eta --Min -5.2 --Max 5.2

UpdateJEC: Execute ExecuteUncertainty
	bash MakeTestData.sh > JECViewerDevelopment/JECData.js

RunAllVersions: Execute ExecuteUncertainty
	bash RunAllVersions.sh

CombineAllData:
	bash CombineAllData.sh > JECViewerDevelopment/JECData.js
	ls -lh JECViewerDevelopment/JECData.js

Deploy:
	cp JECViewerDevelopment/* ~/public/html/JECViewer/
