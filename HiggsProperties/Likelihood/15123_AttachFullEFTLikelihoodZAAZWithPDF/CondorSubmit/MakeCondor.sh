echo executable              = RunLikelihood.sh
echo universe                = vanilla
echo input                   =
echo should_transfer_files   = YES
echo transfer_output_files   = DummyFile
echo when_to_transfer_output = ON_EXIT
echo request_memory          = 2000
echo

for i in `cat FileList15251.txt | grep 13TeV`
do
   echo arguments               = OriginalTrees15251/$i AttachedTrees15251/$i 31426 13
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

for i in `cat FileList15251.txt | grep 14TeV`
do
   echo arguments               = OriginalTrees15251/$i AttachedTrees15251/$i 31426 14
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

for i in `cat FileList15251.txt | grep -v 13TeV | grep -v 14TeV`
do
   echo arguments               = OriginalTrees15251/$i AttachedTrees15251/$i 31426 0
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done



