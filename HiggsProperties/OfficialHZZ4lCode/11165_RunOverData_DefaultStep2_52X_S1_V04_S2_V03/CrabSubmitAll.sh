#!/bin/sh

for i in `ls | grep ^crab_0_ | grep -v cfg$`
do
   crab -submit -c $i
done



