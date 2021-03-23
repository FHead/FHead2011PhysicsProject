
default: RunPaperFigures CopyAway

ExecuteScatterPlot2: MakeScatterPlot2.cpp
	CompileRootMacro MakeScatterPlot2.cpp ExecuteScatterPlot2

TestRun: ExecutePosteriorPlot
	./ExecutePosteriorPlot \
		--file root/Matter_NewSys.root \
		--prior false \
		--world 8,20,0,1.6,8,90,0,1.6,8,100,0,1.6 \
		--output Figure8_PosteriorMatter

RunPaperFigures: RunPaperFigure4 RunPaperFigure6 RunPaperFigure7 RunPaperFigure8 RunPaperFigure9 RunPaperFigure11 RunPaperFigure12 RunPaperFigure14

RunPaperFigure4: ExecuteScatterPlot2 
	./ExecuteScatterPlot2 \
		--file root/LBT_NewSys.root,root/Matter_NewSys.root \
		--transform false \
		--name "A","B","C","D" \
		--label LBT,MATTER \
		--lowerindex 0 --upperindex 1 \
		--legendx 0.78 --legendy 0.83 \
		--output Figure4_ScatterMatterLBT

RunPaperFigure6: ExecutePosteriorPlot
	./ExecutePosteriorPlot \
		--file root/LBT_NewSys.root \
		--prior true \
		--world 8,20,0,1.6,8,90,0,1.6,8,100,0,1.6 \
		--output Figure6_DesignLBT

RunPaperFigure7: ExecutePosteriorPlot
	./ExecutePosteriorPlot \
		--file root/LBT_NewSys.root \
		--prior false \
		--world 8,20,0,1.6,8,90,0,1.6,8,100,0,1.6 \
		--output Figure7_PosteriorLBT

RunPaperFigure8: ExecutePosteriorPlot
	./ExecutePosteriorPlot \
		--file root/Matter_NewSys.root \
		--prior false \
		--world 8,20,0,1.6,8,90,0,1.6,8,100,0,1.6 \
		--output Figure8_PosteriorMatter

RunPaperFigure9: ExecuteScatterPlot2 
	./ExecuteScatterPlot2 \
		--file root/MatterLBT1_NewSys.root,root/MatterLBT1_NewSys_LHC.root,root/MatterLBT1_NewSys_RHIC.root \
		--transform true \
		--name "A","C","B","D","Q" \
		--label RHIC+LHC,LHC,RHIC \
		--legendx 0.81 --legendy 0.84 \
		--lowerindex 0 --upperindex 1 \
		--model MATTER+LBT1 \
		--output Figure9_ScatterMatterLBT1

RunPaperFigure11: ExecutePosteriorPlot
	./ExecutePosteriorPlot \
		--file root/MatterLBT1_NewSys.root \
		--prior false \
		--world 8,20,0,1.6,8,90,0,1.6,8,100,0,1.6 \
		--output Figure11_PosteriorMatterLBT1

RunPaperFigure12: ExecuteScatterPlot2
	./ExecuteScatterPlot2 \
		--file root/MatterLBT2_NewSys.root,root/MatterLBT2_NewSys_LHC.root,root/MatterLBT2_NewSys_RHIC.root \
		--transform true \
		--name "A","C","D","Q" \
		--label RHIC+LHC,LHC,RHIC \
		--legendx 0.77 --legendy 0.82 \
		--lowerindex 0 --upperindex 1 \
		--model MATTER+LBT2 \
		--output Figure12_ScatterMatterLBT2

RunPaperFigure14: ExecutePosteriorPlot
	./ExecutePosteriorPlot \
		--file root/MatterLBT2_NewSys.root \
		--prior false \
		--world 8,20,0,1.6,8,90,0,1.6,8,100,0,1.6 \
		--output Figure14_PosteriorMatterLBT2

RunPaperFigure15: ExecuteScatterPlot2 
	./ExecuteScatterPlot2 \
		--file root/MatterLBT2_NewSys.root,root/MatterLBT2Alternative_NewSys.root \
		--transform true \
		--name "A","C","D","Q" \
		--label "l_{k} = 0.2","l_{k} = 10" \
		--legendx 0.79 --legendy 0.87 \
		--lowerindex 0 --upperindex 1 \
		--output Figure15_ScatterMatterLBT2Length
	./ExecuteScatterPlot2 \
		--file root/MatterLBT2Alternative_NewSys.root,root/MatterLBT2Alternative_NewSys_LHC.root,root/MatterLBT2Alternative_NewSys_RHIC.root \
		--transform true \
		--name "A","C","D","Q" \
		--label Both,LHC,RHIC \
		--legendx 0.81 --legendy 0.87 \
		--lowerindex 0 --upperindex 1 \
		--output Figure15Alt_ScatterMatterLBT2Length

RunPaperFigure16: ExecutePosteriorPlot
	./ExecutePosteriorPlot \
		--file root/MatterLBT2Alternative_NewSys.root \
		--prior false \
		--world 8,20,0,1.6,8,90,0,1.6,8,100,0,1.6 \
		--output Figure16_PosteriorMatterLBT2Length

CopyAway:
	cp *pdf ~/WindowsHome/Downloads/
	cp *png ~/WindowsHome/Downloads/

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

RunExtraPlot: ExecuteScatterPlot2
	./ExecuteScatterPlot2 \
		--file root/LBT_OldSys.root,root/LBT_NewSys.root \
		--transform false \
		--name "A","B","C","D" \
		--label "LBT (old)","LBT (new)" \
		--lowerindex 0 --upperindex 1 \
		--legendx 0.76 --legendy 0.85 \
		--output Figure_ScatterLBTLBT



