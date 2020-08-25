
default: RunPosteriorPlot

ExecuteScatterPlot: MakeScatterPlot.cpp
	CompileRootMacro MakeScatterPlot.cpp ExecuteScatterPlot

RunScatterPlot: ExecuteScatterPlot
	./ExecuteScatterPlot \
		--file root/Matter_NewSys.root \
		--transform false \
		--name "A","B","C","D" \
		--model LBT \
		--detail "RHIC+LHC","Old systematics" \
		--output ScatterMatter.pdf
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
	cp *pdf ~/WindowsHome/Downloads/
