#!/bin/bash

Input=HLTRatesAll.txt
Trigger=HLT_PuAK4CaloJet40Eta5p1_v1

Input=$1
Trigger=$2

All=`bzgrep $Trigger $Input | awk '{print $5}' | Sum`
Pass=`bzgrep $Trigger $Input | awk '{print $6}' | Sum`

Percentage=`echo $Pass | DivideConst $All | MultiplyConst 100`

echo "$Trigger: $Pass / $All = $Percentage%"



