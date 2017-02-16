for i in `ls CleanTrees | grep Mini`
do
   echo $i
   ./RunSignal CleanTrees/$i 0 200000 > BatchResult/${i}_SignalLog
   ./RunBackground CleanTrees/$i 0 200000 > BatchResult/${i}_BackgroundLog
done
