echo "Universe              = vanilla"
echo "Executable            = `pwd`/RunFile.sh"
echo "should_transfer_files = NO"
echo

for i in JRA2017/*root
do
   j=`echo $i | cut -d '_' -f 2`

   echo "Arguments = `pwd` `pwd`/$i `pwd`/Output2017/jra_$j"
   echo "Output    = Log/jra.out.\$(Process)"
   echo "Error     = Log/jra.err.\$(Process)"
   echo "Log       = Log/jra.log.\$(Process)"
   echo "Queue"
   echo
done



