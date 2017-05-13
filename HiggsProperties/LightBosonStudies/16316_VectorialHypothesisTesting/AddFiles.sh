for i in `ls Result/ | cut --delim='_' --field=2 | sort | uniq`
do
   echo $i
   hadd -f CombinedResult/Likelihood_${i}.root Result/Likelihood_${i}_*root
done
