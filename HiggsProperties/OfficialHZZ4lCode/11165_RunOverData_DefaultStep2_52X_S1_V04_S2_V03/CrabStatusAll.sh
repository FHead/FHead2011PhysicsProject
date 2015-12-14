#!/bin/sh

for i in `ls | grep ^crab_0_ | grep -v cfg$`
do
   crab -status -c $i
done



