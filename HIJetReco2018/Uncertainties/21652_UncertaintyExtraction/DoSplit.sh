#!/bin/bash

Input=Autumn18_V18_DATA_UncertaintySources_AK4PFchs.txt
Input=Fall17_17Nov2017F_V32_DATA_UncertaintySources_AK4PFchs.txt

csplit $Input /]/ {*}
rm xx00

for i in xx*
do
   Tag=`head -n1 $i | tr -d '[]'`

   tail -n+2 $i > Uncertainty_${Tag}.txt
   rm $i
done



