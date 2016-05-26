echo executable              = RunLikelihood.sh
echo universe                = vanilla
echo input                   =
echo should_transfer_files   = YES
echo transfer_output_files   = DummyFile
echo when_to_transfer_output = ON_EXIT
echo request_memory          = 2000
echo

for i in `cat FileList15265.txt | grep 13TeV | grep gg`
do
   echo arguments               = OriginalTrees15265/$i AttachedTrees15265/$i 31426 13
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

for i in `cat FileList15265.txt | grep 14TeV | grep gg`
do
   echo arguments               = OriginalTrees15265/$i AttachedTrees15265/$i 31426 14
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

for i in `cat FileList15265.txt | grep -v 13TeV | grep -v 14TeV | grep gg`
do
   echo arguments               = OriginalTrees15265/$i AttachedTrees15265/$i 31426 0
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

for i in `cat FileList15265.txt | grep 13TeV | grep -v gg`
do
   echo arguments               = OriginalTrees15265/$i AttachedTrees15265/$i -1 13
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

for i in `cat FileList15265.txt | grep 14TeV | grep -v gg`
do
   echo arguments               = OriginalTrees15265/$i AttachedTrees15265/$i -1 14
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

for i in `cat FileList15265.txt | grep -v 13TeV | grep -v 14TeV | grep -v gg`
do
   echo arguments               = OriginalTrees15265/$i AttachedTrees15265/$i -1 0
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done





