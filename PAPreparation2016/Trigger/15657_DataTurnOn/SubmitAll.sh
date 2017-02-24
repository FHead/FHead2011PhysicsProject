for Location in `cat Input2`
do
   Run2=`basename $Location`
   Run1=`basename \`dirname $Location\``
   Version=`basename \`dirname \\\`dirname \\\\\\\`dirname $Location\\\\\\\`\\\`\``

   echo $Location $Version $Run1 $Run2

   Count=0
   for i in `ls ~/EOS/cms/$Location`
   do
      Count=`echo $Count | AddConst 1`
      echo $Count $i

      Input=$Location/$i
      Output=Output_${Version}_${Run1}${Run2}_${Count}.root

      cat RunBatch.sh \
         | sed "s#__RUN__#$Run1$Run2#g" \
         | sed "s#__INPUT__#$Input#g" \
         | sed "s#__OUTPUT__#$Output#g" \
         | bsub -J TurnOn_${Version}_${Run1}${Run2}
   done
done




