# for i in `ls CleanTrees | grep Mini`
# do
#    echo $i
#    ./RunSignal CleanTrees/$i 0 200000 > BatchResult/${i}_SignalLog
#    ./RunBackground CleanTrees/$i 0 200000 > BatchResult/${i}_BackgroundLog
# done

D=16141

mkdir -p BatchResult
for i in `ls OriginalTrees$D`
do
   echo $i
   
   cp OriginalTrees$D/$i $D$i
   
   time ./RunSignal $D$i 0 9999999 -1 0 | grep $i | cut --delim=' ' --field=3- > BatchResult/${i}_SignalLog
   time ./RunBackground $D$i 0 9999999 -1 0 | grep $i | cut --delim=' ' --field=3- > BatchResult/${i}_BackgroundLog

   time ./AttachBranch BranchCentralSignal BatchResult/${i}_SignalLog $D$i 
   time ./AttachBranch BranchCentralBackground BatchResult/${i}_BackgroundLog $D$i 
   mv $D$i AttachedTrees$D/$i
done
