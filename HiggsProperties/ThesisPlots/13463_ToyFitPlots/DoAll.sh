mkdir -p Plots
./a.out PlotsReco11.root Meow11 11 0
./a.out PlotsReco11.root Meow11 11 1
./a.out PlotsReco16.root Meow16 16 0
./a.out PlotsReco16.root Meow16 16 1

mkdir -p PickedPlots

for i in Plots/*O_Meow11_YY_Y_*
do
   j=`basename $i`
   cp $i PickedPlots/MultiDimensionalValidation-FitResults-ToyFitResultsSM${j/CoolPlotO_Meow11_YY_Y_/}
done

cp Plots/CoolPlot_Meow11_YY_Y_8.png PickedPlots/MultiDimensionalValidation-FitResults-ToyFitResultsSM8.png
cp Plots/CoolPlot_Meow11_YY_Y_8.C   PickedPlots/MultiDimensionalValidation-FitResults-ToyFitResultsSM8.C
cp Plots/CoolPlot_Meow11_YY_Y_8.eps PickedPlots/MultiDimensionalValidation-FitResults-ToyFitResultsSM8.eps
cp Plots/CoolPlot_Meow11_YY_Y_8.pdf PickedPlots/MultiDimensionalValidation-FitResults-ToyFitResultsSM8.pdf

for i in Plots/*O_Meow16_YY_Y_*
do
   j=`basename $i`
   cp $i PickedPlots/MultiDimensionalValidation-FitResults-ToyFitResultsExotic${j/CoolPlotO_Meow16_YY_Y_/}
done

cp Plots/CoolPlot_Meow16_YY_Y_8.png PickedPlots/MultiDimensionalValidation-FitResults-ToyFitResultsExotic8.png
cp Plots/CoolPlot_Meow16_YY_Y_8.C   PickedPlots/MultiDimensionalValidation-FitResults-ToyFitResultsExotic8.C
cp Plots/CoolPlot_Meow16_YY_Y_8.eps PickedPlots/MultiDimensionalValidation-FitResults-ToyFitResultsExotic8.eps
cp Plots/CoolPlot_Meow16_YY_Y_8.pdf PickedPlots/MultiDimensionalValidation-FitResults-ToyFitResultsExotic8.pdf
