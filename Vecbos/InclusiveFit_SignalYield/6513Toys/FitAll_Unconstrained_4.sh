DHFile="\"Samples/DataAll.dh\""

for i in `seq 10 4999`
do
   root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/Samples_30.root\", 4, \"Calo\", 30, $DHFile, $i)"
done



