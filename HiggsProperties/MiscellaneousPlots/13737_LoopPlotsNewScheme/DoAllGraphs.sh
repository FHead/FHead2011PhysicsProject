CompileRootMacro MakeGraph.cpp RunGraph

for i in BothS EMS EES
do
   ./RunGraph Temp_${i}_A_PointA.root ${i} A 0.42866   A 1.0 0.0 2.0 0.01 0 0.007
   ./RunGraph Temp_${i}_H_PointA.root ${i} H 0.47159   A 1.0 0.0 2.0 0.01 0 0.007
   ./RunGraph Temp_${i}_I_PointA.root ${i} I 0.36049   A 1.0 0.0 2.0 0.01 0 0.007
   ./RunGraph Temp_${i}_J_PointA.root ${i} J 0.44786   A 1.0 0.0 2.0 0.01 0 0.007
   ./RunGraph Temp_${i}_A_PointB.root ${i} A 0.42702   B 1.5 1.0 2.0 0.01 0 0.007
   ./RunGraph Temp_${i}_H_PointB.root ${i} H 0.47089   B 1.5 1.0 2.0 0.01 0 0.007
   ./RunGraph Temp_${i}_I_PointB.root ${i} I 0.35976   B 1.5 1.0 2.0 0.01 0 0.007
   ./RunGraph Temp_${i}_J_PointB.root ${i} J 0.44691   B 1.5 1.0 2.0 0.01 0 0.007
   ./RunGraph Temp_${i}_A_PointC.root ${i} A 0.42702   B 2.5 -1.0 2.0 0.01 0 0.007
   ./RunGraph Temp_${i}_H_PointC.root ${i} H 0.47089   B 2.5 -1.0 2.0 0.01 0 0.007
   ./RunGraph Temp_${i}_I_PointC.root ${i} I 0.35976   B 2.5 -1.0 2.0 0.01 0 0.007
   ./RunGraph Temp_${i}_J_PointC.root ${i} J 0.44691   B 2.5 -1.0 2.0 0.01 0 0.007
done
   
./RunGraph Temp_Both_A_PointA.root Both A 0.42866   A 1.0 0.0 2.0 0.01 0 0.007
./RunGraph Temp_Both_H_PointA.root Both H 0.47159   A 1.0 0.0 2.0 0.01 0 0.007
./RunGraph Temp_Both_I_PointA.root Both I 0.36049   A 1.0 0.0 2.0 0.01 0 0.007
./RunGraph Temp_Both_J_PointA.root Both J 0.44786   A 1.0 0.0 2.0 0.01 0 0.007
# ./RunGraph Temp_BothF_A_PointA.root BothF A 0.42866   A 1.0 0.0 2.0 0.01 0 0.007
# ./RunGraph Temp_BothF_H_PointA.root BothF H 0.47159   A 1.0 0.0 2.0 0.01 0 0.007
# ./RunGraph Temp_BothF_I_PointA.root BothF I 0.36049   A 1.0 0.0 2.0 0.01 0 0.007
# ./RunGraph Temp_BothF_J_PointA.root BothF J 0.44786   A 1.0 0.0 2.0 0.01 0 0.007
   
hadd -f AllGraphs.root Temp*root
# rm Temp*root

