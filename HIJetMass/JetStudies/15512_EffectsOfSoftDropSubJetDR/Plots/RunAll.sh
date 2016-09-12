#!/bin/sh

for i in AA6Dijet AA8Dijet PP6Dijet PP8Dijet HydjetMB
do
   hadd -f -k ${i}.root Result/${i}*.root
   ./a.out ${i}.root Plots/${i}
done
