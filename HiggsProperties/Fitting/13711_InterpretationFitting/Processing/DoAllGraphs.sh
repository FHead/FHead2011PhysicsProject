CompileRootMacro MakeGraph.cpp RunGraph
for i in BothS EMS EES
do
   ./RunGraph Temp_${i}_A.root ${i} A 0.44359 # 0.727693
   ./RunGraph Temp_${i}_J.root ${i} J 0.46218 # 0.743760
done
   
hadd -f AllGraphs.root Temp*root
rm Temp*root
