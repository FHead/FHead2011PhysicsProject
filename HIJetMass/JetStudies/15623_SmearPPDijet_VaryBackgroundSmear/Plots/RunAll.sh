./a.out ScaledResult_Smear000/PP6Dijet.root Plots/Smear000_
./a.out ScaledResult_Smear005/PP6Dijet.root Plots/Smear005_
./a.out ScaledResult_Smear010/PP6Dijet.root Plots/Smear010_
./a.out ScaledResult_Smear020/PP6Dijet.root Plots/Smear020_

for i in `ls Plots | grep pdf`
do
   echo $i
   cp Plots/$i RenamedPlots/15623_PPSmearing_BackgroundSigma_$i
done
