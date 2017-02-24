# ls Output/HLT*root > AllFiles
# echo 'Sleeping for 10 seconds to allow files to finish transferring (if any)'
# sleep 10

for i in `cat AllFiles | sed "s#Output/##g" | grep ^HLT | rev | cut --delim='_' --field=2- | rev | sort | uniq`
do
   echo $i

   hadd -f7 /tmp/chenyi/${i}_Merged.root `cat AllFiles | grep $i`
done
