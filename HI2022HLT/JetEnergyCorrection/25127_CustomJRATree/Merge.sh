#!/bin/bash

mkdir -p Output/Merged/

for i in `seq 1 52`
do
   hadd /tmp/chenyi/JRA_${i}.root Output/JRA_${i}_*.root
   mv /tmp/chenyi/JRA_${i}.root Output/Merged/
done

