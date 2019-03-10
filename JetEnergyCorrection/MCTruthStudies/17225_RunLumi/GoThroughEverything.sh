for i in SimpleNoPU/*root
do
   cat RunFile.sh \
      | sed "s#__FILE__#`pwd`/$i#" \
      | sed "s#__OUTPUT__#`pwd`/ResultSimpleNoPU/`basename $i | sed "s/root/txt/g"`#" \
      | bsub
done
 
for i in SimplePU/*root
do
   echo $i
   cat RunFile.sh \
      | sed "s#__FILE__#`pwd`/$i#" \
      | sed "s#__OUTPUT__#`pwd`/ResultSimplePU/`basename $i | sed "s/root/txt/g"`#" \
      | bsub
done

exit

for i in MagdaNoPU/*/*root
do
   cat RunFile.sh \
      | sed "s#__FILE__#`pwd`/$i#" \
      | sed "s#__OUTPUT__#`pwd`/ResultNoPU/`basename $i | sed "s/root/txt/g"`#" \
      | bsub
done
 
for i in MagdaWithPU/*/*root
do
   echo $i
   cat RunFile.sh \
      | sed "s#__FILE__#`pwd`/$i#" \
      | sed "s#__OUTPUT__#`pwd`/ResultWithPU/`basename $i | sed "s/root/txt/g"`#" \
      | bsub
done
