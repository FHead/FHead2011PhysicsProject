# CompileRootMacro MakePlot.cpp a.out
# time ./a.out Mass_SD0_Data.txt SD0Data
# time ./a.out Mass_SD0_MC.txt SD0MC
# time ./a.out Mass_SD7_Data.txt SD7Data
# time ./a.out Mass_SD7_MC.txt SD7MC

for i in SD0_Data SD0_MC SD7_Data SD7_MC
do
   cat Mass_${i}.txt | sed "s/Data/0/g" | sed "s/Smear/1/g" \
      | TextToTree ${i}.root 8 "Type:Centrality:PT:MassRatio:ZG:DR:PTPT:W"
done




