source Setup_FileLocation.sh

mkdir -p $Step1Output/ResultNoPU $Step1Output/ResultWithPU

Input=$NoPUFiles
for i in $Input
do
   cat Step1ListRunLumi.sh \
      | sed "s#__FILE__#$i#" \
      | sed "s#__OUTPUT__#$Step1Output/ResultNoPU/`basename $i | sed "s/root/txt/g"`#" \
      | sed "s#__WORKDIR__#`pwd`#" \
      | bsub
done
 
Input=$WithPUFiles
for i in $Input
do
   cat Step1ListRunLumi.sh \
      | sed "s#__FILE__#$i#" \
      | sed "s#__OUTPUT__#$Step1Output/ResultWithPU/`basename $i | sed "s/root/txt/g"`#" \
      | sed "s#__WORKDIR__#`pwd`#" \
      | bsub
done

