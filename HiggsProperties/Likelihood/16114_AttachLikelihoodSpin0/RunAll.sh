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
   ./RunSignal OriginalTrees$D/$i 0 9999999 -1 0 | grep $i | cut --delim=' ' --field=3- > BatchResult/${i}_SignalLog
   ./RunBackground OriginalTrees$D/$i 0 9999999 -1 0 | grep $i | cut --delim=' ' --field=3- > BatchResult/${i}_BackgroundLog

   cp OriginalTrees$D/$i .
   ./AttachBranch BranchCentralSignal BatchResult/${i}_SignalLog $i 
   ./AttachBranch BranchCentralBackground BatchResult/${i}_BackgroundLog $i 
   mv $i AttachedTrees$D/
done
