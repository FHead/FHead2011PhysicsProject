mkdir -p Plots
./a.out ScaledResult/AA6Dijet.root Plots/AA6Dijet 
./a.out ScaledResult/AA8Dijet.root Plots/AA8Dijet 
./a.out ScaledResult/PP6Dijet.root Plots/PP6Dijet 
./a.out ScaledResult/PP8Dijet.root Plots/PP8Dijet
./a.out ScaledResult/AAData_NoCrossSection.root Plots/AAData
./a.out ScaledResult/PPDataHighPTJet_NoCrossSection.root Plots/PPData

mkdir -p RenamedPlots
for i in `ls Plots | grep pdf | grep -v MassProjection`
do
   cp Plots/$i RenamedPlots/15524_FirstLookAtData_$i
done
for i in `ls Plots | grep pdf | grep MassProjection`
do
   cp Plots/$i RenamedPlots/15532_SecondLookAtData_$i
done

