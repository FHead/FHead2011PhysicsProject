# echo MAIN FILE
# (cat -n source/CalculateME.cpp | grep "double Get" | sed "s/(/ /g" | awk '{print $1, $3}'; \
# cat -n source/CalculateME.cpp | grep "complex<double> Get" | sed "s/(/ /g" | awk '{print $1, $3}') | sort -n

echo SPLITTED FILE
for i in source/CalculateME_Part*.cpp;
do
   echo $i
   (cat -n $i | grep "double Get" | sed "s/(/ /g" | awk '{print $1, $3}'; \
      cat -n $i | grep "complex<double> Get" | sed "s/(/ /g" | awk '{print $1, $3}') | sort -n
   echo
done

