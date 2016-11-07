./a.out ScaledResult_Rho100/PP6Dijet.root Plots/Rho100_
./a.out ScaledResult_Rho200/PP6Dijet.root Plots/Rho200_

for i in `ls Plots | grep pdf`
do
   echo $i
   cp Plots/$i RenamedPlots/15623_PPSmearing_BackgroundSigma_$i
done
