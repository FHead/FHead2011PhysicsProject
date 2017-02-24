for i in LSFJOB_*/STDOUT
do
   if grep -q "Jet" $i; then
      echo $i
   else
      rm $i
      rm `dirname $i`/LSFJOB
      rmdir `dirname $i`
   fi
done
