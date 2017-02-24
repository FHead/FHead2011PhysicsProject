./a.out ScaledResult/PP6Dijet.root Plots/PP6Dijet
./a.out ScaledResult/PP8Dijet.root Plots/PP8Dijet
./a.out ScaledResult/AA6Dijet.root Plots/AA6Dijet
./a.out ScaledResult/AA8Dijet.root Plots/AA8Dijet

mkdir -p RenamedPlots
for i in `ls Plots | grep pdf`
do
   cp Plots/$i RenamedPlots/15543_RegionIICharacteristics_$i
done
