#!/bin/sh

echo > FinalFile.cpp
echo "#include <cmath>" >> FinalFile.cpp
echo "#include <iostream>" >> FinalFile.cpp
echo "#include <complex>" >> FinalFile.cpp
echo "using namespace std;" >> FinalFile.cpp
echo "" >> FinalFile.cpp
echo "#include \"CalculateME.h\"" >> FinalFile.cpp
echo "#include \"AngleConversion.h\"" >> FinalFile.cpp
echo "#include \"Constants.h\"" >> FinalFile.cpp
echo "" >> FinalFile.cpp

for i in `sh ListComponents.sh | grep ^Parts | grep A[1-3] | sed "s/ /_/g"`
do
   FileName=`echo $i | sed "s/.txt_/.txt /" | awk '{print $1}'`
   Components=`echo $i | sed "s/.txt_/.txt /" | awk '{print $2}'`
   FileBase=`echo $FileName | sed "s/.txt//" | sed "s/s\_//"`

   echo $FileBase: $Components

   Arguments=
   for j in `echo $Components | sed "s/_/ /g"`
   do
      Arguments="$Arguments, double $j"
   done

   echo "double GetGeneralScalar2e2mu_$FileBase(LeptonVectors &leptons$Arguments)" >> FinalFile.cpp
   echo "{" >> FinalFile.cpp
   cat Header.txt >> FinalFile.cpp
   echo -n "return " >> FinalFile.cpp
   cat $FileName >> FinalFile.cpp
   echo ";" >> FinalFile.cpp
   echo "}" >> FinalFile.cpp
   echo >> FinalFile.cpp
done

cp FinalFile.cpp Temp.cpp
sed '/[0-9]*\./{N;s/\([0-9.]*\)\n[;]/\1;/}' < Temp.cpp > FinalFile.cpp
rm Temp.cpp


echo
echo Code to copy to the *.h file
grep "^double" FinalFile.cpp | tr '\n' ';' | sed "s/;/;\n/g"







