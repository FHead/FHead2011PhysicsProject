#!/bin/sh

mkdir -p Temp

# for i in EventF.root EventGd.root \
#    EventXi1N1.root EventXi1N2.root EventXi1N3.root EventXi1N4.root \
#    EventXi1P1.root EventXi1P2.root EventXi1P3.root EventXi1P4.root EventXi1P5.root \
#    EventXi2N1.root EventXi2N2.root EventXi2N3.root EventXi2N4.root \
#    EventXi2P1.root EventXi2P2.root EventXi2P3.root EventXi2P4.root EventXi2P5.root
# for i in EventXi3N1.root EventXi3N2.root EventXi3N3.root EventXi3N4.root \
#     EventXi3P1.root EventXi3P2.root EventXi3P3.root EventXi3P4.root EventXi3P5.root
for i in EventXi2N1.root EventXi2N2.root EventXi2N3.root EventXi2N4.root \
  EventXi2P1.root EventXi2P2.root EventXi2P3.root EventXi2P4.root EventXi2P5.root \
  Madgraph2e2mu_part1.root Madgraph4e_part1.root
do
   for j in Central LeptonUp LeptonDown LeptonWide LeptonNarrow \
      BCentral BLeptonUp BLeptonDown BLeptonWide BLeptonNarrow
   do
      cat BatchResult/${i}_* | grep "^$i " | grep " $j " \
         | cut --delim=' ' --field=3- > Temp/SynthesizedLog_${i}_${j}.txt
   done
done


