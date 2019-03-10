for i in `cat ResultNoPU/*txt | awk '{print $2}' | grep ^[0-9] | sort -n | uniq`
do
   File1=`grep " $i " ResultNoPU/*txt | awk '{print $3}'`
   File2=`grep " $i " ResultWithPU/*txt | awk '{print $3}'`
   echo $i $File1 $File2
done | tee MatchedFiles



