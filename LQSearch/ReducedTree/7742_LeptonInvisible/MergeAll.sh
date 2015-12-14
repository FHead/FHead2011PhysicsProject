#!/bin/sh

for i in `ls | sed "s/_[0-9]*.root//g" | uniq`
do
   hadd /wntmp/yichen/Merging/${i}_All.root $i*.root
done




