echo "Universe              = vanilla"
echo "Executable            = `pwd`/RunFile.sh"
echo "should_transfer_files = NO"
echo "requirements          = (OpSysAndVer =?= \"SLCern6\")"
echo "+JobFlavour           = \"longlunch\""
echo

Count=0
for i in `cat FileList`
do
   Count=`echo $Count | AddConst 1`
   echo "Arguments = `pwd` $i `pwd`/Output/HiForest_${Count}.root"
   echo "Output    = Log/out.\$(Process)"
   echo "Error     = Log/err.\$(Process)"
   echo "Log       = Log/log.\$(Process)"
   echo "Queue"
   echo
done
