mkdir -p CombinedResult/
for i in `ls Result | cut --delim='_' --field=2-3 | sort | uniq`
do
   hadd -f -k CombinedResult/Output_${i}.root Result/Output_${i}_*
done
