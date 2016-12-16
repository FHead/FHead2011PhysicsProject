#!/bin/sh

for i in PP8Dijet PP6Dijet AA8Dijet AA6Dijet HydjetMB PPDataHighPTJet AAData AADataMB
do
   hadd -f -k ${i}.root Result/${i}*.root
   ./a.out ${i}.root ${i}
done

mkdir -p RenamedPlots
for i in *pdf
do
   cp $i RenamedPlots/15473_JetComposition_$i
done
