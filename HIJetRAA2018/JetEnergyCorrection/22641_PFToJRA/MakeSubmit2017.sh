echo "Universe              = vanilla"
echo "Executable            = `pwd`/RunFile.sh"
echo "should_transfer_files = NO"
echo

for i in Data2017/*root
do
   j=`echo $i | cut -d '_' -f 2`

   echo "Arguments = `pwd` `pwd`/$i `pwd`/Output2017/JRA_$j" false
   echo "Output    = Log/Step1NoPU.out.\$(Process)"
   echo "Error     = Log/Step1NoPU.err.\$(Process)"
   echo "Log       = Log/Step1NoPU.log.\$(Process)"
   echo "Queue"
   echo
done



