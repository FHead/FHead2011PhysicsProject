CompileRootMacro QuickDraw.cpp
for i in Y N
do
   ./a.out 0   1000 0.0 0.2 $i
   ./a.out 100 1000 0.0 0.2 $i
   ./a.out 100 1000 0.2 0.5 $i
   ./a.out 100 1000 0.5 0.8 $i
   ./a.out 100 1000 0.0 0.8 $i
   ./a.out 120 1000 0.0 0.2 $i
   ./a.out 140 1000 0.0 0.5 $i
   ./a.out 200 1000 0.0 0.5 $i
   ./a.out 140 1000 0.0 0.2 $i
   ./a.out 200 1000 0.0 0.2 $i
   ./a.out 200 1000 0.0 0.1 $i
   ./a.out 140 1000 0.0 0.1 $i
   ./a.out 140 1000 0.1 0.4 $i
   ./a.out 140 1000 0.0 0.8 $i
   ./a.out 140 1000 0.1 0.8 $i
   ./a.out 140 1000 0.3 0.8 $i
   ./a.out 140 1000 0.5 0.8 $i
   ./a.out 200 300  0.0 0.5 $i
   ./a.out 200 300  0.0 0.2 $i
   ./a.out 200 300  0.2 0.5 $i
   ./a.out 200 300  0.5 0.8 $i
   ./a.out 300 500  0.0 0.5 $i
   ./a.out 500 1000 0.0 0.2 $i
done
mkdir -p PlotsPDF
mv Plots/*pdf PlotsPDF/
