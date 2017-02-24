FILE=FileList16141
OutputBase=AttachedTrees16141
InputBase=OriginalTrees16141
# OutputBase=/home/yichen/PhysicsWorkspace/HiggsProperties/Likelihood/16114_AttachLikelihoodSpin0/CondorSubmit

echo executable              = RunLikelihood.sh
echo universe                = vanilla
echo input                   =
echo should_transfer_files   = YES
echo transfer_output_files   = DummyFile
echo when_to_transfer_output = ON_EXIT
echo request_memory          = 2000
echo

for i in `cat $FILE`
do
   echo arguments               = $InputBase/$i $OutputBase/$i -1 0
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

exit

for i in `cat $FILE | grep 13TeV | grep gg`
do
   echo arguments               = $InputBase/$i $OutputBase/$i 31426 13
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

for i in `cat $FILE | grep 14TeV | grep gg`
do
   echo arguments               = $InputBase/$i $OutputBase/$i 31426 14
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

for i in `cat $FILE | grep -v 13TeV | grep -v 14TeV | grep gg`
do
   echo arguments               = $InputBase/$i $OutputBase/$i 31426 0
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

for i in `cat $FILE | grep 13TeV | grep -v gg`
do
   echo arguments               = $InputBase/$i $OutputBase/$i -1 13
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

for i in `cat $FILE | grep 14TeV | grep -v gg`
do
   echo arguments               = $InputBase/$i $OutputBase/$i -1 14
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done

for i in `cat $FILE | grep -v 13TeV | grep -v 14TeV | grep -v gg`
do
   echo arguments               = $InputBase/$i $OutputBase/$i -1 0
   echo output                  = Log/Run_${i/.root/}.out
   echo error                   = Log/Run_${i/.root/}.err
   echo log                     = Log/Run_${i/.root/}.log
   echo queue
   echo
done





