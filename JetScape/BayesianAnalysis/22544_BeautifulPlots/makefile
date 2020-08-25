
default: RunScatterPlot

ExecuteScatterPlot: MakeScatterPlot.cpp
	CompileRootMacro MakeScatterPlot.cpp ExecuteScatterPlot

RunScatterPlot: ExecuteScatterPlot
	./ExecuteScatterPlot \
		--file root/Matter_NewSys.root \
		--transform false \
		--name "A","B","C","D" \
		--label MATTER \
		--detail "MATTER","RHIC+LHC" \
		--output ScatterMatter.pdf
	./ExecuteScatterPlot \
		--file root/LBT_NewSys.root \
		--transform false \
		--name "A","B","C","D" \
		--label LBT \
		--detail "LBT","RHIC+LHC" \
		--output ScatterLBT.pdf
	./ExecuteScatterPlot \
		--file root/LBT_NewSys.root,root/Matter_NewSys.root \
		--transform false \
		--name "A","B","C","D" \
		--label LBT,MATTER \
		--detail "RHIC+LHC" \
		--legendx 0.70 \
		--output ScatterMatterLBT.pdf
	./ExecuteScatterPlot \
		--file root/MatterLBT1_NewSys.root,root/MatterLBT1_NewSys_LHC.root,root/MatterLBT1_NewSys_RHIC.root \
		--transform false \
		--name "A","C","B","D","Q" \
		--label "Combined","LHC","RHIC" \
		--legendx 0.70 \
		--detail "" \
		--output ScatterMatterLBT1.pdf
	./ExecuteScatterPlot \
		--file root/MatterLBT1_OldSys.root,root/MatterLBT1_OldSys_LHC.root,root/MatterLBT1_OldSys_RHIC.root \
		--transform false \
		--name "A","C","B","D","Q" \
		--label "Combined","LHC","RHIC" \
		--legendx 0.70 \
		--detail "" \
		--output ScatterMatterLBT1Old.pdf
	./ExecuteScatterPlot \
		--file root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys_LHC.root,root/MatterLBT2_NewSys_RHIC.root \
		--transform false \
		--name "A","C","D","Q" \
		--label "Combined","LHC","RHIC" \
		--legendx 0.70 \
		--detail "" \
		--output ScatterMatterLBT2.pdf
	./ExecuteScatterPlot \
		--file root/MatterLBT2_OldSys.root,root/MatterLBT2_OldSys_LHC.root,root/MatterLBT2_OldSys_RHIC.root \
		--transform false \
		--name "A","C","D","Q" \
		--label "Combined","LHC","RHIC" \
		--legendx 0.70 \
		--detail "" \
		--output ScatterMatterLBT2Old.pdf
	cp *pdf ~/WindowsHome/Downloads/

ExecutePosteriorPlot: MakePosteriorPlot.cpp
	CompileRootMacro MakePosteriorPlot.cpp ExecutePosteriorPlot

RunPosteriorPlot: ExecutePosteriorPlot
	./ExecutePosteriorPlot \
		--file root/Matter_NewSys.root \
		--prior false \
		--output PosteriorMatter.pdf
	./ExecutePosteriorPlot \
		--file root/Matter_NewSys.root \
		--prior true \
		--output DesignMatter.pdf
	./ExecutePosteriorPlot \
		--file root/LBT_NewSys.root \
		--prior false \
		--output PosteriorLBT.pdf
	./ExecutePosteriorPlot \
		--file root/LBT_NewSys.root \
		--prior true \
		--output DesignLBT.pdf
	./ExecutePosteriorPlot \
		--file root/MatterLBT1_NewSys.root \
		--prior false \
		--output PosteriorMatterLBT1.pdf
	./ExecutePosteriorPlot \
		--file root/MatterLBT2_NewSys.root \
		--prior false \
		--output PosteriorMatterLBT2.pdf
	cp *pdf ~/WindowsHome/Downloads/



