#!/bin/bash

for i in `cat PriorityListJER`
do
   echo Running version $i
   bash MakeSingleDataJER.sh $i > Fragments/JER_${i}.txt
done
