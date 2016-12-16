#!/bin/sh

for i in AA6Dijet AA8Dijet PP6Dijet PP8Dijet HydjetMB
do
   hadd -f -k ${i}.root Result/${i}*.root
   ./a.out ${i}.root Plots/${i}
done

for i in `ls Plots | grep pdf`
do
   cp Plots/$i RenamedPlots/15512_JetMassDR_$i
done
