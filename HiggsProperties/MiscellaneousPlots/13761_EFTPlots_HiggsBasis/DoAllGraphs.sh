CompileRootMacro MakeGraph.cpp RunGraph

mkdir -p Temps

for i in BothS 
do
   echo
   ./RunGraph Temps/Temp_${i}_A_Point0.root ${i} A 0.42866   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
   ./RunGraph Temps/Temp_${i}_H_Point0.root ${i} H 0.47159   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
   ./RunGraph Temps/Temp_${i}_I_Point0.root ${i} I 0.36049   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
   ./RunGraph Temps/Temp_${i}_J_Point0.root ${i} J 0.44786   0 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00 0.00
done
   
hadd -f AllGraphs.root Temps/Temp*root

