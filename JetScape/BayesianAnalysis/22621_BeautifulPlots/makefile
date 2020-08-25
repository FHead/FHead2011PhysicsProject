
default: RunPaperFigures CopyAway

ExecuteScatterPlot2: MakeScatterPlot2.cpp
	CompileRootMacro MakeScatterPlot2.cpp ExecuteScatterPlot2

RunPaperFigures: ExecuteScatterPlot2 ExecutePosteriorPlot
	./ExecuteScatterPlot2 \
		--file root/LBT_NewSys.root,root/Matter_NewSys.root \
		--transform false \
		--name "A","B","C","D" \
		--label LBT,MATTER \
		--detail "RHIC+LHC" \
		--lowerindex 0 --upperindex 1 \
		--legendx 0.76 --legendy 0.85 \
		--output Figure4_ScatterMatterLBT.pdf
	./ExecutePosteriorPlot \
		--file root/LBT_NewSys.root \
		--prior true \
		--output Figure6_DesignLBT.pdf
	./ExecutePosteriorPlot \
		--file root/LBT_NewSys.root \
		--prior false \
		--output Figure7_PosteriorLBT.pdf
	./ExecutePosteriorPlot \
		--file root/Matter_NewSys.root \
		--prior false \
		--output Figure8_PosteriorMatter.pdf
	./ExecuteScatterPlot2 \
		--file root/MatterLBT1_NewSys.root,root/MatterLBT1_NewSys_LHC.root,root/MatterLBT1_NewSys_RHIC.root \
		--transform true \
		--name "A","C","B","D","Q" \
		--label Both,LHC,RHIC \
		--legendx 0.81 --legendy 0.87 \
		--lowerindex 0 --upperindex 1 \
		--output Figure9_ScatterMatterLBT1.pdf
	./ExecutePosteriorPlot \
		--file root/MatterLBT1_NewSys.root \
		--prior false \
		--output Figure11_PosteriorMatterLBT1.pdf
	./ExecuteScatterPlot2 \
		--file root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys_LHC.root,root/MatterLBT2_NewSys_RHIC.root \
		--transform true \
		--name "A","C","D","Q" \
		--label Both,LHC,RHIC \
		--legendx 0.81 --legendy 0.87 \
		--lowerindex 0 --upperindex 1 \
		--output Figure12_ScatterMatterLBT2.pdf
	./ExecutePosteriorPlot \
		--file root/MatterLBT2_NewSys.root \
		--prior false \
		--output Figure14_PosteriorMatterLBT2.pdf

CopyAway:
	cp *pdf ~/WindowsHome/Downloads/

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



