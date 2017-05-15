#!/bin/sh

function HypothesisTesting()
{
   CompileRootMacro Harvesting.cpp DoHarvest

   mkdir -p ModelComparison
   mkdir -p PDF

   echo Start doing hypothesis testing

   for Model1 in A1UU A1UUpA2UURI A1UUpA3UU A1UZ A1UZpA2UA A2UA A2UApA2UZ A2UU A2UZ A3UU A2UA
   do
      for Model2 in A1UU A1UUpA2UURI A1UUpA3UU A1UZ A1UZpA2UA A2UA A2UApA2UZ A2UU A2UZ A3UU A2UA
      do
         if [[ "$Model1" > "$Model2" ]]
         then
            ./DoHarvest $Model1 $Model2 \
               CombinedResult/Likelihood_${Model1}.root CombinedResult/Likelihood_${Model2}.root
         fi
      done
   done
}

HypothesisTesting

