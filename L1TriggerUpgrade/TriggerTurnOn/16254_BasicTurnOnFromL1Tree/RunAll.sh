for i in `ls SampleBase/ | grep Neutrino`
do
   echo $i
   mkdir -p Result/$i

   for j in `ls SampleBase/$i/`
   do
      root -l -b -q "run.C(\"$i/$j\")"
   done
done

