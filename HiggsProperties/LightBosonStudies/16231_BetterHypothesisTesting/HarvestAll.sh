#!/bin/sh

# ./a.out Model1 Model2 Cut Scenario File1 File2

mkdir -p ExportedLikelihood

echo Collecting likelihoods

# for i in `ls Result/ | cut -d '_' -f 1,2,3,5 | sort | uniq`
# do
#    echo ${i/.bz2}
# 
#    bunzip2 Result/`echo $i | cut -d '_' -f 1,2,3`_*_`echo $i | cut -d '_' -f 4`
# 
#    cat Result/`echo $i | cut -d '_' -f 1,2,3`_*_`echo ${i/.bz2} | cut -d '_' -f 4` | \
#       grep -v nan > ExportedLikelihood/${i/.bz2}
#    
#    bzip2 Result/`echo $i | cut -d '_' -f 1,2,3`_*_`echo ${i/.bz2} | cut -d '_' -f 4`
#    bzip2 ExportedLikelihood/${i/.bz2}
# done

mkdir -p ModelComparison
mkdir -p PDF

echo Start doing hypothesis testing

for Cut in F P
do
   for Scenario in `seq 0 29`
   do
      for Model1 in A1UU A2UA A2UU A2UZ A1UUpA3UU 
      do
         for Model2 in A1UU A2UA A2UU A2UZ A1UUpA3UU 
         do
            if [[ "$Model1" > "$Model2" ]]
            then
               for Type in Fixed_00 Floated_10 FixedA2UV_01 FloatedA2UV_11
               do
                  InputType=`echo $Type | cut -d '_' -f 1`
                  OutputType=`echo $Type | cut -d '_' -f 2`

                  bunzip2 ExportedLikelihood/Likelihood${InputType}_${Model1}_${Cut}_Scenario${Scenario}.bz2
                  bunzip2 ExportedLikelihood/Likelihood${InputType}_${Model2}_${Cut}_Scenario${Scenario}.bz2

                  ./a.out $Model1 $Model2 $Cut $Scenario \
                     ExportedLikelihood/Likelihood${InputType}_${Model1}_${Cut}_Scenario$Scenario \
                     ExportedLikelihood/Likelihood${InputType}_${Model2}_${Cut}_Scenario$Scenario \
                     $OutputType

                  bzip2 ExportedLikelihood/Likelihood${InputType}_${Model1}_${Cut}_Scenario${Scenario}
                  bzip2 ExportedLikelihood/Likelihood${InputType}_${Model2}_${Cut}_Scenario${Scenario}
               done
            fi
         done
      done
   done
done




