echo executable              = RunLikelihood.sh
echo universe                = vanilla
echo input                   =
echo should_transfer_files   = YES
echo transfer_output_files   = DummyFile
echo when_to_transfer_output = ON_EXIT
echo

for i in `cat FileList13435.txt`
do
   echo arguments               = OriginalTrees13435/$i AttachedTrees13435/$i
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done


