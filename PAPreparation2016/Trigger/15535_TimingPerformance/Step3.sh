TempFile1=asjldkfjaklsqwehutivhqweuithvuwh
TempFile2=asdhaighewuhvaiwhuvnwunuwehvuhvd

for i in `ls *.step2_* | rev | cut --delim='_' --field=1 | rev | sort | uniq`
do
   CombinedFile=Output.step3_$i

   grep "^[ ]*[0-9]" `ls *.step2_$i | head -1` | \
      awk '{print $3}' > $CombinedFile

   for j in `ls *.step2_$i`
   do
      grep "^[ ]*[0-9]" $j | awk '{print $1,$2}' > $TempFile1
      FileLineAppend $CombinedFile $TempFile1 $TempFile2
      mv $TempFile2 $CombinedFile
   done

   rm -f $TempFile1 $TempFile2
done
