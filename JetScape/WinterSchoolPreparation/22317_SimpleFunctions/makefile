default: TestRun

TestRun: Execute
	./Execute --XMin 0 --XMax 10 --YMin 0 --YMax 1.2 \
		--Function "(x^0*exp(-x))/1" \
		--Output Poisson0.pdf \
		--Title ";#theta;L(#theta|x=0)"
	./Execute --XMin 0 --XMax 12 --YMin 0 --YMax 0.25 \
		--Function "(x^3*exp(-x))/6" \
		--Output Poisson3.pdf \
		--Title ";#theta;L(#theta|x=3)"
	./Execute --XMin 0 --XMax 40 --YMin 0 --YMax 0.12 \
		--Function "(x^20*exp(-x))/(2.43e18)" \
		--Output Poisson20.pdf \
		--Title ";#theta;L(#theta|x=20)"
	./Execute --XMin 20 --XMax 60 --YMin 0 --YMax 0.07 \
		--Function "(x^40*exp(-x))/(8.16e47)" \
		--Output Poisson40.pdf \
		--Title ";#theta;L(#theta|x=40)"
	./Execute --XMin 0 --XMax 10 --YMin 0 --YMax 1 \
		--Function "x*0" \
		--Output Empty.pdf \
		--Title ";#theta;L(#theta|x)"

Execute: PlotFunction.cpp
	CompileRootMacro PlotFunction.cpp Execute
