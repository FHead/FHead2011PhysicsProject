cat Cleaned/Function_EEEE_*R_*R > CalculateME_Part47.cpp
cat Cleaned/Function_EEEE_*R_*I > CalculateME_Part48.cpp
cat Cleaned/Function_EEEE_*I_*R > CalculateME_Part49.cpp
cat Cleaned/Function_EEEE_*I_*I > CalculateME_Part50.cpp
cat Cleaned/Function_EEMM_*R_*R > CalculateME_Part51.cpp
cat Cleaned/Function_EEMM_*R_*I > CalculateME_Part52.cpp
cat Cleaned/Function_EEMM_*I_*R > CalculateME_Part53.cpp
cat Cleaned/Function_EEMM_*I_*I > CalculateME_Part54.cpp

for i in EEMM EEEE
do
   grep $i Header | grep -v I_ > ${i}RR
   grep $i Header | grep -v R_ > ${i}II
   grep $i Header | grep R_A | grep I_1 > ${i}RI
   grep $i Header | grep I_A | grep R_1 > ${i}IR
done

cp ../../CommonCode/source/MEFunctions.cpp Meow0

for i in EEMM EEEE
do
   for j in RR II RI IR
   do
      cat Meow0 > Meow1
      echo "double CalculateSpin2XVV_${i}_${j}_15764(LeptonVectors &Leptons, ExtendedAVVBasis &A, ZPrimeParameters &P)" >> Meow1
      echo "{" >> Meow1
      echo "   return" >> Meow1
      cat ${i}${j} >> Meow1
      echo "}" >> Meow1
      echo "" >> Meow1
      mv Meow1 Meow0
   done
done



