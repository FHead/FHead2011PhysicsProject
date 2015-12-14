CompileRootMacro MakeGraph.cpp RunGraph

rm Trees1GeV Trees2GeV
ln -s ../../Fitting/13555_GenFullFittingWithPDF/CondorSubmit/CollectedResults/ Trees2GeV
ln -s ../../Fitting/13674_GenFullFittingWithPDF1GeV/CondorSubmit/CollectedResults/ Trees1GeV

rm Trees
ln -s ../../Fitting/13555_GenFullFittingWithPDF/CondorSubmit/CollectedResults/ Trees

for i in Both BothS EMS EES
do
   ./RunGraph Temp_${i}_A.root ${i} A 0.44359 # 0.727693
   ./RunGraph Temp_${i}_B.root ${i} B 0.35322 # 0.590503
   ./RunGraph Temp_${i}_C.root ${i} C 0.35221 # 0.590509
   ./RunGraph Temp_${i}_D.root ${i} D 0.48706 # 0.797016
   ./RunGraph Temp_${i}_E.root ${i} E 0.46201 # 0.759701
   ./RunGraph Temp_${i}_F.root ${i} F 0.94703 # 0.999653
   ./RunGraph Temp_${i}_G.root ${i} G 0.48179 # 0.799547
   ./RunGraph Temp_${i}_H.root ${i} H 0.48739 # 0.797664
   ./RunGraph Temp_${i}_I.root ${i} I 0.37430 # 0.601295
   ./RunGraph Temp_${i}_J.root ${i} J 0.46218 # 0.743760
   ./RunGraph Temp_${i}_K.root ${i} K 0.35438 # 0.572263
done
   
./RunGraph Temp_BothHalf_J.root BothHalf J 0.46218 # 0.743760

hadd -f AllGraphs.root Temp*root
rm Temp*root

rm Trees
ln -s ../../Fitting/13674_GenFullFittingWithPDF1GeV/CondorSubmit/CollectedResults/ Trees

for i in Both BothS EMS EES
do
   ./RunGraph Temp_${i}_A.root ${i} A 0.44359 # 0.727693
   ./RunGraph Temp_${i}_H.root ${i} H 0.48739 # 0.797664
   ./RunGraph Temp_${i}_I.root ${i} I 0.37430 # 0.601295
   ./RunGraph Temp_${i}_J.root ${i} J 0.46218 # 0.743760
done
 
hadd -f AllGraphs1GeV.root Temp*root
rm Temp*root
