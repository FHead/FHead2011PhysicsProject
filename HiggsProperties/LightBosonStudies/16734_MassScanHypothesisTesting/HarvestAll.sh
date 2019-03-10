#!/bin/sh

function TestOnePair()
{
   Model1=$1
   Model2=$2
   Mass=$3

   if [[ "$Model1" < "$Model2" ]]
   then
      Temp=$Model1
      Model1=$Model2
      Model2=$Temp
   fi

   ./DoHarvest $Model1 $Model2 $Mass \
      CombinedResult/Likelihood_${Model1}_P_${Mass}.root \
      CombinedResult/Likelihood_${Model2}_P_${Mass}.root
}

function HypothesisTesting()
{
   mkdir -p ModelComparison
   mkdir -p PDF

   echo Start doing hypothesis testing

   for Mass in 18p4 18p8 18p9 18p92 18p94 19p0 19p3
   do
      for Model1 in A1UU A2UU A3UU A2UA A2UZ A1UZ
      do
         for Model2 in A1UU A2UU A3UU A2UA A2UZ A1UZ
         do
            if [[ "$Model1" > "$Model2" ]]
            then
               TestOnePair($Model1, $Model2, $Mass)
            fi
         done
      done
   done
}

HypothesisTesting

