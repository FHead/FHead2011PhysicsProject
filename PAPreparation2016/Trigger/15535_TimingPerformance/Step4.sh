for i in Output.step3_*
do
   ./RunMeanRMS < $i > ${i/step3/step4}
done
