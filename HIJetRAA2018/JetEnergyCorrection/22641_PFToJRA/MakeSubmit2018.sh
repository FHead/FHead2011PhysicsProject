echo "Universe              = vanilla"
echo "Executable            = `pwd`/RunFile.sh"
echo "should_transfer_files = NO"
echo

for i in Data2018/*/*/*root
do
   j=`echo $i | cut -d '_' -f 3`

   echo "Arguments = `pwd` `pwd`/$i `pwd`/Output2018/JRA_$j" true
   echo "Output    = Log/Step1NoPU.out.\$(Process)"
   echo "Error     = Log/Step1NoPU.err.\$(Process)"
   echo "Log       = Log/Step1NoPU.log.\$(Process)"
   echo "Queue"
   echo
done



