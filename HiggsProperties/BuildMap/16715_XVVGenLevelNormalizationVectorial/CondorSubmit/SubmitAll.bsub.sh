for i in `seq 101 1000`
do
   cat BatchTemplate.submit | \
      sed "s#__EXECUTABLE__#`pwd`/../Run#g" | \
      sed "s#__RUNNUMBER__#$i#g" | \
      sed "s#__RESULT__#`pwd`/Result_${i}.txt#g" | bsub -J SignalNormalization
done
