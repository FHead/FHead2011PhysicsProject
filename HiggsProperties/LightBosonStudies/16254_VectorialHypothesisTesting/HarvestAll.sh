#!/bin/sh

function CollectLikelihood()
{
   mkdir -p ExportedLikelihood

   echo Collecting likelihoods

   for i in `ls Result/ | cut -d '_' -f 1,2,3,5 | sort | uniq`
   do
      echo ${i/.bz2}

      bunzip2 Result/`echo $i | cut -d '_' -f 1,2,3`_*_`echo $i | cut -d '_' -f 4`

      cat Result/`echo $i | cut -d '_' -f 1,2,3`_*_`echo ${i/.bz2} | cut -d '_' -f 4` | \
         grep -v nan > ExportedLikelihood/${i/.bz2}

      bzip2 Result/`echo $i | cut -d '_' -f 1,2,3`_*_`echo ${i/.bz2} | cut -d '_' -f 4`
      bzip2 ExportedLikelihood/${i/.bz2}
   done
}

function HypothesisTesting()
{
   CompileRootMacro Harvesting.cpp DoHarvest

   mkdir -p ModelComparison
   mkdir -p PDF

   echo Start doing hypothesis testing

   for Cut in P #F P
   do
      for Scenario in `seq 10 29` #`seq 0 29`
      do
         for Model1 in A1UU A1UUpA2UURI A1UUpA3UU A1UZ A1UZpA2UA A2UA A2UApA2UZ A2UU A2UZ A3UU A2UA
         do
            for Model2 in A1UU A1UUpA2UURI A1UUpA3UU A1UZ A1UZpA2UA A2UA A2UApA2UZ A2UU A2UZ A3UU A2UA
            do
               if [[ "$Model1" > "$Model2" ]]
               then
                  for Type in Floated_10 #Fixed_00 Floated_10 FixedA2UV_01 FloatedA2UV_11
                  do
                     InputType=`echo $Type | cut -d '_' -f 1`
                     OutputType=`echo $Type | cut -d '_' -f 2`

                     # bunzip2 ExportedLikelihood/Likelihood${InputType}_${Model1}_${Cut}_Scenario${Scenario}.bz2
                     # bunzip2 ExportedLikelihood/Likelihood${InputType}_${Model2}_${Cut}_Scenario${Scenario}.bz2

                     time ./DoHarvest $Model1 $Model2 $Cut $Scenario \
                        ExportedLikelihood/Likelihood${InputType}_${Model1}_${Cut}_Scenario$Scenario \
                        ExportedLikelihood/Likelihood${InputType}_${Model2}_${Cut}_Scenario$Scenario \
                        $OutputType

                     # bzip2 ExportedLikelihood/Likelihood${InputType}_${Model1}_${Cut}_Scenario${Scenario}
                     # bzip2 ExportedLikelihood/Likelihood${InputType}_${Model2}_${Cut}_Scenario${Scenario}
                  done
               fi
            done
         done
      done
   done
}

# CollectLikelihood
HypothesisTesting

