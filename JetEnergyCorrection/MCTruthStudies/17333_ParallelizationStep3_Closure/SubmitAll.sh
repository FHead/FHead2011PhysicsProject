Count=0
for i in `ls $PWD/MagdaWithPU/*/*root | Reformat 20 | tr ' ' ':'`
do
   echo $i
   File=`echo $i | tr ':' ' '`
   cat RunFile.sh \
      | sed "s#__FILE__#$File#g" \
      | sed "s#__ID__#$Count#g" \
      | bsub -J Closure
   Count=`echo $Count | AddConst 1`
done
