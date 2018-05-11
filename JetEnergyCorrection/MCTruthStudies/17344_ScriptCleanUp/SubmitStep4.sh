source Setup_FileLocation.sh

Input=$WithPUFiles
Output=$Step4Output

Count=0
for i in `ls $Input | Reformat 20 | tr ' ' ':'`
do
   echo $i
   File=`echo $i | tr ':' ' '`
   cat RunFile.sh \
      | sed "s#__FILE__#$File#g" \
      | sed "s#__ID__#$Count#g" \
      | sed "s#__WORKDIR__#`pwd`#g" \
      | sed "s#__OUTPUT__#$Output#" \
      | bsub -J Closure
   Count=`echo $Count | AddConst 1`
done
