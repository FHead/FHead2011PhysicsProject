DHFile="\"Samples/DataAll.dh\""

# root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/DataAll.root\", 5, \"pf\", 15, $DHFile)"

for i in `seq 1001 5000`
do
   root -l -b -q "SimultaneousFit_FloatAll.C+(\"Samples/Samples_30.root\", 4, \"pf\", 30, $DHFile, $i)"
done

