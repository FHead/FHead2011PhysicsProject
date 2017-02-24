mkdir -p RenamedPlots/

for i in `ls FitPlots | grep pdf$`
do
   cp FitPlots/$i RenamedPlots/${i/SimpleFitResult/15631_MBSpectrumFit}
done

