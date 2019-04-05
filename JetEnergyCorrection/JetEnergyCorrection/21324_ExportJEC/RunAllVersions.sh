#!/bin/bash

# for i in `ls JECDatabase`
for i in `cat PriorityList`
do
   if [[ $i == *"DATA" ]] || [[ $i == *"MC" ]]; then
      echo Running version $i
      bash MakeSingleData.sh $i > Fragments/${i}.txt
   fi
done
