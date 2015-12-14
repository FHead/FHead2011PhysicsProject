CompileRootMacro MakeGraph.cpp RunGraph -I ../../CommonCode/include ../../CommonCode/library/EFTBases.o

mkdir -p Temps

for i in BothS Both
do
   echo
   ./RunGraph Temps/Temp_${i}_A_Point0.root ${i} A 0.42866   0  0.00 0.00 0.00 0.00  0.00  0.00    0.00   0.00
   # ./RunGraph Temps/Temp_${i}_H_Point0.root ${i} H 0.47159   0  0.00 0.00 0.00 0.00  0.00  0.00    0.00   0.00
   # ./RunGraph Temps/Temp_${i}_I_Point0.root ${i} I 0.36049   0  0.00 0.00 0.00 0.00  0.00  0.00    0.00   0.00
   ./RunGraph Temps/Temp_${i}_J_Point0.root ${i} J 0.44786   0  0.00 0.00 0.00 0.00  0.00  0.00    0.00   0.00
   # ./RunGraph Temps/Temp_${i}_A_PointD.root ${i} A 1.00000   D  0.00 0.00 0.00 0.014 0.00 -0.0078 -0.0081 0.00
   # ./RunGraph Temps/Temp_${i}_H_PointD.root ${i} H 1.00000   D  0.00 0.00 0.00 0.014 0.00 -0.0078 -0.0081 0.00
   # ./RunGraph Temps/Temp_${i}_I_PointD.root ${i} I 1.00000   D  0.00 0.00 0.00 0.014 0.00 -0.0078 -0.0081 0.00
   # ./RunGraph Temps/Temp_${i}_J_PointD.root ${i} J 1.00000   D  0.00 0.00 0.00 0.014 0.00 -0.0078 -0.0081 0.00
done
   
hadd -f AllGraphs.root Temps/Temp*root

