for i in `cat ListOfSeeds.txt`
do
   root -l -b -q 'CheckRate.C("HLT_'$i'")' | grep ^HLT
done > Result.txt
