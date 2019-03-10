#!/bin/sh/

for i in 1 2 4
do
   Base=/eos/project/j/jetquenching/JetWorkshop2017/samples/qpythiaQhat$i/5TeV/pthat80/
   hadd -f /tmp/chenyi/All.root $Base/*root
   ./a.out /tmp/chenyi/All.root /tmp/chenyi/QPythia
   mv /tmp/chenyi/*pu14 $Base/
done
