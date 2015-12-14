CompileRootMacro MakeGraph.cpp RunGraph -I ../../CommonCode/include ../../CommonCode/library/EFTBases.o

mkdir -p Temps

for i in BothS Both
do
   echo A Point0 $i
   ./RunGraph Temps/Temp_${i}_A_Point0.root ${i} A 0.42866   0  0.00 0.00 0.00  0.00  0.00  0.00    0.00   0.00   0.00 0.00 173.21 2.00 79.95
   echo J Point0 $i
   ./RunGraph Temps/Temp_${i}_J_Point0.root ${i} J 0.44786   0  0.00 0.00 0.00  0.00  0.00  0.00    0.00   0.00   0.00 0.00 173.21 2.00 79.95  
   echo A PointA $i
   ./RunGraph Temps/Temp_${i}_A_PointA.root ${i} A 0.42866   A  0.01 0.00 0.007 0.014 0.00  0.00   -0.0081 0.00   1.00 0.00 173.21 2.00 79.95
   echo J PointA $i
   ./RunGraph Temps/Temp_${i}_J_PointA.root ${i} J 0.44786   A  0.01 0.00 0.007 0.014 0.00  0.00   -0.0081 0.00   1.00 0.00 173.21 2.00 79.95
   echo A PointD $i
   ./RunGraph Temps/Temp_${i}_A_PointD.root ${i} A 0.42866   D  0.00 0.00 0.00  0.014 0.00 -0.0078 -0.0081 0.00   1.00 0.00 173.21 2.00 79.95
   echo J PointD $i
   ./RunGraph Temps/Temp_${i}_J_PointD.root ${i} J 0.44786   D  0.00 0.00 0.00  0.014 0.00 -0.0078 -0.0081 0.00   1.00 0.00 173.21 2.00 79.95
done
   
hadd -f AllGraphs.root Temps/Temp*root

