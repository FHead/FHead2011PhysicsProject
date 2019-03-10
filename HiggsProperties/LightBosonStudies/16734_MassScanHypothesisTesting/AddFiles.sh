for i in `ls Result/ | cut -d '_' -f 2,3,5 | sort | uniq | sed "s/.root//"`
do
   echo $i
   A=`echo $i | cut -d '_' -f 1,2`
   B=`echo $i | cut -d '_' -f 3`
   hadd -f CombinedResult/Likelihood_${A}_${B}.root Result/Likelihood_${A}_*_${B}.root
done
