CompileRootMacro MakeGraph.cpp RunGraph

mkdir -p Temps

for i in BothS EMS EES
do
   echo
   # ./RunGraph Temps/Temp_${i}_A_PointA.root ${i} A 0.42866   A 0.01 0.00 0.007 0.0141977000 0.00 0.00 -0.008102360 0.00 
   # ./RunGraph Temps/Temp_${i}_H_PointA.root ${i} H 0.47159   A 0.01 0.00 0.007 0.0141977000 0.00 0.00 -0.008102360 0.00 
   # ./RunGraph Temps/Temp_${i}_I_PointA.root ${i} I 0.36049   A 0.01 0.00 0.007 0.0141977000 0.00 0.00 -0.008102360 0.00 
   # ./RunGraph Temps/Temp_${i}_J_PointA.root ${i} J 0.44786   A 0.01 0.00 0.007 0.0141977000 0.00 0.00 -0.008102360 0.00 
   # ./RunGraph Temps/Temp_${i}_A_PointO.root ${i} A 0.42866   O 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 
   # ./RunGraph Temps/Temp_${i}_H_PointO.root ${i} H 0.47159   O 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 
   # ./RunGraph Temps/Temp_${i}_I_PointO.root ${i} I 0.36049   O 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 
   # ./RunGraph Temps/Temp_${i}_J_PointO.root ${i} J 0.44786   O 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 
   ./RunGraph Temps/Temp_${i}_A_Point0.root ${i} A 0.42866   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 
   ./RunGraph Temps/Temp_${i}_B_Point0.root ${i} B 0.35322   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 
   ./RunGraph Temps/Temp_${i}_C_Point0.root ${i} C 0.35221   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 
   ./RunGraph Temps/Temp_${i}_D_Point0.root ${i} D 0.48706   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 
   ./RunGraph Temps/Temp_${i}_H_Point0.root ${i} H 0.47159   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 
   ./RunGraph Temps/Temp_${i}_I_Point0.root ${i} I 0.36049   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 
   ./RunGraph Temps/Temp_${i}_J_Point0.root ${i} J 0.44786   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 
   # ./RunGraph Temps/Temp_${i}_A_PointB.root ${i} A 0.42702   B 0.01 0.00 0.007 0.0137981000 -0.001212710 0.00 -0.006960880 -0.006945650
   # ./RunGraph Temps/Temp_${i}_H_PointB.root ${i} H 0.47089   B 0.01 0.00 0.007 0.0137981000 -0.001212710 0.00 -0.006960880 -0.006945650
   # ./RunGraph Temps/Temp_${i}_I_PointB.root ${i} I 0.35976   B 0.01 0.00 0.007 0.0137981000 -0.001212710 0.00 -0.006960880 -0.006945650
   # ./RunGraph Temps/Temp_${i}_J_PointB.root ${i} J 0.44691   B 0.01 0.00 0.007 0.0137981000 -0.001212710 0.00 -0.006960880 -0.006945650
   # ./RunGraph Temps/Temp_${i}_A_PointC.root ${i} A 0.42702   C 0.01 0.00 0.007 0.0128392000 0.0012127100 0.00 -0.004221310 0.0069456500
   # ./RunGraph Temps/Temp_${i}_H_PointC.root ${i} H 0.47089   C 0.01 0.00 0.007 0.0128392000 0.0012127100 0.00 -0.004221310 0.0069456500
   # ./RunGraph Temps/Temp_${i}_I_PointC.root ${i} I 0.35976   C 0.01 0.00 0.007 0.0128392000 0.0012127100 0.00 -0.004221310 0.0069456500
   # ./RunGraph Temps/Temp_${i}_J_PointC.root ${i} J 0.44691   C 0.01 0.00 0.007 0.0128392000 0.0012127100 0.00 -0.004221310 0.0069456500
done
   
# ./RunGraph Temps/Temp_Both_A_PointA.root Both A 0.42866   A 0.01 0 0.007 0.0141977000 0.00 0.00 -0.008102360 0.00 
# ./RunGraph Temps/Temp_Both_H_PointA.root Both H 0.47159   A 0.01 0 0.007 0.0141977000 0.00 0.00 -0.008102360 0.00 
# ./RunGraph Temps/Temp_Both_I_PointA.root Both I 0.36049   A 0.01 0 0.007 0.0141977000 0.00 0.00 -0.008102360 0.00 
# ./RunGraph Temps/Temp_Both_J_PointA.root Both J 0.44786   A 0.01 0 0.007 0.0141977000 0.00 0.00 -0.008102360 0.00 
# ./RunGraph Temps/Temp_Both_A_PointO.root Both A 0.42866   O 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
# ./RunGraph Temps/Temp_Both_H_PointO.root Both H 0.47159   O 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
# ./RunGraph Temps/Temp_Both_I_PointO.root Both I 0.36049   O 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
# ./RunGraph Temps/Temp_Both_J_PointO.root Both J 0.44786   O 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_Both_A_Point0.root Both A 0.42866   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_Both_B_Point0.root Both B 0.35322   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_Both_C_Point0.root Both C 0.35221   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_Both_D_Point0.root Both D 0.48706   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_Both_H_Point0.root Both H 0.47159   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_Both_I_Point0.root Both I 0.36049   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_Both_J_Point0.root Both J 0.44786   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_BothHalf_A_Point0.root BothHalf A 0.42866   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_BothHalf_B_Point0.root BothHalf B 0.35332   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_BothHalf_C_Point0.root BothHalf C 0.35221   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_BothHalf_D_Point0.root BothHalf D 0.48706   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_BothHalf_H_Point0.root BothHalf H 0.47159   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_BothHalf_I_Point0.root BothHalf I 0.36049   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
./RunGraph Temps/Temp_BothHalf_J_Point0.root BothHalf J 0.44786   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
   
hadd -f AllGraphs.root Temps/Temp*root
# rm Temp*root

