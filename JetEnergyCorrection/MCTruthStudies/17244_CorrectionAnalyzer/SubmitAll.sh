for i in `ls SimplePU/`
do
   echo $i
   cat RunFile.sh | \
      sed "s#__FILE__#$i#g" | \
      bsub -J ResponseAnalyzer
done
